// Welcome to the Fulcrum Physics examples, we will start with the DarkGDK 3D wizard
// sample code, this is usually the first thing you see when getting started with DarkGDK.
// The difference with the Fulcrum Physics version is that the floating spheroids are now
// going to be given physical properties, they will now act like real objects with mass.
// The main purpose of this example is to show you the basics of using fulcrum physics and
// the recommended order in which things should be done.


#include "..\..\..\..\Include\DarkGDK\DarkGDK.h"
#include "..\..\..\..\Include\Fulcrum\FulcrumPhy.h"         // Always needed when using Fulcrum Physics

// Here we declare our physics module, we will do it here so it is global,
// meaning any functions we create will have access to it.
FulcrumPhy myPhysics;      // You can call this anything you like (fp, PHY, myPhysics etc)


void DarkGDK ( void )
{
	// The first thing you must do it call the FulcrumPhy::start() function,
	// this initialises Fulcrum Physics for us and creates a physics scene.
	myPhysics.start();
    // For most applications you will need to add gravity to the scene.
	myPhysics.setGravity(0, -9.8, 0);
	// We will add a ground plane so our objects don't fall indefinitely.
	myPhysics.makeGroundPlane();

	dbSyncOn   ( );
	dbSyncRate ( 60 );
	dbRandomize ( dbTimer ( ) );

	// make some 3D objects
	for ( int i = 1; i < 50; i++ )
	{
		dbMakeObjectSphere ( i, 1 );
		dbPositionObject ( i, dbRnd ( 20 ), dbRnd ( 20 ), dbRnd ( 20 ) );
		dbScaleObject ( i, 100 + dbRnd ( 400 ), 100 + dbRnd ( 400 ), 100 + dbRnd ( 400 ) );
		dbColorObject ( i, dbRgb ( dbRnd ( 255 ), dbRnd ( 255 ), dbRnd ( 255 ) ) );
		dbSetObjectSpecularPower ( i, 255 );
		dbSetObjectAmbient ( i, 0 );

		// For each spheroid we will create a dynamic actor which will then take over
		// the object and give it life like properties.
		// If the objects were spheres we would use FulcrumPhy::makeSphere(), but as they
		// are spheroids FulcrumPhy::makeConvexMesh() is the better option.
		myPhysics.makeConvexMesh(i, true);                // We set to true to make the actor dynamic.
	}

	dbPositionCamera ( 10, 10, -20 );

    // Now all our objects and their corresponding actors are set up we can tell Fulcrum Physics
    // to simulate the physics scene on another thread, the call to FulcrumPhy::simulate() does this for us.
	// Each call to FulcrumPhyics::simulate() should have a call to FulcrumPhy::getPhysicsResults()
	// to retrieve the results of the simulation for that particular time-step.
	myPhysics.simulate();

	while ( LoopGDK ( ) )
	{
        // The first thing we do in our loop is make a call to FulcrumPhy::getPhysicsResults(),
		// this will stop the simulation and we will be ready to update our objects so that their
		// positions and orientations match their correspinding actors positions and orientations,
		// we will do this with the FulcrumPhy::update() function.
		myPhysics.getPhysicsResults();

        // This section of the loop, between FulcrumPhy::getPhysicsResults() and FulcrumPhy::simulate()
		// is where we will apply any forces to our actors. Its also the best place to create new actors
		// or release existing actors from the scene.
		// In the original demo we would rotate our objects using dbRotateObject(), now that our objects
		// are controlled by dynamic actors, we manipulate them by applying forces to the actors, you
		// may want to try this with and without gravity.

		// for ( int i = 1; i < 50; i++ )
		//  	myPhysics.applyTorque(i, 0, 500, 0);


		// This call to FulcrumPhy::simulate() will start the simulation so it is ready for the next call to
		// FulcrumPhy::getPhysicsResults() at the start of the next loop.
		myPhysics.simulate();

		// This next function positions and orientates all our objects so they match their corresponding actors
		// positions and orientations, this is positioning all our objects from the last
		// call to FulcrumPhy::getPhyicsResults while the physics simulates for the next frame.
		myPhysics.update();

		dbText ( 0, 0, "Use the up and down arrow keys to move the camera" );
		if ( dbUpKey ( ) )
			dbMoveCamera ( 1 );
		if ( dbDownKey ( ) )
			dbMoveCamera ( -1 );

		dbSync ( );
	}

	// This next function releases all your actors and returns any memory it was using.
	myPhysics.stop();

	for ( int i = 1; i < 50; i++ )
		dbDeleteObject ( i );

	return;
}