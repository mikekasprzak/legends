
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void term_func( int Signal ) {
	printf( "SIGTERM recieved -- %i\n", Signal );
	fflush(0);
	exit(1);
}

int main( int argc, char* argv[] ) {
	
	signal( SIGTERM, term_func );

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
