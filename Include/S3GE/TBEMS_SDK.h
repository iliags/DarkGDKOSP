/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TournamentBlitz Event Managment System v2.0 DarkNet by F.L.Taylor 2010
//tournamentblitz.hpquest.com
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef TBEMS_SDK_H
#define TBEMS_SDK_H

#include "DarkNet.h"
#include "S3GE.h"

using namespace std;

#define TBEMS_RESPONSE_OK	1
#define TBEMS_RESPONSE_ENTRYREGISTER	2
#define TBEMS_RESPONSE_NOACCESS	0
#define TBEMS_RESPONSE_ENTRYSUCCESS	1
#define TBEMS_RESPONSE_NOCREDITS	-1
#define TBEMS_RESPONSE_EVENTFULL	-2
#define TBEMS_RESPONSE_NODATABASE	-256
#define TBEMS_RESPONSE_TRADESUCCESSFUL	1
#define TBEMS_RESPONSE_TRADEREJECTED	-1

//Variable names
#define TBEMS_VARIABLE_NAME_SESSIONADVERTISEMENT	1
#define TBEMS_VARIABLE_NAME_SESSIONTIMEOUT	2
#define TBEMS_VARIABLE_NAME_SESSIONTIMER	3
#define TBEMS_VARIABLE_NAME_SESSIONUNAME	4
#define TBEMS_VARIABLE_NAME_SESSIONPASS	5
#define TBEMS_VARIABLE_NAME_SESSIONACTIVE	6
#define TBEMS_VARIABLE_NAME_SESSIONLANGUAGE	7
#define TBEMS_VARIABLE_NAME_GAMEPLAY	8
#define TBEMS_VARIABLE_NAME_GAMESCORE	9
#define TBEMS_VARIABLE_NAME_EVENTKEY	10
#define TBEMS_VARIABLE_NAME_EVENTMESSAGE	11
#define TBEMS_VARIABLE_NAME_EVENTFINALSCORE	12
#define TBEMS_VARIABLE_NAME_EVENTLEADER	13
#define TBEMS_VARIABLE_NAME_EVENTLIST	14
#define TBEMS_VARIABLE_NAME_EVENTITEM	15
#define TBEMS_VARIABLE_NAME_EVENTID	16
#define TBEMS_VARIABLE_NAME_EVENTNAME	17
#define TBEMS_VARIABLE_NAME_EVENTHOSTIP	18
#define TBEMS_VARIABLE_NAME_EVENTTYPE	19
#define TBEMS_VARIABLE_NAME_EVENTMINSKILL	20
#define TBEMS_VARIABLE_NAME_EVENTENTRYFEE	21
#define TBEMS_VARIABLE_NAME_EVENTENTRYFEETYPE	22
#define TBEMS_VARIABLE_NAME_EVENTPLAYERBALANCE	23
#define TBEMS_VARIABLE_NAME_EVENTPRIZE	24
#define TBEMS_VARIABLE_NAME_EVENTMAXPLAYERS	25
#define TBEMS_VARIABLE_NAME_EVENTCURRENTPLAYERS	26
#define TBEMS_VARIABLE_NAME_EVENTVALUE	27
#define TBEMS_VARIABLE_NAME_PLAYERREGISTER	28
#define TBEMS_VARIABLE_NAME_PLAYEREVENTS	29
#define TBEMS_VARIABLE_NAME_PLAYERCREDITS	30
#define TBEMS_VARIABLE_NAME_PLAYERTBPOINTS	31
#define TBEMS_VARIABLE_NAME_PLAYERTOPSCORE	32
#define TBEMS_VARIABLE_NAME_PLAYERTOPUNAME	33
#define TBEMS_VARIABLE_NAME_PLAYERLIST	34
#define TBEMS_VARIABLE_NAME_PLAYERITEM	35
#define TBEMS_VARIABLE_NAME_PLAYERSCORE	36
#define TBEMS_VARIABLE_NAME_PLAYERUNAME	37
#define TBEMS_VARIABLE_NAME_PLAYERBONUS	38
#define TBEMS_VARIABLE_NAME_PLAYERRANK	39
#define TBEMS_VARIABLE_NAME_NETPING	40

