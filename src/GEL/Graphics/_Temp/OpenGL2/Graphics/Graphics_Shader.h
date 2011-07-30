// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Shader_H__
#define __Graphics_Shader_H__
// - ------------------------------------------------------------------------------------------ - //
extern GLuint CurrentProgram;
// - ------------------------------------------------------------------------------------------ - //
extern GLuint FlatShader_Prog;
extern GLuint FlatShader_Vs;
extern GLuint FlatShader_Fs;

extern GLuint ColorShader_Prog;
extern GLuint ColorShader_Vs;
extern GLuint ColorShader_Fs;

extern GLuint TextureShader_Prog;
extern GLuint TextureShader_Vs;
extern GLuint TextureShader_Fs;

extern GLuint TextureColorShader_Prog;
extern GLuint TextureColorShader_Vs;
extern GLuint TextureColorShader_Fs;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetShader( const GLuint Program ) {
	CurrentProgram = Program;
	glUseProgram(CurrentProgram);
}
// - ------------------------------------------------------------------------------------------ - //
void gelBuildInternalShaders();
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelFlatShaded();
void gelColorShaded();
void gelTextureShaded();
void gelTextureColorShaded();
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelVertexAttribPointer( GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const void* Ptr ) {
/*
	if ( Index == 0 ) {
		glVertexPointer( Size, Type, Stride, Ptr );
	}
*/
	glVertexAttribPointer( Index, Size, Type, Normalized, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelVertexPointer( GLint Size, GLenum Type, GLsizei Stride, const void* Ptr ) {
//	glVertexPointer( Size, Type, Stride, Ptr );
	glVertexAttribPointer( 0, Size, Type, GL_FALSE, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelTexCoordPointer( GLint Size, GLenum Type, GLsizei Stride, const void* Ptr ) {
	//glTexCoordPointer( Size, Type, Stride, Ptr );
	glVertexAttribPointer( 1, Size, Type, GL_FALSE, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelColorPointer( GLint Size, GLenum Type, GLsizei Stride, const void* Ptr ) {
	//gelColorPointer( Size, Type, Stride, Ptr );
	glVertexAttribPointer( 2, Size, Type, GL_FALSE, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Shader_H__ //
// - ------------------------------------------------------------------------------------------ - //
