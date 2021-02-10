/*
|``````.        .'.       |`````````, |    ..'' |        |         |       .'.       
|       |     .''```.     |'''|'''''  |..''     |        |         |     .''```.     
|       |   .'       `.   |    `.     |``..     |        |         |   .'       `.   
|......'  .'           `. |      `.   |    ``.. |_______ `._______.' .'           `. 

This program is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
Lesser GNU General Public License for more details.

You should have received a copy of the Lesser GNU General Public License
along with this program. if(not, see HTTP://www.gnu.org/licenses/.
*/

/*
DarkLUA 1.1 Plug-in by Frankie `techlord` Taylor
based on LUA for Windows 5.1.4 HTTP://luaforwindows.luaforge.net/
*/

#include "..\DarkGDK\DarkGDK.h"
#include "DarkNet.h"
#include "TBEMS_SDK.h"
#include "S3GE.h"
#include "MAUI.h"
#include "Illudium.h"
#include "QuantumPath.h"
#include "Scenergy.h"

/**
* @brief	DARKLUA BINDINGS: C++ to LUA Binding Functions, Plug-in: LUA for Windows 5.1.4 (HTTP://luaforwindows.luaforge.net)
*			Notes: lua_register expects a int value to be returned from binding functions
*/

inline int darklua_aiNavGeometryLoad(lua_State *L){ //to be replace with single method
	if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);}
	QuantumPath::Geometry *ainavgeometry = QuantumPath::Geometry::Create(QUANTUMPATH_GEOMETRY_TYPE_DEFAULT);
	ainavgeometry->Load(DARKLUA_STRING(1)); 
	ainavgeometry->Build(); 
	dbSetObject(ainavgeometry->dbObjectID,0,0,0,0,0,0,0); 
	return 0; 
}

