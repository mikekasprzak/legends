// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_API_OPENGL2_H__
#define __GEL_API_OPENGL2_H__
// - ------------------------------------------------------------------------------------------ - //
#include <External/GLEE/GLee.h>

#ifdef _WIN32
	// Hide some Warnings on Windows //
	#undef GL_LINES_ADJACENCY_EXT
	#undef GL_LINE_STRIP_ADJACENCY_EXT
	#undef GL_TRIANGLES_ADJACENCY_EXT
	#undef GL_TRIANGLE_STRIP_ADJACENCY_EXT
#endif // _WIN32

#include <gl/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_API_OPENGL2_H__ //
// - ------------------------------------------------------------------------------------------ - //
