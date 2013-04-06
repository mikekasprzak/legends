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
		TVar.Add("Number") = Right ? 2 : 1;
		Art = cArt::new_HalfCircle( Vector3D::Zero, Real(36+2), Right ? Vector3D(+1,0,0) : Vector3D(-1,0,0), Color );
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

		// TODO: Coordinate here should be Vector3D::Zero, but chaining coords unsupported //
		Object->Sensor.push_back( cBody::new_HalfCircleI( Pos+HS->Pos, HS->Radius, HS->Normal ) );
	}
	virtual void DestroyObject( cObject* Object ) {

		// ... //
		cTemplate::DestroyObject( Object );
	}

	// Works Just Fine //
	virtual void Step( cObject* Object ) {
		cTemplate::Step( Object );
			
		Object->Sensor[0]->GetHalfCirclePtr()->Pos = Object->Body->GetHalfCirclePtr()->Pos;
		Object->Sensor[0]->GetHalfCirclePtr()->Radius = Object->Body->GetHalfCirclePtr()->Radius - Real::Two;
			
//		extern int __1Key;
//		if ( __1Key ) {
//			Art->GetHalfCirclePtr()->Radius = Real(30);
//			Object->Body->GetHalfCircleVPtr()->Radius = Real(30);
//			Object->Sensor[0]->GetHalfCirclePtr()->Radius = Real(30);
//		}
//		extern int __2Key;
//		if ( __2Key ) {
//			Art->GetHalfCirclePtr()->Radius = Real(40);
//			Object->Body->GetHalfCircleVPtr()->Radius = Real(40);
//			Object->Sensor[0]->GetHalfCirclePtr()->Radius = Real(40);
//		}

	}
//	virtual void Draw( cObject* Object, const Matrix4x4& Matrix ) {
//		cTemplate::Draw( Object, Matrix );
//	}

	virtual const bool Contact( cObject* Object, cObject* Vs ) {
		return true;
	}
	virtual void Sense( cObject* Object, cObject* Vs, const st32 SensorIndex ) {
		Log("Sensor %i Found something inside the the Net", SensorIndex);
		Vs->Notify( Object, TVar("Number").ToInt() ); // Go Home //
	}
	virtual void Notice( cObject* Object, cObject* Sender, const int Message ) {
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TEMPLATE_NET_H__ //
// - ------------------------------------------------------------------------------------------ - //
