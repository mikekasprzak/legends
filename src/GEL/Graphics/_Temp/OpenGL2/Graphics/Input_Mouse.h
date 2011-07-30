// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Input_Mouse_H__
#define __GEL_Input_Mouse_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cMouse {
public:
	Vector2D Pos;
	Vector2D Old;
	
	int Wheel;
	int WheelOld;
	
	int ButtonCurrent;
	int ButtonLast;
	
public:
	cMouse() {
		extern int mouse_b;
		extern int mouse_b_new;
		
		ButtonCurrent = mouse_b | mouse_b_new;
		ButtonLast = mouse_b | mouse_b_new;
		mouse_b_new = 0;
		
		Wheel = 0;
		WheelOld = 0;
	}
	
	inline void Update() {
		float x, y;

#if defined( USES_MULTITOUCH )

		#define MAX_POINTERS 16
		extern float pointer_x[MAX_POINTERS];
		extern float pointer_y[MAX_POINTERS];
		extern int pointer_b[MAX_POINTERS];
		extern int pointer_n[MAX_POINTERS];

		extern int NewestPointer;
//		extern int LastPointer;
		
		int CurrentPointer = NewestPointer;

		int _Button = pointer_n[CurrentPointer] | pointer_b[CurrentPointer];
		pointer_n[CurrentPointer] = 0;
		
		if ( ActualScreen::TallScreen ) {
			x = (float)ActualScreen::Height-pointer_y[CurrentPointer];
			y = pointer_x[CurrentPointer];
		}
		else {
			x = pointer_x[CurrentPointer];
			y = pointer_y[CurrentPointer];
		}

#else // USES_MULTITOUCH //

		extern int mouse_x;
		extern int mouse_y;
		extern int mouse_b;
		extern int mouse_b_new;

		int _Button = mouse_b_new | mouse_b;
		mouse_b_new = 0;

		if ( ActualScreen::TallScreen ) {
			x = ActualScreen::Height-mouse_y;
			y = mouse_x;
		}
		else {
			x = mouse_x;
			y = mouse_y;
		}

#endif // USES_MULTITOUCH //

		Old = Pos;
		if ( ActualScreen::TallScreen ) {
			Pos.x = -ActualScreen::HalfShape.y;
			Pos.y = -ActualScreen::HalfShape.x;
		}
		else {
			Pos = -ActualScreen::HalfShape;
		}
		Pos += Vector2D(x, y);
		Pos /= (RefScreen::Scalar);

#ifdef USES_SDL		
		extern int mouse_wheel;
		WheelOld = Wheel;
		Wheel = mouse_wheel;
#endif // USES_SDL //

		ButtonLast = ButtonCurrent;
		ButtonCurrent = _Button;
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Diff() const {
		return Old - Pos;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int WheelDiff() const {
		return WheelOld - Wheel;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const int Button( const int Mask = -1 ) const {
		return ButtonCurrent & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int Last( const int Mask = -1 ) const {
		return ButtonLast & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int Pressed( const int Mask = -1 ) const {
		return (ButtonCurrent ^ ButtonLast) & ButtonCurrent & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const int Released( const int Mask = -1 ) const {
		return (ButtonCurrent ^ ButtonLast) & ButtonLast & Mask;
	}
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //
extern cMouse Mouse;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Input_Mouse_H__ //
// - ------------------------------------------------------------------------------------------ - //
