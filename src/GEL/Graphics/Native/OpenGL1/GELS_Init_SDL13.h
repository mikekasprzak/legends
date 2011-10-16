// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Init_SDL13_H__
#define __GEL_Graphics_Init_SDL13_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
#ifdef USES_SDL_1_3
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Graphics/Graphics_System.h>
#include <Graphics/Graphics_Screen.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
// - ------------------------------------------------------------------------------------------ - //
//extern SDL_Surface* Buffer;

extern SDL_Window* MyWindow;
extern SDL_WindowID MyWindowID;
extern SDL_GLContext MyGLContext;

extern int ActualRefreshRate;
extern Uint32 ActualPixelFormat;

extern int NativeRefreshRate;
extern Uint32 NativePixelFormat;
// - ------------------------------------------------------------------------------------------ - //
#define GELS_GRAPHICS_EXIT

inline void gels_GraphicsExit() {
//	if ( Buffer ) { 
//		SDL_FreeSurface( Buffer );
//		Buffer = 0;
//	}

//	if ( MyContext )
	{
		SDL_GL_DeleteContext( MyGLContext );
	}

	if ( MyWindow ) {
		SDL_DestroyWindow( MyWindow );
		MyWindow = 0;
	}
}
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
	Log( "+ Attempting to Initialize SDL..." );
	//SDL_INIT_NOPARACHUTE
    if ( SDL_Init( 0 ) ) {
		ELog( "- SDL initialization failed: %s", SDL_GetError() );	    
	    exit( 1 );
	}
	else {
		Log( "- SUCCESS: SDL Initialized." );
	}

	Log( "" );
	
	// Check how many drivers there are (even though we only plan to use the first) //
	int NumVideoDrivers = SDL_GetNumVideoDrivers();
	Log( "+ Number of Video Drivers: %i", NumVideoDrivers );
	for ( int idx = 0; idx < NumVideoDrivers; idx++ ) {
		Log( "* Driver #%i: %s", idx, SDL_GetVideoDriver(idx) );
	}
	Log( "- Done Video Drivers" );
	Log( "" );

	Log( "+ Attempting to Initialize Default (0) Video Driver..." );
	// Note: Can specify a specific video driver here if you wanted //
    if ( SDL_VideoInit( NULL ) ) {
		ELog( "- SDL Video initialization failed: %s", SDL_GetError() );	    
	    exit( 1 );
	}
	else {
		Log( "- SUCCESS: SDL Video Initialized." );
	}
	Log( "" );

	// Check how many displays are driven by the current driver //
	int NumVideoDisplays = SDL_GetNumVideoDisplays();
	Log( "+ Number of Video Displays: %i", NumVideoDisplays );
	for ( int idx = 0; idx < NumVideoDisplays; idx++ ) {
		SDL_Rect rect;
		SDL_GetDisplayBounds( idx, &rect );
		Log( "* Display #%i: %i, %i", idx, rect.w, rect.h );
	}
	Log( "- Done Video Displays" );

