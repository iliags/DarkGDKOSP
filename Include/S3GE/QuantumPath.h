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

#pragma once
#ifndef QUANTUMPATH_H
#define QUANTUMPATH_H

#include "S3GE.h"					//by S3GE Enhanced Library

#include "..\recastnavigation\RecastDemo\Include\Sample_DGDK.h"
#include "..\recastnavigation\Detour\Include\DetourNavMesh.h"
#include "..\recastnavigation\DetourCrowd\Include\DetourObstacleAvoidance.h"
#include "..\recastnavigation\DetourCrowd\Include\DetourCrowd.h"

using namespace S3GE;

#define	QUANTUMPATH_GEOMETRY_TYPE_DEFAULT 0

#define	QUANTUMPATH_IMPORT_EXTENTION_TYPE_DEFAULT	0
#define	QUANTUMPATH_IMPORT_EXTENTION_TYPE_OBJ	1

class QuantumPath{
	private:
	public:
		//rcMeshLoaderObj

		/**
		* @brief	Navigation Mesh
		*/
		class Geometry{
			//
			private:
			public:
				
				struct TRINT{
					int a, b, c;
				};

				static map<string,int> ImportExtMap;

				int ID;
				string Filename;

				//recast mesh data
				rcContext Context;
				Sample *Mesh;

				//dgdk mesh data
				vector<D3DVECTOR> m_vert;
				vector<TRINT> m_face;
				int dbMeshID;
				int dbObjectID;

				static Geometry *Create(int type);
				static void Destroy(Geometry *instance);
				static void Update(void);
				static void Process(void);
				static void ProcessNow(void);

				static void ImportExtSet(string ext, int mode = QUANTUMPATH_IMPORT_EXTENTION_TYPE_DEFAULT);
				static int ImportExtGet(string file);
				
				Geometry(void);
				~Geometry(void);
				
				void Load(string filename);
				int Import(string filename);
				bool Make(void);
				bool Build(void);
				void Demolish(void);
				void Clean(void);
				
				bool OBJImport(string filename, int objectID);
				char* OBJImportRowParse(char* buf, char* bufEnd, char* row, int len);
				int OBJImportFaceParse(char* row, int* data, int n, int vcnt);
				bool OBJExport(string filename, int objectID);	

				void CalculateSurfaceNormal(D3DVECTOR a, D3DVECTOR b, D3DVECTOR c, D3DVECTOR &normal, bool normalizeflag);
				void MemblockVertexWrite(int memblockID, int &offset, float x, float y, float z, float nx, float ny, float nz, int r, int g, int b, float u, float v);

		};

		/**
		* @brief	Navigation Agent
		*/
		class Agent{
			//
			private:
			public:

				//dtCrowd m_crowd;

				Agent(void);
				~Agent(void);

				static Agent *Create(int type);
				static void Destroy(Agent *instance);
				static void Update(void);
				static void Process(void);
				static void ProcessNow(void);

		};

		class System{
			private:
			public:
				System(void);
				~System(void);
				static void Start(void);
				static void Stop(void);
		};

};

#endif

/*
Design Notes:

Utilizes constructs from the Recast Demo

Workflow
	1. Create QuantumPath Geometry Structure
		and Load Geometry
	2. Import Geometry(.x, .3ds, .dbo, .obj, .md*)
		and Construct dbMesh
	3. Make Recast Geometry from dbMesh
	4. Build Navigation Geometry from Recast Geometry

*/