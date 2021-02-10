/*
 __  __    _   _   _ ___   ____     ___  
|  \/  |  / \ | | | |_ _| |___ \   / _ \ 
| |\/| | / / \| | | || |    __) | | | | |
| |  | |/ /_\ \ |_| || |   / __/ _| |_| |
|_|  |_/_/   \_\___/|___| |_____|_|\___/ 
      Multi-App User Interface 2.0
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
along with this program. if(not, see HTTP://www.gnu.org/licenses/.
*/

#include "MAUI.h"

// GENERAL ////////////////////////////////////////////////////////////////////////////////////////////////////

// MESSAGING //////////////////////////////////////////////////////////////////////////////////////////////////

// EVENT STATE MACHINE ////////////////////////////////////////////////////////////////////////////////////////
map<string, int> MAUI::ESM::StateNameMap;
map<string, int>::iterator MAUI::ESM::StateNameMapIterator;
int MAUI::ESM::StateIndex = 0;

/**
* @brief	Adds a Event State Name; auto generates a Integer Index, Creates LUA EventState Global Var
* @param	void
* @return	void
*/
void MAUI::ESM::StateNameAdd(string statename){

	if(!StateNameMap[statename]){
		StateNameMap[statename] = StateIndex;
		DarkLUA::System::IntegerSet((char*)statename.data(),StateIndex);
		StateIndex++;
	}
}

/**
* @brief	Clear State
* @param	void
* @return	void
*/
void  MAUI::ESM::Clear(void){

	PreviousState = State = NextState = 0;
	TransitState = -1;
	Counter = Count = Delta = 0.0f;
}

// SYSTEM //////////////////////////////////////////////////////////////////////////////////////////
MAUI::Behavior *MAUI::Behavior::DefaultBehavior = NULL;
MAUI::Behavior *MAUI::Behavior::DefaultTransition = NULL;
MAUI::Style *MAUI::Style::DefaultStyle = NULL;
MAUI::Theme *MAUI::Theme::DefaultTheme = NULL;
MAUI::Scheme *MAUI::Scheme::DefaultScheme = NULL;

MAUI::Canvas *MAUI::Canvas::BaseCanvas = NULL;
MAUI::Gizmo *MAUI::Gizmo::BaseGizmo = NULL;
MAUI::Gizmo *MAUI::Gizmo::Pointer = NULL;
MAUI::Gizmo *MAUI::Gizmo::Caret = NULL;

MAUI::Behavior *MAUI::Behavior::CurrentBehavior = NULL;
MAUI::Behavior *MAUI::Behavior::CurrentTransition = NULL;
MAUI::Style *MAUI::Style::CurrentStyle = NULL;
MAUI::Theme *MAUI::Theme::CurrentTheme = NULL;
MAUI::Scheme *MAUI::Scheme::CurrentScheme = NULL;
MAUI::Gizmo *MAUI::Gizmo::CurrentGizmo = NULL;
MAUI::Canvas *MAUI::Canvas::CurrentCanvas = NULL;
MAUI::HTTPForm* MAUI::HTTPForm::CurrentHTTPForm = NULL;

map<string,int> MAUI::InputDevice::ScanCodeMap;

/**
* @brief	Initializes MAUI; Creates base Gizmo, EventState name defs, xmlnode name defs
* @param	void
* @return	void
*/
void MAUI::System::Start(void){

	//DarkLUA Setup

	//darklua bind property access uiGizmoPropertyGet/Set
	Gizmo::PropertyAdd("Name", MAUI_GIZMO_PROPERTY_NAME);
	Gizmo::PropertyAdd("Description", MAUI_GIZMO_PROPERTY_DESCRIPTION);
	Gizmo::PropertyAdd("Caption", MAUI_GIZMO_PROPERTY_CAPTION);
	Gizmo::PropertyAdd("EventState", MAUI_GIZMO_PROPERTY_EVENTSTATE_STATE);
	Gizmo::PropertyAdd("EventStateCount", MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNT);
	Gizmo::PropertyAdd("EventStateCounter", MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNTER);
	Gizmo::PropertyAdd("BoundCollision", MAUI_GIZMO_PROPERTY_BOUND_COLLISION);
	Gizmo::PropertyAdd("BoundX",MAUI_GIZMO_PROPERTY_BOUND_X);
	Gizmo::PropertyAdd("BoundY",MAUI_GIZMO_PROPERTY_BOUND_Y);
	Gizmo::PropertyAdd("BoundZ",MAUI_GIZMO_PROPERTY_BOUND_Z);
	Gizmo::PropertyAdd("BoundPitch",MAUI_GIZMO_PROPERTY_BOUND_PITCH);
	Gizmo::PropertyAdd("BoundYaw",MAUI_GIZMO_PROPERTY_BOUND_YAW);
	Gizmo::PropertyAdd("BoundRoll",MAUI_GIZMO_PROPERTY_BOUND_ROLL);
	Gizmo::PropertyAdd("BoundWidth",MAUI_GIZMO_PROPERTY_BOUND_WIDTH);
	Gizmo::PropertyAdd("BoundHeight",MAUI_GIZMO_PROPERTY_BOUND_HEIGHT);
	Gizmo::PropertyAdd("BoundDepth",MAUI_GIZMO_PROPERTY_BOUND_DEPTH);	
	Gizmo::PropertyAdd("BoundOrientation",MAUI_GIZMO_PROPERTY_BOUND_ORIENTATION);	
	Gizmo::PropertyAdd("DeviceContact", MAUI_GIZMO_PROPERTY_CONTACT_COLLISION);
	Gizmo::PropertyAdd("DeviceAxisX", MAUI_GIZMO_PROPERTY_AXIS_X);
	Gizmo::PropertyAdd("DeviceAxisY", MAUI_GIZMO_PROPERTY_AXIS_Y);
	Gizmo::PropertyAdd("DeviceAxisZ", MAUI_GIZMO_PROPERTY_AXIS_Z);
	Gizmo::PropertyAdd("SpriteObject", MAUI_GIZMO_PROPERTY_SPRITE_OBJECT);
	Gizmo::PropertyAdd("State", MAUI_GIZMO_PROPERTY_STATE);
	Gizmo::PropertyAdd("DefaultCaption", MAUI_GIZMO_PROPERTY_DEFAULTCAPTION);

	//scancodes based on Blitz3D Scancode list
	
	InputDevice::ScanCodeMap["escape"]=1;
	InputDevice::ScanCodeMap["1"]=2;
	InputDevice::ScanCodeMap["2"]=3;
	InputDevice::ScanCodeMap["3"]=4;
	InputDevice::ScanCodeMap["4"]=5;
	InputDevice::ScanCodeMap["5"]=6;
	InputDevice::ScanCodeMap["6"]=7;
	InputDevice::ScanCodeMap["7"]=8;
	InputDevice::ScanCodeMap["8"]=9;
	InputDevice::ScanCodeMap["9"]=10;
	InputDevice::ScanCodeMap["0"]=11;
	InputDevice::ScanCodeMap["-"]=12;
	InputDevice::ScanCodeMap["="]=13;
	InputDevice::ScanCodeMap["backspace"]=14;
	InputDevice::ScanCodeMap["tab"]=15;
	InputDevice::ScanCodeMap["q"]=16;
	InputDevice::ScanCodeMap["w"]=17;
	InputDevice::ScanCodeMap["e"]=18;
	InputDevice::ScanCodeMap["r"]=19;
	InputDevice::ScanCodeMap["t"]=20;
	InputDevice::ScanCodeMap["y"]=21;
	InputDevice::ScanCodeMap["u"]=22;
	InputDevice::ScanCodeMap["i"]=23;
	InputDevice::ScanCodeMap["o"]=24;
	InputDevice::ScanCodeMap["p"]=25;
	InputDevice::ScanCodeMap["["]=26;
	InputDevice::ScanCodeMap["]"]=27;
	InputDevice::ScanCodeMap["enter"]=28;
	InputDevice::ScanCodeMap["leftcontrol"]=29;
	InputDevice::ScanCodeMap["a"]=30;
	InputDevice::ScanCodeMap["s"]=31;
	InputDevice::ScanCodeMap["d"]=32;
	InputDevice::ScanCodeMap["f"]=33;
	InputDevice::ScanCodeMap["g"]=34;
	InputDevice::ScanCodeMap["h"]=35;
	InputDevice::ScanCodeMap["j"]=36;
	InputDevice::ScanCodeMap["k"]=37;
	InputDevice::ScanCodeMap["l"]=38;
	InputDevice::ScanCodeMap[";"]=39;
	InputDevice::ScanCodeMap["'"]=40;
	InputDevice::ScanCodeMap["grave"]=41;
	InputDevice::ScanCodeMap["leftshift"]=42;
	InputDevice::ScanCodeMap["backslash"]=43;
	InputDevice::ScanCodeMap["z"]=44;
	InputDevice::ScanCodeMap["x"]=45;
	InputDevice::ScanCodeMap["c"]=46;
	InputDevice::ScanCodeMap["v"]=47;
	InputDevice::ScanCodeMap["b"]=48;
	InputDevice::ScanCodeMap["n"]=49;
	InputDevice::ScanCodeMap["m"]=50;
	InputDevice::ScanCodeMap[","]=51;
	InputDevice::ScanCodeMap["."]=52;
	InputDevice::ScanCodeMap["/"]=53;
	InputDevice::ScanCodeMap["rightshift"]=54;
	InputDevice::ScanCodeMap["*"]=55;
	InputDevice::ScanCodeMap["leftalt"]=56;
	InputDevice::ScanCodeMap["space"]=57;
	InputDevice::ScanCodeMap["capital"]=58;
	InputDevice::ScanCodeMap["f1"]=59;
	InputDevice::ScanCodeMap["f2"]=60;
	InputDevice::ScanCodeMap["f3"]=61;
	InputDevice::ScanCodeMap["f4"]=62;
	InputDevice::ScanCodeMap["f5"]=63;
	InputDevice::ScanCodeMap["f6"]=64;
	InputDevice::ScanCodeMap["f7"]=65;
	InputDevice::ScanCodeMap["f8"]=66;
	InputDevice::ScanCodeMap["f9"]=67;
	InputDevice::ScanCodeMap["f10"]=68;
	InputDevice::ScanCodeMap["numlock"]=69;
	InputDevice::ScanCodeMap["scrolllock"]=70;
	InputDevice::ScanCodeMap["num7"]=71;
	InputDevice::ScanCodeMap["num8"]=72;
	InputDevice::ScanCodeMap["num9"]=73;
	InputDevice::ScanCodeMap["num-"]=74;
	InputDevice::ScanCodeMap["num4"]=75;
	InputDevice::ScanCodeMap["num5"]=76;
	InputDevice::ScanCodeMap["num6"]=77;
	InputDevice::ScanCodeMap["num+"]=78;
	InputDevice::ScanCodeMap["num1"]=79;
	InputDevice::ScanCodeMap["num2"]=80;
	InputDevice::ScanCodeMap["num3"]=81;
	InputDevice::ScanCodeMap["num0"]=82;
	InputDevice::ScanCodeMap["num."]=83;
	InputDevice::ScanCodeMap["oem_102"]=86;
	InputDevice::ScanCodeMap["f11"]=87;
	InputDevice::ScanCodeMap["f12"]=88;
	InputDevice::ScanCodeMap["f13"]=100;
	InputDevice::ScanCodeMap["f14"]=101;
	InputDevice::ScanCodeMap["f15"]=102;
	InputDevice::ScanCodeMap["kana"]=112;
	InputDevice::ScanCodeMap["abnt_c1"]=115;
	InputDevice::ScanCodeMap["convert"]=121;
	InputDevice::ScanCodeMap["noconvert"]=123;
	InputDevice::ScanCodeMap["yen"]=125;
	InputDevice::ScanCodeMap["abnt_c2"]=126;
	InputDevice::ScanCodeMap["equals"]=141;
	InputDevice::ScanCodeMap["prevtrack"]=144;
	InputDevice::ScanCodeMap["at"]=145;
	InputDevice::ScanCodeMap["colon(:)"]=146;
	InputDevice::ScanCodeMap["underline"]=147;
	InputDevice::ScanCodeMap["kanji"]=148;
	InputDevice::ScanCodeMap["stop"]=149;
	InputDevice::ScanCodeMap["ax"]=150;
	InputDevice::ScanCodeMap["unlabeled"]=151;
	InputDevice::ScanCodeMap["nexttrack"]=153;
	InputDevice::ScanCodeMap["numenter"]=156;
	InputDevice::ScanCodeMap["rightcontrol"]=157;
	InputDevice::ScanCodeMap["mute"]=160;
	InputDevice::ScanCodeMap["calculator"]=161;
	InputDevice::ScanCodeMap["playpause"]=162;
	InputDevice::ScanCodeMap["mediastop"]=164;
	InputDevice::ScanCodeMap["volumedown"]=174;
	InputDevice::ScanCodeMap["volumeup"]=176;
	InputDevice::ScanCodeMap["webhome"]=178;
	InputDevice::ScanCodeMap[","]=179;
	InputDevice::ScanCodeMap["/"]=181;
	InputDevice::ScanCodeMap["sysreq"]=183;
	InputDevice::ScanCodeMap["rightalt"]=184;
	InputDevice::ScanCodeMap["pause"]=197;
	InputDevice::ScanCodeMap["home"]=199;
	InputDevice::ScanCodeMap["up"]=200;
	InputDevice::ScanCodeMap["pageup"]=201;
	InputDevice::ScanCodeMap["pagedown"]=202;
	InputDevice::ScanCodeMap["left"]=203;
	InputDevice::ScanCodeMap["right"]=205;
	InputDevice::ScanCodeMap["end"]=207;
	InputDevice::ScanCodeMap["down"]=208;
	InputDevice::ScanCodeMap["next"]=209;
	InputDevice::ScanCodeMap["insert"]=210;
	InputDevice::ScanCodeMap["delete"]=211;
	InputDevice::ScanCodeMap["leftwindows"]=219;
	InputDevice::ScanCodeMap["rightwindows"]=220;
	InputDevice::ScanCodeMap["apps"]=221;
	InputDevice::ScanCodeMap["power"]=222;
	InputDevice::ScanCodeMap["sleep"]=223;
	InputDevice::ScanCodeMap["wake"]=227;
	InputDevice::ScanCodeMap["websearch"]=229;
	InputDevice::ScanCodeMap["webfavorites"]=230;
	InputDevice::ScanCodeMap["webrefresh"]=231;
	InputDevice::ScanCodeMap["webstop"]=232;
	InputDevice::ScanCodeMap["webforward"]=233;
	InputDevice::ScanCodeMap["webback"]=234;
	InputDevice::ScanCodeMap["mycomputer"]=235;
	InputDevice::ScanCodeMap["mail"]=236;
	InputDevice::ScanCodeMap["mediaselect"]=237;

}

/**
* @brief	Update All UIObjects
* @param	void
* @return	void
*/
void MAUI::System::Update(void){

	InputDevice::Update();

	Canvas::Update();

	Gizmo::Update();

}

/**
* @brief	Shutdown MAUI
* @param	void
* @return	void
*/
void MAUI::System::Stop(void){

	Behavior::Destroy();
	Style::Destroy();
	Theme::Destroy();
	Scheme::Destroy();
	Gizmo::Destroy();
	InputDevice::Destroy();
	Canvas::Destroy();
}

// BEHAVIOR //////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::Behavior*> MAUI::Behavior::NameMap;
map<string,MAUI::Behavior*>::iterator MAUI::Behavior::NameMapIterator;

/**
* @brief	Behavior Constructor
* @param	void
*/
MAUI::Behavior::Behavior(void){
	
}

/**
* @brief	Behavior Constructor
* @param	string name - Behavior name
* @param	string description Behavior description used for Tooltip
*/	
MAUI::Behavior::Behavior(string name, string description=""){

	this->Name = name;
	this->Description = description;

}


/**
* @brief	Behavior Destructor
* @param	void
*/
MAUI::Behavior::~Behavior(void){
	
}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Behavior *MAUI::Behavior::Create(string name, string description){
	
	if(NameMap[name] == NULL){ 
		NameMap[name] = new Behavior(name, description);
	}
	return(NameMap[name]);
}

/**
* @brief	Destroy Behavior by Pointer
* @param	void
* @return	void
*/
void MAUI::Behavior::Destroy(Behavior *instance){

	//Destroy EventAction
	map<int, EventScript*>::iterator eventactioniterator;

	for(eventactioniterator = instance->EventAction.begin(); eventactioniterator !=  instance->EventAction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){			
			//delete task script if not shared
			if((*eventactioniterator).second->Task != NULL){
				if( !(*eventactioniterator).second->Task->Shared ) {
					delete (*eventactioniterator).second->Task;
				} else {
					(*eventactioniterator).second->Task->Shared--;
				}
			}

			delete (*eventactioniterator).second;
		}
	}

	instance->EventAction.clear();
	
	delete instance;

}

/**
* @brief	Destroys All Behaviors
* @param	void
* @return	void
*/
void MAUI::Behavior::Destroy(void){

	map<string,Behavior*>::iterator NameMapIterator;
	for(NameMapIterator = NameMap.begin(); NameMapIterator !=  NameMap.end();  NameMapIterator++){
		Destroy((*NameMapIterator).second);
	}
	NameMap.clear();
}

/**
* @brief	Return Pointer by name; if not available will Create Pointer
* @param	string name
* @return	MAUI::Behavior*
*/
MAUI::Behavior* MAUI::Behavior::Get(string name){
	
	if(NameMap[name] == NULL){ 
		NameMap[name] = new Behavior(name, "tbd");
	}
	return(NameMap[name]);
}

/**
* @brief	Copies Behavior and EventAction returns Pointer to Copy
* @param	string name
* @param	string description
* @return	MAUI::Behavior*
*/
MAUI::Behavior* MAUI::Behavior::Copy(string name, string description) {

	map<int, EventScript*>::iterator eventactioniterator;

	Behavior *instance = Create(name, description);

	//copy eventactions
	for(eventactioniterator = EventAction.begin(); eventactioniterator !=  EventAction.end();  eventactioniterator++){
	
		if((*eventactioniterator).second != NULL){
			//create eventaction
			instance->EventAction[(*eventactioniterator).first] = (*eventactioniterator).second->Copy();
		}
		
	}

	return(instance);
}

/**
* @brief	Assign Eventaction Property based ActionState
* @param	Behavior* instance
* @param	int propertytype - Behavior,Transition,Theme
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Behavior::Assign(MAUI::Behavior* instance, int propertytype, void* propertyptr, int actionstate){

	if(instance->EventAction[actionstate] == NULL) instance->EventAction[actionstate] = new Behavior::EventScript;

	switch(propertytype){

		case MAUI_BEHAVIOR_ASSIGN_PROPERTY_TASK:
			instance->EventAction[actionstate]->Task = (DarkLUA::Task*)propertyptr;
			break;
	}
}

/**
* @brief	Alias. Assign Eventaction Property based ActionState 
* @param	int propertytype - Behavior,Transition,Theme
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Behavior::Assign(int propertytype, void *propertyptr, int actionstate){
	Assign(this, propertytype, propertyptr, actionstate);
}

// BEHAVIOR::EVENTSCRIPT //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
*/
MAUI::Behavior::EventScript::EventScript(void){

	Task = NULL;

}

/**
* @brief	Inheritor
* @param	void
* @return	void
*/
void MAUI::Behavior::EventScript::Inherit(MAUI::Behavior::EventScript *parent){

	Task = parent->Task;

}

/**
* @brief	Copy
* @param	void
* @return	void
*/
MAUI::Behavior::EventScript *MAUI::Behavior::EventScript::Copy(void){

	EventScript *instance = new EventScript;
					
	//copy task
	if(Task != NULL){
		//replace gizmo names in scripts
		instance->Task = Task;
		Task->Shared++;
	}
	
	return(instance);

}

// STYLE //////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::Style*> MAUI::Style::NameMap;
map<string,MAUI::Style*>::iterator MAUI::Style::NameMapIterator;

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Style::Style(void){

	Type = 0;

}

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Style::Style(string name, string description=""){
	
	this->Name = name;
	this->Description = description;

}

/**
* @brief	destructor
* @param	void
* @return	void
*/
MAUI::Style::~Style(void){

}

/**
* @brief	Return Pointer by name; if not available will Create Pointer
* @param	void
* @return	void
*/
MAUI::Style *MAUI::Style::Create(string name, string description){
	
	if(NameMap[name] == NULL){ 
		NameMap[name] = new Style(name, description);
	}
	return(NameMap[name]);

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Style::Destroy(Style *instance){

	//Destroy EventAction

	map<int, EventScript*>::iterator eventactioniterator;
	for(eventactioniterator = instance->EventAction.begin(); eventactioniterator !=  instance->EventAction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){			
			//delete task script if not shared
			if((*eventactioniterator).second->Task != NULL){
				if( !(*eventactioniterator).second->Task->Shared ) {
					delete (*eventactioniterator).second->Task;
				} else {
					(*eventactioniterator).second->Task->Shared--;
				}
			}
			delete (*eventactioniterator).second;
		}
	}

	instance->EventAction.clear();

	delete instance;

}

/**
* @brief	destroys all styles
* @param	void
* @return	void
*/
void MAUI::Style::Destroy(void){
	
	map<string,Style*>::iterator NameMapIterator;
	for(NameMapIterator = NameMap.begin(); NameMapIterator != NameMap.end();  NameMapIterator++){
		Destroy((*NameMapIterator).second);
	}
	NameMap.clear();
}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Style *MAUI::Style::Get(string name){
	
	if(NameMap[name] == NULL){ 
		NameMap[name] = new Style(name, "tbd");
	}
	return(NameMap[name]);
}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Style *MAUI::Style::Copy(string name, string description) {

	map<int, EventScript*>::iterator eventactioniterator;

	Style *instance = Create(name, description);
	
	instance->Type = Type;

	//copy eventactions
	for(eventactioniterator = EventAction.begin(); eventactioniterator !=  EventAction.end();  eventactioniterator++){
	
		if((*eventactioniterator).second != NULL){

			//create eventaction
			instance->EventAction[(*eventactioniterator).first] = (*eventactioniterator).second->Copy();

		}
	}

	return(instance);

}

/**
* @brief	Assign Eventaction Property based ActionState
* @param	Style* instance
* @param	int propertytype -
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Style::Assign(MAUI::Style* instance, int propertytype, void* propertyptr, int actionstate){

	if(instance->EventAction[actionstate] == NULL) instance->EventAction[actionstate] = new Style::EventScript;

	switch(propertytype){

		case MAUI_STYLE_ASSIGN_PROPERTY_TASK://Task
			instance->EventAction[actionstate]->Task = (DarkLUA::Task*)propertyptr;
			break;
	}
}

/**
* @brief	Alias. Assign Eventaction Property based ActionState 
* @param	int propertytype - 
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Style::Assign(int propertytype, void *propertyptr, int actionstate){
	Assign(this, propertytype, propertyptr, actionstate);
}

// STYLE::EVENTSCRIPT //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	 Constructor
* @param	void
* @return	void
*/
MAUI::Style::EventScript::EventScript(void){

	Type = MAUI_STYLE_FONT_TYPE_DX9FONT;
	Fontname = "arial";
	FontID = 1;
	Size.x = Size.y = Size.z = 12;
	Alpha = 255;
	OpaqueFlag = false;
	TransparentFlag = true;
	BoldFlag = false;
	ItalicFlag = false;
	Color = -1;
	bgColor = -1;

	Parent = NULL;
	//meshfont = NULL;
	Task = NULL;

}

/**
* @brief	Set True Type Font
* @param	void
* @return	void
*/
void MAUI::Style::EventScript::dx9FontSet(void){

	Core->Text->FontSet(FontID);

}

/**
* @brief	Set True Type Font
* @param	void
* @return	void
*/
void MAUI::Style::EventScript::FontArtSet(void){

	//FontArt
	if(S3GE::FontArt::NameMap[Fontname]!=NULL){
		S3GE::FontArt::CurrentFontArt = S3GE::FontArt::NameMap[Fontname];
	}

}

/**
* @brief	Set True Type Font
* @param	void
* @return	void
*/
void MAUI::Style::EventScript::MeshFontSet(void){

}

/**
* @brief	Inheritor
* @param	void
* @return	void
*/
void MAUI::Style::EventScript::Inherit(MAUI::Style::EventScript *parent){

	Fontname = 	parent->Fontname;
	//meshfont = 	parent->meshfont;
	Size = 	parent->Size;
	Alpha = 	parent->Alpha;
	OpaqueFlag = 	parent->OpaqueFlag;
	TransparentFlag = 	parent->TransparentFlag;
	BoldFlag = 	parent->BoldFlag;
	ItalicFlag = 	parent->ItalicFlag;
	Color = 	parent->Color;
	bgColor = 	parent->bgColor;
	Task = 	parent->Task;

}

/**
* @brief	Copy
* @param	void
* @return	void
*/
MAUI::Style::EventScript *MAUI::Style::EventScript::Copy(void){

	EventScript *instance = new EventScript;
	
	instance->Parent = Parent;
	instance->Type = Type;
	instance->Fontname = Fontname;
	instance->FontID = FontID;
	instance->Size = Size;
	instance->Alpha = Alpha; 
	instance->OpaqueFlag = OpaqueFlag;
	instance->TransparentFlag = TransparentFlag;
	instance->BoldFlag = BoldFlag;
	instance->ItalicFlag = ItalicFlag;
	instance->Color = Color;
	instance->bgColor = bgColor;

	//copy task
	if(Task != NULL){
		//replace gizmo names in scripts
		instance->Task = Task;
		Task->Shared++;
	}

	return(instance);

}



// THEME //////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::Theme*> MAUI::Theme::NameMap;
map<string,MAUI::Theme*>::iterator MAUI::Theme::NameMapIterator;

/**
* @brief	Constructor
* @param	void
*/
MAUI::Theme::Theme(void){

	Type = 0; //2D
}

/**
* @brief	Constructor
* @param	void
*/
MAUI::Theme::Theme(string name, string description=""){
	
	this->Name = name;
	this->Description = description;

}

/**
* @brief	Destructor
* @param	void
*/
MAUI::Theme::~Theme(void){

}

/**
* @brief	Return Pointer by name; if not available will Create Pointer
* @param	void
* @return	void
*/
MAUI::Theme *MAUI::Theme::Create(string name, string description){
	
	if(NameMap[name] == NULL){ 
		NameMap[name] = new Theme(name, description);
	}
	return(NameMap[name]);
}

/**
* @brief	Destroy Theme Instance
* @param	void
* @return	void
*/
void MAUI::Theme::Destroy(Theme *instance){

	//Destroy EventAction

	map<int, EventScript*>::iterator eventactioniterator;

	for(eventactioniterator = instance->EventAction.begin(); eventactioniterator !=  instance->EventAction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){

			//delete task script if not shared
			if((*eventactioniterator).second->Task != NULL){
				if( !(*eventactioniterator).second->Task->Shared ) {
					delete (*eventactioniterator).second->Task;
				} else {
					(*eventactioniterator).second->Task->Shared--;
				}
			}

			delete (*eventactioniterator).second;
		}
	}

	instance->EventAction.clear();
	
	delete instance;

}

/**
* @brief	destroys all themes
* @param	void
* @return	void
*/
void MAUI::Theme::Destroy(void){

	map<string,Theme*>::iterator NameMapIterator;
	for(NameMapIterator = NameMap.begin(); NameMapIterator !=  NameMap.end();  NameMapIterator++){
		if((*NameMapIterator).second != NULL){
			Destroy((*NameMapIterator).second);
		}
	}
	NameMap.clear();

}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Theme *MAUI::Theme::Get(string name){

	if(NameMap[name] == NULL){ 
		NameMap[name] = new Theme(name, "tbd");
	}
	return(NameMap[name]);
}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Theme *MAUI::Theme::Copy(string name, string description) {

	map<int, EventScript*>::iterator eventactioniterator;

	Theme *instance = Create(name, description);
	
	instance->Type = Type;

	//copy eventactions
	for(eventactioniterator = EventAction.begin(); eventactioniterator !=  EventAction.end();  eventactioniterator++){
	
		if((*eventactioniterator).second != NULL){

			//create eventaction
			instance->EventAction[(*eventactioniterator).first] = (*eventactioniterator).second->Copy();
	
		}
		
	}

	return(instance);

}


/**
* @brief	Assign Eventaction Property based ActionState
* @param	Theme* instance
* @param	int propertytype -
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Theme::Assign(MAUI::Theme* instance, int propertytype, void* propertyptr, int actionstate){

	if(instance->EventAction[actionstate] == NULL) instance->EventAction[actionstate] = new Theme::EventScript;

	switch(propertytype){

		case MAUI_THEME_ASSIGN_PROPERTY_TASK://Task
			instance->EventAction[actionstate]->Task = (DarkLUA::Task*)propertyptr;
			break;
	}
}

/**
* @brief	Alias. Assign Eventaction Property based ActionState 
* @param	int propertytype - 
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Theme::Assign(int propertytype, void *propertyptr, int actionstate){
	Assign(this, propertytype, propertyptr, actionstate);
}

// THEME::EVENTSCRIPT //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	 Constructor
* @param	void
* @return	void
*/
MAUI::Theme::EventScript::EventScript(void){

	ColorKeyRed  = ColorKeyGreen = ColorKeyBlue = 0;
	Border.Clear();

	Parent = NULL;
	Task = NULL;

}


/**
* @brief	Draws Theme Borders/Center Lines and Images
* @param	D3DVECTOR size (.x = width,.y = height)
* @param	int offsetx
* @param	int offsety
* @return	void
*/
void MAUI::Theme::EventScript::Draw(D3DVECTOR size, int offsetx, int offsety){

	//LINE DRAWING 
	float loop;

	//FILL
	if(Border.Edge.Middle.Center.Size){
		dbInk(Border.Edge.Middle.Center.Color, 0);
		dbBox(offsetx + Border.Edge.Middle.Left.Size, offsety + Border.Edge.Top.Center.Size, offsetx + (int)size.x - Border.Edge.Middle.Right.Size,  offsety + (int)size.y - Border.Edge.Bottom.Center.Size);
	}

	//TOP
	if(Border.Edge.Top.Center.Size){
		dbInk(Border.Edge.Top.Center.Color, 0);
		for(loop = 0; loop < Border.Edge.Top.Center.Size; loop++){
			LineStyleDraw(Border.Edge.Top.Center.LineStyle, offsetx + loop,  offsety + loop,  offsetx + size.x - loop, offsety + loop);
		}
	}

	//BOTTOM
	if(Border.Edge.Bottom.Center.Size){
		dbInk(Border.Edge.Bottom.Center.Color, 0);
		for(loop = 0; loop < Border.Edge.Bottom.Center.Size; loop++){
			LineStyleDraw(Border.Edge.Bottom.Center.LineStyle, offsetx + loop,  size.y - loop - 1,  size.x - loop,  size.y - loop - 1);
		}
	}

	//LEFT
	if(Border.Edge.Middle.Left.Size){
		dbInk(Border.Edge.Middle.Left.Color, 0);
		for(loop = 0; loop < Border.Edge.Middle.Left.Size; loop++){
			LineStyleDraw(Border.Edge.Middle.Left.LineStyle, offsetx + loop,  offsety + loop,  offsetx + loop, offsety + size.y - loop);
		}
	}

	//RIGHT.
	if(Border.Edge.Middle.Right.Size){
		dbInk(Border.Edge.Middle.Right.Color, 0);
		for(loop = 0; loop < Border.Edge.Middle.Right.Size; loop++){
			LineStyleDraw(Border.Edge.Middle.Right.LineStyle, offsetx + size.x - loop - 1,  offsety + loop,  offsetx + size.x - loop - 1, offsety + size.y - loop);
		}
	}

	//IMAGE DRAWING
	float toprightimagestartx = size.x - (float)dbGetImageWidth(Border.Edge.Top.Right.dbImageID);
	float bottomleftimagestarty = size.y - (float)dbGetImageHeight(Border.Edge.Bottom.Left.dbImageID);
	float bottomrightimagestartx = size.x - (float)dbGetImageWidth(Border.Edge.Bottom.Right.dbImageID);
	float bottomrightimagestarty = size.y - (float)dbGetImageHeight(Border.Edge.Bottom.Right.dbImageID);

	//CENTER TILES
	if(Border.Edge.Middle.Center.dbImageID){
		float middlecenterimagestartx = (float)dbGetImageWidth(Border.Edge.Middle.Left.dbImageID);
		float middlecenterimagestarty = (float)dbGetImageHeight(Border.Edge.Top.Left.dbImageID);
		int middlecenterimagextiles = Border.Edge.Middle.Center.Tile > 0 ? Border.Edge.Middle.Center.Tile : size.x - ( dbGetImageWidth(Border.Edge.Middle.Left.dbImageID) + dbGetImageWidth(Border.Edge.Middle.Right.dbImageID) ) / dbGetImageWidth(Border.Edge.Middle.Center.dbImageID);
		int middlecenterimageytiles = Border.Edge.Middle.Center.Tile > 0 ? Border.Edge.Middle.Center.Tile : size.y - ( dbGetImageHeight(Border.Edge.Top.Center.dbImageID) + dbGetImageHeight(Border.Edge.Bottom.Center.dbImageID) )  / dbGetImageHeight(Border.Edge.Middle.Center.dbImageID);

		for(loop = 0; loop < middlecenterimageytiles; loop++){
			for(int loop2 = 0; loop2 < middlecenterimagextiles; loop2++){
				dbPasteImage( Border.Edge.Middle.Center.dbImageID, offsetx + (int)middlecenterimagestartx, offsety + (int)middlecenterimagestarty, Border.Edge.Middle.Center.Transparency);
				middlecenterimagestartx += (float)dbGetImageWidth(Border.Edge.Middle.Center.dbImageID);
			}
			middlecenterimagestarty += (float)dbGetImageHeight(Border.Edge.Middle.Center.dbImageID);
			middlecenterimagestartx = (float)dbGetImageWidth(Border.Edge.Middle.Left.dbImageID);

		}
	}
	
	//HORIZONTAL EDGES
	if(Border.Edge.Top.Center.dbImageID){
		float topcenterimagestartx = (float)dbGetImageWidth(Border.Edge.Top.Left.dbImageID);
		int topcenterimagetiles = Border.Edge.Top.Center.Tile > 0 ? Border.Edge.Top.Center.Tile : toprightimagestartx - topcenterimagestartx / dbGetImageWidth(Border.Edge.Top.Center.dbImageID);

		for(loop = 0; loop < topcenterimagetiles; loop++){
			dbPasteImage(Border.Edge.Top.Center.dbImageID, offsetx + (int)topcenterimagestartx, offsety, Border.Edge.Top.Center.Transparency);
			topcenterimagestartx += (float)dbGetImageWidth(Border.Edge.Top.Center.dbImageID);
		}
	}

	if(Border.Edge.Bottom.Center.dbImageID){
		float bottomcenterimagestartx = (float)dbGetImageWidth(Border.Edge.Bottom.Left.dbImageID);
		int bottomcenterimagetiles = Border.Edge.Bottom.Center.Tile > 0 ? Border.Edge.Bottom.Center.Tile : bottomrightimagestartx - bottomcenterimagestartx / (float)dbGetImageWidth(Border.Edge.Bottom.Center.dbImageID);
		float bottomcenterimagestarty = size.y - dbGetImageHeight(Border.Edge.Bottom.Center.dbImageID);

		for(int loop = 0; loop < bottomcenterimagetiles; loop++){
			dbPasteImage(Border.Edge.Bottom.Center.dbImageID, offsetx + (int)bottomcenterimagestartx, offsety + (int)bottomcenterimagestarty, Border.Edge.Bottom.Center.Transparency);
			bottomcenterimagestartx += (float)dbGetImageWidth(Border.Edge.Bottom.Center.dbImageID);

		}
	}

	//VERTICAL EDGES
	if(Border.Edge.Middle.Left.dbImageID){
		float middleleftimagestarty = (float)dbGetImageHeight(Border.Edge.Top.Left.dbImageID);
		int middleleftimagetiles = Border.Edge.Middle.Left.Tile > 0 ? Border.Edge.Middle.Left.Tile : bottomleftimagestarty - middleleftimagestarty / dbGetImageHeight(Border.Edge.Middle.Left.dbImageID);

		for(loop = 0; loop < middleleftimagetiles; loop++){
			dbPasteImage(Border.Edge.Middle.Left.dbImageID, offsetx, offsety + (int)middleleftimagestarty, Border.Edge.Middle.Left.Transparency);
			middleleftimagestarty += (float)dbGetImageHeight(Border.Edge.Middle.Left.dbImageID);

		}
	}

	if(Border.Edge.Middle.Right.dbImageID){
		float middlerightimagestarty = (float)dbGetImageHeight(Border.Edge.Bottom.Left.dbImageID);
		int middlerightimagetiles = Border.Edge.Middle.Right.Tile > 0 ? Border.Edge.Middle.Right.Tile : bottomrightimagestarty - middlerightimagestarty / dbGetImageHeight(Border.Edge.Middle.Right.dbImageID);
		float middlerightimagestartx = size.x - dbGetImageWidth(Border.Edge.Middle.Right.dbImageID);

		for(loop = 0; loop < middlerightimagetiles; loop++){
			dbPasteImage(Border.Edge.Middle.Right.dbImageID, offsetx + (int)middlerightimagestartx, offsety + (int)middlerightimagestarty, Border.Edge.Middle.Right.Transparency);
			middlerightimagestarty += (float)dbGetImageHeight(Border.Edge.Middle.Right.dbImageID);
		}
	}

	//CORNERS
	if(Border.Edge.Top.Left.dbImageID){
		dbPasteImage(Border.Edge.Top.Left.dbImageID, offsetx, offsety, Border.Edge.Top.Left.Transparency);
	}

	if(Border.Edge.Top.Right.dbImageID){
		dbPasteImage(Border.Edge.Top.Right.dbImageID, offsetx + (int)toprightimagestartx, offsety, Border.Edge.Top.Right.Transparency);
	}

	if(Border.Edge.Bottom.Left.dbImageID){
		dbPasteImage(Border.Edge.Bottom.Left.dbImageID, offsetx, offsety + (int)bottomleftimagestarty, Border.Edge.Bottom.Left.Transparency);
	}

	if(Border.Edge.Bottom.Right.dbImageID){
		dbPasteImage(Border.Edge.Bottom.Right.dbImageID, offsetx + (int)bottomrightimagestartx, offsety + (int)bottomrightimagestarty, Border.Edge.Bottom.Right.Transparency);
	}

}

void MAUI::Theme::EventScript::LineStyleDraw(int type, float x1, float y1, float x2, float y2){

	switch(type){
		case 0://standard line
		default:	
			dbLine((int)x1, (int)y1, (int)x2, (int)y2);
			break;

	}

}

/**
* @brief	Inheritor
* @param	void
* @return	void
*/
void MAUI::Theme::EventScript::Inherit(MAUI::Theme::EventScript *parent){

	ColorKeyRed = parent->ColorKeyRed;	
	ColorKeyGreen = parent->ColorKeyGreen;	
	ColorKeyBlue = parent->ColorKeyBlue;	
	Task = parent->Task;	

}

/**
* @brief	Copy
* @param	void
* @return	void
*/
MAUI::Theme::EventScript *MAUI::Theme::EventScript::Copy(void){


	EventScript *instance = new EventScript;

	instance->Parent = Parent;	
	Border.Copy(instance->Border);	
	instance->ColorKeyRed = ColorKeyRed;	
	instance->ColorKeyGreen = ColorKeyGreen;	
	instance->ColorKeyBlue = ColorKeyBlue;	

	//copy task
	if(Task != NULL){
		//replace gizmo names in scripts
		instance->Task = Task;
		Task->Shared++;
	}	

	return(instance);
	
}

// THEME::BORDERSET //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
*/
MAUI::Theme::BorderArt::BorderArt(void){

}

/**
* @brief	Destructor
* @param	void
*/
MAUI::Theme::BorderArt::~BorderArt(void){

}

/**
* @brief	inheritor
* @param	void
* @return	void
*/
void MAUI::Theme::BorderArt::Inherit(MAUI::Theme::BorderArt parent){

	Edge.Inherit(parent.Edge);

}

/**
* @brief	clear
* @param	void
* @return	void
*/
void MAUI::Theme::BorderArt::Clear(void){

	Edge.Clear();
}

/**
* @brief	inheritor
* @param	void
* @return	void
*/
void MAUI::Theme::BorderArt::Copy(MAUI::Theme::BorderArt &instance){

	Edge.Copy(instance.Edge);

}

// SCHEME //////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::Scheme*> MAUI::Scheme::NameMap;
map<string,MAUI::Scheme*>::iterator MAUI::Scheme::NameMapIterator;

/**
* @brief	Constructor
* @param	void
*/
MAUI::Scheme::Scheme(void){

}

/**
* @brief	Constructor
* @param	void
*/
MAUI::Scheme::Scheme(string name, string description=""){

	this->Name = name;
	this->Description = description;

}

/**
* @brief	Destructor
* @param	void
*/
MAUI::Scheme::~Scheme(void){

}

/**
* @brief	Return Pointer by name; if not available will Create Pointer
* @param	void
* @return	void
*/
MAUI::Scheme *MAUI::Scheme::Create(string name, string description){

	if(NameMap[name] == NULL){ 
		NameMap[name] = new Scheme(name, description);
	}
	return(NameMap[name]);
}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Scheme::Destroy(Scheme *instance){

	//Destroy EventAction
	map<int, EventScript*>::iterator eventactioniterator;

	for(eventactioniterator = instance->EventAction.begin(); eventactioniterator !=  instance->EventAction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){

			//delete audio
			switch(((*eventactioniterator).second)->System){
				case MAUI_SCHEME_AUDIO_SYSTEM_DGDK:

					switch(((*eventactioniterator).second)->Type){

						case MAUI_SCHEME_AUDIO_TYPE_SOUND:
							if(((*eventactioniterator).second)->AudioID){
								if(dbSoundExist(((*eventactioniterator).second)->AudioID)){
									dbDeleteSound(((*eventactioniterator).second)->AudioID);
								}
								dbSoundResource->Push(((*eventactioniterator).second)->AudioID);
							}
							break;

						case MAUI_SCHEME_AUDIO_TYPE_MUSIC:
							if(((*eventactioniterator).second)->AudioID){
								if(dbMusicExist(((*eventactioniterator).second)->AudioID)){
									dbDeleteMusic(((*eventactioniterator).second)->AudioID);
								}
								dbMusicResource->Push(((*eventactioniterator).second)->AudioID);
							}
							break;
					}
			}

			//delete task script if not shared
			if((*eventactioniterator).second->Task != NULL){
				if( !(*eventactioniterator).second->Task->Shared ) {
					delete (*eventactioniterator).second->Task;
				} else {
					(*eventactioniterator).second->Task->Shared--;
				}
			}

			delete (*eventactioniterator).second;
		}
	}
	instance->EventAction.clear();
	
	delete instance;

}

/**
* @brief	destroys all schemes
* @param	void
* @return	void
*/
void MAUI::Scheme::Destroy(void){

	map<string,Scheme*>::iterator NameMapIterator;
	for(NameMapIterator = NameMap.begin(); NameMapIterator !=  NameMap.end();  NameMapIterator++){
		Destroy((*NameMapIterator).second);
	}
	NameMap.clear();
}

/**
* @brief	Return Pointer by name; if not available will Create Pointer
* @param	void
* @return	void
*/
MAUI::Scheme *MAUI::Scheme::Get(string name){

	if(NameMap[name] == NULL){ 
		NameMap[name] = new Scheme(name, "tbd");
	}
	return(NameMap[name]);
}


/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Scheme *MAUI::Scheme::Copy(string name, string description) {

	map<int, EventScript*>::iterator eventactioniterator;

	Scheme *instance = Create(name, description);

	//copy eventactions
	for(eventactioniterator = EventAction.begin(); eventactioniterator !=  EventAction.end();  eventactioniterator++){
	
		if((*eventactioniterator).second != NULL){

			//create eventaction
			instance->EventAction[(*eventactioniterator).first] = (*eventactioniterator).second->Copy();

		}
		
	}

	return(instance);

}

/**
* @brief	Assign Eventaction Property based ActionState
* @param	Scheme* instance
* @param	int propertytype -
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Scheme::Assign(MAUI::Scheme* instance, int propertytype, void* propertyptr, int actionstate){

	if(instance->EventAction[actionstate] == NULL) instance->EventAction[actionstate] = new Scheme::EventScript;

	switch(propertytype){

		case MAUI_SCHEME_ASSIGN_PROPERTY_TASK://Task
			instance->EventAction[actionstate]->Task = (DarkLUA::Task*)propertyptr;
			break;
	}
}

/**
* @brief	Alias. Assign Eventaction Property based ActionState 
* @param	int propertytype - 
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Scheme::Assign(int propertytype, void *propertyptr, int actionstate){
	Assign(this, propertytype, propertyptr, actionstate);
}

// SCHEME::EVENTSCRIPT //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	 Constructor
* @param	void
* @return	void
*/
MAUI::Scheme::EventScript::EventScript(void){

	Type = AudioID = System = Loop = LoopCount = 0;
	Task = NULL;

}

/**
* @brief	 
* @param	void
* @return	void
*/
void MAUI::Scheme::EventScript::Inherit(MAUI::Scheme::EventScript *parent){

	Type = parent->Type;
	AudioID = parent->AudioID;
	System = parent->System;
	Task = parent->Task;

}

/**
* @brief	Copy
* @param	void
* @return	void
*/
MAUI::Scheme::EventScript *MAUI::Scheme::EventScript::Copy(void){

	EventScript *instance = new EventScript;
	
	instance->Type = Type;
	instance->AudioID = AudioID;
	instance->System = System;
	instance->Loop = Loop;
	instance->LoopCount	= LoopCount;

	//copy task
	if(Task != NULL){
		//replace gizmo names in scripts
		instance->Task = Task;
		Task->Shared++;
	}

	return(instance);

}


// DEVICE //////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::InputDevice*> MAUI::InputDevice::NameMap;
map<string,MAUI::InputDevice*>::iterator MAUI::InputDevice::NameMapIterator;
list<MAUI::InputDevice*> MAUI::InputDevice::ActiveList;
list<MAUI::InputDevice*>::iterator MAUI::InputDevice::ActiveListIterator;
queue<MAUI::InputDevice*> MAUI::InputDevice::InactiveQueue;

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::InputDevice::InputDevice(void){

	Type = ContactType = ContactExist = Contact = AxisType = 0;

}

/**
* @brief	Constructor
* @param	void
*/
MAUI::InputDevice::InputDevice(string name, string description=""){

	Type = ContactType = ContactExist = Contact = AxisType = 0;
	this->Name = name;
	this->Description = description;
}

/**
* @brief	Destructor
* @param	void
*/
MAUI::InputDevice::~InputDevice(void){

}

/**
* @brief	Creates new InputDevice
* @param	string parentname - name of parent InputDevice
* @param	string name - name for this InputDevice
* @param	string description - tooltip description
* @return	void
*/
MAUI::InputDevice *MAUI::InputDevice::Create(string parentname, string name, string description, int type){

	if(NameMap[name] == NULL){
        NameMap[name] = new InputDevice(name, description);
	}

	NameMap[name]->Type = type;

	ActiveList.push_back(NameMap[name]);
	NameMap[name]->State = ACTIVE;

	return(NameMap[name]);
}

/**
* @brief	Destroy InputDevice by Pointer
* @param	void
* @return	void
*/
void MAUI::InputDevice::Destroy(MAUI::InputDevice *instance){

	delete instance;
}

/**
* @brief	destroys all InputDevices
* @param	void
* @return	void
*/
void MAUI::InputDevice::Destroy(void){

	map<string,InputDevice*>::iterator NameMapIterator;
	for(NameMapIterator = NameMap.begin(); NameMapIterator !=  NameMap.end();  NameMapIterator++){
		Destroy((*NameMapIterator).second);
	}
	NameMap.clear();
}

/**
* @brief	sends InputDevice to garbage
* @param	void
* @return	void
*/
void MAUI::InputDevice::Trash(void){

	State = DISABLED;
	InactiveQueue.push(this);
}

