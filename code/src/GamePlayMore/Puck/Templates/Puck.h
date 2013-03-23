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
		Object->Body = cBody::new_CircleV( Pos, Real(4), Vector3D::Zero, Real(0.1f), Real(0.9f) );
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

//	virtual void Contact( cObject* Object, cObject* Vs );
//	virtual void Sense( cObject* Object, cObject* Vs );
	virtual void Notice( cObject* Object, cObject* Sender, const int Message ) {
		if ( (Message == 1) || (Message == 2) ) { // Puck Go Home //
			Object->Body->GetCircleVPtr()->Pos = Vector3D::Zero;
			Object->Body->GetCircleVPtr()->SetVelocity( Vector3D::Zero );
			if ( Message == 1 ) {
				SVar("Score1") += 1;
			}
			if ( Message == 2 ) {
				SVar("Score2") += 1;
			}
		}		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TEMPLATE_PUCK_H__ //
// - ------------------------------------------------------------------------------------------ - //
