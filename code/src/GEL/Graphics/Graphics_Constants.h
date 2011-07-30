// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Constants_H__
#define __GEL_Graphics_Constants_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL2/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_D3D9)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/D3D9/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_PSP)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/PSP/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_PS3)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/PS3/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WII)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/Wii/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_DSI)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/DSi/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_3DS)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/3DS/GELS_Constants.h"
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Constants_H__ //
// - ------------------------------------------------------------------------------------------ - //
