// WSAErrors.cpp
//
// by Brian Schick
//
// classes to print out Winsock2 Networking errors
#pragma once
#include "WSAErrors.h"
#include <iostream>
#include <iomanip>
#include <Winsock2.h>
using namespace std;

// The VS2008 help page at ms-help://MS.VSCC.v90/MS.MSDNQTR.v90.en/winsock/winsock/windows_sockets_error_codes_2.htm#winsock.wsaenotsock_2
const long WSAErrorsToConsole::ShowWinsock2Error( const long errcode )
{
	switch( errcode )
	{
	case WSA_INVALID_HANDLE:
		cout << "An application attempts to use an event object, but the specified handle is not valid. Note that this error is returned by the operating system, so the error number may change in future releases of Windows" << endl;
		break;
	case WSA_NOT_ENOUGH_MEMORY:
		cout << "An application used a Windows Sockets function that directly maps to a Windows function. The Windows function is indicating a lack of required memory resources. Note that this error is returned by the operating system, so the error number may change in future releases of Windows" << endl;
		break;
	case WSA_INVALID_PARAMETER:
		cout << "An application used a Windows Sockets function which directly maps to a Windows function. The Windows function is indicating a problem with one or more parameters. Note that this error is returned by the operating system, so the error number may change in future releases of Windows" << endl;
		break;
	case WSA_OPERATION_ABORTED:
		cout << "An overlapped operation was canceled due to the closure of the socket, or the execution of the SIO_FLUSH command in WSAIoctl. Note that this error is returned by the operating system, so the error number may change in future releases of Windows" << endl;
		break;
	case WSA_IO_INCOMPLETE:
		cout << "The application has tried to determine the status of an overlapped operation which is not yet completed. Applications that use WSAGetOverlappedResult (with the fWait flag set to FALSE) in a polling mode to determine when an overlapped operation has completed, get this error code until the operation is complete. Note that this error is returned by the operating system, so the error number may change in future releases of Windows" << endl;
		break;
	case WSA_IO_PENDING:
		cout << "The application has initiated an overlapped operation that cannot be completed immediately. A completion indication will be given later when the operation has been completed. Note that this error is returned by the operating system, so the error number may change in future releases of Windows" << endl;
		break;
	case WSAEINTR:
		cout << "A blocking operation was interrupted by a call to WSACancelBlockingCall" << endl;
		break;
	case WSAEBADF:
		cout << "The file handle supplied is not valid" << endl;
		break;
	case WSAEACCES:
		cout << "An attempt was made to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt(SO_BROADCAST). "
			<< "\n\nAnother possible reason for the WSAEACCES error is that when the bind function is called (on Windows NT 4 SP4 or later), another application, service, or kernel mode driver is bound to the same address with exclusive access. Such exclusive access is a new feature of Windows NT 4 SP4 and later, and is implemented by using the SO_EXCLUSIVEADDRUSE option" << endl;
		break;
	case WSAEFAULT:
		cout << "The system detected an invalid pointer address in attempting to use a pointer argument of a call. This error occurs if an application passes an invalid pointer value, or if the length of the buffer is too small. For instance, if the length of an argument, which is a sockaddr structure, is smaller than the sizeof(sockaddr)." << endl;
		break;
	case WSAEINVAL:
		cout << "Some invalid argument was supplied (for example, specifying an invalid level to the setsockopt function). In some instances, it also refers to the current state of the socket—for instance, calling accept on a socket that is not listening" << endl;
		break;
	case WSAEMFILE:
		cout << "Too many open sockets. Each implementation may have a maximum number of socket handles available, either globally, per process, or per thread" << endl;
		break;
	case WSAEWOULDBLOCK:
		cout << "This error is returned from operations on nonblocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket. It is a nonfatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a nonblocking SOCK_STREAM socket, since some time must elapse for the connection to be established" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking operation is currently executing. Windows Sockets only allows a single blocking operation—per- task or thread—to be outstanding, and if any other function call is made (whether or not it references that or any other socket) the function fails with the WSAEINPROGRESS error" << endl;
		break;
	case WSAEALREADY:
		cout << "An operation was attempted on a nonblocking socket with an operation already in progress—that is, calling connect a second time on a nonblocking socket that is already connecting, or canceling an asynchronous request (WSAAsyncGetXbyY) that has already been canceled or completed" << endl;
		break;
	case WSAENOTSOCK:
		cout << "An operation was attempted on something that is not a socket. Either the socket handle parameter did not reference a valid socket, or for select, a member of an fd_set was not valid" << endl;
		break;
	case WSAEDESTADDRREQ:
		cout << "A required address was omitted from an operation on a socket. For example, this error is returned if sendto is called with the remote address of ADDR_ANY" << endl;
		break;
	case WSAEMSGSIZE:
		cout << "A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram was smaller than the datagram itself" << endl;
		break;
	case WSAEPROTOTYPE:
		cout << "A protocol was specified in the socket function call that does not support the semantics of the socket type requested. For example, the ARPA Internet UDP protocol cannot be specified with a socket type of SOCK_STREAM" << endl;
		break;
	case WSAENOPROTOOPT:
		cout << "An unknown, invalid or unsupported option or level was specified in a getsockopt or setsockopt call" << endl;
		break;
	case WSAEPROTONOSUPPORT:
		cout << "The requested protocol has not been configured into the system, or no implementation for it exists. For example, a socket call requests a SOCK_DGRAM socket, but specifies a stream protocol" << endl;
		break;
	case WSAESOCKTNOSUPPORT:
		cout << "The support for the specified socket type does not exist in this address family. For example, the optional type SOCK_RAW might be selected in a socket call, and the implementation does not support SOCK_RAW sockets at all" << endl;
		break;
	case WSAEOPNOTSUPP:
		cout << "The attempted operation is not supported for the type of object referenced. Usually this occurs when a socket descriptor to a socket that cannot support this operation is trying to accept a connection on a datagram socket" << endl;
		break;
	case WSAEPFNOSUPPORT:
		cout << "The protocol family has not been configured into the system or no implementation for it exists. This message has a slightly different meaning from WSAEAFNOSUPPORT. However, it is interchangeable in most cases, and all Windows Sockets functions that return one of these messages also specify WSAEAFNOSUPPORT" << endl;
		break;
	case WSAEAFNOSUPPORT:
		cout << "An address incompatible with the requested protocol was used. All sockets are created with an associated address family (that is, AF_INET for Internet Protocols) and a generic protocol type (that is, SOCK_STREAM). This error is returned if an incorrect protocol is explicitly requested in the socket call, or if an address of the wrong family is used for a socket, for example, in sendto" << endl;
		break;
	case WSAEADDRINUSE:
		cout << "Typically, only one usage of each socket address (protocol/IP address/port) is permitted. This error occurs if an application attempts to bind a socket to an IP address/port that has already been used for an existing socket, or a socket that was not closed properly, or one that is still in the process of closing. For server applications that need to bind multiple sockets to the same port number, consider using setsockopt (SO_REUSEADDR). Client applications usually need not call bind at all— connect chooses an unused port automatically. When bind is called with a wildcard address (involving ADDR_ANY), a WSAEADDRINUSE error could be delayed until the specific address is committed. This could happen with a call to another function later, including connect, listen, WSAConnect, or WSAJoinLeaf" << endl;
		break;
	case WSAEADDRNOTAVAIL:
		cout << "The requested address is not valid in its context. This normally results from an attempt to bind to an address that is not valid for the local computer. This can also result from connect, sendto, WSAConnect, WSAJoinLeaf, or WSASendTo when the remote address or port is not valid for a remote computer (for example, address or port 0)." << endl;
		break;
	case WSAENETDOWN:
		cout << "A socket operation encountered a dead network. This could indicate a serious failure of the network system (that is, the protocol stack that the Windows Sockets DLL runs over), the network interface, or the local network itself" << endl;
		break;
	case WSAENETUNREACH:
		cout << "A socket operation was attempted to an unreachable network. This usually means the local software knows no route to reach the remote host" << endl;
		break;
	case WSAENETRESET:
		cout << "The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. It can also be returned by setsockopt if an attempt is made to set SO_KEEPALIVE on a connection that has already failed" << endl;
		break;
	case WSAECONNABORTED:
		cout << "An established connection was aborted by the software in your host computer, possibly due to a data transmission time-out or protocol error" << endl;
		break;
	case WSAECONNRESET:
		cout << "An existing connection was forcibly closed by the remote host. This normally results if the peer application on the remote host is suddenly stopped, the host is rebooted, the host or remote network interface is disabled, or the remote host uses a hard close (see setsockopt for more information on the SO_LINGER option on the remote socket). This error may also result if a connection was broken due to keep-alive activity detecting a failure while one or more operations are in progress. Operations that were in progress fail with WSAENETRESET. Subsequent operations fail with WSAECONNRESET" << endl;
		break;
	case WSAENOBUFS:
		cout << "An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full" << endl;
		break;
	case WSAEISCONN:
		cout << "A connect request was made on an already-connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket (for SOCK_STREAM sockets, the to parameter in sendto is ignored) although other implementations treat this as a legal occurrence" << endl;
		break;
	case WSAENOTCONN:
		cout << "A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using sendto) no address was supplied. Any other type of operation might also return this error—for example, setsockopt setting SO_KEEPALIVE if the connection has been reset" << endl;
		break;
	case WSAESHUTDOWN:
		cout << "A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. By calling shutdown a partial close of a socket is requested, which is a signal that sending or receiving, or both have been discontinued" << endl;
		break;
	case WSAETOOMANYREFS:
		cout << "Too many references to some kernel object" << endl;
		break;
	case WSAETIMEDOUT:
		cout << "A connection attempt failed because the connected party did not properly respond after a period of time, or the established connection failed because the connected host has failed to respond" << endl;
		break;
	case WSAECONNREFUSED:
		cout << "No connection could be made because the target computer actively refused it. This usually results from trying to connect to a service that is inactive on the foreign host—that is, one with no server application running" << endl;
		break;
	case WSAELOOP:
		cout << "A socket operation failed because the destination host is down. A socket operation encountered a dead host. Networking activity on the local host has not been initiated. These conditions are more likely to be indicated by the error WSAETIMEDOUT" << endl;
		break;
	case WSAENAMETOOLONG:
		cout << "A name component or a name was too long" << endl;
		break;
	case WSAEHOSTDOWN:
		cout << "A socket operation failed because the destination host is down. A socket operation encountered a dead host. Networking activity on the local host has not been initiated. These conditions are more likely to be indicated by the error WSAETIMEDOUT" << endl;
		break;
	case WSAEHOSTUNREACH:
		cout << "A socket operation was attempted to an unreachable host. See WSAENETUNREACH" << endl;
		break;
	case WSAENOTEMPTY:
		cout << "Cannot remove a directory that is not empty" << endl;
		break;
	case WSAEPROCLIM:
		cout << "A Windows Sockets implementation may have a limit on the number of applications that can use it simultaneously.WSAStartup may fail with this error if the limit has been reached" << endl;
		break;
	case WSAEUSERS:
		cout << "Ran out of user quota" << endl;
		break;
	case WSAEDQUOT:
		cout << "Ran out of disk quota" << endl;
		break;
	case WSAESTALE:
		cout << "The file handle reference is no longer available" << endl;
		break;
	case WSAEREMOTE:
		cout << "The item is not available locally" << endl;
		break;
	case WSASYSNOTREADY:
		cout << "This error is returned by WSAStartup if the Windows Sockets implementation cannot function at this time because the underlying system it uses to provide network services is currently unavailable. Users should check:\n\n"
			<< "That the appropriate Windows Sockets DLL file is in the current path. \n\n"
			<< "That they are not trying to use more than one Windows Sockets implementation simultaneously. If there is more than one Winsock DLL on your system, be sure the first one in the path is appropriate for the network subsystem currently loaded. \n\n"
			<< "The Windows Sockets implementation documentation to be sure all necessary components are currently installed and configured correctly" << endl;
		break;
	case WSAVERNOTSUPPORTED:
		cout << "The current Windows Sockets implementation does not support the Windows Sockets specification version requested by the application. Check that no old Windows Sockets DLL files are being accessed" << endl;
		break;
	case WSANOTINITIALISED:
		cout << "Either the application has not called WSAStartup or WSAStartup failed. The application may be accessing a socket that the current active task does not own (that is, trying to share a socket between tasks), or WSACleanup has been called too many times" << endl;
		break;
	case WSAEDISCON:
		cout << "Returned by WSARecv and WSARecvFrom to indicate that the remote party has initiated a graceful shutdown sequence" << endl;
		break;
	case WSAENOMORE:
		cout << "No more results can be returned by the WSALookupServiceNext function" << endl;
		break;
	case WSAECANCELLED:
		cout << "A call to the WSALookupServiceEnd function was made while this call was still processing. The call has been canceled" << endl;
		break;
	case WSAEINVALIDPROCTABLE:
		cout << "The service provider procedure call table is invalid. A service provider returned a bogus procedure table to Ws2_32.dll. This is usually caused by one or more of the function pointers being NULL" << endl;
		break;
	case WSAEINVALIDPROVIDER:
		cout << "The requested service provider is invalid. This error is returned by the WSCGetProviderInfo and WSCGetProviderInfo32 functions if the protocol entry specified could not be found. This error is also returned if the service provider returned a version number other than 2.0" << endl;
		break;
	case WSAEPROVIDERFAILEDINIT:
		cout << "The requested service provider could not be loaded or initialized. This error is returned if either a service provider's DLL could not be loaded (LoadLibrary failed) or the provider's WSPStartup or NSPStartup function failed" << endl;
		break;
	case WSASYSCALLFAILURE:
		cout << "A system call that should never fail has failed. This is a generic error code, returned under various conditions.\n\n"
			<< "Returned when a system call that should never fail does fail. For example, if a call to WaitForMultipleEvents fails or one of the registry functions fails trying to manipulate the protocol/namespace catalogs.\n\n"
			<< "Returned when a provider does not return SUCCESS and does not provide an extended error code. Can indicate a service provider implementation error" << endl;
		break;
	case WSASERVICE_NOT_FOUND:
		cout << "No such service is known. The service cannot be found in the specified name space" << endl;
		break;
	case WSATYPE_NOT_FOUND:
		cout << "The specified class was not found" << endl;
		break;
	case WSA_E_NO_MORE:
		cout << "No more results can be returned by the WSALookupServiceNext function" << endl;
		break;
	case WSA_E_CANCELLED:
		cout << "A call to the WSALookupServiceEnd function was made while this call was still processing. The call has been canceled" << endl;
		break;
	case WSAEREFUSED:
		cout << "A database query failed because it was actively refused" << endl;
		break;
	case WSAHOST_NOT_FOUND:
		cout << "No such host is known. The name is not an official host name or alias, or it cannot be found in the database(s) being queried. This error may also be returned for protocol and service queries, and means that the specified name could not be found in the relevant database" << endl;
		break;
	case WSATRY_AGAIN:
		cout << "This is usually a temporary error during host name resolution and means that the local server did not receive a response from an authoritative server. A retry at some time later may be successful" << endl;
		break;
	case WSANO_RECOVERY:
		cout << "This indicates that some sort of nonrecoverable error occurred during a database lookup. This may be because the database files (for example, BSD-compatible HOSTS, SERVICES, or PROTOCOLS files) could not be found, or a DNS request was returned by the server with a severe error" << endl;
		break;
	case WSANO_DATA:
		cout << "The requested name is valid and was found in the database, but it does not have the correct associated data being resolved for. The usual example for this is a host name-to-address translation attempt (using gethostbyname or WSAAsyncGetHostByName) which uses the DNS (Domain Name Server). An MX record is returned but no A record—indicating the host itself exists, but is not directly reachable" << endl;
		break;
	case WSA_QOS_RECEIVERS:
		cout << "At least one QOS reserve has arrived" << endl;
		break;
	case WSA_QOS_SENDERS:
		cout << "At least one QOS send path has arrived" << endl;
		break;
	case WSA_QOS_NO_SENDERS:
		cout << "There are no QOS senders" << endl;
		break;
	case WSA_QOS_NO_RECEIVERS:
		cout << "There are no QOS receivers" << endl;
		break;
	case WSA_QOS_REQUEST_CONFIRMED:
		cout << "The QOS reserve request has been confirmed" << endl;
		break;
	case WSA_QOS_ADMISSION_FAILURE:
		cout << "A QOS error occurred due to lack of resources" << endl;
		break;
	case WSA_QOS_POLICY_FAILURE:
		cout << "The QOS request was rejected because the policy system couldn’t allocate the requested resource within the existing policy" << endl;
		break;
	case WSA_QOS_BAD_STYLE:
		cout << "An unknown or conflicting QOS style was encountered" << endl;
		break;
	case WSA_QOS_BAD_OBJECT:
		cout << "A problem was encountered with some part of the filterspec or the provider-specific buffer in general" << endl;
		break;
	case WSA_QOS_TRAFFIC_CTRL_ERROR:
		cout << "An error with the underlying traffic control (TC) API as the generic QOS request was converted for local enforcement by the TC API. This could be due to an out of memory error or to an internal QOS provider error" << endl;
		break;
	case WSA_QOS_GENERIC_ERROR:
		cout << "A general QOS error" << endl;
		break;
	case WSA_QOS_ESERVICETYPE:
		cout << "An invalid or unrecognized service type was found in the QOS flowspec" << endl;
		break;
	case WSA_QOS_EFLOWSPEC:
		cout << "An invalid or inconsistent flowspec was found in the QOS structure" << endl;
		break;
	case WSA_QOS_EPROVSPECBUF:
		cout << "An invalid QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_EFILTERSTYLE:
		cout << "An invalid QOS filter style was used" << endl;
		break;
	case WSA_QOS_EFILTERTYPE:
		cout << "An invalid QOS filter type was used" << endl;
		break;
	case WSA_QOS_EFILTERCOUNT:
		cout << "An incorrect number of QOS FILTERSPECs were specified in the FLOWDESCRIPTOR" << endl;
		break;
	case WSA_QOS_EOBJLENGTH:
		cout << "An object with an invalid ObjectLength field was specified in the QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_EFLOWCOUNT:
		cout << "An incorrect number of flow descriptors was specified in the QOS structure" << endl;
		break;
	case WSA_QOS_EUNKOWNPSOBJ:
		cout << "An unrecognized object was found in the QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_EPOLICYOBJ:
		cout << "An invalid policy object was found in the QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_EFLOWDESC:
		cout << "An invalid QOS flow descriptor was found in the flow descriptor list" << endl;
		break;
	case WSA_QOS_EPSFLOWSPEC:
		cout << "An invalid or inconsistent flowspec was found in the QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_EPSFILTERSPEC:
		cout << "An invalid FILTERSPEC was found in the QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_ESDMODEOBJ:
		cout << "An invalid shape discard mode object was found in the QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_ESHAPERATEOBJ:
		cout << "An invalid shaping rate object was found in the QOS provider-specific buffer" << endl;
		break;
	case WSA_QOS_RESERVED_PETYPE:
		cout << "A reserved policy element was found in the QOS provider-specific buffer" << endl;
		break;

	default:
		cout << "unknown error" << endl;
		break;
	}
	return errcode;
}

