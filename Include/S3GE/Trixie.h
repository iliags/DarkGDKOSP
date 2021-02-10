/*
  ________	
 /__  ___/                              
   / /   __     ( )         ( )  ___  2.0
  / /  //  ) ) / / \\ / /  / / //___)) 
 / /  //      / /   \/ /  / / //        
/ /  //      / /    / /\ / / ((____     

Trixie - Dynamic 2D/3D Image drawing and mapping system for S3GE
based on Trixie_Design_Doc by TechLord & Haliop

Synopsis:

Trixie uses a system of Image layers, ChannelMaps, Stamps, scripted effects to draw 
Images in real-time or non real-time. Inspired by several 2D and 3D UV mapping 
applications such as AEM, Gimp, TextureMAX, Genetica, Trixie provides this 
functionality at the lowest level of S3GE 2D Imagery. 

	Dynamic Rendering System - A command set for use of dynmically generating Images
	during run - time.
	
	MegaTexture System

License:

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
#ifndef TRIXIE_H
#define TRIXIE_H

#define NOMINMAX					// Techlord put here, if(not included we get following:

#include <new>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <map>
#include <string>
#include <fstream>
#include <math.h>

#include "..\DarkGDK\DarkGDK.h"		//by TGC
#include "S3GE_Common.h"			//by DOSP Common Library
#include "S3GE.h"					//by Techlord
#include "diag.h"					//by Techlord
#include "DarkLUA.h"				//by Techlord

using namespace std;

class Trixie{

public:

	class LayerAbstract: public S3GE::Image {
		/*
		Purpose: Base Class for 2D/3D Layers
		*/
		public:
			//properties
			string Name;
			string Description;
			int Type;
			DWORD Width;
			DWORD Height;
			DWORD Depth;
			D3DVECTOR Scale;
			float Angle;
			int dbMemblockID;
			int Alpha;
			int Mode;	//ChannelMap
			bool VisibleFlag;
			bool ActiveFlag;
			
			//constructor/destructor

			//factory
			virtual LayerAbstract* Create(DWORD width, DWORD height)=0; // Defualt 32 bits Image.
			virtual LayerAbstract* Create(DWORD width, DWORD height,DWORD depth) =0; // 8 - 16 - 32 bits Image.
			virtual void Destroy(LayerAbstract* layer)=0;

			//process
			virtual void Update(void)=0;
			virtual void Process(void)=0;

			//Set
			void	NameSet(string name);
			void	WidthSet(DWORD width);
			void	HeightSet(DWORD height);
			void	DepthSet(DWORD depth);
			void	MemblockSet(int memblockID);
			void	AlphaSet(int alpha);
			void	TypeSet(int type);
			void	ModeSet(int mode);
			void	ActiveSet(bool activeflag);
			void	VisibleSet(bool visibleflag);


			//Get - Return
			string	NameGet(void);
			DWORD	WidthGet(void);
			DWORD	HeightGet(void);
			DWORD	DepthGet(void);
			int		MemblockGet(void);
			int		AlphaGet(void);
			int		TypeGet(void);
			int		ModeGet(void);
			bool	ActiveGet(void);
			bool	VisibleGet(void);
			

			//Get - Refrence
			void	NameGet(string &var);
			void	WidthGet(DWORD &var);
			void	HeightGet(DWORD &var);
			void	DepthGet(DWORD &var);
			void	MemblockGet(int &var);
			void	AlphaGet(int &var);
			void	TypeGet(int &var);
			void	ModeGet(int &var);
			void	ActiveGet(bool &var);
			void	VisibleGet(bool &var);

			//operations
			virtual LayerAbstract* Copy(void)=0;
			virtual void Inherit(LayerAbstract* parent)=0;
			virtual void Merge(LayerAbstract* target)=0;

	};

	class Layer2D: public LayerAbstract{
		/*
		Purpose: Abstract Layer class
		*/
		public:
			//constructor/destructor
			Layer2D(void);
			~Layer2D(void);
			
			//factory
			LayerAbstract* Create(DWORD width, DWORD height); // Defualt 32 bits Layer
			LayerAbstract* Create(DWORD width, DWORD height,DWORD depth); // 8 - 16 - 32 bits Layer
			void Destroy(LayerAbstract* layer);

			//process
			void Update(void);
			void Process(void);
			//operations
			
			// Get
			LayerAbstract* Get(string name);
			LayerAbstract* Copy(void);
			void Inherit(LayerAbstract* parent);
			void Merge(LayerAbstract* target);
	};

	class UV
	{
		/*
		Purpose: UV coordinates List.
		*/
		public:
			float X,Y;		// X and Y coordinates of the UV on the Texture <> Layer3D
			bool ActiveFlag;    // UV coord Active on and off

			// Constructor / Destructor

			UV(void);
			~UV(void);

			// functions
			void Active(bool Active,int X,int Y);
			// Processing new Destination
			void Process(void);
	};

	class Layer3D: public LayerAbstract{
		/*
		Purpose: 3D UVmap
		*/
		public:
			//properties
			list<UV*> UVList;
			list<UV*>::iterator UVListIterator;

			vector <UV*> ActiveUVvector;
			vector <UV*>::iterator ActiveUVVectorIterator;

			float Usize,Vsize; // Scaling on layer , not layer size.

			DarkLUA::Task* Task; // DarkLua extention for diffrent UV mapping Algos.

			// Constructor / Destructor
			Layer3D(void);
			~Layer3D(void);

			// Functions
				// Get Distance From
					/*
						Getting Distance From UV to anywhere on the Layer3D Canvas in 2D, will let Users ,Algos, Fx , Materails etc
						Tuning Tune Better or Worse the Classes Mentioned above
					*/
			float SelectionDistanceGet(float x,float y);
				// Get Distance In
					/*
						Getting Distance Inside a UV Coord Templates will let the User or Algo or Effects,Materials 
						Tune up or Down Texture Sizes and Real Time effects
					*/
			float SelectionDistanceGet(void);

			// Set/ Select  // with mouse keyboard combinations selects from 1 to all vertices
			void SelectionSet	(void);
			void SelectionRemove(void); // removes all selection

			// Move 
			void SelectionMove	(float MoveX,float MoveY);
			void SelectionSize	(float Radius);
			void SelectionSize	(float SizeX,float SizeY);
			void SelectionRotate(float Angle);
			void SelectionFlip	(bool Vertical); // if Vertical = false , will be Horizantal

			// Visual Methods
			void VisualTrianglesSet(void);
			void VisualQuadsSet(void);

	};

	class Channel: public LayerAbstract{
		/*
		Purpose: Color Channel Layer
		*/
		private:
			//properties

		public:
			//properties
			static map<DWORD,Channel*> ColorMap; //mapped to layer by color
			D3DCOLOR Color;

			//properties
			int PixelType;	// 0,1,2,3 0=RED, 1 = GREEN, 2 = BLUE, 3 = ALPHA
			//constructor/destructor
			Channel(void);
			Channel(BYTE Red,BYTE Green,BYTE Blue,BYTE Alpha,int PixelType); 

			~Channel(void);
			//factory
			//process
			//operations
			// Set functions
			void ColorSet(BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha);
			void PixelTypeSet(int PixelType);	// 0,1,2,3 equals to Pos+ on a memblock
			
			// Get functions
			
			int			PixelGet(int x,int y);	// Getting a pixel Data , needs to define which RGBA value at setPixelType
			D3DCOLOR	RGBGet(int x,int y);	// Getting the entire RGBA color
	};

	class ChannelMap{
		/*
		Purpose: Channel Map aka ColorMap
		*/
		public:
			list<Channel*> ChannelList;

			// Constructor/Destructor
			ChannelMap(void);
			~ChannelMap(void);
	};

	class Image{
		/*
		Purpose: Singlar Visual respresentation of a Layer Group
		*/
		private:
			static map<int,Image*> IDmap; //couple to dbImageID
			static map<int,Image*>::iterator IDmapiterator;
			static list<Image*> ActiveList;
			static list<Image*>::iterator ActiveListIterator;
			static queue<Image*> InactiveQueue;

		public:
			string Name;
			list<LayerAbstract*> LayerList;
			list<LayerAbstract*>::iterator LayerListIterator;
			//map<string,LayerAbstract*> layerNameMap;
			//map<string,LayerAbstract*>::iterator layerNameMapIterator;

			enum Layer3Ds{NONE} Layer3D;
			
			//properties
			int dbImageID;
			int State;
			
			//constructor/destructor
			Image(void);
			Image(int ID);
			~Image(void);

			//factory
			static Image* Create(int dbImageID);
			static void Destroy(Image* image);

			//process
			void Update(void);
			void Process(void);

			//operations
			Image* Get(int ID);			//dbImageID
			void Render(void);			//double buffer|direct apply

			//layer/layer group operations
				//new
				//delete
				//duplicate
				//setmode
				//hide/show
				//merge
					//up
					//down
					//visible
					//all
	};

	class Paintbot{
		/*
		Purpose: A scriptable task that performs drawing operations
		*/
		private:
			static map<string,Paintbot*> NameMap;
			static map<string,Paintbot*>::iterator NameMapIterator;
			static list<Paintbot*> ActiveList;
			static list<Paintbot*>::iterator ActiveListIterator;
			static queue<Paintbot*> InactiveQueue;

		public:
			//properties
			string Name;
			DarkLUA::Task* Task;
			map<string,float> VariableMap;	//dynamics: radius, spikes, pressure, hardness, random, aspect, angle, spacing, etc;
			enum Layer3Ds{NONE} Layer3D;

			//constructor/destructor
			Paintbot(void);
			~Paintbot(void);

			//factory
			Paintbot* Create(void);
			void Destroy(Paintbot* Paintbot);

			//process
			void Update(void);
			void Process(void);

			//operations
			Paintbot* Copy(void);
			Paintbot Inherit(Paintbot* parent);
	};

	class Paintcrew{
		/*
		Purpose: A Group of effects
		*/
		private:
			static map<string,Paintcrew*> NameMap;
			static map<string,Paintcrew*>::iterator NameMapIterator;
			static list<Paintcrew*> ActiveList;
			static list<Paintcrew*>::iterator ActiveListIterator;
			static queue<Paintcrew*> InactiveQueue;

		public:
			//properties
			string Name;
			list<Paintbot*> EffectList;
			enum Layer3Ds{NONE} Layer3D;

			//constructor/destructor
			Paintcrew(void);
			~Paintcrew(void);

			//factory
			Paintcrew* Create(void);
			void Destroy(Paintcrew* paintcrew);

			//process
			void Update(void);
			void Process(void);

			//operations
			Paintcrew* Copy(void);
			Paintcrew Inherit(Paintcrew* parent);

	};

	class Material{
		/*
		Purpose: virtual Material
		*/
		public:
		
		// Constructrors / Destructors		
			Material(void);
			~Material(void);
	};

	class Stamp{
		/*
		Purpose: Image used to paint on a another
		*/
		private:
			static map<string,Stamp*> NameMap;
			static map<string,Stamp*>::iterator NameMapIterator;
			static list<Stamp*> ActiveList;
			static list<Stamp*>::iterator ActiveListIterator;
			static queue<Stamp*> InactiveQueue;

		public:
			string name;
			Image *Image; //drawing Image
			Paintcrew *Paintcrew;
			enum Layer3Ds{NONE} Layer3D;

			//constructor/destructor
			Stamp(void);
			~Stamp(void);

			//factory
			Stamp* Create(void);
			void Destroy(Stamp* Stamp);

			//process
			void Update(void);
			void Process(void);

			//operations
			Stamp* Copy(void);
			Stamp Inherit(Stamp* parent);

	};

	class Cluster{
		/*
		Purpose: A Group of Stamps
		*/
		private:
			static map<string,Cluster*> NameMap;
			static map<string,Cluster*>::iterator NameMapIterator;
			static list<Cluster*> ActiveList;
			static list<Cluster*>::iterator ActiveListIterator;
			static queue<Cluster*> InactiveQueue;

		public:
			//properties
			string Name;
			list<Stamp*> Stamplist;
			enum Layer3Ds{NONE} Layer3D;

			//constructor/destructor
			Cluster(void);
			~Cluster(void);

			//factory
			Cluster* Create(void);
			void Destroy(Cluster* Cluster);

			//process
			void Update(void);
			void Process(void);
	};

	class Shader{
		/*
		Purpose: Pixel Shader Object
		*/
		public:
			// Constructors/Destrucotrs
			Shader(void);
			~Shader(void);
	};

	class PointerBase{
		/*
		Purpose: Base Object of Tool Objects that use the Pointer
		*/
		public:
			// Constructor/ Destructor
			PointerBase(void);
			~PointerBase(void);
			
	};

	class Brush: public PointerBase{
		/*
		Purpose: Tool object used to apply a Stamp to a layer
		*/
		public:
			//properties
			LayerAbstract *targetlayer;
			LayerAbstract *shapeChannelMapmask;		//ChannelMap mask used to define shape
			Cluster *Cluster;						//pointer Cluster 
			Paintcrew *Paintcrew;					//Paintcrew pointer
			map<string,float> VariableMap;			//dynamics: radius, spikes, pressure, hardness, random, aspect, angle, spacing, etc;
			DarkLUA::Task* task;					//DarkLua extension for unique Brushes.
			enum Layer3Ds{NONE} Layer3D;

			//constructor/destructor
			Brush(void);
			~Brush(void);

			//factory
			Brush* Create(void);
			void Destroy(Brush* Brush);

			// functions
			
				// Dynamic Vars - for DarkLua , creating uniqe Brushes.
			void newVariable(string name,float var); 
			void deleteVariable(string name);

			//process
			void Update(void);
			void Process(void);


	};

	class Selector: public PointerBase {
	public:
		// Constructor/ Destructor
		Selector(void);
		~Selector(void);
	};

	//Trixie members
	
	Trixie(void);
	~Trixie(void);
	static void Start(void);
	static void Stop(void);
	static void Update(void);

};

#endif