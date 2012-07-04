// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_OPENGL_RENDERTARGET_H__
#define __GEL_OPENGL_RENDERTARGET_H__
// - ------------------------------------------------------------------------------------------ - //
// TIP: I may want to use a non Renderbuffer for Depth (i.e. a texture). //
//	If I do, it means I could use samplers in the shader for reading the data. //
// - ------------------------------------------------------------------------------------------ - //
// TODO: Allow choice of Depth and Stencil modes. //
//	GL_RGBA4	(ES2 Spec)
//	GL_RGB565	(ES2 Spec)
//	GL_RGB5_A1	(ES2 Spec)
//	GL_DEPTH_COMPONENT16
//	GL_DEPTH_COMPONENT24 (with extension)
//	GL_STENCIL_INDEX8
//	GL_DEPTH24_STENCIL8_EXT (with extension)
//	GL_DEPTH24_STENCIL8_OES (with extension)
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_FBO) || defined(USES_FBO_EXT) || defined(USES_FBO_OES)
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <Debug/GelDebug.h>
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
#include "RenderTarget_GLDefines.h"
// - ------------------------------------------------------------------------------------------ - //
class cRenderTarget {
public:
	size_t Width;
	size_t Height;

private:	
	std::vector< GLuint > FBO;				// If an MRT, then there will be only 1 FBO //
	std::vector< GLuint > Texture;
	std::vector< GLuint > DepthBuffer;
	std::vector< GLuint > StencilBuffer;		
		
public:
	inline cRenderTarget( const size_t _w, const size_t _h, const size_t _Textures, const size_t _DepthBuffers = 1, const size_t _StencilBuffers = 0, const bool UseMRT = true ) :
		Width( _w ),
		Height( _h )
	{
		// Number of FBOs //
#ifdef USES_MRT
		if ( UseMRT )
			FBO.resize( 1 );
		else
#endif // USES_MRT //
		FBO.resize( _Textures );

		// Generate FBO IDs //
		gels_GenFramebuffers( FBO.size(), &FBO[0] );
		
		
		// Depth Buffers //
		if ( _DepthBuffers > 0 ) {
			// Number of DepthBuffers //
			DepthBuffer.resize( _DepthBuffers );
			// Generate DepthBuffers IDs //
			gels_GenRenderBuffers( DepthBuffer.size(), &DepthBuffer[0] );
			
			// For all Depth Buffers //
			for ( size_t idx = 0; idx < _DepthBuffers; idx++ ) {
				gels_BindRenderbuffer( GELS_RENDERBUFFER, DepthBuffer[idx] );
				gels_RenderbufferStorage( GELS_RENDERBUFFER, GL_DEPTH_COMPONENT16, Width, Height );
			}
			gels_BindRenderbuffer( GELS_RENDERBUFFER, 0 ); // Unbind //
		}		


		// Stencil Buffers //
		if ( _StencilBuffers > 0 ) {
			// Number of StencilBuffers //
			StencilBuffer.resize( _StencilBuffers );
			// Generate StencilBuffer IDs //
			gels_GenRenderBuffers( StencilBuffer.size(), &StencilBuffer[0] );
			
			// For all Stencil Buffers //
			for ( size_t idx = 0; idx < _StencilBuffers; idx++ ) {
				gels_BindRenderbuffer( GELS_RENDERBUFFER, StencilBuffer[idx] );
				gels_RenderbufferStorage( GELS_RENDERBUFFER, GL_STENCIL_INDEX8, Width, Height );
			}
			gels_BindRenderbuffer( GELS_RENDERBUFFER, 0 ); // Unbind //			
		}


		// Number of Textures //
		Texture.resize( _Textures );
		// Generate Texture IDs //
		glGenTextures( Texture.size(), &Texture[0] );

		// For all Textures //
		for ( size_t idx = 0; idx < _Textures; idx++ ) {
#ifdef USES_MRT
			if ( UseMRT )
				gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[0] );
			else
#endif // USES_MRT //
			gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[idx] );
			
			glBindTexture( GL_TEXTURE_2D, Texture[idx] );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glBindTexture( GL_TEXTURE_2D, 0 );	// Unbind //

			// Bind texture to current FBO //
			gels_FramebufferTexture2D( GELS_FRAMEBUFFER, GELS_COLOR_ATTACHMENT0+idx, GL_TEXTURE_2D, Texture[idx], 0 );

#ifdef USES_MRT
			if ( (UseMRT && (idx == 0)) || (!UseMRT) ) {
#endif // USES_MRT //
				// Bind the Depth Buffer //
				if ( _DepthBuffers > 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_DEPTH_ATTACHMENT, GELS_RENDERBUFFER, DepthBuffer[idx] );
				}
				else if ( _DepthBuffers == 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_DEPTH_ATTACHMENT, GELS_RENDERBUFFER, DepthBuffer[0] );
				}
#ifdef USES_MRT
			}
#endif // USES_MRT //

#ifdef USES_MRT
			if ( (UseMRT && (idx == 0)) || (!UseMRT) ) {
#endif // USES_MRT //
				// Bind the Stencil Buffer //
				if ( _StencilBuffers > 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_STENCIL_ATTACHMENT, GELS_RENDERBUFFER, StencilBuffer[idx] );
				}
				else if ( _StencilBuffers == 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_STENCIL_ATTACHMENT, GELS_RENDERBUFFER, StencilBuffer[0] );
				}
#ifdef USES_MRT
			}
#endif // USES_MRT //
		}
		
		// Validate FBOs //
		for ( size_t idx = 0; idx < FBO.size(); idx++ ) {
			gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[idx] );
			
			if ( gels_CheckFramebufferStatus( GELS_FRAMEBUFFER ) != GELS_FRAMEBUFFER_COMPLETE ) {
				Log( "* ERROR: FBO %i Unavailable! (%i)", idx, FBO[idx] );
			}
			else {
				Log( "* FBO %i OK. (GL_ID: %i)", idx, FBO[idx] );
			}
		}
		
		gels_BindFramebuffer( GELS_FRAMEBUFFER, 0 ); // Unbind //
	}
	
	inline ~cRenderTarget() {
		if ( FBO.size() > 0 )
			gels_DeleteFramebuffers( FBO.size(), &FBO[0] );

		if ( Texture.size() > 0 )
			glDeleteTextures( Texture.size(), &Texture[0] );

		if ( DepthBuffer.size() > 0 )
			gels_DeleteRenderbuffers( DepthBuffer.size(), &DepthBuffer[0] );

		if ( StencilBuffer.size() > 0 )
			gels_DeleteRenderbuffers( StencilBuffer.size(), &StencilBuffer[0] );
	}
	
	inline void Bind( const size_t Index = 0 ) const {
		gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[Index] );
		
		glViewport( 
			0,
			0,
			Width, 
			Height
			);	
	}
		
	inline static void UnBind( ) {
		gels_BindFramebuffer( GELS_FRAMEBUFFER, 0 );
		
		glViewport( 
			0,
			0, 
			ActualScreen::Width, 
			ActualScreen::Height
			);
	}
	
	inline void BindAsTexture( const size_t Index = 0 ) const { 
		glBindTexture( GL_TEXTURE_2D, Texture[Index] );
	}
};

//#ifdef USES_MRT
//			if ( FBO.size() == 1 )

//#ifdef USES_MRT // Multiple Render Targets //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_FBO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_OPENGL_RENDERTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
