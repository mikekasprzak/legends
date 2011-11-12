// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_CAMERA_H__
#define __GEL_CAMERA_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>

#include <Geometry/Projection/Projection.h>
// - ------------------------------------------------------------------------------------------ - //
class GelCamera {
public:
	Vector3D Pos;				// Where the camera is //
	Vector3D Target;			// What the camera is looking at //

public:	
	Real NearPlane;
	Real FarPlane;
	
	Real PlaneWidth;
	Real PlaneHeight;
	
public:	
	Matrix4x4 Projection;		// Projection Component //
	Matrix4x4 View;				// View Component (Camera Pos->Target) //
	
	Matrix4x4 ProjectionView;	// Combined Matrix //
public:
	
	GelCamera() :
		PlaneWidth( 16 ),
		PlaneHeight( 9 ),
		NearPlane( 10 ),
		FarPlane( 100 )
	{
		Pos = Vector3D(0,0,0);
		Target = Vector3D(0,0,-1);		
	}
	
	GelCamera( const Real _Width, const Real _Height, const Real _Near, const Real _Far ) :
		PlaneWidth( _Width ),
		PlaneHeight( _Height ),
		NearPlane( _Near ),
		FarPlane( _Far )
	{
		Pos = Vector3D(0,0,0);
		Target = Vector3D(0,0,-1);
	}
	
	void SetFrustum( const Real _Width, const Real _Height, const Real _Near, const Real _Far ) {
		PlaneWidth = _Width;
		PlaneHeight = _Height;
		NearPlane = _Near;
		FarPlane = _Far;
	}
	
	void UpdateMatrix() {
		Projection = Calc_Frustum_PerspectiveProjection( PlaneWidth, PlaneHeight, NearPlane, FarPlane );		
		View = Calc_LookAt( Pos, Target );
	
		ProjectionView = Projection;
		ProjectionView.Multiply( View );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_CAMERA_H__
// - ------------------------------------------------------------------------------------------ - //
