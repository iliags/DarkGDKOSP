// This example will show you how to set up a vehicle, it will also show you 
// a few ways you can make the vehicle more stable. There is lots more you can
// do to get any desired effect when it comes to handling, there is alot of 
// information on the web, it does not matter what physics engine you are using
// the principles are mostly the same.


#include "..\..\..\..\Include\DarkGDK\DarkGDK.h"
#include "..\..\..\..\Include\Fulcrum\FulcrumPhy.h"

void floatingCam(int objectID, float speed, float height);
void setupCar();
void resetCar();
void applyForces();
int levelID = 1;
int carID = 2;

FulcrumPhy myPhysics;

void DarkGDK ( void )
{
	myPhysics.start(true);
	myPhysics.setGravity(0, -9.8, 0);

	dbSyncOn   ( );
	dbSyncRate ( 60 );

	dbLoadObject("../../Media/TestLevel/TestMap.dbo", levelID);
	dbScaleObject(levelID, 15, 15, 15);
	myPhysics.makeTriangleMeshFromDBO(levelID);

	setupCar();

	myPhysics.simulate();
	while ( LoopGDK ( ) )
	{
		myPhysics.getPhysicsResults();

        if(dbSpaceKey()) resetCar();
		dbText(0, 0, "Use arrow keys to control vehicle, space key to reset");
		dbText(0, 15, "FPS: ");
		dbText(100, 15, dbStr(dbScreenFPS()));
		dbText(0, 30, "Polys: ");
		dbText(100, 30, dbStr(dbStatistic(1)));
		// Apply power to, and turn the wheels
		applyForces();
		myPhysics.update();
		floatingCam(carID, 0.01f, 5.0f); 
		myPhysics.simulate();
		dbSync ( );
	}

	return;
}



void setupCar()
{
	// Load car model
    dbLoadObject("../../Media/F1 Car/H-F1 Car-Move.x", carID);

	// Creating the car hull shape(s) works just like making a compound actor, we need the car 
	// object at position (0, 0, 0) for this to work. What we do is make primitive objects(boxes, 
	// spheres etc). We then size, rotate and position them so they are a good representation of the
	// car object.

	//BOX
	dbMakeObjectBox(100, dbObjectSizeX(carID), dbObjectSizeY(carID) - 0.2, dbObjectSizeZ(carID) / 3);
    dbPositionObject(100,  0, dbObjectSizeY(carID) / 2, 2);
    dbHideObject(100);
	
	//BOX
	dbMakeObjectBox(102, dbObjectSizeX(carID), dbObjectSizeY(carID)/ 4, dbObjectSizeZ(carID) / 8);
    dbPositionObject(102,  0, dbObjectSizeY(carID) / 2 - 0.5, -2.2);
    dbHideObject(102);
    
	//SPHERE(scaled)
	dbMakeObjectSphere(101, dbObjectSizeX(carID), 10, 10);
	dbScaleObject(101, 100, 40, 250);
	dbPositionObject(101,  0, dbObjectSizeY(carID) / 2, 0);
    dbHideObject(101);

	// Now we have a good representation of the car for the physics simulation. The more shapes we
	// create, the more realistic the car will act at the cost of cpu.
	// The next three commands will create the shapes and add them to the shape list.
	myPhysics.makeConvexShape(101); //hull
	myPhysics.makeBoxShape(100);    //
    myPhysics.makeBoxShape(102);    //

    // We now initialise our vehicle, this will grab(and delete) our shapes from the shape
	// list and create our vehicle, all we need do next is add some wheels.
    myPhysics.makeVehicle(carID);
	
	// First you need to find what the limb number is for each wheel, there are many ways of 
	// doing this, you could create a function that hides all the limbs and then just 
	// shows one at a time with the limb ID number displayed. You can use commands:
	// dbHideLimb(), dbShowLimb().
	// Once we know the limb ID's we give each wheel an ID in relation to that vehicle,
	// this is the ID number we us to access the wheels later.
	float radius = 0.5;
	myPhysics.makeWheelShape(carID, 2, 1, radius); 
	myPhysics.makeWheelShape(carID, 3, 2, radius);
	myPhysics.makeWheelShape(carID, 4, 3, radius); 
	myPhysics.makeWheelShape(carID, 6, 4, radius);
  
	// Now we have added some wheels we make our vehicle.
	myPhysics.buildVehicle(carID);



	// ADVANCED SETTINGS
    // Setting up the vehicle is just the start, there are an almost unlimited amount of 
	// ways to get your vehicle to handle the way you would like. I will show some of 
	// the methods for making your vehicle more stable.

	// We make a material for the wheels, we dont want much bounciness, but we do
	// want lots of grip(friction).
	myPhysics.makeMaterial(1, 0.01f, 1.0f, 1.0f);

	// We set each wheel to the above material
	myPhysics.setMaterial(carID, 1, 1);
    myPhysics.setMaterial(carID, 2, 1);
	myPhysics.setMaterial(carID, 3, 1);
    myPhysics.setMaterial(carID, 4, 1);

	// Linear damping will simulate air resistance
	myPhysics.setLinearDamping(carID, 0.1);
	// Since we have a large shape at the back, the center of mass for the actor/object
	// as a whole will be higher up and further back than we want it, making the car tip
	// over very easily. Changing(lowering) the centre of mass is the easiest way to stop
	// your vehicle from tipping over. If you lower it enough it will not tip over at all 
	// but you may get strange results in certain situations, its a good idea to try to 
	// keep the centre of mass within the frame of the vehicle.
	myPhysics.setCMassLocalPosition(carID, 0.0f, 0.0f, 0.0f);	
}


