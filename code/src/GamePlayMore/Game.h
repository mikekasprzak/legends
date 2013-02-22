// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_GAME_H__
#define __PLAYMORE_GAME_H__
// - ------------------------------------------------------------------------------------------ - //
// Games are collections of Objects that play, act, and respond to rules. //
// - ------------------------------------------------------------------------------------------ - //
#include "Shared.h"
#include "Template.h"
#include "Object.h"
// - ------------------------------------------------------------------------------------------ - //
class cGame {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cGame thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
//	//cObject[] Parents;	// Parents are Stepped and Drawn //
//	//cObject[] Children;	// Children are only Stepped or Drawn if their Parent decides to do so. //
	
	// The idea of Inactive Objects, have some flag to say "I don't check for collisions" (though //
	// others may check me). Actually this may not work, since I may want to do the increment //
	// optimization (i.e. idx2=idx+1). //
	
	// Active, Inactive, Children ? YES! //
	
	//cObject[] Active;		// Active Parent Objects are Stepped, Drawn, and tested against eachother. //
	//cObject[] InActive;	// InActive Parent Objects are Stepped, Drawn, and tested against by Actives. //
	//cObject[] Children;	// Children are not tested against, and are only Stepped or Drawn by Parents. //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cGame()
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_GAME_H__ //
// - ------------------------------------------------------------------------------------------ - //
