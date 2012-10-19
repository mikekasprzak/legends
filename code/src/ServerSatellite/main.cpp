// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include "NetGet.h"
#include <cJSON/cJSON.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GELGeoData.h"
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	gelNetInit();

	// **** //

	printf( "Lets Start!\n" );
	fflush( 0 );

	// **** //

	GELGeoData MyGeo = GetMyGeoData();
	
	printf( "ME: %s %s %f %f\n", MyGeo.IP, MyGeo.Country, MyGeo.Latitude, MyGeo.Longitude );
	
	if ( MyGeo.Success ) {	
		int MyPort = 10240;
		int MyVersion = 100;
		
		printf( "Sending Update Packet...\n" );
		fflush( 0 );
		
		{
			char PostData[4096];
			snprintf( PostData, sizeof(PostData), "action=update&Address=%s&Port=%i&Version=%i&Latitude=%f&Longitude=%f&Info=%s%s%s%s",
				MyGeo.IP,
				MyPort,
				MyVersion,
				MyGeo.Latitude,
				MyGeo.Longitude,
				"DD",
				MyGeo.Country,
				"__",
				"__"
				);
			
			printf( "To Send: %s\n", PostData );
			
			GelArray<char>* ServerData = gelNetPostText( "http://sykhronics.com/satellite/json.php", PostData );
			
			// Nothing to do with it //
			
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

