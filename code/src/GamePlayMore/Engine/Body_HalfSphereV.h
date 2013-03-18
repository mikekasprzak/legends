// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_HALFSPHEREV_H__
#define __PLAYMORE_BODY_HALFSPHEREV_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cBody_HalfSphereV {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_HalfSphereV thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Vector3D	Normal;		// Dividing Plane's Normal //
	Real 		Radius;
	Vector3D 	Pos;		// Position Last, so it can be followed by Verlet Members //

	// Verlet Members //
	Vector3D 	Old;		// Old Position (Verlet) //
	Real		InvMass;	// Inverse Mass (i.e. 1.0/Mass). This makes InvMass of 0 == infinity. //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_HalfSphereV()
	{
	}

	cBody_HalfSphereV( const Vector3D& _Pos, const Real& _Radius, const Vector3D& _Normal, const Vector3D& Velocity = Vector3D::Zero, const Real& Mass = Real::One ) :
		Normal( _Normal ),
		Radius( _Radius ),
		Pos( _Pos ),
		Old( _Pos - Velocity ),
		InvMass( (Mass != Real::Zero) ? Real::One / Mass : Real::Zero )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_HALFSPHEREV_H__ //
// - ------------------------------------------------------------------------------------------ - //
