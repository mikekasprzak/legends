// - ------------------------------------------------------------------------------------------ - //
#ifndef __PUCK_TEMPLATE_PLAYER_H__
#define __PUCK_TEMPLATE_PLAYER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Engine/Engine.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
class tPlayer: public cTemplate {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef tPlayer thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
public: // - Constructors and Destructors ----------------------------------------------------- - //
	tPlayer( const int PlayerNumber, const GelColor& Color = GEL_RGB_WHITE ) {
		TVar.Add("Number") = PlayerNumber;
		TVar.Add("Radius") = 12.0f;
		Art = cArt::new_Circle( Vector3D::Zero, TVar("Radius").ToFloat(), Color );
	}
	
	virtual ~tPlayer() {
	}

public: // - Methods -------------------------------------------------------------------------- - //
public: // - Specialization Methods ----------------------------------------------------------- - //
	virtual void CreateObject( cObject* Object, const Vector3D& Pos ) {
		cTemplate::CreateObject( Object, Pos );
		// ... //
		
		Object->Body = cBody::new_CircleV( Pos, TVar("Radius").ToFloat() );
	}
	virtual void DestroyObject( cObject* Object ) {

		// ... //
		cTemplate::DestroyObject( Object );
	}

	// Works Just Fine //
	virtual void Step( cObject* Object ) {
		cTemplate::Step( Object );

		Vector3D Stick = Input::XInput::GamePad[TVar("Number").ToInt()].LStick.ToVector3D();
		if ( Stick.x.Abs() < Real(0.1f) )
			Stick.x = Real::Zero;
		if ( Stick.y.Abs() < Real(0.1f) )
			Stick.y = Real::Zero;
//		Stick *= Real(0.9f);
//		Stick *= Real(1.1111111111111111111111f);

		Object->Body->GetCircleVPtr()->AddForce( Stick * Real(0.3f) );
			
//		Object->Body->GetCircleVPtr()->AddForce( Vector3D( 
//			Input::XInput::GamePad[TVar("Number").ToInt()].LStickX, 
//			Input::XInput::GamePad[TVar("Number").ToInt()].LStickY, 
//			0 
//			) );
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
#endif // __PUCK_TEMPLATE_PLAYER_H__ //
// - ------------------------------------------------------------------------------------------ - //
