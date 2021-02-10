#pragma once
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "winmm.lib")

#ifndef _WIN64
	#ifdef _DEBUG
		#pragma comment(lib, "MikeNetDebug.lib")
	#else
		#pragma comment(lib, "MikeNet.lib")
	#endif
#else
	#ifdef _DEBUG
		#pragma comment(lib, "MikeNetDebug64.lib")
	#else
		#pragma comment(lib, "MikeNet64.lib")
	#endif
#endif

#include <string>
#include <winsock2.h>

// State
#define STATE_SERVER		1
#define STATE_CLIENT		2
#define STATE_BROADCAST		3

// UDP mode
#define UDPMODE_PER_CLIENT						1
#define UDPMODE_PER_CLIENT_PER_OPERATION		2
#define UDPMODE_CATCH_ALL						3
#define UDPMODE_CATCH_ALL_NO					4

#define UM_PER_CLIENT						1
#define UM_PER_CLIENT_PER_OPERATION			2
#define UM_CATCH_ALL						3
#define UM_CATCH_ALL_NO						4

// TCP mode
#define TM_SIZE			1 // Default
#define TM_POST_FIX		2

#define ERRORMODE_DISABLE_MESSAGE_BOX			1 // DEPRECIATED, use EM_SAVE instead
#define ERRORMODE_ENABLE_MESSAGE_BOX			2 // DEPRECIATED, use EM_MESSAGE_BOX instead

#define EM_SAVE					1 
#define EM_MESSAGE_BOX			2 // Default on
#define EM_EXCEPTION			3

// mnClientConnected return values
#define C_NOT_CONNECTED			0
#define C_CONNECTED				2

// Below only possible in graceful mode
#define C_NO_SEND				7
#define C_NO_RECV				8
#define C_NO_SEND_RECV			9

// Firewall
#define FW_DOMAIN				0
#define FW_STANDARD				1

#define FW_IP_V4				0
#define FW_IP_V6				1
#define FW_IP_ANY				2

#define FW_UDP					17
#define FW_TCP					6

#define FW_FILE_PRINT			0
#define FW_UPNP					1
#define FW_REMOTE_DESKTOP		2
#define FW_NONE					3

// Used internally
// You should not use this class
struct WSABUF_2: public WSABUF
{
	JUSTDOINGANINSANESEARCH used;
	JUSTDOINGANINSANESEARCH offset;

	WSABUF_2();

	WSABUF_2(const WSABUF & CopyMe);
	WSABUF_2(const WSABUF_2 & CopyMe);
	WSABUF_2(char * pBuf, JUSTDOINGANINSANESEARCH pLen, JUSTDOINGANINSANESEARCH pUsed, JUSTDOINGANINSANESEARCH pOffset);
};

// Packet class, you can use this
class clPacket
{
	// Used by Add commands
	void _AddAdjustUsedSize(JUSTDOINGANINSANESEARCH AddSize);
	
	// Used by Encryption/Decryption commands
	void InvCipher(unsigned char * pInData,unsigned char * pOutData, unsigned char Nn, unsigned char * RoundKey);
	void Cipher(unsigned char * InData, unsigned char * OutData, unsigned char Nn, unsigned char * RoundKey);

	unsigned char State[4][4]; // Stores intermediate encryption result

	void _XORRoundKey(int Round, unsigned char * RoundKey);
	void _InvMixColumns();
	void _MixColumns();
	void _InvShiftRows();
	void _ShiftRows();
	void _InvSubBytes();
	void _SubBytes();
	unsigned char _gMul(unsigned char a, unsigned char b);

	// Used by operators or copy constructor
	void _Copy(const clPacket & CopyMe);
	void _Copy(const char * CopyMe, JUSTDOINGANINSANESEARCH CopyMeSize);
	void _Copy(const WSABUF_2 & CopyMe);

	void _AddPacket(clPacket & Destination, const clPacket & Source);
	void _AddPacket(clPacket & Destination, const WSABUF_2 & Source);

	void _DefaultVars(bool Full, bool InternalUse);
	

public:
	// Set to true if object is being used internally
	// In this case exceptions are not fully handled
	bool bInternalUse;

	char * sData;
	size_t clientIDFrom;
	int iOperation;
	size_t instanceID;
	JUSTDOINGANINSANESEARCH iClock;
	JUSTDOINGANINSANESEARCH iCursorPos;
	JUSTDOINGANINSANESEARCH iMemSize;
	JUSTDOINGANINSANESEARCH iUsedSize;