void applyForces()
{
	// Declare some variables
	static float wheelAngle = 0;
	static float maxAngle = 30;
	static float wheelReturnSpeed = 1.5;
	static float wheelTorque = 0;
	static float power = 550; 
    static float downForce = -1000;

	// Limit wheel angle
    if (wheelAngle > maxAngle) 
		wheelAngle = maxAngle;
    if (wheelAngle < -maxAngle) 
		wheelAngle = -maxAngle;

    // KEYS
	// Power
	if (dbUpKey())    
		wheelTorque = -power;
	else if (dbDownKey()) 
		wheelTorque = power;
	else wheelTorque = 0;
    // Turn
	if (dbLeftKey())    
		wheelAngle -= 1.5;
	else if (dbRightKey()) 
		wheelAngle += 1.5;
    else if (wheelAngle > 0) 
		wheelAngle -= wheelReturnSpeed;
    else if (wheelAngle < 0) 
		wheelAngle += wheelReturnSpeed;
	    
	// We shall turn the front wheels only and add power to the rear wheels only.
	myPhysics.driveWheel(carID, 1, wheelTorque);
	myPhysics.driveWheel(carID, 2, wheelTorque);
	myPhysics.steerWheel(carID, 3, wheelAngle);
	myPhysics.steerWheel(carID, 4, wheelAngle);

	// DownForce
	// Adding downforce is a good way to increase vehicle grip, in a more realistic
	// simulation you might want to increase downforce in relation to the velocity
	// of the vehicle.
	myPhysics.applyForce(carID, 0, downForce, 0);
}


void resetCar()
{
	myPhysics.setPosition(carID, 0, 0, 0);
	myPhysics.setOrientation(carID, 0, 0, 0);
	myPhysics.setLinearVelocity(carID, 0, 0, 0);
	myPhysics.setAngularVelocity(carID, 0, 0, 0);
}


void floatingCam(int objectID, float speed, float height)
{
	float distance = dbSqrt(
		              ((dbObjectPositionX(objectID) - dbCameraPositionX()) 
					    *
						 (dbObjectPositionX(objectID) - dbCameraPositionX())) 
						   + 
		                    ((dbObjectPositionZ(objectID) - dbCameraPositionZ()) 
					           *
						        (dbObjectPositionZ(objectID) - dbCameraPositionZ())));

	dbPointCamera(dbObjectPositionX(objectID), dbObjectPositionY(objectID), dbObjectPositionZ(objectID));
    dbMoveCamera(speed * (distance * 1.5));
	dbPositionCamera(dbCameraPositionX(), dbObjectPositionY(objectID) + height, dbCameraPositionZ());
}