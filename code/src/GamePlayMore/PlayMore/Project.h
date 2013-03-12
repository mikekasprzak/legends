// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_PROJECT_H__
#define __PLAYMORE_PROJECT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <list>

#include "KeyStore.h"
#include "Scene.h"
// - ------------------------------------------------------------------------------------------ - //
class cProject {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cProject thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cKeyStore PVar;						// Key (Variable) Storage, Project Scope (Highest Level) //

	std::list<cScene> Scene;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cProject()
	{
		Log( "Hey it's me" );
		cUID Scobe;
		cUID Scob;
		Log( "%i", Scob.Get() );
			
		flex MyFlex = true;
		MyFlex += "Scores!";
		MyFlex += 44;
		
		flex Shoe = 144;
		Shoe += 10;
		Shoe += "Sock";
		Shoe += true;
		Shoe += false;
		
		MyFlex += Shoe;

		Log( "%s %s %i %f o_o", MyFlex.ToString(), Shoe.ToString(), MyFlex.ToInt(), MyFlex.ToFloat() );
	}

public: // - Methods -------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_PROJECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
