#pragma once

/**
 * @brief Commands for procedural programming, that wrap around internal classes.
 *
 * These commands exist for those who prefer procedural programming over object orientated.
 * They wrap around the classes of the networking module and deal with errors differently 
 * dependent on the error mode we are in.
 */
namespace mn
{
#ifdef C_LINKAGE
	extern "C"
	{
#endif
	CPP_DLL const char * GetVersion();


	DBP_CPP_DLL int Start(size_t numInstances, size_t numThreads);
	DBP_CPP_DLL int Finish(size_t instanceID);

	DBP_CPP_DLL const char * DNS_B(const char * hostName);
	DBP_CPP_DLL size_t GetLocalInterfaceAmount();

	CPP_DLL const char * GetLocalInterfaceStr(size_t num);
	CPP_DLL const char * GetHostName();

	DBP_CPP_DLL NetUtility::ConnectionStatus Connect(size_t instanceID, const char * connectIP_TCP, unsigned short connectPort_TCP, const char * connectIP_UDP, unsigned short connectPort_UDP, size_t timeoutMilliseconds, bool block, __int64 profile);
	DBP_CPP_DLL int StartServer(size_t instanceID, size_t maxClients, __int64 profile);

	DBP_CPP_DLL int StartBroadcast(size_t instanceID, const char * connectAddressIP, unsigned short connectAddressPort, bool sendEnabled, bool recvEnabled, __int64 profile);

	DBP_CPP_DLL int DisconnectClient(size_t instanceID, size_t clientID);
	DBP_CPP_DLL int SetServerTimeout(size_t instanceID, size_t timeoutMilliseconds);
	DBP_CPP_DLL size_t GetServerTimeout(size_t instanceID);
	DBP_CPP_DLL size_t ClientJoined(size_t instanceID);
	DBP_CPP_DLL size_t ClientLeft(size_t instanceID);
	CPP_DLL const char * GetClientIPTCP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL unsigned short GetClientPortTCP(size_t instanceID, size_t clientID);

	CPP_DLL const char * GetClientIPUDP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL unsigned short GetClientPortUDP(size_t instanceID, size_t clientID);

	DBP_CPP_DLL size_t GetClientFrom(__int64 Packet);
	DBP_CPP_DLL int ShutdownClient(size_t instanceID, size_t clientID);
	DBP_CPP_DLL NetUtility::ConnectionStatus ClientConnected(size_t instanceID, size_t clientID);
	DBP_CPP_DLL int FlushRecvTCP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL int FlushRecvUDP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL int ChangeBufferSizeTCP(size_t instanceID, size_t clientID, size_t newSize);
	DBP_CPP_DLL int SetAutoResizeTCP(size_t instanceID, size_t clientID, bool autoResize);

	CPP_DLL const char * GetConnectIPTCP(size_t instanceID);
	DBP_CPP_DLL unsigned short GetConnectPortTCP(size_t instanceID);

	CPP_DLL const char * GetConnectIPUDP(size_t instanceID);
	DBP_CPP_DLL unsigned short GetConnectPortUDP(size_t instanceID);
	DBP_CPP_DLL NetUtility::ConnectionStatus PollConnect(size_t instanceID);
	DBP_CPP_DLL int StopConnect(size_t instanceID);
	DBP_CPP_DLL bool GetConnecting(size_t instanceID);
	DBP_CPP_DLL size_t GetClientID(size_t instanceID);
	DBP_CPP_DLL size_t GetMaxClients(size_t instanceID);
	DBP_CPP_DLL size_t GetMaxOperations(size_t instanceID);
	DBP_CPP_DLL size_t GetRecvSizeUDP(size_t instanceID);
	DBP_CPP_DLL size_t GetThreads();
	DBP_CPP_DLL size_t GetNumInstances();
	DBP_CPP_DLL NetInstance::Type GetState(size_t instanceID);
	DBP_CPP_DLL NetMode::ProtocolMode GetModeUDP(size_t instanceID);
	DBP_CPP_DLL int GetEnabledUDP(size_t instanceID);
	DBP_CPP_DLL double GetPercentTCP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL size_t GetRecvSizeTCP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL size_t GetBytesTCP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL int GetHandshakeEnabledTCP(size_t instanceID);
	DBP_CPP_DLL NetMode::ProtocolMode GetModeTCP(size_t instanceID);
	DBP_CPP_DLL int GetGracefulDisconnectEnabledTCP(size_t instanceID);
	DBP_CPP_DLL unsigned int GetSendTimeout(size_t instanceID);
	DBP_CPP_DLL size_t GetStoreAmountTCP(size_t instanceID, size_t clientID);
	DBP_CPP_DLL size_t GetStoreAmountUDP(size_t instanceID, size_t clientID);

	DBP_CPP_DLL int GetPostfixTCP(size_t instanceID, __int64 packet);
	DBP_CPP_DLL int GetNagleEnabledTCP(size_t instanceID);
	DBP_CPP_DLL int GetAutoResizeTCP(size_t instanceID, size_t clientID);

	CPP_DLL const char * GetLocalIPTCP(size_t instanceID);
	DBP_CPP_DLL unsigned short GetLocalPortTCP(size_t instanceID);

	CPP_DLL const char * GetLocalIPUDP(size_t instanceID);
	DBP_CPP_DLL unsigned short GetLocalPortUDP(size_t instanceID);

	DBP_CPP_DLL size_t RecvTCP(size_t instanceID, __int64 destinationPacket, size_t clientID);
	DBP_CPP_DLL size_t RecvUDP(size_t instanceID, __int64 destinationPacket, size_t clientID, size_t operationID);
	DBP_CPP_DLL int SendUDP(size_t instanceID, __int64 packet, size_t clientID, bool keep, bool block);
	DBP_CPP_DLL int SendToUDP(size_t instanceID, __int64 packet, const char * addrIP, unsigned short addrPort, bool keep, bool block);
	DBP_CPP_DLL int SendTCP(size_t instanceID, __int64 packet, size_t clientID, bool keep, bool block);
	DBP_CPP_DLL int SendAllTCP(size_t instanceID, __int64 packet, bool keep, bool block, size_t clientExcludeID);
	DBP_CPP_DLL int SendAllUDP(size_t instanceID, __int64 packet, bool keep, bool block, size_t clientExcludeID);

	DBP_CPP_DLL int AddUnsignedInt(__int64 packet, unsigned int Add);
	DBP_CPP_DLL int AddInt(__int64 packet, int Add);
	CPP_DLL int AddLongInt(__int64 packet, long int Add);
	DBP_CPP_DLL int AddLongLongInt(__int64 packet, long long int Add);
	DBP_CPP_DLL int AddFloat(__int64 packet, float Add);
	DBP_CPP_DLL int AddUnsignedByte(__int64 packet, unsigned char Add);
	CPP_DLL int AddByte(__int64 packet, char Add);
	CPP_DLL int AddSignedByte(__int64 packet, signed char Add);
	DBP_CPP_DLL int AddDouble(__int64 packet, double Add);
	CPP_DLL int AddLongDouble(__int64 packet, long double Add);
	CPP_DLL int AddShortInt(__int64 packet, short int Add);
	DBP_CPP_DLL int AddUnsignedShortInt(__int64 packet, unsigned short int Add);
	CPP_DLL int AddUnsignedLongInt(__int64 packet, unsigned long int Add);
	CPP_DLL int AddUnsignedLongLongInt(__int64 packet, unsigned long long int Add);
	DBP_CPP_DLL int AddSizeT(__int64 packet, size_t add);
	DBP_CPP_DLL int AddStringC(__int64 packet, const char * source, size_t length, bool prefix);
	DBP_CPP_DLL size_t GetPacketRemainder(__int64 packet);
	DBP_CPP_DLL unsigned int GetUnsignedInt(__int64 packet);
	DBP_CPP_DLL int GetInt(__int64 packet);
	CPP_DLL long int GetLongInt(__int64 packet);
	DBP_CPP_DLL long long int GetLongLongInt(__int64 packet);
	CPP_DLL float GetFloat(__int64 packet);
	DBP_CPP_DLL unsigned char GetUnsignedByte(__int64 packet);
	CPP_DLL char GetByte(__int64 packet);
	CPP_DLL signed char GetSignedByte(__int64 packet);
	DBP_CPP_DLL double GetDouble(__int64 packet);
	CPP_DLL long double GetLongDouble(__int64 packet);
	CPP_DLL short int GetShortInt(__int64 packet);
	DBP_CPP_DLL unsigned short int GetUnsignedShortInt(__int64 packet);
	CPP_DLL char * GetStringC(__int64 packet, size_t length, bool nullTerminated);
	CPP_DLL int GetStringC_B(__int64 packet, char * dest, size_t length, bool nullTerminated);
	CPP_DLL unsigned long int GetUnsignedLongInt(__int64 packet);
	CPP_DLL unsigned long long int GetUnsignedLongLongInt(__int64 packet);
	DBP_CPP_DLL size_t GetSizeT(__int64 packet);
	DBP_CPP_DLL size_t GetAge(__int64 packet);
	DBP_CPP_DLL size_t GetOperation(__int64 packet);
	CPP_DLL const char * GetErrorOperation();
	DBP_CPP_DLL size_t GetInstance(__int64 packet);
	DBP_CPP_DLL int ClearPacket(__int64 packet);
	DBP_CPP_DLL int AddPacket(__int64 dest, __int64 source);
	DBP_CPP_DLL int AssignPacket(__int64 dest, __int64 source);
	DBP_CPP_DLL int ComparePacket(__int64 packet1, __int64 packet2);
	DBP_CPP_DLL __int64 CreatePacket();
	DBP_CPP_DLL int DeletePacket(__int64 packet);
	DBP_CPP_DLL int SetMemorySize(__int64 packet, size_t size);
	DBP_CPP_DLL size_t GetMemorySize(__int64 packet);
	DBP_CPP_DLL int SetUsedSize(__int64 packet, size_t size);
	DBP_CPP_DLL size_t GetUsedSize(__int64 packet);
	DBP_CPP_DLL int SetCursor(__int64 packet, size_t cursor);
	DBP_CPP_DLL size_t GetCursor(__int64 packet);
	DBP_CPP_DLL int Erase(__int64 packet, size_t startPos, size_t amount);
	DBP_CPP_DLL int Insert(__int64 packet, size_t amount);
	DBP_CPP_DLL __int64 CreatePacketFromPacket(__int64 fromPacket);
	DBP_CPP_DLL __int64 CreatePacketFromString(const char * str);
	DBP_CPP_DLL int ComparePacketString(__int64 packet, const char * str);
	DBP_CPP_DLL int ChangeMemorySize(__int64 packet, size_t size);
	DBP_CPP_DLL int AssignPacketString(__int64 destination, const char * from);
	DBP_CPP_DLL size_t GetStringSize(__int64 packet);

	DBP_CPP_DLL int Encrypt(__int64 packet, __int64 key, bool block);
	DBP_CPP_DLL int Decrypt(__int64 packet, __int64 key, bool block);
	DBP_CPP_DLL int GetLastEncryptionOperationFinished(__int64 packet);

	DBP_CPP_DLL bool GetErrorFlag();
	DBP_CPP_DLL void SetErrorFlag();
	DBP_CPP_DLL void ClearErrorFlag();
	CPP_DLL const char * GetErrorCommand();
	CPP_DLL const char * GetErrorFile();
	CPP_DLL const char * GetErrorFull();
	DBP_CPP_DLL __int64 GetErrorCode();
	DBP_CPP_DLL unsigned __int64 GetErrorLine();


	DBP_CPP_DLL int SetProfileBufferSizes(__int64 profile, size_t recvSizeTCP, size_t recvSizeUDP);
	DBP_CPP_DLL int SetProfileEnabledUDP(__int64 profile, bool option);
	DBP_CPP_DLL int SetProfileAutoResizeTCP(__int64 profile, bool autoResize);
	DBP_CPP_DLL int SetProfileHandshakeEnabled(__int64 profile, bool option);
	DBP_CPP_DLL int SetProfileModeTCP(__int64 profile, char modeTCP);

	DBP_CPP_DLL int SetProfileGracefulDisconnectEnabled(__int64 profile, bool option);
	DBP_CPP_DLL int SetProfileSendTimeout(__int64 profile, unsigned int  timeoutMilliseconds);
	DBP_CPP_DLL int SetProfilePostfixTCP(__int64 profile, __int64 packet);
	DBP_CPP_DLL int SetProfileNagleEnabledTCP(__int64 profile, bool option);
	DBP_CPP_DLL int SetProfileLocalTCP(__int64 profile, const char * IP, unsigned short port);
	DBP_CPP_DLL int SetProfileLocalUDP(__int64 profile, const char * IP, unsigned short port);
	DBP_CPP_DLL int SetProfileLocal(__int64 profile, const char * IP_TCP, unsigned short portTCP, const char * IP_UDP, unsigned short portUDP);
	DBP_CPP_DLL int SetProfileDecryptKeyUDP(__int64 profile, __int64 key);
	DBP_CPP_DLL int SetProfileServerTimeout(__int64 profile, size_t timeoutMilliseconds);
	DBP_CPP_DLL int SetProfileModeUDP(__int64 profile, char modeUDP);
	DBP_CPP_DLL int SetProfileReusableUDP(__int64 profile, bool option);
	DBP_CPP_DLL int SetProfileNumOperationsUDP(__int64 profile, size_t numOperations);

	DBP_CPP_DLL size_t GetProfileBufferSizeTCP(__int64 profile);
	DBP_CPP_DLL size_t GetProfileBufferSizeUDP(__int64 profile);
	CPP_DLL const char * GetProfileLocalIPTCP(__int64 profile);
	DBP_CPP_DLL unsigned short GetProfileLocalPortTCP(__int64 profile);
	CPP_DLL const char * GetProfileLocalIPUDP(__int64 profile);
	DBP_CPP_DLL unsigned short GetProfileLocalPortUDP(__int64 profile);	
	DBP_CPP_DLL int GetProfileEnabledUDP(__int64 profile);
	DBP_CPP_DLL int GetProfileDecryptKeyLoadedUDP(__int64 profile);
	DBP_CPP_DLL __int64 GetProfileDecryptKeyUDP(__int64 profile);
	DBP_CPP_DLL	int GetProfileHandshakeEnabled(__int64 profile);
	DBP_CPP_DLL	NetMode::ProtocolMode GetProfileModeTCP(__int64 profile);
	DBP_CPP_DLL NetMode::ProtocolMode GetProfileModeUDP( __int64 profile );
	DBP_CPP_DLL	int GetProfileAutoResizeTCP(__int64 profile);
	DBP_CPP_DLL size_t GetProfileSendTimeout(__int64 profile);
	DBP_CPP_DLL	int GetProfileGracefulDisconnectEnabled(__int64 profile);
	DBP_CPP_DLL	int GetProfileNagleEnabledTCP(__int64 profile);
	DBP_CPP_DLL	int GetProfilePostfixTCP(__int64 profile, __int64 destination);
	DBP_CPP_DLL int GetProfileReusableUDP(__int64 profile);
	DBP_CPP_DLL size_t GetProfileServerTimeout(__int64 profile);
	DBP_CPP_DLL size_t GetProfileNumOperationsUDP(__int64 profile);


	DBP_CPP_DLL __int64 CreateInstanceProfile();
	DBP_CPP_DLL __int64 CreateInstanceProfileFrom(__int64 profile);
	DBP_CPP_DLL int DeleteInstanceProfile(__int64 profile);
	DBP_CPP_DLL __int64 AssignInstanceProfile(__int64 dest, __int64 source);
	DBP_CPP_DLL int CompareInstanceProfile(__int64 profile1, __int64 profile2);

	DBP_CPP_DLL int ToggleErrorMode(int errorMode);
	DBP_CPP_DLL int SetErrorMode(int errorMode, bool enabled);
	DBP_CPP_DLL int GetErrorMode(int errorMode);

	DBP_CPP_DLL __int64 CreateKey256(__int64 key1, __int64 key2, __int64 key3, __int64 key4);
	DBP_CPP_DLL __int64 CreateKey192(__int64 key1, __int64 key2, __int64 key3);
	DBP_CPP_DLL __int64 CreateKey128(__int64 key1, __int64 key2);
	DBP_CPP_DLL int DeleteKey(__int64 Key);
	
	DBP_CPP_DLL size_t GetLogicalCPU();

	CPP_DLL void FreeString(char * freeMe);

	CPP_DLL void SetAffixEnableTCP(size_t instanceID, size_t clientID, bool enabledflag);
	CPP_DLL bool GetAffixEnableTCP(size_t instanceID, size_t clientID);

	CPP_DLL void SetBinaryModeTCP(size_t instanceID, size_t clientID, bool enabledflag);
	CPP_DLL bool GetBinaryModeTCP(size_t instanceID, size_t clientID);

	CPP_DLL void SetHeaderFoundTCP(size_t instanceID, size_t clientID, bool foundflag);
	CPP_DLL bool GetHeaderFoundTCP(size_t instanceID, size_t clientID); 


#ifdef DBP
	DBP_CPP_DLL DWORD DBP_GetErrorOperation(DWORD pOldString);
	DBP_CPP_DLL DWORD DBP_GetErrorCommand(DWORD pOldString);
	DBP_CPP_DLL DWORD DBP_GetErrorFile(DWORD pOldString);
	DBP_CPP_DLL DWORD DBP_GetErrorFull(DWORD pOldString);
	DBP_CPP_DLL DWORD DBP_GetVersion(DWORD pOldString);

	DBP_CPP_DLL DWORD DBP_GetUnsignedByte(__int64 Packet);
	DBP_CPP_DLL DWORD DBP_GetString(DWORD pOldString, __int64 Packet, size_t Length, bool NullTerminated);
	DBP_CPP_DLL DWORD DBP_GetLocalIPTCP(DWORD pOldString, size_t Instance);
	DBP_CPP_DLL DWORD DBP_GetLocalIPUDP(DWORD pOldString, size_t Instance);
	DBP_CPP_DLL DWORD DBP_GetConnectIPTCP(DWORD pOldString, size_t Instance);
	DBP_CPP_DLL DWORD DBP_GetConnectIPUDP(DWORD pOldString, size_t Instance);
	DBP_CPP_DLL DWORD DBP_GetClientIPTCP(DWORD pOldString, size_t Instance, size_t clientID);
	DBP_CPP_DLL DWORD DBP_GetClientIPUDP(DWORD pOldString, size_t Instance, size_t clientID);
	DBP_CPP_DLL DWORD DBP_GetFloat(__int64 Packet);
	DBP_CPP_DLL DWORD DBP_DNS(DWORD pOldString, char * HostName);
	DBP_CPP_DLL DWORD DBP_GetLocalInterface(DWORD pOldString, size_t Number);
	DBP_CPP_DLL DWORD DBP_GetHostName(DWORD pOldString);
	DBP_CPP_DLL DWORD DBP_GetProfileLocalIPTCP(DWORD pOldString, __int64 profile);
	DBP_CPP_DLL DWORD DBP_GetProfileLocalIPUDP(DWORD pOldString, __int64 profile);

	DBP_CPP_DLL int DBP_GetMemblock(__int64 Packet, size_t DestinationPtr, size_t Length, bool NullTerminated);
	DBP_CPP_DLL int DBP_AddMemblock(__int64 Packet, size_t DestinationPtr, size_t Length, bool Prefix); 
#endif

#ifdef C_LINKAGE
	}
#endif

