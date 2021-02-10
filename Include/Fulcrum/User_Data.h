#pragma once
#include "NxPhysics.h"
#include "NxController.h"  // for use of ExtendedVec3
#include "..\DarkGDK\DarkGDK.h"

class User_Data
{
public:
	User_Data(void);
	~User_Data(void);
    
	void initialize(int objectID);
    void setScale();


	int itsObjectID;
	bool itsScaled;
	NxVec3 itsScale;
	NxExtendedVec3 itsOffset;  // for controllers
};
