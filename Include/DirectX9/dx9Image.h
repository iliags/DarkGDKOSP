#pragma once

#ifndef DX9IMAGE_H
#define DX9IMAGE_H

#include <map>
#include "..\DarkGDK\DarkSDK.h"
#include <string>
#include "d3d9.h"

using namespace std;

#define 	SQR(a)   ((a)*(a))

#define IMAGECACHE_WIDTH		32			// ImageCache Width default value , 32 shows best results under 60 FPS.
#define IMAGECACHE_HEIGHT		32			// ImageCache Height default value , 32 shows best results under 60 FPS.

#define IMAGECACHE_WIDTH_MAX	1024		// ImageCache Maximum Width, 1024 Maximum using MegaTexture - Cells in MegaTextures will be 1024 or lower.
#define IMAGECACHE_HEIGHT_MAX	1024		// ImageCache Maximum Width, 1024 Maximum using MegaTexture	- Cells in MegaTextures will be 1024 or lower.
#define MAX_POLY_CORNERS		64

// Rect Structure.
struct Rect{
	int startX;
	int startY;
	int endX;
	int endY;
};

class cacheImage
{
public:
	// Properties
	// RGB values
	int R[IMAGECACHE_WIDTH][IMAGECACHE_HEIGHT];		// Red
	int G[IMAGECACHE_WIDTH][IMAGECACHE_HEIGHT];		// Green
	int B[IMAGECACHE_WIDTH][IMAGECACHE_HEIGHT];		// Blue
	int A[IMAGECACHE_WIDTH][IMAGECACHE_HEIGHT];		// Alpha

	int bliterations; // how many times cache blits.
	int temppixelsX;
	int temppixelsY;

	// rect
	Rect image;

	int lastX,lastY;
	bool caching;

	int destinationCacheX,destinationCacheY;

	// Constructor
	cacheImage(void);

	// Destructor
	~cacheImage(void);

	// Cache Function
	void cache(int x,int y,DWORD rgba);

};

class dx9Image 
{
private:
	// temp properties for copyRect
	LPDIRECT3DSURFACE9 tempSurface;
	D3DLOCKED_RECT tempRect;          
	D3DSURFACE_DESC tempDesc;  

	int lastSourceImage;
	int tw, th, tb;
	unsigned char *tempAddr;

	int destX,destY;

	int tpixels;

	cacheImage cache;
	void cacheTemp(int width,int height);
	void useCache(int startX,int startY,int endX,int endY);
	void useCache(int startX,int startY,int endX,int endY,DWORD color);

	// Direct3D initiliazer -< < < < Called in the constructors
	void Init(void);

	// rederTarget to BackBufferPtr
	void targetBbuffer (void);

	// 2D drawings internal functions
	void circlePoints(int cx, int cy, int x, int y, DWORD c);
	void drawCircle(int xCenter, int yCenter, int radius,DWORD c);
	void circleFill(int xc, int yc, int r,DWORD c);


public:
	// STATIC - Global >>> DISABLED FOR DURATION OF TESTING
	//static IDirect3DDevice9*			DGDKdevice;								//Direct 3D device Pointer	
	//static LPDIRECT3DSURFACE9			g_pGlob_pHoldBackBufferPtr;				//mimic DSDK Source `g_pGlob->pHoldBackBufferPtr`
	//static LPDIRECT3DSURFACE9			g_pGlob_pHoldDepthBufferPtr;			//mimic DSDK Source `g_pGlob->pHoldDepthBufferPtr`
	// STATIC - Global >>> DISABLED FOR DURATION OF TESTING
	// Properties
	LPDIRECT3DSURFACE9					DestSurface;							//this Surface
	LPDIRECT3DSURFACE9					DestDepthStencilSurface;				//this DepthStencil Surface
	D3DLOCKED_RECT						DestRect;								//this Rect
	D3DSURFACE_DESC						DestDesc;								//this Description							//this Color Value

	// color fill properties / can also act as a color value
	int cA,cR,cG,cB;

