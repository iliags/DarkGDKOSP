#include "FullInclude.h"


/**
 * @brief Constructor.
 *
 * @param partialPacketSize Maximum amount of partial data (data that does not make up a full packet) that can be stored (in bytes).
 * Packets larger than this size cannot be received without memory reallocation.
 * @param autoResize If true then if a packet larger than @a partialPacketSize is received then more memory will be automatically allocated so that it can be received. \n
 * If false then an error will be thrown if a packet larger than @a partialPacketSize is received.
 */
NetModeTcp::NetModeTcp(size_t partialPacketSize, bool autoResize) : autoResize(autoResize)
{
	partialPacket.SetMemorySize(partialPacketSize);
}

/**
 * @brief Deep copy / assignment operator helper.
 *
 * @param	copyMe	Object to copy.
 */
void NetModeTcp::Copy(const NetModeTcp & copyMe)
{
	this->autoResize = copyMe.autoResize;
	this->partialPacket.SetMemorySize(copyMe.partialPacket.GetMemorySize()); // Memory size is not copied automatically
	this->partialPacket = copyMe.partialPacket;
	this->packetStore = copyMe.packetStore;
}

/**
 * @brief Deep copy constructor.
 *
 * @param	copyMe	Object to copy.
 */
NetModeTcp::NetModeTcp(const NetModeTcp & copyMe)
{
	Copy(copyMe);
}

/**
 * @brief Deep assignment operator.
 *
 * @param	copyMe	Object to copy. 
 * @return	reference to this object.
 */
NetModeTcp & NetModeTcp::operator= (const NetModeTcp & copyMe)
{
	Copy(copyMe);
	return *this;
}

/**
 * @brief Destructor.
 */
NetModeTcp::~NetModeTcp()
{
	// Nothing to do, object destructors do everything
}

/**
 * @brief Erases all stored TCP data.
 *
 * The object will now be in the same state as if it were newly constructed.
 */
void NetModeTcp::ClearData()
{
	ClearPacketStore();
	partialPacket.Clear();
}

/**
 * @brief Clears only the complete packet store, completely emptying it.
 */
void NetModeTcp::ClearPacketStore()
{
	packetStore.Clear();
}

/**
 * @brief Retrieves the number of fully received packets in the complete packet store.
 *
 * @param clientID Ignored (optional, default = 0).
 * @param operationID Ignored (optional, default = 0).
 *
 * @return the number of fully received packets in the packet store. 
 */
size_t NetModeTcp::GetPacketAmount( size_t clientID, size_t operationID ) const
{
	return packetStore.Size();
}

/**
 * @brief Changes the the size of the largest packet that can be received.
 *
 * Packets larger than this will require an increase in memory size or
 * an exception will be thrown.
 *
 * @note Attempting to decrease the size may not be effective. If data exists in the buffer
 * this will not be discarded. The buffer will decrease as much as possible without discarding data.
 *
 * @param newSize New size.
 */
void NetModeTcp::ChangeMaxPacketSize(size_t newSize)
{
	partialPacket.ChangeMemorySize(newSize);
}

/**
 * @brief Enables or disables the 'auto resize' option.
 *
 * @param paraAutoResize Value to set autoResize to. \n
 * When true, if a packet larger than the maximum TCP packet
 * size is received then the max size will be increased silently.\n
 * When false, if a packet larger than the maximum TCP packet
 * size is received then an exception will be thrown.
 */
void NetModeTcp::SetAutoResize(bool paraAutoResize)
{
	autoResize.Set(paraAutoResize);
}

/**
 * @brief Determines whether the 'auto resize' option is enabled.
 *
 * @return when true, if a packet larger than the maximum TCP packet
 * size is received then the max size will be increased silently.\n
 * @return when false, if a packet larger than the maximum TCP packet
 * size is received then an exception will be thrown.
 */
bool NetModeTcp::GetAutoResize() const
{
	return autoResize.Get();
}

