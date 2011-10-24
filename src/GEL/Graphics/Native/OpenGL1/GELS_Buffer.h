// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_Buffer_H__
#define __GEL_Graphics_OpenGL_Buffer_H__
// - ------------------------------------------------------------------------------------------ - //
#include "API.h"
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_CLEAR_COLOR
// - ------------------------------------------------------------------------------------------ - //
inline void gels_SetClearColor( const GelColor Color ) {
	glClearColor( 
		((float)GEL_GET_R(Color)) * ( 1.0f / 255.0f ), 
		((float)GEL_GET_G(Color)) * ( 1.0f / 255.0f ), 
		((float)GEL_GET_B(Color)) * ( 1.0f / 255.0f ), 
		((float)GEL_GET_A(Color)) * ( 1.0f / 255.0f )
		);
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_COLOR_MASK
// - ------------------------------------------------------------------------------------------ - //
inline void gels_SetColorMask( const bool Red, const bool Green, const bool Blue, const bool Alpha ) {
	glColorMask( Red, Green, Blue, Alpha );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_CLEAR
// - ------------------------------------------------------------------------------------------ - //
inline void gels_Clear( const bool ColorBuffer = true, const bool DepthBuffer = false, const bool StencilBuffer = false ) {
	int ClearMask = 0;
	if ( ColorBuffer )
		ClearMask |= GL_COLOR_BUFFER_BIT;
	if ( DepthBuffer )
		ClearMask |= GL_DEPTH_BUFFER_BIT;
	if ( StencilBuffer )
		ClearMask |= GL_STENCIL_BUFFER_BIT;
	
	glClear( ClearMask );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Buffer Swapping Function //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_EGL
// - ------------------------------------------------------------------------------------------ - //
extern EGLDisplay egl_display;
extern EGLSurface egl_surface;
extern EGLContext egl_context;
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SWAP_BUFFER

inline void gels_SwapBuffer() {
	glFinish();
	eglSwapBuffers(egl_display, egl_surface);
}
// - ------------------------------------------------------------------------------------------ - //
#elif USES_SDL_1_3
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SWAP_BUFFER

inline void gels_SwapBuffer() {
	extern SDL_Window* MyWindow;
	
	SDL_GL_SwapWindow( MyWindow );
}
// - ------------------------------------------------------------------------------------------ - //
#elif USES_SDL_EGLPROXY
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SWAP_BUFFER

inline void gels_SwapBuffer() {
	extern EGLDisplay g_eglDisplay;
	extern EGLSurface g_eglSurface;	
	
	eglSwapBuffers(g_eglDisplay, g_eglSurface);
}
// - ------------------------------------------------------------------------------------------ - //
#elif USES_SDL
// - ------------------------------------------------------------------------------------------ - //
extern SDL_Surface* Buffer;
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SWAP_BUFFER

inline void gels_SwapBuffer() {
	SDL_GL_SwapBuffers();
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES //
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SWAP_BUFFER

inline void gels_SwapBuffer() {
	glFinish();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_EGL //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_Buffer_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
