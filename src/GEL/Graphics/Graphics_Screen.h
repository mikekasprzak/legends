// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Screen_H__
#define __GEL_Graphics_Screen_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
// Reference Screen //
namespace RefScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;

	extern Real Scalar;
	extern int OffsetX;
	extern int OffsetY;

	extern int DiffX;
	extern int DiffY;
};
// - ------------------------------------------------------------------------------------------ - //
namespace FullRefScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;

	extern Vector2D Shape;
	extern Vector2D HalfShape;

	extern Real Scalar;
};
// - ------------------------------------------------------------------------------------------ - //
namespace ActualScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;
	extern bool TallScreen;

	extern Vector2D Shape;
	extern Vector2D HalfShape;
};
// - ------------------------------------------------------------------------------------------ - //
namespace ProxyScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;
	extern bool TallScreen;

	extern Vector2D Shape;
	extern Vector2D HalfShape;

	extern Real Scalar;
	extern int OffsetX;
	extern int OffsetY;

	extern int DiffX;
	extern int DiffY;
};
// - ------------------------------------------------------------------------------------------ - //
namespace OverscanScreen {
	extern int Width;
	extern int Height;
	
	extern Real AspectRatio;
	extern Vector2D Scalar;
};
// - ------------------------------------------------------------------------------------------ - //
namespace NativeScreen {
	extern int Width;
	extern int Height;
	
	extern Vector2D Scalar;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void gelSetClip( const int x, const int y, const int w, const int h );
void gelResetClip( );
void gelSetProxyClip( const int x, const int y, const int w, const int h );
void gelResetProxyClip( );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Screen_H__ //
// - ------------------------------------------------------------------------------------------ - //
