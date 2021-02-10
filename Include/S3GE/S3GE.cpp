/*
 DarkGDK Open Source Project-Trio
  ______ ______  _______ _______ 
 / _____|_____ \(_______|_______)
( (____  _____) )_   ___ _____   
 \____ \(_____ (| | (_  |  ___)  
 _____) )_____) ) |___) | |_____ 
(______/(______/ \_____/|_______)
Super   3D      Game    Engine
Enhancement Lib
                             
This program is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
Lesser GNU General Public License for more details.

You should have received a copy of the Lesser GNU General Public License
along with this program. if(not, see http://www.gnu.org/licenses/.
*/

#include "S3GE.h"

// GENERAL //////////////////////////////////////////////////////////////////////////////////////////

int S3GE::Text::CurrentFontID = 0;
S3GE::Text::Font *S3GE::Text::CurrentFont = NULL;

//initialize Global var
S3GE::System *Core = new S3GE::System;

// TEXT::FONT //////////////////////////////////////////////////////////////////////////////////////////

map<int,S3GE::Text::Font*> S3GE::Text::Font::IDMap;
map<int,S3GE::Text::Font*>::iterator S3GE::Text::Font::IDMapIterator;
map<string,int> S3GE::Text::Font::NameMap;
map<string,int>::iterator S3GE::Text::Font::NameMapIterator;

/**
* @brief	Constructor
* @param	void
*/
S3GE::Text::Font::Font(void){
		
	ID3DXFont* FontInterface = NULL;
	LPSTR Face = "Arial";
	Size = 12;			//g_FontSize
	BoldFlag = false;	//g_Bold
	ItalicFlag = false;	//g_Italic
	Red = 255;			//g_nRed
	Green = 255;		//g_nGreen
	Blue = 255;			//g_nBlue
	Alpha = 255;		//g_nAlpha

}

/**
* @brief	Destructor
* @param	void
*/
S3GE::Text::Font::~Font(void){

}

/**
* @brief	return total width of characters based on average
* @param	void
* @return	int
*/
int S3GE::Text::Font::WidthGet(string text){

	SIZE size;
	GetTextExtentPoint32(FontInterface->GetDC(), (char*)text.data(), text.size(), &size); 
	return(size.cx);
}

/**
* @brief	return total width
*
* @param	void
*
* @return	int
*/
int S3GE::Text::Font::HeightGet(string text){

	return(Metrics.tmHeight);
}

// TEXT //////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
* @return	void
*/
S3GE::Text::Text(void){

	Red = 255;					//g_nRed
	Green = 255;				//g_nGreen
	Blue = 255;					//g_nBlue
	Alpha = 255;				//g_nAlpha
	//Device = NULL;			//g_pd3dDevice
	//SpriteInterface = NULL;	//g_pTextSprite

}

/**
* @brief	Destructor
* @param	void
* @return	void
*/
S3GE::Text::~Text(void){

}

/**
* @brief	Initialize
* @param	void
* @return	void
*/
void S3GE::Text::Start(void){

	//Device = dbGetDirect3DDevice();
}

/**
* @brief	Shutdown
* @param	void
* @return	void
*/
void S3GE::Text::Stop(void){

	//iterate thru all fonts and delete

}

/**
* @brief	create font
* @param	void
* @return	void
*/
void S3GE::Text::FontCreate(int fontID, LPSTR face, int size, bool boldflag, bool italicflag, int red, int green, int blue, int alpha){

    if(!fontID) return;

	Text::Font *Font = new Text::Font;
	Font->Face = face;
	Font->Size = size;
	Font->BoldFlag = boldflag;
	Font->ItalicFlag = italicflag;
	Font->Red = red;
	Font->Green = green;
	Font->Blue = blue;
	Font->Alpha = alpha;

	HDC hDC = GetDC(NULL);
    int LogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

    D3DXCreateFont(								// return(HRESULT WINAPI)
		Core->Device,							// LPDIRECT3DDEVICE9 pDevice - A pointer to your Direct3D Device.
		-size * LogPixelsY / 72,				// unsigned int Height - The height (in pixels) of the font you want to create. 
		0,										// unsigned int Width - The width (in pixels) of the font you want to create. Set this to 0 for default width based on the height you gave above.
		Font->BoldFlag ? FW_BOLD : FW_NORMAL,	// unsigned int Weight - How thick the font is. Valid values range from 0-1,000. Common flags and their numeric values are: * FW_THIN(100), * FW_NORMAL(400), * FW_BOLD(700), * FW_HEAVY(900) 
		1,										// unsigned int MipLevels, Number of MipMaps to create. 0 creates a full chain. Used to show the font at different sizes more efficiently. Since we won't be scaling our text, we use 1 to save memory.
		Font->ItalicFlag,						// BOOL Italic - True/False, do you want Italics?
		DEFAULT_CHARSET,						// DWORD CharSet - Character Set. Used to specify international character sets (Arabic, Greek, etc), just set it to DEFAULT_CHARSET.
		OUT_DEFAULT_PRECIS,						// DWORD OutputPrecision - How precisely the output must match the font. You can probably just leave this as OUT_DEFAULT_PRECIS.
		DEFAULT_QUALITY,						// DWORD Quality - Some possible values are: ANTIALIASED_QUALITY, DEFAULT_QUALITY, DRAFT_QUALITY, and PROOF_QUALITY. 
		DEFAULT_PITCH | FF_DONTCARE,			// DWORD PitchAndFamily - You can safely set this to DEFAULT_PITCH|FF_DONTCARE. 
		face,									// LPCTSTR pFaceName - The name of the font you want. You can set this to an empty string ("") and let it pick a font for you that matches the other parameters. 
		&Font->FontInterface					// LPD3DXFONT *ppFont - 
	); 

	Font->FontInterface->PreloadGlyphs(32,180);
	Font->FontInterface->GetTextMetrics(&Font->Metrics);

	/*
	if (Core->SpriteInterface == NULL){
		D3DXCreateSprite( Core->Device, &Core->SpriteInterface );
	}
*/

	Font::IDMap[fontID] = Font;
	FontSet(fontID);

}

/**
* @brief	createfont w autogenerated ID
* @param	void
* @return	void
*/
int S3GE::Text::FontCreate(LPSTR face, int size, bool boldflag, bool italicflag, int red=255, int green=255, int blue=255, int alpha=255){

	int fontID = S3GETextFontResource->Pop();
	FontCreate(fontID, face, size, boldflag, italicflag, red, green, blue, alpha);
	return(fontID);
}

/**
* @brief	Create Font with Auto-generated ID
* @param	void
* @return	void
*/
int S3GE::Text::FontCreate(string name, LPSTR face, int size, bool boldflag, bool italicflag, int red=255, int green=255, int blue=255, int alpha=255){

	int fontID = S3GETextFontResource->Pop();
	FontCreate(fontID, face, size, boldflag, italicflag, red, green, blue, alpha);
	Font::NameMap[name] = fontID;
	return(fontID);
}

