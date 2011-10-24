// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_Draw_DrawTexturedColors_H__
#define __GEL_Graphics_OpenGL1_Draw_DrawTexturedColors_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include "GELS_Shader.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_TEXTURED_COLORS
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawTexturedColors( const int Mode, const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    gels_VertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );
		gels_TexCoordPointer(2, GL_UVType, sizeof(VertType), UV);
		gels_ColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(VertType), Colors );
	}
	else {
	    gels_VertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
		gels_TexCoordPointer(2, GL_UVType, 0, UV);
		gels_ColorPointer( 4, GL_UNSIGNED_BYTE, 0, Colors );
	}
	glDrawArrays( Mode, 0, PolyCount );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_INDEXED_TEXTURED_COLORS
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawIndexedTexturedColors( const int Mode, const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    gels_VertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );
		gels_TexCoordPointer(2, GL_UVType, sizeof(VertType), UV);
		gels_ColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(VertType), Colors );
	}
	else {
	    gels_VertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
		gels_TexCoordPointer(2, GL_UVType, 0, UV);
		gels_ColorPointer( 4, GL_UNSIGNED_BYTE, 0, Colors );
	}
	glDrawElements( Mode, IndexCount, GL_UNSIGNED_SHORT, (const unsigned short*)Index );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_Draw_DrawTexturedColors_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
