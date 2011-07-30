// - ------------------------------------------------------------------------------------------ - //
#include "Graphics.h"
#include "Shaders/Shaders.h"
// - ------------------------------------------------------------------------------------------ - //
GLuint CurrentProgram;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GLuint FlatShader_Prog;
GLuint FlatShader_Vs;
GLuint FlatShader_Fs;

GLuint ColorShader_Prog;
GLuint ColorShader_Vs;
GLuint ColorShader_Fs;

GLuint TextureShader_Prog;
GLuint TextureShader_Vs;
GLuint TextureShader_Fs;

GLuint TextureColorShader_Prog;
GLuint TextureColorShader_Vs;
GLuint TextureColorShader_Fs;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelFlatShaded() {
	gelSetShader( FlatShader_Prog );
	gelsApplyMatrix();
	gelsApplyColor( Current::Color );
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //
void gelColorShaded() {
	gelSetShader( ColorShader_Prog );
	gelsApplyMatrix();	
	gelsApplyColor( Current::Color );
	glDisableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //
void gelTextureShaded() {
	gelSetShader( TextureShader_Prog );
	gelsApplyMatrix();	
	gelsApplyColor( Current::Color );
	glEnableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //
void gelTextureColorShaded() {
	gelSetShader( TextureColorShader_Prog );
	gelsApplyMatrix();	
	gelsApplyColor( Current::Color );
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GLuint gelsCompileShader( const char* ShaderSrc, GLenum type ) {
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
void gelBuildInternalShaders() {
	// - --------------------------------------------------------------------------------------- - //

	Log( "Compiling and Linking Shaders...\n" );
	
	// - --------------------------------------------------------------------------------------- - //

	// Link Flat Shader for Use! //
	Log( "- FlatShader\n" );
#ifdef USES_BINARY_SHADERS
	FlatShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	FlatShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &FlatShader_Vs, (GLenum)0, FlatShaderGlvs, sizeof(int)*FlatShaderGlvsLength);
	glShaderBinary(1, &FlatShader_Fs, (GLenum)0, FlatShaderGlfs, sizeof(int)*FlatShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	FlatShader_Vs = gelsCompileShader( vsFlatShader, GL_VERTEX_SHADER );
	FlatShader_Fs = gelsCompileShader( fsFlatShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	FlatShader_Prog = glCreateProgram();

	glAttachShader(FlatShader_Prog, FlatShader_Fs);
	glAttachShader(FlatShader_Prog, FlatShader_Vs);


	glBindAttribLocation(FlatShader_Prog, 0, "VertexPos");

	glLinkProgram(FlatShader_Prog);
	glUseProgram(FlatShader_Prog);

	// - --------------------------------------------------------------------------------------- - //

	// Link Color Shader for Use! //
	Log( "- ColorShader\n" );
#ifdef USES_BINARY_SHADERS
	ColorShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	ColorShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &ColorShader_Vs, (GLenum)0, ColorShaderGlvs, sizeof(int)*ColorShaderGlvsLength);
	glShaderBinary(1, &ColorShader_Fs, (GLenum)0, ColorShaderGlfs, sizeof(int)*ColorShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	ColorShader_Vs = gelsCompileShader( vsColorShader, GL_VERTEX_SHADER );
	ColorShader_Fs = gelsCompileShader( fsColorShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	ColorShader_Prog = glCreateProgram();

	glAttachShader(ColorShader_Prog, ColorShader_Fs);
	glAttachShader(ColorShader_Prog, ColorShader_Vs);


	glBindAttribLocation(ColorShader_Prog, 0, "VertexPos");
	glBindAttribLocation(ColorShader_Prog, 2, "VertexColor");

	glLinkProgram(ColorShader_Prog);
	glUseProgram(ColorShader_Prog);

	// - --------------------------------------------------------------------------------------- - //

	// Link Texture Shader for Use! //
	Log( "- TextureShader\n" );
#ifdef USES_BINARY_SHADERS
	TextureShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	TextureShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &TextureShader_Vs, (GLenum)0, TextureShaderGlvs, sizeof(int)*TextureShaderGlvsLength);
	glShaderBinary(1, &TextureShader_Fs, (GLenum)0, TextureShaderGlfs, sizeof(int)*TextureShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	TextureShader_Vs = gelsCompileShader( vsTextureShader, GL_VERTEX_SHADER );
	TextureShader_Fs = gelsCompileShader( fsTextureShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	TextureShader_Prog = glCreateProgram();

	glAttachShader(TextureShader_Prog, TextureShader_Fs);
	glAttachShader(TextureShader_Prog, TextureShader_Vs);


	glBindAttribLocation(TextureShader_Prog, 0, "VertexPos");
	glBindAttribLocation(TextureShader_Prog, 1, "TexCoord");

	glLinkProgram(TextureShader_Prog);
	glUseProgram(TextureShader_Prog);

	// - --------------------------------------------------------------------------------------- - //

	// Link TextureColor Shader for Use! //
	Log( "- TextureColorShader\n" );
#ifdef USES_BINARY_SHADERS
	TextureColorShader_Vs = glCreateShader(GL_VERTEX_SHADER);
	TextureColorShader_Fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderBinary(1, &TextureColorShader_Vs, (GLenum)0, TextureColorShaderGlvs, sizeof(int)*TextureColorShaderGlvsLength);
	glShaderBinary(1, &TextureColorShader_Fs, (GLenum)0, TextureColorShaderGlfs, sizeof(int)*TextureColorShaderGlfsLength);
#else // USES_BINARY_SHADERS //
	TextureColorShader_Vs = gelsCompileShader( vsTextureColorShader, GL_VERTEX_SHADER );
	TextureColorShader_Fs = gelsCompileShader( fsTextureColorShader, GL_FRAGMENT_SHADER );
#endif // USES_BINARY_SHADERS //

	TextureColorShader_Prog = glCreateProgram();

	glAttachShader(TextureColorShader_Prog, TextureColorShader_Fs);
	glAttachShader(TextureColorShader_Prog, TextureColorShader_Vs);


	glBindAttribLocation(TextureColorShader_Prog, 0, "VertexPos");
	glBindAttribLocation(TextureColorShader_Prog, 1, "TexCoord");
	glBindAttribLocation(ColorShader_Prog, 2, "VertexColor");

	glLinkProgram(TextureColorShader_Prog);
	glUseProgram(TextureColorShader_Prog);	

	// - --------------------------------------------------------------------------------------- - //
}
// - ------------------------------------------------------------------------------------------ - //

