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
		PVar.Add( "ShowDebug" ) = false;
		AddScene( "Game", new cSceneGame() );
	}
	
	//virtual void Destroy() { // See Above //
	virtual ~cProjectPuck() {
		
	}
public: // - Methods -------------------------------------------------------------------------- - //
	virtual void Draw( const Matrix4x4& Matrix ) {
		cProject::Draw( Matrix );
		if ( PVar("ShowDebug").ToBool() ) {
			cProject::DrawBody( Matrix );
			cProject::DrawRect( Matrix );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_PROJECTPUCK_H__ //
// - ------------------------------------------------------------------------------------------ - //
