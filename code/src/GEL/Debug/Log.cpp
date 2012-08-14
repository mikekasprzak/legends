// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef EMSCRIPTEN
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_LOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdarg.h>
// - ------------------------------------------------------------------------------------------ - //
extern int LogLevel;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef LOG_LEVEL
// - ------------------------------------------------------------------------------------------ - //
	int LogLevel = LOG_LEVEL;
// - ------------------------------------------------------------------------------------------ - //
#else // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //
	// Default level is 1, primary logging only //
	int LogLevel = 1;
// - ------------------------------------------------------------------------------------------ - //
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //

//#define FlushFunc fflush(0)
#define LOG_FUNC		vfprintf
#define LOG_FUNC2		fprintf
#define LOG_TARGET		stdout

// - ------------------------------------------------------------------------------------------ - //
int CurrentLogIndentation = 0;
// - ------------------------------------------------------------------------------------------ - //
void LogIndentation( int Count, const char Val = ' ' ) {
	if ( Count > 0 ) {	
		char s[Count+1];
		for ( int idx = 0; idx < Count; idx++ ) {
			s[idx] = Val;
		}
		s[Count] = 0;
		
		LOG_FUNC2( LOG_TARGET, s );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
void PreLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		LOG_FUNC2( LOG_TARGET, ANSI_BG_RED );
		LogIndentation( CurrentLogIndentation, '!' );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star+ //
			LOG_FUNC2( LOG_TARGET, ANSI_GREEN );
			LogIndentation( CurrentLogIndentation, '*' );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			LOG_FUNC2( LOG_TARGET, ANSI_YELLOW );
			LogIndentation( CurrentLogIndentation );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			LOG_FUNC2( LOG_TARGET, ANSI_MAGENTA );
			LogIndentation( CurrentLogIndentation, '>' );
		}
		else if ( s[0] == '+' ) {
			LogIndentation( CurrentLogIndentation );
			CurrentLogIndentation++;
		}
		else if ( s[0] == '-' ) {
			CurrentLogIndentation--;
			LogIndentation( CurrentLogIndentation );
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
			LOG_FUNC2( LOG_TARGET, ANSI_CYAN );
		}
	}
} 
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
void PostLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		LOG_FUNC2( LOG_TARGET, ANSI_NORMAL );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star //
			LOG_FUNC2( LOG_TARGET, ANSI_NORMAL );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			LOG_FUNC2( LOG_TARGET, ANSI_NORMAL );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			LOG_FUNC2( LOG_TARGET, ANSI_NORMAL );
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
			LOG_FUNC2( LOG_TARGET, ANSI_NORMAL );
		}
	}
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void LogAlways( const char* s, ... ) {
	PreLog( s );

	va_list vl;
	va_start( vl, s );
	LOG_FUNC( LOG_TARGET, s, vl );
	va_end( vl );
	
	PostLog( s );

	LOG_FUNC2( LOG_TARGET, (char*)"\n" );

#ifdef ALWAYS_FLUSH
	fflush(0);
#endif // ALWAYS_FLUSH
}
// - ------------------------------------------------------------------------------------------ - //
void _LogAlways( const char* s, ... ) {
	PreLog( s );

	va_list vl;
	va_start( vl, s );
	LOG_FUNC( LOG_TARGET, s, vl );
	va_end( vl );

	PostLog( s );
}
// - ------------------------------------------------------------------------------------------ - //
#define GEN_LOG_FUNCTION_CRLF( _NAME, _LEVEL ) \
	void _NAME( const char* s, ... ) { \
		if ( LogLevel >= _LEVEL ) { \
			PreLog( s ); \
			va_list vl; \
			va_start( vl, s ); \
			LOG_FUNC( LOG_TARGET, s, vl ); \
			va_end( vl ); \
			PostLog( s ); \
			LOG_FUNC2( LOG_TARGET, (char*)"\n" ); \
		} \
	}
// - ------------------------------------------------------------------------------------------ - //
#ifdef ALWAYS_FLUSH
// - ------------------------------------------------------------------------------------------ - //
#undef GEN_LOG_FUNCTION_CRLF
#define GEN_LOG_FUNCTION_CRLF( _NAME, _LEVEL ) \
	void _NAME( const char* s, ... ) { \
		if ( LogLevel >= _LEVEL ) { \
			PreLog( s ); \
			va_list vl; \
			va_start( vl, s ); \
			LOG_FUNC( LOG_TARGET, s, vl ); \
			va_end( vl ); \
			PostLog( s ); \
			LOG_FUNC2( LOG_TARGET, (char*)"\n" ); \
			fflush(0); \
		} \
	}
// - ------------------------------------------------------------------------------------------ - //
#endif // ALWAYS_FLUSH
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GEN_LOG_FUNCTION( _NAME, _LEVEL ) \
	void _NAME( const char* s, ... ) { \
		if ( LogLevel >= _LEVEL ) { \
			PreLog( s ); \
			va_list vl; \
			va_start( vl, s ); \
			LOG_FUNC( LOG_TARGET, s, vl ); \
			va_end( vl ); \
			PostLog( s ); \
		} \
	}
// - ------------------------------------------------------------------------------------------ - //
GEN_LOG_FUNCTION_CRLF( Log, 1 )
GEN_LOG_FUNCTION_CRLF( VLog, 2 )
GEN_LOG_FUNCTION_CRLF( VVLog, 3 )
GEN_LOG_FUNCTION_CRLF( VVVLog, 4 )
// - ------------------------------------------------------------------------------------------ - //
GEN_LOG_FUNCTION( _Log, 1 )
GEN_LOG_FUNCTION( _VLog, 2 )
GEN_LOG_FUNCTION( _VVLog, 3 )
GEN_LOG_FUNCTION( _VVVLog, 4 )
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
#endif // EMSCRIPTEN //
// - ------------------------------------------------------------------------------------------ - //
