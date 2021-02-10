/*
|``````.        .'.       |`````````, |    ..'' |        |         |       .'.       
|       |     .''```.     |'''|'''''  |..''     |        |         |     .''```.     
|       |   .'       `.   |    `.     |``..     |        |         |   .'       `.   
|......'  .'           `. |      `.   |    ``.. |_______ `._______.' .'           `. 

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

/*
DarkLUA v1.1 Plug-in by Frankie `techlord//Taylor
based on LUA for Windows 5.1.4 HTTP://luaforwindows.luaforge.net/

References:
	HTTP://darkgdkosp.svn.sourceforge.net/viewvc/darkgdkosp/Include/lua_plugin.h?revision=6&view=markup
	HTTP://www.codegurus.be/codegurus/Programming/luaintroduction_en.htm

	LUA Compiler
	http://www.lua.org/manual/4.0/luac.html

*/

/**
Introduction

DarkLUA Scripting System is designed with the goal of building Applications and AI in a hierarchal and
modular fashion using self contained blocks of script called Batches.

DarkLUA Language is a multi-layered Language that contains several language `layers//utilizing a sequence
of Preprocessors to convert it into `pure//LUA Language.

Application Hierarchy:

	Batch -> Task/Job -> Service -> Applet -> Application

	1. Batch = a text file or string containing a series of Script Language commands. It can be
		embedded in between other text such as a markup Language.
		1b. Macro = Name Key associated to a Batch that can be embedded in other scripts.

	2. Task =  A dependent Batch procedure attached and controlled externally by another object or
		2b. Job = is a independent Task procedure controlled internally. It uses FSM to manage its
			own state.

		reserved lua Batch vars:
		this - Reference to Batch ID currently being processed
		me - Reference to object ID the Batch belongs to

	3. Service = A group of Tasks that work together to perform specific functions within a Application
		without user input. Each Task or Job can effect the state of each other.

	4. Applet = A group of Services that work together within a Application that may or may not require
		user input. A CLI or GUI is usually applied to frontend for use	by a user.

	5. Application = A series of Applets integrated together.

AI Hierararchy:

	Finite State Machine
		EventState Triggered via Condition Check (comparison, collision, input state checks)

		- Action = Batch that executes during a particular EventState.
		- Behavior = Batch that manages an Object's EventStates.
		- Transition = Batch that executes between Event State transition.
		- Global Event = Series of Object Actions triggered by one or more Object EventState Changes

	Neural Network and Genetic Algorithms
		- Node
		- Neurode


int to LUA Script Accessibility

	DarkLUA provides a Priviledge system for accessing Functions explosed to LUA.
	Priviledges are defined in Script Header.

	Levels of Access: None, Read, Write, Execute

		read commands

		write commands any command that assigns or changes the property values

			set, modify, update
			save,open

	Group Priviledge

	int Group Prividges
		Priviledge per Group

	User Priviledge


*/

#pragma once
#ifndef DARKLUA_H
#define DARKLUA_H

#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>

//lua
//#include "..\LUA\etc\lua.hpp"
#include "..\LUA\lua.hpp"

#include "S3GE_Common.h"
#include "diag.h"

using namespace std;

#define DARKLUA_BATCH_MAX	512
#define DARKLUA_TASK_MAX	512

#define DARKLUA_ERROR	-1
#define DARKLUA_ERROR_MESSAGE_SIZE	256

#define DARKLUA_INT(n)	lua_tointeger(L,n)
#define DARKLUA_FLOAT(n)	(float)lua_tonumber(L,n)
#define DARKLUA_STRING(n)	lua_tostring(L,n)
#define DARKLUA_POINTER(n)	lua_topointer(L,n)

#define DARKLUA_RETURNINT(n)	lua_pushinteger(L,n)
#define DARKLUA_RETURNFLOAT(n)	lua_pushnumber(L,n)
#define DARKLUA_RETURNSTRING(n)	lua_pushstring(L,n)
#define DARKLUA_RETURNPOINTER(n)	lua_pushlightuserdata(L,n)


