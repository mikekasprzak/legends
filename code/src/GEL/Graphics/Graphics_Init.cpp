// - ------------------------------------------------------------------------------------------ - //
#include "Graphics.h"
#include <Input/Input_Mouse.h>
#include <Geometry/Projection/Projection.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELS_Init_GLExtensions.h"

#include "Native/OpenGL1/GELS_Init_SDL.h"
#include "Native/OpenGL1/GELS_Init_SDL13.h"
#include "Native/OpenGL1/GELS_Init_SDL_EGLProxy.h"
#include "Native/OpenGL1/GELS_Init_Airplay.h"
//#include "Native/OpenGL1/GELS_Init_EGL.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Init sets all important variables nedded before calling Setup. //
// - ------------------------------------------------------------------------------------------ - //
bool gelInit() {
#ifdef GELS_INIT_GRAPHICS_API
	gels_InitGraphicsAPI();
#endif // GELS_INIT_GRAPHICS_API //

	// System //
	System::ShutdownGame = false;
	System::CloseButtonPressed = false;
	System::ToggleFullScreen = false;
	
	System::InitFlags.Flags = 0;
	System::InfoFlags.Flags = 0;
		
	System::StencilSize = 0;
	System::DepthSize = 0;
	
	// Current //
	Current::Color = GEL_RGB_DEFAULT;
	Current::NormalColor = GEL_RGB_DEFAULT;
	
	Current::NormalLength = 8;

	// ActualScreen //
	ActualScreen::Width = 0;
	ActualScreen::Height = 0;

	// NativeScreen //
	NativeScreen::Width = 0;
	NativeScreen::Height = 0;
	
	// RefScreen //
	RefScreen::Width = 0;
	RefScreen::Height = 0;
		
	// Overscan //
	OverscanScreen::Scalar.x = 1.0f;
	OverscanScreen::Scalar.y = 1.0f;
		
	// Native //
	NativeScreen::Scalar.x = 1.0f;
	NativeScreen::Scalar.y = 1.0f;
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Calculate Screen Information //
// - ------------------------------------------------------------------------------------------ - //
void gelCalculateScreenShape() {
	// Reference Screen (Virtual Resulution in Pseudopixels) //
	RefScreen::Shape = Vector2D( RefScreen::Width, RefScreen::Height );
	RefScreen::HalfShape = RefScreen::Shape * Real::Half;
		
	RefScreen::AspectRatio = Real( RefScreen::Width ) / Real( RefScreen::Height );
		
	// Actual Screen (Physical Resolution in Pixels) //
	ActualScreen::Shape = Vector2D( ActualScreen::Width, ActualScreen::Height );
	ActualScreen::HalfShape = ActualScreen::Shape * Real::Half;
	if ( ActualScreen::TallScreen )
		ActualScreen::AspectRatio = Real( ActualScreen::Height ) / Real( ActualScreen::Width );
	else
		ActualScreen::AspectRatio = Real( ActualScreen::Width ) / Real( ActualScreen::Height );

	// Overscanned Screen //
	OverscanScreen::Width = (int)(Real( ActualScreen::Width ) * OverscanScreen::Scalar.x);
	OverscanScreen::Height = (int)(Real( ActualScreen::Height ) * OverscanScreen::Scalar.y);
	if ( ActualScreen::TallScreen )
		OverscanScreen::AspectRatio = Real( OverscanScreen::Height ) / Real( OverscanScreen::Width );
	else
		OverscanScreen::AspectRatio = Real( OverscanScreen::Width ) / Real( OverscanScreen::Height );

	// Calculate Scalars and Difference necessary to fit Reference screen to the Overscanned Screen //
	if ( RefScreen::AspectRatio > OverscanScreen::AspectRatio ) {
		// Final Screen (Information and Scalars that differentiate the two) //
		if ( ActualScreen::TallScreen ) {
			RefScreen::Scalar = Real( OverscanScreen::Height ) / Real( RefScreen::Width );

			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
		}
		else {
			RefScreen::Scalar = Real( OverscanScreen::Width ) / Real( RefScreen::Width );

			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
		}
	}
	else {
		// Final Screen (Information and Scalars that differentiate the two) //
		if ( ActualScreen::TallScreen ) {
			RefScreen::Scalar = Real( OverscanScreen::Width ) / Real( RefScreen::Height );

			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
		}
		else {
			RefScreen::Scalar = Real( OverscanScreen::Height ) / Real( RefScreen::Height );
		
			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
		}
	}
	
	RefScreen::OffsetX = RefScreen::DiffX >> 1;
	RefScreen::OffsetY = RefScreen::DiffY >> 1;

	// Full Reference Screen (How much extra space we really have in reference co-ordinates) //
	// *NOTE* : I did not use Overscan here. FullRefScreen is used for stuff like fades. //
	if ( ActualScreen::TallScreen ) {
		FullRefScreen::Width = (int)( Real(ActualScreen::Height) / RefScreen::Scalar );
		FullRefScreen::Height = (int)( Real(ActualScreen::Width) / RefScreen::Scalar );
	}	
	else {
		FullRefScreen::Width = (int)( Real(ActualScreen::Width) / RefScreen::Scalar );
		FullRefScreen::Height = (int)( Real(ActualScreen::Height) / RefScreen::Scalar );
	}

	// Calculate Scalars and Difference necessary to fit Reference screen to the Overscanned Screen //
	if ( RefScreen::AspectRatio > OverscanScreen::AspectRatio ) {
		// Final Screen (Information and Scalars that differentiate the two) //
		if ( ActualScreen::TallScreen ) {
			FullRefScreen::Scalar = Real( OverscanScreen::Height ) / Real( FullRefScreen::Width );
		}
		else {
			FullRefScreen::Scalar = Real( OverscanScreen::Width ) / Real( FullRefScreen::Width );
		}
	}
	else {
		// Final Screen (Information and Scalars that differentiate the two) //
		if ( ActualScreen::TallScreen ) {
			FullRefScreen::Scalar = Real( OverscanScreen::Width ) / Real( FullRefScreen::Height );
		}
		else {
			FullRefScreen::Scalar = Real( OverscanScreen::Height ) / Real( FullRefScreen::Height );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void gelCalculateProxyScreenShape() {
	ProxyScreen::Shape = Vector2D( ProxyScreen::Width, ProxyScreen::Height );
	ProxyScreen::HalfShape = ProxyScreen::Shape * Real::Half;
	if ( ProxyScreen::TallScreen )
		ProxyScreen::AspectRatio = Real( ProxyScreen::Height ) / Real( ProxyScreen::Width );
	else
		ProxyScreen::AspectRatio = Real( ProxyScreen::Width ) / Real( ProxyScreen::Height );

	// Final Screen (Information and Scalars that differentiate the two) //
	if ( ProxyScreen::TallScreen ) {
		ProxyScreen::Scalar = Real( ProxyScreen::Height ) / Real( RefScreen::Width );

		ProxyScreen::DiffX = (ProxyScreen::Width - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
		ProxyScreen::DiffY = (ProxyScreen::Height - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
	}
	else {
		ProxyScreen::Scalar = Real( ProxyScreen::Width ) / Real( RefScreen::Width );

		ProxyScreen::DiffX = (ProxyScreen::Width - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
		ProxyScreen::DiffY = (ProxyScreen::Height - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
	}
	
	ProxyScreen::OffsetX = RefScreen::DiffX >> 1;
	ProxyScreen::OffsetY = RefScreen::DiffY >> 1;
}
// - ------------------------------------------------------------------------------------------ - //
void gelCalculateViewMatrix() {
	ViewMatrix = Calc_Simple_OrthoProjection( 
		ActualScreen::Width / RefScreen::Scalar,
		ActualScreen::Height / RefScreen::Scalar
		);

	if ( ActualScreen::TallScreen ) {
		Rotate_Matrix_XY( ViewMatrix );
	}

}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Setup Actually Sets 
// - ------------------------------------------------------------------------------------------ - //
bool gelSetup() {
#ifdef GELS_LOG_GRAPHICS_DETAILS
	gels_LogGraphicsDetails();
#endif // GELS_LOG_GRAPHICS_DETAILS //

#ifdef GELS_AUTODETECT_NATIVE_SCREEN_SHAPE	
	if ( !System::InfoFlags.HasScreenShape ) {
		gels_AutodetectNativeScreenShape();
		System::InfoFlags.HasScreenShape = true;
	}
#endif // GELS_AUTODETECT_NATIVE_SCREEN_SHAPE //


//#ifdef GELS_AUTODETECT_SCREEN_SHAPE	
	if ( System::InitFlags.AutodetectScreenShape ) {
		if ( NativeScreen::Width > 0 ) {
			ActualScreen::Width = (int)((float)NativeScreen::Width * NativeScreen::Scalar.x);
			ActualScreen::Height = (int)((float)NativeScreen::Height * NativeScreen::Scalar.y);
			
			if ( (ActualScreen::Width & 3) != 0 ) {
				ActualScreen::Width = (ActualScreen::Width & ~3) + 4;
			}
				
			if ( (ActualScreen::Height & 3) != 0 ) {
				ActualScreen::Height = (ActualScreen::Height & ~3) + 4;
			}
				
			ActualScreen::TallScreen = ActualScreen::Width < ActualScreen::Height;		
		}
		
//		gels_AutodetectScreenShape();
//		ActualScreen::TallScreen = ActualScreen::Width < ActualScreen::Height;
	}
//#endif // GELS_AUTODETECT_SCREEN_SHAPE //
		
	if ( !System::InitFlags.RefShapeSet ) {
		if ( !System::InitFlags.ScreenShapeSet ) {
			Log( "ERROR: No screen dimensions specified or detected!" );
			return false;
		}
		else {
			// If ScreenShape is set, but not the reference shape, use the ScreenShape. //
			RefScreen::Width = ActualScreen::Width;
			RefScreen::Height = ActualScreen::Height;
		}
	}

	Log( "** Actual: %i %i  Ref: %i %i\n", ActualScreen::Width, ActualScreen::Height, RefScreen::Width, RefScreen::Height );

	// Given RefScreen, Calculate Screen Information //
	gelCalculateScreenShape();

#ifdef GELS_SET_VIDEO_MODE
	gels_SetVideoMode();
#endif // GELS_SET_VIDEO_MODE //

#ifdef GELS_SET_SWAP_INTERVAL
	gels_SetSwapInterval();
#endif // GELS_SET_SWAP_INTERVAL //
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Legacy!! This function exists ONLY to support exist applications, until fully refactored! // 
// - ------------------------------------------------------------------------------------------ - //
bool gelPostSetup() {
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	Log( "** Actual: %i %i\n", ActualScreen::Width, ActualScreen::Height );
	Log( "** Ref: %i %i %i\n", RefScreen::Width, RefScreen::Height, (int)(RefScreen::Scalar * Real(1000)) );
	gelCalculateViewMatrix();

	ModelMatrix = Matrix4x4::ScalarMatrix( 1 );

#ifndef USES_OPENGL2
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
#endif // USES_OPENGL2 //

	glViewport( 
		0,
		0, 
//		NativeScreen::Width, 
//		NativeScreen::Height
		ActualScreen::Width, 
		ActualScreen::Height
		);

#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	gels_BuildInternalShaders();
#else // USES_OPENGL2 //
	// Set a Transformation Matrix that makes Texture Co-ordinates work from 0-63 //	
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
	//glScalef( 0.015625f, 0.015625f, 0.015625f );
	glScalef( 1 / GEL_UV_ONE_F, 1 / GEL_UV_ONE_F, 1 / GEL_UV_ONE_F );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
#endif // USES_OPENGL2 //

	// Reset Clipping and Set Projection //
	glEnable( GL_SCISSOR_TEST );
	gelResetClip();
	
	// Set the initial current color defaulting to white //
	// (Note, makecol only works after set_gel_mode) //
	Current::Color = GEL_RGB_DEFAULT;
	Current::NormalColor = GEL_RGB_DEFAULT;
	
	Current::NormalLength = 8;
	
	// Make sure we have a freshly initialized mouse //
	Mouse = cMouse();

	gelInitCapture();

	return true;
}
// - ------------------------------------------------------------------------------------------ - //
