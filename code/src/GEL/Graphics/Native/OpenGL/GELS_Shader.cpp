// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics.h>
#include "EmbeddedShaders/EmbeddedShaders.h"
// - ------------------------------------------------------------------------------------------ - //
GLuint GELS_CurrentProgram;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GLuint GELS_FlatShader_Prog;
GLuint GELS_FlatShader_Vs;
GLuint GELS_FlatShader_Fs;

GLuint GELS_ColorShader_Prog;
GLuint GELS_ColorShader_Vs;
GLuint GELS_ColorShader_Fs;

GLuint GELS_TextureShader_Prog;
GLuint GELS_TextureShader_Vs;
GLuint GELS_TextureShader_Fs;

GLuint GELS_TextureColorShader_Prog;
GLuint GELS_TextureColorShader_Vs;
GLuint GELS_TextureColorShader_Fs;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gels_FlatShaded() {
	gels_SetShader( GELS_FlatShader_Prog );
//	gels_ApplyMatrix();
//	gels_ApplyColor( Current::Color );
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //
void gels_ColorShaded() {
	gels_SetShader( GELS_ColorShader_Prog );
//	gelsApplyMatrix();	
//	gelsApplyColor( Current::Color );
	glDisableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //
void gels_TextureShaded() {
	gels_SetShader( GELS_TextureShader_Prog );
//	gelsApplyMatrix();
//	gelsApplyColor( Current::Color );
	glEnableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //
void gels_TextureColorShaded() {
	gels_SetShader( GELS_TextureColorShader_Prog );
//	gelsApplyMatrix();	
//	gelsApplyColor( Current::Color );
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //
void gels_NullShaded() {
//	gels_SetShader( GELS_FlatShader_Prog );

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GLuint gels_CompileShader( const char* ShaderSrc, GLenum type ) {
	GLuint Shader;
	GLint Compiled;
	
	Shader = glCreateShader( type );
	if ( Shader == 0 )
		return 0;
	
	glShaderSource( Shader, 1, &ShaderSrc, NULL );
	glCompileShader( Shader );
	
	glGetShaderiv( Shader, GL_COMPILE_STATUS, &Compiled );
	
	if ( !Compiled ) {
		GLint InfoLen = 0;
		glGetShaderiv( Shader, GL_INFO_LOG_LENGTH, &InfoLen );
		
		if ( InfoLen > 0 ) {
			char* InfoLog = new char[InfoLen];
			
			glGetShaderInfoLog( Shader, InfoLen, NULL, InfoLog );
			Log( "* Error Compiling Shader:\n%s\n", InfoLog );
			
			delete [] InfoLog;
		}
		
		glDeleteShader( Shader );
		return 0;
	}
	
	return Shader;
}
// - ------------------------------------------------------------------------------------------ - //
void gels_BuildInternalShaders() {
	// - --------------------------------------------------------------------------------------- - //

	Log( "+ Compiling and Linking Embeded Shaders..." );
	
	// - --------------------------------------------------------------------------------------- - //

	// Link Flat Shader for Use! //
	VLog( "* FlatShader\n" );
#ifdef USES_BINARY_SHADERS
	GELS_FlatShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	GELS_FlatShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &GELS_FlatShader_Vs, (GLenum)0, FlatShaderGlvs, sizeof(int)*FlatShaderGlvsLength);
	glShaderBinary(1, &GELS_FlatShader_Fs, (GLenum)0, FlatShaderGlfs, sizeof(int)*FlatShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	GELS_FlatShader_Vs = gels_CompileShader( vsFlatShader, GL_VERTEX_SHADER );
	GELS_FlatShader_Fs = gels_CompileShader( fsFlatShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	GELS_FlatShader_Prog = glCreateProgram();

	glAttachShader(GELS_FlatShader_Prog, GELS_FlatShader_Fs);
	glAttachShader(GELS_FlatShader_Prog, GELS_FlatShader_Vs);


	glBindAttribLocation(GELS_FlatShader_Prog, 0, "VertexPos");

	glLinkProgram(GELS_FlatShader_Prog);
	glUseProgram(GELS_FlatShader_Prog);

	// - --------------------------------------------------------------------------------------- - //

	// Link Color Shader for Use! //
	VLog( "* ColorShader\n" );
#ifdef USES_BINARY_SHADERS
	GELS_ColorShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	GELS_ColorShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &GELS_ColorShader_Vs, (GLenum)0, ColorShaderGlvs, sizeof(int)*ColorShaderGlvsLength);
	glShaderBinary(1, &GELS_ColorShader_Fs, (GLenum)0, ColorShaderGlfs, sizeof(int)*ColorShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	GELS_ColorShader_Vs = gels_CompileShader( vsColorShader, GL_VERTEX_SHADER );
	GELS_ColorShader_Fs = gels_CompileShader( fsColorShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	GELS_ColorShader_Prog = glCreateProgram();

	glAttachShader(GELS_ColorShader_Prog, GELS_ColorShader_Fs);
	glAttachShader(GELS_ColorShader_Prog, GELS_ColorShader_Vs);


	glBindAttribLocation(GELS_ColorShader_Prog, 0, "VertexPos");
	glBindAttribLocation(GELS_ColorShader_Prog, 2, "VertexColor");

	glLinkProgram(GELS_ColorShader_Prog);
	glUseProgram(GELS_ColorShader_Prog);

	// - --------------------------------------------------------------------------------------- - //

	// Link Texture Shader for Use! //
	VLog( "* TextureShader\n" );
#ifdef USES_BINARY_SHADERS
	GELS_TextureShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	GELS_TextureShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &GELS_TextureShader_Vs, (GLenum)0, TextureShaderGlvs, sizeof(int)*TextureShaderGlvsLength);
	glShaderBinary(1, &GELS_TextureShader_Fs, (GLenum)0, TextureShaderGlfs, sizeof(int)*TextureShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	GELS_TextureShader_Vs = gels_CompileShader( vsTextureShader, GL_VERTEX_SHADER );
	GELS_TextureShader_Fs = gels_CompileShader( fsTextureShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	GELS_TextureShader_Prog = glCreateProgram();

	glAttachShader(GELS_TextureShader_Prog, GELS_TextureShader_Fs);
	glAttachShader(GELS_TextureShader_Prog, GELS_TextureShader_Vs);


	glBindAttribLocation(GELS_TextureShader_Prog, 0, "VertexPos");
	glBindAttribLocation(GELS_TextureShader_Prog, 1, "TexCoord");

	glLinkProgram(GELS_TextureShader_Prog);
	glUseProgram(GELS_TextureShader_Prog);

	// - --------------------------------------------------------------------------------------- - //

	// Link TextureColor Shader for Use! //
	VLog( "* TextureColorShader\n" );
#ifdef USES_BINARY_SHADERS
	GELS_TextureColorShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	GELS_TextureColorShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &GELS_TextureColorShader_Vs, (GLenum)0, TextureColorShaderGlvs, sizeof(int)*TextureColorShaderGlvsLength);
	glShaderBinary(1, &GELS_TextureColorShader_Fs, (GLenum)0, TextureColorShaderGlfs, sizeof(int)*TextureColorShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	GELS_TextureColorShader_Vs = gels_CompileShader( vsTextureColorShader, GL_VERTEX_SHADER );
	GELS_TextureColorShader_Fs = gels_CompileShader( fsTextureColorShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	GELS_TextureColorShader_Prog = glCreateProgram();

	glAttachShader(GELS_TextureColorShader_Prog, GELS_TextureColorShader_Fs);
	glAttachShader(GELS_TextureColorShader_Prog, GELS_TextureColorShader_Vs);


	glBindAttribLocation(GELS_TextureColorShader_Prog, 0, "VertexPos");
	glBindAttribLocation(GELS_TextureColorShader_Prog, 1, "TexCoord");
	glBindAttribLocation(GELS_TextureColorShader_Prog, 2, "VertexColor");

	glLinkProgram(GELS_TextureColorShader_Prog);
	glUseProgram(GELS_TextureColorShader_Prog);	

	// - --------------------------------------------------------------------------------------- - //
	Log("- Finished Compiling and Linking Embedded Shaders.");
	// - --------------------------------------------------------------------------------------- - //
}
// - ------------------------------------------------------------------------------------------ - //
void gels_FreeInternalShaders() {
	glDeleteProgram( GELS_FlatShader_Prog );
	glDeleteShader( GELS_FlatShader_Vs );
	glDeleteShader( GELS_FlatShader_Fs );

	glDeleteProgram( GELS_ColorShader_Prog );
	glDeleteShader( GELS_ColorShader_Vs );
	glDeleteShader( GELS_ColorShader_Fs );

	glDeleteProgram( GELS_TextureShader_Prog );
	glDeleteShader( GELS_TextureShader_Vs );
	glDeleteShader( GELS_TextureShader_Fs );

	glDeleteProgram( GELS_TextureColorShader_Prog );
	glDeleteShader( GELS_TextureColorShader_Vs );
	glDeleteShader( GELS_TextureColorShader_Fs );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL2 //
// - ------------------------------------------------------------------------------------------ - //