#define TBEMS_TABLE_GAME	1
#define TBEMS_TABLE_EVENT	2
#define TBEMS_TABLE_PLAYER	3

namespace TBEMS{

	class DataItem{
		public:
			map <string, string> Variable;
			map <string, string>::iterator VariableIterator;
			void Set(string name, string value);
			string Get(string name);
	};

	class DataTable{
		public:
			map<int,DataItem*> Item;
	};

	class System{
		public:
			//TBEMS Object Group
			map <string, int> VariableNameMap;
			map <string, int>::iterator VariableNameMapIterator;

			int EventSelectedIndex;
			DarkNet::HTTP *HTTP;
			string writepath;
		
			map<int,DataTable*> Table;
			int GameItemIndex;//1=Game, 2=Event, 3=Player
			int PlayerItemIndex;
			int EventItemIndex;
			S3GE::File *HTTPFile;
			enum ProcessStates{IDLE,LOAD,LOADING,LOADCOMPLETE,DOWNLOADING,READY} ProcessState;

			System(void);
			~System(void);

			void Start(string gameID);
			void Stop(void);
			void Update(void);
			void Process(void);
			int Request(string requeststring);
			int Load(string filename);
			void List(void);
			void Entry(void);
			void Results(void);
			void Register(void);
			void Stats(void);
			void Reset(void);
			void RTStart(string rtplayeruname,string rtplayerpass);
			void RTStop(string rtplayeruname,string rtplayerpass);
			void RTEnter(string rtplayeruname,string rtplayerpass);
			void RTExit(string rtplayeruname,string rtplayerpass);
			void RTUpdate(string rtplayeruname,string rtplayerpass);
			void CommerceTrade(string commerceunamefrom,string commercepassfrom,string commerceunameto,string commercepassto,string commerceitemID);
			void TBNetList(void);
			void TBNetAdd(void);
			void TBNetRefresh(void);
			void TBNetRemove(void);
			void TBNetPing(void);
			void Test(void);
			string VariableGet(int tableID, int itemID, string variablename);
			void VariableSet(int tableID, int itemID, string variablename, string value);

	};

}

//Globals
extern TBEMS::System *TBGameApp;

#endif

/*
Design Notes:

Variables

	CommerceCredits
	CommercePass
	CommerceUname
	EventCurrentPlayers
	EventEntryFee
	EventEntryFeeType
	EventID
	EventItem
	EventList
	EventMaxPlayers
	EventMinSkill
	EventName
	EventPlayerBalance
	EventPrize
	EventType
	EventValue
	EventFinalScore
	EventKey
	EventLeader
	EventMessage - Welcome message
	Events
	EventSelectedIndex - stores event selected by TBEMS_Event_ID Array
	EventsMax //24 stores maximum number of events
	GameID - stores official game license key used as Game ID, must be acquired from TournamentBlitz.com required for communications with tournamentblitz
	GamePlay - stores entry response returned by TBEMS_Enter() Function. Valid Response: TBEMS_RESPONSE_ENTRYSUCCESS,TBEMS_RESPONSE_NOCREDITS,TBEMS_RESPONSE_EVENTFULL
	GameScore - stores gamescore submitted by TBEMS_Results() Function
	PlayerCredits
	PlayerEvents
	PlayerRegister
	Players
	PlayersMax 
	PlayerTbpoints
	PlayerTopScore
	PlayerTopUname
	RTPlayerpass
	RTPlayerUname
	SessionActive - stores login response returned by TBEMS_List() Function. Valid Response: TBEMS_RESPONSE_OK,TBEMS_RESPONSE_ENTRYREGISTER,TBEMS_RESPONSE_NOACCESS
	SessionAdvertisement
	SessionLanguage - "en-us"
	SessionPass - stores user password required for communications with tournamentblitz
	SessionTimeOut
	SessionTimer
	SessionUname - stores username required for communications with tournamentblitz
	TBNetEventID
	TBNetPingIP
*/