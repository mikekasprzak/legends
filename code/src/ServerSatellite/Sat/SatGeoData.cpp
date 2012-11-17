// - ------------------------------------------------------------------------------------------ - //
#include <Net/NetGet.h>

#include <cJSON/cJSON.h>
#include <Util/cJSON_ValidateSchema.h>
// - ------------------------------------------------------------------------------------------ - //
#include "SatGeoData.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define safe_sprintf( ... ) sprintf_s( __VA_ARGS__ )
#else // _MSC_VER //
#define safe_sprintf( ... ) snprintf( __VA_ARGS__ )
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SatGeoData::SatGeoData( const char* _IP, const char* _Country, const float _Latitude, const float _Longitude, const bool _Success ) :
	Latitude( _Latitude ),
	Longitude( _Longitude ),
	Good( _Success )
{
	safe_sprintf( IP, sizeof(IP), "%s", _IP );
	safe_sprintf( Country, sizeof(Country), "%s", _Country );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct SatGeoService {
	const char* URL;
	
	const char* IPField;
	const char* CountryField;
	const char* LatitudeField;
	const char* LongitudeField;
	
	const int Flags;
};
// - ------------------------------------------------------------------------------------------ - //
enum {
	SATGEO_NONE = 			0x0,
	SATGEO_STRINGLAT = 		0x1,
	SATGEO_STRINGLONG = 	0x2,
	SATGEO_STRINGLATLONG =	SATGEO_STRINGLAT | SATGEO_STRINGLONG,
};
// - ------------------------------------------------------------------------------------------ - //
const SatGeoService GeoServices[] = {
	"http://syk-country.appspot.com", "IP", "CountryCode", "Latitude", "Longitude", SATGEO_NONE,
	"http://api.easyjquery.com/ips/", "IP", "COUNTRY", "cityLatitude", "cityLongitude", SATGEO_NONE, 
	"http://freegeoip.net/json/", "ip", "country_code", "latitude", "longitude", SATGEO_STRINGLATLONG,
};
// - ------------------------------------------------------------------------------------------ - //
inline const SatGeoData DummyGeoData() {
	return SatGeoData( "?.?.?.?", "__", 0, 0, false );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const SatGeoData LookupGeoData( const SatGeoService* Service ) {
	SatGeoData Ret;
	Ret.Good = false;
		
	GelArray<char>* NetData = gelNetGetText( Service->URL );
	
	if ( NetData ) {		
		cJSON *root = cJSON_Parse( NetData->Data );
		
		if ( root ) {
			// Build a Schema to validate the data //
			char SchemaText[2048];
			safe_sprintf( SchemaText, sizeof(SchemaText),
				"{\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}",
				Service->IPField, "string",
				Service->CountryField, "string",
				Service->LatitudeField, (Service->Flags & SATGEO_STRINGLAT)  ? "string" : "number",
				Service->LongitudeField,(Service->Flags & SATGEO_STRINGLONG) ? "string" : "number"
				);
			
			cJSON *Schema = cJSON_Parse( SchemaText );
			int Err; // This is here, because goto requires no initializations //
			
			if ( Schema == 0 ) {
				printf( "Schema Fail: %s\n", SchemaText );
				goto SchemaFail;
			}
			
			Err = cJSON_ValidateSchema( Schema, root );
			
			cJSON_Delete( Schema );
			
			if ( Err == 0 ) {
				printf( "Data Failed Schema Validation!\n" );
				goto SchemaFail;
			}
			
			// ** DATA IS VALIDATED ** //
			
			// IP and Country //
			safe_sprintf( Ret.IP, sizeof(Ret.IP), "%s", cJSON_GetObjectItem( root, Service->IPField )->valuestring );
			safe_sprintf( Ret.Country, sizeof(Ret.Country), "%s", cJSON_GetObjectItem( root, Service->CountryField )->valuestring );

			// Latitude //
			if ( Service->Flags & SATGEO_STRINGLAT )
				Ret.Latitude = atof( cJSON_GetObjectItem( root, Service->LatitudeField )->valuestring );
			else
				Ret.Latitude = cJSON_GetObjectItem( root, Service->LatitudeField )->valuedouble;

			// Longitude //
			if ( Service->Flags & SATGEO_STRINGLONG )
				Ret.Longitude = atof( cJSON_GetObjectItem( root, Service->LongitudeField )->valuestring );
			else
				Ret.Longitude = cJSON_GetObjectItem( root, Service->LongitudeField )->valuedouble;

			// Success!! //
			Ret.Good = true;

			// **** //
			
			SchemaFail:	// Go here if the Schema fails //
				
			cJSON_Delete( root );
		}
		
		delete_GelArray<char>( NetData );
	}
	
	if ( !Ret.IsGood() ) {
		return DummyGeoData();
	}
	
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
void SatGeoData::operator()( ) { 
	for ( int idx = 0; idx < sizeof(GeoServices) / sizeof(SatGeoService); idx++ ) {
		*this = LookupGeoData( &GeoServices[idx] );
		if ( IsGood() )
			return;
	}
	
	*this = DummyGeoData();
}
// - ------------------------------------------------------------------------------------------ - //
