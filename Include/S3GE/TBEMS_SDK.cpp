/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TournamentBlitz Event Managment System v2.0 DarkNet by F.L.Taylor 2010
//tournamentblitz.hpquest.com
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TBEMS_SDK.h"
#include "S3GE_Common.h"
#include "S3GE.h"

using namespace std;
using namespace S3GE;

TBEMS::System *TBGameApp = new TBEMS::System;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TBEMS SYSTEM FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 	
* @brief	TBEMS System Constructor
* @param	void
*/
TBEMS::System::System(void){

	GameItemIndex = EventItemIndex = PlayerItemIndex = 0;
}
/** 	
* @brief	TBEMS System Destructor
* @param	void
*/
TBEMS::System::~System(void){
}

/** 	
* @brief	Creates new instance of TBEMS Object
* @param	string gameID
* @return	void
*/
void TBEMS::System::Start(string gameID){

	//setup variable name for switch
	VariableNameMap["SessionAdvertisement"] = TBEMS_VARIABLE_NAME_SESSIONADVERTISEMENT;
	VariableNameMap["SessionTimeout"] = TBEMS_VARIABLE_NAME_SESSIONTIMEOUT;
	VariableNameMap["SessionTimer"] = TBEMS_VARIABLE_NAME_SESSIONTIMER;
	VariableNameMap["SessionUname"] = TBEMS_VARIABLE_NAME_SESSIONUNAME;
	VariableNameMap["SessionPass"] = TBEMS_VARIABLE_NAME_SESSIONPASS;
	VariableNameMap["SessionActive"] = TBEMS_VARIABLE_NAME_SESSIONACTIVE;
	VariableNameMap["SessionLanguage"] = TBEMS_VARIABLE_NAME_SESSIONLANGUAGE;
	VariableNameMap["GamePlay"] = TBEMS_VARIABLE_NAME_GAMEPLAY;
	VariableNameMap["GameScore"] = TBEMS_VARIABLE_NAME_GAMESCORE;
	VariableNameMap["EventKey"] = TBEMS_VARIABLE_NAME_EVENTKEY;
	VariableNameMap["EventMessage"] = TBEMS_VARIABLE_NAME_EVENTMESSAGE;
	VariableNameMap["EventFinalScore"] = TBEMS_VARIABLE_NAME_EVENTFINALSCORE;
	VariableNameMap["EventLeader"] = TBEMS_VARIABLE_NAME_EVENTLEADER;
	VariableNameMap["EventList"] = TBEMS_VARIABLE_NAME_EVENTLIST;
	VariableNameMap["EventItem"] = TBEMS_VARIABLE_NAME_EVENTITEM;
	VariableNameMap["EventID"] = TBEMS_VARIABLE_NAME_EVENTID;
	VariableNameMap["EventName"] = TBEMS_VARIABLE_NAME_EVENTNAME;
	VariableNameMap["EventHostIP"] = TBEMS_VARIABLE_NAME_EVENTHOSTIP;
	VariableNameMap["EventType"] = TBEMS_VARIABLE_NAME_EVENTTYPE;
	VariableNameMap["EventMinSkill"] = TBEMS_VARIABLE_NAME_EVENTMINSKILL;
	VariableNameMap["EventEntryFee"] = TBEMS_VARIABLE_NAME_EVENTENTRYFEE;
	VariableNameMap["EventEntryFeeType"] = TBEMS_VARIABLE_NAME_EVENTENTRYFEETYPE;
	VariableNameMap["EventPlayerBalance"] = TBEMS_VARIABLE_NAME_EVENTPLAYERBALANCE;
	VariableNameMap["EventPrize"] = TBEMS_VARIABLE_NAME_EVENTPRIZE;
	VariableNameMap["EventMaxPlayers"] = TBEMS_VARIABLE_NAME_EVENTMAXPLAYERS;
	VariableNameMap["EventCurrentPlayers"] = TBEMS_VARIABLE_NAME_EVENTCURRENTPLAYERS;
	VariableNameMap["EventValue"] = TBEMS_VARIABLE_NAME_EVENTVALUE;
	VariableNameMap["PlayerRegister"] = TBEMS_VARIABLE_NAME_PLAYERREGISTER;
	VariableNameMap["PlayerEvents"] = TBEMS_VARIABLE_NAME_PLAYEREVENTS;
	VariableNameMap["PlayerCredits"] = TBEMS_VARIABLE_NAME_PLAYERCREDITS;
	VariableNameMap["PlayerTbpoints"] = TBEMS_VARIABLE_NAME_PLAYERTBPOINTS;
	VariableNameMap["PlayerTopScore"] = TBEMS_VARIABLE_NAME_PLAYERTOPSCORE;
	VariableNameMap["PlayerTopuname"] = TBEMS_VARIABLE_NAME_PLAYERTOPUNAME;
	VariableNameMap["PlayerList"] = TBEMS_VARIABLE_NAME_PLAYERLIST;
	VariableNameMap["PlayerItem"] = TBEMS_VARIABLE_NAME_PLAYERITEM;
	VariableNameMap["PlayerScore"] = TBEMS_VARIABLE_NAME_PLAYERSCORE;
	VariableNameMap["PlayerUname"] = TBEMS_VARIABLE_NAME_PLAYERUNAME;
	VariableNameMap["PlayerBonus"] = TBEMS_VARIABLE_NAME_PLAYERBONUS;
	VariableNameMap["PlayerRank"] = TBEMS_VARIABLE_NAME_PLAYERRANK;
	VariableNameMap["NetPing"] = TBEMS_VARIABLE_NAME_NETPING;

	TBGameApp->Table[TBEMS_TABLE_GAME] = new DataTable;
	TBGameApp->Table[TBEMS_TABLE_EVENT] = new DataTable;
	TBGameApp->Table[TBEMS_TABLE_PLAYER] = new DataTable;

	GameItemIndex = 1;
	TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex] = new DataItem;
	TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"] = gameID;

}

