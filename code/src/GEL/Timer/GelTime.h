// -------------------------------------------------------------------------- //
#ifndef __GEL_GELTIME_H__
#define __GEL_GELTIME_H__
// -------------------------------------------------------------------------- //
// Code for testing time, either current, file time, or hardcoded //
// NOTE: GelDate's and GelTime's are human readable, unlike GelTimeDate's. //
// -------------------------------------------------------------------------- //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
#include <stdlib.h>
#include <time.h>
// -------------------------------------------------------------------------- //
typedef unsigned int GelTime;
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Gets the Current Time //
// -------------------------------------------------------------------------- //
inline GelTime get_GelTime() {
	char Buffer[80];
	time_t RawTime;
	tm* TimeInfo;
	
	time( &RawTime );
	TimeInfo = localtime( &RawTime );
	
	strftime( Buffer, sizeof(Buffer), "%H%M%S", TimeInfo );
	
	GelTime CurrentTime = (GelTime)atoi(Buffer);
	return CurrentTime;
}
// -------------------------------------------------------------------------- //
inline GelTime new_GelTime( const unsigned int Hour, const unsigned int Minute, const unsigned int Second = 0 ) {
	GelTime CurrentTime;
	
	CurrentTime = Hour * 10000;
	CurrentTime += Minute * 100;
	CurrentTime += Second;
	
	return CurrentTime;	
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
inline unsigned int get_Hour_GelTime( const GelTime _Time ) {
	return _Time / 10000;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Minute_GelTime( const GelTime _Time ) {
	return (_Time / 100) % 100;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Second_GelTime( const GelTime _Time ) {
	return _Time % 100;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
#endif // __GEL_GELTIME_H__ //
// -------------------------------------------------------------------------- //
