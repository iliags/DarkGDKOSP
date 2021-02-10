/*
   ____     ____       _                  _   _    ____     
U | __")uU |  _"\ uU  /"\  u     ___     | \ |"|  / __"| u  
 \|  _ \/ \| |_) |/ \/ _ \/     |_"_|   <|  \| |><\___ \/   
  | |_) |  |  _ <   / ___ \      | |    U| |\  |u u___) |   
  |____/   |_| \_\ /_/   \_\   U/| |\u   |_| \_|  |____/>>  
 _|| \\_   //   \\_ \\    >>.-,_|___|_,-.||   \\,-.)(  (__) 
(__) (__) (__)  (__)__)  (__)\_)-' '-(_/ (_")  (_/(__)      

Behavioral Rules Artificial Intelligence Node System
F.L.Taylor 2010 ©

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

#include "BRAIN.h"

// EVENT STATE MACHINE ////////////////////////////////////////////////////////////////////////////////////////
std::map<std::string, int> brains::esm::statenamemap;
std::map<std::string, int>::iterator brains::esm::statenamemapiterator;
int brains::esm::stateindex = 0;

void brains::esm::statenameadd(std::string statename){

	/*!
	* Description: Adds a Event State Name; auto generates a Integer Index, Creates LUA EventState Global Var
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(!statenamemap[statename]){
		statenamemap[statename] = stateindex;
		darklua::integerset((char*)statename.data(),stateindex);

		//bugboard->enable();
		bugboard->print("\n");
		bugboard->print(statename);	
		bugboard->print("=");
		bugboard->print(dbStr(statenamemap[statename]));
		//bugboard->disable();

		stateindex++;
	}
}

void  brains::esm::clear(void){

	/*!
	* Description: Clear State
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	previousstate = state = 0;
	counter = count = delta = 0.0f;
}


// GENERAL //////////////////////////////////////////////////////////////////////////////////////////
brains::behavior *brains::defaultbehavior = NULL;
brains::transition *brains::defaulttransition = NULL;
brains::style *brains::defaultstyle = NULL;
brains::theme *brains::defaulttheme = NULL;
brains::scheme *brains::defaultscheme = NULL;
brains::canvas *brains::basecanvas = NULL;
brains::agent *brains::baseagent = NULL;
brains::agent *brains::pointer = NULL;
brains::agent *brains::caret = NULL;

debugclipbrd *brains::bugboard = NULL;
std::string brains::output;

//intialize brains dgdk object resource managers
resourcemanager *brains::dbMemblockResource = new resourcemanager(32);
resourcemanager *brains::dbBitmapResource = new resourcemanager(32);
resourcemanager *brains::dbImageResource =  new resourcemanager(4096);
resourcemanager *brains::dbSpriteResource = new resourcemanager(4096);
resourcemanager *brains::dbObjectResource = new resourcemanager(4096);
resourcemanager *brains::dbSoundResource =  new resourcemanager(256);
resourcemanager *brains::dbMusicResource =  new resourcemanager(64);
resourcemanager *brains::dbCameraResource =  new resourcemanager(4);
resourcemanager *brains::dbLightResource =  new resourcemanager(8);		static std::map<std::string,int> scancodemap;

std::map<std::string,int> brains::scancodemap;

void brains::start(void){

	/*!
	* Description: Initializes MAUI; Creates base agent, eventstate name defs, xmlnode name defs
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard = darklua::bugboard;
	bugboard->print("\nMAUI 2.0");
	bugboard->enable();

	xmlfile::nodenameadd("brains", BRAIN_XML_NODENAME_MAUI);
	xmlfile::nodenameadd("agent", BRAIN_XML_NODENAME_AGENT);
	xmlfile::nodenameadd("behavior", BRAIN_XML_NODENAME_BEHAVIOR);
	xmlfile::nodenameadd("transition", BRAIN_XML_NODENAME_TRANSITION);
	xmlfile::nodenameadd("event", BRAIN_XML_NODENAME_EVENT);
	xmlfile::nodenameadd("meta", BRAIN_XML_NODENAME_META);
	xmlfile::nodenameadd("script", BRAIN_XML_NODENAME_SCRIPT);
	xmlfile::nodenameadd("orientate", BRAIN_XML_NODENAME_ORIENTATE);
	xmlfile::nodenameadd("border",BRAIN_XML_NODENAME_BORDER);
	xmlfile::nodenameadd("audio",BRAIN_XML_NODENAME_AUDIO);
	xmlfile::nodenameadd("physics",BRAIN_XML_NODENAME_PHYSICS);
	xmlfile::nodenameadd("form",BRAIN_XML_NODENAME_FORM);
	xmlfile::nodenameadd("submit",BRAIN_XML_NODENAME_FORMSUBMIT);
	xmlfile::nodenameadd("reset",BRAIN_XML_NODENAME_FORMRESET);
	xmlfile::nodenameadd("canvas",BRAIN_XML_NODENAME_CANVAS);
	xmlfile::nodenameadd("device",BRAIN_XML_NODENAME_DEVICE);
	xmlfile::nodenameadd("state",BRAIN_XML_NODENAME_STATE);
	xmlfile::nodenameadd("object",BRAIN_XML_NODENAME_OBJECT);
	xmlfile::nodenameadd("variable",BRAIN_XML_NODENAME_VARIABLE);

	xmlfile::attributevalueadd("",0);//default
	xmlfile::attributevalueadd("true",true);
	xmlfile::attributevalueadd("false",false);
	xmlfile::attributevalueadd("mouse",BRAIN_DEVICE_TYPE_MOUSE);
	xmlfile::attributevalueadd("keyboard",BRAIN_DEVICE_TYPE_KEYBOARD);
	xmlfile::attributevalueadd("joystick",BRAIN_DEVICE_TYPE_JOYSTICK);
	xmlfile::attributevalueadd("xbox360",BRAIN_DEVICE_TYPE_JOYSTICK_360);
	xmlfile::attributevalueadd("wii",BRAIN_DEVICE_TYPE_JOYSTICK_WII);
	xmlfile::attributevalueadd("widget",BRAIN_AGENT_TYPE_0D);
	xmlfile::attributevalueadd("doodad",BRAIN_AGENT_TYPE_1D);
	xmlfile::attributevalueadd("agent",BRAIN_AGENT_TYPE_2D);
	xmlfile::attributevalueadd("wizmo",BRAIN_AGENT_TYPE_3D);
	xmlfile::attributevalueadd("left",BRAIN_AGENT_BODY_ORIENTATE_XALIGN_LEFT);
	xmlfile::attributevalueadd("center",BRAIN_AGENT_BODY_ORIENTATE_XALIGN_CENTER);
	xmlfile::attributevalueadd("right",BRAIN_AGENT_BODY_ORIENTATE_XALIGN_RIGHT);
	xmlfile::attributevalueadd("top",BRAIN_AGENT_BODY_ORIENTATE_YALIGN_TOP);
	xmlfile::attributevalueadd("middle",BRAIN_AGENT_BODY_ORIENTATE_YALIGN_MIDDLE);
	xmlfile::attributevalueadd("bottom",BRAIN_AGENT_BODY_ORIENTATE_YALIGN_BOTTOM);
	xmlfile::attributevalueadd("front",BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_FRONT);
	xmlfile::attributevalueadd("neutral",BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_NEUTRAL);
	xmlfile::attributevalueadd("neutral",BRAIN_AGENT_BODY_ORIENTATE_ALIGN_NEUTRAL);
	xmlfile::attributevalueadd("back",BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_BACK);
	xmlfile::attributevalueadd("password",BRAIN_SPRITE_CAPTIONTYPE_PASSWORD);
	xmlfile::attributevalueadd("hidden",BRAIN_SPRITE_CAPTIONTYPE_HIDDEN);
	xmlfile::attributevalueadd("realtime",BRAIN_SPRITE_CAPTIONTYPE_REALTIME);
	xmlfile::attributevalueadd("dgdk",BRAIN_SCHEME_AUDIO_SYSTEM_DGDK);
	xmlfile::attributevalueadd("oaw",BRAIN_SCHEME_AUDIO_SYSTEM_OAW);
	xmlfile::attributevalueadd("sound",BRAIN_SCHEME_AUDIO_TYPE_SOUND);
	xmlfile::attributevalueadd("music",BRAIN_SCHEME_AUDIO_TYPE_MUSIC);
	xmlfile::attributevalueadd("world",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_WORLD);
	xmlfile::attributevalueadd("body",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_BODY);
	xmlfile::attributevalueadd("mousejoint",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_MOUSE);
	xmlfile::attributevalueadd("distancejoint",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_DISTANCE);
	xmlfile::attributevalueadd("revolutejoint",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_REVOLUTE);
	xmlfile::attributevalueadd("prismaticjoint",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_PRISMATIC);
	xmlfile::attributevalueadd("pullyjoint",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_PULLEY);
	xmlfile::attributevalueadd("gearjoint",BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_GEAR);
	xmlfile::attributevalueadd("GET",DARKNET_HTTP_METHOD_GET);
	xmlfile::attributevalueadd("POST",DARKNET_HTTP_METHOD_POST);

	//DarkLUA Setup

	//darklua bind property access uiAgentPropertyGet/Set
	agent::propertyadd("Name", BRAIN_AGENT_PROPERTY_NAME);
	agent::propertyadd("Description", BRAIN_AGENT_PROPERTY_DESCRIPTION);
	agent::propertyadd("Eventstate", BRAIN_AGENT_PROPERTY_EVENTSTATE_STATE);
	agent::propertyadd("EventstateCount", BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNT);
	agent::propertyadd("EventstateCounter", BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNTER);
	agent::propertyadd("BodyCollision", BRAIN_AGENT_PROPERTY_BOUND_COLLISION);
	agent::propertyadd("DeviceContact", BRAIN_AGENT_PROPERTY_CONTACT_COLLISION);
	agent::propertyadd("DeviceAxisX", BRAIN_AGENT_PROPERTY_AXIS_X);
	agent::propertyadd("DeviceAxisY", BRAIN_AGENT_PROPERTY_AXIS_Y);
	agent::propertyadd("DeviceAxisZ", BRAIN_AGENT_PROPERTY_AXIS_Z);
	agent::propertyadd("SpriteQuad", BRAIN_AGENT_PROPERTY_SPRITE_QUAD);

	//scancodes based on Blitz3D Scancode list
	scancodemap["ESCAPE"]=1;
	scancodemap["1"]=2;
	scancodemap["2"]=3;
	scancodemap["3"]=4;
	scancodemap["4"]=5;
	scancodemap["5"]=6;
	scancodemap["6"]=7;
	scancodemap["7"]=8;
	scancodemap["8"]=9;
	scancodemap["9"]=10;
	scancodemap["0"]=11;
	scancodemap["Minus (-)"]=12;
	scancodemap["Equals (=)"]=13;
	scancodemap["Backspace"]=14;
	scancodemap["Tab"]=15;
	scancodemap["Q"]=16;
	scancodemap["W"]=17;
	scancodemap["E"]=18;
	scancodemap["R"]=19;
	scancodemap["T"]=20;
	scancodemap["Y"]=21;
	scancodemap["U"]=22;
	scancodemap["I"]=23;
	scancodemap["O"]=24;
	scancodemap["P"]=25;
	scancodemap["Left Bracket ([)"]=26;
	scancodemap["Right Bracket (])"]=27;
	scancodemap["Return/Enter"]=28;
	scancodemap["Left Control"]=29;
	scancodemap["A"]=30;
	scancodemap["S"]=31;
	scancodemap["D"]=32;
	scancodemap["F"]=33;
	scancodemap["G"]=34;
	scancodemap["H"]=35;
	scancodemap["J"]=36;
	scancodemap["K"]=37;
	scancodemap["L"]=38;
	scancodemap["Semi-Colon (;)"]=39;
	scancodemap["Apostrophe (')"]=40;
	scancodemap["Grave"]=41;
	scancodemap["Left Shift"]=42;
	scancodemap["Backslash (\)"]=43;
	scancodemap["Z"]=44;
	scancodemap["X"]=45;
	scancodemap["C"]=46;
	scancodemap["V"]=47;
	scancodemap["B"]=48;
	scancodemap["N"]=49;
	scancodemap["M"]=50;
	scancodemap["Comma (,)"]=51;
	scancodemap["Period (.)"]=52;
	scancodemap["Slash (/)"]=53;
	scancodemap["Right Shift"]=54;
	scancodemap["Multiply (*)"]=55;
	scancodemap["Left Alt/Menu"]=56;
	scancodemap["Space"]=57;
	scancodemap["Capital"]=58;
	scancodemap["F1"]=59;
	scancodemap["F2"]=60;
	scancodemap["F3"]=61;
	scancodemap["F4"]=62;
	scancodemap["F5"]=63;
	scancodemap["F6"]=64;
	scancodemap["F7"]=65;
	scancodemap["F8"]=66;
	scancodemap["F9"]=67;
	scancodemap["F10"]=68;
	scancodemap["NumLock"]=69;
	scancodemap["Scroll Lock"]=70;
	scancodemap["NumPad 7"]=71;
	scancodemap["NumPad 8"]=72;
	scancodemap["NumPad 9"]=73;
	scancodemap["Subtract (-)"]=74;
	scancodemap["NumPad 4"]=75;
	scancodemap["NumPad 5"]=76;
	scancodemap["NumPad 6"]=77;
	scancodemap["Add (+)"]=78;
	scancodemap["NumPad 1"]=79;
	scancodemap["NumPad 2"]=80;
	scancodemap["NumPad 3"]=81;
	scancodemap["NumPad 0"]=82;
	scancodemap["Decimal (.)"]=83;
	scancodemap["OEM_102"]=86;
	scancodemap["F11"]=87;
	scancodemap["F12"]=88;
	scancodemap["F13"]=100;
	scancodemap["F14"]=101;
	scancodemap["F15"]=102;
	scancodemap["Kana"]=112;
	scancodemap["ABNT_C1"]=115;
	scancodemap["Convert"]=121;
	scancodemap["NoConvert"]=123;
	scancodemap["Yen"]=125;
	scancodemap["ABNT_C2"]=126;
	scancodemap["Equals"]=141;
	scancodemap["PrevTrack"]=144;
	scancodemap["AT"]=145;
	scancodemap["Colon (:)"]=146;
	scancodemap["Underline"]=147;
	scancodemap["Kanji"]=148;
	scancodemap["Stop"]=149;
	scancodemap["AX"]=150;
	scancodemap["Unlabeled"]=151;
	scancodemap["Next Track"]=153;
	scancodemap["Enter"]=156;
	scancodemap["Right Control"]=157;
	scancodemap["Mute"]=160;
	scancodemap["Calculator"]=161;
	scancodemap["Play/Pause"]=162;
	scancodemap["Media Stop"]=164;
	scancodemap["Volume Down"]=174;
	scancodemap["Volume Up"]=176;
	scancodemap["Web Home"]=178;
	scancodemap["Comma (,)"]=179;
	scancodemap["Divide (/)"]=181;
	scancodemap["SysReq"]=183;
	scancodemap["Right Alt/Menu"]=184;
	scancodemap["Pause"]=197;
	scancodemap["Home"]=199;
	scancodemap["Up"]=200;
	scancodemap["Page Up/Prior"]=201;
	scancodemap["Left"]=203;
	scancodemap["Right"]=205;
	scancodemap["End"]=207;
	scancodemap["Down"]=208;
	scancodemap["Next"]=209;
	scancodemap["Insert"]=210;
	scancodemap["Delete"]=211;
	scancodemap["Left Windows"]=219;
	scancodemap["Right Windows"]=220;
	scancodemap["Apps"]=221;
	scancodemap["Power"]=222;
	scancodemap["Sleep"]=223;
	scancodemap["Wake"]=227;
	scancodemap["Web Search"]=229;
	scancodemap["Web Favorites"]=230;
	scancodemap["Web Refresh"]=231;
	scancodemap["Web Stop"]=232;
	scancodemap["Web Forward"]=233;
	scancodemap["Web Back"]=234;
	scancodemap["My Computer"]=235;
	scancodemap["Mail "]=236;
	scancodemap["Media Select"]=237;

}

void brains::update(void){

	/*!
	* Description: Calls update functions for Agents, XMLfiles
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	device::update();

	canvas::update();

	agent::update();

	xmlfile::update();

}

void brains::stop(void){

	/*!
	* Description: Shutdown MAUI
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	behavior::destroy();
	transition::destroy();
	style::destroy();
	theme::destroy();
	scheme::destroy();
	agent::destroy();
	device::destroy();
	canvas::destroy();

}

int brains::load(std::string filename){

	/*!
	* Description: Loads a *brains XML, no validation for format; Non blocking implementation
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	/* file check
		if file not avaliable on local drive, request from Host Server
		else return Error code
	*/

	new xmlfile(filename);

	return(1);

}

// BEHAVIOR //////////////////////////////////////////////////////////////////////////////////////////
std::map<std::string,brains::behavior*> brains::behavior::namemap;
std::map<std::string,brains::behavior*>::iterator brains::behavior::namemapiterator;

brains::behavior::behavior(void){

	/*!
	* Description: constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
}

brains::behavior::behavior(std::string name, std::string description=""){

	/*!
	* Description: constructor
	*
	* -#Input:
	*	-# string name - behavior name
	*	-# string description behavior description used for Tooltip
	*
	* -#Output:
	*	-# none
	*/
	
	this->name = name;
	this->description = description;

}


brains::behavior::~behavior(void){

	/*!
	* Description: destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
}

brains::behavior *brains::behavior::create(std::string name, std::string description){
	/*!
	* Description: 
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	if(namemap[name] == NULL){ 
		namemap[name] = new behavior(name, description);
	}
	return(namemap[name]);
}

void brains::behavior::destroy(behavior *behavior){

	/*!
	* Description: destroy behavior by pointer
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	//destroy eventaction
	bugboard->print("\ndestroying behavior ");
	bugboard->print(behavior->name);

	std::map<int, eventscript *>::iterator eventactioniterator;

	for(eventactioniterator = behavior->eventaction.begin(); eventactioniterator !=  behavior->eventaction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){			
			//delete task script
			if(((*eventactioniterator).second)->task != NULL){
				delete ((*eventactioniterator).second)->task;
			}
			delete (*eventactioniterator).second;
		}
	}

	behavior->eventaction.clear();
	
	delete behavior;

}

void brains::behavior::destroy(void){

	/*!
	* Description: destroys all behaviors
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\nbehavior::destroy all");
	std::map<std::string,behavior *>::iterator namemapiterator;
	for(namemapiterator = namemap.begin(); namemapiterator !=  namemap.end();  namemapiterator++){
		destroy((*namemapiterator).second);
	}
	namemap.clear();
	bugboard->print("\n~behavior::destroy all");
}

brains::behavior *brains::behavior::get(std::string name){
	/*!
	* Description: Return pointer by name; if not available will create pointer
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	if(namemap[name] == NULL){ 
		namemap[name] = new behavior(name, "tbd");
	}
	return(namemap[name]);
}

// BEHAVIOR::EVENTSCRIPT //////////////////////////////////////////////////////////////////////////////////////////
brains::behavior::eventscript::eventscript(void){
	/*!
	* Description:  Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	task = NULL;

}

void brains::behavior::eventscript::inherit(brains::behavior::eventscript *parent){
	/*!
	* Description:  Inheritor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	task = parent->task;

}

// TRANSITION //////////////////////////////////////////////////////////////////////////////////////////
std::map<std::string,brains::transition*> brains::transition::namemap;
std::map<std::string,brains::transition*>::iterator brains::transition::namemapiterator;

brains::transition::transition(void){

	/*!
	* Description: constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
}

brains::transition::transition(std::string name, std::string description=""){

	/*!
	* Description: constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	this->name = name;
	this->description = description;

}


brains::transition::~transition(void){

	/*!
	* Description: destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
}

brains::transition *brains::transition::create(std::string name, std::string description){

	/*!
	* Description: 
	*
	* -#Input:
	*	-# string name - behavior name
	*	-# string description behavior description used for Tooltip
	*
	* -#Output:
	*	-# none
	*/
	
	if(namemap[name] == NULL){ 
		namemap[name] = new transition(name, description);
	}

	return(namemap[name]);
}

