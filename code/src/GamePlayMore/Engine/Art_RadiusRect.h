// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ART_RADIUSRECT_H__
#define __PLAYMORE_ART_RADIUSRECT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
class cArt_RadiusRect {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cArt_RadiusRect thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Vector3D 	Pos;	// Relative //
	Vector2D	Radius;
	GelColor 	Color;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cArt_RadiusRect()
	{
	}

	cArt_RadiusRect( const Vector3D& _Pos, const Vector2D& _Radius, const GelColor _Color ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Color( _Color )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ART_RADIUSRECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
