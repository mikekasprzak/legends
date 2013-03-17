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
		for ( auto Itr = Active.begin(); Itr != Active.end(); Itr++ ) {
			(*Itr)->Template->DestroyObject( *Itr );
			delete *Itr;
		}
		for ( auto Itr = Static.begin(); Itr != Static.end(); Itr++ ) {
			(*Itr)->Template->DestroyObject( *Itr );
			delete *Itr;
		}
		for ( auto Itr = Children.begin(); Itr != Children.end(); Itr++ ) {
			(*Itr)->Template->DestroyObject( *Itr );
			delete *Itr;
		}

		// Templates Last, so the above Destroy functions work //
		for ( auto Itr = Template.begin(); Itr != Template.end(); Itr++ ) {
			delete Itr->second;
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
		
	// Templates ------------------------------------------------------------------------------ - //
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
	
	// Objects -------------------------------------------------------------------------------- - //
	// TODO: Give a Position and Overloads //
	inline void AddObject( const char* TemplateName, const Vector3D& Pos = Vector3D::Zero ) {
		//Template[Name] = _Template;
		auto Itr = Template.find( TemplateName );
		if ( Itr != Template.end() ) {
			cObject* NewObj = new cObject( Itr->second );
			NewObj->Template->CreateObject( NewObj, Pos );
			NewObj->UpdateRect();
			
			Active.push_back( NewObj );
		}
		else {
			Log( "! ERROR: Can't Add Object! Template \"%s\" not found!", TemplateName );
		}

	}
	inline void AddObject( const std::string& TemplateName, const Vector3D& Pos = Vector3D::Zero ) {
		AddObject( TemplateName.c_str(), Pos );
	}

public:
	virtual void Step();
	virtual void Draw( const Matrix4x4& Matrix );

	void DrawRect( const Matrix4x4& Matrix );
	void DrawBody( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_SCENE_H__ //
// - ------------------------------------------------------------------------------------------ - //
