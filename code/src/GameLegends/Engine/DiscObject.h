// - ------------------------------------------------------------------------------------------ - //
#ifndef __DiscObject_H__
#define __DiscObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <AssetPool/AssetPool.h>
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
class cDiscObject {
public:
	GelAssetHandle	Texture;
	GelColor		Color;

	GelAssetHandle	OverlayTexture;
	GelColor		OverlayColor;
	
	GelAssetHandle	GlowTexture;
	GelColor		GlowColor;

	
public:
	cDiscObject( GelAssetHandle _Texture, GelColor _Color = GEL_RGB_WHITE ) :
		Texture( _Texture ),
		Color( _Color ),
		OverlayTexture( 0 ),
		OverlayColor( GEL_RGB_WHITE ),
		GlowTexture( _Texture ),
		GlowColor( _Color )
	{	
	}
	
	cDiscObject( const char* InFile ) :
		Texture( 0 ),
		Color( GEL_RGB_WHITE ),
		OverlayTexture( 0 ),
		OverlayColor( GEL_RGB_WHITE ),
		GlowTexture( 0 ),
		GlowColor( GEL_RGB_WHITE )
	{
		LoadFile( InFile );
	}
	
	void LoadFile( const char* InFile );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __DiscObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
