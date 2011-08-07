// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Current_H__
#define __GEL_Graphics_Current_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelFont/GelFont.h>
#include <Graphics/GelColor.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Current {
	extern const ::GelFont* Font;

	extern GelColor Color;
	extern GelColor NormalColor;
	extern Real NormalLength;
	
	extern int DrawMode;
	extern int OldDrawMode;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Current_H__ //
// - ------------------------------------------------------------------------------------------ - //