/**
* @brief	Iterates through all InputDevices, executes process
* @param	void
* @return	void
*/
void MAUI::InputDevice::Update(void){

	//Windows Message Pump Modified for games
	/*	
	MSG Message;

	if( PeekMessage( &Message, NULL, 0, 0, PM_NOREMOVE ) ){
		if( !GetMessage( &Message, NULL, 0, 0 ) ){
			//return Message.wParam;
		}
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
*/

	//iterate through active InputDevices
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
		(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive InputDevices
	while (!InactiveQueue.empty()){
		ActiveList.remove(InactiveQueue.front());
		Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::InputDevice::Process(void){

	switch(State){

		case DISABLED:
			break;

		case ACTIVE:
			AxisQuery();
			ContactQuery();
			break;

	}

}

/**
* @brief	Queries input InputDevice axis based on type; stores query in axis/Contact buffer
* @param	void
* @return	void
*/
void MAUI::InputDevice::AxisQuery(void){

	switch(Type){

		case MAUI_INPUTDEVICE_TYPE_MOUSE:
			Axis.x = (float)dbMouseX();
			Axis.y = (float)dbMouseY();
			Axis.z = (float)dbMouseZ();
			break;

		case MAUI_INPUTDEVICE_TYPE_JOYSTICK:
			Axis.x = (float)dbJoystickX();
			Axis.y = (float)dbJoystickY();
			Axis.z = (float)dbJoystickZ();
			break;

		case MAUI_INPUTDEVICE_TYPE_JOYSTICK_360:
			break;

		case MAUI_INPUTDEVICE_TYPE_JOYSTICK_WII:
			break;

		case MAUI_INPUTDEVICE_TYPE_INPUTDEVICE:
			Axis.x = (float)dbControlDeviceX();
			Axis.y = (float)dbControlDeviceY();
			Axis.z = (float)dbControlDeviceZ();
			break;

	}

}

/**
* @brief	queries input InputDevice contacts based on type; stores query in axis/Contact buffer
* @param	void
* @return	void
*/
void MAUI::InputDevice::ContactQuery(void){

	ContactExist = 0;

	switch(Type){

		case MAUI_INPUTDEVICE_TYPE_MOUSE:
			Contact = dbMouseClick();
			if(Contact){
				//contactqueue.push(Contact);
				ContactExist = Contact;
			}
			break;

		case MAUI_INPUTDEVICE_TYPE_JOYSTICK:
			for(int loop=0;loop<32;loop++){
				Contact = dbJoystickFireX(loop);
				if(Contact){
					//contactqueue.push(Contact);
					ContactExist = Contact;
				}
			}
			break;

		case MAUI_INPUTDEVICE_TYPE_JOYSTICK_360:
			break;

		case MAUI_INPUTDEVICE_TYPE_JOYSTICK_WII:
			break;

		case MAUI_INPUTDEVICE_TYPE_INPUTDEVICE:
			break;

		case MAUI_INPUTDEVICE_TYPE_KEYBOARD:
			Contact = dbScanCode();
			if(Contact){
				//contactqueue.push(Contact);
				ContactExist = Contact;
			}
			break;

	}
}

// BODY //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Body Constructor
* @param	void
*/
MAUI::Body::Body(void){

	Type = CollisionExist = 0;
	CollideFlag = PhysicsFlag = GravityFlag = PathfinderFlag = 0;
	Position.x = Position.y = Position.z = Size.x = Size.y = Size.z = Angle.x = Angle.y = Angle.z = 0;
	Physics = NULL;
}

/**
* @brief	Body Constructor
* @param	void
* @return	void
*/
MAUI::Body::Body(float x, float y, float z, float width, float height, float depth, float anglex, float angley, float anglez){

	Type = MAUI_BODY_TYPE_3D;
	CollisionExist = 0;
	CollideFlag = PhysicsFlag = GravityFlag = PathfinderFlag = 0;

	Position.x = x;
	Position.y = y;
	Position.z = z;

	Size.x = width;
	Size.y = height;
	Size.z = depth;

	Angle.x = anglex;
	Angle.y = angley;
	Angle.z = anglez;

	Physics = NULL;
}

/**
* @brief	Body Destructor
* @param	void
* @return	void
*/
MAUI::Body::~Body(void){

}

/**
* @brief	Create Body
* @param	int type - Body Type: 0=2D, 1=3D
* @param	int physicstype - 
* @param	int objectID - objectID used to select Collision Object Shape based on mesh
* @param	float x
* @param	float y
* @param	float z
* @param	float width
* @param	float height
* @param	float depth
* @param	float anglex
* @param	float angley
* @param	float anglez
* @return	Body*
*/
MAUI::Body* MAUI::Body::Create(int type, int physicstype, int objectID, float x, float y, float z, float width, float height, float depth, float anglex, float angley, float anglez){
	
	Body *instance = new Body(x, y, z, width, height, depth, anglex, angley, anglez);

	instance->Type = type;

	switch(physicstype){

		case -1: break;

		case MAUI_BODY_PHYSICS2D_TYPE_WORLD:
			instance->Physics = new CanvasPhysics2D;
			//instance->Physics->Create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping);
			break;

		case MAUI_BODY_PHYSICS2D_TYPE_JOINT_MOUSE:
			instance->Physics = new PointerPhysics2D;
			//instance->Physics->Create(string canvasname);
			break;

		case MAUI_BODY_PHYSICS2D_TYPE_BODY:
		case MAUI_BODY_PHYSICS2D_TYPE_JOINT_DISTANCE:
		case MAUI_BODY_PHYSICS2D_TYPE_JOINT_REVOLUTE:
		case MAUI_BODY_PHYSICS2D_TYPE_JOINT_PRISMATIC:
		case MAUI_BODY_PHYSICS2D_TYPE_JOINT_PULLEY:
		case MAUI_BODY_PHYSICS2D_TYPE_JOINT_GEAR:
			instance->Physics = new GizmoPhysics2D;
			//instance->Physics->Create(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor);
			break;

		//3D
		case MAUI_BODY_PHYSICS3D_TYPE_GROUNDPLANE:
		case MAUI_BODY_PHYSICS3D_TYPE_BOX:
		case MAUI_BODY_PHYSICS3D_TYPE_SPHERE:
		case MAUI_BODY_PHYSICS3D_TYPE_CAPSULE:
		case MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESHFROMDBO:
		case MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESH:
		case MAUI_BODY_PHYSICS3D_TYPE_CONVEXMESH:
		case MAUI_BODY_PHYSICS3D_TYPE_BOXSHAPE:
		case MAUI_BODY_PHYSICS3D_TYPE_SPHERESHAPE:
		case MAUI_BODY_PHYSICS3D_TYPE_CONVEXSHAPE:
		case MAUI_BODY_PHYSICS3D_TYPE_COMPOUNDACTOR:
		case MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERBOX:
		case MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERCAPSULE:
			instance->Physics = new GizmoPhysics3D;
			//instance->Physics->Set(int type, bool dynamic, float density, float maxstep, float slopelimit, float radius, bool yoffset, float length, float sizex, float sizey, float sizez);
			//instance->Physics->Create(int objectID);
			break;

	}

	if(instance->Physics != NULL) {
		instance->Physics->Type = physicstype;
		instance->PhysicsFlag = true;
	}

	return(instance);
}

/**
* @brief	Destroy Body Instance
* @param	void
* @return	void
*/
void MAUI::Body::Destroy(MAUI::Body* instance){

	delete instance->Physics;
	delete instance;
}

/**
* @brief	Centers Body based on Canvas centeroffeset
* @param	void
* @return	void
*/
void MAUI::Body::Center(string canvasname){

	if(Canvas::NameMap[canvasname] == NULL){
		Output = "Canvas `";
		Output.append(canvasname);
		Output.append("` Not Defined for Body Center.");
		alertbox("MAUI ERROR",Output,ALERTBOX_SEVERITY_ERROR);
	}
	
	Position.x *= Canvas::NameMap[canvasname]->ZoomFactor.x + Canvas::NameMap[canvasname]->CenterOffset.x;
	Position.y *= Canvas::NameMap[canvasname]->ZoomFactor.y + Canvas::NameMap[canvasname]->CenterOffset.y;

}

/**
* @brief	Zoom Body based on Canvas ZoomFactor
* @param	string canvasname
* @return	void
*/
void MAUI::Body::Zoom(string canvasname){

	if(Canvas::NameMap[canvasname] == NULL){
		Output = "Canvas `";
		Output.append(canvasname);
		Output.append("` Not Defined for Body Zoom.");
		alertbox("MAUI ERROR",Output,ALERTBOX_SEVERITY_ERROR);
	}

	Size.x *= Canvas::NameMap[canvasname]->ZoomFactor.x;
	Size.y *= Canvas::NameMap[canvasname]->ZoomFactor.y;

}

/**
* @brief	auto orientates based on reference Gizmo
			uses position for a offset if align > 0
* @param	string refgizmoname
* @param	float x
* @param	float y
* @param	float z
* @param	int xalign
* @param	int yalign
* @param	int zalign
* @return	void
*/
void MAUI::Body::Orientate(string refgizmoname, float x, float y, float z, int xalign, int yalign, int zalign){

	Gizmo *refgizmo = Gizmo::Reference(refgizmoname);

	Position.x = x;
	Position.y = y;
	Position.z = z;

	//if no dimensions copy ref's
	if(Size.x==0){Size.x = refgizmo->Body->Size.x;}
	if(Size.y==0){Size.y = refgizmo->Body->Size.y;}
	if(Size.x==0){Size.z = refgizmo->Body->Size.z;}

	if((yalign || zalign) && !xalign){xalign = MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL;}
	if((xalign || zalign) && !yalign){yalign = MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL;}
	if((xalign || yalign) && !zalign){zalign = MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL;}

	//auto alignment
	switch(xalign){

		case MAUI_BODY_ORIENTATE_XALIGN_LEFT:
			Position.x += refgizmo->Body->Position.x - Size.x;
			break;

		case MAUI_BODY_ORIENTATE_XALIGN_CENTER:
			Position.x += refgizmo->Body->Position.x;
			break;

		case MAUI_BODY_ORIENTATE_XALIGN_RIGHT:
			Position.x += refgizmo->Body->Position.x + refgizmo->Body->Size.x;
			break;
			
	}

	switch(yalign){

		case MAUI_BODY_ORIENTATE_YALIGN_TOP:
			Position.y += refgizmo->Body->Position.y - Size.y;
			break;

		case MAUI_BODY_ORIENTATE_YALIGN_MIDDLE:
			Position.y += refgizmo->Body->Position.y;
			break;

		case MAUI_BODY_ORIENTATE_YALIGN_BOTTOM:
			Position.y += refgizmo->Body->Position.y + refgizmo->Body->Size.y;
			break;
		
	}

	switch(zalign){

		case MAUI_BODY_ORIENTATE_ZALIGN_FRONT:
			Position.z += refgizmo->Body->Position.z - Size.z;
			break;

		case MAUI_BODY_ORIENTATE_ZALIGN_NEUTRAL:
			Position.z += refgizmo->Body->Position.z;
			break;

		case MAUI_BODY_ORIENTATE_ZALIGN_BACK:
			Position.z += refgizmo->Body->Position.z + Size.z;
			break;

	}

}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Body *MAUI::Body::Copy(void){

	Body *instance = new Body(Position.x, Position.y, Position.z, Size.x, Size.y, Size.z, Angle.x, Angle.y, Angle.z);
	
	//settings
	instance->Type = Type; 
	instance->CollideFlag = CollideFlag;
	instance->PhysicsFlag = PhysicsFlag;
	instance->GravityFlag = GravityFlag;
	instance->PathfinderFlag = PathfinderFlag;

	return(instance);

}

// BODY::CanvasPhysics2D ////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
*/
MAUI::Body::CanvasPhysics2D::CanvasPhysics2D(void){

	WorldAABB.lowerBound.x = WorldAABB.lowerBound.y = 0;
	World = NULL;
	AllowSleep = false;
	Gravity.x = Gravity.y = Gravity.z = 0;
	TimeStep = 0;
	Iterations = 0;

}

/**
* @brief	Destructor
* @param	void
* @return	void
*/
MAUI::Body::CanvasPhysics2D::~CanvasPhysics2D(void){

}

/**
* @brief	 
* @param	void
* @return	void
*/
void MAUI::Body::CanvasPhysics2D::Create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping ){

	WorldAABB.lowerBound.Set(position.x,position.y);
	WorldAABB.upperBound.Set(size.x/b2PixelRatio, size.y/b2PixelRatio);

	// Define the gravity vector.
	Gravity.x = gravityx;
	Gravity.y = gravityy;

	// Do we want to let bodies sleep?
	//allowsleep

	// Construct a World object, which will hold and simulate the rigid bodies.
	World = new b2World(WorldAABB, (b2Vec2&)Gravity, allowsleeping);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	TimeStep = timestep;
	Iterations = iterations;
	AllowSleep = allowsleeping;

}

/**
* @brief	Destroy Physics
* @param	void
* @return	void
*/
void MAUI::Body::CanvasPhysics2D::Destroy(void){

	delete World;

}

/**
* @brief	Rturn b2World Pointer
* @param	void
* @return	b2World Pointer
*/
b2World* MAUI::Body::CanvasPhysics2D::WorldGet(void){

	return (World);
}

/**
* @brief	Create Body on Canvas
* @param	void
* @return	void
*/
b2Body* MAUI::Body::CanvasPhysics2D::BodyCreate(const b2BodyDef bodydef){

	return(World->CreateBody(&bodydef));

}

/**
* @brief	Update
* @param	void
* @return	void
*/
void MAUI::Body::CanvasPhysics2D::Update(void){

	World->Step(TimeStep,Iterations);
}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Body::PhysicsAbstract *MAUI::Body::CanvasPhysics2D::Copy(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping ){

	CanvasPhysics2D *instance = new CanvasPhysics2D;
	instance->Create(position, size, gravityx, gravityy, timestep, iterations, allowsleeping);
	return(instance);
}

// BODY::GizmoPhysics2D ////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Body::GizmoPhysics2D::GizmoPhysics2D(void){

	ShapeTypeDef = 0;
	DynamicBody = NULL;
}

/**
* @brief	Destructor
* @param	void
* @return	void
*/
MAUI::Body::GizmoPhysics2D::~GizmoPhysics2D(){

}
	
/**
* @brief	Create Box2D Physics Body & Shape
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics2D::Create(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){

	if(Canvas::NameMap[canvasname] == NULL){
		Output = "Canvas `";
		Output.append(canvasname);
		Output.append("` Not Defined for Gizmo Physics");
		alertbox("MAUI ERROR",Output,ALERTBOX_SEVERITY_ERROR);
	}

	// Define the dynamic Body. 
	BodyDef.position.Set((position.x + (size.x/2.0f)) /b2PixelRatio, (position.y + (size.y/2.0f)) /b2PixelRatio);
	
	//BodyDef.massData.mass = 2.0f;   // the Body's mass in kg
	//BodyDef.Center.SetZero();       // the center of mass in local coordinates
	//BodyDef.I = 3.0f;               // the rotational inertia in kg*m^2.
	//BodyDef.linearDamping = 0.0f;
	//BodyDef.angularDamping = 0.01f;
	//BodyDef.allowSleep = true;
	//BodyDef.isBullet = true;

	//select default Canvas
	World = Canvas::NameMap[canvasname]->Body->Physics->WorldGet();

	//We set its position and call the Body factory.
	DynamicBody = World->CreateBody(&BodyDef);

	// Define another box shape for our dynamic Body.
	ShapeDef.SetAsBox((size.x/b2PixelRatio)/2.0f, (size.y/b2PixelRatio)/2.0f);

	// Set the box density to be non-zero, so it will be dynamic.
	ShapeDef.density = density;

	// Override the default friction.
	ShapeDef.friction = friction;

	ShapeDef.restitution = restitution;

	ShapeDef.isSensor = sensor;

	// Add the shape to the Body.
	DynamicBody->CreateShape(&ShapeDef);

	// Now tell the dynamic Body to compute it's mass properties base
	// on its shape.
	DynamicBody->SetMassFromShapes();

}

/**
* @brief	Destroy
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics2D::Destroy(void){

	World->DestroyBody(DynamicBody);

}

/**
* @brief	update Physics sim
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics2D::Update(D3DVECTOR &position, D3DVECTOR &angle){

	angle.z = (float)DynamicBody->GetAngle();
	angle.z *= (float)(180.0 / 3.141592653589793238);
	position = (D3DVECTOR&)DynamicBody->GetPosition();
	position.x *= b2PixelRatio; //MeterToPixel conversion
	position.y *= b2PixelRatio;

}

/**
* @brief	store user Pointer for circular reference
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics2D::UserDataSet(void* userPTR){

	BodyDef.userData = userPTR;

}

/**
* @brief	returns user Pointer
* @param	void
* @return	void
*/
void *MAUI::Body::GizmoPhysics2D::UserDataGet(void){

	return(BodyDef.userData);

}

/**
* @brief	Set the position of the Body's origin and rotation (radians). 
			this breaks any contacts and wakes the other bodies. 
			returns false if out of boundary
* @param	void
* @return	void
*/
bool MAUI::Body::GizmoPhysics2D::OrientationSet(b2Vec2 position, float32 angle){

	position.x /= b2PixelRatio;
	position.y /= b2PixelRatio;

	return(DynamicBody->SetXForm(position, angle));
}
	
/**
* @brief	Create Box2D Physics Body & Shape
* @param	void
* @return	void
*/
MAUI::Body::PhysicsAbstract *MAUI::Body::GizmoPhysics2D::Copy(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){

	GizmoPhysics2D *instance = new GizmoPhysics2D;
	instance->Create(canvasname, shapetype, position, size, angle, density, friction, restitution, sensor);
	return(instance);

}


// BODY::PointerPhysics2D ////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Body::PointerPhysics2D::PointerPhysics2D(){
 
	World = NULL;
	MouseJoint = NULL;

}

/**
* @brief	Destructor
* @param	void
* @return	void
*/
MAUI::Body::PointerPhysics2D::~PointerPhysics2D(){

}


/**
* @brief	Create Box2D Physics Body & Shape
* @param	void
* @return	void
*/
void MAUI::Body::PointerPhysics2D::Create(string canvasname){

	World = Canvas::NameMap[canvasname]->Body->Physics->WorldGet();
}

/**
* @brief	Create Box2D Physics Body & Shape
* @param	void
* @return	void
*/
void MAUI::Body::PointerPhysics2D::Destroy(void){

	if(MouseJoint != NULL){
		World->DestroyJoint(MouseJoint);
	}

}

/**
* @brief	Update Physics Simulation
* @param	void
* @return	void
*/
void MAUI::Body::PointerPhysics2D::Update(b2Vec2 p, int actionstate){

	//pixel to meter
	p.x /= b2PixelRatio;
	p.y /= b2PixelRatio;

	//movement
	if(MouseJoint){
		MouseJoint->SetTarget(p);
	}

	switch(actionstate){

		case 0: //up
			if (MouseJoint){
				World->DestroyJoint(MouseJoint);
				MouseJoint = NULL;
			}
			break;

		case MAUI_INPUTDEVICE_MOUSE_BUTTON_LEFT: //down
			if (MouseJoint != NULL){
				return;
			}

			World = Canvas::BaseCanvas->Body->Physics->WorldGet();
			
			// Create a small box.
			b2AABB aabb;
			b2Vec2 d;
			d.Set(0.001f, 0.001f);
			aabb.lowerBound = p - d;
			aabb.upperBound = p + d;

			// Query the World for overlapping shapes.
			const int32 k_maxCount = 10;
			b2Shape* shapes[k_maxCount];
			int32 count = World->Query(aabb, shapes, k_maxCount);
			b2Body* dynamicbody = NULL;

			for (int32 i = 0; i < count; ++i){
				b2Body* shapebody = shapes[i]->GetBody();
				if(shapebody->IsStatic() == false && shapebody->GetMass() > 0.0f){
					bool inside = shapes[i]->TestPoint(shapebody->GetXForm(), p);
					if (inside){
						dynamicbody = shapes[i]->GetBody();
						break;
					}
				}
			}

			if (dynamicbody){
				b2MouseJointDef md;
				md.body1 = World->GetGroundBody();
				md.body2 = dynamicbody;
				md.target = p;
//#ifdef TARGET_FLOAT32_IS_FIXED
//				md.maxForce = (Body->GetMass() < 16.0) ? (1000.0f * Body->GetMass()) : float32(16000.0);
//#else
				md.maxForce = 1000.0f * dynamicbody->GetMass();
//#endif
				MouseJoint = (b2MouseJoint*)World->CreateJoint(&md);
				dynamicbody->WakeUp();
			}

			break;
	}

}

/**
* @brief	Create Box2D Physics Body & Shape
* @param	void
* @return	void
*/
MAUI::Body::PhysicsAbstract *MAUI::Body::PointerPhysics2D::Copy(string canvasname){

	PointerPhysics2D *instance = new PointerPhysics2D;
	instance->Create(canvasname);
	return(instance);
}


// BODY::GizmoPhysics3D ////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
*/
MAUI::Body::GizmoPhysics3D::GizmoPhysics3D(void){

	Type = 0;
	Dynamic = false;
	Density = 10;
	MaxStep = 0;
	SlopeLimit = 0;
	Radius = 1.0f;
	YOffset = 0;
	Length = 1.0f;
	SizeX = 1.0f;
	SizeY = 1.0f;
	SizeZ = 1.0f;

}

/**
* @brief	Destructor
* @param	void
*/
MAUI::Body::GizmoPhysics3D::~GizmoPhysics3D(){

}

/**
* @brief	Create Box3D Physics Body & Shape
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics3D::Create(int objectID){

	switch(Type){

		case MAUI_BODY_PHYSICS3D_TYPE_GROUNDPLANE:
			Core->Physics->makeGroundPlane();
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_BOX:
			Core->Physics->makeBox(objectID, Dynamic, Density);
			if(Dynamic) Core->Physics->setKinematicOn(objectID); 
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_SPHERE:
			Core->Physics->makeSphere(objectID, Dynamic, Density);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_CAPSULE:
			Core->Physics->makeCapsule(objectID, Dynamic, Density, Radius, Length);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESHFROMDBO:
			Core->Physics->makeTriangleMeshFromDBO(objectID);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESH:
			Core->Physics->makeTriangleMesh(objectID);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_CONVEXMESH:
			Core->Physics->makeConvexMesh(objectID, Dynamic, Density);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_BOXSHAPE:
			Core->Physics->makeBoxShape(objectID);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_SPHERESHAPE:
			Core->Physics->makeSphereShape(objectID);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_CONVEXSHAPE:
			Core->Physics->makeConvexShape(objectID);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_COMPOUNDACTOR:
			Core->Physics->makeCompoundActor(objectID, Dynamic, Density);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERBOX:
			Core->Physics->makeControllerBox(objectID, MaxStep, SlopeLimit, YOffset);
			//Core->Physics->makeControllerBox(objectID, MaxStep, SlopeLimit, SizeX, SizeY, SizeZ);
			break;

		case MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERCAPSULE:
			Core->Physics->makeControllerCapsule(objectID, MaxStep, SlopeLimit, YOffset);
			//Core->Physics->makeControllerCapsule(objectID, MaxStep, SlopeLimit, Radius, Length);
			break;
	}


}

/**
* @brief	Destroy Physics
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics3D::Destroy(void){
}

/**
* @brief	update Physics sim
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics3D::Update(void){

}

/**
* @brief	store user Pointer for circular reference
* @param	void
* @return	void
*/
void MAUI::Body::GizmoPhysics3D::UserDataSet(void* userPTR){

}

/**
* @brief	returns user Pointer
* @param	void
* @return	void
*/
void *MAUI::Body::GizmoPhysics3D::UserDataGet(void){

	return(NULL);

}

/**
* @brief	Set Physics values
* @param	void
* @return	void
*/void MAUI::Body::GizmoPhysics3D::Set(int type, bool dynamic, float density, float maxstep, float slopelimit, float radius, bool yoffset, float length, float sizex, float sizey, float sizez){

	Type = type;
	Dynamic = dynamic;
	Density = density;
	MaxStep = maxstep;
	SlopeLimit = slopelimit;
	Radius = radius;
	YOffset = yoffset;
	Length = length;
	SizeX = sizex;
	SizeY = sizey;
	SizeZ = sizez;

}

/**
* @brief	Create Box3D Physics Body & Shape
* @param	void
* @return	void
*/
MAUI::Body::PhysicsAbstract *MAUI::Body::GizmoPhysics3D::Copy(int objectID){

	GizmoPhysics3D *instance = new GizmoPhysics3D;
	instance->Create(objectID);
	return(instance);

}

// CANVAS //////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::Canvas*> MAUI::Canvas::NameMap;
map<string,MAUI::Canvas*>::iterator MAUI::Canvas::NameMapIterator;
list<MAUI::Canvas*> MAUI::Canvas::ActiveList;
list<MAUI::Canvas*>::iterator MAUI::Canvas::ActiveListIterator;
queue<MAUI::Canvas*> MAUI::Canvas::InactiveQueue;

/**
* @brief	Canvas Constructor
* @param	void
* @return	void
*/
MAUI::Canvas::Canvas(void){

	Name = Description = "";

	Type = 0;
	dbCameraID = -1;
	FOV = NearRange = FarRange = Aspect = 0;
	BackdropFlag = 0;
	DWORD BackdropColor = 0;
	BackdropImageID = 0;

	ZoomFactor.x = ZoomFactor.y = ZoomFactor.z = 1.0;
	CenterOffset.x = CenterOffset.y = CenterOffset.z = 0;
	ListenerScale.x = ListenerScale.y = ListenerScale.z = 1.0;

	Body = NULL;
	InputDevice = NULL;

}

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Canvas::Canvas(string name, string description = ""){
	
	this->Name = name;
	this->Description = description;

	Type = 0;
	dbCameraID = -1;
	FOV = NearRange = FarRange = Aspect = 0;
	BackdropFlag = 0;
	DWORD BackdropColor = 0;
	BackdropImageID = 0;

	ZoomFactor.x = ZoomFactor.y = ZoomFactor.z = 1.0;
	CenterOffset.x = CenterOffset.y = CenterOffset.z = 0;
	ListenerScale.x = ListenerScale.y = ListenerScale.z = 1.0;

	Body = NULL;
	InputDevice = NULL;

}

/**
* @brief	Canvas Destructor
* @param	void
* @return	void
*/
MAUI::Canvas::~Canvas(void){
}
	
