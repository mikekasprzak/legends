// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Support_EGL_H__
#define __Graphics_Support_EGL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_EGL
// - ------------------------------------------------------------------------------------------ - //
extern EGLDisplay egl_display;
extern EGLSurface egl_surface;
extern EGLContext egl_context;
// - ------------------------------------------------------------------------------------------ - //
#define GELS_SWAPBUFFER

inline void gelsSwapBuffer() {
	glFinish();
	eglSwapBuffers(egl_display, egl_surface);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_EGL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Support_EGL_H__ //
// - ------------------------------------------------------------------------------------------ - //