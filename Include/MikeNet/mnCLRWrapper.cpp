#include "FullInclude.h"

#ifdef CLR
#using <mscorlib.dll>
using namespace System;
using System::Runtime::InteropServices::Marshal;

/**
 * @brief	Converts a C string into a CLR string.
 *
 * @param	ConvertMe	C string to convert.
 *
 * @return	CLR string.
 */
String ^ ConvertStr(const char * ConvertMe)
{
	String ^ Return = gcnew String(ConvertMe);
	return(Return);
}

/**
 * @brief	Converts a CLR string into a C string that is stored in managed memory.
 *
 * @param [in]	ConvertMe		String to convert. 
 * @param [out]	ptr				Reference to destination to store pointer to string, which
 * should be cleaned up using CleanupPtr.
 *
 * @return	c string.
 */
char * ConvertStr(String ^ ConvertMe, IntPtr & ptr)
{
		ptr = Marshal::StringToHGlobalAnsi(ConvertMe);
		char * Return = static_cast<char*>(ptr.ToPointer());
		return(Return);
}

/**
 * @brief	Cleans up pointer.
 *
 * @param 	ptr	The pointer to cleanup. 
 */
void CleanupPtr(IntPtr ptr)
{
	Marshal::FreeHGlobal(ptr);
}