/**
* @brief	Creates Canvas by name
* @param	void
* @return	MAUI::Canvas object Pointer
*/
MAUI::Canvas *MAUI::Canvas::Create(string parentname, string name, string description, int dbCameraID, float FOV, float nearrange, float farrange, float aspect, bool backdropflag, DWORD backdropcolor, int backdropimageID){

	if(NameMap[name] == NULL){
		CurrentCanvas = new Canvas(name, description);
        NameMap[name] = CurrentCanvas;
	} else {
		CurrentCanvas = NameMap[name];
	}

	CurrentCanvas->Description = description;
	CurrentCanvas->dbCameraID = dbCameraID;
	CurrentCanvas->FOV = FOV;
	CurrentCanvas->NearRange = nearrange;
	CurrentCanvas->FarRange = farrange;
	CurrentCanvas->Aspect = aspect;
	CurrentCanvas->BackdropFlag = backdropflag;
	CurrentCanvas->BackdropColor = backdropcolor;
	CurrentCanvas->BackdropImageID = backdropimageID;
	
	if(backdropcolor) dbColorBackdrop(backdropcolor);
	if(backdropimageID) dbTextureBackdrop(backdropimageID);

	ActiveList.push_back(CurrentCanvas);
	CurrentCanvas->State = ACTIVE;

	return(CurrentCanvas);
}
	
/**
* @brief	Destroys Canvas by Pointer
* @param	void
* @return	MAUI::Canvas object Pointer
*/
void MAUI::Canvas::Destroy(MAUI::Canvas *instance){

	//Destroy Body & Physics
	if(instance->Body != NULL){
		if(instance->Body->Physics != NULL){
			instance->Body->Physics->Destroy();
			delete instance->Body->Physics;
		}
		delete instance->Body;
	}

	if(instance->dbCameraID){
		dbDeleteCamera(instance->dbCameraID);
		dbCameraResource->Push(instance->dbCameraID);
	}

	delete instance;
}

/**
* @brief	destroys all Canvas (except 0)
* @param	void
* @return	void
*/
void MAUI::Canvas::Destroy(void){

	map<string,Canvas*>::iterator NameMapIterator;
	for(NameMapIterator = NameMap.begin(); NameMapIterator !=  NameMap.end();  NameMapIterator++){
		Destroy((*NameMapIterator).second);
	}
	NameMap.clear();

}
	
/**
* @brief	sends Canvas to garbage
* @param	void
* @return	void
*/
void MAUI::Canvas::Trash(void){

	State = DISABLED;
	InactiveQueue.push(this);

}

/**
* @brief	Return Canvas Pointer by name
* @param	string name
* @return	Canvas*
*/
MAUI::Canvas* MAUI::Canvas::Get(string name){

	if(NameMap[name] == NULL){ 
		NameMap[name] = new Canvas(name, "tbd");
	}
	return(NameMap[name]);

}

/**
* @brief	Canvas
* @param	void
* @return	void
*/
void MAUI::Canvas::Set(void){

}

