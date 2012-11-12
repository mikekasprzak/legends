
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(n) Sleep(1000*n)
#endif // _WIN32

// http://en.wikipedia.org/wiki/C_signal_handling
// http://en.wikipedia.org/wiki/Unix_signal
// Unsupported on Windows: http://msdn.microsoft.com/en-us/library/xdkz3x12%28v=vs.110%29.aspx

void term_func( int Signal ) {
	printf( "SIGTERM (Terminate) recieved -- %i\n", Signal );
	exit(1);
}

void int_func( int Signal ) {
	printf( "\nSIGINT (Interrupt) recieved (CTRL+C) -- %i\n", Signal );
}

#ifndef _WIN32
void tstop_func( int Signal ) {
	printf( "\nSIGTSTP (Terminal Stop) recieved (CTRL+Z) -- %i\n", Signal );
}
void quit_func( int Signal ) {
	printf( "\nSIGQUIT (Quit) recieved (CTRL+\\) -- %i\n", Signal );
}
#endif // _WIN32

int main( int argc, char* argv[] ) {
	
	signal( SIGTERM, term_func );
	signal( SIGINT, int_func );

#ifndef _WIN32
	signal( SIGTSTP, tstop_func );
	signal( SIGQUIT, quit_func );
#endif // _WIN32

	printf( "Waiting for a kill signal...\n" );
	fflush(0);
	
	char In;
	do {
		//In = getchar();
		sleep(1);
	}
	while( In != ' ' );

	printf( "Done.\n" );

	return 0;
}
