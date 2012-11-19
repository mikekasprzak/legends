// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
#include <Util/curses.h>
#include "Text/Out.h"
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
	
	gelNetInit();	// Mainly for WinSock //
	
	// **** //
	
	extern void SatBodyTest();
	SatBodyTest();
	
	// **** //

	OutInit();
	OutClear();

	{
		cApp App;
		App();
	}

	OutExit();

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
