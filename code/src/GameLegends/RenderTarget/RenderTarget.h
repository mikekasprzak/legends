// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDERTARGET_H__
#define __GEL_RENDERTARGET_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_FBO) || defined(USES_FBO_EXT) || defined(USES_FBO_OES)
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_FBO)
// - ------------------------------------------------------------------------------------------ - //
#define gels_GenFramebuffers			glGenFramebuffers
#define gels_DeleteFramebuffers			glDeleteFramebuffers
#define gels_BindFramebuffer			glBindFramebuffer
#define gels_GenRenderBuffers			glGenRenderbuffers
#define gels_DeleteRenderbuffers		glDeleteRenderbuffers
#define gels_BindRenderbuffer			glBindRenderbuffer
#define gels_RenderbufferStorage 		glRenderbufferStorage
#define gels_FramebufferTexture2D		glFramebufferTexture2D
#define gels_FramebufferRenderbuffer	glFramebufferRenderbuffer
#define gels_CheckFramebufferStatus		glCheckFramebufferStatus

#define GELS_FRAMEBUFFER				GL_FRAMEBUFFER
#define GELS_RENDERBUFFER				GL_RENDERBUFFER
#define GELS_DEPTH_COMPONENT			GL_DEPTH_COMPONENT
#define GELS_STENCIL_COMPONENT			GL_STENCIL_COMPONENT
#define GELS_FRAMEBUFFER_COMPLETE		GL_FRAMEBUFFER_COMPLETE
#define GELS_MAX_COLOR_ATTACHMENTS		GL_MAX_COLOR_ATTACHMENTS
#define GELS_COLOR_ATTACHMENT0			GL_COLOR_ATTACHMENT0
#define GELS_COLOR_ATTACHMENT1			GL_COLOR_ATTACHMENT1
#define GELS_COLOR_ATTACHMENT2			GL_COLOR_ATTACHMENT2
#define GELS_COLOR_ATTACHMENT3			GL_COLOR_ATTACHMENT3
#define GELS_COLOR_ATTACHMENT4			GL_COLOR_ATTACHMENT4
#define GELS_COLOR_ATTACHMENT5			GL_COLOR_ATTACHMENT5
#define GELS_COLOR_ATTACHMENT6			GL_COLOR_ATTACHMENT6
#define GELS_COLOR_ATTACHMENT7			GL_COLOR_ATTACHMENT7
#define GELS_COLOR_ATTACHMENT8			GL_COLOR_ATTACHMENT8
#define GELS_COLOR_ATTACHMENT9			GL_COLOR_ATTACHMENT9
#define GELS_COLOR_ATTACHMENT10			GL_COLOR_ATTACHMENT10
#define GELS_COLOR_ATTACHMENT11			GL_COLOR_ATTACHMENT11
#define GELS_COLOR_ATTACHMENT12			GL_COLOR_ATTACHMENT12
#define GELS_COLOR_ATTACHMENT13			GL_COLOR_ATTACHMENT13
#define GELS_COLOR_ATTACHMENT14			GL_COLOR_ATTACHMENT14
#define GELS_COLOR_ATTACHMENT15			GL_COLOR_ATTACHMENT15
#define GELS_DEPTH_ATTACHMENT			GL_DEPTH_ATTACHMENT
#define GELS_STENCIL_ATTACHMENT			GL_STENCIL_ATTACHMENT
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_FBO_EXT)
// - ------------------------------------------------------------------------------------------ - //
#define gels_GenFramebuffers			glGenFramebuffersEXT
#define gels_DeleteFramebuffers			glDeleteFramebuffersEXT
#define gels_BindFramebuffer			glBindFramebufferEXT
#define gels_GenRenderBuffers			glGenRenderbuffersEXT
#define gels_DeleteRenderbuffers		glDeleteRenderbuffersEXT
#define gels_BindRenderbuffer			glBindRenderbufferEXT
#define gels_RenderbufferStorage 		glRenderbufferStorageEXT
#define gels_FramebufferTexture2D		glFramebufferTexture2DEXT
#define gels_FramebufferRenderbuffer	glFramebufferRenderbufferEXT
#define gels_CheckFramebufferStatus		glCheckFramebufferStatusEXT

