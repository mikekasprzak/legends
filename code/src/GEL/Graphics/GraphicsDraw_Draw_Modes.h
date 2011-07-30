// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_Draw_Modes_H__
#define __GEL_GraphicsDraw_Draw_Modes_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELSDraw_Draw_Modes.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeFlat_() {
#ifdef GELS_DRAW_MODE_FLAT
	gels_DrawModeFlat();
#endif // GELS_DRAW_MODE_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeColors_() {
#ifdef GELS_DRAW_MODE_COLORS
	gels_DrawModeColors();
#endif // GELS_DRAW_MODE_COLORS //	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeTextured_() {
#ifdef GELS_DRAW_MODE_TEXTURED
	gels_DrawModeTextured();
#endif // GELS_DRAW_MODE_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeTexturedColors_() {
#ifdef GELS_DRAW_MODE_TEXTURED_COLORS
	gels_DrawModeTexturedColors();
#endif // GELS_DRAW_MODE_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeFlat() {
	Current::OldDrawMode = Current::DrawMode;
	Current::DrawMode = GEL_DRAWMODE_FLAT;
	gelDrawModeFlat_();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeColors() {
	Current::OldDrawMode = Current::DrawMode;
	Current::DrawMode = GEL_DRAWMODE_COLORS;
	gelDrawModeColors_();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeTextured() {
	Current::OldDrawMode = Current::DrawMode;
	Current::DrawMode = GEL_DRAWMODE_TEXTURED;
	gelDrawModeTextured_();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeTexturedColors() {
	Current::OldDrawMode = Current::DrawMode;
	Current::DrawMode = GEL_DRAWMODE_TEXTURED_COLORS;
	gelDrawModeTexturedColors_();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawModeRestore() {
	Current::DrawMode = Current::OldDrawMode;
	if ( Current::OldDrawMode == GEL_DRAWMODE_FLAT ) {
		gelDrawModeFlat();
	}
	else if ( Current::OldDrawMode == GEL_DRAWMODE_COLORS ) {
		gelDrawModeColors();
	}
	else if ( Current::OldDrawMode == GEL_DRAWMODE_TEXTURED ) {
		gelDrawModeTextured();
	}
	else if ( Current::OldDrawMode == GEL_DRAWMODE_TEXTURED_COLORS ) {
		gelDrawModeTexturedColors();
	}
	else {
		Log("* Unknown Draw Mode (%i)\n", Current::OldDrawMode );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_Draw_Modes_H__ //
// - ------------------------------------------------------------------------------------------ - //
