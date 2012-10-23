
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void term_func( int Signal ) {
	printf( "SIGTERM (Terminate) recieved -- %i\n", Signal );
	exit(1);
}

void tstop_func( int Signal ) {
	printf( "SIGTSTP (Terminal Stop) recieved (CTRL+Z) -- %i\n", Signal );
	exit(1);
}

int main( int argc, char* argv[] ) {
	
	signal( SIGTERM, term_func );
	signal( SIGTSTP, tstop_func );

	printf( "Waiting for a kill signal...\n" );
	fflush(0);
	
	char In;
	do {
		In = getchar();
	}
	while( In != ' ' );

	printf( "Done.\n" );

	return 0;
}
