// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelDirectory.h>
#include <Util/String/String.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics.h>
#include <Graphics/GelTexture.h>
// - ------------------------------------------------------------------------------------------ - //
#include "AssetPool.h"
// - ------------------------------------------------------------------------------------------ - //
// Use some STL, since I want to save time //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(_MSC_VER) || defined(USES_WINDOWS_SLASH)
	#define TEXTURE_POOL_SLASH "\\"
#else // _MSC_VER //
	#define TEXTURE_POOL_SLASH "/"
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern char AppBaseDir[];
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
extern void MessageLoop();
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_PALM
#define HACK_TEXTURE5_GLITCH
#endif // PRODUCT_PALM //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace AssetPool {
// - ------------------------------------------------------------------------------------------ - //
#ifdef HACK_TEXTURE5_GLITCH	
	unsigned int PalmGlitch;
#endif // HACK_TEXTURE5_GLITCH //

	// - -------------------------------------------------------------------------------------- - //
	class GelAsset_Instance {
	public:
		std::string FileName;
		
		
		
		GelTexture Texture;

	public:
		GelAsset_Instance()
		{
		}
		
		GelAsset_Instance( const char* _FileName ) :
			FileName( _FileName )
		{
			// Note: I did not pass anythnig to Texture, that would cause a load //
		}
		
		void Load( const std::string Prefix ) {
			std::string File = String::SystemSlash( Prefix + FileName );
			Log( "* Caching \"%s\"...\n", File.c_str() );
			Texture.Load( File.c_str() );
		}

		void Free() {
			Texture.Free();
		}
	};
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Members //
	std::string FilePrefix;	
	std::vector< GelAsset_Instance > AssetInstance;
	std::map< std::string, GelAssetHandle > AssetLookup;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	void Init( const char* BaseDirectory ) {		
		GelTexture::Init();
		
#ifdef HACK_TEXTURE5_GLITCH
		PalmGlitch = 0;
#endif // HACK_TEXTURE5_GLITCH //
		
		// Create a string containing the base filename directory //
		{
			// If an empty string (i.e. first character is terminator) //
			if ( BaseDirectory[0] == 0 )
				FilePrefix = AppBaseDir;
			else
				FilePrefix = std::string( AppBaseDir ) + BaseDirectory;

			// Store the prefix (without trailing slash.  Slash will be part of search strings) //

			VVLog("FilePrefix: %s\n", FilePrefix.c_str());
		}
		
		{
			// Initalize the AssetInstance //
			AssetInstance.clear();
			AssetInstance.push_back( GelAsset_Instance() );	// Dummy //
			
			// Initalize the AssetLookup //
			AssetLookup.clear();
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void AddDirectory( const char* Directory ) {
		// TODO: Be sure to include a beginning "/" in the populated filenames //
		// TODO: Be sure to remove file extensions in the search query //
		std::string ReadDir = FilePrefix;
		if ( Directory[0] != 0 ) {
			ReadDir += Directory;
		}
		//ReadDir += TEXTURE_POOL_SLASH;
		
		GelDirectory* Dir = new_GelDirectory( ReadDir.c_str() );
		Log( "+ Adding Asset Directory \"%s\" (%i Total)\n", ReadDir.c_str(), size_GelDirectory( Dir ) );
		
		for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
			std::string SlashString = TEXTURE_POOL_SLASH;
			SlashString += index_GelDirectory( Dir, idx );
			AssetInstance.push_back( GelAsset_Instance( (std::string(Directory) + SlashString).c_str() ) );
			
			std::string NoExt = String::NoExtensions( SlashString );
			AssetLookup[ NoExt.c_str() ] = AssetInstance.size() - 1;
			
			Log( "* %s (%i) [Pattern: %s]\n", SlashString.c_str(), idx, NoExt.c_str() );
		}
		
		delete_GelDirectory( Dir );
		
		Log( "- Asset Directory added.\n" );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	GelAssetHandle Find( const char* FileName ) {
		// Search the map for the specific pattern //
		std::map<std::string, GelAssetHandle>::iterator SearchIterator = AssetLookup.find( FileName );
		Log( "+ Searching for %s\n", FileName );
		
		// If it was found, return the Id //
		if ( SearchIterator != AssetLookup.end() ) {
			VLog( "- %s found in lookup cache!\n", FileName );
			return SearchIterator->second;
		}

		// Linear pattern matching search (if it contains the pattern, instead of exact match) //
		for ( size_t idx = 0; idx < AssetInstance.size(); idx++ ) {
			// Linear test strings if they contain the pattern passed //
			if ( AssetInstance[idx].FileName.find( FileName ) != std::string::npos ) {
				VLog( "- Found %s!\n", FileName );
				return idx;
			}
		}
		Log( "- %s NOT FOUND!!\n", FileName );
		
		// Otherwise, no file was found.  Return the dummy Id (0). //
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	void Set( const GelAssetHandle Texture ) {
		AssetInstance[ Texture ].Texture.Bind( 0 );
		
//		glBindTexture( GL_TEXTURE_2D, AssetInstance[ Texture ].Texture.Handle );
////		if ( Texture != 0 ) {
////			if ( AssetInstance[ Texture ].Texture.Handle == 0 ) {
////				LoadTexture( Texture );
////			}
////			
////			glBindTexture( GL_TEXTURE_2D, AssetInstance[ Texture ].Texture.Handle );
////		}
////		else {
////			glBindTexture( GL_TEXTURE_2D, 0 );
////		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void LoadTexture( const GelAssetHandle Texture ) {
		// Bail if the dummy texture //
		if ( Texture == 0 )
			return;
		
		// If GL Texture is set, activate it //
		if ( AssetInstance[ Texture ].Texture.Handle ) {
			Set( Texture );		
			return;
		}
						
		// TODO: If there is uncompressed data, load it in to memory //
		// TODO: If there is compressed data, decompress it, then load in to memory //
		
		// If there is only a filename, load it //
		{
			AssetInstance[ Texture ].Load( FilePrefix );

#ifdef HACK_TEXTURE5_GLITCH
			if ( AssetInstance[ Texture ].Texture.Handle == 5 ) {
				Log( "** WebOS! ** : Working around 'Texture 5' glitch...\n" );
				PalmGlitch = AssetInstance[ Texture ].Texture.Handle;				
				AssetInstance[ Texture ].Load( FilePrefix );
			}
#endif // HACK_TEXTURE5_GLITCH //
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	GelAssetHandle Load( const char* FileName ) {
#ifdef USES_SDL
		MessageLoop();
#endif // USES_SDL //

		// Bail if we're in the middle of shutting down //
		if ( System::ShutdownGame || System::CloseButtonPressed ) {
			Log( "> Shutdown Detected!  Aborting Texture Load...\n");
			return 0;
		}

		// Search for ID based on input string //
		GelAssetHandle Texture = Find( FileName );
		
		// Loaded, so cache the texture in memory //
		LoadTexture( Texture );
		
		// Return the Id //
		return Texture;	
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	void Free( const GelAssetHandle Asset ) {
		AssetInstance[ Asset ].Free();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	void Exit() {
		GelTexture::LogAllocations();
		
		for ( size_t idx = 0; idx < AssetInstance.size(); idx++ ) {
			AssetInstance[ idx ].Free();
		}
		
#ifdef HACK_TEXTURE5_GLITCH
		if ( PalmGlitch != 0 ) {
			glDeleteTextures( 1, (const GLuint*)&PalmGlitch );
		}
#endif // HACK_TEXTURE5_GLITCH //
		
		GelTexture::Exit();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Free textures so we can reload them in to the new/current OpenGL Context //
	void ReleaseTextures() {
		Exit();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Reload all the previously released textures //
	void ReloadTextures() {
		for ( size_t idx = 0; idx < AssetInstance.size(); idx++ ) {
			LoadTexture( idx );
		}
	}
// - ------------------------------------------------------------------------------------------ - //
#undef TEXTURE_POOL_SLASH
// - ------------------------------------------------------------------------------------------ - //
}; // namespace AssetPool //
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//inline GelAssetHandle gelLoadTexture( const char* FileName ) {
//	// TODO: Remove file extensions from the search string //
//#ifdef _MSC_VER
//	std::string Temp = String::WindowsSlash( std::string(FileName) );
//	VLog( "Loading %s...\n", Temp.c_str() );
//	return TexturePool::Load( Temp.c_str() );
//#else // _MSC_VER //
//	return TexturePool::Load( FileName );
//#endif // _MSC_VER //
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void gelSetTexture( const GelAssetHandle Texture ) {
//	TexturePool::Set( Texture );
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void gelFreeTexture( const GelAssetHandle Texture ) {
//	TexturePool::Free( Texture );
//}
//// - ------------------------------------------------------------------------------------------ - //
