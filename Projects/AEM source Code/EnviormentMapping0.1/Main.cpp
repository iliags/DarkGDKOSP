
#include "..\..\..\Include\DarkGDK\DarkGDK.h"

int cBrush = 0;

int dummyImg = 0;

#include "GdkSystem.h"
#include "AEM.h"

void plot_memimage(int mem,int x,int y,int col,int res,int alpha,int size);
void color_memimage(int,int,int,int,int,int);
void update_memimage(int mem,int img);
void create_memimage(int mem,int img,int wid,int hig);
void ResizeImage(int MemId,int Imageid,int newX,int newY);
void ResizeBitmap(int ImgId,int NewImgId,int NewWidth,int NewHeight);
void recolor_memimage(int mem,int x,int y,DWORD Newcol,DWORD oldcol,int res);
DWORD getmemimage_color(int mem,int x,int y,int res,bool);
int getmemimage_colorR(int mem,int x,int y,int res);
int create_brush(int stamp,int sSize);

int TerrainRes = 512;
int ColorRes = 512;

int stamp_mem = 2;

DWORD White = (255,255,255); 

void DarkGDK ( void )
{
	dbFlushVideoMemory();
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );
	// First Selecting your Screen Resulotion
	ResSelect(1);
	dbAutoCamOff();
	// Randomizing
	dbRandomize(dbTimer());

	//Trixie *tx = new Trixie;
	//Trixie::layer *Layer1 = tx->NewLayer();



	//dbSetCameraView(0,0,dbScreenWidth()/2,dbScreenHeight());
	dbSetCameraRange (0, 1.0f, 30000.0f );
	dbRotateCamera(0,90,0,0);

	//dbMakeCamera(1);
	//dbSetCameraView(1,dbScreenWidth()/2,0,dbScreenWidth(),dbScreenHeight());
	//dbMakeCamera(0);
	// Settin up Camera

	dummyImg = GetFreeImage();
	dbCreateBitmap(1,10,10);
	dbSetCurrentBitmap(1);
	dbCLS(dbRGB(255,255,255));
	dbGetImage(dummyImg,0,0,10,10);
	dbDeleteBitmap(1);


	// Creating Text Overlay
	int overlayText = GetFreeImage();
	dbCreateBitmap(1,dbScreenWidth(),dbScreenHeight());
	dbSetCurrentBitmap(1);
	dbSetTextSize(18);
	dbInk(dbRGB(255,0,0),0);
	dbSetTextToBold();
	dbText(0,0,"Automated Enviorment Mapping 0.1 - Super3dGameEngine - Core PlugIn -");
	dbText(0,30,"Selecting Colors 1 - 10, full version will include 255 X 3 color selection");
	dbText(0,60,"Paint on Terrain with Left Mouse Button");
	dbText(0,90,"Switch Between Low Res / AEM High Res  Right Mouse Button");
	dbText(0,120,"Reset Terrain Coloring with 'R' - Low Res");
	dbText(0,150,"Increase Brush Size 'Q' | Decrease Brush Size 'A'");
	dbText(0,180,"Zoom In 'W' | Zoom Out 'S'");
	dbText(0,210,"Show/Hide Help Menu 'H'");
	dbText(0,240,"Press the Space Key To Excute AEM Stamp Algorithem");
	dbText(0,270,"Press the Control Key to Switch between Top View and First Person View");
	dbText(0,300,"Select a Color , Aim with your mouse on a Colored Surface , Press 'X' to Recolor");
	dbText(0,330,"Press the 'F' Key to fill the entire terrain with a single color");
	dbText(0,360,"Move with Arrow Keys");
	dbText(0,390,"Increse Stamp Dentisy 'E' | Decrease Stamp Dentisy 'D'");
	dbText(0,420,"Not Included in this demo: NormalMapping/ MipMapping/ Layers / Shaders/Foliage and Enviorment Models");
	dbText(0,450,"Also Note that only Channel/Color 1 and 4 will Calculate Stamps");
	dbGetImage(overlayText,0,0,dbBitmapWidth(),dbBitmapHeight());
	dbSetCurrentBitmap(0);
	dbInk(dbRGB(255,255,255),0);
	dbSetTextToNormal();

	// text OverLay Sprite
	
	dbSprite(1,0,0,overlayText);


	int lowres = 3;
	// Creating the RGB Texture for the Terrain
	create_memimage(1,3,ColorRes,ColorRes);
	for( int x=0;x <= ColorRes;x++)
	{
		for( int y=0;y <= ColorRes;y=y++)
		{
			plot_memimage(1,x,y,dbRGBB(dbRnd(255)),ColorRes,255,1);
		}
	}

	//update_memimage(1,2);

	// Loading up Terrain
	// Mask Terrain
	dbSetupTerrain ( );
	dbMakeObjectTerrain ( 1 );
	dbSetTerrainHeightMap ( 1, "map.bmp" );
	dbSetTerrainScale ( 1, 9.0f, 1.8f,9.0f );
	dbSetTerrainLight ( 1, 1.0f, -0.25f, 1.0f, 1.0f, 1.0f, 0.78f, 0.5f );
	dbBuildTerrain ( 1 );
	update_memimage(1,lowres);

	float tXsize = dbObjectSizeX(1);
	float tZsize = dbObjectSizeZ(1);


	float fHeight = 0.0f;
	int Fps = 0;
	int mx = 0 ,my = 0;
	int pick = 0;
	int BrushSize = 20;




	cBrush = GetFreeImage();
	dbLoadImage("Cbrush.png",cBrush);
	dbCreateBitmap(1,100,100);
	dbCLS();
	dbSetCurrentBitmap(0);

	create_brush(cBrush,BrushSize);

	int hTimer = 0;
	bool hHide = false;
	int cTimer = 0;
	bool cView = false;

	dbPositionCamera(0,tXsize/2,1000,tZsize/2);
	//dbPositionCamera(1,tXsize/2,dbGetTerrainGroundHeight(1,tXsize/2,tZsize/2),tZsize/2);

	dbSetCurrentCamera(0);
	// declaring Stamps Images Ids and loading them
	int Grass[3] = {0};
	Grass[0] = GetFreeImage();
	dbLoadImage("Stamps/Grass1.png",Grass[0]);
	Grass[1] = GetFreeImage();
	dbLoadImage("Stamps/Grass2.png",Grass[1]);

	int Alpha[3] = {0};
	Alpha[0] = GetFreeImage();
	dbLoadImage("Stamps/alpha_cracks1.png",Alpha[0]);
	Alpha[1] = GetFreeImage();
	dbLoadImage("Stamps/alpha_cracks2.png",Alpha[1]);

	int Rock[3] = {0};
	Rock[0] = GetFreeImage();
	dbLoadImage("Stamps/rock1.png",Rock[0]);

	int CurrentColor = 0;
	int definedcolors = 2;
	// Declaring Colors (AKA Channels in Trixie) 
	// ok , Color or channel , holds an RGB value of what it is
	// holds name , and holds the connection to the stamps that the stamps algo use to stamp with on a spechific color/channel.
	// In trixie , instead of declaring for the paintbot for this channel do this and this , my suggestion
	// declare the stamps (of the stamp algo) to a spechific channel, this way the paintbot will just randomize them while knowing in advance what stamps
	// are used for what color / channel / channel layer.
	// and since we are using a channel as an induvidual layer of the entire texture , the paint bot when it start the stamp algo it will
	// calculate only the current layer deffinition by width and height and not the entire trixie object , it will help fasten the system calculations
	// do not forget we are going to use megatextures and in the case of 1000000000x 10000000 texture it will take a very long time to do a stamp algo on
	// the entire map or current level.
	// this approach is faster , and much more cleaner.
	Color Env[10];
	Env[0].SetColor(0,255,0); // the first channel
	Env[0].SetName("Grass"); // the green grass channel
	Env[0].AddTextureStamp(Grass[0],1000,25,29); // AddTextureStamp(Image Id,stamp priority on the channel,minimum size random , maximum size random)
	Env[0].AddTextureStamp(Grass[1],15,20,27);
	Env[0].AddTextureStamp(Rock[0],75,3,15);
	// as you can see the first channel , recive 3 stamps , these stamps are connected to that channel, it dosent mean you cant connect them to other channels
	// but they are connected , and within the channel they contain all the properties they need in order to work properly 

	Env[1].SetColor(34,177,76);
	Env[1].SetName("DarkGrass");

	Env[2].SetColor(69,96,59);
	Env[2].SetName("HardGrass");

	Env[3].SetColor(230,213,185);
	Env[3].SetName("LightDirt");
	Env[3].AddTextureStamp(Alpha[0],1000,10,25);
	Env[3].AddTextureStamp(Rock[0],5,3,15);
	Env[3].AddTextureStamp(Alpha[1],3,5,32);
	// and as you can see here , the lightdirt channel contain 3 stamps also , but 2 of them are diffrent from the on in grass channel
	// the one that is similar is Rock[0] , but look , the rock priority here is much lower , meaning we dont want it as much as in the grass channel
	// so , you get diffrent properties and overall diffrent implentation of the same stamp but with diffrent detisy regarding other stamp in this channel.
	// it is more organized thats all.

	Env[4].SetColor(194,154,86);
	Env[4].SetName("Dirt");

	Env[5].SetColor(255,255,255);
	Env[5].SetName("Ice");

	Env[6].SetColor(155,150,111);
	Env[6].SetName("HighGrounds Rocks");

	Env[7].SetColor(75,56,35);
	Env[7].SetName("HighGrounds Dirt");

	Env[8].SetColor(244,244,244);
	Env[8].SetName("HighGrounds Snow");

	Env[9].SetColor(111,106,107);
	Env[9].SetName("Road");



	int crntRed = 0;
	int crntGreen = 255;
	int crntBlue = 0;

	int SpaceTimer = 0;

	int ResetTimer = 0;
	bool hRes = false;
	int MouseTimer = 0;
	bool StampNow = false;

	int stampcounter = 0;
	//dbHideObject(1);
	//dbHideObject(2);

	bool painted = false;
	int iPart =4092;
	int switchTimer = 0;
	bool oldColorMatched = false;
	int sDentisy = 6; 
	int dTimer = 0;
	int sTimer = 0;
	int rTimer = 0;
	// our main loop
	while ( LoopGDK ( ) )
	{
		// Current Selected Color Name.
		dbCenterText(dbScreenWidth()/2 ,0,Env[CurrentColor].GetName());


		// saving mouse X / Y once
		mx = dbMouseX(); my = dbMouseY();
		
		// Recoloring. X key.
		if (dbKeyState(45))
		{
			if (ActionTimer(dbTimer(),switchTimer,300))
			{
				pick=dbPickObject(mx,my,1,1);
				if (pick>0)
				{
					float curx=dbCameraPositionX()+dbGetPickVectorX();
					float curz=dbCameraPositionZ()+dbGetPickVectorZ();
					float px=(curx/tXsize)*ColorRes;
					float py=(curz/tZsize)*ColorRes;
					DWORD oldColor = getmemimage_color(1,px,py,ColorRes,0);
					for (int i = 0; i< 10;i++)
					{
						if (dbRGBR(oldColor) == Env[i].GetColorRed() && dbRGBG(oldColor) == Env[i].GetColorGreen() && dbRGBB(oldColor) == Env[i].GetColorBlue())
						{
							oldColorMatched = true;
						}
					}
					if (oldColorMatched)
					{
						for( int x=0;x <= ColorRes;x++)
						{
							for( int y=0;y <= ColorRes;y=y++)
							{
								recolor_memimage(1,x,y,dbRGB(crntRed,crntGreen,crntBlue),oldColor,ColorRes);
							}
						}
						update_memimage(1,lowres);
						oldColorMatched = false;
						painted = true;
					}
				}
				//switchTimer = dbTimer();

			}
		}
		// Color Fill
		if (dbKeyState(33)) // F Key
		{
			if (ActionTimer(dbTimer(),ResetTimer,500))
			{
				for( int x=0;x <= ColorRes;x++)
				{
					for( int y=0;y <= ColorRes;y=y++)
					{
						plot_memimage(1,x,y,dbRGB(crntRed,crntGreen,crntBlue),ColorRes,255,1);
					}
				}
				//ResetTimer = dbTimer();
				update_memimage(1,lowres);
				painted = true;
			}
		}

		// Reseting Color Texture
		if (dbKeyState(19)== 1)
		{
			if (ActionTimer(dbTimer(),ResetTimer,500))
			{
				for( int x=0;x <= ColorRes;x++)
				{
					for( int y=0;y <= ColorRes;y=y++)
					{
						plot_memimage(1,x,y,dbRGBB(dbRnd(255)),ColorRes,255,1);
					}
				}
				//ResetTimer = dbTimer();
				update_memimage(1,lowres);
				painted = true;
			}
		}


		// Switching to High Res Texture
		if (dbMouseClick()==2)
		{
			if (ActionTimer(dbTimer(),MouseTimer,500))
			{
				if (!hRes)
				{
					dbTextureObject(1,100);
					hRes = true;
				}
				else
				{
					dbTextureObject(1,lowres);
					hRes = false;
				}
				//MouseTimer = dbTimer();
			}
		}

		// Aem Key
		if (dbSpaceKey())
		{
			if(ActionTimer(dbTimer(),SpaceTimer,500))
			{
				dbCenterText(dbScreenWidth()/2,dbScreenHeight()/2,"Creating Higer Res Texutre, it may take some time, Please Wait.");
				dbSync();
				if (painted)
				{
					
					ResizeBitmap(lowres,100,iPart,iPart);
					painted = false;
				}
				//dbTextureObject(1,100);
				//dbSetObjectTexture(1,6,1);
				//SpaceTimer = dbTimer();
				//dbHideObject(1);
				//dbShowObject(2);
				StampNow = true;
			}
		}
		// Aem ALGO
		if (StampNow)
		{


			//int tbit = GetFreeBitmap();
			//dbCreateBitmap(tbit,iPart,iPart);
			int ibit = GetFreeBitmap();
			dbSetTextSize(50);
			dbCreateBitmap(ibit,iPart,iPart);
			dbSetCurrentBitmap(ibit);
			dbCLS();
			dbPasteImage(100,0,0);
			int tm = GetFreeMemblock();
			DWORD point = 0;
			dbMakeMemblockFromBitmap(tm,ibit);

			// temp vars
			int tRed = 0,tGreen = 0,tBlue = 0;

			//dbSetCurrentBitmap(tbit);		
			for( int x=0;x <= iPart;x = x + sDentisy)
			{
				for( int y=0;y <= iPart;y++)
				{
					point = getmemimage_color(tm,x,y,iPart,1);
					tRed = dbRGBR(point);
					tGreen = dbRGBG(point);
					tBlue = dbRGBB(point);
					for (int i =0;i < 10;i++)
					{
						if (Env[i].GetTextureCounter() > 0)
						{
							if (tRed == Env[i].GetColorRed() && tGreen == Env[i].GetColorGreen() && tBlue == Env[i].GetColorBlue())
							{
								Env[i].Stamp(x,y);
								stampcounter ++;
								y = y+ sDentisy;
							}
						}
					}
				}
				dbSetCurrentBitmap(0);
				//dbSync();
				int p =(float)x/iPart * 100;
				TextStr(0,dbScreenHeight()-75,p);
				dbText(75,dbScreenHeight()-75,"Done!");
				dbSync();
				if (x <= iPart)
				dbSetCurrentBitmap(ibit);
				else
					dbSetCurrentBitmap(0);

			}
			dbSetTextSize(15);
			StampNow = false;
			dbGetImage(100,0,0,iPart,iPart);
			dbTextureObject(1,100);
			//debuging
			//dbGetImage(1,0,0,iPart,iPart);
			//dbSetCurrentBitmap(0);
			//dbDeleteBitmap(tbit);
			dbDeleteBitmap(ibit);
			dbDeleteMemblock(tm);
		}

		// Color Key Switch
		int scan = dbScanCode();
		if (scan > 0 && scan < 12)
		{
			CurrentColor = scan-2;
			crntRed = Env[scan-2].GetColorRed();
			crntGreen = Env[scan-2].GetColorGreen();
			crntBlue = Env[scan-2].GetColorBlue();
		}
		// switching FirstPerson View / SatCam
		if (dbControlKey())
		{
			if (ActionTimer(dbTimer(),cTimer,200))
			{
				if (cView)
				{				
					dbSetCurrentCamera(0);
					cView = false;
				}
				else
				{
					dbSetCurrentCamera(1);
					cView = true;
				}
				//cTimer = dbTimer();
			}

		}

		// Hide / Show Help Sprite
		if (dbKeyState(35))
		{
			if (ActionTimer(dbTimer(),hTimer,200))
			{
				if (hHide)
				{
					dbShowSprite(1);
					hHide = false;
				}
				else
				{
					dbHideSprite(1);
					hHide = true;
				}

				//hTimer = dbTimer();
			}
		}




		if (cView)
		{
			FpsCamera(0);
			//find the ground height of the terrain
			fHeight = dbGetTerrainGroundHeight ( 1, dbCameraPositionX ( 0), dbCameraPositionZ (0 ));

			// reposition the camera so it is directly above the ground
			dbPositionCamera ( dbCameraPositionX ( 0), fHeight + 35.0f, dbCameraPositionZ (0 ));
		}
		else
		{
			dbRotateCamera(90,0,0);
			SatControl();
		}




		// Coloring

		if (dbMouseClick()==1)
		{	
			pick=dbPickObject(mx,my,1,1);
			if (pick>0)
			{
				float curx=dbCameraPositionX()+dbGetPickVectorX();
				float curz=dbCameraPositionZ()+dbGetPickVectorZ();
				float px=(curx/tXsize)*ColorRes;
				float py=(curz/tZsize)*ColorRes;
				//plot_memimage(1,px,py,dbRgb(0,255,0),ColorRes,0,20);	
				color_memimage(1,px-BrushSize/2,py+BrushSize/2,ColorRes,dbRGB(crntRed,crntGreen,crntBlue),stamp_mem);
				update_memimage(1,lowres);

			}
			painted = true;
		}
		// Color Brush Size
		if (dbKeyState(16))
		{
			if (ActionTimer(dbTimer(),sTimer,75))
			{
				if (BrushSize < 60)
				{
					//sTimer = dbTimer();
					BrushSize++;
					create_brush(cBrush,BrushSize);
				}
			}
		}
		else
		{
			if (dbKeyState(30))
			{
				if (ActionTimer(dbTimer(),sTimer,75))
				{
					if (BrushSize > 10)	
					{
					//	sTimer = dbTimer();
						BrushSize--;
						create_brush(cBrush,BrushSize);
					}

				}
			}
		}


		// Dentisy Select
		if (dbKeyState(18))// E key
		{
			if (ActionTimer(dbTimer(),sTimer,75))
			{
				if (sDentisy > 3)
				{
					//sTimer = dbTimer();
					sDentisy --;
				}

			}
		}
		else
		{
			if (dbKeyState(32)) // D Key
			{
				if (ActionTimer(dbTimer(),sTimer,75))
				{
					if (sDentisy < 22)
					{
						//sTimer = dbTimer();
						sDentisy ++;
					}

				}
			}
		}
		Fps = dbScreenFPS ();

		// Text
		TextStr(dbScreenWidth()-20,0,Fps);
		TextStr(dbScreenWidth()-50,0,stampcounter);

		// Dentisy Text
		dbText(0, dbScreenHeight()-45,"Stamp Dentisy : ");
		int tDent = 22 - sDentisy+3;
		int dPre =(float)tDent/22 * 100;
		TextStr(0 + dbTextWidth("Stamp Dentisy : "),dbScreenHeight()-45,dPre);

		// Brush Size Text
		dbText(0,dbScreenHeight()-30,"Color Brush Size : ");
		int bPre = (float)BrushSize/60 * 100;
		TextStr(0+dbTextWidth("Color Brush Size : "),dbScreenHeight()-30,bPre);


		// update Terrain
		dbUpdateTerrain( );
		// update the screen
		dbSync ( );
	}

	// Cleaning or Deleting All Ids
	CleanAll();

	// return back to windows
	return;
}

