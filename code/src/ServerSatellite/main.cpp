// - ------------------------------------------------------------------------------------------ - //
#ifdef _WIN32

// We need to do this ourselves: http://msdn.microsoft.com/en-us/library/aa383745.aspx
#define _WIN32_WINNT 0x0501
#include <windows.h>

#endif // _WIN32
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <Debug/Log.h>

#include <Mongoose/mongoose.h>

#include "NetGet.h"
#include <cJSON/cJSON.h>
#include <Core/Data_MD5.h>

#include "NetAdapter.h"
// - ------------------------------------------------------------------------------------------ - //
#include "GELGeoData.h"
// - ------------------------------------------------------------------------------------------ - //


char InterfaceIP[40];
char InterfaceNetmask[40];
char InterfaceBroadcast[40];
char InterfaceMac[40];


// Subnet Mask on WinRT
// You can use HostName.IPInformation.PrefixLength.
// See http://msdn.microsoft.com/en-us/library/windows/apps/windows.networking.connectivity.ipinformation.prefixlength.aspx

#ifdef _WIN32

#include <Iphlpapi.h>

void GetInterfaces() {
	// http://msdn.microsoft.com/en-us/library/windows/desktop/aa366058%28v=vs.85%29.aspx
	ULONG IPASize = 16384;
	IP_ADAPTER_ADDRESSES* IPA = (IP_ADAPTER_ADDRESSES*)new char[IPASize];
	
	// http://msdn.microsoft.com/en-us/library/windows/desktop/aa365915%28v=vs.85%29.aspx
	GetAdaptersAddresses( /*AF_UNSPEC*/AF_INET, 0, NULL, IPA, &IPASize );
	
	for ( IP_ADAPTER_ADDRESSES* Current = IPA; Current != 0; Current = Current->Next ) {
		printf( "> %s ", Current->AdapterName );
		wprintf( L"%s -- %s\n", 
			Current->FriendlyName,
			Current->Description
			);
		
		char MyMac[40];
		sprintf( MyMac, "%02x:%02x:%02x:%02x:%02x:%02x",
			Current->PhysicalAddress[0],
			Current->PhysicalAddress[1],
			Current->PhysicalAddress[2],
			Current->PhysicalAddress[3],
			Current->PhysicalAddress[4],
			Current->PhysicalAddress[5]
			);
		
		printf( "MAC: %s [%i]\n", MyMac, Current->PhysicalAddressLength );
		
		char MyIP[40] = "";
		
		// IP_ADAPTER_UNICAST_ADDRESS -- http://msdn.microsoft.com/en-us/library/windows/desktop/aa366066%28v=vs.85%29.aspx
		// SOCKET_ADDRESS -- http://msdn.microsoft.com/en-us/library/windows/desktop/ms740507%28v=vs.85%29.aspx
		// sockaddr/sockaddr_in -- http://msdn.microsoft.com/en-us/library/windows/desktop/ms740496%28v=vs.85%29.aspx
		for ( IP_ADAPTER_UNICAST_ADDRESS* Cur = Current->FirstUnicastAddress; Cur != 0; Cur = Cur->Next ) {
			//printf("* %i\n", Cur->Address.lpSockaddr->sa_family);
			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;
				const char* Addr = inet_ntoa( SAI->sin_addr );
				memcpy( MyIP, Addr, strlen(Addr) );
				printf( "Unicast: %s *****\n", MyIP );
			}
		}
		
		for ( IP_ADAPTER_ANYCAST_ADDRESS* Cur = Current->FirstAnycastAddress; Cur != 0; Cur = Cur->Next ) {
			//printf("** %i\n", Cur->Address.lpSockaddr->sa_family);
			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;
				printf( "Anycast: %s\n", inet_ntoa( SAI->sin_addr ) );
			}
		}
		
		for ( IP_ADAPTER_MULTICAST_ADDRESS* Cur = Current->FirstMulticastAddress; Cur != 0; Cur = Cur->Next ) {
			//printf("*** %i\n", Cur->Address.lpSockaddr->sa_family);
			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;
				printf( "Multicast: %s\n", inet_ntoa( SAI->sin_addr ) );
			}
		}
		
		for ( IP_ADAPTER_DNS_SERVER_ADDRESS* Cur = Current->FirstDnsServerAddress; Cur != 0; Cur = Cur->Next ) {
			//printf("**** %i\n", Cur->Address.lpSockaddr->sa_family);
			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;
				printf( "DNS Server: %s $$$$$$\n", inet_ntoa( SAI->sin_addr ) );
			}
		}
		
		// If Server has a DNS //
		if ( Current->FirstDnsServerAddress != 0 ) {
			memcpy( InterfaceMac, MyMac, strlen(MyMac) );
			memcpy( InterfaceIP, MyIP, strlen(MyIP) );
		}
	}
	Log("");
	
	delete IPA;
}

