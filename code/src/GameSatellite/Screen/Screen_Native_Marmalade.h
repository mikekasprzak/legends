// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SCREEN_NATIVE_MARMALADE_H__
#define __GEL_SCREEN_NATIVE_MARMALADE_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_MARMALADE
// - ------------------------------------------------------------------------------------------ - //
//#include <gl/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelError.h>
#include <Core/GelArray.h>
#include <Debug/Log.h>
#include "main_Product.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Screen {
// - ------------------------------------------------------------------------------------------ - //
class cNative {
public:
	inline cNative() {
	}
	
	inline ~cNative() {
	}

public:
//	// Outside Interface. Call these only after creating a Window. //
//	inline const int GetWidth() const {
//		return Bounds.w;
//	}
//	inline const int GetHeight() const {
//		return Bounds.h;
//	}
//	inline const int GetX() const {
//		return Bounds.x;
//	}
//	inline const int GetY() const {
//		return Bounds.y;
//	}
//	
//	inline const float GetAspectRatio() const {
//		return (float)Bounds.h / (float)Bounds.w;
//	}

};
// - ------------------------------------------------------------------------------------------ - //
extern cNative* Native;
// - ------------------------------------------------------------------------------------------ - //
inline void InitNative() {
	Native = new cNative;	
}
// - ------------------------------------------------------------------------------------------ - //
inline void DestroyNative() {
	delete Native;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Screen //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MARMALADE //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SCREEN_NATIVE_MARMALADE_H__ //
// - ------------------------------------------------------------------------------------------ - //
