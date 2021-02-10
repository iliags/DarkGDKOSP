#include "../../../../../../Include/MikeNet/FullInclude.h"
//#include <MikeNet/FullInclude.h>
#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;

// Operations
const int OP_FLOAT = 0;
const int OP_STRING = 1;
const int OP_INT = 2;

// Entry point
void main()
{
	// Connect to server
	int iReturn = 0;
	cout << "DarkNet version: " << mn::GetVersion() << "\n";

	long long int RecvPacket = mn::CreatePacket();
	long long int SendPacket = mn::CreatePacket();
	mn::SetMemorySize(SendPacket,1024);

	mn::Start(1,0);

	// Determine IP of localhost
	const char * LocalHost = mn::DNS_B("localhost");

	__int64 profile = mn::CreateInstanceProfile();
	mn::SetProfileLocal(profile,LocalHost,0,LocalHost,0);
	mn::SetProfileModeUDP(profile,NetMode::UDP_PER_CLIENT_PER_OPERATION);
	mn::SetProfileNumOperationsUDP(profile,3);
	iReturn = mn::Connect(0,LocalHost,6565,LocalHost,6565,5000,true,profile);
	switch(iReturn)
	{
		case(1):
			cout << "Connected to server\n";
		break;

		case(0):
			cout << "Connection timed out\n";
			system("PAUSE");
			return;
		break;

		case(-1):
			cout << "Error occurred whilst connecting\n";
			system("PAUSE");
			return;
		break;

		case(-2):
			cout << "The connection request was rejected because the server is full.\n";
			system("PAUSE");
			return;
		break;
	}


	// Main loop
	unsigned int SendTimer = 0;
	unsigned int SendFreq = 1000;

	while(mn::ClientConnected(0,0) == 1)
	{
		// Use less CPU
		Sleep(1);

		// TCP packets
		iReturn = mn::RecvTCP(0,RecvPacket,0);
	
		if(iReturn > 0)
		{
			cout << "New TCP packet received\n";
		}

		// UDP packets
		for(size_t cl = 1;cl<=mn::GetMaxClients(0);cl++)
		{
			for(size_t op = 0;op<mn::GetMaxOperations(0);op++)
			{
				iReturn = mn::RecvUDP(0,RecvPacket,cl,op);
				
				if(iReturn > 0)
				{
					// Decide what to do depending on operation
					switch(op)
					{
						case(OP_FLOAT):
						{
							float fl = mn::GetFloat(RecvPacket);
							cout << "Float received from server, that was originally sent by client " << cl << ": " << fl << '\n';
						}
						break;

						case(OP_STRING):
						{
							char * str = mn::GetStringC(RecvPacket,0,1);
							cout << "String received from server, that was originally sent by client " << cl << ": " << str;

							// Deallocate memory allocated by mn::GetStringC
							delete[] str;
						}
						break;

						case(OP_INT):
						{
							int i = mn::GetInt(RecvPacket);
							cout << "Integer received from server, that was originally sent by client " << cl << ": " << i << '\n';
						}
						break;

						default:
							cout << "Invalid operation" << '\n';
							system("PAUSE");
						break;
					}
				}
			}
		}

		// Send messages every SendFreq ms
		if(clock() - SendTimer > SendFreq)
		{
			// Operation
			int op = rand() % 3; // Random number between 0 and 2
			mn::AddSizeT(SendPacket,op);

			// Decide what to do depending on operation
			switch(op)
			{
				case(OP_FLOAT):
				{
					float fl = (rand()*1.0f)+(rand() % 11)*0.1f;
					mn::AddFloat(SendPacket,fl);

					cout << "Float sent to server: " << fl << '\n';
				}
				break;

				case(OP_STRING):
				{
					time_t time1 = time(NULL);
					tm * time2 = localtime(&time1);
					char * str = asctime(time2);
					
					mn::AddStringC(SendPacket,str,0,true);

					cout << "String sent to server: " << str;
				}
				break;

				case(OP_INT):
				{
					int i = rand();
					mn::AddInt(SendPacket,i);

					cout << "Integer sent to server: " << i << '\n';
				}
				break;

				default:
					cout << "Invalid operation\n";
					system("PAUSE");
				break;
			}

			// Send packet
			mn::SendUDP(0,SendPacket,0,0,1);

			// Update timer
			SendTimer = clock();
		}
	}
}