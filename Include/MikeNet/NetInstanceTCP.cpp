#include "FullInclude.h"

/**
 * @brief Constructor.
 *
 * @param handshakeEnabled If false the @ref handshakePage "TCP handshake process" is disabled.
 * @note Virtual inheritance means that NetInstance constructor will never be called by this constructor.
 */
NetInstanceTCP::NetInstanceTCP(bool handshakeEnabled) : NetInstance()
{
	this->handshakeEnabled = handshakeEnabled;
}

/**
 * @brief Destructor.
 */
NetInstanceTCP::~NetInstanceTCP()
{

}

/**
 * @brief Determines whether the handshake process is enabled.
 *
 * @return true if handshake is enabled, false if not.
 * For more information see @ref handshakePage "server/client handshaking process".
 */
bool NetInstanceTCP::IsHandshakeEnabled() const
{
	return handshakeEnabled;
}

/** 
 * @brief Determines whether specified size is valid.
 * 
 * @param size Size to check.
 * @return true If @a size is larger enough (i.e. Larger than or equal to GetRecvSizeMinTCP).
 */
bool NetInstanceTCP::ValidateRecvSizeTCP(size_t size) const
{
	return(size >= GetRecvSizeMinTCP());
}

/**
 * @brief Techlord Modification. Enable/Disable the postfix in use, which indicates the end of a packet.
 */
void NetInstanceTCP::SetAffixEnableTCP(size_t clientID, bool enabledflag)
{
}

/**
* @brief Techlord Modification for TCP_FOR_HTTP Mode. Retrieves Affix Enabled Flag Value.
*
* @param clientID ID of client to use, may be ignored.
*/
bool NetInstanceTCP::GetAffixEnableTCP(size_t clientID)
{
	return(true);
}

/**
 * @brief Techlord Modification for TCP_FOR_HTTP Mode. Enable/Disable the HTTP Binary Mode Flag.
 */
void NetInstanceTCP::SetBinaryModeTCP(size_t clientID, bool foundflag)
{
}

/**
* @brief Techlord Modification for TCP_FOR_HTTP Mode. Retrieves the Binary Mode Flag Value.
*
* @param clientID ID of client to use, may be ignored.
*/
bool NetInstanceTCP::GetBinaryModeTCP(size_t clientID)
{
	return(true);
}

/**
 * @brief Techlord Modification. Set Header Found Flag.
 */
void NetInstanceTCP::SetHeaderFoundTCP(size_t clientID, bool foundflag)
{
}

/**
* @brief Techlord Modification for TCP_FOR_HTTP Mode. Retrieves the  Header Found Flag Value.
*
* @param clientID ID of client to use, may be ignored.
*/
bool NetInstanceTCP::GetHeaderFoundTCP(size_t clientID)
{
	return(true);
}