const long WSAErrorsToConsole::ShowConnectError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEADDRINUSE:
		cout << "The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs when executing bind, but could be delayed until this function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of this function" << endl;
		break;
	case WSAEINTR:
		cout << "The blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAEALREADY:
		cout << "A nonblocking connect call is in progress on the specified socket.\nNote  In order to preserve backward compatibility, this error is reported as WSAEINVAL to Windows Sockets 1.1 applications that link to either Winsock.dll or Wsock32.dll" << endl;
		break;
	case WSAEADDRNOTAVAIL:
		cout << "The remote address is not a valid address (such as ADDR_ANY)." << endl;
		break;
	case WSAEAFNOSUPPORT:
		cout << "Addresses in the specified family cannot be used with this socket" << endl;
		break;
	case WSAECONNREFUSED:
		cout << "The attempt to connect was forcefully rejected" << endl;
		break;
	case WSAEFAULT:
		cout << "The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, or the name parameter contains incorrect address format for the associated address family" << endl;
		break;
	case WSAEINVAL:
		cout << "The parameter s is a listening socket" << endl;
		break;
	case WSAEISCONN:
		cout << "The socket is already connected (connection-oriented sockets only)." << endl;
		break;
	case WSAENETUNREACH:
		cout << "The network cannot be reached from this host at this time" << endl;
		break;
	case WSAEHOSTUNREACH:
		cout << "A socket operation was attempted to an unreachable host" << endl;
		break;
	case WSAENOBUFS:
		cout << "No buffer space is available. The socket cannot be connected" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	case WSAETIMEDOUT:
		cout << "Attempt to connect timed out without establishing a connection" << endl;
		break;
	case WSAEWOULDBLOCK:
		cout << "The socket is marked as nonblocking and the connection cannot be completed immediately" << endl;
		break;
	case WSAEACCES:
		cout << "Attempt to connect datagram socket to broadcast address failed because setsockopt option SO_BROADCAST is not enabled" << endl;
		break;

	default:
		break;
	}

	return errcode;
}

