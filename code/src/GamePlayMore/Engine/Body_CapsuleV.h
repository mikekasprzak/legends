// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_CAPSULEV_H__
#define __PLAYMORE_BODY_CAPSULEV_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include "Body_Base.h"
// - ------------------------------------------------------------------------------------------ - //
class cBody_CapsuleV: public cBody_Base {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_CapsuleV thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Real 		RadiusA;
	Vector3D 	PosA;
	Vector3D	OldA;
	Real 		RadiusB;
	Vector3D 	PosB;
	Vector3D	OldB;

	Real		InvMass;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_CapsuleV()
	{
	}

	cBody_CapsuleV( const Vector3D& _PosA, const Real& _RadiusA, const Vector3D& _PosB, const Real& _RadiusB, const Vector3D& VelocityA = Vector3D::Zero, const Vector3D& VelocityB = Vector3D::Zero, const Real& Mass = Real::One ) :
		RadiusA( _RadiusA ),
		PosA( _PosA ),
		OldA( _PosA - VelocityA ),
		RadiusB( _RadiusB ),
		PosB( _PosB ),
		OldB( _PosB - VelocityB ),
		InvMass( (Mass != Real::Zero) ? Real::One / Mass : Real::Zero )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_CAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
