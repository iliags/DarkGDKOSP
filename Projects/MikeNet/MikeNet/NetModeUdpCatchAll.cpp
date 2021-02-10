#include "FullInclude.h"

/**
 * @brief Constructor.
 *
 * @param numClients Number of clients that object should store packets for.
 */
NetModeUdpCatchAll::NetModeUdpCatchAll(size_t numClients)
{
	packetStore.ResizeAllocate(numClients+1); // +1 because clients are 1 indexed, not 0.
}

/**
 * @brief Copy constructor / assignment operator helper method.
 *
 * @param	copyMe	Object to copy into this object.
 */
void NetModeUdpCatchAll::Copy(const NetModeUdpCatchAll & copyMe)
{
	this->packetStore = copyMe.packetStore;
}

/**
 * @brief Deep copy constructor.
 *
 * @param	copyMe	Object to copy.
 */
NetModeUdpCatchAll::NetModeUdpCatchAll(const NetModeUdpCatchAll & copyMe) : NetModeUdp(copyMe)
{
	Copy(copyMe);
}

/**
 * @brief Deep assignment operator.
 *
 * @param	copyMe	Object to copy. 
 * @return	reference to this object.
 */
NetModeUdpCatchAll & NetModeUdpCatchAll::operator= (const NetModeUdpCatchAll & copyMe)
{
	NetModeUdp::operator=(copyMe);
	Copy(copyMe);
	return *this;
}

/** 
 * @brief Retrieves a deep copy of this object.
 *
 * @return a deep copy of this object.
 */
NetModeUdpCatchAll * NetModeUdpCatchAll::Clone() const
{
	NetModeUdpCatchAll * clone = new (nothrow) NetModeUdpCatchAll(*this);
	Utility::DynamicAllocCheck(clone,__LINE__,__FILE__);

	return clone;
}

/**
 * @brief Destructor.
 */
NetModeUdpCatchAll::~NetModeUdpCatchAll()
{

}

/**
 * @brief Deals with a complete packet.
 *
 * The class deals with it in one of two ways:
 * - Passes it to a user function specified by @a udpRecvFunc parameter.
 * - If no user function is defined then it is put into a queue to be retrieved using GetPacketFromStore().
 *
 * @warning If the packet is passed to a user function this is done synchronously, so this method
 * will not return until the user function returns.
 *
 * @param [in] completePacket The complete packet that should be dealt with. The packet is now owned by this object and should not be referenced elsewhere.
 * @param [in] udpRecvFunc Method will be executed and data not added to the queue if this is non NULL.
 */
void NetModeUdpCatchAll::PacketDone(Packet * completePacket, NetSocket::RecvFunc udpRecvFunc)
{
	_ErrorException((completePacket == NULL),"queuing a UDP packet, completePacket parameter cannot be NULL",0,__LINE__,__FILE__);
	ValidateClientID(completePacket->GetClientFrom());

	if(udpRecvFunc == NULL)
	{
		packetStore[completePacket->GetClientFrom()].Add(completePacket);
	}
	else
	{
		udpRecvFunc(*completePacket);
		delete completePacket;
	}
}


/**
 * @brief Resets data of specified client.
 *
 * @param clientID ID of client to use.
 */
void NetModeUdpCatchAll::Reset(size_t clientID)
{
	ValidateClientID(clientID);

	packetStore[clientID].Clear();
}

/**
 * @brief Reset data of all clients.
 */
void NetModeUdpCatchAll::Reset()
{
	for(size_t n = 0;n<packetStore.Size();n++)
	{
		Reset(n);
	}
}

/**
 * @brief Deals with newly received data.
 *
 * @param buffer Newly received data.
 * @param completionBytes Number of bytes of new data stored in @a buffer.
 * @param [in] udpRecvFunc Method will be executed and data not added to the queue if this is non NULL.
 * @param instanceID Instance that data was received on.
 * @param clientID ID of client that data was received from, set to 0 if not applicable.
 */
void NetModeUdpCatchAll::DealWithData(const WSABUF & buffer, size_t completionBytes, NetSocket::RecvFunc udpRecvFunc, size_t clientID, size_t instanceID)
{
	Packet * newPacket = new (nothrow) Packet(buffer, completionBytes, 0, clientID, 0, instanceID, 0);
	Utility::DynamicAllocCheck(newPacket,__LINE__,__FILE__);

	PacketDone(newPacket, udpRecvFunc);
}

