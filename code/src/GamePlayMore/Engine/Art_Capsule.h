// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ART_CAPSULE_H__
#define __PLAYMORE_ART_CAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //
class cArt_Capsule {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cArt_Capsule thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Vector3D 	PosA;	// Relative //
	Real 		RadiusA;
	Vector3D 	PosB;	// Relative //
	Real 		RadiusB;
	GelColor 	Color;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cArt_Capsule()
	{
	}

	cArt_Capsule( const Vector3D& _PosA, const Real& _RadiusA, const Vector3D& _PosB, const Real& _RadiusB, const GelColor _Color ) :
		PosA( _PosA ),
		RadiusA( _RadiusA ),
		PosB( _PosB ),
		RadiusB( _RadiusB ),
		Color( _Color )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ART_CAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
