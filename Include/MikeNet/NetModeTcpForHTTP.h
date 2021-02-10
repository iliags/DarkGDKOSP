//MikeNet TCP Mode for HTTP by Frankie 'TechLord' Taylor
class NetModeTcpForHTTP: public NetModeTcp
{
	/**
	 * @brief Stores postfix used to indicate the end of a packet.
	 */
	Packet postfix;

public:
	NetModeTcpForHTTP(size_t partialPacketSize, bool autoResize, const Packet & packetPostfix);
	NetModeTcpForHTTP(const NetModeTcpForHTTP & copyMe);
	NetModeTcpForHTTP & operator= (const NetModeTcpForHTTP & copyMe);
	NetModeTcpForHTTP * Clone() const;

	void DealWithData(const WSABUF & buffer, size_t completionBytes, NetSocket::RecvFunc tcpRecvFunc, size_t clientID, size_t instanceID);
	
	NetSend * GetSendObject(const Packet * packet, bool block);

	ProtocolMode GetProtocolMode() const;

	double GetPartialPacketPercentage() const;
	
	const Packet & GetPostfix() const;

	static bool TestClass();
	
	void SetAffixEnable(bool enabledflag);

	bool GetAffixEnable();

	void SetBinaryMode(bool enabledflag); //Techlord Modification for TCP_FOR_HTTP Mode.

	bool GetBinaryMode(); //Techlord Modification for TCP_FOR_HTTP Mode.
	
	void SetHeaderFound(bool foundflag); //Techlord Modification for TCP_FOR_HTTP Mode.

	bool GetHeaderFound(); //Techlord Modification for TCP_FOR_HTTP Mode.	

};