/**
* @brief	Iterates through all Canvass, executes process
* @param	void
* @return	void
*/
void MAUI::Canvas::Update(void){

	//iterate through active Canvases
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
			(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive Canvass
	while (!InactiveQueue.empty()){	
		ActiveList.remove(InactiveQueue.front());
		Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Canvas::Process(void){

	switch(State){

		case ACTIVE:
			if(Body != NULL){
				if(Body->PhysicsFlag){
					Body->Physics->Update();
				}
			}
			break;
	}

}

/**
* @brief	calculate 2D Gizmo Screen Zoom
* @param	void
* @return	void
*/
void MAUI::Canvas::Zoom(float zoomfactorx, float zoomfactory){

	zoomfactorx == 0 ? ZoomFactor.x = dbScreenWidth()/Body->Size.x : ZoomFactor.x = zoomfactorx;
	zoomfactory == 0 ? ZoomFactor.y = dbScreenHeight()/Body->Size.y : ZoomFactor.y = zoomfactory;

	CenterOffset.x = dbScreenWidth()/2.0f - (Body->Size.x * ZoomFactor.x)/2.0f; 
	CenterOffset.y = dbScreenHeight()/2.0f - (Body->Size.y * ZoomFactor.y)/2.0f;
}

/**
* @brief	Translates 3D Vector to Screen Point
* @param	D3DVECTOR &position
* @return	void
*/
void MAUI::Canvas::ScreenPositionGet(D3DXVECTOR3 &position, int &x, int &y){

	// camera ptr
	CameraData* Camera = (CameraData*)dbGetCameraInternalData(dbCameraID);

	// get current camera transformation matrices
	D3DXMATRIX matTransform = Camera->matView * Camera->matProjection;

	// Transform object position from world-space to screen-space
	D3DXVec3TransformCoord(&position, &position, &matTransform);

	// Screen data
	x=(int)((position.x+1.0f)*(dbScreenWidth()/2.0f));
	y=(int)((1.0f-position.y)*(dbScreenHeight()/2.0f));

	// leefix - 280305 - adjust coordinates using viewport of the target camera
	float fVPWidth = Camera->viewPort3D.Width;
	float fVPHeight = Camera->viewPort3D.Height;
	float fRealX = ( fVPWidth / dbScreenWidth() ) * (x);
	float fRealY = ( fVPHeight / dbScreenHeight() ) * (y);
	x = fRealX + Camera->viewPort3D.X;
	y = fRealY + Camera->viewPort3D.Y;
	
}


// SPRITE ///////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Sprite Constructor
* @param	void
* @return	void
*/
MAUI::Sprite::Sprite(void){

	Type = dbImageID = dbObjectID = BackdropImageID = IconImageID = CaptionType = 0;
	StartFrame = StopFrame = CurrentFrame = 0;

	CaptionStyle = NULL;
	Caption = CaptionView = "";
	CaptionPosition.x = CaptionPosition.y = CaptionPosition.z = 0;
	CaptionSize.x = CaptionSize.y = CaptionSize.z = 0;

	BackdropTheme = NULL;
	BackdropImageAlign.x = BackdropImageAlign.y = BackdropImageAlign.z = 0;
	SnapshotFlag = false;

	IconTheme = NULL;
	IconImageAlign.x = IconImageAlign.y = IconImageAlign.z = 0;

	VisibleFlag = LODFlag = false;

}

/**
* @brief	Sprite Destructor
* @param	void
* @return	void
*/
MAUI::Sprite::~Sprite(void){

}

/**
* @brief	Create Sprite
* @param	int spritetype
* @param	string spritesourcefile
* @return	Sprite*
*/
MAUI::Sprite* MAUI::Sprite::Create(int spritetype, string sourcefilename){

	Sprite *instance = new Sprite;

	instance->Type = spritetype;

	switch(instance->Type){

		case S3GE_OBJECT_TYPE_2D:

			if(sourcefilename.find(".") == string::npos) instance->BackdropImageID = (int)dbVal((char*)sourcefilename.data());
			
			if(instance->BackdropImageID && dbImageExist(instance->BackdropImageID)){
				
				//deliberate blank

			} else {
			
				switch(int fileexists = Core->File->Exist(sourcefilename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

					case S3GE_FILE_FOUND:
						instance->BackdropImageID = dbImageResource->Add(sourcefilename);
						if(!dbImageExist(instance->BackdropImageID)){
							Core->Image->Create(instance->BackdropImageID, S3GE_IMAGE_TYPE_STATIC, sourcefilename, S3GE::File::GET_FROM_LOCAL|S3GE::File::GET_FROM_NETWORK);
						}
						break;
				}

			}
			break;

	}

	return instance;
}

/**
* @brief	Create Sprite
* @param	int spritetype
* @param	string backdropfilename
* @param	string objectfilname
* @param	Body *body 
* @param	Theme *theme 
* @param	Style *style
* @param	Object *object
* @return	Sprite*
*/
MAUI::Sprite* MAUI::Sprite::Create(int spritetype, string backdropfilename, MAUI::Theme *theme, MAUI::Style *style, S3GE::Object *object, MAUI::Body *body){			

	Sprite *instance = new Sprite;

	instance->Type = spritetype;

	//background
	if(!backdropfilename.empty()){

		int backdropimageID = 0;
		if(backdropfilename.find(".") == string::npos) backdropimageID = (int)dbVal((char*)backdropfilename.data());
		if(backdropimageID && dbImageExist(backdropimageID)){
			instance->BackdropImageID = backdropimageID;
		} else {
	
			switch(int fileexists = Core->File->Exist(backdropfilename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){
				case S3GE_FILE_FOUND:
					instance->BackdropImageID = dbImageResource->Add(backdropfilename);
					if(!dbImageExist(instance->BackdropImageID)){
						Core->Image->Create(instance->BackdropImageID, S3GE_IMAGE_TYPE_STATIC, backdropfilename, S3GE::File::GET_FROM_LOCAL|S3GE::File::GET_FROM_NETWORK);
					}
					break;
			}
		}

	}

	//Theme
	if(theme != NULL){
		instance->BackdropTheme = theme;
	} else {
		//assign default
		instance->BackdropTheme =Theme::DefaultTheme;
	}

	//Style
	if(style != NULL){
		instance->CaptionStyle = style;
	} else {
		//assign default
		instance->CaptionStyle = Style::DefaultStyle;
	}
		
	//Display Object
	if(object != 0){
		instance->dbObjectID = object->ID;
	} else {
		instance->dbObjectID = dbObjectResource->Pop();
		if(!dbObjectExist(instance->dbObjectID)){
			dbMakeObjectPlain(instance->dbObjectID, 1.0, 1.0);
			dbSetObject(instance->dbObjectID, 1, 0, 0, 0, 0, 0, 0);
		}
	}

	//texture
	dbTextureObject(instance->dbObjectID, instance->BackdropImageID);

	if(body != NULL){

		switch(instance->Type){

			case S3GE_OBJECT_TYPE_2D:
				break;

			case S3GE_OBJECT_TYPE_MESH:

				//scale
				//dbScaleObject(instance->dbObjectID, body->Size.x, body->Size.y, body->Size.z);
							
				//position
				dbPositionObject(instance->dbObjectID, body->Position.x, body->Position.y, body->Position.z);

				//rotation	
				dbRotateObject(instance->dbObjectID, body->Angle.x, body->Angle.y, body->Angle.z);
							
				//physics
				if(body->PhysicsFlag) body->Physics->Create(instance->dbObjectID);

				break;
		}
	}


	return(instance);

}

/**
* @brief	Destroy Sprite
* @param	Sprite *instance
* @return	if successful returns NULL
*/
MAUI::Sprite* MAUI::Sprite::Destroy(MAUI::Sprite *instance){

	if(instance != NULL){
		delete instance;
		return NULL;
	}

	return instance;
}

/**
* @brief	Draw Image 
* @param	string filename
* @param	framesacross = frames across, used for animated Sprite
* @param	framesdown = frames down
* @return	int
*/
int MAUI::Sprite::ImageLoad(string filename, int framesacross=1, int framesdown=1){
	
	StartFrame = framesacross;
	StopFrame = framesdown;

	return(0);
}

/**
* @brief	Draw on Sprite Image based Theme,Icon,Caption
* @param	void
* @return	void
*/
int MAUI::Sprite::ImageDraw(MAUI::Body *body, int actionstate){

	if(!dbImageID){return(0);}

	//Draw Backdrop
	if(BackdropImageID){
		dbPasteImage(BackdropImageID,(int)BackdropImageAlign.x,(int)BackdropImageAlign.y);
	}

	//Draw Backdrop Theme
	if(BackdropTheme != NULL && BackdropTheme->EventAction[actionstate] != NULL){
		BackdropTheme->EventAction[actionstate]->Draw(body->Size);
		//Execute Theme Script
		if(BackdropTheme->EventAction[actionstate]->Task != NULL){
			//DarkLUA::System::PointerSet("this",(Theme*)BackdropTheme);
			BackdropTheme->EventAction[actionstate]->Task->Execute(DarkLUA::Task::RUNNING);
		}
	}

	//Draw Icon Theme
	if(IconTheme != NULL && IconTheme->EventAction[actionstate] != NULL){
		IconTheme->EventAction[actionstate]->Draw(body->Size,(int)IconImageAlign.x,(int)IconImageAlign.y);
		//Execute Theme Script
		if(IconTheme->EventAction[actionstate]->Task != NULL){
			//DarkLUA::System::PointerSet("this",(Theme*)IconTheme);
			IconTheme->EventAction[actionstate]->Task->Execute(DarkLUA::Task::RUNNING);
		}
	}

	//Draw Icon
	if(IconImageID){
		dbPasteImage(IconImageID,(int)IconImageAlign.x,(int)IconImageAlign.y);
	}

	//Draw Caption
	if(CaptionStyle != NULL){

		//set Caption
		string captiontext;

		switch(CaptionType){

			case MAUI_SPRITE_CAPTION_TYPE_STANDARD:
				captiontext = Caption;
				break;

			case MAUI_SPRITE_CAPTION_TYPE_PASSWORD:
				//captiontext.insert(0,Caption.length(),"*");
				break;
		}

		//select ttf, bitmapfont, mesh
		if(CaptionStyle->EventAction[actionstate] != NULL && CaptionType != MAUI_SPRITE_CAPTION_TYPE_HIDDEN){

			switch(CaptionStyle->EventAction[actionstate]->Type){

				case MAUI_STYLE_FONT_TYPE_DX9FONT:
					Core->Text->FontSet(CaptionStyle->EventAction[actionstate]->FontID);
					//draw Caption
					CaptionSize.x = Core->Text->WidthGet(captiontext);
					CaptionSize.y = Core->Text->HeightGet(captiontext);
					Core->Text->Print((int)CaptionPosition.x, (int)CaptionPosition.y,(char*)captiontext.data());
					break;

				case MAUI_STYLE_FONT_TYPE_FONTART:
					CaptionStyle->EventAction[actionstate]->FontArtSet();
					//draw Caption
					CaptionSize.x = Core->FontArtText->WidthGet(captiontext);
					CaptionSize.y = Core->FontArtText->HeightGet(captiontext);
					Core->FontArtText->Draw((int)CaptionPosition.x, (int)CaptionPosition.y, captiontext);
					break;
			}	
		}

		//Execute Style Script
		if(CaptionStyle->EventAction[actionstate]->Task != NULL){
			//DarkLUA::System::PointerSet("this",(Style*)CaptionStyle);
			CaptionStyle->EventAction[actionstate]->Task->Execute(DarkLUA::Task::RUNNING);
		}

	}

	return(1);
}
	
/**
* @brief	Captures Sprite Image
* @param	MAUI::Body *body
* @param	int actionstate
* @return	void
*/
int MAUI::Sprite::ImageCapture(MAUI::Body *body, int actionstate){

	if(!dbImageID) return(0);
	
	Core->Image->Create(dbImageID, S3GE_IMAGE_TYPE_RENDERTARGET, "", 0, (int)body->Size.x, (int)body->Size.y);
	Core->Image->Set(dbImageID);
	ImageDraw(body, actionstate);
	Core->Image->Reset();

	return(1);
}

/**
* @brief	Inheritor
* @param	void
* @return	void
*/
void MAUI::Sprite::Inherit(MAUI::Sprite *parent){

	Type = parent->Type;
	//dbImageID = parent->dbImageID;
	dbObjectID = parent->dbObjectID;
	StartFrame =  parent->StartFrame; 
	StopFrame =  parent->StopFrame; 
	CurrentFrame = parent->CurrentFrame;
	CaptionStyle = parent->CaptionStyle;
	CaptionType = parent->CaptionType;
	Caption =  parent->Caption; 
	CaptionView = parent->CaptionView;
	CaptionPosition = parent->CaptionPosition;
	BackdropTheme = parent->BackdropTheme;
	BackdropImageID = parent->BackdropImageID;
	BackdropImageAlign = parent->BackdropImageAlign;
	VisibleFlag = parent->VisibleFlag;
	LODFlag = parent->LODFlag;

}
	
/**
* @brief	Returns Text Width based on Caption Style font type
* @param	string data
* @return	int width
*/
int MAUI::Sprite::CaptionWidth(string text){

	int actionstate = 0;

	if(CaptionStyle->EventAction[actionstate] != NULL){

		switch(CaptionStyle->EventAction[actionstate]->Type){

			case MAUI_STYLE_FONT_TYPE_DX9FONT:
				return(Core->Text->WidthGet(text));
				break;

			case MAUI_STYLE_FONT_TYPE_FONTART:
				return(Core->FontArtText->WidthGet(text));
				break;
		}
	}
}
	
/**
* @brief	Returns Text Height based on Caption Style font type
* @param	string data
* @return	int height
*/
int MAUI::Sprite::CaptionHeight(string text){

	int actionstate = 0;

	if(CaptionStyle->EventAction[actionstate] != NULL){

		switch(CaptionStyle->EventAction[actionstate]->Type){

			case MAUI_STYLE_FONT_TYPE_DX9FONT:
				return(Core->Text->HeightGet(text));

			case MAUI_STYLE_FONT_TYPE_FONTART:
				return(Core->FontArtText->HeightGet(text));

		}
	}
}

/**
* @brief	Auto Orientates position based on size vs Body size
			uses position for a offset if align > 0
* @param	void
* @return	void
*/
void MAUI::Sprite::Orientate(MAUI::Body *body, D3DVECTOR &position, D3DVECTOR size, float x, float y, float z, int xalign, int yalign, int zalign){

	position.x = x;
	position.y = y;
	position.z = z;
	
	if((yalign || zalign) && !xalign){xalign = MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL;}
	if((xalign || zalign) && !yalign){yalign = MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL;}
	if((xalign || yalign) && !zalign){zalign = MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL;}

	//auto alignment
	switch(xalign){

		case MAUI_BODY_ORIENTATE_XALIGN_LEFT:
			position.x += 0;
			break;

		case MAUI_BODY_ORIENTATE_XALIGN_CENTER:
			position.x += (body->Size.x / 2.0f) - (size.x/2.0f);
			break;

		case MAUI_BODY_ORIENTATE_XALIGN_RIGHT:
			position.x += body->Size.x - size.x;
			break;
			
	}

	switch(yalign){

		case MAUI_BODY_ORIENTATE_YALIGN_TOP:
			position.y += 0;
			break;

		case MAUI_BODY_ORIENTATE_YALIGN_MIDDLE:
			position.y += (body->Size.y / 2.0f) - (size.y/2.0f);
			break;

		case MAUI_BODY_ORIENTATE_YALIGN_BOTTOM:
			position.y += body->Size.y - size.y;
			break;
		
	}

	/*
	switch(zalign){

		case MAUI_BODY_ORIENTATE_ZALIGN_FRONT:
			position.z += 0;
			break;

		case MAUI_BODY_ORIENTATE_ZALIGN_NEUTRAL:
			position.z += (body->Size.z / 2.0f) - (size.z/2.0f);
			break;

		case MAUI_BODY_ORIENTATE_ZALIGN_BACK:
			position.z += body->Position.z - size.z;
			break;

	}
	*/

}

/**
* @brief	Auto orientates Caption based on Body size
			uses position for a offset if align > 0
* @param	void
* @return	void
*/
void MAUI::Sprite::CaptionOrientate(MAUI::Body *body, float x, float y, float z, int xalign, int yalign, int zalign){

	D3DVECTOR size = {CaptionWidth(Caption), CaptionHeight(Caption), 0};
	Orientate(body, CaptionPosition, size, x, y, z, xalign, yalign, zalign);
}

/**
* @brief	Orientates Caption Images based on Body size
			uses position for a offset if align > 0
* @param	void
* @return	void
*/
void MAUI::Sprite::ImageOrientate(MAUI::Body *body, int imageID, D3DVECTOR &position, float x, float y, float z, int xalign, int yalign, int zalign){

	if(imageID < 1) return;
	if(!dbImageExist(imageID)) return;

	S3GE::Image *image = Core->Image->Get(imageID);
	D3DVECTOR size = {image->ImageInfo.Width, image->ImageInfo.Height, 0};
	Orientate(body, position, size, x, y, z, xalign, yalign, zalign);
}

/**
* @brief	Copy
* @param	void
* @return	void
*/
MAUI::Sprite *MAUI::Sprite::Copy(void){

	Sprite *instance = new Sprite;

	instance->Type = Type;
	//instance->dbImageID = dbImageID;
	//instance->dbObjectID = dbObjectID;
	//instance->StartFrame = StartFrame;
	//instance->StopFrame = StopFrame;
	//instance->CurrentFrame = CurrentFrame;
	instance->CaptionStyle = CaptionStyle;
	instance->CaptionType = CaptionType;
	instance->Caption = Caption;
	instance->CaptionView  = CaptionView ;
	instance->CaptionPosition = CaptionPosition;
	instance->CaptionSize = CaptionSize;
	instance->BackdropTheme = BackdropTheme;
	instance->BackdropImageID = BackdropImageID;
	instance->BackdropImageAlign = BackdropImageAlign;
	instance->IconTheme = IconTheme;
	instance->IconImageID = IconImageID;
	instance->IconImageAlign = IconImageAlign;
	instance->SnapshotFlag = SnapshotFlag;
	instance->VisibleFlag = VisibleFlag;
	instance->LODFlag = LODFlag;

	return(instance);

}


// GIZMO //////////////////////////////////////////////////////////////////////////////////////////
map<string,int> MAUI::Gizmo::PropertyNameMap;
map<string,int>::iterator MAUI::Gizmo::PropertyNameMapIterator;
map<string,MAUI::Gizmo*> MAUI::Gizmo::NameMap;
map<string,MAUI::Gizmo*>::iterator MAUI::Gizmo::NameMapIterator;
list<MAUI::Gizmo*> MAUI::Gizmo::ActiveList;
list<MAUI::Gizmo*>::iterator MAUI::Gizmo::ActiveListIterator;
queue<MAUI::Gizmo*> MAUI::Gizmo::InactiveQueue;

int MAUI::Gizmo::Index = -1;

/**
* @brief	Default Constructor
* @param	void
*/
MAUI::Gizmo::Gizmo(void){

	ID = Type = HTTPFileID = ParentalControlBitflag = SpriteID = Priority = 0;
	CollisionFlag = VisibleFlag = AudioFlag = ActiveFlag = OperateFlag = TransitFlag = false;
	ProcessBitflag = NONE;
	Name = Description = "";
	DebugFlag = false;
	Parent = First = Last = Previous = Next = NULL;
	Message = NULL;
	Body = NULL;
	ControllerType = MAUI_GIZMO_CONTROLLER_TYPE_PHYSICS;
	InputDevice = NULL;
	EventState.Clear();

}

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Gizmo::Gizmo(string name, string description=""){

	Name = name;
	Description = description;
	ID = Type = HTTPFileID = ParentalControlBitflag = SpriteID = Priority = 0;
	CollisionFlag = OperateFlag = TransitFlag = ActiveFlag = VisibleFlag = AudioFlag = false;
	ProcessBitflag = NONE;
	DebugFlag = false;
	Parent = First = Last = Previous = Next = NULL;
	Message = NULL;
	Body = NULL;
	ControllerType = MAUI_GIZMO_CONTROLLER_TYPE_PHYSICS;
	InputDevice = NULL;
	State = DISABLED;
	EventState.Clear();
}

/**
* @brief	Destructor
* @param	void
*/
MAUI::Gizmo::~Gizmo(void){

}

/**
* @brief	Creates new Gizmo
* @param	string parentname - name of parent Gizmo
* @param	string name - name for this Gizmo
* @param	string description - tooltip description
* @param	bool visible - starting visibility
* @param	bool collision - starting collision
* @return	Gizmo*
*/
MAUI::Gizmo* MAUI::Gizmo::Create(string parentname, string name, string description,  bool collisionflag, bool operateflag, bool transitflag, bool activeflag, bool visibleflag, bool audioflag){

	if(NameMap[name] == NULL){
		CurrentGizmo = new Gizmo(name, description);
        NameMap[name] = CurrentGizmo;
	}  else {
		CurrentGizmo = NameMap[name];
	}

	CurrentGizmo->FamilyAdd(NameMap[parentname]);
	CurrentGizmo->Inherit(NameMap[parentname]);

	CurrentGizmo->CollisionFlag =  collisionflag;
	CurrentGizmo->OperateFlag = operateflag;
	CurrentGizmo->TransitFlag = transitflag;
	CurrentGizmo->ActiveFlag = activeflag;
	CurrentGizmo->VisibleFlag = visibleflag;
	CurrentGizmo->AudioFlag = audioflag ;

	ActiveList.push_back(CurrentGizmo);
	CurrentGizmo->EventState.State = MAUI_EVENT_STATE_IDLE;
	CurrentGizmo->State = ACTIVE;

	return(CurrentGizmo);
}

/**
* @brief	Creates new Gizmo
* @param	string parentname - name of parent Gizmo
* @param	string name - name for this Gizmo
* @param	string description - tooltip description
* @param	DWORD processingbitflag - 
* @return	Gizmo*
*/
MAUI::Gizmo* MAUI::Gizmo::Create(string parentname, string name, string description, DWORD processbitflag){

	if(NameMap[name] == NULL){
		CurrentGizmo = new Gizmo(name, description);
        NameMap[name] = CurrentGizmo;
	}  else {
		CurrentGizmo = NameMap[name];
	}

	CurrentGizmo->FamilyAdd(NameMap[parentname]);
	CurrentGizmo->Inherit(NameMap[parentname]);

	CurrentGizmo->ProcessBitflag = processbitflag;
	CurrentGizmo->ProcessBitflag & COLLISION ? CurrentGizmo->CollisionFlag = true : CurrentGizmo->CollisionFlag = false;
	CurrentGizmo->ProcessBitflag & OPERATE ? CurrentGizmo->OperateFlag = true : CurrentGizmo->CollisionFlag = false;
	CurrentGizmo->ProcessBitflag & TRANSITION ? CurrentGizmo->TransitFlag = true : CurrentGizmo->CollisionFlag = false;
	CurrentGizmo->ProcessBitflag & ACTION ? CurrentGizmo->ActiveFlag = true : CurrentGizmo->CollisionFlag = false;
	CurrentGizmo->ProcessBitflag & VISIBLE ? CurrentGizmo->VisibleFlag = true : CurrentGizmo->CollisionFlag = false;
	CurrentGizmo->ProcessBitflag & AUDIBLE ? CurrentGizmo->AudioFlag = true : CurrentGizmo->CollisionFlag = false;

	ActiveList.push_back(CurrentGizmo);
	CurrentGizmo->EventState.State = MAUI_EVENT_STATE_IDLE;
	CurrentGizmo->State = ACTIVE;

	return(CurrentGizmo);
}
	
/**
* @brief	Destroys Gizmo by Pointer
* @param	Gizmo* object Pointer
* @return	void
*/
void MAUI::Gizmo::Destroy(MAUI::Gizmo *instance){

	//Destroy Body & Physics
	if(instance->Body != NULL){

		if(instance->Body->Physics != NULL){
			instance->Body->Physics->Destroy();
			delete instance->Body->Physics;
		}
		delete instance->Body;
	}

	//Destroy EventAction
	map<int, EventScript*>::iterator eventactioniterator;

	for(eventactioniterator = instance->EventAction.begin(); eventactioniterator !=  instance->EventAction.end();  eventactioniterator++){
		if((*eventactioniterator).second != NULL){

			if((*eventactioniterator).second->Sprite != NULL){

				switch(instance->Type){

					case MAUI_GIZMO_TYPE_GIZMO:
						if((*eventactioniterator).second->Sprite->dbImageID){
							//push to dbImageID potential orphan list?
							if(dbImageExist((*eventactioniterator).second->Sprite->dbImageID)){
								dbDeleteImage((*eventactioniterator).second->Sprite->dbImageID);
							}
							dbImageResource->Push((*eventactioniterator).second->Sprite->dbImageID);
						}
						break;

					case MAUI_GIZMO_TYPE_WIZMO:
						if((*eventactioniterator).second->Sprite->dbObjectID){
							//push to dbObjectID potential orphan list?
							if(dbObjectExist((*eventactioniterator).second->Sprite->dbObjectID)){
								dbDeleteObject((*eventactioniterator).second->Sprite->dbObjectID);
							}
							dbObjectResource->Push((*eventactioniterator).second->Sprite->dbObjectID);
						}
						break;
				}
				delete (*eventactioniterator).second->Sprite;
			}

			//delete task script if not shared
			if((*eventactioniterator).second->Task != NULL){
				if( !(*eventactioniterator).second->Task->Shared ) {
					delete (*eventactioniterator).second->Task;
				} else {
					(*eventactioniterator).second->Task->Shared--;
				}
			}

			delete (*eventactioniterator).second;
		}
	}

	instance->EventAction.clear();	

	//Destroy Sprite

	if(instance->Type == MAUI_GIZMO_TYPE_GIZMO){
		if(instance->SpriteID){
			if(dbSpriteExist(instance->SpriteID)){
				dbDeleteSprite(instance->SpriteID);
			}
			dbSpriteResource->Push(instance->SpriteID);
		}
	}

	delete instance;
}

/**
* @brief	Destroys All Gizmos
* @param	void
* @return	void
*/
void MAUI::Gizmo::Destroy(void){

	map<string,Gizmo*>::iterator NameMapIterator;
	for(NameMapIterator = NameMap.begin(); NameMapIterator != NameMap.end(); NameMapIterator++){
		if( (*NameMapIterator).second != NULL ){
			Destroy((*NameMapIterator).second);
		}
	}
	NameMap.clear();
}


/**
* @brief	sends Gizmo to garbage
* @param	void
* @return	void
*/
void MAUI::Gizmo::Trash(void){

	if(InactiveQueue.front()->Parent != NULL){
		InactiveQueue.front()->FamilyRemove();
	}

	State = DISABLED;
	InactiveQueue.push(this);
}

/**
* @brief	Return Pointer by name; if not available will Create Pointer
* @param	string name - Gizmo name
* @return	void
*/
MAUI::Gizmo *MAUI::Gizmo::Get(string name){
	
	if(NameMap[name] == NULL){ 
		return(NULL);
	}
	return(NameMap[name]);
}

/**
* @brief	Return Pointer by name; if not available will Create Pointer
* @param	string name - Gizmo name
* @return	void
*/
bool MAUI::Gizmo::Exist(string name){
	
	if(NameMap[name] == NULL){ 
		return(false);
	}
	return(true);
}
	
/**
* @brief	Copies Gizmo components.
* @param	void
* @return	void
*/
void MAUI::Gizmo::Inherit(MAUI::Gizmo *parent){

	if(parent == NULL) return;

	CollisionFlag = parent->CollisionFlag;
	VisibleFlag = parent->VisibleFlag;
	AudioFlag = parent->AudioFlag;
	ActiveFlag = parent->ActiveFlag;
 	TransitFlag = parent->TransitFlag;
	OperateFlag = parent->OperateFlag;
	//DebugFlag = parent->DebugFlag;

}
	
/**
* @brief	Generates a unique Copy of the Gizmo and all properties. Requires unique Name.
			Clone -	Creates an exact duplicate of Entity
			Copy -	Creates a unique Entity, copies over specified properties
			Mimic - Copies over property values to existing Entity from another
			Inherit - Copies over properties from a Parent Entity
			Instanced - Creates a duplicate with references to Originals properities
* @param	string name
* @param	string description
* @return	void
*/
MAUI::Gizmo *MAUI::Gizmo::Copy(string name, string description){

	//create gizmo copy instance
	Gizmo *instance = Create(Parent != NULL ? Parent->Name: "", name, description, CollisionFlag, OperateFlag, TransitFlag, ActiveFlag, VisibleFlag, AudioFlag);
	instance->Mimic(this);
	return(instance);
}

/**
* @brief	Generates a unique Copy of the Gizmo and all properties. Requires unique Name.
			Clone -	Creates an exact duplicate of Entity
			Copy -	Creates a unique Entity, copies over specified properties
			Mimic - Copies over property values to existing Entity from another
			Inherit - Copies over properties from a Parent Entity
			Instanced - Creates a duplicate with references to Originals properities
* @param	MAUI::Gizmo *instance - The gizmo* to mimic
* @return	void
*/
void MAUI::Gizmo::Mimic(MAUI::Gizmo *instance){

	//copy variables
	for(VariableMapIterator = instance->VariableMap.begin(); VariableMapIterator !=  instance->VariableMap.end();  VariableMapIterator++){
		VariableMap[(*VariableMapIterator).first] = (*VariableMapIterator).second;
	}

	//copy input device
	InputDevice = instance->InputDevice;
	ControllerType = instance->ControllerType;

	//copy body
	//if(Body!=NULL){
	//	Body = instance->Body->Copy();
	//}

	//copy eventactions
	map<int, EventScript*>::iterator eventactioniterator;
	for(eventactioniterator = instance->EventAction.begin(); eventactioniterator !=  instance->EventAction.end();  eventactioniterator++){
	
		if((*eventactioniterator).second != NULL){

			//create eventaction
			EventAction[(*eventactioniterator).first] = (*eventactioniterator).second->Copy();
		
/*
			//copy behevior
			EventAction[(*eventactioniterator).first]->Behavior = (*eventactioniterator).second->Behavior;

			//copy transition
			EventAction[(*eventactioniterator).first]->Transition = (*eventactioniterator).second->Transition;

			//copy scheme
			EventAction[(*eventactioniterator).first]->Scheme = (*eventactioniterator).second->Scheme;

			//copy sprite
			if((*eventactioniterator).second->Sprite != NULL){

				//create sprite
				EventAction[(*eventactioniterator).first]->Sprite = new Sprite;

				//copy style
				EventAction[(*eventactioniterator).first]->Sprite->CaptionStyle = (*eventactioniterator).second->Sprite->CaptionStyle;

				//copy theme
				EventAction[(*eventactioniterator).first]->Sprite->BackdropTheme = (*eventactioniterator).second->Sprite->BackdropTheme;

				//copy display object
				switch(Type){

					case MAUI_GIZMO_TYPE_GIZMO:

						//capture?
						break;

					case MAUI_GIZMO_TYPE_WIZMO:

						//capture?
						break;
				}

			}

			//copy task
			if((*eventactioniterator).second->Task != NULL){
				//replace gizmo names in scripts
				EventAction[(*eventactioniterator).first]->Task = (*eventactioniterator).second->Task;
			}
*/
		}
		
	}

}

/**
* @brief	Utility Method that Returns Gizmo Pointer based Relationships relative to CurrentGizmo 
* @param	string name
* @return	void
*/
MAUI::Gizmo *MAUI::Gizmo::Reference(string name){

	Gizmo *instance = NameMap[name];

	if(instance == NULL){

		if(name.compare("current") == 0){
			instance = CurrentGizmo;
		
		} else if(name.compare("previous") == 0){
			instance = CurrentGizmo->Previous;
		
		} else if(name.compare("parent") == 0) {
			instance = CurrentGizmo->Parent;

		} else if(name.compare("next") == 0){
			instance = CurrentGizmo->Next;

		} else if(name.compare("first") == 0){
			 instance = CurrentGizmo->First;

		} else if(name.compare("last") == 0){
			instance = CurrentGizmo->Last;
		
		} 
		
		if(instance == NULL) CurrentGizmo->Parent != NULL ? instance = CurrentGizmo->Parent : instance = BaseGizmo ;

	}

	return(instance);
}

/**
* @brief	Adds Gizmo to Family Tree
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilyAdd(MAUI::Gizmo *parent){

	if(parent != NULL){
		//parent
		this->Parent = parent;
		//first
		if(parent->First == NULL){
			parent->First = parent->Last = this;
		} else {
			//Siblings
			Previous = parent->Last;
			Next = parent->First;
			//parent Children
			parent->First->Previous = this;
			parent->Last->Next = this;
			parent->Last = this;
		}
	}
}

/**
* @brief	Removes Gizmo from Family Tree
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilyRemove(void){

	if(Parent != NULL && Parent != this){

		if(Parent->First != NULL){
			if(Parent->First == this){
				if(Previous != NULL){
					Parent->First = Previous;
				}
			}
		}

		if(Parent->Last != NULL){
			if(Parent->Last == this){
				if(Next != NULL){
					Parent->Last = Next;
				}
			}
		}

		if(Previous->Next != NULL){
			if(Previous->Next == this){
				if(Next != NULL){
					Previous->Next = Next;
				}
			}
		}

		if(Next->Previous != NULL){
			if(Next->Previous == this){
				if(Previous != NULL){
					Next->Previous = Previous;
				}
			}
		}

	}
}

/**
* @brief	Iterates through all gizmos, executes process
* @param	void
* @return	void
*/
void MAUI::Gizmo::Update(void){

	//iterate through active gizmos
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
		(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive gizmos
	while (!InactiveQueue.empty()){

		if(InactiveQueue.front()->ActiveFlag){
			ActiveList.remove(InactiveQueue.front());
		}
		Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::Process(void){

	switch(State){

		case DISABLED:
			break;

		case DRAW:
/*
			switch(type){
				case MAUI_GIZMO_TYPE_GIZMO:
					ImageCapture(MAUI_EVENT_STATE_IDLE);
					if(Body->PhysicsFlag){
						SpriteOffset();
					}
					break;
			}
			State = ACTIVE;
*/
			break;

		case ACTIVE:

			//message pump
			Pump();

			//controller
			Control();

			//collsion
			//ProcessBitflag & COLLISION
			if(CollisionFlag) Collision();

			//Debugging
			if(DebugFlag) Debug();

			//Behavior
			//ProcessBitflag & OPERATE
			if(OperateFlag) Operate();	

			//Transition
			//ProcessBitflag & TRANSITION
			if(TransitFlag)	Transit();

			//action
			//ProcessBitflag & ACTION
			if(ActiveFlag) Action();

			//audio
			//ProcessBitflag & AUDIBLE
			if(AudioFlag) Produce(); 

			//display
			//ProcessBitflag & VISIBLE
			if(VisibleFlag)	Display();

			break;

		case DOWNLOADING:
			break;

	}

}

/**
* @brief	Draws image and assigns to Sprite based on actionstate
			Sprite,Body,Theme,Style must preexist
* @param	void
* @return	void
*/
void MAUI::Gizmo::ImageCapture(int actionstate){

	if(!EventAction[actionstate]->Sprite->dbImageID){
		EventAction[actionstate]->Sprite->dbImageID = dbImageResource->Pop();
	}

	EventAction[actionstate]->Sprite->ImageCapture(
		Body,
		actionstate
	);
	
	dbSetSprite(SpriteID,0,1); //set Sprite;

	dbSprite(
		SpriteID,
		(int)Body->Position.x,
		(int)Body->Position.y,
		EventAction[actionstate]->Sprite->dbImageID
	);

	if(Body->PhysicsFlag){SpriteOffset();}

	dbHideSprite(SpriteID);

}

/**
* @brief	Draws image and assigns to object as texture based on actionstate
			Sprite,Body,Theme,Style must preexist
* @param	void
* @return	void
*/
void MAUI::Gizmo::TextureCapture(int actionstate){

	if(!EventAction[actionstate]->Sprite->dbImageID){
		EventAction[actionstate]->Sprite->dbImageID = dbImageResource->Pop();
	}
	
	EventAction[actionstate]->Sprite->ImageCapture(
		Body,
		actionstate
	);

	//texture object
	SpriteID = EventAction[actionstate]->Sprite->dbObjectID;
	dbTextureObject(SpriteID, EventAction[actionstate]->Sprite->dbImageID);
	
	//dbHideObject(SpriteID);
}

/**
* @brief	Capture Gizmo Image/Texture
			Sprite,Body,Theme,Style must preexist
* @param	void
* @return	void
*/
void MAUI::Gizmo::Capture(MAUI::Gizmo *instance, int actionstate){

	switch(instance->Type){

		case MAUI_GIZMO_TYPE_GIZMO:
			instance->ImageCapture(actionstate);
			break;

		case MAUI_GIZMO_TYPE_WIZMO:
			instance->TextureCapture(actionstate);
			break;
	}
}


/**
* @brief	Offsets Sprite for Box2D Physics
* @param	void
* @return	void
*/
void MAUI::Gizmo::SpriteOffset(void){

	dbOffsetSprite(
		SpriteID,
		(int)Body->Size.x/2,
		(int)Body->Size.y/2
	);

}

/**
* @brief	MAUI Message Pump
* @param	void
* @return	void
*/
void MAUI::Gizmo::Pump(void){

	while(MessageGet()){
		//message->translate();
		MessageProcess();
	}
}

/**
* @brief	Movement Controller
* @param	void
* @return	void
*/
void MAUI::Gizmo::Control(void){

	if (Body == NULL) return;

	switch(ControllerType){

		case	MAUI_GIZMO_CONTROLLER_TYPE_INPUTDEVICE:

			if (InputDevice == NULL) return;

			//Steering
			Body->Position.x = InputDevice->Axis.x;
			Body->Position.y = InputDevice->Axis.y;
			Body->Position.z = InputDevice->Axis.z;

			switch(InputDevice->Type){

				case MAUI_INPUTDEVICE_TYPE_MOUSE:
					if(Body->PhysicsFlag){
						Body->Physics->Update((b2Vec2&)Body->Position, InputDevice->Contact); //move
					}
					break;

				/*
				case  MAUI_INPUTDEVICE_TYPE_MANUAL: //manual position
					if(Body->PhysicsFlag){					
						Body->Position.x += Body->Size.x/2.0;
						Body->Position.y += Body->Size.y/2.0;
						Body->Physics->OrientationSet((b2Vec2&)Caret->Body->Position, Body->Angle);
						Body->Physics->Update(Body->Position, Body->Angle);
					}
					break;

			*/

			}
			break;
			
		case MAUI_GIZMO_CONTROLLER_TYPE_PHYSICS:
			if(Body->PhysicsFlag){
				if(Body->Physics != NULL) Body->Physics->Update(Body->Position, Body->Angle);
			}
			break;
	}
}

/**
* @brief	Collision Detection, Input Device Contact Collision Detection
* @param	void
* @return	void
*/
void MAUI::Gizmo::Collision(void){

	switch(Type){

		case MAUI_GIZMO_TYPE_WIDGET:
			//select InputDevice 
			//check axisqueue contactqueue for matching 'value' VariableMap
			//if no match flush queue
			if(InputDevice != NULL){
				switch(InputDevice->Type){

					case MAUI_INPUTDEVICE_TYPE_MOUSE:

						switch(InputDevice->ContactType){

							default:
								if(InputDevice->ContactExist == (int)dbVal((char*)VariableMap["value"].data()) ){
									InputDevice->ContactExist = InputDevice->Contact;
								} else {
									//InputDevice->ContactExist = 0;
								}	
								break;
						}
						break;

					case MAUI_INPUTDEVICE_TYPE_KEYBOARD:

						switch((int)dbVal((char*)VariableMap["keyfilter"].data())){ //InputDevice->ContactType)

							case 1: //filter none
								InputDevice->ContactExist = InputDevice->Contact;
								break;

							case 2: //filter inclusion - all scancodes are included
								if(InputDevice->Contact){
									InputDevice->ContactExist = 0;
									for(int loop = 0; loop < VariableMap["value"].size(); loop++){
										if( InputDevice->Contact == InputDevice::ScanCodeMap[VariableMap["value"].substr(loop,1)]){
											InputDevice->ContactExist = InputDevice->Contact;
											break;
										}
									}
								}
								break;

							case 3: //filter exclusion - all scancodes are excluded
								if(InputDevice->Contact){
									InputDevice->ContactExist = InputDevice->Contact;
									for(int loop = 0; loop < VariableMap["value"].size(); loop++){
										if( InputDevice->Contact == InputDevice::ScanCodeMap[VariableMap["value"].substr(loop,1)]){
											InputDevice->ContactExist = 0;
											break;
										}
									}
								}
								break;

							case 4: //filter fusion - scancodes in `key` variable are added scancode `value`
								break;
				
							default: //single key
								if(InputDevice->Contact == InputDevice::ScanCodeMap[VariableMap["value"]] ){
									InputDevice->ContactExist = InputDevice->Contact;
								} else {
									InputDevice->ContactExist = 0;
								}
								break;
						}
						break;
				}
			}
			break;

		case MAUI_GIZMO_TYPE_DOODAD:
		case MAUI_GIZMO_TYPE_GIZMO:

			switch(Body->Type){

				case 0: //box2d
					/*
					if(InputDevice != NULL){
					} else {
						//Physics collision reponse
						if(Body->PhysicsFlag){
							//do stuff
						}
					}
					*/

					if(this != Pointer){
						if(Pointer->Body->Position.x > Body->Position.x - (Body->Size.x/2.0) && Pointer->Body->Position.x < (Body->Position.x - (Body->Size.x/2.0)) + Body->Size.x && Pointer->Body->Position.y > Body->Position.y - (Body->Size.y/2.0) && Pointer->Body->Position.y < (Body->Position.y - (Body->Size.y/2.0)) + Body->Size.y){
							Body->CollisionExist = 1;
						} else {
							Body->CollisionExist = 0;
						}
					}
					break;

				case 1: //procedural
					//this vs Pointer
					if(this != Pointer){
						if(Pointer->Body->Position.x > Body->Position.x - (Body->Size.x/2.0) && Pointer->Body->Position.x < (Body->Position.x - (Body->Size.x/2.0)) + Body->Size.x
						&& Pointer->Body->Position.y > Body->Position.y - (Body->Size.y/2.0) && Pointer->Body->Position.y < (Body->Position.y - (Body->Size.y/2.0)) + Body->Size.y){
							Pointer->Body->CollisionQueue.push(Body);
						}
					}
					break;
			}
			break;

		case MAUI_GIZMO_TYPE_WIZMO:

			switch(Body->Type){

				case 1://reserved fulcrum collision
					break;
				
				case 0: //dgdk collision
					if(this != Pointer){
						//dbPickObject is slow need faster alternative
						if(dbPickObject( (int)Pointer->Body->Position.x, (int)Pointer->Body->Position.y, SpriteID, SpriteID) ){
							Body->CollisionExist = 1;
						} else {
							Body->CollisionExist = 0;
						}
					}
					break;
			}
			break;

	}
	
}

/**
* @brief	Select and Execute Behavior Script based on EventState.State
* @param	void
* @return	void
*/
void MAUI::Gizmo::Operate(void){

	if(EventAction[EventState.State] == NULL) return;

	if(EventAction[EventState.State]->Behavior != NULL){

		if(EventAction[EventState.State]->Behavior->EventAction[EventState.State] != NULL){

			if(EventAction[EventState.State]->Behavior->EventAction[EventState.State]->Task != NULL){

				//set PreviousState
				EventState.PreviousState = EventState.State;
				
				//set script globals based on type
				DarkLUA::System::PointerSet("this",(Gizmo*)this);
				DarkLUA::System::IntegerSet("uiGizmoEventState",EventState.State);

				switch(Type){

					case MAUI_GIZMO_TYPE_WIDGET:
						if(InputDevice != NULL){
							DarkLUA::System::IntegerSet("uiGizmoContact",InputDevice->ContactExist);
							DarkLUA::System::FloatSet("uiGizmoAxisX",InputDevice->Axis.x);
							DarkLUA::System::FloatSet("uiGizmoAxisY",InputDevice->Axis.y);
							DarkLUA::System::FloatSet("uiGizmoAxisZ",InputDevice->Axis.z);
						}
						break;

					default:
						DarkLUA::System::IntegerSet("uiPointerBound",Body->CollisionExist);
						if(Pointer != NULL) DarkLUA::System::IntegerSet("uiPointerContact",Pointer->InputDevice->ContactExist);
						break;
				}
				
				EventAction[EventState.State]->Behavior->EventAction[EventState.State]->Task->Execute(DarkLUA::Task::RUNNING);
				//get script globals
				EventState.State = DarkLUA::System::IntegerGet("uiGizmoNextEventState");

			}
		}
	}

}

/**
* @brief	Select and Execute Transisition Script based on EventState.State from previous
* @param	void
* @return	void
*/
void MAUI::Gizmo::Transit(void){

	/* debugging
	if(Name.compare("SFXEditObjectSoundFX")==0 && Body->CollisionExist == 1)
		Output.append("");
	*/

	if(EventAction[EventState.State] == NULL) return;

	if(EventState.State != EventState.TransitState){

		if(EventAction[EventState.State]->Transition != NULL){

			if(EventAction[EventState.State]->Transition->EventAction[EventState.State] != NULL){

				if(EventState.State != EventState.PreviousState){
					EventState.TransitState = EventState.PreviousState;
				}

				if(EventAction[EventState.State]->Transition->EventAction[EventState.State]->Task != NULL){
					//setup variables
						//set script globals
						DarkLUA::System::PointerSet("this",(Gizmo*)this);
						DarkLUA::System::IntegerSet("uiGizmoPreviousEventState",EventState.TransitState);
						EventAction[EventState.State]->Transition->EventAction[EventState.State]->Task->Execute(DarkLUA::Task::RUNNING);
						//get script globals
						EventState.TransitState = DarkLUA::System::IntegerGet("uiGizmoPreviousEventState");
				}
			}
		}
	}
}

/**
* @brief	Execute Action Script based on EventState.State
* @param	void
* @return	void
*/
void MAUI::Gizmo::Action(void){

	if(EventAction[EventState.State] == NULL) return;

	if(EventAction[EventState.State]->Task != NULL){

		DarkLUA::System::PointerSet("this",(Gizmo*)this);

		EventAction[EventState.State]->Task->Execute(DarkLUA::Task::RUNNING);
		
	}

}

/*
* @brief	Gizmo Audio Update
* @param	void
* @return	void
*/
void MAUI::Gizmo::Produce(void){

	if(EventAction[EventState.State] == NULL) return;

		if(EventAction[EventState.State]->Scheme != NULL){

			if(EventState.State != EventState.PreviousState){
				//turn off previous sound

				if(EventAction[EventState.PreviousState]->Scheme != NULL){

					if(EventAction[EventState.PreviousState]->Scheme->EventAction[EventState.PreviousState]!= NULL){

						switch(EventAction[EventState.PreviousState]->Scheme->EventAction[EventState.PreviousState]->System){

							case MAUI_SCHEME_AUDIO_SYSTEM_DGDK:
								
								switch(EventAction[EventState.PreviousState]->Scheme->EventAction[EventState.PreviousState]->Type){

									case MAUI_SCHEME_AUDIO_TYPE_SOUND:
										if(dbSoundPlaying(EventAction[EventState.PreviousState]->Scheme->EventAction[EventState.PreviousState]->AudioID)){
											dbStopSound(EventAction[EventState.PreviousState]->Scheme->EventAction[EventState.PreviousState]->AudioID);
										}
										break;

									case MAUI_SCHEME_AUDIO_TYPE_MUSIC:
										if(dbMusicPlaying(EventAction[EventState.PreviousState]->Scheme->EventAction[EventState.PreviousState]->AudioID)){
											dbStopMusic(EventAction[EventState.PreviousState]->Scheme->EventAction[EventState.PreviousState]->AudioID);
										}
										break;
								}
								break;
					
							case MAUI_SCHEME_AUDIO_SYSTEM_OAW:
								break;
						}

					}

				}
				//EventAction[EventState.State]->Scheme->EventAction[EventState.PreviousState]->Loopcount = 0;

			} else {

				//start new sound, if not playing
				if(EventAction[EventState.State]->Scheme->EventAction[EventState.State]!= NULL){

					//if(EventAction[EventState.State]->Scheme->EventAction[EventState.State]->Loopcount < EventAction[EventState.State]->Scheme->EventAction[EventState.State]->Loop){
						
						switch(EventAction[EventState.State]->Scheme->EventAction[EventState.State]->System){

							case MAUI_SCHEME_AUDIO_SYSTEM_DGDK:
								
								switch(EventAction[EventState.State]->Scheme->EventAction[EventState.State]->Type){

									case MAUI_SCHEME_AUDIO_TYPE_SOUND:
										if(!dbSoundPlaying(EventAction[EventState.State]->Scheme->EventAction[EventState.State]->AudioID)){
											dbPlaySound(EventAction[EventState.State]->Scheme->EventAction[EventState.State]->AudioID);
											//EventAction[EventState.State]->Scheme->EventAction[EventState.State]->Loopcount++;
										}
										break;

									case MAUI_SCHEME_AUDIO_TYPE_MUSIC:
										if(!dbMusicPlaying(EventAction[EventState.State]->Scheme->EventAction[EventState.State]->AudioID)){
											dbPlayMusic(EventAction[EventState.State]->Scheme->EventAction[EventState.State]->AudioID);
											//EventAction[EventState.State]->Scheme->EventAction[EventState.State]->Loopcount++;
										}
										break;
								}
								break;
					
							case MAUI_SCHEME_AUDIO_SYSTEM_OAW:
								break;
						}

					//}

				}

			}
			
		}

}

/**
* @brief	Gizmo Display Update
* @param	void
* @return	void
*/
void MAUI::Gizmo::Display(void){
	
	if(Body != NULL){

		switch(Type){

			case MAUI_GIZMO_TYPE_GIZMO:
				if(!SpriteID || !dbSpriteExist(SpriteID)) return;
				//switch Sprite image, if state has change and another image exists
				if(EventState.State != EventState.PreviousState){
					if(EventAction[EventState.State] != NULL){
						if(EventAction[EventState.State]->Sprite != NULL){
							if(EventAction[EventState.State]->Sprite->dbImageID){
								dbSetSpriteImage(SpriteID, EventAction[EventState.State]->Sprite->dbImageID);
							} else {
								//capture on the fly
								ImageCapture(EventState.State);
							}
						}
					}
				}

				//Display Sprite Object
				dbPasteSprite(SpriteID, (int)Body->Position.x, (int)Body->Position.y);
				dbRotateSprite(SpriteID, Body->Angle.z);//
				break;

			case MAUI_GIZMO_TYPE_WIZMO:
				//switch Sprite object, if State has change and another image exists
				if(EventState.State != EventState.PreviousState){
					if(EventAction[EventState.State] != NULL){
						if(EventAction[EventState.State]->Sprite != NULL){
							if(EventAction[EventState.State]->Sprite->dbObjectID){
								SpriteID = EventAction[EventState.State]->Sprite->dbObjectID;
								if(EventAction[EventState.State]->Sprite->BackdropTheme != NULL){
									if(EventAction[EventState.State]->Sprite->dbImageID){
										dbTextureObject(EventAction[EventState.State]->Sprite->dbObjectID,EventAction[EventState.State]->Sprite->dbImageID);
									} else {
										//capture texture on the fly
										TextureCapture(EventState.State);
									}
								}
							}
						}
					}
				}

				//Display Sprite Object											
				dbPositionObject(SpriteID, Body->Position.x, Body->Position.y, Body->Position.z);
				dbRotateObject(SpriteID, Body->Angle.x, Body->Angle.y, Body->Angle.z);

				//performance visibility/LOD
				if(dbObjectInScreen(SpriteID)){
					dbShowObject(SpriteID);
				}else{
					dbHideObject(SpriteID);
				}

				break;
		}
	}
}

/**
* @brief	Debug Visuals
* @param	void
* @return	void
*/
void MAUI::Gizmo::Debug(void){

	if(Body==NULL || VisibleFlag==false) return;

	if(Body->CollisionExist){					
		dbInk(D3DCOLOR_XRGB(0,255,0),0);
		Core->Text->ColorSet(0,255,0,255);
	} else {
		dbInk(D3DCOLOR_XRGB(255,0,0),0);
		Core->Text->ColorSet(255,0,0,255);
	}

	switch(Type){

		case MAUI_GIZMO_TYPE_DOODAD:
		case MAUI_GIZMO_TYPE_GIZMO:
			Core->Text->Print( (int)(Body->Position.x - (Body->Size.x/2.0)), (int)(Body->Position.y - (Body->Size.y/2.0)),(char*)Name.data());
			dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)), (int)(Body->Position.y - (Body->Size.y/2.0)), (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)(Body->Position.y - (Body->Size.y/2.0)));
			dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)(Body->Position.y - (Body->Size.y/2.0)), (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)(Body->Position.y - (Body->Size.y/2.0)) + (int)Body->Size.y);
			dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)(Body->Position.y - (Body->Size.y/2.0)) + (int)Body->Size.y, (int)(Body->Position.x - (Body->Size.x/2.0)), (int)(Body->Position.y - (Body->Size.y/2.0)) + (int)Body->Size.y);
			dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)), (int)(Body->Position.y - (Body->Size.y/2.0)) + (int)Body->Size.y, (int)(Body->Position.x - (Body->Size.x/2.0)) , (int)(Body->Position.y - (Body->Size.y/2.0)));
			break;

		case MAUI_GIZMO_TYPE_JIGGER:
		case MAUI_GIZMO_TYPE_WIZMO:
			
			if(Canvas::CurrentCanvas!=NULL){
				int x, y;
				Canvas::CurrentCanvas->ScreenPositionGet((D3DXVECTOR3)Body->Position, x, y);
				Core->Text->Print( x, y, (char*)Name.data());
				dbDot( x, y);
			}
			break;

	}

}


