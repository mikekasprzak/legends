// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_SPHERE_H__
#define __PLAYMORE_BODY_SPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include "Body_Base.h"
// - ------------------------------------------------------------------------------------------ - //
class cBody_Sphere: public cBody_Base {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_Sphere thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Real 		Radius;
	Vector3D 	Pos;		// Position Last, so it can be followed by Verlet Members //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_Sphere() {
	}

	cBody_Sphere( const Vector3D& _Pos, const Real& _Radius ) :
		Radius( _Radius ),
		Pos( _Pos )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline const Vector3D GetVelocity() const {
		return Vector3D::Zero;
	}
	inline const Vector3D& GetPos() const {
		return Pos;
	}
	inline const Vector3D& GetOld() const {
		return Pos;
	}
	inline const Real GetMass() const {
		return Real::Zero;
	}
	inline const Real& GetFriction() const {
		return Real::Zero;	// Will not "Frick" //
	}
	inline const Real& GetRestitution() const {
		return Real::Zero;	// Will take Vs Instead //
	}
};
// - ------------------------------------------------------------------------------------------ - //
typedef cBody_Sphere cBody_Circle;
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_SPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
