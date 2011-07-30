// -------------------------------------------------------------------------- //
#ifndef __GEL_TIMER_FUNCTIONS_H__
#define __GEL_TIMER_FUNCTIONS_H__
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
TIMEVALUE GetTimeNow();
TIMEVALUE AddTime( TIMEVALUE a, TIMEVALUE b );
TIMEVALUE SubtractTime( TIMEVALUE a, TIMEVALUE b );

void SetFramesPerSecond( const int Ticks );
int GetFrames( TIMEVALUE* tv );
void AddFrame( TIMEVALUE* tv );
void ResetTime();

void Wait( const int Ticks );
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
#endif // __GEL_TIMER_FUNCTIONS_H__ //
// -------------------------------------------------------------------------- //
