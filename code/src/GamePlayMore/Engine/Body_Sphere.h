// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_SPHERE_H__
#define __PLAYMORE_BODY_SPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cBody_Sphere {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_Sphere thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Real 		Radius;
	Vector3D 	Pos;		// Position Last, so it can be followed by Verlet Members //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_Sphere()
	{
	}

	cBody_Sphere( const Vector3D& _Pos, const Real& _Radius ) :
		Radius( _Radius ),
		Pos( _Pos )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_SPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
