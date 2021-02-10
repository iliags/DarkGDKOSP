#include "../../../../../../Include/MikeNet/FullInclude.h"
#include <windows.h>
#include <iostream>
using namespace std;

// Operations
const int OP_FLOAT = 0;
const int OP_STRING = 1;
const int OP_INT = 2;

// Entry point
void main()
{
	// Setup server
	int iReturn = 0;
	NetSocketTCP socket(1024, false, true, new NetModeTcpPrefixSize(2048,true));
	cout << "DarkNet version: " << mn::GetVersion() << "\n";

	long long int RecvPacket = mn::CreatePacket();
	long long int SendPacket = mn::CreatePacket();
	mn::SetMemorySize(SendPacket,1024);

	mn::Start(1,0);

	// Determine IP of localhost
	const char * LocalHost = mn::DNS_B("localhost");

	__int64 profile = mn::CreateInstanceProfile();
	mn::SetProfileLocal(profile,LocalHost,6565,LocalHost,6565);
	mn::SetProfileModeUDP(profile,NetMode::UDP_PER_CLIENT_PER_OPERATION);
	mn::SetProfileNumOperationsUDP(profile,3);
	mn::StartServer(0,50,profile);
	
	cout << "Server started on TCP port " << mn::GetLocalPortTCP(0) << " and UDP port " << mn::GetLocalPortUDP(0) << '\n';


	// Main loop
	bool bRunning = true;
	while(bRunning == true)
	{
		// Use less CPU
		Sleep(1);

		// New clients
		iReturn = mn::ClientJoined(0);
		if(iReturn > 0)
		{
			cout << "New client joined, ID: " << iReturn << "\n";
		}

		// Leaving clients
		iReturn = mn::ClientLeft(0);
		if(iReturn > 0)
		{
			cout << "Client left, ID: " << iReturn << "\n";
		}

		for(size_t cl = 1;cl<=mn::GetMaxClients(0);cl++)
		{
			// TCP packets
			iReturn = mn::RecvTCP(0,RecvPacket,cl);
		
			if(iReturn > 0)
			{
				cout << "New TCP packet received from client " << iReturn << "\n";
			}
		
			// UDP packets
			for(size_t op = 0;op<mn::GetMaxOperations(0);op++)
			{
				iReturn = mn::RecvUDP(0,RecvPacket,cl,op);
				
				if(iReturn > 0)
				{
					// Begin formulating packet to send to clients
					mn::AddSizeT(SendPacket,cl);
					mn::AddSizeT(SendPacket,op);

					// Decide what to do depending on operation
					switch(op)
					{
						case(OP_FLOAT):
						{
							float fl = mn::GetFloat(RecvPacket);
							cout << "Float received from client " << cl << ": " << fl << '\n';
							
							// Finish formulating packet to send to clients
							mn::AddFloat(SendPacket,fl);
						}
						break;

						case(OP_STRING):
						{
							char * str = mn::GetStringC(RecvPacket,0,1);
							cout << "String received from client " << cl << ": " << str;

							// Finish formulating packet to send to clients
							mn::AddStringC(SendPacket,str,0,true);

							// Deallocate memory allocated by mn::GetStringC
							delete[] str;
						}
						break;

						case(OP_INT):
						{
							int i = mn::GetInt(RecvPacket);
							cout << "Integer received from client " << cl << ": " << i << '\n';

							// Finish formulating packet to send to clients
							mn::AddInt(SendPacket,i);
						}
						break;

						default:
							cout << "Invalid operation\n";
							system("PAUSE");
						break;
					}

					// Send packet to all clients (excluding the client we received it from)
					mn::SendAllUDP(0,SendPacket,0,1,cl);
				}
			}
		}
	}

}