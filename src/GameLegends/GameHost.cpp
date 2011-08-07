// - ------------------------------------------------------------------------------------------ - //
#include "GameHost.h"
// - ------------------------------------------------------------------------------------------ - //
cGameHost::cGameHost() {
	Log("- Begin GameHost Constructor\n");

	// Setup Texture Pool //
	TexturePool::Init( "Content/Art/4444" );
	TexturePool::AddDirectory( "" );

/*
	Log( "+ Setting Base Content Directory...\n" );
#ifdef USES_TEXTURECOMPRESSION //
	if ( System::InfoFlags.HasTextureCompression ) {
		Log( "- Texture Compression Found -- Using DXT5\n" );
		TexturePool::Init( "Content/DXT5" );
	}
	else
#else // USES_TEXTURECOMPRESSION //
	Log( "* Build Flag \"USES_TEXTURECOMPRESSION\" not set. Defaulting to RGBA4444\n" );
#endif // USES_TEXTURECOMPRESSION //
	{
		// Fallback, no compression //
		Log( "- Texture Compression Not Found -- Using RGBA4444\n" );
		TexturePool::Init( "Content/4444" );
	}
	TexturePool::AddDirectory( "" );
*/
	
	// Set a new Initial Reference Screen (So Smiles does a weird zoom) //
//	gelSetupRefScreenShape( 64, 64 );
//	gelCalculateScreenShape();
//	gelCalculateViewMatrix();

	// Create GameSupport //
	GameSupport = new cGameSupport;
	
	// Set Fade Color //
	GameSupport->FadeSetColor( GEL_RGB_WHITE );
	
	// Game is null //
	Game = 0;
	
	Log("+ End GameHost Constructor\n");
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
}
// - ------------------------------------------------------------------------------------------ - //
void cGameHost::CreateGame() {		
	// Create Game //
	Log("+ Creating Game Instance...\n");	
	Game = new cGame;
	Log("- Game Create.\n");

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
		Log( "WARNING! GAME STEPPED WITHOUT CreateGame call! Creating...\n" );
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
		Log( "WARNING! GAME DRAWN WITHOUT CreateGame call! Creating...\n" );
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