void create_memimage(int mem,int img,int wid,int hig)
{
	int size=(wid*hig*4)+12;

	if (dbMemblockExist(mem)==1){dbDeleteMemblock( mem);}

	dbMakeMemblock(mem,size);

	dbWriteMemblockDword( mem,0,wid);
	dbWriteMemblockDword( mem,4,hig);
	dbWriteMemblockDword( mem,8,32);

	if (dbImageExist(img)==1) dbDeleteImage( img);
	dbMakeImageFromMemblock( img,mem);
}


void plot_memimage(int mem,int x,int y,int col,int res,int alpha,int size)
{
	//x=res-x;

	if (dbMemblockExist(mem)==0)return;

	y= res-y;
	if (x<0 || y<0) return;
	if (x>=res || y>=res) return;

	int  pos=12+((x+(y*res))*4);

	dbWriteMemblockByte( mem,pos+0,dbRgbB(col));
	dbWriteMemblockByte( mem,pos+1,dbRgbG(col));
	dbWriteMemblockByte( mem,pos+2,dbRgbR(col));
	dbWriteMemblockByte( mem,pos+3,alpha);
}

void recolor_memimage(int mem,int x,int y,DWORD Newcol,DWORD oldcol,int res)
{
	//x=res-x;

	if (dbMemblockExist(mem)==0)return;

	y= res-y;
	if (x<0 || y<0) return;
	if (x>=res || y>=res) return;

	int  pos=12+((x+(y*res))*4);

	int r = dbMemblockByte(mem,pos+2);
	int g = dbMemblockByte(mem,pos+1);
	int b = dbMemblockByte(mem,pos+0);

	if (r == dbRGBR(oldcol) && g == dbRGBG(oldcol) && b == dbRGBB(oldcol))
	{
		dbWriteMemblockByte( mem,pos+0,dbRgbB(Newcol));
		dbWriteMemblockByte( mem,pos+1,dbRgbG(Newcol));
		dbWriteMemblockByte( mem,pos+2,dbRgbR(Newcol));
		dbWriteMemblockByte( mem,pos+3,255);
	}


}

