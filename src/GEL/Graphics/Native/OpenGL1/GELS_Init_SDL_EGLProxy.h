// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Init_SDL_EGLProxy_H__
#define __GEL_Graphics_Init_SDL_EGLProxy_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
#ifndef USES_SDL_1_3
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL_EGLPROXY
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Graphics/Graphics_System.h>
#include <Graphics/Graphics_Screen.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
// - ------------------------------------------------------------------------------------------ - //
extern SDL_Surface* Buffer;
// - ------------------------------------------------------------------------------------------ - //
extern EGLDisplay g_eglDisplay;
extern EGLConfig g_eglConfig;
extern EGLContext g_eglContext;
extern EGLSurface g_eglSurface;
extern Display *g_x11Display;
 
// consts
#define COLOURDEPTH_RED_SIZE  		5
#define COLOURDEPTH_GREEN_SIZE 		6
#define COLOURDEPTH_BLUE_SIZE 		5
#define COLOURDEPTH_DEPTH_SIZE		16
 
extern const EGLint g_configAttribs[];

// - ------------------------------------------------------------------------------------------ - //
#define GELS_GRAPHICS_EXIT

inline void gels_GraphicsExit() {
	eglMakeCurrent(g_eglDisplay, NULL, NULL, EGL_NO_CONTEXT);
	eglDestroySurface(g_eglDisplay, g_eglSurface);
	eglDestroyContext(g_eglDisplay, g_eglContext);
	g_eglSurface = 0;
	g_eglContext = 0;
	g_eglConfig = 0;
	eglTerminate(g_eglDisplay);
	g_eglDisplay = 0;
	XCloseDisplay(g_x11Display);
	g_x11Display = NULL;
	
	if ( Buffer ) { 
		SDL_FreeSurface( Buffer );
		Buffer = 0;
	}
}

// - ------------------------------------------------------------------------------------------ - //
#define GELS_SET_VIDEO_MODE

