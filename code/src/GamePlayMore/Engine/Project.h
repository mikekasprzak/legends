// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_PROJECT_H__
#define __PLAYMORE_PROJECT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>
#include <algorithm>

#include "KeyStore.h"
#include "Scene.h"
// - ------------------------------------------------------------------------------------------ - //
class cProject {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cProject thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cKeyStore 						PVar;	// Key (Variable) Storage, Project Scope (Highest Level) //

	std::map<std::string,cScene*>	Scene;	// All Scenes (named for easy identifying) //
	std::list<cScene*>				Active;	// Currently Active Scenes //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cProject() {
		Shared.Project = this;
		
		//Create(); // Will not work in C++, because constructors can't call child virtual functions //
					// Details here: http://www.artima.com/cppsource/nevercall.html
	}
	
	virtual ~cProject() {
		//Destroy();
		
		for ( auto Itr = Scene.begin(); Itr != Scene.end(); Itr++ ) {
			delete Itr->second;
		}
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline void AddScene( const char* Name, cScene* _Scene, const bool Activate = true ) {
		Scene[Name] = _Scene;
		if ( Activate ) {
			ActivateScene( Name );
		}
	}
	inline void AddScene( const std::string& Name, cScene* _Scene, const bool Activate = true ) {
		AddScene( Name.c_str(), _Scene, Activate );
	}
	
	inline void DeleteScene( const char* Name ) {
		auto Itr = Scene.find( Name );
		if ( Itr != Scene.end() ) {
			delete Itr->second;
			Scene.erase( Itr );
		}
		else {
			Log( "! ERROR: Can't Delete Scene! Scene \"%s\" not found!", Name );
		}
	}
	inline void DeleteScene( const std::string& Name ) {
		DeleteScene( Name.c_str() );
	}
	
	inline void ActivateScene( const char* Name ) {
		auto Itr = Scene.find( Name );
		if ( Itr != Scene.end() ) {
			// Make sure the Scene we're adding isn't in the active list //
			auto Itr2 = find( Active.begin(), Active.end(), Itr->second );
			if ( Itr2 == Active.end() ) {
				Active.push_back( Itr->second );
			}
			else {
				Log( "! ERROR: Scene \"%s\" is already Active!", Name );
			}
		}
		else {
			Log( "! ERROR: Can't Set Scene! Scene \"%s\" not found!", Name );
		}
	}
	inline void ActivateScene( const std::string& Name ) {
		ActivateScene( Name.c_str() );
	}

	// Variation that doesn't check if a Scene is in the Active List //
	inline void _ActivateScene( const char* Name ) {
		auto Itr = Scene.find( Name );
		if ( Itr != Scene.end() ) {
			Active.push_back( Itr->second );
		}
		else {
			Log( "! ERROR: Can't Set Scene! Scene \"%s\" not found!", Name );
		}
	}
	inline void _ActivateScene( const std::string& Name ) {
		_ActivateScene( Name.c_str() );
	}
	
	// Deactivates all instances of a Scene (typically just one) //
	inline void DeactivateScene( const char* Name ) {
		auto Itr = Scene.find( Name );
		if ( Itr != Scene.end() ) {
			// Find all scenes
			auto Itr2 = find( Active.begin(), Active.end(), Itr->second );
			if ( Itr2 == Active.end() ) {
				Log( "! ERROR: Can't Deactivate Scene! No active instances of scene \"%s\" found!", Name );
			}
			else {
				do {
					Itr2 = Active.erase( Itr2 ); // returns next element, so feed that in to the find //
					Itr2 = find( Itr2, Active.end(), Itr->second );
				}
				while( Itr2 != Active.end() );
			}
		}
		else {
			Log( "! ERROR: Can't Deactivate Scene! Scene \"%s\" not found!", Name );
		}
	}
	inline void DeactivateScene( const std::string& Name ) {
		DeactivateScene( Name.c_str() );
	}

	// Deactivates first instances of a Scene //
	inline void _DeactivateScene( const char* Name ) {
		auto Itr = Scene.find( Name );
		if ( Itr != Scene.end() ) {
			// Find all scenes
			auto Itr2 = find( Active.begin(), Active.end(), Itr->second );
			if ( Itr2 == Active.end() ) {
				Log( "! ERROR: Can't Deactivate Scene! No active instances of scene \"%s\" found!", Name );
			}
			else {
				// This is what's different than DeactivateScene(), one erase call. //
				Active.erase( Itr2 );
			}
		}
		else {
			Log( "! ERROR: Can't Deactivate Scene! Scene \"%s\" not found!", Name );
		}
	}
	inline void _DeactivateScene( const std::string& Name ) {
		_DeactivateScene( Name.c_str() );
	}
	
public: // - Specialization Methods ----------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
//	virtual void Create() { }
//	virtual void Destroy() { }

	virtual void Step();
	virtual void Draw( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_PROJECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
