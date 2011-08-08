// - ------------------------------------------------------------------------------------------ - //
#include <Util/WhitespaceTokenizer/WhitespaceTokenizer.h>

using namespace std;
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Graphics/GelColor.h>
#include <Graphics/GelUV.h>
#include "PMEFile.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_ASSIMP
// - ------------------------------------------------------------------------------------------ - //
#include <assimp.h>        // Plain-C interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ASSIMP //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cPMEFile::TextLoad() {
	int Lines = 0;
	Log( "+ Loading %s\n", FileName.c_str() );

	// TODO: Support compressed reading //
	cWhitespaceTokenizer File( FileName.c_str() );
	
	do {
		if ( File.IsStringToken( "Mesh" ) ) {
			File.NextToken();
			
			// A mesh found, so add one //
			Mesh.push_back( cPMEMesh() );
			Mesh.back().Name = File.StringToken();
		}
		else if ( File.IsStringToken( "Materials" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "Material" ) ) {
			File.NextToken();
			
			// Ignore "Index" Token //
			File.NextToken();
			
			// Name //
			Mesh.back().Material.push_back( cPMEMaterial() );
			Mesh.back().Material.back().Name = File.StringToken();
		}
		else if ( File.IsStringToken( "Image" ) ) {
			File.NextToken();
			
			Mesh.back().Material.back().ImageFileName = File.StringToken();
		}
		else if ( File.IsStringToken( "Vertices" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "Vertex" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Color = GEL_RGB_WHITE;
		}
		else if ( File.IsStringToken( "VertexNorm" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();// * Real(200);
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();// * Real(200);
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();// * Real(200);
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Color = GEL_RGB_WHITE;
		}
		else if ( File.IsStringToken( "VertexNormUV" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();// * Real(100);
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();// * Real(100);
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();// * Real(100);
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * GEL_UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * GEL_UV_ONE_F;
			Mesh.back().Vertex.back().Color = GEL_RGB_WHITE;
		}
		else if ( File.IsStringToken( "VertexNormUVColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * GEL_UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * GEL_UV_ONE_F;
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = GEL_RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "VertexNormColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Normal.z = File.StepFloatToken();
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = GEL_RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "VertexUV" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * GEL_UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * GEL_UV_ONE_F;
			Mesh.back().Vertex.back().Color = GEL_RGB_WHITE;
		}
		else if ( File.IsStringToken( "VertexUVColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			Mesh.back().Vertex.back().UV.u = File.StepFloatToken() * GEL_UV_ONE_F;
			Mesh.back().Vertex.back().UV.v = File.StepFloatToken() * GEL_UV_ONE_F;
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = GEL_RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "VertexColor" ) ) {
			File.NextToken();
			
			Mesh.back().Vertex.push_back( cPMEVertex() );
			Mesh.back().Vertex.back().Pos.x = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.y = File.StepFloatToken();
			Mesh.back().Vertex.back().Pos.z = File.StepFloatToken();
			int r = File.StepIntegerToken();
			int g = File.StepIntegerToken();
			int b = File.StepIntegerToken();
			int a = File.StepIntegerToken();
			Mesh.back().Vertex.back().Color = GEL_RGBA(r,g,b,a);
		}
		else if ( File.IsStringToken( "Faces" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "FaceGroup" ) ) {
			File.NextToken();
			
			Mesh.back().FaceGroup.push_back( cPMEFaceGroup() );
		}
		else if ( File.IsStringToken( "UseMaterial" ) ) {
			File.NextToken();
			
			Mesh.back().FaceGroup.back().Material = File.IntegerToken();
		}
		else if ( File.IsStringToken( "Face" ) ) {
			File.NextToken();
			
			Mesh.back().FaceGroup.back().Face.push_back( cPMEFaceGroup::FaceType() );
			Mesh.back().FaceGroup.back().Face.back().a = File.StepIntegerToken();
			Mesh.back().FaceGroup.back().Face.back().b = File.StepIntegerToken();
			Mesh.back().FaceGroup.back().Face.back().c = File.StepIntegerToken();
		}
		else if ( File.IsStringToken( "Properties" ) ) {
			// Ignored //
		}
		else if ( File.IsStringToken( "Property" ) ) {
			// TODO: Property decoding and noting //
		}
		else {
#ifndef _MSC_VER
			Log( "%s (%s): Unknown Command\n", __PRETTY_FUNCTION__, __FILE__ );
#endif // _MSC_VER //
		}
		Lines++;
	} while ( File.NextLine() );
	Log("- Done. %i lines processed\n", Lines );
}
// - ------------------------------------------------------------------------------------------ - //
void cPMEFile::TextSave() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_ASSIMP
// - ------------------------------------------------------------------------------------------ - //
void cPMEFile::Import( const char* FileName ) {
	const aiScene* Scene = aiImportFile( 
		FileName,
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
				Mesh.push_back( cPMEMesh() );
				
				Log( "**\n" );

				for ( int idx = 0; idx < Scene->mMeshes[Meshes]->mNumVertices; idx++ ) {
					Mesh.back().Vertex.push_back( cPMEVertex() );
					Mesh.back().Vertex.back().Pos.x = Scene->mMeshes[Meshes]->mVertices[idx].x;
					Mesh.back().Vertex.back().Pos.y = Scene->mMeshes[Meshes]->mVertices[idx].y;
					Mesh.back().Vertex.back().Pos.z = Scene->mMeshes[Meshes]->mVertices[idx].z;
					Mesh.back().Vertex.back().Color = GEL_RGB_WHITE;
				}

				Log( "**\n" );
				
				Mesh.back().FaceGroup.push_back( cPMEFaceGroup() );
				for ( int idx = 0; idx < Scene->mMeshes[Meshes]->mNumFaces; idx++ ) {
					Mesh.back().FaceGroup.back().Face.push_back( cPMEFaceGroup::FaceType() );
					Mesh.back().FaceGroup.back().Face.back().a = Scene->mMeshes[Meshes]->mFaces[idx].mIndices[0];
					Mesh.back().FaceGroup.back().Face.back().b = Scene->mMeshes[Meshes]->mFaces[idx].mIndices[1];
					Mesh.back().FaceGroup.back().Face.back().c = Scene->mMeshes[Meshes]->mFaces[idx].mIndices[2];
				}	
				Log( "**\n" );
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
// - ------------------------------------------------------------------------------------------ - //
#else // USES_ASSIMP //
// - ------------------------------------------------------------------------------------------ - //
void cPMEFile::Import( const char* FileName ) {
	ELog("WARNING: Assimp not available.\n" );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ASSIMP //
// - ------------------------------------------------------------------------------------------ - //
