#pragma once
#include "NxPhysics.h"
#include "NxCooking.h"

#include "NxController.h"
#include "NxControllerManager.h"
//NOTE: commented out a function in CharacterControllerManager.cpp as I was getting linker errors
#include "NxCapsuleController.h"
#include "NxBoxController.h"

#include "Stream.h"
#include <vector>
#include "..\DarkGDK\DarkGDK.h"

//**********************************************************************//
//********************* PHYSX STATIC CLASS *****************************//
//**********************************************************************//

// Contains general helper functions

class PhysX
{
public:

//     static const enum Shape{BOX, SPHERE, CAPSULE};

     /**
	   Creates a scene and adds it to aPhysicsSDK
	   -Input:
	   -# aPhysicsSDK, your instance of the SDK which you must define first to build your simulation
	   -# restitution, sets the scenes default materials bounciness 
	   -# staticFriction, sets the scenes default materials resting friction
	   -# dynamicFriction, sets the scenes default materials sliding friction
	   -Output: returns the scene
	  */
    static NxScene* createScene(NxPhysicsSDK* aPhysicsSDK, float restitution, float staticFriction, float dynamicFriction);  

	static void kinematicOn(NxActor* anActor);

	static void kinematicOff(NxActor* anActor);

    static NxActor* makeTriangleMesh(NxPhysicsSDK* aPhysicsSDK, NxScene* aScene, int totalVertices, NxVec3* vertices, int totalIndices, NxU32* indices, NxVec3 localPose, NxVec3 globalPose, NxVec3 orientation);

    static NxActor* createConvexMesh(NxPhysicsSDK* aPhysicsSDK, NxScene* aScene,  bool dynamic, float density, int totalVertices, NxVec3* vertices, NxVec3 localPose, NxVec3 globalPose, NxVec3 orientation);
   
    static NxActor* createConvexMesh(NxPhysicsSDK* aPhysicsSDK, NxScene* aScene, bool dynamic, float density, int totalVertices, NxVec3* vertices, NxVec3 localPose, NxMat34 matrix);

    static bool createConvexMeshShape(NxConvexShapeDesc* convexdesc, NxPhysicsSDK* aPhysicsSDK, NxScene* aScene, int totalVertices, NxVec3* vertices, NxVec3 localPose, NxVec3 globalPose, NxVec3 orientation);

    static NxController* createCharacterController( NxControllerManager* manager, NxScene *scene, NxVec3 pos, NxReal radius, NxReal height, NxReal step, NxReal slopeLimit, NxReal skinWidth); 
    
	static NxController* createCharacterController( NxControllerManager* manager, NxScene *scene, NxVec3 pos, NxVec3 dim, NxReal step, NxReal slopeLimit, NxReal skinWidth); 

	static void createBoxShape(NxBoxShapeDesc* aBoxShape, NxVec3 localPosition, NxVec3 dimensions, NxVec3 localOrientation);

    static void createSphereShape(NxSphereShapeDesc* aShape, NxVec3 localPos, NxVec3 size, NxVec3 orientation);

    static void createCapsuleShape(NxCapsuleShapeDesc* aCapsuleShape, NxVec3 localPos, NxVec3 size, NxVec3 orientation);

    static void createBody(NxBodyDesc* aBody, NxReal mass);

	static void createActorDesc(NxActorDesc* anActorDesc, NxShapeDesc* aShapeDesc, NxBodyDesc* aBodyDesc, NxVec3 globalPosition, NxVec3 globalOrientation, NxReal density);

    static NxActor* createActorPrimitive(NxScene* aScene, bool dynamic, NxVec3 localPosition, NxVec3 localOrientation, NxVec3 globalPosition, NxVec3 globalOrientation, NxVec3 dimensions, NxReal density, NxShapeType aShapeType);

    static NxMat33 getOrientationMatrix(NxVec3 orientation);



};
