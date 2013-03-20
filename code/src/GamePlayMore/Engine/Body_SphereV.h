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
	Real		InvMass;		// Inverse Mass (i.e. 1.0/Mass). This makes InvMass of 0 == infinity. //
	Real		Friction;
	Real		Restitution;	// Elasticity. 1 is perfectly elastic physics (pool ball). 0 is inelastic. //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody_SphereV() {
	}

	// Mass of 0 is considered Infinity (Even though according to usage here it's massless) //
	cBody_SphereV( const Vector3D& _Pos, const Real& _Radius, const Vector3D& Velocity = Vector3D::Zero, const Real& Mass = Real::One, const Real& _Friction = Real::One, const Real& _Restitution = Real::One ) :
		Radius( _Radius ),
		Pos( _Pos ),
		Old( _Pos - Velocity ),
		InvMass( (Mass != Real::Zero) ? Real::One / Mass : Real::Zero ),
		Friction( _Friction ),
		Restitution( _Restitution )		
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
	inline const Real GetMass() const {
		if ( InvMass == Real::Zero ) {
			return Real::Zero;
		}
		else {
			return Real::One / InvMass;
		}
	}
	inline const Real& GetFriction() const {
		return Friction;
	}
	inline const Real& GetRestitution() const {
		return Restitution;
	}
	inline const Real& GetInvMass() const {
		return InvMass;
	}

	
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
	// NOTE: Friction of 0 is considered frictionless (Ice) //
	inline void SetFriction( const Real& _Friction ) {
		Friction = _Friction;
	}
	inline void SetRestitution( const Real& _Restitution ) {
		Restitution = _Restitution;
	}
public:
	virtual void Step() {
		Vector3D Velocity = GetVelocity();
		Old = Pos;
		Pos += Velocity * 0.995f; // Was (Accum+Velocity) //
		// (Accum * TimeStep * TimeStep), but TimeStep is 1, so it cancels out. //
		
		// TODO: Do Friction by adding forces to the Accumulator. //
		//       Note that friction should not reverse our direction (At least ideally not). //
		//       Therefor, seperating the friction step may be ideal. //
		
		// TODO: Need some way to control friction of contacting objects. May need to store it //
		//       inside an Object property, because otherwise I need to add a surface friction //
		//       property to every body (even if it's a non V). Or add it directly to the Object, //
		//       keeping bodies simple. No no! To the Template! Ha ha! However that may not be good //
		//       for when it comes to things that can adjust their friction. Practical example is a //
		//       platformer map that may have different friction values associated with tiles. In //
		//       this case, a function will need to somehow know the blocks touching, and respond //
		//       with a different friction value. GetFriction should probably be a function. //
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_SPHEREV_H__ //
// - ------------------------------------------------------------------------------------------ - //
