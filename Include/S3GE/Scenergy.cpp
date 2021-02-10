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

#include "Scenergy.h"

// SYSTEM //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Initializes Scenergy
* @param	void
* @return	void
*/
void Scenergy::System::Start(void){

	//XMLFile::TagNameAdd("maui", S3GXL_TAG_S3GE);
	XMLFile::TagNameAdd("s3ge", S3GXL_TAG_S3GE);
	XMLFile::TagNameAdd("widget", S3GXL_TAG_WIDGET);
	XMLFile::TagNameAdd("doodad", S3GXL_TAG_DOODAD);
	XMLFile::TagNameAdd("jigger", S3GXL_TAG_JIGGER);
	XMLFile::TagNameAdd("gizmo", S3GXL_TAG_GIZMO);
	XMLFile::TagNameAdd("wizmo", S3GXL_TAG_WIZMO);
	XMLFile::TagNameAdd("behavior", S3GXL_TAG_BEHAVIOR);
	XMLFile::TagNameAdd("transition", S3GXL_TAG_TRANSITION);
	XMLFile::TagNameAdd("style", S3GXL_TAG_STYLE);
	XMLFile::TagNameAdd("theme", S3GXL_TAG_THEME);
	XMLFile::TagNameAdd("scheme", S3GXL_TAG_SCHEME);
	XMLFile::TagNameAdd("event", S3GXL_TAG_EVENT);
	XMLFile::TagNameAdd("meta", S3GXL_TAG_META);
	XMLFile::TagNameAdd("script", S3GXL_TAG_SCRIPT);
	XMLFile::TagNameAdd("font", S3GXL_TAG_FONT);
	XMLFile::TagNameAdd("alpha", S3GXL_TAG_ALPHA);
	XMLFile::TagNameAdd("opaque", S3GXL_TAG_OPAQUE);
	XMLFile::TagNameAdd("transparent", S3GXL_TAG_TRANSPARENT);
	XMLFile::TagNameAdd("b", S3GXL_TAG_BOLD);
	XMLFile::TagNameAdd("i", S3GXL_TAG_ITALIC);
	XMLFile::TagNameAdd("orientate", S3GXL_TAG_ORIENTATE);
	XMLFile::TagNameAdd("body", S3GXL_TAG_ORIENTATE);//alias for orientate
	XMLFile::TagNameAdd("border",S3GXL_TAG_BORDER);
	XMLFile::TagNameAdd("audio",S3GXL_TAG_AUDIO);
	XMLFile::TagNameAdd("physics",S3GXL_TAG_PHYSICS);
	XMLFile::TagNameAdd("form",S3GXL_TAG_FORM);
	XMLFile::TagNameAdd("submit",S3GXL_TAG_FORMSUBMIT);
	XMLFile::TagNameAdd("reset",S3GXL_TAG_FORMRESET);
	XMLFile::TagNameAdd("canvas",S3GXL_TAG_CANVAS);
	XMLFile::TagNameAdd("inputdevice",S3GXL_TAG_INPUTDEVICE);
	XMLFile::TagNameAdd("state",S3GXL_TAG_STATE);
	XMLFile::TagNameAdd("object",S3GXL_TAG_OBJECT);
	XMLFile::TagNameAdd("variable",S3GXL_TAG_VARIABLE);
	XMLFile::TagNameAdd("property",S3GXL_TAG_VARIABLE); //alias for variable
	XMLFile::TagNameAdd("include",S3GXL_TAG_INCLUDE);
	XMLFile::TagNameAdd("task",S3GXL_TAG_TASK);
	XMLFile::TagNameAdd("gadget",S3GXL_TAG_GADGET);
	XMLFile::TagNameAdd("terrain",S3GXL_TAG_TERRAIN);
	XMLFile::TagNameAdd("matrix",S3GXL_TAG_MATRIX);
	XMLFile::TagNameAdd("light",S3GXL_TAG_LIGHT);
	XMLFile::TagNameAdd("shader",S3GXL_TAG_SHADER);
	XMLFile::TagNameAdd("interactive",S3GXL_TAG_GIZMO);
	XMLFile::TagNameAdd("entity",S3GXL_TAG_GADGET);
	XMLFile::TagNameAdd("particle",S3GXL_TAG_PARTICLE);
	XMLFile::TagNameAdd("reactor",S3GXL_TAG_REACTOR);

	XMLFile::AttributeValueAdd("",0);//default
	XMLFile::AttributeValueAdd("true",true);
	XMLFile::AttributeValueAdd("false",false);
	XMLFile::AttributeValueAdd("mouse",MAUI_INPUTDEVICE_TYPE_MOUSE);
	XMLFile::AttributeValueAdd("keyboard",MAUI_INPUTDEVICE_TYPE_KEYBOARD);
	XMLFile::AttributeValueAdd("joystick",MAUI_INPUTDEVICE_TYPE_JOYSTICK);
	XMLFile::AttributeValueAdd("xbox360",MAUI_INPUTDEVICE_TYPE_JOYSTICK_360);
	XMLFile::AttributeValueAdd("wii",MAUI_INPUTDEVICE_TYPE_JOYSTICK_WII);
	XMLFile::AttributeValueAdd("widget",MAUI_GIZMO_TYPE_WIDGET);
	XMLFile::AttributeValueAdd("doodad",MAUI_GIZMO_TYPE_DOODAD);
	XMLFile::AttributeValueAdd("jigger",MAUI_GIZMO_TYPE_JIGGER);
	XMLFile::AttributeValueAdd("gizmo",MAUI_GIZMO_TYPE_GIZMO);
	XMLFile::AttributeValueAdd("wizmo",MAUI_GIZMO_TYPE_WIZMO);
	XMLFile::AttributeValueAdd("left",MAUI_BODY_ORIENTATE_XALIGN_LEFT);
	XMLFile::AttributeValueAdd("center",MAUI_BODY_ORIENTATE_XALIGN_CENTER);
	XMLFile::AttributeValueAdd("right",MAUI_BODY_ORIENTATE_XALIGN_RIGHT);
	XMLFile::AttributeValueAdd("top",MAUI_BODY_ORIENTATE_YALIGN_TOP);
	XMLFile::AttributeValueAdd("middle",MAUI_BODY_ORIENTATE_YALIGN_MIDDLE);
	XMLFile::AttributeValueAdd("bottom",MAUI_BODY_ORIENTATE_YALIGN_BOTTOM);
	XMLFile::AttributeValueAdd("front",MAUI_BODY_ORIENTATE_ZALIGN_FRONT);
	XMLFile::AttributeValueAdd("neutral",MAUI_BODY_ORIENTATE_ZALIGN_NEUTRAL);
	XMLFile::AttributeValueAdd("neutral",MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL);
	XMLFile::AttributeValueAdd("back",MAUI_BODY_ORIENTATE_ZALIGN_BACK);
	XMLFile::AttributeValueAdd("password",MAUI_SPRITE_CAPTION_TYPE_PASSWORD);
	XMLFile::AttributeValueAdd("hidden",MAUI_SPRITE_CAPTION_TYPE_HIDDEN);
	XMLFile::AttributeValueAdd("realtime",MAUI_SPRITE_CAPTION_TYPE_REALTIME);
	XMLFile::AttributeValueAdd("dgdk",MAUI_SCHEME_AUDIO_SYSTEM_DGDK);
	XMLFile::AttributeValueAdd("oaw",MAUI_SCHEME_AUDIO_SYSTEM_OAW);
	XMLFile::AttributeValueAdd("sound",MAUI_SCHEME_AUDIO_TYPE_SOUND);
	XMLFile::AttributeValueAdd("music",MAUI_SCHEME_AUDIO_TYPE_MUSIC);
	XMLFile::AttributeValueAdd("2d",MAUI_BODY_TYPE_2D);
	XMLFile::AttributeValueAdd("3d",MAUI_BODY_TYPE_3D);
	XMLFile::AttributeValueAdd("world",MAUI_BODY_PHYSICS2D_TYPE_WORLD);
	XMLFile::AttributeValueAdd("body",MAUI_BODY_PHYSICS2D_TYPE_BODY);
	XMLFile::AttributeValueAdd("mousejoint",MAUI_BODY_PHYSICS2D_TYPE_JOINT_MOUSE);
	XMLFile::AttributeValueAdd("distancejoint",MAUI_BODY_PHYSICS2D_TYPE_JOINT_DISTANCE);
	XMLFile::AttributeValueAdd("revolutejoint",MAUI_BODY_PHYSICS2D_TYPE_JOINT_REVOLUTE);
	XMLFile::AttributeValueAdd("prismaticjoint",MAUI_BODY_PHYSICS2D_TYPE_JOINT_PRISMATIC);
	XMLFile::AttributeValueAdd("pullyjoint",MAUI_BODY_PHYSICS2D_TYPE_JOINT_PULLEY);
	XMLFile::AttributeValueAdd("gearjoint",MAUI_BODY_PHYSICS2D_TYPE_JOINT_GEAR);
	XMLFile::AttributeValueAdd("groundplane",MAUI_BODY_PHYSICS3D_TYPE_GROUNDPLANE);
	XMLFile::AttributeValueAdd("box",MAUI_BODY_PHYSICS3D_TYPE_BOX); 
	XMLFile::AttributeValueAdd("sphere",MAUI_BODY_PHYSICS3D_TYPE_SPHERE);
	XMLFile::AttributeValueAdd("capsule",MAUI_BODY_PHYSICS3D_TYPE_CAPSULE);
	XMLFile::AttributeValueAdd("dbomesh",MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESHFROMDBO);
	XMLFile::AttributeValueAdd("trianglemesh",MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESH);
	XMLFile::AttributeValueAdd("convemesh",MAUI_BODY_PHYSICS3D_TYPE_CONVEXMESH);
	XMLFile::AttributeValueAdd("boxshape",MAUI_BODY_PHYSICS3D_TYPE_BOXSHAPE);
	XMLFile::AttributeValueAdd("sphereshape",MAUI_BODY_PHYSICS3D_TYPE_SPHERESHAPE);
	XMLFile::AttributeValueAdd("convexshape",MAUI_BODY_PHYSICS3D_TYPE_CONVEXSHAPE);
	XMLFile::AttributeValueAdd("compound",MAUI_BODY_PHYSICS3D_TYPE_COMPOUNDACTOR);
	XMLFile::AttributeValueAdd("controllerbox",MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERBOX);
	XMLFile::AttributeValueAdd("controllercapsule",MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERCAPSULE);
	XMLFile::AttributeValueAdd("GET",DARKNET_HTTP_METHOD_GET);
	XMLFile::AttributeValueAdd("POST",DARKNET_HTTP_METHOD_POST);
	XMLFile::AttributeValueAdd("ttfont",MAUI_STYLE_FONT_TYPE_DX9FONT);
	XMLFile::AttributeValueAdd("fontart",MAUI_STYLE_FONT_TYPE_FONTART);
	XMLFile::AttributeValueAdd("meshfont",MAUI_STYLE_FONT_TYPE_MESHFONT);
	XMLFile::AttributeValueAdd("mesh",S3GE_OBJECT_TYPE_MESH);
	XMLFile::AttributeValueAdd("terrain",S3GE_OBJECT_TYPE_TERRAIN);
	XMLFile::AttributeValueAdd("matrix",S3GE_OBJECT_TYPE_MATRIX);
	XMLFile::AttributeValueAdd("light",S3GE_OBJECT_TYPE_LIGHT);
	XMLFile::AttributeValueAdd("particle",S3GE_OBJECT_TYPE_PARTICLE);
	XMLFile::AttributeValueAdd("shader",S3GE_OBJECT_TYPE_SHADER);

}

