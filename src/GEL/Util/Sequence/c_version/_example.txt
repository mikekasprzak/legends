#include <stdio.h>
#include "sequence.h"

int main( int argc, char* argv[] ) {
	printf("- Sequence Test -\n");
	
	sequence IntroSeq;
	seq_Init(&IntroSeq);
	
	seq_Activate(&IntroSeq);
	
	int idx = 0;
	for ( ; idx < 40; idx++ ) {
		if ( seq_Begin(&IntroSeq, 1) ) {
			printf("Begin %i\n", seq_Get(&IntroSeq) );	
		}
		else if ( seq_Next(&IntroSeq, 4) ) {
			printf("Next %i\n", seq_Get(&IntroSeq) );			
		}
		else if ( seq_Loop(&IntroSeq, 2, 0) ) {
			printf("Loop Loops:%i\n", seq_GetLoopCount(&IntroSeq) );	
		}
		else if ( seq_End(&IntroSeq) ) {
			printf("End Loops:%i\n", seq_GetLoopCount(&IntroSeq) );	
		}
	}
	return 0;
}