//	Log( "" );
//	
//	// No longer supported!!! OH SHIT! //
//	Log( "- Setting Default (0) Display..." );
//    if ( SDL_SelectVideoDisplay( 0 ) ) {
//		Log( "* ERROR: SDL Video Display Set failed: %s", SDL_GetError() );	    
//	    exit( 1 );
//	}
//	else {
//		Log( "+ SUCCESS: SDL Video Display Set." );
//	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
inline const char* gels_SDLVideoModeName( Uint32 Format ) {
	switch( Format ) {
		case SDL_PIXELFORMAT_UNKNOWN: 		return "SDL_PIXELFORMAT_UNKNOWN";
		case SDL_PIXELFORMAT_INDEX1LSB:		return "SDL_PIXELFORMAT_INDEX1LSB";
		case SDL_PIXELFORMAT_INDEX1MSB:		return "SDL_PIXELFORMAT_INDEX1MSB";
		case SDL_PIXELFORMAT_INDEX4LSB:		return "SDL_PIXELFORMAT_INDEX4LSB";
		case SDL_PIXELFORMAT_INDEX4MSB:		return "SDL_PIXELFORMAT_INDEX4MSB";
		case SDL_PIXELFORMAT_INDEX8:		return "SDL_PIXELFORMAT_INDEX8";
		case SDL_PIXELFORMAT_RGB332:		return "SDL_PIXELFORMAT_RGB332";
		case SDL_PIXELFORMAT_RGB444:		return "SDL_PIXELFORMAT_RGB444";
		case SDL_PIXELFORMAT_RGB555:		return "SDL_PIXELFORMAT_RGB555";
		case SDL_PIXELFORMAT_BGR555:		return "SDL_PIXELFORMAT_BGR555";
		case SDL_PIXELFORMAT_ARGB4444:		return "SDL_PIXELFORMAT_ARGB4444";
		case SDL_PIXELFORMAT_ABGR4444:		return "SDL_PIXELFORMAT_ABGR4444";
		case SDL_PIXELFORMAT_ARGB1555:		return "SDL_PIXELFORMAT_ARGB1555";
		case SDL_PIXELFORMAT_ABGR1555:		return "SDL_PIXELFORMAT_ABGR1555";
		case SDL_PIXELFORMAT_RGB565:		return "SDL_PIXELFORMAT_RGB565";
		case SDL_PIXELFORMAT_BGR565:		return "SDL_PIXELFORMAT_BGR565";
		case SDL_PIXELFORMAT_RGB24:			return "SDL_PIXELFORMAT_RGB24";
		case SDL_PIXELFORMAT_BGR24:			return "SDL_PIXELFORMAT_BGR24";
		case SDL_PIXELFORMAT_RGB888:		return "SDL_PIXELFORMAT_RGB888";
		case SDL_PIXELFORMAT_BGR888:		return "SDL_PIXELFORMAT_BGR888";
		case SDL_PIXELFORMAT_ARGB8888:		return "SDL_PIXELFORMAT_ARGB8888";
		case SDL_PIXELFORMAT_RGBA8888:		return "SDL_PIXELFORMAT_RGBA8888";
		case SDL_PIXELFORMAT_ABGR8888:		return "SDL_PIXELFORMAT_ABGR8888";
		case SDL_PIXELFORMAT_BGRA8888:		return "SDL_PIXELFORMAT_BGRA8888";
		case SDL_PIXELFORMAT_ARGB2101010:	return "SDL_PIXELFORMAT_ARGB2101010";
		case SDL_PIXELFORMAT_YV12:			return "SDL_PIXELFORMAT_YV12";
		case SDL_PIXELFORMAT_IYUV:			return "SDL_PIXELFORMAT_IYUV";
		case SDL_PIXELFORMAT_YUY2:			return "SDL_PIXELFORMAT_YUY2";
		case SDL_PIXELFORMAT_UYVY:			return "SDL_PIXELFORMAT_UYVY";
		case SDL_PIXELFORMAT_YVYU:			return "SDL_PIXELFORMAT_YVYU";
	};
	return "???";
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_LOG_GRAPHICS_DETAILS

inline void gels_LogGraphicsDetails() {
	// About to begin Graphics Init Procedure //
	Log( "** Graphics Initalizing -=======-" );
	
	// Get information about our video hardware //
	SDL_DisplayMode DisplayMode;
	SDL_GetDesktopDisplayMode( 0, &DisplayMode ); // Obsolete!? //
	//SDL_GetFullscreenDisplayMode( &DisplayMode );
	//SDL_GetCurrentDisplayMode( &DisplayMode );
	
	Log( "* Desktop Resolution: %i x %i at %i Hz", DisplayMode.w, DisplayMode.h, DisplayMode.refresh_rate );
	Log( "* Pixel Format: %s -- More: %s", gels_SDLVideoModeName(DisplayMode.format), DisplayMode.driverdata != 0 ? "Yes" : "No" );
	Log( "" );

	{
		int NumDisplayModes = SDL_GetNumDisplayModes(0);
		VVLog( "+ Number of Fullscreen Display Modes: %i", NumDisplayModes );
		for (int idx = 0; idx < NumDisplayModes; idx++ ) {
			SDL_DisplayMode DisplayMode;
			SDL_GetDisplayMode( 0, idx, &DisplayMode );
			VLog("+ %i x %i at %i Hz -- %s", DisplayMode.w, DisplayMode.h, DisplayMode.refresh_rate, gels_SDLVideoModeName(DisplayMode.format) );
		}
		VVLog( "- Done Fullscreen Display Modes" );
		VVLog( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_AUTODETECT_NATIVE_SCREEN_SHAPE

inline void gels_AutodetectNativeScreenShape() {
	// Get information about our video hardware //    
	SDL_DisplayMode DisplayMode;
	SDL_GetDesktopDisplayMode( 0, &DisplayMode );

	NativeScreen::Width = DisplayMode.w;
	NativeScreen::Height = DisplayMode.h;
	NativeRefreshRate = DisplayMode.refresh_rate;
	NativePixelFormat = DisplayMode.format;
	System::InitFlags.NativeShapeDetected = true;
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_AUTODETECT_SCREEN_SHAPE

inline void gels_AutodetectScreenShape() {
	// Get information about our video hardware //    
	SDL_DisplayMode DisplayMode;
	SDL_GetDesktopDisplayMode( 0, &DisplayMode );

	ActualScreen::Width = DisplayMode.w;
	ActualScreen::Height = DisplayMode.h;
	ActualRefreshRate = DisplayMode.refresh_rate;
	ActualPixelFormat = DisplayMode.format;
}
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_VIDEO_MODE

// Given all prior settings, set the video mode //
inline void gels_SetVideoMode() {
/*
	// Get information about our video hardware //    
	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
	
	// In the incredibly unlikely case that we have no video hardware... //  
	if ( VideoInfo ) {
		// Construct our list of SDL video options //
		int VideoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_WINDOW_SHOWN; // | SDL_RESIZABLE  
*/
		Uint32 VideoFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;// | SDL_WINDOW_INPUT_GRABBED;

		if ( System::InitFlags.FullScreen ) {
			VideoFlags |= SDL_WINDOW_FULLSCREEN;
			System::InfoFlags.IsFullScreen = true;
		}
		else {
			System::InfoFlags.IsFullScreen = false;
		}
		
//		// Depeding on if our hardware supports a hardware framebuffer //
//	    if ( VideoInfo->hw_available )
//			VideoFlags |= SDL_HWSURFACE;
//	    else
//			VideoFlags |= SDL_SWSURFACE;
		
//		// Hardware blitting support (a good thing) //
//	    if ( VideoInfo->blit_hw )
//			VideoFlags |= SDL_HWACCEL;
	
//		int ColorDepth = 32;
//
//		if ( !System::InitFlags.FullScreen ) {
//			ColorDepth = VideoInfo->vfmt->BitsPerPixel;
//		}

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
	
		extern const char ProductName[];
//		SDL_WM_SetCaption( ProductName, NULL );
	
		
		//	float largest_supported_anisotropy;
		//	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy); 
		//-	Log( LOG_HIGHEST_LEVEL, "largest_supported_anisotropy: " << largest_supported_anisotropy );
			
		// Create our Screen //
//		Buffer = SDL_SetVideoMode( ActualScreen::Width, ActualScreen::Height, ColorDepth, VideoFlags );	

		MyWindow = SDL_CreateWindow( ProductName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ActualScreen::Width, ActualScreen::Height, VideoFlags );
		
//		const SDL_VideoInfo* VideoInfo2 = SDL_GetVideoInfo();
//		Log( "Set Resolution: %ix%i %ibbp", VideoInfo2->current_w, VideoInfo2->current_h, VideoInfo2->vfmt->BitsPerPixel );
		
		MyGLContext = SDL_GL_CreateContext( MyWindow );
		SDL_GL_MakeCurrent( MyWindow, MyGLContext );
		
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 0;
		SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &r );
		SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &g );
		SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &b );
		SDL_GL_GetAttribute( SDL_GL_ALPHA_SIZE, &a );
		Log( "OpenGL Surface RGBA Mode: %i%i%i%i", r,g,b,a );
		
		int DepthBits = 0;
		glGetIntegerv( GL_DEPTH_BITS, (GLint*)&DepthBits );
		Log( "Depth Bits: %i", DepthBits );

		int StencilBits = 0;
		glGetIntegerv( GL_STENCIL_BITS, (GLint*)&StencilBits );
		Log( "Stencil Bits: %i", StencilBits );
		
		char TextBuffer[256];
		SDL_VideoDriverName(TextBuffer, sizeof(TextBuffer));
		Log( "Driver: %s", TextBuffer);
		Log( "" );
		
		// Get OpenGL Information Strings //
		const char* OpenGLVendor = (const char*)glGetString( GL_VENDOR );
		const char* OpenGLRenderer = (const char*)glGetString( GL_RENDERER );
		const char* OpenGLVersion = (const char*)glGetString( GL_VERSION );
		const char* OpenGLExtensions = (const char*)glGetString( GL_EXTENSIONS );		
		
		// Log OpenGL Details //
		Log( "OpenGL Vendor: %s", OpenGLVendor );
		Log( "OpenGL Renderer: %s", OpenGLRenderer );
		Log( "OpenGL Version: %s", OpenGLVersion );
#ifndef USES_OPENGLES
		Log( "OpenGL Shading Language Version: %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
#endif // USES_OPENGLES //
		Log( "OpenGL Extensions:" );
		Log( "%s", OpenGLExtensions );
				
		
		if ( find_String( "GL_EXT_texture_compression_s3tc", OpenGLExtensions ) ) {
			Log( "* Found S3TC" );
			System::InfoFlags.HasS3TC = true;
		}
		else if ( find_String( "GL_S3_s3tc", OpenGLExtensions ) ) {
			Log( "* Found S3TC" );
			System::InfoFlags.HasS3TC = true;
		}

		if ( find_String( "GL_IMG_texture_compression_pvrtc", OpenGLExtensions ) ) {
			Log( "* Found PVRTC" );
			System::InfoFlags.HasPVRTC = true;
		}
		
/*
		// Newer OpenGL's only //
		int NumExtensions = 0;
		glGetIntegerv( GL_NUM_EXTENSIONS, &NumExtensions );
		Log( "OpenGL Extensions (%i):", NumExtensions );
		for ( int idx = 0; idx < NumExtensions; idx++ ) {
			printf( "* %s", glGetStringi( GL_EXTENSIONS, idx ) );
		}
*/
		Log( "" );
		
		Log( "OpenGL Environment Settings" );
		glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*)&System::MaxTextureSize );
		Log( "GL_MAX_TEXTURE_SIZE: %i", System::MaxTextureSize );
			
#ifndef PRODUCT_NO_INTEL_FIX
		// Check both the Vendor and the Renderer, since Intel subcontracted the Linux driver to Tungsten. //
		// Intel GMA 950's have only enough texture cache for 1024x1024 textures, so making that the limit //
		if ( find_String( "Intel", OpenGLVendor ) ) {
			Log( "* Found Intel GPU" );
			System::InfoFlags.GPUVendor = System::GEL_GPU_INTEL;
			if ( System::MaxTextureSize == 2048 ) {
				Log( "* Limiting textures to 1024x1024 (was %i)", System::MaxTextureSize );
				System::MaxTextureSize = 1024;
			}
		}
		else if ( find_String( "Intel", OpenGLRenderer ) ) {
			Log( "* Found Intel GPU" );
			System::InfoFlags.GPUVendor = System::GEL_GPU_INTEL;
			if ( System::MaxTextureSize == 2048 ) {
				Log( "* Limiting textures to 1024x1024 (was %i)", System::MaxTextureSize );
				System::MaxTextureSize = 1024;
			}
		}
#endif // PRODUCT_NO_INTEL_FIX //

		Log( "" ); 
//	}
}
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
#endif // USES_SDL_1_3 //
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Init_SDL13_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
