// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_SHADER_SHADER_OPENGL_H__
#define __GEL2_SHADER_SHADER_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Shader {
// - ------------------------------------------------------------------------------------------ - //
void Init();
void Exit();
// - ------------------------------------------------------------------------------------------ - //
extern cUberShader* Default;
// - ------------------------------------------------------------------------------------------ - //
extern ShaderHandle FlatShader;
extern ShaderHandle ColorShader;
extern ShaderHandle TextureShader;
extern ShaderHandle ColorTextureShader;
extern ShaderHandle NoiseShader;
extern ShaderHandle ColorNoiseShader;
extern ShaderHandle Noise1BitShader;
extern ShaderHandle ColorNoise1BitShader;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Shader //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_SHADER_SHADER_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
