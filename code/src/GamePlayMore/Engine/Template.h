// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_TEMPLATE_H__
#define __PLAYMORE_TEMPLATE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>

#include "KeyStore.h"

#include "Body.h"
#include "Art.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Shared.h"
// - ------------------------------------------------------------------------------------------ - //
// Plan, Design, Original, Mold, Prototype, Prefab, Blueprint, Cookie Cutter, Master, Model, Built.
class cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cTemplate thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cKeyStore TVar;				// Key (Variable) Storage //
	cBody* Body;				// Collision //
	cArt* Art;					// Artwork //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cTemplate() :
		Body( 0 ),
		Art( 0 )
	{
	}
	
	virtual ~cTemplate() {
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// TVar, GVar, MVar //


	inline flex& Var( const char* Name ) {
		return Shared.Var( Name );
	}
	inline flex& Var( const std::string& Name ) {
		return Shared.Var( Name );
	}
public: // - Specialization Methods ----------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
	virtual void Create( class cObject* Object ) { }
	virtual void Destroy( class cObject* Object ) { }
	
	virtual void Step( class cObject* Object ) { }
	virtual void Draw( class cObject* Object, const Matrix4x4& Matrix ) { }

	virtual void Contact( class cObject* Object, class cObject* Vs ) { }
	virtual void Sense( class cObject* Object, class cObject* Vs ) { }
	virtual void Notify( class cObject* Object, class cObject* Sender, const int Message ) { }
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_TEMPLATE_H__ //
// - ------------------------------------------------------------------------------------------ - //