	const NetAddress & DNS_A(const char * hostName);
	const NetAddress & GetLocalInterface(size_t num);

	NetUtility::ConnectionStatus Connect(size_t instanceID, const NetAddress * connectAddrTCP, const NetAddress * connectAddrUDP, size_t timeoutMilliseconds, bool block, const NetInstanceProfile & profile);

	int StartServer(size_t instanceID, size_t maxClients, const NetInstanceProfile & profile);

	int StartBroadcast(size_t instanceID, const NetAddress & connectAddress, bool sendEnabled, bool recvEnabled, const NetInstanceProfile & profile);
	NetAddress GetClientAddressTCP(size_t instanceID, size_t clientID);
	NetAddress GetClientAddressUDP(size_t instanceID, size_t clientID);
	NetAddress GetConnectAddressTCP(size_t instanceID);
	NetAddress GetConnectAddressUDP(size_t instanceID);
	int GetPostfixTCP(size_t instanceID, Packet & packet);

	NetAddress GetLocalAddressTCP(size_t instanceID);
	NetAddress GetLocalAddressUDP(size_t instanceID);
	size_t RecvTCP(size_t instanceID, Packet & destinationPacket, size_t clientID);
	size_t RecvUDP(size_t instanceID, Packet & destinationPacket, size_t clientID, size_t operationID);
	NetUtility::SendStatus SendUDP(size_t instanceID, Packet & packet, size_t clientID, bool keep, bool block);
	NetUtility::SendStatus SendToUDP(size_t instanceID, Packet & packet, const NetAddress & address, bool keep, bool block);
	NetUtility::SendStatus SendTCP(size_t instanceID, Packet & packet, size_t clientID, bool keep, bool block);
	int SendAllTCP(size_t instanceID, Packet & packet, bool keep, bool block, size_t clientExcludeID);
	int SendAllUDP(size_t instanceID, Packet & packet, bool keep, bool block, size_t clientExcludeID);

