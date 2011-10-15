
#include "DiscObject.h"

#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>
#include <cJSON.h>

void cDiscObject::LoadFile( const char* InFile ) {
	DataBlock* File = new_read_nullterminate_DataBlock( InFile );
	
//	Log( "%i -- %i", File, File->Size );
	
	cJSON* root = cJSON_Parse( File->Data );

	if ( root == 0 ) {
		Log( "DiscObject: Error parsing data!\n" );
	}
	else {
		Log( "DiscObject Name: %s", cJSON_GetObjectItem( root, "Name" )->valuestring );
		
		cJSON* obj;
		
		obj = cJSON_GetObjectItem( root, "Texture" );
		if ( obj ) {
			Texture = AssetPool::Load( obj->valuestring );
		}

		obj = cJSON_GetObjectItem( root, "Color" );
		if ( obj ) {
			int Size = cJSON_GetArraySize( obj );
			if ( Size == 3 ) {
				Color = GEL_RGB( 
					cJSON_GetArrayItem( obj, 0 )->valueint,
					cJSON_GetArrayItem( obj, 1 )->valueint,
					cJSON_GetArrayItem( obj, 2 )->valueint
					);
			}
			else if ( Size == 4 ) {
				Color = GEL_RGBA( 
					cJSON_GetArrayItem( obj, 0 )->valueint,
					cJSON_GetArrayItem( obj, 1 )->valueint,
					cJSON_GetArrayItem( obj, 2 )->valueint,
					cJSON_GetArrayItem( obj, 3 )->valueint
					);
			}
			else {
				Log( "DiscObject Error: Invalid Array-of-Colors Size %i", Size );
			}
		}

		cJSON* OverlayRoot = cJSON_GetObjectItem( root, "Overlay" );
		if ( OverlayRoot ) {
			Log( "* Has Overlay" );
			obj = cJSON_GetObjectItem( OverlayRoot, "Texture" );
			if ( obj ) {
				OverlayTexture = AssetPool::Load( obj->valuestring );
			}
	
			obj = cJSON_GetObjectItem( OverlayRoot, "Color" );
			if ( obj ) {
				int Size = cJSON_GetArraySize( obj );
				if ( Size == 3 ) {
					OverlayColor = GEL_RGB( 
						cJSON_GetArrayItem( obj, 0 )->valueint,
						cJSON_GetArrayItem( obj, 1 )->valueint,
						cJSON_GetArrayItem( obj, 2 )->valueint
						);
				}
				else if ( Size == 4 ) {
					OverlayColor = GEL_RGBA( 
						cJSON_GetArrayItem( obj, 0 )->valueint,
						cJSON_GetArrayItem( obj, 1 )->valueint,
						cJSON_GetArrayItem( obj, 2 )->valueint,
						cJSON_GetArrayItem( obj, 3 )->valueint
						);
				}
				else {
					Log( "DiscObject Error: Invalid Array-of-Colors Size %i", Size );
				}
			}
		}		
	
		cJSON* GlowRoot = cJSON_GetObjectItem( root, "Glow" );
		if ( GlowRoot ) {
			Log( "* Has Glow" );
			obj = cJSON_GetObjectItem( GlowRoot, "Texture" );
			if ( obj ) {
				GlowTexture = AssetPool::Load( obj->valuestring );
			}
	
			obj = cJSON_GetObjectItem( GlowRoot, "Color" );
			if ( obj ) {
				int Size = cJSON_GetArraySize( obj );
				if ( Size == 3 ) {
					GlowColor = GEL_RGB( 
						cJSON_GetArrayItem( obj, 0 )->valueint,
						cJSON_GetArrayItem( obj, 1 )->valueint,
						cJSON_GetArrayItem( obj, 2 )->valueint
						);
				}
				else if ( Size == 4 ) {
					GlowColor = GEL_RGBA( 
						cJSON_GetArrayItem( obj, 0 )->valueint,
						cJSON_GetArrayItem( obj, 1 )->valueint,
						cJSON_GetArrayItem( obj, 2 )->valueint,
						cJSON_GetArrayItem( obj, 3 )->valueint
						);
				}
				else {
					Log( "DiscObject Error: Invalid Array-of-Colors Size %i", Size );
				}
			}
		}
	}
	
	cJSON_Delete( root );
	
	delete_DataBlock( File );
}
