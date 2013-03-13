// - ------------------------------------------------------------------------------------------ - //
#include "SceneGame.h"
#include <Render/Render.h>
#include <Render/Font.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
cSceneGame::cSceneGame() {
	SVar.Add("Score1") = 0;
	SVar.Add("Score2") = 0;
	SVar.Add("Time") = 3*60*60;
	
	SVar.Add("DelayTime") = 4*60;
	
	// Add Templates //
	AddTemplate( "Screwy", new tScrewy() );
	
	// Add Objects //
	AddObject( "Screwy", Vector3D(200,0,0) );
	
}
// - ------------------------------------------------------------------------------------------ - //
cSceneGame::~cSceneGame() {
	
}	
// - ------------------------------------------------------------------------------------------ - //
void cSceneGame::Step() {
	if ( SVar("DelayTime").ToInt() > 0 ) {
		SVar("DelayTime") -= 1;
	}
	else {
		SVar("Time") -= 1;		
	}
	
	// *** //
	cScene::Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cSceneGame::Draw( const Matrix4x4& Matrix ) {
	// *** //
	cScene::Draw( Matrix );
	// *** //
	extern cFont* Font;
	Font->printf( Vector3D(-270,+150,0), 64.0f, GEL_ALIGN_TOP_LEFT, "%i", SVar("Score1").ToInt() );
	Font->printf( Vector3D(+270,+150,0), 64.0f, GEL_ALIGN_TOP_RIGHT, "%i", SVar("Score2").ToInt() );
	
	int Time = SVar("Time").ToInt();
//	Font->printf( Vector3D(0,+150,0), 32.0f, GEL_ALIGN_TOP_CENTER, "%i:%02i:%02i", (Time / 60) / 60, (Time / 60) % 60, Time % 60 );
	Font->printf( Vector3D(0,+150,0), 32.0f, GEL_ALIGN_TOP_CENTER, "%i:%02i", (Time / 60) / 60, (Time / 60) % 60 );

	int DelayTime = SVar("DelayTime").ToInt();
	Font->printf( 
		Vector3D(0,0,0), 
		192.0f * ((DelayTime % 60)/60.0f), 
		GEL_ALIGN_MIDDLE_CENTER, 
		"%i", (DelayTime / 60) % 60
	);

}
// - ------------------------------------------------------------------------------------------ - //
