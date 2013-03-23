// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_CAPSULE_H__
#define __PLAYMORE_BODY_CAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include "Body_Base.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Body_Sphere.h"
// - ------------------------------------------------------------------------------------------ - //
class cBody_Capsule: public cBody_Base {
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
	
	inline const cBody_Sphere& GetSphereA() const {
		return *((cBody_Sphere*)&RadiusA);
	}
	inline const cBody_Sphere& GetSphereB() const {
		return *((cBody_Sphere*)&RadiusB);
	}

	inline cBody_Sphere* GetSphereAPtr() {
		return ((cBody_Sphere*)&RadiusA);
	}
	inline cBody_Sphere* GetSphereBPtr() {
		return ((cBody_Sphere*)&RadiusB);
	}
	
	inline const cBody_Sphere GetSphere( const Real& LinePos ) const { // Between 0 and 1 //
		cBody_Sphere Ret;
		
		Vector3D Line = PosB-PosA;
		Ret.Pos = PosA + (Line * LinePos);
		Ret.Radius = mix( RadiusA, RadiusB, LinePos );
		
		return Ret;
	}

	inline const cBody_Sphere GetNearestSphere( const Vector3D& Pos ) const {
		cBody_Sphere Ret;

//		Log( "Near1 -- (%s) (%s) (%s)", PosA.ToString(), PosB.ToString(), Pos.ToString() );
		
		Vector3D Line = PosB-PosA;
		Vector3D ToPos = Pos-PosA;

//		Log( "Near2 -- (%s) vs (%s)", Line.ToString(), ToPos.ToString() );

		
		Real Length = Line.NormalizeRet();
		Real Distance = dot( Line, ToPos );
		Distance = max( Real::Zero, Distance );
		Distance = min( Length, Distance );

//		Log( "Near3 -- %s and %s", Length.ToString(), Distance.ToString() );
		
		Ret.Pos = PosA + (Line * Distance);
		Ret.Radius = mix( RadiusA, RadiusB, Distance/Length );
		
		return Ret;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_CAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