/**
* @brief	Destroy and release resources
* @param	void
* @return	void
*/
void S3GE::Text::FontDestroy(int fontID){

	if(Font::IDMap[fontID] != NULL){
		//free up dx resource
		Font::IDMap[fontID]->FontInterface->OnLostDevice();
		delete Font::IDMap[fontID];
		Font::IDMap[fontID] = NULL;
		S3GETextFontResource->Push(fontID);
	}
}

/**
* @brief	set CurrentFontID to fontID and reset color;
* @param	void
* @return	void
*/
void S3GE::Text::FontSet(int fontID){

	CurrentFontID = fontID; 
	CurrentFont = Font::IDMap[fontID];
	ColorSet();
}

/**
* @brief	set CurrentFontID to fontID and reset color;
* @param	void
* @return	void
*/
int S3GE::Text::FontGet(string name){

	return(Font::NameMap[name]);
}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Text::ColorSet(BYTE red, BYTE green, BYTE blue, BYTE alpha){

	Red = red;
	Green = green;
	Blue = blue;
	Alpha = alpha;

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Text::ColorSet(DWORD color){

	Red =	(int)((color & 0x00FF0000) >> 16);
	Green =	(int)((color & 0x0000FF00) >> 8);
	Blue =	(int)((color & 0x000000FF) );
	Alpha = (int)((color & 0xFF000000) >> 24);

}


/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Text::ColorSet(int fontID){

	Red = Font::IDMap[fontID]->Red;
	Green = Font::IDMap[fontID]->Green;
	Blue = Font::IDMap[fontID]->Blue;
	Alpha = Font::IDMap[fontID]->Alpha;

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Text::ColorSet(void){

	ColorSet(CurrentFontID);

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Text::Begin(void){

	Core->SpriteInterface->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
}

/**
* @brief	
* @param	void
* @return	void
*/	
void S3GE::Text::End(void){

	Core->SpriteInterface->End();
}

/**
* @brief	Base Drawing Function.
* @param	void
* @return	void
*/
void S3GE::Text::Draw(int fontID, int left, int top, int right, int bottom, DWORD align, LPSTR string){

    if(!fontID) return;

    RECT rect;
	
	SetRect(		//Note: RECT structure stores the coordinate for the right and bottom extent. Top and Left extents are inclusive. Bottom and Right extents are exclusive.
		&rect,	//struct RECT{
		left,		//int left
		top,		//int top
		right,		//int right
		bottom		//int bottom
	);

	Font::IDMap[fontID]->FontInterface->DrawText(						//return(int fontheight)
							Core->SpriteInterface,						//LPD3DXSPRITE pSprite - A pointer to a ID3DXSprite interface. Used for advanced batching and optimization. Set it to NULL for now.
							string,										//LPCTSTR String - The string you want to render.
							-1,											//int Count - The number of characters you want to render. If you want to render the entire string, and the string is NULL terminated, you can just pass -1. 
							&rect,										// LPRECT pRect - Formatting and Clipping rectangle. Used to position and format your text. 
							DT_NOCLIP|align,							// DWORD Format - Flags to specify text alignment, clipping and many other things. Definition Reference: http://msdn.microsoft.com/en-us/library/ms901121.aspx
							D3DCOLOR_ARGB( Alpha, Red, Green, Blue )	//D3DCOLOR Color - Standard 32-bit ARGB colour. Note: The alpha channel is respected for transparency. If you set the alpha to 0 you will not see your text. 
						);


}

/**
* @brief	Draw Alias
* @param	
* @return	void
*/
void S3GE::Text::Draw(LONG left, LONG top, LONG right, LONG bottom, DWORD align, LPSTR string){

	Draw(CurrentFontID, left, top, right, bottom, align, string);
}

/**
* @brief	Draw Alias
* @param	void
* @param	LONG left
* @param	LONG top
* @param	LONG right
* @param	LONG bottom
* @param	LPSTR string
* @return	void
*/
void S3GE::Text::Draw(LONG left, LONG top, LONG right, LONG bottom, LPSTR string){

	Draw(CurrentFontID, left, top, right, bottom, DT_LEFT, string);
}

/**
* @brief	
* @param	int fontID
* @param	int x
* @param	int y
* @param	DWORD align
* @param	LPSTR string
* @return	void
*/
void S3GE::Text::Draw(int fontID, int x, int y, DWORD align, LPSTR string){

	Draw(fontID, x, y, dbScreenWidth(), dbScreenHeight(), align, string);

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Text::Draw(int x, int y, DWORD align, LPSTR string){

	Draw(CurrentFontID, x, y, dbScreenWidth(), dbScreenHeight(), align, string);
}

/**
* @brief	Print Text to Screen
* @param	void
* @return	void
*/
void S3GE::Text::Print(int x, int y, LPSTR string){

	Begin();
	Draw(CurrentFontID, x, y, dbScreenWidth(), dbScreenHeight(), DT_LEFT, string);
	End();
}

/**
* @brief	Print To Screen
* @param	void
* @return	void
*/
void S3GE::Text::Print(int fontID, int x, int y, DWORD align, DWORD color, LPSTR string){

	Begin();
	ColorSet(color);
	Draw(fontID, x, y, dbScreenWidth(), dbScreenHeight(), align, string);
	End();
}

/**
* @brief	return total width of characters based on average
* @param	void
* @return	void
*/
int S3GE::Text::WidthGet(string text){

	SIZE size;
	GetTextExtentPoint32(CurrentFont->FontInterface->GetDC(), (char*)text.data(), text.size(), &size); 
	return(size.cx);
}

/**
* @brief	return total width
* @param	string text
* @return	void
*/
int S3GE::Text::HeightGet(string text){

	return(CurrentFont->Metrics.tmHeight);
}

// IMAGE //////////////////////////////////////////////////////////////////////////////////////////

map<int,S3GE::Image*> S3GE::Image::IDMap;
map<int,S3GE::Image*>::iterator S3GE::Image::IDMapIterator;

list<S3GE::Image*> S3GE::Image::ActiveList;
list<S3GE::Image*>::iterator S3GE::Image::ActiveListIterator;
queue<S3GE::Image*> S3GE::Image::InactiveQueue;

/**
* @brief	Image Constructor
* @param	void
*/
S3GE::Image::Image(void){

	Surface = NULL;
	DepthStencilSurface = NULL;
	Type = S3GE_IMAGE_TYPE_STATIC;
	Shared = 0;
	HTTPFile = NULL;
	State = IDLE;
}

/**
* @brief	Image Destructor
* @param	void
*/
S3GE::Image::~Image(void){

}

/**
* @brief	Sets Render-Target Image Surface based on imageID
* @param	void
* @return	void
*/
void S3GE::Image::Set(int imageID){

	if(IDMap[imageID]) Core->Device->SetRenderTarget(0,IDMap[imageID]->Surface);

	/*
	{ 
		if(IDMap[imageID]->Type == S3GE_IMAGE_TYPE_RENDERTARGET) Core->Device->SetRenderTarget(0,IDMap[imageID]->Surface);
	}
*/
}

/**
* @brief	Returns Pointer to Image based imageID
* @param	void
* @return	void
*/
S3GE::Image *S3GE::Image::Get(int imageID){

	return(IDMap[imageID]);
}

/**
* @brief	Resets Render-Target to System Backbuffer
* @param	void
* @return	void
*/
void S3GE::Image::Reset(void){

	Core->Device->SetRenderTarget(0,Core->BackBuffer); 

}


/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::Lock(void){

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::Unlock(void){

}

/**
* @brief	Creates 
* @param	void
* @return	void
*/
void S3GE::Image::Create(int imageID, int type, string filename, DWORD loadoptionbitflag, int width, int height){

	//if filename and fileexists continue else return

	if(!filename.empty()) {

		switch(int fileexists = Core->File->Exist(filename, loadoptionbitflag)){	

			case S3GE_FILE_FOUND:
				break;

			case S3GE_FILE_NOTFOUND:
				filename.append(" could not be opened!");
				alertbox("S3GE::Image",filename,ALERTBOX_SEVERITY_ERROR);
				return;

			default:
				HTTPFile = S3GE::File::HTTPFileMap[fileexists];
				
				//destroy any previous images using the ID
				if(IDMap[imageID] != NULL) Destroy(imageID);

				//create new Image
				Image *instance = new Image;
				instance->Type = type;

				State = DOWNLOADING;
				ActiveList.push_back(instance);
				return;

		}
	}

	//destroy any previous images using the ID
	if(IDMap[imageID] != NULL) Destroy(imageID);

	//create new Image
	Image *instance = new Image;
	instance->Type = type;

	//get image dimensions
	if(!filename.empty()) {
		D3DXGetImageInfoFromFile( (LPCTSTR)filename.data(), &instance->ImageInfo );
		width = instance->ImageInfo.Width;
		height = instance->ImageInfo.Height;
	}

	//validate size
	if (width < 1) width = S3GE_IMAGE_WIDTH_MAX;
	if (height < 1) height = S3GE_IMAGE_HEIGHT_MAX;

	//select and create surface type using DGDK
	switch(type){

		case S3GE_IMAGE_TYPE_STATIC:
			dbMakeImageUsage(imageID, width, height, 0)->GetSurfaceLevel(0, &instance->Surface); //Managed Texture
			break;
		
		case S3GE_IMAGE_TYPE_RENDERTARGET:
			dbMakeImageRenderTarget(imageID, width, height, D3DFMT_A8R8G8B8)->GetSurfaceLevel(0, &instance->Surface); //D3DFMT_A1R5G5B5(Depth = 16), D3DFMT_A8R8G8B8(Depth = 32);
			break;

		case S3GE_IMAGE_TYPE_DYNAMIC:
			dbMakeImageUsage(imageID, width, height, D3DUSAGE_RENDERTARGET)->GetSurfaceLevel(0, &instance->Surface); //D3DUSAGE_DYNAMIC
			break;

		case S3GE_IMAGE_TYPE_OFFSCREEN:
			dbMakeImage(imageID, width, height)->GetSurfaceLevel(0, &instance->Surface);
			Core->Device->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8 , D3DPOOL_DEFAULT, &instance->Surface, NULL); //D3DFMT_A8R8G8B8
			break;
	}

	//load image file from local
	if(!filename.empty()){
		D3DXLoadSurfaceFromFile(instance->Surface, NULL, NULL, (LPCTSTR)filename.data(), NULL, D3DX_DEFAULT, 0, NULL);
	} else {
		//clean surface to black
		RECT rect = { 0, 0, width, height };
		Core->Device->ColorFill(instance->Surface, &rect, D3DCOLOR_ARGB(0,0,0,0) );
	}

	//get surface description
	instance->Surface->GetDesc(&instance->SurfaceDesc);
	
	//create depth stencil surface
	//CreateDepthStencilSurface(width, height, GetValidStencilBufferFormat(CommonFormat), D3DMULTISAMPLE_NONE, 0, TRUE, &DepthStencilSurface, NULL );

	//Set ID Map Pointer
	IDMap[imageID] = instance;
	ActiveList.push_back(instance);
}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::Destroy(int imageID){

	Image *instance = IDMap[imageID];

	//release DX resources
	if(instance->Surface != NULL) instance->Surface->Release();
	
	delete instance;

}


/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::Destroy(Image *instance){

	//release DX resources
	if(instance->Surface != NULL) instance->Surface->Release();
	
	delete instance;

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::Update(void){

	//iterate through active Images
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
			(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive Images
	while (!InactiveQueue.empty()){
		ActiveList.remove(InactiveQueue.front());
		Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}
}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::Process(void){

	switch(State){

			case IDLE:
				break;

			case DOWNLOADING:

				//download completed
				if(HTTPFile->State == S3GE::File::COMPLETE){
					/*
					//destroy any previous images using the ID
					if(IDMap[imageID] != NULL) Destroy(imageID);

					//create new Image
					Image *instance = new Image;
					instance->Type = type;

					//load image to surface
					if(!filename.empty()) {
						D3DXGetImageInfoFromFile( (LPCTSTR)filename.data(), &instance->ImageInfo );
						width = instance->ImageInfo.Width;
						height = instance->ImageInfo.Height;
					}

					//validate size
					if (width < 1) width = S3GE_IMAGE_WIDTH_MAX;
					if (height < 1) height = S3GE_IMAGE_HEIGHT_MAX;

					//select and create surface type
					switch(type){

						case S3GE_IMAGE_TYPE_STATIC:
							dbMakeImageUsage(imageID, width, height, 0)->GetSurfaceLevel(0, &instance->Surface); //Managed Texture
							break;
						
						case S3GE_IMAGE_TYPE_RENDERTARGET:
							dbMakeImageRenderTarget(imageID, width, height, D3DFMT_A8R8G8B8)->GetSurfaceLevel(0, &instance->Surface); //D3DFMT_A1R5G5B5(Depth = 16), D3DFMT_A8R8G8B8(Depth = 32);
							break;

						case S3GE_IMAGE_TYPE_DYNAMIC:
							dbMakeImageUsage(imageID, width, height, D3DUSAGE_RENDERTARGET)->GetSurfaceLevel(0, &instance->Surface); //D3DUSAGE_DYNAMIC
							break;

						case S3GE_IMAGE_TYPE_OFFSCREEN:
							dbMakeImage(imageID, width, height)->GetSurfaceLevel(0, &instance->Surface);
							Core->Device->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8 , D3DPOOL_DEFAULT, &instance->Surface, NULL); //D3DFMT_A8R8G8B8
							break;
					}

					//load file
					if(!filename.empty()){
						D3DXLoadSurfaceFromFile(instance->Surface, NULL, NULL, (LPCTSTR)filename.data(), NULL, D3DX_DEFAULT, 0, NULL);
					} else {
						//clean surface to black
						RECT rect = { 0, 0, width, height };
						Core->Device->ColorFill(instance->Surface, &rect, D3DCOLOR_ARGB(0,0,0,0) );
					}

					//get surface description
					instance->Surface->GetDesc(&instance->SurfaceDesc);
					
					//create depth stencil surface
					//CreateDepthStencilSurface(width, height, GetValidStencilBufferFormat(CommonFormat), D3DMULTISAMPLE_NONE, 0, TRUE, &DepthStencilSurface, NULL );

					//Set ID Map Pointer
					IDMap[imageID] = instance;
				*/
				}
				break;

	}

}

/**
* @brief	
*
* @param	void
*
* @return	void
*/
void S3GE::Image::ProcessNow(void){

	//while(HTTP->State != DarkNet::PALM::TERMINATE){
	while(State != COMPLETE){
		Process(); 
	}
}


/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::RectCopy(int sourceimageID, int sourcex, int sourcey, int sourcewidth, int sourceheight, int destimageID, int destx, int desty){

	//validate IDs
	if(IDMap[sourceimageID]==NULL||IDMap[destimageID]==NULL) return;

	//validate RT to RT
	if(IDMap[sourceimageID]->Type != S3GE_IMAGE_TYPE_RENDERTARGET || IDMap[destimageID]->Type != S3GE_IMAGE_TYPE_RENDERTARGET) return;	

	Image *sourceimage = IDMap[sourceimageID];
	Image *destimage = IDMap[destimageID];

	if(sourcex < 0) sourcex = 0;
	if(sourcex > sourceimage->SurfaceDesc.Width) sourcex = sourceimage->SurfaceDesc.Width;
	if(sourcey < 0) sourcey = 0;
	if(sourcey > sourceimage->SurfaceDesc.Height) sourcey = sourceimage->SurfaceDesc.Height;
	if(sourcex + sourcewidth < 1) sourcewidth = 1;
	if(sourcex + sourcewidth > sourceimage->SurfaceDesc.Width) sourcewidth = (sourcex + sourcewidth) - sourceimage->SurfaceDesc.Width;
	if(sourcey + sourceheight < 1) sourceheight = 1;
	if(sourcey + sourceheight > sourceimage->SurfaceDesc.Height) sourceheight = (sourcey + sourceheight) - sourceimage->SurfaceDesc.Height;

	RECT sourcerect = {sourcex, sourcey, sourcex + sourcewidth, sourcey + sourceheight}; //source rect

	if(destx < 0) destx = 0;
	if(destx > destimage->SurfaceDesc.Width) destx = destimage->SurfaceDesc.Width;
	if(desty < 0) desty = 0;
	if(desty > destimage->SurfaceDesc.Height) desty = destimage->SurfaceDesc.Height;
	if(destx + sourcewidth < 1) sourcewidth = 1;
	if(destx + sourcewidth > destimage->SurfaceDesc.Width) sourcewidth = (destx + sourcewidth) - destimage->SurfaceDesc.Width;
	if(desty + sourceheight < 1) sourceheight = 1;
	if(desty + sourceheight > destimage->SurfaceDesc.Height) sourceheight = (desty + sourceheight) - destimage->SurfaceDesc.Height;
	
	RECT destrect = {destx, desty, destx + sourcewidth, desty + sourceheight}; //dest rect

	Core->Device->StretchRect(sourceimage->Surface, &sourcerect, destimage->Surface, &destrect, D3DTEXF_NONE);

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::RectCreate(int sourceimageID, int destimageID){

	if(IDMap[sourceimageID]==NULL) return;

	Image *sourceimage = IDMap[sourceimageID];
	//Create(destimageID, S3GE_IMAGE_TYPE_RENDERTARGET, "" , sourceimage->SurfaceDesc.Width, sourceimage->SurfaceDesc.Height);
	Create(destimageID, S3GE_IMAGE_TYPE_RENDERTARGET, "" , 0, sourceimage->SurfaceDesc.Width, sourceimage->SurfaceDesc.Height);
	RectCopy(sourceimageID, 0, 0, sourceimage->SurfaceDesc.Width, sourceimage->SurfaceDesc.Height, destimageID, 0,0);

}


/**
* @brief	Creates image from Source Image
* @param	void
* @return	void
*/
void S3GE::Image::RectCreate(int sourceimageID, int sourcex, int sourcey, int sourcewidth, int sourceheight, int destimageID){

	if(IDMap[sourceimageID]==NULL) return;

	Create(destimageID, S3GE_IMAGE_TYPE_RENDERTARGET, "", sourcewidth, sourceheight);
	RectCopy(sourceimageID, sourcex, sourcey, sourcewidth, sourceheight, destimageID, 0,0);

}

/**
* @brief	Crops Image
* @param	void
* @return	void
*/
void S3GE::Image::RectCrop(int sourceimageID, int sourcex, int sourcey, int sourcewidth, int sourceheight){

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::TextDraw(int FontID, int x, int y, DWORD Align, LPSTR String){



}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::TextDraw(int x, int y, DWORD Align, LPSTR String){
}

/**
* @brief	
* @param	void
* @param	
* @return	void
*/
void S3GE::Image::TextDraw(int x, int y, LPSTR String){

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::PixelDraw(int x, int y, DWORD color){

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::LineDraw(int top, int left, int right, int bottom, DWORD color ){//http://msdn.microsoft.com/en-us/library/bb174699(VS.85).aspx

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::BoxDraw(int top, int left, int right, int bottom, DWORD color, bool fillflag){

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::EllipseDraw(DWORD color, bool fillflag){

}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::PolygonDraw(POINT **point, DWORD color, bool fillflag){


}

/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::Image::CurveDraw(DWORD color, bool fillflag){ //bezier curves

}

/**
* @brief	
* @param	void
* @return	void
*/
int S3GE::Image::FormatOffsetGet(int format){

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

// FONTART //////////////////////////////////////////////////////////////////////////////////////////
S3GE::FontArt *S3GE::FontArt::CurrentFontArt = NULL;
map<string,S3GE::FontArt*> S3GE::FontArt::NameMap;
map<string,S3GE::FontArt*>::iterator S3GE::FontArt::NameMapiterator;

/**
* @brief	
* @param	void
* @return	void
*/
S3GE::FontArt::FontArt(void){
	
	dbImageID = 0;  
}


/**
* @brief	
* @param	void
* @return	void
*/
S3GE::FontArt::~FontArt(void){

	dbImageID = 0;
}


/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::FontArt::Start(void){

}


/**
* @brief	
* @param	void
* @return	void
*/
void S3GE::FontArt::Stop(void){

}

/** 	
* @brief	
* @param	string name
* @param	string filename
* @param	int kern	
* @return	S3GE::FontArt*
*/
S3GE::FontArt *S3GE::FontArt::Load(string name, string filename, int kern){

	switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

		case S3GE_FILE_FOUND:
			CurrentFontArt = new FontArt;
			CurrentFontArt->Name = name;
			CurrentFontArt->Filename = filename;
			CurrentFontArt->dbImageID = dbImageResource->Add(filename);
			CurrentFontArt->Kern = kern >> 1; //divide kern in half, capture characters x + kern/2, w - kern/2

			if(!dbImageExist(CurrentFontArt->dbImageID)){
				Core->Image->Create(CurrentFontArt->dbImageID, S3GE_IMAGE_TYPE_STATIC, filename, File::GET_FROM_LOCAL|File::GET_FROM_NETWORK);
			}

			//if(dbGetImageWidth(CurrentFontArt->dbImageID) < 640 || dbGetImageHeight(CurrentFontArt->dbImageID) < 640)
			
			CurrentFontArt->Slice(CurrentFontArt->Kern);
			
			//map to name
			NameMap[name] = CurrentFontArt;
			return(CurrentFontArt);
			break;	

	}

	return(NULL);
}

/** 	
* @brief	Slice FontArt Base Image into Individual Character Images
* @param	
* @return	
*/
void S3GE::FontArt::Slice(int kern){


	Size = dbGetImageWidth(dbImageID) / 10;
	int ascii = 32;
	for(int y = 0; y < 10; y++){
		for(int x = 0; x < 10; x++){
			CharacterMap[ascii] = new Character;
			//CharacterMap[ascii]->ascii = ascii;
			//CharacterMap[ascii]->height = Size;
			CharacterMap[ascii]->Capture(dbImageID, x * Size, y * Size, Size, Size, kern );
			ascii++;
		}
	}

	//set up space charactter
	CharacterMap[32]->Width = Size / 2;

}

// FONTART CHARACTER ////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	void
*/
S3GE::FontArt::Character::Character(void){

	//ascii = 0;
	dbImageID = 0;
	Width = 0;
	//height = 0;
	//FontArt = NULL;
}

/**
* @brief	Destructor	
* @param	void
*/
S3GE::FontArt::Character::~Character(void){

}


/**
* @brief	Captures and Trims FontArt Character Images
* @param	int fontartimageID
* @param	int xstart
* @param	int ystart
* @param	DWORD xsize
* @param	DWORD ysize
* @param	int kern
* @return	void
*/
void S3GE::FontArt::Character::Capture(int fontartimageID, int xstart, int ystart, DWORD xsize, DWORD ysize, int kern){

	if(!dbImageExist(fontartimageID)) return;

	Width = xsize;

	//rect
	S3GE::Image *fontimage = Core->Image->Get(fontartimageID);

	//trim
	int trimstartx = 0;
	int alpha = 0;

	D3DLOCKED_RECT lockedrect;
	fontimage->Surface->LockRect(&lockedrect, 0, 0); //&sourcerect

	//scan pixels vertically from left edge, rightward to find the alpha pixel > 0
	for(int pixelx = xstart; pixelx < xstart + xsize; pixelx++){
		for(int pixely = ystart; pixely < ystart + ysize; pixely+=1){//check y @ double pixel spacing
			alpha = (int)((*(DWORD*)((unsigned char*)lockedrect.pBits + (pixelx << 2) + (pixely * lockedrect.Pitch)) & 0xFF000000) >> 24);
			if(alpha){	
				trimstartx = pixelx;
				break;
			}
		}
		if(alpha) break;
	}

	//scan pixels vertically from right edge, leftward to find the alpha pixel > 0
	for(int pixelx = xstart + xsize; pixelx > xstart; pixelx--){
		for(int pixely = ystart; pixely < ystart + ysize; pixely+=1){
			alpha = (int)((*(DWORD*)((unsigned char*)lockedrect.pBits + (pixelx << 2) + (pixely * lockedrect.Pitch)) & 0xFF000000) >> 24);
			if(alpha){	
				Width = pixelx - trimstartx - kern;
				break;
			}
		}
		if(alpha) break;
	}

	fontimage->Surface->UnlockRect();

	//create rect
	dbImageID = dbImageResource->Pop();
	Core->Image->Create(dbImageID, S3GE_IMAGE_TYPE_RENDERTARGET, "", 0, Width, ysize);
	S3GE::Image *characterimage = Core->Image->Get(dbImageID);
	RECT sourcerect = { trimstartx + kern, ystart, trimstartx + Width, ystart + ysize};
	D3DXLoadSurfaceFromSurface(characterimage->Surface, NULL, NULL, fontimage->Surface, NULL, &sourcerect, D3DX_FILTER_NONE, 0xFF000000);
}

// FONTART TEXT ////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	Constructor
* @param	
*/
S3GE::FontArt::Text::Text(void){

	StaticFlag = false;
}

/**
* @brief	Destructor
* @param	
*/
S3GE::FontArt::Text::~Text(void){

}

/**	
* @brief	Create Text as Statice by default
* @param	
* @return	
*/
S3GE::FontArt::Text *S3GE::FontArt::Text::Create(string fontartname, string data, int kern){
	
	Text *instance = new Text;
	instance->Capture(fontartname, data, kern);

	return(instance);
}

/**	
* @brief	Wrapper Method. Assumes Current FontArt Set
* @param	
* @return	
*/
S3GE::FontArt::Text *S3GE::FontArt::Text::Create(string data){


	return(Create(CurrentFontArt->Name, data, 0));
}
/** 	
* @brief	
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Destroy( S3GE::FontArt::Text* text){

	for(text->SpriteListIterator = text->SpriteList.begin(); text->SpriteListIterator != text->SpriteList.end(); text->SpriteListIterator++ ){
		dbDeleteSprite((*text->SpriteListIterator));
		dbSpriteResource->Push((*text->SpriteListIterator));
	}

	text->SpriteList.clear();

	delete text;
}

/** 	
* @brief	Alters and Positions FontArt Text as Images at position/kern
			Used in drawing operations; Data not altered.
* @param	string fontartname
* @param	string data
* @param	int x
* @param	int y
* @param	int kern
* @param	string fontartname, string data, int x, int y, int kern
* @return	int Total Width
*/
int S3GE::FontArt::Text::Draw(string fontartname, string data, int x, int y, int kern){

	if(NameMap[fontartname]== NULL){
		fontartname == CurrentFontArt->Name;
	} 

	int ascii;

	//draw images
	for(int loop = 0; loop < data.length(); loop++){
		ascii = (int)*(unsigned char*)data.substr(loop,1).data();
		if (ascii != 32) dbPasteImage(NameMap[fontartname]->CharacterMap[ascii]->dbImageID, x, y, 1);
		x += NameMap[fontartname]->CharacterMap[ascii]->Width + kern;
	}

	return(x-kern);
}

/** 	
* @brief	Wrapper Method; Parameters Matched to dbText(). Alters and Positions FontArt Text as Images at position/kern
			Uses Current FontArt
* @param	
* @return	void
*/
int S3GE::FontArt::Text::Draw(int x, int y, string data){


	return(Draw(CurrentFontArt->Name, data, x, y, 0));

}

/** 	
* @brief	Wrapper Method; Draws FontArt Text as Images at position/kern using stored data
			Uses Current FontArt
* @param	
* @return	void
*/
int S3GE::FontArt::Text::Draw(int x, int y){

	return(Draw(CurrentFontArt->Name, this->Data, x, y, 0));

}

/**
 	
* @brief	Capture Single Text as Single Sprite
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Capture(string fontartname, string data, int kern){

	//destroy existing sprites
	for(SpriteListIterator = SpriteList.begin(); SpriteListIterator != SpriteList.end(); SpriteListIterator++ ){
		if(StaticFlag){
			//return image resources
			dbDeleteImage(dbSpriteImage((*SpriteListIterator)));
			dbImageResource->Push(dbSpriteImage((*SpriteListIterator)));
		}
		dbDeleteSprite((*SpriteListIterator));
		dbSpriteResource->Push((*SpriteListIterator));
	}
	SpriteList.clear();

	//setup image
	int fontartspriteID = 0;
	int fontartimageID = 0;

	//render to image
	fontartimageID = dbImageResource->Pop();	
	Core->Image->Create(fontartimageID, S3GE_IMAGE_TYPE_RENDERTARGET, "", 0, WidthGet(fontartname, data), NameMap[fontartname]->Size); 
	Core->Image->Set(fontartimageID);
	Draw(fontartname, data, 0, 0, kern);
	Core->Image->Reset();

	//create new sprite
	fontartspriteID = dbSpriteResource->Pop();
	dbSprite(fontartspriteID, 0, 0, fontartimageID);
	dbHideSprite(fontartspriteID);
	SpriteList.push_back(fontartspriteID);

	this->Data = data;

	StaticFlag = true;

}

/** 	
* @brief	Alters and Positions Dynamic FontArt Text 
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Alter(string fontartname, string data, int x, int y, int kern){

	if(NameMap[fontartname]== NULL){
		fontartname == CurrentFontArt->Name;
	} 

	//destroy existing sprites
	for(SpriteListIterator = SpriteList.begin(); SpriteListIterator != SpriteList.end(); SpriteListIterator++ ){
		if(StaticFlag){
			//return image resources
			dbDeleteImage(dbSpriteImage((*SpriteListIterator)));
			dbImageResource->Push(dbSpriteImage((*SpriteListIterator)));
		}
		dbDeleteSprite((*SpriteListIterator));
		dbSpriteResource->Push((*SpriteListIterator));
	}
	SpriteList.clear();

	int spriteID;
	Character *character = NULL;

	//create new sprites
	for(int loop = 0; loop < data.length(); loop++){
		character = NameMap[fontartname]->CharacterMap[(int)*(unsigned char*)data.substr(loop,1).data()];
		spriteID = dbSpriteResource->Pop();
		dbSprite(spriteID, x, y, character->dbImageID);
		x += character->Width + kern;
		SpriteList.push_back(spriteID);
		dbHideSprite(spriteID);
	}

	this->Data = data;

	StaticFlag = false;
}

/** 	
* @brief	Wrapper Method. Parameters Matched to dbText(). Alters and Positions Dynamic FontArt Text 
			Uses Current FontArt
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Alter(int x, int y, string data){

	Alter(CurrentFontArt->Name, data, x, y, 0);
}

/** 	
* @brief	Paste Static / Dynamic FontArt Text as Sprites at position/kern.
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Paste(int x, int y){


	for(SpriteListIterator = SpriteList.begin(); SpriteListIterator != SpriteList.end(); SpriteListIterator++ ){
		dbPasteSprite((*SpriteListIterator), dbSpriteX((*SpriteListIterator)) + x, dbSpriteY((*SpriteListIterator)) + y);
	}

}

/** 	
* @brief	
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Hide(void){

	for(SpriteListIterator = SpriteList.begin(); SpriteListIterator != SpriteList.end(); SpriteListIterator++ ){
		dbHideSprite((*SpriteListIterator));
	}
}

/** 	
* @brief	
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Show(void){


	for(SpriteListIterator = SpriteList.begin(); SpriteListIterator != SpriteList.end(); SpriteListIterator++ ){
		dbShowSprite((*SpriteListIterator));
	}

}

/** 	
* @brief	
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Size(int x, int y ){

}

/** 	
* @brief	
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Scale(int scale ){

}

/** 	
* @brief	
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Position(int x, int y ){

}

/** 	
* @brief	
* @param	
* @return	void
*/
void S3GE::FontArt::Text::Color(int red, int blue, int green){

}

/** 	
* @brief	Returns Static / Dynamic Text Width based on Images
* @param	
* @return	void
*/
int S3GE::FontArt::Text::WidthGet(string fontartname, string data){

	int width = 0;
	for(int loop = 0; loop < data.length(); loop++){
		width += dbGetImageWidth( NameMap[fontartname]->CharacterMap[(int)*(unsigned char*)data.substr(loop,1).data()]->dbImageID);
		//width +=  Core->Image->IDMap[ NameMap[fontartname]->CharacterMap[(int)*(unsigned char*)data.substr(loop,1).data()]->dbImageID ]->SurfaceDesc.Width;
	}
	return(width);
}

/** 	
* @brief	Wrapper Method; Parameters Matched to dbTextWidth().
			Uses Current FontArt
* @param	
* @return	void
*/
int S3GE::FontArt::Text::WidthGet(string data){

	return(WidthGet(CurrentFontArt->Name, data));
}

/** 	
* @brief	Returns cummalative sprite width
			Uses Current FontArt
* @param	
* @return	void
*/
int S3GE::FontArt::Text::WidthGet(void){

	int width = 0;

	//return cumulative sprite width
	for(SpriteListIterator = SpriteList.begin(); SpriteListIterator != SpriteList.end(); SpriteListIterator++ ){
		width += dbSpriteWidth((*SpriteListIterator));
	}	
	return(width);
}

/** 	
* @brief	Returns Static / Dynamic Text Height based on Sprites
			Uses Curent FontArt
* @param	
* @return	void
*/
int S3GE::FontArt::Text::HeightGet(string fontartname, string data){

	int height = 0;
	int ascii;

	for(int loop = 0; loop < data.length(); loop++){
		ascii = (int)*(unsigned char*)data.substr(loop,1).data();
		if(height < dbGetImageHeight( NameMap[fontartname]->CharacterMap[ascii]->dbImageID)){
			height = dbGetImageHeight( NameMap[fontartname]->CharacterMap[ascii]->dbImageID);
		}
	}

	return(height);
}


/** 	
* @brief	Wrapper Method; Parameters Matched to dbTextHeight().
			Uses Current FontArt
* @param	
* @return	void
*/
int S3GE::FontArt::Text::HeightGet(string data){


	return(HeightGet(CurrentFontArt->Name, data));
}


/** 	
* @brief	Return Tallest Character Height
			Uses Current FontArt
* @param	
* @return	void
*/
int S3GE::FontArt::Text::HeightGet(void){

	int height = 0;

	//return sprite height
	for(SpriteListIterator = SpriteList.begin(); SpriteListIterator != SpriteList.end(); SpriteListIterator++ ){
		if(height < dbSpriteHeight((*SpriteListIterator))){
			height = dbSpriteHeight((*SpriteListIterator));
		}
	}

	return(height);
}

// OBJECT //////////////////////////////////////////////////////////////////////////////////////////
map<string,int> S3GE::Object::NameMap;
map<string,int>::iterator S3GE::Object::NameMapIterator;
map<int,S3GE::Object*> S3GE::Object::IDMap;

/**
* @brief	S3GE Object Constructor
* @param	void
*/
S3GE::Object::Object(void){

	ID = Type = Renderer = 0;
	WireFlag = TransparentFlag = CullFlag= FilterFlag = LightFlag = FogFlag = AmbientFlag = HTTPFileID = 0;
	DWORD VisualBitflag = 0;

}

/**
* @brief	S3GE Object Destructor
* @param	void
*/
S3GE::Object::~Object(void){

}

/**
* @brief	Create 3D Object
* @param	int objecttype
* @param	string objectfilename
* @param	int objectID
* @return	Object*
*/
S3GE::Object *S3GE::Object::Create(int objecttype, string objectfilename, int objectID){

	Object *instance = new Object();

	if(objecttype != S3GE_OBJECT_TYPE_MESH){
		objectID == 0 ? instance->ID = dbObjectResource->Pop() : instance->ID = objectID;
	}

	float size = 0.05f; 

	switch(objecttype){

		case S3GE_OBJECT_TYPE_PRIMITIVE_PLANE:
			dbMakeObjectPlane(instance->ID,size,size);
			break;

		case S3GE_OBJECT_TYPE_PRIMITIVE_CUBE: //primitive
			dbMakeObjectCube(instance->ID,size);
			break;

		case S3GE_OBJECT_TYPE_PRIMITIVE_SPHERE:
			dbMakeObjectSphere(instance->ID,size);
			break;

		case S3GE_OBJECT_TYPE_PRIMITIVE_CONE:
			dbMakeObjectCone(instance->ID,size);
			break;

		case S3GE_OBJECT_TYPE_MESH:
			if(!objectfilename.empty()){
				
				switch(int fileexists = Core->File->Exist(objectfilename, File::GET_FROM_LOCAL | File::GET_FROM_NETWORK)){

					case S3GE_FILE_FOUND:
						objectID == 0 ? instance->ID = dbObjectResource->Add(objectfilename) : instance->ID = objectID;;
						if(!dbObjectExist(instance->ID)){
							dbLoadObject((char*)objectfilename.data(),instance->ID);
						}
						break;

					case S3GE_FILE_NOTFOUND:
						objectID == 0 ? instance->ID = dbObjectResource->Pop() : instance->ID = objectID;;
						if(!dbObjectExist(instance->ID)){
							dbMakeObjectPlane(instance->ID, 1.0, 1.0);
							dbSetObject(instance->ID, 1, 0, 0, 0, 0, 0, 0);
						}
						break;
					}
			}
			break;

	}

	IDMap[instance->ID] = instance;
	return(instance);
}

/**
* @brief	Destroy 3D Object
* @param	Object *instance
* @return	void
*/
void S3GE::Object::Destroy(Object *instance){

	delete instance;
}

// FILE //////////////////////////////////////////////////////////////////////////////////////////
ResourceManager *S3GE::File::HTTPFileResource = NULL;
map<int,S3GE::File*> S3GE::File::HTTPFileMap;

list<S3GE::File*> S3GE::File::ActiveList;
list<S3GE::File*>::iterator S3GE::File::ActiveListIterator;
queue<S3GE::File*> S3GE::File::InactiveQueue;

/**
* @brief	Verifies file exist, if not get file with a variety of local/remote loading options.
* @param	[in]string &filename 
* @param	[in]DWORD loadoptionbitflag (See enum LoadingOptions declaration in S3GE.h S3GE::File Class)
* @return	[out]int - S3GE_FILE_FOUND = 0, S3GE_FILE_NOTFOUND = -1, n = HTTPFileResource ID
*/
int S3GE::File::Exist(string &filename, DWORD loadoptionbitflag){


	if(!dbFileExist((char*)filename.data())){

		string readpath;

		if(loadoptionbitflag & File::GET_FROM_LOCAL){
			readpath = Core->ConfigPropertyGet("GameContentDirectory");
			readpath.append(filename);
			if(dbFileExist((char*)readpath.data())){
				filename = readpath;
				return(S3GE_FILE_FOUND);
			}
		}
	
		if(loadoptionbitflag & File::GET_FROM_NETWORK){
			//request file confirmation for net
			File *instance = Create(filename);
			if( loadoptionbitflag & File::CONTINUE_WHILE_LOADING){
				return(instance->HTTPFileID);
			} else {
				int fileexists = instance->ProcessNow();
				//Destroy HTTP Resource
				instance->Destroy();
				if(fileexists != S3GE_FILE_NOTFOUND) return(S3GE_FILE_FOUND);
			}
		}

		return(S3GE_FILE_NOTFOUND);

	}

	return(S3GE_FILE_FOUND);
}

/** 	
* @brief	Create HTTP File for file transfer
* @param	
* @return	void
*/
S3GE::File* S3GE::File::Create(string &filename){

	string readpath = Core->ConfigPropertyGet("HostServerContentDirectory");
	readpath.append(filename);

	string writepath = Core->ConfigPropertyGet("GameContentDirectory");
	writepath.append(filename);

	File *instance = new File;
	instance->HTTPFileID =  HTTPFileResource->Pop();	
	
	filename = writepath;
	instance->Filename = filename;

	//Create HTTP resource
	instance->HTTP = DarkNet::HTTP::FileGet(readpath, DARKNET_HTTP_METHOD_GET, Core->ConfigPropertyGet("HostServer"), (int)dbVal((char*)Core->ConfigPropertyGet("HostServerPort").data()), readpath, writepath, DARKNET_HTTP_TRANSFER_MODE_BINARY);
	HTTPFileMap[instance->HTTPFileID] = instance;
	
	ActiveList.push_back(instance);
	return(instance);

}

/** 	
* @brief	Destroy File
* @param	3GE::File *instance
* @return	void
*/
void S3GE::File::Destroy(S3GE::File *instance){

	instance->HTTP = NULL;
	HTTPFileMap[instance->HTTPFileID] = NULL;
	HTTPFileResource->Push(instance->HTTPFileID);
	delete instance;

}

/** 	
* @brief	Destroy File
* @param	
* @return	void
*/
void S3GE::File::Destroy(void){

	ActiveList.remove(this);
	Destroy(this);
}

/**
* @brief	Iterates through all Files to processed
* @param	
* @return	void
*/
void S3GE::File::Update(void){

	//iterate through active Files
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
			(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive Files
	while (!InactiveQueue.empty()){
		ActiveList.remove(InactiveQueue.front());
		Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}
}

/** 	
* @brief	Process File Transfer via HTTP
* @param	
* @return	void
*/
void S3GE::File::Process(void){


	if(HTTP->State == DarkNet::HTTP::TERMINATE){

		if(HTTP->Response.Code < 400){

			Output = "Download ";
			Output.append(HTTP->Response.WritePath);
			Output.append(" Complete!");

			switch(int fileexists = Exist(HTTP->Response.WritePath, File::GET_FROM_LOCAL)){

				case S3GE_FILE_FOUND:
					State = COMPLETE;
					Output = "Loading ";
					Output.append(HTTP->Response.WritePath);
					break;

				case S3GE_FILE_NOTFOUND:
					State = COMPLETE;
					InactiveQueue.push(this);
					HTTP->Response.WritePath.append(" could not be opened!");
					alertbox("S3GE::File",HTTP->Response.WritePath,ALERTBOX_SEVERITY_ERROR);
					break;

				}
		
		} else {
		
			State = IDLE;
			InactiveQueue.push(this);
			HTTP->Response.WritePath.append(" Download Error! Response Code: ");
			HTTP->Response.WritePath.append(dbStr(HTTP->Response.Code));
			alertbox("S3GE::File",HTTP->Response.WritePath,ALERTBOX_SEVERITY_ERROR);
		}

	} else {

		Output = "Downloading ";
		Output.append(HTTP->Response.WritePath);
		Output.append(" Bytes:");
		Output.append(dbStr(HTTP->Response.BytesLoaded));

	}

}

/**
* @brief	HTTP Transaction Process Method. Process Immediately HTTP Object based on Transaction State
* @param	void
* @return	[out]int 1=Good, -1=Error  
*/
int S3GE::File::ProcessNow(void){

	//while(HTTP->State != DarkNet::PALM::TERMINATE){
	while(State != COMPLETE){
		//if error return S3GE_FILE_NOTFOUND
		HTTP->Process();
		Process(); 
	}
	if(dbFileExist((char*)HTTP->Response.WritePath.data())) return(S3GE_FILE_FOUND);
	return(S3GE_FILE_NOTFOUND);
}

// SYSTEM //////////////////////////////////////////////////////////////////////////////////////////

std::map<std::string, std::string> S3GE::System::ConfigPropertyMap;

/**
* @brief	Constructor
* @param	
* @return	void
*/
S3GE::System::System(void){
}

/**
* @brief	Destructor
* @param	
* @return	void
*/
S3GE::System::~System(void){

}

/**
* @brief	Initialize
* @param	
* @return	void
*/
void S3GE::System::Start(void){

	//Setup Config Properties from Registry

	string configfile = "config.lua";

	switch(int fileexists = File->Exist(configfile)){

		case S3GE_FILE_FOUND:
			DarkLUA::System::Execute("configuration", "config.lua", "");

			if(ConfigPropertyGet("AuthorizationKey").compare("e6ceb3eece2a66a5d4a29088a783b2e3")){
				alertbox("S3GE::System::Start()","No Authorization Key Found. Run `config.reg` and relaunch.",ALERTBOX_SEVERITY_ERROR);
			} else {
				ConfigPropertyMap["Title"].append(" v");
				ConfigPropertyMap["Title"].append(ConfigPropertyGet("Version"));
				ConfigPropertyMap["Title"].append(" ");
				ConfigPropertyMap["Title"].append(ConfigPropertyGet("ProductionPhase"));
				ConfigPropertyMap["Title"].append(" Build");
				dbSetWindowTitle((char*)ConfigPropertyMap["Title"].data());
			}
			break;

		case S3GE_FILE_NOTFOUND:
			alertbox("S3GE::System::Start()","No config.lua Found. Engine Terminated.",ALERTBOX_SEVERITY_ERROR);
			break;

	}

	//DGDK Setup
	Direct3D = dbGetDirect3D();
	Device = dbGetDirect3DDevice();
	Device->GetRenderTarget(0,&BackBuffer); 
	Device->GetDepthStencilSurface(&DepthStencilBuffer);
	BackBuffer->GetDesc(&BackBufferDesc);
	CommonSurfaceFormat = BackBufferDesc.Format;

	//Global Sprite Interface
	D3DXCreateSprite( Device, &SpriteInterface );

	//File Setup
	File = new S3GE::File;
	File->HTTPFileResource = new ResourceManager(32);

	//Text Setup
	Text = new S3GE::Text;
	Text->FontCreate("Arial", 12, false, false, 255, 255, 255, 255);

	//FontArt Text Setup
	FontArt::Load("Blood","2D/FontArt/BloodBath2.png");
	FontArtText = FontArt::Text::Create("00"); 

	//Fulcrum Physics Setup
	Physics = new FulcrumPhy;
	Physics->start();


}

/**
* @brief	Shutdown
* @param	
* @return	void
*/
void S3GE::System::Stop(void){

	//Text Setup
	
	Text->Stop();
	delete Text;

	Physics->stop();

	delete File->HTTPFileResource;
	delete File;

	delete this;

}

/**
* @brief	Shutdown
* @param	
* @return	void
*/
void S3GE::System::Update(){

	//FontArt testing Core->
	FontArtText->Alter(dbScreenWidth() - Core->FontArtText->WidthGet(),0,dbStr(dbScreenFPS()));
	FontArtText->Paste(0,0);

	//Output (StatusBar)
	Text->Print(1, 0, dbScreenHeight() - 20, DT_RIGHT, D3DCOLOR_RGBA(255,255,255,255), (char*)Output.data());

	//File Update
	File::Update();

}

/**
* @brief	Assigns Registry Value to Local Config Property
* @param	
* @return	void
*/
void S3GE::System::ConfigPropertySet( char* directory, char* key){

	ConfigPropertyMap[key] = dbGetRegistryS(directory, key); 
}

/**
* @brief	Returns value from Local Config Property
* @param	
* @return	void
*/
string S3GE::System::ConfigPropertyGet(string key){

	return(ConfigPropertyMap[key]);
}


/**
* @brief	Assigns Value to Local Config Property
* @param	
* @return	void
*/
void S3GE::System::ConfigPropertyValueSet(string key, string value){

	ConfigPropertyMap[key] = value; 
}

/**
* @brief	Returns value from Local Config Property
* @param	
* @return	void
*/
string S3GE::System::ConfigPropertyValueGet(string key){

	return(ConfigPropertyMap[key]);
}


/**
* @brief	Read Key and Return Value from Registry
* @param	
* @return	void
*/
string ConfigPropertyRead(char* directory, char* key){

	/*

	HKEY hKeyNames = 0;
	DWORD Status;
	char ObjectType[256];
	DWORD Datavalue = 0;

	strcpy(string,"");
	strcpy(ObjectType,"Num");
	Status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PerfmonNamesKey, 0L, KEY_READ, &hKeyNames);
    if(Status==ERROR_SUCCESS)
	{
		DWORD Type=REG_SZ;
		DWORD Size=256;
		Status = RegQueryValueEx(hKeyNames, valuekey, NULL, &Type, NULL, &Size);
		if(Size<255)
			RegQueryValueEx(hKeyNames, valuekey, NULL, &Type, (LPBYTE)string, &Size);

		RegCloseKey(hKeyNames);
	}
*/

	string registryvalue;
	return(registryvalue);

}

/**
* @brief	Write Key and Value to Registry
* @param	
* @return	void
*/
void ConfigPropertyWrite(char* directory, char* key, char* value){

	/*
	HKEY hKeyNames = 0;
	DWORD Status;
	DWORD dwDisposition;
	char ObjectType[256];
	strcpy(ObjectType,"Num");
	Status = RegCreateKeyEx(HKEY_LOCAL_MACHINE, PerfmonNamesKey, 0L, ObjectType, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WRITE, NULL, &hKeyNames, &dwDisposition);
	if(dwDisposition==REG_OPENED_EXISTING_KEY)
	{
		RegCloseKey(hKeyNames);
		Status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, PerfmonNamesKey, 0L, KEY_WRITE, &hKeyNames);
	}
    if(Status==ERROR_SUCCESS)
	{
        Status = RegSetValueEx(hKeyNames, valuekey, 0, REG_SZ, (LPBYTE)string, (strlen(string)+1)*sizeof(char));
	}
	RegCloseKey(hKeyNames);
	hKeyNames=0;
	return true;
*/
}