/**
* @brief	DarkLUA System Class using LUA 5.1	
* @remarks	F.L.Taylor aka TechLord 11/09/10
*/
namespace DarkLUA{

		/**
		* @brief	DarkLUA's Stack Machine Class (TBD)
		* @remarks	F.L.Taylor aka TechLord 11/09/10
		*/
		class Machine{
			public:
				static list<Machine*> Instance;

				vector<int> instructionvector;
				stack<string> ProcessStack;

				string EAX;
				string ECX;

				lua_State *L;

				bool ZFlag;
				int InstructionIndex;
				int SuspendTimer;
				
				enum ProcessStates{HALT,SUSPEND,SUSPENDING,SUSPENDED,RESUSPEND,RUN,RUNNING} State;

				Machine(void); //constructor
				~Machine(void); //destructor
				void Process(void);
				void Run(void);
				void Halt(void);
				void Suspend(int duration);
				void Pause(void);

				void Load(string filename);
				void Save(string filename);

		};

		/**
		* @brief	DarkLUA's Batch Class, stores Script
		* @remarks	F.L.Taylor aka TechLord 11/09/10
		*/
		class Batch{
			public:	
				static map<string,Batch*> NameMap;
				static map<string,Batch*>::iterator NameMapIterator;
		
				string Name;
				string Description;
				string Script; //! general purpose script data

				//! methods
				Batch(void);
				Batch(string name, string script); //load  will first look for a Batch config header (Markup Lang) at the top of Batch file or string that defines what if(its compile and preprocessors to use
				~Batch(void);
				void Load(string filename);
				
		};

		/**
		* @brief	DarkLUA's Task Class, Performance Operation and Maintenance on Batch
		* @remarks	F.L.Taylor aka TechLord 11/09/10
		*/
		class Task{

			public:
				/**
				* @brief	File Structure passed to luaMemRead Method
				* @remarks	F.L.Taylor aka TechLord 11/09/10
				*/
				typedef struct luaMemFile{
				  const char *text;
				  size_t size;
				} luaMemFile;


				static map<string,Task*> NameMap;
				static map<string,Task*>::iterator NameMapIterator;

				static list<Task*> ProcessList;
				static list<Task*>::iterator ProcessListIterator;
				static queue<Task*> InactiveQueue;

				static const char *LUAFileRead(lua_State *, void *ud, size_t *size);

				map<int, Batch*> ActionBatch;
				map<int, Batch*> BehaviorBatch;
				map<int, Batch*> TransitionBatch;
				static void Update(void);

				string Name;
				string Description;

				luaMemFile LUAFile; //lua reader var

				Task *Parent, *First, *Last, *Next, *Previous;	

				float StartTime;
				float StopTime;
				float Frequency;
				float DurationCount;
				float DurationCounter;
				int Shared;

				enum ExecutionTypes{NONE,ONCE,DURATION,FOREVER} ExecutionType;
				enum StartupTypes{DISABLE,AUTOMATIC,MANUAL,STARTUPTYPE_MAX} StartupType;
				//enum StopTypes{NONE,AUTOMATIC,MANUAL,STOPTYPE_MAX} StopType;
				enum States{IDLE,RUN,RUNNING,SUSPEND,SUSPENDING,SUSPENDED,RESUME,RESUMING,TERMINATE,TERMINATING,TERMINATED,STATE_MAX} State;
				
				//! methods
				Task(void);
				Task(string name, string script);
				~Task(void);

				void Process(void);

				//state commands
				void Run(void);
				void Halt(void);
				void Suspend(void);
				int Execute(void);
				void Execute(States state);
				void Schedule(DarkLUA::Task::ExecutionTypes ExecutionType, DarkLUA::Task::StartupTypes StartupType, int DurationCount);
				void Schedule(DarkLUA::Task::ExecutionTypes ExecutionType, DarkLUA::Task::StartupTypes StartupType, int StartTime, int StopTime);

				int Clone(Task *task);
				int CloneByName(string name);
				int Inherit(Task &task);

		};

