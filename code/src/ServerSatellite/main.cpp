
#include <stdio.h>
#include "NetGet.h"
#include <cJSON/cJSON.h>


int main( int argc, char* argv[] ) {
	gelNetInit();

	// **** //

	printf( "Lets Start!\n" );
	fflush( 0 );

	// **** //
		
	GelArray<char>* CountryData = gelNetGetText( "http://syk-country.appspot.com" );
	
	if ( CountryData ) {
		cJSON *root = cJSON_Parse( CountryData->Data );
			
		char* MyIP = cJSON_GetObjectItem( root, "IP" )->valuestring;
		char* MyCountry = cJSON_GetObjectItem( root, "CountryCode" )->valuestring;
		double& MyLatitude = cJSON_GetObjectItem( root, "Latitude" )->valuedouble;
		double& MyLongitude = cJSON_GetObjectItem( root, "Longitude" )->valuedouble;
		
		printf( "IP: %s\n", MyIP );
		printf( "Country: %s\n", MyCountry );
		printf( "Location: %f, %f\n", MyLatitude, MyLongitude );
		
		int MyPort = 10240;
		int MyVersion = 100;
		
		printf( "Sending Update Packet...\n" );
		fflush( 0 );
		
		{
			char ServerInfo[8+1];
			sprintf( ServerInfo, "%s%s%s%s",
				"DD",
				MyCountry,
				"__",
				"__"
				);
							
			char PostData[4096];
			snprintf( PostData, sizeof(PostData), "action=update&Address=%s&Port=%i&Version=%i&Latitude=%f&Longitude=%f&Info=%s",
				MyIP,
				MyPort,
				MyVersion,
				MyLatitude,
				MyLongitude,
				ServerInfo
				);
			
			printf( "To Send: %s -- (%s)\n", PostData, ServerInfo );
			
			GelArray<char>* ServerData = gelNetPostText( "http://sykhronics.com/satellite/json.php", PostData );
			
			// Nothing to do with it //
			
			delete_GelArray<char>( ServerData );
		}
		
		// **** //

		cJSON_Delete( root );
		delete_GelArray<char>( CountryData );
	}	

	// **** //
	
	return 0;
}

