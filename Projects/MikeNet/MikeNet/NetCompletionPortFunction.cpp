#include "FullInclude.h"

/**
 * @brief Thread function which manages a completion port,
 * cleaning up send operations and dealing with received data.
 */
DWORD WINAPI NetManageCompletionPort(LPVOID lpParameter)
{
	const char * cCommand = "an internal function (NetManageCompletionPort)";


	try
	{
		// Get all parameters
		ThreadSingle * thread = static_cast<ThreadSingle*>(lpParameter);
		size_t threadID = thread->GetManualThreadID();
		CompletionPort * completionPort = static_cast<CompletionPort*>(thread->GetParameter());
		ThreadSingle::ThreadSetCallingThread(thread);

		bool bRunning = true;
		while(bRunning == true)
		{
			// Get completion status
			CompletionKey * completionKey = NULL;
			DWORD completionBytes = 0;
			OVERLAPPED * completionOverlapped = NULL;

			bool success = completionPort->GetCompletionStatus(completionKey,completionBytes,completionOverlapped);
			_ErrorException((completionKey == NULL),"retrieving a completion status",WSAGetLastError(),__LINE__,__FILE__);

			// Determine whether instance is shutting down
			if(completionBytes == 0)
			{
				success = false;
			}
			bool shuttingDown = (success == false && WSAGetLastError() == WSA_OPERATION_ABORTED);

			// Instance initiated operation
			if(completionKey->IsOwnedByInstance() == true)
			{
				NetInstance * instance = completionKey->GetInstance();

				try
				{
					bool isRecvOperation = completionKey->GetSocket()->IsOurOverlapped(completionOverlapped);
					bool isSendOperation = !isRecvOperation;
					size_t clientID = completionKey->GetClientID();
					NetSocket * socket = completionKey->GetSocket();

					if(completionBytes == 0)
					{
						success = false;
					}

					bool shuttingDown = (success == false && WSAGetLastError() == WSA_OPERATION_ABORTED);

					if(isRecvOperation == true)
					{
						if(success == false)
						{
							if(shuttingDown == false)
							{
								instance->CompletionError(socket,clientID);
							}

							// Indicate that we have completely finished receiving and dealing with receive data
							// Socket will wait until this has happened before cleaning up
							socket->SetCompletionPortFinishRecvNotification();
						}
						else
						{
							instance->DealCompletion(socket,completionBytes,clientID);

							// Start another receive operation	
							instance->DoRecv(socket,clientID);
						}
					}
					// isSendOperation = true
					else
					{
						instance->CompletedSendOperation(socket,completionOverlapped,success,shuttingDown,clientID);
					}

				}
				// Request that socket be closed in the event of an error
				catch(ErrorReport & error){instance->RequestDestroy();}
				catch(...){instance->RequestDestroy();}
			}
			// Instance did not initiate operation
			else
			{
				switch(completionKey->GetType())
				{
				case(CompletionKey::SOCKET):
				{
					bool isRecvOperation = completionKey->GetSocket()->IsOurOverlapped(completionOverlapped);
					bool isSendOperation = !isRecvOperation;
					
					if(isRecvOperation == true)
					{
						if(success == false)
						{
							if(shuttingDown == false)
							{
								// Request that socket be closed
								completionKey->GetSocket()->CompletionPortRequestClose();
							}

							// Indicate that we have completely finished receiving and dealing with receive data
							// Socket will wait until this has happened before cleaning up
							completionKey->GetSocket()->SetCompletionPortFinishRecvNotification();
						}
						else
						{
							try
							{
								// Deal with received data
								completionKey->GetSocket()->DealWithData(completionKey->GetSocket()->recvBuffer,completionBytes,completionKey->GetSocket()->GetRecvFunction(),NULL,NULL);

								// Indicate that we have completely finished receiving and dealing with receive data
								// MUST do before starting new receive operation
								completionKey->GetSocket()->SetCompletionPortFinishRecvNotification();

								// Start another receive operation	
								bool error = completionKey->GetSocket()->Recv();

								// Request that socket be closed upon error
								if(error && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAENOTSOCK)
								{
									completionKey->GetSocket()->CompletionPortRequestClose();
								}
							}
							// Request that socket be closed in the event of an error
							catch(ErrorReport & error){	completionKey->GetSocket()->CompletionPortRequestClose(); }
							catch(...){ completionKey->GetSocket()->CompletionPortRequestClose(); }
						}
					}
					// isSendOperation = true
					else
					{
						completionKey->GetSocket()->CompletedSendOperation(completionOverlapped,success,shuttingDown);
					}
				}
					break;

				case(CompletionKey::SHUTDOWN):
					bRunning = false;
					break;
				}
			}
		}
	}
	MSG_CATCH

	return(0);
}
