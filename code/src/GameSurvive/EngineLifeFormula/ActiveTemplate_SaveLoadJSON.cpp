// - ------------------------------------------------------------------------------------------ - //
#include "ActiveTemplate.h"

#include <cJSON.h>
#include <Debug/Log.h>
#include <Core/DataBlock.h>
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
void cActiveTemplate::Load( const char* InFile ) {
	DataBlock* File = new_read_nullterminate_DataBlock( InFile );
	if ( File == 0 ) {
		Log( "! ActiveTemplate: Error reading file %s!", InFile );
	}
	cJSON* root = cJSON_Parse( File->Data );

	if ( root == 0 ) {
		Log( "! ActiveTemplate: Error parsing JSON data! Check for bad formatting, extra commas, etc" );
	}
	else {
//		MaxCount = cJSON_GetObjectItem( root, "MaxCount" )->valueint;

		// Reference //
//		int Count = cJSON_GetArraySize( root );
//		Log( "> %i Objects found in map", Count );
//	
//		for ( int idx = 0; idx < Count; idx++ ) {
//			cJSON* Element = cJSON_GetArrayItem( root, idx );
//	
//			cJSON* obj = cJSON_GetObjectItem( Element, "Type" );
//			if ( obj ) {
//				if ( obj->valuestring == std::string("Object") ) {
//					Vector3D Pos(0,0,0);
//
//					cJSON* _Pos = cJSON_GetObjectItem( Element, "Pos" );
//					if ( _Pos ) {
//						Pos = Vector3D(
//							cJSON_GetArrayItem( _Pos, 0 )->valuedouble,
//							cJSON_GetArrayItem( _Pos, 1 )->valuedouble,
//							cJSON_GetArrayItem( _Pos, 2 )->valuedouble
//							);
//					}
//			
//					AddObject( Pos, cJSON_GetObjectItem( Element, "Disc" )->valuestring );		
	}

	cJSON_Delete( root );
	delete_DataBlock( File );
}
// - ------------------------------------------------------------------------------------------ - //
void cActiveTemplate::Save( const char* OutFile ) {
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
