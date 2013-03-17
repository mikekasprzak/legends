// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ART_H__
#define __PLAYMORE_ART_H__
// - ------------------------------------------------------------------------------------------ - //
enum eArtType {
	AT_NULL = 0,
	
	AT_CIRCLE,
	AT_SPHERE,

	AT_HALFCIRCLE,
	AT_HALFSPHERE,
	
	AT_CAPSULE,

	AT_AABB,	// ?? //
	AT_RECT,
	AT_RADIUSRECT,
};
// - ------------------------------------------------------------------------------------------ - //
#include "Art_Sphere.h"			// Both Circles and Spheres //
#include "Art_HalfSphere.h"		// Spheres with a dividing plane (normal) //
#include "Art_RadiusRect.h"		// Rectangles with a center and "radius" about each axis //
#include "Art_Capsule.h"		// A line segment of Two points and Two Radius //
// - ------------------------------------------------------------------------------------------ - //
class cArt {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cArt thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	eArtType 	Type;				// 32bit //
	st32		Size;				// 32bit -- Size in Bytes //
	
	char 		Data[0];			// TBD   -- The Data //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cArt() :
		Type( AT_NULL ),
		Size( 0 )
	{
	}

	cArt( const eArtType& _Type, const st32 _Size ) :
		Type( _Type ),
		Size( _Size )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Type Checking -------------------------------------------------------------------------- - //
	inline const bool IsNull() const {
		return Type == AT_NULL;
	}
	inline const bool IsCircle() const {
		return Type == AT_CIRCLE;
	}
	inline const bool IsSphere() const {
		return Type == AT_SPHERE;
	}
	inline const bool IsHalfCircle() const {
		return Type == AT_HALFCIRCLE;
	}
	inline const bool IsAABB() const {
		return Type == AT_AABB;
	}
	inline const bool IsRect() const {
		return Type == AT_RECT;
	}
	inline const bool IsRadiusRect() const {
		return Type == AT_RADIUSRECT;
	}
	inline const bool IsCapsule() const {
		return Type == AT_CAPSULE;
	}

	// Data Retrieval ------------------------------------------------------------------------- - //
	inline const cArt_Sphere& GetCircle() const {
		return *((cArt_Sphere*)Data);
	}
	inline const cArt_Sphere& GetSphere() const {
		return GetCircle();
	}
	inline const cArt_HalfSphere& GetHalfCircle() const {
		return *((cArt_HalfSphere*)Data);
	}
	inline const cArt_HalfSphere& GetHalfSphere() const {
		return GetHalfCircle();
	}
	inline const cArt_RadiusRect& GetRadiusRect() const {
		return *((cArt_RadiusRect*)Data);
	}
	inline const cArt_Capsule& GetCapsule() const {
		return *((cArt_Capsule*)Data);
	}

	// Data Changing -------------------------------------------------------------------------- - //
	inline void SetCircle( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
		((cArt_Sphere*)Data)->Pos = Pos;
		((cArt_Sphere*)Data)->Radius = Radius;
		((cArt_Sphere*)Data)->Color = Color;
	}
	inline void SetSphere( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
		SetCircle( Pos, Radius, Color );
	}
	inline void SetHalfCircle( const Vector3D& Pos, const Real Radius, const Vector3D& Normal, const GelColor Color ) {
		((cArt_HalfSphere*)Data)->Pos = Pos;
		((cArt_HalfSphere*)Data)->Radius = Radius;
		((cArt_HalfSphere*)Data)->Normal = Normal;		
		((cArt_HalfSphere*)Data)->Color = Color;
	}
	inline void SetHalfSphere( const Vector3D& Pos, const Real Radius, const Vector3D& Normal, const GelColor Color ) {
		SetHalfCircle( Pos, Radius, Normal, Color );
	}
	inline void SetRadiusRect( const Vector3D& Pos, const Vector2D& Radius, const GelColor Color ) {
		((cArt_RadiusRect*)Data)->Pos = Pos;
		((cArt_RadiusRect*)Data)->Radius = Radius;
		((cArt_RadiusRect*)Data)->Color = Color;
	}
	inline void SetCapsuleRect( const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const GelColor Color ) {
		((cArt_Capsule*)Data)->PosA = PosA;
		((cArt_Capsule*)Data)->RadiusA = RadiusA;
		((cArt_Capsule*)Data)->PosB = PosB;
		((cArt_Capsule*)Data)->RadiusB = RadiusB;
		((cArt_Capsule*)Data)->Color = Color;
	}
	
