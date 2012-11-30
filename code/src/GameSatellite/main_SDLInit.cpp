// - ------------------------------------------------------------------------------------------ - //
#include <SDL2/SDL.h>
#include <gl/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Input_XInput.h"
#include "main_SDLInit.h"
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
		VLog( "-=- SDL Video Drivers (not very useful) -=-" );
		for( int idx = 0; idx < SDL_GetNumVideoDrivers(); idx++ ) {			
			VLog( "%i - %s", idx, SDL_GetVideoDriver( idx ) );
		}
		VLog("");
	}
	
	{
		Log( "-=- Video Displays -- %i Device(s) Connected -=-", SDL_GetNumVideoDisplays() );
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
void ReportSDLInputInfo() {
	// TODO: Poll Input Devices //
	
	// Not Actually SDL, but Input //
	#ifdef USES_XINPUT
	{
		XInput::Init();
		XInput::Poll();
		
		Log( "-=- XInput -- %i Device(s) Connected -=-", XInput::DevicesConnected() );
		for ( int idx = 0; idx < XInput::Size(); idx++ ) {
	        if ( XInput::IsConnected(idx) ) {
	        	Log( "%i - Connected", idx );
			}			
		}
		Log( "" );		
	}
	#endif // USES_XINPUT //
}
// - ------------------------------------------------------------------------------------------ - //
const char* SDL_WindowEventName( Uint8 EventName ) {
	switch( EventName ) {
		case SDL_WINDOWEVENT_NONE:			return "SDL_WINDOWEVENT_NONE";
		case SDL_WINDOWEVENT_SHOWN:			return "SDL_WINDOWEVENT_SHOWN";
		case SDL_WINDOWEVENT_HIDDEN:		return "SDL_WINDOWEVENT_HIDDEN";
		case SDL_WINDOWEVENT_EXPOSED:		return "SDL_WINDOWEVENT_EXPOSED";
		case SDL_WINDOWEVENT_MOVED:			return "SDL_WINDOWEVENT_MOVED";
		case SDL_WINDOWEVENT_RESIZED:		return "SDL_WINDOWEVENT_RESIZED";
		case SDL_WINDOWEVENT_SIZE_CHANGED:	return "SDL_WINDOWEVENT_SIZE_CHANGED";
		case SDL_WINDOWEVENT_MINIMIZED:		return "SDL_WINDOWEVENT_MINIMIZED";
		case SDL_WINDOWEVENT_MAXIMIZED:		return "SDL_WINDOWEVENT_MAXIMIZED";
		case SDL_WINDOWEVENT_RESTORED:		return "SDL_WINDOWEVENT_RESTORED";
		case SDL_WINDOWEVENT_ENTER:			return "SDL_WINDOWEVENT_ENTER";
		case SDL_WINDOWEVENT_LEAVE:			return "SDL_WINDOWEVENT_LEAVE";
		case SDL_WINDOWEVENT_FOCUS_GAINED:	return "SDL_WINDOWEVENT_FOCUS_GAINED";
		case SDL_WINDOWEVENT_FOCUS_LOST:	return "SDL_WINDOWEVENT_FOCUS_LOST";
		case SDL_WINDOWEVENT_CLOSE:			return "SDL_WINDOWEVENT_CLOSE";
	};
	return "SDL_WINDOWEVENT_???";
}
// - ------------------------------------------------------------------------------------------ - //