	// Operators
	clPacket operator+ (const clPacket &);
	void operator+= (const clPacket &);
	bool operator== (const clPacket &);

	bool operator== (const char *);

	clPacket operator+ (const WSABUF_2 &);
	void operator+= (const WSABUF_2 &);
	bool operator== (const WSABUF_2 &);

	// Empty packet
	void ClearPacket();
	
	// Constructors
	clPacket();
	clPacket(bool InternalUse);

	// Destructor
	~clPacket();

	// Copy constructors
	clPacket(const clPacket &);
	clPacket(const char *);
	clPacket(const WSABUF_2 &);

	clPacket & operator= (const clPacket &);
	clPacket & operator= (const char *);
	clPacket & operator= (const WSABUF_2 &);

	// Shifts contents down by Amount, changing used size
	// From StartPos to Amount will be erased
	int Erase(JUSTDOINGANINSANESEARCH StartPos, JUSTDOINGANINSANESEARCH Amount);

	// Inserts empty space at cusor position, changing used size and memory size as necassary
	int Insert(JUSTDOINGANINSANESEARCH Amount);

	// Add functions
	int AddUnsignedInt(JUSTDOINGANINSANESEARCH);
	int AddInt(int);
	int AddUnsignedLongInt(unsigned long int);
	int AddLongInt(long int);
	int AddUnsignedLongLongInt(unsigned long long int);
	int AddLongLongInt(long long int);
	int AddFloat(float);
	int AddUnsignedByte(unsigned char);
	int AddByte(char);
	int AddSignedByte(signed char); // Accomodate possibility that char = unsigned char (compiler option)
	int AddDouble(double);
	int AddLongDouble(long double);
	int AddShortInt(short int);
	int AddUnsignedShortInt(unsigned short int);
	int AddStringSTD(std::string, bool Prefix);
	int AddStringC(char*, JUSTDOINGANINSANESEARCH Length, bool Prefix);

	// Get functions
	JUSTDOINGANINSANESEARCH GetPacketRemainder();
	JUSTDOINGANINSANESEARCH GetUnsignedInt();
	int GetInt();
	unsigned long int GetUnsignedLongInt();
	long int GetLongInt();
	unsigned __int64 GetUnsignedLongLongInt();
	__int64 GetLongLongInt();
	float GetFloat();
	unsigned char GetUnsignedByte();
	char GetByte();
	signed char GetSignedByte(); // Accomodate possibility that char = unsigned char (compiler option)
	double GetDouble();
	long double GetLongDouble();
	short int GetShortInt();
	unsigned short int GetUnsignedShortInt();
	std::string GetStringSTD(JUSTDOINGANINSANESEARCH Length);
	char * GetStringC(JUSTDOINGANINSANESEARCH Length, bool NullTerminated);
	int mnGetStringC(char * Destination, JUSTDOINGANINSANESEARCH Length, bool NullTerminated);

	// Extra get/set functions
	JUSTDOINGANINSANESEARCH GetMemorySize();
	int SetMemorySize(JUSTDOINGANINSANESEARCH Size);
	int ChangeMemorySize(JUSTDOINGANINSANESEARCH Size);
	void SetUsedSize(JUSTDOINGANINSANESEARCH Size);
	JUSTDOINGANINSANESEARCH GetUsedSize();
	JUSTDOINGANINSANESEARCH GetCursor();
	void SetCursor(JUSTDOINGANINSANESEARCH Position);
	JUSTDOINGANINSANESEARCH GetUDPClock();
	int GetClientFrom();
	int GetOperation();
	int GetInstance();

	// Functions not affected by bInternalUse
	// These exist so that the clPacket class is compatible with the rest of MikeNet
	int SendUDP(int Instance, size_t clientID, bool Keep_packet, bool Block_until_sent);
	int SendTCP(int Instance, size_t clientID, bool Keep_packet, bool Block_until_sent);
	int SendTCPAll(int Instance, bool Keep_packet, bool Block_until_sent, size_t client_exclude);
	int SendUDPAll(int Instance, bool Keep_packet, bool Block_until_sent, size_t client_exclude);
	int RecvTCP(int Instance, size_t clientID); 
	int RecvUDP(int Instance, size_t clientID, int OperationID);
	int GetInputData(int InputInstance);
	int PlayData(int OutputInstance);
	int SetDataVolume(unsigned short BitsPerSample, int PercentageChange);
	int GetDataVolume(unsigned short BitsPerSample);

