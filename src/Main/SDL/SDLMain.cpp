// - ------------------------------------------------------------------------------------------ - //
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //

#include <Timer/Timer.h>
#include <System/Path.h>

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_WEBOS)
// - ------------------------------------------------------------------------------------------ - //
#include <PDL.h>
#include <PDLPatch.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_MACOSX)
// - ------------------------------------------------------------------------------------------ - //
#include <mach-o/dyld.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_UNIX)
// - ------------------------------------------------------------------------------------------ - //
#include <unistd.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_LEGACY_SMILES
#include <ProductInfo.h>
#endif // PRODUCT_LEGACY_SMILES
// - ------------------------------------------------------------------------------------------ - //
#include <GameHost.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_LEGACY_SMILES
#include "Sound/SoundPlayer.h"
#include "Sound/MusicPlayer.h"
#else // PRODUCT_LEGACY_SMILES //
#include <Audio/SoundPlayer.h>
#include <Audio/MusicPlayer.h>
#endif // PRODUCT_LEGACY_SMILES //
// - ------------------------------------------------------------------------------------------ - //
#include <Core/Data.h>
#include <Graphics/Graphics.h>
#include <Graphics/GraphicsDraw.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //

#ifdef USES_SIXENSE
#include <sixense.h>
#endif // USES_SIXENSE //

//#ifdef USES_MINGW
//#include <io.h>
//#include <fcntl.h>
//
//void ActivateConsole()
//{
//    AllocConsole();
//    
//    HANDLE newConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
//    HANDLE newConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//    
//    int inFd = _open_osfhandle((long)newConsoleInput, _O_TEXT);
//    int outFd = _open_osfhandle((long)newConsoleOutput, _O_TEXT);
//    
//    FILE* consoleIn = _fdopen(inFd, "r");
//    FILE* consoleOut = _fdopen(outFd, "w");
//    
//    setvbuf(consoleIn, NULL, _IONBF, 0);
//    setvbuf(consoleOut, NULL, _IONBF, 0);
//    
//    *stdin = *consoleIn;
//    *stdout = *consoleOut;
//    
//    fprintf( consoleOut, "Hey" );
//}
//#endif // USES_MINGW //

// - ------------------------------------------------------------------------------------------ - //
TIMEVALUE WorkTime;
void SkipTime() {
	WorkTime = GetTimeNow();
}
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

//int CursorTimeout;
//bool HasDetectedMotion;

int EventValue = 0;
// - ------------------------------------------------------------------------------------------ - //
extern int phone_orientation;
int phone_orientation = 0;

extern bool IsActive;
bool IsActive = true;

extern bool RefreshScreen;
bool RefreshScreen = false;

extern char AppBaseDir[];
char AppBaseDir[2048];

extern char AppSaveDir[];
char AppSaveDir[2048] = "";

