/*
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

/*Diag for general purpose logging etc*/

#pragma once
#ifndef DIAG_H
#define DIAG_H

#include <string>
#include <fstream>

using namespace std;

#define DEBUGLOG_TEXTTAB_MULTIPLIER 8

#define ALERTBOX_SEVERITY_ERROR 1
#define ALERTBOX_SEVERITY_WARNING 2

class debuglog{
		/**
		* @brief	
		*
		*/		
	private:
		int type;
		bool enableflag;
		bool appendflag;
		DWORD outputsourcebitflag; //0=Clipboard, 1=Logfile
		
	public:

		debuglog(void);
		~debuglog(void);

		string name;		//Log File Name
		string workingtext;	//
		int texttab;
		fstream file;

		enum outputsourcetypes{
			NONE					= 0x00,
			CLIPBOARD				= 0x01,
			LOGFILE					= 0x02	
		} outputsourcetype;

		static debuglog* create(char *logname);
		static void destroy(debuglog *instance);

		int start(char *filename);
		void stop(void);

		void print(string text);
		void append(string text);
		void write(void);
		void clear(void);
		void get(void);

		void enable(void);
		void disable(void);

		void outputsourceset(DWORD outputsourcebitflag);
		/*
		//outputs texts to clipboard
		//c:\WINDOWS\system32\clipbrd.exe
		*/
};


/*
class profiler{
	//profiler class
	
};
*/

int alertbox(string title, string message, int severity);
/*
Reference: http://msdn.microsoft.com/en-us/library/ms645505%28VS.85%29.aspx

int MessageBox(
  __in  HWND hWnd,
  __in  LPCTSTR lpText,
  __in  LPCTSTR lpCaption,
  __in  UINT uType
);
*/

extern debuglog *BugLog;

#endif