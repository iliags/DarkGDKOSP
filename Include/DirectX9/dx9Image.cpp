#include "..\..\Include\DarkGDK\DarkSDK.h"
#include "d3d9.h"
#include "dx9Image.h"
#include "math.h"

cacheImage::cacheImage(void)
{
	for (int x=0; x< IMAGECACHE_WIDTH;x++)
	{
		for (int y=0; y< IMAGECACHE_HEIGHT; y++)
		{
			R[x][y]= G[x][y] = B[x][y] = A[x][y] = 0;
		}
	}
	lastX = lastY = 0;
	bliterations = 1;
	caching = false;
	destinationCacheX = destinationCacheY = 0;
	image.startX = image.startY = image.endX = image.endY =0;
}

cacheImage::~cacheImage(void){}

void cacheImage::cache(int x,int y,DWORD argb)
{
	//D3DFMT_A8R8G8B8
	A[x][y] = (int)((argb & 0xFF000000) >> 24);	//RgbA
	R[x][y] = (int)((argb & 0x00FF0000) >> 16);	//RgbR
	G[x][y] = (int)((argb & 0x0000FF00) >> 8);	//RgbG 
	B[x][y] = (int)((argb & 0x000000FF) );		//RgbB
}
void dx9Image::Init(void)
{
	// STATIC - Global >>> DISABLED FOR DURATION OF TESTING
	//by Techlord (GDK Mimic)
	////DGDKdevice = dbGetDirect3DDevice();
	//DGDKdevice->GetRenderTarget(0,&g_pGlob_pHoldBackBufferPtr); 
	//DGDKdevice->GetDepthStencilSurface(&g_pGlob_pHoldDepthBufferPtr);


	DestSurface=0; 
	w = h = b = 0;
	DestAddr = NULL;
	tempSurface = 0;
	tempAddr = NULL;
	lastSourceImage = 0;
	lastDestinationImage = 0;
}


dx9Image::dx9Image(void)
{
	Init();
}
dx9Image::dx9Image(int GDKImageId)
{
	Init();
	
	dbGetImagePointer(GDKImageId)->GetSurfaceLevel(0, &DestSurface);
	
	DestSurface->GetDesc(&DestDesc);
	DestSurface->LockRect(&DestRect, 0, 0);

	DestAddr = (unsigned char*)DestRect.pBits; 	

	b = GetMemOffset(DestDesc.Format);

	w = dbGetImageWidth(GDKImageId);
	h = dbGetImageHeight(GDKImageId);

	DestSurface->UnlockRect();
}

dx9Image::dx9Image(int GDKImageID,int Width,int Height, LPCSTR fileName,DWORD dxUsage)
{
	Init();
	dbMakeImageUsage(GDKImageID,Width,Height,dxUsage)->GetSurfaceLevel(0,&DestSurface);
	D3DXLoadSurfaceFromFile(DestSurface, NULL, NULL, fileName, NULL, D3DX_DEFAULT, 0, NULL);
	DestSurface ->GetDesc(&DestDesc);
}

dx9Image::~dx9Image()
{
	DestSurface = 0;
}

void dx9Image::SetImage(int ImageId)
{
	DestSurface=0; 
	w = h = b = 0;
	DestAddr = NULL;
	
	dbGetImagePointer(ImageId)->GetSurfaceLevel(0, &DestSurface);

	w = dbGetImageWidth(ImageId);
	h = dbGetImageHeight(ImageId);
	lastDestinationImage = ImageId;
}

void dx9Image::LockSurface()
{

	DestSurface->LockRect(&DestRect, 0, 0);
	locked = true;

}

void dx9Image::LockSurface(int ImageId)
{
	if ( lastDestinationImage !=ImageId)
	{
	DestSurface=0; 
	w = h = b = 0;
	DestAddr = NULL;
	
	dbGetImagePointer(ImageId)->GetSurfaceLevel(0, &DestSurface);

	w = dbGetImageWidth(ImageId);
	h = dbGetImageHeight(ImageId);

	DestSurface->GetDesc(&DestDesc);


	DestAddr = (unsigned char*)DestRect.pBits; 	

	b = GetMemOffset(DestDesc.Format);


	}
	DestSurface->LockRect(&DestRect, 0, 0);
	locked = true;

}
void dx9Image::UnlockSurface()
{
	DestSurface->UnlockRect();
	DestSurface->Release();
	locked = false;
}