	// Encryption/Decryption functions
	int Encrypt(__int64 Key);
	int Decrypt(__int64 Key);
};

// Class allows you to more easily use critical sections
// You can use this in conjunction with mnSetFunction,
// to manage access between threads to shared resources
class clCriticalSection
{
	CRITICAL_SECTION CT;

public:
	clCriticalSection();
	~clCriticalSection();

	void Enter();
	void Leave();
};

const char * mnGetVersion();

int mnAddPacket(__int64 Destination, __int64 From);
int mnEqualPacket(__int64 Destination, __int64 From);
int mnComparePacket(__int64 Packet1, __int64 Packet2);

int mnToggleAffinity(JUSTDOINGANINSANESEARCH Processor);
int mnSetAffinity(size_t threadID);
int mnGetAffinity(JUSTDOINGANINSANESEARCH Processor);
int mnSetPriority(size_t threadID, int Priority);
int mnGetPriority(size_t threadID);

int mnSetDecryptUDP(int Instance, __int64 Key);

int mnEncrypt(__int64 Packet, __int64 Key);
int mnDecrypt(__int64 Packet, __int64 Key);

__int64 mnCreateKey256(__int64 Key1, __int64 Key2, __int64 Key3, __int64 Key4);
__int64 mnCreateKey192(__int64 Key1, __int64 Key2, __int64 Key3);
__int64 mnCreateKey128(__int64 Key1, __int64 Key2);
int mnDeleteKey(__int64 Key);

int mnDisconnectClient(int Instance, size_t clientID); 
int mnClientConnected(int Instance, size_t clientID); 

int mnGetErrorLine();
__int64 mnGetErrorCode(); 

int mnAddInt(__int64 Packet, int);
int mnAddLongLongInt(__int64 Packet, long long int);
int mnAddFloat(__int64 Packet, float); 
int mnAddUnsignedByte(__int64 Packet, unsigned char); 
int mnAddDouble(__int64 Packet, double); 
int mnAddUnsignedShortInt(__int64 Packet, unsigned short int);
int mnAddUnsignedInt(__int64 Packet, JUSTDOINGANINSANESEARCH);
int mnAddStringC(__int64 Packet, char*, JUSTDOINGANINSANESEARCH Length, bool Prefix); 

int mnGetClientFrom(__int64 Packet);
JUSTDOINGANINSANESEARCH mnGetLocalIPAmount();

int mnGetInt(__int64 Packet); 
__int64 mnGetLongLongInt(__int64 Packet);
unsigned char mnGetUnsignedByte(__int64 Packet); 
double mnGetDouble(__int64 Packet); 
unsigned short int mnGetUnsignedShortInt(__int64 Packet); 
JUSTDOINGANINSANESEARCH mnGetUnsignedInt(__int64 Packet);

JUSTDOINGANINSANESEARCH mnGetUDPClock(__int64 Packet); 
JUSTDOINGANINSANESEARCH mnGetPacketRemainder(__int64 Packet);
int mnClearPacket(__int64 Packet); 
double mnGetTCPPercent(int Instance, size_t clientID); 

int mnSendUDP(int Instance, __int64 Packet, size_t clientID, bool Keep_packet, bool Block_until_sent);
int mnSendTCP(int Instance, __int64 Packet, size_t clientID, bool Keep_packet, bool Block_until_sent);
int mnSendTCPAll(int Instance, __int64 Packet, bool Keep_packet, bool Block_until_sent, size_t client_exclude);
int mnSendUDPAll(int Instance, __int64 Packet, bool Keep_packet, bool Block_until_sent, size_t client_exclude);
int mnRecvTCP(int Instance, __int64 Packet, size_t clientID); 
int mnRecvUDP(int Instance, __int64 Packet, size_t clientID, int OperationID); 

int mnSetLocal(int Instance, const char * TCP_local_IP, unsigned short TCP_local_port, const char * UDP_local_IP, unsigned short UDP_local_port );
int mnSetBufferSizes(int Instance, JUSTDOINGANINSANESEARCH UDP_receive_buffer_size, JUSTDOINGANINSANESEARCH TCP_receive_buffer_size, char State);
void mnDisableMessageBoxes(); // DEPRECIATED
void mnEnableMessageBoxes(); // DEPRECIATED

int mnStart(int Number_of_instances, int Number_of_threads);

int mnDisableUDP(int Instance);

