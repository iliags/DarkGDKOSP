//=======================================
//NAVIGATION MESHES CPP
//Marabillas 2010
//=======================================

#include "hNavMesh.h"

hNavMesh::hNavMesh()
{
	//Default Variables
	m_cellSize = 3.0f;//0.3f;
	m_cellHeight = 2.0f;//0.2f;
	m_agentHeight = 2.0f;
	m_agentRadius = 0.6f;
	m_agentMaxClimb = 0.9f;
	m_agentMaxSlope = 45.0f;
	m_regionMinSize = 50;
	m_regionMergeSize = 20;
	m_edgeMaxLen = 12.0f;
	m_edgeMaxError = 1.3f;
	m_vertsPerPoly = 6.0f;
	m_detailSampleDist = 6.0f;
	m_detailSampleMaxError = 1.0f;

	//StatMeshSimple Variables
	m_keepInterResults=false;
}

hNavMesh::~hNavMesh()
{
	//Sample Variables
	delete [] m_verts;
	m_verts=0;
	delete [] m_tris;
	m_tris=0;

	//StatMesh Variables
	delete m_navMesh;
	m_navMesh=0;

	//StatMeshSimple Variables
	delete [] m_triflags;
	m_triflags = 0;
	delete m_solid;
	m_solid = 0;
	delete m_chf;
	m_chf = 0;
	delete m_cset;
	m_cset = 0;
	delete m_pmesh;
	m_pmesh = 0;
	delete m_dmesh;
	m_dmesh = 0;
}

void hNavMesh::LoadGDKObject( int pObjectID )
{
	if (dbMeshExist(MESHID_NAVMESH))
		dbDeleteMesh(MESHID_NAVMESH);
	dbMakeMeshFromObject(MESHID_NAVMESH, pObjectID);
	dbLockVertexDataForMesh(MESHID_NAVMESH);

	m_nverts=dbGetVertexDataVertexCount();
	m_ntris=dbGetVertexDataIndexCount();
	//m_nverts=m_ntris*3;
	m_tris=new int[m_ntris];
	
	m_verts=new float[m_nverts*3];
	
	for (int i=0;i<m_nverts;i++)
	{
		m_verts[i*3]=dbGetVertexDataPositionX(i);
		m_verts[i*3+1]=dbGetVertexDataPositionY(i);
		m_verts[i*3+2]=dbGetVertexDataPositionZ(i);
	}

	for (int i=0;i<m_ntris;i+=3)
	{
		m_tris[i]=dbGetIndexData(i);
		m_tris[i+1]=dbGetIndexData(i+1);
		m_tris[i+2]=dbGetIndexData(i+2);
	}

	m_ntris=m_ntris/3;
	dbUnlockVertexData();
	dbDeleteMesh(MESHID_NAVMESH);
}

