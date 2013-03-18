// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_CAPSULEVT_H__
#define __PLAYMORE_BODY_CAPSULEVT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cBody_CapsuleVT {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_CapsuleVT thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Real 		RadiusA;
	Vector3D 	PosA;
	Vector3D	OldA;
	Real		InvMassA;
	Real 		RadiusB;
	Vector3D 	PosB;
	Vector3D	OldB;
	Real		InvMassB;
	
	Real		Length;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_CapsuleVT()
	{
	}

	cBody_CapsuleVT( const Vector3D& _PosA, const Real& _RadiusA, const Vector3D& _PosB, const Real& _RadiusB, const Vector3D& _VelocityA = Vector3D::Zero, const Vector3D& _VelocityB = Vector3D::Zero, const Real& _MassA = Real::One, const Real& _MassB = Real::One ) :
		RadiusA( _RadiusA ),
		PosA( _PosA ),
		OldA( _PosA - _VelocityA ),
		InvMassA( (_MassA != Real::Zero) ? Real::One / _MassA : Real::Zero ),
		RadiusB( _RadiusB ),
		PosB( _PosB ),
		OldB( _PosB - _VelocityB ),
		InvMassB( (_MassB != Real::Zero) ? Real::One / _MassB : Real::Zero ),
		Length( (_PosB - _PosA).Magnitude() )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_CAPSULEVT_H__ //
// - ------------------------------------------------------------------------------------------ - //