/**
 * @brief Determines the number of packets in the specified packet store. 
 *
 * @param clientID ID of client to use.
 * @param operationID Ignored (optional, default = 0).
 *
 * @return the number of packets in the packet store.
 */
size_t NetModeUdpCatchAll::GetPacketAmount(size_t clientID, size_t operationID) const
{
	ValidateClientID(clientID);

	return packetStore[clientID].Size();
}

/**
 * @brief Retrieves a packet from the specified packet store.
 *
 * @param [out] destination Destination to copy packet into. 
 * @param clientID ID of client to use.
 * @param operationID Ignored (optional, default = 0).
 *
 * @return the number of packets in packet queue before this method was called.
 */
size_t NetModeUdpCatchAll::GetPacketFromStore(Packet * destination, size_t clientID, size_t operationID)
{
	_ErrorException((destination == NULL),"retrieving a UDP packet from a complete packet store, destination must not be NULL",0,__LINE__,__FILE__);
	ValidateClientID(clientID);

	size_t returnMe = packetStore[clientID].Get(destination);

	return returnMe;
}


/**
 * @brief Generates a NetSend object.
 *
 * @param packet Packet to send.
 * @param block True if sending should be synchronous, false if sending should be asynchronous.
 *
 * @return a send object.
 */
NetSend * NetModeUdpCatchAll::GetSendObject(const Packet * packet, bool block)
{
	NetSend * sendObject = new (nothrow) NetSendRaw(packet,block);
	Utility::DynamicAllocCheck(sendObject,__LINE__,__FILE__);
	
	return sendObject;
}

/**
 * @brief Retrieves the protocol mode in use.
 *
 * @return NetMode::UDP_CATCH_ALL.
 */
NetMode::ProtocolMode NetModeUdpCatchAll::GetProtocolMode() const
{
	return NetMode::UDP_CATCH_ALL;
}

/**
 * @brief Retrieves the number of operations that this object can manage.
 *
 * @return 1 because operations are not valid for this object.
 */
size_t NetModeUdpCatchAll::GetNumOperations() const
{
	return 1;
}

/**
 * @brief Retrieves the number of clients that this object can manage.
 *
 * @return the number of clients that this object can manage.
 */
size_t NetModeUdpCatchAll::GetNumClients() const
{
	return packetStore.Size()-1; // -1 because we did +1 in constructor.
}

/**
 * @brief	Throws an exception if an invalid client ID is specified.
 *
 * @param	clientID	Client ID to check.
 *
 * @throws ErrorReport If @a clientID is invalid.
 */
void NetModeUdpCatchAll::ValidateClientID(size_t clientID) const
{
	_ErrorException((clientID >= packetStore.Size()),"performing a client related operation; the client ID is invalid",0,__LINE__,__FILE__);
}

/**
 * @brief Tests class.
 *
 * @return true if no problems while testing were found, false if not.
 * Note that not all tests automatically check for problems so some tests
 * require manual verification.
 */
bool NetModeUdpCatchAll::TestClass()
{
	cout << "Testing NetModeUdpCatchAll class...\n";
	bool problem = false;

	NetModeUdpCatchAll obj(10);
	
	if(obj.GetNumClients() != 10)
	{
		cout << "Constructor or GetNumClients is bad\n";
		problem = true;
	}
	else
	{
		cout << "Constructor and GetNumClients are good\n";
	}

	if(obj.GetProtocolMode() != NetMode::UDP_CATCH_ALL)
	{
		cout << "GetProtocolMode is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetProtocolMode is good\n";
	}

	char * str = "hello world, I am a packet!";
	Packet packet(str);
	WSABUF buffer;
	packet.PtrIntoWSABUF(buffer);
	obj.DealWithData(buffer,packet.GetUsedSize(),NULL,3,1);
	
	if(obj.GetPacketAmount(3) != 1)
	{
		cout << "DealWithData is bad\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good\n";
	}

	Packet destination;
	size_t result = obj.GetPacketFromStore(&destination,3);
	if(result != 1 || destination != str)
	{
		cout << "DealWithData is bad (packet 1)\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good (packet 1)\n";
	}

	packet = "";
	packet.PtrIntoWSABUF(buffer);
	obj.DealWithData(buffer,packet.GetUsedSize(),NULL,0,0);

	result = obj.GetPacketFromStore(&destination,0);
	if(result != 1 || destination != "")
	{
		cout << "DealWithData is bad (packet 2)\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good (packet 2)\n";
	}

	cout << "\n\n";
	return !problem;
}
