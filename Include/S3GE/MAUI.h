/*
 __  __    _   _   _ ___   ____     ___  
|  \/  |  / \ | | | |_ _| |___ \   / _ \ 
| |\/| | / / \| | | || |    __) | | | | |
| |  | |/ /_\ \ |_| || |   / __/ _| |_| |
|_|  |_/_/   \_\___/|___| |_____|_|\___/ 
      Multi-App User Interface 2.0
            F.L.Taylor 2010 ©

Dependencies:
	DarkGDK
	S3GE_common indexmanager
	2D Physics - Box2D HTTP://www.box2d.org
	3D Physics - Physx HTTP://developer.nvidia.com/object/physx.html
	bitmapfont lib
	irrxml for XML
	STL

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
#ifndef MAUI_H
#define MAUI_H

#include "S3GE.h"							//by S3GE Enhanced Library

using namespace std;
using namespace S3GE;

/*
SpreadSheet-Ready Define Format
#define LABEL[tab]Replacement
*/

#define MAUI_ERROR	-1

#define MAUI_MSG_PARAMETER_TYPE_VALUE	0
#define MAUI_MSG_PARAMETER_TYPE_PROPERTY	1
#define MAUI_MSG_PARAMETER_TYPE_VARIABLE	2
#define MAUI_MSG_PARAMETER_TYPE_SCRIPT	3
	
#define MAUI_MSG_QUIT	-1
#define MAUI_MSG_GIZMO_CLOSE 1 	
#define MAUI_MSG_GIZMO_OPEN	2
#define MAUI_MSG_GIZMO_HIDE	3
#define MAUI_MSG_GIZMO_SHOW	4
#define MAUI_MSG_GIZMO_MOVE	5
#define MAUI_MSG_GIZMO_SIZE	6
#define MAUI_MSG_GIZMO_ROTATE	7
#define MAUI_MSG_GIZMO_DISABLE	8
#define MAUI_MSG_GIZMO_ENABLE	9
#define MAUI_MSG_GIZMO_TRASH	10
#define MAUI_MSG_GIZMO_EXECUTE	11
#define MAUI_MSG_GIZMO_COLLISION_DISABLE	12
#define MAUI_MSG_GIZMO_COLLISION_ENABLE	13
#define MAUI_MSG_GIZMO_MUTE	14
#define MAUI_MSG_GIZMO_AUDIBLE	15
#define MAUI_MSG_GIZMO_MOVE_X	16
#define MAUI_MSG_GIZMO_MOVE_Y	17
#define MAUI_MSG_GIZMO_MOVE_Z	18

#define MAUI_MSG_TO_SELF	0x01
#define	MAUI_MSG_TO_PARENT	0x02
#define	MAUI_MSG_TO_SIBLINGS	0x04
#define	MAUI_MSG_TO_CHILDREN	0x08
#define	MAUI_MSG_TO_ALL	0x10

//Behavior Assign() Properties
#define MAUI_BEHAVIOR_ASSIGN_PROPERTY_TASK	1

//Style Assign() Properties
#define MAUI_STYLE_ASSIGN_PROPERTY_TASK	1

#define MAUI_STYLE_FONT_TYPE_DX9FONT	0
#define MAUI_STYLE_FONT_TYPE_FONTART	1
#define MAUI_STYLE_FONT_TYPE_MESHFONT	2

//Theme Assign() Properties
#define MAUI_THEME_ASSIGN_PROPERTY_TASK	1

//Scheme Assign() Properties
#define MAUI_SCHEME_ASSIGN_PROPERTY_TASK	1

#define MAUI_SCHEME_AUDIO_TYPE_SOUND	0
#define MAUI_SCHEME_AUDIO_TYPE_MUSIC	1
	
#define MAUI_SCHEME_AUDIO_SYSTEM_DGDK	0
#define MAUI_SCHEME_AUDIO_SYSTEM_OAW	1
	
//events are the detection of Pointer movement/click in relation to a Gizmo boundbox	
//event states order top-down by greatest duration	
#define MAUI_EVENT_STATE_IDLE 0	
	
//Device Type	
#define MAUI_INPUTDEVICE_TYPE_MOUSE	1
#define MAUI_INPUTDEVICE_TYPE_KEYBOARD	2
#define MAUI_INPUTDEVICE_TYPE_JOYSTICK	3
#define MAUI_INPUTDEVICE_TYPE_JOYSTICK_360	4
#define MAUI_INPUTDEVICE_TYPE_JOYSTICK_WII	5
#define MAUI_INPUTDEVICE_TYPE_INPUTDEVICE	6 //Control Device
	
//Device Mouse Buttons	
/*	
A mouse can have up to four buttons, and each one can be detected using this command.	
Each button is assigned a value. 	
The left button is assigned a value of 1. 	
The right button is assigned a value of 2.	
Buttons three and four are assigned values of 4 and 8 respectively.	
When more than one button is pressed, the value of the buttons are added to produce a combined value you can check for. 	
*/	
#define MAUI_INPUTDEVICE_MOUSE_BUTTON_LEFT	1
#define MAUI_INPUTDEVICE_MOUSE_BUTTON_RIGHT	2
#define MAUI_INPUTDEVICE_MOUSE_BUTTON_THREE	4
#define MAUI_INPUTDEVICE_MOUSE_BUTTON_FOUR	8
	
#define MAUI_INPUTDEVICE_KEYBOARD_KEYFILTER_NONE	0
#define MAUI_INPUTDEVICE_KEYBOARD_KEYFILTER_SINGLEKEY	0
#define MAUI_INPUTDEVICE_KEYBOARD_KEYFILTER_INCLUSION	0
#define MAUI_INPUTDEVICE_KEYBOARD_KEYFILTER_EXCLUSION	0
#define MAUI_INPUTDEVICE_KEYBOARD_KEYFILTER_FUSION	0
	
//Gizmo (Collision) Types	
#define MAUI_GIZMO_TYPE_GIZMO	0
#define MAUI_GIZMO_TYPE_WIZMO	1
#define MAUI_GIZMO_TYPE_JIGGER	4//3D Body only
#define MAUI_GIZMO_TYPE_DOODAD	2//2D Body only
#define MAUI_GIZMO_TYPE_WIDGET	3//no Body, no Sprite
	
