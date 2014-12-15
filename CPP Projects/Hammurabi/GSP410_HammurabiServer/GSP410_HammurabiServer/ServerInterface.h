// ServerInterface class
// =====================
// Creates the Server that connects the client to HammurabiGame

#pragma once

#include "HammurabiDataTypes.h"
#include "HammurabiGame.h"
#include <iostream>
#include <iomanip>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include "WSAErrors.h"

//#define SERVER_IP			"127.0.0.1"
#define SERVER_PORT			7654
#define MSG_BUFFER_SIZE		512		// buffer size for messages to/from clients
#define KB_BUFFER_SIZE		128		// buffer size for keyboard events

// struct to hold data used by all threads
struct threadData
{
	SOCKET socket;	// active connection
	HANDLE mutex;	// shared mutex
	char * msgBuff;	// shared message buffer
	LONGLONG numThreads;	// used to determine the thread id
};

#define SERVERINTERFACE ServerInterface::Instance()

class ServerInterface
{
// member variables

// member functions
private:
	ServerInterface(void);
	ServerInterface(const ServerInterface&);
	ServerInterface* operator=(const ServerInterface&);
	~ServerInterface(void);

public:
	// launches the main server thread that listens for clients
	int Run(void);

	// shuts down the ServerInterface once the user quits, or there is an error
	void ShutDown(void);
	
	// accesses the singleton
	static ServerInterface* Instance(void);

	// gets the IP address of this host and prints it to the console
	char* GetHostIP(void);
};