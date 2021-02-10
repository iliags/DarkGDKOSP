/*
   ____                    __                  ____        __  __  
  / __ \__  ______ _____  / /___  ______ ___  / __ \____ _/ /_/ /_ 
 / / / / / / / __ `/ __ \/ __/ / / / __ `__ \/ /_/ / __ `/ __/ __ \
/ /_/ / /_/ / /_/ / / / / /_/ /_/ / / / / / / ____/ /_/ / /_/ / / /
\___\_\__,_/\__,_/_/ /_/\__/\__,_/_/ /_/ /_/_/    \__,_/\__/_/ /_/ 
                                                                   
This program is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
Lesser GNU General Public License for more details.

You should have received a copy of the Lesser GNU General Public License
along with this program. if(not, see HTTP://www.gnu.org/licenses/.

*/

#include "QuantumPath.h"
#include "..\recastnavigation\RecastDemo\Include\MeshLoaderObj.h"

// SYSTEM //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	QuantumPath System Constructor
* @param	void
*/
QuantumPath::System::System(void){

}

/**
* @brief	QuantumPat System Destructor
* @param	void
*/
QuantumPath::System::~System(void){

}

/**
* @brief	QuantumPath System Startup
* @param	void
* @return	void
*/
void QuantumPath::System::Start(void){

	//Default Import Extensions 
	Geometry::ImportExtSet("x");
	Geometry::ImportExtSet("dbo");
	Geometry::ImportExtSet("3ds");
	Geometry::ImportExtSet("mdl");
	Geometry::ImportExtSet("md2");
	Geometry::ImportExtSet("md3");
	//Specialty Import Extensions
	Geometry::ImportExtSet("obj", QUANTUMPATH_IMPORT_EXTENTION_TYPE_OBJ);

}

/**
* @brief	QuantumPath System Shutdown
* @param	void
* @return	void
*/
void QuantumPath::System::Stop(void){

}

// GEOMETRY //////////////////////////////////////////////////////////////////////////////////////////

map<string,int> QuantumPath::Geometry::ImportExtMap;

/**
* @brief	QuantumPath Geometry Object Constructor
* @param	void
*/
QuantumPath::Geometry::Geometry(void){
	
	Mesh = NULL;
	dbMeshID = dbObjectID = 0;
}

/**
* @brief	QuantumPath Geometry Object Destructor
* @param	void
*/
QuantumPath::Geometry::~Geometry(void){

}

/**
* @brief	Create QuantumPath Geometry
* @param	int type
* @return	QuantumPath::Geometry *
*/
QuantumPath::Geometry *QuantumPath::Geometry::Create(int type){

	Geometry *instance = new Geometry;

	switch(type){

		default:
			instance->Mesh = new Sample_DGDK;
			break;
	}
	
	instance->Mesh->m_geom = new InputGeom;
	instance->Mesh->m_ctx = new BuildContext;

	return(instance);
}

/**
* @brief	Destroy QuantumPath Geometry
* @param	Geomtery *instance
* @return	void
*/
void QuantumPath::Geometry::Destroy(Geometry *instance){
	
	delete instance->Mesh->m_ctx;
	delete instance->Mesh->m_geom;
	delete instance->Mesh;
	delete instance;
}

/**
* @brief	Update QuantumPath Geometry
* @param	void
* @return	void
*/
void QuantumPath::Geometry::Update(void){
	
}

/**
* @brief	Process QuantumPath Geometry
* @param	void
* @return	void
*/
void QuantumPath::Geometry::Process(void){
	
}

/**
* @brief	Process QuantumPath Geometry Now
* @param	void
* @return	void
*/
void QuantumPath::Geometry::ProcessNow(void){
	
}


/**
* @brief	Loads variety of mesh formats into dbObject and Recast geometry structure
* @param	string filename
* @return	void
*/
void QuantumPath::Geometry::Load(string filename){
	
	//geometry format conversion Import --> dbObject --> Make recastmesh object

	switch(Import(filename)){

		case -1://error
			return;

		default:
			Make();
	}
}

/**
* @brief	Sets a specified enumeration for Import File Extension
* @param	[in]string ext - file extension 
* @param	[in]int ,default=
*/
void QuantumPath::Geometry::ImportExtSet(string ext, int mode){

	ImportExtMap[ext] = mode;
}

/**
* @brief	Returns enumeration value for File's Extension, if its set
* @param	[in]string file - filename
* @return	int Import Mode
*/
int QuantumPath::Geometry::ImportExtGet(string file){
	
	return (ImportExtMap[file.substr(file.find_last_of(".") + 1)]);
}


/**
* @brief	Import variety of mesh formats into dbObject and Recast geometry structure
* @param	string filename
* @return	int dbMeshID
*/
int QuantumPath::Geometry::Import(string filename){
			
	switch(int fileexists = Core->File->Exist(filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK)){

		case S3GE_FILE_FOUND:
			/*
			1. select Import/Script Plugin by extension, load vertex and triangles into PTR
			2. Create blank dbObject
			3. Move over  data {vertex, triangles, other} into dbObject Structure
			*/
			
			dbObjectID = dbObjectResource->Add(filename);
			if(!dbObjectExist(dbObjectID)){

				switch(ImportExtGet(filename)){

					case QUANTUMPATH_IMPORT_EXTENTION_TYPE_OBJ:
						if(!OBJImport(filename, dbObjectID)) return -1;
						break;

					default:
						dbLoadObject((char*)filename.data(), dbObjectID);
						//create mesh data
				};
			}
			break;
	
		case S3GE_FILE_NOTFOUND:
			return -1;

	}

	return dbMeshID;
}

/**
* @brief	Caclulate Normals
			Ref: http://www.fullonsoftware.co.uk/snippets/content/Math_-_Calculating_Face_Normals.pdf
* @param	int memblockID
* @param	D3DVECTOR a
* @param	D3DVECTOR b
* @param	D3DVECTOR c
* @param	D3DVECTOR &normal
* @param	bool normalizeflag
* @return	int
*/

void QuantumPath::Geometry::CalculateSurfaceNormal(D3DVECTOR a, D3DVECTOR b, D3DVECTOR c, D3DVECTOR &normal, bool normalizeflag){

	D3DVECTOR v1,v2;
	
	v1.x = b.x - a.x;
	v1.y = b.y - a.y;
	v1.z = b.z - a.z;
	v2.x = c.x - a.x;
	v2.y = c.y - a.y;
	v2.z = c.z - a.z;

	normal.x = (v1.y * v2.z) - (v1.z * v2.y);
	normal.y = -((v2.z * v1.x) - (v2.x * v1.z));
	normal.z = (v1.x * v2.y) - (v1.y * v2.x);
	
	if(normalizeflag){
		float normalisationfactor = sqrt( (normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));
		normal.x /= normalisationfactor;
		normal.y /= normalisationfactor;
		normal.z /= normalisationfactor;
	}

}

/**
* @brief	Writes Vertex Data into Memblock, Adjusts Offset, used in OBJImport
* @param	int memblockID
* @param	float x
* @param	float y
* @param	float z
* @param	float nx
* @param	float ny
* @param	float nz
* @param	int r
* @param	int g
* @param	int b
* @param	float u
* @param	float v
* @return	int
*/
void QuantumPath::Geometry::MemblockVertexWrite(int memblockID, int &offset, float x, float y, float z, float nx, float ny, float nz, int r, int g, int b, float u, float v){

	//vertex
	dbWriteMemblockFloat(memblockID, offset, x);
	dbWriteMemblockFloat(memblockID, offset+4, y);
	dbWriteMemblockFloat(memblockID, offset+8, z);

	//normal
	dbWriteMemblockFloat(memblockID, offset+12, nx);
	dbWriteMemblockFloat(memblockID, offset+16, ny);
	dbWriteMemblockFloat(memblockID, offset+20, nz);
	
	//difuse
	dbWriteMemblockDWORD(memblockID, offset+24, D3DCOLOR_XRGB(r,g,b));

	//uv
	dbWriteMemblockFloat(memblockID, offset+28, u);
	dbWriteMemblockFloat(memblockID, offset+32, v);

	offset+=36;
}