// Given all prior settings, set the video mode //
inline void gels_SetVideoMode() {
	
	// Get information about our video hardware //    
	const SDL_VideoInfo* VideoInfo = SDL_GetVideoInfo();
	
	// In the incredibly unlikely case that we have no video hardware... //  
	if ( VideoInfo ) {
		// Construct our list of SDL video options //
		int VideoFlags = /*SDL_OPENGL |*/ SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE; // | SDL_RESIZABLE  

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
	
		extern const char ProductName[];
		SDL_WM_SetCaption( ProductName, NULL );
	
		
		//	float largest_supported_anisotropy;
		//	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy); 
		//-	Log( LOG_HIGHEST_LEVEL, "largest_supported_anisotropy: " << largest_supported_anisotropy );
			
		// Create our Screen //
		Buffer = SDL_SetVideoMode( ActualScreen::Width, ActualScreen::Height, ColorDepth, VideoFlags );	

		{
			// use EGL to initialise GLES
			Log( "- Getting X11 Display...\n" );
			g_x11Display = XOpenDisplay(NULL);
		 
			if (!g_x11Display)
			{
				Log("* ERROR: unable to get display!\n");
				return;
			}
		 
			Log( "- Initializing EGL...\n" );
			g_eglDisplay = eglGetDisplay((EGLNativeDisplayType)g_x11Display);
			if (g_eglDisplay == EGL_NO_DISPLAY)
			{
				Log("* ERROR: Unable to bind display to EGL.\n");
				return;
			}

			EGLint egl_majorversion;
			EGLint egl_minorversion;
		 
			if (!eglInitialize(g_eglDisplay, &egl_majorversion, &egl_minorversion))
			{
				Log("* ERROR: Unable to initialise EGL display.\n");
				return;
			}
			Log( "+ Successfully Initialized EGL -- v%i.%i\n", egl_majorversion, egl_minorversion );
		
			Log( "EGL Version: %s\n", eglQueryString(g_eglDisplay, EGL_VERSION) );
			Log( "Driver Vendor: %s\n", eglQueryString(g_eglDisplay, EGL_VENDOR) );
			Log( "Client APIs: %s\n", eglQueryString(g_eglDisplay, EGL_CLIENT_APIS) );
			Log( "Extensions: %s\n\n", eglQueryString(g_eglDisplay, EGL_EXTENSIONS) );
		 			
			{
				EGLint WindowConfigAttribList[] = {
//					EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
//					EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
//					EGL_RED_SIZE, 5,
//					EGL_GREEN_SIZE, 6,
//					EGL_BLUE_SIZE, 5,
			//		EGL_BIND_TO_TEXTURE_RGB, GL_TRUE,
			//		EGL_ALPHA_SIZE, EGL_DONT_CARE,
			//		EGL_BUFFER_SIZE, EGL_DONT_CARE,
			//		EGL_DEPTH_SIZE, EGL_DONT_CARE,
			//		EGL_STENCIL_SIZE, EGL_DONT_CARE,
			//		EGL_SAMPLE_BUFFERS, 0,
			
			//		EGL_NATIVE_RENDERABLE,    EGL_FALSE,
					EGL_NONE,
				};
			
				const EGLint MaxWindowConfigs = 10;
				EGLConfig WindowConfigs[MaxWindowConfigs];
				
				EGLint numConfigs;
				eglChooseConfig( g_eglDisplay, WindowConfigAttribList, WindowConfigs, MaxWindowConfigs, &numConfigs );
				Log( "+ %i configuration(s) found matching request.\n", numConfigs );
			}		 
		 
		 	
			// Find a matching config
			Log( "- eglChooseConfig\n" );
			EGLint numConfigsOut = 0;
			if (eglChooseConfig(g_eglDisplay, g_configAttribs, &g_eglConfig, 1, &numConfigsOut) != EGL_TRUE || numConfigsOut == 0)
			{
				Log("Unable to find appropriate EGL config.\n");
				return;
			}
			Log( "+ eglChooseConfig ok!\n" );
		 
			// Get the SDL window handle
			Log( "- SDL\n" );
			SDL_SysWMinfo sysInfo; //Will hold our Window information
			SDL_VERSION(&sysInfo.version); //Set SDL version
			Log( "- SDL\n" );
			if(SDL_GetWMInfo(&sysInfo) <= 0) 
			{
				Log("Unable to get window handle!\n");
				return;
			}
			Log( "+ SDL Ok!\n" );
		 
			Log( "- eglCreateWindowSurface\n" );
			g_eglSurface = eglCreateWindowSurface(g_eglDisplay, g_eglConfig, (EGLNativeWindowType)sysInfo.info.x11.window, 0);
			if ( g_eglSurface == EGL_NO_SURFACE)
			{
				Log("Unable to create EGL surface!\n");
				return;
			}
			Log( "+ eglCreateWindowSurface Ok!\n" );
		 
			// Bind GLES and create the context
			eglBindAPI(EGL_OPENGL_ES_API);
			EGLint contextParams[] = {EGL_CONTEXT_CLIENT_VERSION, 1, EGL_NONE};		// Use GLES version 1.x
			g_eglContext = eglCreateContext(g_eglDisplay, g_eglConfig, NULL, NULL);
			if (g_eglContext == EGL_NO_CONTEXT)
			{
				Log("Unable to create GLES context!\n");
				return;
			}
		 
			if (eglMakeCurrent(g_eglDisplay,  g_eglSurface,  g_eglSurface, g_eglContext) == EGL_FALSE)
			{
				Log("Unable to make GLES context current\n");
				return;
			}		
		}
		
		const SDL_VideoInfo* VideoInfo2 = SDL_GetVideoInfo();
		Log( "Set Resolution: %ix%i %ibbp\n", VideoInfo2->current_w, VideoInfo2->current_h, VideoInfo2->vfmt->BitsPerPixel );
		
//		int r = 0;
//		int g = 0;
//		int b = 0;
//		int a = 0;
//		SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &r );
//		SDL_GL_GetAttribute( SDL_GL_GREEN_SIZE, &g );
//		SDL_GL_GetAttribute( SDL_GL_BLUE_SIZE, &b );
//		SDL_GL_GetAttribute( SDL_GL_ALPHA_SIZE, &a );
//		Log( "OpenGL Surface RGBA Mode: %i%i%i%i\n", r,g,b,a );
		
		int DepthBits = 0;
		glGetIntegerv( GL_DEPTH_BITS, (GLint*)&DepthBits );
		Log( "Depth Bits: %i\n", DepthBits );

		int StencilBits = 0;
		glGetIntegerv( GL_STENCIL_BITS, (GLint*)&StencilBits );
		Log( "Stencil Bits: %i\n", StencilBits );
		
		char TextBuffer[256];
		SDL_VideoDriverName(TextBuffer, sizeof(TextBuffer));
		Log( "Driver: %s\n\n", TextBuffer);
		
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
#endif // USES_SDL_EGLPROXY //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL_1_3 //
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Init_SDL_EGLProxy_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
