// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_GelFont_H__
#define __GEL_Graphics_GelFont_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelUV.h>
#include <Graphics/BMFont/BMFont.h>
// - ------------------------------------------------------------------------------------------ - //
#include <AssetPool/AssetPool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
struct GelFont {
	BMFont* Font;
	std::vector< GelAssetHandle > Texture;
	
public:
	GelFont( const char* InFile ) :
		Font( new_read_BMFont( InFile ) )
	{
		for ( size_t idx = 0; idx < Font->PageName->Size; idx++ ) {
			Texture.push_back( AssetPool::Load( Font->PageName->Data[idx] ) );
		}
	}
	
	enum {
		GEL_FONT_LEFT = 	0x1 << 0,
		GEL_FONT_HCENTER =	0x2 << 0,
		GEL_FONT_RIGHT = 	0x3 << 0,
		
		GEL_FONT_TOP =	 	0x1 << 2,
		GEL_FONT_VCENTER =	0x2 << 2,
		GEL_FONT_BOTTOM = 	0x3 << 2,

		GEL_FONT_CENTER = GEL_FONT_HCENTER | GEL_FONT_VCENTER
	};
	
	void DrawText( const char* Text, const Vector3D Pos, const int Align = GEL_FONT_CENTER ) {
		
	}
	
	inline void DrawText( const char* Text, const Vector2D Pos, const int Align = GEL_FONT_CENTER ) {
		DrawText( Text, Pos.ToVector3D(), Align );
	}
	
	~GelFont() {
		delete_BMFont( Font );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_GelFont_H__ //
// - ------------------------------------------------------------------------------------------ - //
