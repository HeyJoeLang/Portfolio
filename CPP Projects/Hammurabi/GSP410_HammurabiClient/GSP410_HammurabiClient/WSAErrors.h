// WSAErrors.h
//
// by Brian Schick
//
// A class for printing errors
#pragma once

class WSAErrorsToConsole
{
public:
static const long ShowWSACleanupError( const long errcode );
static const long ShowRecvError( const long errcode );
static const long ShowSendError( const long errcode );
static const long ShowWSAStartupError( const long errcode );
static const long ShowSocketError( const long errcode );
static const long ShowShutdownError( const long errcode );
static const long ShowCloseSocketError( const long errcode );
static const long ShowBindError( const long errcode );
static const long ShowListenError( const long errcode );
static const long ShowAcceptError( const long errcode );
static const long ShowConnectError( const long errcode );
static const long ShowWinsock2Error( const long errcode );
};