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

		//SetArt_Circle( Vector3D::Zero, Real(8), GEL_RGB_WHITE );
		Art = cArt::new_Circle( Vector3D::Zero, Real(40), GEL_RGB_ORANGE );
	}
	
	virtual ~tScrewy() {
		Log( "Screwy died" );
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
	virtual void CreateObject( cObject* Object, const Vector3D& Pos ) {
		cTemplate::CreateObject( Object, Pos );
		// ... //
		//SetBody( BT_POINT, Pos );
		Object->Body = cBody::new_Point( Pos );
		
		Log( "Screwy Instanced" );
	}
	virtual void DestroyObject( cObject* Object ) {
		Log( "Screwy Instance Killed" );
		// ... //
		cTemplate::DestroyObject( Object );
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
