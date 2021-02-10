//************************ WELCOME TO FULCRUM PHYSICS ***************************// 

// Physics plug-in for DarkGDK, developed for S3GE(super 3D game engine).
// By Matthew Hoban.


// Thanks to Jezza (Jezza Parker) from the TGC forums, used his example code
// for rendering DGDK objects to correct position and orientation of respective
// PhysX actors. 
// http://forum.thegamecreators.com/?m=forum_view&t=150169&b=22

#pragma once

#define NOMINMAX  // You must #define NOMINAX before using the windows.h file* 


#include "FulcrumPhyCustomClasses.h"


class FulcrumPhy
{
   protected:
      
   //PHYSXSDK//
   // Our instance of the PhysXSDK module
   NxPhysicsSDK* itsPhysicsSDK;
   // Physics scene, probably need to add ability to make multiple scenes
   NxScene* itsScene;

   //MEMORY//
   // Memory allocator
   UserAllocator* itsAllocator;

   //VISUAL DEBUGGER//
   NxRemoteDebugger* itsRemoteDebugger;

   //CONTACT REPORT//
   ContactReport *itsContactReport;
   Contact *itsContact;

   //RAYCAST//
   Raycast *itsRay;

   //ACTORS//
   // Each actor has a unique integer value
   std::map <int, NxActor*> staticActors;
   std::map <int, NxActor*> dynamicActors;
   std::map <int, NxActor*> compoundActors;
   std::map <int, NxActor*>::iterator actorIterate;

   // Ground actor not held in map as it does not need an
   // id number to create it, I don't want to force the user to 
   // create an id number which is not related to a rendered object
   NxActor* groundPlaneActor;

   //MULTIPLE ACTORS WITH SHARED ID (objects with multiple meshes)//
   std::map<int, std::vector<NxActor*>> multipleActors;

   //SHAPES//
   std::vector<NxShapeDesc*> shapes;

   //MATERIALS//
   std::map<int, int> materials; // materials are added to array in scene

   //VEHICLES//
   std::map<int, FulcrumPhyVehicle*> vehicles;
   std::map<int, FulcrumPhyVehicle*>::iterator vehicleIterator;

   //CONTROLLERS// 
   // Will hold and control all character controllers that are created
   NxControllerManager* itsControllerManager;
   // Each controler has a unique integer value
   std::map<int, NxController*> controllers;
   std::map<int, NxController*>::iterator controllerIterator;

   bool simulating;


   bool makeConvexFromSingleMesh(int id, bool dynamic = false, float density = 10);
   bool makeConvexFromMultipleMesh(int id, bool dynamic = false, float density = 10);
   
public:
   FulcrumPhy(void);
   ~FulcrumPhy(void);



   //************************************************************************//
   //**************************** CORE **************************************//
   //************************************************************************//
   bool start(bool useDebugger = false);
   void update();
   void stop();
   void simulate();
   void getPhysicsResults();
   float getDefaultSkinWidth();
   float getDefaultRestitution();
   float getDefaultStaticFriction();
   float getDefaultDynamicFriction();
   void setDefaultSkinWidth(float skinWidth);
   void setDefaultRestitution(float restitution);
   void setDefaultStaticFriction(float staticFriction);
   void setDefaultDynamicFriction(float dynamicfriction);

	//TechLord addition
   void Update(void){ 
		getPhysicsResults();
		updateActors();
		simulate();		
   };

   //************************************************************************//
   //************************* CONSTRUCTION *********************************//
   //************************************************************************//
  
   //*********** ACTORS ************//
   void makeGroundPlane();
   bool makeBox(int id, bool dynamic = false, float density = 10);
   bool makeSphere(int id, bool dynamic = false, float density = 10);
   bool makeCapsule(int id, bool dynamic, float density, float radius, float length);
   bool makeTriangleMeshFromDBO(int id);
   bool makeTriangleMesh(int id);
   bool makeConvexMesh(int id, bool dynamic = false, float density = 10);

   //***** SHAPES AND COMPOUND *****//
   bool makeBoxShape(int id);
   bool makeSphereShape(int id);
   bool makeConvexShape(int id);
   bool makeCompoundActor(int id, bool dynamic = false, float density = 10);


   //********* CONTROLLERS **********//
   bool makeControllerBox(int id, float maxStep, float slopeLimit, bool yOffset);
   bool makeControllerBox(int id, float maxStep, float slopeLimit, float sizeX, float sizeY, float sizeZ);
   bool makeControllerCapsule(int id, float maxStep, float slopeLimit, bool yOffset);
   bool makeControllerCapsule(int id, float maxStep, float slopeLimit, float radius, float height);

   //*********** RELEASE ***********//
   void releaseActor(int id);
   void releaseController(int id);
   void releaseGroundPlane();





   //************************************************************************//
   //***************************** ACTORS ***********************************//
   //************************************************************************//

   void setCollisionOn(int id);
   void setCollisionOff(int id);
   void setPosition(int id, float posX, float posY, float posZ);
   void setOrientation(int actorID, float x, float y, float z);

