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
public:
	cUberShader( const char* InFile );
	~cUberShader();
	
	GelShaderHandle Find( const char* ShaderName );
	void Bind( const GelShaderHandle Index ) const;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_UBERSHADER_UBERSHADER_H__ //
// - ------------------------------------------------------------------------------------------ - //