/** 	
* @brief	Creates new instance of TBEMS Object
* @param	void
* @return	void
*/
void TBEMS::System::Stop(void){


	delete TBGameApp->Table[TBEMS_TABLE_GAME];
	delete TBGameApp->Table[TBEMS_TABLE_EVENT];
	delete TBGameApp->Table[TBEMS_TABLE_PLAYER];
}

/** 	
* @brief	Updates TBEMS Processor
* @param	void
* @return	void
*/
void TBEMS::System::Update(void){
	
	Process();

}

/** 	
* @brief	TBEMS Processor
* @param	void
* @return	void
*/
void TBEMS::System::Process(void){

	switch(ProcessState){

		case IDLE:
			return;

		case LOAD:
			ProcessState = LOADING;
			break;

		case LOADING:
			if(HTTP->State != DarkNet::HTTP::TERMINATE){
				HTTP->Process();
			} else {
				delete HTTP;
				ProcessState = LOADCOMPLETE;
			}
			break;

		case LOADCOMPLETE:
			{
				//load variables from file
				if(Load(writepath) == 1){
					dbDeleteFile((char*)writepath.data());
					ProcessState = READY;
				}else{
					ProcessState = IDLE; //ERROR
				}
			}
			break;

		case DOWNLOADING:

			if(HTTPFile->State == S3GE::File::COMPLETE){

			}
			break;


		case READY:
			ProcessState = IDLE;		
			break;

	}
}

/** 	
* @brief	Request Data from TournamentBlitz Server
* @param	string reqeuststring
* @return	int
*/
int TBEMS::System::Request(string requeststring){


	if(Core->ConfigPropertyGet("TBEMSServer").empty()){
		alertbox("TBEMS::System::Request","TournamentBlitz EMS Server Not Found. Run `config.reg` and relaunch.",ALERTBOX_SEVERITY_ERROR);
		return(DARKNET_HTTP_ERROR);
	}

	writepath = Core->ConfigPropertyGet("GameContentDirectory");
	writepath.append("Data/Logic/TBEMS.dat");
	
	HTTP = DarkNet::HTTP::FileGet("TBEMSRequest", DARKNET_HTTP_METHOD_POST, Core->ConfigPropertyGet("TBEMSServer"), (int)dbVal((char*)Core->ConfigPropertyGet("TBEMSServerPort").data()), "/TBEMS.php", writepath, DARKNET_HTTP_TRANSFER_MODE_ASCII);
	HTTP->Request.PageVariables = requeststring;
	if(HTTP == NULL) return(DARKNET_HTTP_ERROR);
	//get dat file from network
	HTTP->ProcessNow();

	ProcessState = LOAD;

	//load variables from file
	if(Load(writepath) == 1){
		//delete dat file
		dbDeleteFile((char*)writepath.data());
	} else {
		return(0);
	}

}