   //********** DYNAMIC ***********//
   void updateActors();
   void updateActor(int id);
   void updateActorFast(int id);
   void setKinematicOn(int id);
   void setKinematicOff(int id);
   void disableGravity(int id);
   void enableGravity(int id);
   void setGravity(float X, float Y, float Z);
   void applyForce(int id, float x, float y, float z);
   void applyLocalForce(int id, float x, float y, float z);
   void applyTorque(int id, float x, float y, float z);
   void applyLocalTorque(int id, float x, float y, float z);
   void freezePositionX(int id, bool frozen = true);
   void freezePositionY(int id, bool frozen = true);
   void freezePositionZ(int id, bool frozen = true);
   void freezeRotationX(int id, bool frozen = true);
   void freezeRotationY(int id, bool frozen = true);
   void freezeRotationZ(int id, bool frozen = true);
   void setLinearDamping(int id, float linearDamping);
   void setAngularDamping(int id, float angularDamping);
   void setAngularVelocity(int id, float x, float y, float z);
   void setLinearVelocity(int id, float x, float y, float z);
   void setCMassLocalPosition(int actorID, float x, float y, float z);
   float getCMassLocalPositionX(int actorID);
   float getCMassLocalPositionY(int actorID);
   float getCMassLocalPositionZ(int actorID);
   float getLinearVelocityX(int actorID);
   float getLinearVelocityY(int actorID);
   float getLinearVelocityZ(int actorID);
   float getAngularVelocityX(int actorID);
   float getAngularVelocityY(int actorID);
   float getAngularVelocityZ(int actorID);



   //************************************************************************//
   //************************ CHARACTER CONTROLLERS *************************//
   //************************************************************************// 
   void updateControllers();   
   void setControllerLocalPositionY(int id, float yOffset);
   float getControllerLocalPositionY(int id);
   void moveCharacterController(int id, float x, float y, float z);  
   void moveCharacterController(int id, float distance, float gravity);
   void positionCharacterController(int id, float posX, float posY, float posZ);
   bool setControllerDimensions(int id, float increaseX, float increaseY, float increaseZ, bool collisionCheck = true);
   bool setControllerDimensions(int id, float heightIncrease, bool collisionCheck = true);




   //**********************************************************************//
   //**************************** RAYCAST *********************************//
   //**********************************************************************//
   int raycast(float originX, float originY, float originZ, float directionX, float directionY, float directionZ);  
   float getRayImpactPosX();
   float getRayImpactPosY();
   float getRayImpactPosZ();
   float getRayImpactNormalX();
   float getRayImpactNormalY();
   float getRayImpactNormalZ();
   float getRayDistance();



   //**********************************************************************//
   //************************* COLLISION GROUPS ***************************//
   //**********************************************************************//
   void setCollisionGroup(int actorID, int group);
   void setGroupCollision(int groupA, int groupB, bool collide);



   //**********************************************************************//
   //***************************** CONTACTS *******************************//
   //**********************************************************************//
   void setContactPair(int objectA, int objectB);  
   void releaseContactPair(int objectA, int objectB);
   bool getContactData();
   int getContactActorA();
   int getContactActorB();


   //**********************************************************************//
   //**************************** VEHICLES ********************************//
   //**********************************************************************//
   bool makeVehicle(int objectID);
   bool makeWheelShape(int vehicleID, int limbID, int wheelID, float radius = 1);
   void buildVehicle(int vehicleID);
   void driveWheel(int vehicleID, int wheelID, float torque);
   void steerWheel(int vehicleID, int wheelID, float angle);
   void updateWheels(int vehicleID);
   void setWheelSuspensionTravelMax(int vehicleID, int wheelID, float distance);



   //**********************************************************************//
   //**************************** MATERIALS *******************************//
   //**********************************************************************//
   void makeMaterial(int materialID, float restitution, float dynamicFriction, float staticFriction);
   void setMaterial(int vehilcleID, int wheelID, int materialID); 
   void setMaterial(int actorID, int materialID);



   //************************************************************************//
   //***************************** SPECIAL **********************************//
   //************************************************************************//
   bool swapObject(int actorId, int newObjectId);










   // Following not needed unless fast update is used

   /**
   * Updates all the actors in the scene, only use this if your objects have not
   * been scaled and you also don't need to retrieve the orientation of the
   * object/actor at any point, this is faster than the updateActors() function.
   */
   //void updateActorsFast();

   //float getPositionX(int actorID);
   //float getPositionY(int actorID);
   //float getPositionZ(int actorID);


   //float getOrientationX(int actorID);
   //float getOrientationY(int actorID);
   //float getOrientationZ(int actorID);


   //***** LOCAL *****//

   // Position
   //void setLocalPosition(int actorID, int shapeNumber, float localX, float localY, float localZ);
   //float getLocalPositionX(int actorID, int shapeNumber);
   //float getLocalPositionY(int actorID, int shapeNumber);
   //float getLocalPositionZ(int actorID, int shapeNumber);
   
   // Orientation
   //void setLocalOrientation(int actorID, int shapeNumber, float x, float y, float z);
};













