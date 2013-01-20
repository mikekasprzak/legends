// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <API/API_OpenGL2.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Timer/Timer.h>
#include <DrMinGW/DrMinGW.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Main/Main_Product.h>
#include <Main/Main_SVNVersion.h>
#include <Main/Main_SDL_InitLog.h>

#include <System/System.h>
#include <Screen/Screen.h>
#include <Search/Search.h>
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <System/Path.h>

//extern char AppBaseDir[];
//char AppBaseDir[2048];
//
//extern char AppSaveDir[];
//char AppSaveDir[2048] = "";
// - ------------------------------------------------------------------------------------------ - //
// TODO: Rename this. ArgInit? SystemInit? Only non arg is the PID
void ArgInit( int argc, char* argv[] ) {
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
				strcpy( System::BaseDir, argv[2] );
				DetermineContentPath = false;
			}
		}

		bool DetermineSavePath = true;
		if ( argc > 4 ) {
			if ( strcmp( argv[3], "-SAVE" ) == 0 ) {
				strcpy( System::SaveDir, argv[4] );
				DetermineSavePath = false;
			}
		}
		
		if ( DetermineContentPath )
			gelGetContentPath( System::BaseDir, sizeof(System::BaseDir) );

		if ( DetermineSavePath )
			gelGetStoragePath( System::SaveDir, sizeof(System::SaveDir) );
		
		Log( "Base Directory: %s", System::BaseDir );
		Log( "Save Directory: %s", System::SaveDir );
		Log( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
bool KillSignal = false;
// - ------------------------------------------------------------------------------------------ - //
int EventHandler( void* /*UserData*/, SDL_Event* Event ) {
	extern bool KillSignal;
	
	if ( Event->type == SDL_QUIT ) {
		Log( "> SDL_QUIT Signal Recieved" );
		KillSignal = true;
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
			KillSignal = true;
			return true;
		}
		#ifndef ndebug
		// Only I use F10 as a standard exit key, so remove it when a release build //
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F10 ) {
			Log( "> F10 Kill Signal Recieved" );
			KillSignal = true;
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
			if ( Event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED ) {
				System::GainFocus();
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_FOCUS_LOST ) {
				System::LoseFocus();
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_MOVED ) {
				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED ) {	// Preferred //
				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_CLOSE )  {
				Log( "> SDL_WINDOWEVENT_CLOSE Signal Recieved from Window %i", Event->window.windowID );
				KillSignal = true;
				return true;		
			}
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#include <signal.h>
// - ------------------------------------------------------------------------------------------ - //
void term_func( int Signal ) {
	Log( "\nSIGTERM (Terminate) recieved -- %i", Signal );
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //
void int_func( int Signal ) {
	Log( "\nSIGINT (Interrupt) recieved (CTRL+C) -- %i", Signal );
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //
#include <Node/GelList.h>
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	LogInit();
	
	signal( SIGTERM, term_func );
	signal( SIGINT, int_func );
	
	// *** //
	
	{
		GelList<int> MyList;
		MyList.Insert( 11, MyList.Front() );
		MyList.Insert( 12, MyList.Front()->Next );
		MyList.Insert( 10, MyList.Back() );
		MyList.Insert( 11, MyList.Back() );
//		MyList.Insert( 12, MyList.Back()->Prev );
//		MyList.Insert( 15, MyList.Front() );
		Log( "NOM: %i", MyList.Remove( MyList.Front()->Next ) );
		
		MyList.PushFront( 13 );
		MyList.PushBack( 20 );
		MyList.PushBack( 23 );
		MyList.PushFront( 10 );
//		Log( "NOM: %i", MyList.PopFront() );
//		Log( "NOM: %i", MyList.PopFront() );
		Log( "NOM: %i", MyList.PopBack() );
		Log( "NOM: %i", MyList.PopBack() );
		Log( "NOM: %i", MyList.PopBack() );
		Log( "NOM: %i", MyList.PopBack() );
		MyList.PushBack( 55 );
		
		GelList<int> List2;
		MyList.Move( MyList.Front()->Next, &List2, List2.Front() );
		MyList.Move( MyList.Back()->Prev, &List2, List2.Back() );

		MyList.Logs();
		List2.Logs();
	}

	Log( "-=======- GEL2 Application Started -- SDL2 Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2013 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	Log( "SVN Revision: %i", SVN_VERSION );
	Log( "Compiled on: %s %s", __DATE__, __TIME__ );
	
	ReportCompilerVersion();
	#ifdef USES_MINGW
	Log( "Using DrMinGW: %s", (InitDrMinGW() ? "No" : "Yes") );
	#endif // USES_MINGW //
	ReportSDLVersion();
	
	ArgInit( argc, argv );

	// **** //

	gelNetInit();
		
	// **** //
	
	SDL_Init( SDL_INIT_VIDEO /*| SDL_INIT_JOYSTICK*/ );
	SDL_GL_LoadLibrary( NULL );
	SDL_DisableScreenSaver();
	atexit(SDL_Quit);
	atexit(SDL_GL_UnloadLibrary);
	atexit(SDL_EnableScreenSaver);
	
	ReportSDLSystemInfo();
	ReportSDLGraphicsInfo();
	
	// **** //
	
	Log( "+ Creating Primary Window..." );
	Screen::InitNative();
	Log( "- Primary Window Created.\n" );

	// **** //

	System::Init();
	Search::Init();
	Input::Init();
	Render::Init();
	
	// **** //

	{
		cApp App;
		SDL_SetEventFilter( EventHandler, 0 );
		
		Log( "Mem: %i", System::GetMemoryUsage() );
		
		extern bool KillSignal;
		while ( !KillSignal ) {
			Input::Poll();
			SDL_PumpEvents();
			App.Step();

			// For All Screens //
			for ( size_t idx = 0; idx < Screen::Native.Size(); idx++ ) {
				if ( Screen::Native[idx].pWindow ) {
					Screen::Native[idx].MakeCurrent(); // Memory Leak //
					
					App.Draw( Screen::Native[idx] );
					
					Screen::Native[idx].Swap(); // Memory Leak //
				}
			}
			
			{
				static int MemDrop = 0;
				MemDrop++;
				if ( (MemDrop & 255) == 255 )
					Log( "Mem: %i (%i) -- %s", System::GetMemoryUsage(), System::GetMemoryUsage() / 1024, System::GetClockShortString() );
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
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