DWORD getmemimage_color(int mem,int x,int y,int res,bool opY)
{

	if (dbMemblockExist(mem)==0)return 0 ;

	if (!opY)
		y= res-y;
	if (x<0 || y<0) return 0;
	if (x>=res || y>=res) return 0;

	int  pos=12+((x+(y*res))*4);

	int r = dbMemblockByte(mem,pos+2);
	int g = dbMemblockByte(mem,pos+1);
	int b = dbMemblockByte(mem,pos+0);

	DWORD color = dbRGB(r,g,b);

	return color;
}

int getmemimage_colorR(int mem,int x,int y,int res)
{

	if (dbMemblockExist(mem)==0)return 0 ;

	//y= res-y;
	if (x<0 || y<0) return 0;
	if (x>=res || y>=res) return 0;

	int  pos=12+((x+(y*res))*4);

	int r = dbMemblockByte(mem,pos+2);
	return r;
}

void color_memimage(int mem,int x,int y,int res,int col,int stamp)
{
	if (dbMemblockExist(mem)==0)return;

	y= res-y;
	if (x<0 || y<0) return;
	if (x>=res || y>=res) return;

	int point = 0;

	// temp rgb
	//int pR = 0,pG = 0,pB = 0;
	int tempRes = dbMemblockByte(stamp,0);
	for (int xX = 0; xX < tempRes;xX++)
	{
		for (int yY = 0; yY< tempRes;yY++)
		{
			point = getmemimage_colorR(stamp,xX,yY,tempRes);
			//pR = dbRGBR(point);
			//pG = dbRGBG(point);
			//pB = dbRGBB(point);
			if (point != 0)
			{
				int  pos=12+((x+xX+(y+yY)*res))*4;
				dbWriteMemblockByte( mem,pos+0,dbRgbB(col));
				dbWriteMemblockByte( mem,pos+1,dbRgbG(col));
				dbWriteMemblockByte( mem,pos+2,dbRgbR(col));
				dbWriteMemblockByte( mem,pos+3,255);
			}

		}
	}

}

