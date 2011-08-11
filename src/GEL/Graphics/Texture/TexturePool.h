// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_LEGACY_SMILES
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLGraphics_TexturePool_H__
#define __GLGraphics_TexturePool_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelTextureID.h>
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
	
	GelTextureID FindID( const char* FileName );
	
	GelTextureID Load( const char* FileName );
	void Set( const GelTextureID Texture );
	void Free( const GelTextureID Texture );

	void ReleaseTextures();
	void ReloadTextures();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline GelTextureID gelLoadTexture( const char* FileName ) {
	// TODO: Remove file extensions from the search string //
#ifdef _MSC_VER
	std::string Temp = String::WindowsSlash( std::string(FileName) );
	VVLog( "Loading %s...\n", Temp.c_str() );
	return TexturePool::Load( Temp.c_str() );
#else // _MSC_VER //
	return TexturePool::Load( FileName );
#endif // _MSC_VER //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetTexture( const GelTextureID Texture ) {
	TexturePool::Set( Texture );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelFreeTexture( const GelTextureID Texture ) {
	TexturePool::Free( Texture );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GLGraphics_TexturePool_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // PRODUCT_LEGACY_SMILES //
// - ------------------------------------------------------------------------------------------ - //