//Gizmo Properties	
#define MAUI_GIZMO_PROPERTY_NAME	1
#define MAUI_GIZMO_PROPERTY_DESCRIPTION	2
#define MAUI_GIZMO_PROPERTY_CAPTION	3
#define MAUI_GIZMO_PROPERTY_EVENTSTATE_STATE	4
#define MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNT	5
#define MAUI_GIZMO_PROPERTY_EVENTSTATE_COUNTER	6
#define MAUI_GIZMO_PROPERTY_BOUND_COLLISION	7
#define MAUI_GIZMO_PROPERTY_BOUND_X	8
#define MAUI_GIZMO_PROPERTY_BOUND_Y	9
#define MAUI_GIZMO_PROPERTY_BOUND_Z	10
#define MAUI_GIZMO_PROPERTY_BOUND_WIDTH	11
#define MAUI_GIZMO_PROPERTY_BOUND_HEIGHT	12
#define MAUI_GIZMO_PROPERTY_BOUND_DEPTH	13
#define MAUI_GIZMO_PROPERTY_BOUND_PITCH	14
#define MAUI_GIZMO_PROPERTY_BOUND_YAW	15
#define MAUI_GIZMO_PROPERTY_BOUND_ROLL	16
#define MAUI_GIZMO_PROPERTY_BOUND_ORIENTATION	17
#define MAUI_GIZMO_PROPERTY_BOUND_SIZE	18
#define MAUI_GIZMO_PROPERTY_CONTACT_COLLISION	19
#define MAUI_GIZMO_PROPERTY_AXIS_X	20
#define MAUI_GIZMO_PROPERTY_AXIS_Y	21
#define MAUI_GIZMO_PROPERTY_AXIS_Z	22
#define MAUI_GIZMO_PROPERTY_SPRITE_OBJECT	23
#define MAUI_GIZMO_PROPERTY_STATE	24
#define MAUI_GIZMO_PROPERTY_DEFAULTCAPTION	25

//Gizmo Assign() Properties
#define MAUI_GIZMO_ASSIGN_PROPERTY_BEHAVIOR	1
#define MAUI_GIZMO_ASSIGN_PROPERTY_TRANSITION	2
#define MAUI_GIZMO_ASSIGN_PROPERTY_BODY	3
#define MAUI_GIZMO_ASSIGN_PROPERTY_OBJECT	4
#define MAUI_GIZMO_ASSIGN_PROPERTY_SPRITE	5
#define MAUI_GIZMO_ASSIGN_PROPERTY_THEME	6
#define MAUI_GIZMO_ASSIGN_PROPERTY_STYLE	7
#define MAUI_GIZMO_ASSIGN_PROPERTY_SCHEME	8
	
//Gizmo Process States	
#define MAUI_GIZMO_STATE_DISABLED	0
#define MAUI_GIZMO_STATE_ACTIVE	1
#define MAUI_GIZMO_STATE_TRANSITION	2
#define MAUI_GIZMO_STATE_TRANSITIONTOACTIVE	3
#define MAUI_GIZMO_STATE_DELETE	4
#define MAUI_GIZMO_STATE_FOCUS	5
#define MAUI_GIZMO_STATE_BLUR	6
	
//Gizmo Family Tree	
#define MAUI_GIZMO_FAMILY_PARENT	0
#define MAUI_GIZMO_FAMILY_FIRST	1
#define MAUI_GIZMO_FAMILY_LAST	2
#define MAUI_GIZMO_FAMILY_NEXT	3
#define MAUI_GIZMO_FAMILY_PREVIOUS	4

//Gizmo Controller Types
#define MAUI_GIZMO_CONTROLLER_TYPE_PHYSICS	0
#define MAUI_GIZMO_CONTROLLER_TYPE_INPUTDEVICE 1

//Gizmo Value Defines	
#define MAUI_GIZMO_VALUE_LINE_DIRECTION_UP	-1
#define MAUI_GIZMO_VALUE_LINE_DIRECTION_DOWN	1
#define MAUI_GIZMO_VALUE_LINE_DIRECTION_LEFT	-1
#define MAUI_GIZMO_VALUE_LINE_DIRECTION_RIGHT	1

//Sprite Caption Types	
#define MAUI_SPRITE_CAPTION_TYPE_STANDARD	0
#define MAUI_SPRITE_CAPTION_TYPE_PASSWORD	1
#define MAUI_SPRITE_CAPTION_TYPE_HIDDEN	2
#define MAUI_SPRITE_CAPTION_TYPE_REALTIME	4

//Gizmo Body Type
#define MAUI_BODY_TYPE_2D	0
#define MAUI_BODY_TYPE_3D	1

//Gizmo Body Orientation	
#define MAUI_BODY_ORIENTATE_XALIGN_LEFT	1
#define MAUI_BODY_ORIENTATE_XALIGN_CENTER	2
#define MAUI_BODY_ORIENTATE_XALIGN_RIGHT	3
#define MAUI_BODY_ORIENTATE_YALIGN_TOP	1
#define MAUI_BODY_ORIENTATE_YALIGN_MIDDLE	2
#define MAUI_BODY_ORIENTATE_YALIGN_BOTTOM	3
#define MAUI_BODY_ORIENTATE_ZALIGN_FRONT	1
#define MAUI_BODY_ORIENTATE_ZALIGN_NEUTRAL	2
#define MAUI_BODY_ORIENTATE_ZALIGN_BACK	3
#define MAUI_BODY_ORIENTATE_ALIGN_NEUTRAL	2

//Gizmo Body Physics Type
//2D
#define MAUI_BODY_PHYSICS2D_TYPE_WORLD	1
#define MAUI_BODY_PHYSICS2D_TYPE_BODY	0
#define MAUI_BODY_PHYSICS2D_TYPE_JOINT_MOUSE	2
#define MAUI_BODY_PHYSICS2D_TYPE_JOINT_DISTANCE	3
#define MAUI_BODY_PHYSICS2D_TYPE_JOINT_REVOLUTE	4
#define MAUI_BODY_PHYSICS2D_TYPE_JOINT_PRISMATIC	5
#define MAUI_BODY_PHYSICS2D_TYPE_JOINT_PULLEY	6
#define MAUI_BODY_PHYSICS2D_TYPE_JOINT_GEAR	7
//3D
#define MAUI_BODY_PHYSICS3D_TYPE_GROUNDPLANE	8
#define MAUI_BODY_PHYSICS3D_TYPE_BOX	9
#define MAUI_BODY_PHYSICS3D_TYPE_SPHERE	10
#define MAUI_BODY_PHYSICS3D_TYPE_CAPSULE	11
#define MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESHFROMDBO	12
#define MAUI_BODY_PHYSICS3D_TYPE_TRIANGLEMESH	13
#define MAUI_BODY_PHYSICS3D_TYPE_CONVEXMESH	14
#define MAUI_BODY_PHYSICS3D_TYPE_BOXSHAPE	15
#define MAUI_BODY_PHYSICS3D_TYPE_SPHERESHAPE	16
#define MAUI_BODY_PHYSICS3D_TYPE_CONVEXSHAPE	17
#define MAUI_BODY_PHYSICS3D_TYPE_COMPOUNDACTOR	18
#define MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERBOX	19
#define MAUI_BODY_PHYSICS3D_TYPE_CONTROLLERCAPSULE	20

//box2d constants	
#define b2PixelRatio	30.0f
#define b2PixelToMeter(n)	((n)/b2PixelRatio)
#define b2MeterToPixel(n)	((n)*b2PixelRatio)
#define b2PixelToHalfMeter(n)	(((n)/b2PixelRatio)/2)
#define b2HalfMeterToPixel(n)	(((n)*b2PixelRatio)*2)

namespace MAUI{
	/**
	* @brief	Multi-App User Interface
	*/
		class Message {
			/**
			* @brief	Inter Messaging Object
			*/
			public:
				class Parameter{
					public:
						int Type; //{VALUE,PROPERTY,VARIABLE,SCRIPT} 
						string Key;
						string Value;
						
						Parameter(int type, string key, string value);
						~Parameter(void);

				};

				void* Receiver;
				int Type;
				int ID; //message identifier
				int ParameterCount;
				map<int, Parameter*> ParameterMap;
				map<int, Parameter*>::iterator ParameterMapIterator;
				int State;

				Message(void);
				~Message(void);
				//static Message *Create(int MessageID, int type);
				static Message *Create(int type);
				static void Destroy(Message *instance);
				static void Insert(Message *instance, int type, string key, string value);

				Message *Copy(void);

		};

		class ESM{
			/**
			* @brief	Event State Machine
			*/
			public:

				static map<string, int> StateNameMap;
				static map<string, int>::iterator StateNameMapIterator;
				static int StateIndex;
				static void StateNameAdd(string statename);

				float Counter;
				float Count;
				float Delta;
				int PreviousState;
				int NextState;
				int TransitState;
				int State;

				void Clear(void);
		};

		class Behavior{
			/**
			* @brief	Behavior - Controls the Operation of Eventstates based on interactive conditions. 
						Behavior execute Script during Current Eventstate to set the Next Eventstate.

						Transition - A Behavior that controls Operation of the Entity during the Transition of one 
						Eventstate to another.
						Transitions execute Scripts based on Previous Eventstate 
						relative to the Current Eventstate.
			*/
			public:

				class EventScript{
					public:
						Behavior* Parent;
						DarkLUA::Task *Task;
						
						EventScript(void);
						void Inherit(EventScript *parent);
						EventScript *Copy(void);

				};


				static Behavior *DefaultBehavior;
				static Behavior *CurrentBehavior;

				static Behavior *DefaultTransition;
				static Behavior *CurrentTransition;

				static map<string,Behavior*> NameMap;
				static map<string,Behavior*>::iterator NameMapIterator;
				static Behavior *Create(string name, string description);
				static void Destroy(Behavior *instance);
				static void Destroy(void);
				static Behavior *Get(string name);
				static void Assign(Behavior *instance, int propertytype, void* propertyptr, int actionstate);

				map<int, EventScript*> EventAction;
				string Name;
				string Description;
				Behavior(void);
				Behavior(string name, string description);
				~Behavior(void);
				Behavior *Copy(string name, string description);
				void Assign(int propertytype, void *propertyptr, int actionstate);


		};

		class Style{
			/**
			* @brief	Gizmo Event-based Font Style applied to Display Object
						Event Script executed during font loading
			*/		
			public:

				class EventScript{
					/**
					* @brief	
					*/	

					public:
						Style *Parent;
						int Type; //0=truetype, 1=bitmap, 2=mesh
						string Fontname;
						int FontID;
						//meshfont *meshfont;
						D3DVECTOR Size;
						int Alpha;
						bool OpaqueFlag;
						bool TransparentFlag;
						bool BoldFlag;
						bool ItalicFlag;
						DWORD Color;
						DWORD bgColor;
						DarkLUA::Task *Task;

						EventScript(void);
						void dx9FontSet(void);
						void FontArtSet(void);
						void MeshFontSet(void);
						void Inherit(EventScript *parent);
						EventScript *Copy(void);
					
				};

				static Style *DefaultStyle;
				static Style *CurrentStyle;

				static map<string,Style*> NameMap;
				static map<string,Style*>::iterator NameMapIterator;
				static Style *Create(string name, string description);
				static void Destroy(Style *instance);
				static void Destroy(void);
				static Style *Get(string name);
				static void Assign(Style *instance, int propertytype, void* propertyptr, int actionstate);

				map<int, EventScript*> EventAction;
				int Type;
				string Name;
				string Description;
				Style(void);
				Style(string name, string description);
				~Style(void);
				Style *Copy(string name, string description);
				void Assign(int propertytype, void *propertyptr, int actionstate);
			
		};
		
		class Theme{
			/**
			* @brief	Event-based 2D Image Border & Fill applied to 2D Display Object
						Event Script executed during image drawing
			*/
			public:	

				class BorderArt{
					/**
					* @brief	Image-based Borderset
					*
					*/

					public:
						/*
						left - center - right
						top
						|
						middle
						|
						bottom
						*/

						class Attribute{
							public:
								int dbImageID;
								int Transparency;
								int Tile; //0=auto, >0=specified
								int Size;
								DWORD Color;
								int Alpha;
								int LineStyle;
								
								void Inherit(Attribute parent){
									dbImageID = parent.dbImageID;
									Transparency = parent.Transparency;
									Tile = parent.Tile;
									Size = parent.Size;
									Color = parent.Color;
									Alpha = parent.Alpha;
									LineStyle = parent.LineStyle;
								}

								void Clear(void){
									dbImageID = Transparency = Tile = Size = Alpha = LineStyle = 0;
									Color = -1;
								}

								void Copy(Attribute &instance){
									instance.dbImageID = dbImageID;
									instance.Transparency = Transparency;
									instance.Tile = Tile;
									instance.Size = Size;
									instance.Color = Color;
									instance.Alpha = Alpha;
									instance.LineStyle = LineStyle;
								}

						};

						class Horizontal{
							public:
								Attribute Left;
								Attribute Center;
								Attribute Right;

								void Inherit(Horizontal parent){
									Left.Inherit(parent.Left);
									Center.Inherit(parent.Center);
									Right.Inherit(parent.Right);
								}

								void Clear(void){
									Left.Clear();
									Center.Clear();
									Right.Clear();
								}

								void Copy(Horizontal &instance){
									Left.Copy(instance.Left);
									Center.Copy(instance.Center);
									Right.Copy(instance.Right);
								}

						};		

						class Vertical{
							public:
								Horizontal Top;
								Horizontal Middle;
								Horizontal Bottom;
								
								void Inherit(Vertical parent){
									Top.Inherit(parent.Top);
									Middle.Inherit(parent.Middle);
									Bottom.Inherit(parent.Bottom);
								}								

								void Clear(void){
									Top.Clear();
									Middle.Clear();
									Bottom.Clear();
								}

								void Copy(Vertical &instance){
									Top.Copy(instance.Top);
									Middle.Copy(instance.Middle);
									Bottom.Copy(instance.Bottom);
								}	

						};

						Vertical Edge;
						//vertical frame;

						BorderArt(void); //constructor
						~BorderArt(void);
	
						void Inherit(BorderArt parent);
						void Clear(void);
						void Copy(BorderArt &instance);

				};

				class EventScript{
					/**
					* @brief	
					*/	
					public:

						Theme *Parent;
						BorderArt Border;
						int ColorKeyRed;
						int ColorKeyGreen;
						int ColorKeyBlue;
						DarkLUA::Task *Task;

						EventScript(void);
						void Draw(D3DVECTOR size, int offsetx=0, int offsety=0);
						void LineStyleDraw(int type, float x1, float y1, float x2, float y2);
						void Inherit(EventScript *parent);
						EventScript *Copy(void);
				};
	
				static Theme *DefaultTheme;
				static Theme *CurrentTheme;

				static map<string,Theme*> NameMap;
				static map<string,Theme*>::iterator NameMapIterator;
				static Theme *Create(string name, string description);
				static void Destroy(Theme *instance);
				static void Destroy(void);
				static Theme *Get(string name);
				static void Assign(Theme *instance, int propertytype, void* propertyptr, int actionstate);

				map<int, EventScript*> EventAction;
				int Type;
				string Name;
				string Description;
				Theme(void);
				Theme(string name, string description);
				~Theme(void);
				Theme *Copy(string name, string description);
				void Assign(int propertytype, void *propertyptr, int actionstate);

		};
		
		class Scheme{
			/**
			* @brief	Event-driven Sound FX Scheme for Gizmos
			*/
			public:
			
				class EventScript{
					public:
						int Type; //music or sound
						int AudioID; //ID
						int System; //0=dbAudio, 1=IrrKlang
						int Loop;
						int LoopCount;
						DarkLUA::Task *Task;
						EventScript(void);
						void Inherit(EventScript *parent);
						EventScript *Copy(void);
				};

				static Scheme *CurrentScheme;
				static Scheme *DefaultScheme;

				static map<string,Scheme*> NameMap;
				static map<string,Scheme*>::iterator NameMapIterator;
				static Scheme *Create(string name, string description);
				static void Destroy(Scheme *instance);
				static void Destroy(void);
				static Scheme *Get(string name);
				static void Assign(Scheme *instance, int propertytype, void* propertyptr, int actionstate);

				map<int, EventScript*> EventAction;
				string Name;
				string Description;
				Scheme(void);
				Scheme(string name, string description);
				~Scheme(void);
				Scheme *Copy(string name, string description);
				void Assign(int propertytype, void *propertyptr, int actionstate);

		};

		//Interactives Objects
		class InputDevice{
			/**
			* @brief	Input Device Controller
			*/
			public:
				static map<string,InputDevice*> NameMap;
				static map<string,InputDevice*>::iterator NameMapIterator;
				static list<InputDevice*> ActiveList;
				static list<InputDevice*>::iterator ActiveListIterator;
				static queue<InputDevice*> InactiveQueue;

				static InputDevice *Create(string parentname, string name, string description, int type);
				static void Destroy(InputDevice *instance);
				static void Destroy(void);
				static void Update(void);

				static map<string,int> ScanCodeMap;

				queue<int> ContactQueue; //queue for key & button presses
				string Name;
				string Description;
				int Type; //[Pointer], keyboard, mouse, joystick, InputDevice, ai, network, Physics3D, Physics2D
				int ContactType;
				int ContactExist;
				int Contact;
				int AxisType;
				D3DVECTOR Axis;
				D3DVECTOR AxisDelta;
				enum DeviceStates{ACTIVE,DISABLED,DEVICESTATES_MAX} State;
	
				InputDevice(void);
				InputDevice(string name, string description);
				~InputDevice(void);

				void Process(void);
				void AxisQuery(void);
				void ContactQuery(void);
				void Trash(void);
				InputDevice *Copy(string name, string description);

		};

		class Body{
			/**
			* @brief	Interactive Collision Body powered by 2D(Box2D)/3D(Physx) Physics Engines
			*/
			public:
/*
				class collision{
					//purpose: collision management

					private:
						static const int vector3ID = 1;
						static list<int> objectlist;
						static list<int>::iterator objectlistiterator;
						enum collisionResponses{NONE, SLIDE, STOP} Response;

					public:

						struct contact{
							int sourcetypelistID;
							int desttypelistID;
							float tolerance;
							int Response;
							int method;
							//int type //db 3dobject type: mesh, light, camera, sound, pivot (virtual  3d point)
							//int method //overloaded check method select
						};

						static const int typelist_max = 32;
						static const int contact_profile_max = 32;

						enum entitytypes{ ENTITY_TYPE_NONE, ENTITY_TYPE_OBJECT1, ENTITY_TYPE_OBJECT2, ENTITY_TYPE_OBJECTMAX} entitytype;

						static list<int> *typelist;
						static list<int>::iterator sourcetypelistiterator;
						static list<int>::iterator desttypelistiterator;

						static int updateFrequency;	//may individualize updateFrequency & counter for contact profile
													//may also automate refresh rate based to typelist size
						static int UpdateFrequencyCounter;
						static int hitcounter;
						static int profile_index;
						static contact *profile;

						static void Start(void);
						static void Stop(void);
						static void Update(void);
						static void Create(int sourcetypelistID, int desttypelistID, int method, int Response, float tolerance);
						static void Destroy(void);
						static void add(int objectID, int typelistID);
						static void remove(int objectID, int typelistID);
						static bool check(D3DVECTOR position1, D3DVECTOR position2, float tolerance);
						static bool check(float dbObjectPositionX1, float dbObjectPositionY1, float dbObjectPositionZ1, float dbObjectPositionX2, float dbObjectPositionY2, float dbObjectPositionZ2, float tolerance);
						static void Process(int sourceobjectID, int destobjectID, int Response);

						//entity collision functions defined in entity.cpp
						static int entityobject(int typelistID, int entityID);
						static void entitycollisions(int sourcetypelistID, int sourceentityID, int desttypelistID, int destentityID);

				};
*/
				class PhysicsAbstract{ //base class
					public:

						int Type;

						//common pure virtuals
						virtual void Destroy(void)=0;
						virtual void UserDataSet(void* userPTR)=0;
						virtual void* UserDataGet(void)=0;

