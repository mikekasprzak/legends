// - ------------------------------------------------------------------------------------------ - //
#include "GameHost.h"
#include <AssetPool/AssetPool.h>
// - ------------------------------------------------------------------------------------------ - //
cGameHost::cGameHost() {
	Log("- Begin GameHost Constructor");


	// * * * * * //

		
	// Setup Asset Pool //
	AssetPool::Init( "Content" );


	#ifdef USES_TEXTURECOMPRESSION //
	// Add (optional) compressed formats to the search first //
	if ( System::InfoFlags.HasDXT5 ) {
		Log( "* Texture Compression Found -- Using DXT5" );
		AssetPool::Init( "/Art/DXT5" );
	}
	if ( System::InfoFlags.HasPVRTC ) {
		Log( "* Texture Compression Found -- Using PVRTC" );
		AssetPool::Init( "/Art/PVRTC" );
	}
	#endif // USES_TEXTURECOMPRESSION //


	// Add Baseline/Required Search Paths //
	AssetPool::AddDirectory( "/Art/4444" );
	AssetPool::AddDirectory( "/Models/Native" );
	AssetPool::AddDirectory( "/Misc" );				// Extra Things (Fonts) //


	#ifndef USES_NO_CONTENT_SRC_PATHS
	// Add Script Source folder first //
	AssetPool::AddDirectory( "/Scripts/src" );

	// Add Backup Content Search Directories (Source Folders) //
	AssetPool::AddDirectory( "/Art/src" );
	AssetPool::AddDirectory( "/Models/src" );
	#endif // USES_NO_CONTENT_SRC_PATHS //


	// Add Compiled Script folder last (because we want to work & use src) //
	AssetPool::AddDirectory( "/Scripts/Compiled" );


	// * * * * * //


#ifdef PRODUCT_SMILES_LEGACY
	// Set a new Initial Reference Screen (So Smiles does a weird zoom) //
	gelSetupRefScreenShape( 64, 64 );
	gelCalculateScreenShape();
	gelCalculateViewMatrix();
#endif // PRODUCT_SMILES_LEGACY //


	// Create GameSupport //
	GameSupport = new cGameSupport;
	
	// Set Fade Color //
	GameSupport->FadeSetColor( GEL_RGB_WHITE );
	
	// Game is null //
	Game = 0;
	
	Log("+ End GameHost Constructor");
}
// - ------------------------------------------------------------------------------------------ - //
cGameHost::~cGameHost() {
	if ( Game ) {
		delete Game;
		Game = 0;
	}
	
	if ( GameSupport ) {
		delete GameSupport;
		GameSupport = 0;
	}
	
	AssetPool::Exit();
//	TexturePool::Exit();
}
// - ------------------------------------------------------------------------------------------ - //
void cGameHost::CreateGame() {		
	// Create Game //
	Log("+ Creating Game Instance...");	
	Game = new cGame;
	Log("- Game Create.");

//	if ( FirstRun() ) {
//		Game->PlayMusic();
//	}	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGameHost::Step() {
	if ( GameSupport )
		GameSupport->Step();
	
	if ( Game ) {
		Game->Step();
	}
	else {
		// Backup! This should never be called! //
		Log( "WARNING! GAME STEPPED WITHOUT CreateGame call! Creating..." );
		CreateGame();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGameHost::Draw() {
	// Draw the game //
	if ( Game ) {
		Game->Draw();

//		// If Capture was enabled, capture the screen, and draw again //
//		if ( Game->Capture ) {
//			gelCapture();
//			
//			Game->Capture = false;
//			Game->Draw();
//		}
//	
//		if ( Game->FirstRun ) {
//			Game->Capture = true;
//			Game->FirstRun = false;
//		}
		
		Game->FirstRun = false;
	}
	else {
		// Backup! This should never be called! //
		Log( "WARNING! GAME DRAWN WITHOUT CreateGame call! Creating..." );
		CreateGame();
	}
		
	// Draw Support (Always on top -- cursors, overlays, popups) //
	if ( GameSupport ) {
		//if ( !Capture )
		GameSupport->Draw();
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGameHost::ForcePaused() {
	if ( Game )
		Game->ForcePaused();
}
// - ------------------------------------------------------------------------------------------ - //
bool cGameHost::FirstRun() {
	if ( Game )
		return Game->FirstRun;
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
void cGameHost::Save() {
	if ( Game ) {
		Game->SaveState();
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cGameHost::GotFocus() {
	if ( Game ) {
		Game->GotFocus();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGameHost::LostFocus() {
	if ( Game ) {
		Game->LostFocus();
	}
}
// - ------------------------------------------------------------------------------------------ - //
