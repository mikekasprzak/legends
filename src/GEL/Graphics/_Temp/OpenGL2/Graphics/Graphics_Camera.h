// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_Camera_H__
#define __Graphics_Camera_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Input_Mouse.h"
// - ------------------------------------------------------------------------------------------ - //
class cCamera {
public:
	Vector2D Pos;
	Real Scale;

	Vector2D ViewShape;
	Vector2D ViewHalfShape;
	
	Vector2D Mouse;
	
	// TODO: Something to do with clipping //
public:
	cCamera( const Vector2D& _Pos = Vector2D::Zero, const Real& _Scale = Real::One ) :
		Pos( _Pos ),
		Scale( _Scale ),
		ViewShape( RefScreen::Shape * Scale ),
		ViewHalfShape( ViewShape * Real::Half )
	{
	}
	
public:
	inline void CalculateViewShape() {
		ViewShape = RefScreen::Shape * Scale;
		ViewHalfShape = ViewShape * Real::Half;
	}

	inline void Update() {
		Mouse.x = (::Mouse.Pos.x * ViewShape.x) / RefScreen::Shape.x;
		Mouse.y = (::Mouse.Pos.y * ViewShape.y) / RefScreen::Shape.y;
		Mouse -= Pos;
	}

	inline const Matrix3x3 GetMatrix() const {
		Matrix3x3 Matrix = Matrix3x3::Scaling( Real::One / Scale );
		Matrix *= Matrix3x3::Translating( Pos );
		Matrix *= Matrix3x3::Translating( RefScreen::HalfShape * Scale );
		return Matrix;
	}	
};
// - ------------------------------------------------------------------------------------------ - //
extern cCamera Camera;
extern cCamera* CurrentCamera;
// - ------------------------------------------------------------------------------------------ - //
/*
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetCameraMatrix( const cCamera& _Camera = *CurrentCamera ) {
//	Matrix = _Camera.GetMatrix();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetScreenMatrix( ) {
//	Matrix = Matrix3x3::Translating( RefScreen::HalfShape );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetScreenAspectMatrix( ) {
	// This is a function for setting an aspect ratio constrained Matrix. //
	//   All screen co-ordinates fall in to at least a -1 to +1 range. //
	// TODO: Make it do what the above suggests.  //
	//   Perhaps horizontal is always -1 to 1, and vertical is some aspect ratio refined one. //
//	Matrix = Matrix3x3::Translating( RefScreen::HalfShape );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelSetCamera( cCamera& _Camera = Camera ) {
	CurrentCamera = &_Camera;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetCameraPos( const Vector2D& v ) {
	CurrentCamera->Pos = v;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelAddCameraPos( const Vector2D& v ) {
	CurrentCamera->Pos += v;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D& gelGetCameraPos() {
	return CurrentCamera->Pos;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D gelGetCameraCenter() {
	return Vector2D::Zero - gelGetCameraPos();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetCameraPos( const Real _x, const Real _y, const Real _z = Real::Zero ) {
	CurrentCamera->Pos = Vector2D( _x, _y );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelAddCameraPos( const Real _x, const Real _y, const Real _z = Real::Zero ) {
	CurrentCamera->Pos += Vector2D( _x, _y );	
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real& gelGetCameraScale() {
	return CurrentCamera->Scale;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelSetCameraScale( const Real _CameraScale ) {
	CurrentCamera->Scale = _CameraScale;	
	
	CurrentCamera->ViewShape = RefScreen::Shape * CurrentCamera->Scale;
	CurrentCamera->ViewHalfShape = CurrentCamera->ViewShape * Real::Half;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelAddCameraScale( const Real _CameraScale ) {
	gelSetCameraScale( gelGetCameraScale() + _CameraScale );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelConstrainCamera( const Vector2D& P1, const Vector2D& P2 ) {
	// Create a rectangle, contracting it's shape by the current size of the zoomed view //
	Rect2D InnerViewRect = Rect2D::Pair(
		P1 + CurrentCamera->ViewHalfShape,
		P2 - CurrentCamera->ViewHalfShape
		);
	
	// Restrict Camera to Zone //
	CurrentCamera->Pos = InnerViewRect.ClosestPoint( CurrentCamera->Pos );	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelConstrainCameraScale( const Real Min, const Real Max ) {
	if ( gelGetCameraScale() < Min )
		gelSetCameraScale( Min );

	if ( gelGetCameraScale() > Max )
		gelSetCameraScale( Max );	
}
// - ------------------------------------------------------------------------------------------ - //
*/

/*
// - ------------------------------------------------------------------------------------------ - //
inline void gelOrtho() {
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
#ifdef USES_OPENGL
	glViewport( 0, 0, ActualScreen::Width, ActualScreen::Height );

	int RefWidth = RefScreen::Width + (int)(Real(RefScreen::DiffX) / RefScreen::Scalar);
	int RefHeight = RefScreen::Height + (int)(Real(RefScreen::DiffY) / RefScreen::Scalar);

	glOrtho(
		-(RefWidth >> 1),  +(RefWidth >> 1),
		-(RefHeight >> 1), +(RefHeight >> 1),
		-1.0f, 1.0f
		);
#else // NOT USES_SDL //
	// TODO: This is wrong.  Does not take in to account the new Aspect Ratio features. //
	glViewport( 0, 0, RefScreen::Height * RefScreen::Scalar, RefScreen::Width * RefScreen::Scalar);
	
	glOrthof(
		-(RefScreen::Height >> 1), +(RefScreen::Height >> 1),
		-(RefScreen::Width >> 1),  +(RefScreen::Width >> 1),
		-1.0f, 1.0f
		);
#endif // USES_SDL //

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

#ifdef USES_IOS
	glRotatef(90,0,0,1);
#endif // USES_IOS //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelPerspective() {
	// OpenGL Spec says only Frustum/Ortho/gluPerspective should affect Projection Matrix //
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

#ifdef USES_OPENGL
	glViewport( 0, 0, ActualScreen::Width, ActualScreen::Height );

	int RefWidth = RefScreen::Width + (int)(Real(RefScreen::DiffX) / RefScreen::Scalar);
	int RefHeight = RefScreen::Height + (int)(Real(RefScreen::DiffY) / RefScreen::Scalar);

	// This frustrum configuration places (0,0,0) between the near and far plane //
	// glFrustrum's Near and Far planes get negated by this call //
	glFrustum(
		-(RefWidth / 8.0f),  +(RefWidth / 8.0f),
		-(RefHeight / 8.0f), +(RefHeight / 8.0f),
		100.0f, 900.0f
		);		
#else // NOT USES_SDL //
#endif // USES_SDL //

	// OpenGL Spec says camera transformations go on the top of the ModelView, not Projection Matrix //
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

#ifdef USES_IOS
	glRotatef(90,0,0,1);
#endif // USES_IOS //
	glTranslatef( 0, 0, -500.0f );
}
// - ------------------------------------------------------------------------------------------ - //
*/
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_Camera_H__ //
// - ------------------------------------------------------------------------------------------ - //
