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
	Real 		Radius;
	Vector3D 	Pos;		// Position Last, so it can be followed by Verlet Members //
	Vector3D	Normal;		// Dividing Plane's Normal //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_HalfSphere()
	{
	}

	cBody_HalfSphere( const Vector3D& _Pos, const Real& _Radius, const Vector3D& _Normal ) :
		Radius( _Radius ),
		Pos( _Pos ),
		Normal( _Normal )
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

	// NOTE: This should get the nearest point on the edge of shape //
	inline const Vector3D GetNearestPointOn( const Vector3D& Vs ) const {
		Vector3D Line = Vs-Pos;
		Real Side = dot( Normal, Line );
		
		if ( Side > Real::Zero ) {
			Line.Normalize();
			return Pos + (Line*Radius);
		}
		else {
			Line.Normalize();

			// TODO: The generated tangent normal should be inside the plane created by //
			//   the Line and the Normal. Right now this is just the Normal //
			Vector3D Tangent = Normal.Tangent().Normal();

//			Log("(%s) (%s)", Normal.ToString(), Tangent.ToString() );
//			Tangent = cross(cross(Tangent,Line),Normal);
//			Vector3D PosA = Pos - (Radius * Tangent);
			
//			Real Distance = dot( Line, Tangent * Radius );
//			Distance = max( -Radius, Distance );
//			Distance = min( Radius, Distance );

			// 2D Version //
//			Tangent = Normal.ToVector2D().Tangent().ToVector3D();

			// Determine which side of the circle to use //
			Real AdjSide = dot( Line, Tangent ).Normal();
			if ( AdjSide.IsZero() )
				AdjSide = Real::One;

			return Pos + ((Radius*AdjSide) * Tangent);
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
