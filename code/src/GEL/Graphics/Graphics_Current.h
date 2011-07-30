// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Current_H__
#define __GEL_Graphics_Current_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelFont/GelFont.h>
#include <Graphics/Color.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Current {
	extern const ::GelFont* Font;

	extern ColorType Color;
	extern ColorType NormalColor;
	extern Real NormalLength;
	
	extern int DrawMode;
	extern int OldDrawMode;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Current_H__ //
// - ------------------------------------------------------------------------------------------ - //
