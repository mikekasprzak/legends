// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_H__
#define __PLAYMORE_BODY_H__
// - ------------------------------------------------------------------------------------------ - //
enum eBodyType {
	BT_NULL = 0,

	BT_POINT,			// Objects with no physicality, just a position //
	BT_SPHERE,
	BT_AABB,
	
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
		Type( BT_NULL )
	{
	}

	cBody( const eBodyType& BodyType ) :
		Type( BodyType )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline const Matrix4x4& GetTransform() {
		// Until we actually do something //
		return Matrix4x4::Identity;
	} 
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
