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
DarkLUA 1.1 Plug-in by Frankie `techlord//Taylor
based on LUA for Windows 5.1.4 HTTP://luaforwindows.luaforge.net/
*/

#include "..\DarkGDK\DarkGDK.h"
#include "DarkLUA.h"

using namespace std;

// GENERAL /////////////////////////////////////////////////////////////////////////////////////////////////////////////
list<DarkLUA::Task*> DarkLUA::Task::ProcessList;
list<DarkLUA::Task*>::iterator DarkLUA::Task::ProcessListIterator;
queue<DarkLUA::Task*> DarkLUA::Task::InactiveQueue;

lua_State *DarkLUA::System::L;
string DarkLUA::System::ErrorMessage = ""; //Note: this data type format has to be used for other LPSTR buffers
int DarkLUA::System::ErrorFlag;

/**
* @brief	Initializes LUA Plugin. Reference LUA for Windows 5.1.4 (HTTP://luaforwindows.luaforge.net)
* @param	void
* @return	void
*/
void DarkLUA::System::Start(void){

	/* initialize Lua */
	L = lua_open();
	//lua_baselibopen(L);/* load Lua base libraries */

	//register bindings
	Bindings();

	if(ErrorFlag){
		//!Exit Prompt "LUA ERROR"
		//Exit to windows
		//return(ErrorFlag);
	}

	//Globals
	DarkLUA::System::IntegerSet("self",0); //this integer ID
	DarkLUA::System::PointerSet("this",NULL); //this pointer

	//BugLog setup
	string buglogname = "Content/Logs/S3GE";
	//buglogname.append(".");
	//buglogname.append(dbStr((int)time(NULL)));
	buglogname.append(".log.html");
	BugLog = debuglog::create((char*)buglogname.data());
	BugLog->enable();
	BugLog->append("<html>\n<head>\n<title>");
	BugLog->append(BugLog->name);
	BugLog->append("</title>\n</head>\n<body>\n<h3>");
	BugLog->append(BugLog->name);
	BugLog->print("</h3>");
}

/**
* @brief	Shutdown LUA Plugin
* @param	void
* @return	void
*/
void DarkLUA::System::Stop(void){


	/* cleanup Lua */

	// Verify the stack
	// (don't forget to include crtdbg.h)
	_ASSERT(lua_gettop(L) == 0);

	lua_close(L);

	if(BugLog != NULL) {
		BugLog->print("\n</body>\n</html>");
		debuglog::destroy(BugLog);
	}

}

/**
* @brief	updates all task & jobs (services & apps)
* @param	void
* @return	void
*/
void DarkLUA::System::Update(void){

	Task::Update();
}

/**
* @brief	User-defined reader int for use by LUA.
			A Recursive int that reads text into LUA until EOF or Size = 0;
* @param	lua_State *  - Lua State
* @param	void *userdata - void pointer redifined as (struct luadata *) within the function
* @return	const char - script->data
*/
const char *DarkLUA::Task::LUAFileRead(lua_State *, void *ud, size_t *size){

	// Convert the ud pointer (UserData) to a pointer of our structure
	luaMemFile *LUAFile = (luaMemFile *) ud;

	// Are we done?
	if(LUAFile->size == 0)
		return NULL;

	// Read everything at once
	// And set size to zero to tell the next call we're done
	*size = LUAFile->size;
	LUAFile->size = 0;
	// Return a pointer to the readed text
	return LUAFile->text;
}

/*
DarkLUA Global Variables

	Example of Uses:

		1. Create/Assign to Global Variable

			DarkLUA::System::IntegerSet("luaVar",100);

		2. Access Value to Global Variable

			int cVar = DarkLUA::System::IntegerGet("luaVar");

*/

/**
* @brief	Set Value to Global Variable via C++;
			Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	variablename
* @param	value
* @return	void
*/
void DarkLUA::System::BoolSet(char* variablename, int value){

	lua_pushboolean(System::L, value);
	lua_setglobal(System::L, variablename);
}

/**
* @brief	Get Value from Global Variable via C++;
* @param	char* variablename
* @param	int value
* @return	void
*/
bool DarkLUA::System::BoolGet(char* variablename){

	lua_getglobal(System::L, variablename);
	bool value = (bool)lua_toboolean(System::L, -1);
	lua_pop(System::L, 1);
	return value;
}

/**
* @brief	Set Value to Global Variable via C++;
			Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	char* variablename
* @param	int value
* @return	void
*/
void DarkLUA::System::IntegerSet(char* variablename, int value){

	lua_pushnumber(System::L, value);
	lua_setglobal(System::L, variablename);
}

/**
* @brief	Get Value from Global Variable via C++;
* @param	variablename
* @return	int
*/
int DarkLUA::System::IntegerGet(char* variablename){

	lua_getglobal(System::L, variablename);
	int value = (int)lua_tointeger(System::L, -1);
	lua_pop(System::L, 1);
	return value;
}

/**
* @brief	Set Value to Global Variable via C++;
* @param	variablename
* @param	value
* @return	void
*/
void DarkLUA::System::FloatSet(char* variablename, float value){

	lua_pushnumber(System::L, value);
	lua_setglobal(System::L, variablename);
}

/**
* @brief	Get Value from Global Variable via C++;
* @param	variablename
* @return	float
*/
float DarkLUA::System::FloatGet(char* variablename){

	lua_getglobal(System::L, variablename);
	float value = (float)lua_tonumber(System::L, -1);
	lua_pop(System::L, 1);
	return value;
}

/**
* @brief	Set Value to Global Variable via C++;
* @param	char* variablename
* @param	char *value
* @return	void
*/
void DarkLUA::System::StringSet(char* variablename, char *value){

	lua_pushstring(System::L, value);
	lua_setglobal(System::L, variablename);
}

/**
* @brief	Get Value from Global Variable via C++;
* @param	char *variablename
* @return	char*
*/
char *DarkLUA::System::StringGet(char *variablename){

	lua_getglobal(System::L, variablename);
	char* value = (char*)lua_tostring(System::L, -1);
	lua_pop(System::L, 1);
	return value;
}

/**
* @brief	Set Value to Global Variable via C++;
* @param	char* variablename
* @param	void *value
* @return	void
*/
void DarkLUA::System::PointerSet(char* variablename, void *value){

	lua_pushlightuserdata(System::L, value);
	lua_setglobal(System::L, variablename);
}

/**
* @brief	Get Value from Global Variable via C++;
* @param	char *variablename
* @return	void
*/
void *DarkLUA::System::PointerGet(char *variablename){

	lua_getglobal(System::L, variablename);
	void* value = (void*)lua_topointer(System::L, -1);
	lua_pop(System::L, 1);
	return value;
}

/*
DarkLUA Table

	Example of Uses:

		1. Create Fields to Table

			DarkLUA::table cTable;
			ctable = new DarkLUA::table;
			cTable->open("luaTable");
			cTable->StringSet("username","nickname");
			cTable->IntegerSet("score",0);
			cTable->close();

		2. Assign/Access Fields to Table

			Note: select Method must be called separately before calling set or get methods.
			Set / Get methods cannot be used interchangably after the same select method.

			GOOD

			cTable->select("luaTable");
			cTable->StringSet("username","techlord");
			cTable->IntegerSet("score",25000);

			cTable->select("luaTable");
			char* cUsername = cTable->StringGet("username");
			int cScore = cTable->IntegerGet("score");

			BAD

			cTable->select("luaTable");
			cTable->StringSet("username","techlord");
			char* cUsername = cTable->StringGet("username");
			cTable->IntegerSet("score",25000);
			int cScore = cTable->IntegerGet("score");
*/


/**
* @brief	Table Constructor
* @param	void
*/
DarkLUA::Table::Table(void){

	Name = NULL;
	Top = 0;
}

/**
* @brief	Table Destructor
* @param	void
*/
DarkLUA::Table::~Table(void){

}

/**
* @brief	Creates New LUA Table to set fields via C++;
* @param	char* tablename
* @return	void
*/
void DarkLUA::Table::Open(char* tablename){
	
	Name = tablename;
	lua_newtable(System::L);
	Top = lua_gettop(System::L); 

}

/**
* @brief	Closes and opened table Global Variable via C++;
* @param	void
* @return	void
*/
void DarkLUA::Table::Close(void){

	lua_setglobal(System::L, Name);
}

/**
* @brief	setsup LUA Table to get fields via C++;
* @param	tablename
* @param	void
* @return	void
*/
void DarkLUA::Table::Select(char* tablename){

	lua_getglobal(System::L, tablename);
	if (!lua_istable(System::L, -1)){
		System::ErrorMessage = "not valid table";
	}
	
}

/**
* @brief	Set Value to Table via C++;
* @param	const char *key
* @param	int value
* @return	void
*/
void DarkLUA::Table::BoolSet(const char *key, int value){

	lua_pushstring(System::L, key);
	lua_pushnumber(System::L, value);
	lua_settable(System::L, Top);
}

/**
* @brief	Set Value to Table via C++;
* @param	const char *key
* @return	bool
*/
bool DarkLUA::Table::BoolGet(const char *key){

	lua_pushstring(System::L, key);
	lua_gettable(System::L, Top);  /* get [key] */
	if (!lua_isnumber(System::L, -1)){
		System::ErrorMessage = "invalid field datatype, expected bool";
		return(false);
	}
	bool value = (bool)lua_toboolean(System::L, -1);
	lua_pop(System::L, 1);  /* remove number */
	return(value);

}

/**
* @brief	Add Value to Table via C++;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	tablename
* @param	value
*
* @return	
* @param	void
*/
void DarkLUA::Table::IntegerSet(const char *key, int value){

	lua_pushstring(System::L, key);
	lua_pushnumber(System::L, value);
	lua_settable(System::L, Top);
}


/**
* @brief	Set Value to Table via C++;
* @param	const char *key
* @return	int
*/
int DarkLUA::Table::IntegerGet(const char *key){


	lua_pushstring(System::L, key);
	lua_gettable(System::L, Top);  /* get [key] */
	if (!lua_isnumber(System::L, -1)){
		System::ErrorMessage = "invalid field datatype, expected integer";
		return(0);
	}
	int value = (int)lua_tonumber(System::L, -1);
	lua_pop(System::L, 1);  /* remove number */
	return(value);
}

/**
* @brief	Add Value to Table via C++;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	tablename
* @param	value
*
* @return	
* @param	void
*/
void DarkLUA::Table::FloatSet(const char *key, float value){


	lua_pushstring(System::L, key);
	lua_pushnumber(System::L, value);
	lua_settable(System::L, Top);
}

/**
* @brief	Set Value to Table via C++;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	tablename
* @param	value
*
* @return	
* @param	void
*/
float DarkLUA::Table::FloatGet(const char *key){


	lua_pushstring(System::L, key);
	lua_gettable(System::L, Top);  /* get [key] */
	if (!lua_isnumber(System::L, -1)){
		System::ErrorMessage = "invalid field datatype, expected float";
		return(0);
	}
	float value = (float)lua_tonumber(System::L, -1);
	lua_pop(System::L, 1);  /* remove number */
	return(value);

}

/**
* @brief	Add Value to Table via C++;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	tablename
* @param	value
*
* @return	
* @param	void
*/
void DarkLUA::Table::StringSet(const char *key, char  *value){


	lua_pushstring(System::L, key);
	lua_pushstring(System::L, value);
	lua_settable(System::L, Top);
}

/**
* @brief	Set Value to Table via C++;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	tablename
* @param	value
*
* @return	
* @param	void
*/
char *DarkLUA::Table::StringGet(const char *key){


	lua_pushstring(System::L, key);
	lua_gettable(System::L, Top);  /* get [key] */
	if (!lua_isstring(System::L, -1)){
		System::ErrorMessage = "invalid field datatype, expected string";
		return("");
	}
	char *value = (char*)lua_tostring(System::L, -1);
	lua_pop(System::L, 1);  /* remove number */
	return(value);
}

/**
* @brief	Add Value to Table via C++;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	tablename
* @param	value
*
* @return	
* @param	void
*/
void DarkLUA::Table::PointerSet(const char *key, void  *value){

	lua_pushstring(System::L, key);
	lua_pushlightuserdata(System::L, value);
	lua_settable(System::L, Top);
}

/**
* @brief	Set Value to Table via C++;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	tablename
* @param	value
*
* @return	
* @param	void
*/
void *DarkLUA::Table::PointerGet(const char *key){


	lua_pushstring(System::L, key);
	lua_gettable(System::L, Top);  /* get [key] */
	if (!lua_islightuserdata(System::L, -1)){
		System::ErrorMessage = "invalid field datatype, expected pointer";
		return("");
	}
	void *value = (void*)lua_topointer(System::L, -1);
	lua_pop(System::L, 1);  /* remove pointer */
	return(value);
}

/**
* @brief	Immediately Executes Script Contents;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	string scriptname
* @param	string script
* @param	char* scriptreturnvariablename
*
* @return	
* @param	string value content
*/
string DarkLUA::System::Execute(string scriptname, string script, string scriptreturnvariablename){


	Task *task = new Task(scriptname, script);
	task->Execute(Task::RUNNING);
	delete task;

	if(scriptreturnvariablename.size()){
		return(StringGet((char*)scriptreturnvariablename.data()));
	}
	return(scriptreturnvariablename);

}

/**
* @brief	Immediately Executes Script Contents, trimming pre-post fix;
*

* Reference: HTTP://gamedevgeek.com/tutorials/calling-lua-functions/
* @param	
* @param	string prefix ie: "<![SCRIPT["
* @param	string postfix ie: "]]>"
* @param	char* scriptreturnvariablename
* @param	string scriptname
* @param	string script
* @param	char* scriptreturnvariablename
*
* @return	
* @param	string value content
*/
string DarkLUA::System::Embed(string prefix, string postfix, string scriptname, string script, char* scriptreturnvariablename){


	if( script.substr(0,prefix.size()).compare(prefix) == 0 ){
		script = script.substr(prefix.size(),script.size());
		if( script.substr(script.size() - postfix.size(),script.size()).compare(postfix) == 0 ){
			script = script.substr(0,script.size() - postfix.size());
		}
		return(Execute(scriptname, script, scriptreturnvariablename));
	}
	return(script);
}


// BATCH /////////////////////////////////////////////////////////////////////////////////////////////////////////////
map<string,DarkLUA::Batch*> DarkLUA::Batch::NameMap;
map<string,DarkLUA::Batch*>::iterator DarkLUA::Batch::NameMapIterator;

/**
* @brief	[Constructor] creates and loads Batch script from file or string
*

* Command: void terminate_lua(void);
*
* @param	
* @param	void
*/
DarkLUA::Batch::Batch(void){

	Name = "Batch";
	Description = "tbd";
	Script = "\0";
	NameMap[Name] = this;

}

/**
* @brief	[Destructor] creates and loads Batch script from file or string
*

* Command: void terminate_lua(void);
*
* @param	
* @param	void
*/
DarkLUA::Batch::~Batch(void){

}


/**
* @brief	creates and loads Batch script from file or string
* @param	string name - name of Batch used for reference and error coding.
* @param	string script - filename or string of script data
			file extensions: 
				.dls = darklua script
				.tpu = dittotpu
				.lua = lua script
* @return	
*/
DarkLUA::Batch::Batch(string name, string script){

	Name = name;

	if(script.substr(script.length()-4,4) == ".lua"){
		Load(script);
	} else {
		Script = script;
	}

	NameMap[name] = this;

	//read header xml within data
	//	get name & description info
	//	get precompiler list
	//  get datatype
	//strip header info from data

}

/**
* @brief	loads a script, and returns string
* Reference: File Loading HTTP://www.cplusplus.com/doc/tutorial/files/
* @param	string filename - filename or string of script data
* @return	void
*/
void DarkLUA::Batch::Load(string filename){

	
	ifstream file((char*)filename.data());

	if (file.is_open()){

		string tmp;

		while (!file.eof()){
			getline(file,tmp);
			Script += tmp;
			Script += "\n";
		}

		file.close();

	} else {

		filename.append(" could not be opened!");
		alertbox("DarkLUA Batch::load",filename,ALERTBOX_SEVERITY_ERROR);

	}

}

// TASK /////////////////////////////////////////////////////////////////////////////////////////////////////////////
map<string,DarkLUA::Task*> DarkLUA::Task::NameMap;
map<string,DarkLUA::Task*>::iterator DarkLUA::Task::NameMapIterator;

/**
* @brief	Task Constructor - creates and loads task script from file or string
* @param	void
*/
DarkLUA::Task::Task(void){

	LUAFile.text = NULL;
	LUAFile.size = 0;
	Parent = First = Last = Next = Previous = NULL;
	Name = "Task";
	Description = "tbd";
	ActionBatch[RUNNING] = new Batch;
	StartTime = StopTime = 0.0f;
	Shared = Frequency = DurationCounter = DurationCount = 0;
	State = IDLE;
}

/**
* @brief	creates/loads task Batch and pushes it processing queue (list)
*

* Command: void terminate_lua(void);
*
* @param	
* @param	string name - name of Batch used for reference and error coding.
* @param	string script - filename or string of script data
*
* @return	
* @param	void
*/
DarkLUA::Task::Task(string name, string script){

	LUAFile.text = NULL;
	LUAFile.size = 0;
	Parent = First = Last = Next = Previous = NULL;
	Name = name;
	ActionBatch[Task::RUNNING] = new Batch(name, script);
	NameMap[name] = this;
	StartTime = StopTime = 0.0f;
	Shared = Frequency = DurationCounter = DurationCount = 0;
	State = IDLE;
	ProcessList.push_back(this);

}

/**
* @brief	[Destructor] creates and loads task script from file or string
*

* Command: void terminate_lua(void);
*
* @param	
* @param	void
*/
DarkLUA::Task::~Task(void){


	//Batch data
	if(ActionBatch[Task::RUNNING] != NULL) {
		delete ActionBatch[Task::RUNNING];
	}
	ProcessList.remove(this);
}

/**
* @brief	Process task states.
* @param	void
* @return	void
*/
void DarkLUA::Task::Update(void){

	for (ProcessListIterator = ProcessList.begin(); ProcessListIterator != ProcessList.end(); ProcessListIterator++ ){
		(*ProcessListIterator)->Process();
	}

	//Garbage Collection clean up inactive task
	while (!InactiveQueue.empty()){
		ProcessList.remove(InactiveQueue.front());
		//delete task
		delete InactiveQueue.front();
		InactiveQueue.pop();
	}
}

/**
* @brief	Process task states.
* @param	void
* @return	void
*/
void DarkLUA::Task::Process(void){

	switch(State){

		case IDLE:
			break;

		case RUN:
			State = RUNNING;
			break;

		case RUNNING:

			switch(ExecutionType){

				//case ONSTARTTIME:

				case ONCE:
				case DURATION:
					if(DurationCounter){
						DurationCounter--;
					} else {
						if(ExecutionType == ONCE) {
							/*then TERMINATE task*/
							State = TERMINATE;
						} else {
							//reset DurationCounter
							DurationCounter = DurationCount;
						}
					}
					break;

				//case NONE:
				//case FOREVER:
				//	break;
			}

			//Batch Execution
			if(State == RUNNING){
				if(Execute()){ //! Error
					System::ErrorFlag = lua_error(System::L);
					State = SUSPEND;
				}
			}
			break;

		case SUSPEND:
			State = SUSPENDING;
			break;

		case SUSPENDING:
			State = SUSPENDED;
			break;

		case SUSPENDED:
			break;

		case RESUME:
			break;

		case RESUMING:
			break;

		case TERMINATE:
			break;

		case TERMINATING:
			break;

		case TERMINATED:
			break;
	}

}

/**
* @brief	parses, compiles and executes task data.
* @param	void
* @return	int ErrorFlag 0=no error;1=error occured
*/
int DarkLUA::Task::Execute(void){

	if(ActionBatch[State]->Script.empty()) return(0);

	//set lua vars this = taskID, me = ownerID
	//@lua::set_int("this",family.self);
	//@lua::set_int("me",ownerID);

	//! execute
	//load first,){call
	LUAFile.text = (char*)ActionBatch[State]->Script.data();
	LUAFile.size = ActionBatch[State]->Script.size();

	//load script
	System::ErrorFlag = lua_load(System::L, LUAFileRead, &LUAFile, (char*)Name.data());

	if(!System::ErrorFlag){
		// Execute the loaded command...
		// The int takes 0 parameters and will return 1 result

 		System::ErrorFlag = lua_pcall(System::L, 0, 1, 0);

		if(!System::ErrorFlag){
			// There was no error
			// Let's get the result from the stack
			lua_Number result = lua_tonumber(System::L, lua_gettop(System::L));
		}

		// Clean-up the stack
		lua_pop(System::L, 1);

	} else {
		// There was a lua_load error...
		// Pop the error value from the stack
		System::ErrorMessage = (char*)lua_tostring(System::L, -1 ); //error message
		lua_pop(System::L, 1);
	}

	//! error detection here
	if(System::ErrorFlag){

		if(System::ErrorMessage.empty()){
			System::ErrorMessage.append("(");
			System::ErrorMessage.append(Name);
			System::ErrorMessage.append(")");
		}
		System::ErrorMessage.append("[");
		System::ErrorMessage.append(dbStr(System::ErrorFlag));
		System::ErrorMessage.append("]");

		alertbox("DarkLUA Execute", System::ErrorMessage, ALERTBOX_SEVERITY_WARNING);
		return(System::ErrorFlag);
	}

	//get return value

	return(0);

}

/**
* @brief	 Executes Script Immediately based on State
*	then executes task data.
*

*
*
* @param	in state state
*
* @return	
* @param	bool ErrorFlag 0=no error;1=error occured
*/
void DarkLUA::Task::Execute(DarkLUA::Task::States state){


	if(state != IDLE){
		States previousstate = this->State;
		this->State = state;
		Execute();
		this->State = previousstate;
	}

}

/**
* @brief	Set Execution Schedule
*	then executes task data.
*

*
*
* @param	in state state
*
* @return	
* @param	bool ErrorFlag 0=no error;1=error occured
*/

void DarkLUA::Task::Schedule(DarkLUA::Task::ExecutionTypes ExecutionType, DarkLUA::Task::StartupTypes StartupType, int DurationCount){

	this->ExecutionType = ExecutionType;
	this->StartupType = StartupType;
	this->DurationCounter = this->DurationCount = DurationCount;

}

/**
* @brief	Runs DarkLUA Task
*

* Command: void terminate_lua(void);
*
*
* @param	int ID = Task ID
*
* @return	
* @param	void
*/
void DarkLUA::Task::Run(void){


	State = RUN;
}

/**
* @brief	Halts DarkLUA Task
*

* Command: void terminate_lua(void);
*
*
* @param	int ID = Task ID
*
* @return	
* @param	void
*/
void DarkLUA::Task::Halt(){


	State = SUSPENDED;

}

/**
* @brief	Suspends DarkLUA Task
*

* Command: void terminate_lua(void);
*
*
* @param	int ID = Task ID
*
* @return	
* @param	void
*/
void DarkLUA::Task::Suspend(void){


	State = SUSPEND;

}



// CATALOG /////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void DarkLUA::catalog::add(lua_State *L,(*function), const char *commandname, const char *parameter, const char *returnvalue, const int priviledgeclassID=0){

///**
//* @brief	Add int to command catalog.
//*
//
//*
//*
//* @param	lua_State *L - LUA State
//* @param	(* functionname) - int pointer
//* @param	char *commandname - Name of command to be call within lua
//* @param	char *parameter - Specifies the types of the arguments the dbpro user command needs.
//*		This is done using a symbol for each type. Types are: $ for String, % for Integer, D for Dword, # for Float.
//* @param	char *returnvalue - Specifies the types of values returned. LUA supports returning more than one
//*		value. similar to the parameter list, this is done using a symbol for each type. if(the command doesn't return
//*		a value use "".
//* @param	int priviledgeclassID
//*
//* @return	
//* @param	void
//*/
//
//	//check priviledgeclass;
//	//lua_pushstring(System::L, "You are not authorized to execute this command.");
//	//if(!authorized exit;
//
//
//	// Verify the number of parameters, we need atleast one!
//	int parametercount = strlen(parameter);
//
//	int n = lua_gettop(L);
//
//	if(n < parametercount){
//		lua_pushstring(System::L, "");// commandname + parametercount
//		lua_error(L);
//	}
//
//	/*
//	Important note: A int pointer always points to a int with a specific signature!
//	Thus all functions, you want to use with the same int pointer, must have the same parameters and return-type!
//*/
//
//	//signature
//	switch(parameter){//read parameter list
//		case "$":
//			char *result = function(lua_tostring(System::L, 1));
//			break;
//
//		case "%###":
//			char *result = function(lua_tointeger(System::L, 1),lua_tofloat(System::L, 2),lua_tostring(System::L, 3),lua_tostring(System::L, 4));
//			break;
//
//		default
//			lua_pushstring(System::L, "Parameter Signature `parameter//not in Catalog.");
//			lua_error(L);
//	}
//
//	// There's one result on the stack
//	//read returnvalues list
//	switch(returnvalue){
//		case "$":
//			lua_pushstring(System::L, result);
//			break;
//		case "%":
//			lua_pushinteger(System::L, result);
//			break;
//		case "#":
//			lua_pushfloat(System::L, result);
//			break;
//	}
//	// (the return value of int if(any)
//
//}