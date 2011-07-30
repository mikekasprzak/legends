// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Init_AIRPLAY_H__
#define __GEL_Graphics_Init_AIRPLAY_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_AIRPLAY
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Graphics/Graphics_System.h>
#include <Graphics/Graphics_Screen.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
// - ------------------------------------------------------------------------------------------ - //
#define GELS_GRAPHICS_EXIT

inline void gels_GraphicsExit() {
//	if ( Buffer ) { 
//		SDL_FreeSurface( Buffer );
//		Buffer = 0;
//	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_EXIT

inline void gels_Exit() {
	gels_GraphicsExit();
//	SDL_Quit();
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_MINIMIZE

inline void gels_Minimize() {
//	SDL_WM_IconifyWindow();	
}
// - ------------------------------------------------------------------------------------------ - //
//#define GELS_INIT_GRAPHICS_API
//
//inline void gels_InitGraphicsAPI() {
////	// Initialize SDL //
////	Log( "- Attempting to Initialize SDL...\n" );
////	//SDL_INIT_NOPARACHUTE
////    if ( SDL_Init( SDL_INIT_VIDEO ) ) {
////		Log( "* ERROR: SDL initialization failed: \n  %s\n", SDL_GetError() );	    
////	    exit( 1 );
////	}
////	else {
////		Log( "+ SUCCESS: SDL Initialized.\n" );
////	}
////
////#ifdef USES_WEBOS
////	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
//////	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
////#endif // USES_WEBOS //
////
////	Log( "\n" );
//}
// - ------------------------------------------------------------------------------------------ - //
//#define GELS_AUTODETECT_NATIVE_SCREEN_SHAPE
//
//inline void gels_AutodetectNativeScreenShape() {
////	// Get information about our video hardware //    
////	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
////	
////	// Check video hardware //
////	if ( VideoInfo ) {
////		int CanSetMode = SDL_VideoModeOK( VideoInfo->current_w, VideoInfo->current_h, VideoInfo->vfmt->BitsPerPixel, SDL_FULLSCREEN|SDL_OPENGL);
////
////		Log( "Can I set this resolution? %s (%ibit)\n", 
////			CanSetMode ?
////			"Yes" : "No",
////			CanSetMode
////			);
////
////		if ( CanSetMode ) {
////			NativeScreen::Width = VideoInfo->current_w;
////			NativeScreen::Height = VideoInfo->current_h;
////			System::InitFlags.NativeShapeDetected = true;
////		}
////		Log( "\n" );
////	}
//}
// - ------------------------------------------------------------------------------------------ - //
//#define GELS_AUTODETECT_SCREEN_SHAPE
//
//inline void gels_AutodetectScreenShape() {
////	// Get information about our video hardware //    
////	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
////	
////	// Check video hardware //
////	if ( VideoInfo ) {
////		int CanSetMode = SDL_VideoModeOK( VideoInfo->current_w, VideoInfo->current_h, VideoInfo->vfmt->BitsPerPixel, SDL_FULLSCREEN|SDL_OPENGL);
////
////		Log( "Can I set this resolution? %s (%ibit)\n", 
////			CanSetMode ?
////			"Yes" : "No",
////			CanSetMode
////			);
////
////		if ( CanSetMode ) {
////			ActualScreen::Width = VideoInfo->current_w;
////			ActualScreen::Height = VideoInfo->current_h;
////		}
////		
////		Log( "\n" );
////	}
//}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_VIDEO_MODE

// Given all prior settings, set the video mode //
inline void gels_SetVideoMode() {
	{
		// Get OpenGL Information Strings //
		const char* OpenGLVendor = (const char*)glGetString( GL_VENDOR );
		const char* OpenGLRenderer = (const char*)glGetString( GL_RENDERER );
		const char* OpenGLVersion = (const char*)glGetString( GL_VERSION );
		const char* OpenGLExtensions = (const char*)glGetString( GL_EXTENSIONS );		
		
		// Log OpenGL Details //
		Log( "OpenGL Vendor: %s\n", OpenGLVendor );
		Log( "OpenGL Renderer: %s\n", OpenGLRenderer );
		Log( "OpenGL Version: %s\n", OpenGLVersion );
#ifndef USES_OPENGLES
		Log( "OpenGL Shading Language Version: %s\n", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
#endif // USES_OPENGLES //
		Log( "OpenGL Extensions: \n%s\n", OpenGLExtensions );
				
		
		if ( find_String( "GL_EXT_texture_compression_s3tc", OpenGLExtensions ) ) {
			Log( "+ Found S3TC\n" );
			System::InfoFlags.HasTextureCompression = true;
		}
		else if ( find_String( "GL_S3_s3tc", OpenGLExtensions ) ) {
			Log( "+ Found S3TC\n" );
			System::InfoFlags.HasTextureCompression = true;
		}

#ifdef USES_PVRTC
		if ( find_String( "GL_IMG_texture_compression_pvrtc", OpenGLExtensions ) ) {
			Log( "+ Found PVRTC\n" );
			System::InfoFlags.HasTextureCompression = true;
		}
#endif // USES_PVRTC //
		
/*
		// Newer OpenGL's only //
		int NumExtensions = 0;
		glGetIntegerv( GL_NUM_EXTENSIONS, &NumExtensions );
		Log( "OpenGL Extensions (%i):\n", NumExtensions );
		for ( int idx = 0; idx < NumExtensions; idx++ ) {
			printf( "- %s\n", glGetStringi( GL_EXTENSIONS, idx ) );
		}
*/
		Log( "\n" );
		
		Log( "OpenGL Environment Settings\n" );
		glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*)&System::MaxTextureSize );
		Log( "GL_MAX_TEXTURE_SIZE: %i\n", System::MaxTextureSize );
			
#ifndef PRODUCT_NO_INTEL_FIX
		// Check both the Vendor and the Renderer, since Intel subcontracted the Linux driver to Tungsten. //
		// Intel GMA 950's have only enough texture cache for 1024x1024 textures, so making that the limit //
		if ( find_String( "Intel", OpenGLVendor ) ) {
			Log( "+ Found Intel GPU\n" );
			if ( System::MaxTextureSize > 1024 ) {
				Log( "* Limiting textures to 1024x1024 (was %i)\n", System::MaxTextureSize );
				System::MaxTextureSize = 1024;
			}
		}
		else if ( find_String( "Intel", OpenGLRenderer ) ) {
			Log( "+ Found Intel GPU\n" );
			if ( System::MaxTextureSize > 1024 ) {
				Log( "* Limiting textures to 1024x1024 (was %i)\n", System::MaxTextureSize );
				System::MaxTextureSize = 1024;
			}
		}
#endif // PRODUCT_NO_INTEL_FIX //

		Log( "\n" ); 
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//#define GELS_SET_SWAP_INTERVAL
//
//// 0 - no sync, 1 - 60 fps sync, 2 - 30 fps sync //
//inline void gels_SetSwapInterval( const int Var = 1 ) {
//
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Init_AIRPLAY_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // OPENGL //
// - ------------------------------------------------------------------------------------------ - //
