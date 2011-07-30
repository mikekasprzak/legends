// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics.h>
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

	class cTextureInfo {
	public:
		// The different levels of texture usability status //
		unsigned int GLTexture;		// Texture is in VRAM //
//		DataBlock* Uncompressed;	// Uncompressed Data Ready to be Transfered //
//		DataBlock* Compressed;		// Compressed Data is Loaded, ready to be decompressed //
		std::string FileName;		// All we have is a filename //
	
		cTextureDetail Detail;
	public:
		cTextureInfo() :
			GLTexture( 0 )
		{
		}
		cTextureInfo( const char* _FileName ) :
			GLTexture( 0 ),
			FileName( _FileName )
		{
		}
		cTextureInfo( std::string _FileName ) :
			GLTexture( 0 ),
			FileName( _FileName )
		{
		}
		
		void Free() {
			if ( GLTexture ) {
				TexturePool::AllocCount--;
				TexturePool::AllocSum -= GLTexture;

				Log( "* GL Texture %i Free'd\n", GLTexture );
				glDeleteTextures( 1, (const GLuint*)&GLTexture );
				GLTexture = 0;
			}
		}
	};
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Members //
	std::string FilePrefix;	
	std::vector< cTextureInfo > TextureInfo;
	std::map<std::string, TextureID> TextureLookup;
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
			TextureInfo.push_back( cTextureInfo() );	// Dummy //
			
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
			TextureInfo.push_back( cTextureInfo( SlashString ) );
			
			std::string NoExt = NoExtensions( SlashString );
			TextureLookup[ NoExt.c_str() ] = TextureInfo.size() - 1;
			
			Log( "* %s (%i)\n", SlashString.c_str(), idx );
			VLog( "  %s\n", NoExt.c_str() );
		}
		
		delete_GelDirectory( Dir );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	TextureID FindID( const char* FileName ) {
		// Search the map for the specific pattern //
		std::map<std::string, TextureID>::iterator SearchIterator = TextureLookup.find( FileName );
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
	void Set( const TextureID Texture ) {
		glBindTexture( GL_TEXTURE_2D, TextureInfo[ Texture ].GLTexture );
//		if ( Texture != 0 ) {
//			if ( TextureInfo[ Texture ].GLTexture == 0 ) {
//				LoadTexture( Texture );
//			}
//			
//			glBindTexture( GL_TEXTURE_2D, TextureInfo[ Texture ].GLTexture );
//		}
//		else {
//			glBindTexture( GL_TEXTURE_2D, 0 );
//		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void LoadTexture( const TextureID Texture ) {
		// Bail if the dummy texture //
		if ( Texture == 0 )
			return;
		
		// If GL Texture is set, activate it //
		if ( TextureInfo[ Texture ].GLTexture ) {
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

			// TODO: Figure out what kind of image this file is //
			TextureInfo[ Texture ].GLTexture = LoadGL_PVRTexture( File.c_str(), &TextureInfo[ Texture ].Detail );

#ifdef HACK_TEXTURE5_GLITCH
			if ( TextureInfo[ Texture ].GLTexture == 5 ) {
				Log( "** WebOS! ** : Working around 'Texture 5' glitch...\n" );
				PalmGlitch = TextureInfo[ Texture ].GLTexture;				
				TextureInfo[ Texture ].GLTexture = LoadGL_PVRTexture( File.c_str(), &TextureInfo[ Texture ].Detail );
			}
#endif // HACK_TEXTURE5_GLITCH //

			TexturePool::AllocCount++;
			TexturePool::AllocSum += TextureInfo[ Texture ].GLTexture;
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	TextureID Load( const char* FileName ) {
#ifdef USES_SDL
		MessageLoop();
#endif // USES_SDL //

		// Bail if we're in the middle of shutting down //
		if ( System::ShutdownGame || System::CloseButtonPressed ) {
			Log( "* Shutdown Detected!  Aborting Texture Load...\n");
			return 0;
		}

		// Search for ID based on input string //
		TextureID Texture = FindID( FileName );
		
		// Loaded, so cache the texture in memory //
		LoadTexture( Texture );
		
		// Return the Id //
		return Texture;	
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	void Free( const TextureID Texture ) {
		if ( TextureInfo[ Texture ].GLTexture ) {
			TexturePool::AllocCount--;
			TexturePool::AllocSum -= TextureInfo[ Texture ].GLTexture;

			Log( "* GL Texture %i Free'd\n", TextureInfo[ Texture ].GLTexture );
			glDeleteTextures( 1, (const GLuint*)&TextureInfo[ Texture ].GLTexture );
			TextureInfo[ Texture ].GLTexture = 0;
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