#else // NOT _WIN32

#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>				// IFF_BROADCAST
#include <sys/socket.h>
#include <linux/if_packet.h>	// sockaddr_ll
#include <netdb.h>
// http://www.kernel.org/doc/man-pages/online/pages/man3/getifaddrs.3.html
// http://stackoverflow.com/questions/6762766/mac-address-with-getifaddrs

void GetInterfaces() {
	ifaddrs* IFA;
	if ( getifaddrs( &IFA ) == 0 ) {
		for( ifaddrs* Current = IFA; Current != 0; Current = Current->ifa_next ) {
			char MyIP[NI_MAXHOST] = "";
			char MySubnet[NI_MAXHOST] = "";
            char MyOther[NI_MAXHOST] = "";
            
            // On BSD the MAC in under AF_LINK -- http://stackoverflow.com/questions/6762766/mac-address-with-getifaddrs
			
			if ( Current->ifa_addr->sa_family == AF_INET || Current->ifa_addr->sa_family == AF_INET6 ) {		
				getnameinfo( 
					Current->ifa_addr, 
					(Current->ifa_addr->sa_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
	                MyIP, NI_MAXHOST, NULL, 0, NI_NUMERICHOST );
	
				getnameinfo(
					Current->ifa_netmask, 
					(Current->ifa_addr->sa_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
	                MySubnet, NI_MAXHOST, NULL, 0, NI_NUMERICHOST );
	                
	            if ( Current->ifa_flags & IFF_BROADCAST ) {            	
					getnameinfo(
						Current->ifa_broadaddr, 
						(Current->ifa_addr->sa_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
		                MyOther, NI_MAXHOST, NULL, 0, NI_NUMERICHOST );
				}
				else if ( Current->ifa_flags & IFF_POINTOPOINT ) {            	
					getnameinfo(
						Current->ifa_dstaddr, 
						(Current->ifa_addr->sa_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
		                MyOther, NI_MAXHOST, NULL, 0, NI_NUMERICHOST );
				}
			}
			else if ( Current->ifa_addr->sa_family == AF_PACKET ) {
				sockaddr_ll* s = (sockaddr_ll*)Current->ifa_addr;
				sprintf( MyIP, "%02x:%02x:%02x:%02x:%02x:%02x",
					s->sll_addr[0],
					s->sll_addr[1],
					s->sll_addr[2],
					s->sll_addr[3],
					s->sll_addr[4],
					s->sll_addr[5]
					);
			}
            
                
            if ( Current->ifa_addr->sa_family == AF_INET ) {
            	if ( strcmp( Current->ifa_name, "lo" ) != 0 ) {
            		memcpy( InterfaceIP, MyIP, strlen(MyIP) );
            		memcpy( InterfaceNetmask, MySubnet, strlen(MySubnet) );
            		memcpy( InterfaceBroadcast, MyOther, strlen(MyOther) );
            	}
            }
            else if ( Current->ifa_addr->sa_family == AF_PACKET ) {
           		if ( strcmp( Current->ifa_name, "lo" ) != 0 ) {
            		memcpy( InterfaceMac, MyIP, strlen(MyIP) );
            	}            	
            }

			printf( "Interface: %s%s -- %s -- %s %s[%s]\n",
				Current->ifa_name, 
				
				(Current->ifa_addr->sa_family == AF_PACKET) ? " (AF_PACKET)" :
				(Current->ifa_addr->sa_family == AF_INET) ?   " (AF_INET)" :
				(Current->ifa_addr->sa_family == AF_INET6) ?  " (AF_INET6)" : "",
				
				MyIP, MySubnet, 

				(Current->ifa_flags & IFF_BROADCAST) ?   "-- (IFF_BROADCAST) " :
				(Current->ifa_flags & IFF_POINTOPOINT) ?  "-- (IFF_POINTOPOINT) " : "",
				
				MyOther
				);
			fflush(0);
		}
		
		freeifaddrs( IFA );
	}
}

#endif // _WIN32 //


GELGeoData MyGeo;

// - ------------------------------------------------------------------------------------------ - //
static void* WebServerCallback( mg_event event, mg_connection *conn ) {
	const mg_request_info* request_info = mg_get_request_info(conn);
	
	if (event == MG_NEW_REQUEST) {
		const unsigned char* IP = (const unsigned char*)&request_info->remote_ip;
		
		char content[1024];
		int content_length = snprintf(
			content, sizeof(content),
			"Hello from %s (Internet: %s, LAN: %s | %s)!\n\nYou are %i.%i.%i.%i:%i -- %s",
			MyGeo.Country, MyGeo.IP,
			InterfaceIP, InterfaceNetmask,
			(int)IP[3],(int)IP[2],(int)IP[1],(int)IP[0],
			request_info->remote_port,
			request_info->query_string
			);

		mg_printf(conn,
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: %d\r\n" // Always set Content-Length
			"\r\n"
			"%s",
			content_length, content);
		
		// Mark as processed
		return (void*)"";
	} 
	else {
		return NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	gelNetInit();
	
	// **** //


	{
		pNetAdapterInfo* Adapters = new_pNetAdapterInfo();							// Get adapters //
		const NetAdapterInfo* Current = get_primary_pNetAdapterInfo( Adapters );	// Get primary adapter //
		printf( "%s: %s (%s)\n", Current->Name, Current->IP, Current->MAC );
		delete_pNetAdapterInfo( Adapters );											// Clean up //
	}

	{
		pNetAdapterInfo* Adapters = new_pNetAdapterInfo();
		size_t AdapterCount = count_pNetAdapterInfo(Adapters);
		for ( size_t Index = 0; Index < AdapterCount; Index++ ) {
			const NetAdapterInfo* Current = get_pNetAdapterInfo( Adapters, Index );	// get_, not get_primary_ //
			printf( "%i - %s: %s (%s)\n", Index, Current->Name, Current->IP, Current->MAC );
		}
		delete_pNetAdapterInfo( Adapters );
	}

	
	//GetInterfaces();
	//fflush(0);

	MyGeo = GetMyGeoData();
	
	//printf( "ME: %s %s %f %f\n", MyGeo.IP, MyGeo.Country, MyGeo.Latitude, MyGeo.Longitude );

	
	{
		int Port = 10080;
	
		// **** //
		
		char PortString[7];
		snprintf( PortString, sizeof(PortString), "%i", Port );
	
		struct mg_context *ctx;
		const char *options[] = {"listening_ports", PortString, NULL};
		
		ctx = mg_start( &WebServerCallback, NULL, options );
		Log( "Webserver started on Port %s.", PortString ); 
		Log( "Visit http://%s:%s in a web browser to edit settings.", InterfaceIP, PortString );
		fflush(0);
		getchar(); // Wait until user hits "enter"
		mg_stop(ctx);	
	
		return 0;
	}

	// **** //

	printf( "Lets Start!\n" );
	fflush( 0 );

	// **** //
	
	if ( MyGeo.Success ) {	
		int MyPort = 10240;
		int MyVersion = 100;
		
		printf( "Sending Update Packet...\n" );
		fflush( 0 );
		
		{
			char KeyData[1024];
			snprintf( KeyData, sizeof(KeyData), "%i&%s&%i&%s",
				MyPort,
				MyGeo.IP,
				MyVersion,
				"ChupacabraSatellites"
				);
			
			MD5Hash MD5 = hash_MD5_Data( KeyData, strlen(KeyData) );	
			
			char PostData[4096];
			snprintf( PostData, sizeof(PostData), "action=update&Address=%s&Port=%i&Version=%i&Latitude=%f&Longitude=%f&Info=%s%s%s%s&Key=%s",
				MyGeo.IP,
				MyPort,
				MyVersion,
				MyGeo.Latitude,
				MyGeo.Longitude,
				"DD",
				MyGeo.Country,
				"__",
				"__",
				MD5.Text // Not actually a key //
				);
			
			printf( "To Send: %s\n", PostData );
			
			GelArray<char>* ServerData = gelNetPostText( "http://sykhronics.com/satellite/json.php", PostData );
			
			// Nothing to do with it //
			printf( "Return: \n%s\n", ServerData->Data );
			
			delete_GelArray<char>( ServerData );
		}
	}	

	// **** //

	{
//		GelArray<char>* ImageData = gelNetGetBinary( "http://www.gravatar.com/avatar/8266e6e52fe185d057db55021ac7bb86" );	
//		write_GelArray<char>( ImageData, "blah.png" );
//		delete_GelArray<char>( ImageData );
	}
	
	return 0;
}