void dx9Image::putPixel(int x, int y, DWORD c) 
{	      

	unsigned int dmem_loc;


	if (x >= 0 && x < w-1 && y >= 0 && y < h-1) {
		dmem_loc = (x * b) + ((y) * DestRect.Pitch);
		*(DWORD*)(DestAddr + dmem_loc) = c;
	}
    
}

DWORD dx9Image::getPixel(int x, int y) 
{	      

	unsigned int dmem_loc;

	DWORD c=0;
	if (x >= 0 && x < w-1 && y >= 0 && y < h-1) {
		dmem_loc = (x * b) + ((y) * DestRect.Pitch);
		c = *(DWORD*)(DestAddr + dmem_loc);
	}
    return c;
}

DWORD dx9Image::getPixelFromTemp(int x, int y) 
{	      

	unsigned int dmem_loc;

	DWORD c=0;
	if (x >= 0 && x < w-1 && y >= 0 && y < h-1) {
		dmem_loc = (x * b) + ((y) * tempRect.Pitch);
		c = *(DWORD*)(tempAddr + dmem_loc);
	}
    return c;
}

void dx9Image::setTempSurface(int SourceImage,bool lock)
{
	// First we check if the new temp image is not the same as the last one , if it is the same then no need to get all the temp information again.
	if (SourceImage != lastSourceImage)
	{
		if (lastSourceImage > 0)
		{
			tempSurface->UnlockRect();
		}
		tempSurface = 0;

		dbGetImagePointer(SourceImage)->GetSurfaceLevel(0,&tempSurface);

		tw = dbGetImageWidth(SourceImage);
		th = dbGetImageHeight(SourceImage);

		tempSurface->GetDesc(&tempDesc);
		tempSurface->LockRect(&tempRect, 0, 0);

		tempAddr = (unsigned char*)tempRect.pBits; 	

		tb = GetMemOffset(tempDesc.Format);
		lastSourceImage = SourceImage;
	}
	if (!lock)
	{
		tempSurface->UnlockRect();
	}
}

void dx9Image::copyRect(int SourceImage)
{
	setTempSurface(SourceImage,1);
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y< h;y++)
		{
			putPixel(x,y,getPixelFromTemp(x,y));
		}
	}
}

void dx9Image::copyRect(int SourceImage,int topleftX,int topleftY,int bottomrightX,int bottomrightY,int destinationX,int destinationY)
{
	setTempSurface(SourceImage,1);

	for (int x = topleftX; x <= topleftX + bottomrightX;x++)
	{
		for (int y= topleftY; y <=topleftY + bottomrightY; y++)
		{
			putPixel(destinationX + x - topleftX,destinationY + y - topleftY, getPixelFromTemp(x,y));
		}
	}
}


void dx9Image::cacheTemp(int width,int height)
{
	int x1,y1;		
	x1=y1=0;
	for (int x = cache.lastX; x < cache.lastX+width; x++)
	{
		y1=0;
		for (int y= cache.lastY; y< cache.lastY+height; y++)
		{
			cache.cache(x1,y1,getPixelFromTemp(x,y));
			y1++;
		}
		x1++;
	}	
}
void dx9Image::useCache(int startX,int startY,int endX,int endY ,DWORD color)
{
	int temp = 0;
	int blit= 0;
	int tX,tY;
	int tempx,tempy;
	int tempstarty = 0;
	while (blit != cache.bliterations)
	{
		// cache system version 0.2.
		// Accuracy pixel checking (cs v0.2) , for not caching or exctracting more then remaining pixels
		// in the old version , even if there was 1 pixel on the X or Y axis , it would cache IMAGECACHE_WIDHT and HEIGHT 
		// and putPixel of that size regardless if there is only one more pixel to cache and put.
		// so on a full image you dont see it , but on small rectangles you do.

		// Accuracy pixel Checking.
		if (cache.destinationCacheX + IMAGECACHE_WIDTH > endX)
		{
			cache.temppixelsX = endX - cache.destinationCacheX;
		}
			else
			{
				cache.temppixelsX = IMAGECACHE_HEIGHT;
			}
		if (cache.destinationCacheY + IMAGECACHE_HEIGHT > endY)
		{
			cache.temppixelsY = endY - cache.destinationCacheY ;
		}
			else
			{
				cache.temppixelsY = IMAGECACHE_WIDTH;
			}

		tX = cache.temppixelsX;
		tY = cache.temppixelsY;

		tempx=tempy=0;
		while (tX > 0)
		{
			tempx = (cache.temppixelsX - tX);
			while (tY > 0)
			{
				tempy = (cache.temppixelsY - tY);
				putPixel(cache.destinationCacheX+ tempx,cache.destinationCacheY + tempy,D3DCOLOR_ARGB(cache.A[tempx][tempy],cache.R[tempx][tempy],cache.G[tempx][tempy],cache.B[tempx][tempy]));
				tY --;
			}
			tX --;
			tY = cache.temppixelsY;
			cache.destinationCacheY = destY;
			
		}
		cache.destinationCacheX += cache.temppixelsX;

		blit++;
		if (cache.lastX >= endX)
		{
			destY += cache.temppixelsY;
			cache.destinationCacheY += cache.temppixelsY;

			cache.destinationCacheX = destX;
		}
		// checking if the process ended.
		if (cache.lastY >= endY)
		{
			cache.destinationCacheX = cache.destinationCacheY = 0;
			cache.temppixelsX = cache.temppixelsY = 0;
			cache.caching = false;
			blit = cache.bliterations;
		}
	}

}

