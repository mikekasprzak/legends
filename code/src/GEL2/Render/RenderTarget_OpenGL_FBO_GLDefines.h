// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_OPENGL_RENDERTARGET_GLDEFINES_H__
#define __GEL2_OPENGL_RENDERTARGET_GLDEFINES_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
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
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_OPENGL_RENDERTARGET_GLDEFINES_H__ //
// - ------------------------------------------------------------------------------------------ - //
