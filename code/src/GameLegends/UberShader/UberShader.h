// - ------------------------------------------------------------------------------------------ - //
#ifndef __LEGENDS_UBERSHADER_UBERSHADER_H__
#define __LEGENDS_UBERSHADER_UBERSHADER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>

#include <Graphics/API.h>
// - ------------------------------------------------------------------------------------------ - //
class cUberShader_Shader {
public:
	GLuint Vertex;
	GLuint Fragment;
	GLuint Geometry;

	GLuint Program;
};
// - ------------------------------------------------------------------------------------------ - //
class cUberShader {
public:
	std::string FileName;
	
	std::vector< cUberShader_Shader > Shader;
		
public:
	cUberShader( const char* InFile );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_UBERSHADER_UBERSHADER_H__ //
// - ------------------------------------------------------------------------------------------ - //