/** 	
* @brief	Load Data from TournamentBlitz Data File
* @param	string filename
* @return	int	
*/
int TBEMS::System::Load(string filename){

	switch(int fileexists = Core->File->Exist(filename, File::GET_FROM_LOCAL)){

		case S3GE_FILE_NOTFOUND:
			return(S3GE_FILE_NOTFOUND);
			break;

	}

	string variablename;
	string value;

	BugLog->print("\n<h2>TournmentBlitz Data</h2>\n");

	ifstream file((char*)filename.data());
	if (file.is_open()){

		while (!file.eof()){

			getline(file,variablename);

			switch(VariableNameMap[variablename]){

				case TBEMS_VARIABLE_NAME_EVENTLIST:
					EventItemIndex||PlayerItemIndex ? BugLog->append("\n</ol>\n<ol>EventList\n") : BugLog->print("\n<ol>EventList\n");
					EventItemIndex = 0;
					break;

				case TBEMS_VARIABLE_NAME_PLAYERLIST:
					EventItemIndex||PlayerItemIndex ? BugLog->append("\n</ol>\n<ol>PlayerList\n") : BugLog->print("\n<ol>PlayerList\n");
					PlayerItemIndex = 0;
					break;

				case TBEMS_VARIABLE_NAME_EVENTITEM:
					EventItemIndex ? BugLog->append("</li>\n<li>EventItem<br>\n") : BugLog->print("\n<li>EventItem<br>\n");
					EventItemIndex++;
					if(TBGameApp->Table[TBEMS_TABLE_EVENT]->Item[EventItemIndex] == NULL) TBGameApp->Table[TBEMS_TABLE_EVENT]->Item[EventItemIndex] = new DataItem;
					break;

				case TBEMS_VARIABLE_NAME_PLAYERITEM:
					PlayerItemIndex ? BugLog->append("</li>\n<li>PlayerItem<br>\n") : BugLog->print("\n<li>PlayerItem<br>\n");
					PlayerItemIndex++;
					if(TBGameApp->Table[TBEMS_TABLE_PLAYER]->Item[PlayerItemIndex] == NULL) TBGameApp->Table[TBEMS_TABLE_PLAYER]->Item[PlayerItemIndex] = new DataItem;
					break;

				case TBEMS_VARIABLE_NAME_SESSIONADVERTISEMENT:
				case TBEMS_VARIABLE_NAME_SESSIONTIMEOUT:
				case TBEMS_VARIABLE_NAME_SESSIONTIMER:
				case TBEMS_VARIABLE_NAME_SESSIONUNAME:
				case TBEMS_VARIABLE_NAME_SESSIONPASS:
				case TBEMS_VARIABLE_NAME_SESSIONACTIVE:
				case TBEMS_VARIABLE_NAME_SESSIONLANGUAGE:
				case TBEMS_VARIABLE_NAME_GAMEPLAY:
				case TBEMS_VARIABLE_NAME_GAMESCORE:
				case TBEMS_VARIABLE_NAME_EVENTKEY:
				case TBEMS_VARIABLE_NAME_EVENTMESSAGE:
				case TBEMS_VARIABLE_NAME_EVENTFINALSCORE:
				case TBEMS_VARIABLE_NAME_EVENTLEADER:
				case TBEMS_VARIABLE_NAME_PLAYERREGISTER:
				case TBEMS_VARIABLE_NAME_PLAYEREVENTS:
				case TBEMS_VARIABLE_NAME_PLAYERCREDITS:
				case TBEMS_VARIABLE_NAME_PLAYERTBPOINTS:
				case TBEMS_VARIABLE_NAME_PLAYERTOPSCORE:
				case TBEMS_VARIABLE_NAME_PLAYERTOPUNAME:
				case TBEMS_VARIABLE_NAME_NETPING:
					getline(file, value);
					TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable[variablename] = value;
					BugLog->append("TBVar(");
					BugLog->append(dbStr(TBEMS_TABLE_GAME));
					BugLog->append(",");
					BugLog->append(dbStr(GameItemIndex));
					BugLog->append(")['");
					BugLog->append(variablename);
					BugLog->append("']");
					BugLog->append("=");
					BugLog->append(value);
					BugLog->print("<br>\n");
					break;

				case TBEMS_VARIABLE_NAME_EVENTID:
				case TBEMS_VARIABLE_NAME_EVENTNAME:
				case TBEMS_VARIABLE_NAME_EVENTHOSTIP:
				case TBEMS_VARIABLE_NAME_EVENTTYPE:
				case TBEMS_VARIABLE_NAME_EVENTMINSKILL:;
				case TBEMS_VARIABLE_NAME_EVENTENTRYFEE:
				case TBEMS_VARIABLE_NAME_EVENTENTRYFEETYPE:
				case TBEMS_VARIABLE_NAME_EVENTPLAYERBALANCE:
				case TBEMS_VARIABLE_NAME_EVENTPRIZE:
				case TBEMS_VARIABLE_NAME_EVENTMAXPLAYERS:
				case TBEMS_VARIABLE_NAME_EVENTCURRENTPLAYERS:
				case TBEMS_VARIABLE_NAME_EVENTVALUE:
					getline(file, value);
					TBGameApp->Table[TBEMS_TABLE_EVENT]->Item[EventItemIndex]->Variable[variablename] = value;
					BugLog->append("TBVar(");
					BugLog->append(dbStr(TBEMS_TABLE_EVENT));
					BugLog->append(",");
					BugLog->append(dbStr(EventItemIndex));
					BugLog->append(")['");
					BugLog->append(variablename);
					BugLog->append("']");
					BugLog->append("=");
					BugLog->append(value);
					BugLog->print("<br>\n");
					break;
				
				case TBEMS_VARIABLE_NAME_PLAYERSCORE:
				case TBEMS_VARIABLE_NAME_PLAYERUNAME:
				case TBEMS_VARIABLE_NAME_PLAYERBONUS:
				case TBEMS_VARIABLE_NAME_PLAYERRANK:
					getline(file, value);
					TBGameApp->Table[TBEMS_TABLE_PLAYER]->Item[PlayerItemIndex]->Variable[variablename] = value;
					BugLog->append("TBVar(");
					BugLog->append(dbStr(TBEMS_TABLE_PLAYER));
					BugLog->append(",");
					BugLog->append(dbStr(PlayerItemIndex));
					BugLog->append(")['");
					BugLog->append(variablename);
					BugLog->append("']");
					BugLog->append("=");
					BugLog->append(value);
					BugLog->print("<br>\n");
					break;
			}

		}

		EventItemIndex||PlayerItemIndex ? BugLog->print("</li>\n</ol>") : BugLog->print("<br>") ;



		file.close();

	} else {
		filename.append(" could not be opened!");
		alertbox("TBEMS Data File Load Error",filename,ALERTBOX_SEVERITY_WARNING);
		return(0);
	}

	return(1);
}

