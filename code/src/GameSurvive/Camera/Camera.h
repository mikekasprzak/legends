// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_CAMERA_H__
#define __GEL_CAMERA_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/TweakValue.h>

#include <Math/Real.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>

#include <Geometry/Projection/Projection.h>
// - ------------------------------------------------------------------------------------------ - //
class GelCamera {
public:
	Vector3D Pos;				// Where the camera is //
	Vector3D Look;				// What the camera is looking at //

	Vector3D Up;				// Up Vector - REMEMBER TO UPDATE THIS IF NOT FIXED! //

public:	
	Real NearPlane;
	Real FarPlane;
	
	Real PlaneWidth;
	Real PlaneHeight;
	
	Real PlanePos;						// Still undecided if I need this //
	
public:	
	Matrix4x4 Projection;				// Projection Component //
	Matrix4x4 CoplanarProjection;		// Coplanar Projection Component //
	Matrix4x4 View;						// View Component (Camera Pos->Look) //
	
	Matrix4x4 ProjectionView;			// Combined Matrix //
	Matrix4x4 CoplanarProjectionView;	// Combined Matrix //
public:
	
	GelCamera() :
		PlaneWidth( 16 ),
		PlaneHeight( 9 ),
		NearPlane( 10 ),
		FarPlane( 100 )
	{
		Pos = Vector3D(0,0,0);
		Look = Vector3D(0,0,1);
		Up = Vector3D(0,1,0);
	}
	
	GelCamera( const Real _Width, const Real _Height, const Real _Near, const Real _Far, const Real _PlanePos = Real::Half ) :
		PlaneWidth( _Width ),
		PlaneHeight( _Height ),
		NearPlane( _Near ),
		FarPlane( _Far ),
		PlanePos( _PlanePos )
	{
		Pos = Vector3D(0,0,0);
		Look = Vector3D(0,0,1);
		Up = Vector3D(0,1,0);
	}
	
	void SetFrustum( const Real _Width, const Real _Height, const Real _Near, const Real _Far, const Real _PlanePos = Real::Half ) {
		PlaneWidth = _Width;
		PlaneHeight = _Height;
		NearPlane = _Near;
		FarPlane = _Far;
		
		PlanePos = _PlanePos;
	}
	
	void UpdateMatrix() {
		Projection = Calc_Frustum_PerspectiveProjection( PlaneWidth, PlaneHeight, NearPlane, FarPlane, PlanePos );

		CoplanarProjection = Calc_Frustum_CoplanarPerspectiveProjection( 
			Real(_TV(-0.01f)), 
			Real(_TV(100.0f)),
			Projection, NearPlane, FarPlane
			);

		View = Calc_LookAt( Pos, Look, Up );
	
		CalculateProjectionView();
	}
	
	void CalculateProjectionView() {
		ProjectionView = Projection;
		ProjectionView.Multiply( View );
		
		CoplanarProjectionView = CoplanarProjection;
		CoplanarProjectionView.Multiply( View );
	}

	inline Real CalcPlanePos( const Real a ) const {
		return NearPlane + ((FarPlane-NearPlane) * a);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_CAMERA_H__
// - ------------------------------------------------------------------------------------------ - //