/**
* @brief	Parse 'v' Row Data for OBJImport
* @param	char* buf
* @param	char* bufEnd
* @param	char* row
* @param	int len
* @return	char* 
*/
char* QuantumPath::Geometry::OBJImportRowParse(char* buf, char* bufEnd, char* row, int len){
	bool cont = false;
	bool start = true;
	bool done = false;
	int n = 0;
	while (!done && buf < bufEnd)
	{
		char c = *buf;
		buf++;
		// multirow
		switch (c)
		{
			case '\\':
				cont = true; // multirow
				break;
			case '\n':
				if (start) break;
				done = true;
				break;
			case '\r':
				break;
			case '\t':
			case ' ':
				if (start) break;
			default:
				start = false;
				cont = false;
				row[n++] = c;
				if (n >= len-1)
					done = true;
				break;
		}
	}
	row[n] = '\0';
	return buf;
}

/**
* @brief	Parse 'f' Face Data for OBJImport
* @param	char* row
* @param	int* data
* @param	int n
* @param	int vcnt
* @return	int
*/
int QuantumPath::Geometry::OBJImportFaceParse(char* row, int* data, int n, int vcnt){
	int j = 0;
	while (*row != '\0')
	{
		// Skip initial white space
		while (*row != '\0' && (*row == ' ' || *row == '\t'))
			row++;
		char* s = row;
		// Find vertex delimiter and terminated the string there for conversion.
		while (*row != '\0' && *row != ' ' && *row != '\t')
		{
			if (*row == '/') *row = '\0';
			row++;
		}
		if (*s == '\0')
			continue;
		int vi = atoi(s);
		data[j++] = vi < 0 ? vi+vcnt : vi-1;
		if (j >= n) return j;
	}
	return j;
}

/**
* @brief	Import *.OBJ format and Construct dbMesh
* @param	string filename
* @param	int objectID
* @return	bool - true if successful
*/
bool QuantumPath::Geometry::OBJImport(string filename, int objectID){

	if(dbObjectExist(objectID)){
		//ERRROR Cannot Overwrite Existing Object
		return false;
	}

	char* buf = 0;
	FILE* fp = fopen(filename.c_str(), "rb");
	if (!fp)
		return false;
	fseek(fp, 0, SEEK_END);
	int bufSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buf = new char[bufSize];
	if (!buf)
	{
		fclose(fp);
		return false;
	}
	fread(buf, bufSize, 1, fp);
	fclose(fp);

	char* src = buf;
	char* srcEnd = buf + bufSize;
	char row[512];
	int face[32];
	int nv;

	D3DVECTOR m_vertpos = {0,0,0};

	while (src < srcEnd){

		// Parse one row
		row[0] = '\0';
		src = OBJImportRowParse(src, srcEnd, row, sizeof(row)/sizeof(char));
		// Skip comments
		if (row[0] == '#') continue;
		if (row[0] == 'v' && row[1] != 'n' && row[1] != 't')
		{
			// Vertex pos
			sscanf(row+1, "%f %f %f", &m_vertpos.x, &m_vertpos.y, &m_vertpos.z);
			//addVertex(x, y, z, vcap);
			m_vertpos.x *= -1;//inverse correction for DX
			m_vert.push_back(m_vertpos);
		}
		if (row[0] == 'f')
		{
			// Faces
			nv = OBJImportFaceParse(row+1, face, 32, m_vert.size());
			for (int i = 2; i < nv; ++i){
			
				TRINT m_facepos = {face[0], face[i-1], face[i]};

				if (m_facepos.a < 0 || m_facepos.a >= m_vert.size() || m_facepos.b < 0 || m_facepos.b >= m_vert.size() || m_facepos.c < 0 || m_facepos.c >= m_vert.size())
					continue;
				//addTriangle(a, b, c, tcap);
				m_face.push_back(m_facepos);

			}
		}
	}

	delete [] buf;

	//Construct dbObejct from Mesh
	D3DVECTOR normal;
	int offset=12;
	int totalvertices = m_face.size() * 3;				// trianglecount * 3 vertices
	int memblocksize = offset + (totalvertices *36);	// 12 byte header + (totalvertices * 36 bytes each) 
	int memblockID = dbMemblockResource->Pop();

	dbMakeMemblock(memblockID, memblocksize);

	dbWriteMemblockDWORD(memblockID,0,338);				//default FVF Format = 338
	dbWriteMemblockDWORD(memblockID,4,36);				//default FVF Format Size = 36
	dbWriteMemblockDWORD(memblockID,8, totalvertices);	//totalvertices

	//write to object data to memblock
	for(int loop = 0;loop < m_face.size(); loop++){//normal normal 0,1,0
		//calculate normals
		CalculateSurfaceNormal(m_vert[m_face[loop].a],m_vert[m_face[loop].b],m_vert[m_face[loop].c],normal,true);
		MemblockVertexWrite(memblockID, offset, m_vert[m_face[loop].a].x,  m_vert[m_face[loop].a].y,  m_vert[m_face[loop].a].z, normal.x, normal.y, normal.z, 255, 255, 255, 0.0, 0.0);
		MemblockVertexWrite(memblockID, offset, m_vert[m_face[loop].b].x,  m_vert[m_face[loop].b].y,  m_vert[m_face[loop].b].z, normal.x, normal.y, normal.z, 255, 255, 255, 0.0, 0.0);
		MemblockVertexWrite(memblockID, offset, m_vert[m_face[loop].c].x,  m_vert[m_face[loop].c].y,  m_vert[m_face[loop].c].z, normal.x, normal.y, normal.z, 255, 255, 255, 0.0, 0.0);
	}

	//mesh exist clear
	dbMeshID = dbMeshResource->Pop();
	dbMakeMeshFromMemblock(dbMeshID, memblockID);
	filename.append(".x"); //filename.obj.x
	dbSaveMesh((char*)filename.data(), dbMeshID); //Functional Data Dump Log
	dbDeleteMemblock(memblockID);
	dbMemblockResource->Push(memblockID);

	dbMakeObject(objectID, dbMeshID, 0);

	return true;
}

