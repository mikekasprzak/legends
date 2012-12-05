// - ------------------------------------------------------------------------------------------ - //
#include <SDL2/SDL.h>
#include <gl/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Input_XInput.h"
#include "main_SDLInit.h"
// - ------------------------------------------------------------------------------------------ - //
void ReportCompilerVersion() {
	#ifdef _MSC_VER
	Log( "With MSVC Version: %i.%i (%i -- %i)", _MSC_VER / 100, _MSC_VER % 100, _MSC_VER, _MSC_FULL_VER );
	#else // _MSC_VER //
	#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
	// _STR -- The name of the macro as a string
	// _XSTR -- The value of a macro as a string
	#define _XSTR(s) _STR(s)
	#define _STR(s) #s
	#define GCC_VERSION_STRING (_XSTR(__GNUC__) "." _XSTR(__GNUC_MINOR__) "." _XSTR(__GNUC_PATCHLEVEL__))
	Log( "With GCC Version: %s (%i -- %s)", GCC_VERSION_STRING, GCC_VERSION, __VERSION__ );
	_Log( "With Settings: " );
	#ifdef __OPTIMIZE__
		_Log( _STR(__OPTIMIZE__) " " );
	#endif
	#ifdef __OPTIMIZE_SIZE__
		_Log( _STR(__OPTIMIZE_SIZE__) " " );
	#endif
	#ifdef __NO_INLINE__
		_Log( _STR(__NO_INLINE__) " " );
	#endif
	#ifdef __STDC__
		_Log( _STR(__STDC__) " " );
	#endif
	#ifdef __STDC_HOSTED__
		_Log( _STR(__STDC_HOSTED__) " " );
	#endif
	#ifdef __STDC_VERSION__
		_Log( _STR(__STDC_VERSION__) "=\"" _XSTR(__STDC_VERSION__) "\" " );
	#endif
	#ifdef __GNUG__
		_Log( _STR(__GNUG__) " " );
	#endif
	#ifdef __STRICT_ANSI__
		_Log( _STR(__STRICT_ANSI__) " " );
	#endif
	#ifdef __ELF__
		_Log( _STR(__ELF__) " " );
	#endif
	#ifdef __GNUC_GNU_INLINE__
		_Log( _STR(__GNUC_GNU_INLINE__) " " );
	#endif
	#ifdef __GNUC_STDC_INLINE__
		_Log( _STR(__GNUC_STDC_INLINE__) " " );
	#endif
	#ifdef __CHAR_UNSIGNED__
		_Log( _STR(__CHAR_UNSIGNED__) " " );
	#endif
	#ifdef __WCHAR_UNSIGNED__
		_Log( _STR(__WCHAR_UNSIGNED__) " " );
	#endif
	#ifdef __REGISTER_PREFIX__
		_Log( _STR(__REGISTER_PREFIX__) "=\"" __REGISTER_PREFIX__ "\" " );
	#endif
	#ifdef __USER_LABEL_PREFIX__
		_Log( _STR(__USER_LABEL_PREFIX__) "=\"" _XSTR(__USER_LABEL_PREFIX__) "\" " );
	#endif
	#ifdef __BYTE_ORDER__
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) " " );
		#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) " " );
		#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_PDP_ENDIAN__) " " );
		#endif
//		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
//			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) "=\"" _XSTR(__BYTE_ORDER__) "\" " );
//		#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
//			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) "=\"" _XSTR(__BYTE_ORDER__) "\" " );
//		#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
//			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_PDP_ENDIAN__) "=\"" _XSTR(__BYTE_ORDER__) "\" " );
//		#endif
	#endif
	#ifdef __FLOAT_WORD_ORDER__
		#if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) " " );
		#elif __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) " " );
		#endif
