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

#pragma once
#ifndef BRAIN_H
#define BRAIN_H

#define NOMINMAX      // Techlord put here, if(not included we get following:
                      // Error: min or max is #defined, probably in <windows.h>.  Put #define NOMINMAX before including windows.h to suppress windows global min,max macros.
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

#include "DarkGDK.h"			//by TGC
#include "S3GE_common.h"		//by DOSP Common Library
#include "diag.h"				//by Techlord
#include "darklua.h"			//by Techlord
#include "xml_plugin.h"
#include "darknet.h"			//by DarkNet Extention by Techlord
//#include "pathfinding lib"
#include "FulcrumPhy.h"			//by Matty
#include "Box2D.h"				//by Techlord

using namespace std;

#define BRAIN_ERROR -1

//events are the detection of pointer movement/click in relation to a agent boundbox
//event states order top-down by greatest duration
#define BRAIN_EVENT_STATE_IDLE 0

//Device Type

//Agent Properties
#define BRAIN_AGENT_PROPERTY_NAME 1
#define BRAIN_AGENT_PROPERTY_DESCRIPTION 2
#define BRAIN_AGENT_PROPERTY_EVENTSTATE_STATE 3
#define BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNT 4
#define BRAIN_AGENT_PROPERTY_EVENTSTATE_COUNTER 5
#define BRAIN_AGENT_PROPERTY_BOUND_COLLISION 6
#define BRAIN_AGENT_PROPERTY_CONTACT_COLLISION 7
#define BRAIN_AGENT_PROPERTY_AXIS_X 8
#define BRAIN_AGENT_PROPERTY_AXIS_Y 9
#define BRAIN_AGENT_PROPERTY_AXIS_Z 10
#define BRAIN_AGENT_PROPERTY_SPRITE_QUAD 11

//Agent (Collision) Types
#define BRAIN_AGENT_TYPE_2D 0
#define BRAIN_AGENT_TYPE_3D 1
#define BRAIN_AGENT_TYPE_1D 2 //body only
#define	BRAIN_AGENT_TYPE_0D 3 //no body, no sprite

//Agent States
#define BRAIN_AGENT_STATE_DISABLED 0
#define BRAIN_AGENT_STATE_ACTIVE 1
#define BRAIN_AGENT_STATE_TRANSITION 2
#define BRAIN_AGENT_STATE_TRANSITIONTOACTIVE 3
#define BRAIN_AGENT_STATE_DELETE 4

//Agent Body Orientation
#define BRAIN_AGENT_BODY_ORIENTATE_XALIGN_LEFT 1
#define BRAIN_AGENT_BODY_ORIENTATE_XALIGN_CENTER 2
#define BRAIN_AGENT_BODY_ORIENTATE_XALIGN_RIGHT 3
#define BRAIN_AGENT_BODY_ORIENTATE_YALIGN_TOP 1
#define BRAIN_AGENT_BODY_ORIENTATE_YALIGN_MIDDLE 2
#define BRAIN_AGENT_BODY_ORIENTATE_YALIGN_BOTTOM 3
#define BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_FRONT 1
#define BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_NEUTRAL 2
#define BRAIN_AGENT_BODY_ORIENTATE_ZALIGN_BACK 3
#define BRAIN_AGENT_BODY_ORIENTATE_ALIGN_NEUTRAL 2

//Agent Body Physics Type
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_WORLD 1
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_BODY 0 
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_MOUSE 2
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_DISTANCE 3
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_REVOLUTE 4
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_PRISMATIC 5
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_PULLEY 6
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_2D_JOINT_GEAR 7
#define BRAIN_AGENT_BODY_PHYSICS_TYPE_3D 8

//XML Tags
#define BRAIN_XML_NODENAME_MAUI 1
#define BRAIN_XML_NODENAME_AGENT 2
#define BRAIN_XML_NODENAME_BEHAVIOR 3
#define BRAIN_XML_NODENAME_TRANSITION 4

#define BRAIN_XML_NODENAME_EVENT 8
#define BRAIN_XML_NODENAME_META 9
#define BRAIN_XML_NODENAME_SCRIPT 10
#define BRAIN_XML_NODENAME_SPRITE 17
#define BRAIN_XML_NODENAME_AUDIO 18
#define BRAIN_XML_NODENAME_ORIENTATE 19
#define BRAIN_XML_NODENAME_PHYSICS 20
#define BRAIN_XML_NODENAME_FORMSUBMIT 23
#define BRAIN_XML_NODENAME_FORMRESET 24
#define BRAIN_XML_NODENAME_STATE 27
#define BRAIN_XML_NODENAME_OBJECT 28
#define BRAIN_XML_NODENAME_VARIABLE 29

//box2d constants
#define b2PixelRatio 30.0f
#define b2PixelToMeter(n) ((n)/b2PixelRatio)
#define b2MeterToPixel(n) ((n)*b2PixelRatio)
#define b2PixelToHalfMeter(n) (((n)/b2PixelRatio)/2)
#define b2HalfMeterToPixel(n) (((n)*b2PixelRatio)*2)

class brains{
	/*!
	* Description: Behavioral Rules Artificial Intelligence Node System
	*
	*/
	
	public:

		class ticker{
			/*!
			* Description: Timing Object
			*	Can be used for various ticker functions
			*/
			private:
				float restart,current,step;
				enum tickerstates{HALT,RUN,RUNNING} state;

			public:

				ticker(void){}

				ticker(float restart, float step){
					this->restart = restart;
					this->step = restart/step * -1;
					this->current = 0.0f;
					this->state = RUN;
				}

				~ticker(void){};

				void set(float restart, float step){
					this->restart = restart;
					this->step = restart/step * -1;
					this->current = 0.0f;
					this->state = RUN;
				}

				void set(float restart){ this->set(restart,restart);}

				bool tick(void){
					switch(state){
						case RUN:
							state = RUNNING;
							break;
						case RUNNING:
							if (current<=0){
								current=restart; 
								return(true);
							}
							if (current>0){
								current+=step;
							}
							return(false);
							break;
						case HALT:
							break;
					}
				}
				float startget(void){return(restart);}
				float currentget(void){	return(current);}
				float stepget(void){return(step);}
				void start(void){state = RUNNING;}
				void stop(void){state = HALT;}

		};

		class esm{
			/*!
			* Description: Event State Machine
			*
			*/
			public:

				static std::map<std::string, int> statenamemap;
				static std::map<std::string, int>::iterator statenamemapiterator;
				static int stateindex;
				static void statenameadd(std::string statename);

				float counter;
				float count;
				float delta;
				int previousstate;
				int nextstate;
				int transitstate;
				int state;

				void clear(void);
		};

		class behavior{
			/*!
			* Description: Interactive Operation Event-drive
			*	controls Agent Event behavior via script
			*/

			public:

				class eventscript{
					public:
						darklua::task *task;
						void inherit(eventscript *parent);
						eventscript(void);

				};

				static std::map<std::string,behavior *> namemap;
				static std::map<std::string,behavior *>::iterator namemapiterator;
				static behavior *create(std::string name, std::string description);
				static void destroy(behavior *behavior);
				static void destroy(void);
				static behavior *get(std::string name);

				std::map<int, eventscript *> eventaction;
				std::string name;
				std::string description;
				behavior(void);
				behavior(std::string name, std::string description);
				~behavior(void);

		};

		class transition{
			/*!
			* Description: Agent Event-driven Transition Animation
			*	Execute Scripts based on Previous Eventstate relative to Current Eventstate
			*/

			public:

				class animation{
					/*!
					* Description: Animation step
					*
					*/

					public:
						darklua::task *task;

				};
				
				class eventscript{
					/*!
					* Description: 
					*
					*/

					public:

						transition *parent;
						//std::map<int, darklua::task  *> task;
						darklua::task *task;

						eventscript(void);
						void inherit(eventscript *parent);
			
						

						/* style and theme device */
						
						/* animation device 
							2D
								avi
								animated sprite
							3D
								keyframe
								bone
						*/
					
						/* movement device
							physics
							ai
							procedural
							input device				
						*/
						
						/* audio device */
					
				} ;

				static std::map<std::string,transition *> namemap;
				static std::map<std::string,transition *>::iterator namemapiterator;
				static transition *create(std::string name, std::string description);
				static void destroy(transition *transition);
				static void destroy(void);
				static transition *get(std::string name);

				std::map<int, eventscript *> eventaction;
				std::string name;
				std::string description;
				transition(void);
				transition(std::string name, std::string description);
				~transition(void);
	
		};
		

