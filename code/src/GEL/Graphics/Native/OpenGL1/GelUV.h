// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_GELUV_H__
#define __GEL_Graphics_OpenGL_GELUV_H__
// - ------------------------------------------------------------------------------------------ - //
// Our UV's are Signed Short's. The numeric range allows for +/- 32 repeats (beyond 0-1) //
// - ------------------------------------------------------------------------------------------ - //
typedef short				GelUV;
#define GL_UVType 			GL_SHORT
// - ------------------------------------------------------------------------------------------ - //
#define GEL_UV_SHIFT		10
#define GEL_UV_ONE			1024
#define GEL_UV_ZERO			0
// - ------------------------------------------------------------------------------------------ - //
#define GEL_UV_ONE_F		1024.0f
#define GEL_UV_ZERO_F		0.0f
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_GELUV_H__ //
// - ------------------------------------------------------------------------------------------ - //