/**
* @brief	Shutdown Scenergy
* @param	void
* @return	void
*/
void Scenergy::System::Stop(void){

}

/**
* @brief	Loads a .s3ge, .maui, .s3gxl  XML, no validation for format; Non blocking implementation
* @param	void
* @return	void
*/
int Scenergy::System::Load(string filename, bool loadallflag, int loadallrate){

	/* file check
		if file not avaliable on local drive, Request from Host Server
		else return Error code
	*/

	new XMLFile(filename, loadallflag, loadallrate);

	return(1);

}

/**
* @brief	Update All Scenergy XML Files
* @param	void
* @return	void
*/
void Scenergy::System::Update(void){

	XMLFile::Update();

}


// XMLFILE //////////////////////////////////////////////////////////////////////////////////////////
map<string,int> Scenergy::XMLFile::TagNameMap;
map<string,int>::iterator Scenergy::XMLFile::TagNameMapIterator;
list<Scenergy::XMLFile*> Scenergy::XMLFile::ActiveList;
list<Scenergy::XMLFile*>::iterator Scenergy::XMLFile::ActiveListIterator;
queue<Scenergy::XMLFile*> Scenergy::XMLFile::InactiveQueue;
map<string,int> Scenergy::XMLFile::AttributeValueMap;

/**
* @brief	 adds tagname to interger map, used in XMLFile::Process() for switch
* @param	void
* @return	void
*/
void Scenergy::XMLFile::TagNameAdd(string tagname, int constant){

	if(!TagNameMap[tagname]){TagNameMap[tagname] = constant;}
}

/**
* @brief	Adds tagname to interger map, used in XMLFile::Process() for switch
* @param	void
* @return	void
*/
void Scenergy::XMLFile::AttributeValueAdd(string attributevalue, int constant){

	if(!AttributeValueMap[attributevalue]){AttributeValueMap[attributevalue] = constant;}
}

/**
* @brief	Constructor; Scenergy Files transferred from the server are stored to the local drive as temp files before load.
* @param	string filename - local filename
* @return	void
*/
Scenergy::XMLFile::XMLFile(string filename, bool loadallflag, int loadallrate){

	switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK | File::CONTINUE_WHILE_LOADING)){

		case S3GE_FILE_FOUND:
			this->Filename = filename;

			XML = createIrrXMLReader((char*)filename.data());
			// parse the file until end reached

			NodeCount = StartTime = 0;
			loadallflag ? State = LOADALL: State = LOAD;  
			!loadallrate ? LoadRate = 18000: LoadRate = loadallrate;
			
			ActiveList.push_back(this);

			break;

		case S3GE_FILE_NOTFOUND:
			InactiveQueue.push(this);
			filename.append(" could not be opened!");
			alertbox("Scenergy::XMLFile",filename,ALERTBOX_SEVERITY_ERROR);
			break;

		default:
			HTTPFile = S3GE::File::HTTPFileMap[fileexists];
			State = DOWNLOADING;
			ActiveList.push_back(this);

	}

}

/**
* @brief	destructor
* @param	void
* @return	void
*/
Scenergy::XMLFile::~XMLFile(void){

	if(XML){
		ActiveList.remove(this);
		delete XML;	//delete the XML parser after usage
	}
}

/**
* @brief	Iterate through all active XMLFile load and process
* @param	void
* @return	void
*/
void Scenergy::XMLFile::Update(void){

	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
		(*ActiveListIterator)->Process();
	}

	//clean up inactive xmlfiles
	while (!InactiveQueue.empty()){	
		delete InactiveQueue.front();
		InactiveQueue.pop();
	}

}

/**
* @brief	Process by State
* @param	void
* @return	void
*/
void Scenergy::XMLFile::Process(void){

	switch(State){

		case IDLE:
			break;

		case LOAD:
			State = LOADING;
			break;

		case LOADING:
			if(Parse() < 1) State = COMPLETE;
			break;

		case LOADALL:
			StartTime = dbTimer();
			while(dbTimer() - StartTime < LoadRate && State == LOADALL){
				if(Parse() < 1) State = COMPLETE;
			}
			break;

		case DOWNLOADING:
			if(HTTPFile->State == S3GE::File::COMPLETE){
				XML = createIrrXMLReader((char*)HTTPFile->Filename.data());
				HTTPFile->Destroy();		
				NodeCount = StartTime = 0;
				LoadRate = 18000;
				State = LOADALL;
			}
			break;

		case COMPLETE:

			//xmlpage load complete, draw default gizmos to Canvas

			while (!LoadedGizmoQueue.empty()){

				//Set Start State
				LoadedGizmoQueue.front()->EventState.State = GizmoPropertyMap[LoadedGizmoQueue.front()].StartEventState;

				switch(LoadedGizmoQueue.front()->Type){

					case MAUI_GIZMO_TYPE_WIDGET:
						break;

					case MAUI_GIZMO_TYPE_GIZMO:	
						if(LoadedGizmoQueue.front()->Body->PhysicsFlag){
							//update 2D Physics for Orientation accuracy
							LoadedGizmoQueue.front()->Body->Physics->Update(LoadedGizmoQueue.front()->Body->Position, LoadedGizmoQueue.front()->Body->Angle);
						}
						//Set to Start Sprite
						if(LoadedGizmoQueue.front()->EventAction[LoadedGizmoQueue.front()->EventState.State]->Sprite != NULL){
							//capture on fly
							if(!LoadedGizmoQueue.front()->EventAction[LoadedGizmoQueue.front()->EventState.State]->Sprite->dbImageID){
								LoadedGizmoQueue.front()->ImageCapture(LoadedGizmoQueue.front()->EventState.State);
							} else {
								dbSetSpriteImage(LoadedGizmoQueue.front()->SpriteID, LoadedGizmoQueue.front()->EventAction[LoadedGizmoQueue.front()->EventState.State]->Sprite->dbImageID);
							}
						}
						break;

					case MAUI_GIZMO_TYPE_WIZMO:
						//Set to Start Sprite
						if(dbObjectExist(LoadedGizmoQueue.front()->EventAction[LoadedGizmoQueue.front()->EventState.State]->Sprite->dbObjectID)){
							//capture on fly
							if(!LoadedGizmoQueue.front()->EventAction[LoadedGizmoQueue.front()->EventState.State]->Sprite->dbImageID){
								LoadedGizmoQueue.front()->TextureCapture(LoadedGizmoQueue.front()->EventState.State);
							} else {
								dbTextureObject(LoadedGizmoQueue.front()->EventAction[LoadedGizmoQueue.front()->EventState.State]->Sprite->dbObjectID, LoadedGizmoQueue.front()->EventAction[LoadedGizmoQueue.front()->EventState.State]->Sprite->dbImageID);
							}
						}

				}

				// line wrap
				if(!LoadedGizmoQueue.front()->VariableMap["linecount"].empty()){
					LoadedGizmoQueue.front()->LineTextWrap(1, MAUI_GIZMO_VALUE_LINE_DIRECTION_DOWN);
					//LoadedGizmoQueue.front()->LineTextCapture(MAUI_EVENT_STATE_IDLE, false);
				}

				LoadedGizmoQueue.front()->State = MAUI::Gizmo::ACTIVE;
				LoadedGizmoQueue.pop();
				
			}

			//set text to default
			if(MAUI::Style::NameMap[""]!=NULL){
				MAUI::Style::NameMap[""]->EventAction[MAUI_EVENT_STATE_IDLE]->dx9FontSet();
			}

			//Pointer/Caret gizmos
			if(MAUI::Gizmo::Caret !=  NULL){
				MAUI::Gizmo::ActiveList.remove(MAUI::Gizmo::Caret);
				MAUI::Gizmo::ActiveList.push_back(MAUI::Gizmo::Caret);
			}

			if(MAUI::Gizmo::Pointer != NULL){
				MAUI::Gizmo::ActiveList.remove(MAUI::Gizmo::Pointer);
				MAUI::Gizmo::ActiveList.push_back(MAUI::Gizmo::Pointer);
			}

			InactiveQueue.push(this);
			break;
				
	}

}

