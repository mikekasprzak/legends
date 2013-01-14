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
	
		
	struct cAttrib {
		enum {
			AI_NONE = 0,
			
			AI_PAD = 1,		// Used for Padding Bytes //
			
			AI_UCHAR = 2,	// 2 //
			AI_CHAR,
			AI_USHORT,		// 4 //
			AI_SHORT,
			AI_UINT,		// 6 //
			AI_INT,
			AI_UINT64,		// 8 //
			AI_INT64,
			AI_UINT128,		// 10 //
			AI_INT128,
			AI_UINT256,		// 12 //
			AI_INT256,
			AI_UINT512,		// 14 //
			AI_INT512,

			AI_QFLOAT = 16,	// Quarter Float (8bit) //
			AI_HFLOAT,		// Half Float (16bit) //
			AI_FLOAT,		// Float (32bit) //
			AI_DOUBLE,		// Double (64bit) //

			// Legacy //
			AI_FIXED,		// 32bit Fixed Point (16:16)
			
			// Extended GL Types //
			AI_UINT_10_10_10_2,	// 10bit x,y,z, 2bit w (unsigned) //
			AI_INT_10_10_10_2,	// 10bit x,y,z, 2bit w (signed) //
			
			
			
			// *** //
			AI_MAX			// Number of AI types //
		};
		
		enum {
			FL_NORMALIZE = 0x1,
		};
		
		int Index;
		int Group;
		int Type;
		int Count;
		int Flags;
		GLenum GLType;
		int Stride;
		
		cAttrib() :
			Group(-1),			// No Group (i.e. Not part of a Vertex Array Object) //
			Type(AI_NONE),
			Count(0),
			Flags(0),
			GLType(0),
			Stride(0)
		{
		}
		
		inline st32 GetSize() {
			static st32 Sizes[] = {
				0,		// AI_NONE //
				1,		// AI_PAD //
								
				1,1,	// char //
				2,2,	// short //
				4,4,	// int //
				8,8,	// int64 //
				16,16,	// int128 //
				32,32,	// int256 //
				64,64,	// int512 //

				1,2,	// QFLOAT, HFLOAT //
				4,8,	// float, double //
				
				// Legacy //
				4,		// Fixed //
				
				// Extended GL Types //
				1,1,	// packed INT_10_10_10_2 types (TODO: Check if sizes correct. Is either 4 or 1) //
			};
			return Sizes[Type] * Count;
		}
	};

	// OLD NOTE: Attribute Indexes are used mainly for compiling the shader. //
	// Positive non-zero enable, negative to disable (i.e. use same value constantly) //

	std::vector< cAttrib > Attrib;

	inline size_t GetAttribGroupSize( const int Group ) {
		size_t Size = 0;
		for ( size_t idx = 0; idx < Attrib.size(); idx++ ) {
			if ( Attrib[idx].Group == Group ) {
				Size += Attrib[idx].GetSize();
			}
		}
		return Size;
	}
	
	inline size_t GetTotalAttribSize() {
		size_t TotalSize = 0;
		for ( size_t idx = 0; idx < Attrib.size(); idx++ ) {
			TotalSize += Attrib[idx].GetSize();
		}
		return TotalSize;		
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

	// **** GL Code **** //

	// GL Hardcoding //
	inline void AttribPointer( const GLuint Index, const GLint Size, const GLenum Type, const GLboolean Normalized, const GLsizei Stride, const void* Ptr ) {
//		Log( "%i %i %i %i %i", Index, Size, Type, Normalized, Stride );

		glVertexAttribPointer( Index, Size, Type, Normalized, Stride, Ptr );
	}
	
	// 
	inline void Attrib( const GLuint Index, const void* Ptr ) {
		const GLint Size = CurrentShader->Attrib[Index].Count;	// Can be GL_BGRA, but not in GL ES //
		const GLenum Type = CurrentShader->Attrib[Index].GLType;
		const GLboolean Normalized = CurrentShader->Attrib[Index].Flags & cUberShader_Shader::cAttrib::FL_NORMALIZE;
		const GLsizei Stride = CurrentShader->Attrib[Index].Stride;
		
//		Log( "%i %i %i %i %i", Index, Size, Type, Normalized, Stride );

		glVertexAttribPointer( Index, Size, Type, Normalized, Stride, Ptr );
	}
	
	// GL Drawing Code //
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
