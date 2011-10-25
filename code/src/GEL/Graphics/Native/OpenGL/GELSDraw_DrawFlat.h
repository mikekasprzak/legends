// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_Draw_DrawFlat_H__
#define __GEL_Graphics_OpenGL1_Draw_DrawFlat_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include "GELS_Shader.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_FLAT
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawFlat( const int Mode, const VertType* Poly, const size_t PolyCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    gels_VertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );
	}
	else {
	    gels_VertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
	}
    glDrawArrays( Mode, 0, PolyCount );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_INDEXED_FLAT
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gels_DrawIndexedFlat( const int Mode, const VertType* Poly, const unsigned short* Index, const size_t IndexCount ) {
	if ( sizeof(VertType) / sizeof(Real) > 4 ) {
		// Hack, hardcoded to 3 if greater than 4 //
	    gels_VertexPointer( 3, GL_FLOAT, sizeof(VertType), (const float*)Poly );		
	}
	else {
	    gels_VertexPointer( sizeof(VertType) / sizeof(Real), GL_FLOAT, sizeof(VertType), (const float*)Poly );
	}
    glDrawElements( Mode, IndexCount, GL_UNSIGNED_SHORT, (const unsigned short*)Index );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_Draw_DrawFlat_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
