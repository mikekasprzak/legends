// - ------------------------------------------------------------------------------------------ - //
// GRAPHICS STENCIL - Stencil Buffer
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Stencil_H__
#define __GEL_Graphics_Stencil_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Graphics_Constants.h"
#include "Graphics_Buffer.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELS_Stencil.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetStencilMask( const int Mask = 0 ) {
#ifdef GELS_SET_STENCIL_MASK
	gels_SetStencilMask( Mask );
#endif // GELS_SET_STENCIL_MASK //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelClearStencil( const int Mask = 0 ) {
	gelSetStencilMask( Mask );
	gelClear( false, false, true );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Enable or Disable the Stencil Test (i.e. actually using the Stencil Buffer) //
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableStencilTest() {
#ifdef GELS_ENABLE_STENCIL_TEST
	gels_EnableStencilTest();
#endif // GELS_ENABLE_STENCIL_TEST //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableStencilTest() {
#ifdef GELS_DISABLE_STENCIL_TEST
	gels_DisableStencilTest();
#endif // GELS_DISABLE_STENCIL_TEST //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Advanced Stencil Operations //
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetStencilFunc( const int Func, const int Variable, const int Mask ) {
#ifdef GELS_SET_STENCIL_FUNC
	gels_SetStencilFunc( Func, Variable, Mask );
#endif // GELS_SET_STENCIL_FUNC //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetStencilOp( const int Fail, const int zFail, const int zPass ) {
#ifdef GELS_SET_STENCIL_OP
	gels_SetStencilOp( Fail, zFail, zPass );
#endif // GELS_SET_STENCIL_OP //
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Sometimes we want a simple stencil behavior, even though they can do so much more with them. //
// These functions Enable or Disable writing to the Stencil Buffer //
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableStencilWriting() {
	gelSetColorMask( false, false, false, false );
	gelSetStencilMask( 0xff );
	
	gelSetStencilOp( GEL_KEEP, GEL_KEEP, GEL_INCR );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableStencilWriting() {
	gelSetColorMask( true, true, true, true );
	gelSetStencilMask( 0 );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Does the system have a Stencil Buffer? //
// - ------------------------------------------------------------------------------------------ - //
inline bool gelHasStencil() {
	// TODO: If no stencil buffer available, make this fail //
	return true;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Stencil_H__ //
// - ------------------------------------------------------------------------------------------ - //
