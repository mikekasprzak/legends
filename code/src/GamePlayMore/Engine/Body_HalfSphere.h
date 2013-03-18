// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_HALFSPHERE_H__
#define __PLAYMORE_BODY_HALFSPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cBody_HalfSphere {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_HalfSphere thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Vector3D	Normal;		// Dividing Plane's Normal //
	Real 		Radius;
	Vector3D 	Pos;		// Position Last, so it can be followed by Verlet Members //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_HalfSphere()
	{
	}

	cBody_HalfSphere( const Vector3D& _Pos, const Real& _Radius, const Vector3D& _Normal ) :
		Normal( _Normal ),
		Radius( _Radius ),
		Pos( _Pos )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_HALFSPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
