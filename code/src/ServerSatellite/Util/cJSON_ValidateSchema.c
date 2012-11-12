// - ------------------------------------------------------------------------------------------ - //
#include <cJSON/cJSON.h>
#include "cJSON_ValidateSchema.h"
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
//				printf( "cJSON_ValidateSchema Error: Unknown Validation Parameter\n" );
				return -1;
			}
		}
	}
	
	return 1;
}
// - ------------------------------------------------------------------------------------------ - //
