// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include "GELS_Init_SDL_EGLProxy.h"
#include "GELS_Init_SDL.h"
#include "GELS_Init_SDL13.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
#ifdef USES_SDL_1_3
// - ------------------------------------------------------------------------------------------ - //
SDL_Window* MyWindow;
SDL_WindowID MyWindowID;
SDL_GLContext MyGLContext;

int ActualRefreshRate = 60;
Uint32 ActualPixelFormat = SDL_PIXELFORMAT_RGB888;

int NativeRefreshRate = 0;
Uint32 NativePixelFormat = 0;

//SDL_Surface* Buffer;
// - ------------------------------------------------------------------------------------------ - //
#else // USES_SDL_1_3 //
// - ------------------------------------------------------------------------------------------ - //
SDL_Surface* Buffer = 0;

#ifdef USES_SDL_EGLPROXY
	EGLDisplay g_eglDisplay = 0;
	EGLConfig g_eglConfig = 0;
	EGLContext g_eglContext = 0;
	EGLSurface g_eglSurface = 0;
	Display *g_x11Display = NULL;

	#define COLOURDEPTH_RED_SIZE  		5
	#define COLOURDEPTH_GREEN_SIZE 		6
	#define COLOURDEPTH_BLUE_SIZE 		5
	#define COLOURDEPTH_DEPTH_SIZE		16
	
	const EGLint g_configAttribs[] ={
//		  EGL_RED_SIZE,      	    COLOURDEPTH_RED_SIZE,
//		  EGL_GREEN_SIZE,    	    COLOURDEPTH_GREEN_SIZE,
//		  EGL_BLUE_SIZE,     	    COLOURDEPTH_BLUE_SIZE,
//		  EGL_DEPTH_SIZE,		    COLOURDEPTH_DEPTH_SIZE,
//		  EGL_SURFACE_TYPE,         EGL_WINDOW_BIT,
//		  EGL_RENDERABLE_TYPE,      EGL_OPENGL_ES_BIT,
//		  EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
		  EGL_NONE
		};	
#endif // USES_SDL_EGLPROXY //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL_1_3 //
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