inline int darklua_bugLogAppend(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} BugLog->append(DARKLUA_STRING(1)); return 0; }		
inline int darklua_bugLogDisable(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} BugLog->disable(); return 0;}		
inline int darklua_bugLogEnable(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} BugLog->enable(); return 0;}		
inline int darklua_bugLogClear(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} BugLog->clear(); return 0;}		
inline int darklua_bugLogPrint(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} BugLog->print(DARKLUA_STRING(1)); return 0; }		
inline int darklua_dbABS(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbABS(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbACOS(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbACOS(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbAlphaAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbAlphaAvailable()) ; return 1;}		
inline int darklua_dbAlphaBlendingAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbAlphaBlendingAvailable()) ; return 1;}		
inline int darklua_dbAlphaComparisionAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbAlphaComparisionAvailable()) ; return 1;}		
inline int darklua_dbAlphaMappingOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetAlphaMappingOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbAmbientLightColorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbColorAmbientLight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbAmbientLightSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetAmbientLight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbAntiAliasAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbAntiAliasAvailable()) ; return 1;}		
inline int darklua_dbAsc(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbAsc((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbASIN(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbASIN(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbATAN(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbATAN(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbATANFULL(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbATANFULL(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2))) ; return 1;}		
inline int darklua_dbAutoCameraOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbAutoCamOff(); return 0;}		
inline int darklua_dbAutoCameraOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbAutoCamOn(); return 0;}		
inline int darklua_dbBackdropColorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbColorBackdrop(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBackdropOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbBackdropOff(); return 0;}		
inline int darklua_dbBackdropOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbBackdropOn(); return 0;}		
inline int darklua_dbBackdropScrollSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbScrollBackdrop(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbBackdropTextureSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbTextureBackdrop(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBin(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(dbBin(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBitmapBlurSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbBlurBitmap(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbBitmapCopySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCopyBitmap(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbBitmapCreateSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbCreateBitmap(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbBitmapCurrentGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbCurrentBitmap()) ; return 1;}		
inline int darklua_dbBitmapCurrentSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetCurrentBitmap(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBitmapDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteBitmap(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBitmapDepthGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbBitmapDepth(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBitmapExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbBitmapExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBitmapFadeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbFadeBitmap(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbBitmapFlippedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbBitmapFlipped(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBitmapFlipSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbFlipBitmap(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBitmapFromMemblockMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeBitmapFromMemblock(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbBitmapHeightGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbBitmapHeight(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBitmapLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadBitmap((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbBitmapMirroredGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbBitmapMirrored(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBitmapMirrorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMirrorBitmap(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBitmapWidthGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbBitmapWidth(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBlitSysToLocalAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbBlitSysToLocalAvailable()) ; return 1;}		
inline int darklua_dbBoxSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbBox(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbBSPCameraCollisionRadiusSet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbSetBSPCameraCollisionRadius(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbBSPCameraCollisionSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetBSPCameraCollision(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbBSPCameraSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetBSPCamera(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBSPCollisionHeightAdjustmentSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetBSPCollisionHeightAdjustment(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbBSPCollisionHitGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbBSPCollisionHit(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBSPCollisionOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetBSPCollisionOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBSPCollisionProcessSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbProcessBSPCollision(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbBSPCollisionThresholdSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetBSPCollisionThreshold(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbBSPCollisionXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbBSPCollisionX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBSPCollisionYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbBSPCollisionY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBSPCollisionZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbBSPCollisionZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbBSPDelete(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDeleteBSP(); return 0;}		
inline int darklua_dbBSPLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadBSP((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbBSPMultiTexturingOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetBSPMultiTexturingOff(); return 0;}		
inline int darklua_dbBSPMultiTexturingOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetBSPMultiTexturingOn(); return 0;}		
inline int darklua_dbBSPObjectCollisionRadiusSet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbSetBSPObjectCollisionRadius(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbBSPObjectCollisionSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetBSPObjectCollision(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbBumpMappingOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetBumpMappingOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbByteFromFileRead(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbReadByteFromFile((char*)DARKLUA_STRING(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbByteWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteByte(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbCalibrateGammaAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbCalibrateGammaAvailable()) ; return 1;}		
inline int darklua_dbCameraAngleXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCameraAngleX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbCameraAngleYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCameraAngleY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbCameraAngleZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCameraAngleZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbCameraAspectSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbSetCameraAspect(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraAutoCollisionSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbAutomaticCameraCollision(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbCameraClearViewSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 argument"); lua_error(L);} dbClearCameraView(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbCameraCurrentSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetCurrentCamera(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbCameraDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteCamera(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbCameraFOVSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbSetCameraFOV(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraMake(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeCamera(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbCameraMove(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0; }		
inline int darklua_dbCameraMoveSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbMoveCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraPitchDown(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbPitchCameraDown(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraPitchUp(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbPitchCameraUp(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraPoint(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPointCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbCameraPositionSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPositionCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbCameraPositionXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCameraPositionX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbCameraPositionYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCameraPositionY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbCameraPositionZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCameraPositionZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbCameraRangeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetCameraRange(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbCameraRollLeft(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbRollCameraLeft(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraRollRight(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbRollCameraRight(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraRotate(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbRotateCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbCameraRotateXSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbXRotateCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraRotateYSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbYRotateCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraRotateZSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbZRotateCamera(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraRotationXYZSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} dbSetCameraRotationXYZ(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbCameraRotationZYXSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 arguments"); lua_error(L);} dbSetCameraRotationZYX(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbCameraToFollow(lua_State *L){if(lua_gettop(L) < 9){lua_pushstring(L, "Error! < 9 arguments"); lua_error(L);} dbSetCameraToFollow(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6),DARKLUA_FLOAT(7),DARKLUA_FLOAT(8),DARKLUA_INT(9)); return 0;}		
inline int darklua_dbCameraToImageSet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbSetCameraToImage(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5)); return 0;}		
inline int darklua_dbCameraToObjectOrientationSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbSetCameraToObjectOrientation(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbCameraTurnLeft(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbTurnCameraLeft(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraTurnRight(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 argument"); lua_error(L);} dbTurnCameraRight(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbCameraViewSet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbSetCameraView(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbCartoonShadingOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetCartoonShadingOn(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbChr(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(dbChr(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbCircleSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbCircle(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbCLGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbCL()) ; return 1;}		
inline int darklua_dbClipAndScalePointsAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbClipAndScalePointsAvailable()) ; return 1;}		
inline int darklua_dbClipboardGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbGetClipboard()) ; return 1;}		
inline int darklua_dbClipboardWrite(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbWriteToClipboard((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbClipTLVertsAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbClipTLVertsAvailable()) ; return 1;}		
inline int darklua_dbCLSSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbCLS(); return 0;}		
inline int darklua_dbColorPerspectiveAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbColorPerspectiveAvailable()) ; return 1;}		
inline int darklua_dbColorWriteEnableAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbColorWriteEnableAvailable()) ; return 1;}		
inline int darklua_dbControlCameraUsingArrowKeysSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbControlCameraUsingArrowKeys(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbControlDeviceSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetControlDevice((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbControlDeviceXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbControlDeviceX()) ; return 1;}		
inline int darklua_dbControlDeviceYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbControlDeviceY()) ; return 1;}		
inline int darklua_dbControlDeviceZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbControlDeviceZ()) ; return 1;}		
inline int darklua_dbControlKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbControlKey()) ; return 1;}		
inline int darklua_dbConvertObjectFVFSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbConvertObjectFVF(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbCOS(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCOS(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbCreateVertexShaderFromFileSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCreateVertexShaderFromFile(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbCubeMapAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbCubeMapAvailable()) ; return 1;}		
inline int darklua_dbCullCCWAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbCullCCWAvailable()) ; return 1;}		
inline int darklua_dbCullCWAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbCullCWAvailable()) ; return 1;}		
inline int darklua_dbCurrentGraphicsCardGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbCurrentGraphicsCard()) ; return 1;}		
inline int darklua_dbCursorSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetCursor(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbCurveAngleGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCurveAngle(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3))) ; return 1;}		
inline int darklua_dbCurveValueGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbCurveValue(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3))) ; return 1;}		
inline int darklua_dbDateGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbGetDate()) ; return 1;}		
inline int darklua_dbDeleteVertexShaderSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteVertexShader(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbDetailMappingOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetDetailMappingOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbDeviceTypeGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetDeviceType()) ; return 1;}		
inline int darklua_dbDirBlockReadSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbReadDirBlock(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbDirectory(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDir(); return 0;}		
inline int darklua_dbDirectoryBlockWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteDirBlock(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbDirectoryChangeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbCD((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbDirectoryDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteDirectory((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbDirectoryGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbGetDir()) ; return 1;}		
inline int darklua_dbDirectoryMake(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeDirectory((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbDirectoryPathExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbPathExist((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbDirectorySet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetDir((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbDisplayModeCheckGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbCheckDisplayMode(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3))) ; return 1;}		
inline int darklua_dbDisplayModeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetDisplayMode(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbDitherAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbDitherAvailable()) ; return 1;}		
inline int darklua_dbDLLCallExist(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbDLLCallExist(DARKLUA_INT(1),(char*)DARKLUA_STRING(2))) ; return 1;}		
inline int darklua_dbDLLCallSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCallDLL(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbDLLDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteDLL(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbDLLExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbDLLExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbDLLLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadDLL((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbDotSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbDot(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbDownKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbDownKey()) ; return 1;}		
inline int darklua_dbDrawSpritesFirstSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDrawSpritesFirst(); return 0;}		
inline int darklua_dbDrawSpritesLastSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDrawSpritesLast(); return 0;}		
inline int darklua_dbDrawToBackSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDrawToBack(); return 0;}		
inline int darklua_dbDriveListSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDriveList(); return 0;}		
inline int darklua_dbEffectConstantBooleanSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetEffectConstantBoolean(DARKLUA_INT(1),(char*)DARKLUA_STRING(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbEffectConstantFloatSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetEffectConstantFloat(DARKLUA_INT(1),(char*)DARKLUA_STRING(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbEffectConstantIntegerSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetEffectConstantInteger(DARKLUA_INT(1),(char*)DARKLUA_STRING(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbEffectConstantMatrixSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetEffectConstantMatrix(DARKLUA_INT(1),(char*)DARKLUA_STRING(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbEffectConstantVectorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetEffectConstantVector(DARKLUA_INT(1),(char*)DARKLUA_STRING(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbEffectDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteEffect(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbEffectExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbEffectExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbEffectLoad(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbLoadEffect((char*)DARKLUA_STRING(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbEffectOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetEffectOn(DARKLUA_INT(1),(char*)DARKLUA_STRING(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbEffectTechniqueSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetEffectTechnique(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbEffectTransposeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetEffectTranspose(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbEllipseSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbEllipse(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbEntryBufferClear(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbClearEntryBuffer(); return 0;}		
inline int darklua_dbEntryBufferGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbEntry()) ; return 1;}		
inline int darklua_dbEscapeKeyDisable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDisableEscapeKey(); return 0;}		
inline int darklua_dbEscapeKeyEnable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbEnableEscapeKey(); return 0;}		
inline int darklua_dbEscapeKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbEscapeKey()) ; return 1;}		
inline int darklua_dbEXP(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbEXP(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbFastSync(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbFastSync(); return 0;}		
inline int darklua_dbFileBlockReadSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbReadFileBlock(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbFileBlockWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteFileBlock(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbFileCloseSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbCloseFile(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbFileCopySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCopyFile((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbFileCreationGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbGetFileCreation()) ; return 1;}		
inline int darklua_dbFileDateGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbGetFileDate()) ; return 1;}		
inline int darklua_dbFileDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteFile((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbFileEndGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbFileEnd(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbFileExecuteSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbExecuteFile((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2), (char*)DARKLUA_STRING(3)); return 0;}		
inline int darklua_dbFileExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbFileExist((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbFileFindFirstSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbFindFirst(); return 0;}		
inline int darklua_dbFileFindNextSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbFindNext(); return 0;}		
inline int darklua_dbFileMake(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeFile((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbFileMoveSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveFile((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbFileNameGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbGetFileName()) ; return 1;}		
inline int darklua_dbFileOpenGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbFileOpen(DARKLUA_INT(1))) ; return 1;}
inline int darklua_dbFileOpenReadSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbOpenToRead(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbFileOpenWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbOpenToWrite(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbFileRenameSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRenameFile((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbFileSizeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbFileSize((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbFileTypeGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetFileType()) ; return 1;}		
inline int darklua_dbFileWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteFile(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbFilteringAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbFilteringAvailable()) ; return 1;}		
inline int darklua_dbFloatWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteFloat(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbFogAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbFogAvailable()) ; return 1;}		
inline int darklua_dbFogColorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbFogColor(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbFogDistanceSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbFogDistance(DARKLUA_FLOAT(1)); return 0;}		
inline int darklua_dbFogOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbFogOff(); return 0;}		
inline int darklua_dbFogOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbFogOn(); return 0;}		
inline int darklua_dbFogRangeAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbFogRangeAvailable()) ; return 1;}		
inline int darklua_dbFogTableAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbFogTableAvailable()) ; return 1;}		
inline int darklua_dbFogVertexAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbFogVertexAvailable()) ; return 1;}		
inline int darklua_dbForceAngleSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbForceAngle(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbForceAutoCenterOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbForceAutoCenterOff(); return 0;}		
inline int darklua_dbForceAutoCenterOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbForceAutoCenterOn(); return 0;}		
inline int darklua_dbForceChainsawSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbForceChainsaw(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbForceDown(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbForceDown(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbForceImpactSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbForceImpact(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbForceLeft(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbForceLeft(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbForceNoEffectSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbForceNoEffect(); return 0;}		
inline int darklua_dbForceRight(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbForceRight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbForceShootSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbForceShoot(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbForceUp(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbForceUp(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbForceWaterEffectSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbForceWaterEffect(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbGammaSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetGamma(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbGlobalCollisionOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetGlobalCollisionOff(); return 0;}		
inline int darklua_dbGlobalCollisionOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetGlobalCollisionOn(); return 0;}		
inline int darklua_dbGraphicsCardSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetGraphicsCard((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbGroundHeightGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetGroundHeight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3))) ; return 1;}		
inline int darklua_dbHCOS(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbHCOS(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbHex(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(dbHex(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbHSIN(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbHSIN(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbHTAN(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbHTAN(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbImageColorKeySet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetImageColorKey(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbImageCreate(lua_State *L){if(lua_gettop(L) < 6){lua_pushstring(L, "Error! < 6 arguments"); lua_error(L);} Core->Image->Create(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_STRING(3),DARKLUA_INT(4),DARKLUA_INT(5),DARKLUA_INT(6)); return 0;}		
inline int darklua_dbImageDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteImage(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbImageExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbImageExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbImageFromMemblockMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeImageFromMemblock(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbImageLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadImage((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbImagePaste(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbPasteImage(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbImageResourcePop(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);}DARKLUA_RETURNINT(dbImageResource->Pop()); return 1;}		
inline int darklua_dbImageResourcePush(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);}dbImageResource->Push(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbImageSave(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSaveImage((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbImageSet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbGetImage(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5)); return 0;}		
inline int darklua_dbInKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbInKey()) ; return 1;}		
inline int darklua_dbInkSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbInk(dbRGB(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)),0); return 0;}		
inline int darklua_dbInt(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT((int)dbVal((char*)DARKLUA_STRING(1))); return 1;}		
inline int darklua_dbINT(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbINT(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbJoystickDownGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickDown()) ; return 1;}		
inline int darklua_dbJoystickFireAGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickFireA()) ; return 1;}		
inline int darklua_dbJoystickFireBGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickFireB()) ; return 1;}		
inline int darklua_dbJoystickFireCGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickFireC()) ; return 1;}		
inline int darklua_dbJoystickFireDGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickFireD()) ; return 1;}		
inline int darklua_dbJoystickFireXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickFireX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbJoystickHatAngleGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickHatAngle(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbJoystickLeftGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickLeft()) ; return 1;}		
inline int darklua_dbJoystickRightGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickRight()) ; return 1;}		
inline int darklua_dbJoystickSliderAGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickSliderA()) ; return 1;}		
inline int darklua_dbJoystickSliderBGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickSliderB()) ; return 1;}		
inline int darklua_dbJoystickSliderCGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickSliderC()) ; return 1;}		
inline int darklua_dbJoystickSliderDGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickSliderD()) ; return 1;}		
inline int darklua_dbJoystickTwistXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickTwistX()) ; return 1;}		
inline int darklua_dbJoystickTwistYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickTwistY()) ; return 1;}		
inline int darklua_dbJoystickTwistZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickTwistZ()) ; return 1;}		
inline int darklua_dbJoystickUpGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickUp()) ; return 1;}		
inline int darklua_dbJoystickXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickX()) ; return 1;}		
inline int darklua_dbJoystickYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickY()) ; return 1;}		
inline int darklua_dbJoystickZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbJoystickZ()) ; return 1;}		
inline int darklua_dbKeyStateGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbKeyState(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLeft(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbLeft((char*)DARKLUA_STRING(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLeftKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbLeftKey()) ; return 1;}		
inline int darklua_dbLen(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbLen((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbLightColorSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbColorLight(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLightDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteLight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbLightDirectionalSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetDirectionalLight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbLightDirectionXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLightDirectionX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightDirectionYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLightDirectionY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightDirectionZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLightDirectionZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbLightExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightHide(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbHideLight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbLightMake(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeLight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbLightMappingOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetLightMappingOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLightPoint(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPointLight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbLightPointSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetPointLight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbLightPositionSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPositionLight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbLightPositionXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLightPositionX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightPositionYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLightPositionY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightPositionZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLightPositionZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightRangeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLightRange(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightRangeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetLightRange(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbLightRotate(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbRotateLight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbLightShow(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShowLight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbLightsMaximumGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetMaximumLights()) ; return 1;}		
inline int darklua_dbLightSpotSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetSpotLight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbLightToObjectOrientationSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetLightToObjectOrientation(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLightToObjectPositionSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetLightToObjectPosition(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLightTypeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbLightType(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLightVisibleGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbLightVisible(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbLimbAddSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbAddLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbLimbAngleXGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbAngleX(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbAngleYGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbAngleY(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbAngleZGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbAngleZ(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbColorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbColorLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbLimbDirectionXGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbDirectionX(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbDirectionYGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbDirectionY(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbDirectionZGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbDirectionZ(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbEffectSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetLimbEffect(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbLimbExist(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbLimbExist(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbHide(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbHideLimb(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLimbLinkCheckGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbCheckLimbLink(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbLinkSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbLinkLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbLimbNameGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbLimbName(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbOffsetSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbOffsetLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbLimbOffsetXGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbOffsetX(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbOffsetYGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbOffsetY(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbOffsetZGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbOffsetZ(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbPositionXGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbPositionX(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbPositionYGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbPositionY(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbPositionZGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbPositionZ(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbRemoveSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRemoveLimb(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLimbRotate(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbRotateLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbLimbScaleSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbScaleLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbLimbScaleXGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbScaleX(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbScaleYGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbScaleY(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbScaleZGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbLimbScaleZ(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbShow(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbShowLimb(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLimbSmoothingSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetLimbSmoothing(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbLimbTextureGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbLimbTexture(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbTextureNameGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbLimbTextureName(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLimbTextureScaleSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbScaleLimbTexture(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbLimbTextureScrollSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbScrollLimbTexture(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbLimbTextureSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbTextureLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbLimbVisibleGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbLimbVisible(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbLineSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbLine(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbListenerAngleXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbListenerAngleX()) ; return 1;}		
inline int darklua_dbListenerAngleYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbListenerAngleY()) ; return 1;}		
inline int darklua_dbListenerAngleZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbListenerAngleZ()) ; return 1;}		
inline int darklua_dbListenerPositionSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbPositionListener(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbListenerPositionXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbListenerPositionX()) ; return 1;}		
inline int darklua_dbListenerPositionYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbListenerPositionY()) ; return 1;}		
inline int darklua_dbListenerPositionZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbListenerPositionZ()) ; return 1;}		
inline int darklua_dbListenerRotate(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbRotateListener(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbListenerScaleSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbScaleListener(DARKLUA_FLOAT(1)); return 0;}		
inline int darklua_dbLongWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteLong(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbLower(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(dbLower((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbMakeMeshFromObjectSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeMeshFromObject(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMakeStaticCollisionBoxSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeStaticCollisionBox(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6)); return 0;}		
inline int darklua_dbMatrix4AddSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbAddMatrix4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMatrix4CopySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCopyMatrix4(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMatrix4DeleteGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbDeleteMatrix4(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrix4DivideSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbDivideMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbMatrix4IdentitySet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetIdentityMatrix4(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrix4InverseGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbInverseMatrix4(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbMatrix4IsEqualGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbIsEqualMatrix4(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbMatrix4IsIdentityGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbIsIdentityMatrix4(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrix4LookAtLHBuild(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbBuildLookAtLHMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbMatrix4LookAtRHBuild(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbBuildLookAtRHMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbMatrix4MakeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMakeMatrix4(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrix4MultiplySet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMultiplyMatrix4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMatrix4OrthoLHBuild(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbBuildOrthoLHMatrix4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbMatrix4OrthoRHBuild(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbBuildOrthoRHMatrix4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbMatrix4PerspectiveLHBuild(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbBuildPerspectiveLHMatrix4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbMatrix4PerspectiveRHBuild(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbBuildPerspectiveRHMatrix4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbMatrix4ReflectionBuild(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbBuildReflectionMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbMatrix4RotateXSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRotateXMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbMatrix4RotateYPRSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbRotateYPRMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbMatrix4RotateYSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRotateYMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbMatrix4RotateZSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRotateZMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbMatrix4RotationAxisBuild(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbBuildRotationAxisMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbMatrix4ScaleSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbScaleMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbMatrix4SubtractSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSubtractMatrix4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMatrix4TranslateSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbTranslateMatrix4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbMatrix4TransposeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbTransposeMatrix4(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMatrixDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteMatrix(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMatrixExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrixFillSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbFillMatrix(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMatrixGhostOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbGhostMatrixOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixGhostOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbGhostMatrixOn(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixHeightGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetMatrixHeight(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3))) ; return 1;}		
inline int darklua_dbMatrixHeightSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetMatrixHeight(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbMatrixMake(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbMakeMatrix(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_INT(4),DARKLUA_INT(5)); return 0;}		
inline int darklua_dbMatrixNormalSet(lua_State *L){if(lua_gettop(L) < 6){lua_pushstring(L, "Error! < 6 arguments"); lua_error(L);} dbSetMatrixNormal(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6)); return 0;}		
inline int darklua_dbMatrixPositionSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPositionMatrix(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbMatrixPositionXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbMatrixPositionX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrixPositionYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbMatrixPositionY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrixPositionZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbMatrixPositionZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrixPrioritySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetMatrixPriority(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMatrixRandomizeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRandomizeMatrix(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbMatrixSet(lua_State *L){if(lua_gettop(L) < 8){lua_pushstring(L, "Error! < 8 arguments"); lua_error(L);} dbSetMatrix(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5),DARKLUA_INT(6),DARKLUA_INT(7),DARKLUA_INT(8)); return 0;}		
inline int darklua_dbMatrixShiftDown(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShiftMatrixDown(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixShiftLeft(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShiftMatrixLeft(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixShiftRight(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShiftMatrixRight(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixShiftUp(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShiftMatrixUp(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixTexturePrepareSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPrepareMatrixTexture(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbMatrixTextureSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetMatrixTexture(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMatrixTileCountGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMatrixTileCount(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrixTileSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetMatrixTile(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbMatrixTilesExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMatrixTilesExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMatrixUpdateSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbUpdateMatrix(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixVector3ToPositionSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetVector3ToMatrixPosition(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMatrixWireframeOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetMatrixWireframeOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixWireframeOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetMatrixWireframeOn(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMatrixWireframeStateGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMatrixWireframeState(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMaximumPixelShaderVersionGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetMaximumPixelShaderVersion()) ; return 1;}		
inline int darklua_dbMaximumVertexShaderVersionGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetMaximumVertexShaderVersion()) ; return 1;}		
inline int darklua_dbMemblockByteGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMemblockByte(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbMemblockCopySet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbCopyMemblock(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5)); return 0;}		
inline int darklua_dbMemblockDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteMemblock(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMemblockDwordWrite(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbWriteMemblockDword(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMemblockExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMemblockExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMemblockFloatGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbMemblockFloat(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbMemblockFloatWrite(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbWriteMemblockFloat(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbMemblockFromBitmapMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeMemblockFromBitmap(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMemblockFromImageMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeMemblockFromImage(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMemblockFromMeshMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeMemblockFromMesh(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMemblockFromSoundMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeMemblockFromSound(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMemblockMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeMemblock(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMemblockSizeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbGetMemblockSize(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMemblockWordWrite(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbWriteMemblockWord(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMeshChangeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbChangeMesh(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbMeshDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteMesh(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMeshExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMeshExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMeshFromMemblockChangeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbChangeMeshFromMemblock(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMeshFromMemblockMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeMeshFromMemblock(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMeshLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadMesh((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMeshSave(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSaveMesh((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMid(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbMid((char*)DARKLUA_STRING(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbMipMapAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMipMapAvailable()) ; return 1;}		
inline int darklua_dbMipMapCubeAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMipCubeMapAvailable()) ; return 1;}		
inline int darklua_dbMipMapVolumeAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMipMapVolumeAvailable()) ; return 1;}		
inline int darklua_dbMouseChangeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbChangeMouse(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMouseClickGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMouseClick()) ; return 1;}		
inline int darklua_dbMouseHide(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbHideMouse(); return 0;}		
inline int darklua_dbMouseMoveXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMouseMoveX()) ; return 1;}		
inline int darklua_dbMouseMoveYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMouseMoveY()) ; return 1;}		
inline int darklua_dbMouseMoveZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMouseMoveZ()) ; return 1;}		
inline int darklua_dbMousePositionSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbPositionMouse(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMouseShow(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbShowMouse(); return 0;}		
inline int darklua_dbMouseXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMouseX()) ; return 1;}		
inline int darklua_dbMouseYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMouseY()) ; return 1;}		
inline int darklua_dbMouseZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbMouseZ()) ; return 1;}		
inline int darklua_dbMusicCDLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadCDMusic(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMusicCDTracksGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetNumberOfCDTracks()) ; return 1;}		
inline int darklua_dbMusicDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteMusic(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMusicExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMusicExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMusicLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadMusic((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMusicLoopingGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMusicLooping(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMusicLoopSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbLoopMusic(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMusicPausedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMusicPaused(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMusicPauseSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbPauseMusic(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMusicPlayingGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMusicPlaying(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMusicPlaySet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbPlayMusic(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMusicResumeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbResumeMusic(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMusicSpeedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMusicSpeed(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMusicSpeedSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetMusicSpeed(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbMusicStopSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbStopMusic(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbMusicVolumeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMusicVolume(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbMusicVolumeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetMusicVolume(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbNewXValueGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbNewXValue(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3))) ; return 1;}		
inline int darklua_dbNewYValueGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbNewYValue(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3))) ; return 1;}		
inline int darklua_dbNewZValueGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbNewZValue(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3))) ; return 1;}		
inline int darklua_dbNonLocalVideoMemoryAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbNonLocalVideoMemoryAvailable()) ; return 1;}		
inline int darklua_dbNonPowTexturesAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbNonPowTexturesAvailable()) ; return 1;}		
inline int darklua_dbNormalizationOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetNormalizationOff(); return 0;}		
inline int darklua_dbNormalizationOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetNormalizationOn(); return 0;}		
inline int darklua_dbObjectAmbienceSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectAmbience(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectAmbientSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectAmbient(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectAngleXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectAngleX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectAngleYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectAngleY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectAngleZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectAngleZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectAppend(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbAppendObject((char*)DARKLUA_STRING(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbObjectAutoCollisionSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbAutomaticObjectCollision(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbObjectBoundsHide(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbHideObjectBounds(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectBoundsShow(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShowObjectBounds(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectClone(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCloneObject(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectCollisionBoxDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteObjectCollisionBox(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectCollisionBoxMake(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeObjectCollisionBox(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6),DARKLUA_FLOAT(7),DARKLUA_INT(8)); return 0;}		
inline int darklua_dbObjectCollisionCenterXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectCollisionCenterX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectCollisionCenterYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectCollisionCenterY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectCollisionCenterZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectCollisionCenterZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectCollisionGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbObjectCollision(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbObjectCollisionOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectCollisionOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectCollisionOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectCollisionOn(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectCollisionRadiusGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectCollisionRadius(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectCollisionToBoxesSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectCollisionToBoxes(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectCollisionToPolygonsSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectCollisionToPolygons(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectCollisionToSpheresSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectCollisionToSpheres(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectCollisionXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetObjectCollisionX()) ; return 1;}		
inline int darklua_dbObjectCollisionYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetObjectCollisionY()) ; return 1;}		
inline int darklua_dbObjectCollisionZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetObjectCollisionZ()) ; return 1;}		
inline int darklua_dbObjectColorSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbColorObject(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectConeMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeObjectCone(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectCubeMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeObjectCube(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectCullSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectCull(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectCylinderMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeObjectCylinder(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteObject(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectDiffuseSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectDiffuse(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectEffectSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectEffect(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectEmissiveSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectEmissive(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectFadeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbFadeObject(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectFilterSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectFilter(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectFogSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectFog(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectFrameGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectFrame(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectFrameSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectFrame(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectFramesTotalGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbTotalObjectFrames(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectFromLimbMake(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeObjectFromLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbObjectGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(S3GE::Object::NameMap[DARKLUA_STRING(1)]) ; return 1;}		
inline int darklua_dbObjectGhostOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbGhostObjectOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectGhostOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbGhostObjectOn(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectHide(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbHideObject(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectHitGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbObjectHit(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbObjectInScreenGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectInScreen(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectInstanceSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbInstanceObject(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectInterpolationGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectInterpolation(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectInterpolationSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectInterpolation(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectIntersectGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbIntersectObject(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6),DARKLUA_FLOAT(7))) ; return 1;}		
inline int darklua_dbObjectLightSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectLight(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadObject((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectLockOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbLockObjectOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectLockOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbLockObjectOn(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectLoopingGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectLooping(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectLoopSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbLoopObject(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectMake(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMakeObject(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbObjectMoveDown(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveObjectDown(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectMoveLeft(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveObjectLeft(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectMoveRight(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveObjectRight(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectMove(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveObject(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectMoveUp(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveObjectUp(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectPickGet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbPickObject(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4))) ; return 1;}		
inline int darklua_dbObjectPitchDown(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbPitchObjectDown(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectPitchUp(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbPitchObjectUp(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectPivotFixSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbFixObjectPivot(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectPlainMake(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMakeObjectPlain(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbObjectPlayingGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectPlaying(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectPlaySet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbPlayObject(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectPointSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPointObject(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbObjectPositionSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPositionObject(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbObjectPositionXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectPositionX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectPositionYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectPositionY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectPositionZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectPositionZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectRadiusSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectRadius(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectResourcePop(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);}DARKLUA_RETURNINT(dbObjectResource->Pop()); return 1;}		
inline int darklua_dbObjectResourcePush(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);}dbObjectResource->Push(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectRollLeft(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRollObjectLeft(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectRollRight(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRollObjectRight(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectRotate(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbRotateObject(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbObjectRotateXSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbXRotateObject(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectRotateYSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbYRotateObject(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectRotateZSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbZRotateObject(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectRotationXYZSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectRotationXYZ(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectRotationZYXSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectRotationZYX(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectScaleSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbScaleObject(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbObjectScreenXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectScreenX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectScreenYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectScreenY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetObject(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbObjectShow(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShowObject(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectSizeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectSize(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectSizeXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectSizeX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectSizeYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectSizeY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectSizeZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbObjectSizeZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectSmoothingSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectSmoothing(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectSpecularPowerSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectSpecularPower(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectSpecularSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectSpecular(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectSpeedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectSpeed(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectSpeedSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectSpeed(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectSphereMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMakeObjectSphere(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectSpin(lua_State *L){if(lua_gettop(L) < 4){ lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbRotateObject(DARKLUA_INT(1), dbWrapValue(dbObjectAngleX(DARKLUA_INT(1)) + DARKLUA_FLOAT(2)), dbWrapValue(dbObjectAngleY(DARKLUA_INT(1)) + DARKLUA_FLOAT(3)), dbWrapValue(dbObjectAngleZ(DARKLUA_INT(1)) + DARKLUA_FLOAT(4))); return 0;}		
inline int darklua_dbObjectSpinX(lua_State *L){if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbXRotateObject(DARKLUA_INT(1), dbWrapValue( dbObjectAngleX(DARKLUA_INT(1)) + DARKLUA_FLOAT(2)) );return 0;}		
inline int darklua_dbObjectSpinY(lua_State *L){if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbYRotateObject(DARKLUA_INT(1), dbWrapValue( dbObjectAngleY(DARKLUA_INT(1)) + DARKLUA_FLOAT(2)) );return 0;}		
inline int darklua_dbObjectSpinZ(lua_State *L){if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbZRotateObject(DARKLUA_INT(1), dbWrapValue( dbObjectAngleY(DARKLUA_INT(1)) + DARKLUA_FLOAT(2)) );return 0;}		
inline int darklua_dbObjectStopSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbStopObject(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectTextureScaleSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbScaleObjectTexture(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbObjectTextureScrollSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbScrollObjectTexture(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbObjectTextureSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbTextureObject(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectToCameraOrientationSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetObjectToCameraOrientation(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectToLimbGlueSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbGlueObjectToLimb(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbObjectToObjectOrientationSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectToObjectOrientation(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectTransparencySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectTransparency(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectTriangleMake(lua_State *L){if(lua_gettop(L) < 10){lua_pushstring(L, "Error! < 10 arguments"); lua_error(L);} dbMakeObjectTriangle(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6),DARKLUA_FLOAT(7),DARKLUA_FLOAT(8),DARKLUA_FLOAT(9),DARKLUA_FLOAT(10)); return 0;}		
inline int darklua_dbObjectTurnLeft(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbTurnObjectLeft(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectTurnRight(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbTurnObjectRight(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbObjectUnglueSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbUnglueObject(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectVisibleGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbObjectVisible(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbObjectWireframeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetObjectWireframe(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbObjectZDepthDisable(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDisableObjectZDepth(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbObjectZDepthEnable(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbEnableObjectZDepth(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbPerformCheckListForDrivesSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbPerformCheckListForDrives(); return 0;}		
inline int darklua_dbPerformCheckListForFilesSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbPerformCheckListForFiles(); return 0;}		
inline int darklua_dbPerformCheckListForObjectLimbsSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbPerformCheckListForObjectLimbs(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbPerspectiveTexturesAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbPerspectiveTexturesAvailable()) ; return 1;}		
inline int darklua_dbPickDistanceGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetPickDistance()) ; return 1;}		
inline int darklua_dbPixelShaderDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeletePixelShader(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbPixelShaderExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbPixelShaderExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbPixelShaderFromFileCreateSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCreatePixelShaderFromFile(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbPixelShaderOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetPixelShaderOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbPixelShaderOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetPixelShaderOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbPixelShaderTextureSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetPixelShaderTexture(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbPixelShaderValueMaximumGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetMaximumPixelShaderValue()) ; return 1;}		
inline int darklua_dbPixelsLockSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbLockPixels(); return 0;}		
inline int darklua_dbPixelsPitchGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbGetPixelsPitch()) ; return 1;}		
inline int darklua_dbPixelsPointerGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbGetPixelsPointer()) ; return 1;}		
inline int darklua_dbPixelsUnlockSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbUnlockPixels(); return 0;}		
inline int darklua_dbPointGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbPoint(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbProjectedTexturesAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbProjectedTexturesAvailable()) ; return 1;}		
inline int darklua_dbPromptExitSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbExitPrompt((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbRainbowShadingOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetRainbowShadingOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbRandomizeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbRandomize(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbReflectionShadingOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetReflectionShadingOn(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbRegistryGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetRegistry((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2))) ; return 1;}		
inline int darklua_dbRegistryWrite(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbWriteToRegistry((char*)DARKLUA_STRING(1),(char*)DARKLUA_STRING(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbRenderAfterFlipAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbRenderAfterFlipAvailable()) ; return 1;}		
inline int darklua_dbRenderWindowedAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbRenderWindowedAvailable()) ; return 1;}		
inline int darklua_dbReturnKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbReturnKey()) ; return 1;}		
inline int darklua_dbRGBBGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbRGBB(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbRGBGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbRGB(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3))) ; return 1;}		
inline int darklua_dbRGBGGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbRGBG(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbRGBRGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbRGBR(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbRight(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbRight((char*)DARKLUA_STRING(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbRightKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbRightKey()) ; return 1;}		
inline int darklua_dbRND(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbRND(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbScanCodeGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbScanCode()) ; return 1;}		
inline int darklua_dbScreenDepthGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbScreenDepth()) ; return 1;}		
inline int darklua_dbScreenFPSGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbScreenFPS()) ; return 1;}		
inline int darklua_dbScreenHeightGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbScreenHeight()) ; return 1;}		
inline int darklua_dbScreenInvalidGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbScreenInvalid()) ; return 1;}		
inline int darklua_dbScreenPickSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbPickScreen(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbScreenTypeGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbScreenType()) ; return 1;}		
inline int darklua_dbScreenWidthGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbScreenWidth()) ; return 1;}		
inline int darklua_dbShadowShadingOn(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetShadowShadingOn(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbShiftKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbShiftKey()) ; return 1;}		
inline int darklua_dbSIN(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbSIN(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbSkipBytesSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSkipBytes(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSleepSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSleep(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundClone(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCloneSound(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSoundDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteSound(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundFromMemblockMake(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMakeSoundFromMemblock(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSoundLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadSound((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSoundLoad3DSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoad3DSound((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSoundLoopingGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundLooping(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundLoopSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbLoopSound(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundPanGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundPan(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundPanSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetSoundPan(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSoundPausedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundPaused(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundPauseSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbPauseSound(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundPlayingGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundPlaying(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundPlaySet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbPlaySound(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundPositionSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPositionSound(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbSoundPositionXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbSoundPositionX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundPositionYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbSoundPositionY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundPositionZGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbSoundPositionZ(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundRecordSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbRecordSound(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundResumeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbResumeSound(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundSave(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSaveSound((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSoundSpeedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundSpeed(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundSpeedSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetSoundSpeed(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSoundStopRecordingSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbStopRecordingSound(); return 0;}		
inline int darklua_dbSoundStopSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbStopSound(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSoundTypeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundType(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundVolumeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSoundVolume(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSoundVolumeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetSoundVolume(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpaceKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbSpaceKey()) ; return 1;}		
inline int darklua_dbSphereMappingOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetSphereMappingOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpriteAlphaGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);}DARKLUA_RETURNINT(dbSpriteAlpha(DARKLUA_INT(1))); return 1;}		
inline int darklua_dbSpriteAlphaSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);}dbSetSpriteAlpha(DARKLUA_INT(1), DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpriteAngleGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbSpriteAngle(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteAnimatedCreateSet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbCreateAnimatedSprite(DARKLUA_INT(1),(char*)DARKLUA_STRING(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5)); return 0;}		
inline int darklua_dbSpriteBlueGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteBlue(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteClone(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCloneSprite(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpriteCollisionGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteCollision(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbSpriteCreateSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSprite(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbSpriteDelete(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbDeleteSprite(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSpriteDiffuseSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetSpriteDiffuse(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbSpriteExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteFlippedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteFlipped(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteFlipSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbFlipSprite(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSpriteFrameGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteFrame(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteFrameSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetSpriteFrame(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpriteGreenGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteGreen(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteHeightGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteHeight(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteHide(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbHideSprite(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSpriteHideAllSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbHideAllSprites(); return 0;}		
inline int darklua_dbSpriteHitGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteHit(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbSpriteImageGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteImage(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteImageSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetSpriteImage(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpriteMirroredGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteMirrored(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteMirrorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMirrorSprite(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSpriteMoveSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMoveSprite(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbSpriteOffsetSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbOffsetSprite(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbSpriteOffsetXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteOffsetX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteOffsetYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteOffsetY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpritePaste(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbPasteSprite(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbSpritePlaySet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbPlaySprite(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbSpritePrioritySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetSpritePriority(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpriteRedGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteRed(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteRotate(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbRotateSprite(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbSpriteScaleSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbScaleSprite(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbSpriteScaleXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteScaleX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteScaleYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteScaleY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetSprite(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbSpriteShow(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbShowSprite(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSpriteShowAllSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbShowAllSprites(); return 0;}		
inline int darklua_dbSpriteSizeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSizeSprite(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbSpriteStretchSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbStretchSprite(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbSpriteTextureCoordSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetSpriteTextureCoord(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbSpriteVisibleGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteVisible(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteWidthGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteWidth(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteXGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteX(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSpriteYGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbSpriteY(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbSQRT(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbSQRT(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbSquareTexturesOnlyAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbOnlySquareTexturesAvailable()) ; return 1;}		
inline int darklua_dbStaticCollisionHitGet(lua_State *L){if(lua_gettop(L) < 12){lua_pushstring(L, "Error! < 12 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetStaticCollisionHit(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6),DARKLUA_FLOAT(7),DARKLUA_FLOAT(8),DARKLUA_FLOAT(9),DARKLUA_FLOAT(10),DARKLUA_FLOAT(11),DARKLUA_FLOAT(12))) ; return 1;}		
inline int darklua_dbStaticCollisionXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetStaticCollisionX()) ; return 1;}		
inline int darklua_dbStaticCollisionYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetStaticCollisionY()) ; return 1;}		
inline int darklua_dbStaticCollisionZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetStaticCollisionZ()) ; return 1;}		
inline int darklua_dbStaticLineOfSightGet(lua_State *L){if(lua_gettop(L) < 8){lua_pushstring(L, "Error! < 8 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbStaticLineOfSight(DARKLUA_FLOAT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5),DARKLUA_FLOAT(6),DARKLUA_FLOAT(7),DARKLUA_FLOAT(8))) ; return 1;}		
inline int darklua_dbStaticLineOfSightXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbStaticLineOfSightX()) ; return 1;}		
inline int darklua_dbStaticLineOfSightYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbStaticLineOfSightY()) ; return 1;}		
inline int darklua_dbStaticLineOfSightZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbStaticLineOfSightZ()) ; return 1;}		
inline int darklua_dbStatisticGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbStatistic(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbStr(lua_State *L){if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(dbStr(DARKLUA_FLOAT(1)));return 1;}		
inline int darklua_dbStringReadSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbReadString(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbStringWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteString(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbSuspendForKeySet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSuspendForKey(); return 0;}		
inline int darklua_dbSuspendForMouseSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSuspendForMouse(); return 0;}		
inline int darklua_dbSync(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSync(); return 0;}		
inline int darklua_dbSyncOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSyncOff(); return 0;}		
inline int darklua_dbSyncOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSyncOn(); return 0;}		
inline int darklua_dbSyncRateSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSyncRate(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbSystemKeysDisable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbDisableSystemKeys(); return 0;}		
inline int darklua_dbSystemKeysEnable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbEnableSystemKeys(); return 0;}		
inline int darklua_dbTAN(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbTAN(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbTerrainBuild(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbBuildTerrain(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbTerrainGroundHeightGet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetTerrainGroundHeight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3))) ; return 1;}		
inline int darklua_dbTerrainHeightmapSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetTerrainHeightmap(DARKLUA_INT(1),(char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_dbTerrainLightSet(lua_State *L){if(lua_gettop(L) < 8){lua_pushstring(L, "Error! < 8 arguments"); lua_error(L);} dbSetTerrainLight(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_INT(5),DARKLUA_INT(6),DARKLUA_INT(7),DARKLUA_FLOAT(8)); return 0;}		
inline int darklua_dbTerrainLoad(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbLoadTerrain((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbTerrainObjectMake(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbMakeObjectTerrain(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbTerrainSave(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSaveTerrain((char*)DARKLUA_STRING(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbTerrainScaleSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetTerrainScale(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbTerrainSplitSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetTerrainSplit(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbTerrainTextureSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetTerrainTexture(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbTerrainTilingSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetTerrainTiling(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbTerrainXSizeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetTerrainXSize(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbTerrainZSizeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetTerrainZSize(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbTextBackgroundTypeGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTextBackgroundType()) ; return 1;}		
inline int darklua_dbTextCenterSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbCenterText(DARKLUA_INT(1),DARKLUA_INT(2),(char*)DARKLUA_STRING(3)); return 0;}		
inline int darklua_dbTextFontGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbTextFont()) ; return 1;}		
inline int darklua_dbTextFontSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetTextFont((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbTextHeightGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbTextHeight((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbTextOpaqueSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetTextOpaque(); return 0;}		
inline int darklua_dbTextSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbText(DARKLUA_INT(1),DARKLUA_INT(2),(char*)DARKLUA_STRING(3)); return 0;}		
inline int darklua_dbTextSizeGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTextSize()) ; return 1;}		
inline int darklua_dbTextSizeSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetTextSize(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbTextStyleGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTextStyle()) ; return 1;}		
inline int darklua_dbTextToBoldItalicSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetTextToBoldItalic(); return 0;}		
inline int darklua_dbTextToBoldSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetTextToBold(); return 0;}		
inline int darklua_dbTextToItalicSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetTextToItalic(); return 0;}		
inline int darklua_dbTextToNormalSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetTextToNormal(); return 0;}		
inline int darklua_dbTextTransparentSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetTextTransparent(); return 0;}		
inline int darklua_dbTextureMaximumHeightGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetMaximumTextureHeight()) ; return 1;}		
inline int darklua_dbTextureMaximumWidthGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetMaximumTextureWidth()) ; return 1;}		
inline int darklua_dbTextureSystemMemoryAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTextureSystemMemoryAvailable()) ; return 1;}		
inline int darklua_dbTextureVideoMemoryAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTextureVideoMemoryAvailable()) ; return 1;}		
inline int darklua_dbTextWidthGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbTextWidth((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbTimeGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(dbGetTime()) ; return 1;}		
inline int darklua_dbTimerGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTimer()) ; return 1;}		
inline int darklua_dbTLVertexSystemMemoryAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTLVertexSystemMemoryAvailable()) ; return 1;}		
inline int darklua_dbTLVertexVideoMemoryAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTLVertexVideoMemoryAvailable()) ; return 1;}		
inline int darklua_dbTNLAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbTNLAvailable()) ; return 1;}		
inline int darklua_dbUpKeyGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbUpKey()) ; return 1;}		
inline int darklua_dbUpper(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(dbUpper((char*)DARKLUA_STRING(1))) ; return 1;}		
inline int darklua_dbVal(lua_State *L){if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbVal((char*)DARKLUA_STRING(1))); return 1;}		
inline int darklua_dbVector2AddSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbAddVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector2CoordsTransformSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbTransformCoordsVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector2CopySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCopyVector2(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector2DeleteGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbDeleteVector2(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbVector2DivideSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbDivideVector2(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbVector2DotProductGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbDotProductVector2(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbVector2HermiteSet(lua_State *L){if(lua_gettop(L) < 6){lua_pushstring(L, "Error! < 6 arguments"); lua_error(L);} dbHermiteVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5),DARKLUA_FLOAT(6)); return 0;}		
inline int darklua_dbVector2IsEqualGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbIsEqualVector2(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbVector2LinearInterpolateSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbLinearInterpolateVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbVector2MakeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMakeVector2(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbVector2MaximizeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMaximizeVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector2MinimizeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMinimizeVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector2MultiplySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMultiplyVector2(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbVector2NormalizeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbNormalizeVector2(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector2ScaleSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbScaleVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbVector2Set(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSetVector2(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbVector2SubtractSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSubtractVector2(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3AddSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbAddVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3CoordsTransformSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbTransformCoordsVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3CopySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCopyVector3(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector3CrossProductSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbCrossProductVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3DeleteGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbDeleteVector3(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbVector3DivideSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbDivideVector3(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbVector3DotProductGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbDotProductVector3(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbVector3HermiteSet(lua_State *L){if(lua_gettop(L) < 6){lua_pushstring(L, "Error! < 6 arguments"); lua_error(L);} dbHermiteVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5),DARKLUA_FLOAT(6)); return 0;}		
inline int darklua_dbVector3IsEqualGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbIsEqualVector3(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbVector3LinearInterpolateSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbLinearInterpolateVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbVector3MakeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMakeVector3(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbVector3MaximizeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMaximizeVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3MinimizeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMinimizeVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3MultiplySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMultiplyVector3(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbVector3NormalizeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbNormalizeVector3(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector3NormalsTransformSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbTransformNormalsVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3ProjectSet(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbProjectVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5)); return 0;}		
inline int darklua_dbVector3ScaleSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbScaleVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbVector3Set(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbSetVector3(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbVector3SubtractSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSubtractVector3(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector3ToCameraPositionSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetVector3ToCameraPosition(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector3ToCameraRotationSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetVector3ToCameraRotation(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector3ToLightPositionSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetVector3ToLightPosition(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector3ToLightRotationSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetVector3ToLightRotation(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector4AddSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbAddVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector4CopySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbCopyVector4(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector4DeleteGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbDeleteVector3(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbVector4DivideSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbDivideVector4(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbVector4HermiteSet(lua_State *L){if(lua_gettop(L) < 6){lua_pushstring(L, "Error! < 6 arguments"); lua_error(L);} dbHermiteVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4),DARKLUA_INT(5),DARKLUA_FLOAT(6)); return 0;}		
inline int darklua_dbVector4IsEqualGet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbIsEqualVector4(DARKLUA_INT(1),DARKLUA_INT(2))) ; return 1;}		
inline int darklua_dbVector4LinearInterpolateSet(lua_State *L){if(lua_gettop(L) < 4){lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} dbLinearInterpolateVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_FLOAT(4)); return 0;}		
inline int darklua_dbVector4MakeGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbMakeVector4(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbVector4MaximizeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMaximizeVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector4MinimizeSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbMinimizeVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector4MultiplySet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbMultiplyVector4(DARKLUA_INT(1),DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_dbVector4NormalizeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbNormalizeVector4(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVector4ScaleSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbScaleVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_FLOAT(3)); return 0;}		
inline int darklua_dbVector4Set(lua_State *L){if(lua_gettop(L) < 5){lua_pushstring(L, "Error! < 5 arguments"); lua_error(L);} dbSetVector4(DARKLUA_INT(1),DARKLUA_FLOAT(2),DARKLUA_FLOAT(3),DARKLUA_FLOAT(4),DARKLUA_FLOAT(5)); return 0;}		
inline int darklua_dbVector4SubtractSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbSubtractVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVector4TransformSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbTransformVector4(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbVectorPickXGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetPickVectorX()) ; return 1;}		
inline int darklua_dbVectorPickYGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetPickVectorY()) ; return 1;}		
inline int darklua_dbVectorPickZGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(dbGetPickVectorZ()) ; return 1;}		
inline int darklua_dbVertexShaderConstantsMaximumGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetMaximumVertexShaderConstants()) ; return 1;}		
inline int darklua_dbVertexShaderExist(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(dbVertexShaderExist(DARKLUA_INT(1))) ; return 1;}		
inline int darklua_dbVertexShaderMatrixSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetVertexShaderMatrix(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbVertexShaderOff(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetVertexShaderOff(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbVertexShaderOn(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetVertexShaderOn(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVertexShaderStreamCountSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetVertexShaderStreamCount(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbVertexShaderStreamSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetVertexShaderStream(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbVertexShaderVectorSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetVertexShaderVector(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_INT(3),DARKLUA_INT(4)); return 0;}		
inline int darklua_dbVideoMemoryFlushSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbFlushVideoMemory(); return 0;}		
inline int darklua_dbVolumeExtentMaximumGet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbGetMaximumVolumeExtent()) ; return 1;}		
inline int darklua_dbVolumeMapAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbVolumeMapAvailable()) ; return 1;}		
inline int darklua_dbWaitKeySet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbWaitKey(); return 0;}		
inline int darklua_dbWaitMouseSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbWaitMouse(); return 0;}		
inline int darklua_dbWaitSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbWait(DARKLUA_INT(1)); return 0;}		
inline int darklua_dbWBufferAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbWBufferAvailable()) ; return 1;}		
inline int darklua_dbWFogAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbWFogAvailable()) ; return 1;}		
inline int darklua_dbWindowHide(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbHideWindow(); return 0;}		
inline int darklua_dbWindowMaximizeSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbMaximizeWindow(); return 0;}		
inline int darklua_dbWindowMinimizeSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbMinimizeWindow(); return 0;}		
inline int darklua_dbWindowOff(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetWindowOff(); return 0;}		
inline int darklua_dbWindowOn(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbSetWindowOn(); return 0;}		
inline int darklua_dbWindowPositionSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetWindowPosition(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbWindowRestoreSet(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbRestoreWindow(); return 0;}		
inline int darklua_dbWindowShow(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} dbShowWindow(); return 0;}		
inline int darklua_dbWindowSizeSet(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbSetWindowSize(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbWindowTitleSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} dbSetWindowTitle((char*)DARKLUA_STRING(1)); return 0;}		
inline int darklua_dbWordWrite(lua_State *L){if(lua_gettop(L) < 2){lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} dbWriteWord(DARKLUA_INT(1),DARKLUA_INT(2)); return 0;}		
inline int darklua_dbWrapValueGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNFLOAT(dbWrapValue(DARKLUA_FLOAT(1))) ; return 1;}		
inline int darklua_dbWriteByteToFileSet(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} dbWriteByteToFile((char*)DARKLUA_STRING(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_dbZBufferAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbZBufferAvailable()) ; return 1;}		
inline int darklua_dbZFogAvailable(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(dbZFogAvailable()) ; return 1;}		

/**/
inline int darklua_fxFuzzFragmentCount(lua_State *L){if(lua_gettop(L) > 0){lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);}DARKLUA_RETURNINT(Illudium::Fuzz::CurrentFuzz != NULL ? Illudium::Fuzz::CurrentFuzz->FragmentCount-1: 0);	return 1;}	
inline int darklua_fxFuzzFragmentGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! > 1 arguments");lua_error(L);}DARKLUA_RETURNPOINTER( Illudium::Fuzz::CurrentFuzz != NULL ? (MAUI::Gizmo*) Illudium::Fuzz::CurrentFuzz->FragmentArray[DARKLUA_INT(1)]: NULL );return 1;}		
inline int darklua_fxFuzzFragmentSet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! > 1 arguments"); lua_error(L);} Illudium::Fuzz::CurrentFuzz = (Illudium::Fuzz*)DARKLUA_POINTER(1) ; return 0;}		

inline int darklua_luaScriptExecute(lua_State *L){if(lua_gettop(L) < 3){lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);}DARKLUA_RETURNSTRING(DarkLUA::System::Execute(DARKLUA_STRING(1), DARKLUA_STRING(2), (char*)DARKLUA_STRING(3)).c_str());	return 1;}
inline int darklua_netHTTPFileGet(lua_State *L){ if(lua_gettop(L) < 6){ lua_pushstring(L, "Error! < 6 arguments"); lua_error(L);} DarkNet::HTTP::FileGet(DARKLUA_STRING(1), DARKLUA_INT(2), DARKLUA_STRING(3), DARKLUA_INT(4), DARKLUA_STRING(5), DARKLUA_STRING(6), DARKLUA_INT(7)); return 0;}		
//inline int darklua_netHTTPRequestHeader(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} mnAddStringC(DARKLUA_INT(1), (char*)DARKLUA_STRING(2), 0, false); return 0;}		
inline int darklua_phyActorFastUpdate(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->updateActorFast(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyActorRelease(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->releaseActor(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyActorsUpdate(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->updateActors(); return 0 ;} 
inline int darklua_phyActorUpdate(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->updateActor(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyAngularDampingSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->setAngularDamping(DARKLUA_INT(1), DARKLUA_FLOAT(2)); return 0 ;} 
inline int darklua_phyAngularVelocitySet(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->setAngularVelocity(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyAngularVelocityXGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getAngularVelocityX(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyAngularVelocityYGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getAngularVelocityY(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyAngularVelocityZGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getAngularVelocityZ(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyBoxMake(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeBox(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3))); return 1 ;} 
inline int darklua_phyBoxShapeMake(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeBoxShape(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyCapsuleMake(lua_State *L){ if(lua_gettop(L) < 5){ lua_pushstring(L,"Error! < 5 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeCapsule(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4), DARKLUA_FLOAT(5))); return 1 ;} 
//inline int darklua_phyCharacterControllerMove(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} Core->Physics->moveCharacterController(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3)); return 0 ;} 
inline int darklua_phyCharacterControllerMove(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->moveCharacterController(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyCharacterControllerPosition(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->positionCharacterController(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyCMassLocalPositionSet(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->setCMassLocalPosition(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyCMassLocalPositionXGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getCMassLocalPositionX(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyCMassLocalPositionYGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getCMassLocalPositionY(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyCMassLocalPositionZGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getCMassLocalPositionZ(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyCollisionGroupSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->setCollisionGroup(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyCollisionOffSet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->setCollisionOff(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyCollisionOnSet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->setCollisionOn(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyCompoundActorMake(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeCompoundActor(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3))); return 1 ;} 
inline int darklua_phyContactActorAGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->getContactActorA()); return 1 ;} 
inline int darklua_phyContactActorBGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->getContactActorB()); return 1 ;} 
inline int darklua_phyContactDataGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->getContactData()); return 1 ;} 
inline int darklua_phyContactPairRelease(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->releaseContactPair(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyContactPairSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->setContactPair(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
//inline int darklua_phyControllerBoxMake(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeControllerBox(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_INT(4))); return 1 ;} 
inline int darklua_phyControllerBoxMake(lua_State *L){ if(lua_gettop(L) < 6){ lua_pushstring(L,"Error! < 6 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeControllerBox(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4), DARKLUA_FLOAT(5), DARKLUA_FLOAT(6))); return 1 ;} 
//inline int darklua_phyControllerCapsuleMake(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeControllerCapsule(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_INT(4))); return 1 ;} 
inline int darklua_phyControllerCapsuleMake(lua_State *L){ if(lua_gettop(L) < 5){ lua_pushstring(L,"Error! < 5 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeControllerCapsule(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4), DARKLUA_FLOAT(5))); return 1 ;} 
//inline int darklua_phyControllerDimensionsSet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->setControllerDimensions(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_INT(3))); return 1 ;} 
inline int darklua_phyControllerDimensionsSet(lua_State *L){ if(lua_gettop(L) < 5){ lua_pushstring(L,"Error! < 5 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->setControllerDimensions(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4), DARKLUA_INT(5))); return 1 ;} 
inline int darklua_phyControllerLocalPositionYGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getControllerLocalPositionY(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyControllerLocalPositionYSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->setControllerLocalPositionY(DARKLUA_INT(1), DARKLUA_FLOAT(2)); return 0 ;} 
inline int darklua_phyControllerRelease(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->releaseController(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyControllersUpdate(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->updateControllers(); return 0 ;} 
inline int darklua_phyConvexMeshMake(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeConvexMesh(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3))); return 1 ;} 
inline int darklua_phyConvexShapeMake(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeConvexShape(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyDefaultDynamicFrictionGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getDefaultDynamicFriction()); return 1 ;} 
inline int darklua_phyDefaultDynamicFrictionSet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->setDefaultDynamicFriction(DARKLUA_FLOAT(1)); return 0 ;} 
inline int darklua_phyDefaultRestitutionGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getDefaultRestitution()); return 1 ;} 
inline int darklua_phyDefaultRestitutionSet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->setDefaultRestitution(DARKLUA_FLOAT(1)); return 0 ;} 
inline int darklua_phyDefaultSkinWidthGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getDefaultSkinWidth()); return 1 ;} 
inline int darklua_phyDefaultSkinWidthSet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->setDefaultSkinWidth(DARKLUA_FLOAT(1)); return 0 ;} 
inline int darklua_phyDefaultStaticFrictionGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getDefaultStaticFriction()); return 1 ;} 
inline int darklua_phyDefaultStaticFrictionSet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->setDefaultStaticFriction(DARKLUA_FLOAT(1)); return 0 ;} 
inline int darklua_phyForceApply(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->applyForce(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyGravityDisable(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->disableGravity(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyGravityEnable(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->enableGravity(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyGravitySet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} Core->Physics->setGravity(DARKLUA_FLOAT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3)); return 0 ;} 
inline int darklua_phyGroundPlaneMake(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->makeGroundPlane(); return 0 ;} 
inline int darklua_phyGroundPlaneRelease(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->releaseGroundPlane(); return 0 ;} 
inline int darklua_phyGroupCollisionSet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} Core->Physics->setGroupCollision(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_INT(3)); return 0 ;} 
inline int darklua_phyKinematicOffSet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->setKinematicOff(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyKinematicOnSet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->setKinematicOn(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyLinearDampingSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->setLinearDamping(DARKLUA_INT(1), DARKLUA_FLOAT(2)); return 0 ;} 
inline int darklua_phyLinearVelocitySet(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->setLinearVelocity(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyLinearVelocityXGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getLinearVelocityX(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyLinearVelocityYGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getLinearVelocityY(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyLinearVelocityZGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getLinearVelocityZ(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyLocalForceApply(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->applyLocalForce(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyLocalTorqueApply(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->applyLocalTorque(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyMaterialMake(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->makeMaterial(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
//inline int darklua_phyMaterialSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->setMaterial(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyMaterialSet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} Core->Physics->setMaterial(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_INT(3)); return 0 ;} 
inline int darklua_phyObjectSwap(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->swapObject(DARKLUA_INT(1), DARKLUA_INT(2))); return 1 ;} 
inline int darklua_phyOrientationSet(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->setOrientation(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyPhysicsResultsGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->getPhysicsResults(); return 0 ;} 
inline int darklua_phyPositionSet(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->setPosition(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyPositionXFreeze(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->freezePositionX(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyPositionYFreeze(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->freezePositionY(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyPositionZFreeze(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->freezePositionZ(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyRaycast(lua_State *L){ if(lua_gettop(L) < 6){ lua_pushstring(L,"Error! < 6 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->raycast(DARKLUA_FLOAT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4), DARKLUA_FLOAT(5), DARKLUA_FLOAT(6))); return 1 ;} 
inline int darklua_phyRayDistanceGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getRayDistance()); return 1 ;} 
inline int darklua_phyRayImpactNormalXGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getRayImpactNormalX()); return 1 ;} 
inline int darklua_phyRayImpactNormalYGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getRayImpactNormalY()); return 1 ;} 
inline int darklua_phyRayImpactNormalZGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getRayImpactNormalZ()); return 1 ;} 
inline int darklua_phyRayImpactPosXGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getRayImpactPosX()); return 1 ;} 
inline int darklua_phyRayImpactPosYGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getRayImpactPosY()); return 1 ;} 
inline int darklua_phyRayImpactPosZGet(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} DARKLUA_RETURNFLOAT(Core->Physics->getRayImpactPosZ()); return 1 ;} 
inline int darklua_phyRotationXFreeze(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->freezeRotationX(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyRotationYFreeze(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->freezeRotationY(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phyRotationZFreeze(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L,"Error! < 2 arguments"); lua_error(L);} Core->Physics->freezeRotationZ(DARKLUA_INT(1), DARKLUA_INT(2)); return 0 ;} 
inline int darklua_phySimulate(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->simulate(); return 0 ;} 
inline int darklua_phySphereMake(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeSphere(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3))); return 1 ;} 
inline int darklua_phySphereShapeMake(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeSphereShape(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyStart(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->start(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyStop(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->stop(); return 0 ;} 
inline int darklua_phyTorqueApply(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} Core->Physics->applyTorque(DARKLUA_INT(1), DARKLUA_FLOAT(2), DARKLUA_FLOAT(3), DARKLUA_FLOAT(4)); return 0 ;} 
inline int darklua_phyTriangleMeshFromDBOMake(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeTriangleMeshFromDBO(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyTriangleMeshMake(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeTriangleMesh(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyUpdate(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L,"Error! > 0 arguments"); lua_error(L);} Core->Physics->update(); return 0 ;} 
inline int darklua_phyVehicleBuild(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->buildVehicle(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyVehicleMake(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeVehicle(DARKLUA_INT(1))); return 1 ;} 
inline int darklua_phyWheelDrive(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} Core->Physics->driveWheel(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3)); return 0 ;} 
inline int darklua_phyWheelShapeMake(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L,"Error! < 4 arguments"); lua_error(L);} DARKLUA_RETURNINT(Core->Physics->makeWheelShape(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_INT(3), DARKLUA_FLOAT(4))); return 1 ;} 
inline int darklua_phyWheelSteer(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} Core->Physics->steerWheel(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3)); return 0 ;} 
inline int darklua_phyWheelsUpdate(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L,"Error! < 1 arguments"); lua_error(L);} Core->Physics->updateWheels(DARKLUA_INT(1)); return 0 ;} 
inline int darklua_phyWheelSuspensionTravelMaxSet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L,"Error! < 3 arguments"); lua_error(L);} Core->Physics->setWheelSuspensionTravelMax(DARKLUA_INT(1), DARKLUA_INT(2), DARKLUA_FLOAT(3)); return 0 ;} 
inline int darklua_sysConfigPropertyGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(S3GE::System::ConfigPropertyGet(DARKLUA_STRING(1)).c_str()); return 1;}		
inline int darklua_sysConfigPropertySet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} S3GE::System::ConfigPropertySet((char*)DARKLUA_STRING(1), (char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_sysConfigPropertyValueGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(S3GE::System::ConfigPropertyValueGet(DARKLUA_STRING(1)).c_str()); return 1;}		
inline int darklua_sysConfigPropertyValueSet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} S3GE::System::ConfigPropertyValueSet((char*)DARKLUA_STRING(1), (char*)DARKLUA_STRING(2)); return 0;}		
inline int darklua_tbGameAppEntry(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} TBGameApp->Entry() ; return 0;}		
inline int darklua_tbGameAppList(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} TBGameApp->List() ; return 0;}
inline int darklua_tbGameAppRegister(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} TBGameApp->Register() ; return 0;}		
inline int darklua_tbGameAppReset(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} TBGameApp->Reset() ; return 0;}		
inline int darklua_tbGameAppResults(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} TBGameApp->Results() ; return 0;}		
inline int darklua_tbGameAppStats(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} TBGameApp->Stats() ; return 0;}		
inline int darklua_tbGameAppTest(lua_State *L){ if(lua_gettop(L) > 0){ lua_pushstring(L, "Error! > 0 arguments"); lua_error(L);} TBGameApp->Test() ; return 0;}		
inline int darklua_tbGameAppVariableGet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(TBGameApp->VariableGet(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_STRING(3)).c_str()); return 1;}		
inline int darklua_tbGameAppVariableSet(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} TBGameApp->VariableSet(DARKLUA_INT(1),DARKLUA_INT(2),DARKLUA_STRING(3),DARKLUA_STRING(4)); return 0;}		
inline int darklua_testBed(lua_State *L){ if(lua_gettop(L) < 6){ lua_pushstring(L, "Error! < 6 arguments"); lua_error(L);} DarkNet::HTTP::FileGet(DARKLUA_STRING(1), DARKLUA_INT(2), DARKLUA_STRING(3), DARKLUA_INT(4), DARKLUA_STRING(5), DARKLUA_STRING(6)); return 0;}		
inline int darklua_uiCaretEdit(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::LineCaretEdit((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2)); return 0;}		
inline int darklua_uiCaretLocate(lua_State *L){if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::LineCaretLocate((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2)); return 0;}		
inline int darklua_uiFormSubmit(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} MAUI::HTTPForm::Submit(DARKLUA_STRING(1)); return 0;}		
inline int darklua_uiGizmoCapture(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::Capture((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2)); return 0;}		
inline int darklua_uiGizmoColor(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} MAUI::Gizmo::Color((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2), DARKLUA_INT(3), DARKLUA_INT(4)); return 0;}		
inline int darklua_uiGizmoExist(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNINT(MAUI::Gizmo::Exist(DARKLUA_STRING(1)));return 1;}		
inline int darklua_uiGizmoGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNPOINTER((MAUI::Gizmo*)MAUI::Gizmo::Get(DARKLUA_STRING(1)));return 1;}		
inline int darklua_uiGizmoLineDisplay(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} MAUI::Gizmo::LineTextDisplay((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2), DARKLUA_INT(3), DARKLUA_INT(4)); return 0;}		
inline int darklua_uiGizmoLineEdit(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::LineTextEdit((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2));return 0;}		
inline int darklua_uiGizmoLinesCapture(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::LineTextCapture((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2)); return 0;}		
inline int darklua_uiGizmoLinesCopy(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::LineTextCopy(DARKLUA_STRING(1), DARKLUA_STRING(2)); return 0;}		
inline int darklua_uiGizmoLineSelectionEdit(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);}MAUI::Gizmo::LineSelectionEdit((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_INT(2)); return 0;}		
inline int darklua_uiGizmoLinesGet(lua_State *L){if(lua_gettop(L) < 1){lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(MAUI::Gizmo::LineTextGet( (MAUI::Gizmo*)DARKLUA_POINTER(1) ).c_str()); return 1;}
inline int darklua_uiGizmoMessageCreate(lua_State *L){ if(lua_gettop(L) > 1){lua_pushstring(L, "Error! > 1 argument"); lua_error(L);} DARKLUA_RETURNPOINTER(MAUI::Message::Create(DARKLUA_INT(1))); return 1;}		
inline int darklua_uiGizmoMessageDestroy(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} MAUI::Message::Destroy((MAUI::Message*)DARKLUA_POINTER(1)); return 0;}		
inline int darklua_uiGizmoMessageInsert(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} MAUI::Message::Insert((MAUI::Message*)DARKLUA_POINTER(1), DARKLUA_INT(2), DARKLUA_STRING(3), DARKLUA_STRING(4)); return 0;}		
inline int darklua_uiGizmoMessageSend(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} MAUI::Gizmo::MessageSend((MAUI::Message*)DARKLUA_POINTER(1), DARKLUA_STRING(2), DARKLUA_INT(3), DARKLUA_INT(4)); return 0;}		
inline int darklua_uiGizmoPropertyGet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(MAUI::Gizmo::PropertyGet((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_STRING(2))); return 1;}		
inline int darklua_uiGizmoPropertyGetByEventstate(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(MAUI::Gizmo::PropertyGet((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_STRING(2), DARKLUA_INT(3))); return 1;}		
inline int darklua_uiGizmoPropertySet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} MAUI::Gizmo::PropertySet((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_STRING(2), (char*)DARKLUA_STRING(3)); return 0;}		
inline int darklua_uiGizmoPropertySetByEventstate(lua_State *L){ if(lua_gettop(L) < 4){ lua_pushstring(L, "Error! < 4 arguments"); lua_error(L);} MAUI::Gizmo::PropertySet((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_STRING(2), (char*)DARKLUA_STRING(3), DARKLUA_INT(4)); return 0;}		
inline int darklua_uiGizmoSpin(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::Spin((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_FLOAT(2)); return 0;}		
inline int darklua_uiGizmoVariableGet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} DARKLUA_RETURNSTRING(MAUI::Gizmo::VariableGet((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_STRING(2))); return 1;}		
inline int darklua_uiGizmoVariableSet(lua_State *L){ if(lua_gettop(L) < 3){ lua_pushstring(L, "Error! < 3 arguments"); lua_error(L);} MAUI::Gizmo::VariableSet((MAUI::Gizmo*)DARKLUA_POINTER(1), DARKLUA_STRING(2), DARKLUA_STRING(3)); return 0;}		
inline int darklua_uiLoad(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} Scenergy::System::Load(DARKLUA_STRING(1),DARKLUA_INT(2),DARKLUA_INT(3)); return 0;}		
inline int darklua_uiOutput(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} Output = DARKLUA_STRING(1); return 0;}
inline int darklua_uiPointerPropertyGet(lua_State *L){ if(lua_gettop(L) < 1){ lua_pushstring(L, "Error! < 1 argument"); lua_error(L);} DARKLUA_RETURNSTRING(MAUI::Gizmo::PropertyGet(MAUI::Gizmo::Pointer, DARKLUA_STRING(1))); return 1;}		
inline int darklua_uiPointerPropertySet(lua_State *L){ if(lua_gettop(L) < 2){ lua_pushstring(L, "Error! < 2 arguments"); lua_error(L);} MAUI::Gizmo::PropertySet(MAUI::Gizmo::Pointer, DARKLUA_STRING(1), (char*)DARKLUA_STRING(2)); return 0;}		

void DarkLUA::System::Bindings(void){
	
/**
* @brief	Catalog of Registered Bind Functions (Alphabetically Ordered)
*
* @location	[source]LUA for Windows 5.1.4 (HTTP://luaforwindows.luaforge.net)
*
* @param	int ID = Task ID
*
* @return	none
*/

lua_register(L, "aiNavGeometryLoad", darklua_aiNavGeometryLoad);
lua_register(L, "bugLogAppend", darklua_bugLogAppend);
lua_register(L, "bugLogDisable", darklua_bugLogDisable);
lua_register(L, "bugLogClear", darklua_bugLogClear);
lua_register(L, "bugLogEnable", darklua_bugLogEnable);		
lua_register(L, "bugLogPrint", darklua_bugLogPrint);		
lua_register(L, "dbABS", darklua_dbABS);		
lua_register(L, "dbACOS", darklua_dbACOS);		
lua_register(L, "dbAlphaAvailable", darklua_dbAlphaAvailable);		
lua_register(L, "dbAlphaBlendingAvailable", darklua_dbAlphaBlendingAvailable);		
lua_register(L, "dbAlphaComparisionAvailable", darklua_dbAlphaComparisionAvailable);		
lua_register(L, "dbAlphaMappingOn", darklua_dbAlphaMappingOn);		
lua_register(L, "dbAmbientLightColorSet", darklua_dbAmbientLightColorSet);		
lua_register(L, "dbAmbientLightSet", darklua_dbAmbientLightSet);		
lua_register(L, "dbAntiAliasAvailable", darklua_dbAntiAliasAvailable);		
lua_register(L, "dbAsc", darklua_dbAsc);		
lua_register(L, "dbASIN", darklua_dbASIN);		
lua_register(L, "dbATAN", darklua_dbATAN);		
lua_register(L, "dbATANFULL", darklua_dbATANFULL);		
lua_register(L, "dbAutoCameraOff", darklua_dbAutoCameraOff);		
lua_register(L, "dbAutoCameraOn", darklua_dbAutoCameraOn);		
lua_register(L, "dbBackdropColorSet", darklua_dbBackdropColorSet);		
lua_register(L, "dbBackdropOff", darklua_dbBackdropOff);		
lua_register(L, "dbBackdropOn", darklua_dbBackdropOn);		
lua_register(L, "dbBackdropScrollSet", darklua_dbBackdropScrollSet);		
lua_register(L, "dbBackdropTextureSet", darklua_dbBackdropTextureSet);		
lua_register(L, "dbBin", darklua_dbBin);		
lua_register(L, "dbBitmapBlurSet", darklua_dbBitmapBlurSet);		
lua_register(L, "dbBitmapCopySet", darklua_dbBitmapCopySet);		
lua_register(L, "dbBitmapCreateSet", darklua_dbBitmapCreateSet);		
lua_register(L, "dbBitmapCurrentGet", darklua_dbBitmapCurrentGet);		
lua_register(L, "dbBitmapCurrentSet", darklua_dbBitmapCurrentSet);		
lua_register(L, "dbBitmapDelete", darklua_dbBitmapDelete);		
lua_register(L, "dbBitmapDepthGet", darklua_dbBitmapDepthGet);		
lua_register(L, "dbBitmapExist", darklua_dbBitmapExist);		
lua_register(L, "dbBitmapFadeSet", darklua_dbBitmapFadeSet);		
lua_register(L, "dbBitmapFlippedGet", darklua_dbBitmapFlippedGet);		
lua_register(L, "dbBitmapFlipSet", darklua_dbBitmapFlipSet);		
lua_register(L, "dbBitmapFromMemblockMake", darklua_dbBitmapFromMemblockMake);		
lua_register(L, "dbBitmapHeightGet", darklua_dbBitmapHeightGet);		
lua_register(L, "dbBitmapLoad", darklua_dbBitmapLoad);		
lua_register(L, "dbBitmapMirroredGet", darklua_dbBitmapMirroredGet);		
lua_register(L, "dbBitmapMirrorSet", darklua_dbBitmapMirrorSet);		
lua_register(L, "dbBitmapWidthGet", darklua_dbBitmapWidthGet);		
lua_register(L, "dbBlitSysToLocalAvailable", darklua_dbBlitSysToLocalAvailable);		
lua_register(L, "dbBoxSet", darklua_dbBoxSet);		
lua_register(L, "dbBSPCameraCollisionRadiusSet", darklua_dbBSPCameraCollisionRadiusSet);		
lua_register(L, "dbBSPCameraCollisionSet", darklua_dbBSPCameraCollisionSet);		
lua_register(L, "dbBSPCameraSet", darklua_dbBSPCameraSet);		
lua_register(L, "dbBSPCollisionHeightAdjustmentSet", darklua_dbBSPCollisionHeightAdjustmentSet);		
lua_register(L, "dbBSPCollisionHitGet", darklua_dbBSPCollisionHitGet);		
lua_register(L, "dbBSPCollisionOff", darklua_dbBSPCollisionOff);		
lua_register(L, "dbBSPCollisionProcessSet", darklua_dbBSPCollisionProcessSet);		
lua_register(L, "dbBSPCollisionThresholdSet", darklua_dbBSPCollisionThresholdSet);		
lua_register(L, "dbBSPCollisionXGet", darklua_dbBSPCollisionXGet);		
lua_register(L, "dbBSPCollisionYGet", darklua_dbBSPCollisionYGet);		
lua_register(L, "dbBSPCollisionZGet", darklua_dbBSPCollisionZGet);		
lua_register(L, "dbBSPDelete", darklua_dbBSPDelete);		
lua_register(L, "dbBSPLoad", darklua_dbBSPLoad);		
lua_register(L, "dbBSPMultiTexturingOff", darklua_dbBSPMultiTexturingOff);		
lua_register(L, "dbBSPMultiTexturingOn", darklua_dbBSPMultiTexturingOn);		
lua_register(L, "dbBSPObjectCollisionRadiusSet", darklua_dbBSPObjectCollisionRadiusSet);		
lua_register(L, "dbBSPObjectCollisionSet", darklua_dbBSPObjectCollisionSet);		
lua_register(L, "dbBumpMappingOn", darklua_dbBumpMappingOn);		
lua_register(L, "dbByteFromFileRead", darklua_dbByteFromFileRead);		
lua_register(L, "dbByteWrite", darklua_dbByteWrite);		
lua_register(L, "dbCalibrateGammaAvailable", darklua_dbCalibrateGammaAvailable);		
lua_register(L, "dbCameraAngleXGet", darklua_dbCameraAngleXGet);		
lua_register(L, "dbCameraAngleYGet", darklua_dbCameraAngleYGet);		
lua_register(L, "dbCameraAngleZGet", darklua_dbCameraAngleZGet);		
lua_register(L, "dbCameraAspectSet", darklua_dbCameraAspectSet);		
lua_register(L, "dbCameraAutoCollisionSet", darklua_dbCameraAutoCollisionSet);		
lua_register(L, "dbCameraClearViewSet", darklua_dbCameraClearViewSet);		
lua_register(L, "dbCameraCurrentSet", darklua_dbCameraCurrentSet);		
lua_register(L, "dbCameraDelete", darklua_dbCameraDelete);		
lua_register(L, "dbCameraFOVSet", darklua_dbCameraFOVSet);		
lua_register(L, "dbCameraMake", darklua_dbCameraMake);		
lua_register(L, "dbCameraMove", darklua_dbCameraMove);		
lua_register(L, "dbCameraMoveSet", darklua_dbCameraMoveSet);		
lua_register(L, "dbCameraPitchDown", darklua_dbCameraPitchDown);		
lua_register(L, "dbCameraPitchUp", darklua_dbCameraPitchUp);		
lua_register(L, "dbCameraPoint", darklua_dbCameraPoint);		
lua_register(L, "dbCameraPositionSet", darklua_dbCameraPositionSet);		
lua_register(L, "dbCameraPositionXGet", darklua_dbCameraPositionXGet);		
lua_register(L, "dbCameraPositionYGet", darklua_dbCameraPositionYGet);		
lua_register(L, "dbCameraPositionZGet", darklua_dbCameraPositionZGet);		
lua_register(L, "dbCameraRangeSet", darklua_dbCameraRangeSet);		
lua_register(L, "dbCameraRollLeft", darklua_dbCameraRollLeft);		
lua_register(L, "dbCameraRollRight", darklua_dbCameraRollRight);		
lua_register(L, "dbCameraRotate", darklua_dbCameraRotate);		
lua_register(L, "dbCameraRotateXSet", darklua_dbCameraRotateXSet);		
lua_register(L, "dbCameraRotateYSet", darklua_dbCameraRotateYSet);		
lua_register(L, "dbCameraRotateZSet", darklua_dbCameraRotateZSet);		
lua_register(L, "dbCameraRotationXYZSet", darklua_dbCameraRotationXYZSet);		
lua_register(L, "dbCameraRotationZYXSet", darklua_dbCameraRotationZYXSet);		
lua_register(L, "dbCameraToFollow", darklua_dbCameraToFollow);		
lua_register(L, "dbCameraToImageSet", darklua_dbCameraToImageSet);		
lua_register(L, "dbCameraToObjectOrientationSet", darklua_dbCameraToObjectOrientationSet);		
lua_register(L, "dbCameraTurnLeft", darklua_dbCameraTurnLeft);		
lua_register(L, "dbCameraTurnRight", darklua_dbCameraTurnRight);		
lua_register(L, "dbCameraViewSet", darklua_dbCameraViewSet);		
lua_register(L, "dbCartoonShadingOn", darklua_dbCartoonShadingOn);		
lua_register(L, "dbChr", darklua_dbChr);		
lua_register(L, "dbCircleSet", darklua_dbCircleSet);		
lua_register(L, "dbCLGet", darklua_dbCLGet);		
lua_register(L, "dbClipAndScalePointsAvailable", darklua_dbClipAndScalePointsAvailable);		
lua_register(L, "dbClipboardGet", darklua_dbClipboardGet);		
lua_register(L, "dbClipboardWrite", darklua_dbClipboardWrite);		
lua_register(L, "dbClipTLVertsAvailable", darklua_dbClipTLVertsAvailable);		
lua_register(L, "dbCLSSet", darklua_dbCLSSet);		
lua_register(L, "dbColorPerspectiveAvailable", darklua_dbColorPerspectiveAvailable);		
lua_register(L, "dbColorWriteEnableAvailable", darklua_dbColorWriteEnableAvailable);		
lua_register(L, "dbControlCameraUsingArrowKeysSet", darklua_dbControlCameraUsingArrowKeysSet);		
lua_register(L, "dbControlDeviceSet", darklua_dbControlDeviceSet);		
lua_register(L, "dbControlDeviceXGet", darklua_dbControlDeviceXGet);		
lua_register(L, "dbControlDeviceYGet", darklua_dbControlDeviceYGet);		
lua_register(L, "dbControlDeviceZGet", darklua_dbControlDeviceZGet);		
lua_register(L, "dbControlKeyGet", darklua_dbControlKeyGet);		
lua_register(L, "dbConvertObjectFVFSet", darklua_dbConvertObjectFVFSet);		
lua_register(L, "dbCOS", darklua_dbCOS);		
lua_register(L, "dbCreateVertexShaderFromFileSet", darklua_dbCreateVertexShaderFromFileSet);		
lua_register(L, "dbCubeMapAvailable", darklua_dbCubeMapAvailable);		
lua_register(L, "dbCullCCWAvailable", darklua_dbCullCCWAvailable);		
lua_register(L, "dbCullCWAvailable", darklua_dbCullCWAvailable);		
lua_register(L, "dbCurrentGraphicsCardGet", darklua_dbCurrentGraphicsCardGet);		
lua_register(L, "dbCursorSet", darklua_dbCursorSet);		
lua_register(L, "dbCurveAngleGet", darklua_dbCurveAngleGet);		
lua_register(L, "dbCurveValueGet", darklua_dbCurveValueGet);		
lua_register(L, "dbDateGet", darklua_dbDateGet);		
lua_register(L, "dbDeleteVertexShaderSet", darklua_dbDeleteVertexShaderSet);		
lua_register(L, "dbDetailMappingOn", darklua_dbDetailMappingOn);		
lua_register(L, "dbDeviceTypeGet", darklua_dbDeviceTypeGet);		
lua_register(L, "dbDirBlockReadSet", darklua_dbDirBlockReadSet);		
lua_register(L, "dbDirectoryBlockWrite", darklua_dbDirectoryBlockWrite);		
lua_register(L, "dbDirectoryChangeSet", darklua_dbDirectoryChangeSet);		
lua_register(L, "dbDirectoryDelete", darklua_dbDirectoryDelete);		
lua_register(L, "dbDirectoryGet", darklua_dbDirectoryGet);		
lua_register(L, "dbDirectoryMake", darklua_dbDirectoryMake);		
lua_register(L, "dbDirectoryPathExist", darklua_dbDirectoryPathExist);		
lua_register(L, "dbDirectorySet", darklua_dbDirectorySet);		
lua_register(L, "dbDirectorySet", darklua_dbDirectorySet);		
lua_register(L, "dbDisplayModeCheckGet", darklua_dbDisplayModeCheckGet);		
lua_register(L, "dbDisplayModeSet", darklua_dbDisplayModeSet);		
lua_register(L, "dbDitherAvailable", darklua_dbDitherAvailable);		
lua_register(L, "dbDLLCallExist", darklua_dbDLLCallExist);		
lua_register(L, "dbDLLCallSet", darklua_dbDLLCallSet);		
lua_register(L, "dbDLLDelete", darklua_dbDLLDelete);		
lua_register(L, "dbDLLExist", darklua_dbDLLExist);		
lua_register(L, "dbDLLLoad", darklua_dbDLLLoad);		
lua_register(L, "dbDotSet", darklua_dbDotSet);		
lua_register(L, "dbDownKeyGet", darklua_dbDownKeyGet);		
lua_register(L, "dbDrawSpritesFirstSet", darklua_dbDrawSpritesFirstSet);		
lua_register(L, "dbDrawSpritesLastSet", darklua_dbDrawSpritesLastSet);		
lua_register(L, "dbDrawToBackSet", darklua_dbDrawToBackSet);		
lua_register(L, "dbDrawToBackSet", darklua_dbDrawToBackSet);		
lua_register(L, "dbDriveListSet", darklua_dbDriveListSet);		
lua_register(L, "dbEffectConstantBooleanSet", darklua_dbEffectConstantBooleanSet);		
lua_register(L, "dbEffectConstantFloatSet", darklua_dbEffectConstantFloatSet);		
lua_register(L, "dbEffectConstantIntegerSet", darklua_dbEffectConstantIntegerSet);		
lua_register(L, "dbEffectConstantMatrixSet", darklua_dbEffectConstantMatrixSet);		
lua_register(L, "dbEffectConstantVectorSet", darklua_dbEffectConstantVectorSet);		
lua_register(L, "dbEffectDelete", darklua_dbEffectDelete);		
lua_register(L, "dbEffectExist", darklua_dbEffectExist);		
lua_register(L, "dbEffectLoad", darklua_dbEffectLoad);		
lua_register(L, "dbEffectOn", darklua_dbEffectOn);		
lua_register(L, "dbEffectTechniqueSet", darklua_dbEffectTechniqueSet);		
lua_register(L, "dbEffectTransposeSet", darklua_dbEffectTransposeSet);		
lua_register(L, "dbEllipseSet", darklua_dbEllipseSet);		
lua_register(L, "dbEntryBufferClear", darklua_dbEntryBufferClear);		
lua_register(L, "dbEntryBufferGet", darklua_dbEntryBufferGet);		
lua_register(L, "dbEscapeKeyDisable", darklua_dbEscapeKeyDisable);		
lua_register(L, "dbEscapeKeyEnable", darklua_dbEscapeKeyEnable);		
lua_register(L, "dbEscapeKeyGet", darklua_dbEscapeKeyGet);		
lua_register(L, "dbEXP", darklua_dbEXP);		
lua_register(L, "dbFastSync", darklua_dbFastSync);		
lua_register(L, "dbFileBlockReadSet", darklua_dbFileBlockReadSet);		
lua_register(L, "dbFileBlockWrite", darklua_dbFileBlockWrite);		
lua_register(L, "dbFileCloseSet", darklua_dbFileCloseSet);		
lua_register(L, "dbFileCopySet", darklua_dbFileCopySet);		
lua_register(L, "dbFileCreationGet", darklua_dbFileCreationGet);		
lua_register(L, "dbFileDateGet", darklua_dbFileDateGet);		
lua_register(L, "dbFileDelete", darklua_dbFileDelete);		
lua_register(L, "dbFileEndGet", darklua_dbFileEndGet);		
lua_register(L, "dbFileExecuteSet", darklua_dbFileExecuteSet);		
lua_register(L, "dbFileExist", darklua_dbFileExist);		
lua_register(L, "dbFileFindFirstSet", darklua_dbFileFindFirstSet);		
lua_register(L, "dbFileFindNextSet", darklua_dbFileFindNextSet);		
lua_register(L, "dbFileMake", darklua_dbFileMake);		
lua_register(L, "dbFileMoveSet", darklua_dbFileMoveSet);		
lua_register(L, "dbFileNameGet", darklua_dbFileNameGet);		
lua_register(L, "dbFileOpenGet", darklua_dbFileOpenGet);		
lua_register(L, "dbFileOpenReadSet", darklua_dbFileOpenReadSet);		
lua_register(L, "dbFileOpenWrite", darklua_dbFileOpenWrite);		
lua_register(L, "dbFileRenameSet", darklua_dbFileRenameSet);		
lua_register(L, "dbFileSizeGet", darklua_dbFileSizeGet);		
lua_register(L, "dbFileTypeGet", darklua_dbFileTypeGet);		
lua_register(L, "dbFileWrite", darklua_dbFileWrite);		
lua_register(L, "dbFilteringAvailable", darklua_dbFilteringAvailable);		
lua_register(L, "dbFloatWrite", darklua_dbFloatWrite);		
lua_register(L, "dbFogAvailable", darklua_dbFogAvailable);		
lua_register(L, "dbFogColorSet", darklua_dbFogColorSet);		
lua_register(L, "dbFogDistanceSet", darklua_dbFogDistanceSet);		
lua_register(L, "dbFogOff", darklua_dbFogOff);		
lua_register(L, "dbFogOn", darklua_dbFogOn);		
lua_register(L, "dbFogRangeAvailable", darklua_dbFogRangeAvailable);		
lua_register(L, "dbFogTableAvailable", darklua_dbFogTableAvailable);		
lua_register(L, "dbFogVertexAvailable", darklua_dbFogVertexAvailable);		
lua_register(L, "dbForceAngleSet", darklua_dbForceAngleSet);		
lua_register(L, "dbForceAutoCenterOff", darklua_dbForceAutoCenterOff);		
lua_register(L, "dbForceAutoCenterOn", darklua_dbForceAutoCenterOn);		
lua_register(L, "dbForceChainsawSet", darklua_dbForceChainsawSet);		
lua_register(L, "dbForceDown", darklua_dbForceDown);		
lua_register(L, "dbForceImpactSet", darklua_dbForceImpactSet);		
lua_register(L, "dbForceLeft", darklua_dbForceLeft);		
lua_register(L, "dbForceNoEffectSet", darklua_dbForceNoEffectSet);		
lua_register(L, "dbForceRight", darklua_dbForceRight);		
lua_register(L, "dbForceShootSet", darklua_dbForceShootSet);		
lua_register(L, "dbForceUp", darklua_dbForceUp);		
lua_register(L, "dbForceWaterEffectSet", darklua_dbForceWaterEffectSet);		
lua_register(L, "dbGammaSet", darklua_dbGammaSet);		
lua_register(L, "dbGlobalCollisionOff", darklua_dbGlobalCollisionOff);		
lua_register(L, "dbGlobalCollisionOn", darklua_dbGlobalCollisionOn);		
lua_register(L, "dbGraphicsCardSet", darklua_dbGraphicsCardSet);		
lua_register(L, "dbGroundHeightGet", darklua_dbGroundHeightGet);		
lua_register(L, "dbHCOS", darklua_dbHCOS);		
lua_register(L, "dbHex", darklua_dbHex);		
lua_register(L, "dbHSIN", darklua_dbHSIN);		
lua_register(L, "dbHTAN", darklua_dbHTAN);		
lua_register(L, "dbImageColorKeySet", darklua_dbImageColorKeySet);
lua_register(L, "dbImageCreate", darklua_dbImageCreate);
lua_register(L, "dbImageDelete", darklua_dbImageDelete);		
lua_register(L, "dbImageExist", darklua_dbImageExist);		
lua_register(L, "dbImageFromMemblockMake", darklua_dbImageFromMemblockMake);		
lua_register(L, "dbImageLoad", darklua_dbImageLoad);		
lua_register(L, "dbImagePaste", darklua_dbImagePaste);		
lua_register(L, "dbImageResourcePop", darklua_dbImageResourcePop);		
lua_register(L, "dbImageResourcePush", darklua_dbImageResourcePush);		
lua_register(L, "dbImageSave", darklua_dbImageSave);		
lua_register(L, "dbImageSet", darklua_dbImageSet);		
lua_register(L, "dbInKeyGet", darklua_dbInKeyGet);		
lua_register(L, "dbInkSet", darklua_dbInkSet);		
lua_register(L, "dbInt", darklua_dbInt);		
lua_register(L, "dbINT", darklua_dbINT);		
lua_register(L, "dbJoystickDownGet", darklua_dbJoystickDownGet);		
lua_register(L, "dbJoystickFireAGet", darklua_dbJoystickFireAGet);		
lua_register(L, "dbJoystickFireBGet", darklua_dbJoystickFireBGet);		
lua_register(L, "dbJoystickFireCGet", darklua_dbJoystickFireCGet);		
lua_register(L, "dbJoystickFireDGet", darklua_dbJoystickFireDGet);		
lua_register(L, "dbJoystickFireXGet", darklua_dbJoystickFireXGet);		
lua_register(L, "dbJoystickHatAngleGet", darklua_dbJoystickHatAngleGet);		
lua_register(L, "dbJoystickLeftGet", darklua_dbJoystickLeftGet);		
lua_register(L, "dbJoystickRightGet", darklua_dbJoystickRightGet);		
lua_register(L, "dbJoystickSliderAGet", darklua_dbJoystickSliderAGet);		
lua_register(L, "dbJoystickSliderBGet", darklua_dbJoystickSliderBGet);		
lua_register(L, "dbJoystickSliderCGet", darklua_dbJoystickSliderCGet);		
lua_register(L, "dbJoystickSliderDGet", darklua_dbJoystickSliderDGet);		
lua_register(L, "dbJoystickTwistXGet", darklua_dbJoystickTwistXGet);		
lua_register(L, "dbJoystickTwistYGet", darklua_dbJoystickTwistYGet);		
lua_register(L, "dbJoystickTwistZGet", darklua_dbJoystickTwistZGet);		
lua_register(L, "dbJoystickUpGet", darklua_dbJoystickUpGet);		
lua_register(L, "dbJoystickXGet", darklua_dbJoystickXGet);		
lua_register(L, "dbJoystickYGet", darklua_dbJoystickYGet);		
lua_register(L, "dbJoystickZGet", darklua_dbJoystickZGet);		
lua_register(L, "dbKeyStateGet", darklua_dbKeyStateGet);		
lua_register(L, "dbLeft", darklua_dbLeft);		
lua_register(L, "dbLeftKeyGet", darklua_dbLeftKeyGet);		
lua_register(L, "dbLen", darklua_dbLen);		
lua_register(L, "dbLightColorSet", darklua_dbLightColorSet);		
lua_register(L, "dbLightDelete", darklua_dbLightDelete);		
lua_register(L, "dbLightDirectionalSet", darklua_dbLightDirectionalSet);		
lua_register(L, "dbLightDirectionXGet", darklua_dbLightDirectionXGet);		
lua_register(L, "dbLightDirectionYGet", darklua_dbLightDirectionYGet);		
lua_register(L, "dbLightDirectionZGet", darklua_dbLightDirectionZGet);		
lua_register(L, "dbLightExist", darklua_dbLightExist);		
lua_register(L, "dbLightHide", darklua_dbLightHide);		
lua_register(L, "dbLightMake", darklua_dbLightMake);		
lua_register(L, "dbLightMappingOn", darklua_dbLightMappingOn);		
lua_register(L, "dbLightPoint", darklua_dbLightPoint);		
lua_register(L, "dbLightPointSet", darklua_dbLightPointSet);		
lua_register(L, "dbLightPositionSet", darklua_dbLightPositionSet);		
lua_register(L, "dbLightPositionXGet", darklua_dbLightPositionXGet);		
lua_register(L, "dbLightPositionYGet", darklua_dbLightPositionYGet);		
lua_register(L, "dbLightPositionZGet", darklua_dbLightPositionZGet);		
lua_register(L, "dbLightRangeGet", darklua_dbLightRangeGet);		
lua_register(L, "dbLightRangeSet", darklua_dbLightRangeSet);		
lua_register(L, "dbLightRotate", darklua_dbLightRotate);		
lua_register(L, "dbLightShow", darklua_dbLightShow);		
lua_register(L, "dbLightsMaximumGet", darklua_dbLightsMaximumGet);		
lua_register(L, "dbLightSpotSet", darklua_dbLightSpotSet);		
lua_register(L, "dbLightToObjectOrientationSet", darklua_dbLightToObjectOrientationSet);		
lua_register(L, "dbLightToObjectPositionSet", darklua_dbLightToObjectPositionSet);		
lua_register(L, "dbLightTypeGet", darklua_dbLightTypeGet);		
lua_register(L, "dbLightVisibleGet", darklua_dbLightVisibleGet);		
lua_register(L, "dbLimbAddSet", darklua_dbLimbAddSet);		
lua_register(L, "dbLimbAngleXGet", darklua_dbLimbAngleXGet);		
lua_register(L, "dbLimbAngleYGet", darklua_dbLimbAngleYGet);		
lua_register(L, "dbLimbAngleZGet", darklua_dbLimbAngleZGet);		
lua_register(L, "dbLimbColorSet", darklua_dbLimbColorSet);		
lua_register(L, "dbLimbDirectionXGet", darklua_dbLimbDirectionXGet);		
lua_register(L, "dbLimbDirectionYGet", darklua_dbLimbDirectionYGet);		
lua_register(L, "dbLimbDirectionZGet", darklua_dbLimbDirectionZGet);		
lua_register(L, "dbLimbEffectSet", darklua_dbLimbEffectSet);		
lua_register(L, "dbLimbExist", darklua_dbLimbExist);		
lua_register(L, "dbLimbHide", darklua_dbLimbHide);		
lua_register(L, "dbLimbLinkCheckGet", darklua_dbLimbLinkCheckGet);		
lua_register(L, "dbLimbLinkSet", darklua_dbLimbLinkSet);		
lua_register(L, "dbLimbNameGet", darklua_dbLimbNameGet);		
lua_register(L, "dbLimbOffsetSet", darklua_dbLimbOffsetSet);		
lua_register(L, "dbLimbOffsetXGet", darklua_dbLimbOffsetXGet);		
lua_register(L, "dbLimbOffsetYGet", darklua_dbLimbOffsetYGet);		
lua_register(L, "dbLimbOffsetZGet", darklua_dbLimbOffsetZGet);		
lua_register(L, "dbLimbPositionXGet", darklua_dbLimbPositionXGet);		
lua_register(L, "dbLimbPositionYGet", darklua_dbLimbPositionYGet);		
lua_register(L, "dbLimbPositionZGet", darklua_dbLimbPositionZGet);		
lua_register(L, "dbLimbRemoveSet", darklua_dbLimbRemoveSet);		
lua_register(L, "dbLimbRotate", darklua_dbLimbRotate);		
lua_register(L, "dbLimbScaleSet", darklua_dbLimbScaleSet);		
lua_register(L, "dbLimbScaleXGet", darklua_dbLimbScaleXGet);		
lua_register(L, "dbLimbScaleYGet", darklua_dbLimbScaleYGet);		
lua_register(L, "dbLimbScaleZGet", darklua_dbLimbScaleZGet);		
lua_register(L, "dbLimbShow", darklua_dbLimbShow);		
lua_register(L, "dbLimbSmoothingSet", darklua_dbLimbSmoothingSet);		
lua_register(L, "dbLimbTextureGet", darklua_dbLimbTextureGet);		
lua_register(L, "dbLimbTextureNameGet", darklua_dbLimbTextureNameGet);		
lua_register(L, "dbLimbTextureScaleSet", darklua_dbLimbTextureScaleSet);		
lua_register(L, "dbLimbTextureScrollSet", darklua_dbLimbTextureScrollSet);		
lua_register(L, "dbLimbTextureSet", darklua_dbLimbTextureSet);		
lua_register(L, "dbLimbVisibleGet", darklua_dbLimbVisibleGet);		
lua_register(L, "dbLineSet", darklua_dbLineSet);		
lua_register(L, "dbListenerAngleXGet", darklua_dbListenerAngleXGet);		
lua_register(L, "dbListenerAngleYGet", darklua_dbListenerAngleYGet);		
lua_register(L, "dbListenerAngleZGet", darklua_dbListenerAngleZGet);		
lua_register(L, "dbListenerPositionSet", darklua_dbListenerPositionSet);		
lua_register(L, "dbListenerPositionXGet", darklua_dbListenerPositionXGet);		
lua_register(L, "dbListenerPositionYGet", darklua_dbListenerPositionYGet);		
lua_register(L, "dbListenerPositionZGet", darklua_dbListenerPositionZGet);		
lua_register(L, "dbListenerRotate", darklua_dbListenerRotate);		
lua_register(L, "dbListenerScaleSet", darklua_dbListenerScaleSet);		
lua_register(L, "dbLongWrite", darklua_dbLongWrite);		
lua_register(L, "dbLower", darklua_dbLower);		
lua_register(L, "dbMakeMeshFromObjectSet", darklua_dbMakeMeshFromObjectSet);		
lua_register(L, "dbMakeStaticCollisionBoxSet", darklua_dbMakeStaticCollisionBoxSet);		
lua_register(L, "dbMatrix4AddSet", darklua_dbMatrix4AddSet);		
lua_register(L, "dbMatrix4CopySet", darklua_dbMatrix4CopySet);		
lua_register(L, "dbMatrix4DeleteGet", darklua_dbMatrix4DeleteGet);		
lua_register(L, "dbMatrix4DivideSet", darklua_dbMatrix4DivideSet);		
lua_register(L, "dbMatrix4IdentitySet", darklua_dbMatrix4IdentitySet);		
lua_register(L, "dbMatrix4InverseGet", darklua_dbMatrix4InverseGet);		
lua_register(L, "dbMatrix4IsEqualGet", darklua_dbMatrix4IsEqualGet);		
lua_register(L, "dbMatrix4IsIdentityGet", darklua_dbMatrix4IsIdentityGet);		
lua_register(L, "dbMatrix4LookAtLHBuild", darklua_dbMatrix4LookAtLHBuild);		
lua_register(L, "dbMatrix4LookAtRHBuild", darklua_dbMatrix4LookAtRHBuild);		
lua_register(L, "dbMatrix4MakeGet", darklua_dbMatrix4MakeGet);		
lua_register(L, "dbMatrix4MultiplySet", darklua_dbMatrix4MultiplySet);		
lua_register(L, "dbMatrix4OrthoLHBuild", darklua_dbMatrix4OrthoLHBuild);		
lua_register(L, "dbMatrix4OrthoRHBuild", darklua_dbMatrix4OrthoRHBuild);		
lua_register(L, "dbMatrix4PerspectiveLHBuild", darklua_dbMatrix4PerspectiveLHBuild);		
lua_register(L, "dbMatrix4PerspectiveRHBuild", darklua_dbMatrix4PerspectiveRHBuild);		
lua_register(L, "dbMatrix4ReflectionBuild", darklua_dbMatrix4ReflectionBuild);		
lua_register(L, "dbMatrix4RotateXSet", darklua_dbMatrix4RotateXSet);		
lua_register(L, "dbMatrix4RotateYPRSet", darklua_dbMatrix4RotateYPRSet);		
lua_register(L, "dbMatrix4RotateYSet", darklua_dbMatrix4RotateYSet);		
lua_register(L, "dbMatrix4RotateZSet", darklua_dbMatrix4RotateZSet);		
lua_register(L, "dbMatrix4RotationAxisBuild", darklua_dbMatrix4RotationAxisBuild);		
lua_register(L, "dbMatrix4ScaleSet", darklua_dbMatrix4ScaleSet);		
lua_register(L, "dbMatrix4SubtractSet", darklua_dbMatrix4SubtractSet);		
lua_register(L, "dbMatrix4TranslateSet", darklua_dbMatrix4TranslateSet);		
lua_register(L, "dbMatrix4TransposeSet", darklua_dbMatrix4TransposeSet);		
lua_register(L, "dbMatrixDelete", darklua_dbMatrixDelete);		
lua_register(L, "dbMatrixExist", darklua_dbMatrixExist);		
lua_register(L, "dbMatrixFillSet", darklua_dbMatrixFillSet);		
lua_register(L, "dbMatrixGhostOff", darklua_dbMatrixGhostOff);		
lua_register(L, "dbMatrixGhostOn", darklua_dbMatrixGhostOn);		
lua_register(L, "dbMatrixHeightGet", darklua_dbMatrixHeightGet);		
lua_register(L, "dbMatrixHeightSet", darklua_dbMatrixHeightSet);		
lua_register(L, "dbMatrixMake", darklua_dbMatrixMake);		
lua_register(L, "dbMatrixNormalSet", darklua_dbMatrixNormalSet);		
lua_register(L, "dbMatrixPositionSet", darklua_dbMatrixPositionSet);		
lua_register(L, "dbMatrixPositionXGet", darklua_dbMatrixPositionXGet);		
lua_register(L, "dbMatrixPositionYGet", darklua_dbMatrixPositionYGet);		
lua_register(L, "dbMatrixPositionZGet", darklua_dbMatrixPositionZGet);		
lua_register(L, "dbMatrixPrioritySet", darklua_dbMatrixPrioritySet);		
lua_register(L, "dbMatrixRandomizeSet", darklua_dbMatrixRandomizeSet);		
lua_register(L, "dbMatrixSet", darklua_dbMatrixSet);		
lua_register(L, "dbMatrixShiftDown", darklua_dbMatrixShiftDown);		
lua_register(L, "dbMatrixShiftLeft", darklua_dbMatrixShiftLeft);		
lua_register(L, "dbMatrixShiftRight", darklua_dbMatrixShiftRight);		
lua_register(L, "dbMatrixShiftUp", darklua_dbMatrixShiftUp);		
lua_register(L, "dbMatrixTexturePrepareSet", darklua_dbMatrixTexturePrepareSet);		
lua_register(L, "dbMatrixTextureSet", darklua_dbMatrixTextureSet);		
lua_register(L, "dbMatrixTileCountGet", darklua_dbMatrixTileCountGet);		
lua_register(L, "dbMatrixTileSet", darklua_dbMatrixTileSet);		
lua_register(L, "dbMatrixTilesExist", darklua_dbMatrixTilesExist);		
lua_register(L, "dbMatrixUpdateSet", darklua_dbMatrixUpdateSet);		
lua_register(L, "dbMatrixVector3ToPositionSet", darklua_dbMatrixVector3ToPositionSet);		
lua_register(L, "dbMatrixWireframeOff", darklua_dbMatrixWireframeOff);		
lua_register(L, "dbMatrixWireframeOn", darklua_dbMatrixWireframeOn);		
lua_register(L, "dbMatrixWireframeStateGet", darklua_dbMatrixWireframeStateGet);		
lua_register(L, "dbMaximumPixelShaderVersionGet", darklua_dbMaximumPixelShaderVersionGet);		
lua_register(L, "dbMaximumVertexShaderVersionGet", darklua_dbMaximumVertexShaderVersionGet);		
lua_register(L, "dbMemblockByteGet", darklua_dbMemblockByteGet);		
lua_register(L, "dbMemblockCopySet", darklua_dbMemblockCopySet);		
lua_register(L, "dbMemblockDelete", darklua_dbMemblockDelete);		
lua_register(L, "dbMemblockDwordWrite", darklua_dbMemblockDwordWrite);		
lua_register(L, "dbMemblockExist", darklua_dbMemblockExist);		
lua_register(L, "dbMemblockFloatGet", darklua_dbMemblockFloatGet);		
lua_register(L, "dbMemblockFloatWrite", darklua_dbMemblockFloatWrite);		
lua_register(L, "dbMemblockFromBitmapMake", darklua_dbMemblockFromBitmapMake);		
lua_register(L, "dbMemblockFromImageMake", darklua_dbMemblockFromImageMake);		
lua_register(L, "dbMemblockFromMeshMake", darklua_dbMemblockFromMeshMake);		
lua_register(L, "dbMemblockFromSoundMake", darklua_dbMemblockFromSoundMake);		
lua_register(L, "dbMemblockMake", darklua_dbMemblockMake);		
lua_register(L, "dbMemblockSizeGet", darklua_dbMemblockSizeGet);		
lua_register(L, "dbMemblockWordWrite", darklua_dbMemblockWordWrite);		
lua_register(L, "dbMeshChangeSet", darklua_dbMeshChangeSet);		
lua_register(L, "dbMeshDelete", darklua_dbMeshDelete);		
lua_register(L, "dbMeshExist", darklua_dbMeshExist);		
lua_register(L, "dbMeshFromMemblockChangeSet", darklua_dbMeshFromMemblockChangeSet);		
lua_register(L, "dbMeshFromMemblockMake", darklua_dbMeshFromMemblockMake);		
lua_register(L, "dbMeshLoad", darklua_dbMeshLoad);		
lua_register(L, "dbMeshSave", darklua_dbMeshSave);		
lua_register(L, "dbMid", darklua_dbMid);		
lua_register(L, "dbMipMapAvailable", darklua_dbMipMapAvailable);		
lua_register(L, "dbMipMapCubeAvailable", darklua_dbMipMapCubeAvailable);		
lua_register(L, "dbMipMapVolumeAvailable", darklua_dbMipMapVolumeAvailable);		
lua_register(L, "dbMouseChangeSet", darklua_dbMouseChangeSet);		
lua_register(L, "dbMouseClickGet", darklua_dbMouseClickGet);		
lua_register(L, "dbMouseHide", darklua_dbMouseHide);		
lua_register(L, "dbMouseMoveXGet", darklua_dbMouseMoveXGet);		
lua_register(L, "dbMouseMoveYGet", darklua_dbMouseMoveYGet);		
lua_register(L, "dbMouseMoveZGet", darklua_dbMouseMoveZGet);		
lua_register(L, "dbMousePositionSet", darklua_dbMousePositionSet);		
lua_register(L, "dbMouseShow", darklua_dbMouseShow);		
lua_register(L, "dbMouseXGet", darklua_dbMouseXGet);		
lua_register(L, "dbMouseYGet", darklua_dbMouseYGet);		
lua_register(L, "dbMouseZGet", darklua_dbMouseZGet);		
lua_register(L, "dbMusicCDLoad", darklua_dbMusicCDLoad);		
lua_register(L, "dbMusicCDTracksGet", darklua_dbMusicCDTracksGet);		
lua_register(L, "dbMusicDelete", darklua_dbMusicDelete);		
lua_register(L, "dbMusicExist", darklua_dbMusicExist);		
lua_register(L, "dbMusicLoad", darklua_dbMusicLoad);		
lua_register(L, "dbMusicLoopingGet", darklua_dbMusicLoopingGet);		
lua_register(L, "dbMusicLoopSet", darklua_dbMusicLoopSet);		
lua_register(L, "dbMusicPausedGet", darklua_dbMusicPausedGet);		
lua_register(L, "dbMusicPauseSet", darklua_dbMusicPauseSet);		
lua_register(L, "dbMusicPlayingGet", darklua_dbMusicPlayingGet);		
lua_register(L, "dbMusicPlaySet", darklua_dbMusicPlaySet);		
lua_register(L, "dbMusicResumeSet", darklua_dbMusicResumeSet);		
lua_register(L, "dbMusicSpeedGet", darklua_dbMusicSpeedGet);		
lua_register(L, "dbMusicSpeedSet", darklua_dbMusicSpeedSet);		
lua_register(L, "dbMusicStopSet", darklua_dbMusicStopSet);		
lua_register(L, "dbMusicVolumeGet", darklua_dbMusicVolumeGet);		
lua_register(L, "dbMusicVolumeSet", darklua_dbMusicVolumeSet);		
lua_register(L, "dbNewXValueGet", darklua_dbNewXValueGet);		
lua_register(L, "dbNewYValueGet", darklua_dbNewYValueGet);		
lua_register(L, "dbNewZValueGet", darklua_dbNewZValueGet);		
lua_register(L, "dbNonLocalVideoMemoryAvailable", darklua_dbNonLocalVideoMemoryAvailable);		
lua_register(L, "dbNonPowTexturesAvailable", darklua_dbNonPowTexturesAvailable);		
lua_register(L, "dbNormalizationOff", darklua_dbNormalizationOff);		
lua_register(L, "dbNormalizationOn", darklua_dbNormalizationOn);		
lua_register(L, "dbObjectAmbienceSet", darklua_dbObjectAmbienceSet);		
lua_register(L, "dbObjectAmbientSet", darklua_dbObjectAmbientSet);		
lua_register(L, "dbObjectAngleXGet", darklua_dbObjectAngleXGet);		
lua_register(L, "dbObjectAngleYGet", darklua_dbObjectAngleYGet);		
lua_register(L, "dbObjectAngleZGet", darklua_dbObjectAngleZGet);		
lua_register(L, "dbObjectAppend", darklua_dbObjectAppend);		
lua_register(L, "dbObjectAutoCollisionSet", darklua_dbObjectAutoCollisionSet);		
lua_register(L, "dbObjectBoundsHide", darklua_dbObjectBoundsHide);		
lua_register(L, "dbObjectBoundsShow", darklua_dbObjectBoundsShow);		
lua_register(L, "dbObjectClone", darklua_dbObjectClone);		
lua_register(L, "dbObjectCollisionBoxDelete", darklua_dbObjectCollisionBoxDelete);		
lua_register(L, "dbObjectCollisionBoxMake", darklua_dbObjectCollisionBoxMake);		
lua_register(L, "dbObjectCollisionCenterXGet", darklua_dbObjectCollisionCenterXGet);		
lua_register(L, "dbObjectCollisionCenterYGet", darklua_dbObjectCollisionCenterYGet);		
lua_register(L, "dbObjectCollisionCenterZGet", darklua_dbObjectCollisionCenterZGet);		
lua_register(L, "dbObjectCollisionGet", darklua_dbObjectCollisionGet);		
lua_register(L, "dbObjectCollisionOff", darklua_dbObjectCollisionOff);		
lua_register(L, "dbObjectCollisionOn", darklua_dbObjectCollisionOn);		
lua_register(L, "dbObjectCollisionRadiusGet", darklua_dbObjectCollisionRadiusGet);		
lua_register(L, "dbObjectCollisionToBoxesSet", darklua_dbObjectCollisionToBoxesSet);		
lua_register(L, "dbObjectCollisionToPolygonsSet", darklua_dbObjectCollisionToPolygonsSet);		
lua_register(L, "dbObjectCollisionToSpheresSet", darklua_dbObjectCollisionToSpheresSet);		
lua_register(L, "dbObjectCollisionXGet", darklua_dbObjectCollisionXGet);		
lua_register(L, "dbObjectCollisionYGet", darklua_dbObjectCollisionYGet);		
lua_register(L, "dbObjectCollisionZGet", darklua_dbObjectCollisionZGet);		
lua_register(L, "dbObjectColorSet", darklua_dbObjectColorSet);		
lua_register(L, "dbObjectConeMake", darklua_dbObjectConeMake);		
lua_register(L, "dbObjectCubeMake", darklua_dbObjectCubeMake);		
lua_register(L, "dbObjectCullSet", darklua_dbObjectCullSet);		
lua_register(L, "dbObjectCylinderMake", darklua_dbObjectCylinderMake);		
lua_register(L, "dbObjectDelete", darklua_dbObjectDelete);		
lua_register(L, "dbObjectDiffuseSet", darklua_dbObjectDiffuseSet);		
lua_register(L, "dbObjectEffectSet", darklua_dbObjectEffectSet);		
lua_register(L, "dbObjectEmissiveSet", darklua_dbObjectEmissiveSet);		
lua_register(L, "dbObjectExist", darklua_dbObjectExist);		
lua_register(L, "dbObjectFadeSet", darklua_dbObjectFadeSet);		
lua_register(L, "dbObjectFilterSet", darklua_dbObjectFilterSet);		
lua_register(L, "dbObjectFogSet", darklua_dbObjectFogSet);		
lua_register(L, "dbObjectFrameGet", darklua_dbObjectFrameGet);		
lua_register(L, "dbObjectFrameSet", darklua_dbObjectFrameSet);		
lua_register(L, "dbObjectFramesTotalGet", darklua_dbObjectFramesTotalGet);		
lua_register(L, "dbObjectFromLimbMake", darklua_dbObjectFromLimbMake);		
lua_register(L, "dbObjectGet", darklua_dbObjectGet);
lua_register(L, "dbObjectGhostOff", darklua_dbObjectGhostOff);		
lua_register(L, "dbObjectGhostOn", darklua_dbObjectGhostOn);		
lua_register(L, "dbObjectHide", darklua_dbObjectHide);		
lua_register(L, "dbObjectHitGet", darklua_dbObjectHitGet);		
lua_register(L, "dbObjectInScreenGet", darklua_dbObjectInScreenGet);		
lua_register(L, "dbObjectInstanceSet", darklua_dbObjectInstanceSet);		
lua_register(L, "dbObjectInterpolationGet", darklua_dbObjectInterpolationGet);		
lua_register(L, "dbObjectInterpolationSet", darklua_dbObjectInterpolationSet);		
lua_register(L, "dbObjectIntersectGet", darklua_dbObjectIntersectGet);		
lua_register(L, "dbObjectLightSet", darklua_dbObjectLightSet);		
lua_register(L, "dbObjectLoad", darklua_dbObjectLoad);		
lua_register(L, "dbObjectLockOff", darklua_dbObjectLockOff);		
lua_register(L, "dbObjectLockOn", darklua_dbObjectLockOn);		
lua_register(L, "dbObjectLoopingGet", darklua_dbObjectLoopingGet);		
lua_register(L, "dbObjectLoopSet", darklua_dbObjectLoopSet);		
lua_register(L, "dbObjectMake", darklua_dbObjectMake);		
lua_register(L, "dbObjectMoveDown", darklua_dbObjectMoveDown);		
lua_register(L, "dbObjectMoveLeft", darklua_dbObjectMoveLeft);		
lua_register(L, "dbObjectMoveRight", darklua_dbObjectMoveRight);		
lua_register(L, "dbObjectMove", darklua_dbObjectMove);		
lua_register(L, "dbObjectMoveUp", darklua_dbObjectMoveUp);		
lua_register(L, "dbObjectPickGet", darklua_dbObjectPickGet);		
lua_register(L, "dbObjectPitchDown", darklua_dbObjectPitchDown);		
lua_register(L, "dbObjectPitchUp", darklua_dbObjectPitchUp);		
lua_register(L, "dbObjectPivotFixSet", darklua_dbObjectPivotFixSet);		
lua_register(L, "dbObjectPlainMake", darklua_dbObjectPlainMake);		
lua_register(L, "dbObjectPlayingGet", darklua_dbObjectPlayingGet);		
lua_register(L, "dbObjectPlaySet", darklua_dbObjectPlaySet);		
lua_register(L, "dbObjectPointSet", darklua_dbObjectPointSet);		
lua_register(L, "dbObjectPositionSet", darklua_dbObjectPositionSet);		
lua_register(L, "dbObjectPositionXGet", darklua_dbObjectPositionXGet);		
lua_register(L, "dbObjectPositionYGet", darklua_dbObjectPositionYGet);		
lua_register(L, "dbObjectPositionZGet", darklua_dbObjectPositionZGet);		
lua_register(L, "dbObjectRadiusSet", darklua_dbObjectRadiusSet);		
lua_register(L, "dbObjectResourcePop", darklua_dbObjectResourcePop);		
lua_register(L, "dbObjectResourcePush", darklua_dbObjectResourcePush);		
lua_register(L, "dbObjectRollLeft", darklua_dbObjectRollLeft);		
lua_register(L, "dbObjectRollRight", darklua_dbObjectRollRight);		
lua_register(L, "dbObjectRotate", darklua_dbObjectRotate);		
lua_register(L, "dbObjectRotationXYZSet", darklua_dbObjectRotationXYZSet);		
lua_register(L, "dbObjectRotationZYXSet", darklua_dbObjectRotationZYXSet);		
lua_register(L, "dbObjectScaleSet", darklua_dbObjectScaleSet);		
lua_register(L, "dbObjectScreenXGet", darklua_dbObjectScreenXGet);		
lua_register(L, "dbObjectScreenYGet", darklua_dbObjectScreenYGet);		
lua_register(L, "dbObjectSet", darklua_dbObjectSet);		
lua_register(L, "dbObjectShow", darklua_dbObjectShow);		
lua_register(L, "dbObjectSizeGet", darklua_dbObjectSizeGet);		
lua_register(L, "dbObjectSizeXGet", darklua_dbObjectSizeXGet);		
lua_register(L, "dbObjectSizeYGet", darklua_dbObjectSizeYGet);		
lua_register(L, "dbObjectSizeZGet", darklua_dbObjectSizeZGet);		
lua_register(L, "dbObjectSmoothingSet", darklua_dbObjectSmoothingSet);		
lua_register(L, "dbObjectSpecularPowerSet", darklua_dbObjectSpecularPowerSet);		
lua_register(L, "dbObjectSpecularSet", darklua_dbObjectSpecularSet);		
lua_register(L, "dbObjectSpeedGet", darklua_dbObjectSpeedGet);		
lua_register(L, "dbObjectSpeedSet", darklua_dbObjectSpeedSet);		
lua_register(L, "dbObjectSphereMake", darklua_dbObjectSphereMake);		
lua_register(L, "dbObjectSpin", darklua_dbObjectSpin);		
lua_register(L, "dbObjectSpinX", darklua_dbObjectSpinX);		
lua_register(L, "dbObjectSpinY", darklua_dbObjectSpinY);		
lua_register(L, "dbObjectSpinZ", darklua_dbObjectSpinZ);		
lua_register(L, "dbObjectStopSet", darklua_dbObjectStopSet);		
lua_register(L, "dbObjectTextureScaleSet", darklua_dbObjectTextureScaleSet);		
lua_register(L, "dbObjectTextureScrollSet", darklua_dbObjectTextureScrollSet);		
lua_register(L, "dbObjectTextureSet", darklua_dbObjectTextureSet);		
lua_register(L, "dbObjectTextureSet", darklua_dbObjectTextureSet);		
lua_register(L, "dbObjectToCameraOrientationSet", darklua_dbObjectToCameraOrientationSet);		
lua_register(L, "dbObjectToLimbGlueSet", darklua_dbObjectToLimbGlueSet);		
lua_register(L, "dbObjectToObjectOrientationSet", darklua_dbObjectToObjectOrientationSet);		
lua_register(L, "dbObjectTransparencySet", darklua_dbObjectTransparencySet);		
lua_register(L, "dbObjectTriangleMake", darklua_dbObjectTriangleMake);		
lua_register(L, "dbObjectTurnLeft", darklua_dbObjectTurnLeft);		
lua_register(L, "dbObjectTurnRight", darklua_dbObjectTurnRight);		
lua_register(L, "dbObjectUnglueSet", darklua_dbObjectUnglueSet);		
lua_register(L, "dbObjectVisibleGet", darklua_dbObjectVisibleGet);		
lua_register(L, "dbObjectWireframeSet", darklua_dbObjectWireframeSet);		
lua_register(L, "dbObjectZDepthDisable", darklua_dbObjectZDepthDisable);		
lua_register(L, "dbObjectZDepthEnable", darklua_dbObjectZDepthEnable);		
lua_register(L, "dbPerformCheckListForDrivesSet", darklua_dbPerformCheckListForDrivesSet);		
lua_register(L, "dbPerformCheckListForFilesSet", darklua_dbPerformCheckListForFilesSet);		
lua_register(L, "dbPerformCheckListForObjectLimbsSet", darklua_dbPerformCheckListForObjectLimbsSet);		
lua_register(L, "dbPerspectiveTexturesAvailable", darklua_dbPerspectiveTexturesAvailable);		
lua_register(L, "dbPickDistanceGet", darklua_dbPickDistanceGet);		
lua_register(L, "dbPixelShaderDelete", darklua_dbPixelShaderDelete);		
lua_register(L, "dbPixelShaderExist", darklua_dbPixelShaderExist);		
lua_register(L, "dbPixelShaderFromFileCreateSet", darklua_dbPixelShaderFromFileCreateSet);		
lua_register(L, "dbPixelShaderOff", darklua_dbPixelShaderOff);		
lua_register(L, "dbPixelShaderOn", darklua_dbPixelShaderOn);		
lua_register(L, "dbPixelShaderTextureSet", darklua_dbPixelShaderTextureSet);		
lua_register(L, "dbPixelShaderValueMaximumGet", darklua_dbPixelShaderValueMaximumGet);		
lua_register(L, "dbPixelsLockSet", darklua_dbPixelsLockSet);		
lua_register(L, "dbPixelsPitchGet", darklua_dbPixelsPitchGet);		
lua_register(L, "dbPixelsPointerGet", darklua_dbPixelsPointerGet);		
lua_register(L, "dbPixelsUnlockSet", darklua_dbPixelsUnlockSet);		
lua_register(L, "dbPointGet", darklua_dbPointGet);		
lua_register(L, "dbProjectedTexturesAvailable", darklua_dbProjectedTexturesAvailable);		
lua_register(L, "dbPromptExitSet", darklua_dbPromptExitSet);		
lua_register(L, "dbRainbowShadingOn", darklua_dbRainbowShadingOn);		
lua_register(L, "dbRandomizeSet", darklua_dbRandomizeSet);		
lua_register(L, "dbReflectionShadingOn", darklua_dbReflectionShadingOn);		
lua_register(L, "dbRegistryGet", darklua_dbRegistryGet);		
lua_register(L, "dbRegistryGet", darklua_dbRegistryGet);		
lua_register(L, "dbRegistryWrite", darklua_dbRegistryWrite);		
lua_register(L, "dbRenderAfterFlipAvailable", darklua_dbRenderAfterFlipAvailable);		
lua_register(L, "dbRenderWindowedAvailable", darklua_dbRenderWindowedAvailable);		
lua_register(L, "dbReturnKeyGet", darklua_dbReturnKeyGet);		
lua_register(L, "dbRGBBGet", darklua_dbRGBBGet);		
lua_register(L, "dbRGBGet", darklua_dbRGBGet);
lua_register(L, "dbRGBGGet", darklua_dbRGBGGet);		
lua_register(L, "dbRGBRGet", darklua_dbRGBRGet);
lua_register(L, "dbRight", darklua_dbRight);		
lua_register(L, "dbRightKeyGet", darklua_dbRightKeyGet);		
lua_register(L, "dbRND", darklua_dbRND);		
lua_register(L, "dbScanCodeGet", darklua_dbScanCodeGet);		
lua_register(L, "dbScreenDepthGet", darklua_dbScreenDepthGet);		
lua_register(L, "dbScreenFPSGet", darklua_dbScreenFPSGet);		
lua_register(L, "dbScreenHeightGet", darklua_dbScreenHeightGet);		
lua_register(L, "dbScreenInvalidGet", darklua_dbScreenInvalidGet);		
lua_register(L, "dbScreenPickSet", darklua_dbScreenPickSet);		
lua_register(L, "dbScreenTypeGet", darklua_dbScreenTypeGet);		
lua_register(L, "dbScreenWidthGet", darklua_dbScreenWidthGet);		
lua_register(L, "dbShadowShadingOn", darklua_dbShadowShadingOn);		
lua_register(L, "dbShiftKeyGet", darklua_dbShiftKeyGet);		
lua_register(L, "dbSIN", darklua_dbSIN);		
lua_register(L, "dbSkipBytesSet", darklua_dbSkipBytesSet);		
lua_register(L, "dbSleepSet", darklua_dbSleepSet);		
lua_register(L, "dbSoundClone", darklua_dbSoundClone);		
lua_register(L, "dbSoundDelete", darklua_dbSoundDelete);		
lua_register(L, "dbSoundExist", darklua_dbSoundExist);		
lua_register(L, "dbSoundFromMemblockMake", darklua_dbSoundFromMemblockMake);		
lua_register(L, "dbSoundLoad", darklua_dbSoundLoad);		
lua_register(L, "dbSoundLoad3DSet", darklua_dbSoundLoad3DSet);		
lua_register(L, "dbSoundLoopingGet", darklua_dbSoundLoopingGet);		
lua_register(L, "dbSoundLoopSet", darklua_dbSoundLoopSet);		
lua_register(L, "dbSoundPanGet", darklua_dbSoundPanGet);		
lua_register(L, "dbSoundPanSet", darklua_dbSoundPanSet);		
lua_register(L, "dbSoundPausedGet", darklua_dbSoundPausedGet);		
lua_register(L, "dbSoundPauseSet", darklua_dbSoundPauseSet);		
lua_register(L, "dbSoundPlayingGet", darklua_dbSoundPlayingGet);		
lua_register(L, "dbSoundPlaySet", darklua_dbSoundPlaySet);		
lua_register(L, "dbSoundPositionSet", darklua_dbSoundPositionSet);		
lua_register(L, "dbSoundPositionXGet", darklua_dbSoundPositionXGet);		
lua_register(L, "dbSoundPositionYGet", darklua_dbSoundPositionYGet);		
lua_register(L, "dbSoundPositionZGet", darklua_dbSoundPositionZGet);		
lua_register(L, "dbSoundRecordSet", darklua_dbSoundRecordSet);		
lua_register(L, "dbSoundResumeSet", darklua_dbSoundResumeSet);		
lua_register(L, "dbSoundSave", darklua_dbSoundSave);		
lua_register(L, "dbSoundSpeedGet", darklua_dbSoundSpeedGet);		
lua_register(L, "dbSoundSpeedSet", darklua_dbSoundSpeedSet);		
lua_register(L, "dbSoundStopRecordingSet", darklua_dbSoundStopRecordingSet);		
lua_register(L, "dbSoundStopSet", darklua_dbSoundStopSet);		
lua_register(L, "dbSoundTypeGet", darklua_dbSoundTypeGet);		
lua_register(L, "dbSoundVolumeGet", darklua_dbSoundVolumeGet);		
lua_register(L, "dbSoundVolumeSet", darklua_dbSoundVolumeSet);		
lua_register(L, "dbSpaceKeyGet", darklua_dbSpaceKeyGet);		
lua_register(L, "dbSphereMappingOn", darklua_dbSphereMappingOn);		
lua_register(L, "dbSpriteAlphaGet", darklua_dbSpriteAlphaGet);		
lua_register(L, "dbSpriteAlphaGet", darklua_dbSpriteAlphaGet);		
lua_register(L, "dbSpriteAlphaSet", darklua_dbSpriteAlphaSet);		
lua_register(L, "dbSpriteAlphaSet", darklua_dbSpriteAlphaSet);		
lua_register(L, "dbSpriteAngleGet", darklua_dbSpriteAngleGet);		
lua_register(L, "dbSpriteAnimatedCreateSet", darklua_dbSpriteAnimatedCreateSet);		
lua_register(L, "dbSpriteBlueGet", darklua_dbSpriteBlueGet);		
lua_register(L, "dbSpriteClone", darklua_dbSpriteClone);		
lua_register(L, "dbSpriteCollisionGet", darklua_dbSpriteCollisionGet);		
lua_register(L, "dbSpriteCreateSet", darklua_dbSpriteCreateSet);		
lua_register(L, "dbSpriteDelete", darklua_dbSpriteDelete);		
lua_register(L, "dbSpriteDiffuseSet", darklua_dbSpriteDiffuseSet);		
lua_register(L, "dbSpriteExist", darklua_dbSpriteExist);		
lua_register(L, "dbSpriteFlippedGet", darklua_dbSpriteFlippedGet);		
lua_register(L, "dbSpriteFlipSet", darklua_dbSpriteFlipSet);		
lua_register(L, "dbSpriteFrameGet", darklua_dbSpriteFrameGet);		
lua_register(L, "dbSpriteFrameSet", darklua_dbSpriteFrameSet);		
lua_register(L, "dbSpriteGreenGet", darklua_dbSpriteGreenGet);		
lua_register(L, "dbSpriteHeightGet", darklua_dbSpriteHeightGet);		
lua_register(L, "dbSpriteHide", darklua_dbSpriteHide);		
lua_register(L, "dbSpriteHideAllSet", darklua_dbSpriteHideAllSet);		
lua_register(L, "dbSpriteHitGet", darklua_dbSpriteHitGet);		
lua_register(L, "dbSpriteImageGet", darklua_dbSpriteImageGet);		
lua_register(L, "dbSpriteImageSet", darklua_dbSpriteImageSet);		
lua_register(L, "dbSpriteMirroredGet", darklua_dbSpriteMirroredGet);		
lua_register(L, "dbSpriteMirrorSet", darklua_dbSpriteMirrorSet);		
lua_register(L, "dbSpriteMoveSet", darklua_dbSpriteMoveSet);		
lua_register(L, "dbSpriteOffsetSet", darklua_dbSpriteOffsetSet);		
lua_register(L, "dbSpriteOffsetXGet", darklua_dbSpriteOffsetXGet);		
lua_register(L, "dbSpriteOffsetYGet", darklua_dbSpriteOffsetYGet);		
lua_register(L, "dbSpritePaste", darklua_dbSpritePaste);		
lua_register(L, "dbSpritePlaySet", darklua_dbSpritePlaySet);		
lua_register(L, "dbSpritePrioritySet", darklua_dbSpritePrioritySet);		
lua_register(L, "dbSpriteRedGet", darklua_dbSpriteRedGet);		
lua_register(L, "dbSpriteRotate", darklua_dbSpriteRotate);		
lua_register(L, "dbSpriteScaleSet", darklua_dbSpriteScaleSet);		
lua_register(L, "dbSpriteScaleXGet", darklua_dbSpriteScaleXGet);		
lua_register(L, "dbSpriteScaleYGet", darklua_dbSpriteScaleYGet);		
lua_register(L, "dbSpriteSet", darklua_dbSpriteSet);		
lua_register(L, "dbSpriteShow", darklua_dbSpriteShow);		
lua_register(L, "dbSpriteShowAllSet", darklua_dbSpriteShowAllSet);		
lua_register(L, "dbSpriteSizeSet", darklua_dbSpriteSizeSet);		
lua_register(L, "dbSpriteStretchSet", darklua_dbSpriteStretchSet);		
lua_register(L, "dbSpriteTextureCoordSet", darklua_dbSpriteTextureCoordSet);		
lua_register(L, "dbSpriteVisibleGet", darklua_dbSpriteVisibleGet);		
lua_register(L, "dbSpriteWidthGet", darklua_dbSpriteWidthGet);		
lua_register(L, "dbSpriteXGet", darklua_dbSpriteXGet);		
lua_register(L, "dbSpriteYGet", darklua_dbSpriteYGet);		
lua_register(L, "dbSQRT", darklua_dbSQRT);		
lua_register(L, "dbSquareTexturesOnlyAvailable", darklua_dbSquareTexturesOnlyAvailable);		
lua_register(L, "dbStaticCollisionHitGet", darklua_dbStaticCollisionHitGet);		
lua_register(L, "dbStaticCollisionXGet", darklua_dbStaticCollisionXGet);		
lua_register(L, "dbStaticCollisionYGet", darklua_dbStaticCollisionYGet);		
lua_register(L, "dbStaticCollisionZGet", darklua_dbStaticCollisionZGet);		
lua_register(L, "dbStaticLineOfSightGet", darklua_dbStaticLineOfSightGet);		
lua_register(L, "dbStaticLineOfSightXGet", darklua_dbStaticLineOfSightXGet);		
lua_register(L, "dbStaticLineOfSightYGet", darklua_dbStaticLineOfSightYGet);		
lua_register(L, "dbStaticLineOfSightZGet", darklua_dbStaticLineOfSightZGet);		
lua_register(L, "dbStatisticGet", darklua_dbStatisticGet);		
lua_register(L, "dbStr", darklua_dbStr);		
lua_register(L, "dbStringReadSet", darklua_dbStringReadSet);		
lua_register(L, "dbStringWrite", darklua_dbStringWrite);		
lua_register(L, "dbSuspendForKeySet", darklua_dbSuspendForKeySet);		
lua_register(L, "dbSuspendForMouseSet", darklua_dbSuspendForMouseSet);		
lua_register(L, "dbSync", darklua_dbSync);		
lua_register(L, "dbSyncOff", darklua_dbSyncOff);		
lua_register(L, "dbSyncOn", darklua_dbSyncOn);		
lua_register(L, "dbSyncRateSet", darklua_dbSyncRateSet);		
lua_register(L, "dbSystemKeysDisable", darklua_dbSystemKeysDisable);		
lua_register(L, "dbSystemKeysEnable", darklua_dbSystemKeysEnable);		
lua_register(L, "dbTAN", darklua_dbTAN);		
lua_register(L, "dbTerrainBuild", darklua_dbTerrainBuild);		
lua_register(L, "dbTerrainGroundHeightGet", darklua_dbTerrainGroundHeightGet);		
lua_register(L, "dbTerrainHeightmapSet", darklua_dbTerrainHeightmapSet);		
lua_register(L, "dbTerrainLightSet", darklua_dbTerrainLightSet);		
lua_register(L, "dbTerrainLoad", darklua_dbTerrainLoad);		
lua_register(L, "dbTerrainObjectMake", darklua_dbTerrainObjectMake);		
lua_register(L, "dbTerrainSave", darklua_dbTerrainSave);		
lua_register(L, "dbTerrainScaleSet", darklua_dbTerrainScaleSet);		
lua_register(L, "dbTerrainSplitSet", darklua_dbTerrainSplitSet);		
lua_register(L, "dbTerrainTextureSet", darklua_dbTerrainTextureSet);		
lua_register(L, "dbTerrainTilingSet", darklua_dbTerrainTilingSet);		
lua_register(L, "dbTerrainXSizeGet", darklua_dbTerrainXSizeGet);		
lua_register(L, "dbTerrainZSizeGet", darklua_dbTerrainZSizeGet);		
lua_register(L, "dbTextBackgroundTypeGet", darklua_dbTextBackgroundTypeGet);		
lua_register(L, "dbTextCenterSet", darklua_dbTextCenterSet);		
lua_register(L, "dbTextFontGet", darklua_dbTextFontGet);		
lua_register(L, "dbTextFontSet", darklua_dbTextFontSet);		
lua_register(L, "dbTextHeightGet", darklua_dbTextHeightGet);		
lua_register(L, "dbTextOpaqueSet", darklua_dbTextOpaqueSet);		
lua_register(L, "dbTextSet", darklua_dbTextSet);		
lua_register(L, "dbTextSizeGet", darklua_dbTextSizeGet);		
lua_register(L, "dbTextSizeSet", darklua_dbTextSizeSet);		
lua_register(L, "dbTextStyleGet", darklua_dbTextStyleGet);		
lua_register(L, "dbTextToBoldItalicSet", darklua_dbTextToBoldItalicSet);		
lua_register(L, "dbTextToBoldSet", darklua_dbTextToBoldSet);		
lua_register(L, "dbTextToItalicSet", darklua_dbTextToItalicSet);		
lua_register(L, "dbTextToNormalSet", darklua_dbTextToNormalSet);		
lua_register(L, "dbTextTransparentSet", darklua_dbTextTransparentSet);		
lua_register(L, "dbTextureMaximumHeightGet", darklua_dbTextureMaximumHeightGet);		
lua_register(L, "dbTextureMaximumWidthGet", darklua_dbTextureMaximumWidthGet);		
lua_register(L, "dbTextureSystemMemoryAvailable", darklua_dbTextureSystemMemoryAvailable);		
lua_register(L, "dbTextureVideoMemoryAvailable", darklua_dbTextureVideoMemoryAvailable);		
lua_register(L, "dbTextWidthGet", darklua_dbTextWidthGet);		
lua_register(L, "dbTimeGet", darklua_dbTimeGet);		
lua_register(L, "dbTimerGet", darklua_dbTimerGet);		
lua_register(L, "dbTLVertexSystemMemoryAvailable", darklua_dbTLVertexSystemMemoryAvailable);		
lua_register(L, "dbTLVertexVideoMemoryAvailable", darklua_dbTLVertexVideoMemoryAvailable);		
lua_register(L, "dbTNLAvailable", darklua_dbTNLAvailable);		
lua_register(L, "dbUpKeyGet", darklua_dbUpKeyGet);		
lua_register(L, "dbUpper", darklua_dbUpper);		
lua_register(L, "dbVal", darklua_dbVal);		
lua_register(L, "dbVector2AddSet", darklua_dbVector2AddSet);		
lua_register(L, "dbVector2CoordsTransformSet", darklua_dbVector2CoordsTransformSet);		
lua_register(L, "dbVector2CopySet", darklua_dbVector2CopySet);		
lua_register(L, "dbVector2DeleteGet", darklua_dbVector2DeleteGet);		
lua_register(L, "dbVector2DivideSet", darklua_dbVector2DivideSet);		
lua_register(L, "dbVector2DotProductGet", darklua_dbVector2DotProductGet);		
lua_register(L, "dbVector2HermiteSet", darklua_dbVector2HermiteSet);		
lua_register(L, "dbVector2IsEqualGet", darklua_dbVector2IsEqualGet);		
lua_register(L, "dbVector2LinearInterpolateSet", darklua_dbVector2LinearInterpolateSet);		
lua_register(L, "dbVector2MakeGet", darklua_dbVector2MakeGet);		
lua_register(L, "dbVector2MaximizeSet", darklua_dbVector2MaximizeSet);		
lua_register(L, "dbVector2MinimizeSet", darklua_dbVector2MinimizeSet);		
lua_register(L, "dbVector2MultiplySet", darklua_dbVector2MultiplySet);		
lua_register(L, "dbVector2NormalizeSet", darklua_dbVector2NormalizeSet);		
lua_register(L, "dbVector2ScaleSet", darklua_dbVector2ScaleSet);		
lua_register(L, "dbVector2Set", darklua_dbVector2Set);		
lua_register(L, "dbVector2SubtractSet", darklua_dbVector2SubtractSet);		
lua_register(L, "dbVector3AddSet", darklua_dbVector3AddSet);		
lua_register(L, "dbVector3CoordsTransformSet", darklua_dbVector3CoordsTransformSet);		
lua_register(L, "dbVector3CopySet", darklua_dbVector3CopySet);		
lua_register(L, "dbVector3CrossProductSet", darklua_dbVector3CrossProductSet);		
lua_register(L, "dbVector3DeleteGet", darklua_dbVector3DeleteGet);		
lua_register(L, "dbVector3DivideSet", darklua_dbVector3DivideSet);		
lua_register(L, "dbVector3DotProductGet", darklua_dbVector3DotProductGet);		
lua_register(L, "dbVector3HermiteSet", darklua_dbVector3HermiteSet);		
lua_register(L, "dbVector3IsEqualGet", darklua_dbVector3IsEqualGet);		
lua_register(L, "dbVector3LinearInterpolateSet", darklua_dbVector3LinearInterpolateSet);		
lua_register(L, "dbVector3MakeGet", darklua_dbVector3MakeGet);		
lua_register(L, "dbVector3MaximizeSet", darklua_dbVector3MaximizeSet);		
lua_register(L, "dbVector3MinimizeSet", darklua_dbVector3MinimizeSet);		
lua_register(L, "dbVector3MultiplySet", darklua_dbVector3MultiplySet);		
lua_register(L, "dbVector3NormalizeSet", darklua_dbVector3NormalizeSet);		
lua_register(L, "dbVector3NormalsTransformSet", darklua_dbVector3NormalsTransformSet);		
lua_register(L, "dbVector3ProjectSet", darklua_dbVector3ProjectSet);		
lua_register(L, "dbVector3ScaleSet", darklua_dbVector3ScaleSet);		
lua_register(L, "dbVector3Set", darklua_dbVector3Set);		
lua_register(L, "dbVector3SubtractSet", darklua_dbVector3SubtractSet);		
lua_register(L, "dbVector3ToCameraPositionSet", darklua_dbVector3ToCameraPositionSet);		
lua_register(L, "dbVector3ToCameraRotationSet", darklua_dbVector3ToCameraRotationSet);		
lua_register(L, "dbVector3ToLightPositionSet", darklua_dbVector3ToLightPositionSet);		
lua_register(L, "dbVector3ToLightRotationSet", darklua_dbVector3ToLightRotationSet);		
lua_register(L, "dbVector4AddSet", darklua_dbVector4AddSet);		
lua_register(L, "dbVector4CopySet", darklua_dbVector4CopySet);		
lua_register(L, "dbVector4DeleteGet", darklua_dbVector4DeleteGet);		
lua_register(L, "dbVector4DivideSet", darklua_dbVector4DivideSet);		
lua_register(L, "dbVector4HermiteSet", darklua_dbVector4HermiteSet);		
lua_register(L, "dbVector4IsEqualGet", darklua_dbVector4IsEqualGet);		
lua_register(L, "dbVector4LinearInterpolateSet", darklua_dbVector4LinearInterpolateSet);		
lua_register(L, "dbVector4MakeGet", darklua_dbVector4MakeGet);		
lua_register(L, "dbVector4MaximizeSet", darklua_dbVector4MaximizeSet);		
lua_register(L, "dbVector4MinimizeSet", darklua_dbVector4MinimizeSet);		
lua_register(L, "dbVector4MultiplySet", darklua_dbVector4MultiplySet);		
lua_register(L, "dbVector4NormalizeSet", darklua_dbVector4NormalizeSet);		
lua_register(L, "dbVector4ScaleSet", darklua_dbVector4ScaleSet);		
lua_register(L, "dbVector4Set", darklua_dbVector4Set);		
lua_register(L, "dbVector4SubtractSet", darklua_dbVector4SubtractSet);		
lua_register(L, "dbVector4TransformSet", darklua_dbVector4TransformSet);		
lua_register(L, "dbVectorPickXGet", darklua_dbVectorPickXGet);		
lua_register(L, "dbVectorPickYGet", darklua_dbVectorPickYGet);		
lua_register(L, "dbVectorPickZGet", darklua_dbVectorPickZGet);		
lua_register(L, "dbVertexShaderConstantsMaximumGet", darklua_dbVertexShaderConstantsMaximumGet);		
lua_register(L, "dbVertexShaderExist", darklua_dbVertexShaderExist);		
lua_register(L, "dbVertexShaderMatrixSet", darklua_dbVertexShaderMatrixSet);		
lua_register(L, "dbVertexShaderOff", darklua_dbVertexShaderOff);		
lua_register(L, "dbVertexShaderOn", darklua_dbVertexShaderOn);		
lua_register(L, "dbVertexShaderStreamCountSet", darklua_dbVertexShaderStreamCountSet);		
lua_register(L, "dbVertexShaderStreamSet", darklua_dbVertexShaderStreamSet);		
lua_register(L, "dbVertexShaderVectorSet", darklua_dbVertexShaderVectorSet);		
lua_register(L, "dbVideoMemoryFlushSet", darklua_dbVideoMemoryFlushSet);		
lua_register(L, "dbVolumeExtentMaximumGet", darklua_dbVolumeExtentMaximumGet);		
lua_register(L, "dbVolumeMapAvailable", darklua_dbVolumeMapAvailable);		
lua_register(L, "dbWaitKeySet", darklua_dbWaitKeySet);		
lua_register(L, "dbWaitMouseSet", darklua_dbWaitMouseSet);		
lua_register(L, "dbWaitSet", darklua_dbWaitSet);		
lua_register(L, "dbWBufferAvailable", darklua_dbWBufferAvailable);		
lua_register(L, "dbWFogAvailable", darklua_dbWFogAvailable);		
lua_register(L, "dbWindowHide", darklua_dbWindowHide);		
lua_register(L, "dbWindowMaximizeSet", darklua_dbWindowMaximizeSet);		
lua_register(L, "dbWindowMinimizeSet", darklua_dbWindowMinimizeSet);		
lua_register(L, "dbWindowOff", darklua_dbWindowOff);		
lua_register(L, "dbWindowOn", darklua_dbWindowOn);		
lua_register(L, "dbWindowPositionSet", darklua_dbWindowPositionSet);		
lua_register(L, "dbWindowRestoreSet", darklua_dbWindowRestoreSet);		
lua_register(L, "dbWindowShow", darklua_dbWindowShow);		
lua_register(L, "dbWindowSizeSet", darklua_dbWindowSizeSet);		
lua_register(L, "dbWindowTitleSet", darklua_dbWindowTitleSet);		
lua_register(L, "dbWordWrite", darklua_dbWordWrite);		
lua_register(L, "dbWrapValueGet", darklua_dbWrapValueGet);		
lua_register(L, "dbWriteByteToFileSet", darklua_dbWriteByteToFileSet);		
lua_register(L, "dbZBufferAvailable", darklua_dbZBufferAvailable);		
lua_register(L, "dbZFogAvailable", darklua_dbZFogAvailable);
lua_register(L, "luaScriptExecute", darklua_luaScriptExecute);

lua_register(L, "fxFuzzFragmentActionColor", darklua_uiGizmoColor);/*alias*/
lua_register(L, "fxFuzzFragmentActionSpin", darklua_uiGizmoSpin);/*alias*/
lua_register(L, "fxFuzzFragmentCount", darklua_fxFuzzFragmentCount);
lua_register(L, "fxFuzzFragmentGet", darklua_fxFuzzFragmentGet);
lua_register(L, "fxFuzzFragmentPropertyGet", darklua_uiGizmoPropertyGet); /*alias*/
lua_register(L, "fxFuzzFragmentPropertyGetByEventstate", darklua_uiGizmoPropertyGetByEventstate); /*alias*/
lua_register(L, "fxFuzzFragmentPropertySet", darklua_uiGizmoPropertySet); /*alias*/
lua_register(L, "fxFuzzFragmentPropertySetByEventstate", darklua_uiGizmoPropertySetByEventstate); /*alias*/
lua_register(L, "fxFuzzFragmentSet", darklua_fxFuzzFragmentSet);
lua_register(L, "netHTTPFileGet", darklua_netHTTPFileGet);		
//lua_register(L, "netHTTPRequestHeader", darklua_netHTTPRequestHeader);
lua_register(L, "phyActorFastUpdate", darklua_phyActorFastUpdate); 
lua_register(L, "phyActorRelease", darklua_phyActorRelease); 
lua_register(L, "phyActorsUpdate", darklua_phyActorsUpdate); 
lua_register(L, "phyActorUpdate", darklua_phyActorUpdate); 
lua_register(L, "phyAngularDampingSet", darklua_phyAngularDampingSet); 
lua_register(L, "phyAngularVelocitySet", darklua_phyAngularVelocitySet); 
lua_register(L, "phyAngularVelocityXGet", darklua_phyAngularVelocityXGet); 
lua_register(L, "phyAngularVelocityYGet", darklua_phyAngularVelocityYGet); 
lua_register(L, "phyAngularVelocityZGet", darklua_phyAngularVelocityZGet); 
lua_register(L, "phyBoxMake", darklua_phyBoxMake); 
lua_register(L, "phyBoxShapeMake", darklua_phyBoxShapeMake); 
lua_register(L, "phyCapsuleMake", darklua_phyCapsuleMake); 
lua_register(L, "phyCharacterControllerMove", darklua_phyCharacterControllerMove); 
lua_register(L, "phyCharacterControllerPosition", darklua_phyCharacterControllerPosition); 
lua_register(L, "phyCMassLocalPositionSet", darklua_phyCMassLocalPositionSet); 
lua_register(L, "phyCMassLocalPositionXGet", darklua_phyCMassLocalPositionXGet); 
lua_register(L, "phyCMassLocalPositionYGet", darklua_phyCMassLocalPositionYGet); 
lua_register(L, "phyCMassLocalPositionZGet", darklua_phyCMassLocalPositionZGet); 
lua_register(L, "phyCollisionGroupSet", darklua_phyCollisionGroupSet); 
lua_register(L, "phyCollisionOffSet", darklua_phyCollisionOffSet); 
lua_register(L, "phyCollisionOnSet", darklua_phyCollisionOnSet); 
lua_register(L, "phyCompoundActorMake", darklua_phyCompoundActorMake); 
lua_register(L, "phyContactActorAGet", darklua_phyContactActorAGet); 
lua_register(L, "phyContactActorBGet", darklua_phyContactActorBGet); 
lua_register(L, "phyContactDataGet", darklua_phyContactDataGet); 
lua_register(L, "phyContactPairRelease", darklua_phyContactPairRelease); 
lua_register(L, "phyContactPairSet", darklua_phyContactPairSet); 
lua_register(L, "phyControllerBoxMake", darklua_phyControllerBoxMake); 
lua_register(L, "phyControllerCapsuleMake", darklua_phyControllerCapsuleMake); 
lua_register(L, "phyControllerDimensionsSet", darklua_phyControllerDimensionsSet); 
lua_register(L, "phyControllerLocalPositionYGet", darklua_phyControllerLocalPositionYGet); 
lua_register(L, "phyControllerLocalPositionYSet", darklua_phyControllerLocalPositionYSet); 
lua_register(L, "phyControllerRelease", darklua_phyControllerRelease); 
lua_register(L, "phyControllersUpdate", darklua_phyControllersUpdate); 
lua_register(L, "phyConvexMeshMake", darklua_phyConvexMeshMake); 
lua_register(L, "phyConvexShapeMake", darklua_phyConvexShapeMake); 
lua_register(L, "phyDefaultDynamicFrictionGet", darklua_phyDefaultDynamicFrictionGet); 
lua_register(L, "phyDefaultDynamicFrictionSet", darklua_phyDefaultDynamicFrictionSet); 
lua_register(L, "phyDefaultRestitutionGet", darklua_phyDefaultRestitutionGet); 
lua_register(L, "phyDefaultRestitutionSet", darklua_phyDefaultRestitutionSet); 
lua_register(L, "phyDefaultSkinWidthGet", darklua_phyDefaultSkinWidthGet); 
lua_register(L, "phyDefaultSkinWidthSet", darklua_phyDefaultSkinWidthSet); 
lua_register(L, "phyDefaultStaticFrictionGet", darklua_phyDefaultStaticFrictionGet); 
lua_register(L, "phyDefaultStaticFrictionSet", darklua_phyDefaultStaticFrictionSet); 
lua_register(L, "phyForceApply", darklua_phyForceApply); 
lua_register(L, "phyGravityDisable", darklua_phyGravityDisable); 
lua_register(L, "phyGravityEnable", darklua_phyGravityEnable); 
lua_register(L, "phyGravitySet", darklua_phyGravitySet); 
lua_register(L, "phyGroundPlaneMake", darklua_phyGroundPlaneMake); 
lua_register(L, "phyGroundPlaneRelease", darklua_phyGroundPlaneRelease); 
lua_register(L, "phyGroupCollisionSet", darklua_phyGroupCollisionSet); 
lua_register(L, "phyKinematicOffSet", darklua_phyKinematicOffSet); 
lua_register(L, "phyKinematicOnSet", darklua_phyKinematicOnSet); 
lua_register(L, "phyLinearDampingSet", darklua_phyLinearDampingSet); 
lua_register(L, "phyLinearVelocitySet", darklua_phyLinearVelocitySet); 
lua_register(L, "phyLinearVelocityXGet", darklua_phyLinearVelocityXGet); 
lua_register(L, "phyLinearVelocityYGet", darklua_phyLinearVelocityYGet); 
lua_register(L, "phyLinearVelocityZGet", darklua_phyLinearVelocityZGet); 
lua_register(L, "phyLocalForceApply", darklua_phyLocalForceApply); 
lua_register(L, "phyLocalTorqueApply", darklua_phyLocalTorqueApply); 
lua_register(L, "phyMaterialMake", darklua_phyMaterialMake); 
lua_register(L, "phyMaterialSet", darklua_phyMaterialSet); 
lua_register(L, "phyMaterialSet", darklua_phyMaterialSet); 
lua_register(L, "phyObjectSwap", darklua_phyObjectSwap); 
lua_register(L, "phyOrientationSet", darklua_phyOrientationSet); 
lua_register(L, "phyPhysicsResultsGet", darklua_phyPhysicsResultsGet); 
lua_register(L, "phyPositionSet", darklua_phyPositionSet); 
lua_register(L, "phyPositionXFreeze", darklua_phyPositionXFreeze); 
lua_register(L, "phyPositionYFreeze", darklua_phyPositionYFreeze); 
lua_register(L, "phyPositionZFreeze", darklua_phyPositionZFreeze); 
lua_register(L, "phyRaycast", darklua_phyRaycast); 
lua_register(L, "phyRayDistanceGet", darklua_phyRayDistanceGet); 
lua_register(L, "phyRayImpactNormalXGet", darklua_phyRayImpactNormalXGet); 
lua_register(L, "phyRayImpactNormalYGet", darklua_phyRayImpactNormalYGet); 
lua_register(L, "phyRayImpactNormalZGet", darklua_phyRayImpactNormalZGet); 
lua_register(L, "phyRayImpactPosXGet", darklua_phyRayImpactPosXGet); 
lua_register(L, "phyRayImpactPosYGet", darklua_phyRayImpactPosYGet); 
lua_register(L, "phyRayImpactPosZGet", darklua_phyRayImpactPosZGet); 
lua_register(L, "phyRotationXFreeze", darklua_phyRotationXFreeze); 
lua_register(L, "phyRotationYFreeze", darklua_phyRotationYFreeze); 
lua_register(L, "phyRotationZFreeze", darklua_phyRotationZFreeze); 
lua_register(L, "phySimulate ", darklua_phySimulate); 
lua_register(L, "phySphereMake", darklua_phySphereMake); 
lua_register(L, "phySphereShapeMake", darklua_phySphereShapeMake); 
lua_register(L, "phyStart", darklua_phyStart); 
lua_register(L, "phyStop", darklua_phyStop); 
lua_register(L, "phyTorqueApply", darklua_phyTorqueApply); 
lua_register(L, "phyTriangleMeshFromDBOMake", darklua_phyTriangleMeshFromDBOMake); 
lua_register(L, "phyTriangleMeshMake", darklua_phyTriangleMeshMake); 
lua_register(L, "phyUpdate", darklua_phyUpdate); 
lua_register(L, "phyVehicleBuild", darklua_phyVehicleBuild); 
lua_register(L, "phyVehicleMake", darklua_phyVehicleMake); 
lua_register(L, "phyWheelDrive", darklua_phyWheelDrive); 
lua_register(L, "phyWheelShapeMake", darklua_phyWheelShapeMake); 
lua_register(L, "phyWheelSteer", darklua_phyWheelSteer); 
lua_register(L, "phyWheelsUpdate", darklua_phyWheelsUpdate); 
lua_register(L, "phyWheelSuspensionTravelMaxSet", darklua_phyWheelSuspensionTravelMaxSet);
lua_register(L, "sysConfigPropertyGet", darklua_sysConfigPropertyGet);
lua_register(L, "sysConfigPropertySet", darklua_sysConfigPropertySet);
lua_register(L, "sysConfigPropertyValueGet", darklua_sysConfigPropertyValueGet);		
lua_register(L, "sysConfigPropertyValueSet", darklua_sysConfigPropertyValueSet);
lua_register(L, "tbGameAppEntry", darklua_tbGameAppEntry);
lua_register(L, "tbGameAppList", darklua_tbGameAppList);
lua_register(L, "tbGameAppRegister", darklua_tbGameAppRegister);
lua_register(L, "tbGameAppReset", darklua_tbGameAppReset);
lua_register(L, "tbGameAppResults", darklua_tbGameAppResults);
lua_register(L, "tbGameAppStats", darklua_tbGameAppStats);
lua_register(L, "tbGameAppTest", darklua_tbGameAppTest);
lua_register(L, "tbGameAppVariableGet", darklua_tbGameAppVariableGet);
lua_register(L, "tbGameAppVariableSet", darklua_tbGameAppVariableSet);
lua_register(L, "testBed", darklua_testBed);		
lua_register(L, "uiCaretEdit", darklua_uiCaretEdit);		
lua_register(L, "uiCaretLocate", darklua_uiCaretLocate);		
lua_register(L, "uiFormSubmit", darklua_uiFormSubmit);		
lua_register(L, "uiGizmoCapture", darklua_uiGizmoCapture);		
lua_register(L, "uiGizmoExist", darklua_uiGizmoExist);		
lua_register(L, "uiGizmoGet", darklua_uiGizmoGet);		
lua_register(L, "uiGizmoLineDisplay", darklua_uiGizmoLineDisplay);		
lua_register(L, "uiGizmoLineEdit", darklua_uiGizmoLineEdit);
lua_register(L, "uiGizmoLinesCapture", darklua_uiGizmoLinesCapture);	
lua_register(L, "uiGizmoLinesCopy", darklua_uiGizmoLinesCopy);		
lua_register(L, "uiGizmoLineSelectionEdit", darklua_uiGizmoLineSelectionEdit);		
lua_register(L, "uiGizmoLinesGet", darklua_uiGizmoLinesGet);
lua_register(L, "uiGizmoMessageCreate", darklua_uiGizmoMessageCreate);		
lua_register(L, "uiGizmoMessageDestroy", darklua_uiGizmoMessageDestroy);		
lua_register(L, "uiGizmoMessageInsert", darklua_uiGizmoMessageInsert);		
lua_register(L, "uiGizmoMessageSend", darklua_uiGizmoMessageSend);		
lua_register(L, "uiGizmoPropertyGet", darklua_uiGizmoPropertyGet);
lua_register(L, "uiGizmoPropertyGetByEventstate", darklua_uiGizmoPropertyGetByEventstate);		
lua_register(L, "uiGizmoPropertySet", darklua_uiGizmoPropertySet);
lua_register(L, "uiGizmoPropertySetByEventstate", darklua_uiGizmoPropertySetByEventstate);
lua_register(L, "uiGizmoVariableGet", darklua_uiGizmoVariableGet);		
lua_register(L, "uiGizmoVariableSet", darklua_uiGizmoVariableSet);		
lua_register(L, "uiLoad", darklua_uiLoad);
lua_register(L, "uiOutput", darklua_uiOutput);
lua_register(L, "uiPointerPropertyGet", darklua_uiPointerPropertyGet);		
lua_register(L, "uiPointerPropertySet", darklua_uiPointerPropertySet);		

}