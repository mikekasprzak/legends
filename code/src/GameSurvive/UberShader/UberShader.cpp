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
	
	ProgramCode = "";//"#version 200\n";	
	ProgramCode += DefineSymbol( "VERTEX_SHADER" );
	ProgramCode += Defines;
	ProgramCode += ShaderSource;
	Program.Vertex = GLSLCompile( ProgramCode.c_str(), GL_VERTEX_SHADER );
	VLog( "* Vertex Shader Compiled (%i)", Program.Vertex );
	
	ProgramCode = "";//"#version 200\n";
	ProgramCode += DefineSymbol( "FRAGMENT_SHADER" );
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
inline void AssignShaderAttributes( cUberShader_Shader& Program, cJSON* Attribute ) {
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
		
		// Store a copy of all attributes, so they can be enabled correctly //
		Program.Attributes.push_back( Index );
		
		// TODO: store negatives when explicit disabled requested //
		
		// Next Attribute //
		Attrib = Attrib->next;
	}
	VLog( "* Attributes bound to Program" );
}
// - ------------------------------------------------------------------------------------------ - //
cUberShader::cUberShader( const char* InFile ) :
	CurrentShader( 0 )
{
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
		
		// HACK: Until I feel like doing this a better way //
		extern char AppBaseDir[]; 
		std::string Prefix = AppBaseDir;

		DataBlock* ShaderSource = new_read_nullterminate_DataBlock( std::string( Prefix + ShaderFile->valuestring ).c_str() );
		
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
				
				// Add Program to the UberShader //
				ShaderLookup[ ShaderObj->string ] = Shader.size();
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cUberShader::Bind( const GelShaderHandle Index ) {
	CurrentShader = &Shader[Index];
	glUseProgram( Shader[Index].Program );

	// Skipping Zero, since I never disable zero //	
	for ( int idx = 1; idx < Shader[Index].Attributes.size(); idx++ ) {
		if ( Shader[Index].Attributes[idx] > 0 ) {
			glEnableVertexAttribArray( Shader[Index].Attributes[idx] );
		}
		else {
			glDisableVertexAttribArray( -Shader[Index].Attributes[idx] );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
GelShaderHandle cUberShader::Find( const char* ShaderName ) {
	Log( "+ Searching for Shader \"%s\"", ShaderName );

	// Search the map for the specific pattern //
	std::map<std::string, GelShaderHandle>::iterator SearchIterator = ShaderLookup.find( ShaderName );
	
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
