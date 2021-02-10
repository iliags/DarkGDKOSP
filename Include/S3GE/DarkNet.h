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

#pragma once
#ifndef DARKNET_H
#define DARKNET_H

#include <new>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <time.h>

#include "..\DarkGDK\DarkGDK.h"
#include "S3GE_Common.h"			//by DOSP Common Library
#include "DarkLUA.h"				//by Techlord

using namespace std;

//packet intention
#define	OP_NEWPLAYER	0
#define OP_LEFTPLAYER	1

//declarations
#define PACKET	long long int

#define DARKNET_NETWORK_PROTOCOL_TCP	1
#define DARKNET_NETWORK_PROTOCOL_UDP	2

#define DARKNET_NETWORK_SERVICE_HTTP	1
#define DARKNET_NETWORK_SERVICE_FTP	2
#define DARKNET_NETWORK_SERVICE_DATABASE	3
#define DARKNET_NETWORK_SERVICE_GAME	4

#define DARKNET_DATABASE_ERROR	-1
#define DARKNET_DATABASE_MAX	2

#define DARKNET_INSTANCE_MAX	32
#define DARKNET_CLIENT_MAX	2000

#define DARKNET_HTTP_MAX	32

#define DARKNET_HTTP_METHOD_GET	1
#define DARKNET_HTTP_METHOD_POST	2
#define DARKNET_HTTP_METHOD_HEAD	3
#define DARKNET_HTTP_METHOD_PUT	4
#define DARKNET_HTTP_METHOD_DELETE	5
#define DARKNET_HTTP_METHOD_TRACE	6
#define DARKNET_HTTP_METHOD_OPTIONS	7
#define DARKNET_HTTP_METHOD_CONNECT	8

#define DARKNET_HTTP_ERROR	-1
#define DARKNET_HTTP_FILESIZE_MAX	8388608 //8388608 = 65536 * 128 8M based hpquest max file upload size

#define DARKNET_HTTP_TYPE_FILE	1
#define DARKNET_HTTP_TYPE_MEDIA	2
#define DARKNET_HTTP_TYPE_DATABASE	3

#define DARKNET_HTTP_TRANSFER_MODE_BINARY	0
#define DARKNET_HTTP_TRANSFER_MODE_ASCII	1

#define DARKNET_MESSAGE_TYPE_NETWORK	1
#define DARKNET_MESSAGE_TYPE_COMMAND	2
#define DARKNET_MESSAGE_TYPE_CHAT	3
#define DARKNET_MESSAGE_TYPE_TWITCH	4
#define DARKNET_MESSAGE_TYPE_PING	5

#define DARKNET_I2P_ROLE_SERVER	0
#define DARKNET_I2P_ROLE_CLIENT	1
#define DARKNET_I2P_ROLE_HOST	2

namespace DarkNet{

		//Programmable Application Layer Model for Transactions: Request-Response 
		//PALM TRRee
		class PALM{
			public:

				class ESM{
					/**
					* @brief	Event State Machine
					*
					*/
					public:

						static map<string, int> StateNameMap;
						static map<string, int>::iterator StateNameMapIterator;
						static int StateIndex;
						static void StateNameAdd(string statename);

						float Counter;
						float Count;
						float Delta;
						int PreviousState;
						int NextState;
						int TransitState;
						int State;

						void Clear(void);
				};

				class Behavior{
					/**
					* @brief	Interactive Operation Event-drive
					*	controls Network Event Behavior via script
					*/

					public:

						class EventScript{
							public:
								DarkLUA::Task *Task;
								void Inherit(EventScript *parent);

								EventScript(void);
								EventScript *Copy(void);

						};

						static map<string,Behavior*> NameMap;
						static map<string,Behavior*>::iterator NameMapIterator;
						static Behavior *Create(string name, string description);
						static void Destroy(Behavior *Behavior);
						static void Destroy(void);
						static Behavior *Get(string name);

						map<int, EventScript*> EventAction;
						string Name;
						string Description;
						Behavior(void);
						Behavior(string name, string description);
						~Behavior(void);
						Behavior *Copy(string name, string description);

				};

				struct HeaderData{
					string Line;
					int LineCount;
					DarkLUA::Task *Task;
				};

				class MessageData{
					public:
						HeaderData Header;
						int Type;
						string Hostname;
						string IP;
						int Port;
						int Method;
						string Page;
						string PageVariables;
						bool Mode; //0=binary, 1=ascii
						int Code;
						long long int Packet;
						vector<long long int> StoredPackets;
						int BytesLoaded;     
						int ContentLength;
						int PacketMemorySize;//1024
						int Status;
						int StartTime;
						int Stoptime;
						string WritePath;
						ofstream OutputFile;
						DarkLUA::Task *Task;
						string Error;
						int State;
				} Request, Response;
			
				class TransactionData{
					public:
						MessageData Request;
						MessageData Response;
				};

				static ResourceManager *InstanceResource;
				static ResourceManager *ClientResource;

				vector<TransactionData*> Transaction;
				map<string,int> MethodNameMap;
				map<int,string> ResponseCodeNameMap;

