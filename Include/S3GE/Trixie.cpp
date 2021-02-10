/*
  ________	
 /__  ___/                              
   / /   __     ( )         ( )  ___  2.0
  / /  //  ) ) / / \\ / /  / / //___)) 
 / /  //      / /   \/ /  / / //        
/ /  //      / /    / /\ / / ((____     

Trixie - Dynamic 2D/3D Image drawing and mapping system for S3GE
based on Trixie_Design_Doc by TechLord & Haliop

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

#include "Trixie.h"

//using namespace Trixie;
using namespace std;

// TRIXIE ////////////////////////////////////////////////////////////////////////////////////////
Trixie::Trixie(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::~Trixie(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

void Trixie::Start(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

void Trixie::Stop(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

void Trixie::Update(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::LAYERABSTRACT //////////////////////////////////////////////////////////////////////////////////////////

//Set functions

void Trixie::LayerAbstract::NameSet(string name){ Name = name;}

void Trixie::LayerAbstract::WidthSet(DWORD width){ Width = width;}

void Trixie::LayerAbstract::HeightSet(DWORD height){ Height = height;}

void Trixie::LayerAbstract::DepthSet(DWORD depth){ Depth = depth;}

void Trixie::LayerAbstract::MemblockSet(int memblockID){ dbMemblockID = memblockID;}

void Trixie::LayerAbstract::AlphaSet(int alpha){ Alpha = alpha;}

void Trixie::LayerAbstract::TypeSet(int type){ Type = type;}

void Trixie::LayerAbstract::ModeSet(int mode){ Mode = mode;}

void Trixie::LayerAbstract::ActiveSet(bool activeflag){ActiveFlag = activeflag;}

void Trixie::LayerAbstract::VisibleSet(bool visibleflag){ VisibleFlag = visibleflag;}

// Get functions - Returns Value

string Trixie::LayerAbstract::NameGet(void)		{ return Name;}

DWORD Trixie::LayerAbstract::WidthGet(void)		{ return Width;}

DWORD Trixie::LayerAbstract::HeightGet(void)	{ return Height;}

DWORD Trixie::LayerAbstract::DepthGet(void)		{ return Depth;}

int Trixie::LayerAbstract::MemblockGet(void)	{ return dbMemblockID;}

int Trixie::LayerAbstract::AlphaGet(void)		{ return Alpha;}

int Trixie::LayerAbstract::TypeGet(void)		{ return Type;}

int Trixie::LayerAbstract::ModeGet(void)		{ return Mode;}

bool Trixie::LayerAbstract::ActiveGet(void)		{ return ActiveFlag;}

bool Trixie::LayerAbstract::VisibleGet(void)	{ return VisibleFlag;}

// Get functions - Refrence

void Trixie::LayerAbstract::NameGet(string &var){ var = Name;}

void Trixie::LayerAbstract::WidthGet(DWORD &var){ var = Width;}

void Trixie::LayerAbstract::HeightGet(DWORD &var){ var = Height;}

void Trixie::LayerAbstract::DepthGet(DWORD &var){ var = Depth;}

void Trixie::LayerAbstract::MemblockGet(int &var){ var = dbMemblockID;}

void Trixie::LayerAbstract::AlphaGet(int &var){ var = Alpha;}

void Trixie::LayerAbstract::TypeGet(int &var){ var = Type;}

void Trixie::LayerAbstract::ModeGet(int &var){ var = Mode;}

void Trixie::LayerAbstract::ActiveGet(bool &var){ var = ActiveFlag;}

void Trixie::LayerAbstract::VisibleGet(bool &var){ var = VisibleFlag;}


// TRIXIE::LAYER2D ////////////////////////////////////////////////////////////////////////////////////////

Trixie::Layer2D::Layer2D(void){
	/**
	* @brief	Constructor
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Layer2D::~Layer2D(void){
	/**
	* @brief	Destructor
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::LayerAbstract* Trixie::Layer2D::Create(DWORD width, DWORD height){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	*	-#
	*/
	LayerAbstract* layer = new Layer2D;
	layer->Width = width;
	layer->Height = height;
	layer->Depth = 32;
	layer->dbMemblockID = dbMemblockResource->Pop();
	dbMakeMemblock(layer->dbMemblockID,(layer->Width * layer->Height) + 12);
	dbWriteMemblockDword(layer->dbMemblockID, 0, layer->Width);
	dbWriteMemblockDword(layer->dbMemblockID, 4, layer->Height);
	dbWriteMemblockDword(layer->dbMemblockID, 8, layer->Depth);
	return(layer);
}

