// - ------------------------------------------------------------------------------------------ - //
#ifndef __LEGENDS_UBERSHADER_UBERSHADER_H__
#define __LEGENDS_UBERSHADER_UBERSHADER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
#include <map>

#include <Graphics/API.h>
#include <Graphics/GelColor.h>
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
typedef size_t GelShaderHandle;
// - ------------------------------------------------------------------------------------------ - //
class cUberShader_Shader {
public:
	GLuint Vertex;
	GLuint Fragment;
	GLuint Geometry;

	GLuint Program;

public:		
	cUberShader_Shader() :
		Vertex( 0 ),
		Fragment( 0 ),
		Geometry( 0 ),
		Program( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cUberShader {
public:
	std::string FileName;
	
	std::vector< cUberShader_Shader > Shader;
	std::map< std::string, GelShaderHandle > ShaderLookup;
		
	cUberShader_Shader* CurrentShader;
public:
	cUberShader( const char* InFile );
	~cUberShader();
	
	GelShaderHandle Find( const char* ShaderName );
	void Bind( const GelShaderHandle Index );

public:
	inline void BindUniform1i( const char* Name, const int v0 );
	inline void BindUniform2i( const char* Name, const int v0, const int v1 );
	inline void BindUniform3i( const char* Name, const int v0, const int v1, const int v2 );
	inline void BindUniform4i( const char* Name, const int v0, const int v1, const int v2, const int v3 );

	inline void BindUniform1f( const char* Name, const float v0 );
	inline void BindUniform2f( const char* Name, const float v0, const float v1 );
	inline void BindUniform3f( const char* Name, const float v0, const float v1, const float v2 );
	inline void BindUniform4f( const char* Name, const float v0, const float v1, const float v2, const float v3 );

	inline void BindUniform1iv( const char* Name, const int* v, const size_t Count );
	inline void BindUniform2iv( const char* Name, const int* v, const size_t Count );
	inline void BindUniform3iv( const char* Name, const int* v, const size_t Count );
	inline void BindUniform4iv( const char* Name, const int* v, const size_t Count );

	inline void BindUniform1fv( const char* Name, const float* v, const size_t Count );
	inline void BindUniform2fv( const char* Name, const float* v, const size_t Count );
	inline void BindUniform3fv( const char* Name, const float* v, const size_t Count );
	inline void BindUniform4fv( const char* Name, const float* v, const size_t Count );
	
	inline void BindUniformMatrix2x2( const char* Name, const Matrix2x2& Matrix );
	inline void BindUniformMatrix3x3( const char* Name, const Matrix3x3& Matrix );
	inline void BindUniformMatrix4x4( const char* Name, const Matrix4x4& Matrix );

	inline void BindUniformMatrix2fv( const char* Name, const float* Matrix, const size_t Count );
	inline void BindUniformMatrix3fv( const char* Name, const float* Matrix, const size_t Count );
	inline void BindUniformMatrix4fv( const char* Name, const float* Matrix, const size_t Count );
	
	inline void BindUniformColor( const char* Name, const GelColor Color );
};
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader_Uniform.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_UBERSHADER_UBERSHADER_H__ //
// - ------------------------------------------------------------------------------------------ - //
