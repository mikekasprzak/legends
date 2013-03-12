// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_ART_H__
#define __PLAYMORE_ART_H__
// - ------------------------------------------------------------------------------------------ - //
enum eArtType {
	AT_NULL = 0,
	
	AT_CIRCLE,
	AT_SPHERE,
	
//	AT_AABB,
};
// - ------------------------------------------------------------------------------------------ - //
#include "Art_Sphere.h"		// Storage Type for both Circles and Spheres //
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

	// Data Retrieval ------------------------------------------------------------------------- - //
	inline const cArt_Sphere& GetCircle() const {
		return *((cArt_Sphere*)Data);
	}
	inline const cArt_Sphere& GetSphere() const {
		return GetCircle();
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
	
	// Data Access ---------------------------------------------------------------------------- - //
	inline cArt_Sphere* GetCirclePtr() {
		return (cArt_Sphere*)Data;
	}
	inline cArt_Sphere* GetSpherePtr() {
		return GetCirclePtr();
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
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_ART_H__ //
// - ------------------------------------------------------------------------------------------ - //
