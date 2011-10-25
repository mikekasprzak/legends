// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Init_GLExtensions_H__
#define __GEL_Graphics_Init_GLExtensions_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Graphics/Graphics_System.h>
#include <Graphics/Graphics_Screen.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelString_Core.h>
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SCAN_GL_EXTENSIONS
inline void gels_ScanGLExtensions() {
	// Get OpenGL Information Strings //
	const char* OpenGLVendor = (const char*)glGetString( GL_VENDOR );
	const char* OpenGLRenderer = (const char*)glGetString( GL_RENDERER );
	const char* OpenGLVersion = (const char*)glGetString( GL_VERSION );
	const char* OpenGLExtensions = (const char*)glGetString( GL_EXTENSIONS );		

	// Log OpenGL Details //
	Log( "OpenGL Vendor: %s", OpenGLVendor );
	Log( "OpenGL Renderer: %s", OpenGLRenderer );
	Log( "OpenGL Version: %s", OpenGLVersion );
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	Log( "OpenGL Shading Language Version: %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
#endif // USES_OPENGLES2 //
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

	// Originally I disabled this, but I still want to know if it's supported. //
	// The define USES_PVRTC says whether the assets are included //
	if ( find_String( "GL_IMG_texture_compression_pvrtc", OpenGLExtensions ) ) {
		Log( "* Found PVRTC" );
		System::InfoFlags.HasPVRTC = true;
	}
			
	Log( "OpenGL Environment Settings" );
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*)&System::MaxTextureSize );
	Log( "GL_MAX_TEXTURE_SIZE: %i", System::MaxTextureSize );
		
	// Check both the Vendor and the Renderer, since Intel subcontracted the Linux driver to Tungsten. //
	// Intel GMA 950's have only enough texture cache for 1024x1024 textures, so making that the limit //
	if ( find_String( "Intel", OpenGLVendor ) ) {
		Log( "* Found Intel GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_INTEL;
#ifndef PRODUCT_NO_INTEL_FIX
		if ( System::MaxTextureSize == 2048 ) {
			Log( "* Limiting textures to 1024x1024 (was %i)", System::MaxTextureSize );
			System::MaxTextureSize = 1024;
		}
#endif // PRODUCT_NO_INTEL_FIX //
	}
	else if ( find_String( "Intel", OpenGLRenderer ) ) {
		Log( "* Found Intel GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_INTEL;
#ifndef PRODUCT_NO_INTEL_FIX
		if ( System::MaxTextureSize == 2048 ) {
			Log( "* Limiting textures to 1024x1024 (was %i)", System::MaxTextureSize );
			System::MaxTextureSize = 1024;
		}
#endif // PRODUCT_NO_INTEL_FIX //
	}
	else if ( find_String( "Imagination", OpenGLVendor ) ) {
		Log( "* Found PowerVR (Imagination Technology) GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_POWERVR;
	}
	else if ( find_String( "PowerVR", OpenGLRenderer ) ) {
		Log( "* Found PowerVR (Imagination Technology) GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_POWERVR;
	}
	else if ( find_String( "Vivante", OpenGLVendor ) ) {
		Log( "* Found Vivante GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_VIVANTE;
	}
	else if ( find_String( "GC8", OpenGLRenderer ) ) {
		Log( "* Found Vivante GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_VIVANTE;
	}
	else if ( find_String( "ARM", OpenGLVendor ) ) {
		Log( "* Found ARM GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_ARM;
	}
	else if ( find_String( "Mali", OpenGLRenderer ) ) {
		Log( "* Found ARM GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_ARM;
	}
	else if ( find_String( "NVIDIA", OpenGLVendor ) ) {
		Log( "* Found NVIDIA GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_NVIDIA;
	}
	else if ( find_String( "NVIDIA", OpenGLRenderer ) ) {
		Log( "* Found NVIDIA GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_NVIDIA;
	}
	else if ( find_String( "ATI", OpenGLVendor ) ) {
		Log( "* Found ATI (AMD) GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_ATI;
	}
	else if ( find_String( "ATI", OpenGLRenderer ) ) {
		Log( "* Found ATI (AMD) GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_ATI;
	}
	else if ( find_String( "AMD", OpenGLVendor ) ) {
		Log( "* Found AMD (ATI) GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_AMD;
	}
	else if ( find_String( "AMD", OpenGLRenderer ) ) {
		Log( "* Found AMD (ATI) GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_AMD;
	}
	else if ( find_String( "Qualcomm", OpenGLVendor ) ) {
		Log( "* Found Qualcomm GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_QUALCOMM;
	}
	else if ( find_String( "Adreno", OpenGLRenderer ) ) {
		Log( "* Found Qualcomm GPU..." );
		System::InfoFlags.GPUVendor = System::GEL_GPU_QUALCOMM;
	}
	else {
		Log( "* Warning! Unknown GPU Vendor! (%s - %s)", OpenGLVendor, OpenGLRenderer );
	}
	Log("");
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Init_GLExtensions_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //
