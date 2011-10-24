// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Matrix_H__
#define __GEL_Graphics_OpenGL_Matrix_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include <Math/Matrix.h>
#include "GELS_Shader.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
extern Matrix4x4 GELS_ModelViewMatrix;
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL2 //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_LOAD_MATRIX
// - ------------------------------------------------------------------------------------------ - //
inline void gels_LoadMatrix( const Matrix4x4& m ) {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	GELS_ModelViewMatrix = m;
	glUniformMatrix4fv(glGetUniformLocation(GELS_CurrentProgram, "ViewMatrix"), 1, GL_FALSE, (const GLfloat*)GELS_ModelViewMatrix.Array);	
#else // USES_OPENGL2 //
	glLoadMatrixf( (float*)m.Array );
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_MULT_MATRIX
// - ------------------------------------------------------------------------------------------ - //
inline void gels_MultMatrix( const Matrix4x4& m ) {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	GELS_ModelViewMatrix = m * GELS_ModelViewMatrix;
	glUniformMatrix4fv(glGetUniformLocation(GELS_CurrentProgram, "ViewMatrix"), 1, GL_FALSE, (const GLfloat*)GELS_ModelViewMatrix.Array);	
#else // USES_OPENGL2 //
	glMultMatrixf( (float*)m.Array );
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Matrix_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
