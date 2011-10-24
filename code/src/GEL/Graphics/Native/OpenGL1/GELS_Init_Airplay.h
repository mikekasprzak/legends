// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Init_AIRPLAY_H__
#define __GEL_Graphics_Init_AIRPLAY_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_AIRPLAY
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
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

#ifdef GELS_SCAN_GL_EXTENSIONS
	gels_ScanGLExtensions();
#endif // GELS_SCAN_GL_EXTENSIONS //

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