		/**
		* @brief	DarkLUA's Service Class, Performance Operation and Maintenance on a Group of Task serving a single purpose.
		* @remarks	F.L.Taylor aka TechLord 11/09/10
		*/
		class Service{
			public:
				
				static map<string,Service*> NameMap;
				static map<string,Service*>::iterator NameMapIterator;

				list<Task*> TaskList;
				
				string Name;
				string Description;

				Service *Parent, *First, *Last, *Next, *Previous;	

				float StartTime;
				float StopTime;

				enum SystemStatus{IDLE,START,STARTING,STARTED,STOP,STOPING,STOPPED,PAUSE,RESUME,RESUMING,RESTART,SYSTEMSTATUS_MAX} status;
				enum StartupTypes{DISABLE,AUTOMATIC,MANUAL,STARTUPTYPE_MAX} StartupType;
				//enum StopTypes{DISABLE,AUTOMATIC,MANUAL,STOPTYPE_MAX} StopType;

				Service(void);
				~Service(void);
				
				//void add(task *job);

		};

		/**
		* @brief	DarkLUA's Applet Class, Performance Operation and Maintenance on a Group of Services serving a single Application.
		* @remarks	F.L.Taylor aka TechLord 11/09/10
		*/
		class Applet{
			public:				
				static map<string,Applet*> NameMap;
				static map<string,Applet*>::iterator NameMapIterator;

				list<Service*> ServiceList;
				
				string Name;
				string Description;
				
				Applet *Parent, *First, *Last, *Next, *Previous;	

				Applet(void);
				~Applet(void);
				//add(Service *Service);
		};

		/**
		* @brief	DarkLUA's Table Class, Binds C++ Table to LUA Table
		* @remarks	F.L.Taylor aka TechLord 11/09/10
		*/
		class Table{
			public:
				//lua_State *L;
				char *Name;
				int Top;

				Table(void);
				~Table(void);
				void Open(char* tablename);
				void Close(void);		
				void Select(char* tablename);			
				void BoolSet(const char *key, int value);
				bool BoolGet(const char *key);
				void IntegerSet(const char *key, int value);
				int IntegerGet(const char *key);
				void FloatSet(const char *key, float value);
				float FloatGet(const char *key);
				void StringSet(const char *key, char  *value);
				char *StringGet(const char *key);
				void PointerSet(const char *key, void  *value);
				void *PointerGet(const char *key);
		};
		
		class System{
			public:
	
				/* the Lua interpreter */
				static lua_State *L;
						
				static string ErrorMessage;
				static int ErrorFlag;
		
				//static void bind(lua_State *L,(*function), const char *commandname, const char *parameter, const char *returnvalue, const int priviledgeclassID=0);
				static void Start(void);
				static void Stop(void);
				static void Update(void);	
				static void Bindings(void);
		
				static void BoolSet(char *variablename, int value);
				static bool BoolGet(char *variablename);
				static void IntegerSet(char *variablename, int value);
				static int IntegerGet(char* variablename);
				static void FloatSet(char* variablename, float value);
				static float FloatGet(char* variablename);
				static void StringSet(char* variablename, char *value);
				static char *StringGet(char* variablename);
				static void PointerSet(char* variablename, void *value);
				static void *PointerGet(char* variablename);
		
				static string Execute(string scriptname, string script, string scriptreturnvariablename);
				static string Embed(string prefix, string postfix, string scriptname, string script, char *scriptreturnvariablename);
		};

}

/**
* @brief	LUA Library Extensions, defines lua_pushXXX (where XXX can be "string", "number", "boolean", ...) but,
* @remarks	F.L.Taylor aka TechLord 11/09/10
*
* Doesn't define the lua_popXXX versions. 
*/
inline LUA_API lua_Number lua_popnumber(lua_State *L)
{
  register lua_Number tmp = lua_tonumber(L, lua_gettop(L));
  lua_pop(L, 1);
  return tmp;
}

inline LUA_API const char *lua_popstring(lua_State *L)
{
  register const char *tmp = lua_tostring(L, lua_gettop(L));
  lua_pop(L, 1);
  return tmp;
}

#endif