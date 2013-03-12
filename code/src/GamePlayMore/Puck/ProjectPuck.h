// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_PROJECTPUCK_H__
#define __PUCK_PROJECTPUCK_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>

#include "SceneGame.h"
// - ------------------------------------------------------------------------------------------ - //
class cProjectPuck: public cProject {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cProjectPuck thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	//virtual void Create() { // Can't do this in C++. See Project.h. Using Constructor instead. //
	cProjectPuck() { 
		AddScene( "Game", new cSceneGame() );
		DeactivateScene( "Game" );
		Log( "Voo: %i", Active.size() );
		_ActivateScene( "Game" );
		_ActivateScene( "Game" );
		Log( "Voo: %i", Active.size() );
		_DeactivateScene( "Game" );
		Log( "Voo: %i", Active.size() );
	}
	
	//virtual void Destroy() { // See Above //
	virtual ~cProjectPuck() {
		
	}
public: // - Methods -------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_PROJECTPUCK_H__ //
// - ------------------------------------------------------------------------------------------ - //
