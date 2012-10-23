// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <Debug/Log.h>

#include <Mongoose/mongoose.h>

#include "NetGet.h"
#include <cJSON/cJSON.h>
#include <Core/Data_MD5.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GELGeoData.h"
// - ------------------------------------------------------------------------------------------ - //


char InterfaceIP[40];
char InterfaceNetmask[40];

#ifdef _WIN32

void GetInterfaces() {

}

#else // NOT _WIN32

#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netdb.h>
// http://www.kernel.org/doc/man-pages/online/pages/man3/getifaddrs.3.html

void GetInterfaces() {
	ifaddrs* IFA;
	if ( getifaddrs( &IFA ) == 0 ) {
		for( ifaddrs* Current = IFA; Current != 0; Current = Current->ifa_next ) {
			char MyIP[NI_MAXHOST] = "";
			char MySubnet[NI_MAXHOST] = "";
            char MyOther[NI_MAXHOST] = "";
			
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
				sprintf( MyIP, "%s:%s:%s:%s:%s:%s",
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
	
	GetInterfaces();

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

