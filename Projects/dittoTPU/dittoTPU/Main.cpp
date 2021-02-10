/*
    __   __   __     __
.--|  | |__| |  |_  |  |_  .-----.
|  _  | |  | |   _| |   _| |  _  |
|_____| |__| |____| |____| |_____|

			  Text Processing Unit for DGDK by frankie taylor 2009 ©
*/

#include "..\..\..\Include\DarkGDK\DarkGDK.h"
#include "dittoTPU.h"

void DarkGDK ( void )
{
START:
	//! Initialize
	dbSyncOn();
	dbSyncRate(60);

	dbSetDisplayMode(800,600,32);
	dbSetWindowOn();

	dittoTPU::start();

	dittoTPU::build("");

UPDATE:

	//! Primary Update Loop
	while (LoopGDK()){

		dittoTPU::update();

		//! Primary Sync
		dbSync();
	}

STOP:
	//! Terminate
	dittoTPU::stop();
	return;
}