void brains::transition::destroy(transition *transition){

	/*!
	* Description: 
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	//destroy eventaction
	bugboard->print("\ndestroying transition ");
	bugboard->print(transition->name);

	std::map<int, eventscript *>::iterator eventactioniterator;

	for(eventactioniterator = transition->eventaction.begin(); eventactioniterator !=  transition->eventaction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){	
			//delete task script
			if(((*eventactioniterator).second)->task != NULL){
				delete ((*eventactioniterator).second)->task;
			}

			delete (*eventactioniterator).second;
		}
	}

	transition->eventaction.clear();
	
	delete transition;

}

void brains::transition::destroy(void){

	/*!
	* Description: destroys all transitions
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\ntransition::destroy all");
	std::map<std::string,transition *>::iterator namemapiterator;
	for(namemapiterator = namemap.begin(); namemapiterator !=  namemap.end();  namemapiterator++){
		destroy((*namemapiterator).second);
	}
	namemap.clear();
	bugboard->print("\n~transition::destroy all");
}

brains::transition *brains::transition::get(std::string name){
	/*!
	* Description: Return pointer by name; if not available will create pointer
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	if(namemap[name] == NULL){ 
		namemap[name] = new transition(name, "tbd");
	}
	return(namemap[name]);
}

// TRANSITION::EVENTSCRIPT //////////////////////////////////////////////////////////////////////////////////////////
brains::transition::eventscript::eventscript(void){
	/*!
	* Description:  Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	task = NULL;

}

void brains::transition::eventscript::inherit(brains::transition::eventscript *parent){
	/*!
	* Description:  Inheritor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	task = parent->task;

}

// BODY //////////////////////////////////////////////////////////////////////////////////////////
brains::body::body(void){
	/*!
	* Description: body Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	type = 0;
	collideflag = physicsflag = gravityflag = pathfinderflag = 0;
	collisionexist = 0;
	physics = NULL;

}

brains::body::body(float x, float y, float z, float width, float height, float depth, float anglex, float angley, float anglez){
	/*!
	* Description: Body Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	type = 0;
	collideflag = physicsflag = gravityflag = pathfinderflag = 0;
	collisionexist = 0;

	position.x = x;
	position.y = y;
	position.z = z;
	size.x = width;
	size.y = height;
	size.z = depth;
	angle.x = anglex;
	angle.y = angley;
	angle.z = anglez;

	physics = NULL;

	bugboard->print("\nset body(x=");
	bugboard->print(dbStr(x));
	bugboard->print(",y=");
	bugboard->print(dbStr(y));
	bugboard->print(",z=");
	bugboard->print(dbStr(z));
	bugboard->print(",width=");
	bugboard->print(dbStr(width));
	bugboard->print(",height=");
	bugboard->print(dbStr(height));
	bugboard->print(",depth");
	bugboard->print(dbStr(depth));
	bugboard->print(",anglex=");
	bugboard->print(dbStr(anglex));
	bugboard->print(",angley");
	bugboard->print(dbStr(angley));
	bugboard->print(",anglez=");
	bugboard->print(dbStr(anglez));
	bugboard->print(")");

}

brains::body::~body(void){
	/*!
	* Description: body Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}

void brains::body::center(std::string canvasname){
	/*!
	* Description: Centers Body based on canvas centeroffeset
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	position.x *= canvas::namemap[canvasname]->zoomfactor.x + canvas::namemap[canvasname]->centeroffset.x;
	position.y *= canvas::namemap[canvasname]->zoomfactor.y + canvas::namemap[canvasname]->centeroffset.y;

}

void brains::body::zoom(std::string canvasname){
	/*!
	* Description: Zoom Body based on canvas zoomfactor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	size.x *= canvas::namemap[canvasname]->zoomfactor.x;
	size.y *= canvas::namemap[canvasname]->zoomfactor.y;

}



void brains::body::orientate(std::string refagentname, float x, float y, float z, int xalign, int yalign, int zalign){
	/*!
	* Description: auto orientates based on reference agent
	*	uses position for a offset if align > 0
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(agent::namemap[refagentname] == NULL){
		bugboard->print(refagentname);
		bugboard->print(" Does Not Exists");
		refagentname="";
	}

	bugboard->print("(");
	bugboard->print(dbStr(position.x));
	bugboard->print(",");
	bugboard->print(dbStr(position.y)); 
	bugboard->print(",");
	bugboard->print(dbStr(size.x));
	bugboard->print(",");
	bugboard->print(dbStr(size.y));
	bugboard->print("); ref=");
	bugboard->print(refagentname); 
	bugboard->print("(");
	bugboard->print(dbStr(agent::namemap[refagentname]->body->position.x));
	bugboard->print(",");
	bugboard->print(dbStr(agent::namemap[refagentname]->body->position.y));
	bugboard->print(",");
	bugboard->print(dbStr(agent::namemap[refagentname]->body->size.x));
	bugboard->print(",");
	bugboard->print(dbStr(agent::namemap[refagentname]->body->size.y));
	bugboard->print(")");

	position.x = x;
	position.y = y;
	position.z = z;

	//if no dimensions copy ref's
	if(size.x==0){size.x = agent::namemap[refagentname]->body->size.x;}
	if(size.y==0){size.y = agent::namemap[refagentname]->body->size.y;}
	if(size.x==0){size.z = agent::namemap[refagentname]->body->size.z;}

	bugboard->print("\nxalign = ");
	bugboard->print(dbStr(xalign));
	bugboard->print(" yalign = ");
	bugboard->print(dbStr(yalign));
	bugboard->print(" zalign = ");
	bugboard->print(dbStr(zalign));

	if((yalign || zalign) && !xalign){xalign = BRAIN_AGENT_BODY_ORIENTATE_ALIGN_NEUTRAL;}
	if((xalign || zalign) && !yalign){yalign = BRAIN_AGENT_BODY_ORIENTATE_ALIGN_NEUTRAL;}
	if((xalign || yalign) && !zalign){zalign = BRAIN_AGENT_BODY_ORIENTATE_ALIGN_NEUTRAL;}

	//auto alignment
	switch(xalign){

		case BRAIN_AGENT_BODY_ORIENTATE_XALIGN_LEFT:
			position.x += agent::namemap[refagentname]->body->position.x - size.x;
			bugboard->print("\nxalign left, this.x + ref.x - this.size.x");
			break;

		case BRAIN_AGENT_BODY_ORIENTATE_XALIGN_CENTER:
			position.x += agent::namemap[refagentname]->body->position.x;
			bugboard->print("\nxalign center, this.x + ref.x");
			break;

		case BRAIN_AGENT_BODY_ORIENTATE_XALIGN_RIGHT:
			position.x += agent::namemap[refagentname]->body->position.x + agent::namemap[refagentname]->body->size.x;
			bugboard->print("\nxalign right, this.x + ref.x + ref.size.x");
			break;
			
	}

	switch(yalign){

		case BRAIN_AGENT_BODY_ORIENTATE_YALIGN_TOP:
			position.y += agent::namemap[refagentname]->body->position.y - size.y;
			bugboard->print("\nyalign top, this.y + ref.y - size.y");
			break;

		case BRAIN_AGENT_BODY_ORIENTATE_YALIGN_MIDDLE:
			position.y += agent::namemap[refagentname]->body->position.y;
			bugboard->print("\nyalign top, this.y + ref.y");
			break;

		case BRAIN_AGENT_BODY_ORIENTATE_YALIGN_BOTTOM:
			position.y += agent::namemap[refagentname]->body->position.y + agent::namemap[refagentname]->body->size.y;
			bugboard->print("\nyalign bottom, this.y + ref.y + ref.size.y");
			break;
		
	}

	switch(zalign){

		case BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_FRONT:
			position.z += agent::namemap[refagentname]->body->position.z - size.z;
			bugboard->print("\nzalign front, this.z + ref.z - this.size.z");
			break;

		case BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_NEUTRAL:
			position.z += agent::namemap[refagentname]->body->position.z;
			bugboard->print("\nzalign front, this.z + ref.z");
			break;

		case BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_BACK:
			position.z += agent::namemap[refagentname]->body->position.z + size.z;
			bugboard->print("\nzalign back, this.z + ref.z + this.size.z");
			break;

	}

}



// BODY::COLLISION /////////////////////////////////////////////////////////////////////////////////////////////
//statics
/*
std::list<int> *brains::body::collision::typelist = new std::list<int>[32 + 1];
std::list<int>::iterator brains::body::collision::sourcetypelistiterator;
std::list<int>::iterator brains::body::collision::desttypelistiterator;
brains::body::collision::contact *brains::body::collision::profile = new brains::body::collision::contact[32 + 1];
int brains::body::collision::profile_index = 0;
int brains::body::collision::updatefrequency = 6;
int brains::body::collision::updatefrequencycounter = 0;
int brains::body::collision::hitcounter = 0;

void brains::body::collision::start(void){
	//purpose: tbd
	//parameters:
	//return: none

	updatefrequencycounter = updatefrequency;
}

void brains::body::collision::stop(void){
	//purpose: tbd
	//parameters:
	//return: none
}

void brains::body::collision::update(void){
	//purpose: update collisions based on contact profiles;
	//parameters:
	//return: none

	//updatefrequencycounter--;
	if (!updatefrequencycounter--){

		int source3dobjectID;
		int dest3dobjectID;

		bugboard->print("updating collisions:");
		//iterate contact profiles
		for(int profileID = 1; profileID < (profile_index + 1); profileID++){

			bugboard->print("[profileID = ");
			bugboard->print(dbStr(profileID));
			bugboard->print("]");
			bugboard->print("{");

			//iterate source typelist
			sourcetypelistiterator = typelist[profile[profileID].sourcetypelistID].begin();
			while(sourcetypelistiterator != typelist[profile[profileID].sourcetypelistID].end()) {

				//get source objectID from source typelist
				int sourceobjectID = *sourcetypelistiterator++;

				bugboard->print("[sourcetypelistID = ");
				bugboard->print(dbStr(profile[profileID].sourcetypelistID));
				bugboard->print(", sourceobjectID = ");
				bugboard->print(dbStr(sourceobjectID));
				bugboard->print("]");

				//iterate destination typelist
				desttypelistiterator = typelist[profile[profileID].desttypelistID].begin();
				while(desttypelistiterator != typelist[profile[profileID].desttypelistID].end()) {

					//get destination objectID from destinatino typelist
					int destobjectID = *desttypelistiterator++;

					bugboard->print("[desttypelistID = ");
					bugboard->print(dbStr(profile[profileID].desttypelistID));
					bugboard->print(", destobjectID = ");
					bugboard->print(dbStr(destobjectID));
					bugboard->print("]");

					//select collision check method
					switch(profile[profileID].method){

						case 1: //perform check between entity.objectID based on distance tolerance
							source3dobjectID = entityobject(profile[profileID].sourcetypelistID, sourceobjectID); 
							dest3dobjectID = entityobject(profile[profileID].desttypelistID, destobjectID);
							//self conflict check
							if(source3dobjectID != dest3dobjectID){
								//perform collision check between 3d objects based on distance tolerance
								if(check(dbObjectPositionX(source3dobjectID),dbObjectPositionY(source3dobjectID),dbObjectPositionZ(source3dobjectID),dbObjectPositionX(dest3dobjectID),dbObjectPositionY(dest3dobjectID),dbObjectPositionZ(dest3dobjectID),profile[profileID].tolerance)){
									//if collided process response between objects
									process(source3dobjectID, dest3dobjectID, profile[profileID].response);
									//call shared entity collision processing function here; entity collision queue
								}
							}
							break;

						case 2: //perform check between objectID and cameraid based on distance tolerance; source3dobject assumed to be camera
							source3dobjectID = entityobject(profile[profileID].sourcetypelistID, sourceobjectID); 
							dest3dobjectID = entityobject(profile[profileID].desttypelistID, destobjectID);
							//self conflict check
							if(source3dobjectID != dest3dobjectID){
								//perform collision check between 3d objects based on distance tolerance
								if(check(dbCameraPositionX(source3dobjectID),dbCameraPositionY(source3dobjectID),dbCameraPositionZ(source3dobjectID),dbObjectPositionX(dest3dobjectID),dbObjectPositionY(dest3dobjectID),dbObjectPositionZ(dest3dobjectID),profile[profileID].tolerance)){
									//if collided process response between objects
									process(source3dobjectID, dest3dobjectID, profile[profileID].response);
									//call shared entity collision processing function here; entity collision queue
								}
							}

						default: //perform check between objectID based on distance tolerance
							//self conflict check
							if(sourceobjectID != destobjectID){
								//perform collision check between 3d objects based on distance tolerance
								if(check(dbObjectPositionX(sourceobjectID),dbObjectPositionY(sourceobjectID),dbObjectPositionZ(sourceobjectID),dbObjectPositionX(destobjectID),dbObjectPositionY(destobjectID),dbObjectPositionZ(destobjectID),profile[profileID].tolerance)){
									//if collided process response between objects
									process(sourceobjectID, destobjectID, profile[profileID].response);
								}
							}
					}

				}
			}
			bugboard->print("}");
		}
		updatefrequencycounter = updatefrequency;
	}
}

void brains::body::collision::process(int sourceobjectID, int destobjectID, int response){
	//purpose: process collision between two 3dobjects based on response type
	//parameters:
	//return: none

	hitcounter++;

	//testing
	dbCenterText(dbScreenWidth() >> 1,dbScreenHeight() >> 1,"hit");

	bugboard->print("{");
	bugboard->print("[h i t:");
	bugboard->print(" sourceobjectID = ");
	bugboard->print(dbStr(sourceobjectID));
	bugboard->print(", destobjectID = ");
	bugboard->print(dbStr(destobjectID));
	bugboard->print(", reponse = ");

	switch(response){
		case NONE:
				bugboard->print("none");
			break;

		case SLIDE:
				bugboard->print("slide");
			break;

		case STOP:
				bugboard->print("stop");
			break;
	}
	bugboard->print("]");
	bugboard->print("}");
}

void brains::body::collision::create(int sourcetypelistID, int desttypelistID, int method, int response, float tolerance){
	//purpose: create a `contact` profile to define collision between sourcetypelist and desttypelist
	//			defines distance tolerance and response. priority
	//parameters:
	//return: none

	profile_index++;
	profile[profile_index].sourcetypelistID = sourcetypelistID;
	profile[profile_index].desttypelistID = desttypelistID;
	profile[profile_index].method = method;
	profile[profile_index].response = response;
	profile[profile_index].tolerance = tolerance;

	bugboard->print("contact profile:");
	bugboard->print("{");
	bugboard->print("[profile_index = ");
	bugboard->print(dbStr(profile_index));
	bugboard->print(", sourcetypelistID = ");
	bugboard->print(dbStr(sourcetypelistID));
	bugboard->print(", desttypelistID = ");
	bugboard->print(dbStr(desttypelistID));
	bugboard->print(", method = ");
	bugboard->print(dbStr(method));
	bugboard->print(", response = ");
	bugboard->print(dbStr(response));
	bugboard->print(", tolerance = ");
	bugboard->print(dbStr(tolerance));
	bugboard->print("]");
	bugboard->print("}");
}

void brains::body::collision::add(int objectID, int typelistid){
	//purpose: adds object to  collision type list,
	//parameters:
	//return: none

	bugboard->print("[adding object to collision type: ");
	bugboard->print("objectID = ");
	bugboard->print(dbStr(objectID));
	bugboard->print(", typelistid = ");
	bugboard->print(dbStr(typelistid));

	typelist[typelistid].push_back(objectID);

	bugboard->print("]");

}

void brains::body::collision::remove(int objectID, int typelistid){
	//purpose: removes object to collision type list
	//parameters:
	//return: none

	bugboard->print("[removing object from collision type: ");
	bugboard->print("objectID = ");
	bugboard->print(dbStr(objectID));
	bugboard->print(", typelistid = ");
	bugboard->print(dbStr(typelistid));

	typelist[typelistid].remove(objectID);
	
	bugboard->print("]");

}

bool brains::body::collision::check(float dbObjectPositionX1, float dbObjectPositionY1, float dbObjectPositionZ1, float dbObjectPositionX2, float dbObjectPositionY2, float dbObjectPositionZ2, float tolerance){
	//purpose: check collision by distance between two objects 3dvectors
	//parameters:
	//return: none

	D3DVECTOR position1;
	D3DVECTOR position2;
	
	position1.x = dbObjectPositionX1;
	position1.y = dbObjectPositionY1;
	position1.z = dbObjectPositionZ1;
	position2.x = dbObjectPositionX2;
	position2.y = dbObjectPositionY2;
	position2.z = dbObjectPositionZ2;

	return(check(position1,position2,tolerance));

}

bool brains::body::collision::check(D3DVECTOR position1, D3DVECTOR position2, float tolerance){
	//purpose: check collision by distance between two objects 3dvectors
	//parameters:
	//return: none

	bugboard->print("checking for collision:");
	bugboard->print("{");
	bugboard->print("[3dvector 1 ");
	bugboard->print(" |");
	bugboard->print(dbStr(position1.x));
	bugboard->print(", ");
	bugboard->print(dbStr(position1.y));
	bugboard->print(", ");
	bugboard->print(dbStr(position1.z));
	bugboard->print("|, 3dvector 2 ");
	bugboard->print(" |");
	bugboard->print(dbStr(position2.x));
	bugboard->print(", ");
	bugboard->print(dbStr(position2.y));
	bugboard->print(", ");
	bugboard->print(dbStr(position2.z));
	bugboard->print("|, tolerance = ");
	bugboard->print(dbStr(tolerance));

	D3DVECTOR delta;
	delta.x = position1.x - position2.x;
	delta.y = position1.y - position2.y;
	delta.z = position1.z - position2.z;
	float distance = sqrt( pow(delta.x,2) +  pow(delta.y,2) + pow(delta.z,2) );


	bugboard->print(", distance = ");
	bugboard->print(dbStr(distance));
	bugboard->print(" |");
	bugboard->print(dbStr(position1.x - position2.x));
	bugboard->print(", ");
	bugboard->print(dbStr(position1.y - position2.y));
	bugboard->print(", ");
	bugboard->print(dbStr(position1.z - position2.z));
	bugboard->print("|");
	bugboard->print("]");
	bugboard->print("}");

	if (distance <= tolerance){
		return true;
	}
	return false;
}

int brains::body::collision::entityobject(int typelistID, int EntityID){
	//Purpose: gets object IDs from Entities based on Collison TypeList
	//Parameters:
	//Return: None

	switch(typelistID){
		case ENTITY_TYPE_OBJECT1:
			//object pointer from EntityID
			//return object ID
			return(1);
			break;
	}
	return(0);
}

void brains::body::collision::entitycollisions(int sourcetypelistID, int sourceentityID, int desttypelistID, int destentityID){

	//Purpose: processes Entity collision; assumes collision = true;
	//Parameters:
	//Return: None

	switch(sourcetypelistID){

		case brains::body::collision::ENTITY_TYPE_OBJECT1:
			//Enzyme::instance[SourceEntityID].collisions.push_back(desttypelistID);
			//Enzyme::instance[SourceEntityID].collisions.push_back(destentityID);

			switch(desttypelistID){
				case brains::body::collision::ENTITY_TYPE_OBJECT2:
				//do stuff
				break;
			}
			break;

		case brains::body::collision::ENTITY_TYPE_OBJECT2:
			//Cell::instance[SourceEntityID].collisions.push_back(desttypelistID);
			//Cell::instance[SourceEntityID].collisions.push_back(destentityID);

			switch(desttypelistID){
				case brains::body::collision::ENTITY_TYPE_OBJECT1:
				//do stuff
				break;

				case brains::body::collision::ENTITY_TYPE_OBJECT2:
				//do stuff
				break;

			}
			break;



	}

}
*/


// BODY::B2WORLD ////////////////////////////////////////////////////////////////
brains::body::b2world::b2world(void){
	
	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	worldAABB.lowerBound.x = worldAABB.lowerBound.y = 0;
	world = NULL;
	allowsleep = false;
	gravity.x = gravity.y = gravity.z = 0;
	timestep = 0;
	iterations = 0;

}

brains::body::b2world::~b2world(void){

	/*!
	* Description: Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}

void brains::body::b2world::create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping ){

	// Description: 
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none
	//

	this->timestep = timestep;
	this->iterations = iterations;
	this->allowsleep = allowsleeping;

	bugboard->print("\ncanvas::timing(");
	bugboard->print("step=");
	bugboard->print(dbStr(timestep));
	bugboard->print(",it=");
	bugboard->print(dbStr(iterations));
	bugboard->print(",sleep=");
	bugboard->print(dbStr(allowsleep));
	bugboard->print(")");

	bugboard->print("\ncanvas::bounds(");
	bugboard->print(dbStr(position.x));
	bugboard->print(",");
	bugboard->print(dbStr(position.y));
	bugboard->print(",");
	bugboard->print(dbStr(size.x/b2PixelRatio));
	bugboard->print("(");
	bugboard->print(dbStr(size.x));
	bugboard->print("),");
	bugboard->print(dbStr(size.y/b2PixelRatio));
	bugboard->print("(");
	bugboard->print(dbStr(size.y));
	bugboard->print("))");

	worldAABB.lowerBound.Set(position.x,position.y);
	worldAABB.upperBound.Set(size.x/b2PixelRatio, size.y/b2PixelRatio);

	// Define the gravity vector.
	bugboard->print("\ncanvas::gravity(");
	bugboard->print(dbStr(gravityx));
	bugboard->print(",");
	bugboard->print(dbStr(gravityy));
	bugboard->print(")");

	gravity.x = gravityx;
	gravity.y = gravityy;

	// Do we want to let bodies sleep?
	//allowsleep

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(worldAABB, (b2Vec2&)gravity, allowsleep);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
}

void brains::body::b2world::destroy(void){

	// Description: destroy physics
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none
	//

	bugboard->print(" b2world::destroy");
	delete world;

}

b2World* brains::body::b2world::worldget(void){
	// Description: return b2World pointer
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	return (world);
}

b2Body* brains::body::b2world::bodycreate(const b2BodyDef bodyDef){

	// Description: Create body on canvas
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	return(world->CreateBody(&bodyDef));

}

void brains::body::b2world::update(void){
	/*!
	* Description: Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	world->Step(timestep,iterations);
}

// BODY::B2BODY ////////////////////////////////////////////////////////////////
brains::body::b2body::b2body(){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	shapetypedef = 0;
	dynamicbody = NULL;
}

brains::body::b2body::~b2body(){

	/*!
	* Description: Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}

void brains::body::b2body::create(std::string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){
	/*!
	* Description: Create Box2D Physics Body & Shape
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("b2body::create");

	// Define the dynamic body. 

	bodyDef.position.Set((position.x + (size.x/2.0f)) /b2PixelRatio, (position.y + (size.y/2.0f)) /b2PixelRatio);
	
	//bodyDef.massData.mass = 2.0f;   // the body's mass in kg
	//bodyDef.center.SetZero();       // the center of mass in local coordinates
	//bodyDef.I = 3.0f;               // the rotational inertia in kg*m^2.
	//bodyDef.linearDamping = 0.0f;
	//bodyDef.angularDamping = 0.01f;
	//bodyDef.allowSleep = true;
	//bodyDef.isBullet = true;

	//select default canvas
	world = canvas::namemap[canvasname]->body->physics->worldget();

	//We set its position and call the body factory.
	dynamicbody = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	shapeDef.SetAsBox((size.x/b2PixelRatio)/2.0f, (size.y/b2PixelRatio)/2.0f);

	// Set the box density to be non-zero, so it will be dynamic.
	shapeDef.density = density;

	// Override the default friction.
	shapeDef.friction = friction;

	shapeDef.restitution = restitution;

	shapeDef.isSensor = sensor;

	// Add the shape to the body.
	dynamicbody->CreateShape(&shapeDef);

	// Now tell the dynamic body to compute it's mass properties base
	// on its shape.
	dynamicbody->SetMassFromShapes();

}

void brains::body::b2body::destroy(void){

	// Description: destroy physics
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none
	//
	bugboard->print(" b2body::destroy");
	world->DestroyBody(dynamicbody);

}

void brains::body::b2body::update(D3DVECTOR &position, D3DVECTOR &angle){

	/*!
	* Description: update physics sim
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	angle.z = (float)dynamicbody->GetAngle();
	angle.z *= (float)(180.0 / 3.141592653589793238);
	position = (D3DVECTOR&)dynamicbody->GetPosition();
	position.x *= b2PixelRatio; //MeterToPixel conversion
	position.y *= b2PixelRatio;

}

void brains::body::b2body::userdataset(void* userPTR){

	/*!
	* Description: store user pointer for circular reference
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bodyDef.userData = userPTR;

}

void *brains::body::b2body::userdataget(void){

	/*!
	* Description: returns user pointer
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	return(bodyDef.userData);

}

bool brains::body::b2body::orientationset(b2Vec2 position, float32 angle){

	/*!
	* Description: Set the position of the body's origin and rotation (radians). 
		this breaks any contacts and wakes the other bodies. 
		returns false if out of boundary
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	position.x /= b2PixelRatio;
	position.y /= b2PixelRatio;

	return(dynamicbody->SetXForm(position, angle));
}


// BODY::B2MOUSE ////////////////////////////////////////////////////////////////
brains::body::b2mouse::b2mouse(){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	world = NULL;
	mousejoint = NULL;

}

brains::body::b2mouse::~b2mouse(){

	/*!
	* Description: Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}


void brains::body::b2mouse::create(std::string canvasname){

	// Description: Create Box2D Physics Body & Shape
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	bugboard->print("b2mouse::create");
	world = canvas::namemap[canvasname]->body->physics->worldget();
}

void brains::body::b2mouse::destroy(void){

	// Description: destroy physics
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none
	//

	bugboard->print(" b2mouse::destroy");
	if(mousejoint != NULL){
		world->DestroyJoint(mousejoint);
	}

}

void brains::body::b2mouse::update(b2Vec2 p, int actionstate){

	/*!
	* Description: update physics sim
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	//pixel to meter
	p.x /= b2PixelRatio;
	p.y /= b2PixelRatio;

	//movement
	if(mousejoint){
		bugboard->print("\nmousejoint set target");
		mousejoint->SetTarget(p);
	}

	switch(actionstate){

		case 0: //up
			if (mousejoint){
				bugboard->print("\ndestroy mousejoint");
				world->DestroyJoint(mousejoint);
				mousejoint = NULL;
			}
			break;

		case BRAIN_DEVICE_MOUSE_BUTTON_LEFT: //down
			if (mousejoint != NULL){
				return;
			}

			bugboard->print("\ncreate mousejoint");

			world = basecanvas->body->physics->worldget();
			
			// create a small box.
			b2AABB aabb;
			b2Vec2 d;
			d.Set(0.001f, 0.001f);
			aabb.lowerBound = p - d;
			aabb.upperBound = p + d;

			bugboard->print("\n aabb(lower=");
			bugboard->print(dbStr(aabb.lowerBound.x));
			bugboard->print(",");
			bugboard->print(dbStr(aabb.lowerBound.y));
			bugboard->print(",upper=");
			bugboard->print(dbStr(aabb.upperBound.x));
			bugboard->print(",");
			bugboard->print(dbStr(aabb.upperBound.y));
			bugboard->print(")");			

			// Query the world for overlapping shapes.
			const int32 k_maxCount = 10;
			b2Shape* shapes[k_maxCount];
			int32 count = world->Query(aabb, shapes, k_maxCount);
			b2Body* dynamicbody = NULL;

			bugboard->print("\nQuery count = ");
			bugboard->print(dbStr(count));

			for (int32 i = 0; i < count; ++i){
				b2Body* shapeBody = shapes[i]->GetBody();
				if(shapeBody->IsStatic() == false && shapeBody->GetMass() > 0.0f){
					bool inside = shapes[i]->TestPoint(shapeBody->GetXForm(), p);
					if (inside){
						dynamicbody = shapes[i]->GetBody();
						break;
					}
				}
			}

			if (dynamicbody){
				b2MouseJointDef md;
				md.body1 = world->GetGroundBody();
				md.body2 = dynamicbody;
				md.target = p;
//#ifdef TARGET_FLOAT32_IS_FIXED
//				md.maxForce = (body->GetMass() < 16.0) ? (1000.0f * body->GetMass()) : float32(16000.0);
//#else
				md.maxForce = 1000.0f * dynamicbody->GetMass();
//#endif
				mousejoint = (b2MouseJoint*)world->CreateJoint(&md);
				dynamicbody->WakeUp();
			}

			break;
	}

}

// SPRITE ///////////////////////////////////////////////////////////////////////////////////////
brains::sprite::sprite(void){

	/*!
	* Description: sprite Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	dbImageID = dbObjectID = bgimageID = captiontype = 0;
	startframe = stopframe = currentframe = 0;

	captionstyle = NULL;
	caption = captionview = "";
	captionposition.x = captionposition.y = captionposition.z = 0;
	
	bgtheme = NULL;
	bgimagealign.x = bgimagealign.y = bgimagealign.z = 0;

	visibleflag = LODFlag = false;

}

brains::sprite::~sprite(void){

	/*!
	* Description: sprite Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/




}

int brains::sprite::imageload(std::string filename, int framesacross=1, int framesdown=1){

	/*!
	* Description: Draw Image 
	*
	* -#Input:
	*	-# string filename
	*	-# framesacross = frames across, used for animated sprite
	*	-# framesdown = frames down
	* -#Output:
	*	-# none
	*/
	
	startframe = framesacross;
	stopframe = framesdown;

	return(0);
}

int brains::sprite::imagedraw(brains::body *body, int actionstate){

	/*!
	* Description: Captures Image based on style and theme
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\nsprite::imagedraw state=");
	bugboard->print(dbStr(actionstate));

	if(!dbImageID){return(0);}

	bugboard->print("\ndbImageID=");
	bugboard->print(dbStr(dbImageID));
	bugboard->print("{sizex=");
	bugboard->print(dbStr(body->size.x));
	bugboard->print(",sizey=");
	bugboard->print(dbStr(body->size.y));	
	bugboard->print("}");

	//draw background
	bugboard->print("\ndraw background ");
	if(bgimageID){
		bugboard->print(" draw bgimageID = ");
		bugboard->print(dbStr(bgimageID));

		dbPasteImage(bgimageID,(int)bgimagealign.x,(int)bgimagealign.y);
	}

	//draw theme border
	if(bgtheme != NULL){

		bugboard->print("\ndraw theme ");
		bugboard->print(bgtheme->name);

		bgtheme->eventaction[actionstate]->draw(body->size);

		//Execute Theme Script
		if(bgtheme->eventaction[actionstate]->task != NULL){
			bugboard->print("\nexecute theme task ");
			bugboard->print(bgtheme->eventaction[actionstate]->task->name);
			bgtheme->eventaction[actionstate]->task->execute(darklua::task::RUNNING);
		}

	}

	//draw caption
	bugboard->print("\ndraw caption ");
	if(captionstyle != NULL){

		bugboard->print(captionstyle->name);

		//select ttf, bitmapfont, mesh

		if(captionstyle->eventaction[actionstate]==NULL){
			bugboard->print(" no style,");
		} else {
			captionstyle->eventaction[actionstate]->ttfontset();
		}

		//set caption
		bugboard->print("\nset captiontype=");
		bugboard->print(dbStr(captiontype));
		
		std::string captiontext;

		switch(captiontype){

			case BRAIN_SPRITE_CAPTIONTYPE_STANDARD:
				captiontext = caption;
				break;

			case BRAIN_SPRITE_CAPTIONTYPE_PASSWORD:
				//captiontext.insert(0,caption.length(),"*");
				break;

			case BRAIN_SPRITE_CAPTIONTYPE_HIDDEN:
				captiontext = "";
				break;

		}

		bugboard->print(",draw caption: ");
		bugboard->print(caption);
		bugboard->print("->");
		bugboard->print(captiontext);
		bugboard->print(" @ ");
		bugboard->print(dbStr(captionposition.x));
		bugboard->print(",");
		bugboard->print(dbStr(captionposition.y));

		//draw caption
		captionsize.x = dbTextWidth((char*)captiontext.data());
		captionsize.y = dbTextHeight((char*)captiontext.data());
		dbText( (int)captionposition.x, (int)captionposition.y, (char*)captiontext.data());

		//Execute Style Script
		if(captionstyle->eventaction[actionstate]->task != NULL){
			bugboard->print("\nexecute style task ");
			bugboard->print(captionstyle->eventaction[actionstate]->task->name);
			captionstyle->eventaction[actionstate]->task->execute(darklua::task::RUNNING);
		}
	}

	bugboard->print("\n~sprite::imagedraw");
	return(1);
}

int brains::sprite::imagecapture(brains::body *body, int actionstate){
	
	// Description: Captures Image based on style and theme
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	bugboard->print("\nsprite::imagecapture state=");
	bugboard->print(dbStr(actionstate));

	if(!dbImageID){return(0);}

	bugboard->print(" dbImageID = ");
	bugboard->print(dbStr(dbImageID));
	
	//prep resources
	int previousbitmapID = dbCurrentBitmap();
	int imagebitmapID = dbBitmapResource->pop();
	int imagememblockID = dbMemblockResource->pop();

	bugboard->print("\nbmp=");
	bugboard->print(dbStr(previousbitmapID));
	bugboard->print(",ibmp=");
	bugboard->print(dbStr(imagebitmapID));
	bugboard->print(",imem=");
	bugboard->print(dbStr(imagememblockID));	


	dbSetBitmapFormat(21); //located in DarkGDK Source::CBitmapC.h & *.cpp // mike - 061005 - new function to change bitmap format for alpha etc.

	dbCreateBitmap(imagebitmapID, (int)body->size.x, (int)body->size.y );
	
	if(dbBitmapExist(imagebitmapID)){
		bugboard->print(",bitmapexist");		
	}

	//colorkey based on theme eventaction[actionstate]
	if(bgtheme != NULL){
		bugboard->print(",colorkey");
		dbSetImageColorKey(bgtheme->eventaction[actionstate]->colorkeyred, bgtheme->eventaction[actionstate]->colorkeygreen, bgtheme->eventaction[actionstate]->colorkeyblue);
	}

	bugboard->print(" call imagedraw");

	imagedraw(body, actionstate);

	bugboard->print("\ncapturing image:");

    //Capture Image
    dbMakeMemblockFromBitmap(imagememblockID,imagebitmapID);
    dbMakeImageFromMemblock(dbImageID,imagememblockID);

	bugboard->print(dbStr(dbImageID));

	//restore previous bitmap
	dbSetCurrentBitmap(previousbitmapID);

	//delete db Resources
	dbDeleteMemblock(imagememblockID);
	dbDeleteBitmap(imagebitmapID);
    dbMemblockResource->push(imagememblockID);
	dbBitmapResource->push(imagebitmapID);

	bugboard->print("\n~sprite::imagecapture");
	return(1);
}

void brains::sprite::inherit(brains::sprite *parent){

	/*!
	* Description: Inheritor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	bugboard->print("\nsprite::inherit");

	type = parent->type;
	//dbImageID = parent->dbImageID;
	dbObjectID = parent->dbObjectID;
	startframe =  parent->startframe; 
	stopframe =  parent->stopframe; 
	currentframe = parent->currentframe;
	captionstyle = parent->captionstyle;
	captiontype = parent->captiontype;
	caption =  parent->caption; 
	captionview = parent->captionview;
	captionposition = parent->captionposition;
	bgtheme = parent->bgtheme;
	bgimageID = parent->bgimageID;
	bgimagealign = parent->bgimagealign;
	visibleflag = parent->visibleflag;
	LODFlag = parent->LODFlag;

}

// AGENT //////////////////////////////////////////////////////////////////////////////////////////
std::map<std::string,int> brains::agent::propertynamemap;
std::map<std::string,int>::iterator brains::agent::propertynamemapiterator;
std::map<std::string,brains::agent*> brains::agent::namemap;
std::map<std::string,brains::agent*>::iterator brains::agent::namemapiterator;
std::list<brains::agent*> brains::agent::activelist;
std::list<brains::agent*>::iterator brains::agent::activelistiterator;
std::queue<brains::agent*> brains::agent::inactivequeue;

int brains::agent::index = -1;

brains::agent::agent(void){

	/*!
	* Description: Default Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	ID = type = parentalcontrol = spriteID = priority = 0;
	collisionflag = visibleflag = audioflag = activeflag = false;
	parent = first = last = previous = next = NULL;
	body = NULL;
	device = NULL;

	eventstate.clear();

}

brains::agent::agent(std::string name, std::string description=""){

	/*!
	* Description: Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	this->name = name;
	this->description = description;
	ID = type = parentalcontrol = spriteID = priority = 0;
	collisionflag = visibleflag = audioflag = activeflag = false;
	parent = first = last = previous = next = NULL;
	body = NULL;
	device = NULL;
	state = DISABLED;

	eventstate.clear();
}

brains::agent::~agent(void){

	/*!
	* Description: Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}

brains::agent *brains::agent::create(std::string parentname, std::string name, std::string description, bool visible, bool collision){

	/*!
	* Description: Creates new agent
	*
	* -#Input:
	*	-# string parentname - name of parent agent
	*	-# string name - name for this agent
	*	-# string description - tooltip description
	*	-# bool visible - starting visibility
	*	-# bool collision - starting collision
	*
	* -#Output:
	*	-# none
	*/

	if(namemap[name] == NULL){
        namemap[name] = new agent(name, description);
	}

	namemap[name]->familyadd(namemap[parentname]);
	namemap[name]->inherit(namemap[parentname]);

	namemap[name]->visibleflag = visible;
	namemap[name]->collisionflag = collision;
	namemap[name]->audioflag = true;
	namemap[name]->activeflag = true;

	activelist.push_back(namemap[name]);
	namemap[name]->eventstate.state = BRAIN_EVENT_STATE_IDLE;
	namemap[name]->sync.set(60.0f,10);
	namemap[name]->state = ACTIVE;

	bugboard->print(" name=`");
	bugboard->print(name);
	bugboard->print("`,visibleflag=");
	bugboard->print(dbStr(namemap[name]->visibleflag));
	bugboard->print("`,collisionflag=");
	bugboard->print(dbStr(namemap[name]->collisionflag));
	bugboard->print("`,audioflag=");
	bugboard->print(dbStr(namemap[name]->audioflag));
	bugboard->print("`,activeflag=");
	bugboard->print(dbStr(namemap[name]->activeflag));
	bugboard->print(",state=");
	bugboard->print(dbStr(namemap[name]->state));

	return(namemap[name]);
}

void brains::agent::destroy(brains::agent *agent){
	
	/*!
	* Description: Destroys agent by pointer
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# brains::agent object pointer
	*/

	bugboard->print("\ndestroying Agent ");
	bugboard->print(agent->name);

	//destroy body & physics
	if(agent->body != NULL){
		bugboard->print(":body");
		if(agent->body->physics != NULL){
			bugboard->print(":physics");
			agent->body->physics->destroy();
			bugboard->print("(destroyed)");
			delete agent->body->physics;
		}
		delete agent->body;
	}

	//destroy eventaction
	std::map<int, eventscript *>::iterator eventactioniterator;

	bugboard->print(":eventactions");

	for(eventactioniterator = agent->eventaction.begin(); eventactioniterator !=  agent->eventaction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){

			if(((*eventactioniterator).second)->sprite != NULL){

				switch(agent->type){

					case BRAIN_AGENT_TYPE_2D:
						if(((*eventactioniterator).second)->sprite->dbImageID){
							//push to dbImageID potential orphan list?
							if(dbImageExist(((*eventactioniterator).second)->sprite->dbImageID)){
								dbDeleteImage(((*eventactioniterator).second)->sprite->dbImageID);
								bugboard->print(":dbimage");
							}
							dbImageResource->push(((*eventactioniterator).second)->sprite->dbImageID);
						}
						break;

					case BRAIN_AGENT_TYPE_3D:
						if(((*eventactioniterator).second)->sprite->dbObjectID){
							//push to dbObjectID potential orphan list?
							if(dbObjectExist(((*eventactioniterator).second)->sprite->dbObjectID)){
								bugboard->print(":dbobject");
								dbDeleteObject(((*eventactioniterator).second)->sprite->dbObjectID);
							}
							dbObjectResource->push(((*eventactioniterator).second)->sprite->dbObjectID);
						}
						break;
				}
				bugboard->print(":sprite");
				delete ((*eventactioniterator).second)->sprite;
			}

			//delete task script
			if(((*eventactioniterator).second)->task != NULL){
				bugboard->print(":task");
				delete ((*eventactioniterator).second)->task;
			}

			delete (*eventactioniterator).second;
		}
	}

	agent->eventaction.clear();	

	//destroy sprite

	if(agent->type == BRAIN_AGENT_TYPE_2D){
		if(agent->spriteID){
			if(dbSpriteExist(agent->spriteID)){
				bugboard->print(":dbsprite");
				dbDeleteSprite(agent->spriteID);
			}
			dbSpriteResource->push(agent->spriteID);
		}
	}

	delete agent;
	bugboard->print(":complete");
}

