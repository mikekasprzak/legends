// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_SHADER_UBERSHADER_OPENGL_BINDUNIFORM_H__
#define __GEL2_SHADER_UBERSHADER_OPENGL_BINDUNIFORM_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform1i( const char* Name, const int v0 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform1i( Location, v0 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform2i( const char* Name, const int v0, const int v1 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform2i( Location, v0, v1 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform3i( const char* Name, const int v0, const int v1, const int v2 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform3i( Location, v0, v1, v2 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform4i( const char* Name, const int v0, const int v1, const int v2, const int v3 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform4i( Location, v0, v1, v2, v3 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform1f( const char* Name, const float v0 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform1f( Location, v0 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform2f( const char* Name, const float v0, const float v1 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform2f( Location, v0, v1 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform3f( const char* Name, const float v0, const float v1, const float v2 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform3f( Location, v0, v1, v2 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform4f( const char* Name, const float v0, const float v1, const float v2, const float v3 ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform4f( Location, v0, v1, v2, v3 );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform1iv( const char* Name, const int* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform1iv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform2iv( const char* Name, const int* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform2iv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform3iv( const char* Name, const int* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform3iv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform4iv( const char* Name, const int* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform4iv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform1fv( const char* Name, const float* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform1fv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform2fv( const char* Name, const float* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform2fv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform3fv( const char* Name, const float* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform3fv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniform4fv( const char* Name, const float* v, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniform4fv( Location, Count, v );
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformMatrix2x2( const char* Name, const Matrix2x2& Matrix ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniformMatrix2fv( Location, 1, GL_FALSE, (const float*)&Matrix );	
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformMatrix3x3( const char* Name, const Matrix3x3& Matrix ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniformMatrix3fv( Location, 1, GL_FALSE, (const float*)&Matrix );	
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformMatrix4x4( const char* Name, const Matrix4x4& Matrix ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniformMatrix4fv( Location, 1, GL_FALSE, (const float*)&Matrix );	
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformMatrix2fv( const char* Name, const float* Matrix, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniformMatrix2fv( Location, Count, GL_FALSE, Matrix );	
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformMatrix3fv( const char* Name, const float* Matrix, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniformMatrix3fv( Location, Count, GL_FALSE, Matrix );	
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformMatrix4fv( const char* Name, const float* Matrix, const size_t Count ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 )
		glUniformMatrix4fv( Location, Count, GL_FALSE, Matrix );	
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformColor( const char* Name, const GelColor Color ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 ) {
		glUniform4f( Location, 
			((float)GEL_GET_R(Color))*(1.0f/255.0f),
			((float)GEL_GET_G(Color))*(1.0f/255.0f),
			((float)GEL_GET_B(Color))*(1.0f/255.0f),
			((float)GEL_GET_A(Color))*(1.0f/255.0f)
			);
	}
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
int cUberShader::BindUniformSColor( const char* Name, const GelSColor Color ) {
	GLint Location = glGetUniformLocation( CurrentShader->Program, Name );
	if ( Location != -1 ) {
		glUniform4f( Location, 
			((float)GEL_SGET_R(Color))*(1.0f/255.0f),
			((float)GEL_SGET_G(Color))*(1.0f/255.0f),
			((float)GEL_SGET_B(Color))*(1.0f/255.0f),
			((float)GEL_SGET_A(Color))*(1.0f/255.0f)
			);
	}
	return Location;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_SHADER_UBERSHADER_OPENGL_BINDUNIFORM_H__ //
// - ------------------------------------------------------------------------------------------ - //
