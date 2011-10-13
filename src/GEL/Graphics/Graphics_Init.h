// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Graphics_Init_H__
#define __GEL_Graphics_Init_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics_System.h>
#include <Graphics/Graphics_Screen.h>
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupFullScreen( const bool Flag = true ) {
	System::InitFlags.FullScreen = Flag;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupAutodetectScreenShape( const bool Flag = true ) {
	System::InitFlags.AutodetectScreenShape = Flag;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupStencilSize( const int Var = 1 ) {
	System::StencilSize = Var;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupDepthSize( const int Var = 16 ) {
	System::DepthSize = Var;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupScreenShape( const int Width, const int Height ) {
	ActualScreen::Width = Width;
	ActualScreen::Height = Height;
	
	ActualScreen::TallScreen = ActualScreen::Width < ActualScreen::Height;
	
	System::InitFlags.ScreenShapeSet = true;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupRefScreenShape( const int Width, const int Height ) {
	RefScreen::Width = Width;
	RefScreen::Height = Height;	

	System::InitFlags.RefShapeSet = true;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupOverscan( const float Width, const float Height ) {
	OverscanScreen::Scalar.x = 1.0f - Width;
	OverscanScreen::Scalar.y = 1.0f - Height;	

	System::InitFlags.OverscanSet = true;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetupNativeScalar( const float Width, const float Height ) {
	NativeScreen::Scalar.x = Width;
	NativeScreen::Scalar.y = Height;	

	System::InitFlags.NativeScalarSet = true;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Init sets all important variables nedded before calling Setup. //
// - ------------------------------------------------------------------------------------------ - //
bool gelInit();
// - ------------------------------------------------------------------------------------------ - //
// Setup Actually Sets 
// - ------------------------------------------------------------------------------------------ - //
bool gelSetup();
// - ------------------------------------------------------------------------------------------ - //
// Legacy!! This function exists ONLY to support exist applications, until fully refactored! // 
// - ------------------------------------------------------------------------------------------ - //
bool gelPostSetup();
// - ------------------------------------------------------------------------------------------ - //

void gelCalculateScreenShape();
void gelCalculateViewMatrix();

void gelCalculateProxyScreenShape();

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Graphics_Init_H__ //
// - ------------------------------------------------------------------------------------------ - //