//		#if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
//			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) "=\"" _XSTR(__FLOAT_WORD_ORDER__) "\" " );
//		#elif __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
//			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) "=\"" _XSTR(__FLOAT_WORD_ORDER__) "\" " );
//		#endif
	#endif
	#ifdef __DEPRECATED
		_Log( _STR(__DEPRECATED) " " );
	#endif
	#ifdef __EXCEPTIONS
		_Log( _STR(__EXCEPTIONS) " " );
	#endif
	#ifdef __GXX_RTTI
		_Log( _STR(__GXX_RTTI) " " );
	#endif
	#ifdef __USING_SJLJ_EXCEPTIONS__
		_Log( _STR(__USING_SJLJ_EXCEPTIONS__) " " );
	#endif
	#ifdef __GXX_EXPERIMENTAL_CXX0X__
		_Log( _STR(__GXX_EXPERIMENTAL_CXX0X__) " " );
	#endif
	#ifdef __GXX_WEAK__
		_Log( _STR(__GXX_WEAK__) " " );
	#endif
	#ifdef __NEXT_RUNTIME__
		_Log( _STR(__NEXT_RUNTIME__) " " );
	#endif
	#ifdef __LP64__
		_Log( _STR(__LP64__) " " );
	#endif
	#ifdef __SSP__
		_Log( _STR(__SSP__) " " );
	#endif
	#ifdef __SSP_ALL__
		_Log( _STR(__SSP_ALL__) " " );
	#endif
	#ifdef __SANITIZE_ADDRESS__
		_Log( _STR(__SANITIZE_ADDRESS__) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_16
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16) " " );
	#endif
	#ifdef __GCC_HAVE_DWARF2_CFI_ASM
		_Log( _STR(__GCC_HAVE_DWARF2_CFI_ASM) " " );
	#endif
	#ifdef __FP_FAST_FMA
		_Log( _STR(__FP_FAST_FMA) " " );
	#endif
	#ifdef __FP_FAST_FMAF
		_Log( _STR(__FP_FAST_FMAF) " " );
	#endif
	#ifdef __FP_FAST_FMAL
		_Log( _STR(__FP_FAST_FMAL) " " );
	#endif
	
	Log( "" );
	#endif // _MSC_VER //
}
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
void ReportSDLSystemInfo() {
	{
		Log( "-=- SDL System Information -=-" );
		Log( "Platform: %s", SDL_GetPlatform() );
		Log( "CPU Cores: %i", SDL_GetCPUCount() );
		Log( "L1 Cache Line Size: %i", SDL_GetCPUCacheLineSize() );
		Log( "Has MMX: %s", SDL_HasMMX() ? "Yes" : "No" );
		Log( "Has 3DNow: %s", SDL_Has3DNow() ? "Yes" : "No" );
		Log( "Has SSE: %s", SDL_HasSSE() ? "Yes" : "No" );
		Log( "Has SSE 2: %s", SDL_HasSSE2() ? "Yes" : "No" );
		Log( "Has SSE 3: %s", SDL_HasSSE3() ? "Yes" : "No" );
		Log( "Has SSE 4.1: %s", SDL_HasSSE41() ? "Yes" : "No" );
		Log( "Has SSE 4.2: %s", SDL_HasSSE42() ? "Yes" : "No" );
		Log( "Has RDTSC Instruction: %s", SDL_HasRDTSC() ? "Yes" : "No" );
		Log( "Has AltiVec: %s", SDL_HasAltiVec() ? "Yes" : "No" );
		Log("");
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
		for ( size_t idx = 0; idx < XInput::Size(); idx++ ) {
	        if ( XInput::IsConnected(idx) ) {
	        	Log( "%i - Connected", idx );
			}			
		}
		Log( "" );
	}
	#endif // USES_XINPUT //
}
// - ------------------------------------------------------------------------------------------ - //
#include <External/OpenGL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WGL
#include <Windows.h>
#include <External/OpenGL/wglext.h>
#endif // USES_WGL //
// - ------------------------------------------------------------------------------------------ - //
void ReportOpenGLGraphicsInfo() {
	#ifdef USES_WGL
	{
		Log( "-=- WGL -=-" );
		PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");
		if ( wglGetExtString ) {
			char* Extensions = ((char*(__stdcall*)(HDC))wglGetExtString)( wglGetCurrentDC() );
			Log( "WGL Extensions (ARB):\n%s", Extensions );
		}
		PROC wglGetExtString2 = wglGetProcAddress("wglGetExtensionsStringEXT");
		if ( wglGetExtString2 ) {
			char* Extensions = ((char*(__stdcall*)(HDC))wglGetExtString2)( wglGetCurrentDC() );
			Log( "WGL Extensions (EXT):\n%s", Extensions );
		}
		Log( "" );
	}
	#endif // USES_WGL //

//	#ifdef USES_GLX
//	{
//		Log( "-=- GLX -=-" );
//		Log( "" );
//	}
//	#endif // USES_GLX //
//
//	#ifdef USES_CGL
//	{
//		Log( "-=- CGL -=-" );
//		Log( "" );
//	}
//	#endif // USES_CGL //
	
	#ifdef USES_EGL
	{
		Log( "-=- EGL -=-" );
		extern EGLDisplay g_eglDisplay;
		Log( "EGL Version: %s", eglQueryString(g_eglDisplay, EGL_VERSION) );
		Log( "Driver Vendor: %s", eglQueryString(g_eglDisplay, EGL_VENDOR) );
		Log( "Client APIs: %s", eglQueryString(g_eglDisplay, EGL_CLIENT_APIS) );
		Log( "Extensions: %s", eglQueryString(g_eglDisplay, EGL_EXTENSIONS) );
		Log( "" );
	}
	#endif // USES_EGL //
	
	{
		// Get OpenGL Information Strings //
		const char* OpenGLVendor = (const char*)glGetString( GL_VENDOR );
		const char* OpenGLRenderer = (const char*)glGetString( GL_RENDERER );
		const char* OpenGLVersion = (const char*)glGetString( GL_VERSION );
		const char* OpenGLExtensions = (const char*)glGetString( GL_EXTENSIONS );		

		Log( "-=- OpenGL -=-" );
		Log( "OpenGL Vendor: %s", OpenGLVendor );
		Log( "OpenGL Renderer: %s", OpenGLRenderer );
		Log( "OpenGL Version: %s", OpenGLVersion );
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
		Log( "OpenGL Shading Language Version: %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
#endif // USES_OPENGLES2 //
		Log( "OpenGL Extensions:\n%s", OpenGLExtensions );
		Log( "" );
	}
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