cGameHost* GameHost = 0;
// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_SDL_1_3
// - ------------------------------------------------------------------------------------------ - //
int SDLWindowStatus = SDL_APPACTIVE;
// - ------------------------------------------------------------------------------------------ - //
#else // USES_SDL_1_3 //
// - ------------------------------------------------------------------------------------------ - //
const char* gels_SDLWindowEventName( Uint8 EventName ) {
	switch( EventName ) {
		case SDL_WINDOWEVENT_NONE:			return "SDL_WINDOWEVENT_NONE";
		case SDL_WINDOWEVENT_SHOWN:			return "SDL_WINDOWEVENT_SHOWN";
		case SDL_WINDOWEVENT_HIDDEN:		return "SDL_WINDOWEVENT_HIDDEN";
		case SDL_WINDOWEVENT_EXPOSED:		return "SDL_WINDOWEVENT_EXPOSED";
		case SDL_WINDOWEVENT_MOVED:			return "SDL_WINDOWEVENT_MOVED";
		case SDL_WINDOWEVENT_RESIZED:		return "SDL_WINDOWEVENT_RESIZED";
		case SDL_WINDOWEVENT_MINIMIZED:		return "SDL_WINDOWEVENT_MINIMIZED";
		case SDL_WINDOWEVENT_MAXIMIZED:		return "SDL_WINDOWEVENT_MAXIMIZED";
		case SDL_WINDOWEVENT_RESTORED:		return "SDL_WINDOWEVENT_RESTORED";
		case SDL_WINDOWEVENT_ENTER:			return "SDL_WINDOWEVENT_ENTER";
		case SDL_WINDOWEVENT_LEAVE:			return "SDL_WINDOWEVENT_LEAVE";
		case SDL_WINDOWEVENT_FOCUS_GAINED:	return "SDL_WINDOWEVENT_FOCUS_GAINED";
		case SDL_WINDOWEVENT_FOCUS_LOST:	return "SDL_WINDOWEVENT_FOCUS_LOST";
		case SDL_WINDOWEVENT_CLOSE:			return "SDL_WINDOWEVENT_CLOSE";
	};
	return "???";
}
// - ------------------------------------------------------------------------------------------ - //
void WindowEventFilter( const SDL_Event& event ) {
	if ( event.type == SDL_WINDOWEVENT ) {
		const SDL_WindowEvent* WindowEvent = (const SDL_WindowEvent*)&event;
		
		VVLog("> WindowEvent: %s", gels_SDLWindowEventName( WindowEvent->event ) );
		
		switch ( WindowEvent->event ) {
			case SDL_WINDOWEVENT_SHOWN: {
				// Window has been shown //
				break;
			}
			case SDL_WINDOWEVENT_HIDDEN: {
				// Window has been hidden //
				break;
			}
			case SDL_WINDOWEVENT_EXPOSED: {
				// Window has been exposed, and should be redrawn //
				break;
			}
			case SDL_WINDOWEVENT_MOVED: {
				// Window has been moved to data1, data2 //
				break;
			}
			case SDL_WINDOWEVENT_RESIZED: {
				// Window size changed to data1 x data2 //
				break;
			}
			case SDL_WINDOWEVENT_MINIMIZED: {
				// Window has been minimized //
				break;
			}
			case SDL_WINDOWEVENT_MAXIMIZED: {
				// Window has been maximized //
				break;
			}
			case SDL_WINDOWEVENT_RESTORED: {
				// Window has been restored to normal size and position //
				break;
			}
			case SDL_WINDOWEVENT_ENTER: {
				// Window has gained mouse focus (hover) //
				if ( cGameSupport::Current() )
					cGameSupport::Current()->MouseEventWindowFocus( true );

				break;
			}
			case SDL_WINDOWEVENT_LEAVE: {
				// Window has lost mouse focus (hover) //
				if ( cGameSupport::Current() )
					cGameSupport::Current()->MouseEventWindowFocus( false );

				break;
			}
			case SDL_WINDOWEVENT_FOCUS_GAINED: {
				// Window has gained keyboard focus //
				SkipTime();
				IsActive = true;
#ifndef PRODUCT_NOMOUSECURSOR
				SDL_ShowCursor( SDL_DISABLE );
#endif // PRODUCT_NOMOUSECURSOR //
				musResume();
				musUpdate();

#ifndef PRODUCT_LEGACY_SMILES
				if ( GameHost ) {
					GameHost->GotFocus();
				}
#endif // PRODUCT_LEGACY_SMILES //
				
				break;
			}
			case SDL_WINDOWEVENT_FOCUS_LOST: {
				// Window has lost keyboard focus //
#ifndef PRODUCT_LEGACY_SMILES
				if ( GameHost ) {
					GameHost->LostFocus();
				}
#endif // PRODUCT_LEGACY_SMILES //

				if ( GameHost )
					GameHost->ForcePaused();

				if ( IsActive )
					RefreshScreen = true;

				IsActive = false;
#ifndef PRODUCT_NOMOUSECURSOR
				SDL_ShowCursor( SDL_ENABLE );
#endif // PRODUCT_NOMOUSECURSOR //
				musPause();
				
				break;
			}
			case SDL_WINDOWEVENT_CLOSE: {
				// Window close button has been pushed //
				System::CloseButtonPressed = true;
				break;
			}
		};
	
		if ( cGameSupport::Current() )
			cGameSupport::Current()->LostFocusEvent( !IsActive );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL_1_3
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_SDL_1_3
// - ------------------------------------------------------------------------------------------ - //
void ActiveEventFilter( const SDL_Event& event ) {
	VVLog( "ACTIVE_EVENT: %i %i (%i %i %i)", event.active.state, event.active.gain, SDL_APPINPUTFOCUS, SDL_APPACTIVE, SDL_APPMOUSEFOCUS );
	
	// Store Active SDL states //
	if ( (event.active.state & SDL_APPACTIVE) ) {
		if ( event.active.gain )
			SDLWindowStatus |= SDL_APPACTIVE;
		else
			SDLWindowStatus &= ~SDL_APPACTIVE;
	}
	if ( (event.active.state & SDL_APPINPUTFOCUS) ) {
		if ( event.active.gain )
			SDLWindowStatus |= SDL_APPINPUTFOCUS;
		else
			SDLWindowStatus &= ~SDL_APPINPUTFOCUS;
	}
	if ( (event.active.state & SDL_APPMOUSEFOCUS) ) {
		if ( event.active.gain )
			SDLWindowStatus |= SDL_APPMOUSEFOCUS;
		else
			SDLWindowStatus &= ~SDL_APPMOUSEFOCUS;
	}
	
	if ( event.active.state & (SDL_APPINPUTFOCUS|SDL_APPACTIVE) ) 
	{
		if ( event.active.gain && (SDLWindowStatus & SDL_APPACTIVE) ) {
			SkipTime();
			IsActive = true;
#ifndef PRODUCT_NOMOUSECURSOR
			SDL_ShowCursor( SDL_DISABLE );
#endif // PRODUCT_NOMOUSECURSOR //
			musResume();
			musUpdate();

#ifndef PRODUCT_LEGACY_SMILES
			if ( GameHost ) {
				GameHost->GotFocus();
			}
#endif // PRODUCT_LEGACY_SMILES //

		}
		else {
#ifndef PRODUCT_LEGACY_SMILES
			if ( GameHost ) {
				GameHost->LostFocus();
			}
#endif // PRODUCT_LEGACY_SMILES //

			if ( GameHost )
				GameHost->ForcePaused();
			if ( IsActive )
				RefreshScreen = true;
			IsActive = false;
#ifndef PRODUCT_NOMOUSECURSOR
			SDL_ShowCursor( SDL_ENABLE );
#endif // PRODUCT_NOMOUSECURSOR //
			musPause();
		}	
	}
	if ( event.active.state & (SDL_APPMOUSEFOCUS) ) {
		if ( cGameSupport::Current() )
			cGameSupport::Current()->MouseEventWindowFocus( event.active.gain );
	}
	
	if ( cGameSupport::Current() )
		cGameSupport::Current()->LostFocusEvent( !IsActive );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // !USES_SDL_1_3 //
// - ------------------------------------------------------------------------------------------ - //

#ifdef USES_ICADE
extern int iCadeStatus;
int iCadeStatus = 0;
#endif // USES_ICADE //

// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_SDL_1_3
int EventFilter( const SDL_Event *event_ptr ) {
#else // USES_SDL_1_3 //
int EventFilter( void*, SDL_Event *event_ptr ) {
#endif // USES_SDL_1_3 //
	const SDL_Event& event = *event_ptr;

	// Lock this thread //	
//	SDL_mutex* ThreadLock = SDL_CreateMutex();
//	SDL_mutexP( ThreadLock );
	
	int RetVal = 1;
	    
    switch( event.type ) {
	    case SDL_VIDEOEXPOSE: {
	    	RefreshScreen = true;
	    	RetVal = 0;
	    	break;	
	    }
		case SDL_KEYDOWN: {
		    switch(event.key.keysym.sym){
#if !defined(NDEBUG) || defined(USES_UNIX)
		    	case SDLK_F10: {
		    		System::CloseButtonPressed = true;
		    		break;
				}
#endif // NDEBUG //

#ifndef NDEBUG
				case SDLK_1: {
					phone_orientation = 0;
					break;
				}
				case SDLK_2: {
					phone_orientation = 1;
					break;
				}
				case SDLK_3: {
					phone_orientation = 2;
					break;
				}
				case SDLK_4: {
					phone_orientation = 3;
					break;
				}
#endif // NDEBUG //

#ifdef USES_WEBOS
				case PDLK_GESTURE_FORWARD:
#endif // USES_WEBOS //
				case SDLK_ESCAPE: {
					EventValue = 1;
					break;
				}

				case SDLK_BACKSPACE: {
					break;
				}
				case SDLK_TAB: {
					break;
				}
				case SDLK_SPACE: {
					break;
				}
				
				case SDLK_F1: {
					EventValue = 9;
					break;
				}
				
				case SDLK_F2: {
					EventValue = 3;
					break;
				}
				
				case SDLK_LEFT: {
					EventValue = 16;
					break;
				}
				
				case SDLK_RIGHT: {
					EventValue = 17;
					break;
				}
				
				case SDLK_UP: {
					EventValue = 18;
					break;
				}
				
				case SDLK_DOWN: {
					EventValue = 19;
					break;
				}

				case SDLK_HOME: {
					break;
				}
				case SDLK_END: {
					break;
				}
				case SDLK_PAGEUP: {
					break;
				}
				case SDLK_PAGEDOWN: {
					break;
				}

#ifdef USES_ICADE
#ifndef USES_ICADE_DVORAK
				// ICADE QWERTY //
				case 'w':
					iCadeStatus |= (1 << 0);
					break;
				case 'e':
					iCadeStatus &= ~(1 << 0);
					break;
				// DOWN //
				case 'x':
					iCadeStatus |= (1 << 1);
					break;
				case 'z':
					iCadeStatus &= ~(1 << 1);
					break;
				// LEFT //
				case 'a':
					iCadeStatus |= (1 << 2);
					break;
				case 'q':
					iCadeStatus &= ~(1 << 2);
					break;
				// RIGHT //
				case 'd':
					iCadeStatus |= (1 << 3);
					break;
				case 'c':
					iCadeStatus &= ~(1 << 3);
					break;
#else // USES_ICADE_DVORAK //				
				// ICADE DVORAK //
				// UP //
				case ',':
					iCadeStatus |= (1 << 0);
					break;
				case '.':
					iCadeStatus &= ~(1 << 0);
					break;
				// DOWN //
				case 'q':
					iCadeStatus |= (1 << 1);
					break;
				case ';':
					iCadeStatus &= ~(1 << 1);
					break;
				// LEFT //
				case 'e':
					iCadeStatus |= (1 << 2);
					break;
				case 'j':
					iCadeStatus &= ~(1 << 2);
					break;
				// RIGHT //
				case 'a':
					iCadeStatus |= (1 << 3);
					break;
				case '\'':
					iCadeStatus &= ~(1 << 3);
					break;
#endif // USES_ICADE_DVORAK //				
#endif // USES_ICADE //

#ifdef USES_MACOSX
				case SDLK_q: {
					//if ( event.key.keysym.mod & KMOD_CTRL ) 
					if ( event.key.keysym.mod & KMOD_META ) 
					{
						System::CloseButtonPressed = true;
					}
					break;
				}
				case SDLK_f: {
					//if ( event.key.keysym.mod & KMOD_CTRL )
					if ( event.key.keysym.mod & KMOD_META )
					{
						// Fullscreen //
//						extern void ToggleGraphicsMode();
//						ToggleGraphicsMode();
					}
					break;
				}
#endif // USES_MACOSX //

#ifdef USES_WINDOWS
				case SDLK_RETURN:
				case SDLK_KP_ENTER: {
					if ( event.key.keysym.mod & KMOD_ALT ) {
						// Fullscreen //
						extern void ToggleGraphicsMode();
						ToggleGraphicsMode();
					}
					break;
				}
#endif // USES_WINDOWS //
				
				default:
					break;
		    }
		    RetVal = 1;
		    break;
		}
		
#ifdef USES_SDL_1_3
		// SDL Touch Code! Currently unsupported //
//		case SDL_FINGERDOWN: {
//			VLog( "* Finger Down!" );
//			break;
//		}
//		case SDL_FINGERUP: {
//			VLog( "* Finger Up!" );
//			break;
//		}
//		case SDL_FINGERMOTION: {
//			VLog( "* Finger Motion!" );
//			break;
//		}
#endif // USES_SDL_1_3

		case SDL_MOUSEBUTTONDOWN: {
#ifdef USES_WEBOS
			if ( event.button.which != 0 ) {
				//return 0;
				RetVal = 0;
				break;
			}
#endif // USES_WEBOS //

			// Note bits in the button mask //
			if ( event.button.button > 0 ) {    			
				int Bit = 1<<(event.button.button-1);
				//VVLog("Click: %i", Bit );
				
				mouse_b |= Bit;
				mouse_b_new |= Bit;
			}
			
			// Button specific //
    		if ( event.button.button == 4 ) {
    			mouse_wheel--;
    		}
    		else if ( event.button.button == 5 ) {
    			mouse_wheel++;
    		}
			else if ( event.button.button > 0 ) {    			
    			mouse_x = event.button.x;
    			mouse_y = event.button.y;
    		}
    		
    		if ( cGameSupport::Current() )
	    		cGameSupport::Current()->MouseEventButtonDown();
   
   			//return 0;
   			RetVal = 0;
    		break;
    	}
    	
    	case SDL_MOUSEMOTION: {
#ifdef USES_WEBOS
			if ( event.motion.which != 0 ) {
				//return 0;
				RetVal = 0;
				break;
			}
#endif // USES_WEBOS //

    		if ( GameHost ) {
	    		if ( GameHost->FirstRun() ) {
	    			//return 0;
	    			RetVal = 0;
	    			break;
	    		}
	    	}

			mouse_x = event.motion.x;
			mouse_y = event.motion.y;

    		if ( cGameSupport::Current() )
	    		cGameSupport::Current()->MouseEventMove();

	    	//return 0;
	    	RetVal = 0;
    		break;	
    	}

    	case SDL_MOUSEBUTTONUP: {
#ifdef USES_WEBOS
			if ( event.button.which != 0 ) {
				//return 0;
				RetVal = 0;
				break;
			}
#endif // USES_WEBOS //

			mouse_b = mouse_b & (~(1<<(event.button.button-1)));

    		if ( cGameSupport::Current() )
	    		cGameSupport::Current()->MouseEventButtonUp();

    		//return 0;
    		RetVal = 0;
    		break;
    	}

#ifndef USES_SDL_1_3
#ifndef USES_WEBOS
		case SDL_ACTIVEEVENT: {
			ActiveEventFilter( event );
	    	break;
	    }
#endif // USES_WEBOS //
#endif // USES_SDL_1_3 //

#ifdef USES_SDL_1_3
		case SDL_WINDOWEVENT: {
			WindowEventFilter( event );
			break;
		}
#endif // USES_SDL_1_3 //
		
		case SDL_QUIT: {
			System::CloseButtonPressed = true;
			//return 1;
			RetVal = 1;
		    break;
		}
	}

//	SDL_mutexV( ThreadLock );
//	SDL_DestroyMutex( ThreadLock );
	return RetVal;
}
// - ------------------------------------------------------------------------------------------ - //
extern void MessageLoop();
void MessageLoop() {
	SDL_Event event;
	// Do Event Polling //
    while ( SDL_PollEvent( &event ) ) {
#ifndef USES_SDL_1_3
    	EventFilter( &event );
#else // USES_SDL_1_3 //
		EventFilter( NULL, &event );
#endif // USES_SDL_1_3 //

#ifndef USES_SDL_1_3
#ifdef USES_WEBOS
	    switch( event.type ) {
			case SDL_ACTIVEEVENT: {
				ActiveEventFilter( event );
		    	break;
		    }
		};
#endif // USES_WEBOS //
#endif // !USES_SDL_1_3 //

#ifdef USES_SDL_1_3
		WindowEventFilter( event );
#endif // USES_SDL_1_3 //
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void HideWaitCursor();
void HideWaitCursor() {
}
// - ------------------------------------------------------------------------------------------ - //
void ShowWaitCursor();
void ShowWaitCursor() {
}
// - ------------------------------------------------------------------------------------------ - //
#include <Project.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_STORE
#include <Store.h>
#endif // USES_STORE //
// - ------------------------------------------------------------------------------------------ - //
#ifndef PRODUCT_SKU
#define PRODUCT_SKU		"UNKNOWN"
#define wPRODUCT_SKU	L"UNKNOWN"
#define FullProductName	"Unknown"

const char* ProductName = "Unknown";
#endif // PRODUCT_SKU //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool GraphicsModeSet = false;
// - ------------------------------------------------------------------------------------------ - //
void System_SetGraphicsMode( const bool FullScreen = true ) {
	if ( GraphicsModeSet ) {
		musPause();

		cGameSupport::Current()->LostFocusDraw();
		gelSwapBuffer();

#ifdef PRODUCT_LEGACY_SMILES
		TexturePool::ReleaseTextures();
#endif // PRODUCT_LEGACY_SMILES //
		gelGraphicsExit();
	}
	
//	gelSetupScreenShape( 854<<1,480<<1 );
//	gelSetupNativeScalar( 1.0f, 1.0f );
//	gelSetupOverscan( 0.0f, 0.0f );
//	gelSetupFullScreen( false );		
//	gelSetupAutodetectScreenShape( false );

//	gelSetupScreenShape( 1600,1200 );
//	gelSetupNativeScalar( 1.0f, 1.0f );
//	gelSetupOverscan( 0.0f, 0.0f );
//	gelSetupFullScreen( true );
//	gelSetupAutodetectScreenShape( false );

	if ( FullScreen ) {
		gelSetupNativeScalar( 1.0f, 1.0f );
		gelSetupFullScreen( true );		
	}
	else {
		gelSetupNativeScalar( 0.85f, 0.85f );
		gelSetupFullScreen( false );		
	}

	gelSetup();
	gelPostSetup();

	if ( GraphicsModeSet ) {
#ifdef PRODUCT_LEGACY_SMILES
		TexturePool::ReloadTextures();
#endif // PRODUCT_LEGACY_SMILES //

		musResume();
		musUpdate();
	}
	
	SkipTime();
	
	GraphicsModeSet = true;
}
// - ------------------------------------------------------------------------------------------ - //
void ToggleGraphicsMode() {
	System_SetGraphicsMode( !System::InitFlags.FullScreen );
	if ( GameHost ) {
		GameHost->Game->UpdateUI();
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	Log( "-=======- GEL Application Started -- SDL Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2012 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	Log( "" );

#ifdef USES_STORE
	Log( "+ Authorizing Store..." );
	if ( gelStoreAuthorize() ) {
		Log( "- Store Authorized" );
	}
	else {
		Log( "- ERROR: Store Authorization Failed" );
		return gelStoreGetExitCode();
	}
	Log("");
#endif // USES_STORE //

	// Report SDL Version //
	{
		SDL_version ver;
		SDL_VERSION(&ver);
		Log( "SDL (core) - v%u.%u.%u -- Compiled Version", ver.major, ver.minor, ver.patch );

		const SDL_version* pver = SDL_Linked_Version();
		Log( "SDL (core) - v%u.%u.%u -- Linked Version (DLL or Shared Library)", pver->major, pver->minor, pver->patch );
		Log( "" );

		int LinkVer = (ver.major << 16) | (ver.minor << 8) | (ver.patch << 0);
		int DLLVer = (pver->major << 16) | (pver->minor << 8) | (pver->patch << 0);

		if ( LinkVer > DLLVer ) {
			Log( "* WARNING: Linked version is older than Compiled version!!" );
			Log( "  If you have problems starting the game, this may be why." );
			Log( "  Upgrade to a newer SDL version to resolve this." );
			Log( "" );
		}
	}
	
	{
//		// Color Code Test //
//		int attr = 1;
//		int fg = 1;
//		int bg = 0;
//		Log("* %c[%d;%d;%dm!!!", 0x1B, attr, fg + 30, bg + 40);
//
//		attr = 0;
//		fg = 7;
//		bg = 0;
//		Log("* %c[%d;%d;%dm!!!", 0x1B, attr, fg + 30, bg + 40);

		// Color Code Test //
		
//		int Constant = 0x1B;
		int Constant = 33;
		int attr = 0;
		int fg = 1;
		Log("* %c[%d;%dm!!!", Constant, attr, fg + 30);

		attr = 0;
		Log("* %c[%dm!!!", Constant, attr);
	}
	
#ifdef USES_WEBOS
	// Need to call this before making any PDL calls //
	WebOS_PDL_Init(0);
	
	// If not a touchpad, assume it's a phone, and set default orientation //
	//if ( WebOS_PDL_GetHardwareID() < HARDWARE_TOUCHPAD ) {
	if ( ActualScreen::TallScreen ) {
		phone_orientation = 3;
	}
#endif // USES_WEBOS //


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

	// Opening scope here, so that all variables created after now get destroyed by the end brace //
	{
		gelInit();		

		gelSetupRefScreenShape( 480, 320 );

#ifndef PRODUCT_LEGACY_SMILES
		gelSetupDepthSize( 24 );
#endif // PRODUCT_LEGACY_SMILES //

#ifdef PRODUCT_OVERSCAN
		gelSetupOverscan( 0.05f, 0.10f );
#endif // PRODUCT_OVERSCAN //

		gelSetupAutodetectScreenShape();

#ifdef PRODUCT_FULLSCREEN
		System_SetGraphicsMode( true );
#else // PRODUCT_FULLSCREEN //
		System_SetGraphicsMode( false );
#endif // PRODUCT_FULLSCREEN //

#ifdef SLOW_VERSION
		SetFramesPerSecond( 50 );
#else // !SLOW_VERSION //
		SetFramesPerSecond( 60 );
#endif // SLOW_VERSION //

#ifdef USES_WEBOS
		extern void WebOS_AccelerometerInit();
		WebOS_AccelerometerInit();
#endif // USES_WEBOS //

		sndInit();
		musInit();
		
		SDL_ShowCursor( SDL_DISABLE );
		
#ifdef USES_SIXENSE
		Log( "+ Starting Sixense..." );
		sixenseInit();
		Log( "- Sixense Initialized." );
#endif // USES_SIXENSE //
		
		{
			Log( "" );
#ifdef PRODUCT_LEGACY_SMILES
			// Populate Product Info, based on Compiled Arguments //
			ProductInfo = cProductInfo::DecodeEmbeddedInfo();
			// Verify that the Product Info bits are correctly formatted //
			if ( !ProductInfo.IsLegal() ) {
				ProductInfo = cProductInfo::TrialGame();
			}
			// Report what product we are //
			ProductInfo.LogInfo();
#endif // PRODUCT_LEGACY_SMILES //
			
			Log("+ Creating GameHost Instance...");
			WorkTime = GetTimeNow();
			GameHost = new cGameHost;
			Log("- GameHost Created.");

			// Clear the screen //
			gelDisableBlending();
			gelClearColor( cGameSupport::Current()->FadeColor );
			gelSwapBuffer();
#ifdef USES_WEBOS
			// webOS layers OpenGL on top of Video, so make sure we don't write Alpha //
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
#endif // USES_WEBOS //
			gelClearColor( cGameSupport::Current()->FadeColor );
			
			// Antialiasing... doesn't work ? //
//			glEnable( GL_POLYGON_SMOOTH );
//			glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
			
			// Explicitly Create Game //
			GameHost->CreateGame();
			
			Log("+ Main: Game Created");

			WorkTime = GetTimeNow();


#ifdef USES_SDL_EVENTTHREAD
#ifndef USES_SDL_1_3
			SDL_SetEventFilter( EventFilter );
#else // USES_SDL_1_3 //
			SDL_SetEventFilter( EventFilter, NULL );
#endif // USES_SDL_1_3 //
			SDL_InitSubSystem( SDL_INIT_EVENTTHREAD | SDL_INIT_NOPARACHUTE );
			SDL_PumpEvents();
			MessageLoop();
#endif // USES_SDL_EVENTTHREAD //

			while( !gelHasShutdown() ) {
				TIMEVALUE TimeDiff = SubtractTime( GetTimeNow(), WorkTime );
				int FramesOfWork = GetFrames( &TimeDiff );
	
				if ( IsActive || RefreshScreen ) {
					bool DoRefresh = false;
					if ( RefreshScreen ) {
						DoRefresh = true;
						RefreshScreen = false;
					}
					
					if ( !DoRefresh ) {
						for ( int Frame = 0; Frame < (FramesOfWork); Frame++ ) {
							SDL_PumpEvents();
							MessageLoop();
							EventInjector.Clear();
							if ( EventValue ) {
								EventInjector.Set( EventValue );
								EventValue = 0;
							}
	
#if defined(USES_WEBOS)
							extern void WebOS_Orientation();
							WebOS_Orientation();
#elif defined(USES_MAEMO)
							extern void Maemo_Orientation();
							Maemo_Orientation();
#endif // USES_WEBOS //
						
							musUpdate();
							
							Mouse.Update();	
							GameHost->Step();
	
							AddFrame( &WorkTime );
						}
					}
					if ( (FramesOfWork > 0) || DoRefresh ) 
					{
						int DrawLoop = 1;
						if ( DoRefresh )
							DrawLoop = 2;
/*
#ifdef USES_SIXENSE
						sixenseSetActiveBase(0);
						sixenseAllControllerData acd;
						sixenseGetAllNewestData( &acd );
						
						static int Craw = 0;
						Craw++;
						if ( Craw >= 64 ) {
							int Active = sixenseGetNumActiveControllers();

							if ( Active > 0 )
								Craw = 0;
							else
								Craw = -512;

							Log( "> Active Sixense Controllers: %i ( ", sixenseGetNumActiveControllers() );

							int MaxControllers = sixenseGetMaxControllers();
							for ( int idx = 0; idx < MaxControllers; idx++ ) {
								Log( "%i ", sixenseIsControllerEnabled( idx ) );	
							}
							
							Log( ")" );
							
							for ( int idx = 0; idx < MaxControllers; idx++ ) {
								if ( sixenseIsControllerEnabled( idx ) ) {
									Log( "ACD (%i): Position: %f %f %f\n\t%f\t%f\t%f\n\t%f\t%f\t%f\n\t%f\t%f\t%f\n", idx, 
										acd.controllers[idx].pos[0], acd.controllers[idx].pos[1], acd.controllers[idx].pos[2],
										acd.controllers[idx].rot_mat[0][0], acd.controllers[idx].rot_mat[0][1], acd.controllers[idx].rot_mat[0][2],
										acd.controllers[idx].rot_mat[1][0], acd.controllers[idx].rot_mat[1][1], acd.controllers[idx].rot_mat[1][2],
										acd.controllers[idx].rot_mat[2][0], acd.controllers[idx].rot_mat[2][1], acd.controllers[idx].rot_mat[2][2]
										);
								}
							}
							
						}
#endif // USES_SIXENSE //
*/							
						for ( ; DrawLoop--; ) {
							// Draw the game //
							GameHost->Draw();
							
							// Swap display buffer to screen //
							gelSwapBuffer();
						}
					}
					else {
#ifdef USES_WEBOS
						Wait(5);
#else // USES_WEBOS //
						Wait(15);
#endif // USES_WEBOS //
					}
				}
				else {
					Wait(250);
					SDL_PumpEvents();
					MessageLoop();
				}
				
				if ( System::ToggleFullScreen ) {
					extern void ToggleGraphicsMode();
					ToggleGraphicsMode();

					System::ToggleFullScreen = false;
				}
			}

			Log( "" );
			Log( "-=======- Beginning GEL Application Shutdown... -=======-" );


#ifdef PRODUCT_LEGACY_SMILES			
			Log( "+ Writing Save Data..." );
			GameHost->Save();
			Log( "- Finished Writing Save Data." );
			Log( "" );
#endif // PRODUCT_LEGACY_SMILES //

			delete GameHost;
			Log( "" );
		}

#ifdef USES_SIXENSE
		Log( "+ Shutting down Sixense..." );
		sixenseExit();
		Log( "- Done Sixense." );
		Log( "" );
#endif // USES_SIXENSE //

//		if ( Buffer ) { 
//			SDL_FreeSurface( Buffer );
//		}
		
		Log( "+ Freeing audio resources..." );
		musFree();
		sndFree();
		Log( "- Audio resources released." );
		Log( "" );

#ifdef USES_STORE
		gelStoreExit();
#endif // USES_STORE //

#ifdef USES_WEBOS
		Log( "+ Shutting Down PDL..." );
		PDL_Quit();
		Log( "- PDL Shut down complete." );
		Log( "" );
#endif // USES_WEBOS //

		Log( "+ Shutting Down GEL Graphics..." );
		gelExit();
		Log( "- GEL Graphics Shut down complete." );
		Log( "" );
	}

	Log( "-=======- GEL Application Exited Successfully -=======-" );
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
