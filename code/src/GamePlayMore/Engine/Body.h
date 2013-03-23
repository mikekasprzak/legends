// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_H__
#define __PLAYMORE_BODY_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
enum eBodyType {			// Types ending in a V are Verlet Physics Versions -- Old, InvMass //
	BT_NULL = 0,

	BT_POINT,				// Objects with no physicality, just a position //

	BT_CIRCLE,				// Z not tested //
	BT_CIRCLEV,
	BT_SPHERE,				// X, Y, and Z tested //
	BT_SPHEREV,

	BT_HALFCIRCLE,			// Z not tested //
//	BT_HALFCIRCLEV,
	BT_HALFSPHERE,			// X, Y, and Z tested //
//	BT_HALFSPHEREV,

	BT_CAPSULE,				// A Line Segment of 2 points, and a pair of Radius //
	BT_CAPSULEV,
	BT_CAPSULEVT,			// Transforming (i.e. it rotates and keeps shape) //
	BT_INVCAPSULE,			// Inverse, in that it keeps things inside //
	
//	BT_AABB,
	
	// Use different ID's for non-transforming versions of these types //
	// Station Region. Pivot Region. Transformed Region. Transformed and Pivot not actually different. //
};
// - ------------------------------------------------------------------------------------------ - //
#include "Body_Sphere.h"			// Both Circles and Spheres //
#include "Body_SphereV.h"			// with Verlet Physics //
#include "Body_HalfSphere.h"			
#include "Body_HalfSphereV.h"			
#include "Body_Capsule.h"
#include "Body_CapsuleV.h"			
#include "Body_CapsuleVT.h"			
// - ------------------------------------------------------------------------------------------ - //
class cBody {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	eBodyType 	Type;				// 32bit //
	st32		Size;				// 32bit -- Size in Bytes //
	
	char 		Data[0];			// TBD   -- The Data //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cBody() :
		Type( BT_NULL ),
		Size( 0 )
	{
	}

	cBody( const eBodyType& _Type, const st32 _Size ) :
		Type( _Type ),
		Size( _Size )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Type Checking -------------------------------------------------------------------------- - //
	inline const bool IsNull() const {
		return Type == BT_NULL;
	}

	inline const bool IsPoint() const {
		return Type == BT_POINT;
	}

	inline const bool IsCircle() const {
		return Type == BT_CIRCLE;
	}
	inline const bool IsCircleV() const {
		return Type == BT_CIRCLEV;
	}
	inline const bool IsSphere() const {
		return Type == BT_SPHERE;
	}
	inline const bool IsSphereV() const {
		return Type == BT_SPHEREV;
	}

	inline const bool IsHalfCircle() const {
		return Type == BT_HALFCIRCLE;
	}
//	inline const bool IsHalfCircleV() const {
//		return Type == BT_HALFCIRCLEV;
//	}
	inline const bool IsHalfSphere() const {
		return Type == BT_HALFSPHERE;
	}
//	inline const bool IsHalfSphereV() const {
//		return Type == BT_HALFSPHEREV;
//	}

	inline const bool IsCapsule() const {
		return Type == BT_CAPSULE;
	}
	inline const bool IsCapsuleV() const {
		return Type == BT_CAPSULEV;
	}
	inline const bool IsCapsuleVT() const {
		return Type == BT_CAPSULEVT;
	}
	inline const bool IsInvCapsule() const {
		return Type == BT_INVCAPSULE;
	}

	// Data Retrieval ------------------------------------------------------------------------- - //
	inline const cBody_Base& GetBase() const {
		return *((cBody_Base*)Data);
	}
	
	// NOTE: Point is a specific Body type. This is not used to get the center. //
	inline const Vector3D& GetPoint() const {
		return *((Vector3D*)Data);
	}

	inline const cBody_Sphere& GetCircle() const {
		return *((cBody_Sphere*)Data);
	}
	inline const cBody_SphereV& GetCircleV() const {
		return *((cBody_SphereV*)Data);
	}
	inline const cBody_Sphere& GetSphere() const {
		return GetCircle();
	}
	inline const cBody_SphereV& GetSphereV() const {
		return GetCircleV();
	}

	inline const cBody_HalfSphere& GetHalfCircle() const {
		return *((cBody_HalfSphere*)Data);
	}
	inline const cBody_HalfSphereV& GetHalfCircleV() const {
		return *((cBody_HalfSphereV*)Data);
	}
	inline const cBody_HalfSphere& GetHalfSphere() const {
		return GetHalfCircle();
	}
	inline const cBody_HalfSphereV& GetHalfSphereV() const {
		return GetHalfCircleV();
	}

	inline const cBody_Capsule& GetCapsule() const {
		return *((cBody_Capsule*)Data);
	}
	inline const cBody_CapsuleV& GetCapsuleV() const {
		return *((cBody_CapsuleV*)Data);
	}
	inline const cBody_CapsuleVT& GetCapsuleVT() const {
		return *((cBody_CapsuleVT*)Data);
	}

	// Data Changing -------------------------------------------------------------------------- - //
	inline void SetPoint( const Vector3D& Pos ) {
		*((Vector3D*)Data) = Pos;
	}
	
