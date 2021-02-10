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

#include "..\DarkGDK\DarkGDK.h"
#include "diag.h"

//DEBUGLOG ///////////////////////////////////

/**
* @brief	Constructor
* @param	void
* @return	void
*/
debuglog::debuglog(void){

	enableflag = false;
	appendflag = false;
	outputsourcebitflag = CLIPBOARD;
	texttab = 0;
	type = 0;
}

/**
* @brief	Destructor
* @param	void
*/
debuglog::~debuglog(void){

}

/**
* @brief	
* @param	void
* @return	void
*/
debuglog* debuglog::create(char *logname){

	debuglog *instance = new debuglog;
	instance->start(logname);
	return(instance);
}

/**
* @brief	Destroy instance
* @param	void
* @return	void
*/
void debuglog::destroy(debuglog *instance){

	if(instance != NULL){
		instance->stop();
		delete instance;
	}
}

/**
* @brief	Opens Log File by filename.
* @param	filename
* @return	int
*/
int debuglog::start(char *filename){

	file.open(filename, fstream::out);
	if(file.is_open()){
		name = filename;
		outputsourcebitflag = LOGFILE;
		return(1);
	} else {
		return(-1);
	}
	return(0);
}

/**
* @brief	Closes Log File
* @param	void
* @return	void
*/
void debuglog::stop(void){

	if (file.is_open()) file.close();

}

/**
* @brief	Enables Output to HTML Logfile/Clipboard
* @param	void
* @return	void
*/
void debuglog::enable(void){

	enableflag = true;
	print(" LOG ENABLED ");
}


/**
* @brief	Disables Output to HTML Logfile/Clipboard
* @param	void
* @return	void
*/
void debuglog::disable(void){

	print(" LOG DISABLED ");
	enableflag = false;
}

/**
* @brief	Output workingtext to HTML Logfile/Clipboard, clear afterwards
* @param	string text
* @return	void
*/
void debuglog::print(string text){

	if(enableflag){

		if((outputsourcebitflag & LOGFILE) && file.is_open()){
			workingtext.append(text);
			file.write(workingtext.data(), workingtext.length());
			workingtext.clear();
		}

		if(outputsourcebitflag & CLIPBOARD){ /* Clipboard*/
			workingtext.append(text);
			//dbWriteToClipboard((char*)workingtext.data());
		}

	}
}

/**
* @brief	Get Contents from Clipboard
* @param	void
* @return	void
*/
void debuglog::get(void){

	//workingtext.append(dbGetClipboard());
}

/**
* @brief	Append Text to WorkingText
* @param	string text
* @return	void
*/
void debuglog::append(string text){

	workingtext.append(text);
}

/**
* @brief	
* @param	void
* @return	void
*/
void debuglog::write(void){

	if(enableflag){
		if((outputsourcebitflag & LOGFILE) && file.is_open()) file.write(workingtext.data(), workingtext.length());
		//if(outputsourcebitflag & CLIPBOARD) dbWriteToClipboard((char*)workingtext.data());
	}
}

/**
* @brief	
* @param	void
* @return	void
*/
void debuglog::clear(void){
	workingtext.clear();
}

/**
* @brief	
* @param	void
* @return	void
*/
void debuglog::outputsourceset(DWORD outputsourcetype){

	outputsourcebitflag = outputsourcetype;
}

/**
* @brief	
* @param	void
* @return	void
*/
int alertbox(string title, string message, int severity){

	UINT options;
	
	switch(severity){
		case ALERTBOX_SEVERITY_ERROR:
			title.insert(0,"S3GE ERROR::");
			options = MB_ICONERROR | MB_OKCANCEL | MB_DEFBUTTON2;
			BugLog->append("\n<font color=#ff0000><p>");
			break;

		case ALERTBOX_SEVERITY_WARNING:
			title.insert(0,"S3GE WARNING::");
			options = MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON1;
			BugLog->append("\n<font color=#ff9900><p>");
			break;
	}

    int msgboxID = MessageBox(
        NULL,
        (char*)message.data(),
        (char*)title.data(),
        options
    );

	BugLog->append(title);
	BugLog->append("\n<br>");
	BugLog->append(message);
	BugLog->print("</p></font>");

    switch (msgboxID){

		case IDCANCEL:
			switch(severity){
				default:
					exit(1);	
					break;
			}
			break;

		case IDOK:
			switch(severity){
				case ALERTBOX_SEVERITY_ERROR:
					exit(1);	
					break;
			}
			break;

	}
    return msgboxID;
}

debuglog *BugLog = NULL;