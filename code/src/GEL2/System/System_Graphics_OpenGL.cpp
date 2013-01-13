// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Core/GelString.h>
#include "System.h"
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL2.h>
#include <External/OpenGL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WGL
#include <Windows.h>
#include <External/OpenGL/wglext.h>
#endif // USES_WGL //
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
int DepthBits = 0;
int StencilBits = 0;
int MaxTextureSize = 0;
// - ------------------------------------------------------------------------------------------ - //
void GraphicsInit() {
	#ifdef USES_WGL
	{
		Log( "-=- WGL -=-" );
		PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");
		if ( wglGetExtString ) {
			char* Extensions = ((char*(__stdcall*)(HDC))wglGetExtString)( wglGetCurrentDC() );
			Log( "WGL Extensions (ARB):\n%s", Extensions );
		}
		else {
			PROC wglGetExtString2 = wglGetProcAddress("wglGetExtensionsStringEXT");
			if ( wglGetExtString2 ) {
				char* Extensions = ((char*(__stdcall*)(HDC))wglGetExtString2)( wglGetCurrentDC() );
				Log( "WGL Extensions (EXT, no ARB):\n%s", Extensions );
			}
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
	
	int Dummy;	// Dummy Value for things we don't want to remember //

	// GL Environment Settings //
	glGetIntegerv( GL_DEPTH_BITS, (GLint*)&DepthBits );
	Log( "GL_DEPTH_BITS: %i", DepthBits );

	glGetIntegerv( GL_STENCIL_BITS, (GLint*)&StencilBits );
	Log( "GL_STENCIL_BITS: %i", StencilBits );
	
	Log( "" );

	{
		int Dummy2[2];
		Dummy2[0] = 0;
		Dummy2[1] = 0;
		glGetIntegerv( GL_MAX_VIEWPORT_DIMS, (GLint*)Dummy2 );
		Log( "GL_MAX_VIEWPORT_DIMS: %i, %i", Dummy2[0], Dummy2[1] );
	}

	Dummy = 0;
	glGetIntegerv( GL_MAX_RENDERBUFFER_SIZE, (GLint*)&Dummy );
	Log( "GL_MAX_RENDERBUFFER_SIZE: %i", Dummy );

	glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*)&System::MaxTextureSize );
	Log( "GL_MAX_TEXTURE_SIZE: %i", System::MaxTextureSize );

	Dummy = 0;
	glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, (GLint*)&Dummy );
	Log( "GL_MAX_CUBE_MAP_TEXTURE_SIZE: %i", Dummy );

	Dummy = 0;
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, (GLint*)&Dummy );
	Log( "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: %i", Dummy );
		
	Log( "" );
	Log( "TERMS: Attributes are Vertex Streams. Varyings are interpolated values from VS to FS. Uniforms are global variables/constants." );

	// TODO: Log more data. http://www.opengl.org/sdk/docs/man/xhtml/glGet.xml	
	Dummy = 0;
	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, (GLint*)&Dummy );
	Log( "GL_MAX_VERTEX_ATTRIBS: %i    (Max number of generic 4 component Vertex Attributes. [Minimum 8])", Dummy );

	Dummy = 0;
	glGetIntegerv( GL_MAX_VARYING_VECTORS, (GLint*)&Dummy );
	#ifdef USES_OPENGL2
	if ( Dummy == 0 ) {
		glGetIntegerv( GL_MAX_VARYING_COMPONENTS, (GLint*)&Dummy );
		Log( "GL_MAX_VARYING_COMPONENTS: %i [%i]    (Max number of interpolated fp values. [Minimum 8])", Dummy, Dummy / 4 );
	}
	else
	#endif // USES_OPENGL2 //
		Log( "GL_MAX_VARYING_VECTORS: %i    (Max number of 4 element interpolated fp values. [Minimum 8])", Dummy );

	Dummy = 0;
	glGetIntegerv( GL_MAX_VERTEX_UNIFORM_VECTORS, (GLint*)&Dummy );
	#ifdef USES_OPENGL2
	if ( Dummy == 0 ) {
		glGetIntegerv( GL_MAX_VERTEX_UNIFORM_COMPONENTS, (GLint*)&Dummy );
		Log( "GL_MAX_VERTEX_UNIFORM_COMPONENTS: %i [%i]    (Max number of fp, int, bool values. [Minimum 128])", Dummy, Dummy / 4 );
	}
	else 
	#endif // USES_OPENGL2 //
		Log( "GL_MAX_VERTEX_UNIFORM_VECTORS: %i    (Max number of 4 element fp, int, bool values. [Minimum 128])", Dummy );


	#if defined(USES_OPENGL3) || defined(USES_OPENGLES3)
	// http://www.opengl.org/wiki/Uniform_Buffer_Object
	Dummy = 0;
	glGetIntegerv( GL_MAX_VERTEX_UNIFORM_BLOCKS, (GLint*)&Dummy );
	Log( "GL_MAX_VERTEX_UNIFORM_BLOCKS: %i    (Max number of Uniform Blocks per Vertex Shader. [Minimum 12])", Dummy );
	#endif // defined(USES_OPENGL3) || defined(USES_OPENGLES3) //

	Dummy = 0;
	glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, (GLint*)&Dummy );
	Log( "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: %i    (Max number of TUs accessable from Vertex Shaders. [Minimum 0])", Dummy );

	Log( "" );
	
	Dummy = 0;
	glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_VECTORS, (GLint*)&Dummy );
	#ifdef USES_OPENGL2
	if ( Dummy == 0 ) {
		glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, (GLint*)&Dummy );
		Log( "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS: %i [%i]    (Max number of fp, int, bool values. [Minimum 16])", Dummy, Dummy / 4 );
	}
	else
	#endif // USES_OPENGL2 //
		Log( "GL_MAX_FRAGMENT_UNIFORM_VECTORS: %i    (Max number of 4 element fp, int, bool values. [Minimum 16])", Dummy );

	#if defined(USES_OPENGL3) || defined(USES_OPENGLES3)
	// http://www.opengl.org/wiki/Uniform_Buffer_Object
	Dummy = 0;
	glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_BLOCKS, (GLint*)&Dummy );
	Log( "GL_MAX_FRAGMENT_UNIFORM_BLOCKS: %i    (Max number of Uniform Blocks per Fragment Shader. [Minimum 12])", Dummy );
	#endif // defined(USES_OPENGL3) || defined(USES_OPENGLES3) //

	Dummy = 0;
	glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&Dummy );
	Log( "GL_MAX_TEXTURE_IMAGE_UNITS: %i    (Max number of TUs accessable from Fragment Shaders. [Minimum 8])", Dummy );

	Log( "" );
	
	// TODO: Detect PowerVR based Intel GPUs //
	// TODO: Detect CPUs //

	// Check both the Vendor and the Renderer, since Intel subcontracted the Linux driver to Tungsten. //
	// Intel GMA 950's have only enough texture cache for 1024x1024 textures, so making that the limit //
	if ( find_String( "Intel", OpenGLVendor ) || find_String( "Intel", OpenGLRenderer ) ) {
		Log( "* Found Intel GPU..." );
		System::GPUVendor = System::GPU_INTEL;
#ifndef PRODUCT_NO_INTEL_FIX
		if ( System::MaxTextureSize == 2048 ) {
			Log( "* Limiting textures to 1024x1024 (was %i) -- GMA Fix", System::MaxTextureSize );
			System::MaxTextureSize = 1024;
		}
#endif // PRODUCT_NO_INTEL_FIX //
	}
	else if ( find_String( "Imagination", OpenGLVendor ) || find_String( "PowerVR", OpenGLRenderer ) ) {
		Log( "* Found PowerVR (Imagination Technology) GPU..." );
		System::GPUVendor = System::GPU_POWERVR;
	}
	else if ( find_String( "ARM", OpenGLVendor ) || find_String( "Mali", OpenGLRenderer ) ) {
		Log( "* Found ARM GPU..." );
		System::GPUVendor = System::GPU_ARM;
	}
	else if ( find_String( "NVIDIA", OpenGLVendor ) || find_String( "NVIDIA", OpenGLRenderer ) ) {
		Log( "* Found NVIDIA GPU..." );
		System::GPUVendor = System::GPU_NVIDIA;
	}
	else if ( find_String( "ATI", OpenGLVendor ) || find_String( "ATI", OpenGLRenderer ) ) {
		Log( "* Found ATI (AMD) GPU..." );
		System::GPUVendor = System::GPU_ATI;
	}
	else if ( find_String( "AMD", OpenGLVendor ) || find_String( "AMD", OpenGLRenderer ) ) {
		Log( "* Found AMD (ATI) GPU..." );
		System::GPUVendor = System::GPU_AMD;
	}
	else if ( find_String( "Qualcomm", OpenGLVendor ) || find_String( "Adreno", OpenGLRenderer ) ) {
		Log( "* Found Qualcomm GPU..." );
		System::GPUVendor = System::GPU_QUALCOMM;
	}
	else if ( find_String( "Vivante", OpenGLVendor ) || find_String( "GC", OpenGLRenderer ) ) {
		Log( "* Found Vivante GPU..." );
		System::GPUVendor = System::GPU_VIVANTE;
	}
	else if ( find_String( "Hisilicon", OpenGLVendor ) || find_String( "Immersion", OpenGLRenderer ) ) {
		Log( "* Found HiSilicon Technologies (Huawei) GPU..." );
		System::GPUVendor = System::GPU_HISILICON;
	}
	else if ( find_String( "Broadcom", OpenGLVendor ) || find_String( "VideoCore", OpenGLRenderer ) ) {
		Log( "* Found Broadcom GPU..." );
		System::GPUVendor = System::GPU_BROADCOM;
	}
	else if ( find_String( "ZiiLABS", OpenGLVendor ) || find_String( "ZMS", OpenGLRenderer ) ) {
		Log( "* Found ZiiLABS GPU..." );
		System::GPUVendor = System::GPU_ZIILABS;
	}
	else if ( find_String( "Advanced", OpenGLVendor ) || find_String( "S", OpenGLRenderer ) ) {
		// Last, because their company name and GPU names are too generic (S5 Multicore) //
		Log( "* Found Advanced Graphics Corporation GPU..." );
		System::GPUVendor = System::GPU_AGC;
	}
	else {
		Log( "* Warning! Unknown GPU Vendor! (%s - %s)", OpenGLVendor, OpenGLRenderer );
		System::GPUVendor = System::GPU_UNKNOWN;
	}
	
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
void GraphicsExit() {
	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL2
// - ------------------------------------------------------------------------------------------ - //
