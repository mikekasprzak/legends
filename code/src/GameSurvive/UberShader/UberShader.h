// - ------------------------------------------------------------------------------------------ - //
#ifndef __LEGENDS_UBERSHADER_UBERSHADER_H__
#define __LEGENDS_UBERSHADER_UBERSHADER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
#include <map>

#include <Graphics/API.h>
#include <Graphics/GelColor.h>
#include <Graphics/GelUV.h>

#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
typedef size_t GelShaderHandle;
// - ------------------------------------------------------------------------------------------ - //
class cUberShader_Shader {
public:
	GLuint Vertex;			// GL 2.0+ and GLSL 1.1+ -- Code: #version 110 -- GLES 2.0+ //
	GLuint Fragment;		// GL 2.0+ and GLSL 1.1+ -- Code: #version 110 -- GLES 2.0+ //

#ifdef USES_GEOMETRY_SHADERS
	GLuint Geometry;		// GL 3.2+ and GLSL 1.5+ -- Code: #version 150 //
#endif // USES_GEOMETRY_SHADERS //
#ifdef USES_TESSELLATION_SHADERS
	GLuint Tessellation;	// GL 4.0+ and GLSL 4.0+ -- Code: #version 400 //
#endif // USES_TESSELLATION_SHADERS //

	GLuint Program;			// GL 2.0+ and GLSL 1.1+ -- Code: #version 110 -- GLES 2.0+ //
	
	std::vector<int> Attributes;	// Positive non-zero enable, negative to disable //
	// Remember, Attributes when disabled use a single value across all //

public:		
	cUberShader_Shader() :
		Vertex( 0 ),
		Fragment( 0 ),
#ifdef USES_GEOMETRY_SHADERS
		Geometry( 0 ),
#endif // USES_GEOMETRY_SHADERS //
#ifdef USES_TESSELLATION_SHADERS
		Tessellation( 0 ),
#endif // USES_TESSELLATION_SHADERS //
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

	template<class VertType>
	inline void VectorAttribPointer( GLuint Index, const VertType* Ptr ) {
		if ( sizeof(VertType) / sizeof(Real) > 4 ) {
			// Hardcoded to 3 (xyz) if greater than 4. This lets us autodetect packed types. //
			AttribPointer( Index, 3, GL_FLOAT, GL_FALSE, sizeof(VertType), (const float*)Ptr );
		}
		else {
			AttribPointer( Index, sizeof(VertType) / sizeof(Real), GL_FLOAT, GL_FALSE, sizeof(VertType), (const float*)Ptr );
		}
	}

	template<class VertType>
	inline void Vector1DAttribPointer( GLuint Index, const VertType* Ptr ) {
		AttribPointer( Index, 1, GL_FLOAT, GL_FALSE, sizeof(VertType), (const float*)Ptr );
	}
	template<class VertType>
	inline void Vector2DAttribPointer( GLuint Index, const VertType* Ptr ) {
		AttribPointer( Index, 2, GL_FLOAT, GL_FALSE, sizeof(VertType), (const float*)Ptr );
	}
	template<class VertType>
	inline void Vector3DAttribPointer( GLuint Index, const VertType* Ptr ) {
		AttribPointer( Index, 3, GL_FLOAT, GL_FALSE, sizeof(VertType), (const float*)Ptr );
	}
	template<class VertType>
	inline void Vector4DAttribPointer( GLuint Index, const VertType* Ptr ) {
		AttribPointer( Index, 4, GL_FLOAT, GL_FALSE, sizeof(VertType), (const float*)Ptr );
	}
	template<class VertType>
	inline void ColorAttribPointer( GLuint Index, const VertType* Ptr ) {
		AttribPointer( Index, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(VertType), (const float*)Ptr );
	}
	template<class VertType>
	inline void UVAttribPointer( GLuint Index, const VertType* Ptr ) {
		AttribPointer( Index, 2, GL_UVType, GL_FALSE, sizeof(VertType), (const float*)Ptr );
	}

	inline void AttribPointer( const GLuint Index, const GLint Size, const GLenum Type, const GLboolean Normalized, const GLsizei Stride, const void* Ptr ) {
		glVertexAttribPointer( Index, Size, Type, Normalized, Stride, Ptr );
	}

	inline void DrawArrays( const int Mode, const size_t PolyCount ) {
		glDrawArrays( Mode, 0, PolyCount );	
	}

	// PolyCount unused here with OpenGL //
	inline void DrawElements( const int Mode, const size_t /*PolyCount*/, const unsigned short* Index, const size_t IndexCount ) {
		glDrawElements( Mode, IndexCount, GL_UNSIGNED_SHORT, (const unsigned short*)Index );
	}

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

	inline int BindUniformColor( const char* Name, const GelColor Color );		// 8 bit unsigned color (255=1.0) //
	inline int BindUniformSColor( const char* Name, const GelSColor Color );	// 16 bit signed color  (255=1.0) //
};
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader_Uniform.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_UBERSHADER_UBERSHADER_H__ //
// - ------------------------------------------------------------------------------------------ - //
