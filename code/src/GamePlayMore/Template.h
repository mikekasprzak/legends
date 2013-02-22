// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_TEMPLATE_H__
#define __PLAYMORE_TEMPLATE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>

#include "Shared.h"
#include "Tag.h"
#include "Body.h"
#include "Art.h"
// - ------------------------------------------------------------------------------------------ - //
class cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cTemplate thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	// Tags //
	cTag* Tag; // TODO: Key/Value Pair //

	// Collision //
	cBody* Body;
	
	// Artwork //
	cArt* Art;

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cTemplate()
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
	virtual void Create( const cShared& Shared, class cObject& Object ) = 0;
	virtual void Destroy( const cShared& Shared, class cObject& Object ) = 0;
	
	virtual void Step( const cShared& Shared, class cObject& Object ) = 0;
	virtual void Draw( const cShared& Shared, class cObject& Object, const Matrix4x4& Matrix ) = 0;

	virtual void Contact( const cShared& Shared, class cObject& Object, class cObject& ObjectVs ) = 0;
	virtual void Sense( const cShared& Shared, class cObject& Object, class cObject& ObjectVs ) = 0;
	virtual void Notify( const cShared& Shared, class cObject& Object, class cObject& ObjectVs, const int Message ) = 0;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_TEMPLATE_H__ //
// - ------------------------------------------------------------------------------------------ - //
