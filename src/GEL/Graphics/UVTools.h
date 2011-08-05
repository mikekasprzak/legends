// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_UVTOOLS_H__
#define __GEL_GRAPHICS_UVTOOLS_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// - ------------------------------------------------------------------------------------------ - //
#include "UV.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Float Version //
// #define UV4(x,y) \
//	((x+0)*0.25f), ((y+0)*0.25f), \
//	((x+1)*0.25f), ((y+0)*0.25f), \
//	((x+0)*0.25f), ((y+1)*0.25f), \
//	((x+1)*0.25f), ((y+1)*0.25f) \
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// UV#, where # is the number of units wide/tall available.  0->#-1.  i.e. UV4 is 0-3. //
// - ------------------------------------------------------------------------------------------ - //
#define UV1(x,y) \
	((x+0)<<(UV_SHIFT-0))+UV_TOP, ((y+0)<<(UV_SHIFT-0))+UV_TOP, \
	((x+1)<<(UV_SHIFT-0))-UV_BOT, ((y+0)<<(UV_SHIFT-0))+UV_TOP, \
	((x+0)<<(UV_SHIFT-0))+UV_TOP, ((y+1)<<(UV_SHIFT-0))-UV_BOT, \
	((x+1)<<(UV_SHIFT-0))-UV_BOT, ((y+1)<<(UV_SHIFT-0))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV2(x,y) \
	((x+0)<<(UV_SHIFT-1))+UV_TOP, ((y+0)<<(UV_SHIFT-1))+UV_TOP, \
	((x+1)<<(UV_SHIFT-1))-UV_BOT, ((y+0)<<(UV_SHIFT-1))+UV_TOP, \
	((x+0)<<(UV_SHIFT-1))+UV_TOP, ((y+1)<<(UV_SHIFT-1))-UV_BOT, \
	((x+1)<<(UV_SHIFT-1))-UV_BOT, ((y+1)<<(UV_SHIFT-1))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV4(x,y) \
	((x+0)<<(UV_SHIFT-2))+UV_TOP, ((y+0)<<(UV_SHIFT-2))+UV_TOP, \
	((x+1)<<(UV_SHIFT-2))-UV_BOT, ((y+0)<<(UV_SHIFT-2))+UV_TOP, \
	((x+0)<<(UV_SHIFT-2))+UV_TOP, ((y+1)<<(UV_SHIFT-2))-UV_BOT, \
	((x+1)<<(UV_SHIFT-2))-UV_BOT, ((y+1)<<(UV_SHIFT-2))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV8(x,y) \
	((x+0)<<(UV_SHIFT-3))+UV_TOP, ((y+0)<<(UV_SHIFT-3))+UV_TOP, \
	((x+1)<<(UV_SHIFT-3))-UV_BOT, ((y+0)<<(UV_SHIFT-3))+UV_TOP, \
	((x+0)<<(UV_SHIFT-3))+UV_TOP, ((y+1)<<(UV_SHIFT-3))-UV_BOT, \
	((x+1)<<(UV_SHIFT-3))-UV_BOT, ((y+1)<<(UV_SHIFT-3))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV16(x,y) \
	((x+0)<<(UV_SHIFT-4))+UV_TOP, ((y+0)<<(UV_SHIFT-4))+UV_TOP, \
	((x+1)<<(UV_SHIFT-4))-UV_BOT, ((y+0)<<(UV_SHIFT-4))+UV_TOP, \
	((x+0)<<(UV_SHIFT-4))+UV_TOP, ((y+1)<<(UV_SHIFT-4))-UV_BOT, \
	((x+1)<<(UV_SHIFT-4))-UV_BOT, ((y+1)<<(UV_SHIFT-4))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV32(x,y) \
	((x+0)<<(UV_SHIFT-5))+UV_TOP, ((y+0)<<(UV_SHIFT-5))+UV_TOP, \
	((x+1)<<(UV_SHIFT-5))-UV_BOT, ((y+0)<<(UV_SHIFT-5))+UV_TOP, \
	((x+0)<<(UV_SHIFT-5))+UV_TOP, ((y+1)<<(UV_SHIFT-5))-UV_BOT, \
	((x+1)<<(UV_SHIFT-5))-UV_BOT, ((y+1)<<(UV_SHIFT-5))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV64(x,y) \
	((x+0)<<(UV_SHIFT-6))+UV_TOP, ((y+0)<<(UV_SHIFT-6))+UV_TOP, \
	((x+1)<<(UV_SHIFT-6))-UV_BOT, ((y+0)<<(UV_SHIFT-6))+UV_TOP, \
	((x+0)<<(UV_SHIFT-6))+UV_TOP, ((y+1)<<(UV_SHIFT-6))-UV_BOT, \
	((x+1)<<(UV_SHIFT-6))-UV_BOT, ((y+1)<<(UV_SHIFT-6))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// UV#, where # is the number of units wide/tall available.  0->#-1.  i.e. UV4 is 0-3. //
