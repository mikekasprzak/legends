// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include "Graphics_Support_SDL.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_MAEMO
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_syswm.h>
#include <X11/Xutil.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MAEMO //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SDL_Surface* Buffer;
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGLES2
// - ------------------------------------------------------------------------------------------ - //
SDL_GLES_Context* GLESContext;
// - ------------------------------------------------------------------------------------------ - //
	
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_MAEMO
// - ------------------------------------------------------------------------------------------ - //
void Maemo_SetCaption( const char* Text ) {
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	if ( SDL_GetWMInfo(&info) ) {
		Display *dpy = info.info.x11.display;
		Window win;
		
		if (dpy){
			win = info.info.x11.fswindow;
			if (win) XStoreName(dpy, win, Text);
			
			win = info.info.x11.wmwindow;
			if (win) XStoreName(dpy, win, Text);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MAEMO //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGLES2 //	
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //