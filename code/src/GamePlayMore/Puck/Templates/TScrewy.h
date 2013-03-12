// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_TSCREWY_H__
#define __PUCK_TSCREWY_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
// - ------------------------------------------------------------------------------------------ - //
class cTScrewy: public cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cTScrewy thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	cTScrewy() {
		Log( "I'm Screwy" );
	}
	
	virtual ~cTScrewy() {
		Log( "Screwy died" );
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
	virtual void Create( cObject* Object ) {
		cTemplate::Create( Object );
		// ... //

	}
	virtual void Destroy( cObject* Object ) {
		
		// ... //
		cTemplate::Destroy( Object );
	}
	
//	virtual void Step( class cObject* Object );
//	virtual void Draw( class cObject* Object, const Matrix4x4& Matrix );
//
//	virtual void Contact( class cObject* Object, class cObject* Vs );
//	virtual void Sense( class cObject* Object, class cObject* Vs );
//	virtual void Notice( class cObject* Object, class cObject* Sender, const int Message );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TSCREWY_H__ //
// - ------------------------------------------------------------------------------------------ - //