/** 	
* @brief	Get TBEMS Variable Value
* @param	int tableID
* @param	int itemID
* @param	string variablename
* @return	string
*/
string TBEMS::System::VariableGet(int tableID, int itemID, string variablename){
	
	if(VariableNameMap[variablename]== 0) return("");
	if(TBGameApp->Table[tableID] == NULL) return("");
	if(TBGameApp->Table[tableID]->Item[itemID] == NULL) return("");
	return(TBGameApp->Table[tableID]->Item[itemID]->Variable[variablename]);

}

/** 	
* @brief	Set TBEMS Variable Value
* @param	
* @return	
*/
void TBEMS::System::VariableSet(int tableID, int itemID, string variablename, string value){

	if(VariableNameMap[variablename]== 0) return;
	if(TBGameApp->Table[tableID] == NULL) return;
	if(TBGameApp->Table[tableID]->Item[itemID] == NULL) return;
	TBGameApp->Table[tableID]->Item[itemID]->Variable[variablename] = value;

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TBEMS UI FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 	
* @brief	Logins into TournamentBlitz Server and Retrieves Event List. Login response is stored in TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionActive"] Variable
			If TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionActive"]=TBGameApp->RESPONSE_OK, a list of Events is stored in TBGameApp->Event Array Group
			If Login all fails, Player should be presented with a Fail Alert Dialog and retuned to Login Dialog.
* @param	None
* @return	TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionActive"]= TBGameApp->RESPONSE_OK|TBGameApp->RESPONSE_ENTRYREGISTER|TBGameApp->RESPONSE_NOACCESS
*/
void TBEMS::System::List(void){
	
	string requeststring = "option=list&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&eventtype=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["EventType"]);
	Request(requeststring);
}

/** 	
* @brief	Submits Entry into Tournament. Prior to Calling this Function the Player a presented a dialog to confirm or cancel entry. 
			The dialog should  display event fee, available credits/tbpoints, and balance
* @param	None
* @return	TBGameApp->GamePlay= TBGameApp->RESPONSE_ENTRYSUCCESS|TBGameApp->RESPONSE_NOCREDITS|TBGameApp->RESPONSE_EVENTFULL
*/
void TBEMS::System::Entry(void){

	string requeststring = "option=entry&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&eventtype=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["EventType"]);
	requeststring.append("&eventID=");
	requeststring.append(dbStr(TBGameApp->EventSelectedIndex));
	Request(requeststring);
}
/** 	
* @brief	Submits Score when GameOver and retrieves Event Results. 
			Results are stored in TBGameApp->Player Array Group
* @param	None
* @return	void
*/
void TBEMS::System::Results(void){

	string requeststring = "option=results&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&eventkey=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["EventKey"]);
	requeststring.append("&score=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameScore"]);
	Request(requeststring);

}

