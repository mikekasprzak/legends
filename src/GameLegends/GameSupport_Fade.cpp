// - ------------------------------------------------------------------------------------------ - //
#include <GEL.h>
#include "GameSupport.h"
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::FadeInit() {
	FadeColor = GEL_RGB_BLACK;
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
		GelColor Color = GEL_RGBA( GEL_GET_R(FadeColor), GEL_GET_G(FadeColor), GEL_GET_B(FadeColor), (int)(CurrentFade*((float)(GEL_GET_A(FadeColor)))) ); 
		gelDrawRectFill( Vector2D(-HalfWidth,-HalfHeight ), Vector2D(HalfWidth,HalfHeight), Color );
		gelDrawModeRestore();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGameSupport::FadeSetColor( const GelColor Color ) {
	FadeColor = Color;
}
// - ------------------------------------------------------------------------------------------ - //
