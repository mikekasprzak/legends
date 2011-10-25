// - ------------------------------------------------------------------------------------------ - //
#include "Graphics.h"
#include "GraphicsDraw.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL/GELS_Init_SDL_EGLProxy.h"
#include "Native/OpenGL/GELS_Init_SDL.h"
#include "Native/OpenGL/GELS_Init_SDL13.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelExit( ) {
#ifdef GELS_EXIT
	gels_Exit();
#endif // GELS_EXIT //
}
// - ------------------------------------------------------------------------------------------ - //
void gelGraphicsExit( ) {
#ifdef GELS_GRAPHICS_EXIT
	gels_GraphicsExit();
#endif // GELS_GRAPHICS_EXIT //
}
// - ------------------------------------------------------------------------------------------ - //
bool gelHasShutdown() {
	if ( System::CloseButtonPressed )
		return true;
	
	return System::ShutdownGame;
}
// - ------------------------------------------------------------------------------------------ - //
void gelShutdown() {
	System::ShutdownGame = true;
}
// - ------------------------------------------------------------------------------------------ - //
void gelMinimize() {
#ifdef GELS_MINIMIZE
	gels_Minimize();
#endif // GELS_MINIMIZE //
}
// - ------------------------------------------------------------------------------------------ - //
