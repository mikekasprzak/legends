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
#if defined(DEFAULT_LOG_LEVEL)
	int LogLevel = DEFAULT_LOG_LEVEL;
#elif defined(LOG_LEVEL)
	int LogLevel = LOG_LEVEL;
#else // LOG_LEVEL //
	int LogLevel = 1; // Default level is 1, primary logging only, but all levels are recorded //
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int CurrentLogIndentation = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_FLOGGING
// - ------------------------------------------------------------------------------------------ - //
// TODO: Curses support (meaning different calls and values to set colors) //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_CURSES
// - ------------------------------------------------------------------------------------------ - //
// Curses FLog Implimentation //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _WIN32
// - ------------------------------------------------------------------------------------------ - //
#undef MOUSE_MOVED
#include <curses.h>
// - ------------------------------------------------------------------------------------------ - //
#else // Linux //
// - ------------------------------------------------------------------------------------------ - //
#include <ncurses.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // _WIN32
// - ------------------------------------------------------------------------------------------ - //
WINDOW* FLOG_TARGET = 			0; // stdscr not initialized until init //
#define FLOG_FUNCV( ... )		vwprintw( FLOG_TARGET, __VA_ARGS__ )
#define FLOG_FUNC( ... )		wprintw( FLOG_TARGET, __VA_ARGS__ )
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogFlush() {
	refresh();
}
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_FLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void FLogColor( const int InColor ) {
	if ( InColor < 0 ) {
		standend();
	}
	else {
		int Color = InColor & 7;
		if ( Color == 0 )
			Color = 8;
	
		attrset( 
			COLOR_PAIR(Color) | 
			(((InColor & 15) > 7) ? A_BOLD : A_NORMAL) |
			((InColor > 15) ? A_REVERSE : A_NORMAL)
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
#else // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //
#define FLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void FLogInit( const char* ) {
	FLOG_TARGET = initscr();	// Default Init //

//	//raw();					// CTRL-Z and CTRL-C *DON'T* trigger signals //
//	cbreak();					// CTRL-Z and CTRL-C trigger signals //
//	//halfdelay(1);				// Calls to getch() return 'ERR' if no key pressed. Time in 10ths //
//	nodelay( stdscr, TRUE );	// Non-Blocking getch(). Returns 'ERR' if no key pressed //
//	keypad( stdscr, TRUE ); 	// Enable Arrow Keys, Function Keys, etc //
//	noecho();					// User input not displayed. "echo()" to display //

	start_color();				// Enable Color //

	init_pair( 1, COLOR_RED, 		COLOR_BLACK );
	init_pair( 2, COLOR_GREEN,		COLOR_BLACK );
	init_pair( 3, COLOR_YELLOW,		COLOR_BLACK );
	init_pair( 4, COLOR_BLUE,		COLOR_BLACK );
	init_pair( 5, COLOR_MAGENTA,	COLOR_BLACK );
	init_pair( 6, COLOR_CYAN,		COLOR_BLACK );
	init_pair( 7, COLOR_WHITE,		COLOR_BLACK );
	init_pair( 8, COLOR_BLACK, 		COLOR_BLACK );
}
// - ------------------------------------------------------------------------------------------ - //
inline void FLogExit() {	
	endwin();	// Shutdown Curses //
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_CURSES //
// - ------------------------------------------------------------------------------------------ - //
// Standard Output FLog Implimentation //
// - ------------------------------------------------------------------------------------------ - //
FILE* FLOG_TARGET = 			stdout;
#define FLOG_FUNCV( ... )		vfprintf( FLOG_TARGET, __VA_ARGS__ )
#define FLOG_FUNC( ... )		fprintf( FLOG_TARGET, __VA_ARGS__ )
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogFlush() {
	fflush( FLOG_TARGET );
}
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_FLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
#define ANSI_HEADER					"\033["

#define ANSI_NORMAL					"\033[0m"
#define ANSI_RESET					ANSI_NORMAL
#define ANSI_NEGATIVE				"\033[7m"

#define ANSI_BLACK					"\033[0;30m"
#define ANSI_RED					"\033[0;31m"
#define ANSI_GREEN					"\033[0;32m"
#define ANSI_BROWN					"\033[0;33m"
#define ANSI_BLUE					"\033[0;34m"
#define ANSI_MAGENTA				"\033[0;35m"
#define ANSI_CYAN					"\033[0;36m"
#define ANSI_LIGHT_GRAY				"\033[0;37m"
#define ANSI_DARK_GRAY				"\033[1;30m"
#define ANSI_LIGHT_RED				"\033[1;31m"
#define ANSI_LIGHT_GREEN			"\033[1;32m"
#define ANSI_YELLOW					"\033[1;33m"
#define ANSI_LIGHT_BLUE				"\033[1;34m"
#define ANSI_LIGHT_MAGENTA			"\033[1;35m"
#define ANSI_LIGHT_CYAN				"\033[1;36m"
#define ANSI_WHITE					"\033[1;37m"

#define ANSI_INV_BLACK				"\033[0;40m"
#define ANSI_INV_RED				"\033[0;41m"
#define ANSI_INV_GREEN				"\033[0;42m"
#define ANSI_INV_BROWN				"\033[0;43m"
#define ANSI_INV_BLUE				"\033[0;44m"
#define ANSI_INV_MAGENTA			"\033[0;45m"
#define ANSI_INV_CYAN				"\033[0;46m"
#define ANSI_INV_LIGHT_GRAY			"\033[0;47m"
#define ANSI_INV_DARK_GRAY			"\033[1;40m"
#define ANSI_INV_LIGHT_RED			"\033[1;41m"
#define ANSI_INV_LIGHT_GREEN		"\033[1;42m"
#define ANSI_INV_YELLOW				"\033[1;43m"
#define ANSI_INV_LIGHT_BLUE			"\033[1;44m"
#define ANSI_INV_LIGHT_MAGENTA		"\033[1;45m"
#define ANSI_INV_LIGHT_CYAN			"\033[1;46m"
#define ANSI_INV_WHITE				"\033[1;47m"
// - ------------------------------------------------------------------------------------------ - //
const char* const ANSIColorTable[] = {
	ANSI_BLACK,
	ANSI_RED,
	ANSI_GREEN,
	ANSI_BROWN,
	ANSI_BLUE,
	ANSI_MAGENTA,
	ANSI_CYAN,
	ANSI_LIGHT_GRAY,
	ANSI_DARK_GRAY,
	ANSI_LIGHT_RED,
	ANSI_LIGHT_GREEN,
	ANSI_YELLOW,
	ANSI_LIGHT_BLUE,
	ANSI_LIGHT_MAGENTA,
	ANSI_LIGHT_CYAN,
	ANSI_WHITE,
	
	ANSI_INV_BLACK,
	ANSI_INV_RED,
	ANSI_INV_GREEN,
	ANSI_INV_BROWN,
	ANSI_INV_BLUE,
	ANSI_INV_MAGENTA,
	ANSI_INV_CYAN,
	ANSI_INV_LIGHT_GRAY,
	ANSI_INV_DARK_GRAY,
	ANSI_INV_LIGHT_RED,
	ANSI_INV_LIGHT_GREEN,
	ANSI_INV_YELLOW,
	ANSI_INV_LIGHT_BLUE,
	ANSI_INV_LIGHT_MAGENTA,
	ANSI_INV_LIGHT_CYAN,
	ANSI_INV_WHITE
};
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogColor( const char* Color ) {
	// Only output color codes when the target is stdout (no color codes in text files) //
	if ( FLOG_TARGET == stdout )
		FLOG_FUNC( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void FLogColor( const int Color ) {
	if ( Color != LOG_NORMAL )
		_FLogColor( ANSIColorTable[ Color ] );
	else
		_FLogColor( ANSI_NORMAL );
}
// - ------------------------------------------------------------------------------------------ - //
#else // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //
#define FLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void FLogInit( const char* TargetFile ) {
	if ( TargetFile ) {
		FLOG_TARGET = fopen( TargetFile, "wb" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void FLogExit() {
	if ( FLOG_TARGET != stdout ) {
		fclose( FLOG_TARGET );
		FLOG_TARGET = stdout;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_CURSES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void FLogIndentation( int Count, const char Val = ' ' ) {
	if ( Count > 0 ) {
		char s[Count+1]; // MSVC may hate this
		for ( int idx = 0; idx < Count; idx++ ) {
			s[idx] = Val;
		}
		s[Count] = 0;

		FLOG_FUNC( s );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void FPreLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		FLogColor( LOG_INV_RED );
		FLogIndentation( CurrentLogIndentation, '!' );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star+ //
			FLogColor( LOG_GREEN );
			FLogIndentation( CurrentLogIndentation, '*' );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			FLogColor( LOG_YELLOW );
			FLogIndentation( CurrentLogIndentation );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			FLogColor( LOG_MAGENTA );
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
			FLogColor( LOG_CYAN );
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
		FLogColor( LOG_NORMAL );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star //
			FLogColor( LOG_NORMAL );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			FLogColor( LOG_NORMAL );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			FLogColor( LOG_NORMAL );
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
			FLogColor( LOG_NORMAL );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogAlways( const char* s, va_list vargs ) {
	FPreLog( s );
	FLOG_FUNCV( s, vargs );
	FPostLog( s );

	FLOG_FUNC( (char*)"\n" );

	_FLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void _FLogAlways( const char* s, va_list vargs ) {
	FPreLog( s );
	FLOG_FUNCV( s, vargs );
	FPostLog( s );
}
// - ------------------------------------------------------------------------------------------ - //
#else // NO_FLOGGING //
// - ------------------------------------------------------------------------------------------ - //
#define FLogAlways( ... ) ;
#define _FLogAlways( ... ) ;
#define _FLogFlush( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOGGING //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void LogColor( const int Color ) {
	FLogColor( Color );
}
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
// NOTE: vprintf style, so these can be nested inside new printf style functions //
// - ------------------------------------------------------------------------------------------ - //
void vLogAlways( const char* s, va_list vargs ) {
	FLogAlways( s, vargs );
//	MLogAlways( s, vargs );
}
// - ------------------------------------------------------------------------------------------ - //
void _vLogAlways( const char* s, va_list vargs ) {
	_FLogAlways( s, vargs );
//	_MLogAlways( s, vargs );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void LogFlush() {
	_FLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void LogExit() {
	LogFlush();
	
	FLogExit();
//	MLogExit();
}
// - ------------------------------------------------------------------------------------------ - //
void LogInit( const char* TargetFile ) {
	FLogInit( TargetFile );
//	MLogInit();

	atexit(LogExit);

	// Embedded LogLevel Test (since Log isn't available yet) //
	if ( LogLevel >= 1 ) {
		LogAlways( "-=- Logging Started - %i", 25);
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