/**
* @brief	Add propertyname key
* @param	void
* @return	void
*/
void MAUI::Gizmo::PropertyAdd(string key,const int constant){

	if(!PropertyNameMap[key]){
		PropertyNameMap[key] = constant;
	}
}

/**
* @brief	Get property value based on keyname
* @param	Gizmo* gizmo
* @param	string key
* @return	char*
*/
char* MAUI::Gizmo::PropertyGet(MAUI::Gizmo* instance, string key, int actionstate){

	if(instance != NULL){
		
		switch(actionstate){
			case -1:
				actionstate = instance->EventState.State;
				break;
			case -2:
				actionstate = instance->EventState.PreviousState;
				break;
		}

		switch(PropertyNameMap[key]){

			case MAUI_GIZMO_PROPERTY_NAME:
				return((char*)instance->Name.data());

			case MAUI_GIZMO_PROPERTY_DESCRIPTION:
				return((char*)instance->Description.data());

			case MAUI_GIZMO_PROPERTY_CAPTION:
				return((char*)instance->EventAction[actionstate]->Sprite->Caption.data());

			case MAUI_GIZMO_PROPERTY_DEFAULTCAPTION:
				return((char*)instance->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->Caption.data());

			case MAUI_GIZMO_PROPERTY_EVENTSTATE_STATE:
				return(dbStr(instance->EventState.State));

			case MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNT:
				return(dbStr(instance->EventState.Count));

			case MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNTER:
				return(dbStr(instance->EventState.Counter));

			case MAUI_GIZMO_PROPERTY_BOUND_COLLISION:
				return(dbStr(instance->Body->CollisionExist));

			case MAUI_GIZMO_PROPERTY_BOUND_X:
				return(dbStr(instance->Body->Position.x));

			case MAUI_GIZMO_PROPERTY_BOUND_Y:
				return(dbStr(instance->Body->Position.y));

			case MAUI_GIZMO_PROPERTY_BOUND_Z:
				return(dbStr(instance->Body->Position.z));

			case MAUI_GIZMO_PROPERTY_BOUND_PITCH:
				return(dbStr(instance->Body->Angle.x));

			case MAUI_GIZMO_PROPERTY_BOUND_YAW:
				return(dbStr(instance->Body->Angle.y));

			case MAUI_GIZMO_PROPERTY_BOUND_ROLL:
				return(dbStr(instance->Body->Angle.z));

			case MAUI_GIZMO_PROPERTY_BOUND_WIDTH:
				return(dbStr(instance->Body->Size.x));

			case MAUI_GIZMO_PROPERTY_BOUND_HEIGHT:
				return(dbStr(instance->Body->Size.y));

			case MAUI_GIZMO_PROPERTY_BOUND_DEPTH:
				return(dbStr(instance->Body->Size.z));

			case MAUI_GIZMO_PROPERTY_BOUND_ORIENTATION:
				{
				string orientationstring;
				orientationstring.append(dbStr(instance->Body->Position.x));
				orientationstring.append(",");
				orientationstring.append(dbStr(instance->Body->Position.y));
				orientationstring.append(",");				
				orientationstring.append(dbStr(instance->Body->Position.z));
				orientationstring.append(",");
				orientationstring.append(dbStr(instance->Body->Angle.x));
				orientationstring.append(",");
				orientationstring.append(dbStr(instance->Body->Angle.y));
				orientationstring.append(",");				
				orientationstring.append(dbStr(instance->Body->Angle.z));
				return((char*)orientationstring.data());
				}
				break;

			case MAUI_GIZMO_PROPERTY_CONTACT_COLLISION:
				return(dbStr(instance->InputDevice->ContactExist));

			case MAUI_GIZMO_PROPERTY_AXIS_X:
				return(dbStr(instance->InputDevice->Axis.x));

			case MAUI_GIZMO_PROPERTY_AXIS_Y:
				return(dbStr(instance->InputDevice->Axis.y));

			case MAUI_GIZMO_PROPERTY_AXIS_Z:
				return(dbStr(instance->InputDevice->Axis.z));

			case MAUI_GIZMO_PROPERTY_SPRITE_OBJECT:
				return(dbStr(instance->SpriteID));
	
			case MAUI_GIZMO_PROPERTY_STATE:
				return(dbStr(instance->State));

		}

	}

	return("");
}

/**
* @brief	Set property value based on keyname
			DarkLUA Bind: `uiGizmoPropertySet`
* @param	void
* @return	void
*/
void MAUI::Gizmo::PropertySet(MAUI::Gizmo *instance, string key, char* value, int actionstate){

	if(instance != NULL){
		
		switch(actionstate){
			case -1:
				actionstate = instance->EventState.State;
				break;
			case -2:
				actionstate = instance->EventState.PreviousState;
				break;
		}

		switch(PropertyNameMap[key]){

			case MAUI_GIZMO_PROPERTY_DESCRIPTION:
				instance->Description = value;
				break;

			case MAUI_GIZMO_PROPERTY_CAPTION:
				instance->EventAction[actionstate]->Sprite->Caption = value;
				break;

			case MAUI_GIZMO_PROPERTY_DEFAULTCAPTION:
				instance->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->Caption = value;
				break;

			case MAUI_GIZMO_PROPERTY_EVENTSTATE_STATE:
				instance->EventState.State = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNT:
				instance->EventState.Count = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNTER:
				instance->EventState.Counter = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_COLLISION:
				instance->Body->CollisionExist = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_X:
				instance->Body->Position.x = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_Y:
				instance->Body->Position.y = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_Z:
				instance->Body->Position.z = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_WIDTH:
				instance->Body->Size.x = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_HEIGHT:
				instance->Body->Size.y = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_DEPTH:
				instance->Body->Size.z = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_PITCH:
				instance->Body->Angle.x = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_YAW:
				instance->Body->Angle.y = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_ROLL:
				instance->Body->Angle.z = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_BOUND_ORIENTATION:
				if((DWORD)dbVal(value) & 0x01) { 
					instance->Body->Physics->OrientationSet((b2Vec2&)instance->Body->Position, 0);
				}
				break;

			case MAUI_GIZMO_PROPERTY_CONTACT_COLLISION:
				instance->InputDevice->ContactExist = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_AXIS_X:
				instance->InputDevice->Axis.x = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_AXIS_Y:
				instance->InputDevice->Axis.y = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_AXIS_Z:
				instance->InputDevice->Axis.z = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_SPRITE_OBJECT:
				instance->SpriteID = dbVal(value);
				break;

			case MAUI_GIZMO_PROPERTY_STATE:
				instance->State = (GizmoStates)(int)dbVal(value);
				break;

		}

	}

}

/**
* @brief	DarkLUA Bind. Get Gizmo variable based on VariableMap key.
* @param	void
* @return	void
*/
char* MAUI::Gizmo::VariableGet(MAUI::Gizmo *instance, string variable){

	return((char*)instance->VariableMap[variable].data());
}

/**
* @brief	DarkLUABind. Set Gizmo variable based on VariableMap key
* @param	void
* @return	void
*/
void MAUI::Gizmo::VariableSet(MAUI::Gizmo *instance, string variable, string value){

	instance->VariableMap[variable] = value;
}


/**
* @brief	Set Gizmo Properties via Family Tree
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilyPropertySet(void){

    Gizmo *sibling = this;
    do {
		PropertySet(sibling,"","");
        if (sibling->First != NULL) { 
			sibling->First->FamilyPropertySet();
		}
        sibling = sibling->Next;
    } while(sibling != this || sibling != NULL);

}

/**
* @brief	Set Gizmo Sibling's Properties via Family Tree
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilySiblingPropertySet(bool subflag){
    Gizmo *sibling = this;
	do{
        PropertySet(sibling,"","");
        if (subflag) { 
			sibling->FamilyChildrenPropertySet(subflag);
		}
        sibling = sibling->Next;
	}while(!(sibling == this || sibling == NULL));
}

/**
* @brief	Set Gizmo Children's Properties via Family Tree
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilyChildrenPropertySet(bool subflag){

   Gizmo *child = First;
    if (child != NULL){
        do{
            //do stuff
            PropertySet(child,"","");
            if (subflag){ 
	    		child->FamilyChildrenPropertySet(subflag);
			}
			child = child->Next;
        }while(!(child == First || child == NULL));
    }
 
}

/**
* @brief	Assign Eventaction Property based ActionState
* @param	Gizmo* instance
* @param	int propertytype - Behavior,Transition,Theme
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Gizmo::Assign(MAUI::Gizmo* instance, int propertytype, void* propertyptr, int actionstate){

	if(instance->EventAction[actionstate] == NULL) instance->EventAction[actionstate] = new Gizmo::EventScript;

	switch(propertytype){

		case MAUI_GIZMO_ASSIGN_PROPERTY_BEHAVIOR://Behavior
			instance->EventAction[actionstate]->Behavior = (Behavior*)propertyptr;
			break;

		case MAUI_GIZMO_ASSIGN_PROPERTY_TRANSITION:	
			instance->EventAction[actionstate]->Transition = (Behavior*)propertyptr;
			break;

		case MAUI_GIZMO_ASSIGN_PROPERTY_BODY:
			instance->Body = (MAUI::Body*)propertyptr;
			break;

		case MAUI_GIZMO_ASSIGN_PROPERTY_SPRITE:
			instance->EventAction[actionstate]->Sprite = (Sprite*)propertyptr;
			break;

		case MAUI_GIZMO_ASSIGN_PROPERTY_THEME:
			if(instance->EventAction[actionstate]->Sprite != NULL) instance->EventAction[actionstate]->Sprite->BackdropTheme = (Theme*)propertyptr;
			break;

		case MAUI_GIZMO_ASSIGN_PROPERTY_STYLE:
			if(instance->EventAction[actionstate]->Sprite != NULL) instance->EventAction[actionstate]->Sprite->CaptionStyle = (Style*)propertyptr;
			break;

		case MAUI_GIZMO_ASSIGN_PROPERTY_SCHEME:
			instance->EventAction[actionstate]->Scheme = (Scheme*)propertyptr;
			break;
	}
}

/**
* @brief	Alias. Assign Eventaction Property based ActionState 
* @param	int propertytype - Behavior,Transition,Theme
* @param	void *propertyptr
* @param	int actionstate
* @return	void
*/
void MAUI::Gizmo::Assign(int propertytype, void *propertyptr, int actionstate){
	Assign(this, propertytype, propertyptr, actionstate);
}

// Hyper Actions /////////////////////////////////////////////////////////////

/**
* @brief	DarkLUABind Performance Test. Spin
* @param	MAUI::Gizmo *instance
* @param	float angle
* @return	void
*/
void MAUI::Gizmo::Spin(MAUI::Gizmo *instance, float angle){
	if(instance==NULL) return;
	instance->Body->Angle.x += angle;
	instance->Body->Angle.y += (int)angle * 2;
	instance->Body->Angle.z += (int)angle * 4;
}

/**
* @brief	DarkLUABind Performance Test. Color
* @param	MAUI::Gizmo *instance
* @param	float angle
* @return	void
*/
void MAUI::Gizmo::Color(MAUI::Gizmo *instance, int red, int green, int blue){
	if(instance==NULL) return;
	if(instance->EventAction[instance->EventState.State]==NULL) return;
	if(instance->EventAction[instance->EventState.State]->Sprite==NULL) return;
	if(!instance->EventAction[instance->EventState.State]->Sprite->dbObjectID) return;
	dbSetObjectDiffuse(instance->EventAction[instance->EventState.State]->Sprite->dbObjectID, (int)D3DCOLOR_XRGB(red,green,blue));
}



//line operations /////////////////////////////////////////////////////
/*
	Caret - Gizmo used that represents a text editing Caret
		Reserved Values:
		linestartposition - stores starting line number
		linestartcharacterposition - stores starting character in line
		linestopposition - stores stopping line number
		linestopcharacterposition - stores stopping character in line

	Gizmo
		Rserved Values:
		line - stored as a value using linenumber as key
		LineTextsection - stores trimmed left/right section 
		LineTextleftsection - store left section, split by Caret
		LineTextrightsection - stores right section, split by Caret
		linecount - stores number of lines
*/

//Caret operations

