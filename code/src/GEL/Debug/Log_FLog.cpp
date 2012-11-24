// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
#include "Log_FLog.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_FLOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern int CurrentLogIndentation;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_CURSES
// - ------------------------------------------------------------------------------------------ - //
// Curses FLog Implimentation //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _WIN32
	#undef MOUSE_MOVED
	#include <curses.h>
#else // Linux //
	#include <ncurses.h>
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

// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_FLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogColor( const int InColor ) {
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
#define _FLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogInit( const char* ) {
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
void FLogExit() {	
	endwin();	// Shutdown Curses //
}
// - ------------------------------------------------------------------------------------------ - //

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
inline void __FLogColor( const char* ColorString ) {
	// Only output color codes when the target is stdout (no color codes in text files) //
	if ( FLOG_TARGET == stdout )
		FLOG_FUNC( ColorString );
}
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogColor( const int Color ) {
	if ( Color >= 0 )
		__FLogColor( ANSIColorTable[ Color ] );
	else
		__FLogColor( ANSI_NORMAL );
}
// - ------------------------------------------------------------------------------------------ - //
#else // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //
#define _FLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogInit( const char* TargetFile ) {
	if ( TargetFile ) {
		FLOG_TARGET = fopen( TargetFile, "wb" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FLogExit() {
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
	enum {
		INDENTATION_MAX = 128
	};
	
	if ( Count > 0 ) {
		char s[INDENTATION_MAX];
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
		_FLogColor( LOG_INV_RED );
		FLogIndentation( CurrentLogIndentation, '!' );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star+ //
			_FLogColor( LOG_GREEN );
			FLogIndentation( CurrentLogIndentation, '*' );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			_FLogColor( LOG_YELLOW );
			FLogIndentation( CurrentLogIndentation );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_FLogColor( LOG_MAGENTA );
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
			_FLogColor( LOG_CYAN );
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
		_FLogColor( LOG_NORMAL );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star //
			_FLogColor( LOG_NORMAL );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			_FLogColor( LOG_NORMAL );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_FLogColor( LOG_NORMAL );
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
			_FLogColor( LOG_NORMAL );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef NO_FLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
void FLogColor( const int InColor ) {
	_FLogColor( InColor );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogFlush() {
	_FLogFlush();
}
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


// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOGGING //
// - ------------------------------------------------------------------------------------------ - //
