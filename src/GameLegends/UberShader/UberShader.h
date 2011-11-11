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
	inline int BindUniform1i( const char* Name, const int v0 );
	inline int BindUniform2i( const char* Name, const int v0, const int v1 );
	inline int BindUniform3i( const char* Name, const int v0, const int v1, const int v2 );
	inline int BindUniform4i( const char* Name, const int v0, const int v1, const int v2, const int v3 );

	inline int BindUniform1f( const char* Name, const float v0 );
	inline int BindUniform2f( const char* Name, const float v0, const float v1 );
	inline int BindUniform3f( const char* Name, const float v0, const float v1, const float v2 );
	inline int BindUniform4f( const char* Name, const float v0, const float v1, const float v2, const float v3 );

	inline int BindUniform1iv( const char* Name, const int* v, const size_t Count );
	inline int BindUniform2iv( const char* Name, const int* v, const size_t Count );
	inline int BindUniform3iv( const char* Name, const int* v, const size_t Count );
	inline int BindUniform4iv( const char* Name, const int* v, const size_t Count );

	inline int BindUniform1fv( const char* Name, const float* v, const size_t Count );
	inline int BindUniform2fv( const char* Name, const float* v, const size_t Count );
	inline int BindUniform3fv( const char* Name, const float* v, const size_t Count );
	inline int BindUniform4fv( const char* Name, const float* v, const size_t Count );

	inline int BindUniformMatrix2x2( const char* Name, const Matrix2x2& Matrix );
	inline int BindUniformMatrix3x3( const char* Name, const Matrix3x3& Matrix );
	inline int BindUniformMatrix4x4( const char* Name, const Matrix4x4& Matrix );

	inline int BindUniformMatrix2fv( const char* Name, const float* Matrix, const size_t Count );
	inline int BindUniformMatrix3fv( const char* Name, const float* Matrix, const size_t Count );
	inline int BindUniformMatrix4fv( const char* Name, const float* Matrix, const size_t Count );

	inline int BindUniformColor( const char* Name, const GelColor Color );
	inline int BindUniformSColor( const char* Name, const GelSColor Color );
};
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader_Uniform.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_UBERSHADER_UBERSHADER_H__ //
// - ------------------------------------------------------------------------------------------ - //