/**
* @ brief	Parses each Scenergy XML Tag; Returns 0 when no more nodes are read;
* @param	void
* @return	0 if no more nodes
*/
int Scenergy::XMLFile::Parse(void){

	if(!XML->read()){return(0);} //get next node else return false

	map<string, string> attribute;
	vector< pair<int,string> > tagvector;
	string tagname;
	string value;
	string taskname;
	int actionstate;
	float width;
	float height;
	float depth;

	string fontname; //testvars
	int fontID;

	switch(XML->getNodeType()){
	
		case EXN_NONE: 	//0 - No XML node. This is usually the node if you did not read anything yet.
			break;//EXN_NONE

		case EXN_ELEMENT: 	//1 - A XML element, like <foo>.

			tagname = XML->getNodeData();

			NodeCount++;

			//specialty attributes
			if(XML->getAttributeValue("width")){
				AttributeValueSafeGet("width").compare("screen")==0 ? width = dbScreenWidth(): width = AttributeValueAsFloatGet("width");
			}

			if(XML->getAttributeValue("height")){
				AttributeValueSafeGet("height").compare("screen")==0 ? height = dbScreenHeight() : height = AttributeValueAsFloatGet("height");
			}

			if(XML->getAttributeValue("depth")){
				AttributeValueSafeGet("depth").compare("screen")==0 ? depth = dbScreenDepth() : depth = AttributeValueAsFloatGet("depth");
			}
	
			switch(TagNameMap[tagname]){
//<s3ge>
				case S3GXL_TAG_S3GE:
					value = "1.0";
					break;
//<state>				
				case S3GXL_TAG_STATE:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){

//<s3ge><state>
						case S3GXL_TAG_S3GE:
							value = AttributeValueSafeGet("name");
							MAUI::ESM::StateNameAdd(value);
							break;

//<gizmo><state>
						case S3GXL_TAG_GIZMO:
							//set default starting State
							MAUI::Gizmo::NameMap[tagvector[0].second]->EventState.State = MAUI::ESM::StateNameMap[AttributeValueSafeGet("name")];
							break;
					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;

//<include>
				case S3GXL_TAG_INCLUDE:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){
//<s3ge><include>
						case S3GXL_TAG_S3GE:
							System::Load(AttributeValueSafeGet("src"),(bool)AttributeValueMap[AttributeValueSafeGet("all")], AttributeValueAsIntGet("rate"));
							break;

						default:
							SyntaxError("Expected Parent Tag to be <s3ge>");								
							break;

					}
					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<behavior>
				case S3GXL_TAG_BEHAVIOR:
					
					value = AttributeValueSafeGet("name");

					if(XML->getAttributeValue("append")){
						value = MAUI::Behavior::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}

					if(XML->getAttributeValue("ref")){
						//then copy from template
						if(MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")] != NULL){
							MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")]->Copy(value, AttributeValueSafeGet("description"));
						}
					} else {
						MAUI::Behavior::Create(value, AttributeValueSafeGet("description"));
					}

					if(XML->getAttributeValue("default")){
						if(AttributeValueMap[AttributeValueSafeGet("default")] == 1){ MAUI::Behavior::DefaultBehavior = MAUI::Behavior::NameMap[value];}
					}
					break;
//<transition>
				case S3GXL_TAG_TRANSITION:

					value = AttributeValueSafeGet("name");

					if(XML->getAttributeValue("append")){
						value = MAUI::Behavior::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}

					if(XML->getAttributeValue("ref")){
						//then copy from template
						if(MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")] != NULL){
							MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")]->Copy(value, AttributeValueSafeGet("description"));
						}
					} else {
						MAUI::Behavior::Create(value, AttributeValueSafeGet("description"));
					}

					if(XML->getAttributeValue("default")){
						if(AttributeValueMap[AttributeValueSafeGet("default")] == 1){ MAUI::Behavior::DefaultTransition = MAUI::Behavior::NameMap[value];}
					}
					break;
//<style>
				case S3GXL_TAG_STYLE:

					value = AttributeValueSafeGet("name");

					if(XML->getAttributeValue("append")){
						value = MAUI::Style::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}

					if(XML->getAttributeValue("ref")){
						//then copy from template
						if(MAUI::Style::NameMap[AttributeValueSafeGet("ref")] != NULL){
							MAUI::Style::NameMap[AttributeValueSafeGet("ref")]->Copy(value, AttributeValueSafeGet("description"));
						}
					} else {
						MAUI::Style::Create(value, AttributeValueSafeGet("description"));
					}

					if(XML->getAttributeValue("default")){
						if(AttributeValueMap[AttributeValueSafeGet("default")] == 1){ MAUI::Style::DefaultStyle = MAUI::Style::NameMap[value];}
					}
					break;
//<theme>
				case S3GXL_TAG_THEME:

					value = AttributeValueSafeGet("name");

					if(XML->getAttributeValue("append")){
						value = MAUI::Theme::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}

					if(XML->getAttributeValue("ref")){
						//then copy from template
						if(MAUI::Theme::NameMap[AttributeValueSafeGet("ref")] != NULL){
							MAUI::Theme::NameMap[AttributeValueSafeGet("ref")]->Copy(value, AttributeValueSafeGet("description"));
						}
					} else {
						MAUI::Theme::Create(value, AttributeValueSafeGet("description"));
					}

					if(XML->getAttributeValue("default")){
						if(AttributeValueMap[AttributeValueSafeGet("default")] == 1){ MAUI::Theme::DefaultTheme = MAUI::Theme::NameMap[value];}
					}
					break;
//<scheme>
				case S3GXL_TAG_SCHEME:

					value = AttributeValueSafeGet("name");

					if(XML->getAttributeValue("append")){
						value = MAUI::Scheme::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}

					if(XML->getAttributeValue("ref")){
						//then copy from template
						if(MAUI::Scheme::NameMap[AttributeValueSafeGet("ref")] != NULL){
							MAUI::Scheme::NameMap[AttributeValueSafeGet("ref")]->Copy(value, AttributeValueSafeGet("description"));
						}
					} else {
						MAUI::Scheme::Create(value, AttributeValueSafeGet("description"));
					}

					if(XML->getAttributeValue("default")){
						if(AttributeValueMap[AttributeValueSafeGet("default")] == 1){ MAUI::Scheme::DefaultScheme = MAUI::Scheme::NameMap[value];}
					}
					break;
//<canvas>
				case S3GXL_TAG_CANVAS:
					{
					value = AttributeValueSafeGet("name");
					
					if(XML->getAttributeValue("append")){
						value = MAUI::Canvas::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}
	
					//backdrop image;

					int backdropimageID = 0;					
					if(XML->getAttributeValue("backdropsrc")){
						string filename = AttributeValueSafeGet("backdropsrc");
						if(filename.find(".") == string::npos) backdropimageID = (int)dbVal((char*)filename.data());
						if(backdropimageID && dbImageExist(backdropimageID)){
							//intentional blank
						} else {

							switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

								case S3GE_FILE_FOUND:
									backdropimageID = dbImageResource->Add(filename);
									if(!dbImageExist(backdropimageID)){
										Core->Image->Create(backdropimageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
									}
									break;

							}

						}
					}

					if(XML->getAttributeValue("ref")){
						//then copy from template
					} else {
						MAUI::Canvas::Create(
							AttributeValueSafeGet("parent"), 
							value,
							AttributeValueSafeGet("description"),
							AttributeValueAsIntGet("camera"), 
							AttributeValueAsFloatGet("fov"),
							AttributeValueAsFloatGet("nearrange"),
							AttributeValueAsFloatGet("farrange"),
							width/height,
							(bool)AttributeValueMap[AttributeValueSafeGet("backdrop")], 
							dbRGB(AttributeValueAsIntGet("backdropcolorred"),AttributeValueAsIntGet("backdropcolorgreen"),AttributeValueAsIntGet("backdropcolorblue")), 
							backdropimageID
						);
					}

					if(XML->getAttributeValue("base")){
						if(AttributeValueMap[AttributeValueSafeGet("base")] == 1){ MAUI::Canvas::BaseCanvas = MAUI::Canvas::NameMap[value];}
					}

					MAUI::Canvas::NameMap[value]->ZoomFactor.x = AttributeValueAsFloatGet("zoomfactorx");
					MAUI::Canvas::NameMap[value]->ZoomFactor.y = AttributeValueAsFloatGet("zoomfactory");
					MAUI::Canvas::NameMap[value]->ZoomFactor.z = AttributeValueAsFloatGet("zoomfactorz");
					}
					break;
//<gizmo>
//<gizmo|widget|doodad|jigger|wizmo>
				case S3GXL_TAG_WIDGET:
				case S3GXL_TAG_DOODAD:
				case S3GXL_TAG_JIGGER:
				case S3GXL_TAG_WIZMO:
				case S3GXL_TAG_GIZMO:

					value = AttributeValueSafeGet("name");

					if(XML->getAttributeValue("append")){
						value = MAUI::Gizmo::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}

					if(MAUI::Gizmo::NameMap[value] == NULL){

						MAUI::Gizmo::Create(
							AttributeValueSafeGet("parent"), 
							value,
							AttributeValueSafeGet("description"), 
							(bool)AttributeValueAsIntGet("collision"), 
							(bool)AttributeValueAsIntGet("operate"),
							(bool)AttributeValueAsIntGet("transit"), 
							(bool)AttributeValueAsIntGet("active"), 
							(bool)AttributeValueAsIntGet("visible"), 
							(bool)AttributeValueAsIntGet("audio")
						);
/*						
						MAUI::Gizmo::Create(
							AttributeValueSafeGet("parent"), 
							value,
							AttributeValueSafeGet("description"), 
							//XML->getAttributeValue("process") ? (DWORD)AttributeValueAsIntGet("process") : 
							(AttributeValueAsBooleanGet("collision") ? MAUI::Gizmo::COLLISION : 0) | 
							(AttributeValueAsBooleanGet("operate") ? MAUI::Gizmo::OPERATE : 0) | 
							(AttributeValueAsBooleanGet("transit") ? MAUI::Gizmo::TRANSITION : 0) | 
							(AttributeValueAsBooleanGet("active") ? MAUI::Gizmo::ACTION : 0) | 
							(AttributeValueAsBooleanGet("visible") ? MAUI::Gizmo::VISIBLE : 0) | 
							(AttributeValueAsBooleanGet("audio") ? MAUI::Gizmo::AUDIBLE : 0)
							
						);

*/						
					}
					
					if(XML->getAttributeValue("ref")){
						//then copy from template
						MAUI::Gizmo::NameMap[value]->Mimic(MAUI::Gizmo::Reference(AttributeValueSafeGet("ref")));
					}

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){
//<gizmo><gizmo>
						case S3GXL_TAG_GIZMO:
							//make child Gizmo
							break;
//<form><gizmo>
						case S3GXL_TAG_FORM:
							//Add to HTTPForm GizmoList
							if(MAUI::HTTPForm::NameMap[tagvector[0].second] != NULL){
								MAUI::HTTPForm::NameMap[tagvector[0].second]->GizmoList.push_back(MAUI::Gizmo::NameMap[value]);
							}
							break;
//<gadget><gizmo>
						case S3GXL_TAG_GADGET:
							//add to Gadget GizmoList
							if(MAUI::Gadget::NameMap[tagvector[0].second] != NULL){
								MAUI::Gadget::NameMap[tagvector[0].second]->GizmoList.push_back(MAUI::Gizmo::NameMap[value]);
							}
							break;
//<reactor><gizmo>
						case S3GXL_TAG_REACTOR:
							//Add to Particle Gizmo to Reactor
							if(Illudium::Reactor::NameMap[tagvector[0].second] != NULL){
								Illudium::Reactor::NameMap[tagvector[0].second]->Add(value, AttributeValueAsIntGet("count") );
							}
							return(1);
							break;
					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));

					//Set Type
					if(XML->getAttributeValue("type")){
						MAUI::Gizmo::NameMap[value]->Type = AttributeValueMap[AttributeValueSafeGet("type")];
					} else {
						//inherit from parent
						if(XML->getAttributeValue("parent")){
							MAUI::Gizmo::NameMap[value]->Type = MAUI::Gizmo::NameMap[AttributeValueSafeGet("parent")]->Type;
						} else {
							//default
							MAUI::Gizmo::NameMap[value]->Type = AttributeValueMap[tagname];
						}
					}
					//treat all types as <gizmo>
					tagname = "gizmo";

					//collision debug flag
					if(XML->getAttributeValue("debug")){ 
						MAUI::Gizmo::NameMap[value]->DebugFlag = (bool)AttributeValueAsIntGet("debug");
					}

					//base
					if(XML->getAttributeValue("base")){
						if(AttributeValueMap[AttributeValueSafeGet("base")] == 1){ MAUI::Gizmo::BaseGizmo = MAUI::Gizmo::NameMap[value];}
					}

					//form reference
					if(XML->getAttributeValue("form")){
						if(MAUI::HTTPForm::NameMap[AttributeValueSafeGet("form")] != NULL){
							MAUI::HTTPForm::NameMap[AttributeValueSafeGet("form")]->GizmoList.push_back(MAUI::Gizmo::NameMap[value]);					
						}
					}
						
					//form value
					if(XML->getAttributeValue("value")){
						MAUI::Gizmo::NameMap[value]->VariableMap["value"] = AttributeValueSafeGet("value");
					}

					//Pointer
					if(XML->getAttributeValue("pointer")){
						if(AttributeValueMap[AttributeValueSafeGet("pointer")] == 1){
							MAUI::Gizmo::Pointer = MAUI::Gizmo::NameMap[value]; 
						}
					}

					//Caret
					if(XML->getAttributeValue("caret")){
						if(AttributeValueMap[AttributeValueSafeGet("caret")] == 1){MAUI::Gizmo::Caret = MAUI::Gizmo::NameMap[value];}
					}

					//InputDevice setup
					if(XML->getAttributeValue("inputdevice")){
						MAUI::Gizmo::NameMap[value]->InputDevice = MAUI::InputDevice::NameMap[AttributeValueSafeGet("inputdevice")];
						MAUI::Gizmo::NameMap[value]->ControllerType = MAUI_GIZMO_CONTROLLER_TYPE_INPUTDEVICE;
					}

					//Create default EventAction
					if(MAUI::Gizmo::NameMap[value]->EventAction[MAUI_EVENT_STATE_IDLE] == NULL){
						MAUI::Gizmo::NameMap[value]->EventAction[MAUI_EVENT_STATE_IDLE] = new MAUI::Gizmo::EventScript;
					}

					//Create Sprite
					switch(MAUI::Gizmo::NameMap[value]->Type){

						case MAUI_GIZMO_TYPE_GIZMO:
							MAUI::Gizmo::NameMap[value]->SpriteID = dbSpriteResource->Pop();
							break;

						case MAUI_GIZMO_TYPE_WIZMO:
							MAUI::Gizmo::NameMap[value]->SpriteID = 0;
							break;
							
					}
					
					MAUI::Gizmo::NameMap[value]->State = MAUI::Gizmo::LOADING;
					LoadedGizmoQueue.push(MAUI::Gizmo::NameMap[value]);

					// if(AttributeValueSafeGet("form") == "formgizmoname1,formgizmoname2,..."){//}
					break;
