// In his example we will demonstrate the FulcrumPhy::raycast() command.
// We will setup a player with a character controller and a ball which
// will be a dynamic actor. We will then simulate the player kicking the ball
// by casting a ray from the player and applying force to the ball if
// the ball is close enough, the force will be applied in the same direction
// the ray is cast.
// You may find raycasts very useful when using character controllers as they are
// a little limited when it comes contacts reports(see 'Contacts' example).


#include "..\..\..\..\Include\DarkGDK\DarkGDK.h"
#include "..\..\..\..\Include\Fulcrum\FulcrumPhy.h"


FulcrumPhy myPhysics;

void raycast();
void controlCharacter(int objectID, float turnSpeed, float walkSpeed, float gravity);
void updateAnimation(int objectID, int firstFrame, int lastFrame);
void updateCamera(int objectID, float distance, float height, float smooth);
int playerID = 1;
int levelID = 2;
int ballID = 3;

void DarkGDK ( void )
{
	myPhysics.start(true);
	myPhysics.setGravity(0, -9.8, 0);

	dbSyncOn   ( );
	dbSyncRate ( 60 );
	dbRandomize ( dbTimer ( ) );

	// LEVEL
	dbLoadObject("..//Media//TestLevel//TestMap.dbo", levelID);
    dbScaleObject(levelID, 10, 10, 10);
	myPhysics.makeTriangleMeshFromDBO(levelID);

	// BALL
	dbMakeObjectSphere(ballID, 1);
	dbColorObject(ballID, dbRGB(dbRND(255), dbRND(255), dbRND(255)));
	dbPositionObject(ballID, 0, 5, -5);
	myPhysics.makeSphere(ballID, true);
	// We apply linear and angular damping on the ball so that it does
	// not travel or spin forever when left untouched
	myPhysics.setLinearDamping(ballID, 0.5);
	myPhysics.setAngularDamping(ballID, 0.5);


    // PLAYER
	dbLoadObject("../Media/Babe/H-Babe-Move.x", playerID);
	myPhysics.makeControllerBox(playerID, 0.1, 45, true);

	myPhysics.simulate();

	while ( LoopGDK ( ) )
	{
		dbText(200, 0, "**Press space for power shot**");
		myPhysics.getPhysicsResults();
		controlCharacter(playerID, 2.0f, 0.1f, -0.3f);
		// Here is where we will test to see if the ball is
		// near to the players feet, and kick if it is
		raycast();
		updateAnimation(playerID, 4, 26);
		myPhysics.simulate();
		myPhysics.update();
        updateCamera(playerID, 4, 2, 10);
		dbSync ( );
	}

	// This next function releases all your actors and returns any memory it was using.
	myPhysics.stop();

	return;
}

void raycast()
{
	// Setup power for possible shot
	float power = 250;
	if(dbSpaceKey())
	{
		dbText(270, 250, "POWER SHOT!!!");
		power = 5000;
	}

	// Get the direction the player is currently facing as components of
	// the x-axis and z-axis and set them as the direction we will cast our
	// ray in.
    float rayDirectionX = dbSin(dbObjectAngleY(playerID) + 180);
	float rayDirectionZ = dbCos(dbObjectAngleY(playerID) + 180);
	// We dont want the ray to go in an upward or downward direction
    float rayDirectionY = 0;

	// Cast our ray from the players current position in the direction
	// the player is facing. If it hits anything, the ID number of the
	// object/actor hit will be stored in the 'rayHit' variable
	int rayHit = myPhysics.raycast(dbObjectPositionX(playerID),
		                            dbObjectPositionY(playerID) + 0.2,
									 dbObjectPositionZ(playerID),
									  rayDirectionX,
									   rayDirectionY,
									    rayDirectionZ);
	// Get the distance the ray travelled
	float distance = myPhysics.getRayDistance();

	// Test to see if ray hit ball
    if(rayHit == ballID)
	{
	    dbText(0, 0, "RACAST HIT...");
		// Only 'kick' if the ball is close enough
		if (distance < 1)
		{   dbText(100, 0, "KICK!!!");
			myPhysics.applyForce(ballID, rayDirectionX * power, power, rayDirectionZ * power);
		}
	}
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