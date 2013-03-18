// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_TEMPLATE_NET_H__
#define __PUCK_TEMPLATE_NET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
// - ------------------------------------------------------------------------------------------ - //
class tNet: public cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef tNet thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	tNet( const GelColor& Color = GEL_RGB_WHITE, const bool Right = false ) {
		Art = cArt::new_HalfCircle( Vector3D::Zero, Real(30), Right ? Vector3D(+1,0,0) : Vector3D(-1,0,0), Color );
	}
	
	virtual ~tNet() {
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	virtual void CreateObject( cObject* Object, const Vector3D& Pos ) {
		cTemplate::CreateObject( Object, Pos );
		// ... //
		cArt_HalfSphere* HS = Art->GetHalfCirclePtr();
		
		Object->Body = cBody::new_HalfCircle( Pos+HS->Pos, HS->Radius, HS->Normal );
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
	virtual void Sense( cObject* Object, cObject* Vs ) {
	}
	virtual void Notice( cObject* Object, cObject* Sender, const int Message ) {
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TEMPLATE_NET_H__ //
// - ------------------------------------------------------------------------------------------ - //
