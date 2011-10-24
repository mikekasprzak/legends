// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL_API_H__
#define __GEL_Graphics_OpenGL_API_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL1) || defined(USES_OPENGLES1)
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_WEBOS) || defined(USES_PANDORA)
// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_SDL_IN_SUBDIR
#include <SDL.h>
#else // USES_SDL_IN_SUBDIR //
#include <SDL/SDL.h>
#endif // USES_SDL_IN_SUBDIR //

#include <GLES/gl.h>
#include <GLES/glext.h>

#ifdef USES_SDL_EGLPROXY
	#include <EGL/egl.h>
	#include <SDL/SDL_syswm.h>
#endif // USES_SDL_EGLPROXY //
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_MARMALADE) || defined(USES_ANDROID) || defined(USES_WINGLES)
// - ------------------------------------------------------------------------------------------ - //
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_IOS)
// - ------------------------------------------------------------------------------------------ - //
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_SDL)
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS
	#include <windows.h>
#endif // USES_WINDOWS //
#ifdef USES_GLEE
	#include <External/GLEE/GLee.h>
#endif // USES_GLEE //

#ifdef NO_SDL_SUBDIR
	#include <SDL.h>
#else // NO_SDL_SUBDIR //
	#include <SDL/SDL.h>
#endif // NO_SDL_SUBDIR //
#ifndef USES_GLEE
	#ifdef NO_SDL_SUBDIR
		#include <SDL_opengl.h>
	#else // NO_SDL_SUBDIR //
		#include <SDL/SDL_opengl.h>
	#endif // NO_SDL_SUBDIR //
#endif // USES_GLEE //
// - ------------------------------------------------------------------------------------------ - //
#else // !USES_x //
// ---------------------------------------------------------------------------------------------- //
#error Unknown OpenGL Implementation
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_x //
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_WEBOS) || defined(USES_MAEMO) || defined(USES_PANDORA)
// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_SDL_IN_SUBDIR
#include <SDL.h>
#else // USES_SDL_IN_SUBDIR //
#include <SDL/SDL.h>
#endif // USES_SDL_IN_SUBDIR //

#ifdef USES_MAEMO
#include <SDL/SDL_gles.h>
#endif // USES_MAEMO //

#include <GLES2/gl.h>
#include <GLES2/glext.h>

#ifdef USES_SDL_EGLPROXY
	#include <EGL/egl.h>
	#include <SDL/SDL_syswm.h>
#endif // USES_SDL_EGLPROXY //
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_MARMALADE) || defined(USES_ANDROID) || defined(USES_WINGLES)
// - ------------------------------------------------------------------------------------------ - //
#include <EGL/egl.h>
#include <GLES2/gl.h>
#include <GLES2/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_NACL)
// - ------------------------------------------------------------------------------------------ - //
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_IOS)
// - ------------------------------------------------------------------------------------------ - //
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_SDL)
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS
	#include <windows.h>
#endif // USES_WINDOWS //
#ifdef USES_GLEE
	#include <External/GLEE/GLee.h>
#endif // USES_GLEE //

#ifdef NO_SDL_SUBDIR
	#include <SDL.h>
#else // NO_SDL_SUBDIR //
	#include <SDL/SDL.h>
#endif // NO_SDL_SUBDIR //
#ifndef USES_GLEE
	#ifdef NO_SDL_SUBDIR
		#include <SDL_opengl.h>
	#else // NO_SDL_SUBDIR //
		#include <SDL/SDL_opengl.h>
	#endif // NO_SDL_SUBDIR //
#endif // USES_GLEE //
// - ------------------------------------------------------------------------------------------ - //
#else // !USES //
// ---------------------------------------------------------------------------------------------- //
#error Unknown OpenGL Implementation
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
#else // USES_OPENGLx //
// - ------------------------------------------------------------------------------------------ - //
#error Unknown OpenGL Implementation (Neither 1 or 2)
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGLx //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL_API_H__ //
// - ------------------------------------------------------------------------------------------ - //
