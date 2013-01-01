// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "Shader.h"
#include "Embedded/GLSL/EmbeddedShaders.h"	// DefaultShader_json, etc //
// - ------------------------------------------------------------------------------------------ - //
namespace Shader {
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
void Init() {
	atexit( Exit );

	// Use Files //	
	Default = new cUberShader( "src/GEL2/Shader/Embedded/GLSL/DefaultShader.json" );
	// Use Embedded //
//	Default = new cUberShader( DefaultShader_json, DefaultShader_json_Size, DefaultShader_glsl, DefaultShader_glsl_Size );

	// Find all the shaders //
	FlatShader = Shader::Default->Find( "Flat" );
	ColorShader = Shader::Default->Find( "Color" );
	TextureShader = Shader::Default->Find( "Texture" );
	ColorTextureShader = Shader::Default->Find( "ColorTexture" );
	NoiseShader = Shader::Default->Find( "Noise" );
	ColorNoiseShader = Shader::Default->Find( "ColorNoise" );
	Noise1BitShader = Shader::Default->Find( "Noise1Bit" );
	ColorNoise1BitShader = Shader::Default->Find( "ColorNoise1Bit" );
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	delete Default;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Shader //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
