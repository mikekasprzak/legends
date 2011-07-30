// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_TexturePool_H__
#define __GLGraphics_TexturePool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TextureID.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#include <string>
#include <Util/String/String.h>
#include <Debug/Log.h>
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
namespace TexturePool {
	void Init( const char* BaseDirectory );
	void Exit();
	void AddDirectory( const char* Directory );
	
	TextureID FindID( const char* FileName );
	
	TextureID Load( const char* FileName );
	void Set( const TextureID Texture );
	void Free( const TextureID Texture );

	void ReleaseTextures();
	void ReloadTextures();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline TextureID gelLoadTexture( const char* FileName ) {
	// TODO: Remove file extensions from the search string //
#ifdef _MSC_VER
	std::string Temp = String::WindowsSlash( std::string(FileName) );
	VLog( "Loading %s...\n", Temp.c_str() );
	return TexturePool::Load( Temp.c_str() );
#else // _MSC_VER //
	return TexturePool::Load( FileName );
#endif // _MSC_VER //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetTexture( const TextureID Texture ) {
	TexturePool::Set( Texture );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelFreeTexture( const TextureID Texture ) {
	TexturePool::Free( Texture );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_TexturePool_H__ //
// - ------------------------------------------------------------------------------------------ - //
