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
	Vector3D 	Pos;
	Real 		Radius;
	Vector3D 	Old;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_Sphere()
	{
	}

	cBody_Sphere( const Vector3D& _Pos, const Real& _Radius ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Old( _Pos )
	{
	}

	cBody_Sphere( const Vector3D& _Pos, const Vector3D& _Old, const Real& _Radius ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Old( _Old )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_SPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