		class  body{
			/*!
			* Description: Collision Body powered by 2D(Box2D)/3D(Physx) Physics Engines
			*
			*/
			public:
/*
				class collision{
					//purpose: collision management

					private:
						static const int vector3ID = 1;
						static std::list<int> objectlist;
						static std::list<int>::iterator objectlistiterator;
						enum collisionresponses{NONE, SLIDE, STOP} response;

					public:

						struct contact{
							int sourcetypelistID;
							int desttypelistID;
							float tolerance;
							int response;
							int method;
							//int type //db 3dobject type: mesh, light, camera, sound, pivot (virtual  3d point)
							//int method //overloaded check method select
						};

						static const int typelist_max = 32;
						static const int contact_profile_max = 32;

						enum entitytypes{ ENTITY_TYPE_NONE, ENTITY_TYPE_OBJECT1, ENTITY_TYPE_OBJECT2, ENTITY_TYPE_OBJECTMAX} entitytype;

						static std::list<int> *typelist;
						static std::list<int>::iterator sourcetypelistiterator;
						static std::list<int>::iterator desttypelistiterator;

						static int updatefrequency;	//may individualize updatefrequency & counter for contact profile
													//may also automate refresh rate based to typelist size
						static int updatefrequencycounter;
						static int hitcounter;
						static int profile_index;
						static contact *profile;

						static void start(void);
						static void stop(void);
						static void update(void);
						static void create(int sourcetypelistID, int desttypelistID, int method, int response, float tolerance);
						static void destroy(void);
						static void add(int objectID, int typelistID);
						static void remove(int objectID, int typelistID);
						static bool check(D3DVECTOR position1, D3DVECTOR position2, float tolerance);
						static bool check(float dbObjectPositionX1, float dbObjectPositionY1, float dbObjectPositionZ1, float dbObjectPositionX2, float dbObjectPositionY2, float dbObjectPositionZ2, float tolerance);
						static void process(int sourceobjectID, int destobjectID, int response);

						//entity collision functions defined in entity.cpp
						static int entityobject(int typelistID, int entityID);
						static void entitycollisions(int sourcetypelistID, int sourceentityID, int desttypelistID, int destentityID);

				};
*/
				class physicsobject{ //base class
					public:

						//pure virtuals
						virtual void destroy(void)=0;
						virtual void userdataset(void* userPTR)=0;
						virtual void* userdataget(void)=0;

						//b2world pure virtuals
						virtual void create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping)=0;
						virtual b2Body* bodycreate(const b2BodyDef bodyDef)=0;
						virtual b2World* worldget(void)=0;
						virtual void update(void)=0;

						//b2body pure virtuals
						virtual void create(std::string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor)=0;
						virtual void update(D3DVECTOR &position, D3DVECTOR &angle)=0;
						virtual bool orientationset(b2Vec2 position, float32 angle)=0;

						//b2mouse pure virtuals
						virtual void create(std::string canvasname)=0;
						virtual void update(b2Vec2 p, int actionstate)=0;

				};

				class b2world: public physicsobject{
					private:
						b2AABB worldAABB;
						b2World *world;
						bool allowsleep;
						D3DVECTOR gravity;
						float32 timestep;
						int32 iterations;

					public:
						b2world(void);
						~b2world(void);

						//virtuals
						void create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping);
						void destroy(void);
						void update(void);
						b2World* worldget(void);						
						b2Body* bodycreate(const b2BodyDef bodyDef);
						void userdataset(void *userPTR){};
						void *userdataget(void){return(NULL);};

						//b2body virtual stubs
						void create(std::string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){}
						void update(D3DVECTOR &position, D3DVECTOR &angle){};
						bool orientationset(b2Vec2 position, float32 angle){return(0);};

