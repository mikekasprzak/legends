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
	cKeyStore 							SVar;		// Key (Variable) Storage, Scene Scope //
	
	std::map<std::string,cTemplate*>	Template;

	std::list<cObject*>					Active;		// Active Parent Objects are Stepped, Drawn, and tested against eachother. //
	std::list<cObject*>					Static;		// Static Parent Objects are Stepped, Drawn, and tested against by Actives. //
	std::list<cObject*>					Children;	// Children are not tested against, and are only Stepped or Drawn by Parents. //

	// Inactives are supposed to be objects that have fallen asleep. //
	// Undecided if they are needed (sleep may be a body property) //
	//std::list<cObject*>				Inactive;	// InActive Parent Objects are Stepped, Drawn, and tested against by Actives. //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cScene() {
	}
	
	virtual ~cScene() {
		for ( auto Itr = Template.begin(); Itr != Template.end(); Itr++ ) {
			delete Itr->second;
		}
		for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
			delete *Itr;
		}
		for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
			delete *Itr;
		}
		for ( auto Itr = Children.begin(); Itr != Children.end(); Itr++ ) {
			delete *Itr;
		}
	}

public: // - Methods -------------------------------------------------------------------------- - //
	// Shorthands for the Shared Variable Functions //
	inline flex& Var( const char* Name );			// Search Scene and Project Keystores //
	inline flex& Var( const std::string& Name );

	//inline flex& SVar( const char* Name );		// The Internal KeyStore //
	//inline flex& SVar( const std::string& Name );
	inline flex& PVar( const char* Name );			// The Project's Keystore //
	inline flex& PVar( const std::string& Name );
		

	inline void AddTemplate( const char* Name, cTemplate* _Template ) {
		Template[Name] = _Template;
	}
	inline void AddTemplate( const std::string& Name, cTemplate* _Template ) {
		AddTemplate( Name.c_str(), _Template );
	}

	inline void DeleteTemplate( const char* Name ) {
		auto Itr = Template.find( Name );
		if ( Itr != Template.end() ) {
			delete Itr->second;
			Template.erase( Itr );
		}
		else {
			Log( "! ERROR: Can't Delete Template! Template \"%s\" not found!", Name );
		}
	}
	inline void DeleteTemplate( const std::string& Name ) {
		DeleteTemplate( Name.c_str() );
	}

public:
	virtual void Step();
	virtual void Draw( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_SCENE_H__ //
// - ------------------------------------------------------------------------------------------ - //
