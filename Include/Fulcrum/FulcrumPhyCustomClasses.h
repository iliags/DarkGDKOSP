// At the moment this file has all the includes plus a few small 
// custom classes, it also declares the helper functions that are implemented
// in the utility file.



#pragma once
#include "..\DarkGDK\DarkGDK.h"

#include "Windows.h"
#include <map>
#include <fstream>

// PhysX
#include "NxPhysics.h"
#include "UserAllocator.h"
#include "NxUserAllocatorDefault.h"
#include "NxController.h"
#include "NxControllerManager.h"     
#include "NxCapsuleController.h"

// PhysX wrapper
#include "PhysX.h"
#include "User_Data.h"

#pragma comment(lib,"PhysXLoader.lib")
#pragma comment(lib,"NxCharacter.lib")
#pragma comment(lib,"NxCooking.lib")
#pragma comment(lib,"FulcrumPhy.lib")

//*********************************** UTILITY ********************************//
bool checkObjectExist(int id, char* function);
NxVec3 getObjectPosition(int id);
NxVec3 getObjectOrientation(int id);
NxVec3 getObjectDimensions(int id);
NxVec3 getObjectScale(int id);
NxU32* getIndexData(sMesh* aMesh);
D3DXMATRIX getScaledMatrix(D3DXMATRIX aMatrix, NxVec3 scale);
NxVec3* getVertexData(sMesh* aMesh, NxVec3 scale);
NxU32* getLimbIndexData(int objectID, int limbID);
NxVec3* getLimbVertexData(int objectID, int limbID, NxVec3 scale);
void quaternionToEuler(NxQuat &quaternion, D3DXVECTOR3 &euler);
void applyPoleCorrection(int id);
NxActor* getActorFromMap(int actorID, std::map<int, NxActor*> &map1, std::map<int, NxActor*> &map2);
NxActor* getActorFromMap(int actorID, std::map<int, NxActor*> &map1, std::map<int, NxActor*> &map2, std::map<int, NxController*> &map3);
//*****************************************************************************//


class FulcrumPhyWheel
{
public:
	FulcrumPhyWheel(void);
	FulcrumPhyWheel(int objectID, int limbID, float radius);
	~FulcrumPhyWheel(void);

    void createShapeDesc(int objectID, int limbID, float radius);
	void update();

	int            itsObjectID;
	int            itsLimbID;
	int            itsShapePosition;   //inside owning actor
	float          itsAxelRotation;
    float          itsSteerAngle;
	NxShapeDesc   *itsShapeDesc;       //wheelShapeDesc
	NxShape       *itsShape;           //pointer to shape after actor is made, for direct access?
};



class FulcrumPhyVehicle
{
public:
	FulcrumPhyVehicle(int objectID);
	~FulcrumPhyVehicle(void);
         
	void addWheel(int limbID, int wheelID, float radius); //Object known from initialize
	void addShapeDesc(NxShapeDesc *aShapeDesc); // hull
	void updateWheels();
    void make();

	int itsObjectID;
	std::map<int, FulcrumPhyWheel*> itsWheels; //wheels
	std::map <int, FulcrumPhyWheel*>::iterator wheelIterate;

	//std::vector<NxShape*> itsShapes;
	std::vector<NxShapeDesc*> itsShapeDescs; //hull
};




class Raycast
{
public:
   NxVec3 itsWorldImpact;
   NxReal itsDist;
   NxReal itsU;
   NxReal itsV;
   NxVec3 itsWorldNormal;
};

class Contact
{
public:
	int actorA;
	int actorB;
};

// Contact report class
class ContactReport : public NxUserContactReport
{
public:

	virtual void onContactNotify(NxContactPair &pair, NxU32 events);

	std::vector<Contact*> itsContacts; 
};
