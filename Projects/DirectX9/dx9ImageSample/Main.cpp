////////////////////////
/*


BenchMarking Hardware Capabilities
Pixel Manipulation.

What is the Score? and how does it Increase?
The Benchmark will draw an Image to another Image Pixel by Pixel in Real Time 
The new Image will be Textured on a 3D Plain Object.

The Score , is the Number of Times it takes for the Hardware
to Plent Pixels from a Loaded(Cached) Image.


Nadav "Haliop" Rosenberg
Gforce9600 GT - Last known Score : 



Do not forget that hardware capabilites should be better if you wont use DarkGDK system.
////


*/
//////////////////////////


#include "..\..\..\Include\DarkGDK\DarkGDK.h"
#include "..\..\..\Include\DirectX9\dx9Image.h"
#include "..\..\..\Include\S3GE\GdkSystem.h"
#include <string>
#include "d3d9.h"

using namespace std;
LPDIRECT3DDEVICE9 DGDKdevice;
string output;

#define OP_MAX 11
#define BOXBLIT_SIZE 64
#define RTSURFACE_MAX 1024

// the main entry point for the application is this function
void DarkGDK ( void )
{
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn();
	dbSyncRate(0);
	dbSync();

	dbSetDisplayMode(800,600,32);
	//dbSetWindowOff();

	dbRandomize(dbTimer());

	//Render-Target Testing by Techlord Part 2
	//DGDK Device
	DGDKdevice = dbGetDirect3DDevice();
	LPDIRECT3DSURFACE9 g_pGlob_pHoldBackBufferPtr; //mimic DSDK Source `g_pGlob->pHoldBackBufferPtr`
	LPDIRECT3DSURFACE9 g_pGlob_pHoldDepthBufferPtr; //mimic DSDK Source `g_pGlob->pHoldDepthBufferPtr`
	DGDKdevice->GetRenderTarget(0,&g_pGlob_pHoldBackBufferPtr); 
	DGDKdevice->GetDepthStencilSurface(&g_pGlob_pHoldDepthBufferPtr);

	D3DSURFACE_DESC backbufferdesc;
	g_pGlob_pHoldBackBufferPtr->GetDesc(&backbufferdesc );
	D3DFORMAT CommonSurfaceFormat = backbufferdesc.Format;

	//create dbImage as a render target
	LPDIRECT3DSURFACE9 myImageSurface;
	LPDIRECT3DSURFACE9 myDepthStencilSurface;
	//dbMakeImageUsage(1, IMAGECACHE_WIDTH_MAX, IMAGECACHE_HEIGHT_MAX, 0); Managed Texture
	//dbMakeImageUsage(1, IMAGECACHE_WIDTH_MAX, IMAGECACHE_HEIGHT_MAX, D3DUSAGE_RENDERTARGET)->GetSurfaceLevel(0, &myImageSurface); //D3DUSAGE_DYNAMIC
	dbMakeImageRenderTarget(1, IMAGECACHE_WIDTH_MAX, IMAGECACHE_HEIGHT_MAX, D3DFMT_A8R8G8B8)->GetSurfaceLevel(0, &myImageSurface); //D3DFMT_A1R5G5B5(Depth = 16), D3DFMT_A8R8G8B8(Depth = 32);
	//load a image to surface
	D3DXLoadSurfaceFromFile(myImageSurface, NULL, NULL, "Media\\race.png", NULL, D3DX_DEFAULT, 0, NULL);
	//get surface description
	D3DSURFACE_DESC myImageSurfaceDesc;
	myImageSurface->GetDesc(&myImageSurfaceDesc);
	//create depth stencil surface
	//CreateDepthStencilSurface(IMAGECACHE_WIDTH_MAX, IMAGECACHE_HEIGHT_MAX, GetValidStencilBufferFormat(CommonFormat), D3DMULTISAMPLE_NONE, 0, TRUE, &myDepthStencilSurface, NULL );

	//dx9Image dxI(1); // dxImage class.

	//create test dynamic surface
	LPDIRECT3DSURFACE9 TestDynamicSurface;
	dbMakeImageRenderTarget(2, IMAGECACHE_WIDTH_MAX, IMAGECACHE_HEIGHT_MAX, D3DFMT_A8R8G8B8)->GetSurfaceLevel(0, &TestDynamicSurface); //D3DFMT_A1R5G5B5(Depth = 16), D3DFMT_A8R8G8B8(Depth = 32);
	D3DXLoadSurfaceFromFile(TestDynamicSurface, NULL, NULL, "Media\\1024x1024.jpg", NULL, D3DX_DEFAULT, 0, NULL);
	D3DSURFACE_DESC TestDynamicSurfaceDesc;
	TestDynamicSurface->GetDesc(&TestDynamicSurfaceDesc);

	//new dynamic surface array for testing
	LPDIRECT3DSURFACE9 NewDynamicSurface[RTSURFACE_MAX];
	D3DSURFACE_DESC NewDynamicSurfaceDesc[RTSURFACE_MAX];
	int newimagecount = -1;

	dbLoadImage("Media\\funbits.png",3);
	dbLoadImage("Media\\pumpkin.jpg",4);
	dbLoadImage("Media\\TheOldFarm.jpg",5);
	dbLoadImage("Media\\turbalance.jpg",6);
	dbLoadImage("Media\\sign.jpg",7);

	dbMakeObjectCube(1,1);
	dbTextureObject(1,1);

	int imagecount = 7;
	int times = 0;
	int saved = dbTimer();
	
	char *Op[OP_MAX] = {
		"Direct Box Fill", 
		"Render-Target Box Blit",
		"Render-Target dbPasteImage",
		"Render-Target dbText",
		"Render-Target dbLine",
		"Render-Target dbBox",
		"Render-Target dbDot",
		"CopyRect Dynamic-Dynamic",
		"CreateRect From Dynamic",
		"CopyRect From Static(WIP)",
		"CreateRect From Static(WIP)"
	};
	

	int opchanger = 0;
	int lastRandomImage = 0;
	int temprandomImage = 0;

	//main loop
	while ( LoopGDK ( ) )
	{

		// Controls
		if (dbScanCode())
		{
			if (ActionTimer(dbTimer(),saved,200))
			{
				if (dbUpKey())
				{
					if (opchanger < OP_MAX) opchanger++;
				}
				if (dbDownKey())
				{
					if (opchanger > 0) opchanger--;
				}
			}
		}

		if(dbSpaceKey()){		
			switch (opchanger)
			{
				case 0://"Direct Box Fill"
					if(dbSpaceKey()){	
						RECT rect = { 0, 0, IMAGECACHE_WIDTH_MAX,IMAGECACHE_HEIGHT_MAX };
						DGDKdevice->ColorFill(myImageSurface, &rect, dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)) );
					}
					break;

				case 1://"Render-Target Box Blit"
					{
					DGDKdevice->SetRenderTarget(0, myImageSurface);
					//DGDKdevice->SetDepthStencilSurface(0,myDepthStencilSurface);
					//D3DRECT	rect = { 0, 0, IMAGECACHE_WIDTH_MAX, IMAGECACHE_HEIGHT_MAX };

					//random start and size
					int width = BOXBLIT_SIZE;
					int height = BOXBLIT_SIZE;
					int left = dbRnd(myImageSurfaceDesc.Width-(width+1));
					int top = dbRnd(myImageSurfaceDesc.Height-(height+1));
					int right = left + width;
					int bottom = top + height;
					D3DRECT	rect = {left , top, right, bottom};
						
					DGDKdevice->Clear ( 1, &rect, D3DCLEAR_TARGET, dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)), 0.0f, 0 );

					//reset to default
					DGDKdevice->SetRenderTarget(0,g_pGlob_pHoldBackBufferPtr); 
					//DGDKdevice->SetDepthStencilSurface(g_pGlob_pHoldDepthBufferPtr);
					}
					break;

				case 2://"Render-Target dbPasteImage"
				case 3://"Render-Target dbText"
				case 4://"Render-Target dbLine"
				case 5://"Render-Target dbBox"
					{
					DGDKdevice->SetRenderTarget(0,myImageSurface);
				
					switch(opchanger){

						case 2:
							//default bitmap size clipping problem 
							temprandomImage = dbRnd(6)+1;
							lastRandomImage = temprandomImage;
							dbPasteImage(temprandomImage, 0, 0); 
							break;
						
						case 3:
							//replacing dbtext with dxText
							dbText( dbRnd(IMAGECACHE_WIDTH_MAX), dbRnd(IMAGECACHE_HEIGHT_MAX), "Render-Target Paste Image"); //works
							break;

						case 4:
							//custom line drawing function
							dbLine( 0, 0, dbRnd(IMAGECACHE_WIDTH_MAX), dbRnd(IMAGECACHE_WIDTH_MAX) ); //does not work
							break;

						case 5:
							//custom box drawing function?
							dbBox( 0,0, dbRnd(IMAGECACHE_WIDTH_MAX), dbRnd(IMAGECACHE_HEIGHT_MAX), dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)),  dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)),  dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)),  dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)) ); //works
							break;

						case 6:
							//custom dot drawing function?
							dbDot(dbRnd(IMAGECACHE_WIDTH_MAX), dbRnd(IMAGECACHE_HEIGHT_MAX)); //works
							break;

					}

					//reset to default
					DGDKdevice->SetRenderTarget(0,g_pGlob_pHoldBackBufferPtr); 
					}
					break;

				case 7://"CopyRect Dynamic-Dynamic(WIP)"
					{
					//use stretchrect
					int width = dbRnd(TestDynamicSurfaceDesc.Width+1);//BOXBLIT_SIZE;
					int height = dbRnd(TestDynamicSurfaceDesc.Height+1);//BOXBLIT_SIZE;
					int left = dbRnd(TestDynamicSurfaceDesc.Width-(width+1));
					int top = dbRnd(TestDynamicSurfaceDesc.Height-(height+1));
					int right = left + width;
					int bottom = top + height;
					RECT sourcerect = {left , top, right, bottom}; //source rect

					left = dbRnd(myImageSurfaceDesc.Width-(width+1));
					top = dbRnd(myImageSurfaceDesc.Height-(height+1));
					right = left + width;
					bottom = top + height;
					RECT descrect = {left , top, right, bottom}; //dest start point

					DGDKdevice->StretchRect(TestDynamicSurface, &sourcerect, myImageSurface, &descrect, D3DTEXF_NONE);
					}
					break;

				case 8://"CreateRect From Dynamic"
					{
					if (newimagecount < RTSURFACE_MAX) {
						//test source

						//generate a random size by multiple of 2, max 512
						int width = dbRnd(256) * 2;
						int height = dbRnd(256) * 2; //width;
						int left = dbRnd(myImageSurfaceDesc.Width-(width+1));
						int top = dbRnd(myImageSurfaceDesc.Height-(height+1));
						int right = left + width;
						int bottom = top + height;
						RECT sourcerect = {left , top, right, bottom}; //source rect

						//create new dynamic surface
						newimagecount++;
						imagecount++;
						dbMakeImageRenderTarget(imagecount, width, height, D3DFMT_A8R8G8B8)->GetSurfaceLevel(0, &NewDynamicSurface[newimagecount]); //D3DFMT_A1R5G5B5(Depth = 16), D3DFMT_A8R8G8B8(Depth = 32);
						NewDynamicSurface[newimagecount]->GetDesc(&NewDynamicSurfaceDesc[newimagecount]);

						//render to new RT
						DGDKdevice->StretchRect(myImageSurface, &sourcerect, NewDynamicSurface[newimagecount], NULL , D3DTEXF_NONE);

						/*
						//render to work RT
						RECT descrect = {0 , 0, width, height}; //dest start point
						//clear to black
						DGDKdevice->ColorFill(myImageSurface, NULL, dbRGB(0,0,0) );
						//copy
						DGDKdevice->StretchRect(NewDynamicSurface[newimagecount], NULL, myImageSurface, &descrect , D3DTEXF_NONE);
						*/
					}
					}
					break;

				case 9://"CopyRect From Static(WIP)"
					//1. create dynamicSurface at size
					//2. Blit Rect from Static to dynamic
					break;

				case 10://"CreateRect From Static(WIP)"
					//1. create dynamicSurface at size
					//2. Blit Rect from Static to dynamic
					break;

			}
		}