/**
* @brief	Export DGDK Object to *.OBJ format used in RecastDemo
* @param	string filename
* @return	int dbObjectID
*/
bool QuantumPath::Geometry::OBJExport(string filename, int objectID){

	return(false);
}

/**
* @brief	Make Recast Geometry from dbObject
* @param	string filename
* @return	void
*/
bool QuantumPath::Geometry::Make(void){
	
	/*
		Select loading method by file extension
		dbObject --> recastmesh object
	*/

	if(!dbMeshExist(dbMeshID)) return false;

	//Reference: InputGeom::loadMesh
	if (Mesh->m_geom->m_mesh)
	{
		delete Mesh->m_geom->m_chunkyMesh;
		Mesh->m_geom->m_chunkyMesh = NULL;
		delete Mesh->m_geom->m_mesh;
		Mesh->m_geom->m_mesh = NULL;
	}
	Mesh->m_geom->m_offMeshConCount = 0;
	Mesh->m_geom->m_volumeCount = 0;

	Mesh->m_geom->m_mesh = new rcMeshLoaderObj;
	if (!Mesh->m_geom->m_mesh)
	{
		Context.log(RC_LOG_ERROR, "loadMesh: Out of memory 'Mesh->m_geom->m_mesh'.");
		return false;
	}
	//load obj file
	/*
	if (!Mesh->m_geom->m_mesh->load(Filename))
	{
		Context.log(RC_LOG_ERROR, "buildTiledNavigation: Could not load '%s'", filepath);
		return false;
	}
	*/

	//Copy Geometry from dbObject to rcMeshLoaderObj
	//Reference: rcMeshLoaderObj::load
	int vcap = 0;
	int tcap = 0;

	//vertices
	for (int i=0;i<m_vert.size();i++){
		Mesh->m_geom->m_mesh->addVertex(
			m_vert[i].x, 
			m_vert[i].y, 
			m_vert[i].z, 
			vcap
			);
	}
	//faces
	for (int i=0;i<m_face.size();i++){
		Mesh->m_geom->m_mesh->addTriangle(
			m_face[i].a, 
			m_face[i].b, 
			m_face[i].c, 
			tcap
			);
	}

	//Reference: InputGeom::loadMesh
	rcCalcBounds(Mesh->m_geom->m_mesh->getVerts(), Mesh->m_geom->m_mesh->getVertCount(), Mesh->m_geom->m_meshBMin, Mesh->m_geom->m_meshBMax);

	Mesh->m_geom->m_chunkyMesh = new rcChunkyTriMesh;
	if (!Mesh->m_geom->m_chunkyMesh)
	{
		Context.log(RC_LOG_ERROR, "buildTiledNavigation: Out of memory 'Mesh->m_geom->m_chunkyMesh'.");
		return false;
	}
	if (!rcCreateChunkyTriMesh(Mesh->m_geom->m_mesh->getVerts(), Mesh->m_geom->m_mesh->getTris(), Mesh->m_geom->m_mesh->getTriCount(), 256, Mesh->m_geom->m_chunkyMesh))
	{
		Context.log(RC_LOG_ERROR, "buildTiledNavigation: Failed to build chunky mesh.");
		return false;
	}

	// Calculate normals.
	Mesh->m_geom->m_mesh->m_normals = new float[Mesh->m_geom->m_mesh->m_triCount*3];
	for (int i = 0; i < Mesh->m_geom->m_mesh->m_triCount*3; i += 3)
	{
		const float* v0 = &Mesh->m_geom->m_mesh->m_verts[Mesh->m_geom->m_mesh->m_tris[i]*3];
		const float* v1 = &Mesh->m_geom->m_mesh->m_verts[Mesh->m_geom->m_mesh->m_tris[i+1]*3];
		const float* v2 = &Mesh->m_geom->m_mesh->m_verts[Mesh->m_geom->m_mesh->m_tris[i+2]*3];
		float e0[3], e1[3];
		for (int j = 0; j < 3; ++j)
		{
			e0[j] = v1[j] - v0[j];
			e1[j] = v2[j] - v0[j];
		}
		float* n = &Mesh->m_geom->m_mesh->m_normals[i];
		n[0] = e0[1]*e1[2] - e0[2]*e1[1];
		n[1] = e0[2]*e1[0] - e0[0]*e1[2];
		n[2] = e0[0]*e1[1] - e0[1]*e1[0];
		float d = sqrtf(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
		if (d > 0)
		{
			d = 1.0f/d;
			n[0] *= d;
			n[1] *= d;
			n[2] *= d;
		}
	}

	//strncpy(Mesh->m_geom->m_mesh->m_filename, Filename.c_str(), sizeof(Mesh->m_geom->m_mesh->m_filename));
	//Mesh->m_geom->m_mesh->m_filename[sizeof(Mesh->m_geom->m_mesh->m_filename)-1] = '\0';

	return true;

}

/**
* @brief	Build Navigation Geometry from Recast Geometry
* @param	void
* @return	void
*/
bool QuantumPath::Geometry::Build(void){

	//Reference:  Sample_SoloMeshSimple::handleBuild()

	if (!Mesh->m_geom->m_mesh)
	{
		Context.log(RC_LOG_ERROR, "buildNavigation: Input mesh is not specified.");
		return false;
	}

	Mesh->handleBuild();

	return true;

}


/**
* @brief	Demolish Navigational Mesh
* @param	void
* @return	void
*/
void QuantumPath::Geometry::Demolish(void){

}


/**
* @brief	Clean up Navigational Mesh
* @param	void
* @return	void
*/
void QuantumPath::Geometry::Clean(void){

}


// AGENT //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	QuantumPath Agent Object Destructor
* @param	void
*/
QuantumPath::Agent::Agent(void){

}

/**
* @brief	QuantumPath Agent Object Destructor
* @param	void
*/
QuantumPath::Agent::~Agent(void){

}

/**
* @brief	Create QuantumPath Agent
* @param	int type
* @return	QuantumPath::Agent *
*/
QuantumPath::Agent *QuantumPath::Agent::Create(int type){
	
	Agent *instance = new Agent;
	return(instance);

}


/**
* @brief	Destroy QuantumPath Agent
* @param	int type
* @return	QuantumPath::Agent *
*/
void QuantumPath::Agent::Destroy(QuantumPath::Agent* instance){

}


/**
* @brief	Update All QuantumPath Agent
* @param	void
* @return	void
*/
void QuantumPath::Agent::Update(void){
}

/**
* @brief	Process QuantumPath Agent
* @param	void
* @return	void
*/
void QuantumPath::Agent::Process(void){
}

/**
* @brief	Process QuantumPath Agent Noew
* @param	void
* @return	void
*/
void QuantumPath::Agent::ProcessNow(void){
}
