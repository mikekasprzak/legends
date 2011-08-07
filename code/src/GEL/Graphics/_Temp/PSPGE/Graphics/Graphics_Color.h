// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Color_H__
#define __Graphics_Color_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetColor( const GelColor Color ) {
	if ( Current::Color != Color ) {
		Current::Color = Color;
		gelsApplyColor( Current::Color );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelRestoreColor( const GelColor Color ) {
	if ( Current::Color != Color ) {
		gelsApplyColor( Current::Color );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetColor( const int r, const int g, const int b, const int a = 255 ) {
	gelSetColor( GEL_RGBA(r,g,b,a) );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetNormalColor( const GelColor Color ) {
	Current::NormalColor = Color;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetNormalColor( const int r, const int g, const int b, const int a = 255 ) {
	Current::NormalColor = GEL_RGBA(r,g,b,a);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetNormalLength( const Real NormalLength ) {
	Current::NormalLength = NormalLength;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Color_H__ //
// - ------------------------------------------------------------------------------------------ - //