// - ------------------------------------------------------------------------------------------ - //
#define UV1R(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-0))+UV_TOP, ((y1)<<(UV_SHIFT-0))+UV_TOP, \
	((x2)<<(UV_SHIFT-0))-UV_BOT, ((y1)<<(UV_SHIFT-0))+UV_TOP, \
	((x1)<<(UV_SHIFT-0))+UV_TOP, ((y2)<<(UV_SHIFT-0))-UV_BOT, \
	((x2)<<(UV_SHIFT-0))-UV_BOT, ((y2)<<(UV_SHIFT-0))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV2R(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-1))+UV_TOP, ((y1)<<(UV_SHIFT-1))+UV_TOP, \
	((x2)<<(UV_SHIFT-1))-UV_BOT, ((y1)<<(UV_SHIFT-1))+UV_TOP, \
	((x1)<<(UV_SHIFT-1))+UV_TOP, ((y2)<<(UV_SHIFT-1))-UV_BOT, \
	((x2)<<(UV_SHIFT-1))-UV_BOT, ((y2)<<(UV_SHIFT-1))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV4R(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-2))+UV_TOP, ((y1)<<(UV_SHIFT-2))+UV_TOP, \
	((x2)<<(UV_SHIFT-2))-UV_BOT, ((y1)<<(UV_SHIFT-2))+UV_TOP, \
	((x1)<<(UV_SHIFT-2))+UV_TOP, ((y2)<<(UV_SHIFT-2))-UV_BOT, \
	((x2)<<(UV_SHIFT-2))-UV_BOT, ((y2)<<(UV_SHIFT-2))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV8R(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-3))+UV_TOP, ((y1)<<(UV_SHIFT-3))+UV_TOP, \
	((x2)<<(UV_SHIFT-3))-UV_BOT, ((y1)<<(UV_SHIFT-3))+UV_TOP, \
	((x1)<<(UV_SHIFT-3))+UV_TOP, ((y2)<<(UV_SHIFT-3))-UV_BOT, \
	((x2)<<(UV_SHIFT-3))-UV_BOT, ((y2)<<(UV_SHIFT-3))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV16R(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-4))+UV_TOP, ((y1)<<(UV_SHIFT-4))+UV_TOP, \
	((x2)<<(UV_SHIFT-4))-UV_BOT, ((y1)<<(UV_SHIFT-4))+UV_TOP, \
	((x1)<<(UV_SHIFT-4))+UV_TOP, ((y2)<<(UV_SHIFT-4))-UV_BOT, \
	((x2)<<(UV_SHIFT-4))-UV_BOT, ((y2)<<(UV_SHIFT-4))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV32R(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y2)<<(UV_SHIFT-5))-UV_BOT, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y2)<<(UV_SHIFT-5))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV64R(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-6))+UV_TOP, ((y1)<<(UV_SHIFT-6))+UV_TOP, \
	((x2)<<(UV_SHIFT-6))-UV_BOT, ((y1)<<(UV_SHIFT-6))+UV_TOP, \
	((x1)<<(UV_SHIFT-6))+UV_TOP, ((y2)<<(UV_SHIFT-6))-UV_BOT, \
	((x2)<<(UV_SHIFT-6))-UV_BOT, ((y2)<<(UV_SHIFT-6))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define UV32R_0(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y2)<<(UV_SHIFT-5))-UV_BOT, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y2)<<(UV_SHIFT-5))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //
#define UV32R_1(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y2)<<(UV_SHIFT-5))-UV_BOT, \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y2)<<(UV_SHIFT-5))-UV_BOT, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y1)<<(UV_SHIFT-5))+UV_TOP \
// - ------------------------------------------------------------------------------------------ - //
#define UV32R_2(x1,y1,x2,y2) \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y2)<<(UV_SHIFT-5))-UV_BOT, \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y2)<<(UV_SHIFT-5))-UV_BOT, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y1)<<(UV_SHIFT-5))+UV_TOP \
// - ------------------------------------------------------------------------------------------ - //
#define UV32R_3(x1,y1,x2,y2) \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x2)<<(UV_SHIFT-5))-UV_BOT, ((y2)<<(UV_SHIFT-5))-UV_BOT, \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y1)<<(UV_SHIFT-5))+UV_TOP, \
	((x1)<<(UV_SHIFT-5))+UV_TOP, ((y2)<<(UV_SHIFT-5))-UV_BOT \
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define UV16RR(x1,y1,x2,y2) \
	((x1)<<(UV_SHIFT-4))+UV_TOPR, ((y1)<<(UV_SHIFT-4))+UV_TOPR, \
	((x2)<<(UV_SHIFT-4))-UV_BOTR, ((y1)<<(UV_SHIFT-4))+UV_TOPR, \
	((x1)<<(UV_SHIFT-4))+UV_TOPR, ((y2)<<(UV_SHIFT-4))-UV_BOTR, \
	((x2)<<(UV_SHIFT-4))-UV_BOTR, ((y2)<<(UV_SHIFT-4))-UV_BOTR \
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_UVTOOLS__ //
// - ------------------------------------------------------------------------------------------ - //