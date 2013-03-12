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
	// TVar, OVar, GVar, MVar //

	inline flex& Var( const char* Name ) {
//		auto Itr = Object->MyVar.find( Name );
//		if ( Itr != Object->MyVar.end() ) {
//			return Itr->second;
//		}
//		else {
//			Log( "! ERROR: Invalid Var \"%s\"", Name );
			static flex Dummy;
			return Dummy;
//		}
	}
	inline flex& Var( const std::string& Name ) {
		return Var( Name.c_str() );
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
// TODO: Use thread keyword, implying a seperate Shared instance per thread
extern cShared Shared;
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_SHARED_H__ //
// - ------------------------------------------------------------------------------------------ - //
