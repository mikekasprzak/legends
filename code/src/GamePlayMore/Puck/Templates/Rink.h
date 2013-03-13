// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_TEMPLATE_RINK_H__
#define __PUCK_TEMPLATE_RINK_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
// - ------------------------------------------------------------------------------------------ - //
class tRink: public cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef tRink thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	tRink( const bool Square = false ) {
		if ( Square ) {
			Art = cArt::new_RadiusRect( Vector3D::Zero, Vector2D(180,180), GEL_RGBA(255,255,255,64) );
			Log( "Cool" );
		}
		else {
			Art = cArt::new_Circle( Vector3D::Zero, Real(180), GEL_RGBA(255,255,255,64) );
		}
	}
	
	virtual ~tRink() {
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	virtual void CreateObject( cObject* Object, const Vector3D& Pos ) {
		cTemplate::CreateObject( Object, Pos );
		// ... //
		
		Object->Body = cBody::new_Point( Pos );
	}
	virtual void DestroyObject( cObject* Object ) {

		// ... //
		cTemplate::DestroyObject( Object );
	}

	// Works Just Fine //
	virtual void Step( cObject* Object ) {
		cTemplate::Step( Object );
	}
//	virtual void Draw( cObject* Object, const Matrix4x4& Matrix ) {
//		cTemplate::Draw( Object, Matrix );
//	}

	virtual const bool Contact( cObject* Object, cObject* Vs ) {
		return false;
	}
//	virtual void Sense( cObject* Object, cObject* Vs ) {
//	}
//	virtual void Notice( cObject* Object, cObject* Sender, const int Message ) {
//	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TEMPLATE_RINK_H__ //
// - ------------------------------------------------------------------------------------------ - //
