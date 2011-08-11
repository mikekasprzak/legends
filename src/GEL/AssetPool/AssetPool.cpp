// - ------------------------------------------------------------------------------------------ - //
// NOTE: GelAsset_Instance is a little weird. You construct with a filename, and pass a prefix to 
//   the load.  This is very odd. Change this.
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include <Core/DataBlock_LZMA.h>

#include <Core/GelDirectory.h>
#include <Util/String/String.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelAsset.h>
#include "AssetPool.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics_System.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelTexture.h>
// - ------------------------------------------------------------------------------------------ - //
// Use some STL, since I want to save time //
#include <map>
#include <vector>
#include <string>
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
// Up here, so this isn't considered part of the namespace //
extern char AppBaseDir[];
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
		enum AssetClass {
			GEL_ASSETCLASS_NULL = 0,
			GEL_ASSETCLASS_TEXTURE = 1,
			GEL_ASSETCLASS_MODEL,
			GEL_ASSETCLASS_AUDIO,
			GEL_ASSETCLASS_SCRIPT,
		};

	public:
		std::string FileName;

		AssetClass Type;

		DataBlock* UnProcessed;

		union {
			GelTexture* Texture;
			char* Data;
		};

	public:
		GelAsset_Instance() :
			Type( GEL_ASSETCLASS_NULL ),
			UnProcessed( 0 )
		{
			// Null the pointer //
			Data = 0;
		}
		
		GelAsset_Instance( const char* _FileName ) :
			FileName( _FileName ),
			Type( GEL_ASSETCLASS_NULL ),
			UnProcessed( 0 )
		{
			// Null the pointer //
			Data = 0;
		}
		
		inline bool HasData() {
			return (Data != 0) || (UnProcessed != 0);
		}
		
		void Load( const std::string Prefix ) {
			// Build a Path to the file, and adapt to system specific slashes. //
			std::string File = String::SystemSlash( Prefix + FileName );

			// Clean up if re-used //
			if ( HasData() ) {
				Log( "* Freeing old Data...\n" );
				Free();
			}

			// A place to hold the processed data //			
			DataBlock* Processed = 0;

			{
				// Bulk-Load the data //
				Log( "* Caching \"%s\"...\n", File.c_str() );
				UnProcessed = new_read_DataBlock( File.c_str() );
	
				// Check if the incoming data is compressed //
				GelAssetType AssetType;
				AssetType.TestCompressionData( UnProcessed->Data );

				if ( AssetType.IsCompression() ) {
					VLog( "* File Data Code: 0x%x\n", AssetType.Type );
					// If Compressed, figure out the compression scheme and decompress //
					switch ( AssetType.Type ) {
						case GEL_ASSET_LZMA: {
							VLog("* Compressed Data (LZMA). Uncompressing...\n" );
							Processed = new_unpack_LZMA_DataBlock( UnProcessed );
							break;
						}
						default: {
							ELog("Unknown or Unsupported Asset Compression Format!\n" );
							delete_DataBlock( UnProcessed );
							return;
							break;
						}
					};
				}
				else {
					// If not compressed //
					VLog( "* Not Compressed\n" );
					
					Processed = UnProcessed;
					UnProcessed = 0;
				}
			}
			
			if ( Processed ) {
				// Now, determine what the data REALLY is //
				GelAssetType AssetDataType;
				AssetDataType.TestData( Processed->Data );
				
				if ( AssetDataType.IsTexture() ) {
					VLog("* Asset is a Texture (0x%x)\n", Processed );
					Type = GEL_ASSETCLASS_TEXTURE;
					Texture = new GelTexture();
					Texture->Load( Processed );
				}
				else if ( AssetDataType.IsModel() ) {
					VLog("* Asset is a Model (0x%x)\n", Processed );
					Type = GEL_ASSETCLASS_MODEL;
				}
				else if ( AssetDataType.IsAudio() ) {
					VLog("* Asset is a Audio (0x%x)\n", Processed );
					Type = GEL_ASSETCLASS_AUDIO;
				}
				else {
					// Do FileName Test //
					
					
					
					ELog("Unknown Asset Type\n" );
					Type = GEL_ASSETCLASS_NULL;
					delete_DataBlock( UnProcessed );
				}
			}
		}

		void Free() {
			if ( HasData() ) {
				if ( Data != 0 ) {
					switch ( Type ) {
						case GEL_ASSETCLASS_TEXTURE: {
							Texture->Free();
							break;
						}
						case GEL_ASSETCLASS_MODEL:
						break;
						case GEL_ASSETCLASS_AUDIO:
						break;
						case GEL_ASSETCLASS_SCRIPT:
						break;
					};
					
					// Reset to zero //
					Data = 0;
				}
				
				if ( UnProcessed != 0 ) {
					delete_DataBlock( UnProcessed );
				}
			}
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
		//ReadDir += String::Slash;
		
		GelDirectory* Dir = new_GelDirectory( ReadDir.c_str() );
		Log( "+ Adding Asset Directory \"%s\" (%i Total)\n", ReadDir.c_str(), size_GelDirectory( Dir ) );
		
		for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
			std::string SlashString = String::Slash;
			SlashString += index_GelDirectory( Dir, idx );
			AssetInstance.push_back( GelAsset_Instance( (std::string(Directory) + SlashString).c_str() ) );
			
			std::string NoExt = String::NoExtensions( SlashString );
			AssetLookup[ NoExt.c_str() ] = AssetInstance.size() - 1;
			
			Log( "* %s [%s] (%i)\n", SlashString.c_str(), NoExt.c_str(), idx );
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
			Log( "- %s found in lookup cache!\n", FileName );
			return SearchIterator->second;
		}

		// Linear pattern matching search (if it contains the pattern, instead of exact match) //
		for ( size_t idx = 0; idx < AssetInstance.size(); idx++ ) {
			// Linear test strings if they contain the pattern passed //
			if ( AssetInstance[idx].FileName.find( FileName ) != std::string::npos ) {
				Log( "- Found %s!\n", FileName );
				return idx;
			}
		}
		Log( "- %s NOT FOUND!!\n", FileName );
		
		// Otherwise, no file was found.  Return the dummy Id (0). //
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	void Set( const GelAssetHandle Asset ) {
		if ( AssetInstance[ Asset ].HasData() ) {	
			AssetInstance[ Asset ].Texture->Bind( 0 );
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void LoadAsset( const GelAssetHandle Asset ) {
		// Bail if the dummy asset //
		if ( Asset == 0 )
			return;
		
		// If this Instance has data //
		if ( AssetInstance[ Asset ].HasData() ) {
			// If a Texture Handle is available, activate it //
			if ( AssetInstance[ Asset ].Texture->Handle ) {
				Set( Asset );		
				return;
			}
		}
		
		// TODO: If there is uncompressed data, load it in to memory //
		// TODO: If there is compressed data, decompress it, then load in to memory //
		
		// If there is only a filename, load it //
		{
			AssetInstance[ Asset ].Load( FilePrefix );

#ifdef HACK_TEXTURE5_GLITCH
			if ( AssetInstance[ Asset ].Texture->Handle == 5 ) {
				Log( "** WebOS! ** : Working around 'Texture 5' glitch...\n" );
				PalmGlitch = AssetInstance[ Asset ].Texture->Handle;				
				AssetInstance[ Asset ].Load( FilePrefix );
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
			Log( "> Shutdown Detected!  Aborting Asset Load...\n");
			return 0;
		}

		// Search for ID based on input string //
		GelAssetHandle Asset = Find( FileName );
		
		// Loaded, so cache the texture in memory //
		LoadAsset( Asset );
		
		// Return the Id //
		return Asset;	
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
//	// - -------------------------------------------------------------------------------------- - //
//	// Free textures so we can reload them in to the new/current OpenGL Context //
//	void ReleaseTextures() {
//		Exit();
//	}
//	// - -------------------------------------------------------------------------------------- - //
//	// Reload all the previously released textures //
//	void ReloadTextures() {
//		for ( size_t idx = 0; idx < AssetInstance.size(); idx++ ) {
//			LoadAsset( idx );
//		}
//	}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace AssetPool //
// - ------------------------------------------------------------------------------------------ - //
