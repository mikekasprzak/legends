// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_TextureMode_H__
#define __GEL_Graphics_TextureMode_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL/GELS_TextureMode.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetSmoothTexturesMipMapped() {
#ifdef GELS_SET_SMOOTH_TEXTURE_MIPMAP
	gels_SetSmoothTextureMipMap();
#endif // GELS_SET_SMOOTH_TEXTURE_MIPMAP //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetSmoothTextures() {
#ifdef GELS_SET_SMOOTH_TEXTURE
	gels_SetSmoothTexture();
#endif // GELS_SET_SMOOTH_TEXTURE //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetBlockyTexturesMipMapped() {
#ifdef GELS_SET_BLOCKY_TEXTURE_MIPMAP
	gels_SetBlockyTextureMipMap();
#endif // GELS_SET_BLOCKY_TEXTURE_MIPMAP //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetBlockyTextures() {
#ifdef GELS_SET_BLOCKY_TEXTURE 
	gels_SetBlockyTexture();
#endif // GELS_SET_BLOCKY_TEXTURE //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableTexturing() {
#ifdef GELS_ENABLE_TEXTURING
	gels_EnableTexturing();
#endif // GELS_ENABLE_TEXTURING //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableTexturing() {
#ifdef GELS_DISABLE_TEXTURING
	gels_DisableTexturing();
#endif // GELS_DISABLE_TEXTURING //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_TextureMode_H__ //
// - ------------------------------------------------------------------------------------------ - //