						//CanvasPhysics2D pure virtuals
						virtual void Create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping)=0;
						virtual b2Body* BodyCreate(const b2BodyDef bodydef)=0;
						virtual b2World* WorldGet(void)=0;
						virtual void Update(void)=0;
						virtual PhysicsAbstract* Copy(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping)=0;

						//GizmoPhysics2D pure virtuals
						virtual void Create(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor)=0;
						virtual void Update(D3DVECTOR &position, D3DVECTOR &angle)=0;
						virtual bool OrientationSet(b2Vec2 position, float32 angle)=0;
						virtual PhysicsAbstract* Copy(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor)=0;

						//PointerPhysics2D pure virtuals
						virtual void Create(string canvasname)=0;
						virtual void Update(b2Vec2 p, int actionstate)=0;
						virtual PhysicsAbstract* Copy(string canvasname)=0;

						//GizmoPhysics3D
						virtual void Create(int objectID)=0;
						virtual void Set(int type, bool dynamic, float density, float maxstep, float slopelimit, float radius, bool yoffset, float length, float sizex, float sizey, float sizez)=0;
						virtual PhysicsAbstract* Copy(int objectID)=0;
						

				};

				class CanvasPhysics2D: public PhysicsAbstract{
					private:
						b2AABB WorldAABB;
						b2World *World;
						bool AllowSleep;
						D3DVECTOR Gravity;
						float32 TimeStep;
						int32 Iterations;

					public:
						CanvasPhysics2D(void);
						~CanvasPhysics2D(void);

						//virtuals
						void Create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping);
						void Destroy(void);
						void Update(void);
						b2World* WorldGet(void);						
						b2Body* BodyCreate(const b2BodyDef bodydef);
						void UserDataSet(void *userPTR){}
						void *UserDataGet(void){return(NULL);}
						PhysicsAbstract* Copy(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping);

						//GizmoPhysics2D virtual stubs: required to overide pure virtuals
						void Create(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){}
						void Update(D3DVECTOR &position, D3DVECTOR &angle){}
						bool OrientationSet(b2Vec2 position, float32 angle){return(false);}
						PhysicsAbstract* Copy(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){return(NULL);}

						//PointerPhysics2D virtual stubs
						void Create(string canvasname){}
						void Update(b2Vec2 p, int actionstate){}
						PhysicsAbstract* Copy(string canvasname){return(NULL);}

