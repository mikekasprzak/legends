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
// Defined inside System_Core.h //
//void TimeInit();
//void TimeExit();
// - ------------------------------------------------------------------------------------------ - //
// NOTE: May not be whole integer numbers per tick. clock_t preferred for math. //
const time_t GetTime();
const char* GetTimeString();
const double GetTimeDiff( const time_t Start, const time_t End );
const char* GetTimeDiffString( const time_t Start, const time_t End );
const char* GetTimeDiffShortString( const time_t Start, const time_t End );

// NOTE: clock_t you can do math on. Measured in fractions of a second (CLOCKS_PER_SEC) //
const clock_t GetClock();
const double GetClockSeconds();
const char* GetClockString();
const char* GetClockShortString();
const double GetClockDiff( const clock_t Start, const clock_t End );
const char* GetClockDiffString( const clock_t Start, const clock_t End );
const char* GetClockDiffShortString( const clock_t Start, const clock_t End );

const char* DoubleTimeToString( const double DTime );
const char* DoubleTimeToShortString( const double DTime );
// - ------------------------------------------------------------------------------------------ - //
// TODO: Move this to System_Core.h //
typedef unsigned long long int tick_t;	// On Windows, not a DWORD. I fix the DWORD bug. //

const tick_t GetTick();
const int GetTickDiff( const tick_t Start, const tick_t End );

inline const tick_t GetFirstTick() {
	extern tick_t FirstTick;
	return FirstTick;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_CORE_WIN32_H__ //
// - ------------------------------------------------------------------------------------------ - //
