// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Constants_H__
#define __Graphics_Constants_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Stencil Test and Depth Test Function Modes //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_NEVER				GL_NEVER
#define GEL_LESS				GL_LESS
#define GEL_LESSEQUAL			GL_LEQUAL
#define GEL_GREATER				GL_GREATER
#define GEL_GREATEREQUAL		GL_GEQUAL
#define GEL_EQUAL				GL_EQUAL
#define GEL_NOTEQUAL			GL_NOTEQUAL
#define GEL_ALWAYS				GL_ALWAYS
// - ------------------------------------------------------------------------------------------ - //
// Stencil Operations //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_KEEP				GL_KEEP
#define GEL_ZERO				GL_ZERO
#define GEL_REPLACE				GL_REPLACE
#define GEL_INVERT				GL_INVERT
#define GEL_INCR				GL_INCR			// Saturate //
#define GEL_DECR				GL_DECR			// Saturate //
#define GEL_INCRWRAP			GL_INCR_WRAP	// GL 1.4+, ES 2.0 and DX Only //
#define GEL_DECRWRAP			GL_DECR_WRAP	// GL 1.4+, ES 2.0 and DX Only //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Constants_H__ //
// - ------------------------------------------------------------------------------------------ - //
