// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Init_SDL_H__
#define __GEL_Graphics_Init_SDL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
#ifndef USES_SDL_2
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Graphics/Graphics_System.h>
#include <Graphics/Graphics_Screen.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
// - ------------------------------------------------------------------------------------------ - //
extern SDL_Surface* Buffer;
// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_SDL_EGLPROXY
// - ------------------------------------------------------------------------------------------ - //
#define GELS_GRAPHICS_EXIT

inline void gels_GraphicsExit() {
	if ( Buffer ) { 
		SDL_FreeSurface( Buffer );
		Buffer = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL_EGLPROXY //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_EXIT

inline void gels_Exit() {
	gels_GraphicsExit();
	SDL_Quit();
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_MINIMIZE

inline void gels_Minimize() {
	SDL_WM_IconifyWindow();	
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_INIT_GRAPHICS_API

inline void gels_InitGraphicsAPI() {
	// Initialize SDL //
	Log( "- Attempting to Initialize SDL...\n" );
	//SDL_INIT_NOPARACHUTE
	
	int Error = SDL_Init( SDL_INIT_VIDEO );
//#ifdef USES_WINDOWS
//	FILE * ctt = fopen("CON", "w" );
//	freopen( "CON", "w", stdout );
//	freopen( "CON", "w", stderr );
//#endif // USES_WINDOWS //
    if ( Error ) {
		Log( "* ERROR: SDL initialization failed: \n  %s\n", SDL_GetError() );	    
	    exit( 1 );
	}
	else {
		Log( "+ SUCCESS: SDL Initialized.\n" );
	}

#ifdef USES_WEBOS
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#endif // USES_WEBOS //

	Log( "\n" );
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_LOG_GRAPHICS_DETAILS

inline void gels_LogGraphicsDetails() {
	// About to begin Graphics Init Procedure //
	Log( "** Graphics Initalizing -=======-\n" );
	
	// Get information about our video hardware //    
	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
	
	// Check video hardware //
	if ( VideoInfo ) {
		Log( "Desktop Resolution: %i x %i %ibit\n", VideoInfo->current_w, VideoInfo->current_h, VideoInfo->vfmt->BitsPerPixel );

		{
			int CanSetMode = SDL_VideoModeOK( VideoInfo->current_w, VideoInfo->current_h, VideoInfo->vfmt->BitsPerPixel, SDL_FULLSCREEN|SDL_OPENGL);

			Log( "Can I set this resolution? %s (%ibit)\n", 
				CanSetMode ?
				"Yes" : "No",
				CanSetMode
				);
		}

		Log( "\n" );

#ifndef USES_WEBOS
		{
			Log( "- Available Fullscreen Resolutions (%ibit): \n", VideoInfo->vfmt->BitsPerPixel );
			SDL_Rect** modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
			for (int i=0; modes[i]; ++i) {
				Log("+ %d x %d\n", modes[i]->w, modes[i]->h);
			}
		}

		Log( "\n" );
#endif // USES_WEBOS //
	}
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_AUTODETECT_NATIVE_SCREEN_SHAPE

inline void gels_AutodetectNativeScreenShape() {
	// Get information about our video hardware //    
	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
	
	// Check video hardware //
	if ( VideoInfo ) {
		int CanSetMode = SDL_VideoModeOK( VideoInfo->current_w, VideoInfo->current_h, VideoInfo->vfmt->BitsPerPixel, SDL_FULLSCREEN|SDL_OPENGL);

		Log( "Can I set this resolution? %s (%ibit)\n", 
			CanSetMode ?
			"Yes" : "No",
			CanSetMode
			);

		if ( CanSetMode ) {
			NativeScreen::Width = VideoInfo->current_w;
			NativeScreen::Height = VideoInfo->current_h;
			System::InitFlags.NativeShapeDetected = true;
		}
		Log( "\n" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_AUTODETECT_SCREEN_SHAPE

inline void gels_AutodetectScreenShape() {
	// Get information about our video hardware //    
	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
	
	// Check video hardware //
	if ( VideoInfo ) {
		int CanSetMode = SDL_VideoModeOK( VideoInfo->current_w, VideoInfo->current_h, VideoInfo->vfmt->BitsPerPixel, SDL_FULLSCREEN|SDL_OPENGL);

		Log( "Can I set this resolution? %s (%ibit)\n", 
			CanSetMode ?
			"Yes" : "No",
			CanSetMode
			);

		if ( CanSetMode ) {
			ActualScreen::Width = VideoInfo->current_w;
			ActualScreen::Height = VideoInfo->current_h;
		}
		
		Log( "\n" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_SDL_EGLPROXY
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_VIDEO_MODE

// Given all prior settings, set the video mode //
inline void gels_SetVideoMode() {
	// Get information about our video hardware //    
	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
	
	// In the incredibly unlikely case that we have no video hardware... //  
	if ( VideoInfo ) {
		// Construct our list of SDL video options //
		int VideoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE; // | SDL_RESIZABLE  

		if ( System::InitFlags.FullScreen ) {
			VideoFlags |= SDL_FULLSCREEN;
			System::InfoFlags.IsFullScreen = true;
		}
		else {
			System::InfoFlags.IsFullScreen = false;
		}
		
		// Depeding on if our hardware supports a hardware framebuffer //
	    if ( VideoInfo->hw_available )
			VideoFlags |= SDL_HWSURFACE;
	    else
			VideoFlags |= SDL_SWSURFACE;
		
		// Hardware blitting support (a good thing) //
	    if ( VideoInfo->blit_hw )
			VideoFlags |= SDL_HWACCEL;
	
		int ColorDepth = 32;

		if ( !System::InitFlags.FullScreen ) {
			ColorDepth = VideoInfo->vfmt->BitsPerPixel;
		}

//		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
//		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 6 );
//		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
		
					
		// Pre window creation GL Attributes //
//		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
//		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
//		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
//		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
//		SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
		// If omitted: //
		// OSX: 32bit 8/8/8/8
		//      16bit 5/5/5/0
		// Linux: 32bit 8/8/8/?
		//        16bit 
		// Windows: 32bit 8/8/8/0 (NVidia)
		//          32bit 8/8/8/8 (GMA)
		//          16bit 8/8/8/0 (NVidia 8600 64bit)
		//          16bit 5/6/5/0 (NVidia 4200m)
		//          16bit 5/6/5/0 (GMA)
		
		if ( System::StencilSize ) {
			SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, System::StencilSize );
		}
		
		if ( System::DepthSize ) {
			SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, System::DepthSize );
		}
	
	//	SDL_GL_SetAttribute( SDL_GL_SUGGEST, SDL_GL_DOUBLEBUFFER | SDL_GL_Z_DEPTH | SDL_GL_RENDERMETHOD | SDL_GL_SAMPLE_BUFFERS | SDL_GL_SAMPLES );
	
//		extern const char ProductName[];
//		SDL_WM_SetCaption( ProductName, NULL );
		extern const char FullProductName[];
		SDL_WM_SetCaption( FullProductName, NULL );
	
		
		//	float largest_supported_anisotropy;
		//	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy); 
		//-	Log( LOG_HIGHEST_LEVEL, "largest_supported_anisotropy: " << largest_supported_anisotropy );
			
		// Create our Screen //
		Buffer = SDL_SetVideoMode( ActualScreen::Width, ActualScreen::Height, ColorDepth, VideoFlags );	

		
		const SDL_VideoInfo* VideoInfo2 = SDL_GetVideoInfo();
		Log( "Set Resolution: %ix%i %ibbp\n", VideoInfo2->current_w, VideoInfo2->current_h, VideoInfo2->vfmt->BitsPerPixel );
		
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 0;
		SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &r );
		SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &g );
		SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &b );
		SDL_GL_GetAttribute( SDL_GL_ALPHA_SIZE, &a );
		Log( "OpenGL Surface RGBA Mode: %i%i%i%i\n", r,g,b,a );
		
		int DepthBits = 0;
		glGetIntegerv( GL_DEPTH_BITS, (GLint*)&DepthBits );
		Log( "Depth Bits: %i\n", DepthBits );

		int StencilBits = 0;
		glGetIntegerv( GL_STENCIL_BITS, (GLint*)&StencilBits );
		Log( "Stencil Bits: %i\n", StencilBits );
		
		char TextBuffer[256];
		SDL_VideoDriverName(TextBuffer, sizeof(TextBuffer));
		Log( "Driver: %s\n\n", TextBuffer);
		
#ifdef GELS_SCAN_GL_EXTENSIONS
		gels_ScanGLExtensions();
#endif // GELS_SCAN_GL_EXTENSIONS //
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL_EGLPROXY //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_SWAP_INTERVAL

// 0 - no sync, 1 - 60 fps sync, 2 - 30 fps sync //
inline void gels_SetSwapInterval( const int Var = 1 ) {
#ifdef PRODUCT_WINDOWS
	// Disable Vertical Sync //	 
	typedef void (APIENTRY * WGLSWAPINTERVALEXT) ( int ) ;
			
	WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT) SDL_GL_GetProcAddress( "wglSwapIntervalEXT" ) ;
	if ( wglSwapIntervalEXT != 0 ) {
		// Disable vertical synchronisation :
		wglSwapIntervalEXT( Var ) ;
	} 
#else // NIX_BUILD //
	Var;
#endif // NIX_BUILD //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL_2 //
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Init_SDL_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
