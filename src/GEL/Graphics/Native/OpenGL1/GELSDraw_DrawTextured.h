// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_Draw_DrawTextured_H__
#define __GEL_Graphics_OpenGL1_Draw_DrawTextured_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_TEXTURED
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawTextured( const int Mode, const VertType* Poly, const GelUV* UV, const size_t PolyCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    glVertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );
	}
	else {
	    glVertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
	}
	glTexCoordPointer(2, GL_UVType, 0, UV);
    glDrawArrays( Mode, 0, PolyCount );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_INDEXED_TEXTURED
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawIndexedTextured( const int Mode, const VertType* Poly, const GelUV* UV, const unsigned short* Index, const size_t IndexCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    glVertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );
	}
	else {
	    glVertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
	}
	glTexCoordPointer(2, GL_UVType, 0, UV);
    glDrawElements( Mode, IndexCount, GL_UNSIGNED_SHORT, (const unsigned short*)Index );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_Draw_DrawTextured_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
