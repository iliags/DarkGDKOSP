// In this example we will look at getting your character walking around a level
// using a character controller, this is a special kind of kinematic dynamic actor.
// Because it is kinematic it is not affected by forces, it is designed to give you
// direct control over your characters. There are two types of controller, capsule
// and box, both have slightly different characteristics but basically do the same
// thing.

#include "..\..\..\..\Include\DarkGDK\DarkGDK.h"
#include "..\..\..\..\Include\Fulcrum\FulcrumPhy.h"

void controlCharacter(int objectID, float turnSpeed, float walkSpeed, float gravity);
void updateAnimation(int objectID, int firstFrame, int lastFrame);
void updateCamera(int objectID, float distance, float height, float smooth);

FulcrumPhy myPhysics;

void DarkGDK ( void )
{
    myPhysics.start(true);

	dbSyncOn   ( );
	dbSyncRate ( 60 );

	dbRandomize ( dbTimer ( ) );

    dbLoadObject("..//Media//Babe//H-Babe-Move.x", 1);
	dbLoadObject("..//Media//TestLevel//TestMap.dbo", 2);
    dbScaleObject(2, 10, 10, 10);

	myPhysics.makeTriangleMeshFromDBO(2);


	// Here, I will show how to make both types of controllers, for each type there are
	// two overloads for the respective 'make' functon, one tries to set up your character
	// size and offset along the y-axis automatically while the other gives you a little
	// more control. The box controller below uses the first way while the capsule controller
	// uses the second.

	myPhysics.makeControllerCapsule(1, 0.1, 45, dbObjectSizeX(1), dbObjectSizeY(1));
	//myPhysics.makeControllerBox(1, 0.2, 45, true);
	myPhysics.positionCharacterController(1, 0, 5, 0);
	myPhysics.setControllerLocalPositionY(1, -1.05);   //Not needed for box controller here


	myPhysics.simulate();
	while ( LoopGDK ( ) )
	{
		myPhysics.getPhysicsResults();
		controlCharacter(1, 1.0f, 0.1f, -0.3f);
		updateAnimation(1, 4, 26);
		myPhysics.update();
        updateCamera(1, 4, 2, 10);
		myPhysics.simulate();
		dbSync ( );
	}

    myPhysics.stop();
	return;
}

void controlCharacter(int id, float turnSpeed, float walkSpeed, float gravity)
{
     if(dbLeftKey())
		 dbRotateObject(id, 0, dbObjectAngleY(id) - turnSpeed, 0);
     if(dbRightKey())
		 dbRotateObject(id, 0, dbObjectAngleY(id) + turnSpeed, 0);

     if(dbUpKey())
		 walkSpeed = -walkSpeed;
     else if(dbDownKey())
		 walkSpeed = walkSpeed;
	 else
		 walkSpeed = 0.0f;

     myPhysics.moveCharacterController(id, walkSpeed, gravity);
}

void updateCamera(int id, float distance, float height, float smooth)
{
     dbSetCameraToFollow(dbObjectPositionX(id),          //PositionX
			              dbObjectPositionY(id),         //PositionY
				           dbObjectPositionZ(id),        //PositionZ
							dbObjectAngleY(id) + 180,    //Angle
							 distance,                   //Distance
						      height,                    //Height
							   smooth,                   //Smooth
								0);                      //Collision
     dbRotateCamera(0, dbObjectAngleY(id) + 180, 0);
}

void updateAnimation(int id, int firstFrame, int lastFrame)
{
    if(dbUpKey())
	   dbSetObjectFrame(id, dbObjectFrame(id) + 1);
    if(dbDownKey())
	   dbSetObjectFrame(id, dbObjectFrame(id) - 1);

	if(dbObjectFrame(id) > lastFrame)
		dbSetObjectFrame(id, firstFrame);
	if(dbObjectFrame(id) < firstFrame)
		dbSetObjectFrame(id, lastFrame);
}