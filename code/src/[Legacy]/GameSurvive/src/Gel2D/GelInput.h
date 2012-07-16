// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2D_GelINPUT_H__
#define __GEL2D_GelINPUT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
void GameInput( float x, float y, int Current, int Last ) __attribute__((used));
void GameMouse( float x, float y, int Current, int Last ) __attribute__((used));
// - ------------------------------------------------------------------------------------------ - //

// - -------------------------------------------------------------------------------------------------------------- - //
extern float _Input_Stick_x;
extern float _Input_Stick_y;
// - -------------------------------------------------------------------------------------------------------------- - //
extern int _Input_KeyCurrent;
extern int _Input_KeyLast;
// - -------------------------------------------------------------------------------------------------------------- - //
enum {
	KEY_UP = 		0x1,
	KEY_DOWN = 		0x2,
	KEY_LEFT = 		0x4,
	KEY_RIGHT = 	0x8,
	KEY_ACTION = 	0x10,
	KEY_ACTION2 = 	0x20,
	KEY_ACTION3 = 	0x40,
	KEY_ACTION4 = 	0x80,
	KEY_MENU =		0x800,
};
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
// Key pressed this frame //
inline const int Input_Key( const int Mask = 0xFFFFFFFF ) {
	return _Input_KeyCurrent & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Key pressed last frame //
inline const int Input_KeyLast( const int Mask = 0xFFFFFFFF ) {
	return _Input_KeyLast & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Key was just pressed this frame //
inline const int Input_KeyPressed( const int Mask  = 0xFFFFFFFF ) {
	return (_Input_KeyCurrent ^ _Input_KeyLast) & _Input_KeyCurrent & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Key was just released this frame //
inline const int Input_KeyReleased( const int Mask  = 0xFFFFFFFF ) {
	return (_Input_KeyCurrent ^ _Input_KeyLast) & _Input_KeyLast & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
class cGelMouse {
public:
	Vector2D Pos;
	
	int Current;
	int Last;
	
public:
	cGelMouse() :
		Current( 0 ),
		Last( 0 )
	{	
	}
};
// - -------------------------------------------------------------------------------------------------------------- - //
extern cGelMouse Mouse;
// - -------------------------------------------------------------------------------------------------------------- - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2D_GelINPUT_H__ //
// - ------------------------------------------------------------------------------------------ - //