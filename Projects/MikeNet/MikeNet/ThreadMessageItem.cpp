#include "FullInclude.h"

/**
 * @brief	Default constructor. 
 *
 * ThreadMessageItem::messageNotInUseByThread begins true and should be unsignaled
 * just before the message is sent to a thread.
 */
ThreadMessageItem::ThreadMessageItem() : messageNotInUseByThread(true), messageNotInUseBySender(true)
{

}

/**
 * @brief	Destructor.
 *
 * Will not return until ThreadMessageItem::messageNotInUseByThread and. 
 * ThreadMessageItem::messageNotInUseBySender are signaled.
 */
ThreadMessageItem::~ThreadMessageItem()
{
	messageNotInUseByThread.WaitUntilSignaled();
	messageNotInUseBySender.WaitUntilSignaled();
}

/**
 * @brief	Specifies whether this message object is in use by a thread.
 *
 * Once set to false the thread must not use the object as it may be cleaned up
 * by the sender.
 *
 * @param	option	True if the object is in use, false if not.
 */
void ThreadMessageItem::SetMessageInUseByThread( bool option )
{
	messageNotInUseByThread.Set(!option);
}

/**
 * @brief	Determines whether the message object is in use by a thread.
 *
 * @return	true if the message object is in use, false if not.
 */
bool ThreadMessageItem::IsMessageInUseByThread() const
{
	return !messageNotInUseByThread.Get();
}

/**
 * @brief	Does not return until this message object is not in use by a thread, or timeout has expired.
 *
 * @param	timeout	Length of time to wait before returning regardless of outcome.
 */
void ThreadMessageItem::WaitUntilNotInUseByThread( DWORD timeout ) const
{
	messageNotInUseByThread.WaitUntilSignaled(timeout);
}

/**
 * @brief	Does not return until this message object is not in use by a thread.
 */
void ThreadMessageItem::WaitUntilNotInUseByThread() const
{
	messageNotInUseByThread.WaitUntilSignaled();
}



/**
 * @brief	Specifies whether this message object is in use by a sender.
 *
 * Once set to false the sender must not use the object as it may be cleaned up
 * by the sender.
 *
 * @param	option	True if the object is in use, false if not.
 */
void ThreadMessageItem::SetMessageInUseBySender( bool option )
{
	messageNotInUseBySender.Set(!option);
}

/**
 * @brief	Determines whether the message object is in use by a sender.
 *
 * @return	true if the message object is in use, false if not.
 */
bool ThreadMessageItem::IsMessageInUseBySender() const
{
	return !messageNotInUseBySender.Get();
}

/**
 * @brief	Does not return until this message object is not in use by a sender, or timeout has expired.
 *
 * @param	timeout	Length of time to wait before returning regardless of outcome.
 */
void ThreadMessageItem::WaitUntilNotInUseBySender( DWORD timeout ) const
{
	messageNotInUseBySender.WaitUntilSignaled(timeout);
}

/**
 * @brief	Does not return until this message object is not in use by a sender.
 */
void ThreadMessageItem::WaitUntilNotInUseBySender() const
{
	messageNotInUseBySender.WaitUntilSignaled();
}


/**
 * @brief	Called by the receiving thread to decide whether to cleanup this send object.
 *
 * This method, used in conjunction with ThreadMessageItem::ShouldSenderCleanup ensures that
 * the object is cleaned up by either the thread or the sender, but is only cleaned up once.
 *
 * @return true if the object should be cleaned up.
 */
bool ThreadMessageItem::ShouldThreadCleanup()
{
	bool returnMe = false;
	mtEventObjects.Enter();

	if(messageNotInUseBySender.Get() == true)
	{
		returnMe = true;
	}

	messageNotInUseByThread.Set(true);

	mtEventObjects.Leave();

	return returnMe;
}

/**
 * @brief	Called by the sending thread to decide whether to cleanup this send object.
 *
 * This method, used in conjunction with ThreadMessageItem::ShouldSenderCleanup ensures that
 * the object is cleaned up by either the thread or the sender, but is only cleaned up once.
 *
 * @return true if this object should be cleaned up.
 */
bool ThreadMessageItem::ShouldSenderCleanup()
{
	bool returnMe = false;
	mtEventObjects.Enter();

	if(messageNotInUseByThread.Get() == true)
	{
		returnMe = true;
	}

	messageNotInUseBySender.Set(true);

	mtEventObjects.Leave();

	return returnMe;
}
