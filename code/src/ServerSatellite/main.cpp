
#include <stdio.h>
#include <curl/curl.h>

#include "NetGet.h"

#include <cJSON/cJSON.h>


size_t write_data( void* buffer, size_t buffer_size, size_t nmemb, void* userp ) {
	int Size = buffer_size * nmemb;
	
	memcpy( userp, buffer, Size );
	((char*)userp)[Size] = 0;
	
	return Size;
}

int main( int argc, char* argv[] ) {
	printf( "Lets Start!\n" );
	fflush( 0 );

	curl_global_init( CURL_GLOBAL_ALL );

	// **** //
	
//	{
//		GelArray<char>* Daddy = gelNetGetText( "http://syk-country.appspot.com" );
//		
//		printf( "Daddy (%i): %s\n", Daddy->Size, Daddy->Data );
//		
//		delete_GelArray<char>( Daddy );
//	}
	
	{
		cJSON *root;
/*		char CopyData[CURL_MAX_WRITE_SIZE];
		
		{
			CURL* curl = curl_easy_init();
			
			if ( curl ) {
				curl_easy_setopt( curl, CURLOPT_URL, "http://syk-country.appspot.com" );
				curl_easy_setopt( curl, CURLOPT_USERAGENT, "Mozilla/5.0 (en-us) Satellite/0.01 (server) Sykhronics" ); 
				curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_data );
				curl_easy_setopt( curl, CURLOPT_WRITEDATA, CopyData ); 
				
				CURLcode Err = curl_easy_perform( curl );
				if( Err != CURLE_OK )
					fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(Err) );
				
				curl_easy_cleanup(curl);
			}
		}*/
		
		GelArray<char>* CountryData = gelNetGetText( "http://syk-country.appspot.com" );
		root = cJSON_Parse( CountryData->Data );
			
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

/*			
			char ReturnData[CURL_MAX_WRITE_SIZE];
			{
				CURL* curl = curl_easy_init();
			
				if ( curl ) {
					curl_easy_setopt( curl, CURLOPT_URL, "http://sykhronics.com/satellite/json.php" );
					curl_easy_setopt( curl, CURLOPT_USERAGENT, "Mozilla/5.0 (en-us) Satellite/0.01 (server) Sykhronics" ); 
					curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_data );
					curl_easy_setopt( curl, CURLOPT_WRITEDATA, ReturnData );
					curl_easy_setopt( curl, CURLOPT_POSTFIELDS, PostData ); 
					
					CURLcode Err = curl_easy_perform( curl );
					if( Err != CURLE_OK )
						fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(Err) );
					
					curl_easy_cleanup(curl);
				}
			}*/
			
			GelArray<char>* ServerData = gelNetPostText( "http://sykhronics.com/satellite/json.php", PostData );
			
			// Nothing to do with it //
			
			delete_GelArray<char>( ServerData );
		}
		
		// **** //

		delete_GelArray<char>( CountryData );
		cJSON_Delete( root );
	}
	
	return 0;
}

