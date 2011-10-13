// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELS_Screen.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Reference Screen //
namespace RefScreen {
	int Width = 0;
	int Height = 0;
	
	Real AspectRatio;

	Vector2D Shape;
	Vector2D HalfShape;

	Real Scalar;
	int OffsetX = 0;
	int OffsetY = 0;

	int DiffX = 0;
	int DiffY = 0;
};
// - ------------------------------------------------------------------------------------------ - //
// Full Reference Screen (Scaled version of Actual) //
namespace FullRefScreen {
	int Width = 0;
	int Height = 0;
	
	Real AspectRatio;

	Vector2D Shape;
	Vector2D HalfShape;

	Real Scalar;
};
// - ------------------------------------------------------------------------------------------ - //
// Actual Screen //
namespace ActualScreen {
	int Width = 0;
	int Height = 0;
	
	Real AspectRatio;
	bool TallScreen = false;

	Vector2D Shape;
	Vector2D HalfShape;
};
// - ------------------------------------------------------------------------------------------ - //
// Proxy Screen //
namespace ProxyScreen {
	int Width = 0;
	int Height = 0;
	
	Real AspectRatio;
	bool TallScreen = false;

	Vector2D Shape;
	Vector2D HalfShape;

	Real Scalar;
	int OffsetX = 0;
	int OffsetY = 0;

	int DiffX = 0;
	int DiffY = 0;
};
// - ------------------------------------------------------------------------------------------ - //
// Overscan Screen //
namespace OverscanScreen {
	int Width = 0;
	int Height = 0;
	
	Real AspectRatio;
	Vector2D Scalar;
};
// - ------------------------------------------------------------------------------------------ - //
// The Native Screen Resolution (Only use this to calculate a Window size) //
namespace NativeScreen {
	int Width = 0;
	int Height = 0;
	
	Vector2D Scalar;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelSetClip( const int x, const int y, const int w, const int h ) {
#ifdef GELS_CROP
	if ( ActualScreen::TallScreen ) {
		gels_Crop( 
			(RefScreen::OffsetX + (y * RefScreen::Scalar)),
			(RefScreen::OffsetY + (x * RefScreen::Scalar)),
			(h * RefScreen::Scalar),
			(w * RefScreen::Scalar)
			);
	}
	else {
		gels_Crop( 
			(RefScreen::OffsetX + (x * RefScreen::Scalar)),
			(RefScreen::OffsetY + (y * RefScreen::Scalar)),
			(w * RefScreen::Scalar),
			(h * RefScreen::Scalar)
			);
	}
#endif // GELS_CROP //
//#ifdef GELS_CROP
//	if ( ActualScreen::TallScreen ) {
//		gels_Crop( 
//			(RefScreen::OffsetX + (y * RefScreen::Scalar)) * NativeScreen::Scalar.y,
//			(RefScreen::OffsetY + (x * RefScreen::Scalar)) * NativeScreen::Scalar.x,
//			(h * RefScreen::Scalar) * NativeScreen::Scalar.y, 
//			(w * RefScreen::Scalar) * NativeScreen::Scalar.x
//			);
//	}
//	else {
//		gels_Crop( 
//			(RefScreen::OffsetX + (x * RefScreen::Scalar)) * NativeScreen::Scalar.x,
//			(RefScreen::OffsetY + (y * RefScreen::Scalar)) * NativeScreen::Scalar.y, 
//			(w * RefScreen::Scalar) * NativeScreen::Scalar.x, 
//			(h * RefScreen::Scalar) * NativeScreen::Scalar.y
//			);
//	}
//#endif // GELS_CROP //
}
// - ------------------------------------------------------------------------------------------ - //
void gelResetClip( ) {
#ifdef GELS_CROP
	gels_Crop( 
		0,
		0,
		ActualScreen::Width,
		ActualScreen::Height
		);
#endif // GELS_CROP //
}
// - ------------------------------------------------------------------------------------------ - //
void gelSetProxyClip( const int x, const int y, const int w, const int h ) {
#ifdef GELS_CROP
	if ( ProxyScreen::TallScreen ) {
		gels_Crop( 
			(ProxyScreen::OffsetX + (y * ProxyScreen::Scalar)),
			(ProxyScreen::OffsetY + (x * ProxyScreen::Scalar)),
			(h * ProxyScreen::Scalar),
			(w * ProxyScreen::Scalar)
			);
	}
	else {
		gels_Crop( 
			(ProxyScreen::OffsetX + (x * ProxyScreen::Scalar)),
			(ProxyScreen::OffsetY + (y * ProxyScreen::Scalar)),
			(w * ProxyScreen::Scalar),
			(h * ProxyScreen::Scalar)
			);
	}
#endif // GELS_CROP //
}
// - ------------------------------------------------------------------------------------------ - //
void gelResetProxyClip( ) {
#ifdef GELS_CROP
	gels_Crop( 
		0,
		0,
		ProxyScreen::Width,
		ProxyScreen::Height
		);
#endif // GELS_CROP //
}
// - ------------------------------------------------------------------------------------------ - //
