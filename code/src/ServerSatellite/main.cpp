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


#include <ifaddrs.h>
// http://www.kernel.org/doc/man-pages/online/pages/man3/getifaddrs.3.html

void MeMeMe() {
	ifaddrs* IFA;
	if ( getifaddrs( &IFA ) == 0 ) {
		ifaddr* Current = IFA;
		for( ifaddr Current = IFA; Current != 0; Current = Current->ifa_next ) {
			printf( "> %s\n", Current->ifa_name );
			fflush(0);
		}
		
		freeifaddrs( IFA );
	}
}


GELGeoData MyGeo;

// - ------------------------------------------------------------------------------------------ - //
static void* WebServerCallback( mg_event event, mg_connection *conn ) {
	const mg_request_info* request_info = mg_get_request_info(conn);
	
	if (event == MG_NEW_REQUEST) {
		const unsigned char* IP = (const unsigned char*)&request_info->remote_ip;
		
		char content[1024];
		int content_length = snprintf(
			content, sizeof(content),
			"Hello from %s (Internet: %s, LAN: %s)! You are %i.%i.%i.%i:%i -- %s",
			MyGeo.Country, MyGeo.IP,
			"??",
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
	
	MeMeMe();

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
		Log( "Webserver started on Port %s. Visit http://?.?.?.?:%s in a browser to edit settings.", PortString, PortString );
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

