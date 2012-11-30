// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_LOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Log_FLog.h"
#include "Log_MLog.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(DEFAULT_LOG_LEVEL)
	int LogLevel = DEFAULT_LOG_LEVEL;
#elif defined(LOG_LEVEL)
	int LogLevel = LOG_LEVEL;
#else // LOG_LEVEL //
	int LogLevel = 1; // Default level is 1, primary logging only, but all levels are recorded //
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void LogColor( const int Color ) {
	FLogColor( Color );
	MLogColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
void LogAlways( const char* s, ... ) {
	va_list vargs;
	va_start( vargs, s );
	FLogAlways( s, vargs );
	MLogAlways( s, vargs );
	va_end( vargs );
}
// - ------------------------------------------------------------------------------------------ - //
void _LogAlways( const char* s, ... ) {
	va_list vargs;
	va_start( vargs, s );
	_FLogAlways( s, vargs );
	_MLogAlways( s, vargs );
	va_end( vargs );
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: vprintf style, so these can be nested inside new printf style functions //
// - ------------------------------------------------------------------------------------------ - //
void vLogAlways( const char* s, va_list vargs ) {
	FLogAlways( s, vargs );
	MLogAlways( s, vargs );
}
// - ------------------------------------------------------------------------------------------ - //
void _vLogAlways( const char* s, va_list vargs ) {
	_FLogAlways( s, vargs );
	_MLogAlways( s, vargs );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void LogFlush() {
	FLogFlush();
	MLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void LogExit() {
	// Flush //
	LogFlush();
	
	// Exit //
	FLogExit();
	MLogExit();
}
// - ------------------------------------------------------------------------------------------ - //
#include <time.h>
// - ------------------------------------------------------------------------------------------ - //
void LogInit( const char* TargetFile ) {
	FLogInit( TargetFile );
	MLogInit();

	atexit(LogExit);

	// Embedded LogLevel Test (since Log isn't available... yet) //
	if ( LogLevel >= 1 ) {
		time_t rawtime;
		struct tm* timeinfo;
		
		time( &rawtime );
		timeinfo = localtime( &rawtime );
		
		// asctime adds a "\n" //
		_LogAlways( "-=- Logging Started - %s", asctime(timeinfo) );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
