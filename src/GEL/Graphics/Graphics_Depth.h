// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Depth_H__
#define __GEL_Graphics_Depth_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Graphics_Constants.h"
#include "Graphics_Buffer.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELS_Depth.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelClearDepth( ) {
	gelClear( false, true );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableDepthTest() {
#ifdef GELS_ENABLE_DEPTH_TEST
	gels_EnableDepthTest();
#endif // GELS_ENABLE_DEPTH_TEST //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableDepthTest() {
#ifdef GELS_DISABLE_DEPTH_TEST
	gels_DisableDepthTest();
#endif // GELS_DISABLE_DEPTH_TEST //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableDepthWriting() {
#ifdef GELS_ENABLE_DEPTH_WRITING
	gels_EnableDepthWriting();
#endif // GELS_ENABLE_DEPTH_WRITING //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableDepthWriting() {
#ifdef GELS_DISABLE_DEPTH_WRITING
	gels_DisableDepthWriting();
#endif // GELS_DISABLE_DEPTH_WRITING //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetDepthFunc( const int Func ) {
#ifdef GELS_SET_DEPTH_FUNC
	gels_SetDepthFunc( Func );
#endif // GELS_SET_DEPTH_FUNC //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetDepthRange( Real zNear, Real zFar ) {
#ifdef GELS_SET_DEPTH_RANGE
	gels_SetDepthRange( zNear, zFar );
#endif // GELS_SET_DEPTH_RANGE //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Does the system have a Depth Buffer? //
// - ------------------------------------------------------------------------------------------ - //
inline bool gelHasDepth() {
	// TODO: If no depth buffer available, make this fail //
	//return true;
	return System::DepthSize > 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Depth_H__ //
// - ------------------------------------------------------------------------------------------ - //
