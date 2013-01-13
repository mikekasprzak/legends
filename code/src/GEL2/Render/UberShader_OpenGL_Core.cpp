// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>

#include <System/System.h>
#include <Search/Search.h>

#include <Util/String/String.h>

#include <Core/DataBlock.h>
#include <cJSON.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add support to the JSON file to load multiple files containing code (thus allowing me
//   to have seperate files for the Vertex and Fragment shaders, if I wanted).
// Consider making CurrentShader a static member of the class, so that there is only 1 current
//   accross all instances of the cUberShader class.
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
inline std::string DefineSymbol( const char* InStr ) {
	return std::string("#define ") + std::string(InStr) + std::string("\n");
}
// - ------------------------------------------------------------------------------------------ - //
GLuint GLSLCompile( const char* ShaderSrc, GLenum type ) {
	GLuint GLShader;
	GLint CompileStatus;
	
	GLShader = glCreateShader( type );
	if ( GLShader == 0 )
		return 0;
	
	glShaderSource( GLShader, 1, &ShaderSrc, NULL );
	glCompileShader( GLShader );
	
	glGetShaderiv( GLShader, GL_COMPILE_STATUS, &CompileStatus );
	
	if ( !CompileStatus ) {
		GLint InfoLen = 0;
		glGetShaderiv( GLShader, GL_INFO_LOG_LENGTH, &InfoLen );
		
		if ( InfoLen > 0 ) {
			char* InfoLog = new char[InfoLen];
			
			glGetShaderInfoLog( GLShader, InfoLen, NULL, InfoLog );
			Log( "! Error Compiling Shader:\n%s\n", InfoLog );
			
			delete [] InfoLog;
		}
		
		glDeleteShader( GLShader );
		return 0;
	}
	
	return GLShader;
}
// - ------------------------------------------------------------------------------------------ - //
inline cUberShader_Shader BuildShader( const char* Defines, const char* ShaderSource, const bool UseGeometryShader = false, const bool UseTessellationShader = false ) {
	cUberShader_Shader Program;
	
	std::string ProgramCode;
	// NOTE: The symbol "GL_ES" is already defined by the shader compilers. //
	// OpenGL Shading Language first version is 110
	// OpenGL ES Shading Language first version is 100
	
	const char* VersionString = "";
//	const char* VersionString = "#version 110\n";
	
#ifdef USES_OPENGL_ES2
//	VersionString = "#version 100\n";
#endif // USES_OPENGL_ES2 //

#ifdef USES_TESSELLATION_SHADERS
	VersionString = "#version 400\n";
#else // USES_TESSELLATION_SHADERS //
#ifdef USES_GEOMETRY_SHADERS
#ifdef USES_ARB_GEOMETRY_SHADERS
	VersionString = "#version 120\n#extension GL_EXT_geometry_shader4 : enable\n";
#else // USES_ARB_GEOMETRY_SHADERS //
	VersionString = "#version 150\n";
#endif // USES_ARB_GEOMETRY_SHADERS //
#endif // USES_GEOMETRY_SHADERS //
#endif // USES_TESSELLATION_SHADERS //
	
	ProgramCode = VersionString;
	ProgramCode += DefineSymbol( "VERTEX_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Vertex = GLSLCompile( ProgramCode.c_str(), GL_VERTEX_SHADER );
	VLog( "* Vertex Shader Compiled (%i)", Program.Vertex );
	
	ProgramCode = VersionString;
	ProgramCode += DefineSymbol( "FRAGMENT_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Fragment = GLSLCompile( ProgramCode.c_str(), GL_FRAGMENT_SHADER );
	VLog( "* Fragment Shader Compiled (%i)", Program.Fragment );
	
#ifdef USES_GEOMETRY_SHADERS
	ProgramCode = VersionString;
	ProgramCode += DefineSymbol( "GEOMETRY_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Geometry = GLSLCompile( ProgramCode.c_str(), GL_GEOMETRY_SHADER );
	VLog( "* Geometry Shader Compiled (%i)", Program.Geometry );
#endif // USES_GEOMETRY_SHADERS //

#ifdef USES_TESSELLATION_SHADERS
	ProgramCode = VersionString;
	ProgramCode += DefineSymbol( "TESSELLATION_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Tessellation = GLSLCompile( ProgramCode.c_str(), GL_TESSELLATION_SHADER );
	VLog( "* Tessellation Shader Compiled (%i)", Program.Tessellation );
#endif // USES_TESSELLATION_SHADERS //
	
	Program.Program = glCreateProgram();

	glAttachShader( Program.Program, Program.Vertex );
	glAttachShader( Program.Program, Program.Fragment );
	// Geometry and Tessellation shaders are optional, even if features are enabled //
#ifdef USES_GEOMETRY_SHADERS
	if ( UseGeometryShader )
		glAttachShader( Program.Program, Program.Geometry );
#endif // USES_GEOMETRY_SHADERS //
#ifdef USES_TESSELLATION_SHADERS
	if ( UseTessellationShader )
		glAttachShader( Program.Program, Program.Tessellation );
#endif // USES_TESSELLATION_SHADERS //
	VLog( "* Shaders Bound to Program (%i)", Program.Program );
	
	return Program;
}
// - ------------------------------------------------------------------------------------------ - //
inline void LinkShader( const cUberShader_Shader& Program ) {
	VLog( "* Linking..." );
	
	glLinkProgram( Program.Program );
	glUseProgram( Program.Program );
	VLog( "* Program Linked. Done." );
}
// - ------------------------------------------------------------------------------------------ - //
inline void _AssignShaderAttributes( cUberShader_Shader& Program, cJSON* Attribute ) {
	cJSON* Attrib = Attribute->child;
	
	// OpenGL requires an Index and a Name. Other Data is Optional //
	while ( Attrib ) {
		// NOTE: Crash Imminent here (non-existing object) //
		int Index = cJSON_GetObjectItem( Attrib, "Index" )->valueint;
		char* Name = cJSON_GetObjectItem( Attrib, "Name" )->valuestring;
		int OrigIndex = Index;
			
		if ( Index < 0 ) {
			Index = -Index;
		}
				
		VLog( "* * Attribute: %i %s%s", 
			Index, 
			Name,
			(OrigIndex != Index) ? " -- Disabled (-1)" : ""
			);
			
		glBindAttribLocation( 
			Program.Program, 
			Index, 
			Name
			);

		if ( (size_t)Index >= Program.Attrib.size() ) {
			Program.Attrib.resize( Index+1 ); // Index 5 is only available if Size is 6 //
		}

		cUberShader_Shader::cAttrib* Attr = &(Program.Attrib.back());
		
		// Store a copy of all attributes, so they can be enabled correctly //
		// NOTE: A negative explicitly disables requested Attribute //
		Attr->Index = OrigIndex;				

		// If there's a group specified, store it //
		if ( cJSON_GetObjectItem( Attrib, "Group" ) ) {
			Attr->Group = cJSON_GetObjectItem( Attrib, "Group" )->valueint;
		}

		// If there's a hardcoded Stride specified, store it //
		if ( cJSON_GetObjectItem( Attrib, "Stride" ) ) {
			Attr->Stride = cJSON_GetObjectItem( Attrib, "Stride" )->valueint;
		}

		// If there's a Count, store it //
		if ( cJSON_GetObjectItem( Attrib, "Count" ) ) {
			Attr->Count = cJSON_GetObjectItem( Attrib, "Count" )->valueint;
		}

		// If there's a Type, decypher it //
		if ( cJSON_GetObjectItem( Attrib, "Type" ) ) {			
			// NOTE: Unsigned's should come first, because of pattern matching //
			char* Type = cJSON_GetObjectItem( Attrib, "Type" )->valuestring;
			if ( strcmp( Type, "float" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_FLOAT;
				Attr->GLType = GL_FLOAT;
			}
			else if ( strcmp( Type, "hfloat" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_HFLOAT;
				Attr->GLType = GL_HALF_FLOAT;
			}
			else if ( strcmp( Type, "fixed" ) == 0 ) {
				// Legacy //
				Attr->Type = cUberShader_Shader::cAttrib::AI_FIXED;
				Attr->GLType = GL_FIXED;
			}
			else if ( strcmp( Type, "uchar" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_UCHAR;
				Attr->GLType = GL_UNSIGNED_BYTE;
			}
			else if ( strcmp( Type, "char" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_CHAR;
				Attr->GLType = GL_BYTE;
			}
			else if ( strcmp( Type, "ushort" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_USHORT;
				Attr->GLType = GL_UNSIGNED_SHORT;
			}
			else if ( strcmp( Type, "short" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_SHORT;
				Attr->GLType = GL_SHORT;
			}
			#if defined(USES_OPENGL3) || defined(USES_OPENGLES3)
				else if ( strcmp( Type, "double" ) == 0 ) {
					Attr->Type = cUberShader_Shader::cAttrib::AI_DOUBLE;
					Attr->GLType = GL_DOUBLE;
				}
				else if ( strcmp( Type, "uint" ) == 0 ) {
					Attr->Type = cUberShader_Shader::cAttrib::AI_UINT;
					Attr->GLType = GL_UNSIGNED_INT;
				}
				else if ( strcmp( Type, "int" ) == 0 ) {
					Attr->Type = cUberShader_Shader::cAttrib::AI_INT;
					Attr->GLType = GL_INT;
				}
				
				// Bitwise breakdown of formats like GL_INT_2_10_10_10_REV (GL3+) //
				// http://sugarpot.sakura.ne.jp/yuno/?OpenGL%E3%83%94%E3%82%AF%E3%82%BB%E3%83%AB%E3%83%95%E3%82%A9%E3%83%BC%E3%83%9E%E3%83%83%E3%83%88
				// NOTE: Other types like GL_SHORT_4_4_4_4 are Texture Only //

				else if ( strcmp( Type, "uint_10_10_10_2" ) == 0 ) {
					Attr->Type = cUberShader_Shader::cAttrib::AI_UINT_10_10_10_2;
					Attr->GLType = GL_UNSIGNED_INT_2_10_10_10_REV;	// Reversed format //
				}
				else if ( strcmp( Type, "int_10_10_10_2" ) == 0 ) {
					Attr->Type = cUberShader_Shader::cAttrib::AI_INT_10_10_10_2;
					Attr->GLType = GL_INT_2_10_10_10_REV; // Reversed Format //
				}
			#endif // defined(USES_OPENGL3) || defined(USES_OPENGLES3)

			// Special Names //
			else if ( strcmp( Type, "UVType" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_SHORT;
				Attr->GLType = GL_SHORT;
			}
			else if ( strcmp( Type, "pad" ) == 0 ) {
				Attr->Type = cUberShader_Shader::cAttrib::AI_PAD;
			}
			
			// Errors //
			else {
				Log( "! Unknown or Unsupported Attribute Type (%s)", Type );
			}
			
			
			VLog( "* * * Info: %s (id: %i) x%i -- %i bytes", 
				Type, 
				Attr->Type,
				Attr->Count,
				Attr->GetSize()
				);
		}
		
		// Next Attribute //
		Attrib = Attrib->next;
	}
	
	// Calculade Strides //
	{
		for ( st32 idx = 0; idx < Program.Attrib.size(); idx++ ) {
			// If a Stride is currently not set //
			if ( Program.Attrib[idx].Stride == 0 ) {
				// If the Attribute has no group //
				if ( Program.Attrib[idx].Group != -1 ) {
					st32 TotalSize = 0;
					for ( st32 idx2 = 0; idx2 < Program.Attrib.size(); idx2++ ) {
						TotalSize += Program.Attrib[idx].GetSize();
					}
					Program.Attrib[idx].Stride = TotalSize;
				}
				else {
					// No Group, so it's only as big as it is //
					Program.Attrib[idx].Stride = Program.Attrib[idx].GetSize();
				}
			}
			
			VLog( "* * %i Stride: %i", idx, Program.Attrib[idx].Stride );
		}
	}

	// Log the Total Size //
	VLog( "* Total Attribute Size: %i bytes (Data per vertex)", Program.GetTotalAttribSize() );
}
// - ------------------------------------------------------------------------------------------ - //
cUberShader::cUberShader( const char* InFile ) :
	CurrentShader( 0 )
{
	ProcessShader( InFile );
}
// - ------------------------------------------------------------------------------------------ - //
cUberShader::cUberShader( const char* JSONFile, const char* GLSLFile ) :
	CurrentShader( 0 )
{
	ProcessShader( JSONFile, GLSLFile );
}
// - ------------------------------------------------------------------------------------------ - //
cUberShader::cUberShader( const char* JSONData, const size_t JSONSize, const char* GLSLData, const size_t GLSLSize ) :
	CurrentShader( 0 )
{
	ProcessShader( JSONData, JSONSize, GLSLData, GLSLSize );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::ProcessShader( const char* InFile ) {
//	ShaderLookup.clear();

	Log( "+ Loading UberShader Permutations File..." );
	Log( "* File: %s", InFile );
	DataBlock* File = new_read_nullterminate_DataBlock( InFile );
	
	VLog( "* Parsing JSON Data (%i bytes)...", File->Size );
	
	cJSON* root = cJSON_Parse( File->Data );

	if ( root == 0 ) {
		Log( "! UberShader: Error parsing JSON data!" );
	}
	else {
		cJSON* ShaderFile = cJSON_GetObjectItem( root, "File" );
		
		VLog( "* Loadinng Shader Sources..." );
		VLog( "* File: %s", ShaderFile->valuestring );
		
		std::string ShaderSourceFile = std::string(String::DirectorySlash( InFile )) + ShaderFile->valuestring;
		VLog( "* FilePath: %s", ShaderSourceFile.c_str() );

		DataBlock* ShaderSource = new_read_nullterminate_DataBlock( ShaderSourceFile.c_str() );
		
		if ( ShaderSource ) {
			VLog( "* Shader Source Loaded (%i bytes).", ShaderSource->Size );
			
			ProcessShader( root, ShaderSource->Data );

			delete_DataBlock( ShaderSource );
			VLog( "* Done with Shader Sources" );
		}
		else {
			Log( "! UberShader: Error loading Shader Sources!" );
		}
		
		cJSON_Delete( root );
		VLog( "* Done JSON Data" );
	}
	
	// Clear Shader Usage //
	glUseProgram( 0 );

	delete_DataBlock( File );
	Log( "- Done with UberShader Permutations File." );	
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::ProcessShader( const char* JSONFile, const char* GLSLFile ) {
//	ShaderLookup.clear();

	Log( "+ Loading UberShader Permutations File..." );
	Log( "* File: %s", JSONFile );
	DataBlock* File = new_read_nullterminate_DataBlock( JSONFile );
	
	VLog( "* Parsing JSON Data (%i bytes)...", File->Size );
	
	cJSON* root = cJSON_Parse( File->Data );

	if ( root == 0 ) {
		Log( "! UberShader: Error parsing JSON data!" );
	}
	else {
		VLog( "* Loadinng Shader Sources (Explicit)..." );
		VLog( "* File: %s", GLSLFile );

		DataBlock* ShaderSource = new_read_nullterminate_DataBlock( GLSLFile );
		
		if ( ShaderSource ) {
			VLog( "* Shader Source Loaded (%i bytes).", ShaderSource->Size );
			
			ProcessShader( root, ShaderSource->Data );

			delete_DataBlock( ShaderSource );
			VLog( "* Done with Shader Sources" );
		}
		else {
			Log( "! UberShader: Error loading Shader Sources!" );
		}
		
		cJSON_Delete( root );
		VLog( "* Done JSON Data" );
	}
	
	// Clear Shader Usage //
	glUseProgram( 0 );

	delete_DataBlock( File );
	Log( "- Done with UberShader Permutations File." );	
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::ProcessShader( const char* JSONData, const size_t JSONSize, const char* GLSLData, const size_t GLSLSize ) {
//	ShaderLookup.clear();

	Log( "+ Loading UberShader Permutations File (Embedded)..." );	
	VLog( "* Parsing JSON Data (%i bytes)...", JSONSize );
	
	cJSON* root = cJSON_Parse( JSONData );

	if ( root == 0 ) {
		Log( "! UberShader: Error parsing JSON data!" );
	}
	else {
		VLog( "* Loadinng Shader Sources (Embedded)..." );
		
		if ( GLSLData ) {
			VLog( "* Shader Source Loaded (%i bytes).", GLSLSize );
			
			ProcessShader( root, GLSLData );
		}
		else {
			Log( "! UberShader: Error loading Shader Sources!" );
		}
		
		cJSON_Delete( root );
		VLog( "* Done JSON Data" );
	}
	
	// Clear Shader Usage //
	glUseProgram( 0 );

	Log( "- Done with UberShader Permutations File." );	
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::ProcessShader( cJSON* root, const char* ShaderSource ) {
	cJSON* ShaderList = cJSON_GetObjectItem( root, "Shaders" );
	
	VLog( "* %s", ShaderList->string );
	
	cJSON* ShaderObj = ShaderList->child;
	while ( ShaderObj != 0 ) {
		VLog( "+ Begin Program \"%s\"", ShaderObj->string );
		
		std::string DefineList;
		
		cJSON* Define = cJSON_GetObjectItem( ShaderObj, "Define" );
		if ( Define ) {
			cJSON* Obj = Define->child;
			while ( Obj != 0 ) {
				VLog("* * #DEFINE %s", Obj->valuestring );
				
				DefineList += DefineSymbol( Obj->valuestring );
				
				// Next Define //
				Obj = Obj->next;
			}
		}
		else {
			Log( "! UberShader: Error, \"Define\" section not found in %s!", ShaderObj->string );
		}

		bool HasGeometryShader = false;
#ifdef USES_GEOMETRY_SHADER
		// Section "Geometry": true, under the shader name //
		cJSON* Geometry = cJSON_GetObjectItem( ShaderObj, "Geometry" );
		if ( Geometry ) {
			if ( Geometry->type == cJSON_True ) {
				HasGeometryShader = true;
			}
		}
#endif // USES_GEOMETRY_SHADER //

		bool HasTessellationShader = false;
#ifdef USES_TESSELLATION_SHADER
		// Section "Tessellation": true, under the shader name //
		cJSON* Tessellation = cJSON_GetObjectItem( ShaderObj, "Tessellation" );
		if ( Tessellation ) {
			if ( Tessellation->type == cJSON_True ) {
				HasTessellationShader = true;
			}
		}
#endif // USES_TESSELLATION_SHADER //

		// Build the Shader //
		cUberShader_Shader Program = BuildShader( DefineList.c_str(), ShaderSource, HasGeometryShader, HasTessellationShader );
		// Assign Attributes //
		cJSON* Attribute = cJSON_GetObjectItem( ShaderObj, "Attribute" );
		if ( Attribute ) {
			VLog( "+ Binding Attributes to Program..." );
			_AssignShaderAttributes( Program, Attribute );
			VLog( "- Attributes bound to Program." );
		}
		else {
			Log( "! UberShader: Error, \"Attribute\" section not found in %s!", ShaderObj->string );
		}				
		// Link the shader for use //
		LinkShader( Program );
		
		// Add Program to the UberShader //
		ShaderLookup[ ShaderObj->string ] = Shader.size();
		Shader.push_back( Program );
		
		VLog( "- Program \"%s\"Finished.", ShaderObj->string );
		
		// Next Shader //
		ShaderObj = ShaderObj->next;
	}
}
// - ------------------------------------------------------------------------------------------ - //
cUberShader::~cUberShader() {
	for ( size_t idx = 0; idx < Shader.size(); idx++ ) {
		if ( Shader[idx].Program )
			glDeleteProgram( Shader[idx].Program );

		if ( Shader[idx].Vertex )
			glDeleteShader( Shader[idx].Vertex );
		if ( Shader[idx].Fragment )
			glDeleteShader( Shader[idx].Fragment );
			
#ifdef USES_GEOMETRY_SHADER
		if ( Shader[idx].Geometry )
			glDeleteShader( Shader[idx].Geometry );
#endif // USES_GEOMETRY_SHADER //		

#ifdef USES_TESSELLATION_SHADER
		if ( Shader[idx].Tessellation )
			glDeleteShader( Shader[idx].Tessellation );
#endif // USES_TESSELLATION_SHADER //		
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::EnableAttrib( const int Index ) {
	glEnableVertexAttribArray( Index );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::DisableAttrib( const int Index ) {
	glDisableVertexAttribArray( Index );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::_Bind( const ShaderHandle Index ) {
	CurrentShader = &Shader[Index];
	glUseProgram( Shader[Index].Program );
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Bind( const ShaderHandle Index ) {
	CurrentShader = &Shader[Index];
	glUseProgram( Shader[Index].Program );

	// Skipping Zero, since I never disable zero //	
	for ( size_t idx = 1; idx < Shader[Index].Attrib.size(); idx++ ) {
		if ( Shader[Index].Attrib[idx].Index >= 0 ) {
			glEnableVertexAttribArray( Shader[Index].Attrib[idx].Index );
		}
		else {
			glDisableVertexAttribArray( -(Shader[Index].Attrib[idx].Index) );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
ShaderHandle cUberShader::Find( const char* ShaderName ) {
	Log( "+ Searching for Shader \"%s\"", ShaderName );

	// Search the map for the specific pattern //
	std::map<std::string, ShaderHandle>::iterator SearchIterator = ShaderLookup.find( ShaderName );
	
	// If it was found, return the Id //
	if ( SearchIterator != ShaderLookup.end() ) {
		Log( "- \"%s\" found!", ShaderName );
		return SearchIterator->second;
	}
	else {
		Log( "- ERROR! No Shader named \"%s\"", ShaderName );
	}
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
