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

// - ------------------------------------------------------------------------------------------ - //
// http://tools.ietf.org/html/draft-zyp-json-schema-03
// - ------------------------------------------------------------------------------------------ - //
//const char LightSchema[] = "{\"IP\":\"text\",\"CountryCode\":\"text\",\"Latitude\":\"number\",\"Longitude\":\"number\"}";
// - ------------------------------------------------------------------------------------------ - //
int cJSON_ValidateSchema( cJSON* Schema, cJSON* Data ) {
	for ( int idx = 0; idx < cJSON_GetArraySize(Schema); idx++ ) {
		cJSON* Sc = cJSON_GetArrayItem(Schema,idx);
		cJSON* Ob = cJSON_GetObjectItem( Data, Sc->string );

//		printf( "> %s\n", cJSON_GetArrayItem(Schema,idx)->string );

		// TODO: Objects (recursive) and maybe Arrays //
		if ( Ob == 0 ) {
			return 0;
		}
		else {
			if ( strcmp( Sc->valuestring, "any" ) == 0 ) {
			}
			else if ( strcmp( Sc->valuestring, "string" ) == 0 ) {
				if ( Ob->type != cJSON_String )
					return 0;
			}
			else if ( strcmp( Sc->valuestring, "number" ) == 0 ) {
				if ( Ob->type != cJSON_Number )
					return 0;
			}
			else {
				printf( "cJSON_ValidateSchema Error: Unknown Validation Parameter\n" );
				return 0;
			}
		}
	}
	
	return 1;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const GELGeoData LookupGeoData( const GELGeoService* Service ) {
	GELGeoData Ret;
	Ret.Success = false;
		
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
				Service->LatitudeField, (Service->Flags & GELGEO_STRINGLAT)  ? "string" : "number",
				Service->LongitudeField,(Service->Flags & GELGEO_STRINGLONG) ? "string" : "number"
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
			
			SchemaFail:	// Go here if the Schema fails //
				
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
