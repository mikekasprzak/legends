// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Blending_H__
#define __GEL_Graphics_OpenGL_Blending_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_ENABLE_ALPHA_BLENDING
inline void gels_EnableAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_ENABLE_PREMULTIPLIED_ALPHA_BLENDING
inline void gels_EnablePremultipliedAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_ENABLE_ADDATIVE_BLENDING
inline void gels_EnableAddativeBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_ENABLE_MODULATION_BLENDING
inline void gels_EnableModulationBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_DST_COLOR, GL_ZERO );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DISABLE_BLENDING
inline void gels_DisableBlending() {
	glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Blending_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
