// - ------------------------------------------------------------------------------------------ - //
#include <SDL2/SDL.h>
#include <gl/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Core/GelError.h>
#include <Timer/Timer.h>
#include <DrMinGW/DrMinGW.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Input_XInput.h"
// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include "main_Product.h"
#include "main_SVNVersion.h"
#include "main_SDLInit.h"
#include "Screen_Native_SDL.h"
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#include <System/Path.h>

extern char AppBaseDir[];
char AppBaseDir[2048];

extern char AppSaveDir[];
char AppSaveDir[2048] = "";
// - ------------------------------------------------------------------------------------------ - //
// TODO: Rename this. ArgInit? SystemInit? Only non arg is the PID
void AppInit( int argc, char* argv[] ) {
	Log( "-=- Application Execution Info -=-" );
	
	// Show Command Line //
	{
		Log( "Command Line Arguments: %i", argc );
		for ( int idx = 0; idx < argc; idx++ ) {
			Log( "argv[%i]: \"%s\"", idx, argv[idx] );	
		}
	}

	// Get Base Directory //
	{	
		// TODO: Add Arg Decomposer //
		if ( argc > 1 ) {
			// HACK: if more than 1 args, assume higher Log Level //
			LogLevel = 3;
		}

		bool DetermineContentPath = true;
		if ( argc > 2 ) {
			if ( strcmp( argv[1], "-DIR" ) == 0 ) {
				strcpy( AppBaseDir, argv[2] );
				DetermineContentPath = false;
			}
		}

		bool DetermineSavePath = true;
		if ( argc > 4 ) {
			if ( strcmp( argv[3], "-SAVE" ) == 0 ) {
				strcpy( AppSaveDir, argv[4] );
				DetermineSavePath = false;
			}
		}
		
		if ( DetermineContentPath )
			gelGetContentPath( AppBaseDir, sizeof(AppBaseDir) );

		if ( DetermineSavePath )
			gelGetStoragePath( AppSaveDir, sizeof(AppSaveDir) );
		
		Log( "Base Directory: %s", AppBaseDir );
		Log( "Save Directory: %s", AppSaveDir );
		Log( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //


enum {
	// Four Split //
	// +-----+-----+ //
	// |  0  |  1  | //
	// +-----+-----+ //
	// |  2  |  3  | //
	// +-----+-----+ //
	RR_FOUR_0 = 			0x1,
	RR_FOUR_1 = 			0x2,
	RR_FOUR_2 = 			0x4,
	RR_FOUR_3 = 			0x8,
	
	RR_FOUR =				(RR_FOUR_0|RR_FOUR_1|RR_FOUR_2|RR_FOUR_3),
	RR_FOUR_TOPLEFT =		RR_FOUR_0,
	RR_FOUR_TOPRIGHT =		RR_FOUR_1,
	RR_FOUR_BOTTOMLEFT =	RR_FOUR_2,
	RR_FOUR_BOTTOMRIGHT =	RR_FOUR_3,

	// Six Split (Wide) //
	// +---+---+---+ //
	// | 0 | 1 | 2 | //
	// +---+---+---+ //
	// | 3 | 4 | 5 | //
	// +---+---+---+ //
	RR_SIXW_0 = 			0x10,
	RR_SIXW_1 = 			0x20,
	RR_SIXW_2 = 			0x40,
	RR_SIXW_3 = 			0x80,
	RR_SIXW_4 = 			0x100,
	RR_SIXW_5 = 			0x200,

	RR_SIXW =				(RR_SIXW_0|RR_SIXW_1|RR_SIXW_2|RR_SIXW_3|RR_SIXW_4|RR_SIXW_5),
	RR_SIXW_TOPLEFT =		RR_SIXW_0,
	RR_SIXW_TOPMIDDLE =		RR_SIXW_1,
	RR_SIXW_TOPRIGHT =		RR_SIXW_2,
	RR_SIXW_BOTTOMLEFT =	RR_SIXW_3,
	RR_SIXW_BOTTOMMIDDLE =	RR_SIXW_4,
	RR_SIXW_BOTTOMRIGHT =	RR_SIXW_5,

	// Six Split (Tall) //
	// +---+---+ //
	// | 0 | 1 | //
	// +---+---+ //
	// | 2 | 3 | //
	// +---+---+ //
	// | 4 | 5 | //
	// +---+---+ //
	RR_SIXT_0 = 			0x400,
	RR_SIXT_1 = 			0x800,
	RR_SIXT_2 = 			0x1000,
	RR_SIXT_3 = 			0x2000,
	RR_SIXT_4 = 			0x4000,
	RR_SIXT_5 = 			0x8000,

	RR_SIXT =				(RR_SIXT_0|RR_SIXT_1|RR_SIXT_2|RR_SIXT_3|RR_SIXT_4|RR_SIXT_5),
	RR_SIXT_TOPLEFT =		RR_SIXT_0,
	RR_SIXT_TOPRIGHT =		RR_SIXT_1,
	RR_SIXT_MIDDLELEFT =	RR_SIXT_2,
	RR_SIXT_MIDDLERIGHT =	RR_SIXT_3,
	RR_SIXT_BOTTOMLEFT =	RR_SIXT_4,
	RR_SIXT_BOTTOMRIGHT =	RR_SIXT_5,

	// Question: Should the ID's map to the same layout as the SIXW? That way the code can be the same? //
};

// TODO: Make a table of which layouts it's part of? Four RR_FOUR's, Six RR_SIXW's, etc. //

// Halfs //
#define H0 (0.0f)
#define H1 (0.5f)
#define H2 (1.0f)

// Thirds //
#define T0 (0.0f/3.0f)
#define T1 (1.0f/3.0f)
#define T2 (2.0f/3.0f)
#define T3 (3.0f/3.0f)

// Render Regions in "0 to 1" format (same as glViewport, but it takes w,h) //
const float RenderRegion[] = {
	// Four Split -- 2x2 (H,H) //
	H0,H0,H1,H1,
	H1,H0,H2,H1,
	H0,H1,H1,H2,
	H1,H1,H2,H2,
	
	// Six Split (Wide) -- 3x2 (T,H) //
	T0,H0,T1,H1,
	T1,H0,T2,H1,
	T2,H0,T3,H1,
	T0,H1,T1,H2,
	T1,H1,T2,H2,
	T2,H1,T3,H2,
	
	// Six Split (Tall) -- 2x3 (H,T) //
	H0,T0,H1,T1,
	H1,T0,H2,T1,
	H0,T1,H1,T2,
	H1,T1,H2,T2,
	H0,T2,H1,T3,
	H1,T2,H2,T3,	
};

#undef H0
#undef H1
#undef H2
#undef T0
#undef T1
#undef T2
#undef T3

// Layout systems should always work in "0 to 1" or "-1 to +1" figures. //
// Minimap placement should be in a corner of an overscan-like rectangle. //
// 

// - ------------------------------------------------------------------------------------------ - //
void PollInput() {
	#ifdef USES_XINPUT
	{
		XInput::Poll();
		if ( XInput::HasConnectionChanged() ) {
			for ( size_t idx = 0; idx < XInput::Size(); idx++ ) {
				if ( XInput::HasConnectionChanged(idx) ) {
					Log( "** XInput Controller %i %s", idx, XInput::IsConnected(idx) ? "Connected" : "Disconnected" );
				}
			}
		}
	}
	#endif // USES_XINPUT //	
}
// - ------------------------------------------------------------------------------------------ - //
int EventHandler( void* UserData, SDL_Event* Event ) {
	if ( Event->type == SDL_QUIT ) {
		Log( "> SDL_QUIT Signal Recieved" );
		return true;
	}
	else if ( Event->type == SDL_KEYUP ) {
//		if ( Event->key.keysym.keycode == SDLK_TAB ) { // Key on current keyboard //
//		if ( Event->key.keysym.scancode == SDL_SCANCODE_TAB ) { // Key on all keyboards //

		if ( (Event->key.keysym.scancode == SDL_SCANCODE_RETURN) && (Event->key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ) {
			Screen::ToggleScreens();
		}
		else if ( (Event->key.keysym.scancode == SDL_SCANCODE_F4) && (Event->key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ) {
			Log( "> ALT+F4 Kill Signal Recieved" );
			return true;
		}
		#ifndef ndebug
		// Only I use F10 as a standard exit key, so remove it when a release build //
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F10 ) {
			Log( "> F10 Kill Signal Recieved" );
			return true;
		}
		#endif // ndebug //
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F12 ) {
			if ( Screen::Native.Size() > 1 ) {
				if ( Screen::Native[1].HasWindow() ) {
					Screen::RemoveScreens();
				}
				else {
					Screen::AddScreens();
				}
			}
		}
	}
	else if ( Event->type == SDL_WINDOWEVENT ) {
		VVLog( "**** [%i] %s [%i,%i]", Event->window.windowID, SDL_WindowEventName( Event->window.event ), Event->window.data1, Event->window.data2 );
		
		int WindowIndex = Screen::GetIndexByWindowID( Event->window.windowID );
			
		if ( WindowIndex >= 0 ) {
			if ( Event->window.event == SDL_WINDOWEVENT_MOVED ) {
				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED ) {	// Preferred //
				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_CLOSE )  {
				Log( "> SDL_WINDOWEVENT_CLOSE Signal Recieved from Window %i", Event->window.windowID );
				return true;		
			}
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int Step() {
	// Poll Input //
	PollInput();

	// Poll Events //
	SDL_Event Event;
	while ( SDL_PollEvent(&Event) ) {
		return_if( EventHandler( 0, &Event ) );
	}
		
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
void Draw( const Screen::cNative& Native ) {
	glMatrixMode( GL_PROJECTION | GL_MODELVIEW );
	glLoadIdentity();
	
	float NewSize = 320.0f * Native.GetAspectRatio();
	glOrtho(
		-320,320,
		NewSize,-NewSize,
		0,1
		);

	float x = 0;
	float y = 0;
	static float r = 0;
	r += 0.5f;
    // Draw //
    glClearColor(0,0,0,1); // Use OpenGL commands, see the OpenGL reference.
    glClear(GL_COLOR_BUFFER_BIT); // clearing screen
    glRotatef(r,0.0f,0.0f,1.0f);  // rotating everything
    glBegin(GL_QUADS); // drawing a multicolored triangle
		glColor3f(1.0f,0.0f,0.0f); glVertex2f(x-90.0f, y+90.0f);
		glColor3f(1.0f,1.0f,1.0f); glVertex2f(x+90.0f, y+90.0f);
		glColor3f(0.0f,1.0f,0.0f); glVertex2f(x+90.0f, y-90.0f);
		glColor3f(0.0f,0.0f,1.0f); glVertex2f(x-90.0f, y-90.0f);
    glEnd();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <signal.h>
// - ------------------------------------------------------------------------------------------ - //
void term_func( int Signal ) {
	ELog( "SIGTERM (Terminate) recieved -- %i", Signal );
	LogFlush();
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //
void int_func( int Signal ) {
	ELog( "\nSIGINT (Interrupt) recieved (CTRL+C) -- %i", Signal );
	LogFlush();
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	LogInit();
	
	signal( SIGTERM, term_func );
	signal( SIGINT, int_func );
	
	// *** //

	Log( "-=======- GEL2 Application Started -- SDL2 Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2013 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	Log( "SVN Revision: %i", SVN_VERSION );
	Log( "Compiled on: %s %s", __DATE__, __TIME__ );
	
	ReportCompilerVersion();
	Log( "Using DrMinGW: %s", (InitDrMinGW() ? "No" : "Yes") );
	ReportSDLVersion();
	
	AppInit( argc, argv );

	// **** //

	gelNetInit();
		
	// **** //
	
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
	SDL_GL_LoadLibrary( NULL );
	SDL_DisableScreenSaver();
	atexit(SDL_Quit);
	atexit(SDL_GL_UnloadLibrary);
	atexit(SDL_EnableScreenSaver);
	
	ReportSDLSystemInfo();
	ReportSDLGraphicsInfo();
	ReportSDLInputInfo();

	// **** //
	
	Screen::InitNative();
	
	// **** //

	{
		cApp App;
		
		bool ExitApp = false;
		while ( !ExitApp ) {
			ExitApp = Step();
			App.Step();

			// For All Screens //
			for ( size_t idx = 0; idx < Screen::Native.Size(); idx++ ) {
				if ( Screen::Native[idx].pWindow ) {
					Screen::Native[idx].MakeCurrent();
					
					Draw( Screen::Native[idx] );		
					App.Draw(); // TODO: Something //
					
					Screen::Native[idx].Swap();
				}
			}
			Wait(5);
		}
	}

	// **** //
	
	Log( "+ Shutdown Started..." );
	Screen::DestroyNative();
	Log( "- Shutdown Complete." );
	
	// **** //

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
