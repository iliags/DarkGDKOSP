//=======================================
//NAVIGATION MESHES HEADER
//Marabillas 2010
//Added S3GE in Rev 182
//=======================================

#ifndef HNAVMESH_H
#define HNAVMESH_H

#include "..\DarkGDK\DarkGDK.h"		//by TGC
#include "S3GE_Common.h"			//by DOSP Common Library
#include "S3GE.h"					//by S3GE Enhanced Library
#include "DarkLUA.h"				//by Techlord
#include "..\irrXML\xml_plugin.h"
#include "DarkNet.h"				//by DarkNet Extention by Techlord

#include "..\recastnavigation\Recast\Include\Recast.h"
//#include "RecastTimer.h"
//#include "RecastLog.h"
#include "..\recastnavigation\Detour\Include\DetourNavMesh.h" // DetourStatNavMesh.h
#include "..\recastnavigation\Detour\Include\DetourNavMeshBuilder.h" //DetourStatNavMeshBuilder.h
#include "..\recastnavigation\Detour\Include\DetourNavMeshQuery.h"


#define MAX_POLYS		30
#define MESHID_NAVMESH	5

class hNavMesh
{
public:
	hNavMesh();
	~hNavMesh();
	
	//!Builds the data(hNavMesh variables) for the GDK Object
	void LoadGDKObject( int pObjectID );

	//!Builds navigation mesh
	bool BuildNavigationMesh();

	//!Computes path
	void ComputePath( float* p_spos, float* p_epos, float* p_straightPath, int* p_nstraightPath);
	
	//Navigation Mesh Configurations
	float		m_cellSize;
	float		m_cellHeight;
	float		m_agentRadius;
	float		m_agentHeight;
	float		m_agentMaxClimb;
	float		m_agentMaxSlope;
	float		m_regionMinSize;
	float		m_regionMergeSize;
	float		m_edgeMaxLen;
	float		m_edgeMaxError;
	float		m_vertsPerPoly;
	float		m_detailSampleDist;
	float		m_detailSampleMaxError;

	dtNavMesh*	m_navMesh;
	dtNavMeshQuery*	m_navMeshQuery;

protected:
	int			ObjectID;

	float*		m_verts;
	int			m_nverts;

	int*		m_tris;
	//const float* m_trinorms;
	int			m_ntris;

	float		m_bmin[3],m_bmax[3];

	//StatMesh	Variables
	dtPolyRef	m_startRef;
	dtPolyRef	m_endRef;
	dtPolyRef	m_polys[MAX_POLYS];
	dtPolyRef	m_parent[MAX_POLYS];
	int			m_npolys;
	float		m_polyPickExt[3];

	float		m_hitPos[3];
	float		m_hitNormal[3];
	float		m_distanceToWall;

	//StatMeshSimple Variables
	bool		m_keepInterResults;
	//rcBuildTimes	m_buildTimes; //not available in new versions of recast

	unsigned char*	m_triflags;
	rcHeightfield*	m_solid;
	rcCompactHeightfield*	m_chf;
	rcContourSet*	m_cset;
	rcPolyMesh*		m_pmesh;
	rcConfig		m_cfg;
	rcPolyMeshDetail*	m_dmesh;

	rcContext* m_context;


};



#endif



