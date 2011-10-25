// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Color_H__
#define __GEL_Graphics_OpenGL_Color_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include <Graphics/GelColor.h>
#include "GELS_Shader.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_APPLY_COLOR
// - ------------------------------------------------------------------------------------------ - //
inline void gels_ApplyColor( const GelColor Color ) {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	// TODO: Change this to something NOT requiring a /255 //
	glUniform4f(glGetUniformLocation(GELS_CurrentProgram, "GlobalColor"), 
		((float)GEL_GET_R(Color))/255.0f,
		((float)GEL_GET_G(Color))/255.0f,
		((float)GEL_GET_B(Color))/255.0f,
		((float)GEL_GET_A(Color))/255.0f
		);
#else // USES_OPENGL2 //
	glColor4ub( GEL_GET_R(Color), GEL_GET_G(Color), GEL_GET_B(Color), GEL_GET_A(Color) );
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Color_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
