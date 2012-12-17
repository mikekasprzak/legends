
#include <stdio.h>

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif // _MSC_VER //

int main( int argc, char* argv[] ) {
	printf( "Hey %s", __PRETTY_FUNCTION__ );
	return 0;	
}
