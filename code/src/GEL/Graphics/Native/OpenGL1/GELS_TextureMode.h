// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_TextureMode_H__
#define __GEL_Graphics_OpenGL_TextureMode_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
// - ------------------------------------------------------------------------------------------ - //

// TODO: control how a texture and vertex color mix //
//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_SMOOTH_TEXTURE_MIPMAP
// - ------------------------------------------------------------------------------------------ - //
inline void gels_SetSmoothTextureMipMap() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_SMOOTH_TEXTURE
// - ------------------------------------------------------------------------------------------ - //
inline void gels_SetSmoothTexture() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_BLOCKY_TEXTURE_MIPMAP
// - ------------------------------------------------------------------------------------------ - //
inline void gels_SetBlockyTextureMipMap() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_BLOCKY_TEXTURE
// - ------------------------------------------------------------------------------------------ - //
inline void gels_SetBlockyTexture() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_TextureMode_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
