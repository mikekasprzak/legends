// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_Draw_Draw_Modes_H__
#define __GEL_Graphics_OpenGL1_Draw_Draw_Modes_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_FLAT
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeFlat() {
	glDisable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeColors() {
	glDisable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_TEXTURED
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeTextured() {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_DRAW_MODE_TEXTURED_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void gels_DrawModeTexturedColors() {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_Draw_Draw_Modes_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