const long WSAErrorsToConsole::ShowSendError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEACCES:
		cout << "The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST socket option to enable use of the broadcast address" << endl;
		break;
	case WSAEINTR:
		cout << "A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAEFAULT:
		cout << "The buf parameter is not completely contained in a valid part of the user address space" << endl;
		break;
	case WSAENETRESET:
		cout << "The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress" << endl;
		break;
	case WSAENOBUFS:
		cout << "No buffer space is available" << endl;
		break;
	case WSAENOTCONN:
		cout << "The socket is not connected" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	case WSAEOPNOTSUPP:
		cout << "MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations" << endl;
		break;
	case WSAESHUTDOWN:
		cout << "The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH" << endl;
		break;
	case WSAEWOULDBLOCK:
		cout << "The socket is marked as nonblocking and the requested operation would block" << endl;
		break;
	case WSAEMSGSIZE:
		cout << "The socket is message oriented, and the message is larger than the maximum supported by the underlying transport" << endl;
		break;
	case WSAEHOSTUNREACH:
		cout << "The remote host cannot be reached from this host at this time" << endl;
		break;
	case WSAEINVAL:
		cout << "The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled" << endl;
		break;
	case WSAECONNABORTED:
		cout << "The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable" << endl;
		break;
	case WSAECONNRESET:
		cout << "The virtual circuit was reset by the remote side executing a hard or abortive close. For UDP sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a 'Port Unreachable' ICMP packet. The application should close the socket as it is no longer usable" << endl;
		break;
	case WSAETIMEDOUT:
		cout << "The connection has been dropped, because of a network failure or because the system on the other end went down without notice" << endl;
		break;
	default:
		break;
	}
	return errcode;
}

