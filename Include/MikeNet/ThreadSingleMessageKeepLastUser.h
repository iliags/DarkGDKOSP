#pragma once
#include "ThreadSingleMessageKeepLast.h"

/**
 * @brief	Used by objects where all instances of that object share a group of threads.
 * @remarks	Michael Pryor, 9/21/2010. 
 */
class ThreadSingleMessageKeepLastUser
{
	/**
	 * @brief Number of packets using the encryption threads.
	 *
	 * Usage begins when Encrypt or Decrypt is first used, and ends when the packet
	 * is destroyed. \n\n
	 *
	 * Access is controlled using Packet::threads critical section.
	 */
	static size_t threadsUsageCount;

	/**
	 * @brief True if the packet is using Packet::threads.
	 */
	ConcurrentObject<bool> usingThreads;

	/**
	 * @brief Local store of the last message that was sent to the encryption thread.
	 *
	 * We use a local store, instead of a global store stored by ThreadSingleMessageKeepLast so that
	 * each individual packet can poll on its own last encryption message, rather than polling on the
	 * last encryption message sent by any packet. \n\n
	 *
	 * A vector is needed because there must be one message per thread.
	 */
	StoreVector<ThreadMessageItem> lastMessage;

	/**
	 * @brief Threads used for encryption and decryption.
	 */
	static StoreVector<ThreadSingleMessageKeepLast> threads;
public:
	ThreadSingleMessageKeepLastUser();
	ThreadSingleMessageKeepLastUser(size_t numThreads, LPTHREAD_START_ROUTINE function, void * parameter);
	virtual ~ThreadSingleMessageKeepLastUser();
protected:
	static void SetupThreads(size_t numThreads, LPTHREAD_START_ROUTINE function, void * parameter);
	void SetupThreadsLocal(size_t numThreads, LPTHREAD_START_ROUTINE function, void * parameter);
	static void CleanupThreads();
	void CleanupThreadsLocal();

	void PostMessageItem(size_t threadID, ThreadMessageItem * message);
	size_t GetNumThreads();
	void WaitUntilLastThreadOperationFinished();
	bool IsLastThreadOperationFinished();
};

