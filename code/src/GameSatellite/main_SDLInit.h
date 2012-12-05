// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_MAIN_SDLINIT_H__
#define __GEL_MAIN_SDLINIT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <SDL2/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
void ReportCompilerVersion();
void ReportSDLVersion();
void ReportSDLSystemInfo();
void ReportSDLInputInfo();
void ReportSDLGraphicsInfo();
void ReportOpenGLGraphicsInfo();
const char* SDL_WindowEventName( Uint8 EventName );
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_MAIN_SDLINIT_H__ //
// - ------------------------------------------------------------------------------------------ - //
