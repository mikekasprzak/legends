// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_Draw_DrawColors_H__
#define __GEL_Graphics_OpenGL1_Draw_DrawColors_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_COLORS
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawColors( const int Mode, const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    glVertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );
		glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(VertType), Colors );
	}
	else {
	    glVertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
		glColorPointer( 4, GL_UNSIGNED_BYTE, 0, Colors );
	}
	glDrawArrays( Mode, 0, PolyCount );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_INDEXED_COLORS
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawIndexedColors( const int Mode, const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    glVertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );
    	glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(VertType), Colors );
	}
	else {
	    glVertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
		glColorPointer( 4, GL_UNSIGNED_BYTE, 0, Colors );
	}
	glDrawElements( Mode, IndexCount, GL_UNSIGNED_SHORT, (const unsigned short*)Index );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_Draw_DrawFlat_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
