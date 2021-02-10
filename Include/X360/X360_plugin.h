#pragma once
#ifndef X360_PLUGIN_H
#define X360_PLUGIN_H

//! Xbox 360 controller plug-in by James 'Faker1089' Lennon

/*
 * The Xbox 360 Controller Library for DarkGDK was written by Todd A. Riggins
 * under the Creative Commons Attribution-No Derivative Works 3.0 Unported License
 * which can be found at http://creativecommons.org/licenses/by-nd/3.0/
 * It has been wrapped so that the function calls meet the standards for S3GE.
 */

//include the Xbox 360 for DGDK lib
#include "XB360C.h"

//some enumerations to make things easier

//use NORMAL for most things, becuase NEW_ALL is very slow (use it for menus and such)
enum MODE360 {
	NORMAL,
	NEW_CONTROLLER,
	NEW_ALL,
	NEW_HEADSET
};

enum CONTROL360 {
	GAMEPAD=1,
	WHEEL,
	ARCADE_STICK,
	FLIGHT_STICK,
	DANCEPAD,
	GUITAR,
	DRUMKIT=8
};

enum BATTERY360 {
	NOCONTROLLER=-3,
	NOHEADSET,
	WIRED,
	EMPTY,
	LOW,
	MEDIUM,
	FULL
};

enum ANSWER360 {
	NO=0,
	YES
};

enum VARIOUS {
	CONTROLLER=0,
	HEADSET
};

enum DPADBUTTONS {
	D_NONE=0,
	D_UP,
	D_DOWN,
	D_LEFT,
	D_RIGHT
};

//button macros
//returns 1 if pressed and 0 if not
#define BUTTON_A(index) XB360AButton(index)
#define BUTTON_B(index) XB360BButton(index)
#define BUTTON_X(index) XB360XButton(index)
#define BUTTON_Y(index) XB360YButton(index)
#define BUTTON_BACK(index) XB360AButton(index)
#define BUTTON_START(index) XB360AButton(index)
#define LBUMP(index) XB360LeftShoulder(index)
#define RBUMP(index) XB360RightShoulder(index)
#define LSTICK(index) XB360LeftThumb(index)
#define RSTICK(index) XB360RightThumb(index)
//DPAD returns 0-4 (see the DPAD enum)
#define DPAD(index) XB360DPAD(index)

//analog macros
//returns 0-255
#define LTRIGGER(index) XB360LeftTrigger(index)
#define RTRIGGER(index) XB360RightTrigger(index)
//returns -32768-327675
#define LSTICK_X(index) XB360ThumbLeftX(index)
#define LSTICK_Y(index) XB360ThumbLeftY(index)
#define RSTICK_X(index) XB360ThumbRightX(index)
#define RSTICK_Y(index) XB360ThumbRightY(index)

#endif