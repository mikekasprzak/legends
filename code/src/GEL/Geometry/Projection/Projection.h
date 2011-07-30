// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Projection_H__
#define __Geometry_Projection_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Simple_OrthoProjection( const Real& Width, const Real& Height ) {
	Real ActualWidth = 2.0 / Width;
	Real ActualHeight = 2.0 / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0;
	Matrix[2] = 0;
	Matrix[3] = 0;
	
	Matrix[4] = 0;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0;
	Matrix[7] = 0;
	
	Matrix[8] = 0;
	Matrix[9] = 0;
	Matrix[10] = 1;
	Matrix[11] = 0;
	
	Matrix[12] = 0;
	Matrix[13] = 0;
	Matrix[14] = 0;
	Matrix[15] = 1;

	return Matrix;
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Frustum_OrthoProjection( const Real& Width, const Real& Height, const Real& Near, const Real& Far ) {
	Real ActualWidth = 2.0 / Width;
	Real ActualHeight = 2.0 / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0;
	Matrix[2] = 0;
	Matrix[3] = 0;
	
	Matrix[4] = 0;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0;
	Matrix[7] = 0;
	
	Matrix[8] = 0;
	Matrix[9] = 0;
	Matrix[10] = 2.0 / (Far - Near);
	Matrix[11] = 0;
	
	Matrix[12] = 0;
	Matrix[13] = 0;
	Matrix[14] = -((Far+Near)/(Far-Near));
	Matrix[15] = 1;

	return Matrix;
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Simple_PerspectiveProjection( const Real& Width, const Real& Height, const Real& Distance ) {
	Real ActualWidth = 2.0 / Width;
	Real ActualHeight = 2.0 / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0;
	Matrix[2] = 0;
	Matrix[3] = 0;
	
	Matrix[4] = 0;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0;
	Matrix[7] = 0;
	
	Matrix[8] = 0;
	Matrix[9] = 0;
	Matrix[10] = 1;
	Matrix[11] = 0;
	
	Matrix[12] = 0;
	Matrix[13] = 0;
	Matrix[14] = -1.0 / Distance;
	Matrix[15] = 1;

	return Matrix;
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Frustum_PerspectiveProjection( const Real& Width, const Real& Height, const Real& Near, const Real& Far, const Real& Center = Real::Half) {
	// Note: Center is a scalar that controls how deep to put the "even perspective" plane //
	Real ActualWidth = (2.0f * (Near+((Far-Near)*Center))) / Width;
	Real ActualHeight = (2.0f * (Near+((Far-Near)*Center))) / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0;
	Matrix[2] = 0;
	Matrix[3] = 0;
	
	Matrix[4] = 0;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0;
	Matrix[7] = 0;
	
	Matrix[8] = 0;
	Matrix[9] = 0;
	Matrix[10] = (Far + Near) / (Far - Near);
	Matrix[11] = 1;
	
	Matrix[12] = 0;
	Matrix[13] = 0;
	Matrix[14] = -((2.0*Far*Near)/(Far-Near));
	Matrix[15] = 0;

	return Matrix;
}
// - ------------------------------------------------------------------------------------------ - //
inline void Rotate_Matrix_XY( Matrix4x4& Matrix ) {
	Matrix2x2 Temp( Matrix[0], Matrix[1], Matrix[4], Matrix[5] );
	
	Matrix[0] = Temp[1];
	Matrix[1] = -Temp[3];
	Matrix[4] = Temp[0];
	Matrix[5] = -Temp[2];
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_LookAt( const Vector3D& Src, const Vector3D& Dest, const Vector3D& WorldUp = Vector3D(0,1,0) ) {
	Vector3D ViewDirection = (Dest - Src).Normal();
	Real Dot = ViewDirection * WorldUp;
	Vector3D Up = (WorldUp - (Dot * ViewDirection)).Normal();
	Vector3D Right = Up % ViewDirection;
	
	return Matrix4x4(
		Right.x, Up.x, ViewDirection.x, 0,
		Right.y, Up.y, ViewDirection.y, 0,
		Right.z, Up.z, ViewDirection.z, 0,
		0, 0, 0, 1
		);

//	return Matrix4x4(
//		Right.x, Up.x, ViewDirection.x, 0,
//		Right.y, Up.y, ViewDirection.y, 0,
//		Right.z, Up.z, ViewDirection.z, 0,
//		-Src.x, -Src.y, -Src.z, 1
//		);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Projection_H__ //
// - ------------------------------------------------------------------------------------------ - //