void dx9Image::useCache(int startX,int startY,int endX,int endY)
{
	int temp = 0;
	int blit= 0;
	int tX,tY;
	int tempx,tempy;
	int tempstarty = 0;
	while (blit != cache.bliterations)
	{
		// cache system version 0.2.
		// Accuracy pixel checking (cs v0.2) , for not caching or exctracting more then remaining pixels
		// in the old version , even if there was 1 pixel on the X or Y axis , it would cache IMAGECACHE_WIDHT and HEIGHT 
		// and putPixel of that size regardless if there is only one more pixel to cache and put.
		// so on a full image you dont see it , but on small rectangles you do.

		// Accuracy pixel Checking.
		if (cache.lastX + IMAGECACHE_WIDTH > endX)
		{
			cache.temppixelsX = endX - cache.lastX;	
		}
			else
			{
				cache.temppixelsX = IMAGECACHE_HEIGHT;
			}
		if (cache.lastY + IMAGECACHE_HEIGHT > endY)
		{
			cache.temppixelsY = endY - cache.lastY;
		}
			else
			{
				cache.temppixelsY = IMAGECACHE_WIDTH;
			}

		tX = cache.temppixelsX;
		tY = cache.temppixelsY;

		cacheTemp(cache.temppixelsX,cache.temppixelsY);
		tempx=tempy=0;
		tempstarty = cache.lastY;
		while (tX > 0)
		{
			tempx = (cache.temppixelsX - tX);
			while (tY > 0)
			{
				tempy = (cache.temppixelsY - tY);
				putPixel(cache.destinationCacheX+ tempx,cache.destinationCacheY + tempy,D3DCOLOR_ARGB(cache.A[tempx][tempy],cache.R[tempx][tempy],cache.G[tempx][tempy],cache.B[tempx][tempy]));
				tY --;
			}
			tX --;
			tY = cache.temppixelsY;
			cache.lastY = tempstarty;
			cache.destinationCacheY = destY;
			
		}
		cache.lastX += cache.temppixelsX;
		cache.destinationCacheX += cache.temppixelsX;

		blit++;
		if (cache.lastX >= endX)
		{
			cache.lastY += cache.temppixelsY;

			destY += cache.temppixelsY;
			cache.destinationCacheY += cache.temppixelsY;

			cache.lastX = startX;
			cache.destinationCacheX = destX;
		}
		// checking if the process ended.
		if (cache.lastY >= endY)
		{
			cache.destinationCacheX = cache.destinationCacheY = 0;
			cache.temppixelsX = cache.temppixelsY = 0;
			cache.lastY = cache.lastX = 0;
			cache.caching = false;
			blit = cache.bliterations;
		}
	}
}

void dx9Image::copyRectWithCache(int SourceImage,int Blit,bool enableMegaTexturing,int topleftX,int topleftY,int bottomrightX,int bottomrightY,int destinationX,int destinationY)
{
	cache.bliterations = Blit;
	if (!cache.caching)
	{
		int tempsizeX = destinationX + (bottomrightX - topleftX);
		int tempsizeY = destinationY + (bottomrightY - topleftY);
		if (!enableMegaTexturing)
		{
			if (tempsizeX > IMAGECACHE_WIDTH_MAX)
			{
				bottomrightX = bottomrightX - ( tempsizeX - IMAGECACHE_WIDTH_MAX);
			}
			if (tempsizeY > IMAGECACHE_HEIGHT_MAX)
			{
				bottomrightY = bottomrightY - ( tempsizeY - IMAGECACHE_HEIGHT_MAX);
			}
		}
		destX = destinationX;
		destY = destinationY;
		cache.destinationCacheX = destX;
		cache.destinationCacheY = destY;
		cache.lastX = topleftX;
		cache.lastY = topleftY;
		cache.image.startX = topleftX;
		cache.image.startY = topleftY;
		cache.image.endX = bottomrightX;
		cache.image.endY = bottomrightY;
		cache.caching = true;
		setTempSurface(SourceImage,1);
	}
	useCache(cache.image.startX,cache.image.startY,cache.image.endX,cache.image.endY);
}

