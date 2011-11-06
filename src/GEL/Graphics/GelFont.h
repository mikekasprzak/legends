// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_GelFont_H__
#define __GEL_Graphics_GelFont_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelUV.h>
#include <Graphics/BMFont/BMFont.h>
// - ------------------------------------------------------------------------------------------ - //
#include <AssetPool/AssetPool.h>
#include <Graphics/Allocator/Allocator.h>
#include <Graphics/Allocator/Vector3DAllocator.h>
#include <Graphics/Allocator/UVAllocator.h>
#include <Graphics/GraphicsDraw.h>
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
		
		int ScaleW = common_BMFont( Font )->ScaleW;
		int ScaleH = common_BMFont( Font )->ScaleH;
		float ScaleW_F = 1.0f / (float)ScaleW; 
		float ScaleH_F = 1.0f / (float)ScaleH;

		int Width = width_BMFont( Font, Text, Length );
		int Height = height_BMFont( Font, Text, Length );
		BMFont_Chars** Glyph = glyph_BMFont( Font );
				
		// Alignment //
		if ( Align & GEL_FONT_HCENTER ) {
			Pos.x -= (Width>>1) * Scalar * ScaleW_F;
		}
		else if ( Align & GEL_FONT_RIGHT ) {
			Pos.x -= Width * Scalar * ScaleW_F;
		}
		if ( Align & GEL_FONT_VCENTER ) {
			Pos.y -= (Height>>1) * Scalar * ScaleH_F;
		}
		else if ( Align & GEL_FONT_BOTTOM ) {
			Pos.y -= Height * Scalar * ScaleH_F;
		}

		Vector3DAllocator Vert( Length * 6 );
		UVAllocator UV( Length * 6 );

		// Assume Matrix and texture mode are set correctly outside this function //
		for ( size_t Tex = 0; Tex < Texture.size(); Tex++ ) {
			AssetPool::BindTexture( Texture[Tex] );
				
			Vert.Clear();
			UV.Clear();
			
			Vector3D CurPos = Pos;
			
			// Draw Text //
			for ( size_t idx = 0; idx < Length; idx++ ) {
				int Ch = Text[idx];
				
				// If I'm on the correct texture page, draw the glyph //
				if ( Glyph[Ch]->Page == Tex ) {
					Vector2D V1( Glyph[Ch]->OffsetX * ScaleW_F, Glyph[Ch]->OffsetY * ScaleH_F );
					Vector2D V2( (Glyph[Ch]->OffsetX + Glyph[Ch]->Width) * ScaleW_F, (Glyph[Ch]->OffsetY + Glyph[Ch]->Height) * ScaleH_F );
					V1 *= Scalar;
					V2 *= Scalar;

					int UV1_x = Glyph[Ch]->x * GEL_UV_ONE / ScaleW;
					int UV1_y = Glyph[Ch]->y * GEL_UV_ONE / ScaleH;
					int UV2_x = (Glyph[Ch]->x + Glyph[Ch]->Width) * GEL_UV_ONE / ScaleW;
					int UV2_y = (Glyph[Ch]->y + Glyph[Ch]->Height) * GEL_UV_ONE / ScaleH;
					
					Vert.Add( Vector3D( V1.x, V1.y, 0) + CurPos );
					Vert.Add( Vector3D( V2.x, V1.y, 0) + CurPos );
					Vert.Add( Vector3D( V2.x, V2.y, 0) + CurPos );
					Vert.Add( Vector3D( V2.x, V2.y, 0) + CurPos );
					Vert.Add( Vector3D( V1.x, V2.y, 0) + CurPos );
					Vert.Add( Vector3D( V1.x, V1.y, 0) + CurPos );
					 					
					UV.Add( UVSet<GelUV>( UV1_x, UV1_y ) );
					UV.Add( UVSet<GelUV>( UV2_x, UV1_y ) );
					UV.Add( UVSet<GelUV>( UV2_x, UV2_y ) );
					UV.Add( UVSet<GelUV>( UV2_x, UV2_y ) );
					UV.Add( UVSet<GelUV>( UV1_x, UV2_y ) );
					UV.Add( UVSet<GelUV>( UV1_x, UV1_y ) );
				
					CharsDrawn++;	
				}
				
				CurPos.x += Glyph[Ch]->AdvanceX * Scalar * ScaleW_F;
			}

			// Draw! //
			gelDrawTrianglesTextured(
				(const Vector3D*)Vert.Data,
				(GelUV*)UV.Data,
				Vert.Size()
				);
			
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