int create_brush(int stamp,int sSize)
{
	int StampSpr = GetFreeSprite();
	dbSprite(StampSpr,0,0,stamp);
	dbSizeSprite(StampSpr,sSize,sSize);
	dbHideSprite(StampSpr);

	int tbit = GetFreeImage();
	dbCreateBitmap(tbit,sSize,sSize);
	dbSetCurrentBitmap(tbit);
	dbCLS();
	dbPasteSprite(StampSpr,0,0);
	if (dbMemblockExist(stamp_mem) ==1 ) dbDeleteMemblock(stamp_mem);
	dbMakeMemblockFromBitmap(stamp_mem,tbit);
	dbDeleteBitmap(tbit);
	dbDeleteSprite(StampSpr);

	return stamp_mem;
}

void update_memimage(int mem,int img)
{

	if (dbMemblockExist(mem)==0) return;
	if (dbImageExist(img) == 1) dbDeleteImage(img);
	dbMakeImageFromMemblock( img,mem);

	dbTextureObject(1,img);
}

void ResizeImage(int MemId,int Imageid,int newX,int newY)
{
	dbMakeMemblockFromImage(MemId ,Imageid);
	int width = dbMemblockDword(MemId, 0);
	int height = dbMemblockDword(MemId, 4);
	int tempMem = GetFreeMemblock();

	//`make new image memblock
	dbMakeMemblock( tempMem, 12 + (newX * newY * 4));
	dbWriteMemblockDword( tempMem, 0, newX);
	dbWriteMemblockDword( tempMem, 4, newY);
	dbWriteMemblockDword( tempMem, 8, 32);

	//`Start copying data
	for (int y = 1;y < newY;y++)
	{
		for (int x = 1; x<newX;x++)
		{

			//`Get positions
			int Ox = width/newX*(x-1);
			int Oy = height/newY*(y-1);
			int Opos = 12 + (Oy*(width)*4) + (Ox*4);

			int pos = 12 + ((y-1)*newX*4) + ((x-1)*4);

			//`Copy data
			dbCopyMemblock(MemId,tempMem, Opos, pos, 4);
		}
	}

	//`Transform into images
	dbMakeImageFromMemblock(10, tempMem);
	dbDeleteMemblock(tempMem);
	dbDeleteMemblock(MemId);
}

void ResizeBitmap(int ImgId,int NewImgId,int NewWidth,int NewHeight)
{
	int b = GetFreeBitmap();
	dbCreateBitmap(b,dbGetImageWidth(ImgId),dbGetImageHeight(ImgId));
	dbSetCurrentBitmap(b);
	dbPasteImage(ImgId,0,0);

	int c = GetFreeBitmap();
	dbCreateBitmap(c,NewWidth,NewHeight);
	dbSetCurrentBitmap(c);
	dbCopyBitmap(b,0,0,dbGetImageWidth(ImgId),dbGetImageHeight(ImgId),c,0,0,NewWidth,NewHeight);
	dbGetImage(NewImgId,0,0,NewWidth,NewHeight);

	dbDeleteBitmap(b);
	dbDeleteBitmap(c);
	dbSetCurrentBitmap(0);
}