void dx9Image::copyRectWithCache(int SourceImage,int Blit)
{
	cache.bliterations = Blit;
	if (!cache.caching)
	{
		cache.image.startX = 0;
		cache.image.startY = 0;
		cache.image.endX = IMAGECACHE_WIDTH_MAX;
		cache.image.endY = IMAGECACHE_HEIGHT_MAX;
		destX = 0;
		destY = 0;
		cache.destinationCacheX = destX;
		cache.destinationCacheY = destY;
		cache.lastX = 0;
		cache.lastY = 0;
		cache.caching = true;
		setTempSurface(SourceImage,1);
	}
	useCache(cache.image.startX,cache.image.startY,cache.image.endX,cache.image.endY);
}

void dx9Image::fillColor(int startX,int startY,int endX,int endY,DWORD color)
{
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y< endY; y++)
		{
			putPixel(x,y,color);
		}
	}
}

void dx9Image::fillColorWithCache(int startX,int startY,int endX,int endY,int Blit,DWORD color)
{
	cache.bliterations = Blit;
	if (!cache.caching)
	{
		cA = (int)((color & 0xFF000000) >> 24);	//RgbA
		cR = (int)((color & 0x00FF0000) >> 16);	//RgbR
		cG = (int)((color & 0x0000FF00) >> 8);	//RgbG 
		cB = (int)((color & 0x000000FF) );		//RgbB

		destX = 0;
		destY = 0;
		cache.destinationCacheX = destX;
		cache.destinationCacheY = destY;
		cache.image.startX =0;
		cache.image.startY = 0;
		cache.image.endX = IMAGECACHE_WIDTH_MAX;
		cache.image.endY = IMAGECACHE_HEIGHT_MAX;
		cache.caching = true;
	}
	useCache(cache.image.startX,cache.image.startY,cache.image.endX,cache.image.endY,D3DCOLOR_ARGB(cA,cR,cG,cB));
}

int dx9Image::GetMemOffset(int format) {

	switch(format) {

		case D3DFMT_R3G3B2:
		case D3DFMT_A8:
			return 1;

		case D3DFMT_R5G6B5:
		case D3DFMT_X1R5G5B5:
		case D3DFMT_A1R5G5B5:
		case D3DFMT_A4R4G4B4:
		case D3DFMT_A8R3G3B2:
		case D3DFMT_X4R4G4B4:
			return 2;

		case D3DFMT_R8G8B8:
			return 3;

		case D3DFMT_A8R8G8B8:
		case D3DFMT_X8R8G8B8:
		case D3DFMT_A8B8G8R8:
		case D3DFMT_X8B8G8R8:
		case D3DFMT_A2B10G10R10:
		case D3DFMT_G16R16:
		case D3DFMT_A2R10G10B10:
			return 4;
	}
	return 0;
}



void dx9Image::drawLine(int x1, int y1, int x2, int y2, DWORD color) 
{
	int dmem_loc;

	int u = 0;
    int dx, dy, c, M, xinc = 1, yinc = 1;
	int hits=0;
    int x3 = x1;
    int y3 = y1;
    dx = x2 - x1;
    dy = y2 - y1;

    if (dx < 0) { xinc = -1; dx = -dx; }
    if (dy < 0) { yinc = -1; dy = -dy; }

    if (dy < dx) {
        c = 2 * dx; 
		M = 2 * dy;

        while (x3 != x2) {
			if (x3 >= 0 && x3 < w-1 && y3 >= 0 && y3 < h-1) {
				dmem_loc = (x3 * b) + ((y3) * DestRect.Pitch);
				*(DWORD*)(DestAddr + dmem_loc) = color;
			}

            x3 += xinc; 
			u += M;

            if (u > dx) { y3 += yinc; u -= c; }
        }

    } else {
        c = 2 * dy; 
		M = 2 * dx;

        while(y3 != y2) {
			if (x3 >= 0 && x3 < w-1 && y3 >= 0 && y3 < h-1) {
				dmem_loc = (x3 * b) + ((y3) * DestRect.Pitch);
				*(DWORD*)(DestAddr + dmem_loc) = color;
			}

            y3 += yinc; 
			u += M;

            if(u > dy) { x3 += xinc; u -= c; }
        }
    }


	if (x3 >= 0 && x3 < w-1 && y3 >= 0 && y3 < h-1) {
		dmem_loc = (x3 * b) + ((y3) * DestRect.Pitch);
		*(DWORD*)(DestAddr + dmem_loc) = color;
	}
}

