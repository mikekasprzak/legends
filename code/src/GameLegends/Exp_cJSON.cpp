
#include <Debug/Log.h>
#include <Core/DataBlock.h>

#include <cJSON.h>

extern void CallExp_cJSON();
void CallExp_cJSON() {
	Log("+ Now Testing cJSON\n");
	{
		DataBlock* Jay = new_read_nullterminate_DataBlock( "XpContent/MapLayout.json" );
		
		Log( "%s\n", Jay->Data );
		
		Log( "Parsing file...\n" );
		
		cJSON* root = cJSON_Parse( Jay->Data );

		if ( root == 0 ) {
			Log( "Error parsing data!\n" );
		}
		else {
			Log( "Parsed!\n" );
			Log( "Extracting Data...\n" );
	
			cJSON* terrain = cJSON_GetObjectItem( root, "terrain" );
			int ArraySize = cJSON_GetArraySize( terrain );
	
			for ( int idx = 0; idx < ArraySize; idx++ ) {
				cJSON* obj = cJSON_GetArrayItem( terrain, idx );
				Log( "%s -- %i, %i, %i\n", 
					cJSON_GetObjectItem( obj, "file" )->valuestring, 
					cJSON_GetObjectItem( obj, "x" )->valueint, 
					cJSON_GetObjectItem( obj, "y" )->valueint,
					cJSON_GetObjectItem( obj, "z" )->valueint 
					);
			}
		}
		
		cJSON_Delete( root );
		
		delete_DataBlock( Jay );
	}
	Log("- Done Testing cJSON\n");
	Log("\n");
}
