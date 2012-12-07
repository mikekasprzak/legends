// - ------------------------------------------------------------------------------------------ - //
#ifndef __CJSON_VALIDATESCHEMA_H__
#define __CJSON_VALIDATESCHEMA_H__
// - ------------------------------------------------------------------------------------------ - //
#include <cJSON/cJSON.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int cJSON_ValidateSchema( cJSON* Schema, cJSON* Data );

#ifdef __cplusplus
}; // extern "C" //
#endif // __cplusplus
// - ------------------------------------------------------------------------------------------ - //
#endif // __CJSON_VALIDATESCHEMA_H__ //
// - ------------------------------------------------------------------------------------------ - //
