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
along with this program. If not, see http://www.gnu.org/licenses/.
*/

/**
* @title	S3GE_Common.h
*
* @brief	A common library Features generic classes, templates, and utility functions for use any any plug-in.
*/


#pragma once
#ifndef S3GE_COMMON_H
#define S3GE_COMMON_H

#include <fstream>
#include <map>
#include <new>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <string>
#include <math.h>
#include <utility>

#define NOMINMAX      // Techlord put here, if(not included we get following:
                      // Error: min or max is #defined, probably in <windows.h>.  Put #define NOMINMAX before including windows.h to suppress windows global min,max macros.

#include "..\DarkGDK\DarkSDK.h"
#include "diag.h"
#include "d3d9.h"

using namespace std;

//DGDK ID Management by Techlord
class IndexManager{
	/**
	* @brief	Integer ID manager; Creates and manages Integer IDs with a LIFO Stack and List.
	*	Manage Integer IDs for Arrays Elements, DGDK Objects Reference, much more...
	* @location	[source]Common Library
	*/

	private:
		int Indices;
		stack<int> UnusedIndexStack; //not used
		list<int> UsedIndexList; //used
		list<int>::iterator UsedIndexListIterator;

	public:
		IndexManager(void){
		}

		IndexManager(int size){

			/**
			* @brief	[Constructor] Creates a Stack of IDs
			*
			* @location	[source]Common Library
			*
			* @param	int size - start number of IDs pushed to the stack from highest to lowest LIFO order.
			*/
			Indices = size;
			for(size+=1;size>0;size--){
				UnusedIndexStack.push(size);
			}
		}

		~IndexManager(void){}	

		int Peek(void){

			/**
			* @brief	Returns the next ID.
			*
			* @location	[source]Common Library
			*
			* @param	void
			*
			* @return	
			* @param	void
			*/

			int ID;
			if(UnusedIndexStack.size() == 1){
				ID = Indices + 1;
			} else {
				ID = UnusedIndexStack.top();
			}
			return(ID);
		}

		int Pop(void){

			/**
			* @brief	Pops ID from stack. If stack is empty it will increase the index return its value as the ID
			*
			* @location	[source]Common Library
			*
			* @param	void
			*
			* @return	[out]int - 
			*/

			int ID;
			if(UnusedIndexStack.size() == 1){
				ID = ++Indices;
			} else {
				ID = UnusedIndexStack.top();
				UnusedIndexStack.pop();
			}
			UsedIndexList.push_back(ID);
			return(ID);
		}

		void Push(int ID){

			/**
			* @brief	Pushes ID to stack for reuse.
			*
			* @location	[source]Common Library
			*
			* @param	int ID - pushed on to the stack.
			*
			* @return	
			* @param	void
			*/

			UnusedIndexStack.push(ID);
			UsedIndexList.remove(ID);
		}

		int Total(void){

			/**
			* @brief	Returns index total aka number from IDs 1 to n
			*
			* @location	[source]Common Library
			*
			*
			* @param	void
			*
			* @return	
			* @param	int count - value equal total number of Indices
			*/

			return(Indices);
		}

		int Unused(void){

			/**
			* @brief	Returns count of IDs not used
			*
			* @location	[source]Common Library
			*
			*
			* @param	void
			*
			* @return	
			* @param	int count - value equal number of Indices in not used
			*/

			return(UnusedIndexStack.size());
		}

		int Used(void){

			/**
			* @brief	Returns count of IDs used
			*
			* @location	[source]Common Library
			*
			*
			* @param	void
			*
			* @return	
			* @param	int count - value equal number of Indices used
			*/

			return(UsedIndexList.size());
		}
};

//DGDK Resource ID Management by Techlord
class ResourceManager{
	/**
	* @brief	Resource Manager; Manage Resource by Name Key, Index as Value 
	* @location	[source]Common Library
	*/
	private:
		IndexManager *Indexer;
		map<string,int> NameMap;
		map<string,int>::iterator NameMapIterator;

	public:

		ResourceManager(void){
		}

		ResourceManager(int size){

			/**
			* @brief	[Constructor] Creates a Stack of IDs
			*
			* @location	[source]Common Library
			*
			* @param	int size - start number of IDs pushed to the stack from highest to lowest LIFO order.
			*/
			Indexer = new IndexManager(size);
		}

		~ResourceManager(void){
			delete Indexer;
		}

		int Peek(void){
			return(Indexer->Peek());
		}

		int Pop(void){
			return(Indexer->Pop());
		}

		void Push(int ID){
			Indexer->Push(ID);
		}
			
		/**
		* @brief	Adds object name to NameMap by ID
		* @param	string name
		* @return	return Index
		*/
		int Add(string name){

			if(!NameMap[name]){
				NameMap[name] = Indexer->Pop();
			}
			return(NameMap[name]);
		}
		
		void Remove(string name){
			/**
			* @brief	Removes object name from NameMap
			*
			* @location	[source]Common Library
			*
			* @param	void
			*
			* @return	
			* @param	void
			*/

			if(NameMap[name]){
				Indexer->Push(NameMap[name]);
				NameMap.erase(name);
			}
		}

		int Get(string name){
			/**
			* @brief	Returns ID if exist, otherwise ERROR
			*
			* @location	[source]Common Library
			*
			* @param	void
			*
			* @return	
			* @param	void
			*/

			if(!NameMap[name]){return(-1);}
			return(NameMap[name]);
		}

		void Set(string name, int ID){

			/**
			* @brief	map name to ID manually, if none exist
			*
			* @location	[source]Common Library
			*
			* @param	void
			*
			* @return	
			* @param	void
			*/

			if(!NameMap[name]){
				NameMap[name] = ID;
			}
		}

};

//DGDK Object Resource Manager Pointers
extern ResourceManager *dbMemblockResource;
extern ResourceManager *dbBitmapResource;
extern ResourceManager *dbImageResource;
extern ResourceManager *dbSpriteResource;
extern ResourceManager *dbMeshResource;
extern ResourceManager *dbObjectResource;
extern ResourceManager *dbSoundResource;
extern ResourceManager *dbMusicResource;
extern ResourceManager *dbCameraResource;
extern ResourceManager *dbLightResource;
extern ResourceManager *FontResource;	
extern ResourceManager *S3GETextFontResource;

extern string Output;

#endif