	int SetProfileModeUDP(NetInstanceProfile & profile, NetMode::ProtocolMode modeUDP);
	NetMode::ProtocolMode GetProfileModeUDP( const NetInstanceProfile & profile );


	int SetProfileBufferSizes(NetInstanceProfile & profile, size_t recvSizeTCP, size_t recvSizeUDP);
	int SetProfileEnabledUDP(NetInstanceProfile & profile, bool option);
	int SetProfileAutoResizeTCP(NetInstanceProfile & profile, bool autoResize);
	int SetProfileHandshakeEnabled(NetInstanceProfile & profile, bool option);
	int SetProfileModeTCP(NetInstanceProfile & profile, NetMode::ProtocolMode modeTCP);
	int SetProfileGracefulDisconnectEnabled(NetInstanceProfile & profile, bool option);
	int SetProfileSendTimeout(NetInstanceProfile & profile, unsigned int timeoutMilliseconds);
	int SetProfilePostfixTCP(NetInstanceProfile & profile, const Packet & packet);
	int SetProfileNagleEnabledTCP(NetInstanceProfile & profile, bool option);
	int SetProfileLocalTCP(NetInstanceProfile & profile, const NetAddress & addressTCP);
	int SetProfileLocalUDP(NetInstanceProfile & profile, const NetAddress & addressUDP);
	int SetProfileLocal(NetInstanceProfile & profile, const NetAddress & addressTCP, const NetAddress & addressUDP);
	int SetProfileServerTimeout(NetInstanceProfile & profile, size_t timeoutMilliseconds);
	size_t GetProfileServerTimeout(const NetInstanceProfile & profile);

