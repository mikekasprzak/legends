// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_HALFSPHERE_H__
#define __PLAYMORE_BODY_HALFSPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include "Body_Base.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Body_Sphere.h"
// - ------------------------------------------------------------------------------------------ - //
class cBody_HalfSphere: public cBody_Base {
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
	inline const cBody_Sphere& GetCircle() const {
		return *((cBody_Sphere*)&Radius);
	}
	inline const cBody_Sphere& GetSphere() const {
		return *((cBody_Sphere*)&Radius);
	}

	inline cBody_Sphere* GetCirclePtr() {
		return ((cBody_Sphere*)&Radius);
	}
	inline cBody_Sphere* GetSpherePtr() {
		return ((cBody_Sphere*)&Radius);
	}

	inline const bool Test( const cBody_Sphere& Vs ) const {
		Vector3D Line = Vs.Pos - Pos;
		Real RadiusSum = Radius + Vs.Radius;
//		Log( "%s --- %s === %s (%s=%s) [%s %s]", Pos.ToString(), Vs.Pos.ToString(), Line.ToString(), Line.Magnitude().ToString(), RadiusSum.ToString(), Radius.ToString(), Vs.Radius.ToString() );
		if ( Line.MagnitudeSquared() < RadiusSum*RadiusSum ) {
			// Passed the sphere check. Now to test versus the half-space //
			return dot(Normal,Line) > Real::Zero;
		}
		else {
			return false;
		}
	}

	// NOTE: This should get the nearest point on the entire shape //
	inline const Vector3D GetNearestPointOn( const Vector3D& Vs ) const {
		Vector3D Line = Vs-Pos;
		Real Side = dot( Normal, Line );
		
		if ( Side > Real::Zero ) {
			//Real Length = Line.NormalizeRet();
			Line.Normalize();
			return Pos + (Line*Radius);
		}
		else {
			Vector3D Tangent = Normal.Tangent();
			Vector3D PosA = Pos - (Radius * Tangent);
			
			Vector3D ToVs = Vs-PosA;
			Real Distance = dot( ToVs, Tangent );
			Distance = max( Real::Zero, Distance );
			Distance = min( Radius+Radius, Distance );

			return PosA + (Distance * Tangent);
		}
	}
	
	// TODO: Do just an edge version, using the half space to place end-caps.
	// Use this for the body //
	
	// TODO: Do a "fully inside" version, and make a new type BT_HALFCIRCLE_INSIDE //
	// Create a sensor of the Inside type. Score points upon fully inside. //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_HALFSPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
