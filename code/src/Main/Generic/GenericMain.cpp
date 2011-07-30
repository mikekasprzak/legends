// - ------------------------------------------------------------------------------------------ - //
#ifndef PRODUCT_EXPERIMENTS
#include "Sound/SoundPlayer.h"
#include "Sound/MusicPlayer.h"
#else // PRODUCT_EXPERIMENTS //
#include <Audio/SoundPlayer.h>
#include <Audio/MusicPlayer.h>
#endif // PRODUCT_EXPERIMENTS //
// - ------------------------------------------------------------------------------------------ - //
#include <GameHost.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern int phone_orientation;
int phone_orientation = 0;

//extern void SkipTime();
//void SkipTime() {
//}
// - ------------------------------------------------------------------------------------------ - //
extern int mouse_b;
extern int mouse_b_new;
int mouse_b = 0;
int mouse_b_new = 0;

extern int mouse_x;
extern int mouse_y;
int mouse_x = 0;
int mouse_y = 0;

extern int mouse_wheel;
int mouse_wheel = 0;

extern int EventValue;
int EventValue = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void HideWaitCursor();
void HideWaitCursor() {
}
// - ------------------------------------------------------------------------------------------ - //
void ShowWaitCursor();
void ShowWaitCursor() {
}
// - ------------------------------------------------------------------------------------------ - //

extern char AppBaseDir[];
char AppBaseDir[2048];

extern char AppSaveDir[];
char AppSaveDir[2048];


// - ------------------------------------------------------------------------------------------ - //
cGameHost* GameHost = 0;
// - ------------------------------------------------------------------------------------------ - //
extern void Simple_Init( int Width, int Height );
void Simple_Init( int Width, int Height ) {
	Log( "-=======- GEL Application Started -- SDL Branch -- SKU: %s -=======-\n", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2010 Mike Kasprzak and Sykhronics Entertainment\n" );
	Log( "\n" );
	Log( "-=- SKU: %s -=- %s -=- \n", PRODUCT_SKU, FullProductName );
	Log( "\n" );
	
	Log( "Width: %i  Height: %i", Width, Height );
	Log( "\n" );

	gelInit();		
	gelSetupRefScreenShape( 480, 320 );

#ifdef PRODUCT_EXPERIMENTS
	gelSetupDepthSize( 24 );
#endif // PRODUCT_EXPERIMENTS //

#ifdef PRODUCT_OVERSCAN
	gelSetupOverscan( 0.05f, 0.10f );
#endif // PRODUCT_OVERSCAN //

//	gelSetupAutodetectScreenShape();
	gelSetupScreenShape( Width, Height );
	NativeScreen::Width = Width;
	NativeScreen::Height = Height;
	gelSetupNativeScalar( 1.0f, 1.0f );
	gelSetupFullScreen( true );		

	gelSetup();
	gelPostSetup();

//#ifdef SLOW_VERSION
//	SetFramesPerSecond( 50 );
//#else // !SLOW_VERSION //
//	SetFramesPerSecond( 60 );
//#endif // SLOW_VERSION //

	sndInit();
	musInit();
	
	//musUpdate();

#ifndef PRODUCT_EXPERIMENTS
			// Populate Product Info, based on Compiled Arguments //
			ProductInfo = cProductInfo::DecodeEmbeddedInfo();
			// Verify that the Product Info bits are correctly formatted //
			if ( !ProductInfo.IsLegal() ) {
				ProductInfo = cProductInfo::TrialGame();
			}
			// Report what product we are //
			ProductInfo.LogInfo();
#endif // PRODUCT_EXPERIMENTS //
	
	Log("+ Creating GameHost Instance...\n");
	GameHost = new cGameHost;
	Log("- GameHost Created.\n");

	// Clear the screen //
	gelDisableBlending();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	gelClearColor( cGameSupport::Current()->FadeColor );
//	gelSwapBuffer();
//#ifdef USES_WEBOS
	// webOS layers OpenGL on top of Video, so make sure we don't write Alpha //
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
//#endif // USES_WEBOS //
	gelClearColor( cGameSupport::Current()->FadeColor );

	// Explicitly Create Game //
	GameHost->CreateGame();
}
// - ------------------------------------------------------------------------------------------ - //
extern void Simple_Exit();
void Simple_Exit() {
	Log( "\n-=======- Beginning GEL Application Shutdown... -=======-\n" );

#ifndef PRODUCT_EXPERIMENTS			
	Log( "- Writing Save Data...\n" );
	GameHost->Save();
	Log( "+ Finished Writing Save Data.\n" );
	Log( "\n" );
#endif // PRODUCT_EXPERIMENTS //
	
	Log( "- Freeing audio resources...\n" );
	musFree();
	sndFree();
	Log( "+ Audio resources released.\n" );
	Log( "\n" );
	
	delete GameHost;

	Log( "- Shutting Down GEL Graphics...\n" );
	gelExit();
	Log( "+ GEL Graphics Shut down complete.\n" );
	Log( "\n" );

	Log( "-=======- GEL Application Exited Successfully -=======-\n" );
}
// - ------------------------------------------------------------------------------------------ - //
extern void Simple_Step();
void Simple_Step() {
	EventInjector.Clear();
	if ( EventValue ) {
		EventInjector.Set( EventValue );
		EventValue = 0;
	}

	musUpdate();
	
	Mouse.Update();	
	GameHost->Step();
}
// - ------------------------------------------------------------------------------------------ - //
extern void Simple_Draw();
void Simple_Draw() {
	// Draw the game //
	GameHost->Draw();
	
	// Swap display buffer to screen //
//	gelSwapBuffer();
}
// - ------------------------------------------------------------------------------------------ - //
extern void Simple_FocusLost();
void Simple_FocusLost() {
	if ( GameHost )
		GameHost->ForcePaused();
	musPause();

	Log( "- Writing Save Data...\n" );
	GameHost->Save();
	Log( "+ Finished Writing Save Data.\n" );
}
// - ------------------------------------------------------------------------------------------ - //
extern void Simple_FocusGained();
void Simple_FocusGained() {
	SkipTime();
	musUpdate();
	musResume();
}
// - ------------------------------------------------------------------------------------------ - //
extern bool IsMainMenu();
bool IsMainMenu() {
	if ( GameHost ) {
		if ( GameHost->Game ) {
			return (GameHost->Game->GameState == cGame::ST_MENU);
		}
	}
		
	return false;	
}
// - ------------------------------------------------------------------------------------------ - //