int mnStartServer(int Instance, int Maximum_number_of_clients, int Maximum_number_of_operations, char UDP_mode);
int mnSetServerTimeout(int Instance, JUSTDOINGANINSANESEARCH Timeout_in_seconds);
JUSTDOINGANINSANESEARCH mnGetServerTimeout(int Instance);
int mnClientJoined(int Instance); 
int mnClientLeft(int Instance); 

int mnConnect(int Instance, const char * TCP_IP_to_connect_to, unsigned short TCP_port_to_connect_to, const char * UDP_IP_to_connect_to, unsigned short UDP_port_to_connect_to, int Timeout_in_seconds, bool Block_until_connected); 
int mnPollConnect(int Instance);
int mnStopConnect(int Instance);

int mnStartBroadcast(int Instance, unsigned short Broadcast_port_to_connect_to, bool Send_enabled, bool Receive_enabled);


int mnGetPhysicalCPU();
int mnGetLogicalCPU(); 

int mnFinish(int Instance); 

int mnGetMaxClients(int Instance); 
int mnGetMaxOperations(int Instance); 
JUSTDOINGANINSANESEARCH mnGetTCPRecvSizeA(int Instance); 
JUSTDOINGANINSANESEARCH mnGetUDPRecvSize(int Instance);
int mnGetThreads();
int mnGetNumInstances();
char mnGetState(int Instance);
char mnGetUDPMode(int Instance);
int mnGetUDPEnabled(int Instance);

unsigned short mnGetLocalPortTCP(int Instance);
unsigned short mnGetLocalPortUDP(int Instance);
unsigned short mnGetConnectPortTCP(int Instance);
unsigned short mnGetConnectPortUDP(int Instance);
unsigned short mnGetClientPortTCP(int Instance, size_t clientID);
unsigned short mnGetClientPortUDP(int Instance, size_t clientID);

int mnGetClientID(int Instance);

__int64 mnCreatePacket();
int mnDeletePacket(__int64 Packet);
int mnSetMemorySize(__int64 Packet,JUSTDOINGANINSANESEARCH Size);
JUSTDOINGANINSANESEARCH mnGetMemorySize(__int64 Packet);
int mnSetUsedSize(__int64 Packet,JUSTDOINGANINSANESEARCH Size);
JUSTDOINGANINSANESEARCH mnGetUsedSize(__int64 Packet);
int mnSetCursor(__int64 Packet, JUSTDOINGANINSANESEARCH Position);
JUSTDOINGANINSANESEARCH mnGetCursor(__int64 Packet);
int mnGetOperation(__int64 Packet);
int mnGetInstance(__int64 Packet);


char * mnGetLocalIP(JUSTDOINGANINSANESEARCH Number);
char * mnGetHostName();

unsigned long int mnGetUnsignedLongInt(__int64 Packet);
unsigned __int64 mnGetUnsignedLongLongInt(__int64 Packet);
long int mnGetLongInt(__int64 Packet);
char mnGetByte(__int64 Packet); 
long double mnGetLongDouble(__int64 Packet); 
short int mnGetShortInt(__int64 Packet); 
signed char mnGetSignedByte(__int64 Packet);

int mnAddUnsignedLongInt(__int64 Packet, unsigned long int);
int mnAddUnsignedLongLongInt(__int64 Packet, unsigned long long int);
int mnAddByte(__int64 Packet, char); 
int mnAddLongDouble(__int64 Packet, long double); 
int mnAddShortInt(__int64 Packet, short int);
int mnAddLongInt(__int64 Packet, long int);
int mnAddSignedByte(__int64 Packet, signed char);


const char * mnGetErrorOperation();
const char * mnGetErrorCommand();
const char * mnGetErrorFile();
char * mnGetErrorFull();

float mnGetFloat(__int64 Packet);

char * mnGetStringC(__int64 Packet, JUSTDOINGANINSANESEARCH Length, bool NullTerminated);
int mnGetStringC(__int64 Packet, char * Destination, JUSTDOINGANINSANESEARCH Length, bool NullTerminated);

int mnAddStringSTD(__int64 Packet, std::string, bool Prefix);
std::string mnGetStringSTD(__int64 Packet, JUSTDOINGANINSANESEARCH Length);

char * mnGetLocalIPTCP(int Instance);
char * mnGetLocalIPUDP(int Instance);
char * mnGetConnectIPTCP(int Instance);
char * mnGetConnectIPUDP(int Instance);
char * mnGetClientIPTCP(int Instance, size_t clientID);
char * mnGetClientIPUDP(int Instance, size_t clientID);
char * mnDNS(char * Host_name);

