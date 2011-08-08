#ifdef USES_ASSIMP

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
			if ( Scene->HasAnimations() ) {
				Log( "* Scene has %i Animations\n", Scene->mNumAnimations );
			}
			if ( Scene->HasCameras() ) {
				Log( "* Scene has %i Camerass\n", Scene->mNumCameras );
			}
			if ( Scene->HasLights() ) {
				Log( "* Scene has %i Lights\n", Scene->mNumLights );
			}
			if ( Scene->HasMaterials() ) {
				Log( "* Scene has %i Materials\n", Scene->mNumMaterials );
			}
			if ( Scene->HasMeshes() ) {
				Log( "* Scene has %i Meshes\n", Scene->mNumMeshes );
				
				for ( int Meshes = 0; Meshes < Scene->mNumMeshes; Meshes++ ) {
					Log( "** Mesh Name: %s\n", Scene->mMeshes[Meshes]->mName.data );
				}
			}
			if ( Scene->HasTextures() ) {
				Log( "* Scene has %i Textures\n", Scene->mNumTextures );
			}
			
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

#endif // USES_ASSIMP //