/**
* @brief	Creates a TournamentBlitz Player 'Scoreboard' Account. 
			Login uname and Password is persistant until logout. If Login all fails, Player should be presented with a Fail Alert Dialog 
			and retuned to Login Dialog.
* @param	None
* @return	1=Username Accepted, -1=Username Taken
*/
void TBEMS::System::Register(void){


	string requeststring = "option=register&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	Request(requeststring);
}

/** 	
* @brief	Requests Stats History List for Game. Game Results storing Player results in stored in TBGameApp->player.TBGameApp->Player_Item(n)
* @param	None
* @return	
*/
void TBEMS::System::Stats(void){

	string requeststring = "option=stats&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	Request(requeststring);
}

/** 	
* @brief	Sets uname and Password to nil. Player should be returned to Login Dialog
* @param	None
* @return	None
*/
void TBEMS::System::Reset(void){

	TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"].clear();
	TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"].clear();
	TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionActive"].clear();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Real-Time Score Update
//Server is client
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 	
* @brief	Tournament Start
* @param	
* @return	
*/
void TBEMS::System::RTStart(string rtplayeruname,string rtplayerpass){

	string requeststring = "option=rtstart&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&rtplayeruname=");
	requeststring.append(rtplayeruname);
	requeststring.append("&rtplayerpass=");
	requeststring.append(rtplayerpass);
	Request(requeststring);
}


/** 	
* @brief	Tournament Stop
* @param	
* @return	
*/
void TBEMS::System::RTStop(string rtplayeruname,string rtplayerpass){

	string requeststring = "option=rtstop&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&rtplayeruname=");
	requeststring.append(rtplayeruname);
	requeststring.append("&rtplayerpass=");
	requeststring.append(rtplayerpass);
	Request(requeststring);
}

/** 	
* @brief	Player Enters the Tournament
* @param	
* @return	
*/
void TBEMS::System::RTEnter(string rtplayeruname,string rtplayerpass){

	string requeststring = "option=rtenter&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&rtplayeruname=");
	requeststring.append(rtplayeruname);
	requeststring.append("&rtplayerpass=");
	requeststring.append(rtplayerpass);
	Request(requeststring);
}

