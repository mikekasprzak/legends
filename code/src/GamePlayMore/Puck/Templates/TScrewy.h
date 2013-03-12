// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_TEMPLATE_SCREWY_H__
#define __PUCK_TEMPLATE_SCREWY_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
// - ------------------------------------------------------------------------------------------ - //
class tScrewy: public cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef tScrewy thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	tScrewy() {
		Log( "I'm Screwy" );
	}
	
	virtual ~tScrewy() {
		Log( "Screwy died" );
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
	virtual void Create( cObject* Object ) {
		cTemplate::Create( Object );
		// ... //
		Log( "Screwy Instanced" );
	}
	virtual void Destroy( cObject* Object ) {
		Log( "Screwy Instance Killed" );
		// ... //
		cTemplate::Destroy( Object );
	}

	// Works Just Fine //
//	virtual void Step( cObject* Object ) {
//		Log( "Stepped" );
//	}
//	virtual void Draw( cObject* Object, const Matrix4x4& Matrix ) {
//		Log( "Drawn" );
//	}

//	virtual void Contact( class cObject* Object, class cObject* Vs );
//	virtual void Sense( class cObject* Object, class cObject* Vs );
//	virtual void Notice( class cObject* Object, class cObject* Sender, const int Message );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TEMPLATE_SCREWY_H__ //
// - ------------------------------------------------------------------------------------------ - //
