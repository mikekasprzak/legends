// - ------------------------------------------------------------------------------------------ - //
#include <SDL2/SDL.h>
#include <gl/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Timer/Timer.h>
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef __unix
#include <unistd.h>		// getpid()
#endif // __unix //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef PRODUCT_SKU
	#define PRODUCT_SKU		"UNKNOWN"
	
	const char* ProductName = "Unknown";
	const char* FullProductName = "Unknown (?) v0.0";
#endif // PRODUCT_SKU //
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
void AppInit( int argc, char* argv[] ) {
	Log( "-=- Application Execution Info -=-" );
	
	// Process ID //
	{
#ifdef _WIN32
		Log( "PID: %i", GetCurrentProcessId() );
#elif defined(__unix)
		Log( "PID: %i", (int)getpid() );
#endif // _WIN32 //
	}

	// Show Command Line //
	{
		Log( "Command Line Arguments: %i", argc );
		for ( int idx = 0; idx < argc; idx++ ) {
			Log( "* argv[%i]: \"%s\"", idx, argv[idx] );	
		}
	}

	// Get Base Directory //
	{	
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
		
		Log( "Base Directory: %s", AppBaseDir );
		Log( "Save Directory: %s", AppSaveDir );
		Log( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define MAX_SDL_DISPLAYS	16
#define MAX_SDL_WINDOWS		16
SDL_Rect Display[MAX_SDL_DISPLAYS];
SDL_Window* pWindow[MAX_SDL_WINDOWS];
SDL_GLContext GLContext[MAX_SDL_WINDOWS];	// (void*) //
bool FullScreen = false;
// - ------------------------------------------------------------------------------------------ - //
void ToggleFullScreen( const int Index ) {
	SDL_Window* Old = pWindow[Index];
	if ( Old ) {
		Log( "* Window ID %i Destroyed", SDL_GetWindowID( Old ) );
		SDL_DestroyWindow( Old );
	}

	const int Width = Display[Index].w;
	const int Height = Display[Index].h;

//	const int WPx = Display[Index].x + ((Display[Index].w - Width) >> 1);
//	const int WPy = Display[Index].y + ((Display[Index].h - Height) >> 1);
	
	pWindow[Index] = SDL_CreateWindow(
		FullProductName,
		SDL_WINDOWPOS_CENTERED_DISPLAY(Index),//WPx,//SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_CENTERED_DISPLAY(Index),//Py,//SDL_WINDOWPOS_UNDEFINED,
		Width, Height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | ((Index==0) ? SDL_WINDOW_INPUT_GRABBED : 0)
		);
		
	// SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE, SDL_WINDOW_INPUT_GRABBED, SDL_WINDOW_FULLSCREEN

	if ( pWindow[Index] == NULL ) {
		Log( "! Error Creating Full Screen Window[%i]: %s", Index, SDL_GetError() );
		return;
	}
	else {
		Log( "* Full Screen Window %i with ID %i Created", Index, SDL_GetWindowID( pWindow[Index] ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleFullScreen() {
	for ( int idx = 0; idx < MAX_SDL_WINDOWS; idx++ ) {
		if ( pWindow[idx] ) {
			ToggleFullScreen(idx);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleWindowed( const int Index ) {
	SDL_Window* Old = pWindow[Index];
	Log( "* Window ID %i Destroyed", SDL_GetWindowID( Old ) );
	SDL_DestroyWindow( Old );

	const int Width = Display[Index].w * 80 / 100;
	const int Height = Display[Index].h * 80 / 100;

//	const int WPx = Display[Index].x + ((Display[Index].w - Width) >> 1);
//	const int WPy = Display[Index].y + ((Display[Index].h - Height) >> 1);
	
	pWindow[Index] = SDL_CreateWindow(
		FullProductName,
		SDL_WINDOWPOS_CENTERED_DISPLAY(Index),//WPx,//SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_CENTERED_DISPLAY(Index),//WPy,//SDL_WINDOWPOS_UNDEFINED,
		Width, Height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		);

	// SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE, SDL_WINDOW_INPUT_GRABBED, SDL_WINDOW_FULLSCREEN

	if ( pWindow[Index] == NULL ) {
		Log( "! Error Creating Window[%i]: %s", Index, SDL_GetError() );
		return;
	}
	else {
		Log( "* Window %i with ID %i Created", Index, SDL_GetWindowID( pWindow[Index] ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleWindowed() {
	for ( int idx = 0; idx < MAX_SDL_WINDOWS; idx++ ) {
		if ( pWindow[idx] ) {
			ToggleWindowed(idx);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleScreen( const int Index ) {
	if ( FullScreen ) {
		ToggleFullScreen( Index );
	}
	else {
		ToggleWindowed( Index );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleScreen() {
	if ( FullScreen ) {
		ToggleFullScreen();
	}
	else {
		ToggleWindowed();
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int InitSDLWindows() {
	memset( pWindow, 0, sizeof(pWindow) );
	memset( Display, 0, sizeof(Display) );
	memset( GLContext, 0, sizeof(GLContext) );
	
	FullScreen = false;

	{
		// NOTE: Not very useful. Number of drivers compiled in to SDL. //
		VVLog( "-=- SDL Video Drivers (not very useful) -=-" );
		for( int idx = 0; idx < SDL_GetNumVideoDrivers(); idx++ ) {			
			VVLog( "%i - %s", idx, SDL_GetVideoDriver( idx ) );
		}
		VVLog("");
	}
	
	{
		Log( "-=- Video Displays -=-" );
		for( int idx = 0; idx < SDL_GetNumVideoDisplays(); idx++ ) {
			SDL_DisplayMode Mode;
			SDL_GetDesktopDisplayMode( idx, &Mode );

			SDL_Rect* Rect;
			SDL_GetDisplayBounds( idx, &Display[idx] );
			Rect = &Display[idx];
			
			Log( "%i - %i, %i at %i Hz [%x] -- Location: %i, %i (%i,%i)", 
				idx, 
				Mode.w, Mode.h, Mode.refresh_rate, Mode.format, 
				Rect->x, Rect->y, Rect->w, Rect->h 
				);
		}
		Log("");
	}

	int Index = 0;	
	{
		ToggleWindowed(Index);

		GLContext[Index] = SDL_GL_CreateContext( pWindow[Index] );
		if ( GLContext[Index] == 0 ) {
			Log( "! Error Creating GLContext[%i]", Index );
			return 1;
		}
		else {
			Log( "* Primary GLContext Created" );
		}
		
		// TODO: GL //
	}
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
void DestroySDLWindows() {
	for( int idx = 0; idx < MAX_SDL_WINDOWS; idx++ ) {
		if ( GLContext[idx] != 0 )
			SDL_GL_DeleteContext( GLContext[idx] );
		
		if ( pWindow[idx] != 0 ) {
			Log( "* Window %i with ID %i Destroyed", idx, SDL_GetWindowID( pWindow[idx] ) );
			SDL_DestroyWindow( pWindow[idx] );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void UpdateScreens() {
	for( int idx = 0; idx < SDL_GetNumVideoDisplays(); idx++ ) {
		if ( pWindow[idx] ) {
			int Width;
			int Height;
			SDL_GetWindowSize( pWindow[idx], &Width, &Height );
	
			SDL_GL_MakeCurrent( pWindow[idx], GLContext[idx] );
			glViewport( 0,0, Width, Height );
		}
	}
	SDL_RaiseWindow( pWindow[0] );
}
// - ------------------------------------------------------------------------------------------ - //
void AddScreens() {
	// TODO: Replace with better test. Keep a count of active pWindows //
	if ( pWindow[1] == 0 ) {

		for( int idx = 1; idx < SDL_GetNumVideoDisplays(); idx++ ) {			
			ToggleScreen(idx);

			if ( GLContext[idx] == 0 ) {
				GLContext[idx] = SDL_GL_CreateContext( pWindow[idx] );
			}
		}
		
		// Do first one like this //
		ToggleScreen(0);
	}
	else {
		for( int idx = 1; idx < SDL_GetNumVideoDisplays(); idx++ ) {
			if ( pWindow[idx] ) {
				SDL_DestroyWindow( pWindow[idx] );
				pWindow[idx] = 0;
			}
	
//			if ( GLContext[idx] ) {
//				SDL_GL_DeleteContext( GLContext[idx] );
//				GLContext[idx] = 0;
//			}
		}

		// Do first one like this //
		ToggleScreen(0);
	}
	
	UpdateScreens();
}

// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int Step() {
	SDL_Event Event;
	SDL_PollEvent(&Event);
	if ( Event.type == SDL_QUIT ) {
		return true;
	}
	else if ( Event.type == SDL_KEYUP ) {
//		if ( Event.key.keysym.keycode == SDLK_TAB ) { // Key on current keyboard //
//		if ( Event.key.keysym.scancode == SDL_SCANCODE_TAB ) { // Key on all keyboards //

		if ( (Event.key.keysym.scancode == SDL_SCANCODE_RETURN) && (Event.key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ) {
			FullScreen = !FullScreen;
			ToggleScreen();
			UpdateScreens();
		}
		else if ( Event.key.keysym.scancode == SDL_SCANCODE_F10 ) {
			return true;
		}
		else if ( Event.key.keysym.scancode == SDL_SCANCODE_F12 ) {
			AddScreens();
		}
	}
	
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
void Draw( const int Index = 0 ) {
	glMatrixMode( GL_PROJECTION | GL_MODELVIEW );
	glLoadIdentity();
	
	int w, h;
	SDL_GetWindowSize( pWindow[Index], &w, &h );
	float Aspect = (float)h / (float)w;
	
	float NewSize = 320.0f * Aspect;
	glOrtho(
		-320,320,
		NewSize,-NewSize,
		0,1
		);

	float x = 0;
	float y = 0;
	static float r = 0;
	r += 0.5;
    // Draw //
    glClearColor(0,0,0,1); // Use OpenGL commands, see the OpenGL reference.
    glClear(GL_COLOR_BUFFER_BIT); // clearing screen
    glRotatef(r,0.0,0.0,1.0);  // rotating everything
    glBegin(GL_QUADS); // drawing a multicolored triangle
		glColor3f(1.0,0.0,0.0); glVertex2f(x-90.0, y+90.0);
		glColor3f(1.0,1.0,1.0); glVertex2f(x+90.0, y+90.0);
		glColor3f(0.0,1.0,0.0); glVertex2f(x+90.0, y-90.0);
		glColor3f(0.0,0.0,1.0); glVertex2f(x-90.0, y-90.0);
    glEnd();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <signal.h>
// - ------------------------------------------------------------------------------------------ - //
void term_func( int Signal ) {
	printf( "SIGTERM (Terminate) recieved -- %i\n", Signal );
	LogFlush();
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //
void int_func( int Signal ) {
	printf( "\nSIGINT (Interrupt) recieved (CTRL+C) -- %i\n", Signal );
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
	
	// **** //
	
	InitSDLWindows();
	
	// **** //

	{
		cApp App;
		LogFlush();
		
		bool ExitApp = false;
		while ( !ExitApp ) {
			ExitApp = Step();
			
			App.Step();
			App.Draw();

			for ( int idx = 0; idx < MAX_SDL_WINDOWS; idx++ ) {
				if ( pWindow[idx] ) {
					SDL_GL_MakeCurrent( pWindow[idx], GLContext[idx] );
					
					Draw( idx );		
					
					SDL_GL_SwapWindow( pWindow[idx] );
				}
			}
			Wait(5);
		}
	}

	// **** //

	DestroySDLWindows();

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
