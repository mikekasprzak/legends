// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Timer/Timer.h>

#include "App.h"
#include <Util/curses.h>
#include "Text/Out.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef PRODUCT_SKU
	#define PRODUCT_SKU		"UNKNOWN"
	
	const char* ProductName = "Unknown";
	const char* FullProductName = "Unknown (?) v0.0";
#endif // PRODUCT_SKU //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <signal.h>
// - ------------------------------------------------------------------------------------------ - //
void term_func( int Signal ) {
	ELog( "SIGTERM (Terminate) recieved -- %i", Signal );
	LogFlush();
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //
void int_func( int Signal ) {
	ELog( "\nSIGINT (Interrupt) recieved (CTRL+C) -- %i", Signal );
	LogFlush();
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {	
	if ( !curses_IsSupported() ) {
		printf( "ERROR: PDCurses is not supported. :(\n\n");
		printf( "Hey, let information@sykhronics.com know you got this error and you could win a\n" );
		printf( "prize!! OK not really, but we really want to know if anyone gets this. Thanks!\n\n" );
		printf( "Solution: Run this from an ordinary CMD shell, or install and use WinPTY.\n" );
		printf( "https://github.com/rprichard/winpty -- \"console SatServ\"\n" );

		return 1;
	}

	// **** //

	LogInit();
	
	signal( SIGTERM, term_func );
	signal( SIGINT, int_func );

	// **** //

	Log( "-=======- GEL2 Server Started -- Curses Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2013 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );

	OutInit();	
	
	// **** //
	
	gelNetInit();	// Mainly for WinSock //
	
	// **** //
	
	extern void SatBodyTest();
	SatBodyTest();
	
	// **** //
	
	{
		cApp App;
		App();
	}

	OutExit();

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
