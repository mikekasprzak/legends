// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Blending_H__
#define __GEL_Graphics_Blending_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL/GELS_Blending.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableAlphaBlending() {
#ifdef GELS_ENABLE_ALPHA_BLENDING
	gels_EnableAlphaBlending();
#endif // GELS_ENABLE_ALPHA_BLENDING //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableAddativeBlending() {
#ifdef GELS_ENABLE_ADDATIVE_BLENDING
	gels_EnableAddativeBlending();
#endif // GELS_ENABLE_ADDATIVE_BLENDING //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableModulationBlending() {
#ifdef GELS_ENABLE_MODULATION_BLENDING
	gels_EnableModulationBlending();
#endif // GELS_ENABLE_MODULATION_BLENDING //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableBlending() {
#ifdef GELS_DISABLE_BLENDING
	gels_DisableBlending();
#endif // GELS_DISABLE_BLENDING //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Blending_H__ //
// - ------------------------------------------------------------------------------------------ - //
