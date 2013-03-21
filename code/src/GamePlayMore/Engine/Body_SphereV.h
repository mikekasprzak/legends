// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_SPHEREV_H__
#define __PLAYMORE_BODY_SPHEREV_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Real.h>
#include "Body_Base.h"
// - ------------------------------------------------------------------------------------------ - //
class cBody_SphereV: public cBody_Base {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody_SphereV thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	Real 		Radius;
	Vector3D 	Pos;			// Position Last, so it can be followed by Verlet Members //

	// Verlet Members //
	Vector3D 	Old;			// Old Position (Verlet) //
	Real		Mass;
	Real		Friction;
	Real		Restitution;	// Elasticity. 1 is perfectly elastic physics (pool ball). 0 is inelastic (pushing). //
	Vector3D	Accum;			// Accumulator (Impulse Forces) //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_SphereV() {
	}

	cBody_SphereV( const Vector3D& _Pos, const Real& _Radius, const Vector3D& Velocity = Vector3D::Zero, const Real& _Mass = Real::One, const Real& _Friction = Real::One, const Real& _Restitution = Real::One ) :
		Radius( _Radius ),
		Pos( _Pos ),
		Old( _Pos - Velocity ),
		Mass( _Mass ),
		Friction( _Friction ),
		Restitution( _Restitution ),
		Accum( Vector3D::Zero )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline const Vector3D GetVelocity() const {
		return Pos - Old; // Old -> Pos, Start -> Dest, A -> B, Dest (B) always goes first //
	}
	inline const Vector3D& GetPos() const {
		return Pos;
	}
	inline const Vector3D& GetOld() const {
		return Old;
	}
	inline const Real& GetMass() const {
		return Mass;
	}
	inline const Real& GetFriction() const {
		return Friction;
	}
	inline const Real& GetRestitution() const {
		return Restitution;
	}

	
	// NOTE: This explicitly sets the velocity property. It does not accumulate. //
	inline void SetVelocity( const Vector3D& _Velocity ) {
		Old = Pos - _Velocity;
	}
	inline void SetMass( const Real& _Mass ) {
		Mass = _Mass;
	}
	// NOTE: Friction of 0 is considered frictionless (Ice) //
	inline void SetFriction( const Real& _Friction ) {
		Friction = _Friction;
	}
	inline void SetRestitution( const Real& _Restitution ) {
		Restitution = _Restitution;
	}
	
	// Impulse Forces //
	inline void AddForce( const Vector3D& Force ) {
		Accum += Force;
	}
public:
	virtual void Step() {
		Vector3D Velocity = GetVelocity();
		Old = Pos;
		// Accum is (Accum * TimeStep * TimeStep), but TimeStep is 1 so it cancels out. //
		Pos += (Velocity + Accum);	// * 0.995f;
		
		// We use a seperate Accumulator so to not pollute the Velocity with impulse forces (??) //
		Accum = Vector3D::Zero; 	// Clear the Accumulator //
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void Solve( cBody_SphereV* A, cBody_SphereV* B ) {
	Vector3D Line = B->Pos - A->Pos;
	Real Length = Line.NormalizeRet();
	
	Real RadiusSum = A->Radius + B->Radius;
							
	Real Diff = RadiusSum - Length;			

	// TODO: Fix this code so that Penetrations after a collision work correctly. //
	//       If I don't do this, then objects solved without enough relaxation steps //
	//       will exhibit the bug I'm trying to avoid by doing this test. //
	if ( Diff > Real(0.1f) ) {
		// Take Velocities before we move Pos so we don't accidentially accumulate more force //
		Vector3D VelocityA = A->GetVelocity();
		Vector3D VelocityB = B->GetVelocity();
		
		// 50% solving, which is less error prone than using the mass here (use it later instead) //
		Diff *= Real::Half;
		A->Pos -= Line * Diff;
		B->Pos += Line * Diff;

		Real ContactA = dot(VelocityA,Line);
		Real ContactB = dot(VelocityB,-Line);

//		Log( "%f, %f, %f vs %f, %f, %f -- %f %f (%f) [%.2f %.2f]", 
//			VelocityA.x.ToFloat(), VelocityA.y.ToFloat(), VelocityA.z.ToFloat(), 
//			VelocityB.x.ToFloat(), VelocityB.y.ToFloat(), VelocityB.z.ToFloat(), 
//			Length.ToFloat(), RadiusSum.ToFloat(), (RadiusSum-Length).ToFloat(),
//			ContactA.ToFloat(), ContactB.ToFloat() );

		Vector3D ImpactA = Line * ContactA;
		Vector3D ImpactB = -Line * ContactB;
		
		// When Velocity and Line are Parallel, the cross is 0 so Tangents cancel out // 
		Vector3D TangentA = cross(cross(VelocityA,Line),Line).Normal();
		Vector3D TangentB = cross(cross(VelocityB,-Line),-Line).Normal();
						
		Real MassSum = (A->Mass+B->Mass);

		Vector3D MomentumA = (A->Mass*ImpactA);
		Vector3D MomentumB = (B->Mass*ImpactB);
		Vector3D Momentum = MomentumA + MomentumB;

		Real Restitution = Real::Max( A->Restitution, B->Restitution );
		Real Friction = Real::Sqrt( A->Friction * B->Friction );
		
		Vector3D ContactVelocityA = ((Restitution*B->Mass*(ImpactB-ImpactA)+Momentum)/MassSum) * Friction;
		Vector3D ContactVelocityB = ((Restitution*A->Mass*(ImpactA-ImpactB)+Momentum)/MassSum) * Friction;

		Vector3D TangentVelocityA = TangentA * dot(VelocityA,TangentA);
		Vector3D TangentVelocityB = TangentB * dot(VelocityB,TangentB);

		A->Old = A->Pos - (TangentVelocityA+ContactVelocityA);
		B->Old = B->Pos - (TangentVelocityB+ContactVelocityB);

//		Log( "%f, %f, %f !! %f, %f, %f", 
//			A->GetVelocity().x.ToFloat(), A->GetVelocity().y.ToFloat(), A->GetVelocity().z.ToFloat(),
//			B->GetVelocity().x.ToFloat(), B->GetVelocity().y.ToFloat(), B->GetVelocity().z.ToFloat() );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_SPHEREV_H__ //
// - ------------------------------------------------------------------------------------------ - //
