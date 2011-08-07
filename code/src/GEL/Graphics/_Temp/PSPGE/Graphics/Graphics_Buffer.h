// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Buffer_H__
#define __Graphics_Buffer_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetClearColor( const GelColor Color ) {
/*
	glClearColor( 
		((float)GEL_GET_R(Color)) * ( 1.0f / 255.0f ), 
		((float)GEL_GET_G(Color)) * ( 1.0f / 255.0f ), 
		((float)GEL_GET_B(Color)) * ( 1.0f / 255.0f ), 
		((float)GEL_GET_A(Color)) * ( 1.0f / 255.0f )
		);
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetColorMask( bool Red, bool Green, bool Blue, bool Alpha ) {
/*
	glColorMask( Red, Green, Blue, Alpha );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelClear( bool ColorBuffer = true, bool DepthBuffer = false, bool StencilBuffer = false ) {
/*	
	int ClearMask = 0;
	if ( ColorBuffer )
		ClearMask |= GL_COLOR_BUFFER_BIT;
	if ( DepthBuffer )
		ClearMask |= GL_DEPTH_BUFFER_BIT;
	if ( StencilBuffer )
		ClearMask |= GL_STENCIL_BUFFER_BIT;

	glClear( ClearMask );
*/
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableColorWriting() {
/*
	gelSetColorMask( true, true, true, true );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableColorWriting() {
/*
	gelSetColorMask( false, false, false, false );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelClearColor( const GelColor Color = GEL_RGB_BLACK ) {
/*
	gelSetClearColor( Color );
	gelClear( true );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSwapBuffer( ) {
#ifdef GELS_SWAPBUFFER
	gelsSwapBuffer();
#endif // GELS_SWAPBUFFER //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Buffer_H__ //
// - ------------------------------------------------------------------------------------------ - //
