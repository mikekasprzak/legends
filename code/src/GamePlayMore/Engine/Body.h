// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_H__
#define __PLAYMORE_BODY_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
enum eBodyType {		// Types ending in a V are Verlet Physics Versions -- Old, InvMass //
	BT_NULL = 0,

	BT_POINT,			// Objects with no physicality, just a position //

	BT_CIRCLE,			// Z not tested //
	BT_CIRCLEV,
	BT_SPHERE,			// X, Y, and Z tested //
	BT_SPHEREV,

	BT_CAPSULE,			// A Line Segment of 2 points, and a pair of Radius //
	BT_CAPSULEV,
	
//	BT_AABB,
	
	// Use different ID's for non-transforming versions of these types //
	// Station Region. Pivot Region. Transformed Region. Transformed and Pivot not actually different. //
};
// - ------------------------------------------------------------------------------------------ - //
#include "Body_Sphere.h"			// Both Circles and Spheres //
#include "Body_SphereV.h"			// with Verlet Physics //
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
	inline const bool IsCapsule() const {
		return Type == BT_CAPSULE;
	}
	inline const bool IsCapsuleV() const {
		return Type == BT_CAPSULEV;
	}

	// Data Retrieval ------------------------------------------------------------------------- - //
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
//	inline const cBody_Capsule& GetCapsule() const {
//		return *((cBody_Capsule*)Data);
//	}
//	inline const cBody_CapsuleVV& GetCapsuleV() const {
//		return *((cBody_CapsuleV*)Data);
//	}

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

	// Data Access ---------------------------------------------------------------------------- - //
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
	inline static cBody* new_CircleV( const Vector3D& Pos, const Real& Radius, const Vector3D& Velocity, const Real& Mass ) {
		char* Ptr = new char[ sizeof(cBody) + sizeof(cBody_SphereV) ];
		cBody* Body = new(Ptr) cBody( BT_CIRCLEV, sizeof(cBody_SphereV) );
		new(Body->Data) cBody_SphereV( Pos, Radius, Velocity, Mass );
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

	void Draw( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
