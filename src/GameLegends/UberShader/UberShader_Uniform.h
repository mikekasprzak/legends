// - ------------------------------------------------------------------------------------------ - //
#ifndef __LEGENDS_UBERSHADER_UBERSHADER_UNIFORM_H__
#define __LEGENDS_UBERSHADER_UBERSHADER_UNIFORM_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformi( const char* Name, const int v0 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform1i( Location, v0 );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformi( const char* Name, const int v0, const int v1 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform2i( Location, v0, v1 );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformi( const char* Name, const int v0, const int v1, const int v2 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform3i( Location, v0, v1, v2 );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformi( const char* Name, const int v0, const int v1, const int v2, const int v3 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform4i( Location, v0, v1, v2, v3 );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformf( const char* Name, const float v0 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform1f( Location, v0 );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformf( const char* Name, const float v0, const float v1 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform2f( Location, v0, v1 );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformf( const char* Name, const float v0, const float v1, const float v2 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform3f( Location, v0, v1, v2 );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::BindUniformf( const char* Name, const float v0, const float v1, const float v2, const float v3 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform4f( Location, v0, v1, v2, v3 );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_UBERSHADER_UBERSHADER_UNIFORM_H__ //
// - ------------------------------------------------------------------------------------------ - //