						//GizmoPhysics3D virtual stubs
						void Create(int objectID){}
						void Set(int type, bool dynamic, float density, float maxstep, float slopelimit, float radius, bool yoffset, float length, float sizex, float sizey, float sizez){};
						PhysicsAbstract* Copy(int objectID){return(NULL);}

				};

				class GizmoPhysics2D: public PhysicsAbstract{
					private:
						b2World *World;
						int ShapeTypeDef;
						b2BodyDef BodyDef;
						b2Body* DynamicBody;
						b2PolygonDef ShapeDef;

					public:
						GizmoPhysics2D(void);
						~GizmoPhysics2D(void);

						//virtuals
						void Create(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor);
						void Destroy(void);
						void Update(D3DVECTOR &position, D3DVECTOR &angle);
						void UserDataSet(void *userPTR);
						void *UserDataGet(void);
						bool OrientationSet(b2Vec2 position, float32 angle);
						PhysicsAbstract* Copy(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor);

						//GizmoPhysics2D virtual stubs
						void Create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping){}
						b2World* WorldGet(void){return(NULL);}
						b2Body* BodyCreate(const b2BodyDef bodydef){return(NULL);}
						void Update(void){}
						PhysicsAbstract* Copy(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping){return(NULL);}

						//PointerPhysics2D virtual stubs
						void Create(string canvasname){}
						void Update(b2Vec2 p, int actionstate){}
						PhysicsAbstract* Copy(string canvasname){return(NULL);}

						//GizmoPhysics3D virtual stubs
						void Create(int objectID){}
						void Set(int type, bool dynamic, float density, float maxstep, float slopelimit, float radius, bool yoffset, float length, float sizex, float sizey, float sizez){}
						PhysicsAbstract* Copy(int objectID){return(NULL);}
				};

				class PointerPhysics2D: public PhysicsAbstract{
					private:
						b2World *World;
						b2MouseJoint* MouseJoint;

					public:
						PointerPhysics2D(void);
						~PointerPhysics2D(void);

						//virtual
						void Create(string canvasname);
						void Destroy(void);
						void Update(b2Vec2 p, int actionstate);
						void UserDataSet(void *userPTR){}
						void *UserDataGet(void){return(NULL);}
						PhysicsAbstract* Copy(string canvasname);
						
						//CanvasPhysics2D virtual stubs
						void Create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 Iterations, bool allowsleeping){}
						b2World* WorldGet(void){return(NULL);}
						b2Body* BodyCreate(const b2BodyDef bodydef){return(NULL);}
						void Update(void){}
						PhysicsAbstract* Copy(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping){return(NULL);}

						//GizmoPhysics2D virtual stubs
						void Create(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){}
						void Update(D3DVECTOR &position, D3DVECTOR &angle){}
						bool OrientationSet(b2Vec2 position, float32 angle){return(0);}
						PhysicsAbstract* Copy(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){return(NULL);}

						//GizmoPhysics3D virtual stubs
						void Create(int objectID){}
						void Set(int type, bool dynamic, float density, float maxstep, float slopelimit, float radius, bool yoffset, float length, float sizex, float sizey, float sizez){}
						PhysicsAbstract* Copy(int objectID){return(NULL);}

				};

				class GizmoPhysics3D: public PhysicsAbstract{
					private:
						bool Dynamic;
						float Density;
						float MaxStep;
						float SlopeLimit;
						float Radius;
						bool YOffset;
						float Length;
						float SizeX;
						float SizeY;
						float SizeZ;

					public:
						GizmoPhysics3D(void);
						~GizmoPhysics3D(void);
					
						//virtual
						void Create(int objectID);
						void Destroy(void);
						void Update(void);
						void UserDataSet(void *userPTR);
						void *UserDataGet(void);
						void Set(int type, bool dynamic, float density, float maxstep, float slopelimit, float radius, bool yoffset, float length, float sizex, float sizey, float sizez);
						PhysicsAbstract* Copy(int objectID);

						//CanvasPhysics2D virtual stubs
						void Create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 Iterations, bool allowsleeping){}
						b2World* WorldGet(void){return(NULL);}
						b2Body* BodyCreate(const b2BodyDef bodydef){return(NULL);}
						PhysicsAbstract* Copy(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping){return(NULL);}

						//GizmoPhysics2D virtual stubs
						void Create(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){}
						void Update(D3DVECTOR &position, D3DVECTOR &angle){}
						bool OrientationSet(b2Vec2 position, float32 angle){return(0);}
						PhysicsAbstract* Copy(string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){return(NULL);}

						//PointerPhysics2D virtual stubs
						void Create(string canvasname){}
						void Update(b2Vec2 p, int actionstate){}
						PhysicsAbstract* Copy(string canvasname){return(NULL);}
				};

				static Body* Create(int type, int physicstype, int objectID=0, float x=0.0f, float y=0.0f, float z=0.0f, float width=1.0f, float height=1.0f, float depth=1.0f, float anglex=0.0f, float angley=0.0f, float anglez=0.0f);
				static void Destroy(Body* instance);

				queue<Body*> CollisionQueue;
				int Type; //2d Procedural, 2D Physics,3D Physics, 3D Polygon, 3D Procedural
				bool CollideFlag; //register collision between objects
				bool PhysicsFlag; //register for Physics simulation
				bool GravityFlag; //register for artificial gravity
				bool PathfinderFlag; //register to patherfinder
				
				//shape
				D3DVECTOR Position;
				D3DVECTOR Size;
				D3DVECTOR Angle;
				
				PhysicsAbstract *Physics;
				int CollisionExist;

				Body(void);
				Body(float x, float y, float z, float width, float height, float depth, float anglex, float angley, float anglez);
				~Body(void);
				
				//Gizmo
				void Center(string canvasname);
				void Zoom(string canvasname);
				void Orientate(string refgizmoname, float x, float y, float z, int xalign, int yalign, int zalign);
				void Inherit(Body *parent);
				Body *Copy(void);
		};

		class Sprite{
			/**
			* @brief	2D/3D Display Object
			*/
			public:

				static Sprite* Create(int spritetype, string sourcefilename);
				static Sprite* Create(int spritetype, string backdropfilename, Theme *theme=NULL, Style *style=NULL, S3GE::Object *object=NULL, Body *body=NULL);
				static Sprite* Destroy(Sprite *instance); 

				//resource
				int Type;//0=3D Sprite, 1=3D Mesh, 2=Animated Image
				int dbImageID;
				int dbObjectID;

				//settings
				int StartFrame; //2D framesacross
				int StopFrame; //2D framesdown
				int CurrentFrame;
				
				//Caption
				Style *CaptionStyle;
				int CaptionType; //normal, password, hidden, encrpted
				string Caption; //normal Caption
				string CaptionView; //Caption:: normal, password, hidden, encrpted
				D3DVECTOR CaptionPosition; //alignment
				D3DVECTOR CaptionSize;

				//background
				Theme *BackdropTheme;
				int BackdropImageID;
				D3DVECTOR BackdropImageAlign;
				bool SnapshotFlag; //takes a snapshot of default bitmap, uses as sprite image
				
				//icon
				Theme *IconTheme;
				int IconImageID;
				D3DVECTOR IconImageAlign;
								
				//states
				bool VisibleFlag;
				int LODFlag;
				
				Sprite(void);
				~Sprite(void);
				int MeshCreate(string meshname);
				void MeshDestroy(void);
				int MeshLoad(string filename);
				int ImageGet(string imagename);
				int ImageLoad(string filename, int framesacross ,int framesdown);
				int ImageDraw(Body *body, int actionstate);
				int ImageCapture(Body *body, int actionstate);
				void Inherit(Sprite *parent);
				int CaptionWidth(string text);
				int CaptionHeight(string text);
				void Orientate(Body *body, D3DVECTOR &position, D3DVECTOR size, float x, float y, float z, int xalign, int yalign, int zalign);
				void CaptionOrientate(Body *body, float x, float y, float z, int xalign, int yalign, int zalign);
				void ImageOrientate(Body *body, int imageID, D3DVECTOR &position, float x, float y, float z, int xalign, int yalign, int zalign);

				Sprite *Copy(void);
		};

		//UI Objects
		class Canvas{
			/**
			* @brief	Integrated 2D Screen/3D Camera + Listener
			*/
			public:

				struct CameraData
				{
					D3DXMATRIX			matProjection;	// projection matrix
					D3DXMATRIX			matView;		// view matrix

					D3DXVECTOR3			vecLook;		// look vector
					D3DXVECTOR3			vecUp;			// up vector
					D3DXVECTOR3			vecRight;		// right vector
					D3DXVECTOR3			vecPosition;	// position vector

					D3DVIEWPORT9		viewPort2D;		// view port for 2D ( area on screen to take up )
					D3DVIEWPORT9		viewPort3D;		// view port for 3D ( area on screen to take up )

					int					iCameraToImage;
					LPDIRECT3DTEXTURE9	pCameraToImageTexture;
					LPDIRECT3DSURFACE9  pCameraToImageSurface;
					LPDIRECT3DTEXTURE9	pCameraToImageAlphaTexture;
					LPDIRECT3DSURFACE9  pCameraToImageAlphaSurface;

					// Stereoscopic mode for camera images
					int					iStereoscopicMode;
					CameraData*			pStereoscopicFirstCamera;
					int					iCameraToStereoImageBack;
					int					iCameraToStereoImageFront;
					LPDIRECT3DTEXTURE9	pCameraToStereoImageBackTexture;
					LPDIRECT3DTEXTURE9	pCameraToStereoImageFrontTexture;
					LPDIRECT3DSURFACE9	pCameraToStereoImageBackSurface;
					LPDIRECT3DSURFACE9	pCameraToStereoImageFrontSurface;	

					int					iBackdropState;	// used as an automatic clear
					DWORD				dwBackdropColor;// color of backdrop

					// Can use XYZ rotation or FreeFlight(YPR)
					bool				bUseFreeFlightRotation;
					D3DXMATRIX			matFreeFlightRotate;
					float				fXRotate, fYRotate, fZRotate;	// rotateangle

					float				fAspect;		// aspect ratio
					float				fAspectMod;
					float				fFOV;			// field of view
					float				fZNear;			// z near
					float				fZFar;			// z far

					bool				bRotate;		// which rotate to use

					// Override camera
					bool				bOverride;
					D3DXMATRIX			matOverride;

					// Clipping planes (so can do reflection tricks)
					int					iClipPlaneOn;
					D3DXPLANE			planeClip;

					// Image ptr storage (DarkSKY) and also some reserves
					int					iBackdropTextureMode;
					LPDIRECT3DTEXTURE9	pBackdropTexture;

					DWORD				dwRes1;
					DWORD				dwRes2;
					DWORD				dwRes3;
					DWORD				dwRes4;
					DWORD				dwRes5;

					//CameraData ( );
				};

				static map<string,Canvas*> NameMap;
				static map<string,Canvas*>::iterator NameMapIterator;
				static list<Canvas*> ActiveList;
				static list<Canvas*>::iterator ActiveListIterator;
				static queue<Canvas*> InactiveQueue;

				static Canvas *BaseCanvas;
				static Canvas *CurrentCanvas;

				static Canvas* Create(string parentname, string name, string description, int dbCameraID, float FOV, float nearrange, float farrange, float aspect, bool backdropflag, DWORD backdropcolor, int backdropimageID);
				static void Destroy(Canvas *instance);
				static void Destroy(void);
				static void Update(void);
				
				string Name;
				string Description;
								
				int Type;
				//3D viewport
				int dbCameraID;
				float FOV;
				float NearRange;
				float FarRange;
				float Aspect;
				//viewport Backdrop
				bool BackdropFlag;
				DWORD BackdropColor;
				int BackdropImageID;
				//screen
				D3DVECTOR ZoomFactor; //effect pos & size gizmos
				D3DVECTOR CenterOffset;								
				//listener
				D3DVECTOR ListenerScale;
				//listener position & rotation are matched to `active` camera

				//Physics
				Body *Body; //screen & depth
				InputDevice *InputDevice;

				enum CanvasStates{DISABLED,ACTIVE,CANVASSTATES_MAX} State;

				//3d Physics (Physx)

				Canvas(void);
				Canvas(string name, string description);
				~Canvas(void);
				Canvas *Get(string name);
				void Process(void);
				void Set(void);
				void Zoom(float zoomfactorx, float zoomfactory);
				void Inherit(Canvas *parent);
				void Trash(void);
				Canvas *Copy(void);
				void ScreenPositionGet(D3DXVECTOR3 &position, int &x, int &y);

		};

		class Gizmo{
			/**
			* @brief	Base Interactive Object
			*/
			public:

				class EventScript{
					public:
						Behavior *Behavior, *Transition;
						Scheme *Scheme;
						Sprite *Sprite;
						DarkLUA::Task *Task;
						
						EventScript(void); //constructor
						void Inherit(EventScript *parent);
						EventScript* Copy(void);

				};

				static map<string,Gizmo*> NameMap;
				static map<string,Gizmo*>::iterator NameMapIterator;
				static list<Gizmo*> ActiveList;
				static list<Gizmo*>::iterator ActiveListIterator;
				static queue<Gizmo*> InactiveQueue;
				static map<string,int> PropertyNameMap;
				static map<string,int>::iterator PropertyNameMapIterator;
				static int Index;

				static Gizmo *BaseGizmo;
				static Gizmo *CurrentGizmo;
				static Gizmo *Pointer;
				static Gizmo *Caret;

				//Binding Functions
				static void PropertyAdd(string key,const int constant);
				static char* PropertyGet(Gizmo *instance, string key, int actionstate=-1);
				static void PropertySet(Gizmo *instance, string key, char* value, int actionstate=-1);
				static char* VariableGet(Gizmo *instance, string variable);
				static void VariableSet(Gizmo *instance, string variable, string value);
				
				static Gizmo *Create(string parentname, string name, string description, bool collisionflag, bool operateflag, bool transitflag, bool activeflag, bool visibleflag, bool audioflag);
				static Gizmo *Create(string parentname, string name, string description, DWORD processbitflag);
				//static Gizmo *Create(string parentname, string name, string label, string behaviorname, string transitionname, string stylename, string themename, string schemename);

				static void Destroy(Gizmo *instance);
				static void Destroy(void);
				static void Update(void);

				static Gizmo *Get(string name);
				static Gizmo *Reference(string name);
				static bool Exist(string name);
				static void Assign(Gizmo *instance, int propertytype, void* propertyptr, int actionstate=MAUI_EVENT_STATE_IDLE);
				static void Capture(Gizmo *instance, int actionstate);

				//Hyper Actions
				static void Spin(Gizmo *instance, float angle);//Test
				static void Color(Gizmo *instance, int red, int green, int blue);

				//script binding wrappers
				static void LineTextDisplay(Gizmo *instance, int red, int green, int blue);
				static void LineTextEdit(Gizmo *instance, int function);
				static void LineTextCapture(Gizmo* instance, int actionstate);
				static void LineTextCopy(string sourcegizmoname, string destgizmoname);
				static string LineTextGet(Gizmo *instance);
				static void LineCaretLocate(Gizmo *instance, int caretmoveflag);
				static void LineCaretEdit(Gizmo *instance, int function);
				static void LineSelectionEdit(Gizmo *instance, int function);

				map<int, EventScript*> EventAction;
				map<string, string>VariableMap;
				map<string, string>::iterator VariableMapIterator;
				
				queue<Message*> MessageQueue;
				Message *Message;

				string Name;
				string Description;
				int ID;
				int HTTPFileID;
				int Type;
				DWORD ParentalControlBitflag; //bitwise map
				Gizmo *Parent,*First,*Last,*Previous,*Next; //Scene Graph?
				InputDevice *InputDevice;
				int ControllerType;
				Body *Body;
				int SpriteID; // 2D(1 dbSprite : Action x Image, IDLE is default for all) || 3D(Action x Object, IDLE is default for all)
				int Priority; //determined by parent

				DWORD ProcessBitflag;
				enum ProcessingOptions {
					//playing with bitflags ref: http://www.cplusplus.com/forum/general/1590/
					NONE =			0x00,
					COLLISION =		0x01,
					VISIBLE =		0x02,
					OPERATE =		0x04,
					TRANSITION =	0x08,
					ACTION =		0x10,		
					AUDIBLE =		0x20,	
					DEBUG =			0x40		

				};

				bool CollisionFlag;
				bool DebugFlag; //display collision bound for testing
				bool VisibleFlag;
				bool AudioFlag; //mute
				bool ActiveFlag;
				bool TransitFlag;
				bool OperateFlag;
				ESM EventState;
				enum GizmoStates{DISABLED,DRAW,ACTIVE,LOADING,DOWNLOADING,GIZMOSTATES_MAX} State;

				Gizmo(void);	//constructors
				Gizmo(string name, string description);
				~Gizmo(void);	//destructor
				void Process(void);
				void Inherit(Gizmo *parent);
				void Mimic(Gizmo *instance);
				Gizmo *Copy(string name, string description);
				void FamilyAdd(Gizmo *parent);
				void FamilyRemove(void);
				void ImageCapture(int actionstate);
				void TextureCapture(int actionstate);
				void CanvasCapture(int actionstate);
				void Assign(int propertytype, void *propertyptr, int actionstate=MAUI_EVENT_STATE_IDLE);
				
				//process operations
				void SpriteOffset(void);
				void Pump(void);
				void Control(void);
				void Display(void);
				void Produce(void);
				void Collision(void);
				void Operate(void);
				void Action(void);
				void Transit(void);
				void Debug(void);
				void Trash(void);

				//Family operations
				//properties
				void FamilyPropertySet(void);
				void FamilySiblingPropertySet(bool subflag);
				void FamilyChildrenPropertySet(bool subflag);
				//variables
				//messages
				void FamilyMessageSend(MAUI::Message *message);
				void FamilySiblingMessageSend(MAUI::Message *message, bool subflag);
				void FamilyChildrenMessageSend(MAUI::Message *message, bool subflag);

				//messaging operations
				bool MessageGet(void);
				bool MessagePeek(void);
				void MessageProcess(void);
				static void MessageSend(MAUI::Message *message, MAUI::Gizmo *receiver);
				static void MessageSend(MAUI::Message *message, string name);
				static void MessageSend(MAUI::Message *message, string name, int groupID, bool subflag);

				//line operations /////////////////////////////////////////////////////

				//Caret operations
				void LineCaretSet(int linestartposition, int linestartcharacterposition, int caretmoveflag);
				void LineCaretGet(void);
				void LineCaretLocate(int caretmoveflag);
				void LineCaretDisplay(float x, float width, float y, float height, int red, int green, int blue);

				//text operations
				void LineTextNew(void);
				void LineTextInsert(string text);
				void LineTextDelete(void);
				void LineTextClear(void);
				void LineTextSplit(void);
				string LineTextTrim(int linenumber, int direction, float width);
				void LineTextAppend(int linenumber, int direction, string text);
				void LineTextShift(int linenumber, int direction);
				void LineTextWrap(int linenumber, int direction);
				void LineTextDisplay(int linenumber, float y, float height, int red, int green, int blue);
				void LineTextDisplay(int startlineumber, int stoplinenumber, int red, int green, int blue);
				void LineTextDisplayAll(int red, int green, int blue);
				void LineTextCapture(int actionstate);
				string LineTextGet(void);
				void LineTextCopy(Gizmo *instance);

				//selection operations
				void LineSelectionSet(void);
				void LineSelectionGet(void); //aka copy
				void LineSelectionInsert(void); //aka paste
				void LineSelectionDelete(void);
				void LineSelectionCut(void); //= get + delete;
				void LineSelectionDisplay(int red, int green, int blue);
				void LineSelectionDisplay(float x, float width, float y, float height, int red, int green, int blue);

				//editor operations
				//autoposition
				//autoscale
				//autoparent

		};

		class Gadget{
			/**
			* @brief	Composite Gizmo Object
			*/
			public:

				class EventScript{
					public:

						DarkLUA::Task *Task;
						
						EventScript(void); //constructor
						void Inherit(EventScript *parent);
						EventScript* Copy(void);

				};

				static map<string,Gadget*> NameMap;
				static map<string,Gadget*>::iterator NameMapIterator;
				static list<Gadget*> ActiveList;
				static list<Gadget*>::iterator ActiveListIterator;
				static queue<Gadget*> InactiveQueue;

				list<Gizmo*> GizmoList;
				list<Gizmo*>::iterator GizmoListIterator;
				string Name;
				string Description;
				int CopyIndex; //counts duplicates, append index to gizmo list names;
				bool CollisionFlag;
				bool DebugFlag; //display collision bound for testing
				bool VisibleFlag;
				bool AudioFlag; //mute
				bool ActiveFlag;
				bool TransitFlag;
				bool OperateFlag;

				Gadget(void);
				~Gadget(void);

				static Gadget *Create(string parentname, string name, string description, bool collisionflag, bool operateflag, bool transitflag, bool activeflag, bool visibleflag, bool audioflag);
				static void Destroy(Gadget* instance);
				int Add(Gizmo* Gizmo);
				void Remove(Gizmo* Gizmo);
				Gadget *Copy(void);
				void Inherit(Gadget* parent);

		};

		class HTTPForm{
			/**
			* @brief	HTTP Form (Interface)
			*/
			public:
				static map<string,HTTPForm*> NameMap;
				static map<string,HTTPForm*>::iterator NameMapIterator;
				static list<HTTPForm*> ActiveList;
				static list<HTTPForm*>::iterator ActiveListIterator;
				static queue<HTTPForm*> InactiveQueue;				
				
				static HTTPForm *Create(string name, string description, int method, string hostname, int port, string page, string writepath );
				static void Destroy(HTTPForm *HTTPForm);
				static void Update(void);
				static void Submit(string name);
				static HTTPForm *CurrentHTTPForm;

				list<Gizmo*> GizmoList;
				list<Gizmo*>::iterator GizmoListIterator;
				string Name;
				string Description;
				string Hostname;
				int Port;//default 80
				string Page;
				string WritePath;
				int Method;
				DarkNet::HTTP *HTTP;
				enum HTTPFormStates{IDLE, SENDING, RECEIVING, READY, TERMINATE} State;

				HTTPForm(void);
				HTTPForm(string name, string description);
				~HTTPForm(void);
				void Process(void);
				void Submit(void);
		};

		class System{
			public:
				//static queue<message*> MessageQueue; //GLOBAL MESSAGE QUEUE
				//static map<> messagemap

				static void Start(void);
				static void Stop(void);
				static void Update(void);

				System(void);//constructor
				~System(void);//destructor
		};
}