/**
 * @brief Deals with a complete packet.
 *
 * The class deals with it in one of two ways:
 * - Passes it to a user function specified by @a tcpRecvFunc parameter.
 * - If no user function is defined then it is put into a queue to be retrieved using GetPacketFromStore().
 *
 * A special case exists for an instance in client state and handshaking. In this case the
 * packet is always added to the packet queue. This is necessary because the handshaking thread
 * needs to receive TCP data. The user of this method must ensure @a tcpRecvFunc is NULL in this case.
 *
 * @warning If the packet is passed to a user function this is done synchronously, so this method
 * will not return until the user function returns.
 *
 * @param [in] completePacket The complete packet that should be dealt with. The packet is now owned by this object and should not be referenced elsewhere.
 * @param [in] tcpRecvFunc Method will be executed and data not added to the queue if this is non NULL.
 */
void NetModeTcp::PacketDone(Packet * completePacket, NetSocket::RecvFunc tcpRecvFunc)
{
	if(tcpRecvFunc == NULL)
	{
		// Add the new packet to the TCP packet user buffer
		packetStore.Add(completePacket);
	}
	else
	{
		// Execute user function to deal with packet
		(*tcpRecvFunc)(*completePacket);
		delete completePacket;
	}
}

/**
 * @brief Retrieves the size of the largest packet that can be received without a change in memory size.
 *
 * @return	the size of the largest packet that can be received, packets larger than this
 * will require an increase in memory size or an exception will be thrown.
 */
size_t NetModeTcp::GetMaxPacketSize() const
{
	return partialPacket.GetMemorySize();
}

/**
 * @brief Determines the amount of the oldest partial packet that
 * has been received in bytes.
 *
 * @return the current size of the partial packet being received.
 * i.e. The number of bytes of the packet that have been received.
 */
size_t NetModeTcp::GetPartialPacketCurrentSize() const
{
	return partialPacket.GetUsedSize();
}

/**
 * @brief Retrieves a complete packet from the packet store.
 *
 * @param [out] destination Destination to copy into.
 * @param clientID Ignored (optional, default = 0).
 * @param operationID Ignored (optional, default = 0).
 *
 * @return number of packets in packet store before this method call.
 */
size_t NetModeTcp::GetPacketFromStore( Packet * destination, size_t clientID, size_t operationID )
{
	_ErrorException((destination == NULL),"retrieving a packet from the complete packet store, destination must not be NULL",0,__LINE__,__FILE__);
	return packetStore.Get(destination);
}

/**
 * @brief Class that implements NetModeTcp so that it can be tested.
 */
class TestClassNetModeTcp : public NetModeTcp
{
public:
	/**
	 * @brief Constructor.
	 *
	 * Adds an integer to partial packet for testing purposes.
	 *
	 * @param partialPacketSize Maximum amount of partial data (data that does not make up a full packet) that can be stored (in bytes).
	 * Packets larger than this size cannot be received without memory reallocation.
	 * @param autoResize If true then if a packet larger than @a partialPacketSize is received then more memory will be automatically allocated so that it can be received. \n
	 * If false then an error will be thrown if a packet larger than @a partialPacketSize is received.
	 */
	TestClassNetModeTcp(size_t partialPacketSize, bool autoResize) : NetModeTcp(partialPacketSize, autoResize)
	{
		partialPacket.Add<int>(5000);
	}

	/** 
	 * @brief Implements virtual method.
	 *
	 * @return 0.0.
	 */
	double GetPartialPacketPercentage() const
	{
		return 0.0;
	}



	/** 
	 * @brief Implements virtual method.
	 *
	 * @return NULL.
	 */
	TestClassNetModeTcp * Clone() const
	{
		return NULL;
	}

	/**
	 * @brief Implements virtual method.
	 *
	 * @param packet Packet to send.
	 * @param block True if sending should be synchronous, false if sending should be asynchronous.
	 *
	 * @return NULL.
	 */
	NetSend * GetSendObject(const Packet * packet, bool block)
	{
		return NULL;
	}

	/** 
	 * @brief Implements virtual method.
	 *
	 * @return ProtocolMode::TCP_POSTFIX.
	 */
	NetMode::ProtocolMode GetProtocolMode() const
	{
		return NetMode::TCP_POSTFIX;
	}

