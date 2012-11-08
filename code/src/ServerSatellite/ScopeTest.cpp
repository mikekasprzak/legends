
#include <stdio.h>

class PropertyTest {
public:
	PropertyTest() {
		x = 0;
		y = 0;
	}
	
	int Scott;
	
	class {
		int Value;
	public:
		// make me private to disable reading //
		operator const int () const {
			return Value;
		}
	public:
		// Make me private to disable assignment //
		const int& operator = ( const int& Vs ) {
			return Value = Vs;
		}
	} x, y;
	
	class {
	public:		
		const int& operator = ( const int& Vs ) {
			//x = Vs;	// Fails due to scope limits //
			Scott = 10;
			return Vs;
		}
	} right;
	
	class {
	public:
		operator const int () const {
			return 7;
		}
	} fake;		
};

int main( int argc, char* argv[] ) {
	PropertyTest sc;
	
	printf( "sc: %i\n", (int)sc.x );	
	sc.x = 10;
	printf( "sc: %i\n", (int)sc.x );
	
	printf( "fake: %i\n", (int)sc.fake );

	return 0;
}
