// - ------------------------------------------------------------------------------------------ - //
#include "Graphics.h"
#include <Input/Mouse.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Init sets all important variables nedded before calling Setup. //
// - ------------------------------------------------------------------------------------------ - //
bool gelInit() {
#ifdef GELS_INIT_GRAPHICS_API
	gelsInitGraphicsAPI();
#endif // GELS_INIT_GRAPHICS_API //

	// System //
	System::ShutdownGame = false;
	System::CloseButtonPressed = false;
	
	System::Flags.Flags = 0;
		
	System::StencilSize = 0;
	System::DepthSize = 0;
	
	// Current //
	Current::Color = GEL_RGB_DEFAULT;
	Current::NormalColor = GEL_RGB_DEFAULT;
	
	Current::NormalLength = 8;

	// ActualScreen //
	ActualScreen::Width = 0;
	ActualScreen::Height = 0;
	
	// RefScreen //
	RefScreen::Width = 0;
	RefScreen::Height = 0;
	
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

	// TODO: Overscan //	

	if ( RefScreen::AspectRatio > ActualScreen::AspectRatio ) {
		// Final Screen (Information and Scalars that differentiate the two) //
		if ( ActualScreen::TallScreen ) {
			RefScreen::Scalar = Real( ActualScreen::Height ) / Real( RefScreen::Width );

			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
		}
		else {
			RefScreen::Scalar = Real( ActualScreen::Width ) / Real( RefScreen::Width );

			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
		}
	}
	else {
		// Final Screen (Information and Scalars that differentiate the two) //
		if ( ActualScreen::TallScreen ) {
			RefScreen::Scalar = Real( ActualScreen::Width ) / Real( RefScreen::Height );

			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
		}
		else {
			RefScreen::Scalar = Real( ActualScreen::Height ) / Real( RefScreen::Height );
		
			RefScreen::DiffX = (ActualScreen::Width - (int)(Real(RefScreen::Width) * RefScreen::Scalar));
			RefScreen::DiffY = (ActualScreen::Height - (int)(Real(RefScreen::Height) * RefScreen::Scalar));
		}
	}
	
	RefScreen::OffsetX = RefScreen::DiffX >> 1;
	RefScreen::OffsetY = RefScreen::DiffY >> 1;

	// Full Reference Screen (How much extra space we really have in reference co-ordinates) //
	if ( ActualScreen::TallScreen ) {
		FullRefScreen::Width = (int)( Real(ActualScreen::Height) / RefScreen::Scalar );
		FullRefScreen::Height = (int)( Real(ActualScreen::Width) / RefScreen::Scalar );
	}	
	else {
		FullRefScreen::Width = (int)( Real(ActualScreen::Width) / RefScreen::Scalar );
		FullRefScreen::Height = (int)( Real(ActualScreen::Height) / RefScreen::Scalar );
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void gelCalculateViewMatrix() {
	Real ActualWidth = (1.0/((ActualScreen::Width / (RefScreen::Scalar*Real(2)))));
	Real ActualHeight = (-1.0/((ActualScreen::Height / (RefScreen::Scalar*Real(2)))));

	if ( ActualScreen::TallScreen ) {
		ViewMatrix[0] = 0;
		ViewMatrix[1] = -ActualHeight;
		ViewMatrix[2] = 0;
		ViewMatrix[3] = 0;
		
		ViewMatrix[4] = ActualWidth;
		ViewMatrix[5] = 0;
		ViewMatrix[6] = 0;
		ViewMatrix[7] = 0;
		
		ViewMatrix[8] = 0;
		ViewMatrix[9] = 0;
		ViewMatrix[10] = 1;
		ViewMatrix[11] = 0;
		
		ViewMatrix[12] = 0;
		ViewMatrix[13] = 0;
		ViewMatrix[14] = 0;
		ViewMatrix[15] = 1;
	}
	else {
		ViewMatrix[0] = ActualWidth;
		ViewMatrix[1] = 0;
		ViewMatrix[2] = 0;
		ViewMatrix[3] = 0;
		
		ViewMatrix[4] = 0;
		ViewMatrix[5] = ActualHeight;
		ViewMatrix[6] = 0;
		ViewMatrix[7] = 0;
		
		ViewMatrix[8] = 0;
		ViewMatrix[9] = 0;
		ViewMatrix[10] = 1;
		ViewMatrix[11] = 0;
		
		ViewMatrix[12] = 0;
		ViewMatrix[13] = 0;
		ViewMatrix[14] = 0;
		ViewMatrix[15] = 1;
	}	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Setup Actually Sets 
// - ------------------------------------------------------------------------------------------ - //
bool gelSetup() {
#ifdef GELS_LOG_GRAPHICS_DETAILS
	gelsLogGraphicsDetails();
#endif // GELS_LOG_GRAPHICS_DETAILS //

#ifdef GELS_AUTODETECT_SCREEN_SHAPE	
	if ( System::Flags.AutodetectScreen ) {
		gelsAutodetectScreenShape();
		ActualScreen::TallScreen = ActualScreen::Width < ActualScreen::Height;
	}
#endif // GELS_AUTODETECT_SCREEN_SHAPE //
		
	if ( !System::Flags.RefShapeSet ) {
		if ( !System::Flags.ScreenShapeSet ) {
			Log( "ERROR: No screen dimensions specified or detected!" );
			return false;
		}
		else {
			// If ScreenShape is set, but not the reference shape, use the ScreenShape. //
			RefScreen::Width = ActualScreen::Width;
			RefScreen::Height = ActualScreen::Height;
		}
	}

	// Given RefScreen, Calculate Screen Information //
	gelCalculateScreenShape();

#ifdef GELS_SET_VIDEO_MODE
	gelsSetVideoMode();
#endif // GELS_SET_VIDEO_MODE //

#ifdef GELS_SET_SWAP_INTERVAL
	gelsSetSwapInterval();
#endif // GELS_SET_SWAP_INTERVAL //

	return true;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Legacy!! This function exists ONLY to support exist applications, until fully refactored! // 
// - ------------------------------------------------------------------------------------------ - //
bool gelPostSetup() {
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	gelCalculateViewMatrix();

	ModelMatrix = Matrix4x4::ScalarMatrix( 1 );
/*
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
*/
	glViewport( 
		0,
		0, 
		ActualScreen::Width, 
		ActualScreen::Height
		);
/*
	// Set a Transformation Matrix that makes Texture Co-ordinates work from 0-63 //	
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
	//glScalef( 0.015625f, 0.015625f, 0.015625f );
	glScalef( 1 / UV_ONE_F, 1 / UV_ONE_F, 1 / UV_ONE_F );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
*/

//	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	gelBuildInternalShaders();

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

	// Setup Texture Pool //	
	TexturePool::Init( "Content" );
	TexturePool::AddDirectory( "" );

	gelInitCapture();

	return true;
}
// - ------------------------------------------------------------------------------------------ - //