	// Data Access ---------------------------------------------------------------------------- - //
	inline cArt_Sphere* GetCirclePtr() {
		return (cArt_Sphere*)Data;
	}
	inline cArt_Sphere* GetSpherePtr() {
		return GetCirclePtr();
	}
	
	inline cArt_HalfSphere* GetHalfCirclePtr() {
		return (cArt_HalfSphere*)Data;
	}
	inline cArt_HalfSphere* GetHalfSpherePtr() {
		return GetHalfCirclePtr();
	}
	
	inline cArt_RadiusRect* GetRadiusRectPtr() {
		return (cArt_RadiusRect*)Data;
	}
	
	inline cArt_Capsule* GetCapsulePtr() {
		return (cArt_Capsule*)Data;
	}

	// Create --------------------------------------------------------------------------------- - //
	inline static cArt* new_Null() {
		char* Ptr = new char[ sizeof(cArt) ];
		cArt* Art = new(Ptr) cArt( AT_NULL, 0 );
		return Art;
	}
	inline static cArt* new_Circle( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_Sphere) ];
		cArt* Art = new(Ptr) cArt( AT_CIRCLE, sizeof(cArt_Sphere) );
		new(Art->Data) cArt_Sphere( Pos, Radius, Color );
		return Art;
	}
	inline static cArt* new_Sphere( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_Sphere) ];
		cArt* Art = new(Ptr) cArt( AT_SPHERE, sizeof(cArt_Sphere) );
		new(Art->Data) cArt_Sphere( Pos, Radius, Color );
		return Art;
	}
	inline static cArt* new_HalfCircle( const Vector3D& Pos, const Real Radius, const Vector3D& Normal, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_HalfSphere) ];
		cArt* Art = new(Ptr) cArt( AT_HALFCIRCLE, sizeof(cArt_HalfSphere) );
		new(Art->Data) cArt_HalfSphere( Pos, Radius, Normal, Color );
		return Art;
	}
	inline static cArt* new_HalfSphere( const Vector3D& Pos, const Real Radius, const Vector3D& Normal, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_HalfSphere) ];
		cArt* Art = new(Ptr) cArt( AT_HALFSPHERE, sizeof(cArt_HalfSphere) );
		new(Art->Data) cArt_HalfSphere( Pos, Radius, Normal, Color );
		return Art;
	}
	inline static cArt* new_RadiusRect( const Vector3D& Pos, const Vector2D& Radius, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_RadiusRect) ];
		cArt* Art = new(Ptr) cArt( AT_RADIUSRECT, sizeof(cArt_RadiusRect) );
		new(Art->Data) cArt_RadiusRect( Pos, Radius, Color );
		return Art;
	}
	inline static cArt* new_Capsule( const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_Capsule) ];
		cArt* Art = new(Ptr) cArt( AT_CAPSULE, sizeof(cArt_Capsule) );
		new(Art->Data) cArt_Capsule( PosA, RadiusA, PosB, RadiusB, Color );
		return Art;
	}
	
	// Destroy -------------------------------------------------------------------------------- - //
	inline static void delete_Art( cArt* Art ) {
		Art->~cArt();
		delete [] Art;
	}

public:
	void Draw( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ART_H__ //
// - ------------------------------------------------------------------------------------------ - //
