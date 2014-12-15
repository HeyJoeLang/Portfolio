#include "ClientInterface.h"

ClientInterface::ClientInterface(void)
{
}

ClientInterface::~ClientInterface(void)
{
}

ClientInterface::ClientInterface(const ClientInterface &mm)
{
}

ClientInterface* ClientInterface::operator=(const ClientInterface &mm)
{
	return this;
}

ClientInterface* ClientInterface::Instance()
{
	static ClientInterface instance;

	return &instance;
}

// called during initialization
// connects to the server and returns the initial game state
OutputData ClientInterface::ConnectToServer(void)
{
	OutputData od;

	memset(&od, 0, sizeof(OutputData));

	//0. Initialize Winsock
	//WSAData holds information about winsock. used for initializing and debugging
	long errcode = 0;
	WSAData myWSAInfo;
	memset(&myWSAInfo, 0, sizeof(WSAData) ); 

	//if there is an error, the ppropriate WSA Error will be filled into errcode and the program will end

	errcode = WSAStartup( 0x0202, &myWSAInfo );				//  <----actually sets up winsock
	WSAErrorsToConsole::ShowWSAStartupError( errcode );

	//describes winsock information
	cout << "desc: " << myWSAInfo.szDescription << endl;
	cout << "desc: " << myWSAInfo.szSystemStatus << endl;
	cout << setbase(16) << showbase << myWSAInfo.wHighVersion << setbase(10) << endl;

	//error checking
	if ( 0 != errcode )
	{
		errcode = WSACleanup();
		if ( SOCKET_ERROR == errcode )
		{
			cout << "WSAStartup: " << endl;
			WSAErrorsToConsole::ShowWSACleanupError( WSAGetLastError() );
		}
		VIEW->EndGame();
		return od;
	}
	
	//If there are no errors, winsock has been sucessfully setup
	cout << "Winsock2 started..." << endl;


	//1. Create a socket for the client
	//Build socket
	myServerSocket = INVALID_SOCKET;							//initialize socket with invalid value
	myServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP );	//builds socket with valid value
	
	//if, for some reason, the build did not take, and the socket is still invalid, display error and shut down
	if ( INVALID_SOCKET == myServerSocket )
	{
		cout << "socket " << endl;
		WSAErrorsToConsole::ShowSocketError( WSAGetLastError() );
		ShutAndCleanSocket( myServerSocket );
		CleanWSA();
		VIEW->EndGame();
		return od;
	}

	//2.  Connect to a socket
	//	Needs an address to connect to
    sockaddr_in srvrAddr;						//initialize serverAddress
    memset(&srvrAddr, 0, sizeof(srvrAddr));		//sets serverAddress to 0
    srvrAddr.sin_family = AF_INET;				//AF_INET = Internet address family

	//although we are connecting locally for hammurabi, it still uses TCP/IP networking
	//to connect to another computer, all you need to do is swap out the SRVR_ADDRESS with the computer's ip address

	string ip = GetServerIP();

    srvrAddr.sin_addr.s_addr = inet_addr(ip.c_str());		//enum for local connections within the same computer
    srvrAddr.sin_port = htons(SRVR_PORT);					//sets the port, port is the connection to the server

	//connects to the socket
	errcode = connect( myServerSocket,
					(SOCKADDR*)&srvrAddr,
					sizeof(srvrAddr) );

	//if connection failed, display error and shut down
	if ( SOCKET_ERROR == errcode )
	{
		cout << "connect to " << ip.c_str() << " failed" << endl;
		WSAErrorsToConsole::ShowConnectError( WSAGetLastError() );
		ShutAndCleanSocket( myServerSocket );
		CleanWSA();
		VIEW->EndGame();
		return od;
	}

	// If iMode!=0, non-blocking mode is enabled.
	u_long iMode=1;
	int err = ioctlsocket(myServerSocket,FIONBIO,&iMode);

	InputData id;

	id.resetGame = true;

	od = SendToServer(id);

	return od;
}

// sends the next turn data to the server, waits for a
// response from the server and hands the new data back
// to the view
OutputData ClientInterface::SendToServer(InputData id)
{
	OutputData od;

	//3.  Send and Receive on the socket
	long errcode = send( myServerSocket, (char*)&id, sizeof(id), 0);

	int numBytes = 0;

	if ( SOCKET_ERROR == errcode )
	{
		cout << "send " << endl;
		WSAErrorsToConsole::ShowSendError( WSAGetLastError() );
		ShutAndCleanSocket( myServerSocket );
		CleanWSA();
		return od;
	}

	do
	{
		numBytes = recv( myServerSocket,(char*)&od, sizeof(od), 0);

		if (numBytes > 0)
		{
			// get the data and return
			return od;
		}
		if (numBytes == 0)
		{
			// do nothing
		}
		else
		{
			int errnum = WSAGetLastError();

			if (errnum == WSAEWOULDBLOCK)
			{
				// do nothing
			}
			else
			{
				cout << "recv " << endl;
				WSAErrorsToConsole::ShowRecvError( WSAGetLastError() );
				ShutAndCleanSocket( myServerSocket );
				CleanWSA();
				return od;
			}
		}

	}
	while( 1 );
}

void ClientInterface::ShutDown(void)
{
	//4.  Disconnect the client
	//Close socket for sending
	long errcode = shutdown( myServerSocket, SD_SEND );
	if ( SOCKET_ERROR == errcode )						//check for errors
	{
		cout << "shutdown " << endl;
		WSAErrorsToConsole::ShowShutdownError( WSAGetLastError() );
		ShutAndCleanSocket( myServerSocket );
		CleanWSA();
		return;
	}
	//Wait for server to close connection
	do
	{
		char buff[BUFFER_SIZE];
		long errcode = recv( myServerSocket, buff, BUFFER_SIZE, 0);
		if ( errcode > 0 )
			cout << "Received " << errcode << " bytes." << endl;
		else if ( errcode == 0 )
			cout << "Closed." << endl;
		else
		{
			cout << "recv " << endl;
			WSAErrorsToConsole::ShowRecvError( WSAGetLastError() );
			ShutAndCleanSocket( myServerSocket );
			CleanWSA();
			return;
		}
	}
	while( errcode > 0 );

	ShutAndCleanSocket( myServerSocket );

	//5.  Release Winsock
	CleanWSA();

	cout << "ClientInterface is done." << endl;
	return;

}

void ClientInterface::ShutAndCleanSocket( SOCKET s )
{
	long errcode = 0;
	errcode = shutdown( s, SD_BOTH );
	if ( SOCKET_ERROR == errcode )
	{
		WSAErrorsToConsole::ShowShutdownError( errcode );
	}

	errcode = closesocket( s );
	if ( SOCKET_ERROR == errcode )
	{
		WSAErrorsToConsole::ShowCloseSocketError( errcode );
	}
}

void ClientInterface::CleanWSA()
{
	long errcode = 0;

	errcode = WSACleanup();
	if ( errcode == SOCKET_ERROR )
	{
		WSAErrorsToConsole::ShowWSACleanupError( WSAGetLastError() );
	}
}

string ClientInterface::GetServerIP(void)
{
	std::cout << "Please enter the server's IP address" << std::endl;
	string s;
	std::getline( std::cin, s);

	std::cout << "Got: " << s.c_str() << std::endl;

	return s;
}