/*
		dxI.LockSurface(); // Locking outside the functions has one purpose , if we want multiple manipulations we dont want to lock unlock each time , but once per manipulation cycle
						   // if we want to manipulate once per cycle , then this can be inside the function.
	
		// Fail Safe for Random Image so it wont random twice the same image.
		do 
		{
			temprandomImage = dbRnd(5)+10;
		}while (temprandomImage ==lastRandomImage);
		lastRandomImage = temprandomImage;

		switch (opchanger)
		{
		case 0: dxI.copyRect(temprandomImage,dbRnd(200),dbRnd(200),400,400,dbRnd(1023),dbRnd(1023));break; // FAST
		case 1: dxI.copyRectWithCache(temprandomImage,1024*500,0,dbRnd(200),dbRnd(200),400,400,dbRnd(1023),dbRnd(1023));break; // FAST
		case 2: dxI.copyRect(temprandomImage);break; // SLOW
		case 3: dxI.copyRectWithCache(temprandomImage,100);break; // FAST
		case 4: dxI.drawBox(dbRnd(200),dbRnd(200),dbRnd(824)+200,dbRnd(824)+200,15,dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)),0,0);break; // FAST
		case 5: dxI.drawBox(dbRnd(200),dbRnd(200),dbRnd(824)+200,dbRnd(824)+200,dbRnd(50),dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)),1,dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)));break; // FAST
		case 6: {
			
			int x1 = dbRnd(895)+64;
			int y1 = dbRnd(895)+64;
			dxI.drawTriangle(x1,y1,x1+64,y1+64,x1-64,y1+64,dbRGB(dbRnd(255),dbRnd(255),dbRnd(255)),0,0);

				}break;
		//case 5: 
		}	

		dxI.UnlockSurface();
*/

		dbRotateObject(1, dbWrapValue(dbObjectAngleX(1) + 1), dbWrapValue(dbObjectAngleY(1) + .5), dbWrapValue(dbObjectAngleZ(1) + .25)  );
		TextStr(dbScreenWidth() - 20,0,dbScreenFPS());
		dbCenterText(dbScreenWidth()/2,0,Op[opchanger]);

		/*
		output = "Surface Description ";
		output.append("\nFormat ");
		output.append(dbStr((int)myImageSurfaceDesc.Format));
		output.append("\nType ");
		output.append(dbStr((int)myImageSurfaceDesc.Type));
		output.append("\nUsage ");
		output.append(dbStr((int)myImageSurfaceDesc.Usage));
		output.append("\nPool ");
		output.append(dbStr((int)myImageSurfaceDesc.Pool));
		output.append("\nMultiSample ");
		output.append(dbStr((int)myImageSurfaceDesc.MultiSampleType));
		output.append("\nMultiSampleQuality ");
		output.append(dbStr((int)myImageSurfaceDesc.MultiSampleQuality));
		output.append("\nWidth ");
		output.append(dbStr((int)myImageSurfaceDesc.Width));
		output.append("\nHeight ");
		output.append(dbStr((int)myImageSurfaceDesc.Height));
*/		

		if(imagecount > 7) {
			dbPasteImage(imagecount,dbScreenWidth()-dbGetImageWidth(imagecount),dbScreenHeight()-dbGetImageHeight(imagecount));
		
			output = "Image ";
			output.append(dbStr(newimagecount));
			output.append(" ");
			output.append(dbStr(dbGetImageWidth(imagecount)));
			output.append(" x ");
			output.append(dbStr(dbGetImageHeight(imagecount)));

			dbText(dbScreenWidth()-dbGetImageWidth(imagecount),dbScreenHeight()-dbGetImageHeight(imagecount) - 16,(char*)output.data());
		}
		

		dbSync(); // Refreshing
		//dxT.~dx9Image();

	}
	//dxI.~dx9Image(); // Releasing the Surface when were done with it.

	// return back to windows
	return;
}