const long WSAErrorsToConsole::ShowRecvError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEFAULT:
		cout << "The buf parameter is not completely contained in a valid part of the user address space" << endl;
		break;
	case WSAENOTCONN:
		cout << "The socket is not connected" << endl;
		break;
	case WSAEINTR:
		cout << "The (blocking) call was canceled through WSACancelBlockingCall" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAENETRESET:
		cout << "The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	case WSAEOPNOTSUPP:
		cout << "MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations" << endl;
		break;
	case WSAESHUTDOWN:
		cout << "The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH" << endl;
		break;
	case WSAEWOULDBLOCK:
		cout << "The socket is marked as nonblocking and the receive operation would block" << endl;
		break;
	case WSAEMSGSIZE:
		cout << "The message was too large to fit into the specified buffer and was truncated" << endl;
		break;
	case WSAEINVAL:
		cout << "The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative" << endl;
		break;
	case WSAECONNABORTED:
		cout << "The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable" << endl;
		break;
	case WSAETIMEDOUT:
		cout << "The connection has been dropped because of a network failure or because the peer system failed to respond" << endl;
		break;
	case WSAECONNRESET:
		cout << "The virtual circuit was reset by the remote side executing a hard or abortive close. The application should close the socket as it is no longer usable. On a UPD-datagram socket this error would indicate that a previous send operation resulted in an ICMP 'Port Unreachable' message" << endl;
		break;
	default:
		break;
	}
	return errcode;
}