//<gadget>
				case S3GXL_TAG_GADGET:

					value = AttributeValueSafeGet("name");

					if(XML->getAttributeValue("append")){
						value = MAUI::Gadget::NameMap[AttributeValueSafeGet("parent")]->Name;
						value.append(AttributeValueSafeGet("append"));
					}

					if(XML->getAttributeValue("ref")){
						//then copy from template
						if(MAUI::Gadget::NameMap[AttributeValueSafeGet("ref")] != NULL){
							MAUI::Gadget::NameMap[AttributeValueSafeGet("ref")]->Copy();
						}					
						
					} else {
						MAUI::Gadget::Create(
							AttributeValueSafeGet("parent"), 
							value,
							AttributeValueSafeGet("description"), 
							(bool)AttributeValueAsIntGet("collision"), 
							(bool)AttributeValueAsIntGet("operate"),
							(bool)AttributeValueAsIntGet("transit"), 
							(bool)AttributeValueAsIntGet("active"), 
							(bool)AttributeValueAsIntGet("visible"), 
							(bool)AttributeValueAsIntGet("audio")
						);
					}

					break;

//<meta>
				case S3GXL_TAG_META:
					break;
//<event>
				case S3GXL_TAG_EVENT:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					value = AttributeValueSafeGet("state");
					actionstate = MAUI::ESM::StateNameMap[value];

					switch(tagvector[0].first){
//<behavior><event>
						case S3GXL_TAG_BEHAVIOR:
							//Create EventAction
							if(MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate] == NULL){

								if(XML->getAttributeValue("ref")){
									if(MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")] != NULL){
										if(MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate] != NULL){
											MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate] = MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate]->Copy();
										}
									}
								} else {
									MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate] = new MAUI::Behavior::EventScript;
									//parent
									if(XML->getAttributeValue("parent")){
										MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate]->Inherit(MAUI::Behavior::NameMap[AttributeValueSafeGet("parent")]->EventAction[actionstate]);
									}
								}

							}
							break;
//<transition><event>
						case S3GXL_TAG_TRANSITION:
							//Create EventAction
							if(MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate] == NULL){

								if(XML->getAttributeValue("ref")){
									if(MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")] != NULL){
										if(MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate] != NULL){
											MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate] = MAUI::Behavior::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate]->Copy();
										}
									}
								} else {
									MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate] = new MAUI::Behavior::EventScript;
									//parent
									if(XML->getAttributeValue("parent")){
										MAUI::Behavior::NameMap[tagvector[0].second]->EventAction[actionstate]->Inherit(MAUI::Behavior::NameMap[AttributeValueSafeGet("parent")]->EventAction[actionstate]);
									}
								}

							}
							break;
//<style><event>
						case S3GXL_TAG_STYLE:

							if(MAUI::Style::NameMap[tagvector[0].second]->EventAction[actionstate] == NULL){

								if(XML->getAttributeValue("ref")){
									if(MAUI::Style::NameMap[AttributeValueSafeGet("ref")] != NULL){
										if(MAUI::Style::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate] != NULL){
											MAUI::Style::NameMap[tagvector[0].second]->EventAction[actionstate] = MAUI::Style::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate]->Copy();
										}
									}
								} else {
									MAUI::Style::NameMap[tagvector[0].second]->EventAction[actionstate] = new MAUI::Style::EventScript;
									//parent
									if(XML->getAttributeValue("parent")){
										MAUI::Style::NameMap[tagvector[0].second]->EventAction[actionstate]->Inherit(MAUI::Style::NameMap[AttributeValueSafeGet("parent")]->EventAction[actionstate]);
									}
								}

							}
							break;
//<theme><event>
						case S3GXL_TAG_THEME:
							//Create EventAction
							if(MAUI::Theme::NameMap[tagvector[0].second]->EventAction[actionstate] == NULL){

								if(XML->getAttributeValue("ref")){
									if(MAUI::Theme::NameMap[AttributeValueSafeGet("ref")] != NULL){
										if(MAUI::Theme::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate] != NULL){
											MAUI::Theme::NameMap[tagvector[0].second]->EventAction[actionstate] = MAUI::Theme::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate]->Copy();
										}
									}
								} else {
									MAUI::Theme::NameMap[tagvector[0].second]->EventAction[actionstate] = new MAUI::Theme::EventScript;
									//parent
									if(XML->getAttributeValue("parent")){
										MAUI::Theme::NameMap[tagvector[0].second]->EventAction[actionstate]->Inherit(MAUI::Theme::NameMap[AttributeValueSafeGet("parent")]->EventAction[actionstate]);
									}
								}

							}
							break;
//<scheme><event>
						case S3GXL_TAG_SCHEME:

							//Create EventAction
							if(MAUI::Scheme::NameMap[tagvector[0].second]->EventAction[actionstate] == NULL){

								if(XML->getAttributeValue("ref")){
									if(MAUI::Scheme::NameMap[AttributeValueSafeGet("ref")] != NULL){
										if(MAUI::Scheme::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate] != NULL){
											MAUI::Scheme::NameMap[tagvector[0].second]->EventAction[actionstate] = MAUI::Scheme::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate]->Copy();
										}
									}
								} else {
									MAUI::Scheme::NameMap[tagvector[0].second]->EventAction[actionstate] = new MAUI::Scheme::EventScript;
									//parent
									if(XML->getAttributeValue("parent")){
										MAUI::Scheme::NameMap[tagvector[0].second]->EventAction[actionstate]->Inherit(MAUI::Scheme::NameMap[AttributeValueSafeGet("parent")]->EventAction[actionstate]);
									}
								}
							}

							//<audio> code

							break;
