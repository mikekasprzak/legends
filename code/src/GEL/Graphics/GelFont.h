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
	
	void DrawText( const char* Text, const size_t Length, Vector3D Pos, const Real Scalar = Real::One, const int Align = GEL_FONT_CENTER ) {
		size_t CharsDrawn = 0;
		int Width = width_BMFont( Font, Text, Length );
		int Height = height_BMFont( Font, Text, Length );
		
		// Alignment //
		if ( Align & GEL_FONT_HCENTER ) {
			Pos.x -= Width>>1;
		}
		else if ( Align & GEL_FONT_RIGHT ) {
			Pos.x -= Width;
		}
		if ( Align & GEL_FONT_VCENTER ) {
			Pos.y -= Height>>1;
		}
		else if ( Align & GEL_FONT_BOTTOM ) {
			Pos.y -= Height;
		}

		// Assume Matrix and texture mode are set correctly outside this function //
		for ( size_t Tex = 0; Tex < Texture.size(); Tex++ ) {
			AssetPool::BindTexture( Texture[Tex] );
			
			// Draw Text // 	
			for ( size_t idx = 0; idx < Length; idx++ ) {
				
			}
			
			if ( Length == CharsDrawn )
				break;
		}		
	}
	
	inline void DrawText( const char* Text, const Vector3D& Pos, const Real Scalar = Real::One, const int Align = GEL_FONT_CENTER ) {
		DrawText( Text, length_String( Text ), Pos, Scalar, Align );
	}
	
	inline void DrawText( const char* Text, const Vector2D& Pos, const Real Scalar = Real::One, const int Align = GEL_FONT_CENTER ) {
		DrawText( Text, Pos.ToVector3D(), Scalar, Align );
	}
	
	~GelFont() {
		delete_BMFont( Font );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_GelFont_H__ //
// - ------------------------------------------------------------------------------------------ - //
