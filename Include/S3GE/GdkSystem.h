#pragma once
#ifndef GDKSYSTEM_H
#define GDKSYSTEM_H

#include "..\..\..\Include\DarkGDK\DarkGDK.h"
float fcamAngleX,fcamAngleY;
#define cMove 2

void SatControl(void)
{
	if (dbUpKey())
	{
		dbPositionCamera(0,dbCameraPositionX(),dbCameraPositionY(),dbCameraPositionZ()+cMove);
	}
	if (dbDownKey())
	{
		dbPositionCamera(0,dbCameraPositionX(),dbCameraPositionY(),dbCameraPositionZ()-cMove);
	}
	if (dbLeftKey())
	{
		dbPositionCamera(0,dbCameraPositionX()-cMove,dbCameraPositionY(),dbCameraPositionZ());
	}
	if (dbRightKey())
	{
		dbPositionCamera(0,dbCameraPositionX()+cMove,dbCameraPositionY(),dbCameraPositionZ());
	}
	if (dbKeyState(17))
	{
		dbMoveCamera(0,cMove*2);
	}
	if (dbKeyState(31))
	{
		dbMoveCamera(0,-cMove*2);
	}
}

void FpsCamera(int Camera)
{
	if (dbUpKey())
	{
		dbMoveCamera(Camera,cMove);
	}
	if (dbDownKey())
	{
		dbMoveCamera(Camera,-cMove);
	}
	if (dbLeftKey())
	{
		dbYRotateCamera(Camera,dbCameraAngleY(Camera)-90);
		dbMoveCamera(Camera,cMove);
		dbYRotateCamera(Camera,dbCameraAngleY(Camera)+90);
	}
	if (dbRightKey())
	{

		dbYRotateCamera(Camera,dbCameraAngleY(Camera)+90);
		dbMoveCamera(Camera,cMove);
		dbYRotateCamera(Camera,dbCameraAngleY(Camera)-90);
	}
	fcamAngleX = dbWrapValue(fcamAngleX + dbMouseMoveY() *0.2f);
	fcamAngleY = dbWrapValue(fcamAngleY + dbMouseMoveX() *0.2f);

	dbXRotateCamera(Camera,fcamAngleX);
	dbYRotateCamera(Camera,fcamAngleY);

}
bool ActionTimer(int tImer,int &sAved,int dElay) // dbTimer , StateTimer, Delay
{
	bool temp=false;
	if (tImer > sAved+dElay)
	{	
		sAved = tImer;
		return true;
	}
	else 
		return false;

}

int GetFreeSprite()
{
	int fs = 1;
	while (dbSpriteExist(fs))
	{
		fs++;
	}
	return fs;
}

class ImageFix
{
private:
	int imgCounter;
public:
	ImageFix(){imgCounter = 0;}

	int IC(void){imgCounter++; return imgCounter;}

};

int GetFreeObject()
{
	int fo = 1;
	while (dbObjectExist(fo))
	{
		fo++;
	}
	return fo;

}

int GetFreeImage()
{
	int i = 1;
	while (dbImageExist(i) == 1)
	{
		i++;
	}
	return i;
}

int GetFreeMemblock()
{
	int i = 3; // Since one and two are AEM prims
	while (dbMemblockExist(i) == 1)
	{
		i++;
	}
	return i;
}

int GetFreeBitmap()
{
	int i = 1;
	while (dbBitmapExist(i) == 1)
	{
		i++;
	}
	return i;
}
void CenterSpriteCords(int ID)
{
	dbOffsetSprite(ID,dbSpriteWidth(ID)/2,dbSpriteHeight(ID)/2);
}

float Get_Distance(float X1,float Y1,float Z1,float X2,float Y2,float Z2)
{
	float DistX = X1 - X2;
	float DistY = Y1 - Y2;
	float DistZ = Z1 - Z2;
	float Distance = dbSqrt(DistX * DistX + DistY * DistY + DistZ * DistZ);

		return Distance;
}

void ResSelect(bool Window)
{
bool ResSelect = false;
	int ResSelectId = 1;
	int ResTimer = 0;
	dbPerformChecklistForDisplayModes();
	while (!ResSelect)
	{
		dbText(0,0,"Choose Resulotion.");
		dbText(0,11,"Up / Down keys .  Press Enter to Select!");
		dbText(0,25,dbChecklistString(ResSelectId));
		if (ActionTimer(dbTimer(),ResTimer,200))
		{
			if (dbUpKey() && ResSelectId < dbChecklistQuantity())
			{
				ResSelectId++;
				dbCLS();
				//ResTimer = dbTimer();
			}
			if (dbDownKey() && ResSelectId > 1)
			{
				ResSelectId--;
				dbCLS();
				//ResTimer = dbTimer();
			}
			if (dbReturnKey())
				ResSelect = true;
		}
		dbSync();	
	}
	dbSetDisplayMode(dbChecklistValueA(ResSelectId),dbChecklistValueB(ResSelectId),dbChecklistValueC(ResSelectId));
	dbSetWindowOn();
	dbSetWindowPosition(0,0);
	//if (!Window)
		//dbMaximiseWindow();
}

void CleanAll()
{
	for (int i =0;i < 10000;i++)
	{
		if (dbMemblockExist(i)==1)
		{
			dbDeleteMemblock(i);
		}
		if (dbObjectExist(i)==1)
		{
			dbDeleteObject(i);
		}
		if (dbSpriteExist(i)==1)
		{
			dbDeleteSprite(i);
		}
		if (dbImageExist(i)==1)
		{
			dbDeleteImage(i);
		}
		if (dbBitmapExist(i) == 1)
		{
			dbDeleteBitmap(i);
		}

	}
}

int PrctgCounter(float Counter,float MaxAmount)
{	
	int Precentege =(float)Counter/MaxAmount * 100;
	return Precentege;
}

// Text Fix by Fersis. for cleaning memory leaks from dbStr function.
void TextStr(int iX,int iY,float fValue)
{
	char* pstrTemp;
	pstrTemp = dbStr(fValue);
	dbText(iX,iY,pstrTemp);
	delete pstrTemp;
}

#endif