/** 	
* @brief	Player Exits the Tournament
* @param	
* @return	
*/
void TBEMS::System::RTExit(string rtplayeruname,string rtplayerpass){

	string requeststring = "option=rtexit&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&rtplayeruname=");
	requeststring.append(rtplayeruname);
	requeststring.append("&rtplayerpass=");
	requeststring.append(rtplayerpass);
	Request(requeststring);

}

/** 	
* @brief	Tournament Score update
* @param	
* @return	
*/
void TBEMS::System::RTUpdate(string rtplayeruname,string rtplayerpass){

	string requeststring = "option=rtupdate&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&rtplayeruname=");
	requeststring.append(rtplayeruname);
	requeststring.append("&rtplayerpass=");
	requeststring.append(rtplayerpass);
	requeststring.append("&eventkey=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["EventKey"]);
	requeststring.append("&score=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameScore"]);	
	Request(requeststring);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//In-Game Commerce
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 	
* @brief	Transfers Credits from Player Pass to Second Party. 
			Only Two Party Transfer Supported. Requires Both Parties Username And Password for Validation.
			Each transfer item must have a unique id//
* @param	None
* @return	TBGameApp->RESPONSE_TRADESUCCESSFUL, TBGameApp->RESPONSE_TRADEREJECTED
*/
void TBEMS::System::CommerceTrade(string commerceunamefrom,string commercepassfrom,string commerceunameto,string commercepassto,string commerceitemID){

	string requeststring = "option=commercetrade&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&commerceunamefrom=");
	requeststring.append(commerceunamefrom);
	requeststring.append("&commercepassfrom=");
	requeststring.append(commercepassfrom);
	requeststring.append("&commerceunameto=");
	requeststring.append(commerceunameto);
	requeststring.append("&commercepassto=");
	requeststring.append(commercepassto);
	requeststring.append("&commerceitemID=");
	requeststring.append(commerceitemID);
	Request(requeststring);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TBNet
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 	
* @brief	Lists TBNet Servers applicable to game
* @param	
* @return	
*/	
void TBEMS::System::TBNetList(void){
	
	string requeststring = "option=tbnetlist&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	Request(requeststring);
}

/** 	
* @brief	Registers Game Server to TBNet Server 
* @param	
* @return	
*/
void TBEMS::System::TBNetAdd(void){

	string requeststring = "option=tbnetadd&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&eventID=");
	requeststring.append(TBGameApp->Table[0]->Item[0]->Variable["TBNetEventID"]);
	Request(requeststring);
}

/** 	
* @brief	
* @param	
* @return	
*/
void TBEMS::System::TBNetRefresh(void){

	string requeststring = "option=tbnetrefresh&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&eventID=");
	requeststring.append(TBGameApp->Table[0]->Item[0]->Variable["TBNetEventID"]);
	Request(requeststring);	

}

/** 	
* @brief	Removes Server From TBNet Registration
* @param	
* @return	
*/	
void TBEMS::System::TBNetRemove(void){

	string requeststring = "option=tbnetremove&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&eventID=");
	requeststring.append(TBGameApp->Table[0]->Item[0]->Variable["TBNetEventID"]);
	Request(requeststring);
}

/** 	
* @brief	Ping TBNet Server
* @param	void
* @return	void
*/	
void TBEMS::System::TBNetPing(void){
		
	string requeststring = "option=tbnetping&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	requeststring.append("&eventID=");
	requeststring.append(TBGameApp->Table[0]->Item[0]->Variable["TBNetEventID"]);
	Request(requeststring);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//testing
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 	
* @brief	Transfers Credits from Player Pass to Second Party.
			Only Two Party Transfer Supported. Requires Both Parties Username And Password for Validation.
* @param	void
* @return	void
*/	
void TBEMS::System::Test(void){

	string requeststring = "option=test&uname=";
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionUname"]);
	requeststring.append("&pass=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["SessionPass"]);
	requeststring.append("&gameID=");
	requeststring.append(TBGameApp->Table[TBEMS_TABLE_GAME]->Item[GameItemIndex]->Variable["GameID"]);
	Request(requeststring);		
}

