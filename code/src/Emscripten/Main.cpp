// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>
#include "Gel2D/GelGraphics2D.h"
// - ------------------------------------------------------------------------------------------ - //
#include "../GameLegends/TreeForge/TFTree.h"
// - ------------------------------------------------------------------------------------------ - //

cTFTree* MyTree;

// - ------------------------------------------------------------------------------------------ - //
void NewGen() __attribute__((used));
void NewGen() {
	// Hack //
	gelGraphicsInit( 640, 480 );

	delete MyTree;
	cTFGenerator TreeGen;
	MyTree = TreeGen.Generate();
	
	MyTree->Draw();
}
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	gelGraphicsInit( 640, 480 );
	
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