						//b2mouse virtual stubs
						void create(std::string canvasname){};
						void update(b2Vec2 p, int actionstate){};

				};

				class b2body: public physicsobject{
					private:
						b2World *world;
						int shapetypedef;
						b2BodyDef bodyDef;
						b2Body* dynamicbody;
						b2PolygonDef shapeDef;

					public:
						b2body(void);
						~b2body(void);

						//virtuals
						void create(std::string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor);
						void destroy(void);
						void update(D3DVECTOR &position, D3DVECTOR &angle);
						void userdataset(void *userPTR);
						void *userdataget(void);
						bool orientationset(b2Vec2 position, float32 angle);

						//b2world virtual stubs
						void create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping){}
						b2World* worldget(void){return(NULL);};
						b2Body* bodycreate(const b2BodyDef bodyDef){return(NULL);};
						void update(void){};

						//b2mouse virtual stubs
						void create(std::string canvasname){};
						void update(b2Vec2 p, int actionstate){};
				};

				class b2mouse: public physicsobject{
					private:
						b2World *world;
						b2MouseJoint* mousejoint;

					public:

						b2mouse(void);
						~b2mouse(void);

						//virtual
						void create(std::string canvasname);
						void destroy(void);
						void update(b2Vec2 p, int actionstate);
						void userdataset(void *userPTR){};
						void *userdataget(void){return(NULL);};

						//b2world virtual stubs
						void create(D3DVECTOR &position, D3DVECTOR &size, float gravityx, float gravityy, float32 timestep, int32 iterations, bool allowsleeping){}
						b2World* worldget(void){return(NULL);};
						b2Body* bodycreate(const b2BodyDef bodyDef){return(NULL);};
						void update(void){};

						//b2body virtual stubs
						void create(std::string canvasname, int shapetype, D3DVECTOR &position, D3DVECTOR &size, D3DVECTOR &angle, float density, float friction, float restitution, bool sensor){}
						void update(D3DVECTOR &position, D3DVECTOR &angle){};
						bool orientationset(b2Vec2 position, float32 angle){return(0);};

				};

				std::queue<body*> collisionqueue;
				int type; //2d Procedural, 2D Physics,3D Physics, 3D Polygon, 3D Procedural
				bool collideflag; //register collision between objects
				bool physicsflag; //register for physics simulation
				bool gravityflag; //register for artificial gravity
				bool pathfinderflag; //register to patherfinder
				
				//shape
				D3DVECTOR position;
				D3DVECTOR size;
				D3DVECTOR angle;
				
				physicsobject *physics;
				int collisionexist;

				body(void);
				body(float x, float y, float z, float width, float height, float depth, float anglex, float angley, float anglez);
				~body(void);
				
				//agent
				void center(std::string canvasname);
				void zoom(std::string canvasname);
				void orientate(std::string refagentname, float x, float y, float z, int xalign, int yalign, int zalign);
				void inherit(body *parent);
		};

		class sprite{
			/*!
			* Description: 2D/3D Object, Rendering powered by Particle System
			*
			*/
			public:
				//resource
				int type;//0=3D Sprite, 1=3D Mesh, 2=Animated Image
				int dbImageID;
				int dbObjectID;

				//settings
				int startframe; //2D framesacross
				int stopframe; //2D framesdown
				int currentframe;
				
				//caption
				style *captionstyle;
				int captiontype; //normal, password, hidden, encrpted
				std::string caption; //normal caption
				std::string captionview; //caption:: normal, password, hidden, encrpted
				D3DVECTOR captionposition; //alignment
				D3DVECTOR captionsize;

				//background
				theme *bgtheme;
				int bgimageID;
				D3DVECTOR bgimagealign;
				
				//states
				bool visibleflag;
				int LODFlag;
				
				sprite(void);
				~sprite(void);
				int meshcreate(std::string meshname);
				void meshdestroy(void);
				int meshload(std::string filename);
				int imageget(std::string imagename);
				int imageload(std::string filename, int framesacross ,int framesdown);
				int imagedraw(body *body, int eventstate);
				int imagecapture(body *body, int eventstate);
				void inherit(sprite *parent);

		};

		class agent{
			//Description: Agent Object

			public:

				class eventscript{
					public:
						behavior *behavior;
						transition *transition;
						scheme *scheme;
						sprite *sprite;
						darklua::task *task;

						eventscript(void);
						void inherit(eventscript *parent);
				};

				static std::map<std::string,int> propertynamemap;
				static std::map<std::string,int>::iterator propertynamemapiterator;
				
				static std::map<std::string,agent *> namemap;
				static std::map<std::string,agent *>::iterator namemapiterator;
				static std::list<agent *> activelist;
				static std::list<agent *>::iterator activelistiterator;
				static std::queue<agent *> inactivequeue;
				static int index;
				
				static void propertyadd(std::string key,const int constant);
				static char* propertyget(agent *agent, std::string key);
				static void propertyset(agent *agent, std::string key, char* value);

				static char* variableget(agent *agent, std::string variable);
				static void variableset(agent *agent, std::string variable, std::string value);

				static agent *create(std::string parentname, std::string name, std::string description, bool visible, bool collision);
				static void destroy(agent *agent);
				static void destroy(void);
				static agent *get(std::string name);
				static void update(void);
				static void locate(agent *agent, int actionstate);
				//lineadd()
				//lineremove()
				//linecharacterinsert()
				//linecharacterdelete()
				//texttocaption()

				std::map<int, eventscript *> eventaction;
				std::map<std::string, std::string>valuemap;
				std::map<std::string, std::string>::iterator valuemapiterator;
				std::string name;
				std::string description;
				int ID;
				int type;
				int parentalcontrol; //bitwise map
				agent *parent,*first,*last,*previous,*next;
				device *device;
				body *body;
				int spriteID; // 2D(1 dbSprite : Action x Image, IDLE is default for all) || 3D(Action x Object, IDLE is default for all)
				int priority; //determined by parent
				bool collisionflag;
				bool visibleflag;
				bool audioflag; //mute
				bool activeflag;
				//bool httpformflag;
				esm eventstate;
				enum agentstates{DISABLED,LOADING,DRAW,ACTIVE,TRANSITION,TRANSITIONING,TRANSISTIONED,STATES_MAX} state;
				ticker sync;

				agent(void);	//constructors
				agent(std::string name, std::string description);
				~agent(void);	//destructor
				void process(void);
				void inherit(agent *parent);
				void familyadd(agent *parent);
				void familyremove(void);
				void imagecapture(int actionstate);
				void texturecapture(int actionstate);

				void spriteoffset(void);
				void control(void);
				void display(void);
				void produce(void);
				void collision(void);
				void operate(void);
				void action(void);
				void transit(void);
				void trash(void);

		};

		class httpform{
			public:
				static std::map<std::string,httpform *> namemap;
				static std::map<std::string,httpform *>::iterator namemapiterator;
				static std::list<httpform *> activelist;
				static std::list<httpform *>::iterator activelistiterator;
				static std::queue<httpform *> inactivequeue;				
			
				static httpform *create(std::string name, std::string description, int method, std::string hostname, int port, std::string page, std::string writepath );
				static void destroy(httpform *httpform);
				static void update(void);
				static void submit(std::string name);

				std::list<agent *> agentlist;
				std::list<agent *>::iterator agentlistiterator;
				std::string name;
				std::string description;
				std::string hostname;
				int port;//default 80
				std::string page;
				std::string writepath;
				int method;
				darknet::http *http;
				enum httpformstates{IDLE, SENDING, RECEIVING, READY, TERMINATE} state;

				httpform(void);
				httpform(std::string name, std::string description);
				~httpform(void);
				void process(void);
				void submit(void);
		};

		class xmlfile{
			/*!
			* Description: *.brains file format reader
			*
			*/

			private:
				IrrXMLReader *xml;

			public:
				static std::map<std::string,int> nodenamemap;
				static std::map<std::string,int>::iterator nodenamemapiterator;
				static std::map<std::string,int> attributevaluemap;
				static std::list<xmlfile *> activelist;
				static std::list<xmlfile *>::iterator activelistiterator;
				static std::queue<xmlfile *> inactivequeue;
				static void nodenameadd(std::string nodename, int constant);
				static void attributevalueadd(std::string attributevalue, int constant);
				static void update(void);

				std::stack< std::pair<int,std::string> > parsestack;
				std::queue<brains::agent*> loadedagentqueue;
				//syntax error checking
				int nodecount;

				ticker sync;
				enum xmlfilestates{IDLE, LOAD, LOADING, COMPLETE} state;

				xmlfile(std::string filename);//constructor
				~xmlfile(void);//destructor

				void process(void);
				int parse(void);

				int syntaxerror(std::string errormsg);
		};

		//DGDK Object Resource Manager Pointers
		static resourcemanager *dbMemblockResource;
		static resourcemanager *dbBitmapResource;
		static resourcemanager *dbImageResource;
		static resourcemanager *dbSpriteResource;
		static resourcemanager *dbObjectResource;
		static resourcemanager *dbSoundResource;
		static resourcemanager *dbMusicResource;
		static resourcemanager *dbCameraResource;
		static resourcemanager *dbLightResource;

		static behavior *defaultbehavior;
		static transition *defaulttransition;

		static agent *baseagent;
		static agent *pointer;

		static debugclipbrd *bugboard;
		static std::string output;

		static std::map<std::string,int> scancodemap;

		static void start(void);
		static void stop(void);
		static void update(void);
		static int load(std::string filename);

		brains(void);//constructor
		~brains(void);//destructor
			
};

#endif

/*
TODO LIST

DESIGN NOTES:

BRAINS

	EventState
	Behavior
	Transitions
	Agent
		Actions
	Bot

Box2D Meters to Pixels
http://www.emanueleferonato.com/2008/11/17/understanding-pixels-and-meters-with-box2d-and-how-to-select-an-object-with-mouse-part-2/

Bot = Composite Agents

*/