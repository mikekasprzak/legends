
#include <stdio.h>

extern "C" {
void gelGraphicsInit( int Width, int Height );
void gelGraphicsExit();

void gelSetColor( int r, int g, int b, int a );
void gelDrawCircle( float x, float y, float Radius );
void gelDrawCircleFill( float x, float y, float Radius );

//void gelDrawFillRect( float x, float y, float w, float h );
};

class SouthBound {
public:
	void SugarMomma() {
		printf("Momma!\n");
	}
};

int main( int argc, char* argv[] ) {
	gelGraphicsInit( 640, 320 );
	
	gelSetColor( 255, 0, 0, 255 );
	gelDrawCircleFill( 240, 240, 32 );
	
	//gelDrawFillRect( 64, 64, 320-128, 128 );
	
//	SouthBound sb;
//	sb.SugarMomma();

	gelGraphicsExit();
	
	return 0;
}
