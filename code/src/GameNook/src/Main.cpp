// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>
#include "Gel2D/GelGraphics2D.h"
// - ------------------------------------------------------------------------------------------ - //
//#include "../GameLegends/TreeForge/TFTree.h"
// - ------------------------------------------------------------------------------------------ - //

float gx;
float gy;

void GameInput( float x, float y, int bits ) __attribute__((used));
void GameInput( float x, float y, int bits ) {
	gx = x;
	gy = y;
//	Input_Stick
}

//cTFTree* MyTree;

// - ------------------------------------------------------------------------------------------ - //
//void NewGen() __attribute__((used));
//void NewGen() {
//	// Hack //
//	gelGraphicsInit( 640, 480 );
//
//	delete MyTree;
//	cTFGenerator TreeGen;
//	MyTree = TreeGen.Generate();
//	
//	MyTree->Draw();
//}
// - ------------------------------------------------------------------------------------------ - //
//int main( int argc, char* argv[] ) {
//	gelGraphicsInit( 640, 480 );
//	
//	{
//		srand ( time(NULL) );
//		int Blah = rand(); // Burn a random number //
//	}
//
//	cTFGenerator TreeGen;
//	MyTree = TreeGen.Generate();
//
//	MyTree->Draw();
//
//	gelGraphicsExit();
//	
//	return 0;
//}
// - ------------------------------------------------------------------------------------------ - //

float px, py;

int Tileset;
// - ------------------------------------------------------------------------------------------ - //
void GameInit() __attribute__((used));
void GameInit() {
	gelGraphicsInit( 320, 240 );
	
	px = 100;
	py = 100;
	
	Tileset = gelLoadImage( "Content/Nook-Tileset.png" );
}
// - ------------------------------------------------------------------------------------------ - //
void GameExit() __attribute__((used));
void GameExit() {
	gelGraphicsExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GameStep() __attribute__((used));
void GameStep() {
	px += gx;
	py += gy;
}
// - ------------------------------------------------------------------------------------------ - //
void GameDraw() __attribute__((used));
void GameDraw() {
	
	
	gelSetColor( 255,0,0,255 );
	gelDrawCircle( px, py, 10 );
	
	gelBindImage( Tileset );
	gelDrawImage( 10, 10 );
}
// - ------------------------------------------------------------------------------------------ - //

