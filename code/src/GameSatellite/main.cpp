// - ------------------------------------------------------------------------------------------ - //
#include <SDL2/SDL.h>
#include <gl/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Timer/Timer.h>
#include <Core/GelError.h>
#include <Util/return_if.h>
// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //

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
void ReportSDLGraphicsInfo() {
	{
		// NOTE: Not very useful. Number of drivers compiled in to SDL. //
		Log( "-=- SDL Video Drivers (not very useful) -=-" );
		for( int idx = 0; idx < SDL_GetNumVideoDrivers(); idx++ ) {			
			Log( "%i - %s", idx, SDL_GetVideoDriver( idx ) );
		}
		Log("");
	}
	
	{
		Log( "-=- Video Displays -=-" );
		for( int idx = 0; idx < SDL_GetNumVideoDisplays(); idx++ ) {
			SDL_DisplayMode Mode;
			SDL_GetDesktopDisplayMode( idx, &Mode );

			SDL_Rect Rect;
			SDL_GetDisplayBounds( idx, &Rect );
			
			Log( "%i - %i, %i at %i Hz [%x] -- Location: %i, %i (%i,%i)", 
				idx, 
				Mode.w, Mode.h, Mode.refresh_rate, Mode.format, 
				Rect.x, Rect.y, Rect.w, Rect.h 
				);
		}
		Log("");
	}	
}
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
			Log( "argv[%i]: \"%s\"", idx, argv[idx] );	
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
#include <Core/GelArray.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Screen {
// - ------------------------------------------------------------------------------------------ - //
// TODO: Derive from cNativeBase. Base is the only one visible to game code. //
class cNative {
	int Index;					// Stored Index... it's either this or pass it in always //
public:
	SDL_Rect DisplayBounds;		// x,y,w,h of the Actual Display //
	SDL_Rect Bounds;			// x,y,w,h of the Window //
	SDL_Window* pWindow;		// Opaque. No direct access to members. //
	SDL_GLContext GLContext;	// (void*) //

public:
	inline cNative() :
		Index( 0 ),
		pWindow( 0 ),
		GLContext( 0 )
	{
	}

public:
	// Outside Interface. Call these only after creating a Window. //
	const int GetWidth() const {
		return Bounds.w;
	}
	const int GetHeight() const {
		return Bounds.h;
	}
	const int GetX() const {
		return Bounds.x;
	}
	const int GetY() const {
		return Bounds.y;
	}
	
	// TODO: Some sort of "IsAvailable" //

public:	
	// Call when you just want the NativeScreen to know it's own bounds //
	inline GelError Init( const int _Index ) {
		Index = _Index;
		
		return_if( GetDisplayBounds() );
		
		return GEL_OK;
	}
	
	// Call when you want to create a Window and Context for this screen //
	inline GelError InitWindow( const int _Index, const bool FullScreen = true ) {
		Index = _Index;
		
		return_if( GetDisplayBounds() );
		
		return_if( NewWindow( FullScreen ) );

		return_if( NewGLContext() );
		
		return GEL_OK;
	}
		
	inline GelError Destroy() {
		return_if( DeleteGLContext() );
		return_if( DeleteWindow() );
		return GEL_OK;
	}
	
	inline const int GetIndex() const {
		return Index;
	}
	
	inline GelError MakeCurrent() { // const?
		return SDL_GL_MakeCurrent( pWindow, GLContext );
	}

	inline GelError Swap() { // const?
		SDL_GL_SwapWindow( pWindow );
		return GEL_OK;
	}
	
	inline GelError UpdateViewport( const bool FullScreen ) const {
		glViewport( 0, 0, Bounds.w, Bounds.h );
		
		return GEL_OK;
	}

	inline bool HasWindow() const {
		return pWindow;
	}
	inline bool HasGLContext() const {
		return GLContext;
	}
	
