// - ------------------------------------------------------------------------------------------ - //
#include "Out.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _WIN32
// - ------------------------------------------------------------------------------------------ - //
#include <curses.h>
// - ------------------------------------------------------------------------------------------ - //
#else // Linux //
// - ------------------------------------------------------------------------------------------ - //
#include <ncurses.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // _WIN32
// - ------------------------------------------------------------------------------------------ - //

// ** Documentation ** //
// A Great Tutorial -- http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/intro.html

// cbreak/delay/echo/etc	-- http://linux.die.net/man/3/cbreak
// getch					-- http://linux.die.net/man/3/curs_getch
// start_color/init_pair	-- http://linux.die.net/man/3/start_color
// attrset/attron			-- http://linux.die.net/man/3/attron
// clear					-- http://linux.die.net/man/3/wclear

// This is cool. Win32a, an enhanced PDCurses w/ SDL. http://www.projectpluto.com/win32a.htm

// - ------------------------------------------------------------------------------------------ - //
int Out_Rows;
int Out_Columns;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void OutInit() {
//	initscr();					// Default Init //

	//raw();					// CTRL-Z and CTRL-C *DON'T* trigger signals //
	cbreak();					// CTRL-Z and CTRL-C trigger signals //
	//halfdelay(1);				// Calls to getch() return 'ERR' if no key pressed. Time in 10ths //
	nodelay( stdscr, TRUE );	// Non-Blocking getch(). Returns 'ERR' if no key pressed //
	keypad( stdscr, TRUE ); 	// Enable Arrow Keys, Function Keys, etc //
	noecho();					// User input not displayed. "echo()" to display //
	
//	start_color();				// Enable Color //
//	
//	init_pair( 1, COLOR_RED, 		COLOR_BLACK );
//	init_pair( 2, COLOR_GREEN,		COLOR_BLACK );
//	init_pair( 3, COLOR_YELLOW,		COLOR_BLACK );
//	init_pair( 4, COLOR_BLUE,		COLOR_BLACK );
//	init_pair( 5, COLOR_MAGENTA,	COLOR_BLACK );
//	init_pair( 6, COLOR_CYAN,		COLOR_BLACK );
//	init_pair( 7, COLOR_WHITE,		COLOR_BLACK );
//	init_pair( 8, COLOR_BLACK, 		COLOR_BLACK );
	
	getmaxyx( stdscr, Out_Rows, Out_Columns );
	
	refresh();
}
// - ------------------------------------------------------------------------------------------ - //
void OutExit() {
//	endwin();	// Shutdown Curses //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Out( const char* Text, ... ) {
	va_list arg;
	va_start( arg, Text );

    vwprintw( stdscr, Text, arg );	// The only va_list compatible function //
    
    va_end( arg );
    
    printw( "\n" );
}
// - ------------------------------------------------------------------------------------------ - //
void Out_( const char* Text, ... ) {
	va_list arg;
	va_start( arg, Text );

    vwprintw( stdscr, Text, arg );	// The only va_list compatible function //
    
    va_end( arg );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void OutColor( const int InColor ) {
	int Color = InColor & 7;
	if ( Color == 0 )
		Color = 8;

	attrset( 
		COLOR_PAIR(Color) | 
		(((InColor & 15) > 7) ? A_BOLD : A_NORMAL) |
		((InColor > 15) ? A_REVERSE : A_NORMAL)
		);
}
// - ------------------------------------------------------------------------------------------ - //
void OutResetColor() {
	standend();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void OutFlush() {
	refresh();
}
// - ------------------------------------------------------------------------------------------ - //
void OutClear() {
	clear();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int GetCh() {
	return getch();
}
// - ------------------------------------------------------------------------------------------ - //
int GetRows() {
	return Out_Rows;
}
// - ------------------------------------------------------------------------------------------ - //
int GetColumns() {
	return Out_Columns;
}
// - ------------------------------------------------------------------------------------------ - //