public ref struct mnCLR
{
	static int AddPacket(__int64 Destination, __int64 From)
	{
		return(mn::AddPacket(Destination, From));
	}
	static int EqualPacket(__int64 Destination, __int64 From)
	{
		return(mn::AssignPacket(Destination, From));
	}
	static int ComparePacket(__int64 Packet1, __int64 Packet2)
	{
		return(mn::ComparePacket(Packet1,Packet2));
	}
	static String ^ GetErrorCommand()
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetErrorCommand();

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);
		return(Return);
	}
	static String ^ GetErrorFile()
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetErrorFile();

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);
		return(Return);
	}
	static size_t GetNumInstances()
	{
		return(mn::GetNumInstances());
	}
	static int Encrypt(__int64 Packet, __int64 Key, bool Block)
	{
		return(mn::Encrypt(Packet, Key, Block));
	}
	static int Decrypt(__int64 Packet, __int64 Key, bool Block)
	{
		return(mn::Decrypt(Packet, Key, Block));
	}
	static int GetLastEncryptionOperationFinished(__int64 Packet)
	{
		return mn::GetLastEncryptionOperationFinished(Packet);
	}

	static __int64 CreateKey256(__int64 key1, __int64 key2, __int64 key3, __int64 key4)
	{
		return(mn::CreateKey256(key1, key2, key3, key4));
	}
	static __int64 CreateKey192(__int64 key1, __int64 key2, __int64 key3)
	{
		return(mn::CreateKey192(key1, key2, key3));
	}
	static __int64 CreateKey128(__int64 key1, __int64 key2)
	{
		return(mn::CreateKey128(key1, key2));
	}
	static int DeleteKey(__int64 Key)
	{
		return(mn::DeleteKey(Key));
	}

	static int DisconnectClient(size_t Instance, size_t ClientID)
	{
		return(mn::DisconnectClient(Instance, ClientID));
	} 
	static size_t ClientConnected(size_t Instance, size_t ClientID)
	{
		return(mn::ClientConnected(Instance, ClientID));
	}

	static __int64 GetErrorLine()
	{
		return(mn::GetErrorLine());
	}
	static __int64 GetErrorCode()
	{
		return(mn::GetErrorCode());
	}

	static int AddInt(__int64 Packet, int Add)
	{
		return(mn::AddInt(Packet, Add));
	}
	static int AddLong(__int64 Packet, __int64 Add)
	{
		return(mn::AddLongLongInt(Packet, Add));
	}
	static int AddFloat(__int64 Packet, float Add)
	{
		return(mn::AddFloat(Packet, Add));
	}
	static int AddUnsignedByte(__int64 Packet, unsigned char Add)
	{
		return(mn::AddUnsignedByte(Packet, Add));
	}
	static int AddDouble(__int64 Packet, double Add)
	{
		return(mn::AddDouble(Packet, Add));
	}
	static int AddUnsignedShort(__int64 Packet, unsigned short int Add)
	{
		return(mn::AddUnsignedShortInt(Packet, Add));
	}
	static int AddUnsignedInt(__int64 Packet, unsigned int Add)
	{
		return(mn::AddUnsignedInt(Packet, Add));
	}
	static int AddString(__int64 Packet, String ^ Add, size_t Length, bool Prefix)
	{
		// ConvertStr parameter
		IntPtr ptr;
		char * ParaData = ConvertStr(Add,ptr);

		// Perform MikeNet operation
		int Result = mn::AddStringC(Packet, ParaData, Length, Prefix);
		CleanupPtr(ptr);

		// Return
		return(Result);
	}

	static size_t GetClientFrom(__int64 Packet)
	{
		return(mn::GetClientFrom(Packet));
	}
	static size_t GetLocalInterfaceAmount()
	{
		return(mn::GetLocalInterfaceAmount());
	}
	static int GetInt(__int64 Packet)
	{
		return(mn::GetInt(Packet));
	}
	static __int64 GetLong(__int64 Packet)
	{
		return(mn::GetLongLongInt(Packet));
	}
	static unsigned char GetUnsignedByte(__int64 Packet)
	{
		return(mn::GetUnsignedByte(Packet));
	}
	static double GetDouble(__int64 Packet)
	{
		return(mn::GetDouble(Packet));
	}
	static unsigned short int GetUnsignedShort(__int64 Packet)
	{
		return(mn::GetUnsignedShortInt(Packet));
	}
	static size_t GetUnsignedInt(__int64 Packet)
	{
		return(mn::GetUnsignedInt(Packet));
	}

	static size_t GetAge(__int64 Packet)
	{
		return(mn::GetAge(Packet));
	}
	static size_t GetPacketRemainder(__int64 Packet)
	{
		return(mn::GetPacketRemainder(Packet));
	}
	static int ClearPacket(__int64 Packet)
	{
		return(mn::ClearPacket(Packet));
	}
	static double GetPercentTCP(size_t Instance, size_t ClientID)
	{
		return(mn::GetPercentTCP(Instance, ClientID));
	}
	static int AddSizeT(__int64 Packet, size_t Data)
	{
		return(mn::AddSizeT(Packet,Data));
	}
	static size_t GetSizeT(__int64 Packet)
	{
		return mn::GetSizeT(Packet);
	}
	static int SendUDP(size_t Instance, __int64 Packet, size_t ClientID, bool Keep_packet, bool Block_until_sent)
	{
		return(mn::SendUDP(Instance, Packet, ClientID, Keep_packet, Block_until_sent));
	}
	static int SendTCP(size_t Instance, __int64 Packet, size_t ClientID, bool Keep_packet, bool Block_until_sent)
	{
		return(mn::SendTCP(Instance, Packet, ClientID, Keep_packet, Block_until_sent));
	}
	static int SendAllTCP(size_t Instance, __int64 Packet, bool Keep_packet, bool Block_until_sent, size_t Client_exclude)
	{
		return(mn::SendAllTCP(Instance, Packet, Keep_packet, Block_until_sent, Client_exclude));
	}
	static int SendAllUDP(size_t Instance, __int64 Packet, bool Keep_packet, bool Block_until_sent, size_t Client_exclude)
	{
		return(mn::SendAllUDP(Instance, Packet, Keep_packet, Block_until_sent, Client_exclude));
	}
	static size_t RecvTCP(size_t Instance, __int64 Packet, size_t ClientID)
	{
		return(mn::RecvTCP(Instance, Packet, ClientID));
	}
	static size_t RecvUDP(size_t Instance, __int64 Packet, size_t ClientID, size_t OperationID)
	{
		return(mn::RecvUDP(Instance, Packet, ClientID, OperationID));
	}


	static int Start(size_t Number_of_instances, size_t Number_of_threads)
	{
		return(mn::Start(Number_of_instances, Number_of_threads));
	}

	static int StartServer(size_t Instance, size_t MaxClients, __int64 Profile)
	{
		return(mn::StartServer(Instance, MaxClients, Profile));
	}
	static int SetServerTimeout(size_t Instance, size_t Timeout_in_seconds)
	{
		return(mn::SetServerTimeout(Instance, Timeout_in_seconds));
	}
	static size_t GetServerTimeout(size_t Instance)
	{
		return(mn::GetServerTimeout(Instance));
	}
	static size_t ClientJoined(size_t Instance)
	{
		return(mn::ClientJoined(Instance));
	}
	static size_t ClientLeft(size_t Instance)
	{
		return(mn::ClientLeft(Instance));
	}

	static int Connect(size_t Instance, String ^ TCP_IP_to_connect_to, unsigned short TCP_port_to_connect_to, String ^ UDP_IP_to_connect_to, unsigned short UDP_port_to_connect_to, size_t Timeout_in_seconds, bool Block_until_connected, __int64 Profile)
	{
		// ConvertStr parameter
		IntPtr ptr1;
		char * ParaData1 = ConvertStr(TCP_IP_to_connect_to,ptr1);
		
		IntPtr ptr2;
		char * ParaData2 = ConvertStr(UDP_IP_to_connect_to,ptr2);

		// Perform MikeNet operation
		int Result = mn::Connect(Instance, ParaData1, TCP_port_to_connect_to, ParaData2, UDP_port_to_connect_to, Timeout_in_seconds, Block_until_connected, Profile);
		CleanupPtr(ptr1);
		CleanupPtr(ptr2);

		// Return
		return(Result);
	}
	static int PollConnect(size_t Instance)
	{
		return(mn::PollConnect(Instance));
	}
	static int StopConnect(size_t Instance)
	{
		return(mn::StopConnect(Instance));
	}

	static int StartBroadcast(size_t Instance, String ^ TCP_IP_to_connect_to, unsigned short Broadcast_port_to_connect_to, bool Send_enabled, bool Receive_enabled, __int64 Profile)
	{
		// ConvertStr parameter
		IntPtr ptr1;
		char * ParaData1 = ConvertStr(TCP_IP_to_connect_to,ptr1);

		int Result = mn::StartBroadcast(Instance, ParaData1, Broadcast_port_to_connect_to, Send_enabled, Receive_enabled, Profile);
		CleanupPtr(ptr1);

		return Result;
	}

	static size_t GetLogicalCPU()
	{
		return(mn::GetLogicalCPU());
	}

	static int Finish(size_t Instance)
	{
		return(mn::Finish(Instance));
	}

	static size_t GetMaxClients(size_t Instance)
	{
		return(mn::GetMaxClients(Instance));
	}
	static size_t GetMaxOperations(size_t Instance)
	{
		return(mn::GetMaxOperations(Instance));
	}
	static size_t GetRecvSizeTCP(size_t Instance, size_t ClientID)
	{
		return(mn::GetRecvSizeTCP(Instance, ClientID));
	}
	static size_t GetRecvSizeUDP(size_t Instance)
	{
		return(mn::GetRecvSizeUDP(Instance));
	}
	static size_t GetThreads()
	{
		return(mn::GetThreads());
	}
	static char GetState(size_t Instance)
	{
		return(mn::GetState(Instance));
	}
	static char GetModeUDP(size_t Instance)
	{
		return(mn::GetModeUDP(Instance));
	}
	static int GetErrorMode(int Mode)
	{
		return(mn::GetErrorMode(Mode));
	}
	static int GetEnabledUDP(size_t Instance)
	{
		return(mn::GetEnabledUDP(Instance));
	}

	static unsigned short GetLocalPortTCP(size_t Instance)
	{
		return(mn::GetLocalPortTCP(Instance));
	}
	static unsigned short GetLocalPortUDP(size_t Instance)
	{
		return(mn::GetLocalPortUDP(Instance));
	}
	static unsigned short GetConnectPortTCP(size_t Instance)
	{
		return(mn::GetConnectPortTCP(Instance));
	}
	static unsigned short GetConnectPortUDP(size_t Instance)
	{
		return(mn::GetConnectPortUDP(Instance));
	}
	static unsigned short GetClientPortTCP(size_t Instance, size_t ClientID)
	{
		return(mn::GetClientPortTCP(Instance, ClientID));
	}
	static unsigned short GetClientPortUDP(size_t Instance, size_t ClientID)
	{
		return(mn::GetClientPortUDP(Instance, ClientID));
	}

	static size_t GetClientID(size_t Instance)
	{
		return(mn::GetClientID(Instance));
	}

	static __int64 CreatePacket()
	{
		return(mn::CreatePacket());
	}
	static int DeletePacket(__int64 Packet)
	{
		return(mn::DeletePacket(Packet));
	}
	static int SetMemorySize(__int64 Packet,size_t Size)
	{
		return(mn::SetMemorySize(Packet,Size));
	}
	static size_t GetMemorySize(__int64 Packet)
	{
		return(mn::GetMemorySize(Packet));
	}
	static int SetUsedSize(__int64 Packet,size_t Size)
	{
		return(mn::SetUsedSize(Packet,Size));
	}
	static size_t GetUsedSize(__int64 Packet)
	{
		return(mn::GetUsedSize(Packet));
	}
	static int SetCursor(__int64 Packet, size_t Position)
	{
		return(mn::SetCursor(Packet, Position));
	}
	static size_t GetCursor(__int64 Packet)
	{
		return(mn::GetCursor(Packet));
	}
	static size_t GetOperation(__int64 Packet)
	{
		return(mn::GetOperation(Packet));
	}
	static size_t GetInstance(__int64 Packet)
	{
		return(mn::GetInstance(Packet));
	}

	static String ^ GetLocalInterface(size_t Number)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetLocalInterface(Number).GetIP();

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}
	static String ^ GetHostName()
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetHostName();

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}

	static unsigned __int64 GetUnsignedLong(__int64 Packet)
	{
		return(mn::GetUnsignedLongLongInt(Packet));
	}
	static char GetByte(__int64 Packet)
	{
		return(mn::GetByte(Packet));
	}
	static short int GetShort(__int64 Packet)
	{
		return(mn::GetShortInt(Packet));
	}

	static int AddUnsignedLong(__int64 Packet, unsigned __int64 Add)
	{
		return(mn::AddUnsignedLongLongInt(Packet, Add));
	}
	static int AddByte(__int64 Packet, char Add)
	{
		return(mn::AddByte(Packet, Add));
	}
	static int AddShort(__int64 Packet, short int Add)
	{
		return(mn::AddShortInt(Packet, Add));
	}


	static String ^ GetErrorOperation()
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetErrorOperation();

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);
		return(Return);
	}
	static String ^ GetErrorFull()
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetErrorFull();

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}


	static float GetFloat(__int64 Packet)
	{
		return(mn::GetFloat(Packet));
	}

	static String ^ GetString(__int64 Packet, size_t Length, bool NullTerminated)
	{
		// Perform MikeNet operation
		char * ReturnData = mn::GetStringC(Packet, Length, NullTerminated);

		// Return
		String ^ Return = ConvertStr(ReturnData);
		delete[] ReturnData;
		return(Return);
	}

	static String ^ GetLocalIPTCP(size_t Instance)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetLocalIPTCP(Instance);

		// Return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}
	static String ^ GetLocalIPUDP(size_t Instance)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetLocalIPUDP(Instance);

		// Return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}
	static String ^ GetConnectIPTCP(size_t Instance)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetConnectIPTCP(Instance);

		// Return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}
	static String ^ GetConnectIPUDP(size_t Instance)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetConnectIPUDP(Instance);

		// Return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}
	static String ^ GetClientIPTCP(size_t Instance, size_t ClientID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetClientIPTCP(Instance, ClientID);

		// Return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}
	static String ^ GetClientIPUDP(size_t Instance, size_t ClientID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetClientIPUDP(Instance, ClientID);

		// Return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}
	static String ^ DNS_B(String ^ Host_name)
	{
		// ConvertStr parameter
		IntPtr ptr;
		char * ParaData = ConvertStr(Host_name,ptr);

		// Perform MikeNet operation
		const char * ReturnData = mn::DNS_B(ParaData);
		CleanupPtr(ptr);

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}

	static String ^ GetPortMapExternalIP(size_t PortMapID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mnNAT::GetPortMapExternalIP(PortMapID);

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}

	static String ^ GetPortMapProtocol(size_t PortMapID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mnNAT::GetPortMapProtocol(PortMapID);

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}

	static String ^ GetPortMapInternalIP(size_t PortMapID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mnNAT::GetPortMapInternalIP(PortMapID);

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}

	static String ^ GetPortMapDescription(size_t PortMapID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mnNAT::GetPortMapDescription(PortMapID);

		// ConvertStr return
		String ^ Return = ConvertStr(ReturnData);
		return(Return);
	}


	static int PollNAT()
	{
		return(mnNAT::PollNAT());
	}

	static __int64 StartNAT(bool Block)
	{
		return(mnNAT::StartNAT(Block));
	}

	static __int64 FinishNAT()
	{
		return(mnNAT::FinishNAT());
	}

	static __int64 UpdateNAT(bool Block)
	{
		return(mnNAT::UpdateNAT(Block));
	}

	static __int64 AddPortMap(String ^ Protocol, long ExternalPort, long InternalPort, String ^ InternalIP, bool Enabled, String ^ Description, bool Block)
	{
		__int64 returnMe;
		
		// ConvertStr parameters
		IntPtr ptr1, ptr2, ptr3;
		char * ParaData1 = ConvertStr(Protocol,ptr1);
		char * ParaData2 = ConvertStr(InternalIP,ptr2);
		char * ParaData3 = ConvertStr(Description,ptr3);

		// Perform MikeNet operation
		returnMe = mnNAT::AddPortMap(ParaData1,ExternalPort,InternalPort,ParaData2,Enabled,ParaData3,Block);

		// Cleanup
		CleanupPtr(ptr1);
		CleanupPtr(ptr2);
		CleanupPtr(ptr3);

		return(returnMe);
	}

	static size_t GetPortMapAmount()
	{
		return(mnNAT::GetPortMapAmount());
	}

	static __int64 EnablePortMap(size_t PortMapID, bool Block)
	{
		return(mnNAT::EnablePortMap(PortMapID,Block));
	}

	static __int64 DisablePortMap(size_t PortMapID, bool Block)
	{
		return(mnNAT::DisablePortMap(PortMapID,Block));
	}

	static __int64 SetPortMapInternalIP(size_t PortMapID, String ^ InternalIP, bool Block)
	{
		__int64 returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(InternalIP,ptr);

		// Perform MikeNet operation
		returnMe = mnNAT::SetPortMapInternalIP(PortMapID,ParaData,Block);

		// Cleanup
		CleanupPtr(ptr);

		return(returnMe);
	}

	static __int64 SetPortMapInternalPort(size_t PortMapID, long InternalPort, bool Block)
	{
		return(mnNAT::SetPortMapInternalPort(PortMapID, InternalPort, Block));
	}

	static __int64 SetPortMapDescription(size_t PortMapID, String ^ Description, bool Block)
	{
		__int64 returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(Description,ptr);

		// Perform MikeNet operation
		returnMe = mnNAT::SetPortMapDescription(PortMapID,ParaData,Block);

		// Cleanup
		CleanupPtr(ptr);

		return(returnMe);
	}

	static long GetPortMapExternalPort(size_t PortMapID)
	{
		return(mnNAT::GetPortMapExternalPort(PortMapID));
	}

	static long GetPortMapInternalPort(size_t PortMapID)
	{
		return(mnNAT::GetPortMapInternalPort(PortMapID));
	}

	static int GetPortMapEnabled(size_t PortMapID)
	{
		return(mnNAT::GetPortMapEnabled(PortMapID));
	}

	static __int64 DeletePortMapA(size_t PortMapID, bool Block)
	{
		return(mnNAT::DeletePortMapA(PortMapID, Block));
	}

	static __int64 DeletePortMapB(String ^ Protocol, long ExternalPort, bool Block)
	{
		__int64 returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(Protocol,ptr);

		// Perform MikeNet operation
		returnMe = mnNAT::DeletePortMapB(ParaData,ExternalPort,Block);

		// Cleanup
		CleanupPtr(ptr);

		return(returnMe);
	}

	static int PortMapExist(String ^ Protocol, long ExternalPort)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(Protocol,ptr);

		// Perform MikeNet operation
		returnMe = mnNAT::PortMapExist(ParaData,ExternalPort);

		// Cleanup
		CleanupPtr(ptr);

		return(returnMe);
	}

	static size_t FindPortMap(String ^ Protocol, long ExternalPort)
	{
		size_t returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(Protocol,ptr);

		// Perform MikeNet operation
		returnMe = mnNAT::FindPortMap(ParaData,ExternalPort);

		// Cleanup
		CleanupPtr(ptr);

		return(returnMe);
	}

	static String ^ GetVersion()
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetVersion();

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);
		return(Return);
	}

	static bool GetErrorFlag()
	{
		return(mn::GetErrorFlag());
	}

	static void SetErrorFlag()
	{
		mn::SetErrorFlag();
	}	

	static void ClearErrorFlag()
	{
		mn::ClearErrorFlag();
	}

	static int ToggleErrorMode(int Mode)
	{
		return(mn::ToggleErrorMode(Mode));
	}

	static int Erase(__int64 Packet, size_t StartPos, size_t Amount)
	{
		return(mn::Erase(Packet, StartPos, Amount));
	}

	static int Insert(__int64 Packet, size_t Amount)
	{
		return(mn::Insert(Packet, Amount));
	}

	static __int64 CreatePacketFromPacket(__int64 FromPacket)
	{
		return(mn::CreatePacketFromPacket(FromPacket));
	}

	static __int64 CreatePacketFromString(String ^ String)
	{
		// ConvertStr parameter
		IntPtr ptr;
		char * ParaData = ConvertStr(String,ptr);

		// Perform MikeNet operation
		__int64 Result = mn::CreatePacketFromString(ParaData);
		CleanupPtr(ptr);

		// Return
		return(Result);
	}

	static int ComparePacketString(__int64 Packet, String ^ String)
	{
		// ConvertStr parameter
		IntPtr ptr;
		char * ParaData = ConvertStr(String,ptr);

		// Perform MikeNet operation
		int Result = mn::ComparePacketString(Packet,ParaData);
		CleanupPtr(ptr);

		// Return
		return(Result);
	}

	static int ChangeMemorySize(__int64 Packet, size_t Size)
	{
		return(mn::ChangeMemorySize(Packet, Size));
	}

	static int EqualPacketString(__int64 Destination, String ^ From)
	{
		// ConvertStr parameter
		IntPtr ptr;
		char * ParaData = ConvertStr(From,ptr);

		// Perform MikeNet operation
		int Result = mn::ComparePacketString(Destination,ParaData);
		CleanupPtr(ptr);

		// Return
		return(Result);
	}


	static int FlushRecvTCP(size_t Instance, size_t Client)
	{
		return(mn::FlushRecvTCP(Instance, Client));
	}

	static int FlushRecvUDP(size_t Instance, size_t Client)
	{
		return(mn::FlushRecvUDP(Instance,Client));
	}

	static int ChangeBufferSizeTCP(size_t Instance, size_t Client, size_t iSize)
	{
		return(mn::ChangeBufferSizeTCP(Instance,Client,iSize));
	}

	static int SetAutoResizeTCP(size_t Instance, size_t Client, bool bAutoResize)
	{
		return(mn::SetAutoResizeTCP(Instance,Client,bAutoResize));
	}

	static int GetAutoResizeTCP(size_t Instance, size_t Client)
	{
		return(mn::GetAutoResizeTCP(Instance,Client));
	}

	static size_t GetBytesTCP(size_t Instance, size_t Client)
	{
		return(mn::GetBytesTCP(Instance,Client));
	}

	static int GetHandshakeEnabledTCP(size_t Instance)
	{
		return(mn::GetHandshakeEnabledTCP(Instance));
	}


	static char GetModeTCP(size_t Instance)
	{
		return(mn::GetModeTCP(Instance));
	}


	static int ShutdownClient(size_t Instance, size_t Client)
	{
		return(mn::ShutdownClient(Instance,Client));
	}


	static int GetGracefulDisconnectEnabledTCP(size_t Instance)
	{
		return(mn::GetGracefulDisconnectEnabledTCP(Instance));
	}


	static unsigned int GetSendTimeout(size_t Instance)
	{
		return(mn::GetSendTimeout(Instance));
	}


	static size_t GetStoreAmountTCP(size_t Instance, size_t Client)
	{
		return(mn::GetStoreAmountTCP(Instance,Client));
	}

	static size_t GetStoreAmountUDP(size_t Instance, size_t Client)
	{
		return(mn::GetStoreAmountUDP(Instance,Client));
	}

	static int GetPostfixTCP(size_t Instance, __int64 Packet)
	{
		return(mn::GetPostfixTCP(Instance,Packet));
	}


	/*
	static int StartFirewall()
	{
		return(mn::StartFirewall());
	}

	static int FinishFirewall()
	{
		return(mn::FinishFirewall());
	}

	static int UpdateFirewall()
	{
		return(mn::UpdateFirewall());
	}


	static size_t GetCurrentProfile()
	{
		return(mn::GetCurrentProfile());
	}

	static int ResetFirewall()
	{
		return(mn::ResetFirewall());
	}

	static int IsPortAllowedA(String ^ FileName, long PortNumber, int Protocol, String ^ LocalAddress, int IPVersion)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptrFileName;
		char * ParaDataFileName = ConvertStr(FileName,ptrFileName);

		IntPtr ptrLocalAddress;
		char * ParaDataLocalAddress = ConvertStr(LocalAddress,ptrLocalAddress);

		// Perform MikeNet operation
		returnMe = mn::IsPortAllowedA(ParaDataFileName,PortNumber,Protocol,ParaDataLocalAddress,IPVersion);

		// Cleanup
		CleanupPtr(ptrFileName);
		CleanupPtr(ptrLocalAddress);

		// Return
		return(returnMe);
	}

	static int IsPortAllowedB(long PortNumber, int Protocol)
	{
		int returnMe;
		
		// Perform MikeNet operation
		returnMe = mn::IsPortAllowedB(PortNumber,Protocol);

		// Return
		return(returnMe);
	}

	static int IsTypeAllowedICMPA(unsigned char Type, String ^ LocalAddress, int IPVersion)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(LocalAddress,ptr);

		// Perform MikeNet operation
		returnMe = mn::IsTypeAllowedICMPA(Type,ParaData,IPVersion);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int IsTypeAllowedICMPB(unsigned char Type, int IPVersion)
	{
		return(mn::IsTypeAllowedICMPB(Type,IPVersion));
	}


	static String ^ GetServiceName(size_t ProfileID, size_t ServiceID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetServiceName(ProfileID,ServiceID);

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);

		// Return
		return(Return);
	}

	static int GetServiceType(size_t ProfileID, size_t ServiceID)
	{
		return(mn::GetServiceType(ProfileID,ServiceID));
	}

	static int GetServiceCustomized(size_t ProfileID, size_t ServiceID)
	{
		return(mn::GetServiceCustomized(ProfileID,ServiceID));
	}

	static int GetServiceIPVersion(size_t ProfileID, size_t ServiceID)
	{
		return(mn::GetServiceIPVersion(ProfileID,ServiceID));
	}

	static int GetServiceScope(size_t ProfileID, size_t ServiceID)
	{
		return(mn::GetServiceScope(ProfileID,ServiceID));
	}

	static String ^ GetServiceRemoteAddresses(size_t ProfileID, size_t ServiceID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetServiceRemoteAddresses(ProfileID,ServiceID);

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);

		// Return
		return(Return);
	}

	static int GetServiceEnabled(size_t ProfileID, size_t ServiceID)
	{
		return(mn::GetServiceEnabled(ProfileID,ServiceID));
	}


	static int SetServiceIPVersion(size_t ProfileID, size_t ServiceID, int IPVersion)
	{
		return(mn::SetServiceIPVersion(ProfileID,ServiceID,IPVersion));
	}

	static int SetServiceScope(size_t ProfileID, size_t ServiceID, int Scope)
	{
		return(mn::SetServiceScope(ProfileID,ServiceID,Scope));
	}

	static int SetServiceRemoteAddresses(size_t ProfileID, size_t ServiceID, String ^ RemoteAddresses)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(RemoteAddresses,ptr);

		// Perform MikeNet operation
		returnMe = mn::SetServiceRemoteAddresses(ProfileID,ServiceID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int SetServiceEnabled(size_t ProfileID, size_t ServiceID, bool Enabled)
	{
		return(mn::SetServiceEnabled(ProfileID,ServiceID,Enabled));
	}

	static int AddServicePort(size_t ProfileID, size_t ServiceID, String ^ Name, int IPVersion, int Protocol, long PortNumber, int Scope, String ^ RemoteAddresses, bool Enabled)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptrName;
		char * ParaDataName = ConvertStr(Name,ptrName);

		IntPtr ptrRemoteAddresses;
		char * ParaDataRemoteAddresses = ConvertStr(RemoteAddresses,ptrRemoteAddresses);

		// Perform MikeNet operation
		returnMe = mn::AddServicePort(ProfileID, ServiceID, ParaDataName,IPVersion,Protocol,PortNumber,Scope,ParaDataRemoteAddresses,Enabled);

		// Cleanup
		CleanupPtr(ptrName);
		CleanupPtr(ptrRemoteAddresses);

		// Return
		return(returnMe);
	}

	static int DeleteServicePortA(size_t ProfileID, size_t ServiceID, long PortNumber, int Protocol)
	{
		return(mn::DeleteServicePortA(ProfileID,ServiceID,PortNumber,Protocol));
	}

	static int DeleteServicePortB(size_t ProfileID, size_t ServiceID, size_t PortID)
	{
		return(mn::DeleteServicePortB(ProfileID,ServiceID,PortID));
	}

	static size_t FindServicePort(size_t ProfileID, size_t ServiceID, long PortNumber, int Protocol)
	{
		return(mn::FindServicePort(ProfileID,ServiceID,PortNumber,Protocol));
	}

	static int ServicePortExist(size_t ProfileID, size_t ServiceID, long PortNumber, int Protocol)
	{
		return(mn::ServicePortExist(ProfileID,ServiceID,PortNumber,Protocol));
	}

	static size_t GetServicePortAmount(size_t ProfileID, size_t ServiceID)
	{
		return(mn::GetServicePortAmount(ProfileID,ServiceID));
	}


	static int GetFirewallEnabled(size_t ProfileID)
	{
		return(mn::GetFirewallEnabled(ProfileID));
	}

	static int GetExceptionsAllowed(size_t ProfileID)
	{
		return(mn::GetExceptionsAllowed(ProfileID));
	}

	static int GetNotificationsEnabled(size_t ProfileID)
	{
		return(mn::GetNotificationsEnabled(ProfileID));
	}

	static int GetUnicastToMulticastEnabled(size_t ProfileID)
	{
		return(mn::GetUnicastToMulticastEnabled(ProfileID));
	}

	static int GetRemoteAdminIPVersion(size_t ProfileID)
	{
		return(mn::GetRemoteAdminIPVersion(ProfileID));
	}

	static int GetRemoteAdminScope(size_t ProfileID)
	{
		return(mn::GetRemoteAdminScope(ProfileID));
	}

	static String ^ GetRemoteAdminAddresses(size_t ProfileID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetRemoteAdminAddresses(ProfileID);

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);

		// Return
		return(Return);
	}

	static int GetRemoteAdminEnabled(size_t ProfileID)
	{
		return(mn::GetRemoteAdminEnabled(ProfileID));
	}

	static int GetICMPAllowOutboundDestinationUnreachable(size_t ProfileID)
	{
		return(mn::GetICMPAllowOutboundDestinationUnreachable(ProfileID));
	}

	static int GetICMPAllowRedirect(size_t ProfileID)
	{
		return(mn::GetICMPAllowRedirect(ProfileID));
	}

	static int GetICMPAllowInboundEchoRequest(size_t ProfileID)
	{
		return(mn::GetICMPAllowInboundEchoRequest(ProfileID));
	}

	static int GetICMPAllowOutboundTimeExceeded(size_t ProfileID)
	{
		return(mn::GetICMPAllowOutboundTimeExceeded(ProfileID));
	}

	static int GetICMPAllowOutboundParameterProblem(size_t ProfileID)
	{
		return(mn::GetICMPAllowOutboundParameterProblem(ProfileID));
	}

	static int GetICMPAllowOutboundSourceQuench(size_t ProfileID)
	{
		return(mn::GetICMPAllowOutboundSourceQuench(ProfileID));
	}

	static int GetICMPAllowInboundRouterRequest(size_t ProfileID)
	{
		return(mn::GetICMPAllowInboundRouterRequest(ProfileID));
	}

	static int GetICMPAllowInboundTimestampRequest(size_t ProfileID)
	{
		return(mn::GetICMPAllowInboundTimestampRequest(ProfileID));
	}

	static int GetICMPAllowInboundMaskRequest(size_t ProfileID)
	{
		return(mn::GetICMPAllowInboundMaskRequest(ProfileID));
	}

	static int GetICMPAllowOutboundPacketTooBig(size_t ProfileID)
	{
		return(mn::GetICMPAllowOutboundPacketTooBig(ProfileID));
	}


	static int SetFirewallEnabled(size_t ProfileID, bool Boolean)
	{
		return(mn::SetFirewallEnabled(ProfileID,Boolean));
	}

	static int SetExceptionsAllowed(size_t ProfileID, bool Boolean)
	{
		return(mn::SetExceptionsAllowed(ProfileID,Boolean));
	}

	static int SetNotificationsEnabled(size_t ProfileID, bool Boolean)
	{
		return(mn::SetNotificationsEnabled(ProfileID,Boolean));
	}

	static int SetUnicastToMulticastEnabled(size_t ProfileID, bool Boolean)
	{
		return(mn::SetUnicastToMulticastEnabled(ProfileID,Boolean));
	}

	static int SetRemoteAdminIPVersion(size_t ProfileID, int IPVersion)
	{
		return(mn::SetRemoteAdminIPVersion(ProfileID,IPVersion));
	}

	static int SetRemoteAdminScope(size_t ProfileID, int Scope)
	{
		return(mn::SetRemoteAdminScope(ProfileID,Scope));
	}

	static int SetRemoteAdminAddresses(size_t ProfileID, String ^ Addresses)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(Addresses,ptr);

		// Perform MikeNet operation
		returnMe = mn::SetRemoteAdminAddresses(ProfileID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int SetRemoteAdminEnabled(size_t ProfileID, bool Boolean)
	{
		return(mn::SetRemoteAdminEnabled(ProfileID,Boolean));
	}

	static int SetICMPAllowOutboundDestinationUnreachable(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowOutboundDestinationUnreachable(ProfileID,Boolean));
	}

	static int SetICMPAllowRedirect(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowRedirect(ProfileID,Boolean));
	}

	static int SetICMPAllowInboundEchoRequest(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowInboundEchoRequest(ProfileID,Boolean));
	}

	static int SetICMPAllowOutboundTimeExceeded(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowOutboundTimeExceeded(ProfileID,Boolean));
	}

	static int SetICMPAllowOutboundParameterProblem(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowOutboundParameterProblem(ProfileID,Boolean));
	}

	static int SetICMPAllowOutboundSourceQuench(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowOutboundSourceQuench(ProfileID,Boolean));
	}

	static int SetICMPAllowInboundRouterRequest(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowInboundRouterRequest(ProfileID,Boolean));
	}

	static int SetICMPAllowInboundTimestampRequest(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowInboundTimestampRequest(ProfileID,Boolean));
	}

	static int SetICMPAllowInboundMaskRequest(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowInboundMaskRequest(ProfileID,Boolean));
	}

	static int SetICMPAllowOutboundPacketTooBig(size_t ProfileID, bool Boolean)
	{
		return(mn::SetICMPAllowOutboundPacketTooBig(ProfileID,Boolean));
	}


	static size_t GetApplicationAmount(size_t ProfileID)
	{
		return(mn::GetApplicationAmount(ProfileID));
	}

	static int AddApplication(size_t ProfileID, String ^ Name, String ^ FileName, int IPVersion, int Scope, String ^ RemoteAddresses, bool Enabled)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptrName;
		char * ParaDataName = ConvertStr(Name,ptrName);

		IntPtr ptrFileName;
		char * ParaDataFileName = ConvertStr(FileName,ptrFileName);

		IntPtr ptrRemoteAddresses;
		char * ParaDataRemoteAddresses = ConvertStr(RemoteAddresses,ptrRemoteAddresses);

		// Perform MikeNet operation
		returnMe = mn::AddApplication(ProfileID,ParaDataName,ParaDataFileName,IPVersion,Scope,ParaDataRemoteAddresses,Enabled);

		// Cleanup
		CleanupPtr(ptrName);
		CleanupPtr(ptrFileName);
		CleanupPtr(ptrRemoteAddresses);

		// Return
		return(returnMe);
	}

	static int DeleteApplicationA(size_t ProfileID, String ^ FileName)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(FileName,ptr);

		// Perform MikeNet operation
		returnMe = mn::DeleteApplicationA(ProfileID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int DeleteApplicationB(size_t ProfileID, size_t ApplicationID)
	{
		return(mn::DeleteApplicationB(ProfileID,ApplicationID));
	}

	static size_t FindApplication(size_t ProfileID, String ^ FileName)
	{
		size_t returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(FileName,ptr);

		// Perform MikeNet operation
		returnMe = mn::FindApplication(ProfileID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int ApplicationExist(size_t ProfileID, String ^ FileName)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(FileName,ptr);

		// Perform MikeNet operation
		returnMe = mn::ApplicationExist(ProfileID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}


	static size_t GetServiceAmount(size_t ProfileID)
	{
		return(mn::GetServiceAmount(ProfileID));
	}


	static int AddPort(size_t ProfileID, String ^ Name, int IPVersion, int Protocol, long PortNumber, int Scope, String ^ RemoteAddresses, bool Enabled)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptrName;
		char * ParaDataName = ConvertStr(Name,ptrName);

		IntPtr ptrRemoteAddresses;
		char * ParaDataRemoteAddresses = ConvertStr(RemoteAddresses,ptrRemoteAddresses);

		// Perform MikeNet operation
		returnMe = mn::AddPort(ProfileID,ParaDataName,IPVersion,Protocol,PortNumber,Scope,ParaDataRemoteAddresses,Enabled);

		// Cleanup
		CleanupPtr(ptrName);
		CleanupPtr(ptrRemoteAddresses);

		// Return
		return(returnMe);
	}

	static int DeletePortA(size_t ProfileID, long PortNumber, int Protocol)
	{
		return(mn::DeletePortA(ProfileID,PortNumber,Protocol));
	}

	static int DeletePortB(size_t ProfileID, size_t PortID)
	{
		return(mn::DeletePortB(ProfileID,PortID));
	}

	static size_t FindPort(size_t ProfileID, long PortNumber, int Protocol)
	{
		return(mn::FindPort(ProfileID,PortNumber,Protocol));
	}

	static int PortExist(size_t ProfileID, long PortNumber, int Protocol)
	{
		return(mn::PortExist(ProfileID,PortNumber,Protocol));
	}

	static size_t GetPortAmount(size_t ProfileID)
	{
		return(mn::GetPortAmount(ProfileID));
	}


	static String ^ GetApplicationName(size_t ProfileID, size_t ApplicationID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetApplicationName(ProfileID,ApplicationID);

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);

		// Return
		return(Return);
	}

	static String ^ GetApplicationFileName(size_t ProfileID, size_t ApplicationID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetApplicationFileName(ProfileID,ApplicationID);

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);

		// Return
		return(Return);
	}

	static int GetApplicationIPVersion(size_t ProfileID, size_t ApplicationID)
	{
		return(mn::GetApplicationIPVersion(ProfileID,ApplicationID));
	}

	static int GetApplicationScope(size_t ProfileID, size_t ApplicationID)
	{
		return(mn::GetApplicationScope(ProfileID,ApplicationID));
	}

	static String ^ GetApplicationRemoteAddresses(size_t ProfileID, size_t ApplicationID)
	{
		// Perform MikeNet operation
		const char * ReturnData = mn::GetApplicationRemoteAddresses(ProfileID,ApplicationID);

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);

		// Return
		return(Return);
	}

	static int GetApplicationEnabled(size_t ProfileID, size_t ApplicationID)
	{
		return(mn::GetApplicationEnabled(ProfileID,ApplicationID));
	}

	static int SetApplicationName(size_t ProfileID, size_t ApplicationID, String ^ Name)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(Name,ptr);

		// Perform MikeNet operation
		returnMe = mn::SetApplicationName(ProfileID,ApplicationID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int SetApplicationFileName(size_t ProfileID, size_t ApplicationID, String ^ FileName)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(FileName,ptr);

		// Perform MikeNet operation
		returnMe = mn::SetApplicationFileName(ProfileID,ApplicationID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int SetApplicationIPVersion(size_t ProfileID, size_t ApplicationID, int IPVersion)
	{
		return(mn::SetApplicationIPVersion(ProfileID,ApplicationID,IPVersion));
	}

	static int SetApplicationScope(size_t ProfileID, size_t ApplicationID, int Scope)
	{
		return(mn::SetApplicationScope(ProfileID,ApplicationID,Scope));
	}

	static int SetApplicationRemoteAddresses(size_t ProfileID, size_t ApplicationID, String ^ RemoteAddresses)
	{
		int returnMe;
		
		// ConvertStr parameters
		IntPtr ptr;
		char * ParaData = ConvertStr(RemoteAddresses,ptr);

		// Perform MikeNet operation
		returnMe = mn::SetApplicationRemoteAddresses(ProfileID,ApplicationID,ParaData);

		// Cleanup
		CleanupPtr(ptr);

		// Return
		return(returnMe);
	}

	static int SetApplicationEnabled(size_t ProfileID, size_t ApplicationID, bool Enabled)
	{
		return(mn::SetApplicationEnabled(ProfileID, ApplicationID, Enabled));
	}
	*/

	static int StartSound(int NoInputInstances, int NoOutputInstances)
	{
		return(mnSound::StartSound(NoInputInstances,NoOutputInstances));
	}

	static int FinishSound()
	{
		return(mnSound::FinishSound());
	}

	static size_t GetNumInputInstances()
	{
		return(mnSound::GetNumInputInstances());
	}

	static size_t GetNumOutputInstances()
	{
		return(mnSound::GetNumOutputInstances());
	}


	static int FinishOutput(size_t InstanceID)
	{
		return(mnSound::FinishOutput(InstanceID));
	}

	static int PlayData(size_t InstanceID, __int64 Packet)
	{
		return(mnSound::PlayData(InstanceID,Packet));
	}

	static int SetDataVolume(unsigned short BitsPerSample, __int64 Packet, int PercentageChange)
	{
		return(mnSound::SetDataVolume(BitsPerSample,Packet,PercentageChange));
	}

	static int GetDataVolume(unsigned short BitsPerSample, __int64 Packet)
	{
		return(mnSound::GetDataVolume(BitsPerSample,Packet));
	}


	static unsigned short GetOutputChannels(size_t InstanceID)
	{
		return(mnSound::GetOutputChannels(InstanceID));
	}

	static size_t GetOutputSamplesPerSec(size_t InstanceID)
	{
		return(mnSound::GetOutputSamplesPerSec(InstanceID));
	}

	static unsigned short GetOutputBitsPerSample(size_t InstanceID)
	{
		return(mnSound::GetOutputBitsPerSample(InstanceID));
	}

	static size_t GetOutputStoredDataCap(size_t InstanceID)
	{
		return(mnSound::GetOutputStoredDataCap(InstanceID));
	}

	static size_t GetOutputLastAddedCap(size_t InstanceID)
	{
		return(mnSound::GetOutputLastAddedCap(InstanceID));
	}


	static double GetHardwarePlaybackRate(size_t InstanceID)
	{
		return(mnSound::GetHardwarePlaybackRate(InstanceID));
	}

	static double GetHardwarePitch(size_t InstanceID)
	{
		return(mnSound::GetHardwarePitch(InstanceID));
	}

	static unsigned short GetHardwareVolumeLeft(size_t InstanceID)
	{
		return(mnSound::GetHardwareVolumeLeft(InstanceID));
	}

	static unsigned short GetHardwareVolumeRight(size_t InstanceID)
	{
		return(mnSound::GetHardwareVolumeRight(InstanceID));
	}

	static int SetHardwarePlaybackRate(size_t InstanceID, double Rate)
	{
		return(mnSound::SetHardwarePlaybackRate(InstanceID,Rate));
	}

	static int SetHardwarePitch(size_t InstanceID, double Pitch)
	{
		return(mnSound::SetHardwarePitch(InstanceID,Pitch));
	}

	static int SetHardwareVolume(size_t InstanceID, unsigned short Left, unsigned short Right)
	{
		return(mnSound::SetHardwareVolume(InstanceID,Left,Right));
	}


	static int FinishInput(size_t InstanceID)
	{
		return(mnSound::FinishInput(InstanceID));
	}

	static int PauseInput(size_t InstanceID)
	{
		return(mnSound::PauseInput(InstanceID));
	}

	static int UnpauseInput(size_t InstanceID)
	{
		return(mnSound::UnpauseInput(InstanceID));
	}

	static size_t GetInputData(size_t InstanceID, __int64 Packet)
	{
		return(mnSound::GetInputData(InstanceID,Packet));
	}

	static int GetInputUnpaused(size_t InstanceID)
	{
		return(mnSound::GetInputUnpaused(InstanceID));
	}

	static int GetInputPaused(size_t InstanceID)
	{
		return(mnSound::GetInputPaused(InstanceID));
	}

	static unsigned short GetInputChannels(size_t InstanceID)
	{
		return(mnSound::GetInputChannels(InstanceID));
	}

	static size_t GetInputSamplesPerSec(size_t InstanceID)
	{
		return(mnSound::GetInputSamplesPerSec(InstanceID));
	}

	static unsigned short GetInputBitsPerSample(size_t InstanceID)
	{
		return(mnSound::GetInputBitsPerSample(InstanceID));
	}

	static size_t GetInputNoBuffers(size_t InstanceID)
	{
		return(mnSound::GetInputNoBuffers(InstanceID));
	}

	static size_t GetInputTimeLength(size_t InstanceID)
	{
		return(mnSound::GetInputTimePerBuffer(InstanceID));
	}


	static size_t GetNumInputDevices()
	{
		return(mnSound::GetNumInputDevices());
	}

	static size_t GetNumOutputDevices()
	{
		return(mnSound::GetNumOutputDevices());
	}

	static unsigned short GetDeviceManuID(unsigned int DeviceID, bool Output)
	{
		return(mnSound::GetDeviceManuID(DeviceID, Output));
	}

	static unsigned short GetDeviceProductID(unsigned int DeviceID, bool Output)
	{
		return(mnSound::GetDeviceProductID(DeviceID, Output));
	}

	static unsigned char GetDeviceDriverMinorVersion(unsigned int DeviceID, bool Output)
	{
		return(mnSound::GetDeviceDriverMinorVersion(DeviceID, Output));
	}

	static unsigned char GetDeviceDriverMajorVersion(unsigned int DeviceID, bool Output)
	{
		return(mnSound::GetDeviceDriverMajorVersion(DeviceID, Output));
	}

	static String ^ GetDeviceName(unsigned int DeviceID, bool Output)
	{
		// Perform MikeNet operation
		const char * ReturnData = mnSound::GetDeviceName(DeviceID,Output);

		// ConvertStr return
		String ^ Return = ConvertStr((char*)ReturnData);

		// Return
		return(Return);
	}

	static int GetNagleEnabled(size_t Instance)
	{
		return(mn::GetNagleEnabledTCP(Instance));
	}

	/*
	static int GetProfileType(size_t ProfileID)
	{
		return(mn::GetProfileType(ProfileID));
	}

	static int GetProfileAmount()
	{
		return(mn::GetProfileAmount());
	}*/

	static size_t GetStringSize(__int64 packet)
	{
		return(mn::GetStringSize(packet));
	}

	static int SetProfileBufferSizes(__int64 profile, size_t recvSizeTCP, size_t recvSizeUDP)
	{
		return(mn::SetProfileBufferSizes(profile,recvSizeTCP,recvSizeUDP));
	}
	static int SetProfileEnabledUDP(__int64 profile, bool option)
	{
		return(mn::SetProfileEnabledUDP(profile,option));
	}
	static int SetProfileAutoResizeTCP(__int64 profile, bool autoResize)
	{
		return(mn::SetProfileAutoResizeTCP(profile,autoResize));
	}
	static int SetProfileHandshakeEnabled(__int64 profile, bool option)
	{
		return(mn::SetProfileHandshakeEnabled(profile,option));
	}
	static int SetProfileModeTCP(__int64 profile, char modeTCP)
	{
		return(mn::SetProfileModeTCP(profile,modeTCP));
	}
	static int SetProfileGracefulDisconnectEnabled(__int64 profile, bool option)
	{
		return(mn::SetProfileGracefulDisconnectEnabled(profile,option));
	}
	static int SetProfileSendTimeout(__int64 profile, unsigned int  timeoutMilliseconds)
	{
		return(mn::SetProfileSendTimeout(profile,timeoutMilliseconds));
	}
	static int SetProfilePostfixTCP(__int64 profile, __int64 packet)
	{
		return(mn::SetProfilePostfixTCP(profile,packet));
	}
	static int SetProfileNagleEnabledTCP(__int64 profile, bool option)
	{
		return(mn::SetProfileNagleEnabledTCP(profile,option));
	}
	static int SetProfileLocalTCP(__int64 profile, String ^ IP, unsigned short port)
	{
		IntPtr ptrPara;
		char * para = ConvertStr(IP,ptrPara);
		return(mn::SetProfileLocalTCP(profile,para,port));
		CleanupPtr(ptrPara);
	}
	static int SetProfileLocalUDP(__int64 profile, String ^ IP, unsigned short port)
	{
		IntPtr ptrPara;
		char * para = ConvertStr(IP,ptrPara);
		return(mn::SetProfileLocalUDP(profile,para,port));
		CleanupPtr(ptrPara);
	}
	static int SetProfileLocal(__int64 profile, String ^ IP_TCP, unsigned short portTCP, String ^ IP_UDP, unsigned short portUDP)
	{
		IntPtr ptrPara1, ptrPara2;
		char * para1 = ConvertStr(IP_TCP,ptrPara1);
		char * para2 = ConvertStr(IP_UDP,ptrPara2);
		int result = mn::SetProfileLocal(profile,para1,portTCP,para2,portUDP);
		CleanupPtr(ptrPara1);
		CleanupPtr(ptrPara2);

		return result;
	}
	static int SetProfileServerTimeout(__int64 profile, size_t timeoutMilliseconds)
	{
		return(mn::SetProfileServerTimeout(profile,timeoutMilliseconds));
	}
	static int SetProfileModeUDP(__int64 profile, char modeUDP)
	{
		return(mn::SetProfileModeUDP(profile,modeUDP));
	}

	static size_t GetProfileBufferSizeTCP(__int64 profile)
	{
		return(mn::GetProfileBufferSizeTCP(profile));
	}
	static size_t GetProfileBufferSizeUDP(__int64 profile)
	{
		return(mn::GetProfileBufferSizeUDP(profile));
	}
	static int GetProfileEnabledUDP(__int64 profile)
	{
		return(mn::GetProfileEnabledUDP(profile));
	}
	static int GetProfileAutoResizeTCP(__int64 profile)
	{
		return(mn::GetProfileAutoResizeTCP(profile));
	}
	static NetMode::ProtocolMode GetProfileModeTCP(__int64 profile)
	{
		return(mn::GetProfileModeTCP(profile));
	}
	static int GetProfileHandshakeEnabled(__int64 profile)
	{
		return(mn::GetProfileHandshakeEnabled(profile));
	}
	static int GetProfileGracefulDisconnectEnabled(__int64 profile)
	{
		return(mn::GetProfileGracefulDisconnectEnabled(profile));
	}
	static size_t GetProfileSendTimeout(__int64 profile)
	{
		return(mn::GetProfileSendTimeout(profile));
	}
	static int GetProfilePostfixTCP(__int64 profile, __int64 destination)
	{
		return(mn::GetProfilePostfixTCP(profile,destination));
	}
	static int GetProfileNagleEnabledTCP(__int64 profile)
	{
		return(mn::GetProfileNagleEnabledTCP(profile));
	}
	static size_t GetProfileServerTimeout(__int64 profile)
	{
		return(mn::GetProfileServerTimeout(profile));
	}
	static String ^ GetProfileLocalIPTCP(__int64 profile)
	{
		const char * result = mn::GetProfileLocalIPTCP(profile);
		String ^ returnMe = ConvertStr(result);
		return returnMe;
	}
	static unsigned short GetProfileLocalPortTCP(__int64 profile)
	{
		return(mn::GetProfileLocalPortTCP(profile));
	}
	static String ^ GetProfileLocalIPUDP(__int64 profile)
	{
		const char * result = mn::GetProfileLocalIPUDP(profile);
		String ^ returnMe = ConvertStr(result);
		return returnMe;
	}
	static unsigned short GetProfileLocalPortUDP(__int64 profile)	
	{
		return(mn::GetProfileLocalPortUDP(profile));
	}
	static NetMode::ProtocolMode GetProfileModeUDP( __int64 profile )
	{
		return(mn::GetProfileModeUDP(profile));
	}

	static __int64 CreateInstanceProfile()
	{
		return mn::CreateInstanceProfile();
	}
	static __int64 CreateInstanceProfileFrom(__int64 profile)
	{
		return mn::CreateInstanceProfileFrom(profile);
	}
	static int DeleteInstanceProfile(__int64 profile)
	{
		return mn::DeleteInstanceProfile(profile);
	}
	static __int64 AssignInstanceProfile(__int64 dest, __int64 source)
	{
		return mn::AssignInstanceProfile(dest,source);
	}
	static int CompareInstanceProfile(__int64 profile1, __int64 profile2)
	{
		return mn::CompareInstanceProfile(profile1,profile2);
	}

	static bool GetConnecting(size_t instanceID)
	{
		return mn::GetConnecting(instanceID);
	}



	static __int64 CreateSoundProfile()
	{
		return(mnSound::CreateSoundProfile());
	}
	static int DeleteSoundProfile(__int64 profile)
	{
		return(mnSound::DeleteSoundProfile(profile));
	}

	static int SetSoundProfile(__int64 profile, DWORD khz, WORD bitsPerSample, WORD channels)
	{
		return(mnSound::SetSoundProfile(profile,khz,bitsPerSample,channels));
	}
	static int SetSoundProfileHighQuality(__int64 profile)
	{
		return(mnSound::SetSoundProfileHighQuality(profile));
	}
	static int SetSoundProfileMediumQuality(__int64 profile)
	{
		return(mnSound::SetSoundProfileMediumQuality(profile));
	}
	static int SetSoundProfileLowQuality(__int64 profile)
	{
		return(mnSound::SetSoundProfileLowQuality(profile));
	}
	static WORD GetSoundProfileChannels(__int64 profile)
	{
		return(mnSound::GetSoundProfileChannels(profile));
	}
	static DWORD GetSoundProfileSamplesPerSecond(__int64 profile)
	{
		return(mnSound::GetSoundProfileSamplesPerSecond(profile));
	}
	static WORD GetSoundProfileBitsPerSample(__int64 profile)
	{
		return(mnSound::GetSoundProfileBitsPerSample(profile));
	}
	
	static int StartOutput(size_t instanceID, unsigned int outputDeviceID, size_t msStoredDataCap, size_t timeGapCap, __int64 soundFormat)
	{
		return(mnSound::StartOutput(instanceID,outputDeviceID,msStoredDataCap,timeGapCap,soundFormat));
	}

	static int StartInput(size_t instanceID, unsigned int inputDeviceID, size_t numBuffers, size_t buffTimeLength, __int64 soundFormat)
	{
		return(mnSound::StartInput(instanceID,inputDeviceID,numBuffers,buffTimeLength,soundFormat));
	}

	static int GetDeviceFormatSupport(unsigned int deviceID, bool output, DWORD khz, WORD bits, WORD channels)
	{
		return(mnSound::GetDeviceFormatSupport(deviceID,output,khz,bits,channels));
	}
	static unsigned short GetDeviceMaxChannels(unsigned int deviceID, bool output)
	{
		return(mnSound::GetDeviceMaxChannels(deviceID,output));
	}
	static int GetIndependentVolumeControlSupported(unsigned int outputDeviceID)
	{
		return(mnSound::GetIndependentVolumeControlSupported(outputDeviceID));
	}
	static int GetVolumeControlSupported(unsigned int outputDeviceID)
	{
		return(mnSound::GetVolumeControlSupported(outputDeviceID));
	}
	static int GetSampleAccurate(unsigned int outputDeviceID)
	{
		return(mnSound::GetSampleAccurate(outputDeviceID));
	}
	static int GetPlaybackRateControlSupported(unsigned int outputDeviceID)
	{
		return(mnSound::GetPlaybackRateControlSupported(outputDeviceID));
	}
	static int GetPitchControlSupported(unsigned int outputDeviceID)
	{
		return(mnSound::GetPitchControlSupported(outputDeviceID));
	}

	static int GetProfileDecryptKeyLoadedUDP(__int64 profile)
	{
		return(mn::GetProfileDecryptKeyLoadedUDP(profile));
	}
	static __int64 GetProfileDecryptKeyUDP(__int64 profile)
	{
		return(mn::GetProfileDecryptKeyUDP(profile));
	}
	static int SetProfileDecryptKeyUDP(__int64 profile, __int64 key)
	{
		return(mn::SetProfileDecryptKeyUDP(profile,key));
	}
	static int SetProfileReusableUDP(__int64 profile, bool option)
	{
		return(mn::SetProfileReusableUDP(profile,option));
	}
	static int GetProfileReusableUDP(__int64 profile)
	{
		return(mn::GetProfileReusableUDP(profile));
	}
	static size_t GetProfileNumOperationsUDP(__int64 profile)
	{
		return(mn::GetProfileNumOperationsUDP(profile));
	}
	static int SetProfileNumOperationsUDP(__int64 profile, size_t numOperations)
	{
		return(mn::SetProfileNumOperationsUDP(profile,numOperations));
	}
};

#endif