/**
* @brief	Binding Function. See LineCaretlocate definition.
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineCaretLocate(MAUI::Gizmo *instance, int caretmoveflag){

	instance->LineCaretLocate(caretmoveflag);
}


/**
* @brief	Sets Caret position, based on starting line and character.
			
			
			Note: MAUI reserves the use of Numbers as VariableMap Keys to store text strings as Line Buffers 
			(ie: VariableMap["1"] = "Hello World") in Gizmos. Assumes Body->CollisionExist = true.
			
			Other reserved VariableMap keys
				Gizmo:		
					"linecount" - holds number of lines
				Caret:
					"targetgizmo" - Gizmo name to focus on
					"linestartposition" - focus Gizmo line position (y)
					"linecstartharacterposition" - focus Gizmo line character position (x), starts in front of character
					"linestopposition" - focus Gizmo line position (y)
					"linestopcharacterposition" - focus Gizmo line character position (x), starts in front of character

* @param	void
* @return	void
*/
void MAUI::Gizmo::LineCaretSet(int linestartposition, int linestartcharacterposition, int caretmoveflag){

	bool linefound = false;
	int linecounter;
	float lineheight; //tallest character height
	float liney;
	float linecharacterx;
	float linecharacterwidth;

	if (Pointer != NULL && Caret != NULL){

		switch(Type){

			case MAUI_GIZMO_TYPE_GIZMO:

				if(!linestartposition){
					return;
				}

				liney = Body->Position.y - (Body->Size.y/2.0);

				for(linecounter=1; linecounter < linestartposition + 1; linecounter++){

					//determine line

					//total Caption character width / max font height
					lineheight = Core->Text->HeightGet(VariableMap[dbStr(linecounter)]); //tallest character height

					if(linecounter == linestartposition){

						linecharacterx = (Body->Position.x - (Body->Size.x/2.0));

						//determine character width & height
						for(int linecharactercounter=0; linecharactercounter < linestartcharacterposition + 1; linecharactercounter++){
							
							//dbTextWidth()
							string linecharacter = VariableMap[dbStr(linecounter)].substr(linecharactercounter,1);
							linecharacterwidth = Core->Text->WidthGet(linecharacter);

							//get character
							if( linecharactercounter == linestartcharacterposition){

								//determine front/rear position
								Caret->Body->Position.y = liney + (Caret->Body->Size.y/2.0);
								
								//position Caret in front
								Caret->Body->Position.x = linecharacterx + (Caret->Body->Size.x/2.0);

								//set Caret position
								Caret->Body->Physics->OrientationSet((b2Vec2&)Caret->Body->Position, 0);

								//set Caret values
								Caret->VariableMap["targetgizmo"] = Name;
								
								switch(caretmoveflag){

									case 1:
										Caret->VariableMap["linestartposition"] = dbStr(linecounter);
										Caret->VariableMap["linestartcharacterposition"] = dbStr(linecharactercounter);
										Caret->VariableMap["linestopposition"] = Caret->VariableMap["linestartposition"];
										Caret->VariableMap["linestopcharacterposition"] = Caret->VariableMap["linestartcharacterposition"];
										break;

									case 2:
										Caret->VariableMap["linestopposition"] = dbStr(linecounter);
										Caret->VariableMap["linestopcharacterposition"] = dbStr(linecharactercounter);
										break;

								}

								return;
								
							} else {

								//next character
								linecharacterx += linecharacterwidth;
							
							}
							
						}

						//Caret at end of line
						return;
							
					} else {

						//next line
						liney += lineheight;
							
					}

				}
				
				break;

			case MAUI_GIZMO_TYPE_WIZMO:
				break;
		}


	}

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineCaretGet(void){

}

/**
* @brief	Sets Caret position, based on Pointer position, relative characters in Caption
			Note: MAUI reserves the use of Numbers as VariableMap Keys to store text strings as Line Buffers 
			(ie: VariableMap["1"] = "Hello World") in Gizmos. Assumes Body->CollisionExist = true
 
			Other reserved VariableMap keys
				Gizmo:		
					"linecount" - holds number of lines
				Caret:
					"targetgizmo" - Gizmo name to focus on
					"linestartposition" - focus Gizmo line position (y)
					"linecstartharacterposition" - focus Gizmo line character position (x), starts in front of character
					"linestopposition" - focus Gizmo line position (y)
				"linestopcharacterposition" - focus Gizmo line character position (x), starts in front of character
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineCaretLocate(int caretmoveflag){
	

	int linecount;
	int linecounter;
	float lineheight; //tallest character height
	float liney;
	float linecharacterx;
	float linecharacterwidth;

	if (Pointer != NULL && Caret != NULL){

		switch(Type){

			case MAUI_GIZMO_TYPE_GIZMO:

				if(Body->CollisionExist){

					linecount = dbVal((char*)VariableMap["linecount"].data());

					if(!linecount){
						return;
					}

					liney = Body->Position.y - (Body->Size.y/2.0);

					for(linecounter=1; linecounter < linecount + 1; linecounter++){

						//determine line

						//total Caption character width / max font height
						lineheight = Core->Text->HeightGet(VariableMap[dbStr(linecounter)]); //tallest character height

						//character bounds collision with Pointer based on line y & height
						if(Pointer->Body->Position.y >= liney && Pointer->Body->Position.y <= liney + lineheight){

							linecharacterx = (Body->Position.x - (Body->Size.x/2.0));

							int linecharactercount = VariableMap[dbStr(linecounter)].size();

							//determine character width & height
							for(int linecharactercounter=0; linecharactercounter < linecharactercount; linecharactercounter++){
							
								//dbTextWidth()
								string linecharacter = VariableMap[dbStr(linecounter)].substr(linecharactercounter,1);
								linecharacterwidth = Core->Text->WidthGet(linecharacter);

								//Display (testing)
								//LineCaretDisplay(linecharacterx, linecharacterwidth, liney, lineheight, 0, 127, 127);
								
								//character bounds collision with Pointer based on character x & width
								if(Pointer->Body->Position.x >= linecharacterx && Pointer->Body->Position.x <= linecharacterx + linecharacterwidth){

									LineCaretDisplay(linecharacterx, linecharacterwidth, liney, lineheight, 255, 0, 0);

									if(caretmoveflag){

										//determine front/rear position
										Caret->Body->Position.y = liney + (Caret->Body->Size.y/2.0);
																			
										if(Pointer->Body->Position.x < linecharacterx + (linecharacterwidth/2.0)){

											//position Caret in front
											Caret->Body->Position.x = linecharacterx + (Caret->Body->Size.x/2.0);

										} else {
											
											//position Caret in rear
											Caret->Body->Position.x = linecharacterx + linecharacterwidth + (Caret->Body->Size.x/2.0);
											
											//increment character by one
											linecharactercounter++;

										}

										//set Caret position
										Caret->Body->Physics->OrientationSet((b2Vec2&)Caret->Body->Position, 0);

										//set Caret values
										Caret->VariableMap["targetgizmo"] = Name;
	
										switch(caretmoveflag){

											case 1:
												Caret->VariableMap["linestartposition"] = dbStr(linecounter);
												Caret->VariableMap["linestartcharacterposition"] = dbStr(linecharactercounter);
												Caret->VariableMap["linestopposition"] = Caret->VariableMap["linestartposition"];
												Caret->VariableMap["linestopcharacterposition"] = Caret->VariableMap["linestartcharacterposition"];
												break;

											case 2:
												Caret->VariableMap["linestopposition"] = dbStr(linecounter);
												Caret->VariableMap["linestopcharacterposition"] = dbStr(linecharactercounter);
												break;
										}
									
									}
									
									return;
								
								} else {

									//next character
									linecharacterx += linecharacterwidth;
							
								}
							
							}

							//Caret at end of line
							return;
							
						} else {

							//next line
							liney += lineheight;
							
						}

					}

				}
				
				break;

			case MAUI_GIZMO_TYPE_WIZMO:
				break;
		}

	}

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineCaretDisplay(float x, float width, float y, float height, int red, int green, int blue){

	dbInk(D3DCOLOR_XRGB(red,green,blue),0);
	dbLine( (int)x, (int)y, (int)x + (int)width, (int)y);
	dbLine( (int)x + (int)width, (int)y, (int)x + (int)width, (int)y + (int)height);
	dbLine( (int)x + (int)width, (int)y + (int)height, (int)x, (int)y + (int)height);
	dbLine( (int)x, (int)y + (int)height, (int)x , (int)y);

}
	
/**
* @brief
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineCaretEdit(MAUI::Gizmo *instance, int function){

	int lineposition = (int)dbVal( (char*)Caret->VariableMap["linestartposition"].data() );
	int linecharacterposition = (int)dbVal( (char*)Caret->VariableMap["linestartcharacterposition"].data() );

	MAUI::Gizmo *targetgizmo = NameMap[Caret->VariableMap["targetgizmo"]];

	int linecount = (int)dbVal((char*)targetgizmo->VariableMap["linecount"].data());
	
	switch(function){

		case 1: //Move Up
			if(lineposition > 1){ 
				lineposition--;
			}

			if(linecharacterposition > targetgizmo->VariableMap[dbStr(lineposition)].size()){ 
				linecharacterposition = targetgizmo->VariableMap[dbStr(lineposition)].size();
			}
			break;

		case 2: //Move Down
			if(lineposition < linecount){ 
				lineposition++;
			}

			if(linecharacterposition > targetgizmo->VariableMap[dbStr(lineposition)].size()){ 
				linecharacterposition = targetgizmo->VariableMap[dbStr(lineposition)].size();
			}
			break;

		case 3: //Move Left
			if(linecharacterposition > 0){ 
				linecharacterposition--;
			} else {
				if(lineposition > 1){ 
					lineposition--;
				}
				linecharacterposition = targetgizmo->VariableMap[dbStr(lineposition)].size();
			}
			break;

		case 4: //Move Right
			if(linecharacterposition < targetgizmo->VariableMap[dbStr(lineposition)].size()){ 
				linecharacterposition++;
			} else {
				if(lineposition < linecount){ 
					lineposition++;
				}
				linecharacterposition = 0;
			}
			break;

		case 5: //Move Top
			lineposition = 1;

			if(linecharacterposition > targetgizmo->VariableMap[dbStr(lineposition)].size()){ 
				linecharacterposition = targetgizmo->VariableMap[dbStr(lineposition)].size();
			}
			break;

		case 6: //Move Bottom
			lineposition = linecount;

			if(linecharacterposition > targetgizmo->VariableMap[dbStr(lineposition)].size()){ 
				linecharacterposition = targetgizmo->VariableMap[dbStr(lineposition)].size();
			}
			break;

		case 7: //Move Front
			linecharacterposition = 0;	
			break;

		case 8: //Move Rear
			linecharacterposition = targetgizmo->VariableMap[dbStr(lineposition)].size();
			break;

	}

	targetgizmo->LineCaretSet(lineposition,linecharacterposition,1);
}

//MAUI::Gizmo::line text operations

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextEdit(MAUI::Gizmo *instance, int function){

	MAUI::Gizmo *targetgizmo = NameMap[Caret->VariableMap["targetgizmo"]];
	
	switch(function){

		case 0: //Insert Text
			targetgizmo->LineTextInsert(dbEntry());
			break;

		case 1: //TBD
			break;

		case 2: //Enter
			targetgizmo->LineTextNew();
			break;

		case 3: //Delete Text
			targetgizmo->LineTextDelete();
			break;
			
		case 4: //Backspace
			LineCaretEdit(targetgizmo,3);
			targetgizmo->LineTextDelete();
			break;
			
		case 5: //Clear Text
			break;
	}

	//clear Entry Buffer
	dbClearEntryBuffer();

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextDisplay(MAUI::Gizmo *instance, int red, int green, int blue){


	if(!instance->VisibleFlag){
		return;
	}
	
	instance->LineTextDisplayAll(red, green, blue);
	instance->LineSelectionDisplay(72, 164, 190); //colors are temp
	
}
	
/**
* @brief	LineTextCapture Binding Wrapper (uiGizmoLinesCapture)
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextCapture(Gizmo* instance, int actionstate){

	instance->LineTextCapture(actionstate);
	
}
	
/**
* @brief	LineTextGet Binding Wrapper (uiGizmoLinesCopy)
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextCopy(string sourcegizmoname, string targetgizmoname){

	if(NameMap[sourcegizmoname]!=NULL||NameMap[targetgizmoname]==NULL) return;

	NameMap[sourcegizmoname]->LineTextCopy(NameMap[targetgizmoname]);

	
}
	
/**
* @brief	LineTextGet Binding Wrapper (uiGizmoLinesGet)
* @param	void
* @return	void
*/
string MAUI::Gizmo::LineTextGet(Gizmo *instance){

	return(instance->LineTextGet());
}

/**
* @brief	inserts new line, adjusts Caret
* @param	Gizmo* points to Gizmo in which function operates on
* @return	void
*/
void MAUI::Gizmo::LineTextNew(void){

	//split line between left/right halfs
	VariableMap["linetextleftsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr(0,(int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()));
	VariableMap["linetextsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr( (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()), VariableMap[ Caret->VariableMap["linestartposition"] ].size() - (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()) );
		
	//append carriage return
	VariableMap["linetextleftsection"].append(" \n");

	//currentsection = leftsection
	VariableMap[ Caret->VariableMap["linestartposition"] ] = VariableMap["linetextleftsection"];

	//shift all other lines
	LineTextShift((int)dbVal((char*)Caret->VariableMap["linestartposition"].data()), 1);

	//new line equals LineTextsection value
	VariableMap[ dbStr( dbVal((char*)Caret->VariableMap["linestartposition"].data()) + 1)  ] = VariableMap["linetextsection"];
			
	//update Caret start with first character position
	LineCaretSet((int)dbVal((char*)Caret->VariableMap["linestartposition"].data()) + 1, 0,1);

}

/**
* @brief	inserts text in line, adjusts Caret
* @param	Gizmo* points to Gizmo in which function operates on
* @return	void
*/
void MAUI::Gizmo::LineTextInsert(string text){


	//split line between left/right halfs
	VariableMap["linetextleftsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr(0,(int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()));
	VariableMap["linetextrightsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr( (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()), VariableMap[ Caret->VariableMap["linestartposition"] ].size() - (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()) );

	//append text to left
	VariableMap[ Caret->VariableMap["linestartposition"] ] = VariableMap["linetextleftsection"];
	VariableMap[ Caret->VariableMap["linestartposition"] ].append(text);
			
	//update Caret position based on left
	LineCaretSet( (int)dbVal((char*)Caret->VariableMap["linestartposition"].data()), VariableMap[ Caret->VariableMap["linestartposition"] ].size(), 1);

	//append right to left
	VariableMap[ Caret->VariableMap["linestartposition"] ].append(VariableMap["linetextrightsection"]);
	
	//wrap following lines down
	LineTextWrap((int)dbVal((char*)Caret->VariableMap["linestartposition"].data()), MAUI_GIZMO_VALUE_LINE_DIRECTION_RIGHT);

}

/**
* @brief	Deletes next character based on Caret location
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextDelete(void){
		
	//split line between left/right halfs
	VariableMap["linetextleftsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr(0,(int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()));
	VariableMap["linetextrightsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr( (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()), VariableMap[ Caret->VariableMap["linestartposition"] ].size() - (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()) );
		
	//remove text to right
	if(VariableMap["linetextrightsection"].size()){
		VariableMap["linetextrightsection"] = VariableMap["linetextrightsection"].substr(1,VariableMap["linetextrightsection"].size() - 1);
	}

	//if last character in line, shift up
	if(VariableMap["linetextrightsection"].empty()){
		int linenumber = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
		linenumber++;
		if(!VariableMap[dbStr(linenumber)].empty()){
			VariableMap["linetextrightsection"] = VariableMap[dbStr(linenumber)]; //next line
			//shift all lines upward
			LineTextShift(linenumber - 1, MAUI_GIZMO_VALUE_LINE_DIRECTION_UP);
		} else {
			//no more lines
			VariableMap["linetextrightsection"] = "";
		}

	}

	//append right to left
	VariableMap[ Caret->VariableMap["linestartposition"] ] = VariableMap["linetextleftsection"];
	VariableMap[ Caret->VariableMap["linestartposition"] ].append(VariableMap["linetextrightsection"]);

	//wrap following lines
	LineTextWrap((int)dbVal((char*)Caret->VariableMap["linestartposition"].data()), MAUI_GIZMO_VALUE_LINE_DIRECTION_RIGHT);
	
}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextClear(void){
		
	//split line between left/right halfs
	VariableMap["linetextleftsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr(0,(int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()));
	VariableMap["linetextrightsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr( (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()), VariableMap[ Caret->VariableMap["linestartposition"] ].size() - (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()) );
		
	//remove all text to right
	VariableMap["linetextrightsection"].clear();
			
	if(VariableMap["linetextrightsection"].empty()){
		int linenumber = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
		linenumber++;
		if(!VariableMap[dbStr(linenumber)].empty()){
			VariableMap["linetextrightsection"] = VariableMap[dbStr(linenumber)]; //next line
			//shift all lines upward
			LineTextShift(linenumber, MAUI_GIZMO_VALUE_LINE_DIRECTION_UP);
		} else {
			//no more lines
			VariableMap["linetextrightsection"] = "";
		}

	}

	//append right to left
	VariableMap[ Caret->VariableMap["linestartposition"] ] = VariableMap["linetextleftsection"];
	VariableMap[ Caret->VariableMap["linestartposition"] ].append(VariableMap["linetextrightsection"]);

	//wrap following lines
	LineTextWrap((int)dbVal((char*)Caret->VariableMap["linestartposition"].data()), MAUI_GIZMO_VALUE_LINE_DIRECTION_RIGHT);

}

/**
* @brief	split text in section based on Caret position
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextSplit(void){

	//split line between left/right halfs
	VariableMap["linetextleftsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr(0,(int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()));
	VariableMap["linetextrightsection"] = VariableMap[ Caret->VariableMap["linestartposition"] ].substr( (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()), VariableMap[ Caret->VariableMap["linestartposition"] ].size() - (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()) );

}

/**
* @brief	Trims of text length Left/Right based on specified width. Trimed text stored in LineTextsection value
			Auto word trim - Trims entire words based on delimiters
* @param	void
* @return	Trimmed string 
*/
string MAUI::Gizmo::LineTextTrim(int linenumber, int direction, float width){

	if( VariableMap[ dbStr(linenumber) ].size() == 0 ){
		return "";
	};

	string line = dbStr(linenumber);
	string delimiter = " -\n\t\v\r";
	int linecount = (int)dbVal((char*)VariableMap["linecount"].data() );
	VariableMap["linetextsection"].clear();

	switch(direction){

		case MAUI_GIZMO_VALUE_LINE_DIRECTION_LEFT:

			//linewidth > gizmowidth
			if(Core->Text->WidthGet(VariableMap[line]) > width){
				string templine = VariableMap[line];
				string templinesection;

				while(1){ //out of bounds trim
					
					templinesection.append(templine.substr(0,1)); //left
					templine = templine.substr(1,templine.size()); //right

					if(Core->Text->WidthGet(templine) <= width){

						string templine2 = templine;
						string templinesection2 = templinesection;

						while(1){ //auto word trim

							templinesection.append(templine.substr(0,1)); //left
							templine = templine.substr(1,templine.size()); //right

							if(!templine.empty()){
								//locate delimiter
								if( delimiter.find( templine.substr(0,1)) != string::npos ){
									VariableMap["linetextsection"] = templinesection;
									VariableMap[line] = templine;
									return templinesection; 
								}
							} else {
								//if no delimiter found
								VariableMap["linetextsection"] = templinesection2;
								VariableMap[line] = templine2;
								return templinesection2;
							}
						}
						break;

					}
				}
			}
			break;

	case MAUI_GIZMO_VALUE_LINE_DIRECTION_RIGHT:

		//linewidth > gizmowidth
		if(Core->Text->WidthGet(VariableMap[line]) > width){

			string templine = VariableMap[line];
			string templinesection;

			while(1){ //out of bounds trim
						
				templinesection.insert(0,templine.substr(templine.size() - 1,1)); //right
				templine = templine.substr(0,templine.size() - 1); //left

				if(Core->Text->WidthGet(templine) <= width){

					string templine2 = templine;
					string templinesection2 = templinesection;

					while(1){ //auto word trim

						templinesection.insert(0,templine.substr(templine.size() - 1,1)); //right
						templine = templine.substr(0,templine.size() - 1); //left

						if(!templine.empty()){
							//locate delimiter
							if( delimiter.find( templine.substr(templine.size() - 1,1) ) != string::npos ){
								VariableMap["linetextsection"] = templinesection;
								VariableMap[line] = templine;
								return templinesection; 
							}
						} else {
							//if no delimiter found
							VariableMap["linetextsection"] = templinesection2;
							VariableMap[line] = templine2;
							return templinesection2;
						}
					}
					break;

				}
			}
		}
		break; 
	}

	return "";
}

/**
* @brief	Appends text to Left/Right of line.
* @param	void
* @return	void
*/
void  MAUI::Gizmo::LineTextAppend(int linenumber, int direction, string text){


	switch(direction){

		case MAUI_GIZMO_VALUE_LINE_DIRECTION_LEFT: //LEFT
			VariableMap[dbStr(linenumber)].insert(0,text);
			break;

		case MAUI_GIZMO_VALUE_LINE_DIRECTION_RIGHT: //RIGHT
			VariableMap[dbStr(linenumber)].append(text);
			break;

	}

}
	
/**
* @brief	Shifts All Lines to Next Line down and inserts LineTextsection value
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextShift(int linenumber, int direction){

	int linecount = dbVal((char*)VariableMap["linecount"].data()); 
	
	switch(direction){

		case MAUI_GIZMO_VALUE_LINE_DIRECTION_UP:
			for(int linecounter = linenumber; linecounter < linecount; linecounter++){
				// move next line into this 
				VariableMap[dbStr(linecounter)] = VariableMap[dbStr(linecounter + 1)];
			}

			//clean last line
			VariableMap[dbStr(linecount)].clear();

			//decrement linecount
			linecount--;
			VariableMap["linecount"] = dbStr(linecount);
			break;

		case MAUI_GIZMO_VALUE_LINE_DIRECTION_DOWN:

			//increment linecount
			linecount++;
			VariableMap["linecount"] = dbStr(linecount);

			for(int linecounter = linecount; linecounter != linenumber; linecounter--){
				// move previous line into this 
				VariableMap[dbStr(linecounter)] = VariableMap[dbStr(linecounter - 1)];
			}
			break;


	}
	

}

/**
* @brief	checks each line, trims and shifts if necessary
* @param	Gizmo* points to Gizmo in which function operates on
* @return	void
*/
void MAUI::Gizmo::LineTextWrap(int linenumber, int direction){

	int linecount = (int)dbVal((char*)VariableMap["linecount"].data() );
	int linealignment =  (int)dbVal((char*)VariableMap["linealignment"].data() );
	int linecounter = 0;

	switch(linealignment){

		default:

			//left to right
			for(linecounter = linenumber; linecounter < linecount + 1; linecounter++){
				string text = LineTextTrim(linecounter, direction, Body->Size.x);
				if(text.size()){
					LineTextAppend(linecounter + 1, MAUI_GIZMO_VALUE_LINE_DIRECTION_LEFT, text);

					//if Caret location part of textsection then relocate
					if((int)dbVal((char*)Caret->VariableMap["linestartposition"].data()) == linecounter){
						if((int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()) > VariableMap[dbStr(linecounter)].size()){ 
							//get difference
							LineCaretSet(linecounter + 1, (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data()) - VariableMap[dbStr(linecounter)].size(),1);
						}
					}

					if(linecount < linecounter + 1){
						linecount = linecounter + 1;
						VariableMap["linecount"] = dbStr(linecount);
					}
				}
			}
			break;
	}

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextDisplay(int linenumber, float y, float height, int red, int green, int blue){

	dbInk(D3DCOLOR_XRGB(red, green , blue),0);
	//dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)), (int)y, (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)y);
	//dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)y, (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)y + (int)height);
	//dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x, (int)y + (int)height, (int)(Body->Position.x - (Body->Size.x/2.0)), (int)y + (int)height);
	//dbLine( (int)(Body->Position.x - (Body->Size.x/2.0)), (int)y + (int)height, (int)(Body->Position.x - (Body->Size.x/2.0)) , (int)y);
	dbBox((int)(Body->Position.x - (Body->Size.x/2.0)),(int)y,(int)(Body->Position.x - (Body->Size.x/2.0)) + (int)Body->Size.x,(int)y + (int)height);

	Core->Text->FontSet(EventAction[EventState.State]->Sprite->CaptionStyle->EventAction[EventState.State]->FontID);
	//Core->Text->ColorSet(red, green , blue, 255);
	//Core->Text->Print( (int)(Body->Position.x - (Body->Size.x/2.0)) - (8 + Core->Text->WidthGet(dbStr(linenumber))), (int)y, (char*)dbStr(linenumber) ); //line number
	//Core->Text->ColorSet();
	Core->Text->Print( (int)(Body->Position.x - (Body->Size.x/2.0)), (int)y, (char*)VariableMap[dbStr(linenumber)].data() );

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextDisplayAll(int red, int green, int blue){
	
	int linecount = (int)dbVal((char*)VariableMap["linecount"].data() );
	MAUI::Gizmo::LineTextDisplay(1, linecount, red, green, blue);

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextDisplay(int startlinenumber, int stoplinenumber, int red, int green, int blue){

	int linecounter = 0;
	float lineheight = 0; //tallest character height
	float liney = Body->Position.y - (Body->Size.y/2.0);

	for(linecounter=startlinenumber; linecounter < stoplinenumber + 1; linecounter++){
		lineheight = Core->Text->HeightGet(VariableMap[dbStr(linecounter)]); //tallest character height
		LineTextDisplay(linecounter, liney, lineheight, red, green, blue);
		liney += lineheight;
	}

}

/**
* @brief	Capture Text to Sprite Image based on actionstate
			Note: Assumes Sprite Exists
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextCapture(int actionstate){

	MAUI::Sprite *Sprite = EventAction[actionstate]->Sprite;
	int linecount = (int)dbVal((char*)VariableMap["linecount"].data() );
	int linecounter = 0;
	float lineheight; //tallest character height
	float liney = 0;

	//render on fly
	if(!Sprite->dbImageID){
		Sprite->dbImageID = dbImageResource->Pop();
		Core->Image->Create(Sprite->dbImageID, S3GE_IMAGE_TYPE_RENDERTARGET, "", 0, (int)Body->Size.x, (int)Body->Size.y);
	}	
	
	//set render target
	Core->Image->Set(Sprite->dbImageID);
	
	//draw background
	if(Sprite->BackdropImageID){
		dbPasteImage(Sprite->BackdropImageID,(int)Sprite->BackdropImageAlign.x,(int)Sprite->BackdropImageAlign.y);
	}

	//draw Theme border
	if(Sprite->BackdropTheme != NULL){

		Sprite->BackdropTheme->EventAction[actionstate]->Draw(Body->Size);

		//Execute Theme Script
		if(Sprite->BackdropTheme->EventAction[actionstate]->Task != NULL){
			//DarkLUA::System::PointerSet("this",(Theme*)Sprite->BackdropTheme);
			Sprite->BackdropTheme->EventAction[actionstate]->Task->Execute(DarkLUA::Task::RUNNING);
		}
	}

	//draw LineText
	if(Sprite->CaptionStyle != NULL){

		Core->Text->FontSet(Sprite->CaptionStyle->EventAction[actionstate]->FontID);

		Sprite->Caption.clear();

		for(linecounter=1; linecounter < linecount + 1; linecounter++){

			//draw text
			lineheight = Core->Text->HeightGet(VariableMap[dbStr(linecounter)]); //tallest character height
			Core->Text->Print( 0, liney, (char*)VariableMap[dbStr(linecounter)].data() );
			liney += lineheight;

			//store in caption
			Sprite->Caption.append(VariableMap[dbStr(linecounter)]);
			if(linecounter < linecount) Sprite->Caption.append("\n");

		}

		//Execute Style Script
		if(Sprite->CaptionStyle->EventAction[actionstate]->Task != NULL){
			//DarkLUA::System::PointerSet("this",(Style*)Sprite->CaptionStyle);
			Sprite->CaptionStyle->EventAction[actionstate]->Task->Execute(DarkLUA::Task::RUNNING);
		}

	}	
	
	//restore backbuffer render target
	Core->Image->Reset();
	
	//apply capture
	switch(Type){

		case MAUI_GIZMO_TYPE_GIZMO:
			dbSetSpriteImage(SpriteID, Sprite->dbImageID);
			break;

		case MAUI_GIZMO_TYPE_WIZMO:
			dbTextureObject(SpriteID, Sprite->dbImageID);
			break;		


	}

}

/**
* @brief	Concenate all Lines into one string and returns it.
* @param	concentated string
* @return	string
*/
string MAUI::Gizmo::LineTextGet(void){

	string concenatedstring;

	int linecount = (int)dbVal((char*)VariableMap["linecount"].data() );
	int linecounter = 0;

	for(linecounter=1; linecounter < linecount + 1; linecounter++){
		concenatedstring.append(VariableMap[dbStr(linecounter)]);
		if(linecounter < linecount) concenatedstring.append("\n");
	}

	return(concenatedstring);
}


/**
* @brief	Copy Lines into another gizmo;
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineTextCopy(Gizmo *instance){

	int linecount = (int)dbVal((char*)VariableMap["linecount"].data() );
	int linecounter = 0;

	for(linecounter=1; linecounter < linecount + 1; linecounter++){
		instance->VariableMap[dbStr(linecounter)] =  VariableMap[dbStr(linecounter)];
	}
}


//MAUI::Gizmo::line selection operations
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionEdit(Gizmo *instance, int function){

	MAUI::Gizmo *targetgizmo = NameMap[Caret->VariableMap["targetgizmo"]];

	switch(function){

		case 0: //Insert (Paste) Selection
			targetgizmo->LineSelectionInsert();
			break;

		case 1://Copy Selection
			targetgizmo->LineSelectionGet();
			break;

		case 2://Cut Selection
			break;

		case 3://Delete Selection
			targetgizmo->LineSelectionDelete();
			break;
	}
}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionSet(void){

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionGet(void){

	int linestartposition = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
	int linestopposition = (int)dbVal((char*)Caret->VariableMap["linestopposition"].data());
	int linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	int linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());

	//swap values if start > stop
	if( linestartposition > linestopposition ) {
		linestartposition = (int)dbVal((char*)Caret->VariableMap["linestopposition"].data());
		linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());
		linestopposition = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
		linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	}

	//swap if start = stop && startchar > stopchar
	if( linestartposition == linestopposition && linestartcharacterposition > linestopcharacterposition) {
		linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());
		linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	}

	if(linestopposition == 0 || linestartposition == 0){
		return;
	}

	int linecounter = 0;
	int Caretlinecount = 0;

	for(linecounter=1; linecounter < linestopposition + 1; linecounter++){

		if(linecounter == linestartposition && linecounter == linestopposition){

			if(linestartcharacterposition == linestopcharacterposition){
				return;
			}

			//head to tail
			Caretlinecount++;

			Caret->VariableMap[dbStr(Caretlinecount)] = VariableMap[dbStr(linecounter)].substr(linestartcharacterposition, linestopcharacterposition - linestartcharacterposition);
			break;

		} else {

			//head
			if(linecounter == linestartposition){
				Caretlinecount++;
				Caret->VariableMap[dbStr(Caretlinecount)] = VariableMap[dbStr(linecounter)].substr(linestartcharacterposition, VariableMap[dbStr(linecounter)].size() - linestartcharacterposition);
			}

			//Body
			if(linecounter > linestartposition && linecounter < linestopposition){
				Caretlinecount++;
				Caret->VariableMap[dbStr(Caretlinecount)] = VariableMap[dbStr(linecounter)];
			}

			//tail
			if(linecounter == linestopposition){
				Caretlinecount++;
				Caret->VariableMap[dbStr(Caretlinecount)] = VariableMap[dbStr(linecounter)].substr( 0, linestopcharacterposition);
			}

		}

	}

	Caret->VariableMap["linecount"] = dbStr(Caretlinecount);

}
		
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionInsert(void){

	int Caretlinecount = (int)dbVal((char*)Caret->VariableMap["linecount"].data());
	
	if(!Caretlinecount){
		return;
	}
	
	for(int Caretlinecounter=1; Caretlinecounter < Caretlinecount + 1; Caretlinecounter++){
		LineTextInsert(Caret->VariableMap[dbStr(Caretlinecounter)]);
	}

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionDelete(void){

	int linestartposition = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
	int linestopposition = (int)dbVal((char*)Caret->VariableMap["linestopposition"].data());
	int linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	int linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());

	//swap values if start > stop
	if( linestartposition > linestopposition ) {
		linestartposition = (int)dbVal((char*)Caret->VariableMap["linestopposition"].data());
		linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());
		linestopposition = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
		linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	}

	//swap if start = stop && startchar > stopchar
	if( linestartposition == linestopposition && linestartcharacterposition > linestopcharacterposition) {
		linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());
		linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	}

	//delete single char
	if(linestopposition == linestartposition && linestartcharacterposition == linestopcharacterposition){
		LineTextDelete();
		return;
	}

	//delete selection
	int Caretlinecount = (int)dbVal((char*)Caret->VariableMap["linecount"].data());
	
	if(!Caretlinecount){
		return;
	}
	
	LineCaretSet(linestartposition, linestartcharacterposition,1);

	for(int Caretlinecounter=1; Caretlinecounter < Caretlinecount + 1; Caretlinecounter++){
		for(int Caretlinecharactercounter = 0; Caretlinecharactercounter < Caret->VariableMap[dbStr(Caretlinecounter)].size(); Caretlinecharactercounter++){
			LineTextDelete();
		}
	}

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionCut(void){

	LineSelectionGet();
	LineSelectionDelete();

}
	
/**
* @brief	Display Selection based on Caret Start/Stop Line & Character Positions
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionDisplay(int red, int green, int blue){

	if(!VisibleFlag){
		return;
	}

	if(this->Name.compare(Caret->VariableMap["targetgizmo"]) != 0){
		return;
	}

	int linestartposition = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
	int linestopposition = (int)dbVal((char*)Caret->VariableMap["linestopposition"].data());
	int linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	int linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());

	//swap values if start > stop
	if( linestartposition > linestopposition ) {
		linestartposition = (int)dbVal((char*)Caret->VariableMap["linestopposition"].data());
		linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());
		linestopposition = (int)dbVal((char*)Caret->VariableMap["linestartposition"].data());
		linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	}

	//swap if start = stop && startchar > stopchar
	if( linestartposition == linestopposition && linestartcharacterposition > linestopcharacterposition) {
		linestartcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestopcharacterposition"].data());
		linestopcharacterposition = (int)dbVal((char*)Caret->VariableMap["linestartcharacterposition"].data());
	}

	if(linestopposition == 0 || linestartposition == 0){
		return;
	}

	int linecounter = 0;
	float linecharacterx = 0;
	float linecharacterwidth = 0;
	float linex = 0;
	float linewidth = 0;
	float liney = Body->Position.y - (Body->Size.y/2.0);
	float lineheight = 0; //tallest character height

	for(linecounter=1; linecounter < linestopposition + 1; linecounter++){

		lineheight = Core->Text->HeightGet(VariableMap[dbStr(linecounter)]); //tallest character height
		
		if(linecounter == linestartposition && linecounter == linestopposition){

			if(linestartcharacterposition == linestopcharacterposition){
				return;
			}

			//head to tail
			linecharacterx = (Body->Position.x - (Body->Size.x/2.0));
			linex = linecharacterx;

			for(int linecharactercounter=0; linecharactercounter < linestopcharacterposition; linecharactercounter++){
				//dbTextWidth()
				string linecharacter = VariableMap[dbStr(linecounter)].substr(linecharactercounter,1);
				linecharacterwidth = Core->Text->WidthGet(linecharacter);
				if(linecharactercounter == linestartcharacterposition){
					linex = linecharacterx;	
				}
				linecharacterx += linecharacterwidth;
			}
			linewidth = linecharacterx - linex;
			LineSelectionDisplay(linex, linewidth, liney, lineheight, red, green, blue);

			Core->Text->ColorSet(0, 0, 0, 255);
			Core->Text->Print((int)(Body->Position.x - (Body->Size.x/2.0)), liney, (char*)VariableMap[dbStr(linecounter)].data());

			break;

		} else {

			//head
			if(linecounter == linestartposition){
				linecharacterx = (Body->Position.x - (Body->Size.x/2.0));
				for(int linecharactercounter=0; linecharactercounter < VariableMap[dbStr(linecounter)].size() + 1; linecharactercounter++){
					//dbTextWidth()
					string linecharacter = VariableMap[dbStr(linecounter)].substr(linecharactercounter,1);
					linecharacterwidth = Core->Text->WidthGet(linecharacter);
					if(linecharactercounter == linestartcharacterposition){
							linex = linecharacterx;	
					}					
					linecharacterx += linecharacterwidth;
				}
				linewidth = linecharacterx - linex;
				LineSelectionDisplay(linex, linewidth, liney, lineheight, red, green, blue);
			}

			//Body
			if(linecounter > linestartposition && linecounter < linestopposition){
				linex = (Body->Position.x - (Body->Size.x/2.0));
				linewidth = Core->Text->WidthGet(VariableMap[dbStr(linecounter)]);
				LineSelectionDisplay(linex, linewidth, liney, lineheight, red, green, blue);
			}

			//tail
			if(linecounter == linestopposition){
				linecharacterx = (Body->Position.x - (Body->Size.x/2.0));
				linex = linecharacterx;
				linewidth = 0;
				for(int linecharactercounter=0; linecharactercounter < linestopcharacterposition; linecharactercounter++){
					//dbTextWidth()
					string linecharacter = VariableMap[dbStr(linecounter)].substr(linecharactercounter,1);
					linecharacterwidth = Core->Text->WidthGet(linecharacter);
					linewidth += linecharacterwidth;
					linecharacterx += linecharacterwidth;
				}
				LineSelectionDisplay(linex, linewidth, liney, lineheight, red, green, blue);
			}

			Core->Text->ColorSet(0, 0, 0,255);
			Core->Text->Print((int)(Body->Position.x - (Body->Size.x/2.0)), liney, (char*)VariableMap[dbStr(linecounter)].data());

		}

		liney += lineheight;
	}

}
	
/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::LineSelectionDisplay(float x, float width, float y, float height, int red, int green, int blue){

	dbInk(D3DCOLOR_XRGB(red, green , blue),0);

	//dbLine((int)x, (int)y, (int)x + (int)width, (int)y);
	//dbLine((int)x + (int)width, (int)y, (int)x + (int)width, (int)y + (int)height);
	//dbLine((int)x + (int)width, (int)y + (int)height, (int)x , (int)y + (int)height);
	//dbLine((int)x , (int)y + (int)height, (int)x, (int)y);
	dbBox((int)x, (int)y, (int)x + (int)width, (int)y + (int)height);

}

// GIZMO MESSAGING //////////////////////////////////////////////////
	
/**
* @brief	Constructor
* @param	void
* @return	void
*/

MAUI::Message::Parameter::Parameter(int type, string key, string value){

	Type = type;
	Key = key;
	Value = value;
}

/**
* @brief	Destructor
* @param	void
* @return	void
*/
MAUI::Message::Parameter::~Parameter(){

}

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Message::Message(void){

	Receiver = NULL;
	Type = ID = ParameterCount = State = 0;
}

/**
* @brief	Destructor
* @param	void
* @return	void
*/
MAUI::Message::~Message(void){

}

/**
* @brief	Create Message
* @param	void
* @return	void
*/
MAUI::Message *MAUI::Message::Create(int type=0){

	Message *instance = new Message;
	instance->Receiver = NULL;
	instance->Type = type;
	instance->ID = 0;
	instance->State = 0;
	return(instance);
}

/**
* @brief	Destroy Message
* @param	void
* @return	void
*/
void MAUI::Message::Destroy(Message *instance){

	//delete Parameters

	for(instance->ParameterMapIterator = instance->ParameterMap.begin(); instance->ParameterMapIterator != instance->ParameterMap.end(); instance->ParameterMapIterator++ ){
		delete (*instance->ParameterMapIterator).second;
	}
	delete instance;
}

/**
* @brief	copy Message
* @param	void
* @return	void
*/
MAUI::Message *MAUI::Message::Copy(void){

	Message *instance = new Message;
	instance->Receiver = NULL;
	instance->Type = Type;
	instance->ID = ID;
	instance->State = State;

	for(ParameterMapIterator = ParameterMap.begin(); ParameterMapIterator != ParameterMap.end(); ParameterMapIterator++ ){
		instance->ParameterCount++;
		instance->ParameterMap[instance->ParameterCount] = new Parameter((*ParameterMapIterator).second->Type, (*ParameterMapIterator).second->Key, (*ParameterMapIterator).second->Value);
	}

	return(instance);
}

/**
* @brief	insert Parameter into list
* @param	void
* @return	void
*/
void MAUI::Message::Insert(Message *instance, int type, string key, string value){

	instance->ParameterCount++;
	instance->ParameterMap[instance->ParameterCount] = new Parameter(type, key, value);
}

/**
* @brief	Retrieves a message from the calling thread's message queue.
* @param	void
* @return	void
*/
bool MAUI::Gizmo::MessageGet(void){

	if(!MessageQueue.empty()){

		Message = MessageQueue.front();
		MessageQueue.pop();

		if(Message->ID != MAUI_MSG_QUIT){
			return true;
		}

	}

	return false;
}

/**
* @brief	Retrieves a Gizmo::messaging from the calling thread's Gizmo::messaging queue.
* @param	void
* @return	void
*/
bool MAUI::Gizmo::MessagePeek(void){
	
	if(!MessageQueue.empty()){

		Message = MessageQueue.front();

		if(Message->ID != MAUI_MSG_QUIT){
			return true;
		}
	}

	return false;

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::MessageProcess(void){

	for(Message->ParameterMapIterator = Message->ParameterMap.begin(); Message->ParameterMapIterator != Message->ParameterMap.end(); Message->ParameterMapIterator++ ){

		switch((*Message->ParameterMapIterator).second->Type){

			case MAUI_MSG_PARAMETER_TYPE_PROPERTY:
				PropertySet(this, (*Message->ParameterMapIterator).second->Key, (char*)(*Message->ParameterMapIterator).second->Value.data() );
				break;

			case MAUI_MSG_PARAMETER_TYPE_VARIABLE:
				VariableSet(this, (*Message->ParameterMapIterator).second->Key, (char*)(*Message->ParameterMapIterator).second->Value.data() );
				break;

			case MAUI_MSG_PARAMETER_TYPE_SCRIPT:
				DarkLUA::Task *task;
				task = new DarkLUA::Task((*Message->ParameterMapIterator).second->Key, (*Message->ParameterMapIterator).second->Value);
				DarkLUA::System::PointerSet("this",(Gizmo*)this);
				task->Execute(DarkLUA::Task::RUNNING);
				delete task;
				break;

			default: //MAUI_MSG_PARAMETER_TYPE_VALUE:

				switch((int)dbVal((char*)(*Message->ParameterMapIterator).second->Key.data())){

					case MAUI_MSG_QUIT:
						break;

					case MAUI_MSG_GIZMO_CLOSE:
						CollisionFlag = OperateFlag = TransitFlag = ActiveFlag = VisibleFlag = AudioFlag = false;
						break;

					case MAUI_MSG_GIZMO_OPEN:
						CollisionFlag = OperateFlag = TransitFlag = ActiveFlag = VisibleFlag = AudioFlag = true;
						break;	

					case MAUI_MSG_GIZMO_HIDE:
						VisibleFlag = false;
						break;

					case MAUI_MSG_GIZMO_SHOW:
						VisibleFlag = true;
						break;

					case MAUI_MSG_GIZMO_COLLISION_DISABLE:
						CollisionFlag = false;
						break;

					case MAUI_MSG_GIZMO_COLLISION_ENABLE:
						CollisionFlag = true;
						break;

					case MAUI_MSG_GIZMO_MUTE:
						AudioFlag = false;
						break;

					case MAUI_MSG_GIZMO_AUDIBLE:
						AudioFlag = true;
						break;

					case MAUI_MSG_GIZMO_MOVE:
						break;

					case MAUI_MSG_GIZMO_SIZE:
						break;

					case MAUI_MSG_GIZMO_ROTATE:
						break;

					case MAUI_MSG_GIZMO_DISABLE:
						State = DISABLED;
						break;

					case MAUI_MSG_GIZMO_ENABLE:
						State = ACTIVE;
						break;

					case MAUI_MSG_GIZMO_TRASH:
						break;

					case MAUI_MSG_GIZMO_EXECUTE:
						break;

					case MAUI_MSG_GIZMO_MOVE_X:
						if(Body != NULL){
							Body->Position.x = dbVal((char*)(*Message->ParameterMapIterator).second->Value.data());
							Body->Physics->OrientationSet((b2Vec2&)Body->Position, 0);
						}
						break;

					case MAUI_MSG_GIZMO_MOVE_Y:
						if(Body != NULL){
							Body->Position.y = dbVal((char*)(*Message->ParameterMapIterator).second->Value.data());
							Body->Physics->OrientationSet((b2Vec2&)Body->Position, 0);
						}
						break;

					case MAUI_MSG_GIZMO_MOVE_Z:
						if(Body != NULL){
							Body->Position.z = dbVal((char*)(*Message->ParameterMapIterator).second->Value.data());
							Body->Physics->OrientationSet((b2Vec2&)Body->Position, 0);
						}
						break;
				}
				break;
		}
	}

	Message::Destroy(Message);
	Message = NULL;
	
}


/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::MessageSend(MAUI::Message *message, MAUI::Gizmo *receiver){

	if(receiver == NULL) return;
	message->Receiver = receiver;
	receiver->MessageQueue.push(message->Copy());

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::MessageSend(MAUI::Message *message, string name){

	if(NameMap[name] != NULL){
		MessageSend(message, NameMap[name]);
	}

}

/**
* @brief	Send message to Family
* @param	groupID: -1=parent, 0=self, 1=Siblings, 2=Children, 3=all; 0x01=parent, 0x02=self, 0x04=Siblings, 0x08=Children, 3=all
* @return	void
*/
void MAUI::Gizmo::MessageSend(MAUI::Message *message, string name, int groupID, bool subflag){

	if(NameMap[name] == NULL) return;
	
	//Bitflag
	//0x02=parent, 0x01= self,  0x04=Siblings, 0x08=Children, 3=all
	if (groupID & MAUI_MSG_TO_SELF) 
		MessageSend(message, NameMap[name]);
		
	if (groupID & MAUI_MSG_TO_PARENT) 
		MessageSend(message, NameMap[name]->Parent);
		
	if (groupID & MAUI_MSG_TO_SIBLINGS)
		NameMap[name]->FamilySiblingMessageSend(message, subflag);
		
	if (groupID & MAUI_MSG_TO_CHILDREN) 
		NameMap[name]->FamilyChildrenMessageSend(message, subflag);
		
	if (groupID & MAUI_MSG_TO_ALL) 
		NameMap[name]->FamilyMessageSend(message);
	
}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilyMessageSend(MAUI::Message *message){

    Gizmo *sibling = this;
    do {
		MessageSend(message, sibling);
        if (sibling->First != NULL) { 
			sibling->First->FamilyMessageSend(message);
		}
        sibling = sibling->Next;
    } while(!(sibling == this || sibling == NULL));

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilySiblingMessageSend(MAUI::Message *message, bool subflag){

    Gizmo *sibling = Next;
	if(sibling != NULL){
		do{
			MessageSend(message, sibling);
			if (subflag) { 
				sibling->FamilyChildrenMessageSend(message, subflag);
			}
			sibling = sibling->Next;
		} while(!(sibling == this || sibling == NULL));
	}
}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gizmo::FamilyChildrenMessageSend(MAUI::Message *message, bool subflag){

	Gizmo *child = First;
    if (child != NULL){
        do{
            MessageSend(message, child);
            if (subflag){ 
	    		child->FamilyChildrenMessageSend(message, subflag);
			}
			child = child->Next;
        }while(!(child == First || child == NULL));
    }
}


// GIZMO EVENTSCRIPT //////////////////////////////////////////////////

/**
* @brief	 Constructor
* @param	void
* @return	void
*/
MAUI::Gizmo::EventScript::EventScript(void){

	Behavior = Transition = NULL;
	Scheme = NULL;
	Sprite = NULL;
	Task = NULL;

}

/**
* @brief	Inheritor
* @param	void
* @return	void
*/
void MAUI::Gizmo::EventScript::Inherit(MAUI::Gizmo::EventScript *parent){

	Behavior = parent->Behavior;
	Transition = parent->Transition;
	Scheme = parent->Scheme;
	Sprite = parent->Sprite;
	Task = parent->Task;

}

/**
* @brief	Copy
* @param	void
* @return	void
*/
MAUI::Gizmo::EventScript *MAUI::Gizmo::EventScript::Copy(void){

	EventScript *instance = new EventScript;
	
	instance->Behavior = Behavior;
	instance->Transition = Transition;
	instance->Scheme = Scheme;

	instance->Sprite = Sprite->Copy();

	//copy task
	if(Task != NULL){
		//replace gizmo names in scripts
		instance->Task = Task;
		Task->Shared++;
	}

	return(instance);

}



// GADGET ////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::Gadget*> MAUI::Gadget::NameMap;
map<string,MAUI::Gadget*>::iterator MAUI::Gadget::NameMapIterator;
list<MAUI::Gadget*> MAUI::Gadget::ActiveList;
list<MAUI::Gadget*>::iterator MAUI::Gadget::ActiveListIterator;
queue<MAUI::Gadget*> MAUI::Gadget::InactiveQueue;

/**
* @brief	Constructor
* @param	void
* @return	void
*/
MAUI::Gadget::Gadget(void){

	Name = "Undefined Gadget";
	Description = "Undefined Gadget";

	CopyIndex = 0;
	CollisionFlag = DebugFlag = VisibleFlag = AudioFlag = ActiveFlag = TransitFlag = OperateFlag = false;
}

/**
* @brief	Destructor
* @param	void
* @return	void
*/
MAUI::Gadget::~Gadget(void){

}

/**
* @brief	Create Gadget from Gizmo and its Family
* @param	void
* @return	void
*/
MAUI::Gadget* MAUI::Gadget::Create(string parentname, string name, string description, bool collisionflag, bool operateflag, bool transitflag, bool activeflag, bool visibleflag, bool audioflag){

	MAUI::Gadget *instance;

	if(NameMap[name] == NULL){
		instance = new MAUI::Gadget;
        NameMap[name] = instance;
	}  else {
		instance = NameMap[name];
	}
	
	instance->Name = name;
	instance->Description = description;
	instance->CollisionFlag;
	instance->DebugFlag = false; 
	instance->VisibleFlag = visibleflag;
	instance->AudioFlag = audioflag;  
	instance->ActiveFlag = activeflag;
	instance->TransitFlag = transitflag;
	instance->OperateFlag = operateflag;

	return(instance);
}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::Gadget::Destroy(Gadget* instance){

}

/**
* @brief	
* @param	void
* @return	void
*/
MAUI::Gadget *MAUI::Gadget::Copy(void){

	string name;
	string description;

	CopyIndex++;

	name = Name;
	name.append("_");
	name.append(dbStr(CopyIndex));

	Gadget *instance = Create("", name, Description, CollisionFlag, OperateFlag, TransitFlag, ActiveFlag, VisibleFlag, AudioFlag);
	
	//iterate through gizmos
	for(GizmoListIterator = GizmoList.begin(); GizmoListIterator != GizmoList.end(); GizmoListIterator++ ){
		
		name = (*GizmoListIterator)->Name;
		name.append("_");
		name.append(dbStr(CopyIndex));

		description = "Reference ";
		description.append((*GizmoListIterator)->Name);
		
		//copy 
		instance->GizmoList.push_back((*GizmoListIterator)->Copy(name, description));
	}

	return (instance);
}

// GADGET EVENTSCRIPT //////////////////////////////////////////////////

/**
* @brief	 Constructor
* @param	void
* @return	void
*/
MAUI::Gadget::EventScript::EventScript(void){

	Task = NULL;

}

/**
* @brief	 Inheritor
* @param	void
* @return	void
*/
void MAUI::Gadget::EventScript::Inherit(MAUI::Gadget::EventScript *parent){

	Task = parent->Task;

}

/**
* @brief	 Copy
* @param	void
* @return	void
*/
MAUI::Gadget::EventScript *MAUI::Gadget::EventScript::Copy(void){

	EventScript *instance = new EventScript;
	
	//copy task
	if(Task != NULL){
		//replace gizmo names in scripts
		instance->Task = Task;
		Task->Shared++;
	}
	
	return(instance);

}

// HTTPFORM //////////////////////////////////////////////////////////////////////////////////////////
map<string,MAUI::HTTPForm*> MAUI::HTTPForm::NameMap;
map<string,MAUI::HTTPForm*>::iterator MAUI::HTTPForm::NameMapIterator;
list<MAUI::HTTPForm*> MAUI::HTTPForm::ActiveList;
list<MAUI::HTTPForm*>::iterator MAUI::HTTPForm::ActiveListIterator;
queue<MAUI::HTTPForm*> MAUI::HTTPForm::InactiveQueue;

/**
* @brief	 Constructor
* @param	void
* @return	void
*/
MAUI::HTTPForm::HTTPForm(void){

	HTTP = NULL;

}

/**
* @brief	 Constructor
* @param	void
* @return	void
*/
MAUI::HTTPForm::HTTPForm(string name, string description){

	this->Name = name;
	this->Description = description;
	HTTP = NULL;

}

/**
* @brief	 Destructor
* @param	void
* @return	void
*/
MAUI::HTTPForm::~HTTPForm(void){

}

/**
* @brief	 
* @param	void
* @return	void
*/
MAUI::HTTPForm *MAUI::HTTPForm::Create(string name, string description, int method, string hostname, int port, string page, string writepath){

	if(NameMap[name] == NULL){
        CurrentHTTPForm = new HTTPForm(name,description);
		NameMap[name] = CurrentHTTPForm;
	} else {
		CurrentHTTPForm = NameMap[name];
	}

	CurrentHTTPForm->Method = method;
	CurrentHTTPForm->Hostname = hostname;
	CurrentHTTPForm->Port = port;
	CurrentHTTPForm->Page = page;
	CurrentHTTPForm->WritePath = writepath;

	ActiveList.push_back(CurrentHTTPForm);
	CurrentHTTPForm->State = IDLE;

	return (CurrentHTTPForm);
}

/**
* @brief	 
* @param	void
* @return	void
*/
void MAUI::HTTPForm::Destroy(MAUI::HTTPForm *HTTPForm){

	delete HTTPForm;
}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::HTTPForm::Update(void){

	//iterate through active gizmos
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
		(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive gizmos
	while (!InactiveQueue.empty()){
		ActiveList.remove(InactiveQueue.front());
		Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}
}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::HTTPForm::Process(void){
	
	switch(State){
		case IDLE:
			break;

		case SENDING:
			if(HTTP->State == DarkNet::PALM::RESPONSESTART){ State = RECEIVING; }
			break;

		case RECEIVING:
			if(HTTP->State == DarkNet::PALM::RESPONSEEND){ State = IDLE; }
			break;
	}
}

/**
* @brief	Encode
* @param	void
* @return	void
*/
void MAUI::HTTPForm::Submit(void){
	
	HTTP = DarkNet::HTTP::FileGet(Name,Method,Hostname,Port,Page,WritePath);

	if(HTTP != NULL){

		//build pagevariable list
		for(GizmoListIterator = GizmoList.begin(); GizmoListIterator != GizmoList.end(); GizmoListIterator++ ){
			for((*GizmoListIterator)->VariableMapIterator = (*GizmoListIterator)->VariableMap.begin(); (*GizmoListIterator)->VariableMapIterator != (*GizmoListIterator)->VariableMap.end(); (*GizmoListIterator)->VariableMapIterator++ ){
				if((*GizmoListIterator)->VariableMapIterator->first.compare("value")==0){
					HTTP->Request.PageVariables.append((*GizmoListIterator)->Name);
					//HTTP->Request.PageVariables.append("_"); //gizmoname_variablename
					//HTTP->Request.PageVariables.append((*GizmoListIterator)->VariableMapIterator->first);
					HTTP->Request.PageVariables.append("=");
					HTTP->Request.PageVariables.append(HTTP->URLEncode((*GizmoListIterator)->VariableMapIterator->second));
					HTTP->Request.PageVariables.append("&");
				}
			}
		}
		//erase last &
		HTTP->Request.PageVariables.erase(HTTP->Request.PageVariables.size()-1);

		State = SENDING;
	}

}

/**
* @brief	
* @param	void
* @return	void
*/
void MAUI::HTTPForm::Submit(string name){

	if(NameMap[name]!=NULL){
		NameMap[name]->Submit();
	}

}