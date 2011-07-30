// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Input_VirtualPointer_H__
#define __GEL_Input_VirtualPointer_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace RefScreen {
	extern Vector2D Mouse;
};
// - ------------------------------------------------------------------------------------------ - //
class cVirtualPointer {
public:
	Vector2D Pos;
	Vector2D Old;
	
	int Wheel;
	int WheelOld;
	
	int ButtonCurrent;
	int ButtonLast;
	
public:
	cVirtualPointer() {
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

		// Update Reference Mouse //		
		RefScreen::Mouse = Pos;
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
//extern cMouse Mouse;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Input_VirtualPointer_H__ //
// - ------------------------------------------------------------------------------------------ - //