void dx9Image::circlePoints(int cx, int cy, int x, int y, DWORD c)
{

	if (x == 0) {
		putPixel( cx, cy + y,c);
		putPixel( cx, cy - y,c);
		putPixel( cx + y, cy,c);
		putPixel( cx - y, cy,c);
	} else 
		if (x == y) {
			putPixel( cx + x, cy + y,c);
			putPixel( cx - x, cy + y,c);
			putPixel( cx + x, cy - y,c);
			putPixel( cx - x, cy - y,c);
		} else 
			if (x < y) {
				putPixel( cx + x, cy + y,c);
				putPixel( cx - x, cy + y,c);
				putPixel( cx + x, cy - y,c);
				putPixel( cx - x, cy - y,c);
				putPixel( cx + y, cy + x,c);
				putPixel( cx - y, cy + x,c);
				putPixel( cx + y, cy - x,c);
				putPixel(cx - y, cy - x ,c);
			}
}

void dx9Image::drawCircle(int xCenter, int yCenter, int radius,DWORD c)
    {
        int x = 0;
        int y = radius;
        int p = (5 - radius*4)/4;

        circlePoints(xCenter, yCenter, x, y,c);
        while (x < y) {
            x++;
            if (p < 0) {
                p += 2*x+1;
            } else {
                y--;
                p += 2*(x-y)+1;
            }
            circlePoints(xCenter, yCenter, x, y,c);
        }
    }
void dx9Image::circleFill(int xc, int yc, int r,DWORD c)
{
	//Scan-Line Circle Fill Algorithm
	//Utilizing Cartesian-Coordinate

	float x1, x2;
	for (int y=yc-r; y<=yc+r; ++y)
	{
		float temp = SQR(r) - SQR(y-yc);
		x1 = floor(xc + sqrt(temp));
		x2 = floor(xc - sqrt(temp));
		drawLine((int)x1, y,(int) x2, y,c);
	}
}


void dx9Image::drawCircle(int CX, int CY, int R, DWORD c,int borderSize,bool fill,DWORD fColor) 
{     
	//drawCircle(CX,CY,R,c);
	// Slow Version of Border Size may need some tweaking
	// Works only with Fill
	if (borderSize > 1 && fill)
	{
		circleFill(CX,CY,R,c);
		circleFill(CX,CY,R-borderSize,fColor);
	}
	else
	if (fill)
	{
		circleFill(CX,CY,R,fColor);
	}
}

void dx9Image::drawBox(int startX,int startY,int endX,int endY,int borderSize, DWORD color,bool fill,DWORD fColor)
{
	int t = 0;
	if (borderSize <= 0)
	{
		borderSize = 1;
	}
	for (int i = 0; i < borderSize; i++)
	{
		drawLine(startX,startY + i,endX,startY + i,color);	// topleft - topright
		drawLine(endX + i,startY,endX + i,endY+borderSize,color);		// topright - bottomright
		drawLine(endX,endY + i,startX,endY + i,color);		// bottomright - bottomleft
		drawLine(startX + i,endY,startX + i,startY,color);	// bottomleft - topleft (closed)
	}
	
	if (fill)
	{
		fillColor(startX + borderSize-1, startY + borderSize-1,endX,endY,fColor);
	}

}

void dx9Image::drawBox(int startX,int startY,int endX,int endY,DWORD color1,DWORD color2,DWORD color3,DWORD color4,bool fill,DWORD fColor)
{
	drawLine(startX,startY,endX,startY,color1);	// topleft - topright
	drawLine(endX,startY,endX,endY,color2);		// topright - bottomright
	drawLine(endX,endY,startX,endY,color3);		// bottomright - bottomleft
	drawLine(startX,endY,startX,startY,color4);	// bottomleft - topleft (closed)

	if (fill)
	{
		fillColor(startX+1,startY+1,endX-1,endY-1,fColor);
	}
}

void dx9Image::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, DWORD color, bool fill, DWORD fColor)
{
	drawLine(x1,y1,x2,y2,color);
	drawLine(x2,y2,x3,y3,color);
	drawLine(x3,y3,x1,y1,color);

	if (fill)
	{

	}
}
