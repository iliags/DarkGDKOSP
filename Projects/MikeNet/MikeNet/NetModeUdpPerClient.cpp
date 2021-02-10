#include "FullInclude.h"

/** 
 * @brief Constructor.
 *
 * @param recvSize Maximum size of UDP packet that can be received.
 * @param numClients Number of clients that object needs to store received packets for.
 * @param numOperations Number of operations per client that object needs to store received packets for, ignored if @a perOperation is true.
 * @param perOperation If true operation ID will be extracted from packet and object is used in NetMode::UDP_PER_CLIENT_PER_OPERATION UDP mode.
 * @param decryptKey Ignored if NULL, otherwise represents memory address of EncryptKey object used to decrypt incoming packets before reading them. Contents
 * of @a decryptKey is copied.
 */
NetModeUdpPerClient::NetModeUdpPerClient(size_t recvSize, size_t numClients, size_t numOperations, bool perOperation, const EncryptKey * decryptKey) : NetModeUdp()
{
	this->perOperation = perOperation;

	if(decryptKey == NULL)
	{
		this->decryptKey = NULL;
	}
	else
	{
		this->decryptKey = new (nothrow) EncryptKey(*decryptKey);
		Utility::DynamicAllocCheck(this->decryptKey,__LINE__,__FILE__);
	}
	
	if(perOperation == false)
	{
		numOperations = 1;
	}

	// First dimension
	packetStore.ResizeAllocate(numClients+1);

	for(size_t x = 0;x<=numClients;x++)
	{
		// Second dimension
		packetStore[x].ResizeAllocate(numOperations);

		for(size_t y = 0;y<numOperations;y++)
		{
			packetStore[x][y].SetMemorySize(recvSize);
		}
	}
}

/**
 * @brief Copy constructor / assignment operator helper method.
 *
 * @param	copyMe	Object to copy into this object.
 */
void NetModeUdpPerClient::Copy(const NetModeUdpPerClient & copyMe)
{
	this->packetStore = copyMe.packetStore;
	this->perOperation = copyMe.perOperation;

	if(copyMe.decryptKey == NULL)
	{
		this->decryptKey = NULL;
	}
	else
	{
		this->decryptKey = new (nothrow) EncryptKey(*copyMe.decryptKey);
		Utility::DynamicAllocCheck(this->decryptKey,__LINE__,__FILE__);
	}
}

/**
 * @brief Deep copy constructor.
 *
 * @param	copyMe	Object to copy.
 */
NetModeUdpPerClient::NetModeUdpPerClient(const NetModeUdpPerClient & copyMe) : NetModeUdp(copyMe)
{
	Copy(copyMe);
}

/**
 * @brief Deep assignment operator.
 *
 * @param	copyMe	Object to copy. 
 * @return	reference to this object.
 */
NetModeUdpPerClient & NetModeUdpPerClient::operator= (const NetModeUdpPerClient & copyMe)
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
NetModeUdpPerClient * NetModeUdpPerClient::Clone() const
{
	NetModeUdpPerClient * clone = new (nothrow) NetModeUdpPerClient(*this);
	Utility::DynamicAllocCheck(clone,__LINE__,__FILE__);

	return clone;
}

/**
 * @brief Resets data of specified client.
 *
 * @param clientID ID of client to use.
 */
void NetModeUdpPerClient::Reset(size_t clientID)
{
	_ErrorException((clientID >= packetStore.Size()),"resetting a UDP packet store, client ID is out of bounds",0,__LINE__,__FILE__);

	for(size_t n = 0;n<packetStore[clientID].Size();n++)
	{
		packetStore[clientID][n].Clear();
	}
}

/**
 * @brief Reset data of all clients.
 */
void NetModeUdpPerClient::Reset()
{
	for(size_t n = 0;n<packetStore.Size();n++)
	{
		Reset(n);
	}
}

/** @brief Destructor. */
NetModeUdpPerClient::~NetModeUdpPerClient()
{
	delete decryptKey;
}

/**
 * @brief Deals with a complete packet.
 *
 * The class deals with it in one of two ways:
 * - Passes it to a user function specified by @a udpRecvFunc parameter.
 * - If no user function is defined then it is put into a queue to be retrieved using GetPacketFromStore().
 *
 * @note This method is not called by DealWithData() but is included for completion.
 *
 * @warning If the packet is passed to a user function this is done synchronously, so this method
 * will not return until the user function returns.
 *
 * @param [in] completePacket The complete packet that should be dealt with. The packet is now owned by this object and should not be referenced elsewhere.
 * @param [in] udpRecvFunc Method will be executed and data not added to the queue if this is non NULL.
 */
