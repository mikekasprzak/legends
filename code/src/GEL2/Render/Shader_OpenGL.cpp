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
ShaderHandle ColorShader;
ShaderHandle TextureShader;
ShaderHandle ColorTextureShader;
ShaderHandle NoiseShader;
ShaderHandle ColorNoiseShader;
ShaderHandle Noise1BitShader;
ShaderHandle ColorNoise1BitShader;
// - ------------------------------------------------------------------------------------------ - //
void InitShader() {
	// Use Files //	
//	Default = new cUberShader( "src/GEL2/Render/Embedded/GLSL/DefaultShader.json" );
	// Use Embedded //
	Default = new cUberShader( DefaultShader_json, DefaultShader_json_Size, DefaultShader_glsl, DefaultShader_glsl_Size );

	// Find all the shaders //
	FlatShader = Default->Find( "Flat" );
	ColorShader = Default->Find( "Color" );
	TextureShader = Default->Find( "Texture" );
	ColorTextureShader = Default->Find( "ColorTexture" );
	NoiseShader = Default->Find( "Noise" );
	ColorNoiseShader = Default->Find( "ColorNoise" );
	Noise1BitShader = Default->Find( "Noise1Bit" );
	ColorNoise1BitShader = Default->Find( "ColorNoise1Bit" );
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