Trixie::LayerAbstract* Trixie::Layer2D::Create(DWORD width, DWORD height,DWORD depth){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
	// FailSafe Image Bit check , if not equal to 8 / 16 / 32 , MemImage will not be created.
	if (depth != 8 || depth != 16 || depth !=32){ return NULL;}

	LayerAbstract* layer = new Layer2D;
	layer->Width = width;
	layer->Height = height;
	layer->Depth = depth;
	layer->dbMemblockID = dbMemblockResource->Pop();
	dbMakeMemblock(layer->dbMemblockID,(layer->Width * layer->Height) + 12);
	dbWriteMemblockDword(layer->dbMemblockID, 0, layer->Width);
	dbWriteMemblockDword(layer->dbMemblockID, 4, layer->Height);
	dbWriteMemblockDword(layer->dbMemblockID, 8, layer->Depth);
	return(layer);
}

void Trixie::Layer2D::Destroy(Trixie::LayerAbstract* layer){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/

	dbDeleteMemblock(layer->dbMemblockID);
	dbMemblockResource->Push(layer->dbMemblockID);
	delete layer;
}

void Trixie::Layer2D::Update(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

void Trixie::Layer2D::Process(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/

}


Trixie::LayerAbstract* Trixie::Layer2D::Copy(void){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
	
	LayerAbstract* layer = Layer2D::Create(Width,Height);
	//copy memblock data
	return(layer);
}

void Trixie::Layer2D::Inherit(Trixie::LayerAbstract* parent){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

void Trixie::Layer2D::Merge(Trixie::LayerAbstract* target){
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/

	//overwrite target 
}

// TRIXIE::LAYER3D ////////////////////////////////////////////////////////////////////////////////////////

Trixie::Layer3D::Layer3D(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Layer3D::~Layer3D(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}


// TRIXIE::CHANNEL ////////////////////////////////////////////////////////////////////////////////////////

Trixie::Channel::Channel(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Channel::~Channel(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::CHANNELMAP /////////////////////////////////////////////////////////////////////////////////////

Trixie::ChannelMap::ChannelMap(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::ChannelMap::~ChannelMap(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}
// TRIXIE::IMAGE //////////////////////////////////////////////////////////////////////////////////////////

Trixie::Image::Image(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Image::~Image(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::PAINTBOT /////////////////////////////////////////////////////////////////////////////////////////
Trixie::Paintbot::Paintbot(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Paintbot::~Paintbot(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::PAINTCREW /////////////////////////////////////////////////////////////////////////////////////////////

Trixie::Paintcrew::Paintcrew(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Paintcrew::~Paintcrew(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::MATERIAL ///////////////////////////////////////////////////////////////////////////////////////

Trixie::Material::Material(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Material::~Material(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::STAMP //////////////////////////////////////////////////////////////////////////////////////////

Trixie::Stamp::Stamp(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}


Trixie::Stamp::~Stamp(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::CLUSTER ////////////////////////////////////////////////////////////////////////////////////////

Trixie::Cluster::Cluster(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Cluster::~Cluster(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::SHADER /////////////////////////////////////////////////////////////////////////////////////////

Trixie::Shader::Shader(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Shader::~Shader(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

// TRIXIE::POINTERBASE ////////////////////////////////////////////////////////////////////////////////////

Trixie::PointerBase::PointerBase(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::PointerBase::~PointerBase(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}
// TRIXIE::BRUSH //////////////////////////////////////////////////////////////////////////////////////////

Trixie::Brush::Brush(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/

	//VariableMap.
}

Trixie::Brush::~Brush(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}
// TRIXIE::SELECTOR ///////////////////////////////////////////////////////////////////////////////////////

Trixie::Selector::Selector(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}

Trixie::Selector::~Selector(void)
{
	/**
	* @brief	
	*
	* @param	
	* @param	
	*
	* @return	
	* @param	
	*/
}