#endif

/*
TODO LIST

	1. Integrate controller InputDevice, Pointer Gizmo


DESIGN NOTES:

Box2D Meters to Pixels
HTTP://www.emanueleferonato.com/2008/11/17/understanding-pixels-and-meters-with-box2d-and-how-to-select-an-object-with-mouse-part-2/

Application Gizmos:

	Gadget - Graphical Gizmos that have the typical Behavior
		found in windows controls: button, option, sliders, etc,

	Viewport - 2D Graphical Gizmo that captures images from the viewer
		buffers and utilizes clipping to fit image in a specific 
		dimension.

	Toggle - non graphical Gizmo usually used to 
		map keys and buttons from input InputDevice to a script

	Layer - non graphic Gizmo that parents visible ones with the 
		primary purpose of show/hide a group of gizmos

	Pointer - a Gizmo thats movement is controlled by input InputDevice
	Cursor - a Gizmo that used to mark position
	Highlighter 

Game Gizmos

	Character - 3D Gizmo that can use the Character Controller Physics
	HUD - Heads Up Display
	Reticule - target cursor, interchangable with the term Pointer
	Event Triggers
	Props
	
3D Entities that do not require UI:
	Terrain, Particles, Building Interior (BSP Maps)

MAUI XML
	Transitions provide a unique Event State handling that can execute
	EventState script during a specific state or between two

REFERENCES

Windows Message Pump
	HTTP://msdn.microsoft.com/en-us/library/ms644928(VS.85).aspx
	HTTP://www.microsoft.com/msj/0795/dilascia/dilascia.aspx

*/