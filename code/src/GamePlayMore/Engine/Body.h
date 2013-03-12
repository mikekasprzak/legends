// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_H__
#define __PLAYMORE_BODY_H__
// - ------------------------------------------------------------------------------------------ - //
enum eBodyType {
	BT_NULL = 0,

	BT_POINT,			// Objects with no physicality, just a position //
	BT_CIRCLE,
	BT_SPHERE,

//	BT_AABB,
	
	// Use different ID's for non-transforming versions of these types //
	// Station Region. Pivot Region. Transformed Region. Transformed and Pivot not actually different. //
};
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
	inline const bool IsSphere() const {
		return Type == BT_SPHERE;
	}

	// Data Retrieval ------------------------------------------------------------------------- - //
	inline const Vector3D& GetPoint() const {
		return *((Vector3D*)Data);
	}
//	inline const cArt_Sphere& GetCircle() const {
//		return *((cArt_Sphere*)Data);
//	}
//	inline const cArt_Sphere& GetSphere() const {
//		return GetCircle();
//	}

	// Data Changing -------------------------------------------------------------------------- - //
	inline void SetPoint( const Vector3D& Pos ) {
		*((Vector3D*)Data) = Pos;
	}
//	inline void SetCircle( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
//		((cArt_Sphere*)Data)->Pos = Pos;
//		((cArt_Sphere*)Data)->Radius = Radius;
//		((cArt_Sphere*)Data)->Color = Color;
//	}
//	inline void SetSphere( const Vector3D& Pos, const Real Radius, const GelColor Color ) {
//		SetCircle( Pos, Radius, Color );
//	}

	// Data Access ---------------------------------------------------------------------------- - //
	inline Vector3D* GetPointPtr() {
		return (Vector3D*)Data;
	}
//	inline cArt_Sphere* GetCirclePtr() {
//		return (cArt_Sphere*)Data;
//	}
//	inline cArt_Sphere* GetSpherePtr() {
//		return GetCirclePtr();
//	}

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

	// Destroy -------------------------------------------------------------------------------- - //
	inline static void delete_Body( cBody* Body ) {
		Body->~cBody();
		delete [] Body;
	}

public:
	inline const Matrix4x4 GetTransform() {
		if ( BT_POINT ) {
			return Matrix4x4::TranslationMatrix( GetPoint() );
		}
		else {
			return Matrix4x4::Identity;
		}
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
