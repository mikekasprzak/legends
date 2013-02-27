// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "Shader.h"
#include "Embedded/GLSL/EmbeddedShaders.h"	// DefaultShader_json, etc //
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
cUberShader* Default;
// - ------------------------------------------------------------------------------------------ - //
ShaderHandle FlatShader;
ShaderHandle FlatShader2D;
ShaderHandle FlatShader_Packed;
ShaderHandle FlatShader2D_Packed;
ShaderHandle ColorShader;
ShaderHandle ColorShader2D;
ShaderHandle TextureShader;
ShaderHandle TextureShader2D;
ShaderHandle ColorTextureShader;
ShaderHandle ColorTextureShader2D;
ShaderHandle ColorTextureShader_Packed;
ShaderHandle ColorTextureShader2D_Packed;
ShaderHandle NoiseShader;
ShaderHandle ColorNoiseShader;
ShaderHandle Noise1BitShader;
ShaderHandle ColorNoise1BitShader;
// - ------------------------------------------------------------------------------------------ - //
void InitShader() {
	// Use Files //	
	Default = new cUberShader( "src/GEL2/Render/Embedded/GLSL/DefaultShader.json" );
	// Use Embedded //
//	Default = new cUberShader( DefaultShader_json, DefaultShader_json_Size, DefaultShader_glsl, DefaultShader_glsl_Size );

	// Find all the shaders //
	FlatShader = Default->Find( "Flat" );
	FlatShader2D = Default->Find( "Flat2D" );
	FlatShader_Packed = Default->Find( "Flat_Packed" );
	FlatShader2D_Packed = Default->Find( "Flat2D_Packed" );
	ColorShader = Default->Find( "Color" );
	ColorShader2D = Default->Find( "Color2D" );
	TextureShader = Default->Find( "Texture" );
	TextureShader2D = Default->Find( "Texture2D" );
	ColorTextureShader = Default->Find( "ColorTexture" );
	ColorTextureShader2D = Default->Find( "ColorTexture2D" );
	ColorTextureShader_Packed = Default->Find( "ColorTexture_Packed" );
	ColorTextureShader2D_Packed = Default->Find( "ColorTexture2D_Packed" );
	NoiseShader = Default->Find( "Noise" );
	ColorNoiseShader = Default->Find( "ColorNoise" );
	Noise1BitShader = Default->Find( "Noise1Bit" );
	ColorNoise1BitShader = Default->Find( "ColorNoise1Bit" );
	
	// Enable this here, since all shaders will always require Attrib 0 to be enabled //
	//glEnableVertexAttribArray( 0 );
	cUberShader::EnableAttrib( 0 );
}
// - ------------------------------------------------------------------------------------------ - //
void ExitShader() {
	delete Default;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