	// Call me inside Resize and Move events so the Bounds are updated correctly //
	inline GelError UpdateBounds() {
		if ( HasWindow() ) {
			SDL_GetWindowPosition( pWindow, &Bounds.x, &Bounds.y );
			SDL_GetWindowSize( pWindow, &Bounds.w, &Bounds.h );
		}
		return GEL_OK;
	}
		
public:
	inline GelError GetDisplayBounds() {
		return_if( SDL_GetDisplayBounds( Index, &DisplayBounds ) );
		return GEL_OK;
	}
	
	inline GelError NewWindow( const int Width, const int Height, const bool FullScreen ) {
		return_if( DeleteWindow() );

		pWindow = SDL_CreateWindow(
			FullProductName, 						// Window Title //
			SDL_WINDOWPOS_CENTERED_DISPLAY(Index),	// Window Position X //
			SDL_WINDOWPOS_CENTERED_DISPLAY(Index),	// Window Position Y //
			Width, Height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (FullScreen ? SDL_WINDOW_FULLSCREEN : 0) | ((FullScreen && (Index==0)) ? SDL_WINDOW_INPUT_GRABBED : 0)
			);
		
		// SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE
		
		if ( FullScreen ) {
			return_if_Log( pWindow == NULL, "! Error Creating Full Screen Window[%i]: %s", Index, SDL_GetError() );
			Log( "* Full Screen Window %i with ID %i Created", Index, SDL_GetWindowID( pWindow ) );
		}
		else {
			return_if_Log( pWindow == NULL, "! Error Creating Window[%i]: %s", Index, SDL_GetError() );
			Log( "* Window %i with ID %i Created", Index, SDL_GetWindowID( pWindow ) );
		}

		return_if( UpdateBounds() );		
		
		return_if( MakeCurrent() );
		
		return_if( UpdateViewport( FullScreen ) );
		
		return GEL_OK;
	}

	// Creates a Window based on the knowledge of the DisplayBounds //
	inline GelError NewWindow( const bool FullScreen ) {
		float Scalar = 1.0f;
		if ( !FullScreen ) {
			Scalar = 0.8f;
		}

		return NewWindow( 
			(int)((float)DisplayBounds.w * Scalar),
			(int)((float)DisplayBounds.h * Scalar),
			FullScreen 
			);
	}

	inline GelError DeleteWindow() {
		if ( HasWindow() ) {
			Log( "* Window %i with ID %i Destroyed", Index, SDL_GetWindowID( pWindow ) );
			SDL_DestroyWindow( pWindow );
			pWindow = 0;
		}
		return (GelError)pWindow; // Should always be zero //
	}
	
	inline GelError NewGLContext() {
		return_if( DeleteGLContext() );
		
		Assert( pWindow == 0, "Window not created before SDL_GL_CreateContext called" );
		
		GLContext = SDL_GL_CreateContext( pWindow );
		
		return_if_Log( GLContext == NULL, "! Error Creating GLContext %i: %i", Index, GLContext );
		Log( "* GLContext %i Created: %i", Index, GLContext );
		
		return GEL_OK;
	}
	
