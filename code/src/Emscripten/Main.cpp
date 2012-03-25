// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>
#include "Gel2D/GelGraphics2D.h"
// - ------------------------------------------------------------------------------------------ - //
#include "../GameLegends/TreeForge/TFTree.h"
// - ------------------------------------------------------------------------------------------ - //

cTFTree* MyTree;

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	gelGraphicsInit( 640, 480 );
	
	//gelSetColor( 255, 0, 0, 255 );
	//gelDrawCircleFill( 240, 240, 32 );
	
	//gelDrawFillRect( 64, 64, 320-128, 128 );


	{
		srand ( time(NULL) );
		int Blah = rand(); // Burn a random number //
	}

	cTFGenerator TreeGen;
	MyTree = TreeGen.Generate();

	MyTree->Draw();

	gelGraphicsExit();
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
