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

	std::list<cScene*> Scene;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cProject() {
	}
	
	virtual ~cProject() {
		for ( auto Itr = Scene.begin(); Itr != Scene.end(); Itr++ ) {
			delete *Itr;
		}
	}

public: // - Methods -------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_PROJECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
