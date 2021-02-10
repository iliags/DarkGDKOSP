
// Dark GDK - The Game Creators - www.thegamecreators.com

// the wizard has created a very simple project that uses Dark GDK
// it contains the basic code for a GDK application

// whenever using Dark GDK you must ensure you include the header file
#include "..\..\Include\DarkGDK\DarkGDK.h"
#include "..\..\Include\DirectX9\dx9Image.h"
// the main entry point for the application is this function
void DarkGDK ( void )
{
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );

	dbSync();
	dbText(1,1,"Please Wait while loading a 1.7 mb image");
	dbSync();
	dbSync();
	dbLoadImage("1024x1024.jpg",1); // the Source Image
	
	// Destination Image , created by a Bitmap.
	dbCreateBitmap(1,1024,1024);
	//dbSetBitmapFormat(20);
	dbSetCurrentBitmap(1);
	dbCLS(dbRGB(255,0,0));
	dbText(1,1,"Testing DirectX Native");
	dbGetImage(2,0,0,1024,1024);
	dbSetCurrentBitmap(0);
	dbDeleteBitmap(1);
	// End of Destination Image


	int Timer = 0;
	int SaveTimer = dbTimer();
	bool TestDirectX = true;

	int Dtimes = 0;
	// our main loop
	bool Locked = true; // a simple Boolean to show us if the Surface is locked.
	bool Finished = false; // True when Copying is complete.
	// our main loop

	dbCLS();
	dbSync();
	dbText(0,0,"Please Wait while Copying the Image 10 times 1024x1024 resolution , Vsync is off.");
	dbSync();
	DWORD Color = 0;

		dbMakeObjectPlain(1,100,100);
	dbTextureObject(1,1);
	dbPositionObject(1,-50,0,0);

	dbMakeObjectPlain(2,100,100);
	dbTextureObject(2,2);
	dbPositionObject(2,+50,0,0);

	//dxI[0].dx9LockSurface(1); // First we lock the Surface same as in dbLockPixel(), the variable SurfaceID represents the ImageId loaded in Dgdk.
	//dxI[1].dx9LockSurface(2); // First we lock the Surface same as in dbLockPixel(), the variable SurfaceID represents the ImageId loaded in Dgdk.
	
	dx9Image dxI(1),dxi(2);
				//Color =  dxI[0].dx9GetImagePixel(x,y); // Getting a RGBA value of the current random pixel x and y.
				//dxI[1].dx9PutImagePixel(x,y,Color);   // Plantting a RGBA value on the current random pixel x and y.
	D3DXLoadSurfaceFromSurface(dxI.DestSurface,NULL,NULL,dxi.DestSurface,NULL,NULL,D3DX_FILTER_NONE,0);
				//if (dbTimer() - SaveTimer > 999) // if its bigger then 999 then one second has passed.
				//{
				//	Timer++; // increasing by seconds.
				//	SaveTimer = dbTimer(); // saving for later use.
				//}
	//dxI[0].dx9UnlockSurface(1); // Unlocking the Surface or Dgdk dbImage , a Must!
	//dxI[1].dx9UnlockSurface(2); // Unlocking the Surface or Dgdk dbImage , a Must!

	while ( LoopGDK ( ) )
	{
			// update the screen
			dbSync ( );
			dbText(1,1,"The Time it Took to copy a 1024x1024 image 10 times to another is:");
			dbText(1,15,dbStr(Timer));
	}

	// return back to windows
	return;
}