void brains::agent::destroy(void){

	/*!
	* Description: destroys all agents
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\nagent::destroy all");
	std::map<std::string,agent *>::iterator namemapiterator;
	for(namemapiterator = namemap.begin(); namemapiterator != namemap.end(); namemapiterator++){
		if( (*namemapiterator).second != NULL ){
			destroy((*namemapiterator).second);
		}
	}
	namemap.clear();
	bugboard->print("\n~agent::destroy all");
}


void brains::agent::trash(void){

	/*!
	* Description: sends agent to garbage
	*
	* -#Input:

	* -#Output:
	*	-# none
	*/

	if(inactivequeue.front()->parent != NULL){
		inactivequeue.front()->familyremove();
	}

	state = DISABLED;
	inactivequeue.push(this);
}

brains::agent *brains::agent::get(std::string name){
	/*!
	* Description: Return pointer by name; if not available will create pointer
	*
	* -#Input:
	*	-# string name - agent name
	*
	* -#Output:
	*	-# none
	*/
	
	if(namemap[name] == NULL){ 
		namemap[name] = new agent(name, "tbd");
	}
	return(namemap[name]);
}

void brains::agent::inherit(brains::agent *parent){
	
	/*!
	* Description: Copies agent components
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	this->collisionflag = parent->collisionflag;
	this->visibleflag = parent->visibleflag;
	this->audioflag = parent->audioflag;
	this->activeflag = parent->activeflag;

} 

void brains::agent::familyadd(brains::agent *parent){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\nFAM:");
	bugboard->print(this->name);

	if(parent != NULL){
		this->parent = parent;

		bugboard->print(";P:");
		bugboard->print(parent->name);	

		if(parent->first == NULL){
			parent->first = parent->last = this;

			bugboard->print(";Pf:");
			bugboard->print(parent->first->name);
			bugboard->print(";Pl:");
			bugboard->print(parent->last->name);

		} else {

			this->previous = parent->last;
			this->next = parent->first;
			parent->first->previous = parent->last->next = parent->last = this;

			bugboard->print(";Pf:");
			bugboard->print(parent->first->name);
			bugboard->print(";Pl:");
			bugboard->print(parent->last->name);
			bugboard->print(";Sp:");
			bugboard->print(this->previous->name);
			bugboard->print(";Sn:");
			bugboard->print(this->next->name);
			bugboard->print(";PfSp:");
			bugboard->print(parent->first->previous->name);
			bugboard->print(";PlSn:");
			bugboard->print(parent->last->next->name);

		}

	}

}

void brains::agent::familyremove(void){

	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print(":FAM");

	if(parent != NULL && parent != this){
		bugboard->print(";P:");
		bugboard->print(parent->name);

		bugboard->print(" 1");
		if(parent->first == NULL){
			bugboard->print("_");
		}
		if(parent->first != NULL){
			bugboard->print("=");
			if(parent->first == this){
				bugboard->print(";Pf:");
				bugboard->print(parent->first->name);
				if(previous != NULL){
					bugboard->print(";Sp:");
					bugboard->print(previous->name);
					parent->first = previous;
					bugboard->print("*");
				}
				bugboard->print("*");
			}
		}

		bugboard->print(" 2");
		if(parent->last == NULL){
			bugboard->print("_");
		}
		if(parent->last != NULL){
			bugboard->print("=");
			if(parent->last == this){
				bugboard->print(";Pl:");
				bugboard->print(parent->last->name);
				if(next != NULL){
					bugboard->print(";Sn:");
					bugboard->print(next->name);
					parent->last = next;
					bugboard->print("*");
				}
				bugboard->print("*");
			}
		}

		bugboard->print(" 3");
		if(previous->next == NULL){
			bugboard->print("_");
		}
		if(previous->next != NULL){
			bugboard->print("=");
			if(previous->next == this){
				bugboard->print(";Spn:");
				bugboard->print(previous->next->name);
				if(next != NULL){
					bugboard->print(";Sn:");
					bugboard->print(next->name);
					previous->next = next;
					bugboard->print("*");
				}
				bugboard->print("*");
			}
		}

		bugboard->print(" 4");
		if(next->previous == NULL){
			bugboard->print("_");
		} else {
			bugboard->print("?");
		}
		if(next->previous != NULL){
			bugboard->print("=");
			if(next->previous == this){
				bugboard->print(";Snp:");
				bugboard->print(next->previous->name);
				if(previous != NULL){
					bugboard->print(";Sp:");
					bugboard->print(previous->name);	
					next->previous = previous;
					bugboard->print("*");
				}
				bugboard->print("*");
			}
		}

		bugboard->print("5");

	}

	bugboard->print("#");
}

void brains::agent::update(void){

	/*!
	* Description: Iterates through all agents, executes process
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	//iterate through active agents
	for(activelistiterator = activelist.begin(); activelistiterator != activelist.end(); activelistiterator++ ){
		//if((*activelistiterator)->sync.tick()){ //update sync
			(*activelistiterator)->process();
		//}
	}

	//Garbage Collection clean up inactive agents
	while (!inactivequeue.empty()){

		if(inactivequeue.front()->activeflag){
			activelist.remove(inactivequeue.front());
		}
		destroy(inactivequeue.front());
		inactivequeue.pop();
	}

}

void brains::agent::process(void){
	/*!
	* Description:
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	switch(state){

		case DISABLED:
			break;

		case DRAW:
/*
			switch(type){
				case BRAIN_AGENT_TYPE_2D:
					imagecapture(BRAIN_EVENT_STATE_IDLE);
					if(body->physicsflag){
						spriteoffset();
					}
					break;
			}
			state = ACTIVE;
*/
			break;

		case ACTIVE:

			//controller
			control();

			//collsion
			if(collisionflag){
				collision();

				//locate testing
				if(this == namemap["min2"]){
					locate(this,BRAIN_EVENT_STATE_IDLE);
				}

			}

			//behavior
			operate();

			//transition
			transit();

			//action
			action();

			//audio
			if(audioflag){
				produce();
			}

			//display
			if(visibleflag && spriteID){
				display();
			}

			break;

	}

}

