// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_TextureMode_H__
#define __GEL_Graphics_TextureMode_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELS_TextureMode.h"
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
#endif // __GEL_Graphics_TextureMode_H__ //
// - ------------------------------------------------------------------------------------------ - //
