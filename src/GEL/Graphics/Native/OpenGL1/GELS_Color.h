// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_Color_H__
#define __GEL_Graphics_OpenGL1_Color_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_APPLY_COLOR
// - ------------------------------------------------------------------------------------------ - //
inline void gels_ApplyColor( const GelColor Color ) {
	glColor4ub( GEL_GET_R(Color), GEL_GET_G(Color), GEL_GET_B(Color), GEL_GET_A(Color) );	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_Color_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //