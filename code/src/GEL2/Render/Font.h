// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_RENDER_FONT_H__
#define __GEL2_RENDER_FONT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Font_BMFont.h"
// - ------------------------------------------------------------------------------------------ - //
#include "UV.h"
#include <Texture/Texture.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Allocator/Allocator.h>
#include <Graphics/Allocator/Vector3DAllocator.h>
#include <Graphics/Allocator/UVAllocator.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <stdio.h>
#include <stdarg.h>

#include <Util/String/String.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
class cFont {
public:
	BMFont* Font;
	std::vector< Texture::TextureHandle > TexturePage;
	
public:
	cFont( const char* InFile ) :
		Font( new_read_BMFont( InFile ) )
	{
		for ( size_t idx = 0; idx < Font->PageName->Size; idx++ ) {
			const char* File = Search::Search( Font->PageName->Data[idx] );			
			DataBlock* Data = new_read_DataBlock( File );
			Texture::STBTexture Tex = Texture::new_STBTexture( Data->Data, Data->Size );
			delete_DataBlock( Data );

			// HACK: Don't Flip. Need to sort out the flip order in my brain //
			TexturePage.push_back( Texture::upload_STBTexture( Tex, false, false ) );
				
			Texture::delete_STBTexture( Tex );
		}
	}
	
	~cFont() {
		for ( size_t idx = 0; idx < Font->PageName->Size; idx++ ) {
			Texture::delete_TextureHandle( TexturePage[idx] );
		}		
		delete_BMFont( Font );
	}
	
	void DrawText( const char* Text, const size_t Length, Vector3D Pos, Real Scalar = Real::One, const int Align = GEL_ALIGN_DEFAULT ) {
		size_t CharsDrawn = 0;
		
		int ScaleW = common_BMFont( Font )->ScaleW;
		int ScaleH = common_BMFont( Font )->ScaleH;
		// Reciprocals //
		float ScaleW_R_F = 1.0f / (float)ScaleW; 
		float ScaleH_R_F = 1.0f / (float)ScaleH;

		Scalar *= (float)size_BMFont( Font );

		int Width = width_BMFont( Font, Text, Length );
		int Height = height_BMFont( Font, Text, Length );
		int BaseLine = baseline_BMFont( Font );
		BMFont_Chars** Glyph = glyph_BMFont( Font );
				
		// Alignment //
		if ( (Align & GEL_ALIGN_FONT_HBITS) == GEL_ALIGN_CENTER ) {
			Pos.x -= (Width>>1) * Scalar * ScaleW_R_F;
		}
		else if ( (Align & GEL_ALIGN_FONT_HBITS) == GEL_ALIGN_RIGHT ) {
			Pos.x -= Width * Scalar * ScaleW_R_F;
		}
		
		if ( (Align & GEL_ALIGN_FONT_VBITS) == GEL_ALIGN_MIDDLE ) {
			Pos.y -= (Height>>1) * Scalar * ScaleH_R_F;
		}
		else if ( (Align & GEL_ALIGN_FONT_VBITS) == GEL_ALIGN_TOP ) {
			Pos.y -= Height * Scalar * ScaleH_R_F;
		}
		else if ( (Align & GEL_ALIGN_FONT_VBITS) == GEL_ALIGN_BASELINE ) {
			Pos.y -= BaseLine * Scalar * ScaleH_R_F;
		}

		Vector3DAllocator Vert( Length * 6 );
		UVAllocator UV( Length * 6 );

		// Assume Matrix and texture mode are set correctly outside this function //
		for ( size_t Tex = 0; Tex < TexturePage.size(); Tex++ ) {
			Vert.Clear();
			UV.Clear();
			
			Vector3D CurPos = Pos;
			
			// Draw Text //
			for ( size_t idx = 0; idx < Length; idx++ ) {
				// NOTE: ASCII+EXT ONLY //
				int Ch = Text[idx] & 0xff;
				
				// If I'm on the correct texture page, draw the glyph //
				if ( (unsigned)Glyph[Ch]->Page == Tex ) {
					// NOTE: I now subtract the positions from the height, since we are creating coords that start from bottom left //
					Vector2D V1( Glyph[Ch]->OffsetX * ScaleW_R_F, (Height - Glyph[Ch]->OffsetY) * ScaleH_R_F );
					Vector2D V2( (Glyph[Ch]->OffsetX + Glyph[Ch]->Width) * ScaleW_R_F, (Height - (Glyph[Ch]->OffsetY + Glyph[Ch]->Height)) * ScaleH_R_F );
					V1 *= Scalar;
					V2 *= Scalar;

					// NOTE: FORMER HACK: I (used to) CHANGED THE Y's AROUND! I DUNNO WHY THEY WERE UPSIDE DOWN! //
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
				
				CurPos.x += Glyph[Ch]->AdvanceX * Scalar * ScaleW_R_F;
			}

			// Draw! //
//			gelDrawTrianglesTextured(
//				(const Vector3D*)Vert.Get(),
//				(GelUV*)UV.Get(),
//				Vert.Size()
//				);
			
			Shader::Default->Bind( Shader::TextureShader );
			Shader::Default->BindUniformColor( "GlobalColor", GEL_RGB_WHITE );
			Shader::Default->BindUniformMatrix4x4( "ViewMatrix", ViewMatrix );
			Texture::Bind( TexturePage[Tex], 0 );
			Shader::Default->BindUniform1i( "TexImage0", 0 );
			Shader::Default->AttribPointer( 0, 3, GL_FLOAT, false, sizeof(const Vector3D), Vert.Get() );
			Shader::Default->AttribPointer( 1, 2, GL_UVType, false, sizeof(UVType)*2, UV.Get() );
			Shader::Default->DrawArrays( GL_TRIANGLES, Vert.Size() );
			
			if ( Length == CharsDrawn )
				break;
		}
	}
	
	inline void DrawText( const char* Text, const Vector3D& Pos, const Real Scalar = Real::One, const int Align = GEL_ALIGN_DEFAULT ) {
		DrawText( Text, length_String( Text ), Pos, Scalar, Align );
	}
	
	inline void DrawText( const char* Text, const Vector2D& Pos, const Real Scalar = Real::One, const int Align = GEL_ALIGN_DEFAULT ) {
		DrawText( Text, Pos.ToVector3D(), Scalar, Align );
	}
	
	inline void printf( const Vector3D& Pos, const Real Scalar, const int Align, const char* Text, ... ) {
		char StrBuff[2048];
		
		{
			va_list vl;
			va_start( vl, Text );
	
			safe_vsprintf( StrBuff, sizeof(StrBuff), Text, vl );
	
			va_end( vl );
		}

		DrawText( StrBuff, Pos, Scalar, Align );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_RENDER_FONT_H__ //
// - ------------------------------------------------------------------------------------------ - //
