// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_TEMPLATE_H__
#define __PLAYMORE_TEMPLATE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include <Math/Matrix.h>

#include "Flex.h"
#include "KeyStore.h"

#include "Body.h"
#include "Art.h"

#include "Shared.h"
// - ------------------------------------------------------------------------------------------ - //
class cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cTemplate thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	// Tags //
	//std::map<std::string,flex> MyVar; // TODO: Key/Value Pair //
	cKeyStore TVar;

	// Collision //
	cBody* Body;
	
	// Artwork //
	cArt* Art;

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cTemplate()
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// TVar, GVar, MVar //
	
//	inline flex& TVar( const char* Name ) {
//		auto Itr = MyVar.find( Name );
//		if ( Itr != MyVar.end() ) {
//			return Itr->second;
//		}
//		else {
//			Log( "! ERROR: Invalid TVar \"%s\"", Name );
//			static flex Dummy;
//			return Dummy;
//		}
//	}
//	inline flex& TVar( const std::string Name ) {
//		return TVar( Name.c_str() );
//	}

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
