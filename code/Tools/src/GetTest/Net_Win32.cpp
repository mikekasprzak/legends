// - ---------------------------------------------------------------------- - //
#include <stdio.h>
#include <winsock2.h>
// - ---------------------------------------------------------------------- - //
#include "Net.h"
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
// Thread Unsafe Stuff. Call once before creating threads. //
// - ---------------------------------------------------------------------- - //
WSADATA wsaData;
// - ---------------------------------------------------------------------- - //
void netInit() {
	WSAStartup( MAKEWORD(1,1), &wsaData );
	atexit( (void(*)())WSACleanup );
}
// - ---------------------------------------------------------------------- - //
void netExit() {
	
}
// - ---------------------------------------------------------------------- - //


// - ---------------------------------------------------------------------- - //
// Thread Safe Stuff //
// - ---------------------------------------------------------------------- - //
struct NetHTTPConnection {
	SOCKET			Sock;
	sockaddr_in		Server;
};
// - ---------------------------------------------------------------------- - //
NetHTTPConnection* netOpenHTTP( const char* HostName, const int Port ) {
	NetHTTPConnection* Con = new NetHTTPConnection;

	Con->Sock = socket( PF_INET, SOCK_STREAM, 0 );
	setsockopt( Con->Sock, SOL_SOCKET, SO_KEEPALIVE, 0, 0 );	
	
	// FYI: Do not release this memory. Winsock stores a single HostEnt structure per thread. //
	hostent* HostEnt = gethostbyname( HostName );
	
	// If we got a HostEnt structure, the HostName is valid //
	if ( HostEnt ) {
		memset( (char*)&Con->Server, 0, sizeof(Con->Server) );								// Zero, to be safe //
		memcpy( (void*)&Con->Server.sin_addr, HostEnt->h_addr_list[0], HostEnt->h_length );	// Cheat, take Addr 0 //
		Con->Server.sin_family = HostEnt->h_addrtype;
		Con->Server.sin_port = (unsigned short)htons( Port );

		// Open Socket Connection //
		int Err = connect( Con->Sock, (const sockaddr*)&Con->Server, sizeof(Con->Server) );
	
		if ( Err < 0 ) {
			delete Con;
			return 0;
		}

		return Con;
	}
	else {
		delete Con;
		return 0;
	}
}
// - ---------------------------------------------------------------------- - //
void netCloseHTTP( NetHTTPConnection* Con ) {
	// Close Socket Connection //
	closesocket( Con->Sock );	// 'close' on BSD //
	
	delete Con;
}
// - ---------------------------------------------------------------------- - //


// Accept-Encoding: gzip

// - ---------------------------------------------------------------------- - //
char* netGetHTTPData( const char* URL ) {
	char* ReturnData = 0;

	const char* HostPath = "/";//"/"
	const char* HostName = URL;//"sykhronics.com";//URL;
	
	NetHTTPConnection* Con;
	Con = netOpenHTTP( HostName, 80 );	
	
	// Send an HTTP GET header //
	{
		char Header[4096];
		sprintf( Header, "%s %s HTTP/1.1\015\012Host: %s\015\012User-Agent: %s\015\012%s\015\012",
			"GET",
			HostPath,
			HostName,
			"Mozilla/5.0 (en-us) Satellite/0.01.0 (gzip) Sykhronics/1.0",
			""//"Accept-Encoding: gzip, deflate\015\012"
			);
		size_t HeaderLength = strlen( Header );
		
		printf( "Header:\n%s\n", Header );
		fflush( 0 );
		
		// Send the Header //
		int ByteCount = send( Con->Sock, Header, HeaderLength, 0 );
		
		if ( ByteCount == 0 )
			return 0;
	}

	// Get Response //
	{
		char Buffer[4096+1]; // One more for a Null Terminator //
		
		// Get the Response //
		int ByteCount = recv( Con->Sock, Buffer, 4096, 0 );
		Buffer[ByteCount] = 0; // Null Terminate //
		
		// Repeating the above will get more data. 0 on done, negative on error //
		
		// TODO: Use a linked list, collect a bunch of parts, then combine in to one for return //
		
		// Copy //
		ReturnData = new char[ByteCount+1];
		memcpy( ReturnData, Buffer, ByteCount+1 );
	}
	
	// Close Connection //
	netCloseHTTP( Con );
	
	return ReturnData;
}
// - ---------------------------------------------------------------------- - //
char* netPostHTTPData( const char* URL, const char* Data ) {
	char* ReturnData = 0;

	const char* HostPath = "/satellite/json.php";//"/"
	const char* HostName = URL;//"sykhronics.com";//URL;
	
	NetHTTPConnection* Con;
	Con = netOpenHTTP( HostName, 80 );	
	
	// Send an HTTP GET header //
	{
		char Header[4096];
		sprintf( Header, "%s %s HTTP/1.1\015\012Host: %s\015\012User-Agent: %s\015\012Content-Type: application/x-www-form-urlencoded\015\012Content-Length: %i\015\012\015\012%s\015\012",
			"POST", HostPath, 	// HTTP Response Header //
			HostName, 			// Host //
			"Mozilla/5.0 (en-us) Satellite/0.01.0 (gzip) Sykhronics/1.0", // User-Agent //
			strlen(Data),
			Data
			);
		size_t HeaderLength = strlen( Header );
		
		printf( "Header:\n%s\n", Header );
		fflush( 0 );
		
		// Send the Header //
		int ByteCount = send( Con->Sock, Header, HeaderLength, 0 );
		
		if ( ByteCount == 0 )
			return 0;
	}

	// Get Response //
	{
		char Buffer[4096+1]; // One more for a Null Terminator //
		
		// Get the Response //
		int ByteCount = recv( Con->Sock, Buffer, 4096, 0 );
		Buffer[ByteCount] = 0; // Null Terminate //
		
		// Repeating the above will get more data. 0 on done, negative on error //
		
		// TODO: Use a linked list, collect a bunch of parts, then combine in to one for return //
		
		// Copy //
		ReturnData = new char[ByteCount+1];
		memcpy( ReturnData, Buffer, ByteCount+1 );
	}
	
	// Close Connection //
	netCloseHTTP( Con );
	
	return ReturnData;
}
// - ---------------------------------------------------------------------- - //
void netDeleteHTTPData( char* Data ) {
	delete Data;
}
// - ---------------------------------------------------------------------- - //

