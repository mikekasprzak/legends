// - ------------------------------------------------------------------------------------------ - //
#include "SceneGame.h"
#include <Render/Render.h>
#include <Render/Font.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
void cSceneGame::Step() {
	SVar("Time") -= 1;
	
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

}
// - ------------------------------------------------------------------------------------------ - //
