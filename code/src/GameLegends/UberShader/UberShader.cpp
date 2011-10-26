// - ------------------------------------------------------------------------------------------ - //
#include "UberShader.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>

#include <cJSON.h>
// - ------------------------------------------------------------------------------------------ - //
cUberShader::cUberShader( const char* InFile ) {
	Log( "+ Loading UberShader Permutations File..." );
	VLog( "* File: %s", InFile );
	DataBlock* File = new_read_nullterminate_DataBlock( InFile );
	
	VLog( "* Parsing JSON Data (%i bytes)...", File->Size );
	
	cJSON* root = cJSON_Parse( File->Data );

	if ( root == 0 ) {
		Log( "! UberShader: Error parsing JSON data!" );
	}
	else {
		cJSON* ShaderFile = cJSON_GetObjectItem( root, "File" );
		
		VLog( "* Loadinng Shader Sources..." );
		VLog( "* File: %s", ShaderFile->valuestring );
		DataBlock* ShaderSource = new_read_nullterminate_DataBlock( ShaderFile->valuestring );
		
		if ( ShaderSource ) {
			VLog( "* Shader Source Loaded (%i bytes).", ShaderSource->Size );
			
			cJSON* ShaderList = cJSON_GetObjectItem( root, "Shaders" );
			
			Log( "* %s", ShaderList->string );
			
			cJSON* Shader = ShaderList->child;
			while ( Shader != 0 ) {
				Log( "* * %s", Shader->string );
				
				cJSON* Obj = Shader->child;
				while ( Obj != 0 ) {
					Log("* * * %s", Obj->valuestring );
					Obj = Obj->next;
				}
				Shader = Shader->next;
			}			
			
			delete_DataBlock( ShaderSource );
			VLog( "* Done with Shader Sources" );
		}
		else {
			Log( "! UberShader: Error loading Shader Sources!" );
		}
		
		
		cJSON_Delete( root );
		VLog( "* Done JSON Data" );
	}

	delete_DataBlock( File );
	Log( "- Done with UberShader Permutations File." );
}
// - ------------------------------------------------------------------------------------------ - //
