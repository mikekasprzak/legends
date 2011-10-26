// - ------------------------------------------------------------------------------------------ - //
#include "UberShader.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>

#include <cJSON.h>
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
inline cUberShader_Shader BuildShader( const char* Defines, const char* ShaderSource, bool UseGeometryShader = false ) {
	cUberShader_Shader Program;
	
	std::string ProgramCode;
		
	ProgramCode = DefineSymbol( "VERTEX_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Vertex = GLSLCompile( ProgramCode.c_str(), GL_VERTEX_SHADER );
	VLog( "* Vertex Shader Compiled (%i)", Program.Vertex );
	
	ProgramCode = DefineSymbol( "FRAGMENT_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Fragment = GLSLCompile( ProgramCode.c_str(), GL_FRAGMENT_SHADER );
	VLog( "* Fragment Shader Compiled (%i)", Program.Fragment );
	
#ifdef USES_GEOMETRY_SHADERS
	ProgramCode = DefineSymbol( "GEOMETRY_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Geometry = GLSLCompile( ProgramCode.c_str(), GL_GEOMETRY_SHADER );
	VLog( "* Geometry Shader Compiled (%i)", Program.Geometry );
#endif // USES_GEOMETRY_SHADERS //
	
	Program.Program = glCreateProgram();

	glAttachShader( Program.Program, Program.Vertex );
	glAttachShader( Program.Program, Program.Fragment );
#ifdef USES_GEOMETRY_SHADERS
	if ( UseGeometryShader )
		glAttachShader( Program.Program, Program.Geometry );
#endif // USES_GEOMETRY_SHADERS //
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
inline void AssignShaderAttributes( const cUberShader_Shader& Program, cJSON* Attribute ) {
	cJSON* Attrib = Attribute->child;
	
	while ( Attrib ) {
		int Index = cJSON_GetObjectItem( Attrib, "Index" )->valueint;
		char* Name = cJSON_GetObjectItem( Attrib, "Name" )->valuestring;
		
		VLog( "* * * Attribute: %i %s", 
			Index, 
			Name
			);

		glBindAttribLocation( 
			Program.Program, 
			Index, 
			Name
			);
		
		// Next Attribute //
		Attrib = Attrib->next;
	}
	VLog( "* Attributes bound to Program" );
}
// - ------------------------------------------------------------------------------------------ - //
cUberShader::cUberShader( const char* InFile ) {
	Log( "+ Loading UberShader Permutations File..." );
	VLog( "* File: %s", InFile );
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
		DataBlock* ShaderSource = new_read_nullterminate_DataBlock( ShaderFile->valuestring );
		
		if ( ShaderSource ) {
			VLog( "* Shader Source Loaded (%i bytes).", ShaderSource->Size );
			
			cJSON* ShaderList = cJSON_GetObjectItem( root, "Shaders" );
			
			VLog( "* %s", ShaderList->string );
			
			cJSON* ShaderObj = ShaderList->child;
			while ( ShaderObj != 0 ) {
				VLog( "* * %s", ShaderObj->string );
				
				std::string DefineList;
				
				cJSON* Define = cJSON_GetObjectItem( ShaderObj, "Define" );
				if ( Define ) {
					cJSON* Obj = Define->child;
					while ( Obj != 0 ) {
						VLog("* * * #DEFINE %s", Obj->valuestring );
						
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

				// Build the Shader //
				cUberShader_Shader Program = BuildShader( DefineList.c_str(), ShaderSource->Data, HasGeometryShader );
				// Assign Attributes //
				cJSON* Attribute = cJSON_GetObjectItem( ShaderObj, "Attribute" );
				if ( Attribute ) {
					AssignShaderAttributes( Program, Attribute );
				}
				else {
					Log( "! UberShader: Error, \"Attribute\" section not found in %s!", ShaderObj->string );
				}				
				// Link the shader for use //
				LinkShader( Program );
				
				// Add Shader to the UberShader //
				Shader.push_back( Program );
				
				// Next Shader //
				ShaderObj = ShaderObj->next;
			}
			
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
