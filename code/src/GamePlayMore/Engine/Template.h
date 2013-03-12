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
	// Shorthands for the Shared Variable Functions //
	inline flex& Var( const char* Name );			// Search All KeyStores (Except Template) //
	inline flex& Var( const std::string& Name );

	//inline flex& TVar( const char* Name );		// The Internal KeyStore //
	//inline flex& TVar( const std::string& Name );
	inline flex& OVar( const char* Name );			// The Object's KeyStore //
	inline flex& OVar( const std::string& Name );
	inline flex& SVar( const char* Name );			// The Scene's Keystore //
	inline flex& SVar( const std::string& Name );
	inline flex& PVar( const char* Name );			// The Project's Keystore //
	inline flex& PVar( const std::string& Name );
		
	void StepChildren( class cObject* Object );
	void DrawChildren( class cObject* Object, const Matrix4x4& Matrix );
public: // - Specialization Methods ----------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
	virtual void Create( class cObject* Object );	// On Object Creation, call the Templates Create method //
	virtual void Destroy( class cObject* Object );	// On Object Destruction, call the Template Destroy method //
	
	virtual void Step( class cObject* Object );
	virtual void Draw( class cObject* Object, const Matrix4x4& Matrix );

	virtual void Contact( class cObject* Object, class cObject* Vs );
	virtual void Sense( class cObject* Object, class cObject* Vs );
	virtual void Notify( class cObject* Object, class cObject* Sender, const int Message );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_TEMPLATE_H__ //
// - ------------------------------------------------------------------------------------------ - //