const long WSAErrorsToConsole::ShowAcceptError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAECONNRESET:
		cout << "An incoming connection was indicated, but was subsequently terminated by the remote peer prior to accepting the call" << endl;
		break;
	case WSAEFAULT:
		cout << "The addrlen parameter is too small or addr is not a valid part of the user address space" << endl;
		break;
	case WSAEINTR:
		cout << "A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall" << endl;
		break;
	case WSAEINVAL:
		cout << "The listen function was not invoked prior to accept" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAEMFILE:
		cout << "The queue is nonempty upon entry to accept and there are no descriptors available" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAENOBUFS:
		cout << "No buffer space is available" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	case WSAEOPNOTSUPP:
		cout << "The referenced socket is not a type that supports connection-oriented service" << endl;
		break;
	case WSAEWOULDBLOCK:
		cout << "The socket is marked as nonblocking and no connections are present to be accepted" << endl;
		break;
	default:
		break;
	}

	return errcode;
}

const long WSAErrorsToConsole::ShowListenError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEADDRINUSE:
		cout << "The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution of the bind function, but could be delayed until this function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of this function" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAEINVAL:
		cout << "The socket has not been bound with bind" << endl;
		break;
	case WSAEISCONN:
		cout << "The socket is already connected" << endl;
		break;
	case WSAEMFILE:
		cout << "No more socket descriptors are available" << endl;
		break;
	case WSAENOBUFS:
		cout << "No buffer space is available" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	case WSAEOPNOTSUPP:
		cout << "The referenced socket is not of a type that supports the listen operation" << endl;
		break;
	default:
		break;
	}
	return errcode;
}

