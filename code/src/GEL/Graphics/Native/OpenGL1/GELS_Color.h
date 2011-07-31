// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_Color_H__
#define __GEL_Graphics_OpenGL1_Color_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include <Graphics/Color.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_APPLY_COLOR
// - ------------------------------------------------------------------------------------------ - //
inline void gels_ApplyColor( const ColorType Color ) {
	glColor4ub( GET_R(Color), GET_G(Color), GET_B(Color), GET_A(Color) );	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_Color_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //