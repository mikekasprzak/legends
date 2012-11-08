
#include <stdio.h>

// for(int __idx_ = Count+1; --__idx_;) // prefix "--" required, as suffix "--" causes a test vs "-1" //
#define FASTLOOP(Count) for(int ___idx_ ## __COUNTER__ = (Count)+1; --___idx_ ## __COUNTER__;)

int main( int argc, char* argv[] ) {

	for(int Index=10; --Index;) {
		printf("%i\n",Index);
	}
	
	FASTLOOP(5) {
		printf( "Hey\n" );
		FASTLOOP(2) {
			printf("Nerf!\n");
		}
	}

	return 0;
}
