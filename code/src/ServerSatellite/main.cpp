// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include "NetGet.h"
#include <cJSON/cJSON.h>
#include <Core/Data_MD5.h>
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
