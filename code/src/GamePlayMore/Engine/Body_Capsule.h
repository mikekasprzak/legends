// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_CAPSULE_H__
#define __PLAYMORE_BODY_CAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cBody_Capsule {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_Capsule thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Real 		RadiusA;
	Vector3D 	PosA;
	Real 		RadiusB;
	Vector3D 	PosB;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	inline cBody_Capsule()
	{
	}

	inline cBody_Capsule( const Vector3D& _PosA, const Real& _RadiusA, const Vector3D& _PosB, const Real& _RadiusB ) :
		RadiusA( _RadiusA ),
		PosA( _PosA ),
		RadiusB( _RadiusB ),
		PosB( _PosB )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline const Vector3D GetCenter() const {
		return ((PosB-PosA) * Real::Half) + PosA;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_CAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