void brains::agent::imagecapture(int actionstate){

	/*!
	* Description: Draws image and assigns to sprite based on actionstate
	*	sprite,body,theme,style must preexist
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	bugboard->print("\nagent::imagecapture state=");
	bugboard->print(dbStr(actionstate));

	if(eventaction[actionstate]->sprite != NULL){
		bugboard->print(" (Good) ");
	}
	
	bugboard->print(name);
	bugboard->print(" dbImageID = (pre)");
	bugboard->print(dbStr(eventaction[actionstate]->sprite->dbImageID));

	if(!eventaction[actionstate]->sprite->dbImageID){
		eventaction[actionstate]->sprite->dbImageID = dbImageResource->pop();
	}
	
	bugboard->print(",(post)");
	bugboard->print(dbStr(eventaction[actionstate]->sprite->dbImageID));
		
	eventaction[actionstate]->sprite->imagecapture(
		body,
		actionstate
	);
	
	bugboard->print("\ndbSprite(");
	bugboard->print(dbStr(spriteID));
	bugboard->print(",");
	bugboard->print(dbStr(eventaction[actionstate]->sprite->dbImageID));
	bugboard->print(")");

	bugboard->print(" State=");
	bugboard->print(dbStr(actionstate));

	dbSetSprite(spriteID,0,1); //set sprite;

	dbSprite(
		spriteID,
		(int)body->position.x,
		(int)body->position.y,
		eventaction[actionstate]->sprite->dbImageID
	);

	if(body->physicsflag){spriteoffset();}

	dbHideSprite(spriteID);

	bugboard->print("~agent::imagecapture");
}

void brains::agent::texturecapture(int actionstate){

	/*!
	* Description: Draws image and assigns to object as texture based on actionstate
	*	sprite,body,theme,style must preexist
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	bugboard->print("\nagent::texturecapture state=");
	bugboard->print(dbStr(actionstate));

	if(eventaction[actionstate]->sprite != NULL){
		bugboard->print(" (Good) ");
	}
	
	bugboard->print(name);
	bugboard->print(" dbImageID = (pre)");
	bugboard->print(dbStr(eventaction[actionstate]->sprite->dbImageID));

	if(!eventaction[actionstate]->sprite->dbImageID){
		eventaction[actionstate]->sprite->dbImageID = dbImageResource->pop();
	}
	
	bugboard->print(",(post)");
	bugboard->print(dbStr(eventaction[actionstate]->sprite->dbImageID));
		
	eventaction[actionstate]->sprite->imagecapture(
		body,
		actionstate
	);
	
	bugboard->print("\ndbSprite(");
	bugboard->print(dbStr(spriteID));
	bugboard->print(",");
	bugboard->print(dbStr(eventaction[actionstate]->sprite->dbImageID));
	bugboard->print(")");

	bugboard->print(" State=");
	bugboard->print(dbStr(actionstate));

	//texture object
	spriteID = eventaction[actionstate]->sprite->dbObjectID;
	dbTextureObject(spriteID, eventaction[actionstate]->sprite->dbImageID);
	
	//dbHideObject(spriteID);

	bugboard->print("~agent::texturecapture");
}

void brains::agent::spriteoffset(void){

	/*!
	* Description: Offsets sprite for Box2D physics
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	dbOffsetSprite(
		spriteID,
		(int)body->size.x/2,
		(int)body->size.y/2
	);

}

void brains::agent::control(void){

	/*!
	* Description: Movement Controller
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	if(device!=NULL){

		//device->axisquery();

		if(body!=NULL){

			body->position.x = device->axis.x;
			body->position.y = device->axis.y;
			body->position.z = device->axis.z;

			switch(device->type){

				case BRAIN_DEVICE_TYPE_MOUSE:
					if(body->physicsflag){
						body->physics->update((b2Vec2&)body->position, device->contact); //move
					}
					break;

				/*
				case  BRAIN_DEVICE_TYPE_MANUAL: //manual position, rotation physicsobject:b2body
					if(body->physicsflag){					
						body->position.x += body->size.x/2.0;
						body->position.y += body->size.y/2.0;
						body->physics->orientationset((b2Vec2&)caret->body->position, body->angle);
						body->physics->update(body->position, body->angle);
					}
					break;

				*/

			}

		}

	} else {

		if(body!=NULL){
			//physics
			if(body->physicsflag){
				body->physics->update(body->position, body->angle);
			}
		}
	}

}

void brains::agent::collision(void){

	/*!
	* Description: Collision Detection, Input Device Contact Collision Detection
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	switch(type){

		case BRAIN_AGENT_TYPE_0D:
			//select device 
			//check axisqueue contactqueue for matching 'value' valuemap
			//if no match flush queue
			if(device != NULL){
				switch(device->type){

					case BRAIN_DEVICE_TYPE_MOUSE:
						if(device->contactexist == (int)dbVal((char*)valuemap["value"].data()) ){
							device->contactexist = device->contact;
						} else {
							device->contactexist = 0;
						}	
						break;

					case BRAIN_DEVICE_TYPE_KEYBOARD:
	
						//bugboard->enable();
						bugboard->print("\nAgent ");
						bugboard->print(name);
						bugboard->print(" contact=");	
						bugboard->print(dbStr(device->contact));
						bugboard->print(" valuemap::value=");	
						bugboard->print(valuemap["value"]);
						bugboard->print(" scancode=");
						bugboard->print(dbStr(scancodemap[valuemap["value"]]));
						//bugboard->disable();

						//single key
						if(device->contact == scancodemap[valuemap["value"]] ){
							device->contactexist = device->contact;
						} else {
							device->contactexist = 0;
						}	
						break;
				}
			}
			break;

		case BRAIN_AGENT_TYPE_1D:
		case BRAIN_AGENT_TYPE_2D:

			switch(body->type){

				case 0: //box2d
					/*
					if(device != NULL){
					} else {
						//physics collision reponse
						if(body->physicsflag){
							//do stuff
						}
					}
					*/

					if(this != pointer){
						if(pointer->body->position.x > body->position.x - (body->size.x/2.0) && pointer->body->position.x < (body->position.x - (body->size.x/2.0)) + body->size.x && pointer->body->position.y > body->position.y - (body->size.y/2.0) && pointer->body->position.y < (body->position.y - (body->size.y/2.0)) + body->size.y){
							body->collisionexist = 1;
						} else {
							body->collisionexist = 0;
						}
					}

					/*
					body->collisionexist ? dbInk(dbRGB(0,255,0),0) : dbInk(dbRGB(255,0,0),0);
					dbText( (int)(body->position.x - (body->size.x/2.0)), (int)(body->position.y - (body->size.y/2.0)),(char*)name.data());
					dbLine( (int)(body->position.x - (body->size.x/2.0)), (int)(body->position.y - (body->size.y/2.0)), (int)(body->position.x - (body->size.x/2.0)) + (int)body->size.x, (int)(body->position.y - (body->size.y/2.0)));
					dbLine( (int)(body->position.x - (body->size.x/2.0)) + (int)body->size.x, (int)(body->position.y - (body->size.y/2.0)), (int)(body->position.x - (body->size.x/2.0)) + (int)body->size.x, (int)(body->position.y - (body->size.y/2.0)) + (int)body->size.y);
					dbLine( (int)(body->position.x - (body->size.x/2.0)) + (int)body->size.x, (int)(body->position.y - (body->size.y/2.0)) + (int)body->size.y, (int)(body->position.x - (body->size.x/2.0)), (int)(body->position.y - (body->size.y/2.0)) + (int)body->size.y);
					dbLine( (int)(body->position.x - (body->size.x/2.0)), (int)(body->position.y - (body->size.y/2.0)) + (int)body->size.y, (int)(body->position.x - (body->size.x/2.0)) , (int)(body->position.y - (body->size.y/2.0)));
					*/
					dbInk(dbRGB(255,255,255),0);

					break;

				case 1: //procedural
					//this vs pointer
					if(this != pointer){
						if(pointer->body->position.x > body->position.x - (body->size.x/2.0) && pointer->body->position.x < (body->position.x - (body->size.x/2.0)) + body->size.x
						&& pointer->body->position.y > body->position.y - (body->size.y/2.0) && pointer->body->position.y < (body->position.y - (body->size.y/2.0)) + body->size.y){
							pointer->body->collisionqueue.push(body);
						}
					}
					break;
			}
			break;

		case BRAIN_AGENT_TYPE_3D:

			switch(body->type){

				case 1://reserved fulcrum collision
					break;
				
				case 0: //dgdk collision
					if(this != pointer){
						if( dbPickObject( (int)pointer->body->position.x, (int)pointer->body->position.y, spriteID, spriteID) ){
							body->collisionexist = 1;
						} else {
							body->collisionexist = 0;
						}
					}
					break;
			}
			break;

	}
	
}

void brains::agent::operate(void){

	/*!
	* Description: Select and Execute Behavior Script based on eventstate.state
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	//bugboard->enable();

	if(eventaction[eventstate.state]->behavior != NULL){
		if(eventaction[eventstate.state]->behavior->eventaction[eventstate.state] != NULL){

			if(eventaction[eventstate.state]->behavior->eventaction[eventstate.state]->task != NULL){

				//set previousstate
				eventstate.previousstate = eventstate.state;
				
				//set script globals based on type
				darklua::pointerset("this",(agent*)this);
				darklua::integerset("uiAgentEventstate",eventstate.state);

				switch(type){

					case BRAIN_AGENT_TYPE_0D:
						if(device != NULL){
							darklua::integerset("uiAgentContact",device->contactexist);
							darklua::floatset("uiAgentAxisX",device->axis.x);
							darklua::floatset("uiAgentAxisY",device->axis.y);
							darklua::floatset("uiAgentAxisZ",device->axis.z);
						}
						break;

					default:
						darklua::integerset("uiPointerBound",body->collisionexist);
						darklua::integerset("uiPointerContact",pointer->device->contactexist);
						break;
				}

				eventaction[eventstate.state]->behavior->eventaction[eventstate.state]->task->execute(darklua::task::RUNNING);
				//get script globals
				eventstate.state = darklua::integerget("uiAgentNextEventstate");

				//NextEventstate
				if(this == namemap["movecamforward"]){
					//bugboard->enable();

					bugboard->print("\nOperate ");
					bugboard->print(name);
					bugboard->print(" ");
					if(eventaction[eventstate.state]->behavior->name==""){
						bugboard->print("default");		
					} else {
						bugboard->print(eventaction[eventstate.state]->behavior->name);		
					}
					//bugboard->print(" Bound=");
					//bugboard->print(dbStr(body->collisionexist));
					//bugboard->print(" Contact=");
					//bugboard->print(dbStr(pointer->device->contactexist));
					bugboard->print(" Contact=");
					bugboard->print(dbStr(device->contactexist));
					bugboard->print(" Eventstate=");
					bugboard->print(dbStr(eventstate.previousstate));
					bugboard->print("|");
					bugboard->print(dbStr(eventstate.state));
					bugboard->print(" EventstateCounter=");
					bugboard->print(dbStr(eventstate.counter));

					//bugboard->disable();
				}


			}
		}
	}

	//bugboard->disable();
}

void brains::agent::transit(void){

	/*!
	* Description: Select and Execute Transisition Script based on eventstate.state from previous
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(eventaction[eventstate.state]->transition != NULL){
		if(eventaction[eventstate.state]->transition->eventaction[eventstate.state] != NULL){

			if(eventstate.state != eventstate.previousstate){
				eventstate.transitstate = eventstate.previousstate;
			}

			if(eventaction[eventstate.state]->transition->eventaction[eventstate.state]->task != NULL){
				//setup variables
					//set script globals
					darklua::pointerset("this",(agent*)this);
					darklua::integerset("uiAgentPreviousEventstate",eventstate.transitstate);
					eventaction[eventstate.state]->transition->eventaction[eventstate.state]->task->execute(darklua::task::RUNNING);
					//get script globals
					eventstate.transitstate = darklua::integerget("uiAgentPreviousEventstate");
			}

		}
	}
}

void brains::agent::action(void){

	/*!
	* Description: Select and Execute Transisition Script based on eventstate.state
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
			
	if(eventaction[eventstate.state]->task != NULL){

		darklua::pointerset("this",(agent*)this);

		eventaction[eventstate.state]->task->execute(darklua::task::RUNNING);
		
		if(darklua::errormessage!=""){bugboard->print((char*)darklua::errormessage.data());}

	}

}

void brains::agent::produce(void){

	// Description: Agent Audio Update
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	if(eventaction[eventstate.state] != NULL){

		if(eventaction[eventstate.state]->scheme != NULL){

			if(eventstate.state != eventstate.previousstate){
				//turn off previous sound

				bugboard->print(" produce previousstate ");

				if(eventaction[eventstate.previousstate]->scheme != NULL){

					bugboard->print(eventaction[eventstate.previousstate]->scheme->name);

					if(eventaction[eventstate.previousstate]->scheme->eventaction[eventstate.previousstate]!= NULL){

						switch(eventaction[eventstate.previousstate]->scheme->eventaction[eventstate.previousstate]->system){

							case BRAIN_SCHEME_AUDIO_SYSTEM_DGDK:
								
								switch(eventaction[eventstate.previousstate]->scheme->eventaction[eventstate.previousstate]->type){

									case BRAIN_SCHEME_AUDIO_TYPE_SOUND:
										if(dbSoundPlaying(eventaction[eventstate.previousstate]->scheme->eventaction[eventstate.previousstate]->audioID)){
											dbStopSound(eventaction[eventstate.previousstate]->scheme->eventaction[eventstate.previousstate]->audioID);
										}
										break;

									case BRAIN_SCHEME_AUDIO_TYPE_MUSIC:
										if(dbMusicPlaying(eventaction[eventstate.previousstate]->scheme->eventaction[eventstate.previousstate]->audioID)){
											dbStopMusic(eventaction[eventstate.previousstate]->scheme->eventaction[eventstate.previousstate]->audioID);
										}
										break;
								}
								break;
					
							case BRAIN_SCHEME_AUDIO_SYSTEM_OAW:
								break;
						}

					}

				}
				//eventaction[eventstate.state]->scheme->eventaction[eventstate.previousstate]->loopcount = 0;

			} else {

				//start new sound, if not playing
				if(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]!= NULL){

					//if(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->loopcount < eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->loop){
						
						switch(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->system){

							case BRAIN_SCHEME_AUDIO_SYSTEM_DGDK:
								
								switch(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->type){

									case BRAIN_SCHEME_AUDIO_TYPE_SOUND:
										if(!dbSoundPlaying(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->audioID)){
											bugboard->print("\nPlay Sound");
											dbPlaySound(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->audioID);
											//eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->loopcount++;
										}
										break;

									case BRAIN_SCHEME_AUDIO_TYPE_MUSIC:
										if(!dbMusicPlaying(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->audioID)){
											bugboard->print("\nPlay Music");
											dbPlayMusic(eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->audioID);
											//eventaction[eventstate.state]->scheme->eventaction[eventstate.state]->loopcount++;
										}
										break;
								}
								break;
					
							case BRAIN_SCHEME_AUDIO_SYSTEM_OAW:
								break;
						}

					//}

				}

			}
			
		}

	}

}

void brains::agent::display(void){

	/*!
	* Description: Agent Display Update
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	if(body != NULL){
/*
		//default shape
		dbInk(dbRGB(127,127,0),0);
		D3DVECTOR position = body->position;
		D3DVECTOR size = body->size;
		position.x -= (float)size.x/2.0;
		position.y -= (float)size.y/2.0;
		dbText( (int)position.x, (int)position.y,(char*)name.data());
		dbLine( (int)position.x, (int)position.y, (int)position.x + (int)size.x, (int)position.y);
		dbLine( (int)position.x + (int)size.x, (int)position.y, (int)position.x + (int)size.x, (int)position.y + (int)size.y);
		dbLine( (int)position.x + (int)size.x, (int)position.y + (int)size.y, (int)position.x, (int)position.y + (int)size.y);
		dbLine( (int)position.x, (int)position.y + (int)size.y, (int)position.x , (int)position.y);
		//dbPasteImage(eventaction[eventstate.state]->sprite->dbImageID, body->position.x , body->position.y);

*/
		switch(type){

			case BRAIN_AGENT_TYPE_2D:
				//switch sprite image, if state has change and another image exists
				if(eventstate.state != eventstate.previousstate){
					if(eventaction[eventstate.state] != NULL){
						if(eventaction[eventstate.state]->sprite != NULL){
							if(eventaction[eventstate.state]->sprite->dbImageID){
								dbSetSpriteImage(spriteID, eventaction[eventstate.state]->sprite->dbImageID);
							}
						}
					}
				}

				//draw sprite
				if(dbSpriteExist(spriteID)){
					dbPasteSprite(spriteID, (int)body->position.x, (int)body->position.y);
					dbRotateSprite(spriteID, body->angle.z);//
				}
				break;

			case BRAIN_AGENT_TYPE_3D:
				//switch sprite object, if state has change and another image exists
				if(eventstate.state != eventstate.previousstate){
					if(eventaction[eventstate.state] != NULL){
						if(eventaction[eventstate.state]->sprite != NULL){
							if(eventaction[eventstate.state]->sprite->dbObjectID){
								spriteID = eventaction[eventstate.state]->sprite->dbObjectID;
								if(dbObjectInScreen(spriteID)){
									dbShowObject(spriteID);
								} else {
									if(dbObjectVisible(spriteID)){
										dbHideObject(spriteID);
									}
								}
							}
						}
					}
				}
				//Physics Physx
				break;
		}

	}
}

