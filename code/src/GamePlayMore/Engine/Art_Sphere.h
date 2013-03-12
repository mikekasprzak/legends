// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ART_SPHERE_H__
#define __PLAYMORE_ART_SPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
class cArt_Sphere {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cArt_Sphere thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Vector3D 	Pos;	// Relative //
	Real 		Radius;
	GelColor 	Color;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cArt_Sphere()
	{
	}

	cArt_Sphere( const Vector3D& _Pos, const Real& _Radius, const GelColor _Color ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Color( _Color )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ART_SPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
