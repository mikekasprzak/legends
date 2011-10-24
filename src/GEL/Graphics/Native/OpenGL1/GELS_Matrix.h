// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Matrix_H__
#define __GEL_Graphics_OpenGL_Matrix_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_LOAD_MATRIX
// - ------------------------------------------------------------------------------------------ - //
inline void gels_LoadMatrix( const Matrix4x4& m ) {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	glUniformMatrix4fv(glGetUniformLocation(GELS_CurrentProgram, "ViewMatrix"), 1, GL_FALSE, (const GLfloat*)m.Array);	
#else // USES_OPENGL2 //
	glLoadMatrixf( (float*)m.Array );
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_MULT_MATRIX
// - ------------------------------------------------------------------------------------------ - //
inline void gels_MultMatrix( const Matrix4x4& m ) {
	glMultMatrixf( (float*)m.Array );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Matrix_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
