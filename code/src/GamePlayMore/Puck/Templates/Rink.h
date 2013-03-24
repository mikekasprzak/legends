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
	tRink( const float Radius = 160, const float Length = 150 ) {
		Art = cArt::new_Capsule( Vector3D(+Length,0,0),Real(Radius), Vector3D(-Length,0,0),Real(Radius), GEL_RGBA(255,255,255,64) );
	}
	
	virtual ~tRink() {
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	virtual void CreateObject( cObject* Object, const Vector3D& Pos ) {
		cTemplate::CreateObject( Object, Pos );
		// ... //
		cArt_Capsule* Cap = Art->GetCapsulePtr();
		
		Object->Body = cBody::new_InvCapsule( Pos+Cap->PosA, Cap->RadiusA, Pos+Cap->PosB, Cap->RadiusB );
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
		return true;
	}
//	virtual void Sense( cObject* Object, cObject* Vs, const st32 SensorIndex ) {
//	}
//	virtual void Notice( cObject* Object, cObject* Sender, const int Message ) {
//	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TEMPLATE_RINK_H__ //
// - ------------------------------------------------------------------------------------------ - //
