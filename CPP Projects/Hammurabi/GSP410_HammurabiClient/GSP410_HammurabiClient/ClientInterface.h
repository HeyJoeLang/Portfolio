// ClientInterface class
// =====================
// Connects the Client to the Server and to HammurabiGame

#pragma once

#include "HammurabiDataTypes.h"
#include "WSAErrors.h"
#include <iostream>
#include <iomanip>
#include <Winsock2.h>
#include "View.h"

using namespace std;

//Needs to be the same as ServerInterface
//#define SRVR_ADDRESS "10.14.9.2"
#define SRVR_PORT 7654
#define BUFFER_SIZE 512

#define CLIENTINTERFACE ClientInterface::Instance()

class ClientInterface
{
// member variables
	SOCKET myServerSocket;	

// member functions
private:
	ClientInterface(void);
	ClientInterface(const ClientInterface&);
	ClientInterface* operator=(const ClientInterface&);
	~ClientInterface(void);

	void CleanWSA();
	void ShutAndCleanSocket(SOCKET s);

public:
	// called during initialization
	// connects to the server and returns the initial game state
	OutputData ConnectToServer(void);

	// sends the next turn data to the server, waits for a
	// response from the server and hands the new data back
	// to the view
	OutputData SendToServer(InputData);

	// shuts down the clientinterface once the user quits, or there is an error
	void ShutDown(void);
	
	// accesses the singleton
	static ClientInterface* Instance(void);

	// asks the user for the server's IP
	string GetServerIP(void);
};