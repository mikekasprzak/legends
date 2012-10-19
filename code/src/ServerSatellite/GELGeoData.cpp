// - ------------------------------------------------------------------------------------------ - //
#include "NetGet.h"
#include <cJSON/cJSON.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GELGeoData.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define safe_sprintf( ... ) sprintf_s( __VA_ARGS__ )
#else // _MSC_VER //
#define safe_sprintf( ... ) snprintf( __VA_ARGS__ )
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
GELGeoData::GELGeoData( const char* _IP, const char* _Country, const float _Latitude, const float _Longitude, const bool _Success ) :
	Latitude( _Latitude ),
	Longitude( _Longitude ),
	Success( _Success )
{
	safe_sprintf( IP, sizeof(IP), "%s", _IP );
	safe_sprintf( Country, sizeof(Country), "%s", _Country );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct GELGeoService {
	const char* URL;
	
	const char* IPField;
	const char* CountryField;
	const char* LatitudeField;
	const char* LongitudeField;
	
	const int Flags;
};
// - ------------------------------------------------------------------------------------------ - //
enum {
	GELGEO_NONE = 			0x0,
	GELGEO_STRINGLAT = 		0x1,
	GELGEO_STRINGLONG = 	0x2,
	GELGEO_STRINGLATLONG =	GELGEO_STRINGLAT | GELGEO_STRINGLONG,
};
// - ------------------------------------------------------------------------------------------ - //
const GELGeoService GeoServices[] = {
	"http://syk-country.appspot.com", "IP", "CountryCode", "Latitude", "Longitude", GELGEO_NONE,
	"http://api.easyjquery.com/ips/", "IP", "COUNTRY", "cityLatitude", "cityLongitude", GELGEO_NONE, 
	"http://freegeoip.net/json/", "ip", "country_code", "latitude", "longitude", GELGEO_STRINGLATLONG,
};
// - ------------------------------------------------------------------------------------------ - //
inline const GELGeoData DummyGeoData() {
	return GELGeoData( "?.?.?.?", "__", 0, 0, false );
}
// - ------------------------------------------------------------------------------------------ - //
const GELGeoData LookupGeoData( const GELGeoService* Service ) {
	GELGeoData Ret;
	Ret.Success = false;
	
	GelArray<char>* NetData = gelNetGetText( Service->URL );
	
	if ( NetData ) {		
		cJSON *root = cJSON_Parse( NetData->Data );
		
		if ( root ) {
			// TODO: Confirm that data exists (could be a failure JSON packet returned) //
			
			// IP and Country //
			safe_sprintf( Ret.IP, sizeof(Ret.IP), "%s", cJSON_GetObjectItem( root, Service->IPField )->valuestring );
			safe_sprintf( Ret.Country, sizeof(Ret.Country), "%s", cJSON_GetObjectItem( root, Service->CountryField )->valuestring );

			// Latitude //
			if ( Service->Flags & GELGEO_STRINGLAT )
				Ret.Latitude = atof( cJSON_GetObjectItem( root, Service->LatitudeField )->valuestring );
			else
				Ret.Latitude = cJSON_GetObjectItem( root, Service->LatitudeField )->valuedouble;

			// Longitude //
			if ( Service->Flags & GELGEO_STRINGLONG )
				Ret.Longitude = atof( cJSON_GetObjectItem( root, Service->LongitudeField )->valuestring );
			else
				Ret.Longitude = cJSON_GetObjectItem( root, Service->LongitudeField )->valuedouble;

			// Success!! //
			Ret.Success = true;

			// **** //
			
			cJSON_Delete( root );
		}
		
		delete_GelArray<char>( NetData );
	}
	
	if ( !Ret.Success ) {
		return DummyGeoData();
	}
	
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
const GELGeoData GetMyGeoData() { 
	for ( int idx = 0; idx < sizeof(GeoServices) / sizeof(GELGeoService); idx++ ) {
		GELGeoData Ret = LookupGeoData( &GeoServices[idx] );
		if ( Ret.Success )
			return Ret;
	}
	
	return DummyGeoData();
}
// - ------------------------------------------------------------------------------------------ - //
