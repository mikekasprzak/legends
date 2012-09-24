
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

const char DefaultHostName[] = "syk-country.appspot.com";

int main( int argc, char* argv[] ) {
	WSADATA wsaData;
	WSAStartup( MAKEWORD(1,1), &wsaData );
	atexit( (void(*)())WSACleanup );
	
	SOCKET Sock = socket( PF_INET, SOCK_STREAM /*SOCK_DGRAM*/, 0 );
	setsockopt( Sock, SOL_SOCKET, SO_KEEPALIVE, 0, 0 );
	
	// HostName is not the url. It's the domain part of a URL //
	const char* HostName = DefaultHostName;
	
	if ( argc > 1 ) {
		HostName = argv[1];
	}
		
	printf( "HostName: %s\n", HostName );

	// FYI: Do not release this memory. Winsock stores a single HostEnt structure per thread. //
	hostent* HostEnt = gethostbyname( HostName );

	// Output the contents of the HostEnt structure //
	if ( HostEnt ) {
		printf( "HostEnt->h_name: %s\n", HostEnt->h_name );
		
		{
			int AliasCount = 0;
			while( HostEnt->h_aliases[AliasCount] != 0 ) {
				printf( "HostEnt->h_aliases[%i]: %s\n", AliasCount, HostEnt->h_aliases[AliasCount] );
				AliasCount++;
			}
			printf( "%i Aliases Found\n", AliasCount );
		}
		
		printf( "HostEnt->h_addrtype: %i\n", HostEnt->h_addrtype );
		printf( "HostEnt->h_length: %i\n", HostEnt->h_length );
		
		{
			int AddrListCount = 0;
			while( HostEnt->h_addr_list[AddrListCount] != 0 ) {
				printf( "HostEnt->h_addr_list[%i]: %u.%u.%u.%u\n", 
					AddrListCount, 
					(unsigned char)HostEnt->h_addr_list[AddrListCount][0], 
					(unsigned char)HostEnt->h_addr_list[AddrListCount][1], 
					(unsigned char)HostEnt->h_addr_list[AddrListCount][2], 
					(unsigned char)HostEnt->h_addr_list[AddrListCount][3] 
					);
				AddrListCount++;
			}
			printf( "%i Addresses Found\n", AddrListCount );
		}		
	}
	else {
		printf( "gethostbyname failed!\n" );
		return -1;
	}
	
	sockaddr_in Server;
	memset( (char*)&Server, 0, sizeof(Server) );									// Zero, to be safe //
	memcpy( (void*)&Server.sin_addr, HostEnt->h_addr_list[0], HostEnt->h_length );	// Cheat, take Addr 0 //
	Server.sin_family = HostEnt->h_addrtype;
	Server.sin_port = (unsigned short)htons( 80 ); // I assume //

	// Open Socket Connection //
	int Err = connect( Sock, (const sockaddr*)&Server, sizeof(Server) );

	if ( Err < 0 ) {
		printf( "Connection Failed!\n" );
		return -1;
	}
	
	{
		// Build an HTTP Header //
		char Header[2048];	
		sprintf( Header, "%s %s HTTP/1.1\015\012Host: %s\015\012User-Agent: %s\015\012%s\015\012",
			"GET",
//			"HEAD",
			(argc > 2) ? argv[2] : "/",
			HostName,
			"WASSAAAAP!_IMA_BROWSER!",
			""
			);
		size_t HeaderLength = strlen( Header );
		
		printf( "** HEADER **\n%s\n** HEADER **\n", Header );
		
		// Send the Header //
		int ByteCount = send( Sock, Header, HeaderLength, 0 );
		
		printf( "%i Bytes Sent (Header)\n\n", ByteCount );
	}
	
	// Since we have no data to send, we'll simply move on to the recieve //
	
	{
		char Buffer[4096];
		memset( (char*)&Buffer, 0, sizeof(Buffer) );
		
		// Get the Response //
		int ByteCount = recv( Sock, Buffer, 4096-1, 0 );
		
		printf( "** DATA RECEIVED **\n%s\n** DATA RECEIVED **\n", Buffer );
		
		printf( "%i Bytes Received (Response)\n\n", ByteCount );
	}

	// Close Socket Connection //
	closesocket( Sock );	// 'close' on BSD //

	return 0;	
}
