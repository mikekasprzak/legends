// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_SHADER_SHADER_OPENGL_H__
#define __GEL2_SHADER_SHADER_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
void InitShader();
void ExitShader();
// - ------------------------------------------------------------------------------------------ - //
extern cUberShader* Default;
// - ------------------------------------------------------------------------------------------ - //
extern ShaderHandle FlatShader;
extern ShaderHandle FlatShader2D;
extern ShaderHandle FlatShader_Packed;
extern ShaderHandle FlatShader2D_Packed;
extern ShaderHandle ColorShader;
extern ShaderHandle ColorShader2D;
extern ShaderHandle TextureShader;
extern ShaderHandle TextureShader2D;
extern ShaderHandle TextureShader_Packed;
extern ShaderHandle TextureShader2D_Packed;
extern ShaderHandle ColorTextureShader;
extern ShaderHandle ColorTextureShader2D;
extern ShaderHandle ColorTextureShader_Packed;
extern ShaderHandle ColorTextureShader2D_Packed;
extern ShaderHandle NoiseShader;
extern ShaderHandle ColorNoiseShader;
extern ShaderHandle Noise1BitShader;
extern ShaderHandle ColorNoise1BitShader;
// - ------------------------------------------------------------------------------------------ - //
inline void Flat( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const st32 Count ) {
	Default->Bind( FlatShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->DrawArrays( Mode, Count );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_SHADER_SHADER_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
