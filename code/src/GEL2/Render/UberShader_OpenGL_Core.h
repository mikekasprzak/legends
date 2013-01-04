// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_SHADER_UBERSHADER_OPENGL_CORE_H__
#define __GEL2_SHADER_UBERSHADER_OPENGL_CORE_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
#include <map>

#include <API/API_OpenGL2.h>
#include <Graphics/GelColor.h>
#include <Graphics/GelUV.h>

#include <Core/DataBlock.h>
#include <cJSON.h>

#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
typedef size_t ShaderHandle;
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
	
	// Attribute Indexes. Used mainly for compiling the shader. //
	std::vector<int> Attributes;	// Positive non-zero enable, negative to disable //
	// Remember, Attributes when disabled use a single value across all //
	
	struct cAttribInfo {
		enum {
			AI_NONE = 0,	// Used for Padding Bytes //
			
			AI_FLOAT = 1,
			AI_DOUBLE = 2,
			AI_HFLOAT = 3,	// Half Float //
			//AI_?? = 4,
			
			AI_UCHAR = 5,
			AI_CHAR = 6,
			AI_USHORT = 7,
			AI_SHORT = 8,
			AI_UINT = 9,
			AI_INT = 10,
			AI_UINT64 = 11,
			AI_INT64 = 12,
		};
		
		int Type;
		int Count;
		
		inline size_t GetSize() {
			static size_t Sizes[] = {
				1,		// Used for Padding Bytes //
				
				4,8,
				2,0,
				
				1,1,
				2,2,
				4,4,
				8,8,
			};
			return Sizes[Type] * Count;
		}
	};
	std::vector< std::vector<cAttribInfo> > AttribInfo;
	inline size_t GetAttribSize( const size_t Index ) {
		size_t Size = 0;
		for ( size_t idx = 0; idx < AttribInfo[Index].size(); idx++ ) {
			Size += AttribInfo[Index][idx].GetSize();
		}
		return Size;
	}

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
	
	std::vector<cUberShader_Shader> Shader;
	std::map<std::string, ShaderHandle> ShaderLookup;
		
	cUberShader_Shader* CurrentShader;
public:
	cUberShader( const char* InFile );
	cUberShader( const char* JSONFile, const char* GLSLFile );
	cUberShader( const char* JSONData, const size_t JSONSize, const char* GLSLData, const size_t GLSLSize );
	~cUberShader();

	void ProcessShader( const char* InFile );
	void ProcessShader( const char* JSONFile, const char* GLSLFile );
	void ProcessShader( const char* JSONData, const size_t JSONSize, const char* GLSLData, const size_t GLSLSize );
	void ProcessShader( cJSON* root, const char* ShaderSource );
	
	ShaderHandle Find( const char* ShaderName );
	void Bind( const ShaderHandle Index = 0 );

	void _Bind( const ShaderHandle Index = 0 );			// Doesn't Enable Attributes //
	static void EnableAttrib( const int Index = 0 );
	static void DisableAttrib( const int Index = 0 );

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

	// GL Code //
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
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_SHADER_UBERSHADER_OPENGL_CORE_H__ //
// - ------------------------------------------------------------------------------------------ - //
