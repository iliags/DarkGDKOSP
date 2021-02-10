/*
 _____                              _     _      ______       _____      _     _      _______
   |        |           |           |     |      |     \        |        |     |      |  |  |
 __|__      |_____      |_____      |_____|      |_____/      __|__      |_____|      |  |  | PU36
A Particle System Manager by F.L.Taylor 2010 ©

 based on the Particle API by by David K. McAllister, davemc@cs.unc.edu
 http://www.particlesystems.org. 

*/

#include "Illudium.h"

// SYSTEM //////////////////////////////////////////////////////////////////////////////////////////
/**
* @class	Illudium System
* @brief	The Particle represents a unique Particle System defined by behavior, transitions, Sprites.
*/

/**
Global Singleton Interfaces
*/
Illudium::Fuzz* Illudium::Fuzz::CurrentFuzz = NULL;
Illudium::Reactor* Illudium::Reactor::CurrentReactor = NULL;

/**
* @brief	Illudium Constructor
* @param	void
*/
Illudium::System::System(void){

}

/**
* @brief	Illudium Destructor
* @param	void
*/
Illudium::System::~System(void){

}

/**
* @brief	Illudium Start
* @param	void
* @return	void
*/
void Illudium::System::Start(void){

}

/**
* @brief	Illudium Stop
* @param	void
* @return	void
*/
void Illudium::System::Stop(void){

}

/**
* @brief	Illudium Update
* @param	void
* @return	void
*/
void Illudium::System::Update(void){

	Reactor::Update();
}


// FUZZ //////////////////////////////////////////////////////////////////////////////////////////
/**
* @class	Illudium Fuzz
* @brief	The Fuzz is a single object based on a Particle Gizmo (Template) 
			that maintains a Particle Emitter and its Fragments.
*/

list<Illudium::Fuzz*> Illudium::Fuzz::ActiveList;
list<Illudium::Fuzz*>::iterator Illudium::Fuzz::ActiveListIterator;
queue<Illudium::Fuzz*> Illudium::Fuzz::InactiveQueue;

ResourceManager *Illudium::Fuzz::FuzzResource = new ResourceManager(ILLUDIUM_FUZZ_MAX);

/**
* @brief	Fuzz Constructor
* @param	void
*/
Illudium::Fuzz::Fuzz(void){

	Emitter = NULL;
	FragmentCount = 0;
	FragmentPTR = ParticlePTR = NULL;
	State = IDLE;
}

/**
* @brief	Fuzz Destructor
* @param	void
*/
Illudium::Fuzz::~Fuzz(void){

}

/**
* @brief	Destroys Fuzz Instance
* @param	void
* @return	void
*/
void Illudium::Fuzz::Destroy(Illudium::Fuzz *instance){
	
	//delete emitter and fragments
	instance->Context.DeleteParticleGroups(instance->ID, instance->FragmentCount);
	FuzzResource->Push(instance->ID);
	delete instance->Effects;
	delete instance;
}

/**
* @brief	Creates Fuzz Instance
			Make Particle Group and sets as the Current Fuzz
* @param	void
* @return	Fuzz*
*/
Illudium::Fuzz* Illudium::Fuzz::Create(MAUI::Gizmo *particle, int fragmentcount){
	
	Fuzz* instance = new Fuzz;
	instance->Emitter = particle;
	instance->FragmentCount = fragmentcount;
	instance->Replicate(instance->Emitter, instance->FragmentCount);
	instance->ID = FuzzResource->Pop();
	instance->Context.CurrentGroup(	instance->Context.GenParticleGroups(instance->ID, instance->FragmentCount) );
	instance->Effects = new ParticleEffects(instance->Context, instance->FragmentCount);
	instance->State = ACTIVE;	
	ActiveList.push_back(instance);

	return instance;
}

/**
* @brief	Updates All Fuzz Instances
* @param	void
* @return	void
*/
void Illudium::Fuzz::Update(void){

	//iterate through active Fuzz Objects
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
* @brief	Process Fuzz States
* @param	void
* @return	void
*/
void Illudium::Fuzz::Process(void){

	CurrentFuzz = this;

	switch(State){

		case IDLE:
			break;

		case ACTIVE:

			//Process Fuzz Effects (PAPI)
			Action();

			//Process Emitter
			//Emitter->Process();
		
			//Process Fragments
			if(Context.GetGroupCount() < 1){
				return;
			}

			FragmentCount = (int)Context.GetParticlePointer(ParticlePTR, Flstride, Pos3Ofs, PosB3Ofs, Size3Ofs, Vel3Ofs, VelB3Ofs, Color3Ofs, Alpha1Ofs, Age1Ofs, Up3Ofs, RVel3Ofs, UpB3Ofs, Mass1Ofs, Data1Ofs);
			/**
			Get PAPI Fragment Properties
			Format: float property = *(FragmentPTR + PropertyOffset + PropertyByteOffset)
			Examples:
				float age = *(FragmentPTR + Age1Ofs);
				D3DVECTOR position = { *(FragmentPTR + Pos3Ofs), *(FragmentPTR + Pos3Ofs + 1), *(FragmentPTR + Pos3Ofs + 2) }; 
			*/

			/**
			Starting PAPI Fragment
			*/
			FragmentPTR = ParticlePTR;

			for(int loop=0;loop<FragmentCount;loop++){

				/**
				Gizmo Fragment Properties
				*/
				MAUI::Gizmo* fragment = FragmentArray[loop];

				fragment->Body->Position.x = *(FragmentPTR + Pos3Ofs);
				fragment->Body->Position.y = *(FragmentPTR + Pos3Ofs + 1);
				fragment->Body->Position.z = *(FragmentPTR + Pos3Ofs + 2); 

				//fragment->Process();

				/**
				Next PAPI Fragment
				*/
				FragmentPTR += Flstride; 
			}
			break;

		default:
			break;

	}

}

/**
* @brief	Fuzz Particle Effects Action
* @param	void
* @return	void
*/
void Illudium::Fuzz::Action(void){

	/*	Reference Effects.cpp
	     0: Atom
	     1: Balloons
	     2: Fireflies 
	     3: Fireworks		//do not use
	     4: Waterfall2
	     5: JetSpray
	     6: Fountain
	     7: FlameThrower
	     8: Rain
	     9: GridShape
	    10: Explosion
	    11: PhotoShape
	    12: Orbit2			//useless
	    13: Restore
	    14: Shower1			//do not use
		16: Shower2			//do not use
		18: Shower3			//do not use
		20: Shower4			//do not use
	    15: BounceToy
		17: Swirl
		19: Snake
		21: Waterfall1
	    22: Sphere
	    23: Experimental
	*/

	Effects->CallDemo(ILLUDIUM_FUZZ_EFFECT_TYPE_FOUNTAIN, false, false);

}

/**
* @brief	Display Fuzz Particle Pool
* @param	void
* @return	void
*/
void Illudium::Fuzz::Display(void){

}

/**
* @brief	Replicate Fuzz Particle Pool
* @param	MAUI::Gizmo *particle
* @param	int fragmentcount
* @return	void
*/
void Illudium::Fuzz::Replicate(MAUI::Gizmo *particle, int fragmentcount){

	for(int loop=0;loop<fragmentcount;loop++){
		
		//name format: name_#
		char* loopstr = dbStr(loop);
		string fragmentname = particle->Name;
		fragmentname.append("_");
		fragmentname.append(loopstr);
		delete loopstr;

		MAUI::Gizmo *fragment = particle->Copy(fragmentname, "");
		//MAUI::Gizmo::ActiveList.remove(fragment);//remove from gizmo
		fragment->Type = particle->Type;
		fragment->OperateFlag = false;
		//fragment->DebugFlag = true;

		//Copy Sprite Display Object
		fragment->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite = particle->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->Copy();
		int fragmentobjectID = dbObjectResource->Pop();
		dbCloneObject(fragmentobjectID, particle->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->dbObjectID);
		dbTextureObject(fragmentobjectID, particle->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->BackdropImageID);
		dbSetObject(fragmentobjectID, 1, 0, 0, 0, 0, 0, 0);		
		fragment->EventAction[MAUI_EVENT_STATE_IDLE]->Sprite->dbObjectID = fragmentobjectID;
		fragment->SpriteID = fragmentobjectID;
		
		//Copy Body|Physics
		if(particle->Body != NULL) fragment->Body = MAUI::Body::Create(particle->Body->Type, particle->Body->Physics->Type, fragmentobjectID);

		FragmentArray.push_back(fragment);
	}

}

// REACTOR //////////////////////////////////////////////////////////////////////////////////////////
/**
* @class	Illudium Reactor
* @brief	The Reactor is a Group of Particle Systems working together to create a complex effect.
*/

map<string,Illudium::Reactor*> Illudium::Reactor::NameMap;
map<string,Illudium::Reactor*>::iterator Illudium::Reactor::NameMapIterator;
list<Illudium::Reactor*> Illudium::Reactor::ActiveList;
list<Illudium::Reactor*>::iterator Illudium::Reactor::ActiveListIterator;
queue<Illudium::Reactor*> Illudium::Reactor::InactiveQueue;

/**
* @brief	Reactor Constructor
* @param	void
*/
Illudium::Reactor::Reactor(void){

	State = IDLE;
}

/**
* @brief	Reactor Destructor
* @param	void
*/
Illudium::Reactor::~Reactor(void){

	NameMap[Name] = NULL;
}

/**
* @brief	Destroy Reactor Instance
* @param	void
* @return	void
*/
void Illudium::Reactor::Destroy(Illudium::Reactor* instance){

	//destroy FuzzObjects
	delete instance;
}

/**
* @brief	Creates Reactor Instance
* @param	void
* @return	Illudium::Reactor*
*/
Illudium::Reactor *Illudium::Reactor::Create(string name, string description){

	Reactor *instance = NULL;
	
	if(NameMap[name] == NULL){
		instance = new Reactor;
		instance->Description = description;
        NameMap[name] = instance;
	}  else {
		instance = NameMap[name];
	}

	instance->State = ACTIVE;
	ActiveList.push_back(instance);

	return instance;

}


/**
* @brief	Copy Reactor Instance
* @param	void
* @return	Illudium::Reactor*
*/
Illudium::Reactor *Illudium::Reactor::Copy(string name, string description){
	
	Reactor *instance = Create(name, description);

	return instance;

}



/**
* @brief	Add Fuzz Object based on Particle Template Name
* @param	string particlename
* @param	int particlecount
* @return	void
*/
void Illudium::Reactor::Add(string particlename, int particlecount){

	if(MAUI::Gizmo::NameMap[particlename] != NULL){
		FuzzList.push_back(Fuzz::Create(MAUI::Gizmo::NameMap[particlename],particlecount));
	}
}

/**
* @brief	Remove Fuzz Object based on Particle Template
* @param	string particlename
* @return	void
*/
void Illudium::Reactor::Remove(string particlename){

}

/**
* @brief	Update All Active Reactors
* @param	void
* @return	void
*/
void Illudium::Reactor::Update(void){

	//iterate through active Reactors
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
* @brief	Process Reactor Instance States
* @param	void
* @return	void
*/
void Illudium::Reactor::Process(void){

	CurrentReactor = this;
	
	switch(State){

		case IDLE:
			break;
	
		case ACTIVE:
			//iterate through Fuzz Objects
			for(FuzzListIterator = FuzzList.begin(); FuzzListIterator != FuzzList.end(); FuzzListIterator++ ){
					(*FuzzListIterator)->Process();
			}
			break;
	}
}