void NetModeUdpPerClient::PacketDone(Packet * completePacket, NetSocket::RecvFunc udpRecvFunc)
{
	size_t clientID = completePacket->GetClientFrom();
	size_t operationID = completePacket->GetOperation();

	_ErrorException((completePacket == NULL),"queuing a UDP packet, completePacket parameter cannot be NULL",0,__LINE__,__FILE__);
	_ErrorException((clientID >= packetStore.Size()),"queuing a UDP packet; the client ID is invalid",0,__LINE__,__FILE__);
	_ErrorException((operationID >= packetStore[clientID].Size()),"queuing a UDP packet; the operation ID is invalid",0,__LINE__,__FILE__);

	if(udpRecvFunc == NULL)
	{
		packetStore[clientID][operationID] = *completePacket;
	}
	else
	{
		udpRecvFunc(*completePacket);
	}

	delete completePacket;
}

/**
 * @brief Deals with newly received data.
 *
 * If @a clientID is 0 then an integer of size_t type will be extracted from the
 * data and that will be used to determine what client ID this packet refers to.\n\n
 *
 * Afterwards, if 'per operation' is enabled then a further integer of size_t type
 * will be extracted and its data will indicate the operation ID that the packet refers to.
 *
 * @param buffer Newly received data.
 * @param completionBytes Number of bytes of new data stored in @a buffer.
 * @param [in] udpRecvFunc Method will be executed and data not added to the queue if this is non NULL.
 * @param instanceID Instance that data was received on.
 * @param clientID ID of client that data was received from, set to 0 if not applicable.
 * If 0 then the client ID will be extracted from the packet directly.
 */
void NetModeUdpPerClient::DealWithData(const WSABUF & buffer, size_t completionBytes, NetSocket::RecvFunc udpRecvFunc, size_t clientID, size_t instanceID)
{
	// Read buffer directly using Packet object
	Packet * packetBuffer = new (nothrow) Packet();
	Utility::DynamicAllocCheck(packetBuffer,__LINE__,__FILE__);

	packetBuffer->SetDataPtr(buffer.buf,buffer.len,completionBytes);

	// Get clock value to determine age of packet
	// Note: clock value is never encrypted
	size_t clock = packetBuffer->GetSizeT();

	// Ignore connection packets
	// Connection packets have a prefix of 0
	if(clock == 0)
	{
		return;
	}

	// If mnDecryptUDP was used, decrypt using preset key
	if(decryptKey != NULL)
	{
		Packet::DecryptWSABUF(buffer, completionBytes - packetBuffer->GetCursor(), packetBuffer->GetCursor(), decryptKey);
	}

	// Extract client ID from packet
	if(clientID == 0)
	{
		// Client ID can be 0 here, means that data was received from server in client state
		clientID = packetBuffer->GetSizeT();
		_ErrorException((clientID >= packetStore.Size()),"dealing with an incoming UDP packet on the client side; the client ID is invalid",0,__LINE__,__FILE__);
	}

	// Operation ID, always 0 in 'per client' UDP mode
	size_t operationID = 0;

	if(perOperation == true)
	{
		// Operation ID
		operationID = packetBuffer->GetSizeT();
		_ErrorException((operationID >= packetStore[clientID].Size()),"dealing with an incoming UDP packet; the operation ID is invalid",0,__LINE__,__FILE__);
	}

	// Ignore old packets
	if(clock <= packetStore[clientID][operationID].GetAge())
	{
		/* If the current clock value is vastly different to the last
		 * clock value, then it is likely that the maximum for
		 * the clock value was reached, and so it looped back round
		 * to 0 */
		if(packetStore[clientID][operationID].GetAge() - clock > packetStore[clientID][operationID].GetAge() / 2)
		{
			packetStore[clientID][operationID].SetAge(0);
		}
		else
		{
			delete packetBuffer;
			return;
		}
	}

	// Save packet
	packetBuffer->SetInstance(instanceID);
	packetBuffer->SetAge(clock);
	packetBuffer->SetClientFrom(clientID);
	packetBuffer->SetOperation(operationID);

	PacketDone(packetBuffer,udpRecvFunc); // packetBuffer is cleaned up by this method
}

/**
 * @brief Determines the number of packets in the specified packet store. 
 *
 * @param clientID ID of client to use.
 * @param operationID Ignored (optional, default = 0).
 *
 * @return 1 if a newly received packet exists in the packet queue.
 * @return 0 if no new packet exists.
 */
