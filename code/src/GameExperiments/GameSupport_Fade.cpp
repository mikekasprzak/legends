// - ------------------------------------------------------------------------------------------ - //
#include <GEL.h>
#include "GameSupport.h"
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::FadeInit() {
	FadeColor = RGB_BLACK;
	CurrentFade = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::FadeExit() {
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::FadeStep() {
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::FadeDraw() {
	if ( CurrentFade != Real::Zero ) {
		float HalfWidth = (FullRefScreen::Width * 0.5f) + 2.0f;
		float HalfHeight = (FullRefScreen::Height * 0.5f) + 2.0f;
		
		gelEnableAlphaBlending();
		gelDrawModeFlat();
		ColorType Color = RGBA( GET_R(FadeColor), GET_G(FadeColor), GET_B(FadeColor), (int)(CurrentFade*((float)(GET_A(FadeColor)))) ); 
		gelDrawRectFill( Vector2D(-HalfWidth,-HalfHeight ), Vector2D(HalfWidth,HalfHeight), Color );
		gelDrawModeRestore();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::FadeSetColor( const ColorType Color ) {
	FadeColor = Color;
}
// - ------------------------------------------------------------------------------------------ - //
