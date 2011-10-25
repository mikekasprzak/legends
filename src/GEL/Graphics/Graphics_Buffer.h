// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Buffer_H__
#define __GEL_Graphics_Buffer_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL/GELS_Buffer.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetClearColor( const GelColor Color ) {
#ifdef GELS_SET_CLEAR_COLOR
	gels_SetClearColor( Color );
#endif // GELS_SET_CLEAR_COLOR //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetColorMask( const bool Red, const bool Green, const bool Blue, const bool Alpha ) {
#ifdef GELS_SET_COLOR_MASK
	gels_SetColorMask( Red, Green, Blue, Alpha );
#endif // GELS_SET_COLOR_MASK // 
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelClear( const bool ColorBuffer = true, const bool DepthBuffer = false, const bool StencilBuffer = false ) {
#ifdef GELS_CLEAR
	gels_Clear( ColorBuffer, DepthBuffer, StencilBuffer );
#endif // GELS_CLEAR //
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableColorWriting() {
	gelSetColorMask( true, true, true, true );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableColorWriting() {
	gelSetColorMask( false, false, false, false );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelClearColor( const GelColor Color = GEL_RGB_BLACK ) {
	gelSetClearColor( Color );
	gelClear( true );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSwapBuffer( ) {
#ifdef GELS_SWAP_BUFFER
	gels_SwapBuffer();
#endif // GELS_SWAP_BUFFER //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Buffer_H__ //
// - ------------------------------------------------------------------------------------------ - //
