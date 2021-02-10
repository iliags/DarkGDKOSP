#include "FullInclude.h"

size_t ThreadSingleMessageKeepLastUser::threadsUsageCount(0);
StoreVector<ThreadSingleMessageKeepLast> ThreadSingleMessageKeepLastUser::threads;

/**
 * @brief	Default constructor. 
 */
ThreadSingleMessageKeepLastUser::ThreadSingleMessageKeepLastUser()
	: usingThreads(false)
{

}

/**
 * @brief	Constructor. 
 *
 * @param	numThreads	Number of threads to setup.
 * @param function Entry point for thread. A pointer to this object will be passed as a parameter.
 * @param parameter Parameter to be passed to thread. 
 */
ThreadSingleMessageKeepLastUser::ThreadSingleMessageKeepLastUser(size_t numThreads, LPTHREAD_START_ROUTINE function, void * parameter)
	: usingThreads(false)
{
	SetupThreadsLocal(numThreads, function, parameter);
}

/**
 * @brief	Destructor. 
 */
ThreadSingleMessageKeepLastUser::~ThreadSingleMessageKeepLastUser()
{
	CleanupThreadsLocal();
	lastMessage.Clear();
}

/**
 * @brief Sets up threads for all objects, loading them into ThreadSingleMessageKeepLastUser::threads.
 *
 * If threads are already setup then does nothing except increase ThreadSingleMessageKeepLastUser::threadsUsageCount.
 *
 * @param numThreads Number of threads to setup.
 * @param function Entry point for thread. A pointer to this object will be passed as a parameter.
 * @param parameter Parameter to be passed to thread. 
 */
void ThreadSingleMessageKeepLastUser::SetupThreads(size_t numThreads, LPTHREAD_START_ROUTINE function, void * parameter)
{
	threads.Enter();

	if(threadsUsageCount == 0)
	{
		try
		{
			threads.Clear();
			for(size_t n = 0;n<numThreads;n++)
			{
				ThreadSingleMessageKeepLast * newThread = new (nothrow) ThreadSingleMessageKeepLast(function,parameter,false,n);
				Utility::DynamicAllocCheck(newThread,__LINE__,__FILE__);
				threads.Add(newThread);
			}
			threadsUsageCount = 1;
		}
		// Release control of all objects before throwing exception
		catch (ErrorReport & error){threads.Leave(); throw(error);}
		catch (...){threads.Leave(); throw(-1);}
	}
	else
	{
		threadsUsageCount++;
	}

	threads.Leave();
}

/**
 * @brief	Sets up the threads for a single object (this object).
 *
 * Calls ThreadSingleMessageKeepLastUser::SetupThreads.
 *
 * @param numThreads Number of threads to setup.
 * @param function Entry point for thread. A pointer to this object will be passed as a parameter.
 * @param parameter Parameter to be passed to thread. 
 */
void ThreadSingleMessageKeepLastUser::SetupThreadsLocal(size_t numThreads, LPTHREAD_START_ROUTINE function, void * parameter)
{
	this->usingThreads.Enter();
	if(this->usingThreads == false)
	{
		SetupThreads(numThreads,function,parameter);
		this->usingThreads = true;

		// One message per thread.
		lastMessage.Resize(threads.Size());
	}
	this->usingThreads.Leave();
}

/**
 * @brief	Cleans up threads for all objects.
 *
 * Does nothing if threads are not already setup.
 */
void ThreadSingleMessageKeepLastUser::CleanupThreads()
{
	threads.Enter();
	try
	{
		if(threadsUsageCount > 0)
		{
			threadsUsageCount--;
			if(threadsUsageCount == 0)
			{
				threads.Clear();
			}
		}
	}
	// Release control of all objects before throwing exception
	catch (ErrorReport & error){threads.Leave(); throw(error);}
	catch (...){threads.Leave(); throw(-1);}

	threads.Leave();
}

/**
 * @brief	Cleans up threads for a single object (this object).
 *
 * Calls ThreadSingleMessageKeepLastUser::CleanupThreads if this is the last object using the
 * threads that has not been destroyed.\n\n
 *
 * Does nothing if object never used threads.
 */
void ThreadSingleMessageKeepLastUser::CleanupThreadsLocal()
{
	usingThreads.Enter();
	if(usingThreads == true)
	{
		CleanupThreads();
		
		for(size_t n = 0;n<lastMessage.Size();n++)
		{
			if(lastMessage.IsAllocated(n) == true)
			{
				bool shouldCleanup = lastMessage[n].ShouldSenderCleanup();

				if(shouldCleanup == true)
				{
					lastMessage.Deallocate(n);
				}
			}
		}
		usingThreads = false;
	}
	usingThreads.Leave();
}

/**
 * @brief	Does not return until the last operation has finished.
 */
void ThreadSingleMessageKeepLastUser::WaitUntilLastThreadOperationFinished()
{
	for(size_t n = 0;n<lastMessage.Size();n++)
	{
		if(lastMessage.IsAllocated(n) == true)
		{
			lastMessage[n].WaitUntilNotInUseByThread();
		}
	}
}

/**
 * @brief	Determines whether the last operation has finished.
 *
 * @return	true if the last operation has finished, false if not.
 */
bool ThreadSingleMessageKeepLastUser::IsLastThreadOperationFinished()
{
	bool isInUse = false;

	for(size_t n = 0;n<lastMessage.Size();n++)
	{
		if(lastMessage.IsAllocated(n) == true)
		{
			if(lastMessage[n].IsMessageInUseByThread() == true)
			{
				isInUse = true;
				break;
			}
		}
	}

	return !isInUse;
}

/**
 * @brief	Posts a message to the thread to be received using ThreadSingleMessage::GetMessageItem().
 *
 * @param	threadID ID of thread to post message to.
 * @param	message	The message to post.
 */
void ThreadSingleMessageKeepLastUser::PostMessageItem(size_t threadID, ThreadMessageItem * message)
{
	threads[threadID].PostMessageItem(message,lastMessage.GetPtr(threadID));
}

/**
 * @brief	Retrieves the number of threads that are operational. 
 *
 * @return	the number of threads.
 */
size_t ThreadSingleMessageKeepLastUser::GetNumThreads()
{
	return threads.Size();
}