	inline GelError DeleteGLContext() {
		if ( HasGLContext() ) {
			Log( "* GLContext %i Destroyed: %i", Index, GLContext );
			SDL_GL_DeleteContext( GLContext );
			GLContext = 0;
		}
		return (GelError)GLContext;	// Should always be zero //
	}
};
// - ------------------------------------------------------------------------------------------ - //
bool FullScreen = false;
cGelArray<cNative> Native;
// - ------------------------------------------------------------------------------------------ - //
void InitNative() {
	FullScreen = false;

	const size_t NumVideoDisplays = SDL_GetNumVideoDisplays();
	Native = new_GelArray<cNative>( NumVideoDisplays );
	
	// Init the Bounds, Window and GL Context for the first display //
	Native[0].InitWindow( 0, FullScreen );

	// Only Init the Bounds for the rest of the displays //
	for ( size_t idx = 1; idx < NumVideoDisplays; idx++ ) {
		Native[idx].Init( idx );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void DestroyNative() {
	for ( size_t idx = 0; idx < Native.Size(); idx++ ) {
		Native[idx].Destroy();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleScreens( const bool _FullScreen ) {
	FullScreen = _FullScreen;

	for ( size_t idx = 0; idx < Native.Size(); idx++ ) {
		if ( Native[idx].HasWindow() ) { // Only toggle if there is a Window. Otherwise ignore //
			Native[idx].NewWindow( FullScreen );
		}
	}
	
	Assert( !Native[0].HasWindow(), "Screen 0 has no Window" );
	SDL_RaiseWindow( Native[0].pWindow ); // Make [0] the focus Window //
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleScreens() {	
	ToggleScreens( !FullScreen );
}
// - ------------------------------------------------------------------------------------------ - //
void AddScreen( const int Index ) {
	Warning( Index < 0, "Invalid Index: %i [%i]", Index, Native.Size() );
	Warning( Index >= Native.Size(), "Invalid Index: %i [%i]", Index, Native.Size() );
	
	Native[Index].NewWindow( FullScreen );
	
	if ( !Native[Index].HasGLContext() ) {
		Native[Index].NewGLContext();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void RemoveScreen( const int Index ) {
	Warning( Index < 0, "Invalid Index: %i [%i]", Index, Native.Size() );
	Warning( Index >= Native.Size(), "Invalid Index: %i [%i]", Index, Native.Size() );
	
	Native[Index].DeleteWindow();
}
// - ------------------------------------------------------------------------------------------ - //
void AddScreens() {
	for ( size_t idx = 1; idx < Native.Size(); idx++ ) {
		AddScreen( idx );
	}

	Assert( !Native[0].HasWindow(), "Screen 0 has no Window" );
	SDL_RaiseWindow( Native[0].pWindow ); // Make [0] the focus Window //
}
// - ------------------------------------------------------------------------------------------ - //
void RemoveScreens() {
	for ( size_t idx = 1; idx < Native.Size(); idx++ ) {
		RemoveScreen( idx );
	}

	Assert( !Native[0].HasWindow(), "Screen 0 has no Window" );
	SDL_RaiseWindow( Native[0].pWindow ); // Make [0] the focus Window //
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Screen //
// - ------------------------------------------------------------------------------------------ - //


/*
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
		if ( GLContext[idx] != 0 ) {
			Log( "* GLContext %i Destroyed", idx );
			SDL_GL_DeleteContext( GLContext[idx] );
			GLContext[idx] = 0;
		}
		
		if ( pWindow[idx] != 0 ) {
			Log( "* Window %i with ID %i Destroyed", idx, SDL_GetWindowID( pWindow[idx] ) );
			SDL_DestroyWindow( pWindow[idx] );
			pWindow[idx] = 0;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
*/
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


/*
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
	
			// Don't delete GL Context. Bad drivers crash if you do it too much. //
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
*/
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
			Screen::ToggleScreens();
		}
		else if ( (Event.key.keysym.scancode == SDL_SCANCODE_F4) && (Event.key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ) {
			Log( "> ALT+F4 Kill Signal Recieved" );
			return true;
		}
		else if ( Event.key.keysym.scancode == SDL_SCANCODE_F10 ) {
			Log( "> F10 Kill Signal Recieved" );
			return true;
		}
		else if ( Event.key.keysym.scancode == SDL_SCANCODE_F12 ) {
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
	
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
void Draw( const int Index = 0 ) {
	glMatrixMode( GL_PROJECTION | GL_MODELVIEW );
	glLoadIdentity();
	
	float Aspect = (float)Screen::Native[Index].GetHeight() / (float)Screen::Native[Index].GetWidth();
	
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
	
	ReportSDLGraphicsInfo();

	// **** //
	
	Screen::InitNative();
	
	// **** //

	{
		cApp App;
		
		bool ExitApp = false;
		while ( !ExitApp ) {
			ExitApp = Step();
			
			App.Step();
			App.Draw();

			for ( int idx = 0; idx < Screen::Native.Size(); idx++ ) {
				if ( Screen::Native[idx].pWindow ) {
					Screen::Native[idx].MakeCurrent();
					
					Draw( idx );		
					
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
