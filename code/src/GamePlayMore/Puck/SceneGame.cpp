// - ------------------------------------------------------------------------------------------ - //
#include "SceneGame.h"
#include <Render/Render.h>
#include <Render/Font.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Templates/Screwy.h"
#include "Templates/Puck.h"
#include "Templates/Player.h"
#include "Templates/Net.h"
#include "Templates/Rink.h"
#include "Templates/DummyRink.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
cSceneGame::cSceneGame() {
	SVar.Add("Score1") = 0;
	SVar.Add("Score2") = 0;
	SVar.Add("Time") = (3*60*60) + 59;
	
	SVar.Add("DelayTime") = 4*60;
	SVar.Add("ShowDelayTime") = true;
	
	SVar.Add("GameMode") = 1;

	SVar.Add("PuckSpeed") = 0.0f;	// Puck Velocity Magnitude //
	
	// Add Templates //
	AddTemplate( "Puck", new tPuck() );
	AddTemplate( "Player1", new tPlayer( 0, GEL_RGB_ORANGE ) );
	AddTemplate( "Player2", new tPlayer( 1, GEL_RGB_RED ) );
	AddTemplate( "Player3", new tPlayer( 2, GEL_RGB_MINT ) );
	AddTemplate( "Player4", new tPlayer( 3, GEL_RGB(0,128,255) ) );
	AddTemplate( "Net1", new tNet( GEL_RGB_ORANGE, false ) );
	AddTemplate( "Net2", new tNet( GEL_RGB_MINT, true ) );
	AddTemplate( "Rink", new tRink() );
	
	// Add Objects //
	AddObject( "Rink", Vector3D(0,0,0) );

	AddObject( "Player1", Vector3D(-60,+60,0) );
	AddObject( "Player2", Vector3D(-60,-60,0) );
	AddObject( "Player3", Vector3D(+60,+60,0) );
	AddObject( "Player4", Vector3D(+60,-60,0) );

	AddObject( "Puck", Vector3D(0,0,0) );

	AddObject( "Net1", Vector3D( -240, 0, 0 ) );
	AddObject( "Net2", Vector3D( +240, 0, 0 ) );
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
		if ( SVar("Time").ToInt() > 0 ) {
			SVar("Time") -= 1;
		}
	}
	
	// *** //
	cScene::Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cSceneGame::Draw( const Matrix4x4& Matrix ) {
	// ** PRE DRAW ** //
	{
	}
	// ** DRAW ** //
	cScene::Draw( Matrix );
	// ** POST DRAW ** //
	{
		extern cFont* Font;
		Font->printf( Vector3D(-270,+150,0), 64.0f, GEL_ALIGN_TOP_LEFT, "%i", SVar("Score1").ToInt() );
		Font->printf( Vector3D(+270,+150,0), 64.0f, GEL_ALIGN_TOP_RIGHT, "%i", SVar("Score2").ToInt() );
		
		int Time = SVar("Time").ToInt();
//		Font->printf( Vector3D(0,+150,0), 32.0f, GEL_ALIGN_TOP_CENTER, "%i:%02i:%02i", (Time / 60) / 60, (Time / 60) % 60, Time % 60 );
		Font->printf( Vector3D(0,+150,0), 32.0f, GEL_ALIGN_TOP_CENTER, "%i:%02i", (Time / 60) / 60, (Time / 60) % 60 );
	
		if ( SVar("ShowDelayTime").ToBool() ) {
			int DelayTime = SVar("DelayTime").ToInt();
			Font->printf( 
				Vector3D(0,0,0), 
				192.0f * ((DelayTime % 60)/60.0f), 
				GEL_ALIGN_MIDDLE_CENTER, 
				"%i%s", (DelayTime / 60) % 60, ((DelayTime / 60) == 0) ? "!" : ""
			);
		}

		if ( SVar("Time").ToBool() == 0 ) {
			if ( SVar("PuckSpeed").ToFloat() < 0.05f ) {
				const char* Text = "TIE!";
				if ( SVar("Score1").ToInt() > SVar("Score2").ToInt() )
					 Text = "ORANGE WINS!";
				if ( SVar("Score2").ToInt() > SVar("Score1").ToInt() )
					 Text = "GREEN WINS!";
					
				Font->printf( 
					Vector3D(0,0,0), 
					128.0f,
					GEL_ALIGN_MIDDLE_CENTER, 
					Text
				);
			}
			else {
				Font->printf( 
					Vector3D(0,0,0), 
					192.0f,
					GEL_ALIGN_MIDDLE_CENTER, 
					"END"
				);
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
