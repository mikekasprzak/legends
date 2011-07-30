// - ------------------------------------------------------------------------------------------ - //
#include <GEL.h>
#include "GameSupport.h"
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::LostFocusInit() {
	LostFocus = false;

	extern char scLostFocusImage[];
	LostFocusImage.Load( scLostFocusImage );	
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::LostFocusExit() {
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::LostFocusStep() {
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::LostFocusDraw() {
	float HalfWidth = (FullRefScreen::Width * 0.5f) + 2.0f;
	float HalfHeight = (FullRefScreen::Height * 0.5f) + 2.0f;
			
	// Draw Overlay Darkness //
	gelEnableAlphaBlending();
	gelDrawModeFlat();
	gelDrawRectFill( Vector2D(-HalfWidth,-HalfHeight ), Vector2D(HalfWidth,HalfHeight), RGBA(64,64,64,192) );
	gelDrawModeRestore();

	{
		ModelMatrix = Matrix4x4::RotationMatrixXY( CurrentAngle );
		gelLoadMatrix( ModelMatrix * ViewMatrix );
							
		gelDrawModeTextured();
		LostFocusImage.DrawGraphic( 0, UIA_HCENTER | UIA_VCENTER, Vector2D(0,0), Real(1) );
		gelDrawModeRestore();

		gelLoadMatrix( ViewMatrix );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::LostFocusEvent( const bool Focus ) {
	LostFocus = Focus;
}
// - ------------------------------------------------------------------------------------------ - //
