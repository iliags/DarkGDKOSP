#pragma once

/**
 * @brief	UDP protocol class, provides a base for extensions to the protocol by UDP mode classes.
 * @remarks	Michael Pryor, 6/28/2010.
 *
 * This class lays out the functionality required by UDP mode classes.
 */
class NetModeUdp : public NetMode
{
public:
	static NetModeUdp * GenerateModeUDP(NetMode::ProtocolMode protocolMode, size_t numClients, size_t numOperations, size_t recvSize, const EncryptKey * decryptKey);

	static bool _HelperTestClass(NetModeUdp & obj, Packet & packet, const char * str, size_t dealWithDataClientID, size_t expectedClientID, size_t operationID);
	static bool TestClass();

	/**
	 * @brief Resets data of specified client.
	 *
	 * @param clientID ID of client to use.
	 */
	virtual void Reset(size_t clientID) = 0;

	/**
	 * @brief Reset data of all clients.
	 */
	virtual void Reset() = 0;

	/**
	 * @brief Retrieves the number of operations that this object can manage.
	 *
	 * Operation IDs range from 0 inclusive to number of operations exclusive.
	 * e.g. With 5 operations, available IDs are: 0, 1, 2, 3, 4.
	 *
	 * @return the number of operations that this object can manage.
	 * @return if operations are not valid for this object then 1 should be returned.
	 */
	virtual size_t GetNumOperations() const = 0;

	/**
	 * @brief Retrieves the number of clients that this object can manage.
	 *
	 * @return the number of clients that this object can manage.
	 */
	virtual size_t GetNumClients() const = 0;

	/**
	 * @brief Retrieves a deep copy of this object.
	 *
	 * @return a deep copy of this object.
	 */
	virtual NetModeUdp * Clone() const = 0;

	virtual ~NetModeUdp();
};