#include "..\..\..\..\Include\DarkGDK\DarkGDK.h"
#include "..\..\..\..\Include\Fulcrum\FulcrumPhy.h"


void checkCollisions();
int groundID = 1;
int sphere1ID = 2;
int sphere2ID = 3;

FulcrumPhy myPhysics;


void DarkGDK ( void )
{
	myPhysics.start();
	myPhysics.setGravity(0, -9.8, 0);

	dbSyncOn   ( );
	dbSyncRate ( 30 );
    dbAutoCamOff();
	dbPositionCamera(0, 10, -40);

	// Make Objects
    dbMakeObjectBox(groundID, 100, 10, 100);
	dbColorObject(groundID, dbRGB(dbRND(255), dbRND(255), dbRND(150)));
	dbMakeObjectSphere(sphere1ID, 5, 20, 20);
	dbColorObject(sphere1ID, dbRGB(dbRND(255), dbRND(150), dbRND(255)));
	dbPositionObject(sphere1ID, 0, 30, 0);
	dbMakeObjectSphere(sphere2ID, 5, 20, 20);
	dbColorObject(sphere2ID, dbRGB(dbRND(150), dbRND(255), dbRND(255)));
	dbPositionObject(sphere2ID, 10, 35, 0);
    // Make Actors
	myPhysics.makeBox(groundID);
	myPhysics.makeSphere(sphere1ID, true);
    myPhysics.makeSphere(sphere2ID, true);

	// Any two actors/objects we want to check collisions for must be
	// set as contact pairs
	myPhysics.setContactPair(groundID, sphere1ID);
	myPhysics.setContactPair(groundID, sphere2ID);

	myPhysics.simulate();

	while ( LoopGDK ( ) )
	{
		myPhysics.getPhysicsResults();

		//Check for collisions and deal with them
		checkCollisions();

		// move the camera
		if ( dbUpKey ( ) )
			dbMoveCamera ( 1 );
		if ( dbDownKey ( ) )
			dbMoveCamera ( -1 );

		myPhysics.update();
		myPhysics.simulate();
		dbSync ( );
	}

	return;
}

void checkCollisions()
{
	// All recorded collisions go onto a stack, when FulcrumPhy::getContactData() is called
	// the last collision is retrieved and removed from the stack. This is why we keep
	// calling for collisions in a 'while' loop until there are no collisions left, we
	// can then be sure we have cleared the stack and dealt with all collisions for this
	// frame.
	while(myPhysics.getContactData())
	{
        dbText(0, 0, "CONTACT....");
		// When FulcrumPhy::getContactData has been called, you can access which
		// two objects/actors were involved in the contact with the following functions
		int actorA = myPhysics.getContactActorA();
		int actorB = myPhysics.getContactActorB();

		// Now we have the two objects/actors we can deal with them as we wish
        if (actorA == groundID || actorB == groundID)   //something hits the ground
		{
            if(actorA == sphere1ID || actorB == sphere1ID)
			{
                dbText(0, 15, "SPHERE 1 HITS THE GROUND");
			}
            if(actorA == sphere2ID || actorB == sphere2ID)
			{
                dbText(0, 35, "SPHERE 2 HITS THE GROUND");
			}
		}
	}
}