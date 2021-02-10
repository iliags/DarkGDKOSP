#pragma once
#ifndef XML_PLUGIN_H
#define XML_PLUGIN_H

//! irrXML plug-in by James 'Faker1089' Lennon

//this is for the XML parser
#include "irrXML.h"
using namespace irr;
using namespace io;

//this is to get data elements and file I/O
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//some macros to make things easier
#define xmlFile IrrXMLReader*
//#define xmlReader(file) (createIrrXMLReader(file))
//old macro that is uneeded, but works
/*
#define xmlGetData(file, type, element, var) \
	int done = 0; \
	string tempvar; \
	xmlFile theFile = xmlReader(file); \
	while(done ==0) \
	{ \
		theFile && theFile->read(); \
		if(theFile->getNodeType() == EXN_ELEMENT) \
		{ \
			if(!strcmp(type, theFile->getNodeName())) \
			{ \
				tempvar = theFile->getAttributeValue(element); \
				var = new char[tempvar.length()+1]; \
				strcpy(var, tempvar.c_str()); \
				done = 1; \
			} \
		} \
	} \
	delete &done; \
*/

#endif