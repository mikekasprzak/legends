// - ------------------------------------------------------------------------------------------ - //
#ifndef __LEGENDS_UBERSHADER_UBERSHADER_H__
#define __LEGENDS_UBERSHADER_UBERSHADER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
#include <map>

#include <Graphics/API.h>
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
	
	inline void BindUniformi( const char* Name, const int v0 );
	inline void BindUniformi( const char* Name, const int v0, const int v1 );
	inline void BindUniformi( const char* Name, const int v0, const int v1, const int v2 );
	inline void BindUniformi( const char* Name, const int v0, const int v1, const int v2, const int v3 );

	inline void BindUniformf( const char* Name, const float v0 );
	inline void BindUniformf( const char* Name, const float v0, const float v1 );
	inline void BindUniformf( const char* Name, const float v0, const float v1, const float v2 );
	inline void BindUniformf( const char* Name, const float v0, const float v1, const float v2, const float v3 );
};
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader_Uniform.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_UBERSHADER_UBERSHADER_H__ //
// - ------------------------------------------------------------------------------------------ - //
