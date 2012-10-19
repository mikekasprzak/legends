// - ------------------------------------------------------------------------------------------ - //
#include <curl/curl.h>
#include <Core/GelVFile.h>
// - ------------------------------------------------------------------------------------------ - //
#include "NetGet.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
size_t gels_write_data( void* buffer, size_t buffer_size, size_t nmemb, void* userp ) {
	int Size = buffer_size * nmemb;

	GelVFile* vf = (GelVFile*)userp;
	
	write_GelVFile( vf, (const char*)buffer, Size );
	
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline GelArray<char>* gelNetGet_( const char* URL, const bool Text, const char* PostData = 0 ) {
	GelVFile* vf = open_GelVFile();
	
	CURL* curl = curl_easy_init();
	
	if ( curl ) {
		curl_easy_setopt( curl, CURLOPT_URL, URL );
		curl_easy_setopt( curl, CURLOPT_USERAGENT, "Mozilla/5.0 (en-us) Satellite/0.01 (server) Sykhronics" ); 
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, gels_write_data );
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, vf );
		if ( PostData )
			curl_easy_setopt( curl, CURLOPT_POSTFIELDS, PostData ); 
		
		CURLcode Err = curl_easy_perform( curl );
		
		if( Err != CURLE_OK ) {
			close_GelVFile( vf );
			return 0;
		}
		
		curl_easy_cleanup(curl);
		
		// Write a null terminator character on the end of the vfile //
		if ( Text ) {
			write_GelVFile( vf, "", 1 );
		}
		
		return close_skeleton_GelVFile( vf );
	}
	else {
		close_GelVFile( vf );		
		return 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Text/Binary determines the return type, not the sent type. //
// Text means to append a null terminator on the end //
// - ------------------------------------------------------------------------------------------ - //
GelArray<char>* gelNetGetText( const char* URL ) {
	return gelNetGet_( URL, true );
}
// - ------------------------------------------------------------------------------------------ - //
GelArray<char>* gelNetGetBinary( const char* URL ) {
	return gelNetGet_( URL, false );
}
// - ------------------------------------------------------------------------------------------ - //
GelArray<char>* gelNetPostText( const char* URL, const char* PostData ) {
	return gelNetGet_( URL, true, PostData );
}
// - ------------------------------------------------------------------------------------------ - //
GelArray<char>* gelNetPostBinary( const char* URL, const char* PostData ) {
	return gelNetGet_( URL, false, PostData );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelNetInit( const bool DoWindowsInit ) {
	curl_global_init( DoWindowsInit ? CURL_GLOBAL_WIN32 : CURL_GLOBAL_NOTHING );
}
// - ------------------------------------------------------------------------------------------ - //
