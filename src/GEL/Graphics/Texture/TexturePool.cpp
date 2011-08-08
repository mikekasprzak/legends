// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics.h>
#include <Graphics/GelTexture.h>
#include "TexturePool.h"
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "Pool_String.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelDirectory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "PVRTexture_Load.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define TEXTURE_POOL_SLASH "\\"
#else // _MSC_VER //
#define TEXTURE_POOL_SLASH "/"
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#if !defined(USES_IOS) && !defined(USES_WINDOWSMOBILE)
extern char AppBaseDir[];
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
extern void MessageLoop();
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //

#ifdef PRODUCT_PALM
#define HACK_TEXTURE5_GLITCH
#endif // PRODUCT_PALM //

// - ------------------------------------------------------------------------------------------ - //
namespace TexturePool {
// - ------------------------------------------------------------------------------------------ - //
	int AllocCount;
	int AllocSum;

#ifdef HACK_TEXTURE5_GLITCH	
	unsigned int PalmGlitch;
#endif // HACK_TEXTURE5_GLITCH //

	// - -------------------------------------------------------------------------------------- - //
	class GelTexture_Instance {
	public:
		std::string FileName;
		GelTexture Texture;

	public:
		GelTexture_Instance()
		{
		}
		
		GelTexture_Instance( const char* _FileName ) :
			FileName( _FileName )
		{
			// Note: I did not pass anythnig to Texture, that would cause a load //
		}
		
		void Load( std::string Prefix ) {
			Texture.Load( (Prefix + FileName).c_str() );
		}

