
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <unistd.h>

// http://en.wikipedia.org/wiki/C_signal_handling
// http://en.wikipedia.org/wiki/Unix_signal

void term_func( int Signal ) {
	printf( "SIGTERM (Terminate) recieved -- %i\n", Signal );
	exit(1);
}

void tstop_func( int Signal ) {
	printf( "\nSIGTSTP (Terminal Stop) recieved (CTRL+Z) -- %i\n", Signal );
}
void int_func( int Signal ) {
	printf( "\nSIGINT (Interrupt) recieved (CTRL+C) -- %i\n", Signal );
}
void quit_func( int Signal ) {
	printf( "\nSIGQUIT (Quit) recieved (CTRL+\) -- %i\n", Signal );
}

int main( int argc, char* argv[] ) {
	
	signal( SIGTERM, term_func );
	signal( SIGTSTP, tstop_func );
	signal( SIGINT, int_func );
	signal( SIGQUIT, quit_func );

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
