// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS
// - ------------------------------------------------------------------------------------------ - //
#include <windows.h>	// timeGetTime //
#include <time.h>		// time, time_t //
// - ------------------------------------------------------------------------------------------ - //
#include "System_Core_Win32.h"
#include <Util/safe_sprintf.h>
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
// http://www.cplusplus.com/reference/ctime/
// - ------------------------------------------------------------------------------------------ - //
// Time since the epoch //
const time_t GetTime() {
	return time(NULL);
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetTimeString() {
	time_t CurTime = GetTime();
	// WARNING: ctime shares a buffer with asctime. new calls erase it. //
	return ctime( &CurTime );
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Diference in Seconds //
const double GetTimeDiff( const time_t Start, const time_t End ) {
	// NOTE: TBH, I have no idea why there is a C std library function, when I could just subtract.
	return difftime( End, Start );
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Diference in Seconds //
const char* GetTimeDiffString( const time_t Start, const time_t End ) {
	return DoubleTimeToString( GetTimeDiff( End, Start ) );
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Diference in Seconds //
const char* GetTimeDiffShortString( const time_t Start, const time_t End ) {
	return DoubleTimeToShortString( GetTimeDiff( End, Start ) );
}
// - ------------------------------------------------------------------------------------------ - //
// Time since program start //
const clock_t GetClock() {
	return clock();
}
// - ------------------------------------------------------------------------------------------ - //
const double GetClockSeconds() {
	return (double)GetClock() / (double)CLOCKS_PER_SEC;
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetClockString() {
	return DoubleTimeToString( GetClockSeconds() );
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetClockShortString() {
	return DoubleTimeToShortString( GetClockSeconds() );
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Difference in Seconds //
const double GetClockDiff( const clock_t Start, const clock_t End ) {
	return (double)(End-Start) / (double)CLOCKS_PER_SEC;
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Difference in Seconds //
const char* GetClockDiffString( const clock_t Start, const clock_t End ) {
	return DoubleTimeToString( GetClockDiff( End, Start ) );
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Difference in Seconds //
const char* GetClockDiffShortString( const clock_t Start, const clock_t End ) {
	return DoubleTimeToShortString( GetClockDiff( End, Start ) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Returns Time Diference in Seconds //
const char* DoubleTimeToString( const double DTime ) {
	// WARNING: Static buffer here. Will be erased after each call. //
	static char OutString[64];
	double Diff = DTime;
	
	int Seconds = (int)Diff % 60;
	Diff /= 60;
	int Minutes = (int)Diff % 60;
	Diff /= 60;
	int Hours = (int)Diff % 24;
	Diff /= 24;
	int Days = (int)Diff;

	if ( Days ) {
		safe_sprintf( OutString, sizeof(OutString), "%i %s, %i %s, %i %s, %i %s" ,
			Days, (Days == 1) ? "day" : "days",
			Hours, (Hours == 1) ? "hour" : "hours",
			Minutes, (Minutes == 1) ? "minute" : "minutes",
			Seconds, (Seconds == 1) ? "second" : "seconds"
		);
	}
	else if ( Hours ) {
		safe_sprintf( OutString, sizeof(OutString), "%i %s, %i %s, %i %s" ,
			Hours, (Hours == 1) ? "hour" : "hours",
			Minutes, (Minutes == 1) ? "minute" : "minutes",
			Seconds, (Seconds == 1) ? "second" : "seconds"
		);
	}
	else if ( Minutes ) {
		safe_sprintf( OutString, sizeof(OutString), "%i %s, %i %s" ,
			Minutes, (Minutes == 1) ? "minute" : "minutes",
			Seconds, (Seconds == 1) ? "second" : "seconds"
		);
	}
	else {
		safe_sprintf( OutString, sizeof(OutString), "%i %s" ,
			Seconds, (Seconds == 1) ? "second" : "seconds"
		);
	}
	return OutString;
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Diference in Seconds //
const char* DoubleTimeToShortString( const double DTime ) {
	// WARNING: Static buffer here. Will be erased after each call. //
	static char OutString[32];
	double Diff = DTime;
	
	int Seconds = (int)Diff % 60;
	Diff /= 60;
	int Minutes = (int)Diff % 60;
	Diff /= 60;
	int Hours = (int)Diff;

	safe_sprintf( OutString, sizeof(OutString), "%i:%02i:%02i",
		Hours,
		Minutes,
		Seconds
	);
	return OutString;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Fixed version of timeGetTime
// - ------------------------------------------------------------------------------------------ - //
inline const DWORD timeGetTime32() {
	// WARNING: Wraps every 49 days! Time in MS since the computer started! //
	return timeGetTime();
}
// - ------------------------------------------------------------------------------------------ - //
// tick_t defined inside header (System_Core_Win32.h) //
// - ------------------------------------------------------------------------------------------ - //
const tick_t timeGetTime64() {
	static tick_t TickBase = 0ULL;
	static DWORD LastTick = timeGetTime32();
	DWORD ThisTick = timeGetTime32();
	if ( ThisTick < LastTick ) {
		TickBase += 1ULL << 32;
	}
	LastTick = ThisTick;
	return TickBase + (tick_t)ThisTick;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern tick_t FirstTick;
tick_t FirstTick = 0ULL;	// The value of the very first tick, to give us better uptime figures //
// - ------------------------------------------------------------------------------------------ - //
void TimeInit() {
	FirstTick = GetTick();
}
// - ------------------------------------------------------------------------------------------ - //
void TimeExit() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const tick_t GetTick() {
	return timeGetTime64() - FirstTick;
}
// - ------------------------------------------------------------------------------------------ - //
// Returns Time Difference in 1000ths of a Second //
const int GetTickDiff( const tick_t Start, const tick_t End ) {
	return (int)(End - Start);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS //
// - ------------------------------------------------------------------------------------------ - //
