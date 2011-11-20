// - ------------------------------------------------------------------------------------------ - //
#include <GEL.h>
#include "GameSupport.h"
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseInit() {
	MouseVisible = false;

	extern char scMouseCursor[];
	MouseCursor.Load( scMouseCursor );

	HasDetectedMotion = false;
	CursorTimeout = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseExit() {
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseStep() {
	if ( CursorTimeout ) {
		MouseVisible = true;					
		CursorTimeout--;
	}
	else {
		MouseVisible = false;
		HasDetectedMotion = false;
	}		
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseDraw() {
#ifndef PRODUCT_NOMOUSECURSOR
	gelDrawModeTextured();
	{
		if ( MouseVisible ) {
			Vector2D Pos = Mouse.Pos - MouseCursor.Element[0].Pos;
			MouseCursor.DrawGraphic( 0, UIA_HLEFT | UIA_VTOP, Pos, (Mouse.Button() == 1 ? Real(0.9) : Real(1)), CurrentAngle );
		}
	}
#endif // PRODUCT_NOMOUSECURSOR //
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseEventMove() {
	if ( Mouse.Button() == 0 ) {
		HasDetectedMotion = true;
	}
	
	if ( HasDetectedMotion ) {
		CursorTimeout = 60*20;
	}
	else if ( CursorTimeout > 0 ) {
		CursorTimeout++;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseEventButtonUp() {	
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseEventButtonDown() {
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::MouseEventWindowFocus( const bool Focus ) {
	if ( Focus ) {
	}
	else {
		CursorTimeout = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //

