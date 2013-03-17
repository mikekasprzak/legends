// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ART_HALFSPHERE_H__
#define __PLAYMORE_ART_HALFSPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
class cArt_HalfSphere {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cArt_HalfSphere thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Vector3D 	Pos;	// Relative //
	Real 		Radius;
	Vector3D	Normal;	// Dividing Plane Normal //
	GelColor 	Color;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cArt_HalfSphere()
	{
	}

	cArt_HalfSphere( const Vector3D& _Pos, const Real& _Radius, const Vector3D& _Normal, const GelColor _Color ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Normal( _Normal ),
		Color( _Color )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ART_HALFSPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