size_t NetModeUdpPerClient::GetPacketAmount(size_t clientID, size_t operationID) const
{
	if(perOperation == false)
	{
		operationID = 0;
	}

	_ErrorException((clientID >= packetStore.Size()),"determining if a new packet exists in a UDP packet store; the client ID is invalid",0,__LINE__,__FILE__);
	_ErrorException((operationID >= packetStore[clientID].Size()),"determining if a new packet exists in a UDP packet store; the operation ID is invalid",0,__LINE__,__FILE__);

	if(packetStore[clientID][operationID].GetUsedSize() == 0)
	{
		return(0);
	}
	else
	{
		return(1);
	}
}

/**
 * @brief Retrieves a packet from the specified packet store.
 *
 * @param [out] destination Destination to copy packet into. 
 * @param clientID ID of client to use.
 * @param operationID ID of operation to use, may be ignored.
 *
 * @return 1 because there will always be only one packet in the store.
 */
size_t NetModeUdpPerClient::GetPacketFromStore(Packet * destination, size_t clientID, size_t operationID)
{
	if(perOperation == false)
	{
		operationID = 0;
	}

	_ErrorException((destination == NULL),"retrieving a UDP packet from a complete packet store, destination must not be NULL",0,__LINE__,__FILE__);
	_ErrorException((clientID >= packetStore.Size()),"transferring a UDP packet to the user; the client ID is invalid",0,__LINE__,__FILE__);
	_ErrorException((operationID >= packetStore[clientID].Size()),"transferring a UDP packet to the user; the operation ID is invalid",0,__LINE__,__FILE__);

	if(packetStore[clientID][operationID].GetUsedSize() > 0)
	{
		*destination = packetStore[clientID][operationID];

		// Do not used clear, because GetAge() must still return age
		// of last received packet!
		packetStore[clientID][operationID].SetUsedSize(0);

		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief Retrieves the clock() value for the currently stored packet for the specified client and operation.
 *
 * @param clientID ID of client to use.
 * @param operationID Operation ID of operation to use, ignored if NetModeUdpPerClient::perOperation is true. 
 *
 * @return age of specified packet.
 */
clock_t NetModeUdpPerClient::GetRecvCounter(size_t clientID, size_t operationID)
{
	if(perOperation == false)
	{
		operationID = 0;
	}

	_ErrorException((clientID >= packetStore.Size()),"retrieving the receive counter of a UDP packet store; the client ID is invalid",0,__LINE__,__FILE__);
	_ErrorException((operationID >= packetStore[clientID].Size()),"retrieving the receive counter of a UDP packet store; the operation ID is invalid",0,__LINE__,__FILE__);

	return packetStore[clientID][operationID].GetAge();
}

/**
 * @brief Manually changes the stored counter value for the specified client and operation.
 *
 * @param clientID ID of client to use.
 * @param operationID Operation ID of operation to use, ignored if NetModeUdpPerClient::perOperation is true. 
 * @param newCounter New counter value.
 */
void NetModeUdpPerClient::SetRecvCounter(size_t clientID, size_t operationID, clock_t newCounter)
{
	if(perOperation == false)
	{
		operationID = 0;
	}

	_ErrorException((clientID >= packetStore.Size()),"changing the receive counter of a UDP packet store; the client ID is invalid",0,__LINE__,__FILE__);
	_ErrorException((operationID >= packetStore[clientID].Size()),"changing the receive counter of a UDP packet store; the operation ID is invalid",0,__LINE__,__FILE__);

	packetStore[clientID][operationID].SetAge(newCounter);
}

/**
 * @brief Generates a NetSend object.
 *
 * @param packet Packet to send.
 * @param block True if sending should be synchronous, false if sending should be asynchronous.
 *
 * @return a send object.
 */
NetSend * NetModeUdpPerClient::GetSendObject(const Packet * packet, bool block)
{
	Packet aux;
	aux.AddSizeT((size_t)clock());

	NetSend * sendObject = new (nothrow) NetSendPrefix(packet,block,aux);
	Utility::DynamicAllocCheck(sendObject,__LINE__,__FILE__);
	
	return sendObject;
}

/**
 * @brief Retrieves the protocol mode in use.
 *
 * @return if NetModeUdpPerClient::perOperation is true then NetMode::UDP_PER_CLIENT_PER_OPERATION.
 * @return if NetModeUdpPerClient::perOperation is false then NetMode::UDP_PER_CLIENT.
 */
NetMode::ProtocolMode NetModeUdpPerClient::GetProtocolMode() const
{
	if(perOperation == true)
	{
		return NetMode::UDP_PER_CLIENT_PER_OPERATION;
	}
	else
	{
		return NetMode::UDP_PER_CLIENT;
	}
}

/**
 * @brief Retrieves the number of operations that this object can manage.
 *
 * @return if NetModeUdpPerClient::perOperation is true then the number of operations that this object can manage.
 * @return if NetModeUdpPerClient::perOperation is false then 1.
 */
size_t NetModeUdpPerClient::GetNumOperations() const
{
	if(GetNumClients() > 0)
	{
		return packetStore[0].Size();
	}
	else
	{
		return 1;
	}
}

/**
 * @brief Retrieves the number of clients that this object can manage.
 *
 * @return the number of clients that this object can manage.
 */
size_t NetModeUdpPerClient::GetNumClients() const
{
	return packetStore.Size()-1; // -1 because we did +1 for 0 index
}

/**
 * @brief Tests class.
 *
 * @return true if no problems while testing were found, false if not.
 * Note that not all tests automatically check for problems so some tests
 * require manual verification.
 */
bool NetModeUdpPerClient::TestClass()
{
	cout << "Testing NetModeUdpPerClient class...\n";
	bool problem = false;
	Packet destination;
	char * str = "hello, this is a packet! HURRAY!";

	{
		NetModeUdpPerClient obj(1024,10,10,false,NULL);

		if(obj.GetProtocolMode() != NetMode::UDP_PER_CLIENT)
		{
			cout << "GetProtocolMode is bad\n";
			problem = true;
		}
		else
		{
			cout << "GetProtocolMode is good\n";
		}

		if(obj.GetNumOperations() != 1)
		{
			cout << "GetNumOperations is bad\n";
			problem = true;
		}
		else
		{
			cout << "GetNumOperations is good\n";
		}

		if(obj.GetNumClients() != 10)
		{
			cout << "GetNumClients is bad\n";
			problem = true;
		}
		else
		{
			cout << "GetNumClients is good\n";
		}

		cout << "Simulating client state in NetMode::UDP_PER_CLIENT..\n";
		{
			Packet packet;

			packet.AddSizeT(0); // Padding, this represents the age of the packet and is changed by _HelperTestClass
	
			size_t clientID = 10;
			packet.AddSizeT(clientID);

			packet.AddStringC(str,0,false);

			if(_HelperTestClass(obj,packet,str,0,clientID,0) == false)
			{
				problem = true;
			}
		}

		cout << "Simulating server state in NetMode::UDP_PER_CLIENT..\n";
		{
			Packet packet;

			packet.AddSizeT(0); // Padding, this represents the age of the packet and is changed by _HelperTestClass
	
			packet.AddStringC(str,0,false);

			if(_HelperTestClass(obj,packet,str,6,6,0) == false)
			{
				problem = true;
			}
		}
	}

	{
		NetModeUdpPerClient obj(1024,10,7,true,NULL);

		if(obj.GetProtocolMode() != NetMode::UDP_PER_CLIENT_PER_OPERATION)
		{
			cout << "GetProtocolMode is bad\n";
			problem = true;
		}
		else
		{
			cout << "GetProtocolMode is good\n";
		}

		if(obj.GetNumOperations() != 7)
		{
			cout << "GetNumOperations is bad\n";
			problem = true;
		}
		else
		{
			cout << "GetNumOperations is good\n";
		}

		if(obj.GetNumClients() != 10)
		{
			cout << "GetNumClients is bad\n";
			problem = true;
		}
		else
		{
			cout << "GetNumClients is good\n";
		}

		cout << "Simulating client state in NetMode::UDP_PER_CLIENT_PER_OPERATION..\n";
		{
			Packet packet;

			packet.AddSizeT(0); // Padding, this represents the age of the packet and is changed by _HelperTestClass
	
			size_t clientID = 10;
			packet.AddSizeT(clientID);

			size_t operationID = 6;
			packet.AddSizeT(operationID);

			packet.AddStringC(str,0,false);

			if(_HelperTestClass(obj,packet,str,0,clientID,operationID) == false)
			{
				problem = true;
			}
		}

		cout << "Simulating server state in NetMode::UDP_PER_CLIENT_PER_OPERATION..\n";
		{
			Packet packet;

			packet.AddSizeT(0); // Padding, this represents the age of the packet and is changed by _HelperTestClass
			packet.AddSizeT(0); // operation ID

			packet.AddStringC(str,0,false);

			if(_HelperTestClass(obj,packet,str,6,6,0) == false)
			{
				problem = true;
			}
		}
	}


	cout << "\n\n";
	return !problem;
}
