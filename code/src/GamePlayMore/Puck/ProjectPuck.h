// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_PROJECTPUCK_H__
#define __PUCK_PROJECTPUCK_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
#include <Render/Render.h>

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
		PVar.Add( "ShowFPS" ) = false;
		AddScene( "Game", new cSceneGame() );
	}
	
	//virtual void Destroy() { // See Above //
	virtual ~cProjectPuck() {
		
	}
public: // - Methods -------------------------------------------------------------------------- - //
	virtual void Step() {
		cProject::Step();
			
		extern int __F1Key;
		if ( __F1Key ) {
			PVar("ShowDebug") = !PVar("ShowDebug").ToBool();
		}

		extern int __F2Key;
		if ( __F2Key ) {
			PVar("ShowFPS") = !PVar("ShowFPS").ToBool();
		}
	}
	virtual void Draw( const Matrix4x4& Matrix ) {
		cProject::Draw( Matrix );
			
		if ( PVar("ShowDebug").ToBool() ) {
			cProject::DrawBody( Matrix );
			cProject::DrawRect( Matrix );
		}

		if ( PVar("ShowFPS").ToBool() ) {
			Render::EnablePremultipliedAlphaBlending();
			extern int FramesPerSecond;
			extern Render::cFont* Font;
			Font->printf( Vector3D(-260,-140,0), 16.0f, GEL_ALIGN_BOTTOM_LEFT, "%i", FramesPerSecond );
			Render::DisableBlending();
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_PROJECTPUCK_H__ //
// - ------------------------------------------------------------------------------------------ - //
