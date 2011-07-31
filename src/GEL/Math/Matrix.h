// - ------------------------------------------------------------------------------------------ - //
// Matrix //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Matrix_H__
#define __Geometry_Matrix_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Matrix/Matrix1x2.h"
#include "Matrix/Matrix2x1.h"
#include "Matrix/Matrix2x2.h"

#include "Matrix/Matrix1x3.h"
#include "Matrix/Matrix3x1.h"
#include "Matrix/Matrix3x3.h"

#include "Matrix/Matrix1x4.h"
#include "Matrix/Matrix4x1.h"
#include "Matrix/Matrix4x4.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// The rule for matrix multiplication is the Width of A must be equal to the Height of B!! //
// The book lists this as the other way around, since they read co-ordinates differently!! //
// [ 0 1 ] //
// [ 2 3 ] //
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix1x2 operator * ( const Matrix2x2& _a, const Matrix1x2& _b ) {
	Matrix1x2 Temp;
	Temp.x = (_a.Array[ 0 ] * _b.x) + (_a.Array[ 1 ] * _b.y);
	Temp.y = (_a.Array[ 2 ] * _b.x) + (_a.Array[ 3 ] * _b.y);
	return Temp;	
}
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix2x1 operator * ( const Matrix2x1& _a, const Matrix2x2& _b ) {
	Matrix2x1 Temp;
	Temp.x = (_a.x * _b.Array[ 0 ]) + (_a.y * _b.Array[ 2 ]);
	Temp.y = (_a.x * _b.Array[ 1 ]) + (_a.y * _b.Array[ 3 ]);
	return Temp;		
}
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix1x3 operator * ( const Matrix3x3& _a, const Matrix1x3& _b ) {
	Matrix1x3 Temp;
	Temp.x = (_a.Array[ 0 ] * _b.x) + (_a.Array[ 1 ] * _b.y) + (_a.Array[ 2 ] * _b.z);
	Temp.y = (_a.Array[ 3 ] * _b.x) + (_a.Array[ 4 ] * _b.y) + (_a.Array[ 5 ] * _b.z);
	Temp.z = (_a.Array[ 6 ] * _b.x) + (_a.Array[ 7 ] * _b.y) + (_a.Array[ 8 ] * _b.z);
	return Temp;	
}
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix3x1 operator * ( const Matrix3x1& _a, const Matrix3x3& _b ) {
	Matrix3x1 Temp;
	Temp.x = (_a.x * _b.Array[ 0 ]) + (_a.y * _b.Array[ 3 ]) + (_a.z * _b.Array[ 6 ]);
	Temp.y = (_a.x * _b.Array[ 1 ]) + (_a.y * _b.Array[ 4 ]) + (_a.z * _b.Array[ 7 ]);
	Temp.z = (_a.x * _b.Array[ 2 ]) + (_a.y * _b.Array[ 5 ]) + (_a.z * _b.Array[ 8 ]);
	return Temp;		
}
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix1x4 operator * ( const Matrix4x4& _a, const Matrix1x4& _b ) {
	Matrix1x4 Temp;
	Temp.x = (_a.Array[ 0 ] * _b.x) + (_a.Array[ 1 ] * _b.y) + (_a.Array[ 2 ] * _b.z) + (_a.Array[ 3 ] * _b.w);
	Temp.y = (_a.Array[ 4 ] * _b.x) + (_a.Array[ 5 ] * _b.y) + (_a.Array[ 6 ] * _b.z) + (_a.Array[ 7 ] * _b.w);
	Temp.z = (_a.Array[ 8 ] * _b.x) + (_a.Array[ 9 ] * _b.y) + (_a.Array[ 10 ] * _b.z) + (_a.Array[ 11 ] * _b.w);
	Temp.w = (_a.Array[ 12 ] * _b.x) + (_a.Array[ 13 ] * _b.y) + (_a.Array[ 14 ] * _b.z) + (_a.Array[ 15 ] * _b.w);
	return Temp;	
}
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix4x1 operator * ( const Matrix4x1& _a, const Matrix4x4& _b ) {
	Matrix4x1 Temp;
	Temp.x = (_a.x * _b.Array[ 0 ]) + (_a.y * _b.Array[ 4 ]) + (_a.z * _b.Array[ 8 ]) + (_a.w * _b.Array[ 12 ]);
	Temp.y = (_a.x * _b.Array[ 1 ]) + (_a.y * _b.Array[ 5 ]) + (_a.z * _b.Array[ 9 ]) + (_a.w * _b.Array[ 13 ]);
	Temp.z = (_a.x * _b.Array[ 2 ]) + (_a.y * _b.Array[ 6 ]) + (_a.z * _b.Array[ 10 ]) + (_a.w * _b.Array[ 14 ]);
	Temp.w = (_a.x * _b.Array[ 3 ]) + (_a.y * _b.Array[ 7 ]) + (_a.z * _b.Array[ 11 ]) + (_a.w * _b.Array[ 15 ]);
	return Temp;		
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Apply a matrix transformation to a vector //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Vector2D::ApplyMatrix( const Matrix2x2& _Vs ) const {
	return (this->ToMatrix2x1() * _Vs).ToVector2D();
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Vector2D::ApplyMatrix( const Matrix3x3& _Vs ) const {
	return (this->ToVector3D().ToMatrix3x1() * _Vs).ToVector3D().ToVector2D();
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Vector2D::ApplyMatrix( const Matrix4x4& _Vs ) const {
	return (this->ToVector4D().ToMatrix4x1() * _Vs).ToVector4D().ToVector2D();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector3D Vector3D::ApplyMatrix( const Matrix3x3& _Vs ) const {
	return (this->ToMatrix3x1() * _Vs).ToVector3D();
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector3D Vector3D::ApplyMatrix( const Matrix4x4& _Vs ) const {
	return (this->ToMatrix4x1() * _Vs).ToVector3D();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector4D Vector4D::ApplyMatrix( const Matrix4x4& _Vs ) const {
	return (this->ToMatrix4x1() * _Vs).ToVector4D();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Matrix4x4 Matrix3x3::ToMatrix4x4() const {
	return Matrix4x4( 
		Array[0], Array[1], Array[2], Real::Zero,
		Array[3], Array[4], Array[5], Real::Zero,
		Array[6], Array[7], Array[8], Real::Zero,
		Real::Zero, Real::Zero, Real::Zero, Real::One
		);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Matrix_H__ //
// - ------------------------------------------------------------------------------------------ - //