	/**
	 * @brief Implements virtual method.
	 *
	 * @param buffer Newly received data.
	 * @param completionBytes Number of bytes of new data stored in @a buffer.
	 * @param [in] recvFunc Method will be executed and data not added to the queue if this is non NULL.
	 * @param instanceID Instance that data was received on.
	 * @param clientID ID of client that data was received from, set to 0 if not applicable.
	 */
	void DealWithData(const WSABUF & buffer, size_t completionBytes, NetSocket::RecvFunc recvFunc, size_t clientID, size_t instanceID)
	{

	}

	/**
	 * @brief Techlord Modification for TCP_FOR_HTTP Mode. Enable/Disable the prefix/postfix in use, which indicates the end of a packet.
	 */
	void SetAffixEnable(bool enabledflag){
		affixenabledflag = enabledflag;
	}

	/**
	 * @brief Techlord Modification for TCP_FOR_HTTP Mode. Returns Affix Flag Value.
	 */
	bool GetAffixEnable(void){
		return(affixenabledflag);
	}

	/**
	 * @brief Techlord Modification for TCP_FOR_HTTP Mode.
	 */
	void SetBinaryMode(bool enabledflag){
		binarymodeflag = enabledflag;
	}

	/**
	 * @brief Techlord Modification for TCP_FOR_HTTP Mode.
	 */
	bool GetBinaryMode(void){
		return(binarymodeflag);
	}

	/**
	 * @brief Techlord Modification for TCP_FOR_HTTP Mode.
	 */
	void SetHeaderFound(bool foundflag){
		headerfoundflag = foundflag;
	}

	/**
	 * @brief Techlord Modification for TCP_FOR_HTTP Mode.
	 */
	bool GetHeaderFound(void){
		return(headerfoundflag);
	}

};

void NetModeTcpTest(Packet & packet)
{
	cout << "Recv function called";
}

/**
 * @brief Tests class.
 *
 * @return true if no problems while testing were found, false if not.
 * Note that not all tests automatically check for problems so some tests
 * require manual verification.
 */
bool NetModeTcp::TestClass()
{
	cout << "Testing NetModeTcp class...\n";
	bool problem = false;

	TestClassNetModeTcp obj(1000,false);

	if(obj.GetMaxPacketSize() != 1000)
	{
		cout << "GetMaxPacketSize or Constructor is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMaxPacketSize and Constructor are good\n";
	}

	obj.ChangeMaxPacketSize(2000);
	if(obj.GetMaxPacketSize() != 2000)
	{
		cout << "ChangeMaxPacketSize is bad\n";
		problem = true;
	}
	else
	{
		cout << "ChangeMaxPacketSize is good\n";
	}

	Packet * packet = new Packet("hello world");
	obj.PacketDone(packet,NULL);

	if(obj.GetPacketAmount() != 1)
	{
		cout << "PacketDone or GetPacketAmount is bad\n";
		problem = true;
	}
	else
	{
		cout << "PacketDone and GetPacketAmount are good\n";
	}
	
	obj.ClearPacketStore();
	if(obj.GetPacketAmount() != 0)
	{
		cout << "ClearPacketStore is bad\n";
		problem = true;
	}
	else
	{
		cout << "ClearPacketStore is good\n";
	}
	
	packet = new Packet("hello universe");
	cout << "Check that below receive function is called!\n";
	obj.PacketDone(packet,NetModeTcpTest);

	if(obj.GetPartialPacketCurrentSize() != sizeof(int))
	{
		cout << "GetPartialPacketCurrentSize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetPartialPacketCurrentSize is good\n";
	}

	obj.ClearData();
	if(obj.GetPartialPacketCurrentSize() != 0)
	{
		cout << "ClearData is bad\n";
		problem = true;
	}
	else
	{
		cout << "ClearData is good\n";
	}

	if(obj.GetAutoResize() == true)
	{
		cout << "GetAutoResize or constructor is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetAutoResize and constructor are good\n";
	}

	obj.SetAutoResize(true);
	if(obj.GetAutoResize() == false)
	{
		cout << "GetAutoResize or constructor is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetAutoResize and constructor are good\n";
	}

	cout << "\n\n";
	return !problem;
}
