// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SAFE_SPRINTF_H__
#define __GEL_SAFE_SPRINTF_H__
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //
#ifndef safe_sprintf
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
// NOTE: Returns negative on not enough room //
#define safe_sprintf sprintf_s
#define safe_vsprintf vsprintf_s
#else // _MSC_VER
// NOTE: Returns a value >= to size on not enough room (but only writes to available room) //
#define safe_sprintf snprintf
#define safe_vsprintf vsnprintf
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#endif // safe_sprintf //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SAFE_SPRINTF_H__ //
// - ------------------------------------------------------------------------------------------ - //
