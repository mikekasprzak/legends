// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_SHARED_H__
#define __PLAYMORE_SHARED_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Flex.h"
// - ------------------------------------------------------------------------------------------ - //
// Shared is an entity that shares 
// - ------------------------------------------------------------------------------------------ - //
class cShared {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cShared thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	class cProject* 	Project;
	class cScene* 		Scene;
	class cObject*		Object;
	class cTemplate*	Template;

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cShared() :
		Project( 0 ),
		Scene( 0 ),
		Object( 0 ),
		Template( 0 )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Macro Methods for checking multiple parts at once //
	inline flex& Var4( const char* Name );			// Object, Template, Scene, Project //
	inline flex& Var4( const std::string& Name );
	inline flex& Var3( const char* Name );			// Object, Scene, Project //
	inline flex& Var3( const std::string& Name );
	inline flex& Var2( const char* Name );			// Scene, Project //
	inline flex& Var2( const std::string& Name );

	// Shorthands to the parts //
	inline flex& TVar( const char* Name );
	inline flex& TVar( const std::string& Name );
	inline flex& OVar( const char* Name );
	inline flex& OVar( const std::string& Name );
	inline flex& SVar( const char* Name );
	inline flex& SVar( const std::string& Name );
	inline flex& PVar( const char* Name );
	inline flex& PVar( const std::string& Name );	
};
// - ------------------------------------------------------------------------------------------ - //
// TODO: Use thread keyword, implying a seperate Shared instance per thread
extern cShared Shared;
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_SHARED_H__ //
// - ------------------------------------------------------------------------------------------ - //
