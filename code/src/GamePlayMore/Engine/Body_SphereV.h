// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_SPHEREV_H__
#define __PLAYMORE_BODY_SPHEREV_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cBody_SphereV {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_SphereV thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Real 		Radius;
	Vector3D 	Pos;		// Position Last, so it can be followed by Verlet Members //

	// Verlet Members //
	Vector3D 	Old;		// Old Position (Verlet) //
	Real		InvMass;	// Inverse Mass (i.e. 1.0/Mass). This makes InvMass of 0 == infinity. //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_SphereV()
	{
	}

	cBody_SphereV( const Vector3D& _Pos, const Real& _Radius ) :
		Radius( _Radius ),
		Pos( _Pos ),
		Old( _Pos ),
		InvMass( Real::One )
	{
	}

	// Mass of 0 is considered Infinity (Even though according to usage here it's massless) //
	cBody_SphereV( const Vector3D& _Pos, const Real& _Radius, const Vector3D& _Velocity, const Real& Mass = Real::One ) :
		Radius( _Radius ),
		Pos( _Pos ),
		Old( _Pos - _Velocity ),
		InvMass( (Mass != Real::Zero) ? Real::One / Mass : Real::Zero )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// NOTE: This explicitly sets the velocity property. It does not accumulate. //
	inline void SetVelocity( const Vector3D& _Velocity ) {
		Old = Pos - _Velocity;
	}
	// NOTE: Mass of 0 is considered infinite strength mass (not massless) //
	inline void SetMass( const Real& _Mass ) {
		if ( _Mass != Real::Zero ) {
			InvMass = Real::One / _Mass;
		}
		else {
			InvMass = _Mass;
		}
	}
public:
	inline void Step() {	
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_SPHEREV_H__ //
// - ------------------------------------------------------------------------------------------ - //
