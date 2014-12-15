#include "ServerInterface.h"

// global critical section used for thread synchronization
CRITICAL_SECTION g_criticalSection;

// function declarations for the main thread code
void StartThread(threadData* data);
void CleanWSA(void);
void MutexRelease(HANDLE handle);
void ShutdownSocket(SOCKET s);

ServerInterface::ServerInterface(void)
{
}

ServerInterface::~ServerInterface(void)
{
}

ServerInterface::ServerInterface(const ServerInterface &mm)
{
}

ServerInterface* ServerInterface::operator=(const ServerInterface &mm)
{
	return this;
}

ServerInterface* ServerInterface::Instance()
{
	static ServerInterface instance;

	return &instance;
}

void ServerInterface::ShutDown(void)
{

}

int ServerInterface::Run(void)
{
	std::cout << "Hammurabi Game by Chris Dickinson & Joe Lang" << std::endl;
	std::cout << "============================================" << std::endl;
	std::cout << "Server" << std::endl;
	std::cout << std::endl;
	long errorCode = 0;

	// created prior to thread creation so all threads have
	// access to it
	threadData sharedData;

	// only want one sever running on this IP and port
	sharedData.mutex = NULL;
	sharedData.mutex = CreateMutex(NULL, true, "HammurabiGameMutex");
	errorCode = GetLastError();
	if (errorCode == ERROR_ALREADY_EXISTS)
	{
		std::cout << "Mutex is already running!" << std::endl;
		return 1;
	}

	std::cout << "I LIVE AGAIN!" << std::endl;

	// initialize WinSock

	// create a wsa data to store info
	WSAData wsaInfo;

	// zero its memory
	memset(&wsaInfo, 0, sizeof(WSAData));

	// check the version. Verify its version 2.2 (0x0202)
	errorCode = WSAStartup( 0x0202, &wsaInfo );

	// did the startup work?
	WSAErrorsToConsole::ShowWSAStartupError (errorCode);

	// print the description and status
	std::cout << "Dscptn: " << wsaInfo.szDescription << std::endl;
	std::cout << "Status: " << wsaInfo.szSystemStatus << std::endl;
	std::cout << std::setbase(16) << std::showbase << wsaInfo.wHighVersion << std::setbase(10) << std::endl; // change to base 16, print, then set back to base 10

	// was there an error?
	if (errorCode != 0)
	{
		CleanWSA();
		MutexRelease( sharedData.mutex);
		CloseHandle( sharedData.mutex);
		return 1;
	}

	// winsock 2 has initialized
	std::cout << "Winsock 2 has initialized!" << std::endl;

	// create the socket
	SOCKET serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		WSAErrorsToConsole::ShowSocketError(WSAGetLastError());
		ShutdownSocket(serverSocket);
		CleanWSA();
		MutexRelease(sharedData.mutex);
		CloseHandle(sharedData.mutex);
		return 1;
	}

	// enable non-blocking mode for the server socket
	u_long non_blocking = true; // anything but false = non-blocking mode
	int ierrorCode = ioctlsocket(serverSocket, FIONBIO, &non_blocking);

	// get the ip address
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_NONE;
	serverAddress.sin_addr.s_addr = inet_addr(GetHostIP());

	// was there an error getting the IP address?
	if (serverAddress.sin_addr.s_addr == INADDR_NONE)
	{
		std::cout << "IP address is incorrect: " << GetHostIP() << std::endl;
		ShutdownSocket(serverSocket);
		CleanWSA();
		MutexRelease(sharedData.mutex);
		CloseHandle(sharedData.mutex);
		return 1;
	}

	// get the port
	serverAddress.sin_port = htons(SERVER_PORT);

	// bind the socket
	errorCode = bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(sockaddr_in));

	// was there an error?
	if (errorCode == SOCKET_ERROR)
	{
		WSAErrorsToConsole::ShowBindError(errorCode);
		ShutdownSocket(serverSocket);
		CleanWSA();
		MutexRelease(sharedData.mutex);
		CloseHandle(sharedData.mutex);
		return 1;
	}

	// begin listening on the socket
	errorCode = listen(serverSocket, SOMAXCONN);
	if (errorCode == SOCKET_ERROR)
	{
		WSAErrorsToConsole::ShowListenError( errorCode );
		ShutdownSocket(serverSocket);
		CleanWSA();
		MutexRelease(sharedData.mutex);
		CloseHandle(sharedData.mutex);
		return 1;
	}

	// create a clientsocket to accept the client on
	SOCKET clientSocket = INVALID_SOCKET;
	sockaddr_in clientAddress;
	int clientAddrSize = sizeof(sockaddr_in);

	// create the shared message buffer
	char sharedBuff[MSG_BUFFER_SIZE];
	memset(sharedBuff, '\0', MSG_BUFFER_SIZE * sizeof(char));

	// initialize the rest of the sharedData object
	sharedData.socket = INVALID_SOCKET;
	sharedData.msgBuff = sharedBuff;
	sharedData.numThreads = 0;

	// initialize the critical section
	InitializeCriticalSection(&g_criticalSection);

	bool running = true;

	// run in a loop
	while (running)
	{
		// accept a socket if the client tries to connect
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &clientAddrSize);

		// was there an error?
		if (clientSocket == INVALID_SOCKET)
		{
			errorCode = WSAGetLastError();

			// Workaround: ignore the error if it is WSAEWOULDBLOCK
			// this error keeps getting spammed regardless of the fact
			// that we're running in non-blocking mode.
			if (errorCode != WSAEWOULDBLOCK)
			{
				WSAErrorsToConsole::ShowAcceptError(errorCode);
				ShutdownSocket(serverSocket);
				ShutdownSocket(clientSocket);
				CleanWSA();
				MutexRelease(sharedData.mutex);
				CloseHandle(sharedData.mutex);
				return 1;
			}
		}
		else
		{
			// increment the thread count
			InterlockedIncrement64( &(sharedData.numThreads));
			
			// store the client socket in the shared data
			sharedData.socket = clientSocket;

			// start a new thread, using the TalkOnThread() function
			// sending sharedData as a parameter
			_beginthread( (void(__cdecl*)(void*))StartThread, 0, &sharedData);
		}
	}

	// WARNING: Code cannot reach this point, yet, since 'running' is always true

	// do a graceful shutdown
	
	// make sure all threads have closed before we try to kill the mutex/critical section
	LONGLONG numThreads = 0;
	do
	{
		InterlockedOr64( &numThreads, sharedData.numThreads );
		if (numThreads > 0)
			Sleep(50); // wait 50 cycles and try again
	}
	while (numThreads != 0);

	// should be safe to delete Critical Section now
	DeleteCriticalSection(&g_criticalSection);

	// shutdown everything
	ShutdownSocket(serverSocket);
	ShutdownSocket(clientSocket);
	CleanWSA();
	MutexRelease(sharedData.mutex);
	CloseHandle(sharedData.mutex);

	std::cout << "Server shutting down. Goodbye." << std::endl;

	// return
	return 0;
}