	NetSocket::RecvFunc GetProfileFunctionTCP(const NetInstanceProfile & profile);
	NetSocket::RecvFunc GetProfileFunctionUDP(const NetInstanceProfile & profile);
	size_t GetProfileBufferSizeTCP(const NetInstanceProfile & profile);
	size_t GetProfileBufferSizeUDP(const NetInstanceProfile & profile);
	int GetProfileEnabledUDP(const NetInstanceProfile & profile);
	int GetProfileAutoResizeTCP(const NetInstanceProfile & profile); 
	int GetProfileHandshakeEnabled(const NetInstanceProfile & profile); 
	NetMode::ProtocolMode GetProfileModeTCP(const NetInstanceProfile & profile); 
	int GetProfileGracefulDisconnectEnabled(const NetInstanceProfile & profile); 
	size_t GetProfileSendTimeout(const NetInstanceProfile & profile);
	Packet GetProfilePostfixTCP(const NetInstanceProfile & profile); 
	int GetProfileNagleEnabledTCP(const NetInstanceProfile & profile); 
	NetAddress GetProfileLocalAddressTCP(const NetInstanceProfile & profile);
	NetAddress GetProfileLocalAddressUDP(const NetInstanceProfile & profile);


	int ToggleErrorMode(ErrorReport::ErrorMode errorMode);
	int SetErrorMode(ErrorReport::ErrorMode errorMode, bool enabled);
	int GetErrorMode(ErrorReport::ErrorMode errorMode);

	bool TestClass();
}
