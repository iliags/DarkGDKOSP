/*

DarkNet(MikeNet2.0) Extension For S3GE/HTTP Demonstration
Michael Pryor & Techlord

References:
http://www.darknetworking.com
HTTP Explanation HTTP://www.jmarshall.com/easy/HTTP/#HTTP1.1c3
*/
#include "../../../Include/MikeNet/FullInclude.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Operations
const int OP_FLOAT = 0;
const int OP_STRING = 1;
const int OP_INT = 2;
int TransferMode = 1; //BINARY=0, ASCII=1
enum TransactionStates{IDLE, REQUESTSTART, REQUESTSTARTING, REQUEST, REQUESTING, REQUESTEND, RESPONSESTART, RESPONSE, RESPONDING, RESPONSEEND, RECOVER, PENDING, SUSPEND, SUSPENDED, RELEASE, TERMINATE} State;

// Entry point
int main()
{

	cout << "DarkNet version: " << mn::GetVersion();
	cout << "\nHTTP GET Binary[0] ASCII[1] File:";
	cin >> TransferMode;
	cout << "You entered: " << TransferMode << endl << endl;

	mn::Start(1,0);

	//Setup TCP Mode
	__int64 profile = mn::CreateInstanceProfile();
	mn::SetProfileModeTCP(profile, (char)NetMode::ProtocolMode::TCP_FOR_HTTP);
	mn::SetProfileHandshakeEnabled(profile, false);
	mn::SetProfileGracefulDisconnectEnabled(profile, true);

	// Determine IP of Host
	string Hostname = "tournamentblitz.hpquest.com";
	int Port = 80;
	const char * HostIP = mn::DNS_B(Hostname.c_str());

	long long int RequestPacket;
	string RequestHeaderLine;
	string RequestPageVariables;
	string RequestPage[] = {"/games/insectoids.zip", "/donate.html"}; //[0]Binary File, [1]ASCII File
	
	long long int ResponsePacket;
	vector<long long int>  ResponseStoredPackets;
	string ResponseHeaderLine;
	int ResponseContentLength = 0;
	int ResponseBytesLoaded = 0;
	string ResponseWritePath[] = {"insectoidz.zip","donate.html"};

	int Status;
	State = REQUESTSTART;

	// Main loop
	while(State != TERMINATE)
	{

		switch(State){

			case IDLE:
				break;

			case REQUESTSTART:
				cout << "\nREQUESTSTART";
				Status = mn::Connect(0,HostIP,Port,HostIP,Port,5000,false,profile);
				mn::SetAutoResizeTCP(0,0,true);
				mn::SetBinaryModeTCP(0,0,1 - TransferMode); //Set Transfer Mode for Message Body
				State = REQUESTSTARTING;
				//break;
				
			case REQUESTSTARTING:
				cout << "\nREQUESTSTARTING";
				Status = mn::PollConnect(0);
				switch(Status){

					case NetUtility::STILL_CONNECTING:
						cout << "\nConnecting...\n";
						break;

					case NetUtility::CONNECTED:
						cout << "\nConnected to server\n";
						RequestPacket = mn::CreatePacket();
						mn::SetMemorySize(RequestPacket,1024);
						State = REQUEST;
						break;

					case NetUtility::TIMED_OUT:
						cout << "\nConnection timed out\n";
						State = TERMINATE;
						break;

					case NetUtility::CONNECTION_ERROR:
						cout << "\nError occurred whilst connecting\n";
						State = TERMINATE;
						break;

					case NetUtility::REFUSED:
						cout << "\nError occurred: server rejected connection Request\n";
						State = TERMINATE;
						break;
				}
				break; 

			case REQUEST://Request Message Header
				cout << "\nREQUEST";
				//Request Method
				RequestHeaderLine = "GET ";

				//PageVariables
				if(!RequestPageVariables.empty()){
					RequestPage[TransferMode].append("?");
					RequestPage[TransferMode].append(RequestPageVariables);
				}

				RequestHeaderLine.append(RequestPage[TransferMode]);
				RequestHeaderLine.append(" HTTP/1.0\r\n");

				cout << "\nHTTP Request:" << RequestHeaderLine.c_str();

				mn::AddStringC(RequestPacket, (char*)RequestHeaderLine.data(),0,false);
				mn::AddStringC(RequestPacket, "Accept: */*\r\n",0,false);
				mn::AddStringC(RequestPacket, "Accept-Language: en-us\r\n",0,false);
				mn::AddStringC(RequestPacket, "User-Agent: mnTcpHTTP\r\n",0,false);
				mn::AddStringC(RequestPacket, "Content-Type: application/text\r\n" ,0,false);
				mn::AddStringC(RequestPacket, "Accept-Encoding: gzip, deflate\r\n",0,false);

				RequestHeaderLine = "Host: ";
				RequestHeaderLine.append(Hostname);
				RequestHeaderLine.append("\r\n");
				mn::AddStringC(RequestPacket, (char*)RequestHeaderLine.data(),0,false);
				mn::AddStringC(RequestPacket, "Connection: close\r\n",0,false); //persistent connection
				mn::AddStringC(RequestPacket, "",0,false);

				cout << "\nREQUEST --> " << Hostname.c_str();

				mn::SendTCP(0, RequestPacket, 0, false, true);
				State = REQUESTEND;
				break;

			case REQUESTING://Request body
				break;

			case REQUESTEND:
				cout << "\nREQUESTEND";
				mn::DeletePacket(RequestPacket);
				State = RESPONSESTART;
				break;

			case RESPONSESTART:
				cout << "\nRESPONSESTART";
				ResponsePacket = mn::CreatePacket();
				State = RESPONSE;
				break; 

			case RESPONSE://Response header
				cout << "\nRESPONSE";
				if(mn::ClientConnected(0,0) != 0){
					// Use less CPU
					Sleep(1);
				
					// Check for graceful disconnect
					if(mn::ClientConnected(0,0) == NetUtility::NO_RECV){
						// Wait for all data to be received before closing connection
						if(mn::GetStoreAmountTCP(0, 0) == 0){

							cout << "\nRemaining bytes of unused data " << (int)mn::GetBytesTCP(0,0);
							mn::ShutdownClient(0,0);
							cout << "\nShutdownClient!!!";

						}
					}

					// TCP packets
					Status = mn::RecvTCP(0,ResponsePacket,0);
				
					if(Status > 0){
						
						if(mn::GetUsedSize(ResponsePacket) > 0){

							cout << "\nPacket data(" << (int)mn::GetUsedSize(ResponsePacket) << ")\n";

							ResponseHeaderLine = mn::GetStringC(ResponsePacket,mn::GetUsedSize(ResponsePacket),true);
							
							cout << "\n" << ResponseHeaderLine.c_str();

							//Response header parsing

							//Response code
							if(ResponseHeaderLine.find("Accept-Ranges: bytes") != string::npos){
								TransferMode = 0;
								cout << "\n" << TransferMode;
							}

							if(ResponseHeaderLine.find("Content-Length: ") != string::npos){
								ResponseContentLength = atoi(ResponseHeaderLine.substr(ResponseHeaderLine.size() - (ResponseHeaderLine.size()-16)).c_str()); 
								
								cout << "\nResponse.ContentLength[" << (int)ResponseHeaderLine.size() << "]{" << (int)(ResponseHeaderLine.size() - ResponseHeaderLine.size()-16) << "}:" << ResponseContentLength << "\n";
							}

							if(ResponseHeaderLine.find("Content-Type:") != string::npos){
								if(ResponseHeaderLine.find("text") != string::npos){
									TransferMode = 1;
									cout << "\n" << TransferMode;
								}
							}

						} else { 
								State = RESPONDING;
								cout << "\nFILE TRANSFER MODE(" << (int)mn::GetAffixEnableTCP(0,0) << ") <-- " << Hostname.c_str() << "\n";
						}
					}
				} else {
					State = RESPONSEEND;
				}
				break;

			case RESPONDING://Response body
				cout << "\nRESPONDING:";

				if(mn::ClientConnected(0,0) != 0){
					// Use less CPU
					Sleep(1);

					// Check for graceful disconnect
					if(mn::ClientConnected(0,0) == NetUtility::NO_RECV){
						// Wait for all data to be received before closing connection
						cout << "\nPackets in Queue:" << (int)mn::GetStoreAmountTCP(0, 0);
						if(mn::GetStoreAmountTCP(0,0) == 0){
							cout << "\nRemaining bytes of unused data " << (int)mn::GetBytesTCP(0, 0);
							mn::ShutdownClient(0,0);
							cout << "\nShutdownClient!!!";
						}
					}

					// TCP packets
					Status = mn::RecvTCP(0, ResponsePacket, 0);

					cout << "\nStatus:" << Status;

					if(Status > 0){

						cout << "\npackets=" << Status;
					
						if(mn::GetUsedSize(ResponsePacket) > 0){

							ResponseStoredPackets.push_back(mn::CreatePacketFromPacket(ResponsePacket));

							ResponseBytesLoaded += (int)mn::GetUsedSize(ResponsePacket);
							double dPercent = ((double)ResponseBytesLoaded /(double)ResponseContentLength) * 100;
								
							cout << " size=" << (int)mn::GetUsedSize(ResponsePacket) << " total=" << ResponseBytesLoaded;

							if(ResponseContentLength){
								cout << " content=" << ResponseContentLength << "(" << (int)(ResponseContentLength - ResponseBytesLoaded) << ") %=" << (int)dPercent;
							}

							switch(TransferMode){

								case 0: //display content as bytes
	/*
									{
										
										string data = mn::GetStringSTD(ResponsePacket,mn::GetUsedSize(ResponsePacket));
										cout << "\n";
										for(int loop = 0; loop < data.length() + 1; loop++){
											cout << data.c_str().substr(loop,1));
										}
										
									}
	*/
									break;

								case 1: //display content as string
									{
										string data = mn::GetStringC(ResponsePacket,mn::GetUsedSize(ResponsePacket),TransferMode);
										cout << "\n" << data.c_str();
									}
									break;
							}
						}
					}

				} else {

					ResponseBytesLoaded += (int)mn::GetUsedSize(ResponsePacket);
					double dPercent = ((double)ResponseBytesLoaded /(double)ResponseContentLength) * 100;

					cout << "\nWrite file " << ResponseWritePath[TransferMode].c_str() << " size=" << (int)mn::GetUsedSize(ResponsePacket) << " total=" << ResponseBytesLoaded;

					if(ResponseContentLength){
						cout << " content=" << ResponseContentLength << "(" << (int)(ResponseContentLength - ResponseBytesLoaded) << ") %=" << (int)dPercent;
					}

					State = RESPONSEEND;
				}
				
				break;

			case RESPONSEEND:
				{
				cout << "\nRESPONSEEND";

				ofstream OutputFile;

				switch(TransferMode){

					case 0:
						//write binary file
						OutputFile.open((char*)ResponseWritePath[TransferMode].data(), ios::out | ios::binary);
						break;
					
					default: 
						//write ascii file
						OutputFile.open((char*)ResponseWritePath[TransferMode].data(), ios::out );
				}

				for(int loop = 0;loop<ResponseStoredPackets.size();loop++){
					cout << "\nWrite Packet " << (int)(loop+1) << " of " << (int)ResponseStoredPackets.size();
			
					mn::SetCursor(ResponseStoredPackets[loop],0);
					//char *data = mn::GetStringC(ResponseStoredPackets[loop], mn::GetUsedSize(ResponseStoredPackets[loop]),TransferMode);//false
					OutputFile.write(mn::GetStringC(ResponseStoredPackets[loop], mn::GetUsedSize(ResponseStoredPackets[loop]),TransferMode), mn::GetUsedSize(ResponseStoredPackets[loop]));
					if(TransferMode == 1) OutputFile.write("\n",1);
					//delete[] data;
					mn::DeletePacket(ResponseStoredPackets[loop]);
				}
				OutputFile.close();

				mn::DeletePacket(ResponsePacket);
				State = TERMINATE;
				}
				break; 

			case RECOVER:
				break; 

			case PENDING:
				break; 

			case SUSPEND:
				break; 

			case SUSPENDED:
				break;

			case RELEASE:
				break; 

			case TERMINATE:
				cout << "\nTERMINATE";
				mn::DisconnectClient(0, 0);
				break;

		}

	}

	cout << "\n" << ResponseWritePath[TransferMode].c_str() << " written to /Debug Directory\n";

	system("PAUSE");

	return 0;

}