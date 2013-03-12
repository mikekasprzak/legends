// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_SCENE_H__
#define __PLAYMORE_SCENE_H__
// - ------------------------------------------------------------------------------------------ - //
// Scenes are collections of Objects that play, act, and respond to rules. //
// - ------------------------------------------------------------------------------------------ - //
#include <list>
#include <map>
#include <string>

#include "Template.h"
#include "Object.h"
#include "KeyStore.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Shared.h"
// - ------------------------------------------------------------------------------------------ - //
class cScene {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cScene thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cKeyStore 						SVar;		// Key (Variable) Storage, Scene Scope //
	
	std::map<std::string,cTemplate>	Template;

	//std::list<cObject>			Parents;	// Parents are Stepped and Drawn //
	//std::list<cObject>			Children;	// Children are only Stepped or Drawn if their Parent decides to do so. //
	
	// The idea of Inactive Objects, have some flag to say "I don't check for collisions" (though //
	// others may check me). Actually this may not work, since I may want to do the increment //
	// optimization (i.e. idx2=idx+1). //
	
	// Active, Inactive, Children ? YES! //
	
	std::list<cObject*>				Active;		// Active Parent Objects are Stepped, Drawn, and tested against eachother. //
	std::list<cObject*>				InActive;	// InActive Parent Objects are Stepped, Drawn, and tested against by Actives. //
	std::list<cObject*>				Children;	// Children are not tested against, and are only Stepped or Drawn by Parents. //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cScene()
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_SCENE_H__ //
// - ------------------------------------------------------------------------------------------ - //
