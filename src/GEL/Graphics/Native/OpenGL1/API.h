// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_OpenGL1_API_H__
#define __GEL_Graphics_OpenGL1_API_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_WEBOS)
// - ------------------------------------------------------------------------------------------ - //
#include <GLES/gl.h>
#include <GLES/glext.h>
#include "SDL.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_ANDROID)
// - ------------------------------------------------------------------------------------------ - //
#include <GLES/gl.h>
#include <GLES/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_MAEMO) || defined(USES_PANDORA)
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#ifdef USES_SDL_EGLPROXY
	#include <EGL/egl.h>
	#include <SDL/SDL_syswm.h>
#endif // USES_SDL_EGLPROXY //
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_IOS)
// - ------------------------------------------------------------------------------------------ - //
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WINDOWSMOBILE)
// - ------------------------------------------------------------------------------------------ - //
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <EGL/egl.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_BADA)
// - ------------------------------------------------------------------------------------------ - //
#include <gl.h>
#include <glext.h>
//#include <FGraphicsOpengl2.h>
//using namespace Osp::Graphics::Opengl; 
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WINGLES)
// - ------------------------------------------------------------------------------------------ - //
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_SDL)
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_GLEE
#include <External/GLEE/GLee.h>
#endif // USES_GLEE //

#ifdef USES_SDL_1_3
#if defined(USES_WINDOWS) && defined(USES_SDL_1_3_HACK)
	#include <SDL13/SDL.h>
	#ifndef USES_GLEE
		#include <SDL13/SDL_opengl.h>
	#endif // USES_GLEE //
#else // USES_WINDOWS //
	#include <SDL/SDL.h>
	#ifndef USES_GLEE
		#include <SDL/SDL_opengl.h>
	#endif // USES_GLEE //
#endif // USES_WINDOWS //
#else // USES_SDL_1_3 //
	#ifdef USES_SDL_BASEDIR
		#include <SDL.h>
		#ifndef USES_GLEE
			#include <SDL_opengl.h>
		#endif // USES_GLEE //
	#else // USES_SDL_BASEDIR //
		#include <SDL/SDL.h>
		#ifndef USES_GLEE
			#include <SDL/SDL_opengl.h>
		#endif // USES_GLEE //
	#endif // USES_SDL_BASEDIR //
#endif // USES_SDL_1_3 //
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_AIRPLAY)
// - ------------------------------------------------------------------------------------------ - //
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <EGL/egl.h>
// - ------------------------------------------------------------------------------------------ - //
#else // !USES //
// ---------------------------------------------------------------------------------------------- //
#error Unknown OpenGL Implementation
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_OpenGL1_API_H__ //
// - ------------------------------------------------------------------------------------------ - //
