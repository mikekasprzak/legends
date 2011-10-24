// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Draw_Draw_Modes_H__
#define __GEL_Graphics_OpenGL_Draw_Draw_Modes_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include "GELS_Shader.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_FLAT
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeFlat() {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	gels_FlatShaded();
#else // USES_OPENGL2 //
	glDisable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeColors() {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	gels_ColorShaded();
#else // USES_OPENGL2 //
	glDisable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_TEXTURED
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeTextured() {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	gels_TextureShaded();
#else // USES_OPENGL2 //
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_TEXTURED_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeTexturedColors() {
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	gels_TextureColorShaded();
#else // USES_OPENGL2 //
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
#endif // USES_OPENGL2 //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Draw_Draw_Modes_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
