// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Projection_H__
#define __Geometry_Projection_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Simple_OrthoProjection( const Real& Width, const Real& Height ) {
	Real ActualWidth = 2.0f / Width;
	Real ActualHeight = 2.0f / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0.0f;
	Matrix[2] = 0.0f;
	Matrix[3] = 0.0f;
	
	Matrix[4] = 0.0f;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0.0f;
	Matrix[7] = 0.0f;
	
	Matrix[8] = 0.0f;
	Matrix[9] = 0.0f;
	Matrix[10] = 1.0f;
	Matrix[11] = 0.0f;
	
	Matrix[12] = 0.0f;
	Matrix[13] = 0.0f;
	Matrix[14] = 0.0f;
	Matrix[15] = 1.0f;

	return Matrix;
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Frustum_OrthoProjection( const Real& Width, const Real& Height, const Real& Near, const Real& Far ) {
	Real ActualWidth = 2.0f / Width;
	Real ActualHeight = 2.0f / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0.0f;
	Matrix[2] = 0.0f;
	Matrix[3] = 0.0f;
	
	Matrix[4] = 0.0f;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0.0f;
	Matrix[7] = 0.0f;
	
	Matrix[8] = 0.0f;
	Matrix[9] = 0.0f;
	Matrix[10] = 2.0 / (Far - Near);
	Matrix[11] = 0.0f;
	
	Matrix[12] = 0.0f;
	Matrix[13] = 0.0f;
	Matrix[14] = -((Far+Near)/(Far-Near));
	Matrix[15] = 1.0f;

	return Matrix;
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Simple_PerspectiveProjection( const Real& Width, const Real& Height, const Real& Distance ) {
	Real ActualWidth = 2.0f / Width;
	Real ActualHeight = 2.0f / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0.0f;
	Matrix[2] = 0.0f;
	Matrix[3] = 0.0f;
	
	Matrix[4] = 0.0f;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0.0f;
	Matrix[7] = 0.0f;
	
	Matrix[8] = 0.0f;
	Matrix[9] = 0.0f;
	Matrix[10] = 1.0f;
	Matrix[11] = 0.0f;
	
	Matrix[12] = 0.0f;
	Matrix[13] = 0.0f;
	Matrix[14] = -1.0f / Distance;
	Matrix[15] = 1.0f;

	return Matrix;
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_Frustum_PerspectiveProjection( const Real& Width, const Real& Height, const Real& Near, const Real& Far, const Real& Center = Real::Half) {
	// Note: Center is a scalar that controls how deep to put the "even perspective" plane //
	Real ActualWidth = (2.0f * (Near+((Far-Near)*Center))) / Width;
	Real ActualHeight = (2.0f * (Near+((Far-Near)*Center))) / Height;

	Matrix4x4 Matrix;

	Matrix[0] = ActualWidth;
	Matrix[1] = 0.0f;
	Matrix[2] = 0.0f;
	Matrix[3] = 0.0f;
	
	Matrix[4] = 0.0f;
	Matrix[5] = -ActualHeight;
	Matrix[6] = 0.0f;
	Matrix[7] = 0.0f;
	
	Matrix[8] = 0.0f;
	Matrix[9] = 0.0f;
	Matrix[10] = (Far + Near) / (Far - Near);
	Matrix[11] = 1.0f;
	
	Matrix[12] = 0.0f;
	Matrix[13] = 0.0f;
	Matrix[14] = -((2.0f*Far*Near)/(Far-Near));
	Matrix[15] = 1.0f;

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
inline Matrix4x4 Calc_LookAtOnly( const Vector3D& Src, const Vector3D& Dest, const Vector3D& CameraUp ) {
	Vector3D ViewDirection = (Dest - Src).Normal();
	Real Dot = dot(ViewDirection, CameraUp);
	Vector3D Up = (CameraUp - (Dot * ViewDirection)).Normal();
//	Vector3D Up = cross(CameraUp, ViewDirection).Normal();
	Vector3D Right = cross(Up, ViewDirection);
	
	return Matrix4x4(
		Right.x, Up.x, ViewDirection.x, 0.0f,
		Right.y, Up.y, ViewDirection.y, 0.0f,
		Right.z, Up.z, ViewDirection.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_LookAt( const Vector3D& Pos, const Vector3D& Look, const Vector3D& CameraUp ) {
	// Build the 3 basis vectors required to create an orientation //
	Vector3D Forward = (Look - Pos).Normal();
	Vector3D Right = cross(Forward, CameraUp);
	Vector3D Up = cross(Forward, Right);

	return Matrix4x4(
		Right.x, Up.x, Forward.x, 0.0f,
		Right.y, Up.y, Forward.y, 0.0f,
		Right.z, Up.z, Forward.z, 0.0f,
		-Pos.x, Pos.y, Pos.z, 1.0f
		);
}
// - ------------------------------------------------------------------------------------------ - //
inline Matrix4x4 Calc_LookAt2( const Vector3D& Src, const Vector3D& Dest, const Vector3D& CameraUp ) {
	Vector3D ViewDirection = (Dest - Src).Normal();
//	Real Dot = ViewDirection * CameraUp;
//	Vector3D Up = (CameraUp - (Dot * ViewDirection)).Normal();
	Vector3D Up = cross(CameraUp, ViewDirection).Normal(); // This is wrong //
	Vector3D Right = cross(Up, ViewDirection);

	return Matrix4x4(
		Right.x, Up.x, ViewDirection.x, 0,
		Right.y, Up.y, ViewDirection.y, 0,
		Right.z, Up.z, ViewDirection.z, 0,
		-dot(Right, Src), -dot(Up, Src), -dot(ViewDirection, Src), 1
		);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Projection_H__ //
// - ------------------------------------------------------------------------------------------ - //