bool hNavMesh::BuildNavigationMesh()
{
	if (!m_verts || ! m_tris)
	{
		//if(rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Input mesh is not specified.");
		return false;
	}
	
	//
	// Step 1. Initialize build config.
	//
	memset(&m_cfg, 0, sizeof(m_cfg));
	m_cfg.cs = m_cellSize;
	m_cfg.ch = m_cellHeight;
	m_cfg.walkableSlopeAngle = m_agentMaxSlope;
	m_cfg.walkableHeight = (int)ceilf(m_agentHeight / m_cfg.ch);
	m_cfg.walkableClimb = (int)ceilf(m_agentMaxClimb / m_cfg.ch);
	m_cfg.walkableRadius = (int)ceilf(m_agentRadius / m_cfg.cs);
	m_cfg.maxEdgeLen = (int)(m_edgeMaxLen / m_cellSize);
	m_cfg.maxSimplificationError = m_edgeMaxError;
	m_cfg.minRegionArea = (int)rcSqr(m_regionMinSize);
	m_cfg.mergeRegionArea = (int)rcSqr(m_regionMergeSize);
	m_cfg.maxVertsPerPoly = (int)m_vertsPerPoly;
	m_cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
	m_cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;
	
	//compute for bmin and bmax from mesh
	rcCalcBounds(m_verts,m_nverts,m_bmin,m_bmax);

	// Set the area where the navigation will be build.
	// Here the bounds of the input mesh are used, but the
	// area could be specified by an user defined box, etc.
	rcVcopy(m_cfg.bmin, m_bmin);
	rcVcopy(m_cfg.bmax, m_bmax);
	rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);

	// Reset build times gathering.
	/*
	memset(&m_buildTimes, 0, sizeof(m_buildTimes));
	rcSetBuildTimes(&m_buildTimes);
	*/

	// Start the build process.	
	//rcTimeVal totStartTime = rcGetPerformanceTimer();

	/*
	if (rcGetLog())
	{
		Context.log(RC_LOG_PROGRESS, "Building navigation:");
		Context.log(RC_LOG_PROGRESS, " - %d x %d cells", m_cfg.width, m_cfg.height);
		Context.log(RC_LOG_PROGRESS, " - %.1fK verts, %.1fK tris", m_nverts/1000.0f, m_ntris/1000.0f);
	}
	*/

	//
	// Step 2. Rasterize input polygon soup.
	//
	
	// Allocate voxel heighfield where we rasterize our input data to.
	m_solid = new rcHeightfield;
	if (!m_solid)
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
		return false;
	}
	if (!rcCreateHeightfield(m_context,*m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
	{
		//if (rcGetLog())	Context.log(RC_LOG_ERROR, "buildNavigation: Could not create solid heightfield.");
		return false;
	}
	
	// Allocate array that can hold triangle flags.
	// If you have multiple meshes you need to process, allocate
	// and array which can hold the max number of triangles you need to process.
	m_triflags = new unsigned char[m_ntris];
	if (!m_triflags)
	{
		//if (rcGetLog())	Context.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'triangleFlags' (%d).", m_ntris);
		return false;
	}
	
	// Find triangles which are walkable based on their slope and rasterize them.
	// If your input data is multiple meshes, you can transform them here, calculate
	// the flags for each of the meshes and rasterize them.
	memset(m_triflags, 0, m_ntris*sizeof(unsigned char));

	unsigned char* areas;

	rcMarkWalkableTriangles(m_context, m_cfg.walkableSlopeAngle, m_verts, m_nverts, m_tris, m_ntris, areas);
	rcRasterizeTriangles(m_context, m_verts, m_nverts, m_tris, m_triflags, m_ntris, *m_solid);

	if (!m_keepInterResults)
	{
		delete [] m_triflags;
		m_triflags = 0;
	}
	
	//
	// Step 3. Filter walkables surfaces.
	//
	
	// Once all geoemtry is rasterized, we do initial pass of filtering to
	// remove unwanted overhangs caused by the conservative rasterization
	// as well as filter spans where the character cannot possibly stand.
	rcFilterLedgeSpans(m_context, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
	rcFilterWalkableLowHeightSpans(m_context, m_cfg.walkableHeight, *m_solid);

	//
	// Step 4. Partition walkable surface to simple regions.
	//

	// Compact the heightfield so that it is faster to handle from now on.
	// This will result more cache coherent data as well as the neighbours
	// between walkable cells will be calculated.
	m_chf = new rcCompactHeightfield;
	if (!m_chf)
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'chf'.");
		return false;
	}
	if (!rcBuildCompactHeightfield(m_context, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Could not build compact data.");
		return false;
	}
	
	if (!m_keepInterResults)
	{
		delete m_solid;
		m_solid = 0;
	}
	
	// Prepare for region partitioning, by calculating distance field along the walkable surface.
	if (!rcBuildDistanceField(m_context, *m_chf))
	{
		//if (rcGetLog())	Context.log(RC_LOG_ERROR, "buildNavigation: Could not build distance field.");
		return false;
	}

	// Partition the walkable surface into simple regions without holes.
	if (!rcBuildRegions(m_context, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
	}
	
	//
	// Step 5. Trace and simplify region contours.
	//
	
	// Create contours.
	m_cset = new rcContourSet;
	if (!m_cset)
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'cset'.");
		return false;
	}
	if (!rcBuildContours(m_context, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Could not create contours.");
		return false;
	}
	
	//
	// Step 6. Build polygons mesh from contours.
	//
	
	// Build polygon navmesh from the contours.
	m_pmesh = new rcPolyMesh;
	if (!m_pmesh)
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmesh'.");
		return false;
	}
	if (!rcBuildPolyMesh(m_context, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Could not triangulate contours.");
		return false;
	}
	
	//
	// Step 7. Create detail mesh which allows to access approximate height on each polygon.
	//
	
	m_dmesh = new rcPolyMeshDetail;
	if (!m_dmesh)
	{
		//if (rcGetLog()) Context.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmdtl'.");
		return false;
	}

	if (!rcBuildPolyMeshDetail(m_context, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh))
	{
		//if (rcGetLog())	Context.log(RC_LOG_ERROR, "buildNavigation: Could not build detail mesh.");
		return false;
	}

	if (!m_keepInterResults)
	{
		delete m_chf;
		m_chf = 0;
		delete m_cset;
		m_cset = 0;
	}

	// At this point the navigation mesh data is ready, you can access it from m_pmesh.
	// See rcDebugDrawPolyMesh or dtCreateNavMeshData as examples how to access the data.
	
	//
	// (Optional) Step 8. Create Detour data from Recast poly mesh.
	//
	
	// The GUI may allow more max points per polygon than Detour can handle.
	// Only build the detour navmesh if we do not exceed the limit.
	
	if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
	{
		unsigned char* navData = 0;
		int navDataSize = 0;

		//place holders techlord 02/11/11
		dtNavMeshCreateParams* params;
		unsigned char** outData;
		int* outDataSize;

		if (!dtCreateNavMeshData(params, outData, outDataSize)
			/*	
			dtCreateNavMeshData(m_pmesh->verts, m_pmesh->nverts,
								 m_pmesh->polys, m_pmesh->npolys, m_pmesh->nvp,
								 m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch,
								 m_dmesh->meshes, m_dmesh->verts, m_dmesh->nverts, m_dmesh->tris, m_dmesh->ntris, 
								 &navData, &navDataSize
								 )
			 */
			)
		{
			//if(rcGetLog()) Context.log(RC_LOG_ERROR, "Could not build Detour navmesh.");
			return false;
		}
		
		m_navMesh = new dtNavMesh;
		if (!m_navMesh)
		{
			delete [] navData;
			//if(rcGetLog()) Context.log(RC_LOG_ERROR, "Could not create Detour navmesh");
			return false;
		}
		
		if (!m_navMesh->init(navData, navDataSize, true))
		{
			delete [] navData;
			//if(rcGetLog()) Context.log(RC_LOG_ERROR, "Could not init Detour navmesh");
			return false;
		}
	}
	
	//rcTimeVal totEndTime = rcGetPerformanceTimer();

	// Show performance stats.
	/*
	if (rcGetLog())
	{
		const float pc = 100.0f / rcGetDeltaTimeUsec(totStartTime, totEndTime);
		
		Context.log(RC_LOG_PROGRESS, "Rasterize: %.1fms (%.1f%%)", m_buildTimes.rasterizeTriangles/1000.0f, m_buildTimes.rasterizeTriangles*pc);
		
		Context.log(RC_LOG_PROGRESS, "Build Compact: %.1fms (%.1f%%)", m_buildTimes.buildCompact/1000.0f, m_buildTimes.buildCompact*pc);
		
		Context.log(RC_LOG_PROGRESS, "Filter Border: %.1fms (%.1f%%)", m_buildTimes.filterBorder/1000.0f, m_buildTimes.filterBorder*pc);
		Context.log(RC_LOG_PROGRESS, "Filter Walkable: %.1fms (%.1f%%)", m_buildTimes.filterWalkable/1000.0f, m_buildTimes.filterWalkable*pc);
		Context.log(RC_LOG_PROGRESS, "Filter Reachable: %.1fms (%.1f%%)", m_buildTimes.filterMarkReachable/1000.0f, m_buildTimes.filterMarkReachable*pc);
		
		Context.log(RC_LOG_PROGRESS, "Build Distancefield: %.1fms (%.1f%%)", m_buildTimes.buildDistanceField/1000.0f, m_buildTimes.buildDistanceField*pc);
		Context.log(RC_LOG_PROGRESS, "  - distance: %.1fms (%.1f%%)", m_buildTimes.buildDistanceFieldDist/1000.0f, m_buildTimes.buildDistanceFieldDist*pc);
		Context.log(RC_LOG_PROGRESS, "  - blur: %.1fms (%.1f%%)", m_buildTimes.buildDistanceFieldBlur/1000.0f, m_buildTimes.buildDistanceFieldBlur*pc);
		
		Context.log(RC_LOG_PROGRESS, "Build Regions: %.1fms (%.1f%%)", m_buildTimes.buildRegions/1000.0f, m_buildTimes.buildRegions*pc);
		Context.log(RC_LOG_PROGRESS, "  - watershed: %.1fms (%.1f%%)", m_buildTimes.buildRegionsReg/1000.0f, m_buildTimes.buildRegionsReg*pc);
		Context.log(RC_LOG_PROGRESS, "    - expand: %.1fms (%.1f%%)", m_buildTimes.buildRegionsExp/1000.0f, m_buildTimes.buildRegionsExp*pc);
		Context.log(RC_LOG_PROGRESS, "    - find catchment basins: %.1fms (%.1f%%)", m_buildTimes.buildRegionsFlood/1000.0f, m_buildTimes.buildRegionsFlood*pc);
		Context.log(RC_LOG_PROGRESS, "  - filter: %.1fms (%.1f%%)", m_buildTimes.buildRegionsFilter/1000.0f, m_buildTimes.buildRegionsFilter*pc);
		
		Context.log(RC_LOG_PROGRESS, "Build Contours: %.1fms (%.1f%%)", m_buildTimes.buildContours/1000.0f, m_buildTimes.buildContours*pc);
		Context.log(RC_LOG_PROGRESS, "  - trace: %.1fms (%.1f%%)", m_buildTimes.buildContoursTrace/1000.0f, m_buildTimes.buildContoursTrace*pc);
		Context.log(RC_LOG_PROGRESS, "  - simplify: %.1fms (%.1f%%)", m_buildTimes.buildContoursSimplify/1000.0f, m_buildTimes.buildContoursSimplify*pc);
		
		Context.log(RC_LOG_PROGRESS, "Build Polymesh: %.1fms (%.1f%%)", m_buildTimes.buildPolymesh/1000.0f, m_buildTimes.buildPolymesh*pc);
		Context.log(RC_LOG_PROGRESS, "Build Polymesh Detail: %.1fms (%.1f%%)", m_buildTimes.buildDetailMesh/1000.0f, m_buildTimes.buildDetailMesh*pc);
		
		Context.log(RC_LOG_PROGRESS, "Polymesh: Verts:%d  Polys:%d", m_pmesh->nverts, m_pmesh->npolys);
		
		Context.log(RC_LOG_PROGRESS, "TOTAL: %.1fms", rcGetDeltaTimeUsec(totStartTime, totEndTime)/1000.0f);
	}
	*/
	return true;
}

void hNavMesh::ComputePath( float* p_spos, float* p_epos, float* p_straightPath, int* p_nstraightPath)
{

	//placeholders for findNearestPoly
	const float* center;
	const float* extents;
	const dtQueryFilter* filter;
	dtPolyRef* nearestRef;
	float* nearestPt;

	//m_startRef = m_navMeshQuery->findNearestPoly(p_spos, m_polyPickExt);
	m_startRef = m_navMeshQuery->findNearestPoly(center, extents, filter, nearestRef, nearestPt);

	//m_endRef = m_navMeshQuery->findNearestPoly(p_epos, m_polyPickExt);
	m_endRef = m_navMeshQuery->findNearestPoly(center, extents, filter, nearestRef, nearestPt);

	if (m_startRef && m_endRef)
		{

			//placeholders for findPath
			dtPolyRef startRef;
			dtPolyRef endRef;
			const float* startPos;
			const float* endPos;
			const dtQueryFilter* filter;
			dtPolyRef* path;
			int* pathCount;
			const int maxPath = 0;

			//m_npolys = m_navMeshQuery->findPath(m_startRef, m_endRef, p_spos, p_epos, m_polys, MAX_POLYS);
			m_navMeshQuery->findPath(startRef, endRef, startPos, endPos, filter, path, pathCount, maxPath);

			if (m_npolys){

				//placeholders for findStraightPath
				const float* startPos;
				const float* endPos;
				const dtPolyRef* path;
				const int pathSize = 0;
				float* straightPath;
				unsigned char* straightPathFlags;
				dtPolyRef* straightPathRefs;
				int* straightPathCount;
				const int maxStraightPath = 0;

				//*p_nstraightPath = m_navMeshQuery->findStraightPath(p_spos, p_epos, m_polys, m_npolys, p_straightPath, MAX_POLYS);
				m_navMeshQuery->findStraightPath(startPos, endPos, path, pathSize, straightPath, straightPathFlags, straightPathRefs, straightPathCount, maxStraightPath);
			}
		}
		else
		{
			m_npolys = 0;
			*p_nstraightPath = 0;
		}
}

