// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
#include "Log_MLog.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_MLOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern int CurrentLogIndentation;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Memory Log Implimentation //
// - ------------------------------------------------------------------------------------------ - //
FILE* MLOG_TARGET = 			stdout;
#define MLOG_FUNCV( ... )		vfprintf( MLOG_TARGET, __VA_ARGS__ )
#define MLOG_FUNC( ... )		fprintf( MLOG_TARGET, __VA_ARGS__ )
// - ------------------------------------------------------------------------------------------ - //
inline void _MLogFlush() {
	fflush( MLOG_TARGET );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_MLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void _MLogColor( const int Color ) {
}
// - ------------------------------------------------------------------------------------------ - //
#else // NO_MLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //
#define _MLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_MLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void MLogInit() {
}
// - ------------------------------------------------------------------------------------------ - //
void MLogExit() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void MLogIndentation( int Count, const char Val = ' ' ) {
	enum {
		INDENTATION_MAX = 128
	};
	
	if ( Count > 0 ) {
		char s[INDENTATION_MAX];
		for ( int idx = 0; idx < Count; idx++ ) {
			s[idx] = Val;
		}
		s[Count] = 0;

		MLOG_FUNC( s );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void MPreLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		_MLogColor( LOG_INV_RED );
		MLogIndentation( CurrentLogIndentation, '!' );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star+ //
			_MLogColor( LOG_GREEN );
			MLogIndentation( CurrentLogIndentation, '*' );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			_MLogColor( LOG_YELLOW );
			MLogIndentation( CurrentLogIndentation );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_MLogColor( LOG_MAGENTA );
			MLogIndentation( CurrentLogIndentation, '>' );
		}
		else if ( s[0] == '+' ) {
			MLogIndentation( CurrentLogIndentation );
			CurrentLogIndentation++;
		}
		else if ( s[0] == '-' ) {
			CurrentLogIndentation--;
			MLogIndentation( CurrentLogIndentation );
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
			_MLogColor( LOG_CYAN );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void MPostLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		_MLogColor( LOG_NORMAL );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star //
			_MLogColor( LOG_NORMAL );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			_MLogColor( LOG_NORMAL );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_MLogColor( LOG_NORMAL );
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
			_MLogColor( LOG_NORMAL );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef NO_MLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
void MLogColor( const int InColor ) {
	_MLogColor( InColor );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_MLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void MLogFlush() {
	_MLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void MLogAlways( const char* s, va_list vargs ) {
	MPreLog( s );
	MLOG_FUNCV( s, vargs );
	MPostLog( s );

	MLOG_FUNC( (char*)"\n" );

	_MLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void _MLogAlways( const char* s, va_list vargs ) {
	MPreLog( s );
	MLOG_FUNCV( s, vargs );
	MPostLog( s );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // NO_MLOGGING //
// - ------------------------------------------------------------------------------------------ - //
