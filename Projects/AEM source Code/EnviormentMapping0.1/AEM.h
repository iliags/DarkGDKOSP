#pragma once
#ifndef AEM_H
#define AEM_H

#include "GdkSystem.h"

class Color
{
private:
	int cRed,cGreen,cBlue ;// color integer representor
	char* colorName ; // color's Name
	int cTextures[32]; // Texture or Stamps ID
	int cTexPrio[32]; // Rando priorety
	int cTexRegionMin[32];
	int cTexRegionMax[32];
	int cTextureMinSize[32], cTextureMaxSize[32];
	int cTextureCounter;
	int cSprite;
	int cImage;
	int cMaxR;
	int sSprite; // Stamp sprite
public:
	Color()
	{
		cRed =0;cGreen = 0;cBlue = 0;colorName = "null"; cSprite = 0;cImage = 0;cTextureCounter = 0;cMaxR=0;
		for (int i =0; i<32;i++)
		{
			cTextures[i] = 0;
			cTexRegionMin[i]=0;
			cTexRegionMax[i] = 0;
			cTexPrio[i] = 0;
			cTextureMinSize[i] = 0;
			cTextureMaxSize[i] = 0;
		}
	}
	void SetColor(int Red,int Green,int Blue)
	{
		cRed = Red; cGreen = Green;cBlue = Blue;

 		sSprite = GetFreeSprite();
		dbSprite(sSprite,0,0,dummyImg);
		CenterSpriteCords(sSprite);
		dbHideSprite(sSprite);
	}
	void SetName(char *Name){colorName = Name;}
	void AddTextureStamp(int ImageId,int TexPriority,int MinSize,int MaxSize)
	{
		cTexPrio[cTextureCounter] = TexPriority ;
		cTextures[cTextureCounter] = ImageId;
		cTextureMinSize[cTextureCounter] = MinSize;
		cTextureMaxSize[cTextureCounter] = MaxSize;
		
		cTexRegionMin[cTextureCounter] = cMaxR;
		cMaxR = cMaxR+ TexPriority;
		cTexRegionMax[cTextureCounter] = cMaxR;
		cTextureCounter ++;

	}
	int Stamp() // for use inside the Main Cpp inside dbSetSpriteImage
	{
		int tempStampRandom = dbRnd(cMaxR)+1;
		int stamp = 0;
		for (int i = 0;i < cTextureCounter; i++)
		{
			if (tempStampRandom >= cTexRegionMin[i] && tempStampRandom < cTexRegionMax[i])
			{
				stamp = cTextures[i];
			}
		}
	
		//dbSetSpriteImage(sSprite,cTextures[stamp]);
		//dbPasteSprite(sSprite,X,Y);
		return stamp;
	}

	void Stamp(int X,int Y) // for use outside the Main cpp , code looks cleaner that way
	{
		int tempStampRandom = dbRnd(cMaxR)+1;
		int stamp = 0;
		int tempRotation = dbRnd(360);
		int tempYrand = dbRnd(5) ;
		int tempXrand = dbRnd(5) ;
		int tempYminus = dbRnd(1);
		int tempXminus = dbRnd(1);
		for (int i = 0;i < cTextureCounter; i++)
		{
			if (tempStampRandom >= cTexRegionMin[i] && tempStampRandom < cTexRegionMax[i])
			{
				stamp = i;
			}
		}
		int tempSize = cTextureMinSize[stamp] + dbRnd(cTextureMaxSize[stamp] - cTextureMinSize[stamp]);
		//if (tempSize < cTextureMinSize[stamp]) {tempSize = cTextureMinSize[stamp];}

		dbRotateSprite(sSprite,tempRotation);
		if (tempYminus == 1)
			tempYminus = -tempYminus;
		if (tempXminus == 1)
			tempXminus = -tempXminus;

		dbSetSpriteImage(sSprite,cTextures[stamp]);
		dbSizeSprite(sSprite,tempSize,tempSize);
		dbPasteSprite(sSprite,X+ tempXrand * tempXminus,Y+ tempYrand * tempYminus);
	}

	int GetColorRed(){return cRed;}
	int GetColorGreen(){return cGreen;}
	int GetColorBlue(){return cBlue;}

	char   *GetName()		{return colorName;}
	int   GetSprite()		{return sSprite;}
	int    GetImage()		{return cImage;}
	int		GetTextureCounter() {return cTextureCounter;}
};
#endif