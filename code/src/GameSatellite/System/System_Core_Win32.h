// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_CORE_WIN32_H__
#define __GEL_SYSTEM_CORE_WIN32_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS
// - ------------------------------------------------------------------------------------------ - //
#include <windows.h>
#include <time.h>
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
typedef DWORD tick_t;

const time_t GetTime();
const char* GetTimeString();
const double GetTimeDiff( const time_t Start, const time_t End );
const char* GetTimeDiffString( const time_t Start, const time_t End );

const clock_t GetClock();
const double GetClockDiff( const clock_t Start, const clock_t End );
const char* GetClockDiffString( const clock_t Start, const clock_t End );

const char* GetDoubleTimeString( const double DTime );

const tick_t GetTick();
const int GetTickDiff( const tick_t Start, const tick_t End );
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_CORE_WIN32_H__ //
// - ------------------------------------------------------------------------------------------ - //
