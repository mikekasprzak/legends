// - ------------------------------------------------------------------------------------------ - //
// SUPPORT.H contains functions ONLY used by library code. It should not be used by game code. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Support_H__
#define __Graphics_Support_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Color.h>
#include <Graphics/Graphics_Shader.h>
#include <Graphics/Graphics_Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
inline void gelsApplyColor( const ColorType Color ) {
//	glColor4ub( GET_R(Color), GET_G(Color), GET_B(Color), GET_A(Color) );	
	glUniform4f(glGetUniformLocation(CurrentProgram, "GlobalColor"), 
		((float)GET_R(Color))/255.0f,
		((float)GET_G(Color))/255.0f,
		((float)GET_B(Color))/255.0f,
		((float)GET_A(Color))/255.0f
		);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelsApplyMatrix() {
	glUniformMatrix4fv(glGetUniformLocation(CurrentProgram, "ViewMatrix"), 1, GL_FALSE, (const GLfloat*)ModelViewMatrix.Array);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelsCrop( const int x, const int y, const int w, const int h ) {
	glScissor( x, y, w, h );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Support_H__ //
// - ------------------------------------------------------------------------------------------ - //