// Calls WSACleanUp and shows errors
void CleanWSA(void)
{
	long errcode = 0;

	errcode = WSACleanup();
	if ( errcode == SOCKET_ERROR )
	{
		WSAErrorsToConsole::ShowWSACleanupError( WSAGetLastError() );
	}
}

// Calls ReleaseMutex and shows msg on error
void MutexRelease( HANDLE handle )
{
	if ( !ReleaseMutex(handle))
	{
		std::cout << "Mutex did not release" << std::endl;
	}
}

// Calls shutdown( s, SD_BOTH ), closesocket( s ), and shows errors
void ShutdownSocket( SOCKET s )
{
	long errcode = 0;
	// shutdown sending and receiving (both) on the socket
	errcode = shutdown( s, SD_BOTH );
	if ( SOCKET_ERROR == errcode )
	{
		WSAErrorsToConsole::ShowShutdownError( errcode );
	}

	// close the socket
	errcode = closesocket( s );
	if ( SOCKET_ERROR == errcode )
	{
		WSAErrorsToConsole::ShowCloseSocketError( errcode );
	}
}

void StartThread(threadData * data)
{
	// this is the function that each server thread (managing
	// a single client) will run through. It should only return
	// when the client disconnects or some error has occured

	// initialize some values
	long numBytes = 0;
	long errorCode = SOCKET_ERROR;
	LONGLONG id = 0;

	// get and store the client socket from the buffer data
	// WARNING: Doesn't this need to use a Critical Section?!
	// 2 clients connecting simultaneously could ruin our day
	SOCKET clientSocket = data->socket;
	//SOCKET clientSocket;
	//InterlockedOr64(&clientSocket, data->socket);

	// set non-blocking mode for the client socket
	u_long non_blocking = 1;
	int error = ioctlsocket(clientSocket, FIONBIO, &non_blocking);

	// read numThreads into id and treat it as its ID number
	InterlockedOr64(&id, data->numThreads);

	// create a new HammurabiGame
	HammurabiGame game;

	// enter the while loop
	do
	{
		// enter the critical section
		EnterCriticalSection(&g_criticalSection);

		// receive data from the client
		// if this is the first communication, we assume they want
		// to start a new game
		numBytes = recv(clientSocket, data->msgBuff, MSG_BUFFER_SIZE, 0);

		// if we received something, HANDLE IT!
		if (numBytes > 0)
		{
			// read the message buffer into an InputData object
			InputData* input = (InputData*)data->msgBuff;
			std::cout << "Thread " << id << " Received " << numBytes << " bytes." << std::endl;
			
			// send this data to the game for processing
			OutputData output = game.ProcessTurn(*input);

			// send the output data back to the Client
			errorCode = send(clientSocket, (char*)&output, sizeof(OutputData), 0);
			LeaveCriticalSection( &g_criticalSection );

			// was there an error sending?
			if (errorCode == SOCKET_ERROR)
			{
				std::cout << "Failed to send message to client!" << std::endl;
				WSAErrorsToConsole::ShowSendError(WSAGetLastError());
				
				long errcode = 0;
				errcode = shutdown( clientSocket, SD_BOTH );
				if ( SOCKET_ERROR == errcode )
				{
					WSAErrorsToConsole::ShowShutdownError( errcode );
				}

				errcode = closesocket( clientSocket );
				if ( SOCKET_ERROR == errcode )
				{
					WSAErrorsToConsole::ShowCloseSocketError( errcode );
				}

				_endthread();
				return;
			}
		}
		// if we got 0 bytes, the client must have disconnected
		else if (numBytes == 0)
		{
			LeaveCriticalSection(&g_criticalSection);
			std::cout << "Thread " << id << " disconnected." << std::endl;
			break;
		}
		// otherwise an error occurreds
		else
		{
			int errnum = WSAGetLastError();

			// ignore 'wouldblock errors'
			if (errnum == WSAEWOULDBLOCK)
			{
				// try again later
				LeaveCriticalSection(&g_criticalSection);
			}
			else
			{
				// shutdown
				LeaveCriticalSection(&g_criticalSection);
				WSAErrorsToConsole::ShowRecvError(WSAGetLastError());
				ShutdownSocket(clientSocket);
				_endthread();
				return;
			}
		}
	}
	while(1);

	// shutdown
	int errCode = shutdown(clientSocket, SD_SEND);

	if (errCode == SOCKET_ERROR)
	{
		WSAErrorsToConsole::ShowShutdownError(WSAGetLastError());
		ShutdownSocket(clientSocket);
		_endthread();
		return;
	}

	// need to empty the socket of incoming messages

	ShutdownSocket(clientSocket);
	Sleep(500);
	_endthread();
	return;
}

char*  ServerInterface::GetHostIP(void)
{
	char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        std::cerr << "Error " << WSAGetLastError() << " when getting local host name." << std::endl;
        return "";
    }
    std::cout << "Host name is " << ac << "." << std::endl;

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        std::cerr << "Yow! Bad host lookup." << std::endl;
        return "";
    }

	in_addr addr;

	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	
	std::cout << "Host IP is " << inet_ntoa(addr) << std::endl;
	
	return inet_ntoa(addr);

	

	/*

    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        std::cout << "Address " << i << ": " << inet_ntoa(addr) << std::endl;
    }*/

}