	inline void SetCircle( const Vector3D& Pos, const Real& Radius ) {
		((cBody_Sphere*)Data)->Pos = Pos;
		((cBody_Sphere*)Data)->Radius = Radius;
	}
	inline void SetSphere( const Vector3D& Pos, const Real& Radius ) {
		SetCircle( Pos, Radius );
	}
	inline void SetCircleV( const Vector3D& Pos, const Real& Radius, const Vector3D& Velocity, const Real& Mass ) {
		((cBody_SphereV*)Data)->Pos = Pos;
		((cBody_SphereV*)Data)->Radius = Radius;
		((cBody_SphereV*)Data)->SetVelocity( Velocity );
		((cBody_SphereV*)Data)->SetMass( Mass );
	}
	inline void SetSphereV( const Vector3D& Pos, const Real& Radius, const Vector3D& Velocity, const Real& Mass ) {
		SetCircleV( Pos, Radius, Velocity, Mass );
	}

	inline void SetHalfCircle( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal ) {
		((cBody_HalfSphere*)Data)->Pos = Pos;
		((cBody_HalfSphere*)Data)->Radius = Radius;
		((cBody_HalfSphere*)Data)->Normal = Normal;
	}
	inline void SetHalfSphere( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal ) {
		SetHalfCircle( Pos, Radius, Normal );
	}
//	inline void SetHalfCircleV( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal, const Vector3D& Velocity, const Real& Mass ) {
//		((cBody_HalfSphere*)Data)->Pos = Pos;
//		((cBody_HalfSphere*)Data)->Radius = Radius;
//		((cBody_HalfSphere*)Data)->Normal = Normal;
//		((cBody_HalfSphereV*)Data)->SetVelocity( Velocity );
//		((cBody_HalfSphereV*)Data)->SetMass( Mass );
//	}
//	inline void SetHalfSphereV( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal, const Vector3D& Velocity, const Real& Mass ) {
//		SetHalfCircleV( Pos, Radius, Normal, Velocity, Mass );
//	}

	inline void SetCapsule( const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB ) {
		((cBody_Capsule*)Data)->PosA = PosA;
		((cBody_Capsule*)Data)->RadiusA = RadiusA;
		((cBody_Capsule*)Data)->PosB = PosB;
		((cBody_Capsule*)Data)->RadiusB = RadiusB;
	}
//	inline void SetCapsuleV( const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const Vector3D& VelocityA, const Vector3D& VelocityB, const Real& MassA, const Real& MassB ) {
//		((cBody_CapsuleV*)Data)->PosA = PosA;
//		((cBody_CapsuleV*)Data)->RadiusA = RadiusA;
//		((cBody_CapsuleV*)Data)->SetVelocityA( VelocityA );
//		((cBody_CapsuleV*)Data)->PosB = PosB;
//		((cBody_CapsuleV*)Data)->RadiusB = RadiusB;
//		((cBody_CapsuleV*)Data)->SetVelocityB( VelocityB );
//		((cBody_CapsuleV*)Data)->SetMass( Mass );
//	}
//	inline void SetCapsuleVT( const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const Vector3D& VelocityA, const Vector3D& VelocityB, const Real& MassA, const Real& MassB ) {
//		((cBody_CapsuleVT*)Data)->PosA = PosA;
//		((cBody_CapsuleVT*)Data)->RadiusA = RadiusA;
//		((cBody_CapsuleVT*)Data)->SetVelocityA( VelocityA );
//		((cBody_CapsuleVT*)Data)->SetMassA( MassA );
//		((cBody_CapsuleVT*)Data)->PosB = PosB;
//		((cBody_CapsuleVT*)Data)->RadiusB = RadiusB;
//		((cBody_CapsuleVT*)Data)->SetVelocityB( VelocityB );
//		((cBody_CapsuleVT*)Data)->SetMassB( MassB );
//		((cBody_CapsuleVT*)Data)->CalcLength();
//	}


	// Data Access ---------------------------------------------------------------------------- - //
	inline cBody_Base* GetBasePtr() {
		return (cBody_Base*)Data;
	}

	inline Vector3D* GetPointPtr() {
		return (Vector3D*)Data;
	}
	
	inline cBody_Sphere* GetCirclePtr() {
		return (cBody_Sphere*)Data;
	}
	inline cBody_SphereV* GetCircleVPtr() {
		return (cBody_SphereV*)Data;
	}
	inline cBody_Sphere* GetSpherePtr() {
		return GetCirclePtr();
	}
	inline cBody_SphereV* GetSphereVPtr() {
		return GetCircleVPtr();
	}
	
	inline cBody_HalfSphere* GetHalfCirclePtr() {
		return (cBody_HalfSphere*)Data;
	}
	inline cBody_HalfSphereV* GetHalfCircleVPtr() {
		return (cBody_HalfSphereV*)Data;
	}
	inline cBody_HalfSphere* GetHalfSpherePtr() {
		return GetHalfCirclePtr();
	}
	inline cBody_HalfSphereV* GetHalfSphereVPtr() {
		return GetHalfCircleVPtr();
	}

