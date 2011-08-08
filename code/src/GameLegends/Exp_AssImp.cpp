
#include <Debug/Log.h>
#include <Core/DataBlock.h>

#include <assimp.h>        // Plain-C interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags

extern void CallExp_AssImp();
void CallExp_AssImp() {
	Log("+ Now Testing AssImp\n");
	{
		const aiScene* Scene = aiImportFile( 
			"Content/Models/src/Chest.3ds",
			aiProcess_CalcTangentSpace | 
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType
			);
		
		if ( Scene ) {
			// Success! //
			
			aiReleaseImport( Scene );
		}
		else {
			ELog( "Scene load failed!\n" );
			Log( "%s\n", aiGetErrorString() );
		}
	}
	Log("- Done Testing AssImp\n");
	Log("\n");
}
