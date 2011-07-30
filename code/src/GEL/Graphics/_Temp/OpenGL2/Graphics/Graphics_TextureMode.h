// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_TextureMode_H__
#define __Graphics_TextureMode_H__
// - ------------------------------------------------------------------------------------------ - //

// This controls how a texture and vertex color mix //
//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetSmoothTexturesMipMapped() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetSmoothTextures() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetBlockyTexturesMipMapped() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetBlockyTextures() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_TextureMode_H__ //
// - ------------------------------------------------------------------------------------------ - //