	inline cBody_Capsule* GetCapsulePtr() {
		return (cBody_Capsule*)Data;
	}
	inline cBody_Capsule* GetInvCapsulePtr() {
		return (cBody_Capsule*)Data;
	}
	inline cBody_CapsuleV* GetCapsuleVPtr() {
		return (cBody_CapsuleV*)Data;
	}
	inline cBody_CapsuleVT* GetCapsuleVTPtr() {
		return (cBody_CapsuleVT*)Data;
	}

	// Create --------------------------------------------------------------------------------- - //
	inline static cBody* new_Null() {
		char* Ptr = new char[ sizeof(cBody) ];
		cBody* Body = new(Ptr) cBody( BT_NULL, 0 );
		return Body;
	}

	inline static cBody* new_Point( const Vector3D& Pos ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(Vector3D) ];
		cBody* Body = new(Ptr) cBody( BT_POINT, sizeof(Vector3D) );
		new(Body->Data) Vector3D( Pos );
		return Body;
	}

	inline static cBody* new_Circle( const Vector3D& Pos, const Real& Radius ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_Sphere) ];
		cBody* Body = new(Ptr) cBody( BT_CIRCLE, sizeof(cBody_Sphere) );
		new(Body->Data) cBody_Sphere( Pos, Radius );
		return Body;
	}
	inline static cBody* new_CircleV( const Vector3D& Pos, const Real& Radius, const Vector3D& Velocity = Vector3D::Zero, const Real& Mass = Real::One, const Real& Restitution = Real::One ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_SphereV) ];
		cBody* Body = new(Ptr) cBody( BT_CIRCLEV, sizeof(cBody_SphereV) );
		new(Body->Data) cBody_SphereV( Pos, Radius, Velocity, Mass, Restitution );
		return Body;
	}
	inline static cBody* new_Sphere( const Vector3D& Pos, const Real& Radius ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_Sphere) ];
		cBody* Body = new(Ptr) cBody( BT_SPHERE, sizeof(cBody_Sphere) );
		new(Body->Data) cBody_Sphere( Pos, Radius );
		return Body;
	}
	inline static cBody* new_SphereV( const Vector3D& Pos, const Real& Radius, const Vector3D& Velocity = Vector3D::Zero, const Real& Mass = Real::One, const Real& Restitution = Real::One ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_SphereV) ];
		cBody* Body = new(Ptr) cBody( BT_SPHEREV, sizeof(cBody_SphereV) );
		new(Body->Data) cBody_SphereV( Pos, Radius, Velocity, Mass, Restitution );
		return Body;
	}

	inline static cBody* new_HalfCircle( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_HalfSphere) ];
		cBody* Body = new(Ptr) cBody( BT_HALFCIRCLE, sizeof(cBody_HalfSphere) );
		new(Body->Data) cBody_HalfSphere( Pos, Radius, Normal );
		return Body;
	}
//	inline static cBody* new_HalfCircleV( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal, const Vector3D& Velocity, const Real& Mass ) {
//		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_HalfSphereV) ];
//		cBody* Body = new(Ptr) cBody( BT_HALFCIRCLEV, sizeof(cBody_HalfSphereV) );
//		new(Body->Data) cBody_HalfSphereV( Pos, Radius, Normal, Velocity, Mass );
//		return Body;
//	}
	inline static cBody* new_HalfSphere( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_HalfSphere) ];
		cBody* Body = new(Ptr) cBody( BT_HALFSPHERE, sizeof(cBody_HalfSphere) );
		new(Body->Data) cBody_HalfSphere( Pos, Radius, Normal );
		return Body;
	}
//	inline static cBody* new_HalfSphereV( const Vector3D& Pos, const Real& Radius, const Vector3D& Normal, const Vector3D& Velocity, const Real& Mass ) {
//		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_HalfSphereV) ];
//		cBody* Body = new(Ptr) cBody( BT_HALFSPHEREV, sizeof(cBody_HalfSphereV) );
//		new(Body->Data) cBody_HalfSphereV( Pos, Radius, Normal, Velocity, Mass );
//		return Body;
//	}
	
	inline static cBody* new_Capsule( const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_Capsule) ];
		cBody* Body = new(Ptr) cBody( BT_CAPSULE, sizeof(cBody_Capsule) );
		new(Body->Data) cBody_Capsule( PosA, RadiusA, PosB, RadiusB );
		return Body;
	}
	inline static cBody* new_InvCapsule( const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_Capsule) ];
		cBody* Body = new(Ptr) cBody( BT_INVCAPSULE, sizeof(cBody_Capsule) );
		new(Body->Data) cBody_Capsule( PosA, RadiusA, PosB, RadiusB );
		return Body;
	}

	// Destroy -------------------------------------------------------------------------------- - //
	inline static void delete_Body( cBody* Body ) {
		Body->~cBody();
		delete [] Body;
	}

public:
	const Matrix4x4 GetTransform();	
	const Rect3D GetRect();
	
	const bool Check( const cBody& Vs ) const;
	void Solve( cBody* Vs );

	void Step();
	void Draw( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