const long WSAErrorsToConsole::ShowBindError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEACCES:
		cout << "Attempt to connect datagram socket to broadcast address failed because setsockopt option SO_BROADCAST is not enabled" << endl;
		break;
	case WSAEADDRINUSE:
		cout << "A process on the computer is already bound to the same fully-qualified address and the socket has not been marked to allow address reuse with SO_REUSEADDR. For example, the IP address and port are bound in the af_inet case). (See the SO_REUSEADDR socket option under setsockopt.)" << endl;
		break;
	case WSAEADDRNOTAVAIL:
		cout << "The specified address is not a valid address for this computer" << endl;
		break;
	case WSAEFAULT:
		cout << "The name or namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains an incorrect address format for the associated address family, or the first two bytes of the memory block specified by name does not match the address family associated with the socket descriptor s" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAEINVAL:
		cout << "The socket is already bound to an address" << endl;
		break;
	case WSAENOBUFS:
		cout << "Not enough buffers available, too many connections" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	default:
		break;
	}

	return errcode;
}

const long WSAErrorsToConsole::ShowCloseSocketError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	case WSAEINTR:
		cout << "The (blocking) Windows Socket 1.1 call was canceled through WSACancelBlockingCall" << endl;
		break;
	case WSAEWOULDBLOCK:
		cout << "The socket is marked as nonblocking, but the l_onoff member of the linger structure is set to non-zero and the l_linger member of the linger structure is set to a nonzero timeout value" << endl;
		break;
	default:
		break;
	}
	return errcode;
}

