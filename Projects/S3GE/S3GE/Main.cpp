/*
 DarkGDK Open Source Project-Trio
  ______ ______  _______ _______ 
 / _____|_____ \(_______|_______)
( (____  _____) )_   ___ _____   
 \____ \(_____ (| | (_  |  ___)  
 _____) )_____) ) |___) | |_____ 
(______/(______/ \_____/|_______)
Super   3D      Game    Engine
                             
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

#define NOMINMAX      // Matty put here, if(not included we get following:
                      // Error: min or max is #defined, probably in <windows.h>.  Put #define NOMINMAX before including windows.h to suppress windows global min,max macros.

//this MUST be before DarkGDK.h due to winsock incompatibilites with DarkGDK

//#pragma comment(linker, "/LIBPATH:")

#include "..\..\..\Include\DarkGDK\DarkGDK.h"		//by TGC also includes Mike Pryors DarkNet due to compiler issues.
#include "..\..\..\Include\S3GE\S3GE.h"				//by S3GE Enhanced Library
#include "..\..\..\Include\S3GE\DarkLUA.h"			//by Techlord
#include "..\..\..\Include\S3GE\DarkNet.h"			//by DarkNet Extention by Techlord
#include "..\..\..\Include\S3GE\MAUI.h"				//by Techlord
#include "..\..\..\Include\S3GE\Illudium.h"			//by Techlord
#include "..\..\..\Include\S3GE\QuantumPath.h"		//by Techlord

#include "..\..\..\Include\S3GE\Scenergy.h"		//by Techlord

using namespace S3GE;


void DarkGDK( void )
{

START:

	dbSetWindowTitle ("Super 3D Game Engine");
	dbSyncOn();
	dbSyncRate(60); //24p film frame rate
	dbSetDisplayMode( 1024, 768, 32 );
	
	//dbSetWindowOff();
	dbSetWindowPosition( GetSystemMetrics(0)/2 - dbScreenWidth()/2.0, 0 );//GetSystemMetrics(1)/2 - dbScreenHeight()/2.0
	//dbSetDisplayModeAntialias( dbScreenWidth(), dbScreenHeight(), 32, 0, 0, 0 ); //Increases FPS, sporatic behavior
	dbSetImageColorKey(0,0,0);

	/*--------------  Systems Initialization (Priority Sensative) -------------*/
	
	/*First*/	
	DarkLUA::System::Start();

	/*Second*/	
	DarkNet::System::Start("1", DARKNET_INSTANCE_MAX,0); //Game ID Provided by HPQUEST(TOURNAMENTBLITZ)

	/*Third*/	
	Core->Start();///S3GE Core

	/*Others*/
	MAUI::System::Start();
	Illudium::System::Start();
	QuantumPath::System::Start();

	/*Last*/
	Scenergy::System::Start();

	/* -------------- S3GE Splashscreen & Credits (Required by EUA) --------------*/
	
	int splashscreenID = dbImageResource->Pop();
	Core->Image->Create(splashscreenID, S3GE_IMAGE_TYPE_STATIC, Core->ConfigPropertyGet("SplashScreenImage"), /*S3GE::File::GET_FROM_LOCAL|*/S3GE::File::GET_FROM_NETWORK);//"Content/2D/splash.png"
	DarkLUA::System::IntegerSet("splashscreenID",splashscreenID);
	DarkLUA::Task *splashtask = new DarkLUA::Task("splashscript", "Content/Data/Logic/splashscript.lua");
	splashtask->Schedule(DarkLUA::Task::ONCE,DarkLUA::Task::AUTOMATIC,256);
	splashtask->Run();

	dbAutoCamOff();

	/* ------------------- Engine Startup -----------------*/

	Output = "S3GE Dev Demo Build. ";
	Scenergy::System::Load(Core->ConfigPropertyGet("MAUIMainFile"),false,0);

	/* ------------------- Test Setup -----------------*/

	//DarkNet I2P Testing
	DarkNet::I2P *testnetworkentity = NULL;
	testnetworkentity = DarkNet::I2P::Create(DARKNET_I2P_ROLE_SERVER, "Test Server",(char*)Core->ConfigPropertyGet("GameServerHostname").data(),(unsigned short)dbVal((char*)Core->ConfigPropertyGet("GameServerPort").data()),NetMode::UDP_PER_CLIENT_PER_OPERATION,32);
	if(!testnetworkentity) testnetworkentity = DarkNet::I2P::Create(DARKNET_I2P_ROLE_CLIENT, "Test Client",(char*)Core->ConfigPropertyGet("GameServerHostname").data(),(unsigned short)dbVal((char*)Core->ConfigPropertyGet("GameServerPort").data()),NetMode::UDP_PER_CLIENT_PER_OPERATION,0);

	//QuantumPath Testing
	/*
	QuantumPath::Geometry *testgeometry = NULL;
	testgeometry = QuantumPath::Geometry::Create(QUANTUMPATH_GEOMETRY_TYPE_DEFAULT);
	testgeometry->Load("Content/3D/dungeon.obj");
	testgeometry->Build();
	dbSetObject(testgeometry->dbObjectID,0,0,0);
	*/

UPDATE:

	while (LoopGDK()){

		DarkLUA::System::Update();
		DarkNet::System::Update();
		Core->Physics->Update();
		MAUI::System::Update();
		Illudium::System::Update();
		Scenergy::System::Update();
		Core->Update();

		dbSync();
	}

STOP:

	//if(testgeometry != NULL) QuantumPath::Geometry::Destroy(testgeometry);
	//delete quark 
	if(testnetworkentity) delete testnetworkentity;

	Scenergy::System::Stop();
	QuantumPath::System::Stop();
	Illudium::System::Stop();
	MAUI::System::Stop();
	oawRelease();
	Core->Stop();
	DarkNet::System::Stop();
	DarkLUA::System::Stop();

	//goto START;
	return;
}