#define GELS_FRAMEBUFFER				GL_FRAMEBUFFER_EXT
#define GELS_RENDERBUFFER				GL_RENDERBUFFER_EXT
#define GELS_DEPTH_COMPONENT			GL_DEPTH_COMPONENT_EXT
#define GELS_STENCIL_COMPONENT			GL_STENCIL_COMPONENT_EXT
#define GELS_FRAMEBUFFER_COMPLETE		GL_FRAMEBUFFER_COMPLETE_EXT
#define GELS_MAX_COLOR_ATTACHMENTS		GL_MAX_COLOR_ATTACHMENTS_EXT
#define GELS_COLOR_ATTACHMENT0			GL_COLOR_ATTACHMENT0_EXT
#define GELS_COLOR_ATTACHMENT1			GL_COLOR_ATTACHMENT1_EXT
#define GELS_COLOR_ATTACHMENT2			GL_COLOR_ATTACHMENT2_EXT
#define GELS_COLOR_ATTACHMENT3			GL_COLOR_ATTACHMENT3_EXT
#define GELS_COLOR_ATTACHMENT4			GL_COLOR_ATTACHMENT4_EXT
#define GELS_COLOR_ATTACHMENT5			GL_COLOR_ATTACHMENT5_EXT
#define GELS_COLOR_ATTACHMENT6			GL_COLOR_ATTACHMENT6_EXT
#define GELS_COLOR_ATTACHMENT7			GL_COLOR_ATTACHMENT7_EXT
#define GELS_COLOR_ATTACHMENT8			GL_COLOR_ATTACHMENT8_EXT
#define GELS_COLOR_ATTACHMENT9			GL_COLOR_ATTACHMENT9_EXT
#define GELS_COLOR_ATTACHMENT10			GL_COLOR_ATTACHMENT10_EXT
#define GELS_COLOR_ATTACHMENT11			GL_COLOR_ATTACHMENT11_EXT
#define GELS_COLOR_ATTACHMENT12			GL_COLOR_ATTACHMENT12_EXT
#define GELS_COLOR_ATTACHMENT13			GL_COLOR_ATTACHMENT13_EXT
#define GELS_COLOR_ATTACHMENT14			GL_COLOR_ATTACHMENT14_EXT
#define GELS_COLOR_ATTACHMENT15			GL_COLOR_ATTACHMENT15_EXT
#define GELS_DEPTH_ATTACHMENT			GL_DEPTH_ATTACHMENT_EXT
#define GELS_STENCIL_ATTACHMENT			GL_STENCIL_ATTACHMENT_EXT
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_FBO_OES)
// - ------------------------------------------------------------------------------------------ - //
#define gels_GenFramebuffers			glGenFramebuffersOES
#define gels_DeleteFramebuffers			glDeleteFramebuffersOES
#define gels_BindFramebuffer			glBindFramebufferOES
#define gels_GenRenderBuffers			glGenRenderbuffersOES
#define gels_DeleteRenderbuffers		glDeleteRenderbuffersOES
#define gels_BindRenderbuffer			glBindRenderbufferOES
#define gels_RenderbufferStorage 		glRenderbufferStorageOES
#define gels_FramebufferTexture2D		glFramebufferTexture2DOES
#define gels_FramebufferRenderbuffer	glFramebufferRenderbufferOES
#define gels_CheckFramebufferStatus		glCheckFramebufferStatusOES

#define GELS_FRAMEBUFFER				GL_FRAMEBUFFER_OES
#define GELS_RENDERBUFFER				GL_RENDERBUFFER_OES
#define GELS_DEPTH_COMPONENT			GL_DEPTH_COMPONENT_OES
#define GELS_STENCIL_COMPONENT			GL_STENCIL_COMPONENT_OES
#define GELS_FRAMEBUFFER_COMPLETE		GL_FRAMEBUFFER_COMPLETE_OES
#define GELS_MAX_COLOR_ATTACHMENTS		GL_MAX_COLOR_ATTACHMENTS_OES
#define GELS_COLOR_ATTACHMENT0			GL_COLOR_ATTACHMENT0_OES
#define GELS_COLOR_ATTACHMENT1			GL_COLOR_ATTACHMENT1_OES
#define GELS_COLOR_ATTACHMENT2			GL_COLOR_ATTACHMENT2_OES
#define GELS_COLOR_ATTACHMENT3			GL_COLOR_ATTACHMENT3_OES
#define GELS_COLOR_ATTACHMENT4			GL_COLOR_ATTACHMENT4_OES
#define GELS_COLOR_ATTACHMENT5			GL_COLOR_ATTACHMENT5_OES
#define GELS_COLOR_ATTACHMENT6			GL_COLOR_ATTACHMENT6_OES
#define GELS_COLOR_ATTACHMENT7			GL_COLOR_ATTACHMENT7_OES
#define GELS_COLOR_ATTACHMENT8			GL_COLOR_ATTACHMENT8_OES
#define GELS_COLOR_ATTACHMENT9			GL_COLOR_ATTACHMENT9_OES
#define GELS_COLOR_ATTACHMENT10			GL_COLOR_ATTACHMENT10_OES
#define GELS_COLOR_ATTACHMENT11			GL_COLOR_ATTACHMENT11_OES
#define GELS_COLOR_ATTACHMENT12			GL_COLOR_ATTACHMENT12_OES
#define GELS_COLOR_ATTACHMENT13			GL_COLOR_ATTACHMENT13_OES
#define GELS_COLOR_ATTACHMENT14			GL_COLOR_ATTACHMENT14_OES
#define GELS_COLOR_ATTACHMENT15			GL_COLOR_ATTACHMENT15_OES
#define GELS_DEPTH_ATTACHMENT			GL_DEPTH_ATTACHMENT_OES
#define GELS_STENCIL_ATTACHMENT			GL_STENCIL_ATTACHMENT_OES
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_FBO //
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
class cRenderTarget {
public:
	size_t Width;
	size_t Height;
	
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
				gels_RenderbufferStorage( GELS_RENDERBUFFER, GELS_DEPTH_COMPONENT, Width, Height );
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
				gels_RenderbufferStorage( GELS_RENDERBUFFER, GELS_STENCIL_COMPONENT, Width, Height );
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
			gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[idx];
			
			if ( gels_CheckFramebufferStatus( GELS_FRAMEBUFFER ) != GELS_FRAMEBUFFER_COMPLETE ) {
				Log( "* ERROR: FBO %i Unavailable! (%i)", idx, FBO[idx] );
			}
			else {
				Log( "* FBO %i OK. (%i)", idx, FBO[idx] );
			}
		}
		
		gels_BindFramebuffer( GELS_FRAMEBUFFER, 0 ); // Unbind //
	}
};

//#ifdef USES_MRT
//			if ( FBO.size() == 1 )

//#ifdef USES_MRT // Multiple Render Targets //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_FBO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDERTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
