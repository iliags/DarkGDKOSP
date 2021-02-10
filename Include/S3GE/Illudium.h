/*
 _____                              _     _      ______       _____      _     _      _______
   |        |           |           |     |      |     \        |        |     |      |  |  |
 __|__      |_____      |_____      |_____|      |_____/      __|__      |_____|      |  |  | PU36
A Particle System Manager by F.L.Taylor 2010 ©

 based on the Particle API by by David K. McAllister, davemc@cs.unc.edu
 http://www.particlesystems.org. 

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
#ifndef ILLUDIUM_H
#define ILLUDIUM_H

#include "MAUI.h"
#include "..\PAPI\Particle2\Particle\pAPI.h"
#include "..\PAPI\Particle2\PSpray\Effects.h"

using namespace std;
using namespace PAPI;

#define ILLUDIUM_FUZZ_MAX 128

#define	ILLUDIUM_FUZZ_EFFECT_TYPE_ATOM	0
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_BALLOONS	1
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_FIREFLIES	2
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_FIREWORKS	3
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_WATERFALL2	4
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_JETSPRAY	5
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_FOUNTAIN	6
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_FLAMETHROWER	7
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_RAIN	8
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_GRIDSHAPE	9
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_EXPLOSION	10
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_PHOTOSHAPE	11
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_ORBIT2	12
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_RESTORE	13
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_SHOWER1	14
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_SHOWER2	16
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_SHOWER3	18
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_SHOWER4	20
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_BOUNCETOY	15
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_SWIRL	17
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_SNAKE	19
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_WATERFALL1	21
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_SPHERE	22
#define	ILLUDIUM_FUZZ_EFFECT_TYPE_EXPERIMENTAL	23

namespace Illudium{

		class Fuzz{
			//Particle Group Object
			public:
				static list<Fuzz*> ActiveList;
				static list<Fuzz*>::iterator ActiveListIterator;
				static queue<Fuzz*> InactiveQueue;

				static ResourceManager *FuzzResource;
				static Fuzz* CurrentFuzz;

				MAUI::Gizmo* Emitter;
				vector<MAUI::Gizmo*> FragmentArray;
				vector<MAUI::Gizmo*>::iterator FragmentArrayIterator;
				int FragmentCount;

				//PAPI
				int ID;
				ParticleContext_t Context;
			    float *ParticlePTR, *FragmentPTR;
				size_t Flstride, Pos3Ofs, PosB3Ofs, Size3Ofs, Vel3Ofs, VelB3Ofs, Color3Ofs, Alpha1Ofs, Age1Ofs, Up3Ofs, RVel3Ofs, UpB3Ofs, Mass1Ofs, Data1Ofs;

				//PAPI Action List & Effects Stack
				ParticleEffects *Effects;

				enum ProcessStates{IDLE,ACTIVE} State;

				Fuzz(void);
				~Fuzz(void);

				static void Destroy(Fuzz *instance);
				static Fuzz* Create(MAUI::Gizmo *particle, int fragmentcount);
				static void Update(void);
				void Process(void);
				void Display(void);
				void Replicate(MAUI::Gizmo *particle, int fragmentcount);
				void Action(void);

		};

		class Reactor{
			//Reactor Composite Fuzz
			public: 

				static map<string,Reactor*> NameMap;
				static map<string,Reactor*>::iterator NameMapIterator;
				static list<Reactor*> ActiveList;
				static list<Reactor*>::iterator ActiveListIterator;
				static queue<Reactor*> InactiveQueue;
				static Reactor* CurrentReactor;

				list<Fuzz*> FuzzList;
				list<Fuzz*>::iterator FuzzListIterator;

				string Name;
				string Description;

				Reactor(void);
				~Reactor(void);
				enum ProcessStates{IDLE,ACTIVE} State;

				static void Destroy(Reactor* instance);
				static Reactor *Create(string name, string description);
				static void Update(void);
				void Process(void);
				Reactor *Copy(string name, string description);

				void Add(string particlename, int particlecount=1000);
				void Remove(string particlename);

		};

		class System{

			public:
				System(void);
				~System(void);
					
				/**
				Global Singleton Interfaces
				*/
				static void Start(void);
				static void Stop(void);
				static void Update(void);
		};
}

#endif

/*
Design Notes:

Particle System Creation Flow:

	Define Effects Behavior, Transition
		Note: EventAction Scripts for particles are designed
		to work on the particle group for greatest performance.
		Reference quarkbeahvior_idle.lua
	Define Display Theme, Scheme?
	
	Create Particle (Template)
		Assign Effects and Display

	Create Reactor
		Add Fuzz to Reactor
			Create Fuzz Emitter/Fragments
		Control Reactor

		//Illudium Test Example (Hardcode)
		MAUI::Behavior* quarkbehavior = MAUI::Behavior::Create("quarkbehavior", "Quark Behavior");
		quarkbehavior->Assign(MAUI_BEHAVIOR_ASSIGN_PROPERTY_TASK, new DarkLUA::Task("particlescript", "Content/Data/Logic/quarkbehavior_idle.lua"), MAUI_EVENT_STATE_IDLE);
		MAUI::Behavior* quarktransition = MAUI::Behavior::Create("quarktransition", "Quark Transition");
		MAUI::Theme* quarktheme = MAUI::Theme::Create("quarktheme", "Quark Theme");
		MAUI::Style* quarkstyle = MAUI::Style::Create("quarkstyle", "Quark Style");
		MAUI::Scheme* quarkscheme = MAUI::Scheme::Create("quarkscheme", "Quark Scheme");
		MAUI::Object* quarkobject = MAUI::Object::Create(MAUI_OBJECT_TYPE_PRIMITIVE_CUBE);
		MAUI::Body* quarkbody = MAUI::Body::Create(MAUI_BODY_TYPE_3D, MAUI_BODY_PHYSICS3D_TYPE_BOX);
		MAUI::Sprite* quarksprite = MAUI::Sprite::Create(S3GE_OBJECT_TYPE_MESH, "Content/2D/maui.bmp", quarktheme, quarkstyle, quarkobject, quarkbody);
		MAUI::Gizmo* quark = MAUI::Gizmo::Create("","Quark","Example Particle", false, true, false, false, true, false);
		quark->Type = MAUI_GIZMO_TYPE_WIZMO;
		quark->Assign(MAUI_GIZMO_ASSIGN_PROPERTY_BEHAVIOR, quarkbehavior, MAUI_EVENT_STATE_IDLE);
		quark->Assign(MAUI_GIZMO_ASSIGN_PROPERTY_TRANSITION, quarktransition, MAUI_EVENT_STATE_IDLE);
		quark->Assign(MAUI_GIZMO_ASSIGN_PROPERTY_BODY, quarkbody);
		quark->Assign(MAUI_GIZMO_ASSIGN_PROPERTY_SPRITE, quarksprite, MAUI_EVENT_STATE_IDLE);
		Illudium::Reactor* quarkreactor = Illudium::Reactor::Create("quarkreactor", "Quark Reactor");
		quarkreactor->Add("Quark",16);


Dynamic Particles
	Fluid
	Pyrotechnics
	Hair?

Semi-Dynamic Particles
	LensFlare

Static Particles
	Flora 
	Decals




*/