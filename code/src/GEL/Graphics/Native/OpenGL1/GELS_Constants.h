// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Constants_H__
#define __GEL_Graphics_OpenGL_Constants_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Stencil Test and Depth Test Function Modes //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_NEVER								GL_NEVER
#define GEL_LESS								GL_LESS
#define GEL_LESSEQUAL							GL_LEQUAL
#define GEL_GREATER								GL_GREATER
#define GEL_GREATEREQUAL						GL_GEQUAL
#define GEL_EQUAL								GL_EQUAL
#define GEL_NOTEQUAL							GL_NOTEQUAL
#define GEL_ALWAYS								GL_ALWAYS
// - ------------------------------------------------------------------------------------------ - //
// Stencil Operations //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_KEEP								GL_KEEP
#define GEL_ZERO								GL_ZERO
#define GEL_REPLACE								GL_REPLACE
#define GEL_INVERT								GL_INVERT
#define GEL_INCR								GL_INCR			// Saturate //
#define GEL_DECR								GL_DECR			// Saturate //
#define GEL_INCRWRAP							GL_INCR_WRAP	// GL 1.4+, ES 2.0 and DX Only //
#define GEL_DECRWRAP							GL_DECR_WRAP	// GL 1.4+, ES 2.0 and DX Only //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Render Operations //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_POINTS								GL_POINTS
#define GEL_LINES								GL_LINES
#define GEL_LINE_STRIP							GL_LINE_STRIP
#define GEL_LINE_LOOP							GL_LINE_LOOP
#define GEL_TRIANGLES							GL_TRIANGLES
#define GEL_TRIANGLE_STRIP						GL_TRIANGLE_STRIP
#define GEL_TRIANGLE_FAN						GL_TRIANGLE_FAN
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DrawMode States //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_DRAWMODE_FLAT						0
#define GEL_DRAWMODE_COLORS						1
#define GEL_DRAWMODE_TEXTURED					2
#define GEL_DRAWMODE_TEXTURED_COLORS			3
#define GEL_DRAWMODE_SHADER						16
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Constants_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
