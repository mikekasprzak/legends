// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_API_H__
#define __GEL_GRAPHICS_API_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/API.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL2/API.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_D3D9)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/D3D9/API.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_PSP)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/PSP/API.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_PS3)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/PS3/API.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WII)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/Wii/API.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_DSI)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/DSi/API.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_3DS)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/3DS/API.h"
// - ------------------------------------------------------------------------------------------ - //
#else // USES //
// - ------------------------------------------------------------------------------------------ - //
#error "No Native API"
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_API_H__ //
// - ------------------------------------------------------------------------------------------ - //