				static void MethodNameAdd(string methodname, int constant);

				__int64 Profile;
				size_t InstanceID;
				size_t ClientID;
				enum TransactionStates{IDLE, REQUESTSTART, REQUESTSTARTING, REQUEST, REQUESTING, REQUESTEND, RESPONSESTART, RESPONSE, RESPONDING, RESPONSEEND, RECOVER, PENDING, SUSPEND, SUSPENDED, RELEASE, TERMINATE, EXIT} State;

		};

		class HTTP: public PALM{
			public:

				static map<string,HTTP*> NameMap;
				static map<string,HTTP*>::iterator NameMapIterator;
				static list<HTTP*> ActiveList;
				static list<HTTP*>::iterator ActiveListIterator;
				static queue<HTTP*> InactiveQueue;

				static map<string,int> TransferModeExtMap;
				static int URLEncodeCharacter[];

				HTTP(void);
				~HTTP(void);
				static HTTP *Create(string name, string hostname, int port);
				static void Destroy(HTTP *instance);
				static void Update(void);
				static HTTP *FileGet(string name, int method, string hostname, int port, string page, string writepath, int mode=DARKNET_HTTP_TRANSFER_MODE_ASCII);

				void Process(void);
				int ProcessNow(void);
				void Get(int method, string page, string writepath);
				void Trash(void);

				string URLVariableEncodeParse(string urldata);
				string URLVariableEncodeAppend(string urldata);
				string URLEncode(string urldata);

				static void TransferModeExtSet(string ext, int mode = DARKNET_HTTP_TRANSFER_MODE_ASCII);
				static int TransferModeExtGet(string file);

		};

		class I2P: public PALM{
			public:

				static map<string,I2P*> NameMap;
				static map<string,I2P*>::iterator NameMapIterator;
				static list<I2P*> ActiveList;
				static list<I2P*>::iterator ActiveListIterator;
				static queue<I2P*> InactiveQueue;

				string Name;
				string Description;
				string Hostname;
				int ID;
				string TCPIP;
				string UDPIP;
				int TCPPort;
				int UDPPort;
				int UDPMode;
				int UDPOperationCount;
				int Status;
				long long int RecvPacket; //= mnCreatePacket();
				long long int SendPacket; //= mnCreatePacket();
				int MaxClients;
				list<size_t> ClientList;
				list<size_t>::iterator ClientListIterator;
				enum ProcessStates{IDLE,JOINING,JOIN,JOINED,ACCEPT,ACCEPTING,ACCEPTED,SEND,SENDING,SENT,TERMINATE} State;
				enum OperationTypes{OP_FLOAT,OP_STRING,OP_INT} OperationType;
				
				I2P(void);
				~I2P(void);

				static I2P *Create(int role, string name, char* hostname, unsigned short port, int udpmode, int maxclients=0);
				static void Update(void);

				//Common Pure Virtuals
				virtual void Destroy(I2P* instance)=0;
				virtual void Process(void)=0;
				virtual void Trash(void)=0;

				//Server Pure Virtuals
				virtual I2P *Create(string name, char* hostname, unsigned short port, int udpmode, int maxclients)=0;

				//Client Pure Virtuals
				virtual I2P *Create(string name, char* hostname, unsigned short port, int udpmode)=0;

		};

		class Server: public I2P{
			private:
			public:
				
				Server(void);
				~Server(void);
			
				//Virtuals
				I2P *Create(string name, char* hostname, unsigned short port, int udpmode, int maxclients);
				void Process(void);				
				void Destroy(I2P* instance){};
				void Trash(void){}

				//Client Virtual Stub
				I2P *Create(string name, char* hostname, unsigned short port, int udpmode){return NULL;}

		};

		class Client: public I2P{
			private:
			public:

				Client(void);
				~Client(void);

				//Virtuals
				I2P *Create(string name, char* hostname, unsigned short port, int udpmode);
				void Process(void);			
				void Destroy(I2P* instance){}
				void Trash(void){}

				//Server Virtual Stubs
				I2P *Create(string name, char* hostname, unsigned short port, int udpmode, int maxclients){return NULL;}

		};

		class System{
			public:
				System(void);
				virtual ~System(void);
				static void Start(string gameID, int instances, int threads);
				static void Update(void);
				static void Stop(void);

		};

}

#endif

/*
I have emailed TechLord the latest release.

If you want to create your own TCP modes you have to use the internal classes. At the highest level you have NetInstanceServer, NetInstanceClient and NetInstanceBroadcast.

To create a TCP mode extend NetModeTcp and pass an instantiation of your class to a NetSocketTCP object which you then pass to a NetInstanceServer or NetInstanceClient object.

If you are interested in performance its worth looking at the following classes:
Packet: you can use this as a high performance string class with in built multi-threaded encryption and decryption.
StoreQueue.
StoreVector.

If you are interested in multi-threading there are some very good classes which make high performance multi-threading very easy to implement:
ThreadSingle.
ThreadSingleGroup.
ThreadSingleMessage.
ThreadSingleMessageKeepLast.
ThreadSingleMessageKeepLastUser.

*/