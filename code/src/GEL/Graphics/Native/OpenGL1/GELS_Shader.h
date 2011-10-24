// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Shader_H__
#define __GEL_Graphics_OpenGL_Shader_H__
// - ------------------------------------------------------------------------------------------ - //
extern GLuint GELS_CurrentProgram;
// - ------------------------------------------------------------------------------------------ - //
extern GLuint GELS_FlatShader_Prog;
extern GLuint GELS_FlatShader_Vs;
extern GLuint GELS_FlatShader_Fs;

extern GLuint GELS_ColorShader_Prog;
extern GLuint GELS_ColorShader_Vs;
extern GLuint GELS_ColorShader_Fs;

extern GLuint GELS_TextureShader_Prog;
extern GLuint GELS_TextureShader_Vs;
extern GLuint GELS_TextureShader_Fs;

extern GLuint GELS_TextureColorShader_Prog;
extern GLuint GELS_TextureColorShader_Vs;
extern GLuint GELS_TextureColorShader_Fs;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_SHADER
inline void gels_SetShader( const GLuint Program ) {
	GELS_CurrentProgram = Program;
	glUseProgram(GELS_CurrentProgram);
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_BUILD_INTERNAL_SHADERS
void gels_BuildInternalShaders();
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_FLAT_SHADED
void gels_FlatShaded();
#define GELS_COLOR_SHADED
void gels_ColorShaded();
#define GELS_TEXTURE_SHADED
void gels_TextureShaded();
#define GELS_TEXTURE_COLOR_SHADED
void gels_TextureColorShaded();
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_VERTEX_ATTRIB_POINTER
inline void gels_VertexAttribPointer( GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const void* Ptr ) {
/*
	if ( Index == 0 ) {
		glVertexPointer( Size, Type, Stride, Ptr );
	}
*/
	glVertexAttribPointer( Index, Size, Type, Normalized, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_VERTEX_POINTER
inline void gels_VertexPointer( GLint Size, GLenum Type, GLsizei Stride, const void* Ptr ) {
//	glVertexPointer( Size, Type, Stride, Ptr );
	glVertexAttribPointer( 0, Size, Type, GL_FALSE, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_TEX_COORD_POINTER
inline void gels_TexCoordPointer( GLint Size, GLenum Type, GLsizei Stride, const void* Ptr ) {
	//glTexCoordPointer( Size, Type, Stride, Ptr );
	glVertexAttribPointer( 1, Size, Type, GL_FALSE, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_COLOR_POINTER
inline void gels_ColorPointer( GLint Size, GLenum Type, GLsizei Stride, const void* Ptr ) {
	//gelColorPointer( Size, Type, Stride, Ptr );
	glVertexAttribPointer( 2, Size, Type, GL_FALSE, Stride, Ptr );	
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Shader_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL2 //
// - ------------------------------------------------------------------------------------------ - //
