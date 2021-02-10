/*
__        __                 ___ ___     ___     ___  ___       __     __       
|  \  /\  |__) |__/    |\ | |__   |     |__  \_/  |  |__  |\ | /__  | /  \ |\ | 
|__/ /--\ |  \ |  \    | \| |___  |     |___ / \  |  |___ | \|  __/ | \__/ | \| 
DarkNet(MikeNet2.0) Extension For S3GE
Michael Pryor & Techlord

References:
http://www.darknetworking.com
HTTP Explanation HTTP://www.jmarshall.com/easy/HTTP/#HTTP1.1c3
HTTP Urlencoding HTTP://www.w3schools.com/tags/ref_URLEncode.asp
*/

#include "DarkNet.h"
#include "TBEMS_SDK.h"

ResourceManager *DarkNet::PALM::InstanceResource = new ResourceManager(DARKNET_INSTANCE_MAX);
ResourceManager *DarkNet::PALM::ClientResource = new ResourceManager(DARKNET_CLIENT_MAX);
int DarkNet::HTTP::URLEncodeCharacter[] = {37, 43, 8, 9, 10, 13, 32, 33, 34, 35, 36, 38, 39, 40, 41, 42, 44, 45, 46, 47, 58, 59, 60, 62, 63, 64, 91, 92, 93, 94, 95, 96, 123, 124, 125, 126};

DarkNet::System::System(void){
	//constructor
}

DarkNet::System::~System(void){
	//deconstructor
}

/**
* @brief	S3GE DarkNet(MikeNet2.0) & TournamentBlitz EMS initialization
* @param	[in]string gameID - = Unique Game Identification required and provided by HPQuest.com to register game on TBNet.
* @param	[in]int instances - The number of Dark Net instances to create. Most of the time 1 should be used, unless multiple games are going to be hosted.
* @param	[in]int threads - The number of threads to use. If set to 0, Dark Net will automatically choose.
* @return	void 
*/
void DarkNet::System::Start(string gameID, int instances=DARKNET_INSTANCE_MAX, int threads=0){


	mn::Start(instances, threads);

	//HTTP Assignments
	//Set Transfer Mode ASCII Extensions
	HTTP::TransferModeExtSet("txt");
	HTTP::TransferModeExtSet("xml");
	HTTP::TransferModeExtSet("php");
	HTTP::TransferModeExtSet("maui");
	HTTP::TransferModeExtSet("s3ge");

	//Response Codes
	//I2P Assignments

	//TournamentBlitz
	TBGameApp->Start(gameID);

}

/**
* @brief	Network Shutdown. This MUST be called at the end of the program, otherwise sockets will be left open and memory leaks can occur.
* @param	void
* @return	void
*/
void DarkNet::System::Stop(void){

	TBGameApp->Stop();

	mn::Finish(-1);
}
	
/**
* @brief	Master Update Method to update all Network Components.
* @param	void
* @param	void
*/
void DarkNet::System::Update(void){

	I2P::Update();
	HTTP::Update();

}

// PALM: Programmable Application Layer Model for Transactions: Request-Response //////////////////


/**
* @brief	Adds Methodname to Interger map
* @param	[in]string methodname
* @param	[in]int constant
* @return	void	
*/
void DarkNet::PALM::MethodNameAdd(string methodname, int constant){


	//if(!MethodNameMap[methodname]){MethodNameMap[methodname] = constant;}
}

// HTTP ////////////////////////////////////////////////////////////////////////////////////////

map<string,DarkNet::HTTP*> DarkNet::HTTP::NameMap;
map<string,DarkNet::HTTP*>::iterator DarkNet::HTTP::NameMapIterator;
list<DarkNet::HTTP*> DarkNet::HTTP::ActiveList;
list<DarkNet::HTTP*>::iterator DarkNet::HTTP::ActiveListIterator;
queue<DarkNet::HTTP*> DarkNet::HTTP::InactiveQueue;
map<string,int> DarkNet::HTTP::TransferModeExtMap;

/**
* @brief	HTTP Object Constructor
* @param	void
*/ 
DarkNet::HTTP::HTTP(void){

	InstanceID = 0;
	ClientID = 0;
	Request.Status = Response.Status = 0;
	Request.ContentLength = Response.ContentLength = 0;
	Response.BytesLoaded = 0;
	Response.Mode = DARKNET_HTTP_TRANSFER_MODE_ASCII;//ascii
	Request.Header.Task = Response.Header.Task = NULL;

	State = IDLE;

}

/**
* @brief	HTTP Object Destructor
* @param	void
*/
DarkNet::HTTP::~HTTP(void){

}

/**
* @brief	Create HTTP Object
* @param	[in]string name - 
* @param	[in]string hostname
* @param	[in]int port -
* @return	[out]HTTP* - HTTP Object Pointer
*/
DarkNet::HTTP *DarkNet::HTTP::Create(string name, string hostname, int port){


	HTTP *instance = new HTTP;

	instance->Profile = mn::CreateInstanceProfile();
	mn::SetProfileModeTCP(instance->Profile, (char)NetMode::ProtocolMode::TCP_FOR_HTTP);
	mn::SetProfileHandshakeEnabled(instance->Profile, false);
	mn::SetProfileGracefulDisconnectEnabled(instance->Profile, true);
	
	instance->Request.Hostname = hostname;
	instance->Request.Port = port;
	instance->Request.IP = (char*)mn::DNS_B(hostname.c_str());

	ActiveList.push_back(instance);
	NameMap[name] = instance;

	BugLog->append("\n<p>Create HTTP</p>\n");

	return(instance);
}

/**
* @brief	Destroy HTTP Object
* @param	[in]HTTP* instance -
* @return	void
*/
void DarkNet::HTTP::Destroy(DarkNet::HTTP *instance){
	
	BugLog->append("\n<p>Destroy HTTP</p>\n");

	InstanceResource->Push(instance->InstanceID);
	mn::DeleteInstanceProfile(instance->Profile);
	delete instance;

}

/**
* @brief	Update All HTTP Objects
* @param	void
* @return	void
*/
void DarkNet::HTTP::Update(void){

	//iterate through active devices
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
		(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive devices
	while (!InactiveQueue.empty()){
		ActiveList.remove(InactiveQueue.front());
		Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}
}

/**
* @brief	HTTP Transaction Process Method. Called from Update loop to Process HTTP Object based on Transaction State
* @param	void
* @return	void 
*/
void DarkNet::HTTP::Process(void){

	switch(State){

		case IDLE:
			break;

		case REQUESTSTART:
			InstanceID = InstanceResource->Pop();
			Request.Status = mn::Connect(InstanceID,Request.IP.c_str(),Request.Port,Request.IP.c_str(),Request.Port,5000,false,Profile);
			mn::SetAutoResizeTCP(InstanceID,ClientID,true);
			mn::SetBinaryModeTCP(InstanceID,ClientID,true - Response.Mode);
			State = REQUESTSTARTING;
			//break;
			
		case REQUESTSTARTING:
			Request.Status = mn::PollConnect(InstanceID);
			switch(Request.Status){

				case NetUtility::STILL_CONNECTING: 
					break;

				case NetUtility::CONNECTED:
					BugLog->print("\n<pre>\nConnected to Server\n");
					Request.Packet = mn::CreatePacket();
					Request.Header.LineCount = 0;
					mn::SetMemorySize(Request.Packet,1024);
					State = REQUEST;
					break;

				case NetUtility::TIMED_OUT:
					BugLog->print("\n<pre>\nConnection Timed Out\n");
					State = TERMINATE;
					break;

				case NetUtility::CONNECTION_ERROR:
					BugLog->print("\n<pre>\nError occurred whilst connecting\n");
					State = TERMINATE;
					break;

				case NetUtility::REFUSED:
					BugLog->print("\n<pre>\nError occurred: Server rejected connection Request\n");
					State = TERMINATE;
					break;
			}
			break; 

		case REQUEST://Request header
			//BugLog->print("\nREQUEST");
			switch(Request.Method){

				case DARKNET_HTTP_METHOD_POST:
					//method
					Request.Header.Line = "POST"; //replaced with map
					Request.Header.Line.append(" ");
					Request.Header.Line.append(Request.Page);
					Request.Header.Line.append(" HTTP/1.0\r\n");

					BugLog->append("\n<b>");
					BugLog->append(Request.Header.Line);
					BugLog->print("</b>");
		
					mn::AddStringC(Request.Packet, (char*)Request.Header.Line.data(),0,false);
					mn::AddStringC(Request.Packet, "Accept: */*\r\n",0,false);
				
					mn::AddStringC(Request.Packet, "Accept-Language: en-us\r\n",0,false);
					mn::AddStringC(Request.Packet, "User-Agent: S3GE_HTTP\r\n",0,false);
					//mn::AddStringC(Request.Packet, "Content-Type: application/text\r\n" ,0,false);
					mn::AddStringC(Request.Packet, "Content-Type: application/x-www-form-urlencoded\r\n" ,0,false);
					mn::AddStringC(Request.Packet, "Accept-Encoding: gzip, deflate\r\n",0,false);
					mn::AddStringC(Request.Packet, "User-Agent: S3GE HTTP\r\n",0,false);

					Request.Header.Line = "Host: ";
					Request.Header.Line.append(Request.Hostname);
					Request.Header.Line.append("\r\n");
					
					BugLog->print("\n");
					BugLog->print(Request.Header.Line);

					mn::AddStringC(Request.Packet, (char*)Request.Header.Line.data(),0,false);
				
					Request.Header.Line = "Content-Length: ";
					Request.Header.Line.append(dbStr((int)Request.PageVariables.size()));
					Request.Header.Line.append("\r\n");

					BugLog->print("\n");
					BugLog->print(Request.Header.Line);

					mn::AddStringC(Request.Packet, (char*)Request.Header.Line.data(),0,false);
					mn::AddStringC(Request.Packet, "Connection: close\r\n",0,false); //persistent connection
					mn::AddStringC(Request.Packet, "Cache-Control: no-cache\r\n" ,0,false);					
					mn::AddStringC(Request.Packet, "\r\n",0,false);

					BugLog->print("\nContents:\n");
					BugLog->print(Request.PageVariables);

					mn::AddStringC(Request.Packet, (char*)Request.PageVariables.data(),0,false); //pre encoded
					mn::AddStringC(Request.Packet, "\r\n",0,false);
					break;

				default: //DARKNET_HTTP_METHOD_GET:
					/*
						//header script
						Request.Header.Task = new DarkLUA::Task("HTTPRequestheaderscript", "assets/data/logic/HTTPheaderscript.lua");
						DarkLUA::System::StringSet("netHTTPRequestHostname",Request.Hostname);
						DarkLUA::System::StringSet("netHTTPRequestMethod",Request.Method);
						DarkLUA::System::StringSet("netHTTPRequestPage",Request.Page);
						DarkLUA::System::StringSet("netHTTPRequestPageVariables",Request.PageVariables);
						DarkLUA::System::IntegerSet("netHTTPRequestContentLength",Request.ContentLength);
						if(Request.Header.Task!=NULL){ 
							Request.Header.Task->Execute(DarkLUA::Task::RUNNING);
						} else {
							//error
							//cancel transmit
						}
						delete Request.Head.Task;
				*/

					//method
					Request.Header.Line = "GET";
					Request.Header.Line.append(" ");

					//PageVariables
					if(!Request.PageVariables.empty()){
						Request.Page.append("?");
						Request.Page.append(Request.PageVariables);
					}

					Request.Header.Line.append(Request.Page);
					Request.Header.Line.append(" HTTP/1.0\r\n");

					BugLog->append("\n<b>HTTP Request:");
					BugLog->append(Request.Header.Line);
					BugLog->print("</b>");

					mn::AddStringC(Request.Packet, (char*)Request.Header.Line.data(),0,false);
					mn::AddStringC(Request.Packet, "Accept: */*\r\n",0,false);
					mn::AddStringC(Request.Packet, "Accept-Language: en-us\r\n",0,false);
					mn::AddStringC(Request.Packet, "User-Agent: S3GE_HTTP\r\n",0,false);
					mn::AddStringC(Request.Packet, "Content-Type: application/text\r\n" ,0,false);
					mn::AddStringC(Request.Packet, "Accept-Encoding: gzip, deflate\r\n",0,false);

					Request.Header.Line = "Host: ";
					Request.Header.Line.append(Request.Hostname);
					Request.Header.Line.append("\r\n");
					mn::AddStringC(Request.Packet, (char*)Request.Header.Line.data(),0,false);
					mn::AddStringC(Request.Packet, "Connection: close\r\n",0,false); //persistent connection
					mn::AddStringC(Request.Packet, "",0,false);
					break;
			}

			mn::SendTCP(InstanceID, Request.Packet, ClientID, false, true);
			State = REQUESTEND;
			break;

		case REQUESTING://Request body
			
			break;

		case REQUESTEND:
			mn::DeletePacket(Request.Packet);
			State = RESPONSESTART;
			break;

		case RESPONSESTART:
			Response.Packet = mn::CreatePacket();
			Response.Header.LineCount = 0;
			State = RESPONSE;
			break; 

		case RESPONSE://Response Header
			if(mn::ClientConnected(InstanceID,ClientID) != 0){
				// Use less CPU
				Sleep(1);
			
				// Check for graceful disconnect
				if(mn::ClientConnected(InstanceID,ClientID) == NetUtility::NO_RECV){
					// Wait for all data to be received before closing connection
					if(mn::GetStoreAmountTCP(InstanceID, ClientID) == 0){

						//BugLog->append("\nRemaining bytes of unused data ");
						//BugLog->append(dbStr( (int)mn::GetBytesTCP(InstanceID,ClientID) ));
						//BugLog->print("\n");

						mn::ShutdownClient(InstanceID,ClientID);
						BugLog->print("\nShutdownClient!!!");

					}
				}

				// TCP packets
				Response.Status = mn::RecvTCP(InstanceID,Response.Packet,ClientID);
			
				if(Response.Status > 0){
					
					if(mn::GetUsedSize(Response.Packet) > 0){

//						BugLog->print("\nPacket data(");
//						BugLog->print(dbStr((int)mn::GetUsedSize(Response.Packet)));
//						BugLog->print(")\n");

						Response.Header.Line = mn::GetStringC(Response.Packet,mn::GetUsedSize(Response.Packet),true);
						Response.Header.LineCount++;

						BugLog->print(Response.Header.Line);
						BugLog->print("\n");

						//Parse Header

						//Response code
						if(Response.Header.Line.find("HTTP/") != string::npos & Response.Header.LineCount == 1){
							Response.Code = dbVal((char*)Response.Header.Line.substr(Response.Header.Line.find(" "),4).data());
							if(Response.Code >= 400){
								State = TERMINATE;
								break;
							}
						}

						//File Size
						if(Response.Header.Line.find("Content-Length: ") != string::npos){
							Response.ContentLength = dbVal((char*)Response.Header.Line.substr(Response.Header.Line.size() - (Response.Header.Line.size()-16)).data()); 
							
							BugLog->append("\nResponse.ContentLength[");
							BugLog->append(dbStr((int)Response.Header.Line.size()));
							BugLog->append("]{");
							BugLog->append(dbStr( (int)(Response.Header.Line.size() - (Response.Header.Line.size()-16)) ));
							BugLog->append("}:");
							BugLog->append(dbStr(Response.ContentLength));
							BugLog->print("\n");
						}

						
					//Header Terminator Found
					} else {

						State = RESPONDING;
						BugLog->append("\n<i>FILE ");
						Response.Mode == DARKNET_HTTP_TRANSFER_MODE_ASCII ? BugLog->append("ASCII"): BugLog->append("BINARY");
						BugLog->append(" TRANSFER[Affix:");
						BugLog->append(dbStr((int)mn::GetAffixEnableTCP(InstanceID,ClientID)));
						BugLog->append("] <-- ");
						BugLog->append(Request.Hostname);
						BugLog->print("</i>\n");

					}
				}
			} else {

				State = RESPONSEEND;

			}
			break;

		case RESPONDING://Response Body

			if(mn::ClientConnected(InstanceID,ClientID) != 0){
				// Use less CPU
				Sleep(1);

				// Check for graceful disconnect
				if(mn::ClientConnected(InstanceID,ClientID) == NetUtility::NO_RECV){
					// Wait for all data to be received before closing connection
//					BugLog->print("\nPackets in Queue:");
//					BugLog->print(dbStr((int)mn::GetStoreAmountTCP(InstanceID, ClientID)));
					if(mn::GetStoreAmountTCP(InstanceID, ClientID) == 0){

						BugLog->append("\nRemaining bytes of unused data ");
						BugLog->append(dbStr( (int)mn::GetBytesTCP(InstanceID, ClientID) ));
						BugLog->print("\n");

						mn::ShutdownClient(InstanceID,ClientID);
						BugLog->print("\nShutdownClient!!!\n</pre>\n");
					}
				}

				// TCP packets
				Response.Status = mn::RecvTCP(InstanceID, Response.Packet, ClientID);

				if(Response.Status > 0){

					if(mn::GetUsedSize(Response.Packet) > 0){

						Response.StoredPackets.push_back(mn::CreatePacketFromPacket(Response.Packet));

						Response.BytesLoaded += (int)mn::GetUsedSize(Response.Packet);
						double dPercent = ((double)Response.BytesLoaded /(double)Response.ContentLength) * 100;

/*
						BugLog->print(" size=");
						BugLog->print(dbStr((int)mn::GetUsedSize(Response.Packet)));
						BugLog->print(" total=");
						BugLog->print(dbStr(Response.BytesLoaded));
						if(Response.ContentLength){
							BugLog->print(" content=");
							BugLog->print(dbStr(Response.ContentLength));
							BugLog->print("(");
							BugLog->print(dbStr(Response.ContentLength - Response.BytesLoaded));
							BugLog->print(") %=");				
							BugLog->print(dbStr((int)dPercent));
						}
*/
						switch(Response.Mode){

							case DARKNET_HTTP_TRANSFER_MODE_BINARY: //display content as bytes
/*
								{
									
									string data = mn::GetStringSTD(Response.Packet,mn::GetUsedSize(Response.Packet));
									BugLog->print("\n");
									for(int loop = 0; loop < data.length() + 1; loop++){
										BugLog->print(data.substr(loop,1));
									}
									
								}
*/
								break;

							case DARKNET_HTTP_TRANSFER_MODE_ASCII: //display content as string
								{
									string data = mn::GetStringC(Response.Packet,mn::GetUsedSize(Response.Packet),Response.Mode);
//									BugLog->print("\n");
//									BugLog->print(data);
								}
								break;
						}
					}
				}

			} else {

				Response.BytesLoaded += (int)mn::GetUsedSize(Response.Packet);
				double dPercent = ((double)Response.BytesLoaded /(double)Response.ContentLength) * 100;

				BugLog->append("\n<p>Write file ");
				BugLog->append(Response.WritePath);
				BugLog->print("</p>\n");
/*
				BugLog->print(" size=");
				BugLog->print(dbStr((int)mn::GetUsedSize(Response.Packet)));
				BugLog->print(" total=");
				BugLog->print(dbStr(Response.BytesLoaded));
				if(Response.ContentLength){
					BugLog->print(" content=");
					BugLog->print(dbStr(Response.ContentLength));
					BugLog->print("(");
					BugLog->print(dbStr(Response.ContentLength - Response.BytesLoaded));
					BugLog->print(") %=");				
					BugLog->print(dbStr((int)dPercent));
				}

*/
				State = RESPONSEEND;
			}
			
			break;

		case RESPONSEEND:

			switch (Response.Mode){
				case DARKNET_HTTP_TRANSFER_MODE_BINARY:
					//write binary file
					Response.OutputFile.open((char*)Response.WritePath.data(), ios::out | ios::binary);
					break;
				default: 
					//write ascii file
					Response.OutputFile.open((char*)Response.WritePath.data(), ios::out );
			}

			for(int loop = 0;loop<Response.StoredPackets.size();loop++){
				//BugLog->print("\nWrite Packet ");
				//BugLog->print(dbStr(loop+1));
				//BugLog->print(" of ");
				//BugLog->print(dbStr((int)Response.StoredPackets.size()));
		
				mn::SetCursor(Response.StoredPackets[loop],0);
				//char *data = mn::GetStringC(Response.StoredPackets[loop], mn::GetUsedSize(Response.StoredPackets[loop]),Response.Mode);//false
				Response.OutputFile.write(mn::GetStringC(Response.StoredPackets[loop], mn::GetUsedSize(Response.StoredPackets[loop]),Response.Mode), mn::GetUsedSize(Response.StoredPackets[loop]));
				if (Response.Mode == DARKNET_HTTP_TRANSFER_MODE_ASCII) Response.OutputFile.write("\n",1);
				//delete[] data;
				mn::DeletePacket(Response.StoredPackets[loop]);
			}
			Response.OutputFile.close();

			mn::DeletePacket(Response.Packet);
			State = TERMINATE;
			break; 

		case RECOVER:
			break; 

		case PENDING:
			break; 

		case SUSPEND:
			break; 

		case SUSPENDED:
			break;

		case RELEASE:
			break; 

		case TERMINATE:
			BugLog->append("\n<p><font color=");
			Response.Code > 399 ? BugLog->append("#FF0000>Terminated ") : BugLog->append("#009900>Disconnect ");
			BugLog->append(dbStr(Response.Code));
			BugLog->print("</font></p>\n");
			mn::DisconnectClient(InstanceID, ClientID);
			InactiveQueue.push(this);
			State = EXIT;
			break;

	}

}

/**
* @brief	HTTP Transaction Process Method. Process Immediately HTTP Object based on Transaction State
* @param	void
* @return	[out]int 1=Good, -1=Error  
*/
int DarkNet::HTTP::ProcessNow(void){

	while(State != EXIT){//TERMINATE
		//if error return -1
		Process();
	}

	return 1;
}

/**
* @brief	Get File via HTTP Object
* @param	[in]int method - 
* @param	[in]string page - 
* @param	[in]string writepath - 
* @return	void 
*/
void DarkNet::HTTP::Get(int method, string page, string writepath){

	Request.Method = method;
	Request.Page = page;
	Response.WritePath = writepath;
	//remove directory path
	State = REQUESTSTART;
}
	
/**
* @brief	HTTP FileGet
* @param	[in]string name - 
* @param	[in]int method - 
* @param	[in]string hostname - 
* @param	[in]int port - 
* @param	[in]string page - 
* @param	[in]string writepath - 
* @param	[in](optional)string writepath - 
* @param	[in](optional)string writepath - 
* @param	[in]int mode - TransferMode: 0=Binary, 1=ASCII
* @return	[out]HTTP* - HTTP Object Pointer
*/
DarkNet::HTTP *DarkNet::HTTP::FileGet(string name, int method, string hostname, int port, string page, string writepath, int mode){

	HTTP *HTTP = Create(name, hostname, port);
	HTTP->Request.Method = method;
	HTTP->Request.Page = page;
	HTTP->Response.WritePath = writepath;
	HTTP->Response.Mode = TransferModeExtGet(HTTP->Request.Page);//mode; //
	HTTP->State =  REQUESTSTART;

	return(HTTP);
}

/**
* @brief	Encodes URL Special Characters with Hexcodes
* @param	[in]string urldata - 
* @return	[out]string - Encoded String
*/
string DarkNet::HTTP::URLEncode(string urldata){

	string urlencode;

	for(int loop=0; loop < 35; loop++){
		   int pos = urldata.find( dbChr(URLEncodeCharacter[loop]) ); // find first occurance
		   while ( pos != string::npos ){
				urlencode = dbHex(URLEncodeCharacter[loop]);
				urlencode.size() < 2 ? urlencode.insert(0,"%0") : urlencode.insert(0,"%");
				urldata.replace( pos, 1, urlencode);
				pos = urldata.find( dbChr(URLEncodeCharacter[loop]), pos + 1 );
		   } 
	}
    //urldata.replace("%20","+"); //replace 'space' codes with '+' to reduce character length

	return(urldata);
}

/**
* @brief	Sets a specified file extension for ASCII Transfer.
			DarkNet HTTP applies Binary Transfer to all files by Default. 
			Binary Transfer will mis-arrange data for ASCII. Thus, 
			ASCII Transfer must be defined prior to requesting a file. 
* @param	[in]string ext - file extension 
* @param	[in]int ,default=DARKNET_HTTP_TRANSFER_MODE_ASCII
*/
void DarkNet::HTTP::TransferModeExtSet(string ext, int mode){

	TransferModeExtMap[ext] = mode;
}

/**
* @brief	Returns the Tranfer Mode Setting for a File's Extension, if its set
* @param	[in]string file - filename
* @return	int Transfer Mode
*/
int DarkNet::HTTP::TransferModeExtGet(string file){
	
	return (TransferModeExtMap[file.substr(file.find_last_of(".") + 1)]);
}

// I2P: Immediate Input Protocol ////////////////////////////////////////////////////////////////////////////////////////
map<string,DarkNet::I2P*> DarkNet::I2P::NameMap;
map<string,DarkNet::I2P*>::iterator DarkNet::I2P::NameMapIterator;
list<DarkNet::I2P*> DarkNet::I2P::ActiveList;
list<DarkNet::I2P*>::iterator DarkNet::I2P::ActiveListIterator;
queue<DarkNet::I2P*> DarkNet::I2P::InactiveQueue;

/**
* @brief	I2P Object Constructor
* @param	void
*/
DarkNet::I2P::I2P(void){

	ID = 0;
	TCPIP = "";
	UDPIP = "";
	TCPPort = 0;
	UDPPort = 0;
	InstanceID = 0;
	Profile = 0;

}

/**
* @brief	I2P Object Destructor
* @param	void
*/
DarkNet::I2P::~I2P(void){

}

/**
* @brief	[static]Create I2P Network Object
* @param	[in]int role - I2P Entity Role: 0=Server, 1=Client
* @param	[in]string name - Name of Server Instance
* @param	[in]char* hostname - Hostname
* @param	[in]unsigned short port - Port
* @param	[in]int udpmode - UDP Mode
* @param	[in]int maxclients - Maximum number of Clients
* @return	[out]I2P Pointer
*/
DarkNet::I2P *DarkNet::I2P::Create(int role, string name, char* hostname, unsigned short port, int udpmode, int maxclients){

	I2P* instance = NULL; 

	switch(role){
		case 0:
			instance = new Server;
			if(!instance->Create(name, hostname, port, udpmode, maxclients)){
				delete instance;
				return(NULL);
			}
			break;

		case 1:
			instance = new Client;
			if(!instance->Create(name, hostname, port, udpmode)){
				delete instance;
				return(NULL);
			}
			break;
	}
	return(instance);
}

/**
* @brief	Destroy I2P Server Object
* @param	[in]Server* instance
* @return	void
*/
void DarkNet::I2P::Destroy(I2P* instance){

	delete instance;

}

/**
* @brief	Update All Active I2P Objects, Destroy All Deactivated I2P Object
* @param	void
* @return	void
*/
void DarkNet::I2P::Update(void){

	//iterate through active hosts
	for(ActiveListIterator = ActiveList.begin(); ActiveListIterator != ActiveList.end(); ActiveListIterator++ ){
		(*ActiveListIterator)->Process();
	}

	//Garbage Collection clean up inactive hosts
	while (!InactiveQueue.empty()){
		ActiveList.remove(InactiveQueue.front());
		//Destroy(InactiveQueue.front());
		InactiveQueue.pop();
	}
}

/**
* @brief	Sends Object to Garbage Collection
* @param	void
* @return	void
*/
void DarkNet::I2P::Trash(void){


	State = TERMINATE;
	InactiveQueue.push(this);
}

// I2P SERVER ////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	I2P Server Object Constructor
* @param	void
*/
DarkNet::Server::Server(void){


	ID = 0;
	TCPIP = "";
	UDPIP = "";
	TCPPort = 0;
	UDPPort = 0;
	InstanceID = 0;
	Profile = 0;

}

/**
* @brief	I2P Server Object Destructor
* @param	void
*/
DarkNet::Server::~Server(void){

}

/**
* @brief	Create I2P Server Object
* @param	[in]string name - Name of Server Instance
* @param	[in]char* hostname - Hostname
* @param	[in]unsigned short port - Port
* @param	[in]int udpmode - UDP Mode
* @param	[in]int maxclients - Maximum number of Clients
* @return	[out]Server* - I2P Server Object Pointer
*/
DarkNet::I2P *DarkNet::Server::Create(string name, char* hostname, unsigned short port, int udpmode, int maxclients){
	RecvPacket = mn::CreatePacket();
	SendPacket = mn::CreatePacket();
	mn::SetMemorySize(SendPacket,1024);

	Name = name;

	TCPIP = (char*)mn::DNS_B(hostname);
	TCPPort = port;
	UDPIP = TCPIP;
	UDPPort = port;
	UDPMode = udpmode;
	MaxClients = maxclients;

	Profile = mn::CreateInstanceProfile();

	// Set the local IP and port of the server
	// Note: if we did not use this command then MikeNet
	// would find a local IP and port to use automatically
	
	mn::SetProfileLocal(Profile ,TCPIP.c_str(),TCPPort,UDPIP.c_str(),UDPPort);
	mn::SetProfileModeUDP(Profile ,UDPMode);
	mn::SetProfileNumOperationsUDP(Profile,3);

	NetSocketTCP socket(1024, false, true, new NetModeTcpPrefixSize(2048,true));

	Status = mn::StartServer(InstanceID, MaxClients, Profile);

	// If started successfully
	if(Status == 0){

		BugLog->print("\nI2P Server Started");
		BugLog->print("\nTCP port: ");
		BugLog->print(dbStr(mn::GetLocalPortTCP(InstanceID)));
		BugLog->print("\nUDP port: ");
		BugLog->print(dbStr(mn::GetLocalPortUDP(InstanceID)));

		State = ACCEPT;
		ActiveList.push_back(this);
		NameMap[name] = this;

	} else {	// If failed to start

		BugLog->print("\nServer failed to start\n");
		State = TERMINATE;

		return(NULL);

	}

	return(this);

}

/**
* @brief	Process Server Objects Based on Hoststate
* @param	void
* @return	void 
*/
void DarkNet::Server::Process(void){


	switch(State){

		case ACCEPT:
			{
				// Use less CPU
				Sleep(1);

				// Check to see if a new client has joined
				size_t Joined = mn::ClientJoined(InstanceID);
				
				// If a new client has joined
				if(Joined > 0){

					// Display the new client's information
					BugLog->print("\nA new Client has joined with a client ID of ");
					BugLog->print(dbStr((int)Joined));
					BugLog->print("\nClient TCP IP is: ");
					BugLog->print(mn::GetClientIPTCP(InstanceID,Joined));
					BugLog->print("\nClient TCP port is: ");
					BugLog->print(dbStr(mn::GetClientPortTCP(InstanceID,Joined)));
					BugLog->print("\nClient UDP IP is: ");
					BugLog->print(mn::GetClientIPUDP(InstanceID,Joined));
					BugLog->print("\nClient UDP port is: ");
					BugLog->print(dbStr(mn::GetClientPortUDP(InstanceID,Joined)));

					// Tell the new client what clients are currently connected

					//iterate through active clients

					if(ClientList.empty() == true){
						mn::AddInt(SendPacket,OP_NEWPLAYER);
						mn::AddInt(SendPacket,Joined);
						mn::SendTCP(InstanceID,SendPacket,Joined,false,false);
						ClientList.push_back(Joined);
					} else {
						for(ClientListIterator = ClientList.begin(); ClientListIterator != ClientList.end(); ClientListIterator++ ){
							if(mn::ClientConnected(InstanceID, (*ClientListIterator)) == 1){
								if((*ClientListIterator) != Joined){
									mn::AddInt(SendPacket,OP_NEWPLAYER);
									mn::AddInt(SendPacket,Joined);
									mn::SendTCP(InstanceID,SendPacket,Joined,false,false);
									ClientList.push_back(Joined);
								}
							}
						}
					}

					// Tell clients that a new client has joined
					mn::AddInt(SendPacket,OP_NEWPLAYER);
					mn::AddInt(SendPacket,Joined);
					mn::SendAllTCP(InstanceID,SendPacket,false,false,Joined);
				}
				
				// Check to see if any clients have left recently
				size_t Left = mn::ClientLeft(InstanceID);

				// If a client has left recently
				if(Left > 0){

					// Print the client id of the client who left
					BugLog->print("\nClient ");
					BugLog->print(dbStr((int)Left));
					BugLog->print(" has disconnected");

					// Tell clients that a client has left
					mn::AddInt(SendPacket,OP_LEFTPLAYER);
					mn::AddInt(SendPacket,Left);
					mn::SendAllTCP(InstanceID,SendPacket,false,false,Left);
					ClientList.remove(Left);

				}
				
				// Deal with new packets from all clients
				for(ClientListIterator = ClientList.begin(); ClientListIterator != ClientList.end(); ClientListIterator++ ){

					// Check to see if any new TCP packets have been received
					Status = mn::RecvTCP(InstanceID,RecvPacket,(*ClientListIterator));
					
					// If any have been received then do nothing
					// for now ignore tcp packets from clients
					if(Status > 0){
						BugLog->print("\nNew TCP packet received from client ");
						BugLog->print(dbStr(Status));
					}

					for(size_t operation = 0;operation<mn::GetMaxOperations(InstanceID);operation++){

						// Check to see if any new UDP packets have been received
						Status = mn::RecvUDP(InstanceID,RecvPacket,(*ClientListIterator),operation);
						
						// If any have been received
						if(Status > 0){

							// Begin formulating packet to send to clients
							mn::AddSizeT(SendPacket,(*ClientListIterator));
							mn::AddSizeT(SendPacket,operation);

							// Decide what to do depending on operation
							switch(operation){

								case(OP_FLOAT):
								{
									float fl = mn::GetFloat(RecvPacket);
									BugLog->print("\nFloat <-- Client ");
									BugLog->print(dbStr((int)(*ClientListIterator)));
									BugLog->print(": ");
									BugLog->print(dbStr(fl));

									// Finish formulating packet to send to clients
									mn::AddFloat(SendPacket,fl);
								}
								break;

								case(OP_STRING):
								{
									char * str = mn::GetStringC(RecvPacket,0,1);
									BugLog->print("\nString <-- Client ");
									BugLog->print(dbStr((int)(*ClientListIterator)));
									BugLog->print(": "); 
									BugLog->print(str);

									// Finish formulating packet to send to clients
									mn::AddStringC(SendPacket,str,0,true);

									// Deallocate memory allocated by mn::GetStringC
									delete[] str;
								}
								break;

								case(OP_INT):
								{
									int i = mn::GetInt(RecvPacket);
									BugLog->print("\nInteger <-- Client ");
									BugLog->print(dbStr((int)(*ClientListIterator)));
									BugLog->print(": ");
									BugLog->print(dbStr(i));

									// Finish formulating packet to send to clients
									mn::AddInt(SendPacket,i);
								}
								break;

								default:
									BugLog->print("\nInvalid operation\n");
									system("PAUSE");
								break;
							}

							// Send packet to all clients (excluding the client we received it from)
							mn::SendAllUDP(InstanceID,SendPacket,0,1,(*ClientListIterator));
						}
					}
				}
			}
			break;

		case TERMINATE:
			BugLog->print("\nTERMINATE");
			mn::DisconnectClient(InstanceID, ClientID);
			break;
	}
}

// I2P CLIENT ////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief	I2P Client Object Constructor
* @param	void
*/
DarkNet::Client::Client(void){

	ID = 0;
	TCPIP = "";
	UDPIP = "";
	TCPPort = 0;
	UDPPort = 0;
	InstanceID = 0;
	Profile = 0;

}

/**
* @brief	I2P Client Object Destructor
* @param	void
*/
DarkNet::Client::~Client(void){

}

/**
* @brief	Create I2P Client Object
* @param	[in]string name - Name of Client Instance
* @param	[in]char* hostname - Hostname
* @param	[in]unsigned short port - Port
* @param	[in]int udpmode - UDP Mode
* @param	[in]int maxclients - To be determined
* @return	[out]Client* - I2P Client Object Pointer
*/
DarkNet::I2P *DarkNet::Client::Create(string name, char* hostname, unsigned short port, int udpmode){

	RecvPacket = mn::CreatePacket();
	SendPacket = mn::CreatePacket();
	mn::SetMemorySize(SendPacket,1024);

	Name = name;

	Hostname = hostname;
	TCPIP = (char*)mn::DNS_B(hostname);
	TCPPort = port;
	UDPIP = TCPIP;
	UDPPort = port;
	UDPMode = udpmode;

	Profile = mn::CreateInstanceProfile();

	// Set the local IP and port of the server
	// Note: if we did not use this command then MikeNet
	// would find a local IP and port to use automatically
	
	mn::SetProfileLocal(Profile ,TCPIP.c_str(),0,UDPIP.c_str(),0);
	mn::SetProfileModeUDP(Profile ,UDPMode);
	mn::SetProfileNumOperationsUDP(Profile,3);

	//JOIN
	Status = mn::Connect(InstanceID,TCPIP.c_str(),TCPPort,UDPIP.c_str(),UDPPort, 5000, false,Profile);
	mn::SetAutoResizeTCP(InstanceID,ClientID,true);

	BugLog->print("\nI2P Client Joining");
	BugLog->print("\nTCP port: ");
	BugLog->print(dbStr(mn::GetLocalPortTCP(InstanceID)));
	BugLog->print("\nUDP port: ");
	BugLog->print(dbStr(mn::GetLocalPortUDP(InstanceID)));

	State = JOINING;
	ActiveList.push_back(this);
	NameMap[name] = this;
	return(this);

}
/**
* @brief	Process Client Object based on State
* @param	void
* @return	void
*/
void DarkNet::Client::Process(void){


	string linedata;

	switch(State){

		case IDLE:
			break;

		case JOINING:
			BugLog->print("\nJOINING");
			Status = mn::PollConnect(InstanceID);
			switch(Status){

				case NetUtility::STILL_CONNECTING:
					break;

				case NetUtility::CONNECTED:
					BugLog->print("\nConnected to Server\n");
					RecvPacket = mn::CreatePacket();
					mn::SetMemorySize(RecvPacket,1024);
					// Find maximum number of clients
					// necassary for UDP receiving					
					
					// Display information
					BugLog->print(" The Local TCP IP is: ");
					BugLog->print(mn::GetLocalIPTCP(InstanceID));
					
					BugLog->print(" The Local TCP port is: ");
					BugLog->print(dbStr(mn::GetLocalPortTCP(InstanceID)));

					BugLog->print(" The Local UDP IP is: ");
					BugLog->print(mn::GetLocalIPUDP(InstanceID));
					
					BugLog->print(" The Local UDP port is: ");
					BugLog->print(dbStr(mn::GetLocalPortUDP(InstanceID)));

					BugLog->print(" Your Client ID is: ");
					BugLog->print(dbStr((int)mn::GetClientID(InstanceID)));
					
					State = JOINED;
					break;


				case NetUtility::TIMED_OUT:
					BugLog->print("\nConnection Timed Out\n");
					State = TERMINATE;
					break;

				case NetUtility::CONNECTION_ERROR:
					BugLog->print("\nError occurred whilst connecting\n");
					State = TERMINATE;
					break;

				case NetUtility::REFUSED:
					BugLog->print("\nError occurred: Server rejected connection Request\n");
					State = TERMINATE;
					break;
			}
			break; 

		case JOINED://Request header
			BugLog->print("\nJOINED --> ");
			BugLog->print(Hostname);
			//mn::SendTCP(InstanceID, RecvPacket, ClientID, false, true);
			State = ACCEPTING;
			break;

		case ACCEPTING://Response Body
			//BugLog->print("\nACCEPTING:"); 
			//BugLog->print(dbStr(mn::ClientConnected(InstanceID,ClientID)));

			if(mn::ClientConnected(InstanceID,ClientID) != 0){

				// Use less CPU
				Sleep(1);

				// Check for graceful disconnect
				if(mn::ClientConnected(InstanceID,ClientID) == NetUtility::NO_RECV){
					// Wait for all data to be received before closing connection
					BugLog->print("\nPackets in Queue:");
					BugLog->print(dbStr((int)mn::GetStoreAmountTCP(InstanceID, ClientID)));
					if(mn::GetStoreAmountTCP(InstanceID, ClientID) == 0){

						BugLog->print("\nRemaining bytes of unused data ");
						BugLog->print(dbStr( (int)mn::GetBytesTCP(InstanceID,ClientID) ));
						BugLog->print("\n");

						mn::ShutdownClient(InstanceID,ClientID);
						BugLog->print("\nShutdownClient!!!");
					}
				}


				// TCP packets
				Status = mn::RecvTCP(InstanceID,RecvPacket,ClientID);
			
				if(Status > 0)
				{
					cout << "New TCP packet received\n";
				}

				// UDP Packets
				for(size_t simclient = 1; simclient <= mn::GetMaxClients(InstanceID); simclient++)
				{
					for(size_t operation = 0; operation <mn::GetMaxOperations(InstanceID); operation++)
					{
						Status = mn::RecvUDP(InstanceID, RecvPacket, simclient, operation);
						
						if(Status > 0)
						{
							// Decide what to do depending on operation
							switch(operation)
							{
								case(OP_FLOAT):
								{
									float fl = mn::GetFloat(RecvPacket);
									BugLog->print("\nFloat <-- Server <-- Client "); 
									BugLog->print(dbStr((int)simclient));
									BugLog->print(": ");
									BugLog->print(dbStr((int)fl));
								}
								break;

								case(OP_STRING):
								{
									char* str = mn::GetStringC(RecvPacket,0,1);
									BugLog->print("\nString <-- Server <-- Client ");
									BugLog->print(dbStr((int)simclient));
									BugLog->print(": ");
									BugLog->print(str);

									// Deallocate memory allocated by mn::GetStringC
									delete[] str;
								}
								break;

								case(OP_INT):
								{
									int i = mn::GetInt(RecvPacket);
									BugLog->print("\nInteger <-- Server <-- Client ");
									BugLog->print(dbStr((int)simclient));
									BugLog->print(": ");
									BugLog->print(dbStr((int)i));
								}
								break;

								default:
									BugLog->print("\nInvalid operation");
									system("PAUSE");
								break;
							}
						}
					}
				}

				// Get Input Updates >> HERE <<

				// Send messages every 1000ms
				
				if(clock() - Response.StartTime > 1000)
				{
					// Operation
					int operation = rand() % 3; // Random number between 0 and 2
					mn::AddSizeT(SendPacket,operation);

					// Decide what to do depending on operation
					switch(operation)
					{
						case(OP_FLOAT):
						{
							float fl = (rand()*1.0f)+(rand() % 11)*0.1f;
							mn::AddFloat(SendPacket,fl);

							BugLog->print("\nFloat --> Server: ");
							BugLog->print(dbStr(fl));
						}
						break;

						case(OP_STRING):
						{
							time_t time1 = time(NULL);
							tm * time2 = localtime(&time1);
							char * str = asctime(time2);
							
							mn::AddStringC(SendPacket,str,0,true);

							BugLog->print("\nString --> Server: ");
							BugLog->print(str);
						}
						break;

						case(OP_INT):
						{
							int i = rand();
							mn::AddInt(SendPacket,i);

							BugLog->print("\nInteger --> Server: ");
							BugLog->print(dbStr(i));
						}
						break;

						default:
							BugLog->print("\nInvalid operation");
							system("PAUSE");
						break;
					}

					// Send packet
					mn::SendUDP(InstanceID,SendPacket,ClientID,false,true);

					// Update timer
					Response.StartTime = (int)clock();
				}


			}
			
			break;

		case ACCEPTED:
			BugLog->print("\nACCEPTED");

			//do stuff

			mn::DeletePacket(SendPacket);
			State = TERMINATE;
			break; 

		case TERMINATE:
			BugLog->print("\nTERMINATE");
			mn::DisconnectClient(InstanceID, ClientID);
			break;

	}
}