//<gizmo><event>
						case S3GXL_TAG_GIZMO:

							//Create EventAction
							if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate] == NULL){

								if(XML->getAttributeValue("ref")){
									if(MAUI::Gizmo::NameMap[AttributeValueSafeGet("ref")] != NULL){
										if(MAUI::Gizmo::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate] != NULL){
											MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate] = MAUI::Gizmo::NameMap[AttributeValueSafeGet("ref")]->EventAction[actionstate]->Copy();
										}
									}
								} else {
									MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate] = new MAUI::Gizmo::EventScript;
									//parent
									if(XML->getAttributeValue("parent")){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Inherit(MAUI::Gizmo::NameMap[AttributeValueSafeGet("parent")]->EventAction[actionstate]);
									}
								}

							}

							//start event state
							if(XML->getAttributeValue("start")){
								if(AttributeValueMap[AttributeValueSafeGet("start")] == 1){ GizmoPropertyMap[MAUI::Gizmo::NameMap[tagvector[0].second]].StartEventState = actionstate;}
							}

							//Behavior
							if(XML->getAttributeValue("behavior")){
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Behavior = MAUI::Behavior::NameMap[AttributeValueSafeGet("behavior")];
							} else if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Behavior != NULL) {
								//assign IDLE Behavior
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Behavior = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Behavior;
							} else {
								//assign default
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Behavior = MAUI::Behavior::NameMap[""];
							}

							//Transition
							if(XML->getAttributeValue("transition")){
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Transition = MAUI::Behavior::NameMap[AttributeValueSafeGet("transition")];
							} else if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Transition != NULL) {
								//assign IDLE Transition
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Transition = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Transition;
							} else {
								//assign default
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Transition = MAUI::Behavior::NameMap[""];
							}
							
							//Scheme
							if(XML->getAttributeValue("scheme")){
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Scheme = MAUI::Scheme::NameMap[AttributeValueSafeGet("scheme")];
							} else if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Scheme != NULL) {
								//assign IDLE Scheme
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Scheme = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Scheme;
							} else {
								//assign default
								MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Scheme = MAUI::Scheme::NameMap[""];
							}

							//Sprite
							switch(MAUI::Gizmo::NameMap[tagvector[0].second]->Type){
		
								case MAUI_GIZMO_TYPE_GIZMO:
								case MAUI_GIZMO_TYPE_WIZMO:		

									//Create Sprite
									if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite == NULL){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite = new MAUI::Sprite;
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->Inherit(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite);
									}

									//background
									if(XML->getAttributeValue("src")){
										string filename = AttributeValueSafeGet("src");
										int backdropimageID = 0;
										if(filename.find(".") == string::npos) backdropimageID = (int)dbVal((char*)filename.data());
										if(backdropimageID && dbImageExist(backdropimageID)){
												MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropImageID = backdropimageID;
										} else {
											switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

												case S3GE_FILE_FOUND:
													MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropImageID = dbImageResource->Add(filename);
													if(!dbImageExist(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropImageID)){
														Core->Image->Create(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL|S3GE::File::GET_FROM_NETWORK);
													}
													break;
											}
										}

										//BackdropImage alignment
										if(XML->getAttributeValue("src_x")|| XML->getAttributeValue("src_y")|| XML->getAttributeValue("src_xalign")|| XML->getAttributeValue("src_yalign")){
											MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->ImageOrientate(
												MAUI::Gizmo::NameMap[tagvector[0].second]->Body,
												MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropImageID,
												MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropImageAlign,
												AttributeValueAsFloatGet("src_x"),
												AttributeValueAsFloatGet("src_y"),
												0,
												AttributeValueMap[AttributeValueSafeGet("src_xalign")],
												AttributeValueMap[AttributeValueSafeGet("src_yalign")],
												AttributeValueMap[AttributeValueSafeGet("src_zalign")]									
											);
										}
									}

									//Theme
									if(XML->getAttributeValue("theme")){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropTheme = MAUI::Theme::NameMap[AttributeValueSafeGet("theme")];
									} else if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->BackdropTheme != NULL) {
										//assign IDLE Theme
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropTheme = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->BackdropTheme;
									} else {
										//assign default
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->BackdropTheme = MAUI::Theme::NameMap[""];
									}
	
									//Style
									if(XML->getAttributeValue("style")){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->CaptionStyle = MAUI::Style::NameMap[AttributeValueSafeGet("style")];
									} else if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->CaptionStyle != NULL) {
										//assign IDLE Style
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->CaptionStyle = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->CaptionStyle;
									} else {
										//assign default
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->CaptionStyle = MAUI::Style::NameMap[""];
									}

									//Caption All (Label)
									if(XML->getAttributeValue("label")){
										//copy IDLE caption to other EventAction[n]->Sprite->Caption
										map<int, MAUI::Gizmo::EventScript*>::iterator eventactioniterator;
										for(eventactioniterator = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction.begin(); eventactioniterator !=  MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction.end();  eventactioniterator++){
											//Caption
											(*eventactioniterator).second->Sprite->Caption = AttributeValueSafeGet("label");

											//Caption Type
											if(AttributeValueAsIntGet("captiontype")){
												(*eventactioniterator).second->Sprite->CaptionType = AttributeValueAsIntGet("captiontype");
											}

											//Caption Alignment
											if(XML->getAttributeValue("x")|| XML->getAttributeValue("y")|| XML->getAttributeValue("xalign")|| XML->getAttributeValue("yalign")){
												(*eventactioniterator).second->Sprite->CaptionOrientate(
													MAUI::Gizmo::NameMap[tagvector[0].second]->Body,
													AttributeValueAsFloatGet("x"),
													AttributeValueAsFloatGet("y"),
													0,
													AttributeValueMap[AttributeValueSafeGet("xalign")],
													AttributeValueMap[AttributeValueSafeGet("yalign")],
													AttributeValueMap[AttributeValueSafeGet("zalign")]									
												);
											}
										}
									}

									//Caption
									if(XML->getAttributeValue("caption")){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->Caption = AttributeValueSafeGet("caption");
									}

									//Caption Type
									if(AttributeValueAsIntGet("captiontype")){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->CaptionType = AttributeValueAsIntGet("captiontype");
									}

									//Caption alignment
									if(XML->getAttributeValue("x")|| XML->getAttributeValue("y")|| XML->getAttributeValue("xalign")|| XML->getAttributeValue("yalign")){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->CaptionOrientate(
											MAUI::Gizmo::NameMap[tagvector[0].second]->Body,
											AttributeValueAsFloatGet("x"),
											AttributeValueAsFloatGet("y"),
											0,
											AttributeValueMap[AttributeValueSafeGet("xalign")],
											AttributeValueMap[AttributeValueSafeGet("yalign")],
											AttributeValueMap[AttributeValueSafeGet("zalign")]									
										);
									}

									if(XML->getAttributeValue("icon_label")){
										
										//copy IDLE IconTheme to other EventAction[n]->Sprite->IconTheme
										map<int, MAUI::Gizmo::EventScript*>::iterator eventactioniterator;
										for(eventactioniterator = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction.begin(); eventactioniterator != MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction.end();  eventactioniterator++){
											
											//IconTheme
											(*eventactioniterator).second->Sprite->IconTheme = MAUI::Theme::NameMap[AttributeValueSafeGet("icon_label")];
				
											//Icon Theme/Image Alignment
											if(XML->getAttributeValue("icon_x")|| XML->getAttributeValue("icon_y")|| XML->getAttributeValue("icon_xalign")|| XML->getAttributeValue("icon_yalign")){

												(*eventactioniterator).second->Sprite->ImageOrientate(
													MAUI::Gizmo::NameMap[tagvector[0].second]->Body,
													(*eventactioniterator).second->Sprite->IconTheme->EventAction[(*eventactioniterator).first]->Border.Edge.Middle.Center.dbImageID,
													(*eventactioniterator).second->Sprite->IconImageAlign,
													AttributeValueAsFloatGet("icon_x"),
													AttributeValueAsFloatGet("icon_y"),
													0,
													AttributeValueMap[AttributeValueSafeGet("icon_xalign")],
													AttributeValueMap[AttributeValueSafeGet("icon_yalign")],
													AttributeValueMap[AttributeValueSafeGet("icon_zalign")]									
												);

											}
										}
									}
										
									//Icon Theme (per actionevent)
									if(XML->getAttributeValue("icon")){
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconTheme = MAUI::Theme::NameMap[AttributeValueSafeGet("icon")];
									} else if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->IconTheme != NULL) {
										//assign IDLE Theme
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconTheme = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->IconTheme;
									} else {
										//assign default
										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconTheme =  MAUI::Theme::DefaultTheme;//MAUI::Theme::NameMap[""];
									}

									//Icon Overlay (icon image overlay)
									if(XML->getAttributeValue("overlay")){
										string filename = AttributeValueSafeGet("overlay");
										int iconimageID = 0;
										if(filename.find(".") == string::npos) iconimageID = (int)dbVal((char*)filename.data());
										if(iconimageID && dbImageExist(iconimageID)){
												MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconImageID = iconimageID;
										} else {
											switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

												case S3GE_FILE_FOUND:
													MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconImageID = dbImageResource->Add(filename);
													if(!dbImageExist(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconImageID)){
														Core->Image->Create(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL|S3GE::File::GET_FROM_NETWORK);
													}
													break;
											}
										}

									}

									//Icon Theme/Image Alignment
									if(XML->getAttributeValue("icon_x")|| XML->getAttributeValue("icon_y")|| XML->getAttributeValue("icon_xalign")|| XML->getAttributeValue("icon_yalign")){
										
										D3DVECTOR size = {0.0f, 0.0f, 0.0f};
										S3GE::Image *image;

										//if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate] != NULL){
											if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite != NULL){
												//get largest w x h
												if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconTheme != NULL){
													if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconTheme->EventAction[actionstate]->Border.Edge.Middle.Center.dbImageID){
														image = Core->Image->Get(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconTheme->EventAction[actionstate]->Border.Edge.Middle.Center.dbImageID);
														if(image->ImageInfo.Width > size.x) size.x = image->ImageInfo.Width;
														if(image->ImageInfo.Height > size.y) size.y = image->ImageInfo.Height;															
													}
												}
												if(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconImageID){
													image = Core->Image->Get(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconImageID);
													if(image->ImageInfo.Width > size.x) size.x = image->ImageInfo.Width;
													if(image->ImageInfo.Height > size.y) size.y = image->ImageInfo.Height;
												}
										
											}
										//}

										MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->Orientate(
											MAUI::Gizmo::NameMap[tagvector[0].second]->Body,
											MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->IconImageAlign,
											size,
											AttributeValueAsFloatGet("icon_x"),
											AttributeValueAsFloatGet("icon_y"),
											0,
											AttributeValueMap[AttributeValueSafeGet("icon_xalign")],
											AttributeValueMap[AttributeValueSafeGet("icon_yalign")],
											AttributeValueMap[AttributeValueSafeGet("icon_zalign")]									
										);

									}
									
									if(MAUI::Gizmo::NameMap[tagvector[0].second]->Type == MAUI_GIZMO_TYPE_GIZMO){
										//capture image on fly
										if(XML->getAttributeValue("capture")){
											if(AttributeValueMap[AttributeValueSafeGet("capture")] == 1){ MAUI::Gizmo::NameMap[tagvector[0].second]->ImageCapture(actionstate);}
										}
									}
									break;

							}
			
							//Body (3D)
							switch(MAUI::Gizmo::NameMap[tagvector[0].second]->Type){

								case MAUI_GIZMO_TYPE_JIGGER:
								case MAUI_GIZMO_TYPE_WIZMO:

									if(XML->getAttributeValue("object")){
									
										if(S3GE::Object::NameMap[AttributeValueSafeGet("object")]){
											MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID = S3GE::Object::NameMap[AttributeValueSafeGet("object")];
										} else {
											SyntaxError("Object Name doesn't exist.");
										}

									} else {
		
										if(XML->getAttributeValue("objectsrc")){
											string filename = AttributeValueSafeGet("objectsrc");
											int dbObjectID = 0;
											if(filename.find(".") == string::npos) dbObjectID = (int)dbVal((char*)filename.data());
											if(dbObjectID && dbObjectExist(dbObjectID)){
												MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID = dbObjectID;
											} else {
	
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID = dbObjectResource->Add(filename);
														if(!dbObjectExist(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID)){
															dbLoadObject((char*)filename.data(),MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID);
														}
														break;

													case S3GE_FILE_NOTFOUND:
														MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID = dbObjectResource->Pop();
														if(!dbObjectExist(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID)){
															dbMakeObjectPlane(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID, 1.0, 1.0);
															dbSetObject(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID, 1, 0, 0, 0, 0, 0, 0);
														}
														break;
												}
											}
										} else {
											if(actionstate == MAUI_EVENT_STATE_IDLE){
												MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID = dbObjectResource->Pop();
												if(!dbObjectExist(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID)){
													dbMakeObjectPlane(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID, 1.0, 1.0);
													dbSetObject(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID, 1, 0, 0, 0, 0, 0, 0);
												}
											} else {
												MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID = MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->dbObjectID;
											}
										}
									}

									//orientation & physics setup
									if(actionstate == MAUI_EVENT_STATE_IDLE){
										
										//scale
										dbScaleObject(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Size.x, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Size.y, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Size.z);
										
										//position
										dbPositionObject(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Position.x, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Position.y, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Position.z);
	
										//rotation	
										dbRotateObject(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Angle.x, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Angle.y, MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Angle.z);
										
										//physics
										if(MAUI::Gizmo::NameMap[tagvector[0].second]->Body->PhysicsFlag){
											MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Physics->Create(MAUI::Gizmo::NameMap[tagvector[0].second]->EventAction[actionstate]->Sprite->dbObjectID);
										}

									}
									
									if(MAUI::Gizmo::NameMap[tagvector[0].second]->Type == MAUI_GIZMO_TYPE_WIZMO){
										//capture texture on fly
										if(XML->getAttributeValue("capture")){
											if(AttributeValueMap[AttributeValueSafeGet("capture")] == 1){MAUI::Gizmo::NameMap[tagvector[0].second]->TextureCapture(actionstate);}
										}
									} else {
										//Jigger: delete graphical object maintain object reference for physics
									}

							}
							break;

						default:
							return(SyntaxError("Expected Parent Tag to be <gizmo>,<behavior>,<transition>,<style>,<theme>,<scheme>"));
					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<inputdevice>
				case S3GXL_TAG_INPUTDEVICE:
					
					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){
//<s3ge><inputdevice>
						case S3GXL_TAG_S3GE:
							//define input InputDevice periphial and input

							value = AttributeValueSafeGet("name");

							if(XML->getAttributeValue("append")){
								value = MAUI::InputDevice::NameMap[AttributeValueSafeGet("parent")]->Name;
								value.append(AttributeValueSafeGet("append"));
							}

							if(XML->getAttributeValue("ref")){
								//then copy from template
							} //else create normally

							MAUI::InputDevice::Create(
								AttributeValueSafeGet("parent"), 
								value, 
								AttributeValueSafeGet("description"), 
								AttributeValueMap[AttributeValueSafeGet("type")]
							);
							break;
//<canvas><inputdevice>
						case S3GXL_TAG_CANVAS:
							break;
//<gizmo><inputdevice>
						case S3GXL_TAG_GIZMO:
							//Create a InputDevice, if not null error
							break;

						default:
							return(SyntaxError("Expected Parent Tag to be <s3ge><canvas><gizmo>"));

					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<variable>
				case S3GXL_TAG_VARIABLE:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){
//<gizmo><variable>
						case S3GXL_TAG_GIZMO:

							//sets Gizmo variable/value pair
							MAUI::Gizmo::VariableSet(MAUI::Gizmo::NameMap[tagvector[0].second],AttributeValueSafeGet("name"),AttributeValueSafeGet("value"));
							break;

					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<orientate>
				case S3GXL_TAG_ORIENTATE:
					//reference;x;y;z;width;height;depth;xalign;yalign;zalign;left;right;bottom;front;back

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){
//<gizmo><orientate>
						case S3GXL_TAG_GIZMO:

							if(MAUI::Gizmo::NameMap[tagvector[0].second]->Type == MAUI_GIZMO_TYPE_WIDGET) break;

							//Create a Body, if not null error
							if(MAUI::Gizmo::NameMap[tagvector[0].second]->Body != NULL){
								SyntaxErrorMessage = tagvector[0].second;
								SyntaxErrorMessage.append(" Physics Body previously defined.");
								return(SyntaxError(SyntaxErrorMessage));
							} //to be replaced with redef

							if(XML->getAttributeValue("ref")){
								//then copy from template
							} //else create normally

							MAUI::Gizmo::NameMap[tagvector[0].second]->Body = MAUI::Body::Create(
								AttributeValueMap[AttributeValueSafeGet("type")],
								-1,
								0,
								AttributeValueAsFloatGet("x"),
								AttributeValueAsFloatGet("y"),
								AttributeValueAsFloatGet("z"),
								width,
								height,
								depth,
								AttributeValueAsFloatGet("anglex"),
								AttributeValueAsFloatGet("angley"),
								AttributeValueAsFloatGet("anglez")
							);
							
							//recalc Body pos and size 
							 
							//auto shape, calculate center and zoom
							switch(MAUI::Gizmo::NameMap[tagvector[0].second]->Type){
								case MAUI_GIZMO_TYPE_DOODAD:
								case MAUI_GIZMO_TYPE_GIZMO:
									MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Center(AttributeValueSafeGet("canvas"));
									MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Zoom(AttributeValueSafeGet("canvas"));
									break;
							}

							//auto alignment
							MAUI::Gizmo::NameMap[tagvector[0].second]->Body->Orientate(
								AttributeValueSafeGet("ref"),
								AttributeValueAsFloatGet("x"),
								AttributeValueAsFloatGet("y"),
								AttributeValueAsFloatGet("z"),
								AttributeValueMap[AttributeValueSafeGet("xalign")],
								AttributeValueMap[AttributeValueSafeGet("yalign")],
								AttributeValueMap[AttributeValueSafeGet("zalign")]
							);
							break;
//<canvas><orientate>
						case S3GXL_TAG_CANVAS:
							//Create a Body, if not null error
							if(MAUI::Canvas::NameMap[tagvector[0].second]->Body != NULL){ 
								SyntaxErrorMessage = tagvector[0].second;
								SyntaxErrorMessage.append(" Physics Body previously defined.");
								return(SyntaxError(SyntaxErrorMessage));
							} //to be replaced with redef

							if(XML->getAttributeValue("ref")){
								//then copy from template
							} //else create normally

							MAUI::Canvas::NameMap[tagvector[0].second]->Body = MAUI::Body::Create(
								AttributeValueMap[AttributeValueSafeGet("type")],
								-1,
								0,
								AttributeValueAsFloatGet("x"),
								AttributeValueAsFloatGet("y"),
								AttributeValueAsFloatGet("z"),
								width,
								height,
								depth,
								AttributeValueAsFloatGet("anglex"),
								AttributeValueAsFloatGet("angley"),
								AttributeValueAsFloatGet("anglez")
							);
							break;

					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<physics>
				case S3GXL_TAG_PHYSICS:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					value = tagvector[0].second;

					switch(tagvector[0].first){
//<orientate><physics>
						case S3GXL_TAG_ORIENTATE:

							tagvector.push_back(ParseStack.top());
							ParseStack.pop();
							
							switch(tagvector[1].first){
//<gizmo><orientate><physics>
								case S3GXL_TAG_GIZMO:

									if(MAUI::Gizmo::NameMap[tagvector[1].second]->Body != NULL){

										//Create Physics collision
										switch(MAUI::Gizmo::NameMap[tagvector[1].second]->Type){

											case MAUI_GIZMO_TYPE_DOODAD:
											case MAUI_GIZMO_TYPE_GIZMO:
												
												//select Physics type
												switch(AttributeValueMap[AttributeValueSafeGet("type")]){

													case MAUI_BODY_PHYSICS2D_TYPE_WORLD:

														if(XML->getAttributeValue("ref")){
															//then copy from template
														} //else create normally

														MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics = new MAUI::Body::CanvasPhysics2D;
														MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics->Create(
															MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Position,
															MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Size,
															AttributeValueAsFloatGet("gravityx"),
															AttributeValueAsFloatGet("gravityy"),
															(float32)(1.0/AttributeValueAsFloatGet("timestep")),
															AttributeValueAsIntGet("iteration"),
															(bool)AttributeValueMap[AttributeValueSafeGet("allowsleep")]
														);
														//set user data
														MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics->UserDataSet(MAUI::Gizmo::NameMap[tagvector[1].second]);
														break;

													case MAUI_BODY_PHYSICS2D_TYPE_JOINT_MOUSE:
														
														if(XML->getAttributeValue("ref")){
															//then copy from template
														} //else create normally

														MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics = new MAUI::Body::PointerPhysics2D;
														MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics->Create(
															AttributeValueSafeGet("canvas")
														);
														break;

													case MAUI_BODY_PHYSICS2D_TYPE_BODY:
													default:

														if(XML->getAttributeValue("ref")){
															//then copy from template
														} //else create normally

														MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics = new MAUI::Body::GizmoPhysics2D;
														MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics->Create(
															AttributeValueSafeGet("canvas"),
															0,
															MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Position,
															MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Size,
															MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Angle,
															AttributeValueAsFloatGet("friction"),
															AttributeValueAsFloatGet("density"),
															AttributeValueAsFloatGet("restitution"),
															(bool)AttributeValueMap[AttributeValueSafeGet("noresponse")]
														);
												
												}
												//if (AttributeValueMap[XML->getAttributeValue("collisiononly")] == 1) { isSensor == false }

												MAUI::Gizmo::NameMap[tagvector[1].second]->Body->PhysicsFlag = true;
												break;
						
											case MAUI_GIZMO_TYPE_JIGGER:		
											case MAUI_GIZMO_TYPE_WIZMO:
		
												//Setup 3D Physics

												if(XML->getAttributeValue("ref")){
													//then copy from template
												} //else create normally

												MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics = new MAUI::Body::GizmoPhysics3D;
												MAUI::Gizmo::NameMap[tagvector[1].second]->Body->Physics->Set(
													AttributeValueMap[AttributeValueSafeGet("type")],
													AttributeValueAsIntGet("dynamic"),
													AttributeValueAsFloatGet("density"),
													AttributeValueAsFloatGet("maxstep"),
													AttributeValueAsFloatGet("slopelimit"),
													AttributeValueAsFloatGet("radius"),
													AttributeValueAsIntGet("yoffset"),
													AttributeValueAsFloatGet("length"),
													AttributeValueAsFloatGet("sizex"),
													AttributeValueAsFloatGet("sizey"),
													AttributeValueAsFloatGet("sizez")
												);														

												MAUI::Gizmo::NameMap[tagvector[1].second]->Body->PhysicsFlag = true;

												break;

										}

									}
									break;
//<canvas><orientate><physics>
								case S3GXL_TAG_CANVAS:

									if(MAUI::Canvas::NameMap[tagvector[1].second]->Body != NULL){

										//Create Physics collision
										switch(MAUI::Canvas::NameMap[tagvector[1].second]->Type){

											case MAUI_GIZMO_TYPE_GIZMO:
												
												if(XML->getAttributeValue("ref")){
													//then copy from template
												} //else create normally

												MAUI::Canvas::NameMap[tagvector[1].second]->Body->Physics = new MAUI::Body::CanvasPhysics2D;
												MAUI::Canvas::NameMap[tagvector[1].second]->Body->Physics->Create(
													MAUI::Canvas::NameMap[tagvector[1].second]->Body->Position, 
													MAUI::Canvas::NameMap[tagvector[1].second]->Body->Size, 
													AttributeValueAsFloatGet("gravityx"), 
													AttributeValueAsFloatGet("gravityy"),
													(float32)(1.0/AttributeValueAsFloatGet("timestep")), 
													AttributeValueAsIntGet("iterations"),
													(bool)AttributeValueMap[AttributeValueSafeGet("allowsleep")]
												);

												MAUI::Canvas::NameMap[tagvector[1].second]->Body->PhysicsFlag = true;
												break;

										}
									}
									break;

							}

							ParseStack.push(make_pair(tagvector[1].first,tagvector[1].second));
							break;

						default:
							return(SyntaxError("Expected Parent Tag to be <gizmo> or <canvas>"));

					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<border>
				case S3GXL_TAG_BORDER:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					value = tagvector[0].second;
					actionstate = MAUI::ESM::StateNameMap[value];

					switch(tagvector[0].first){
//<event><border>
						case S3GXL_TAG_EVENT:

							tagvector.push_back(ParseStack.top());
							ParseStack.pop();

							switch(tagvector[1].first){
//<theme><event><border>
								case S3GXL_TAG_THEME:

									if(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]!=NULL){
												
										if(XML->getAttributeValue("topleftref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("topleftsrc")){
											string filename = AttributeValueSafeGet("topleftsrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.dbImageID = dbImageID;
											} else {
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.dbImageID = dbImageResource->Add(filename);
												if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.dbImageID)){
													Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.Size = AttributeValueAsIntGet("topleftsize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.Color = dbRGB(AttributeValueAsIntGet("topleftred"),AttributeValueAsIntGet("topleftgreen"),AttributeValueAsIntGet("topleftblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.Alpha = AttributeValueAsIntGet("topleftalpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.LineStyle = AttributeValueAsIntGet("topleftlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.Tile = AttributeValueAsIntGet("toplefttile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Left.Transparency = AttributeValueAsIntGet("toplefttransparency");

										if(XML->getAttributeValue("topcenterref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("topcentersrc")){
											string filename = AttributeValueSafeGet("topcentersrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.Size = AttributeValueAsIntGet("topcentersize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.Color = dbRGB(AttributeValueAsIntGet("topcenterred"),AttributeValueAsIntGet("topcentergreen"),AttributeValueAsIntGet("topcenterblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.Alpha = AttributeValueAsIntGet("topcenteralpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.LineStyle = AttributeValueAsIntGet("topcenterlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.Tile = AttributeValueAsIntGet("topcentertile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Center.Transparency = AttributeValueAsIntGet("topcentertransparency");
		
										if(XML->getAttributeValue("toprightref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("toprightsrc")){
											string filename = AttributeValueSafeGet("toprightsrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.Size = AttributeValueAsIntGet("toprightsize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.Color = dbRGB(AttributeValueAsIntGet("toprightred"),AttributeValueAsIntGet("toprightgreen"),AttributeValueAsIntGet("toprightblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.Alpha = AttributeValueAsIntGet("toprightalpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.LineStyle = AttributeValueAsIntGet("toprightlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.Tile = AttributeValueAsIntGet("toprighttile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Top.Right.Transparency = AttributeValueAsIntGet("toprighttransparency");
										if(XML->getAttributeValue("topleftref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("middleleftsrc")){
											string filename = AttributeValueSafeGet("middleleftsrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.Size = AttributeValueAsIntGet("middleleftsize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.Color = dbRGB(AttributeValueAsIntGet("middleleftred"),AttributeValueAsIntGet("middleleftgreen"),AttributeValueAsIntGet("middleleftblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.Alpha = AttributeValueAsIntGet("middleleftalpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.LineStyle = AttributeValueAsIntGet("middleleftlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.Tile = AttributeValueAsIntGet("middlelefttile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Left.Transparency = AttributeValueAsIntGet("middlelefttransparency");

										if(XML->getAttributeValue("middlecenterref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("middlecentersrc")){
											string filename = AttributeValueSafeGet("middlecentersrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}

										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.Size = AttributeValueAsIntGet("middlecentersize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.Color = dbRGB(AttributeValueAsIntGet("middlecenterred"),AttributeValueAsIntGet("middlecentergreen"),AttributeValueAsIntGet("middlecenterblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.Alpha = AttributeValueAsIntGet("middlecenteralpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.LineStyle = AttributeValueAsIntGet("middlecenterlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.Tile = AttributeValueAsIntGet("middlecentertile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Center.Transparency = AttributeValueAsIntGet("middlecentertransparency");

										if(XML->getAttributeValue("middlerightref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("middlerightsrc")){
											string filename = AttributeValueSafeGet("middlerightsrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.Size = AttributeValueAsIntGet("middlerightsize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.Color = dbRGB(AttributeValueAsIntGet("middlerightred"),AttributeValueAsIntGet("middlerightgreen"),AttributeValueAsIntGet("middlerightblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.Alpha = AttributeValueAsIntGet("middlerightalpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.LineStyle = AttributeValueAsIntGet("middlerightlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.Tile = AttributeValueAsIntGet("middlerighttile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Middle.Right.Transparency = AttributeValueAsIntGet("middlerighttransparency");

										if(XML->getAttributeValue("bottomleftref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("bottomleftsrc")){
											string filename = AttributeValueSafeGet("bottomleftsrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.Size = AttributeValueAsIntGet("bottomleftsize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.Color = dbRGB(AttributeValueAsIntGet("bottomleftred"),AttributeValueAsIntGet("bottomleftgreen"),AttributeValueAsIntGet("bottomleftblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.Alpha = AttributeValueAsIntGet("bottomleftalpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.LineStyle = AttributeValueAsIntGet("bottomleftlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.Tile = AttributeValueAsIntGet("bottomlefttile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Left.Transparency = AttributeValueAsIntGet("bottomlefttransparency");

										if(XML->getAttributeValue("bottomcenterref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("bottomcentersrc")){
											string filename = AttributeValueSafeGet("bottomcentersrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.Size = AttributeValueAsIntGet("bottomcentersize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.Color = dbRGB(AttributeValueAsIntGet("bottomcenterred"),AttributeValueAsIntGet("bottomcentergreen"),AttributeValueAsIntGet("bottomcenterblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.Alpha = AttributeValueAsIntGet("bottomcenteralpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.LineStyle = AttributeValueAsIntGet("bottomcenterlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.Tile = AttributeValueAsIntGet("bottomcentertile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Center.Transparency = AttributeValueAsIntGet("bottomcentertransparency");

										if(XML->getAttributeValue("bottomrightref")){
											//then copy from template
										} else {
										}

										if(XML->getAttributeValue("bottomrightsrc")){
											string filename = AttributeValueSafeGet("bottomrightsrc");
											int dbImageID = 0;
											if(filename.find(".") == string::npos) dbImageID = (int)dbVal((char*)filename.data());
											if(dbImageID && dbImageExist(dbImageID)){
												MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.dbImageID = dbImageID;
											} else {
												switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

													case S3GE_FILE_FOUND:
														MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.dbImageID = dbImageResource->Add(filename);
														if(!dbImageExist(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.dbImageID)){
															Core->Image->Create(MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, S3GE::File::GET_FROM_LOCAL | S3GE::File::GET_FROM_NETWORK);
														}
														break;

												}
											}
										}
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.Size = AttributeValueAsIntGet("bottomrightsize");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.Color = dbRGB(AttributeValueAsIntGet("bottomrightred"),AttributeValueAsIntGet("bottomrightgreen"),AttributeValueAsIntGet("bottomrightblue"));
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.Alpha = AttributeValueAsIntGet("bottomrightalpha");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.LineStyle = AttributeValueAsIntGet("bottomrightlinestyle");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.Tile = AttributeValueAsIntGet("bottomrighttile");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->Border.Edge.Bottom.Right.Transparency = AttributeValueAsIntGet("bottomrighttransparency");

										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->ColorKeyRed = AttributeValueAsIntGet("colorkeyred");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->ColorKeyGreen = AttributeValueAsIntGet("colorkeygreen");
										MAUI::Theme::NameMap[tagvector[1].second]->EventAction[actionstate]->ColorKeyBlue = AttributeValueAsIntGet("colorkeyblue");

									}
									break;

							}

							ParseStack.push(make_pair(tagvector[1].first,tagvector[1].second));
							break;
					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<audio>
				case S3GXL_TAG_AUDIO:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					value = tagvector[0].second;
					actionstate = MAUI::ESM::StateNameMap[value];

					switch(tagvector[0].first){
//<event><audio>
						case S3GXL_TAG_EVENT:

							tagvector.push_back(ParseStack.top());
							ParseStack.pop();

							switch(tagvector[1].first){
//<scheme><event><audio>
								case S3GXL_TAG_SCHEME:
									if(XML->getAttributeValue("src")){
										string filename = AttributeValueSafeGet("src");
										int audioID = -1;
										if(filename.find(".") == string::npos) audioID = (int)dbVal((char*)filename.data());
										if(audioID < 0){
											switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

												case S3GE_FILE_FOUND:
													audioID = 0;
													break;

												case S3GE_FILE_NOTFOUND:
													alertbox("Scenergy::XMLFile",filename,ALERTBOX_SEVERITY_ERROR);
													break;

											}
										}
										if(audioID > -1){
										
											MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->Type = AttributeValueMap[AttributeValueSafeGet("type")];
											MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->System = AttributeValueMap[AttributeValueSafeGet("system")];
											MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->Loop = AttributeValueAsIntGet("loop");

											//select sound system
											switch(AttributeValueMap[AttributeValueSafeGet("system")]){

												case MAUI_SCHEME_AUDIO_SYSTEM_OAW:
													//set up oaw audio
													break;

												case MAUI_SCHEME_AUDIO_SYSTEM_DGDK:
												default:
													//select sound type
													switch(AttributeValueMap[AttributeValueSafeGet("type")]){

														case MAUI_SCHEME_AUDIO_TYPE_SOUND:
															if(audioID && dbSoundExist(audioID)){
																MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID = audioID;
															} else {
																MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID = dbSoundResource->Add(filename);
																if(!dbSoundExist(MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID)){
																	dbLoadSound((char*)filename.data(),MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID);
																}
															}
															break;

														case MAUI_SCHEME_AUDIO_TYPE_MUSIC:
															if(audioID && dbMusicExist(audioID)){
																MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID = audioID;
															} else {
																MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID = dbMusicResource->Add(filename);
																if(!dbMusicExist(MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID)){
																	dbLoadMusic((char*)filename.data(),MAUI::Scheme::NameMap[tagvector[1].second]->EventAction[actionstate]->AudioID);
																}
															}
															break;
													}

											}
										}
									}
									break;

								default:
									return(SyntaxError("Expected Parent Tag to be <event>"));

							}

							ParseStack.push(make_pair(tagvector[1].first,tagvector[1].second));
							break;
					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<font>
				case S3GXL_TAG_FONT:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();
					
					switch(tagvector[0].first){
//<s3ge><font>
						case S3GXL_TAG_S3GE:
							//<font name="" src=""/>
							if(XML->getAttributeValue("name") && XML->getAttributeValue("src")){
								S3GE::FontArt::Load(AttributeValueSafeGet("name"),(char*)AttributeValueSafeGet("src").data(),AttributeValueAsIntGet("kern"));
							} else {
								if(XML->getAttributeValue("name") && XML->getAttributeValue("face")){
									Core->Text->FontCreate(
										AttributeValueSafeGet("name"),
										(char*)AttributeValueSafeGet("face").data(),
										AttributeValueAsIntGet("size"),
										AttributeValueAsIntGet("bold"),
										AttributeValueAsIntGet("italic"),
										AttributeValueAsIntGet("red"),
										AttributeValueAsIntGet("green"),
										AttributeValueAsIntGet("blue"),
										AttributeValueAsIntGet("alpha")
									);
								} else {
									SyntaxError("Expected FontArt Tag");
								}
							}
							break;
//<event><font>
						case S3GXL_TAG_EVENT:

							tagvector.push_back(ParseStack.top());
							ParseStack.pop();

							switch(tagvector[1].first){
//<style><event><font>
								case S3GXL_TAG_STYLE:
									fontname = AttributeValueSafeGet("name");
									fontID = Core->Text->FontGet(fontname);
									MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->Fontname = fontname;
									MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->FontID = fontID;
									if(S3GE::FontArt::NameMap[MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->Fontname] != NULL){
										MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->Type = MAUI_STYLE_FONT_TYPE_FONTART;
									}
									break;

							}

							ParseStack.push(make_pair(tagvector[1].first,tagvector[1].second));
							break;
					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;

//<font_properties:alpha|opaque|transparent|bold|italic>

				case S3GXL_TAG_ALPHA:
				case S3GXL_TAG_OPAQUE:
				case S3GXL_TAG_TRANSPARENT:
				case S3GXL_TAG_BOLD:
				case S3GXL_TAG_ITALIC:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();
					
					switch(tagvector[0].first){
//<event><font_properties>
						case S3GXL_TAG_EVENT:

							tagvector.push_back(ParseStack.top());
							ParseStack.pop();

							switch(tagvector[1].first){
//<style><event><font_properties>
								case S3GXL_TAG_STYLE:
									switch(TagNameMap[tagname]){
//<style><event><font_properties:alpha>
										case S3GXL_TAG_ALPHA:
											MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->Alpha = AttributeValueAsIntGet("value");
											break;
//<style><event><font_properties:opaque>
										case S3GXL_TAG_OPAQUE:
											MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->OpaqueFlag = true;
											break;
//<style><event><font_properties:transparent>
										case S3GXL_TAG_TRANSPARENT:
											MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->TransparentFlag = true;
											break;
//<style><event><font_properties:bold>
										case S3GXL_TAG_BOLD:
											MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->BoldFlag = true;
											break;
//<style><event><font_properties:italic>
										case S3GXL_TAG_ITALIC:
											MAUI::Style::NameMap[tagvector[1].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[0].second]]->ItalicFlag = true;
											break;
									}
									break;
							}
							
							ParseStack.push(make_pair(tagvector[1].first,tagvector[1].second));
							break;
					}

					ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
					break;
//<font>
				case S3GXL_TAG_FORM:

					value = AttributeValueSafeGet("name");
												
					if(XML->getAttributeValue("ref")){
							//then copy from template
					} //else create normally

					MAUI::HTTPForm::Create(
						value, 
						AttributeValueSafeGet("description"),
						AttributeValueMap[AttributeValueSafeGet("method")],
						AttributeValueSafeGet("host"),
						AttributeValueAsIntGet("port"),
						AttributeValueSafeGet("src"),
						AttributeValueSafeGet("path")
					);

					break;
//<object>
				case S3GXL_TAG_OBJECT:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){

						default: //allow anywhere
							{
								value = AttributeValueSafeGet("name");
								string filename = AttributeValueSafeGet("src");
								int objectID = 0;

								switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

									case S3GE_FILE_FOUND:

											objectID = S3GE::Object::NameMap[value];
											if(!objectID){
												objectID = dbObjectResource->Add(filename);
												S3GE::Object::NameMap[value] = objectID;
											}

											//setup object
											switch(AttributeValueMap[AttributeValueSafeGet("type")]){

												case S3GE_OBJECT_TYPE_MESH:
													dbLoadObject((char*)filename.data(), objectID);
													break;

												case S3GE_OBJECT_TYPE_TERRAIN:
													//from height map
													dbSetupTerrain();
													dbMakeObjectTerrain(objectID);
													dbSetTerrainHeightMap(objectID, (char*)filename.data());
													dbSetTerrainScale(objectID, 9.0f, 1.8f, 9.0f );
													dbSetTerrainLight(objectID, 1.0f, -0.25f, 1.0f, 1.0f, 1.0f, 0.78f, 0.5f );
													dbBuildTerrain(objectID);
													break;

												case S3GE_OBJECT_TYPE_MATRIX:
													//load from matrix
													break;
											}

										break;
				
									case S3GE_FILE_NOTFOUND:
										break;

									default:
										//HTTPFileID = fileexists;
										//State = DOWNLOADING;
										//ActiveList.push_back(this);
										break;

								}
								
							}
							break;
					}

					ParseStack.push(make_pair(tagvector[0].first, tagvector[0].second));
					break;

//<reactor>
				case S3GXL_TAG_REACTOR:

					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					switch(tagvector[0].first){
//<s3ge><reactor>
						case S3GXL_TAG_S3GE:
							value = AttributeValueSafeGet("name");

							if(XML->getAttributeValue("ref")){
								//then copy from template
								if(Illudium::Reactor::NameMap[AttributeValueSafeGet("ref")] != NULL){
									Illudium::Reactor::NameMap[AttributeValueSafeGet("ref")]->Copy(value, AttributeValueSafeGet("description"));
								}
							} else {
								Illudium::Reactor::Create(value, AttributeValueSafeGet("description"));
							}
							break;

						default:
							SyntaxError("Expected Parent Tag to be <s3ge>");								
							break;

					}
					
					ParseStack.push(make_pair(tagvector[0].first, tagvector[0].second));
					break;

			}

			//PUSH TAGNAME/VALUE PAIR TO PARSE STACK
			if(!XML->isEmptyElement()) {
				//if element is not an empty element, like <foo /> then push to stack

				ParseStack.push(make_pair(TagNameMap[tagname],value));

			}

			break;//EXN_ELEMENT
//</foo>		
		case EXN_ELEMENT_END: 	//2 -End of an XML element, like </foo>.
			if(!ParseStack.empty()){ 
				tagvector.push_back(ParseStack.top());
				ParseStack.pop();
			}
			break;//EXN_ELEMENT_END

//		case EXN_TEXT: 	//3 - Text within a XML element: <foo> this is the text. </foo>.
//			break;//EXT_TEXT
//		
//		case EXN_COMMENT: 	//4 - An XML comment like <!-- I am a comment --> or a DTD definition.
//			break;//EXN_COMMENT

//<![CDATA[
		case EXN_CDATA: 	//5 - An XML cdata section like <![CDATA[ this is some CDATA ]]>.
			//Get Element

			tagvector.push_back(ParseStack.top());
			ParseStack.pop();

			switch(tagvector[0].first){
//<script>
				case S3GXL_TAG_SCRIPT:
					
					//get Script Parent Tag
					tagvector.push_back(ParseStack.top());
					ParseStack.pop();

					string scriptcontent = (char*)XML->getNodeData(); //Preprocessor?

					switch(tagvector[1].first){
//<event><script>
						case S3GXL_TAG_EVENT:

							tagvector.push_back(ParseStack.top());
							ParseStack.pop();
							
							//task name
							taskname = tagvector[2].second;
							if(taskname.compare("")!=0 ){
								taskname.append("_");
							}
							taskname.append(tagvector[1].second);

							switch(tagvector[2].first){
//<behavior><event><script>
								case S3GXL_TAG_BEHAVIOR:
									taskname.insert(0,"behavior_");
									if(MAUI::Behavior::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task != NULL) MAUI::Behavior::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task->Shared--; 
									MAUI::Behavior::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task = new DarkLUA::Task(taskname,scriptcontent);
									break;
//<transition><event><script>
								case S3GXL_TAG_TRANSITION:
									taskname.insert(0,"transition_");
									if(MAUI::Behavior::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task != NULL) MAUI::Behavior::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task->Shared--; 
									MAUI::Behavior::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task = new DarkLUA::Task(taskname,scriptcontent);
									break;
//<style><event><script>
								case S3GXL_TAG_STYLE:
									taskname.insert(0,"style_");
									if(MAUI::Style::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task != NULL) MAUI::Style::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task->Shared--; 
									MAUI::Style::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task = new DarkLUA::Task(taskname,scriptcontent);
									break;
//<theme><event><script>
								case S3GXL_TAG_THEME:
									taskname.insert(0,"theme_");
									if(MAUI::Theme::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task != NULL) MAUI::Theme::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task->Shared--; 
									MAUI::Theme::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task = new DarkLUA::Task(taskname,scriptcontent);
									break;
//<scheme><event><script>
								case S3GXL_TAG_SCHEME:
									taskname.insert(0,"scheme_");
									if(MAUI::Scheme::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task != NULL) MAUI::Scheme::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task->Shared--; 
									MAUI::Scheme::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task = new DarkLUA::Task(taskname,scriptcontent);
									break;
//<gizmo><event><script>
								case S3GXL_TAG_GIZMO:
									taskname.insert(0,"gizmo_");
									//if(AttributeValueSafeGet("language")=="darklua"){
									if(MAUI::Gizmo::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task != NULL) MAUI::Gizmo::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task->Shared--; 
									MAUI::Gizmo::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task = new DarkLUA::Task(taskname,scriptcontent);
									MAUI::Gizmo::NameMap[tagvector[2].second]->EventAction[MAUI::ESM::StateNameMap[tagvector[1].second]]->Task->ExecutionType = (DarkLUA::Task::ExecutionTypes)AttributeValueAsIntGet("execution");
									//}
									break;

							}

							ParseStack.push(make_pair(tagvector[2].first,tagvector[2].second));
							break;

						default:
							//load task and execute
							DarkLUA::Task *task;
							task = new DarkLUA::Task("mauiscript",scriptcontent);
							task->Execute(DarkLUA::Task::RUNNING);
							delete task;
							break;
					
					}

					ParseStack.push(make_pair(tagvector[1].first,tagvector[1].second));
					break;

			}

			ParseStack.push(make_pair(tagvector[0].first,tagvector[0].second));
			break;//EXN_CDATA

		//case EXN_UNKNOWN: 	//6 - Unknown element. 
		//	break;//EXN_UNKNOWN

	}

	return(1);
}

/**
* @brief	generates XML parse error exit
* @param	void
* @return	0 if no more nodes
*/
int Scenergy::XMLFile::SyntaxError(string errormessage){

	alertbox("Scenergy XML Syntax Error",errormessage,ALERTBOX_SEVERITY_ERROR);

	return(SCENERGY_ERROR);
}

/**
* @brief	DarkLUA Preprocessor
* @param	void
* @return	string
*/
string Scenergy::XMLFile::AttributeValueSafeGet(char *attribute){

	return(DarkLUA::System::Embed("darklua:", "", "xmlembed", XML->getAttributeValueSafe(attribute), "xmlAttributeValue"));	

}

/**
* @brief	DarkLUA Preprocessor
* @param	void
* @return	Integer
*/
int Scenergy::XMLFile::AttributeValueAsIntGet(char *attribute){

	return((int)dbVal((char*)AttributeValueSafeGet(attribute).data()));	
}

/**
* @brief	DarkLUA Preprocessor
* @param	void
* @return	Boolean
*/
bool Scenergy::XMLFile::AttributeValueAsBooleanGet(char *attribute){

	return((bool)dbVal((char*)AttributeValueSafeGet(attribute).data()));	
}


/**
* @brief	DarkLUA Preprocessor
* @param	void
* @return	Float
*/
float Scenergy::XMLFile::AttributeValueAsFloatGet(char *attribute){

	return(dbVal((char*)AttributeValueSafeGet(attribute).data()));	

}

/* 
Scenergy XML

Tags
<s3ge>			Start Scenergy S3GXL file
<state>			Defines Event State Constant
<behavior>		Declares Gizmo Behavior for Gizmo Event Action States
<style>			Declares Gizmo 2D/3D Sprite Style Font
<theme>			Declares Gizmo 2D Sprite Theme Fill & Borders (Currently for 2D only)
<scheme>		Declares Gizmo Audio Scheme
<canvas>		Declares Canvas Object (Camera/Observer)
<inputdevice>		Declares Input Device
<hizmo>			Declares Gizmo
	<form>		Defines Gizmo as Form Input (Values are concenated and submitted via HTTP
	<submit>	Defines Gizmo as HTTP Submission Gizmo
	<reset>		Resets Gizmo Value Fields?
<meta>			TBD
<script>		Declares LUA Script (Script defined in CDATA)

<orientate>		Defines Gizmo Body (2D/3D Collision/Physics) Orientation and Shape
<physics>		Defines Body Physics Properties
<event>			Defines Event-based Action for Behaviors, Styles, Themes, Schemes, Gizmos
<font>			Defines Style Font Properties
<alpha>			Sets Font Alpha Property
<opaque>
<transparent>
<b>
<i>
<border>		Defines Theme Border Properties
<audio>

DESIGN NOTES:

	Gizmo with/without Sprites can be automatically determined by how they are declared.
	There is no to explicit declare OD(No Body, No Sprite)/1D(Body Only)/2D/3D.

		0D Style & Theme & Orientation = False

		1D Style & Theme = False, Orientation = True
			<orientate> initializes *Body
		
		2D Style & Theme & Orientation = True
			<orientate> initializes *Body, if 2D Style or Theme in Gizmo initialize Sprite 
		
		3D Style & Theme & Orientation = True
			<orientate> initializes *Body

	0D-2D bodies are interchangable.

*/