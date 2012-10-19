// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include "NetGet.h"
#include <cJSON/cJSON.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define safe_sprintf( ... ) sprintf_s( __VA_ARGS__ )
#else // _MSC_VER //
#define safe_sprintf( ... ) snprintf( __VA_ARGS__ )
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GELGeoData {
public:
	char IP[38+1];
	char Country[2+1];
	float Latitude;
	float Longitude;
	
	bool Success;

public:
	inline GELGeoData() { }
	
	inline GELGeoData( const char* _IP, const char* _Country, const float _Latitude, const float _Longitude, const bool _Success = false ) :
		Latitude( _Latitude ),
		Longitude( _Longitude ),
		Success( _Success )
	{
		safe_sprintf( IP, sizeof(IP), _IP );
		safe_sprintf( Country, sizeof(Country), _Country );
	}
};
// - ------------------------------------------------------------------------------------------ - //
struct GeoService {
	const char* URL;
	
	const char* IPField;
	const char* CountryField;
	const char* LatitudeField;
	const char* LongitudeField;
	
	const int Flags;
};
// - ------------------------------------------------------------------------------------------ - //
const GeoService GeoServices[] = {
	"http://syk-country.appspot.com", "IP", "CountryCode", "Latitude", "Longitude", 0,
	"http://api.easyjquery.com/ips/", "IP", "COUNTRY", "cityLatitude", "cityLongitude", 0, 
	"http://freegeoip.net/json/", "ip", "country_code", "latitude", "longitude", 0,		// stores Lat/Long in strings //
};
// - ------------------------------------------------------------------------------------------ - //
const GELGeoData LookupGeoData( const GeoService* Service ) {
	GELGeoData Ret;
	Ret.Success = false;
	
	GelArray<char>* NetData = gelNetGetText( Service->URL );
	
	if ( NetData ) {		
		cJSON *root = cJSON_Parse( NetData->Data );
		
		if ( root ) {
			// TODO: Confirm that data exists (could be a failure JSON packet returned) //
			safe_sprintf( Ret.IP, sizeof(Ret.IP), cJSON_GetObjectItem( root, Service->IPField )->valuestring );
			safe_sprintf( Ret.Country, sizeof(Ret.Country), cJSON_GetObjectItem( root, Service->CountryField )->valuestring );
			Ret.Latitude = cJSON_GetObjectItem( root, Service->LatitudeField )->valuedouble;
			Ret.Longitude = cJSON_GetObjectItem( root, Service->LongitudeField )->valuedouble;
			Ret.Success = true;

			cJSON_Delete( root );
		}
		
		delete_GelArray<char>( NetData );
	}
	
	if ( !Ret.Success ) {
		return GELGeoData( "?.?.?.?", "??", 0, 0, false );
	}
	
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
const GELGeoData GetMyGeoData() { 
	for ( int idx = 0; idx < sizeof(GeoServices) / sizeof(GeoService); idx++ ) {
		GELGeoData Ret = LookupGeoData( &GeoServices[idx] );
		if ( Ret.Success )
			return Ret;
	}
	
	return GELGeoData( "?.?.?.?", "??", 0, 0, false );
}
// - ------------------------------------------------------------------------------------------ - //


int main( int argc, char* argv[] ) {
	gelNetInit();

	// **** //

	printf( "Lets Start!\n" );
	fflush( 0 );

	// **** //
		
//	GelArray<char>* CountryData = gelNetGetText( "http://syk-country.appspot.com" );
//	
//	if ( CountryData ) {
//		cJSON *root = cJSON_Parse( CountryData->Data );
//			
//		char* MyIP = cJSON_GetObjectItem( root, "IP" )->valuestring;
//		char* MyCountry = cJSON_GetObjectItem( root, "CountryCode" )->valuestring;
//		double& MyLatitude = cJSON_GetObjectItem( root, "Latitude" )->valuedouble;
//		double& MyLongitude = cJSON_GetObjectItem( root, "Longitude" )->valuedouble;
//		
//		printf( "IP: %s\n", MyIP );
//		printf( "Country: %s\n", MyCountry );
//		printf( "Location: %f, %f\n", MyLatitude, MyLongitude );

	GELGeoData MyGeo = GetMyGeoData();
	
	printf( "ME: %s %s %f %f\n", MyGeo.IP, MyGeo.Country, MyGeo.Latitude, MyGeo.Longitude );
	
	if ( MyGeo.Success ) {	
		int MyPort = 10240;
		int MyVersion = 100;
		
		printf( "Sending Update Packet...\n" );
		fflush( 0 );
		
		{
			char ServerInfo[8+1];
			sprintf( ServerInfo, "%s%s%s%s",
				"DD",
				//MyCountry,
				MyGeo.Country,
				"__",
				"__"
				);
							
			char PostData[4096];
			snprintf( PostData, sizeof(PostData), "action=update&Address=%s&Port=%i&Version=%i&Latitude=%f&Longitude=%f&Info=%s",
				//MyIP,
				MyGeo.IP,
				MyPort,
				MyVersion,
				//MyLatitude,
				//MyLongitude,
				MyGeo.Latitude,
				MyGeo.Longitude,
				ServerInfo
				);
			
			printf( "To Send: %s -- (%s)\n", PostData, ServerInfo );
			
			GelArray<char>* ServerData = gelNetPostText( "http://sykhronics.com/satellite/json.php", PostData );
			
			// Nothing to do with it //
			
			delete_GelArray<char>( ServerData );
		}
		
		// **** //

//		cJSON_Delete( root );
//		delete_GelArray<char>( CountryData );
	}	

	// **** //
	
	return 0;
}