int mnSetFunction(int Instance, void (*TCPRecvFunc)(size_t threadID, clPacket & Packet),void (*UDPRecvFunc)(size_t threadID, clPacket & Packet));

int mnStartUPNP();
__int64 mnFinishUPNP(bool Block);
int mnPollUPNP(__int64 Action);

__int64 mnStartNAT(bool Block);
__int64 mnFinishNAT(bool Block);
__int64 mnUpdateNAT(bool Block);
__int64 mnAddPortMap(char * Protocol, long ExternalPort, long InternalPort, char * InternalIP, bool Enabled, char * Description, bool Block);
JUSTDOINGANINSANESEARCH mnGetPortMapAmount();
__int64 mnEnablePortMap(JUSTDOINGANINSANESEARCH PortMapID, bool Block);
__int64 mnDisablePortMap(JUSTDOINGANINSANESEARCH PortMapID, bool Block);
__int64 mnSetPortMapInternalIP(JUSTDOINGANINSANESEARCH PortMapID, char * InternalIP, bool Block);
__int64 mnSetPortMapInternalPort(JUSTDOINGANINSANESEARCH PortMapID, long InternalPort, bool Block);
__int64 mnSetPortMapDescription(JUSTDOINGANINSANESEARCH PortMapID, char * Description, bool Block);
char * mnGetPortMapExternalIP(JUSTDOINGANINSANESEARCH PortMapID);
long mnGetPortMapExternalPort(JUSTDOINGANINSANESEARCH PortMapID);
long mnGetPortMapInternalPort(JUSTDOINGANINSANESEARCH PortMapID);
char * mnGetPortMapProtocol(JUSTDOINGANINSANESEARCH PortMapID);
char * mnGetPortMapInternalIP(JUSTDOINGANINSANESEARCH PortMapID);
int mnGetPortMapEnabled(JUSTDOINGANINSANESEARCH PortMapID);
char * mnGetPortMapDescription(JUSTDOINGANINSANESEARCH PortMapID);
__int64 mnDeletePortMapA(JUSTDOINGANINSANESEARCH PortMapID, bool Block);
__int64 mnDeletePortMapB(char * Protocol, long ExternalPort, bool Block);
int mnPortMapExist(char * Protocol, long ExternalPort);
JUSTDOINGANINSANESEARCH mnFindPortMap(char * Protocol, long ExternalPort);

void mnDisableDebug();
int mnGetDebugEnabled();

// New to v1.1.5
bool mnGetErrorFlag();
void mnSetErrorFlag();
void mnClearErrorFlag();
int mnToggleErrorMode(int Mode);
int mnGetErrorMode(int Mode);

struct clError
{
	bool bGenerated; // Indicates whether object is completely filled with info about an error

	char * sFullMessage;
	const char * sOperation;
	const char * sCommand;
	__int64 iErrorCode; // Large data type to ensure compatibility with all possible return types (e.g. including UINT)
	int iLine;
	const char * sFile;

	// Helper functions
	void _CheckGenerated(); // Error if bGenerated is not true
	void _Copy(const clError & CopyMe); // Fills object with contents of CopyMe
	void _DefaultVars(); // Sets variables to default

	// Constructor, copy constructors and destructor
	clError();
	clError(const clError & CopyMe);
	clError & operator= (const clError & CopyMe);
	~clError();

	// Manipulate variables
	void Clear(); // Reset variables
	void SetCore(const char * Operation, __int64 ErrorCode, int LineNo, const char * CodeFile); // Set everything except command
	void SetCommand(const char * Command); // Set command
	void SetFull(const char * Command, const char * Operation, __int64 ErrorCode, int LineNo, const char * CodeFile); // Set everything
	
	// Generate full message based on information set by SetCore, SetCommand and SetFull
	void Generate();

	// Generate message and display message box
	void GenMessageBox(const char * Command);
	void GenMessageBox(const char * Command, const char * Operation, __int64 ErrorCode, int LineNo, const char * CodeFile);

	// Generate message and decide what to do based on error mode
	void GenEvent(const char * Command);
	void GenEvent(const char * Command, const char * Operation, __int64 ErrorCode, int LineNo, const char * CodeFile);

	// Generate message and throw exception
	void GenRethrow(const char * Command);
	void GenRethrow(const char * Command, const char * Operation, __int64 ErrorCode, int LineNo, const char * CodeFile);

	// Below must be used AFTER full message is generated
	void DoMessageBox(); // Display message box
	void DoSave();	// Save message to be returned by mnGetError commands
	void DoRethrow(); // Throw clError exception
	void DoEvent(); // Decides what action to take based on error mode
};

int mnErase(__int64 Packet, JUSTDOINGANINSANESEARCH StartPos, JUSTDOINGANINSANESEARCH Amount);
int mnInsert(__int64 Packet, JUSTDOINGANINSANESEARCH Amount);
__int64 mnCreatePacketFromPacket(__int64 FromPacket);
__int64 mnCreatePacketFromString(char * String);
int mnComparePacketString(__int64 Packet, char * String);
int mnChangeMemorySize(__int64 Packet, JUSTDOINGANINSANESEARCH Size);
int mnEqualPacketString(__int64 Destination, char * From);

int mnFlushRecvTCP(int Instance, size_t client);
int mnFlushRecvUDP(int Instance, size_t client);
int mnChangeBufferSizeTCP(int Instance, size_t client, JUSTDOINGANINSANESEARCH iSize);
int mnSetAutoResizeTCP(int Instance, size_t client, bool bAutoResize);
int mnGetAutoResizeTCP(size_t instanceID, size_t clientID);
JUSTDOINGANINSANESEARCH mnGetTCPRecvSizeB(int Instance, size_t client);
JUSTDOINGANINSANESEARCH mnGetTCPBytes(int Instance, size_t client);

int mnDisableTCPHandshake(int Instance);
int mnGetTCPHandshakeEnabled(int Instance);

char mnGetTCPMode(int Instance);
int mnSetTCPMode(int Instance, char iTCPMode);

int mnShutdownClient(int Instance, size_t client);
int mnEnableGracefulDisconnect(int Instance);
int mnGetGracefulDisconnectEnabled(int Instance);

JUSTDOINGANINSANESEARCH mnGetSendTimeout(int Instance);
int mnSetSendTimeout(int Instance, JUSTDOINGANINSANESEARCH iTimeout);

JUSTDOINGANINSANESEARCH mnGetTCPStoreAmount(int Instance, size_t client);
JUSTDOINGANINSANESEARCH mnGetUDPStoreAmount(int Instance, size_t client);

int mnSetTCPPostfix(int Instance, __int64 Packet);
int mnSetTCPPostfix(int Instance, clPacket & Packet);
int mnGetTCPPostfix(int Instance, __int64 Packet);
int mnGetTCPPostfix(int Instance, clPacket & Packet);

int mnStartFirewall();
int mnFinishFirewall();
int mnUpdateFirewall();

JUSTDOINGANINSANESEARCH mnGetCurrentProfile();
int mnResetFirewall();
int mnIsPortAllowedA(char * FileName, long PortNumber, int Protocol, char * LocalAddress, int IPVersion);
int mnIsPortAllowedB(long PortNumber, int Protocol);
int mnIsTypeAllowedICMPA(unsigned char Type, char * LocalAddress, int IPVersion);
int mnIsTypeAllowedICMPB(unsigned char Type, int IPVersion);

const char * mnGetServiceName(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);
int mnGetServiceType(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);
int mnGetServiceCustomized(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);
int mnGetServiceIPVersion(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);
int mnGetServiceScope(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);
const char * mnGetServiceRemoteAddresses(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);
int mnGetServiceEnabled(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);

int mnSetServiceIPVersion(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, int IPVersion);
int mnSetServiceScope(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, int Scope);
int mnSetServiceRemoteAddresses(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, char * RemoteAddresses);
int mnSetServiceEnabled(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, bool Enabled);
int mnAddServicePort(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, char * Name, int IPVersion, int Protocol, long PortNumber, int Scope, char * RemoteAddresses, bool Enabled);
int mnDeleteServicePortA(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, long PortNumber, int Protocol);
int mnDeleteServicePortB(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, JUSTDOINGANINSANESEARCH PortID);
JUSTDOINGANINSANESEARCH mnFindServicePort(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, long PortNumber, int Protocol);
int mnServicePortExist(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID, long PortNumber, int Protocol);
JUSTDOINGANINSANESEARCH mnGetServicePortAmount(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ServiceID);

