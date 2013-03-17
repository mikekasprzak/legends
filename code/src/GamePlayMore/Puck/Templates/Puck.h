// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_TEMPLATE_PUCK_H__
#define __PUCK_TEMPLATE_PUCK_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
// - ------------------------------------------------------------------------------------------ - //
class tPuck: public cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef tPuck thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	tPuck() {
		//SetArt_Circle( Vector3D::Zero, Real(8), GEL_RGB_WHITE );
		Art = cArt::new_Circle( Vector3D::Zero, Real(4), GEL_RGB_YELLOW );
	}
	
	virtual ~tPuck() {
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	// Temporary, until moved to Squirrel //
	virtual void CreateObject( cObject* Object, const Vector3D& Pos ) {
		cTemplate::CreateObject( Object, Pos );
		// ... //
		//SetBody( BT_POINT, Pos );
		Object->Body = cBody::new_Circle( Pos, Real(4) );
	}
	virtual void DestroyObject( cObject* Object ) {

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
#endif // __PUCK_TEMPLATE_PUCK_H__ //
// - ------------------------------------------------------------------------------------------ - //