void brains::agent::propertyadd(std::string key,const int constant){

	// Description: Add propertyname key
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	if(!propertynamemap[key]){
		propertynamemap[key] = constant;
	}
}

char* brains::agent::propertyget(brains::agent* agent, std::string key){

	// Description: Get property value based on keyname
	//	DarkLUA Bind: `uiAgentPropertyGet`
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	//bugboard->enable();
	//bugboard->print("\nagent::propertyget ");
	//bugboard->print(agent->name);
		
	if(agent != NULL){

		//bugboard->print(" ");
		//bugboard->print(key);
		//bugboard->print("(");
		//bugboard->print(dbStr(propertynamemap[key]));
		//bugboard->print(")=");
		
		switch(propertynamemap[key]){

			case BRAIN_AGENT_PROPERTY_DESCRIPTION:
				return((char*)agent->description.data());

			case BRAIN_AGENT_PROPERTY_EVENTSTATE_STATE:
				return(dbStr(agent->eventstate.state));

			case BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNT:
				return(dbStr(agent->eventstate.count));

			case BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNTER:
				//bugboard->print(dbStr(agent->eventstate.counter));
				//bugboard->disable();
				return(dbStr(agent->eventstate.counter));

			case BRAIN_AGENT_PROPERTY_BOUND_COLLISION:
				return(dbStr(agent->body->collisionexist));

			case BRAIN_AGENT_PROPERTY_CONTACT_COLLISION:
				return(dbStr(agent->device->contactexist));

			case BRAIN_AGENT_PROPERTY_AXIS_X:
				return(dbStr(agent->device->axis.x));

			case BRAIN_AGENT_PROPERTY_AXIS_Y:
				return(dbStr(agent->device->axis.y));

			case BRAIN_AGENT_PROPERTY_AXIS_Z:
				return(dbStr(agent->device->axis.z));

			case BRAIN_AGENT_PROPERTY_SPRITE_QUAD:
				return(dbStr(agent->spriteID));

		}

	}

	//bugboard->disable();
	return("");
}

void brains::agent::propertyset(brains::agent *agent, std::string key, char* value){

	// Description: Set property value based on keyname
	//	DarkLUA Bind: `uiAgentPropertySet`
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	//bugboard->enable();
	//bugboard->print("\nagent::propertyset ");
	//bugboard->print(agent->name);

	if(agent != NULL){

		//bugboard->print(" value=");
		//bugboard->print(value);
		//bugboard->print(" ");
		//bugboard->print(key);
		//bugboard->print("(");
		//bugboard->print(dbStr(propertynamemap[key]));
		//bugboard->print(")=");
		
		switch(propertynamemap[key]){

			case BRAIN_AGENT_PROPERTY_DESCRIPTION:
				agent->description = value;
				break;

			case BRAIN_AGENT_PROPERTY_EVENTSTATE_STATE:
				agent->eventstate.state = dbVal(value);
				break;

			case BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNT:
				agent->eventstate.count = dbVal(value);
				break;

			case BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNTER:
				agent->eventstate.counter = dbVal(value);
				//bugboard->print(dbStr(agent->eventstate.counter));
				break;

			case BRAIN_AGENT_PROPERTY_BOUND_COLLISION:
				agent->body->collisionexist = dbVal(value);
				break;

			case BRAIN_AGENT_PROPERTY_CONTACT_COLLISION:
				agent->device->contactexist = dbVal(value);
				break;

			case BRAIN_AGENT_PROPERTY_AXIS_X:
				agent->device->axis.x = dbVal(value);
				break;

			case BRAIN_AGENT_PROPERTY_AXIS_Y:
				agent->device->axis.y = dbVal(value);
				break;

			case BRAIN_AGENT_PROPERTY_AXIS_Z:
				agent->device->axis.z = dbVal(value);
				break;

			case BRAIN_AGENT_PROPERTY_SPRITE_QUAD:
				agent->spriteID = dbVal(value);
				break;

		}

	}
	//bugboard->disable();

}

char* brains::agent::variableget(agent *agent, std::string variable){
	// Description: Get agent variable based on valuemap key
	//	DarkLUA Bind: `uiAgentVariableGet`
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	return((char*)agent->valuemap[variable].data());
}

void brains::agent::variableset(agent *agent, std::string variable, std::string value){
	// Description: Set agent variable based on valuemap key
	//	DarkLUA Bind: `uiAgentVariableSet`
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none

	agent->valuemap[variable] = value;
}

void brains::agent::locate(brains::agent *agent, int actionstate){

	//!
	// Description: Sets caret position, based on pointer position, relative characters in caption
	//	assumes agent->body->collisionexist = true
	//	Note: MAUI reserves the use of Numbers as Valuemap Keys to store text strings as Line Buffers 
	//		(ie: valuemap["1"] = "Hello World") in Agents.
	//  
	//	Other reserved valuemap keys
	//		Agent:		
	//			"linecount" - holds number of lines
	//
	//		Caret:
	//			"focusedagent" - agent name to focus on
	//			"startlineposition" - focus agent line position (y)
	//			"startlinecharacterposition" - focus agent line character position (x), starts in front of character
	//			"stoplineposition" - focus agent line position (y)
	//			"stoplinecharacterposition" - focus agent line character position (x), starts in front of character
	//
	// -#Input:
	//	-# none
	//
	// -#Output:
	//	-# none
	///

	bugboard->enable();
	bugboard->print("\nagent::locate ");
	bugboard->print(agent->name);

	bool linefound = false;
	int linecount;
	int linecounter;
	float lineheight; //tallest character height
	float liney;
	float linecharacterx;
	float linecharacterwidth;

	if (pointer != NULL && caret != NULL){

		switch(agent->type){

			case BRAIN_AGENT_TYPE_2D:

				if(agent->body->collisionexist){

					linecount = dbVal((char*)agent->valuemap["linecount"].data());

					bugboard->print(" linecount=");
					bugboard->print(dbStr(linecount));

					if(!linecount){
						bugboard->print(" ~agent::locate");
						bugboard->disable();
						return;
					}

					liney = agent->body->position.y - (agent->body->size.y/2.0);

					bugboard->print(" liney=");
					bugboard->print(dbStr(liney));

					for(linecounter=1; linecounter < linecount + 1; linecounter++){

						//determine line

						bugboard->print("\nlinecounter=");
						bugboard->print(dbStr(linecounter));
						bugboard->print(":");
						bugboard->print(dbStr(linecount));

						//total caption character width / max font height
						lineheight = dbTextHeight((char*)agent->valuemap[dbStr(linecounter)].data()); //tallest character height

						bugboard->print(" lineheight=");
						bugboard->print(dbStr(lineheight));

						dbInk(dbRGB(255,255,0),0);
						dbText( (int)(agent->body->position.x - (agent->body->size.x/2.0)), (int)liney, (char*)agent->valuemap[dbStr(linecounter)].data() );
						dbLine( (int)(agent->body->position.x - (agent->body->size.x/2.0)), (int)liney, (int)(agent->body->position.x - (agent->body->size.x/2.0)) + (int)agent->body->size.x, (int)liney);
						dbLine( (int)(agent->body->position.x - (agent->body->size.x/2.0)) + (int)agent->body->size.x, (int)liney, (int)(agent->body->position.x - (agent->body->size.x/2.0)) + (int)agent->body->size.x, (int)liney + (int)lineheight);
						dbLine( (int)(agent->body->position.x - (agent->body->size.x/2.0)) + (int)agent->body->size.x, (int)liney + (int)lineheight, (int)(agent->body->position.x - (agent->body->size.x/2.0)), (int)liney + (int)lineheight);
						dbLine( (int)(agent->body->position.x - (agent->body->size.x/2.0)), (int)liney + (int)lineheight, (int)(agent->body->position.x - (agent->body->size.x/2.0)) , (int)liney);

						if(pointer->body->position.y > liney && pointer->body->position.y < liney + lineheight){

							linecharacterx = (agent->body->position.x - (agent->body->size.x/2.0));

							bugboard->print(" linecharacterx=");
							bugboard->print(dbStr(linecharacterx));

							int linecharactercount = agent->valuemap[dbStr(linecounter)].size();

							bugboard->print(" linecharactercount=");
							bugboard->print(dbStr(linecharactercount));

							//determine character width & height
							for(int linecharactercounter=0; linecharactercounter < linecharactercount; linecharactercounter++){
							
								//dbTextWidth()
								std::string linecharacter = agent->valuemap[dbStr(linecounter)].substr(linecharactercounter,1);
								linecharacterwidth = dbTextWidth((char*)linecharacter.data());
								
								//bugboard->print(" ");
								//bugboard->print(linecharacter);
								//bugboard->print(":");
								//bugboard->print(dbStr(linecharactercounter));
								//bugboard->print("/");
								//bugboard->print(dbStr(linecharacterwidth));

								dbInk(dbRGB(0,255,255),0);
								dbText( (int)linecharacterx, (int)liney, (char*)linecharacter.data() );
								dbLine( (int)linecharacterx, (int)liney, (int)linecharacterx + (int)linecharacterwidth, (int)liney);
								dbLine( (int)linecharacterx + (int)linecharacterwidth, (int)liney, (int)linecharacterx + (int)linecharacterwidth, (int)liney + (int)lineheight);
								dbLine( (int)linecharacterx + (int)linecharacterwidth, (int)liney + (int)lineheight, (int)linecharacterx, (int)liney + (int)lineheight);
								dbLine( (int)linecharacterx, (int)liney + (int)lineheight, (int)linecharacterx , (int)liney);
								
								//get character
								if(pointer->body->position.x > linecharacterx && pointer->body->position.x < linecharacterx + linecharacterwidth){

									dbInk(dbRGB(255,255,255),0);
									dbText( (int)linecharacterx, (int)liney, (char*)linecharacter.data() );
									dbLine( (int)linecharacterx, (int)liney, (int)linecharacterx + (int)linecharacterwidth, (int)liney);
									dbLine( (int)linecharacterx + (int)linecharacterwidth, (int)liney, (int)linecharacterx + (int)linecharacterwidth, (int)liney + (int)lineheight);
									dbLine( (int)linecharacterx + (int)linecharacterwidth, (int)liney + (int)lineheight, (int)linecharacterx, (int)liney + (int)lineheight);
									dbLine( (int)linecharacterx, (int)liney + (int)lineheight, (int)linecharacterx , (int)liney);

									//determine front/rear position
									caret->body->position.y = liney + (caret->body->size.y/2.0);
																		
									if(pointer->body->position.x < linecharacterx + (linecharacterwidth/2.0)){

										//position caret in front
										caret->body->position.x = linecharacterx + (caret->body->size.x/2.0);

									} else {
										
										//position caret in rear
										caret->body->position.x = linecharacterx + linecharacterwidth + (caret->body->size.x/2.0);

									}

									//set caret values
									
									caret->body->physics->orientationset((b2Vec2&)caret->body->position, 0);

									caret->valuemap["focusedagent"] = agent->name;
									caret->valuemap["startlineposition"] = dbStr(linecounter);
									caret->valuemap["startlinecharacterposition"] = dbStr(linecharactercounter);

									bugboard->print(" focusedagent=");
									bugboard->print(caret->valuemap["focusedagent"]);
									bugboard->print(" startlineposition=");
									bugboard->print(caret->valuemap["startlineposition"]);
									bugboard->print(" startlinecharacterposition=");
									bugboard->print(caret->valuemap["startlinecharacterposition"]);


									bugboard->print(" ~~agent::locate");
									bugboard->disable();
									
									return;
								
								} else {

									//next character
									linecharacterx += linecharacterwidth;
							
								}
							
							}

							//caret at end of line
							bugboard->print(" end of line ~~agent::locate");
							bugboard->disable();
							return;
							
						} else {

							//next line
							liney += lineheight;
							
						}

					}

				}
				
				break;

			case BRAIN_AGENT_TYPE_3D:
				break;
		}


	}

	bugboard->print(" ~~~agent::locate");
	bugboard->disable();

}

/*
void brains::agent::linecharacterinsert(){

	locate caret line & linecharacter position
	insert new character in front of caret in line
	if(multilineflag){
		if(wordwrapflag){
			thisline = line
			while(thisline != NULL){
				if(thisline.size > agent->body->size.x){
					find last word in thisline and cut 
					if nextline != exist then create new line
					insert cut word in front on the nextline
					thisline = nextline
				}
			}

		}
	}
	
}

void brains::agent::linecharacterdelete(){

	locate caret line & linecharacter position
	if delete { 
		delete character in back of caret in line 
	} else if backspace {
		delete character in front of caret in line 
	}
	if(multiline){
		if(wordwrap){
			thisline = line
			while(thisline != NULL){
				if(thisline.size < agent->body->size.x){
					if nextline == exist {
						then find last word in next line, cut, move to rear of this line
						on nextline delete word....
					}
					
					thisline = nextline
				}
			}

		}
	}

}

//DOWN
void brains::agent::lineselectionstartset(){
}

//HOLD
void brains::agent::lineselectioncapture(){
}

//UP
void brains::agent::lineselectionstopset(){
}

//SELECTION INSERT (PASTE)
void brains::agent::lineselectioninsert(){
	locate caret line & linecharacter position
	for (eachlinecharacter in lineselectioncopybuffer start from left to right{
		linecharacterinsert(eachlinecharacter)
	}

}

// SELECTION DELETE
void brains::agent::lineselectiondelete(){
	locate caret line & linecharacter position
	for (eachlinecharacter in lineselection start from left to right{
		linecharacterdelete(eachlinecharacter)
	}
}

//SELECTION COPY
void brains::agent::lineselectioncopy(){
	copy lineselection to lineselectioncopybuffer
}

//SELECTION CUT
void brains::agent::lineselectioncut(){
	lineselectioncopy()
	lineselectiondelete()
}

void brains::agent::linecapture(){

}


*/

