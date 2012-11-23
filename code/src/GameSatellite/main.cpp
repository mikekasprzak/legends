// - ------------------------------------------------------------------------------------------ - //
#include <SDL2/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Timer/Timer.h>
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void ReportSDLVersion() {
	SDL_version ver;
	SDL_VERSION(&ver);
	Log( "SDL (core) - v%u.%u.%u -- Compiled Version", ver.major, ver.minor, ver.patch );

	SDL_version pver;
	SDL_GetVersion(&pver);
	Log( "SDL (core) - v%u.%u.%u -- Linked Version (DLL or Shared Library)", pver.major, pver.minor, pver.patch );
	Log( "" );

	int LinkVer = (ver.major << 16) | (ver.minor << 8) | (ver.patch << 0);
	int DLLVer = (pver.major << 16) | (pver.minor << 8) | (pver.patch << 0);

	if ( LinkVer > DLLVer ) {
		Log( "* WARNING: Linked version is older than Compiled version!!" );
		Log( "  If you have problems starting the game, this may be why." );
		Log( "  Upgrade to a newer SDL version to resolve this." );
		Log( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#include <System/Path.h>

extern char AppBaseDir[];
char AppBaseDir[2048];

extern char AppSaveDir[];
char AppSaveDir[2048] = "";
// - ------------------------------------------------------------------------------------------ - //
void ProcessCommandLineArgs( int argc, char* argv[] ) {
	Log( "+ Command Line Arguments: %i", argc );
	for ( int idx = 0; idx < argc; idx++ ) {
		Log( "* \"%s\"", argv[idx] );	
	}
	Log( "- End of Command Line" );
	Log( "" );

	// Get Base Directory //
	{	
		Log( "+ Getting Content Path..." );
		//set_Data( 0, AppBaseDir, sizeof(AppBaseDir) );
		
		bool CalculatePath = true;
		if ( argc > 2 ) {
			if ( strcmp( argv[1], "-DIR" ) == 0 ) {
				strcpy( AppBaseDir, argv[2] );
				CalculatePath = false;
			}
		}

		if ( argc > 4 ) {
			if ( strcmp( argv[3], "-SAVE" ) == 0 ) {
				strcpy( AppSaveDir, argv[4] );
			}
		}
		
		if ( CalculatePath ) {
			gelGetContentPath( AppBaseDir, sizeof(AppBaseDir) );
		}
		
		Log( "- Base Directory: %s", AppBaseDir );
		Log( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef PRODUCT_SKU
	#define PRODUCT_SKU		"UNKNOWN"
	
	const char* ProductName = "Unknown";
	const char* FullProductName = "Unknown (?) v0.0";
#endif // PRODUCT_SKU //
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	Log( "-=======- GEL2 Application Started -- SDL2 Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2013 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	Log( "" );
	
	ReportSDLVersion();
	ProcessCommandLineArgs( argc, argv );

	// **** //

	gelNetInit();
		
	// **** //
	
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
	atexit(SDL_Quit);
	
	// **** //
	
	int ScreenW, ScreenH;
	
	{
		Log( "Video Displays" );
		for( int idx = 0; idx < SDL_GetNumVideoDisplays(); idx++ ) {		
			SDL_DisplayMode Mode;
			SDL_GetDesktopDisplayMode( idx, &Mode );
			ScreenW = Mode.w;
			ScreenH = Mode.h;

			SDL_Rect Rect;
			SDL_GetDisplayBounds( idx, &Rect );
			
			Log( "%i - %i, %i at %i Hz [%x] -- Location: %i, %i (%i,%i)", idx, Mode.w, Mode.h, Mode.refresh_rate, Mode.format, Rect.x, Rect.y, Rect.w, Rect.h );
		}
	}
	
	// **** //
	
	ScreenW *= 90;
	ScreenW /= 100;

	ScreenH *= 90;
	ScreenH /= 100;
	
	SDL_Window* pWindow = SDL_CreateWindow(
		FullProductName,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		ScreenW, ScreenH,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		);
	
	// SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE, SDL_WINDOW_INPUT_GRABBED, SDL_WINDOW_FULLSCREEN
	
	if ( pWindow == NULL ) {
		Log( "Error Creating Window: %s", SDL_GetError() );
		return 1;
	}
	
	SDL_GLContext GLContext = SDL_GL_CreateContext( pWindow );
	
	SDL_DisableScreenSaver();
	
	Log( "" );
	
	// **** //

	{
		cApp App;
		fflush(0);
		
		
		bool ExitApp = false;
		while ( !ExitApp ) {
			SDL_Event Event;
			SDL_PollEvent(&Event);
			if ( Event.type == SDL_QUIT ) {
				ExitApp = true;
			}
			
			App.Step();
			App.Draw();
			SDL_GL_SwapWindow( pWindow );
			Wait(5);
		}
	}

	// **** //
	
	SDL_EnableScreenSaver();
	
	SDL_GL_DeleteContext( GLContext );
	SDL_DestroyWindow( pWindow );

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
