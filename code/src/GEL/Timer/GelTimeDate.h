// -------------------------------------------------------------------------- //
#ifndef __GEL_GELTIMEDATE_H__
#define __GEL_GELTIMEDATE_H__
// -------------------------------------------------------------------------- //
// NOTES: An INT isn't large enough to hold Time (in second), Date, and Year //
//   That is why Unix Time uses the Epoc (1970's). //
// -------------------------------------------------------------------------- //
// To make this fit, you need to remove seconds. //
// Or a better solution would be to store both Time and Date separately. //
// i.e. a make GelTimeDate a struct containing one of each, and add operators //
// -------------------------------------------------------------------------- //
/*
// Code for testing time, either current, file time, or hardcoded //
// NOTE: Unlike GelDate's and GelTime's, GelTimeDate's are NOT human readable. //
// -------------------------------------------------------------------------- //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
#include "time.h"
// -------------------------------------------------------------------------- //
typedef unsigned int GelTimeDate;
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Gets the Current Time //
// -------------------------------------------------------------------------- //
inline GelTimeDate get_GelTimeDate() {
	char Buffer[16];
	time_t RawTime;
	tm* TimeInfo;
	
	time( &RawTime );
	TimeInfo = localtime( &RawTime );
	
	// 24*60*60 is 86400, less than 100,000 //
	strftime( Buffer, sizeof(Buffer), "%S", TimeInfo );	
	int CurrentTime = atoi(Buffer);
	strftime( Buffer, sizeof(Buffer), "%M", TimeInfo );	
	CurrentTime += atoi(Buffer) * 60;
	strftime( Buffer, sizeof(Buffer), "%H", TimeInfo );	
	CurrentTime += atoi(Buffer) * 60 * 60;
	
	// 12*31 is 372, less than 1000 //
	strftime( Buffer, sizeof(Buffer), "%d", TimeInfo );	
	int CurrentDay = atoi(Buffer);
	strftime( Buffer, sizeof(Buffer), "%m", TimeInfo );	
	CurrentDay += atoi(Buffer) * 31;
	
	strftime( Buffer, sizeof(Buffer), "%Y", TimeInfo );	
	int CurrentYear = atoi(Buffer);
	
	GelTimeDate Now = CurrentTime;
	Now += CurrentDay * 100000;
	Now += CurrentYear * 100000 * 1000;
	
	return Now;
}
// -------------------------------------------------------------------------- //
//inline GelTime new_GelTime( const unsigned int Hour, const unsigned int Minute, const unsigned int Second ) {
//	GelTime CurrentTime;
//	
//	CurrentTime = Hour * 10000;
//	CurrentTime += Minute * 100;
//	CurrentTime += Second;
//	
//	return CurrentTime;	
//}
// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //
inline unsigned int get_Year_GelTimeDate( const GelTimeDate Value ) {
	return Value / (100000 * 1000);
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Date_GelTimeDate( const GelTimeDate Value ) {
	// NOTE: This includes year //
	return Value / 100000;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Time_GelTimeDate( const GelTimeDate Value ) {
	return Value % 100000;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
inline unsigned int get_Day_GelTimeDate( const GelTimeDate Value ) {
	return Value % 100;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Month_GelTimeDate( const GelTimeDate Value ) {
	return (Value / 100) % 100;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
inline unsigned int get_Hour_GelTimeDate( const GelTimeDate Value ) {
	return Value / 10000;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Minute_GelTimeDate( const GelTimeDate Value ) {
	return (Value / 100) % 100;
}
// -------------------------------------------------------------------------- //
inline unsigned int get_Second_GelTimeDate( const GelTimeDate Value ) {
	return Value % 100;
}
// -------------------------------------------------------------------------- //
*/
// -------------------------------------------------------------------------- //
#endif // __GEL_GELTIMEDATE_H__ //
// -------------------------------------------------------------------------- //