brains::agent::eventscript::eventscript(void){

	/*!
	* Description:  Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	behavior = NULL;
	transition = NULL;
	scheme = NULL;
	sprite = NULL;
	task = NULL;

}

void brains::agent::eventscript::inherit(brains::agent::eventscript *parent){

	/*!
	* Description: Inheritor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	behavior = parent->behavior;
	transition = parent->transition;
	scheme = parent->scheme;
	sprite = parent->sprite;
	task = parent->task;

}

// HTTPFORM //////////////////////////////////////////////////////////////////////////////////////////
std::map<std::string,brains::httpform *> brains::httpform::namemap;
std::map<std::string,brains::httpform *>::iterator brains::httpform::namemapiterator;
std::list<brains::httpform*> brains::httpform::activelist;
std::list<brains::httpform*>::iterator brains::httpform::activelistiterator;
std::queue<brains::httpform*> brains::httpform::inactivequeue;

brains::httpform::httpform(void){
	/*!
	* Description:  Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	http = NULL;

}

brains::httpform::httpform(std::string name, std::string description){
	/*!
	* Description:  Constructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	this->name = name;
	this->description = description;
	http = NULL;

}

brains::httpform::~httpform(void){
	/*!
	* Description:  Destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

}

brains::httpform *brains::httpform::create(std::string name, std::string description, int method, std::string hostname, int port, std::string page, std::string writepath){
		/*!
	* Description:  
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(namemap[name] == NULL){
        namemap[name] = new httpform(name,description);
	}
	namemap[name]->method = method;
	namemap[name]->hostname = hostname;
	namemap[name]->port = port;
	namemap[name]->page = page;
	namemap[name]->writepath = writepath;

	//bugboard->enable();
	bugboard->print("\nHTTPFORM Create(");
	bugboard->print(namemap[name]->name);
	bugboard->print(" method=");
	bugboard->print(dbStr(namemap[name]->method));
	bugboard->print(" hostname=");
	bugboard->print(namemap[name]->hostname);
	bugboard->print(" port=");
	bugboard->print(dbStr(namemap[name]->port));
	bugboard->print(" page=");
	bugboard->print(namemap[name]->page);
	bugboard->print(" writepath=");
	bugboard->print(namemap[name]->writepath);
	bugboard->print(")");
	//bugboard->disable();

	activelist.push_back(namemap[name]);
	namemap[name]->state = IDLE;

	return (namemap[name]);
}

void brains::httpform::destroy(brains::httpform *httpform){
	/*!
	* Description:  
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	delete httpform;
}

void brains::httpform::update(void){
	/*!
	* Description: 
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	//iterate through active agents
	for(activelistiterator = activelist.begin(); activelistiterator != activelist.end(); activelistiterator++ ){
		(*activelistiterator)->process();
	}

	//Garbage Collection clean up inactive agents
	while (!inactivequeue.empty()){
		activelist.remove(inactivequeue.front());
		destroy(inactivequeue.front());
		inactivequeue.pop();
	}
}

void brains::httpform::process(void){
	/*!
	* Description: 
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/
	
	switch(state){
		case IDLE:
			break;

		case SENDING:
			if(http->state == darknet::PALM::RESPONSESTART){ state = RECEIVING; }
			break;

		case RECEIVING:
			if(http->state == darknet::PALM::RESPONSEEND){ state = IDLE; }
			break;
	}
}

void brains::httpform::submit(void){
	/*!
	* Description: Encode
	*
	* -#Input: 
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\nHTTP Submit PageVars:");
	
	http = darknet::http::fileget(name,method,hostname,port,page,writepath);

	if(http != NULL){

		//build pagevariable list
		for(agentlistiterator = agentlist.begin(); agentlistiterator != agentlist.end(); agentlistiterator++ ){
			for((*agentlistiterator)->valuemapiterator = (*agentlistiterator)->valuemap.begin(); (*agentlistiterator)->valuemapiterator != (*agentlistiterator)->valuemap.end(); (*agentlistiterator)->valuemapiterator++ ){
				http->request.pagevariables.append((*agentlistiterator)->name);
				//http->request.pagevariables.append("_");
				//http->request.pagevariables.append((*agentlistiterator)->valuemapiterator->first);
				http->request.pagevariables.append("=");
				http->request.pagevariables.append(http->urlencode((*agentlistiterator)->valuemapiterator->second));
				http->request.pagevariables.append("&");
			}
		}
		//erase last &
		http->request.pagevariables.erase(http->request.pagevariables.size()-1);

		bugboard->print(http->request.pagevariables);

		state = SENDING;
	}

}

void brains::httpform::submit(std::string name){
	/*!
	* Description: 
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	//bugboard->enable();

	bugboard->print("\nHTTPFORM Submit");

	if(namemap[name]!=NULL){
		namemap[name]->submit();
	}

	//bugboard->disable();

}

// XMLFILE //////////////////////////////////////////////////////////////////////////////////////////
std::map<std::string,int> brains::xmlfile::nodenamemap;
std::map<std::string,int>::iterator brains::xmlfile::nodenamemapiterator;
std::list<brains::xmlfile*> brains::xmlfile::activelist;
std::list<brains::xmlfile*>::iterator brains::xmlfile::activelistiterator;
std::queue<brains::xmlfile*> brains::xmlfile::inactivequeue;
std::map<std::string,int> brains::xmlfile::attributevaluemap;

void brains::xmlfile::nodenameadd(std::string nodename, int constant){
	/*!
	* Description:  adds nodename to interger map, used in xmlfile::process() for switch
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(!nodenamemap[nodename]){nodenamemap[nodename] = constant;}
}

void brains::xmlfile::attributevalueadd(std::string attributevalue, int constant){
	/*!
	* Description:  adds nodename to interger map, used in xmlfile::process() for switch
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(!attributevaluemap[attributevalue]){attributevaluemap[attributevalue] = constant;}
}

brains::xmlfile::xmlfile(std::string filename){

	/*!
	* Description: Constructor; MAUI Files transferred from the server are stored to the local drive as temp files before load.
	*
	* -#Input: 
	*	-# string filename - local filename
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\nLoading ");
	bugboard->print(filename);

	if(dbFileExist((char*)filename.data())){

		xml = createIrrXMLReader((char*)filename.data());
		// parse the file until end reached
		//updatable processing

		nodecount = 0;

		bugboard->print("\nMAUI XML Activated");
		sync.set(60.0f,1.0);
		state = LOAD;
		activelist.push_back(this);

	} else {

		bugboard->print("\nMAUI XML Activated, but file not found!");
		inactivequeue.push(this);
		filename.append(" could not be opened!");
		alertbox("MAUI::xmlfile",filename,ALERTBOX_SEVERITY_ERROR);

	}

}

brains::xmlfile::~xmlfile(void){

	/*!
	* Description: destructor
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	if(xml){
		activelist.remove(this);
		delete xml;	//delete the xml parser after usage
		bugboard->print("\nDeactivated");
	}

	bugboard->print("\n~Loading");
}

void brains::xmlfile::update(void){
	/*!
	* Description: Iterate through all active xmlfile load and process
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	for(activelistiterator = activelist.begin(); activelistiterator != activelist.end(); activelistiterator++ ){
		//if((*activelistiterator)->sync.tick()){ //update sync
			(*activelistiterator)->process();
		//}
	}

	//clean up inactive xmlfiles
	while (!inactivequeue.empty()){	
		bugboard->print("\nXML Garbage");
		delete inactivequeue.front();
		inactivequeue.pop();
	}

}

void brains::xmlfile::process(void){
	/*!
	* Description: Process by State
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# none
	*/

	bugboard->print("\nXML Process");

	int parsereturn;

	switch(state){

		case IDLE:
			break;

		case LOAD:
			output.append("MAUI XML Load");
			state = LOADING;
			break;

		case LOADING:
			parsereturn = parse();
			
			bugboard->print(" return = ");
			bugboard->print(dbStr(parsereturn));

			switch(parsereturn){
				//case 1 more to parse
				case 0:
					state = COMPLETE;
					break;

				case BRAIN_ERROR:
					state = COMPLETE; //ERROR
					break;
			}
			break;

		case COMPLETE:

			//xmlpage load complete, draw default agents to canvas

			while (!loadedagentqueue.empty()){

				bugboard->print("\nCOMPLETE loadedagent ");
				bugboard->print(loadedagentqueue.front()->name);

				switch(loadedagentqueue.front()->type){

					case BRAIN_AGENT_TYPE_0D:
						break;

					default:	
						if(loadedagentqueue.front()->body->physicsflag){
							//update 2D physics for orientation accuracy
							loadedagentqueue.front()->body->physics->update(loadedagentqueue.front()->body->position, loadedagentqueue.front()->body->angle);
						}
						break;
				}

				loadedagentqueue.front()->state = agent::ACTIVE;
				loadedagentqueue.pop();
				
			}

			//set text to default
			if(style::namemap[""]!=NULL){
				style::namemap[""]->eventaction[BRAIN_EVENT_STATE_IDLE]->ttfontset();
			}

			inactivequeue.push(this);

			output.append("ng Complete!");

			break;
				
	}

	bugboard->print("\n~XML Process");

}

