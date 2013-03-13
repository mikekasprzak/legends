// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ART_H__
#define __PLAYMORE_ART_H__
// - ------------------------------------------------------------------------------------------ - //
enum eArtType {
	AT_NULL = 0,
	
	AT_CIRCLE,
	AT_SPHERE,

	AT_HALFCIRCLE,
	AT_LEFTHALFCIRCLE,
	AT_RIGHTHALFCIRCLE,

	AT_AABB,
	AT_RECT,
	AT_RADIUSRECT,
};
// - ------------------------------------------------------------------------------------------ - //
#include "Art_Sphere.h"		// Storage Type for both Circles and Spheres //
#include "Art_RadiusRect.h"	
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

	// Data Retrieval ------------------------------------------------------------------------- - //
	inline const cArt_Sphere& GetCircle() const {
		return *((cArt_Sphere*)Data);
	}
	inline const cArt_Sphere& GetSphere() const {
		return GetCircle();
	}
	inline const cArt_RadiusRect& GetRadiusRect() const {
		return *((cArt_RadiusRect*)Data);
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
	inline void SetRadiusRect( const Vector3D& Pos, const Vector2D& Radius, const GelColor Color ) {
		((cArt_RadiusRect*)Data)->Pos = Pos;
		((cArt_RadiusRect*)Data)->Radius = Radius;
		((cArt_RadiusRect*)Data)->Color = Color;
	}
	
	// Data Access ---------------------------------------------------------------------------- - //
	inline cArt_Sphere* GetCirclePtr() {
		return (cArt_Sphere*)Data;
	}
	inline cArt_Sphere* GetSpherePtr() {
		return GetCirclePtr();
	}
	inline cArt_RadiusRect* GetRadiusRectPtr() {
		return (cArt_RadiusRect*)Data;
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
	inline static cArt* new_LeftHalfCircle( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_Sphere) ];
		cArt* Art = new(Ptr) cArt( AT_LEFTHALFCIRCLE, sizeof(cArt_Sphere) );
		new(Art->Data) cArt_Sphere( Pos, Radius, Color );
		return Art;
	}
	inline static cArt* new_RightHalfCircle( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_Sphere) ];
		cArt* Art = new(Ptr) cArt( AT_RIGHTHALFCIRCLE, sizeof(cArt_Sphere) );
		new(Art->Data) cArt_Sphere( Pos, Radius, Color );
		return Art;
	}
	inline static cArt* new_RadiusRect( const Vector3D& Pos, const Vector2D& Radius, const GelColor Color ) {
		char* Ptr = new char[ sizeof(cArt) + sizeof(cArt_RadiusRect) ];
		cArt* Art = new(Ptr) cArt( AT_RADIUSRECT, sizeof(cArt_RadiusRect) );
		new(Art->Data) cArt_RadiusRect( Pos, Radius, Color );
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
