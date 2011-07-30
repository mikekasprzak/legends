// -------------------------------------------------------------------------- //
#ifndef __GEL_GELDATE_H__
#define __GEL_GELDATE_H__
// -------------------------------------------------------------------------- //
// Code for testing dates, either current, file dates, or hardcoded //
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
typedef unsigned int GelDate;
// -------------------------------------------------------------------------- //
// Constants for the current month //
// -------------------------------------------------------------------------- //
enum {
	GEL_JANUARY = 1,
	GEL_FEBRUARY,
	GEL_MARCH,
	GEL_APRIL,
	GEL_MAY,
	GEL_JUNE,
	GEL_JULY,
	GEL_AUGUST,
	GEL_SEPTEMBER,
	GEL_OCTOBER,
	GEL_NOVEMBER,
	GEL_DECEMBER,
};
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Gets the Current Date //
// -------------------------------------------------------------------------- //
inline GelDate get_GelDate() {
	char Buffer[80];
	time_t RawTime;
	tm* TimeInfo;
	
	time( &RawTime );
	TimeInfo = localtime( &RawTime );
	
	strftime( Buffer, sizeof(Buffer), "%Y%m%d", TimeInfo );
	
	GelDate CurrentDate = (GelDate)atoi(Buffer);
	return CurrentDate;
}
// -------------------------------------------------------------------------- //
inline GelDate new_GelDate( const unsigned int Month, const unsigned int Day, const unsigned int Year ) {
	GelDate CurrentDate;
	
	CurrentDate = Year * 10000;
	// NOTE: I tried |'ing these values at first, and that didn't work (for some reason) //
	CurrentDate += Month * 100;
	CurrentDate += Day;
	
	return CurrentDate;	
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
inline unsigned int get_Day_GelDate( const GelDate _Date ) {
	return _Date % 100;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Month_GelDate( const GelDate _Date ) {
	return (_Date / 100) % 100;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Year_GelDate( const GelDate _Date ) {
	return _Date / 10000;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
#endif // __GEL_GELDATE_H__ //
// -------------------------------------------------------------------------- //
