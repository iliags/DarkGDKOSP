/* _____                                      
  / ___/________  ____  ___  _________ ___  __
  \__ \/ ___/ _ \/ __ \/ _ \/ ___/ __ `/ / / /
 ___/ / /__/  __/ / / /  __/ /  / /_/ / /_/ / 
/____/\___/\___/_/ /_/\___/_/   \__, /\__, /  
S3GXL Scene Import System      /____//____/   
By TechLord


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
#ifndef SCENERGY_H
#define SCENERGY_H

#include "MAUI.h"					//by Techlord
#include "Illudium.h"				//by Techlord
#include "QuantumPath.h"			//by Techlord

using namespace std;
using namespace S3GE;

#define	SCENERGY_ERROR	-1

//XML Tags	
#define S3GXL_TAG_S3GE	1
#define S3GXL_TAG_WIDGET	2
#define S3GXL_TAG_DOODAD	3
#define S3GXL_TAG_JIGGER	4
#define S3GXL_TAG_GIZMO	5
#define S3GXL_TAG_WIZMO	6
#define S3GXL_TAG_BEHAVIOR	7
#define S3GXL_TAG_TRANSITION	8
#define S3GXL_TAG_STYLE	9
#define S3GXL_TAG_THEME	10
#define S3GXL_TAG_SCHEME	11
#define S3GXL_TAG_EVENT	12
#define S3GXL_TAG_META	13
#define S3GXL_TAG_SCRIPT	14
#define S3GXL_TAG_FONT	15
#define S3GXL_TAG_ALPHA	16
#define S3GXL_TAG_OPAQUE	17
#define S3GXL_TAG_TRANSPARENT	18
#define S3GXL_TAG_BOLD	19
#define S3GXL_TAG_ITALIC	20
#define S3GXL_TAG_SPRITE	21
#define S3GXL_TAG_AUDIO	22
#define S3GXL_TAG_ORIENTATE	23
#define S3GXL_TAG_PHYSICS	24
#define S3GXL_TAG_BORDER	25
#define S3GXL_TAG_FORM	26
#define S3GXL_TAG_FORMSUBMIT	27
#define S3GXL_TAG_FORMRESET	28
#define S3GXL_TAG_CANVAS	29
#define S3GXL_TAG_INPUTDEVICE	30
#define S3GXL_TAG_STATE	31
#define S3GXL_TAG_OBJECT	32
#define S3GXL_TAG_VARIABLE	33
#define S3GXL_TAG_INCLUDE	34
#define S3GXL_TAG_TASK	35
#define S3GXL_TAG_GADGET	36
#define S3GXL_TAG_OBJECT	37
#define S3GXL_TAG_TERRAIN	38
#define S3GXL_TAG_MATRIX	39
#define S3GXL_TAG_LIGHT	40
#define S3GXL_TAG_SHADER	41
#define S3GXL_TAG_PARTICLE	42
#define S3GXL_TAG_REACTOR	43

class Scenergy{
	private:
	public:

		class XMLFile{
			/**
			* @brief	*.maui, *.s3ge file format import/export
			*/
			private:
				class GizmoProperty{
					public:
						int StartEventState;
				};

				queue<MAUI::Gizmo*> LoadedGizmoQueue;
				map<MAUI::Gizmo*,GizmoProperty> GizmoPropertyMap;

			public:
				static map<string,int> TagNameMap;
				static map<string,int>::iterator TagNameMapIterator;
				static map<string,int> AttributeValueMap;
				static list<XMLFile*> ActiveList;
				static list<XMLFile*>::iterator ActiveListIterator;
				static queue<XMLFile*> InactiveQueue;
				static void TagNameAdd(string tagname, int constant);
				static void AttributeValueAdd(string attributevalue, int constant);
				static void Update(void);
				//static Save(void);

				IrrXMLReader *XML;
				string Filename;
				stack< pair<int,string> > ParseStack;

				//syntax error checking
				int NodeCount;
				int StartTime;
				int LoadRate; //msec
				S3GE::File *HTTPFile;

				enum XMLFileStates{IDLE, LOAD, LOADING, LOADALL, DOWNLOADING, COMPLETE} State;

				XMLFile(string filename, bool loadallflag, int loadallrate);//constructor
				~XMLFile(void);//destructor

				void Process(void);
				int Parse(void);
				//saving methods
				//void writetag();
				//void writeattribute();

				string AttributeValueSafeGet(char *attribute);
				int AttributeValueAsIntGet(char *attribute);
				bool AttributeValueAsBooleanGet(char *attribute);
				float AttributeValueAsFloatGet(char *attribute);

				string SyntaxErrorMessage;
				int SyntaxError(string errormessage);

		};

		class System{
			private:
			public:
		
				static void Start(void);
				static void Stop(void);
				static void Update(void);
				static int Load(string filename, bool loadallflag, int loadallrate);

			};

};

#endif