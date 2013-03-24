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
		Object->OVar.Add("Stun") = 0;
		Object->OVar.Add("Dash") = 0;
		
		Object->Body = cBody::new_CircleV( Pos, TVar("Radius").ToFloat(), Vector3D::Zero, Real::One, Real(0.7f) );
	}
	virtual void DestroyObject( cObject* Object ) {

		// ... //
		cTemplate::DestroyObject( Object );
	}

	// Works Just Fine //
	virtual void Step( cObject* Object ) {
		cTemplate::Step( Object );

		// Input //
		Vector3D Stick;
//		if ( SVar("DelayTime").ToInt() == 0 ) {
			Stick = Input::XInput::GamePad[TVar("Number").ToInt()].LStick.ToVector3D();
//		}
		Real StickMag = Stick.Magnitude();
		if ( StickMag < Real(0.1f) )
			Stick = Vector3D::Zero;

		cBody_SphereV* Bd = Object->Body->GetCircleVPtr();

		if ( Var("Stun").ToInt() > 0 )
			Var("Stun") -= 1;
		if ( Var("Dash").ToInt() > 0 )
			Var("Dash") -= 1;

		Real Scalar = Real::One;
		int Dash = Var("Dash").ToInt();

		if ( Var("Dash").ToInt() > 0 ) {
			if ( Dash > 20 )
				Dash = 20;
			Scalar = Real::One - Real(Dash / 20.0f); 
		}
		else {
			if ( (Input::XInput::GamePad[TVar("Number").ToInt()].Button) ) {
				Var("Dash") = 40;
				Bd->AddForce( Stick * Real(2.5f) );
			}
		}

		int Stun = Var("Stun").ToInt();

		if ( Stun > 0 ) {
			if ( Stun > 10 )
				Stun = 10;
			Scalar = min(Scalar,Real::One - Real(Stun / 10.0f)); 
		}

		Vector3D Line = ((Stick * Real(2)) - Bd->GetVelocity()) * (Real(0.15) + Stick.Magnitude());
		Bd->AddForce( Line * Real(0.25f) * Scalar );
	}
//	virtual void Draw( cObject* Object, const Matrix4x4& Matrix ) {
//		cTemplate::Draw( Object, Matrix );
//	}

	virtual const bool Contact( cObject* Object, cObject* Vs ) {
		int DashA = Object->OVar("Dash").ToInt();
		int DashB = 0;
		if ( Vs->OVar.Exists("Dash") ) {
			DashB = Vs->OVar("Dash").ToInt();
		}
		
		if ( (DashA > 10) && (DashB > 10) ) {
			// Both in Motion, no Effect //
		}
		else {
			if ( DashA > 10) {
				Vs->Notify( Object, 5 );
			}
		}
		return true;
	}
	virtual void Sense( cObject* Object, cObject* Vs, const st32 SensorIndex ) {
	}
	virtual void Notice( cObject* Object, cObject* Sender, const int Message ) {
		if ( Message == 5 ) {
			Object->OVar("Stun") = 20;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PUCK_TEMPLATE_PLAYER_H__ //
// - ------------------------------------------------------------------------------------------ - //
