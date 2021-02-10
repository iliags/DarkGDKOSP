/*
 DarkGDK Open Source Project-Trio
  ______ ______  _______ _______ 
 / _____|_____ \(_______|_______)
( (____  _____) )_   ___ _____   
 \____ \(_____ (| | (_  |  ___)  
 _____) )_____) ) |___) | |_____ 
(______/(______/ \_____/|_______)
Super   3D      Game    Engine
Enhancement Lib
                             
This program is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
Lesser GNU General Public License for more details.

You should have received a copy of the Lesser GNU General Public License
along with this program. if(not, see http://www.gnu.org/licenses/.
*/

#pragma once
#ifndef S3GE_H
#define S3GE_H

#include "..\DarkGDK\DarkGDK.h"				//by TGC

#include "S3GE_Common.h"					//by DOSP Common Library
#include "DarkLUA.h"						//by Techlord
#include "DarkNet.h"						//by DarkNet Extention by Techlord
#include "..\irrXML\xml_plugin.h"			
#include "..\X360\X360_plugin.h"			//by Faker1089
//#include "..\Wii\wii_wrapper.h"			//by chunkschunks
#include "..\Misc\oawgdk.h"					//by chunkschunks
#include "..\Fulcrum\FulcrumPhy.h"			//by Matty
#include "..\Box2D\Include\Box2D.h"			//by Techlord
#include "..\PAPI\Particle2\Particle\pAPI.h"

#pragma comment (lib, "box2d.lib")

#define S3GE_IMAGE_WIDTH_MAX 1024
#define S3GE_IMAGE_HEIGHT_MAX 1024

#define S3GE_IMAGE_TYPE_STATIC 0
#define S3GE_IMAGE_TYPE_RENDERTARGET 1
#define S3GE_IMAGE_TYPE_DYNAMIC 2
#define S3GE_IMAGE_TYPE_OFFSCREEN 3

#define S3GE_FILE_FOUND 0
#define S3GE_FILE_NOTFOUND -1

//Sprite Object Types
#define S3GE_OBJECT_TYPE_2D	0
#define S3GE_OBJECT_TYPE_MESH	1
#define S3GE_OBJECT_TYPE_TERRAIN	2
#define S3GE_OBJECT_TYPE_MATRIX	3
#define S3GE_OBJECT_TYPE_LIGHT	4
#define S3GE_OBJECT_TYPE_PARTICLE	5
#define S3GE_OBJECT_TYPE_SHADER	6

//Object Types (follows Sprite Object Types enumerations)
#define S3GE_OBJECT_TYPE_PRIMITIVE_PLANE 10
#define S3GE_OBJECT_TYPE_PRIMITIVE_CUBE	11
#define S3GE_OBJECT_TYPE_PRIMITIVE_SPHERE	12
#define S3GE_OBJECT_TYPE_PRIMITIVE_CONE	13

using namespace std;

namespace S3GE{

		//FILE OBJECT
		class File{
			public:

				static map<int,File*> HTTPFileMap;
				static ResourceManager *HTTPFileResource;

				static list<File *> ActiveList;
				static list<File *>::iterator ActiveListIterator;
				static queue<File *> InactiveQueue;

				enum LoadingOptions {
					//playing with bitflags ref: http://www.cplusplus.com/forum/general/1590/
					NONE						= 0x00,
					GET_FROM_LOCAL				= 0x01,
					GET_FROM_NETWORK			= 0x02,
					GET_NEW_FROM_NETWORK		= 0x04,
					USE_PLACEHODER				= 0x08,
					CONTINUE_WHILE_LOADING		= 0x10

				} LoadOptions;

				enum LoadingStates{IDLE,SEARCHING,DOWNLOADING,COMPLETE} State;
				
				string Filename;
				string Pathname;
				int HTTPFileID;
				DarkNet::HTTP* HTTP;
				
				static File *Create(string &filename);
				static void Destroy(File *instance);
				static void Update(void);

				//File(void);
				//~File(void);

				void Process(void);
				int ProcessNow(void);
				void Destroy(void);

				int Exist(string &filename, DWORD loadoptionbitflag=NONE);
				//string FilenameGet(string name);
				//string PathnameGet(string name, int updirectory);
		};

		//TEXT OBJECT
		class Text{
			public:

				class Font{
					public:
						static map<int,Font*> IDMap;
						static map<int,Font*>::iterator IDMapIterator;
						static map<string,int> NameMap;
						static map<string,int>::iterator NameMapIterator;

