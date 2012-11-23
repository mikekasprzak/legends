// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_LOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <vector>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef LOG_LEVEL
// - ------------------------------------------------------------------------------------------ - //
	int LogLevel = LOG_LEVEL;
// - ------------------------------------------------------------------------------------------ - //
#else // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
	int LogLevel = 1; // Default level is 1, primary logging only //
// - ------------------------------------------------------------------------------------------ - //
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //

#define LOG_FUNCV		vfprintf
#define LOG_FUNC		fprintf
FILE* LOG_TARGET = 		stdout;

// - ------------------------------------------------------------------------------------------ - //
inline void _FLogFlush() {
	fflush( LOG_TARGET );
}
// - ------------------------------------------------------------------------------------------ - //
void FLogFlush() {
	_FLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int CurrentLogIndentation = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void FLogColor( const char* Color ) {
	LOG_FUNC( LOG_TARGET, Color );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void FLogIndentation( int Count, const char Val = ' ' ) {
	if ( Count > 0 ) {	
		char s[Count+1]; // MSVC may hate this
		for ( int idx = 0; idx < Count; idx++ ) {
			s[idx] = Val;
		}
		s[Count] = 0;
		
		LOG_FUNC( LOG_TARGET, "%s", s );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void FPreLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		FLogColor( ANSI_BG_RED );
		FLogIndentation( CurrentLogIndentation, '!' );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star+ //
			FLogColor( ANSI_GREEN );
			FLogIndentation( CurrentLogIndentation, '*' );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			FLogColor( ANSI_YELLOW );
			FLogIndentation( CurrentLogIndentation );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			FLogColor( ANSI_MAGENTA );
			FLogIndentation( CurrentLogIndentation, '>' );
		}
		else if ( s[0] == '+' ) {
			FLogIndentation( CurrentLogIndentation );
			CurrentLogIndentation++;
		}
		else if ( s[0] == '-' ) {
			CurrentLogIndentation--;
			FLogIndentation( CurrentLogIndentation );
		}
	}
	else if ( s[1] == 0 ) {
		return;
	}
	else if ( s[2] == 0 ) {
		return;
	}
	else if ( s[0] == '-' ) {
		if ( s[1] == '=' ) {
			// Headline //
			FLogColor( ANSI_CYAN );
		}
	}
} 
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void FPostLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		FLogColor( ANSI_NORMAL );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star //
			FLogColor( ANSI_NORMAL );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			FLogColor( ANSI_NORMAL );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			FLogColor( ANSI_NORMAL );
		}
		else if ( s[0] == '+' ) {
		}
		else if ( s[0] == '-' ) {
		}
	}
	else if ( s[1] == 0 ) {
		return;
	}
	else if ( s[2] == 0 ) {
		return;
	}
	else if ( s[0] == '-' ) {
		if ( s[1] == '=' ) {
			// Headline //
			FLogColor( ANSI_NORMAL );
		}
	}
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogAlways( const char* s, va_list vargs ) {
	FPreLog( s );
	LOG_FUNCV( LOG_TARGET, s, vargs );
	FPostLog( s );

	LOG_FUNC( LOG_TARGET, (char*)"\n" );

	_FLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void _FLogAlways( const char* s, va_list vargs ) {
	FPreLog( s );
	LOG_FUNCV( LOG_TARGET, s, vargs );
	FPostLog( s );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void LogAlways( const char* s, ... ) {
	va_list vargs;
	va_start( vargs, s );
	FLogAlways( s, vargs );
//	MLogAlways( s, vargs );
	va_end( vargs );
}
// - ------------------------------------------------------------------------------------------ - //
void _LogAlways( const char* s, ... ) {
	va_list vargs;
	va_start( vargs, s );
	_FLogAlways( s, vargs );
//	_MLogAlways( s, vargs );
	va_end( vargs );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void LogExit() {
}
// - ------------------------------------------------------------------------------------------ - //
void LogInit() {
	// open a file and set LOG_TARGET equal to that //	

	atexit(LogExit);
	
	// Embedded LogLevel Test (since Log isn't available yet) //
	if ( LogLevel >= 1 ) {
		LogAlways( "-=- Logging Started - %i", 25);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void LogFlush() {
	_FLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