	int lastDestinationImage;
	
	int w, h, b;
	unsigned char *DestAddr;
	
	bool locked;

	// Constructor / Destructor
	dx9Image(void);
	dx9Image(int GDKImageID);
	dx9Image(int GDKImageID,int Width,int Height,LPCSTR fileName,DWORD dwUsage);
	~dx9Image(void);

	void SetImage(int GDKImageID);
	void setTempSurface(int GDKImageId,bool lock);
	// Lock Unlock Surface Functions
	void LockSurface(void);
	void LockSurface(int GDKImageID);
	void UnlockSurface(void);

	// Pixel Perfect Functions
	void putPixel(int x, int y, DWORD c); // To Work with this you need to Lock a surface first using dx9LockSurface, after finsihing dont forget to Unlock the surface using dx9UnlockSurface
	
	DWORD getPixel(int x, int y);
	DWORD getPixelFromTemp(int x,int y);

	void copyRect(int SourceImage);
	void copyRect(int SourceImage,int topleftX,int topleftY,int bottomrightX,int bottomrightY,int destinationX,int destinationY);
	void copyRectWithCache(int SourceImage,int Blit,bool enableMegaTexturing,int topleftX,int topleftY,int bottomrightX,int bottomrightY,int destinationX,int destinationY);
	void copyRectWithCache(int SourceImage,int Blit);
	void fillColor(int startX,int startY,int endX,int endY,DWORD color);
	void fillColorWithCache(int startX,int startY,int endX,int endY,int Blit,DWORD color);

	void drawLine(int x1, int y1, int x2, int y2, DWORD color);
	void drawCircle(int CX, int CY, int R, DWORD c,int borderSize,bool fill,DWORD fColor);
	void drawBox(int startX,int startY,int endX,int endY,int borderSize,DWORD color,bool fill,DWORD fColor);
	void drawBox(int startX,int startY,int endX,int endY,DWORD color1,DWORD color2,DWORD color3,DWORD color4,bool fill,DWORD fColor);
	void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3,DWORD color,bool fill,DWORD fColor);
	void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3,DWORD color1,DWORD color2,DWORD color3,bool fill,DWORD fColor);
	
	int GetMemOffset(int format); // used internally but not really needed.
};

class dx9Surface{
	//Purpose: db texture surface (image) direct dx manipulation
	public:

		static map<int, dx9Surface*> IDmap;
		static map<int, dx9Surface*>::iterator IDmapiterator;
		
		LPDIRECT3DDEVICE9 device;
		LPDIRECT3DTEXTURE9 texture;
		LPDIRECT3DSURFACE9 surface; 
		D3DLOCKED_RECT lockedrect;          
		D3DSURFACE_DESC surfacedesc;  

		int width;
		int height;
		int b;
		unsigned char *addr;

		// Constructor / Destructor
		dx9Surface(int imageID);
		~dx9Surface(void);

		static dx9Surface *create(int imageID);
		static void destroy(dx9Surface *instance);
		static dx9Surface *get(int imageID);

		int capturerect(int sourceimageID, int sourcex, int sourcey, int sourcewidth, int sourceheight, int destx, int desty);
		int capturefrommemblock(int memblockID, int x, int y);
		int capturefrombitmap(int bitmapID, int x, int y);
		int draw(int sourceimageID, int x ,int y);
		//int drawline();
		//int drawrect();
		//int drawoval();
		//int drawpixel();


};

#endif

/*
References: 
http://www.two-kings.de/tutorials/dxgraphics/
	Render to Surface: http://www.two-kings.de/tutorials/dxgraphics/dxgraphics16.html

	Understanding DXSurface
	http://msdn.microsoft.com/en-us/library/aa753544%28VS.85%29.aspx

	IDirect3DDevice9::CreateOffscreenPlainSurface Method
	http://msdn.microsoft.com/en-us/library/bb174358%28VS.85%29.aspx

	Animating Sprites
	http://www.toymaker.info/Games/html/2d_animation.html

*/