int brains::xmlfile::parse(void){
	/*!
	* Description: Parses each MAUI XML Node; Returns 0 when no more nodes are read;
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# 0 if no more nodes
	*/

	bugboard->print("\nxmlfile::parse");

	if(!xml->read()){return(0);} //get next node else return false

	std::map<std::string, std::string> attribute;
	std::vector< std::pair<int,std::string> > parentnode;
	std::string nodename;

	nodecount++;

	//testing	
	switch(xml->getNodeType()){
		case EXN_NONE:
			bugboard->print("\nEXN_NONE ");
			break;
		case EXN_ELEMENT:
			bugboard->print("\nEXN_ELEMENT ");
			break;
		case EXN_ELEMENT_END:
			bugboard->print("\nEXN_ELEMENT_END ");
			break;
		case EXN_TEXT:
			bugboard->print("\nEXN_TEXT ");
			break;
		case EXN_COMMENT:
			bugboard->print("\nEXN_COMMENT ");
			break;
		case EXN_CDATA:
			bugboard->print("\nEXN_CDATA ");
			break;
		case EXN_UNKNOWN:
			bugboard->print("\nEXN_UNKNOWN ");
			break;
	}
	bugboard->print((char*)xml->getNodeData()); //getnodedata and getnodename are synomous

	switch(xml->getNodeType()){
	
		case EXN_NONE: 	//0 - No xml node. This is usually the node if you did not read anything yet.
			break;//EXN_NONE

		case EXN_ELEMENT: 	//1 - A xml element, like <foo>.

			nodename = (char*)xml->getNodeData();

			bugboard->print(" [");
			bugboard->print(dbStr(nodenamemap[nodename]));
			bugboard->print("]");
			
			//specialty attributes
			if(xml->getAttributeValue("width")){
				bugboard->print("\nWIDTH=");
				bugboard->print(xml->getAttributeValueSafe("width"));
				if(strcmp(xml->getAttributeValueSafe("width"),"screen")==0){
					attribute["width"] = dbStr(dbScreenWidth());
				} else {
					attribute["width"] = dbStr(xml->getAttributeValueAsFloat("width"));
				}
				bugboard->print("-->");
				bugboard->print(attribute["width"]);
			}

			if(xml->getAttributeValue("height")){
				bugboard->print("\nHEIGHT=");
				bugboard->print(xml->getAttributeValueSafe("height"));
				if(strcmp(xml->getAttributeValueSafe("height"),"screen")==0){
					attribute["height"] = dbStr(dbScreenHeight());
				} else {
					attribute["height"] = dbStr(xml->getAttributeValueAsFloat("height"));
				}
				bugboard->print("-->");
				bugboard->print(attribute["height"]);
			}

			if(xml->getAttributeValue("depth")){
				if(strcmp(xml->getAttributeValueSafe("depth"),"screen")==0){
					attribute["depth"] = dbStr(dbScreenDepth());
				} else {
					attribute["depth"] = dbStr(xml->getAttributeValueAsFloat("depth"));
				}
			}
	
			switch(nodenamemap[nodename]){

				case BRAIN_XML_NODENAME_MAUI:
					attribute["value"] = "2.0(DGDK)";
					break;

				case BRAIN_XML_NODENAME_STATE:

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_MAUI:
							attribute["value"] = (char*)xml->getAttributeValueSafe("name");
							esm::statenameadd(attribute["value"]);
							break;

						case BRAIN_XML_NODENAME_AGENT:
							//set default starting state
							agent::namemap[parentnode[0].second]->eventstate.state = esm::statenamemap[xml->getAttributeValueSafe("name")];
							break;
					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_BEHAVIOR:
					output.append("i");
					attribute["value"] = (char*)xml->getAttributeValueSafe("name");
					behavior::create(attribute["value"], xml->getAttributeValueSafe("description"));

					if(xml->getAttributeValue("default")){
						if(attributevaluemap[xml->getAttributeValueSafe("default")] == 1){ defaultbehavior = behavior::namemap[attribute["value"]];}
						bugboard->print(" default");
					}
					break;

				case BRAIN_XML_NODENAME_TRANSITION:
					output.append("i");
					attribute["value"] = (char*)xml->getAttributeValueSafe("name");
					transition::create(attribute["value"], xml->getAttributeValueSafe("description"));
					
					if(xml->getAttributeValue("default")){
						if(attributevaluemap[xml->getAttributeValueSafe("default")] == 1){ defaulttransition = transition::namemap[attribute["value"]];}
						bugboard->print(" default");
					}
					break;

				case BRAIN_XML_NODENAME_STYLE:
					output.append("i");
					attribute["value"] = (char*)xml->getAttributeValueSafe("name");
					style::create(attribute["value"], xml->getAttributeValueSafe("description"));

					if(xml->getAttributeValue("default")){
						if(attributevaluemap[xml->getAttributeValueSafe("default")] == 1){ defaultstyle = style::namemap[attribute["value"]];}
						bugboard->print(" default");
					}
					break;

				case BRAIN_XML_NODENAME_THEME:
					output.append("i");
					attribute["value"] = (char*)xml->getAttributeValueSafe("name");
					theme::create(attribute["value"], xml->getAttributeValueSafe("description"));

					if(xml->getAttributeValue("default")){
						if(attributevaluemap[xml->getAttributeValueSafe("default")] == 1){ defaulttheme = theme::namemap[attribute["value"]];}
						bugboard->print(" default");
					}
					break;

				case BRAIN_XML_NODENAME_SCHEME:
					output.append("i");
					attribute["value"] = (char*)xml->getAttributeValueSafe("name");
					scheme::create(attribute["value"], xml->getAttributeValueSafe("description"));

					if(xml->getAttributeValue("default")){
						if(attributevaluemap[xml->getAttributeValueSafe("default")] == 1){ defaultscheme = scheme::namemap[attribute["value"]];}
						bugboard->print(" default");
					}
					break;

				case BRAIN_XML_NODENAME_CANVAS:
					output.append("i");
					bugboard->print(" create canvas(\"");
					bugboard->print((char*)xml->getAttributeValueSafe("name"));
					bugboard->print("\")");

					attribute["value"] = (char*)xml->getAttributeValueSafe("name");

					canvas::create(
						xml->getAttributeValueSafe("parent"), 
						attribute["value"],
						xml->getAttributeValueSafe("description"),
						xml->getAttributeValueAsInt("camera"), 
						xml->getAttributeValueAsFloat("fov"),
						xml->getAttributeValueAsFloat("nearrange"),
						xml->getAttributeValueAsFloat("farrange"),
						dbVal((char*)attribute["width"].data())/dbVal((char*)attribute["height"].data()),
						(bool)attributevaluemap[xml->getAttributeValueSafe("backdrop")], 
						dbRGB(xml->getAttributeValueAsInt("backdropcolorred"),xml->getAttributeValueAsInt("backdropcolorgreen"),xml->getAttributeValueAsInt("backdropcolorblue")), 
						0
					);

					if(xml->getAttributeValue("base")){
						if(attributevaluemap[xml->getAttributeValueSafe("base")] == 1){ basecanvas = canvas::namemap[attribute["value"]];}
						bugboard->print(" base");
					}

					canvas::namemap[attribute["value"]]->zoomfactor.x = xml->getAttributeValueAsFloat("zoomfactorx");
					canvas::namemap[attribute["value"]]->zoomfactor.y = xml->getAttributeValueAsFloat("zoomfactory");
					canvas::namemap[attribute["value"]]->zoomfactor.z = xml->getAttributeValueAsFloat("zoomfactorz");
					break;
				
				case BRAIN_XML_NODENAME_AGENT:
					output.append("i");

					bugboard->print(" create agent(\"");
					bugboard->print((char*)xml->getAttributeValueSafe("name"));
					bugboard->print("\")");

					attribute["value"] = (char*)xml->getAttributeValueSafe("name");

					agent::create(
						xml->getAttributeValueSafe("parent"), 
						attribute["value"],
						xml->getAttributeValueSafe("description"), 
						(bool)xml->getAttributeValueAsInt("visible"), 
						(bool)xml->getAttributeValueAsInt("collision")
					);

					//base
					if(xml->getAttributeValue("base")){
						if(attributevaluemap[xml->getAttributeValueSafe("base")] == 1){ baseagent = agent::namemap[attribute["value"]];}
						bugboard->print(" base");
					}

					//httpform
					parentnode.push_back(parsestack.top());
					parsestack.pop();

					switch(parentnode[0].first){
						case BRAIN_XML_NODENAME_AGENT:
							//make child agent
							break;

						case BRAIN_XML_NODENAME_FORM:
							//add to httpform agentlist
							if(httpform::namemap[parentnode[0].second] != NULL){
								httpform::namemap[parentnode[0].second]->agentlist.push_back(agent::namemap[attribute["value"]]);
								bugboard->print("\nHTTPFORM Agent Add:");
								bugboard->print(parentnode[0].second);

							}
							break;
					}
					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));

					//form reference
					if(xml->getAttributeValue("form")){
						if(httpform::namemap[xml->getAttributeValueSafe("form")] != NULL){
							httpform::namemap[xml->getAttributeValueSafe("form")]->agentlist.push_back(agent::namemap[attribute["value"]]);					
							bugboard->print("\nHTTPFORM Agent Add:");
							bugboard->print(xml->getAttributeValueSafe("form"));
						}
					}
						
					//form value
					if(xml->getAttributeValue("value")){
						agent::namemap[attribute["value"]]->valuemap["value"] = xml->getAttributeValueSafe("value");
					}

					//pointer
					if(xml->getAttributeValue("pointer")){
						if(attributevaluemap[xml->getAttributeValueSafe("pointer")] == 1){pointer = agent::namemap[attribute["value"]];}
						bugboard->print(" pointer");
					}

					//caret
					if(xml->getAttributeValue("caret")){
						if(attributevaluemap[xml->getAttributeValueSafe("caret")] == 1){caret = agent::namemap[attribute["value"]];}
						bugboard->print(" caret");
					}

					//device setup
					if(xml->getAttributeValue("device")){
						agent::namemap[attribute["value"]]->device = device::namemap[xml->getAttributeValueSafe("device")];
						bugboard->print(" device =");
						bugboard->print(xml->getAttributeValueSafe("device"));
					}

					//auto type set
					if(xml->getAttributeValue("type")){
						agent::namemap[attribute["value"]]->type = attributevaluemap[xml->getAttributeValueSafe("type")];
					} else {
						//inherit from parent
						if(xml->getAttributeValue("parent")){
							agent::namemap[attribute["value"]]->type = agent::namemap[xml->getAttributeValueSafe("parent")]->type;
						} else {
							//default
							agent::namemap[attribute["value"]]->type = BRAIN_AGENT_TYPE_2D;
						}
					}
					
					bugboard->print(" type=");
					bugboard->print(dbStr(agent::namemap[attribute["value"]]->type));

					//create default eventaction
					agent::namemap[attribute["value"]]->eventaction[BRAIN_EVENT_STATE_IDLE] = new agent::eventscript;

					//create sprite
					switch(agent::namemap[attribute["value"]]->type){

						case BRAIN_AGENT_TYPE_2D:
							agent::namemap[attribute["value"]]->spriteID = dbSpriteResource->pop();
							break;

						case BRAIN_AGENT_TYPE_3D:
							agent::namemap[attribute["value"]]->spriteID = 0;
							break;
							
					}
					
					agent::namemap[attribute["value"]]->state = agent::LOADING;
					loadedagentqueue.push(agent::namemap[attribute["value"]]);

					// if(xml->getAttributeValueSafe("form") == "formagentname1,formagentname2,..."){//}
					break;

				case BRAIN_XML_NODENAME_META:
					break;

				case BRAIN_XML_NODENAME_EVENT:

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					attribute["value"] = (char*)xml->getAttributeValueSafe("state");

					bugboard->print("\nElement:");
					bugboard->print(dbStr(parentnode[0].first));

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_BEHAVIOR:
							//create eventaction
							if(behavior::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] == NULL){
								behavior::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] = new behavior::eventscript;
								//parent
								if(xml->getAttributeValue("parent")){
									behavior::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->inherit(behavior::namemap[xml->getAttributeValueSafe("parent")]->eventaction[esm::statenamemap[attribute["value"]]]);
								}
							}
							break;

						case BRAIN_XML_NODENAME_TRANSITION:
							//create eventaction
							if(transition::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] == NULL){
								transition::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] = new transition::eventscript;
								//parent
								if(xml->getAttributeValue("parent")){
									transition::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->inherit(transition::namemap[xml->getAttributeValueSafe("parent")]->eventaction[esm::statenamemap[attribute["value"]]]);
								}
							}
							break;

						case BRAIN_XML_NODENAME_STYLE:
							//create eventaction							
							bugboard->print("\nstyle(\"");
							bugboard->print(style::namemap[parentnode[0].second]->name);
							bugboard->print("\")[");
							bugboard->print(attribute["value"]);
							bugboard->print(",");
							bugboard->print(dbStr(esm::statenamemap[attribute["value"]]));
							bugboard->print("]");

							if(style::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] == NULL){
								style::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] = new style::eventscript;
								//parent
								if(xml->getAttributeValue("parent")){
									style::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->inherit(style::namemap[xml->getAttributeValueSafe("parent")]->eventaction[esm::statenamemap[attribute["value"]]]);
								}
							}
							break;

						case BRAIN_XML_NODENAME_THEME:
							//create eventaction
							if(theme::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] == NULL){
								theme::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] = new theme::eventscript;
								//parent
								if(xml->getAttributeValue("parent")){
									theme::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->inherit(theme::namemap[xml->getAttributeValueSafe("parent")]->eventaction[esm::statenamemap[attribute["value"]]]);
								}
							}
							break;

						case BRAIN_XML_NODENAME_SCHEME:

							//create eventaction
							if(scheme::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] == NULL){
								scheme::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] = new scheme::eventscript;
								//parent
								if(xml->getAttributeValue("parent")){
									scheme::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->inherit(scheme::namemap[xml->getAttributeValueSafe("parent")]->eventaction[esm::statenamemap[attribute["value"]]]);
								}
							}

							//<audio> code

							break;

						case BRAIN_XML_NODENAME_AGENT:
							//create eventaction
							bugboard->print("\nagentaction(\"");
							bugboard->print(agent::namemap[parentnode[0].second]->name);
							bugboard->print("\")[");
							bugboard->print(attribute["value"]);
							bugboard->print(",");
							bugboard->print(dbStr(esm::statenamemap[attribute["value"]]));
							bugboard->print("]");
							
							//create eventaction
							if(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] == NULL){
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]] = new agent::eventscript;
								//parent
								if(xml->getAttributeValue("parent")){
									agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->inherit(agent::namemap[xml->getAttributeValueSafe("parent")]->eventaction[esm::statenamemap[attribute["value"]]]);
								}
							}

							//behavior
							if(xml->getAttributeValue("behavior")){
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->behavior = behavior::namemap[xml->getAttributeValueSafe("behavior")];
							} else if(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->behavior != NULL) {
								//assign IDLE behavior
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->behavior = agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->behavior;
							} else {
								//assign default
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->behavior = behavior::namemap[""];
							}

							//transition
							if(xml->getAttributeValue("transition")){
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->transition = transition::namemap[xml->getAttributeValueSafe("transition")];
							} else if(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->transition != NULL) {
								//assign IDLE transition
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->transition = agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->transition;
							} else {
								//assign default
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->transition = transition::namemap[""];
							}
							
							//scheme
							if(xml->getAttributeValue("scheme")){
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->scheme = scheme::namemap[xml->getAttributeValueSafe("scheme")];
							} else if(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->scheme != NULL) {
								//assign IDLE scheme
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->scheme = agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->scheme;
							} else {
								//assign default
								agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->scheme = scheme::namemap[""];
							}

							switch(agent::namemap[parentnode[0].second]->type){
			
								case BRAIN_AGENT_TYPE_0D:
									bugboard->print("\nWidget Created");
									break;

								case BRAIN_AGENT_TYPE_1D:
									bugboard->print("\nDoodad Created");
									break;

								case BRAIN_AGENT_TYPE_2D:

									//create sprite
									if(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite == NULL){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite = new sprite;
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->inherit(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite);
										bugboard->print("\nCreated Agent Sprite");
									}

									//background
									if(xml->getAttributeValue("src")){
										if(dbFileExist((char*)xml->getAttributeValue("src"))){
											agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID = dbImageResource->add(xml->getAttributeValue("src"));
											bugboard->print("BgImage Loaded ");
											if(!dbImageExist(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID)){
												dbLoadImage((char*)xml->getAttributeValue("src"),agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID);
												bugboard->print("YES ");
											}

											agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimagealign.x = xml->getAttributeValueAsFloat("x");
											agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimagealign.y = xml->getAttributeValueAsFloat("y");

											bugboard->print((char*)xml->getAttributeValue("src"));
											bugboard->print("[");
											bugboard->print(dbStr(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID));
											bugboard->print("]");
										}
									}

									//theme
									if(xml->getAttributeValue("theme")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgtheme = theme::namemap[xml->getAttributeValueSafe("theme")];
									} else if(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->bgtheme != NULL) {
										//assign IDLE theme
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgtheme = agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->bgtheme;
									} else {
										//assign default
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgtheme = theme::namemap[""];
									}
	
									//style
									if(xml->getAttributeValue("style")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionstyle = style::namemap[xml->getAttributeValueSafe("style")];
									} else if(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->captionstyle != NULL) {
										//assign IDLE style
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionstyle = agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->captionstyle;
									} else {
										//assign default
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionstyle = style::namemap[""];
									}

									//caption
									if(xml->getAttributeValue("caption")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->caption = xml->getAttributeValueSafe("caption");
									}
									
									if(xml->getAttributeValueAsInt("captiontype")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captiontype = xml->getAttributeValueAsInt("captiontype");
									}
									
									if(xml->getAttributeValue("halign")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionposition.x = xml->getAttributeValueAsFloat("halign");
									}

									if(xml->getAttributeValue("valign")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionposition.y = xml->getAttributeValueAsFloat("valign");
									}
																		
									bugboard->print("\ncaption ");
									bugboard->print(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->caption);

									//capture image
									agent::namemap[parentnode[0].second]->imagecapture(esm::statenamemap[attribute["value"]]);

									break;

								case BRAIN_AGENT_TYPE_3D:

									//create sprite
									if(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite == NULL){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite = new sprite;
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->inherit(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite);
										bugboard->print("\nCreated Agent Sprite");
									}

									//texture (bgimage)
									if(xml->getAttributeValue("src")){
										if(dbFileExist((char*)xml->getAttributeValue("src"))){
											agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID = dbImageResource->add(xml->getAttributeValue("src"));
											bugboard->print("BgImage Loaded ");
											if(!dbImageExist(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID)){
												dbLoadImage((char*)xml->getAttributeValue("src"),agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID);
												bugboard->print("YES ");
											}

											agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimagealign.x = xml->getAttributeValueAsFloat("x");
											agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimagealign.y = xml->getAttributeValueAsFloat("y");

											bugboard->print((char*)xml->getAttributeValue("src"));
											bugboard->print("[");
											bugboard->print(dbStr(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgimageID));
											bugboard->print("]");
										}
									}

									//object
									if(xml->getAttributeValue("object") && dbFileExist((char*)xml->getAttributeValue("object"))){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->dbObjectID = dbObjectResource->add(xml->getAttributeValue("object"));
										bugboard->print(" Object Loaded ");
										if(!dbObjectExist(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->dbObjectID)){
											dbLoadObject((char*)xml->getAttributeValue("object"),agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->dbObjectID);
											bugboard->print("YES ");
											bugboard->print((char*)xml->getAttributeValue("object"));
										}
									} else {
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->dbObjectID = dbObjectResource->pop();
										bugboard->print(" Object Created ");
										if(!dbObjectExist(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->dbObjectID)){
											dbMakeObjectPlain(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->dbObjectID,agent::namemap[parentnode[0].second]->body->size.x,agent::namemap[parentnode[0].second]->body->size.y);
											bugboard->print("YES ");
										}
									}

									bugboard->print("[");
									bugboard->print(dbStr(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->dbObjectID));
									bugboard->print("]");

									//theme
									if(xml->getAttributeValue("theme")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgtheme = theme::namemap[xml->getAttributeValueSafe("theme")];
									} else if(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->bgtheme != NULL) {
										//assign IDLE theme
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgtheme = agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->bgtheme;
									} else {
										//assign default
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->bgtheme = theme::namemap[""];
									}

									//style
									if(xml->getAttributeValue("style")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionstyle = style::namemap[xml->getAttributeValueSafe("style")];
									} else if(agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->captionstyle != NULL) {
										//assign IDLE style
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionstyle = agent::namemap[parentnode[0].second]->eventaction[BRAIN_EVENT_STATE_IDLE]->sprite->captionstyle;
									} else {
										//assign default
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionstyle = style::namemap[""];
									}

									//caption
									if(xml->getAttributeValue("caption")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->caption = xml->getAttributeValueSafe("caption");
									}
									
									if(xml->getAttributeValueAsInt("captiontype")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captiontype = xml->getAttributeValueAsInt("captiontype");
									}
									
									if(xml->getAttributeValue("halign")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionposition.x = xml->getAttributeValueAsFloat("halign");
									}

									if(xml->getAttributeValue("valign")){
										agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->captionposition.y = xml->getAttributeValueAsFloat("valign");
									}
																		
									bugboard->print("\ncaption ");
									bugboard->print(agent::namemap[parentnode[0].second]->eventaction[esm::statenamemap[attribute["value"]]]->sprite->caption);

									//capture texture
									agent::namemap[parentnode[0].second]->texturecapture(esm::statenamemap[attribute["value"]]);
									break;

							}
							break;

						default:
							return(syntaxerror("Expected Previous <agent>,<behavior>,<transition>,<style>,<theme>,<scheme>"));
					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_SCRIPT:

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					attribute["value"] = parentnode[0].second;

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_MAUI:
						case BRAIN_XML_NODENAME_META:
						case BRAIN_XML_NODENAME_EVENT:
							break;

						default:
							return(syntaxerror("Expected Previous <brains>,<meta>,<event>"));

					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_DEVICE:
					
					parentnode.push_back(parsestack.top());
					parsestack.pop();

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_MAUI:
							//define input device periphial and input

							bugboard->print(" create device(\"");
							bugboard->print((char*)xml->getAttributeValueSafe("name"));
							bugboard->print("\")");

							attribute["value"] = (char*)xml->getAttributeValueSafe("name");

							device::create(
								xml->getAttributeValueSafe("parent"), 
								attribute["value"], 
								xml->getAttributeValueSafe("description"), 
								attributevaluemap[(char*)xml->getAttributeValueSafe("type")]
							);
							break;

						case BRAIN_XML_NODENAME_CANVAS:
							break;

						case BRAIN_XML_NODENAME_AGENT:
							//create a device, if not null error
							break;

						default:
							return(syntaxerror("Expected Previous <brains><canvas><agent>"));

					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_VARIABLE:

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_AGENT:

							//sets agent variable/value pair
							brains::agent::variableset(agent::namemap[parentnode[0].second],(char*)xml->getAttributeValueSafe("name"),(char*)xml->getAttributeValueSafe("value"));
							break;

					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_ORIENTATE:
					//reference;x;y;z;width;height;depth;xalign;yalign;zalign;left;right;bottom;front;back

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_AGENT:

							//create a body, if not null error
							if(agent::namemap[parentnode[0].second]->body != NULL){return(syntaxerror("Physics Body already defined."));} //to be replaced with redef
							bugboard->print("\nnew agent body");

							agent::namemap[parentnode[0].second]->body = new body(
								xml->getAttributeValueAsFloat("x"),
								xml->getAttributeValueAsFloat("y"),
								xml->getAttributeValueAsFloat("z"),
								dbVal((char*)attribute["width"].data()),
								dbVal((char*)attribute["height"].data()),
								dbVal((char*)attribute["depth"].data()),
								xml->getAttributeValueAsFloat("anglex"),
								xml->getAttributeValueAsFloat("angley"),
								xml->getAttributeValueAsFloat("anglez")
							);
							
							//recalc body pos and size 

							//auto shape, calculate center and zoom	
							agent::namemap[parentnode[0].second]->body->center((char*)xml->getAttributeValueSafe("canvas"));
							agent::namemap[parentnode[0].second]->body->zoom((char*)xml->getAttributeValueSafe("canvas"));
							
							bugboard->print("\npre_orientate ");
							bugboard->print(parentnode[0].second);

							//auto alignment
							agent::namemap[parentnode[0].second]->body->orientate(
								(char*)xml->getAttributeValueSafe("ref"),
								xml->getAttributeValueAsFloat("x"),
								xml->getAttributeValueAsFloat("y"),
								xml->getAttributeValueAsFloat("z"),
								attributevaluemap[(char*)xml->getAttributeValueSafe("xalign")],
								attributevaluemap[(char*)xml->getAttributeValueSafe("yalign")],
								attributevaluemap[(char*)xml->getAttributeValueSafe("zalign")]
							);

							bugboard->print("\npost_orientate ");
							bugboard->print(parentnode[0].second);//, 
							bugboard->print("(");
							bugboard->print(dbStr(agent::namemap[parentnode[0].second]->body->position.x)); 
							bugboard->print(",");
							bugboard->print(dbStr(agent::namemap[parentnode[0].second]->body->position.y));
							bugboard->print(",");								
							bugboard->print(dbStr(agent::namemap[parentnode[0].second]->body->size.x));
							bugboard->print(",");								
							bugboard->print(dbStr(agent::namemap[parentnode[0].second]->body->size.y));
							bugboard->print(")");

							break;

						case BRAIN_XML_NODENAME_CANVAS:
							//create a body, if not null error
							if(canvas::namemap[parentnode[0].second]->body != NULL){ return(syntaxerror("Physics Body already defined."));} //to be replaced with redef
							bugboard->print("\nnew canvas body `");
							bugboard->print(parentnode[0].second);
							bugboard->print("`");
													
							canvas::namemap[parentnode[0].second]->body = new body(
								xml->getAttributeValueAsFloat("x"),
								xml->getAttributeValueAsFloat("y"),
								xml->getAttributeValueAsFloat("z"),
								dbVal((char*)attribute["width"].data()),
								dbVal((char*)attribute["height"].data()),
								dbVal((char*)attribute["depth"].data()),
								xml->getAttributeValueAsFloat("anglex"),
								xml->getAttributeValueAsFloat("angley"),
								xml->getAttributeValueAsFloat("anglez")
							);
							
							//test
							bugboard->print("\ncanvas bounds(");
							bugboard->print(dbStr(canvas::namemap[parentnode[0].second]->body->position.x));//, 
							bugboard->print(",");
							bugboard->print(dbStr(canvas::namemap[parentnode[0].second]->body->position.y));//, 
							bugboard->print(",");
							bugboard->print(dbStr(canvas::namemap[parentnode[0].second]->body->size.x));//, 
							bugboard->print(",");
							bugboard->print(dbStr(canvas::namemap[parentnode[0].second]->body->size.y));
							bugboard->print(")");
							break;

					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_PHYSICS:

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					attribute["value"] = parentnode[0].second;

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_ORIENTATE:

							parentnode.push_back(parsestack.top());
							parsestack.pop();
							
							switch(parentnode[1].first){

								case BRAIN_XML_NODENAME_AGENT:

									if(agent::namemap[parentnode[1].second]->body != NULL){

										//create physics collision
										switch(agent::namemap[parentnode[1].second]->type){

											case BRAIN_AGENT_TYPE_2D:
												
												//select physics type
												switch(attributevaluemap[(char*)xml->getAttributeValueSafe("type")]){

													case BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_WORLD:
														bugboard->print("\nmake 2D world physics ");
														agent::namemap[parentnode[1].second]->body->physics = new brains::body::b2world;
														agent::namemap[parentnode[1].second]->body->physics->create(
															agent::namemap[parentnode[1].second]->body->position,
															agent::namemap[parentnode[1].second]->body->size,
															xml->getAttributeValueAsFloat("gravityx"),
															xml->getAttributeValueAsFloat("gravityy"),
															(float32)(1.0/xml->getAttributeValueAsFloat("timestep")),
															xml->getAttributeValueAsInt("iteration"),
															(bool)attributevaluemap[xml->getAttributeValueSafe("allowsleep")]
														);
														//set user data
														agent::namemap[parentnode[1].second]->body->physics->userdataset(agent::namemap[parentnode[1].second]);
														break;

													case BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_MOUSE:
														bugboard->print("\nmake 2D mouse joint physics ");
														agent::namemap[parentnode[1].second]->body->physics = new brains::body::b2mouse;
														agent::namemap[parentnode[1].second]->body->physics->create(
															(char*)xml->getAttributeValueSafe("canvas")
														);
														break;

													case BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_BODY:
													default:
														bugboard->print("\nmake 2D body physics ");
														agent::namemap[parentnode[1].second]->body->physics = new brains::body::b2body;
														agent::namemap[parentnode[1].second]->body->physics->create(
															(char*)xml->getAttributeValueSafe("canvas"),
															0,
															agent::namemap[parentnode[1].second]->body->position,
															agent::namemap[parentnode[1].second]->body->size,
															agent::namemap[parentnode[1].second]->body->angle,
															xml->getAttributeValueAsFloat("friction"),
															xml->getAttributeValueAsFloat("density"),
															xml->getAttributeValueAsFloat("restitution"),
															(bool)attributevaluemap[xml->getAttributeValueSafe("noresponse")]
														);
												
												}
												//if (attributevaluemap[xml->getAttributeValue("collisiononly")] == 1) { isSensor == false }

												agent::namemap[parentnode[1].second]->body->physicsflag = true;

												//offset sprite
												agent::namemap[parentnode[1].second]->spriteoffset();

												bugboard->print("\npost physics ");
												bugboard->print(parentnode[1].second);//, 
												bugboard->print("(");
												bugboard->print(dbStr(agent::namemap[parentnode[1].second]->body->position.x));
												bugboard->print(",");
												bugboard->print(dbStr(agent::namemap[parentnode[1].second]->body->position.y));
												bugboard->print(",");								
												bugboard->print(dbStr(agent::namemap[parentnode[1].second]->body->size.x));
												bugboard->print(",");								
												bugboard->print(dbStr(agent::namemap[parentnode[1].second]->body->size.y));
												bugboard->print(")");

												break;

											case BRAIN_AGENT_TYPE_3D:
												//create 3D Physics
												break;

										}

									}
									break;

								case BRAIN_XML_NODENAME_CANVAS:

									if(canvas::namemap[parentnode[1].second]->body != NULL){

										//create physics collision
										switch(canvas::namemap[parentnode[1].second]->type){

											case BRAIN_AGENT_TYPE_2D:
												bugboard->print("\nmake 2D world physics ");
												canvas::namemap[parentnode[1].second]->body->physics = new brains::body::b2world;
												canvas::namemap[parentnode[1].second]->body->physics->create(
													canvas::namemap[parentnode[1].second]->body->position, 
													canvas::namemap[parentnode[1].second]->body->size, 
													xml->getAttributeValueAsFloat("gravityx"), 
													xml->getAttributeValueAsFloat("gravityy"),
													(float32)(1.0/xml->getAttributeValueAsFloat("timestep")), 
													xml->getAttributeValueAsInt("iterations"),
													(bool)attributevaluemap[xml->getAttributeValueSafe("allowsleep")]
												);

												canvas::namemap[parentnode[1].second]->body->physicsflag = true;
												break;

										}
									}
									break;

							}

							parsestack.push(make_pair(parentnode[1].first,parentnode[1].second));
							break;

						default:
							return(syntaxerror("Expected Previous <agent> or <canvas>"));

					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_BORDER:

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					attribute["value"] = parentnode[0].second;

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_EVENT:

							parentnode.push_back(parsestack.top());
							parsestack.pop();

							switch(parentnode[1].first){

								case BRAIN_XML_NODENAME_THEME:

									if(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]!=NULL){

										bugboard->print("\nCreate border ");

										if(xml->getAttributeValue("topleftsrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.left.dbImageID = dbImageResource->add(xml->getAttributeValue("topleftsrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.left.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("topleftsrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.left.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("topleftsrc Loaded ");

										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.left.size = xml->getAttributeValueAsInt("topleftsize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.left.color = dbRGB(xml->getAttributeValueAsInt("topleftred"),xml->getAttributeValueAsInt("topleftgreen"),xml->getAttributeValueAsInt("topleftblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.left.alpha = xml->getAttributeValueAsInt("topleftalpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.left.linestyle = xml->getAttributeValueAsInt("topleftlinestyle");

										if(xml->getAttributeValue("topcentersrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.center.dbImageID = dbImageResource->add(xml->getAttributeValue("topcentersrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.center.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("topcentersrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.center.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("topcentersrc Loaded ");
										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.center.size = xml->getAttributeValueAsInt("topcentersize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.center.color = dbRGB(xml->getAttributeValueAsInt("topcenterred"),xml->getAttributeValueAsInt("topcentergreen"),xml->getAttributeValueAsInt("topcenterblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.center.alpha = xml->getAttributeValueAsInt("topcenteralpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.center.linestyle = xml->getAttributeValueAsInt("topcenterlinestyle");

										if(xml->getAttributeValue("toprightsrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.right.dbImageID = dbImageResource->add(xml->getAttributeValue("toprightsrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.right.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("toprightsrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.right.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("toprightsrc Loaded ");
										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.right.size = xml->getAttributeValueAsInt("toprightsize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.right.color = dbRGB(xml->getAttributeValueAsInt("toprightred"),xml->getAttributeValueAsInt("toprightgreen"),xml->getAttributeValueAsInt("toprightblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.right.alpha = xml->getAttributeValueAsInt("toprightalpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.top.right.linestyle = xml->getAttributeValueAsInt("toprightlinestyle");

										if(xml->getAttributeValue("middleleftsrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.left.dbImageID = dbImageResource->add(xml->getAttributeValue("middleleftsrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.left.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("middleleftsrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.left.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("middleleftsrc Loaded ");
										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.left.size = xml->getAttributeValueAsInt("middleleftsize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.left.color = dbRGB(xml->getAttributeValueAsInt("middleleftred"),xml->getAttributeValueAsInt("middleleftgreen"),xml->getAttributeValueAsInt("middleleftblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.left.alpha = xml->getAttributeValueAsInt("middleleftalpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.left.linestyle = xml->getAttributeValueAsInt("middleleftlinestyle");

										if(xml->getAttributeValue("middlecentersrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.center.dbImageID = dbImageResource->add(xml->getAttributeValue("middlecentersrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.center.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("middlecentersrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.center.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("middlecentersrc Loaded ");
										}

										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.center.size = xml->getAttributeValueAsInt("middlecentersize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.center.color = dbRGB(xml->getAttributeValueAsInt("middlecenterred"),xml->getAttributeValueAsInt("middlecentergreen"),xml->getAttributeValueAsInt("middlecenterblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.center.alpha = xml->getAttributeValueAsInt("middlecenteralpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.center.linestyle = xml->getAttributeValueAsInt("middlecenterlinestyle");

										if(xml->getAttributeValue("middlerightsrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.right.dbImageID = dbImageResource->add(xml->getAttributeValue("middlerightsrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.right.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("middlerightsrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.right.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("middlerightsrc Loaded ");
										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.right.size = xml->getAttributeValueAsInt("middlerightsize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.right.color = dbRGB(xml->getAttributeValueAsInt("middlerightred"),xml->getAttributeValueAsInt("middlerightgreen"),xml->getAttributeValueAsInt("middlerightblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.right.alpha = xml->getAttributeValueAsInt("middlerightalpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.middle.right.linestyle = xml->getAttributeValueAsInt("middlerightlinestyle");

										if(xml->getAttributeValue("bottomleftsrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.left.dbImageID = dbImageResource->add(xml->getAttributeValue("bottomleftsrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.left.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("bottomleftsrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.left.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("bottomleftsrc Loaded ");
										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.left.size = xml->getAttributeValueAsInt("bottomleftsize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.left.color = dbRGB(xml->getAttributeValueAsInt("bottomleftred"),xml->getAttributeValueAsInt("bottomleftgreen"),xml->getAttributeValueAsInt("bottomleftblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.left.alpha = xml->getAttributeValueAsInt("bottomleftalpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.left.linestyle = xml->getAttributeValueAsInt("bottomleftlinestyle");

										if(xml->getAttributeValue("bottomcentersrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.center.dbImageID = dbImageResource->add(xml->getAttributeValue("bottomcentersrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.center.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("bottomcentersrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.center.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("bottomcentersrc Loaded ");
										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.center.size = xml->getAttributeValueAsInt("bottomcentersize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.center.color = dbRGB(xml->getAttributeValueAsInt("bottomcenterred"),xml->getAttributeValueAsInt("bottomcentergreen"),xml->getAttributeValueAsInt("bottomcenterblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.center.alpha = xml->getAttributeValueAsInt("bottomcenteralpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.center.linestyle = xml->getAttributeValueAsInt("bottomcenterlinestyle");

										if(xml->getAttributeValue("bottomrightsrc")){
											theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.right.dbImageID = dbImageResource->add(xml->getAttributeValue("bottomrightsrc"));
											if(!dbImageExist(theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.right.dbImageID)){
												dbLoadImage((char*)xml->getAttributeValue("bottomrightsrc"),theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.right.dbImageID);
												bugboard->print("YES ");
											}
											bugboard->print("bottomrightsrc Loaded ");
										}
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.right.size = xml->getAttributeValueAsInt("bottomrightsize");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.right.color = dbRGB(xml->getAttributeValueAsInt("bottomrightred"),xml->getAttributeValueAsInt("bottomrightgreen"),xml->getAttributeValueAsInt("bottomrightblue"));
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.right.alpha = xml->getAttributeValueAsInt("bottomrightalpha");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->border.edge.bottom.right.linestyle = xml->getAttributeValueAsInt("bottomrightlinestyle");

										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->colorkeyred = xml->getAttributeValueAsInt("colorkeyred");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->colorkeygreen = xml->getAttributeValueAsInt("colorkeygreen");
										theme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->colorkeyblue = xml->getAttributeValueAsInt("colorkeyblue");

									}
									break;

							}

							parsestack.push(make_pair(parentnode[1].first,parentnode[1].second));
							break;
					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_AUDIO:

					parentnode.push_back(parsestack.top());
					parsestack.pop();

					attribute["value"] = parentnode[0].second;

					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_EVENT:

							parentnode.push_back(parsestack.top());
							parsestack.pop();

							switch(parentnode[1].first){

								case BRAIN_XML_NODENAME_SCHEME:
									bugboard->print("\nSound Scheme");

									if(xml->getAttributeValue("src")){
										if(dbFileExist((char*)xml->getAttributeValue("src"))){
										
											scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->type = attributevaluemap[xml->getAttributeValue("type")];
											scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->system = attributevaluemap[xml->getAttributeValue("system")];
											scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->loop = xml->getAttributeValueAsInt("loop");

											//select sound system
											switch(attributevaluemap[(char*)xml->getAttributeValueSafe("system")]){

												case BRAIN_SCHEME_AUDIO_SYSTEM_OAW:
													//set up oaw audio
													break;

												case BRAIN_SCHEME_AUDIO_SYSTEM_DGDK:
												default:
													//select sound type
													switch(attributevaluemap[(char*)xml->getAttributeValueSafe("type")]){

														case BRAIN_SCHEME_AUDIO_TYPE_SOUND:
															scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->audioID = dbSoundResource->add(xml->getAttributeValue("src"));
															bugboard->print(" DGDK Sound Loaded ");
															if(!dbSoundExist(scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->audioID)){
																dbLoadSound((char*)xml->getAttributeValue("src"),scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->audioID);
																bugboard->print("YES ");
															}
															break;

														case BRAIN_SCHEME_AUDIO_TYPE_MUSIC:
															scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->audioID = dbMusicResource->add(xml->getAttributeValue("src"));
															bugboard->print(" DGDK Music Loaded ");
															if(!dbMusicExist(scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->audioID)){
																dbLoadMusic((char*)xml->getAttributeValue("src"),scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->audioID);
																bugboard->print("YES ");
															}													
															break;
													}

											}
											
											bugboard->print((char*)xml->getAttributeValue("src"));
											bugboard->print("[type=");
											bugboard->print(dbStr(scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->type));
											bugboard->print(",audioID=");
											bugboard->print(dbStr(scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->audioID));
											bugboard->print(",system=");
											bugboard->print(dbStr(scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->system));
											bugboard->print(",loop=");
											bugboard->print(dbStr(scheme::namemap[parentnode[1].second]->eventaction[esm::statenamemap[attribute["value"]]]->loop));
											bugboard->print("]");
										}
									}
									break;

								default:
									return(syntaxerror("Expected Previous <event>"));

							}

							parsestack.push(make_pair(parentnode[1].first,parentnode[1].second));
							break;
					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_FONT:

					parentnode.push_back(parsestack.top());
					parsestack.pop();
					
					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_EVENT:

							parentnode.push_back(parsestack.top());
							parsestack.pop();

							switch(parentnode[1].first){

								case BRAIN_XML_NODENAME_STYLE:
									style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->fontname = (char*)xml->getAttributeValueSafe("face");
									style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->type = xml->getAttributeValueAsInt("type");
									style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->size.x = xml->getAttributeValueAsFloat("size");

									if(xml->getAttributeValueAsInt("alpha")){style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->alpha = xml->getAttributeValueAsInt("alpha");}
									if(xml->getAttributeValueAsInt("opaque")){style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->opaque = (bool)xml->getAttributeValueAsInt("opaque");}
									if(xml->getAttributeValueAsInt("transparent")){style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->transparent = (bool)xml->getAttributeValueAsInt("transparent");}
									if(xml->getAttributeValueAsInt("bold")){style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->bold = (bool)xml->getAttributeValueAsInt("bold");}
									if(xml->getAttributeValueAsInt("italic")){style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->italic = (bool)xml->getAttributeValueAsInt("italic");}

									style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->color = dbRGB(xml->getAttributeValueAsInt("red"),xml->getAttributeValueAsInt("green"),xml->getAttributeValueAsInt("blue"));
									style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->bgcolor = dbRGB(xml->getAttributeValueAsInt("bgred"),xml->getAttributeValueAsInt("bggreen"),xml->getAttributeValueAsInt("bgblue"));
									
									bugboard->print("\nstyle(\"");
									bugboard->print(parentnode[1].second);
									bugboard->print("\")[");
									bugboard->print(dbStr(esm::statenamemap[parentnode[0].second]));
									bugboard->print("]->font(");
									bugboard->print(style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->fontname);
									bugboard->print(")");
									break;

							}

							parsestack.push(make_pair(parentnode[1].first,parentnode[1].second));
							break;
					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_ALPHA:
				case BRAIN_XML_NODENAME_OPAQUE:
				case BRAIN_XML_NODENAME_TRANSPARENT:
				case BRAIN_XML_NODENAME_BOLD:
				case BRAIN_XML_NODENAME_ITALIC:

					parentnode.push_back(parsestack.top());
					parsestack.pop();
					
					switch(parentnode[0].first){

						case BRAIN_XML_NODENAME_EVENT:

							parentnode.push_back(parsestack.top());
							parsestack.pop();

							switch(parentnode[1].first){

								case BRAIN_XML_NODENAME_STYLE:
									switch(nodenamemap[nodename]){
										case BRAIN_XML_NODENAME_ALPHA:
											style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->alpha = xml->getAttributeValueAsInt("value");
											break;
										case BRAIN_XML_NODENAME_OPAQUE:
											style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->opaque = true;
											break;
										case BRAIN_XML_NODENAME_TRANSPARENT:
											style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->transparent = true;
											break;
										case BRAIN_XML_NODENAME_BOLD:
											style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->bold = true;
											break;
										case BRAIN_XML_NODENAME_ITALIC:
											style::namemap[parentnode[1].second]->eventaction[esm::statenamemap[parentnode[0].second]]->italic = true;
											break;
									}
									break;
							}
							
							parsestack.push(make_pair(parentnode[1].first,parentnode[1].second));
							break;
					}

					parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
					break;

				case BRAIN_XML_NODENAME_FORM:

					attribute["value"] = (char*)xml->getAttributeValueSafe("name");
					
					httpform::create(
						attribute["value"], 
						xml->getAttributeValueSafe("description"),
						attributevaluemap[xml->getAttributeValueSafe("method")],
						xml->getAttributeValueSafe("host"),
						xml->getAttributeValueAsInt("port"),
						xml->getAttributeValueSafe("src"),
						xml->getAttributeValueSafe("path")
					);

					break;

			}

			//PUSH NODENAME/VALUE PAIR TO PARSE STACK
			if(!xml->isEmptyElement()) {
				//if element is not an empty element, like <foo /> then push to stack
				bugboard->print("\nPUSH parsestack(");
				bugboard->print(nodename);
				bugboard->print(",\"");
				bugboard->print(attribute["value"]);
				bugboard->print("\")");

				parsestack.push(make_pair(nodenamemap[nodename],attribute["value"]));

			} else {

				bugboard->print("\nNO PUSH Element Empty");

			}

			break;//EXN_ELEMENT
		
		case EXN_ELEMENT_END: 	//2 -End of an xml element, like </foo>.
			if(!parsestack.empty()){ 

				bugboard->print("\nPOP parsestack");
			
				parentnode.push_back(parsestack.top());

				bugboard->print("(");
				bugboard->print(dbStr(parentnode[0].first));
				bugboard->print(",\"");
				bugboard->print(parentnode[0].second);
				bugboard->print("\")");			

				parsestack.pop();

			}
			break;//EXN_ELEMENT_END

//		case EXN_TEXT: 	//3 - Text within a xml element: <foo> this is the text. </foo>.
//			break;//EXT_TEXT
//		
//		case EXN_COMMENT: 	//4 - An xml comment like <!-- I am a comment --> or a DTD definition.
//			break;//EXN_COMMENT

		case EXN_CDATA: 	//5 - An xml cdata section like <![CDATA[ this is some CDATA ]]>.
			//Get Element

			parentnode.push_back(parsestack.top());
			parsestack.pop();

			switch(parentnode[0].first){

				case BRAIN_XML_NODENAME_SCRIPT:
					
					//get Script Parent Node
					parentnode.push_back(parsestack.top());
					parsestack.pop();

					switch(parentnode[1].first){

						case BRAIN_XML_NODENAME_MAUI:
							//load task and execute
							bugboard->print("\nloading brainsscript");
							darklua::task *task;
							task = new darklua::task("brainsscript",(char*)xml->getNodeData());
							task->execute(darklua::task::RUNNING);
							delete task;
							break;

						case BRAIN_XML_NODENAME_META:
							//load task and execute
							break;

						case BRAIN_XML_NODENAME_EVENT:

							parentnode.push_back(parsestack.top());
							parsestack.pop();

							bugboard->print("\nElement: ");
							bugboard->print(dbStr(parentnode[2].first));
							bugboard->print(", Name: ");
							bugboard->print(parentnode[2].second);
							bugboard->print(", State: ");
							bugboard->print(parentnode[1].second);
							
							//task name
							attribute["taskname"] = parentnode[2].second;
							if(strcmp((char*)attribute["taskname"].data(),"")!=0 ){
								attribute["taskname"].append("_");
							}
							attribute["taskname"].append(parentnode[1].second);

							switch(parentnode[2].first){

								case BRAIN_XML_NODENAME_BEHAVIOR:
									attribute["taskname"].insert(0,"behavior_");
									behavior::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task = new darklua::task(attribute["taskname"],(char*)xml->getNodeData());
									break;

								case BRAIN_XML_NODENAME_TRANSITION:
									attribute["taskname"].insert(0,"transition_");
									transition::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task = new darklua::task(attribute["taskname"],(char*)xml->getNodeData());
									break;

								case BRAIN_XML_NODENAME_STYLE:
									attribute["taskname"].insert(0,"style_");
									style::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task = new darklua::task(attribute["taskname"],(char*)xml->getNodeData());
									bugboard->print("\nStyle  Task Created\n");
									break;

								case BRAIN_XML_NODENAME_THEME:
									attribute["taskname"].insert(0,"theme_");
									theme::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task = new darklua::task(attribute["taskname"],(char*)xml->getNodeData());
									break;

								case BRAIN_XML_NODENAME_SCHEME:
									attribute["taskname"].insert(0,"scheme_");
									scheme::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task = new darklua::task(attribute["taskname"],(char*)xml->getNodeData());
									break;

								case BRAIN_XML_NODENAME_AGENT:
									attribute["taskname"].insert(0,"agent_");
									//if(xml->getAttributeValueSafe("language")=="darklua"){
									agent::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task = new darklua::task(attribute["taskname"],(char*)xml->getNodeData());
									agent::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task->executiontype = (darklua::task::executiontypes)xml->getAttributeValueAsInt("execution");
									//}
/*
									bugboard->print("\nagent(\"");
									bugboard->print(agent::namemap[parentnode[2].second]->name);
									bugboard->print("\")[");
									bugboard->print(parentnode[1].second);
									bugboard->print("]->task(");
									bugboard->print(attribute["taskname"]);
									bugboard->print(")=\"");
									//bugboard->print((char*)xml->getNodeData());
									bugboard->print(agent::namemap[parentnode[2].second]->eventaction[esm::statenamemap[parentnode[1].second]]->task->actionbatch[darklua::task::states::RUNNING]->script); 
									bugboard->print("\"");
*/									
									break;

							}

							bugboard->print(" Task ");
							bugboard->print(attribute["taskname"]);

							parsestack.push(make_pair(parentnode[2].first,parentnode[2].second));
							break;
					
					}

					parsestack.push(make_pair(parentnode[1].first,parentnode[1].second));
					break;

			}

			parsestack.push(make_pair(parentnode[0].first,parentnode[0].second));
			break;//EXN_CDATA

		//case EXN_UNKNOWN: 	//6 - Unknown element. 
		//	break;//EXN_UNKNOWN

	}
	
	bugboard->print("\n~xmlfile::parse");

	return(1);
}

int brains::xmlfile::syntaxerror(std::string errormsg){
	/*!
	* Description: generates xml parse error exit
	*
	* -#Input:
	*	-# none
	*
	* -#Output:
	*	-# 0 if no more nodes
	*/

	bugboard->get();
	bugboard->append("\nSYNTAX ERROR[");
	bugboard->append(dbStr(nodecount));
	bugboard->append("]:");
	bugboard->append(errormsg);
	bugboard->write();

	alertbox("MAUI XML Syntax Error",errormsg,ALERTBOX_SEVERITY_ERROR);

	return(BRAIN_ERROR);
}



/* 
MAUI XML

Tags
<brains>			Start MAUI XML file
<state>			Defines Event State Constant
<behavior>		Declares Agent Behavior for Agent Event Action States
<style>			Declares Agent 2D/3D Sprite Style Font
<theme>			Declares Agent 2D Sprite Theme Fill & Borders (Currently for 2D only)
<scheme>		Declares Agent Audio Scheme
<canvas>		Declares Canvas Object (Camera/Observer)
<device>		Declares Input Device
<agent>			Declares Agent
	<form>		Defines Agent as Form Input (Values are concenated and submitted via HTTP
	<submit>	Defines Agent as HTTP Submission Agent
	<reset>		Resets Agent Value Fields?
<meta>			TBD
<script>		Declares LUA Script (Script defined in CDATA)
<opaque>
<transparent>
<b>
<i>
<orientate>		Defines Agent Body (2D/3D Collision/Physics) Orientation and Shape
<physics>		Defines Body Physics Properties
<event>			Defines Event-based Action for Behaviors, Styles, Themes, Schemes, Agents
<font>			Defines Style Font Properties
<alpha>			Sets Font Alpha Property
<border>		Defines Theme Border Properties
<audio>

DESIGN NOTES:

	Agent with/without Sprites can be automatically determined by how they are declared.
	There is no to explicit declare OD(No Body, No Sprite)/1D(Body Only)/2D/3D.

		0D Style & Theme & Orientation = False

		1D Style & Theme = False, Orientation = True
			<orientate> initializes *body
		
		2D Style & Theme & Orientation = True
			<orientate> initializes *body, if 2D Style or Theme in Agent initialize Sprite 
		
		3D Style & Theme & Orientation = True
			<orientate> initializes *body

	0D-2D bodies are interchangable.

*/

/*
void brains::agent::propertylistinsert(std::string agentpropertyname, std::string agentpropertyvalue){
   //purpose: inserts property and value item to propertylist
   //parameters:
   //return:
    array insert at bottom agentpropertylist()
    agentpropertylist().name = agentpropertyname
    agentpropertylist().value = agentpropertyvalue
}

void brains::agent::propertylistdelete(std::string agentpropertyname)
   //purpose: removes item based on property name
   //parameters:
   //return:
    array index to top agentpropertylist()
    for agentpropertylistloop = 0 to array count(agentpropertylist())
        if (array index val(agentpropertylist())
            if (agentpropertylist().name = agentpropertyname
                array delete element agentpropertylist()
                exitvoid 0
            }
        }
        next array index agentpropertylist()
    }
}

void brains::agent::propertylistedit(std::string agentpropertyname ,std::string agentpropertyvalue ){
   //purpose: modifies property
   //parameters:
   //return:
    array index to top agentpropertylist()
    for agentpropertylistloop = 0 to array count(agentpropertylist())
        if (array index val(agentpropertylist())
            if (agentpropertylist().name = agentpropertyname
                agentpropertylist().value = agentpropertyvalue
                exitvoid 0
            }
        }
        next array index agentpropertylist()
    }
}

void brains::agent::propertylistclear()
   //purpose:
   //parameters:
   //return:
    empty array agentpropertylist()
}

void brains::agent::propertylistset(this){
   //purpose: modifies properties and actions for self
   //parameters:
   //return:
    //debugprint("agentpropertylistset(" + agent(this).name + ")")
    array index to top agentpropertylist()
    for agentpropertylistloop = 0 to array count(agentpropertylist())

        select fast left(agentpropertylist().name,6)
            case "action"
                   //debugprint(agentpropertylist().name + " executing...")
                   lua set int "agent",this
                   lua load string agentpropertylist().value,agentpropertylist().name + "_" + agent(this).name
                   lua_errorcheck()
            break;
            case "script"
                   //debugprint(agentpropertylist().name + " executing...")
                   script = scriptgetbyname(agentpropertylist().value)
                   lua set int "agent",this
                   lua load string script(script).content,script(script).name
                   lua_errorcheck()
		   break;
            case default
                   agentpropertyset(this,agentpropertylist().name,agentpropertylist().value)
            break;
        endselect

        next array index agentpropertylist()
    }
    //debugprint("~")
}

void brains::agent::siblingspropertylistset(this, agentsiblingschildrenflag){
   //purpose: modifies properties for siblings
   //parameters:
   //return:
    //bugboard->print("agentsiblingspropertylistset(" + agent(this).name + ")")
    siblingagent = agent(this).next
    repeat
        agentpropertylistset(siblingagent)
        if (agentsiblingschildrenflag { agentchildrenpropertylistset(siblingagent,agentsiblingschildrenflag);}
        siblingagent = agent(siblingagent).next
    until siblingagent = this or siblingagent = 0
    //bugboard->print("~")
}


void brains::agent::childrenpropertylistset(this, agentchildrenschildrenflag)
   //purpose: modifies properties for children, childrenchildren
   //parameters:
   //return:
    //bugboard->print("agentchildrenpropertylistset(" + agent(this).name + ")")
    childagent = agent(this).first
    if (childagent){
        repeat
            //do stuff
            agentpropertylistset(childagent)
            if (agentchildrenschildrenfla)g { agentchildrenpropertylistset(childagent,agentchildrenschildrenflag);}
            childagent = agent(childagent).next
        until childagent = agent(this).first or childagent = NULL
    }
    //bugboard->print("~")
}

void brains::agent::familypropertylistset(this)
   //purpose: modifies properties for self, siblings, siblingchildren, children, childrenchildren
   //parameters:
   //return:
    //bugboard->print("agentfamilypropertylistset(" + agent(this).name + ")")
    siblingagent = this;
    repeat
        agentpropertylistset(siblingagent)
        if (agent(siblingagent).first) { agentfamilypropertylistset(agent(siblingagent).first);}
        siblingagent = agent(siblingagent).next;
    until siblingagent = this or siblingagent = NULL;
    //bugboard->print("~");
}
*/