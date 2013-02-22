// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_BODY_H__
#define __PLAYMORE_BODY_H__
// - ------------------------------------------------------------------------------------------ - //
class cBody {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cBody thistype;
	inline void* GetThis() { return this; }
public: // - Enumerations --------------------------------------------------------------------- - //
	enum eBodyType {
		BT_NULL = 0,
		BT_POINT = 1,	// Objects with no physicality, just a position //
		BT_SPHERE = 2,
		BT_AABB = 3,
		
		// Use different ID's for non-transforming versions of these types //
		// Station Region. Pivot Region. Transformed Region. Transformed and Pivot not actually different. //
	};
public: // - Members -------------------------------------------------------------------------- - //
	eBodyType Type;
	// ... //
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
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_BODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