int mnGetProfileType(JUSTDOINGANINSANESEARCH ProfileID);
JUSTDOINGANINSANESEARCH mnGetProfileAmount();
int mnGetFirewallEnabled(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetExceptionsAllowed(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetNotificationsEnabled(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetUnicastToMulticastEnabled(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetRemoteAdminIPVersion(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetRemoteAdminScope(JUSTDOINGANINSANESEARCH ProfileID);
const char * mnGetRemoteAdminAddresses(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetRemoteAdminEnabled(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowOutboundDestinationUnreachable(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowRedirect(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowInboundEchoRequest(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowOutboundTimeExceeded(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowOutboundParameterProblem(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowOutboundSourceQuench(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowInboundRouterRequest(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowInboundTimestampRequest(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowInboundMaskRequest(JUSTDOINGANINSANESEARCH ProfileID);
int mnGetICMPAllowOutboundPacketTooBig(JUSTDOINGANINSANESEARCH ProfileID);

int mnSetFirewallEnabled(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetExceptionsAllowed(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetNotificationsEnabled(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetUnicastToMulticastEnabled(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetRemoteAdminIPVersion(JUSTDOINGANINSANESEARCH ProfileID, int IPVersion);
int mnSetRemoteAdminScope(JUSTDOINGANINSANESEARCH ProfileID, int Scope);
int mnSetRemoteAdminAddresses(JUSTDOINGANINSANESEARCH ProfileID, char * Addresses);
int mnSetRemoteAdminEnabled(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowOutboundDestinationUnreachable(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowRedirect(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowInboundEchoRequest(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowOutboundTimeExceeded(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowOutboundParameterProblem(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowOutboundSourceQuench(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowInboundRouterRequest(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowInboundTimestampRequest(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowInboundMaskRequest(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);
int mnSetICMPAllowOutboundPacketTooBig(JUSTDOINGANINSANESEARCH ProfileID, bool Boolean);

JUSTDOINGANINSANESEARCH mnGetApplicationAmount(JUSTDOINGANINSANESEARCH ProfileID);
int mnAddApplication(JUSTDOINGANINSANESEARCH ProfileID, char * Name, char * FileName, int IPVersion, int Scope, char * RemoteAddresses, bool Enabled);
int mnDeleteApplicationA(JUSTDOINGANINSANESEARCH ProfileID, char * FileName);
int mnDeleteApplicationB(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID);
JUSTDOINGANINSANESEARCH mnFindApplication(JUSTDOINGANINSANESEARCH ProfileID, char * FileName);
int mnApplicationExist(JUSTDOINGANINSANESEARCH ProfileID, char * FileName);

JUSTDOINGANINSANESEARCH mnGetServiceAmount(JUSTDOINGANINSANESEARCH ProfileID);

int mnAddPort(JUSTDOINGANINSANESEARCH ProfileID, char * Name, int IPVersion, int Protocol, long PortNumber, int Scope, char * RemoteAddresses, bool Enabled);
int mnDeletePortA(JUSTDOINGANINSANESEARCH ProfileID, long PortNumber, int Protocol);
int mnDeletePortB(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH PortID);
JUSTDOINGANINSANESEARCH mnFindPort(JUSTDOINGANINSANESEARCH ProfileID, long PortNumber, int Protocol);
int mnPortExist(JUSTDOINGANINSANESEARCH ProfileID, long PortNumber, int Protocol);
JUSTDOINGANINSANESEARCH mnGetPortAmount(JUSTDOINGANINSANESEARCH ProfileID);

const char * mnGetApplicationName(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID);
const char * mnGetApplicationFileName(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID);
int mnGetApplicationIPVersion(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID);
int mnGetApplicationScope(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID);
const char * mnGetApplicationRemoteAddresses(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID);
int mnGetApplicationEnabled(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID);
int mnSetApplicationName(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID, char * Name);
int mnSetApplicationFileName(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID, char * FileName);
int mnSetApplicationIPVersion(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID, int IPVersion);
int mnSetApplicationScope(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID, int Scope);
int mnSetApplicationRemoteAddresses(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID, char * RemoteAddresses);
int mnSetApplicationEnabled(JUSTDOINGANINSANESEARCH ProfileID, JUSTDOINGANINSANESEARCH ApplicationID, bool Enabled);

int mnStartSound(int NoInputInstances, int NoOutputInstances);
int mnFinishSound();
int mnGetNumInputInstances();
int mnGetNumOutputInstances();

int mnStartOutput(int InstanceID, JUSTDOINGANINSANESEARCH OutputDevice);
int mnFinishOutput(int InstanceID);
int mnPlayData(int InstanceID, __int64 Packet);
int mnSetOutputSmoothValues(int InstanceID, JUSTDOINGANINSANESEARCH MillisecondsOfStoredDataCap, JUSTDOINGANINSANESEARCH TimeSinceLastAddedCap);
int mnSetOutputFormat(int InstanceID, unsigned short Channels, JUSTDOINGANINSANESEARCH SamplesPerSec, unsigned short BitsPerSample);
int mnSetOutputFormatHigh(int InstanceID);
int mnSetOutputFormatMedium(int InstanceID);
int mnSetOutputFormatLow(int InstanceID);
int mnSetDataVolume(unsigned short BitsPerSample, __int64 Packet, int PercentageChange);
int mnGetDataVolume(unsigned short BitsPerSample, __int64 Packet);

unsigned short mnGetOutputChannels(int InstanceID);
JUSTDOINGANINSANESEARCH mnGetOutputSamplesPerSec(int InstanceID);
unsigned short mnGetOutputBitsPerSample(int InstanceID);
JUSTDOINGANINSANESEARCH mnGetOutputStoredDataCap(int InstanceID);
JUSTDOINGANINSANESEARCH mnGetOutputLastAddedCap(int InstanceID);

double mnGetHardwarePlaybackRate(int InstanceID);
double mnGetHardwarePitch(int InstanceID);
unsigned short mnGetHardwareVolumeLeft(int InstanceID);
unsigned short mnGetHardwareVolumeRight(int InstanceID);
int mnSetHardwarePlaybackRate(int InstanceID, double Rate);
int mnSetHardwarePitch(int InstanceID, double Pitch);
int mnSetHardwareVolume(int InstanceID, unsigned short Left, unsigned short Right);

int mnStartInput(int InstanceID, JUSTDOINGANINSANESEARCH InputDevice);
int mnFinishInput(int InstanceID);
int mnPauseInput(int InstanceID);
int mnUnpauseInput(int InstanceID);
int mnGetInputData(int InstanceID, __int64 Packet);
int mnGetInputUnpaused(int InstanceID);
int mnGetInputPaused(int InstanceID);
int mnSetInputSmoothValues(int InstanceID, JUSTDOINGANINSANESEARCH NoBuffers, JUSTDOINGANINSANESEARCH TimePerBuffer);
int mnSetInputFormat(int InstanceID, unsigned short Channels, JUSTDOINGANINSANESEARCH SamplesPerSec, unsigned short BitsPerSample);
int mnSetInputFormatHigh(int InstanceID);
int mnSetInputFormatMedium(int InstanceID);
int mnSetInputFormatLow(int InstanceID);

unsigned short mnGetInputChannels(int InstanceID);
JUSTDOINGANINSANESEARCH mnGetInputSamplesPerSec(int InstanceID);
unsigned short mnGetInputBitsPerSample(int InstanceID);
JUSTDOINGANINSANESEARCH mnGetInputNoBuffers(int InstanceID);
JUSTDOINGANINSANESEARCH mnGetInputTimePerBuffer(int InstanceID);


JUSTDOINGANINSANESEARCH mnGetNumInputDevices();
JUSTDOINGANINSANESEARCH mnGetNumOutputDevices();
unsigned short mnGetDeviceManuID(JUSTDOINGANINSANESEARCH DeviceID, bool Output);
unsigned short mnGetDeviceProductID(JUSTDOINGANINSANESEARCH DeviceID, bool Output);
unsigned char mnGetDeviceDriverMinorVersion(JUSTDOINGANINSANESEARCH DeviceID, bool Output);
unsigned char mnGetDeviceDriverMajorVersion(JUSTDOINGANINSANESEARCH DeviceID, bool Output);
const char * mnGetDeviceName(JUSTDOINGANINSANESEARCH DeviceID, bool Output);
JUSTDOINGANINSANESEARCH mnGetDeviceFormatSupport(JUSTDOINGANINSANESEARCH DeviceID, bool Output);
int mnReadDeviceFormatSupport(JUSTDOINGANINSANESEARCH SupportInfo, unsigned char KHZ, unsigned char Channels, unsigned char Bits);
unsigned short mnGetDeviceMaxChannels(JUSTDOINGANINSANESEARCH DeviceID, bool Output);
int mnGetDeviceHardwareSupport(JUSTDOINGANINSANESEARCH OutputDeviceID, JUSTDOINGANINSANESEARCH Feature);

int mnGetNagleEnabled(int Instance);
int mnDisableNagle(int Instance);

int mnFinishND(size_t instanceID);
int mnSendToUDP(size_t instanceID, __int64 Packet, const char * IP, unsigned short Port, bool bKeep, bool bBlock);