		void Free() {
			Texture.Free();
		}
	};
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Members //
	std::string FilePrefix;	
	std::vector< GelTexture_Instance > TextureInfo;
	std::map<std::string, GelTextureID> TextureLookup;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	void Init( const char* BaseDirectory ) {
		AllocCount = 0;
		AllocSum = 0;
		
#ifdef HACK_TEXTURE5_GLITCH
		PalmGlitch = 0;
#endif // HACK_TEXTURE5_GLITCH //
		
		// Create a string containing the base filename directory //
		{
			char _FilePrefix[2048];

#ifdef USES_IOS

// TODO: Update this //
#define MY_APP_NAME "SmilesSE.app"

			// If an empty string (i.e. first character is terminator) //
			if ( BaseDirectory[0] == 0 )
				sprintf(_FilePrefix,"%s/%s", getenv("HOME"), MY_APP_NAME );
			else
				sprintf(_FilePrefix,"%s/%s/%s", getenv("HOME"), MY_APP_NAME, BaseDirectory );
#elif defined(USES_WINDOWSMOBILE)
			if ( BaseDirectory[0] == 0 )
				sprintf(_FilePrefix,"Program Files\\Smiles\\" );
			else
				sprintf(_FilePrefix,"Program Files\\Smiles\\%s", BaseDirectory );
#else // USES //
			// If an empty string (i.e. first character is terminator) //
			if ( BaseDirectory[0] == 0 )
				sprintf(_FilePrefix,"%s", AppBaseDir );
			else
				sprintf(_FilePrefix,"%s%s", AppBaseDir, BaseDirectory );			
#endif // USES //

			// Store the prefix (without trailing slash.  Slash will be part of search strings) //
			FilePrefix = _FilePrefix;

			VLog("FilePrefix: %s\n", FilePrefix.c_str());
		}
		
		{
			// Initalize the TextureInfo //
			TextureInfo.clear();
			TextureInfo.push_back( GelTexture_Instance() );	// Dummy //
			
			// Initalize the TextureLookup //
			TextureLookup.clear();
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void AddDirectory( const char* Directory ) {
		// TODO: Be sure to include a beginning "/" in the populated filenames //
		// TODO: Be sure to remove file extensions in the search query //
		std::string ReadDir = FilePrefix;
		if ( Directory[0] != 0 ) {
//			ReadDir += TEXTURE_POOL_SLASH;
			ReadDir += Directory;
		}
		//ReadDir += TEXTURE_POOL_SLASH;
		
		GelDirectory* Dir = new_GelDirectory( ReadDir.c_str() );
		Log( "Adding Directory \"%s\" (%i)\n", ReadDir.c_str(), size_GelDirectory( Dir ) );
		
		for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
			std::string SlashString = TEXTURE_POOL_SLASH;
			SlashString += index_GelDirectory( Dir, idx );
			TextureInfo.push_back( GelTexture_Instance( SlashString.c_str() ) );
			
			std::string NoExt = NoExtensions( SlashString );
			TextureLookup[ NoExt.c_str() ] = TextureInfo.size() - 1;
			
			Log( "* %s (%i)\n", SlashString.c_str(), idx );
			VLog( "  %s\n", NoExt.c_str() );
		}
		
		delete_GelDirectory( Dir );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	GelTextureID FindID( const char* FileName ) {
		// Search the map for the specific pattern //
		std::map<std::string, GelTextureID>::iterator SearchIterator = TextureLookup.find( FileName );
		Log( "- Searching for %s\n", FileName );
		
		// If it was found, return the Id //
		if ( SearchIterator != TextureLookup.end() ) {
			VLog( "+ %s found in lookup cache!\n", FileName );
			return SearchIterator->second;
		}

		// Linear pattern matching search (if it contains the pattern, instead of exact match) //
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			// Linear test strings if they contain the pattern passed //
			if ( TextureInfo[idx].FileName.find( FileName ) != std::string::npos ) {
				VLog( "+ Found %s!\n", FileName );
				return idx;
			}
		}
		Log( "* %s not found\n", FileName );
		
		// Otherwise, no file was found.  Return the dummy Id (0). //
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	void Set( const GelTextureID Texture ) {
		TextureInfo[ Texture ].Texture.Bind( 0 );
		
//		glBindTexture( GL_TEXTURE_2D, TextureInfo[ Texture ].Texture.Handle );
////		if ( Texture != 0 ) {
////			if ( TextureInfo[ Texture ].Texture.Handle == 0 ) {
////				LoadTexture( Texture );
////			}
////			
////			glBindTexture( GL_TEXTURE_2D, TextureInfo[ Texture ].Texture.Handle );
////		}
////		else {
////			glBindTexture( GL_TEXTURE_2D, 0 );
////		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void LoadTexture( const GelTextureID Texture ) {
		// Bail if the dummy texture //
		if ( Texture == 0 )
			return;
		
		// If GL Texture is set, activate it //
		if ( TextureInfo[ Texture ].Texture.Handle ) {
			Set( Texture );		
			return;
		}
						
		// TODO: If there is uncompressed data, load it in to memory //
		// TODO: If there is compressed data, decompress it, then load in to memory //
		
		// If there is only a filename, load it //
		{
			std::string File = FilePrefix;
			File += TextureInfo[ Texture ].FileName;
			
			Log( "Caching %s...\n", File.c_str() );
			
			TextureInfo[ Texture ].Texture.Load( File.c_str() );

			// TODO: Figure out what kind of image this file is //
			//TextureInfo[ Texture ].Texture.Handle = LoadGL_PVRTexture( File.c_str(), &TextureInfo[ Texture ].Texture.Detail );

#ifdef HACK_TEXTURE5_GLITCH
			if ( TextureInfo[ Texture ].Texture.Handle == 5 ) {
				Log( "** WebOS! ** : Working around 'Texture 5' glitch...\n" );
				PalmGlitch = TextureInfo[ Texture ].Texture.Handle;				
				TextureInfo[ Texture ].Texture.Load( File.c_str() );
//				TextureInfo[ Texture ].Texture.Handle = LoadGL_PVRTexture( File.c_str(), &TextureInfo[ Texture ].Texture.Detail );
			}
#endif // HACK_TEXTURE5_GLITCH //

			TexturePool::AllocCount++;
			TexturePool::AllocSum += TextureInfo[ Texture ].Texture.Handle;
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	GelTextureID Load( const char* FileName ) {
#ifdef USES_SDL
		MessageLoop();
#endif // USES_SDL //

		// Bail if we're in the middle of shutting down //
		if ( System::ShutdownGame || System::CloseButtonPressed ) {
			Log( "* Shutdown Detected!  Aborting Texture Load...\n");
			return 0;
		}

		// Search for ID based on input string //
		GelTextureID Texture = FindID( FileName );
		
		// Loaded, so cache the texture in memory //
		LoadTexture( Texture );
		
		// Return the Id //
		return Texture;	
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	void Free( const GelTextureID Texture ) {
		if ( TextureInfo[ Texture ].Texture.Handle ) {
			TexturePool::AllocCount--;
			TexturePool::AllocSum -= TextureInfo[ Texture ].Texture.Handle;

			Log( "* GL Texture %i Free'd\n", TextureInfo[ Texture ].Texture.Handle );
			glDeleteTextures( 1, (const GLuint*)&TextureInfo[ Texture ].Texture.Handle );
			TextureInfo[ Texture ].Texture.Handle = 0;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	void Exit() {
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			//Free( idx );
			TextureInfo[ idx ].Free();
		}
		
#ifdef HACK_TEXTURE5_GLITCH
		if ( PalmGlitch != 0 ) {
			glDeleteTextures( 1, (const GLuint*)&PalmGlitch );
		}
#endif // HACK_TEXTURE5_GLITCH //
		
		Log("GL Allocations: %i  Sum: %i\n", AllocCount, AllocSum );
		
		if ( AllocCount != 0 ) {
			Log("** TEXTUREPOOL EXIT ERROR ** : GL ALLOCATION MISSMATCHED!!\n" );
		}
		
		if ( AllocSum != 0 ) {
			Log("** TEXTUREPOOL EXIT ERROR ** : GL ALLOCATION SUM MISSMATCHED!!\n" );
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	// Free textures so we can reload them in to the new/current OpenGL Context //
	void ReleaseTextures() {
		Exit();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Reload all the previously released textures //
	void ReloadTextures() {
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			LoadTexture( idx );
		}
	}
// - ------------------------------------------------------------------------------------------ - //
#undef TEXTURE_POOL_SLASH
// - ------------------------------------------------------------------------------------------ - //
}; // namespace TexturePool //
// - ------------------------------------------------------------------------------------------ - //