const long WSAErrorsToConsole::ShowShutdownError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAENOTSOCK:
		cout << "The descriptor is not a socket" << endl;
		break;
	case WSAEINVAL:
		cout << "The how parameter is not valid, or is not consistent with the socket type. For example, SD_SEND is used with a UNI_RECV socket type" << endl;
		break;
	case WSAENOTCONN:
		cout << "The socket is not connected (connection-oriented sockets only)." << endl;
		break;
	default:
		break;
	}

	return errcode;
}

const long WSAErrorsToConsole::ShowWSACleanupError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem has failed" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	default:
		break;
	}

	return errcode;
}

const long WSAErrorsToConsole::ShowWSAStartupError( const long errcode )
{
	switch( errcode )
	{
	case WSASYSNOTREADY:
		cout << "The underlying network subsystem is not ready for network communication." << endl;
		break;
	case WSAVERNOTSUPPORTED:
		cout << "The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation." << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 operation is in progress." << endl;
		break;
	case WSAEPROCLIM:
		cout << "A limit on the number of tasks supported by the Windows Sockets implementation has been reached." << endl;
		break;
	case WSAEFAULT:
		cout << "The lpWSAData parameter is not a valid pointer." << endl;
		break;
	case 0:
		break;
	default:
		break;
	}
	return errcode;
}

const long WSAErrorsToConsole::ShowSocketError( const long errcode )
{
	switch( errcode )
	{
	case WSANOTINITIALISED:
		cout << "A successful WSAStartup call must occur before using this function" << endl;
		break;
	case WSAENETDOWN:
		cout << "The network subsystem or the associated service provider has failed" << endl;
		break;
	case WSAEAFNOSUPPORT:
		cout << "The specified address family is not supported" << endl;
		break;
	case WSAEINPROGRESS:
		cout << "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function" << endl;
		break;
	case WSAEMFILE:
		cout << "No more socket descriptors are available" << endl;
		break;
	case WSAENOBUFS:
		cout << "No buffer space is available. The socket cannot be created" << endl;
		break;
	case WSAEPROTONOSUPPORT:
		cout << "The specified protocol is not supported" << endl;
		break;
	case WSAEPROTOTYPE:
		cout << "The specified protocol is the wrong type for this socket" << endl;
		break;
	case WSAESOCKTNOSUPPORT:
		cout << "The specified socket type is not supported in this address family" << endl;
		break;
	default:
		break;
	}

	return errcode;
}

