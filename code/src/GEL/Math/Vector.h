// - ------------------------------------------------------------------------------------------ - //
// Vector //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector_H__
#define __Geometry_Vector_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Vector/Vector2D.h"
#include "Vector/Vector3D.h"
#include "Vector/Vector4D.h"
#include "Vector/ScalarVector2D.h"
#include "Vector/ScalarVector3D.h"
#include "Vector/ScalarVector4D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Define the function that converts to a ScalarVector //
// - ------------------------------------------------------------------------------------------ - //
const ScalarVector2D& Vector2D::ToScalarVector() const {
	return (const ScalarVector2D&)*this;
}
// - ------------------------------------------------------------------------------------------ - //
const ScalarVector3D& Vector3D::ToScalarVector() const {
	return (const ScalarVector3D&)*this;
}
// - ------------------------------------------------------------------------------------------ - //
const ScalarVector4D& Vector4D::ToScalarVector() const {
	return (const ScalarVector4D&)*this;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const Vector3D Vector2D::ToVector3D() const {
	return Vector3D( x, y, Real::Zero );
}
// - ------------------------------------------------------------------------------------------ - //
const Vector3D Vector2D::ToHomoVector3D() const {
	return Vector3D( x, y, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //
const Vector4D Vector2D::ToVector4D() const {
	return Vector4D( x, y, Real::Zero, Real::Zero );
}
// - ------------------------------------------------------------------------------------------ - //
const Vector4D Vector2D::ToHomoVector4D() const {
	return Vector4D( x, y, Real::One, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const Vector2D Vector3D::ToVector2D() const {
	return Vector2D( x, y );
}
// - ------------------------------------------------------------------------------------------ - //
const Vector3D Vector3D::ToHomoVector3D() const {
	return Vector3D( x, y, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //
const Vector4D Vector3D::ToVector4D() const {
	return Vector4D( x, y, z, Real::Zero );
}
// - ------------------------------------------------------------------------------------------ - //
const Vector4D Vector3D::ToHomoVector4D() const {
	return Vector4D( x, y, z, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const Vector2D Vector4D::ToVector2D() const {
	return Vector2D( x, y );
}
// - ------------------------------------------------------------------------------------------ - //
const Vector3D Vector4D::ToVector3D() const {
	return Vector3D( x, y, z );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D ClosestPointOnLine( const Vector2D& A, const Vector2D& B, const Vector2D& P ) {
	Vector2D Line = B - A;
	Vector2D LineNormal = Line;
	Real LineLength = LineNormal.NormalizeRet();
	
	Vector2D Ray = P - A;
	
	Real DotLength = LineNormal * Ray;
	
	if ( DotLength < Real::Zero ) {
		DotLength = Real::Zero;
	}
	if ( DotLength > LineLength ) {
		DotLength = LineLength;
	}
	
	return A + (LineNormal * DotLength);
} 
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Vector_H__ //
// - ------------------------------------------------------------------------------------------ - //