						ID3DXFont* FontInterface;
						string Face;
						int Size;
						bool BoldFlag;
						bool ItalicFlag;
						D3DCOLOR Color;
						int Red;
						int Green;
						int Blue;
						int Alpha;
						TEXTMETRIC Metrics;

						Font(void);
						~Font(void);
					
						int WidthGet(string text);
						int HeightGet(string text);
				};

				//Text Members

				static int CurrentFontID;
				static Font *CurrentFont;

				int Red;
				int Green;
				int Blue;
				int Alpha;
				//IDirect3DDevice9* Device;
				//ID3DXSprite* SpriteInterface;

				Text(void);
				~Text(void);

				void Start(void);
				void Stop(void);
				void Begin(void);
				void End(void);
				void FontCreate(int fontID, LPSTR face, int size, bool boldflag, bool italicflag, int red, int green, int blue, int alpha);
				int FontCreate(LPSTR face, int size, bool boldflag, bool italicflag, int red, int green, int blue, int alpha);
				int FontCreate(string name, LPSTR face, int size, bool boldflag, bool italicflag, int red, int green, int blue, int alpha);
				void FontDestroy(int fontID);
				void FontSet(int fontID);
				int FontGet(string name);
				void Draw(int fontID, int left, int top, int right, int bottom, DWORD align, LPSTR string);
				void Draw(int fontID, int x, int y, DWORD align, LPSTR string);
				void Draw(LONG left, LONG top, LONG right, LONG bottom, DWORD align, LPSTR string);
				void Draw(int x, int y, DWORD align, LPSTR string);
				void Draw(LONG left, LONG top, LONG right, LONG bottom, LPSTR string);
				void Print(int x, int y, LPSTR atring);
				void Print(int fontID, int x, int y, DWORD align, DWORD color, LPSTR string);
				void ColorSet(BYTE red, BYTE green, BYTE blue, BYTE alpha);
				void ColorSet(DWORD color);
				void ColorSet(int fontID);
				void ColorSet(void);
				int WidthGet(string text);
				int HeightGet(string text);

		};

		//IMAGE OBJECT
		class Image{
			public:
				static map<int,Image*> IDMap;
				static map<int,Image*>::iterator IDMapIterator;

				static list<Image *> ActiveList;
				static list<Image *>::iterator ActiveListIterator;
				static queue<Image *> InactiveQueue;

				//create dbImage as a render target
				int Type;
				int Shared;
				S3GE::File *HTTPFile;
				
				D3DXIMAGE_INFO ImageInfo;
				LPDIRECT3DSURFACE9 Surface;
				LPDIRECT3DSURFACE9 DepthStencilSurface;
				D3DSURFACE_DESC SurfaceDesc;

				enum ProcessStates{IDLE,UPDATING,SEARCHING,DOWNLOADING,COMPLETE} State;

				Image(void);
				~Image(void);

				void Set(int imageID);
				Image *Get(int imageID);
				void Reset(void);

				void Lock(void);
				void Unlock(void); 

				void Create(int imageID, int type, string filename, DWORD loadoptionbitflag = File::GET_FROM_LOCAL|File::GET_FROM_NETWORK, int width = -1, int height = -1);
				void Destroy(int imageID);
				void Destroy(Image *instance);

				void Update(void);
				void Process(void);
				void ProcessNow(void);
				
				void RectCopy(int sourceimageID, int sourcex, int sourcey, int sourcewidth, int sourceheight, int destimageID, int destx, int desty);
				void RectCreate(int sourceimageID, int destimageID);
				void RectCreate(int sourceimageID, int sourcex, int sourcey, int sourcewidth, int sourceheight, int destimageID);
				void RectCrop(int sourceimageID, int sourcex, int sourcey, int sourcewidth, int sourceheight);

				//text
				void TextDraw(int FontID, int x, int y, DWORD Align, LPSTR String);
				void TextDraw(int x, int y, DWORD Align, LPSTR String);
				void TextDraw(int x, int y, LPSTR String);

				//drawing primitives
				void PixelDraw(int x, int y, DWORD color);
				void LineDraw(int top, int left, int right, int bottom, DWORD color );//http://msdn.microsoft.com/en-us/library/bb174699(VS.85).aspx
				void BoxDraw(int top, int left, int right, int bottom, DWORD color, bool fillflag);
				void EllipseDraw(DWORD color, bool fillflag);
				void PolygonDraw(POINT **point, DWORD color, bool fillflag);
				void CurveDraw(DWORD color, bool fillflag); //bezier curves

				//utilities
				int FormatOffsetGet(int format);
		};
		
		//SPRITE OBJECT
				
		//FONTART OBJECT By Techlord & Craig Copperfield - http://www.thecodebrewers.com/Fonts.html
		class FontArt{
			public:

				class Character{
					public:
						//FontArt *FontArt;
						//int ascii;
						int dbImageID;
						int Width;
						//int height;

						Character(void);
						~Character(void);
						void Capture(int fontartimageID, int xstart, int ystart, DWORD xsize, DWORD ysize, int kern = 0);
						
				};

				class Text{
					public:
						Text(void);
						~Text(void);
						list<int> SpriteList;
						list<int>::iterator SpriteListIterator;

						string Data;
						D3DVECTOR Spacing;
						bool StaticFlag;

						static Text *Create(string fontartname, string data, int kern);
						static Text *Create(string data);
						static void Destroy(Text *text);

						int Draw(string fontartname, string data, int x, int y, int kern);
						int Draw(int x, int y, string data);
						int Draw(int x, int y);
						void Capture(string fontartname, string data, int kern);
						void Alter(string fontartname, string data, int x, int y, int kern);
						void Alter(int x, int y, string data);
						void Paste(int x, int y);
						void Hide(void);
						void Show(void);
						void Size(int x, int y);
						void Scale(int scale);
						void Position(int x, int y);
						void Color(int red, int blue, int green);
						int WidthGet(string fontartname, string data);
						int WidthGet(string data);
						int HeightGet(string fontartname, string data);
						int HeightGet(string data);
						int WidthGet(void);
						int HeightGet(void);
				};

				static map<string,FontArt*> NameMap;
				static map<string,FontArt*>::iterator NameMapiterator;
				static void Start(void);
				static void Stop(void); 
				static FontArt *Load(string name, string filename, int kern = 0);
				static FontArt *CurrentFontArt;
				
				string Name;
				string Filename;
				DWORD Size;
				int dbImageID;
				int Kern;
				map<int, Character *> CharacterMap;

				FontArt(void);
				~FontArt(void);
				void Slice(int kern = 0);
		};

		class Object{
			/**
			* @brief	DGDK 3D Object
			*/
			public:

				static map<string,int> NameMap;
				static map<string,int>::iterator NameMapIterator;
				static map<int,Object*>	IDMap;

				static Object *Create(int objecttype, string objectfilename="", int objectID=0);
				static void Destroy(Object *instance);

				void Update(void);
				void Process(void);
				void ProcessNow(void);

				int ID;
				int Type;
				int Renderer;

				//visual option flags
				bool WireFlag;
				bool TransparentFlag;
				bool CullFlag;
				bool FilterFlag;
				bool LightFlag;
				bool FogFlag;
				bool AmbientFlag;
				int HTTPFileID;
			
				DWORD VisualBitflag;
				
				/*
				enum VisualOptions {
					//playing with bitflags ref: http://www.cplusplus.com/forum/general/1590/
					NONE =			0x00,
					WIRE =			0x01,
					TRANSPARENT =	0x02,
					CULL =			0x04,
					LIGHT =			0x08,
					FOG =			0x10,		
					AMBIENT =		0x20	
				};
				*/

				enum ProcessStates{IDLE, LOADING, DOWNLOADING, READY} ProcessStates;
	
				Object(void);
				~Object(void);

				Object *Copy(string name);

		};

		//S3G3 DGDK members
		class System{
			public:
				IDirect3D9 *Direct3D;
				LPDIRECT3DDEVICE9 Device;
				LPDIRECT3DSURFACE9 BackBuffer;
				LPDIRECT3DSURFACE9 DepthStencilBuffer;
				D3DSURFACE_DESC BackBufferDesc;
				D3DFORMAT CommonSurfaceFormat;
				ID3DXSprite* SpriteInterface;

				static map<string, string> ConfigPropertyMap;

				/**
				Global Singleton Interfaces
				*/
				File *File;
				Text *Text;
				Image *Image;
				Object *Object;
				FontArt::Text *FontArtText;
				FulcrumPhy *Physics;
				DarkNet::I2P *Network;

			 	enum ProcessStates {IDLE, ACTIVE, SUSPENDING, SUSPEND, SUSPENDED} ProcessState;

				System(void);
				~System(void);

				void Start(void);
				void Stop(void);
				void Update(void);
				static void ConfigPropertySet(char* directory, char* key);
				static string ConfigPropertyGet(string key);
				static void ConfigPropertyValueSet(string key, string value);
				static string ConfigPropertyValueGet(string key);
				static string ConfigPropertyRead(char* directory, char* key);
				static void ConfigPropertyWrite(char* directory, char* key, char* value);

		};

}

//Globals
extern S3GE::System *Core;

#endif


/*
Design Notes:
*/