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
#define SWIZZLE2( _TYPE, _RETURNTYPE, _A, _B ) \
	const _RETURNTYPE _TYPE::_A ## _B () const { return _RETURNTYPE(_A,_B); }
#define SWIZZLE3( _TYPE, _RETURNTYPE, _A, _B, _C ) \
	const _RETURNTYPE _TYPE::_A ## _B ## _C () const { return _RETURNTYPE(_A,_B,_C); }
#define SWIZZLE4( _TYPE, _RETURNTYPE, _A, _B, _C, _D ) \
	const _RETURNTYPE _TYPE::_A ## _B ## _C ## _D() const { return _RETURNTYPE(_A,_B,_C,_D); }
// - ------------------------------------------------------------------------------------------ - //
SWIZZLE2( Vector2D, Vector2D, x,x );
SWIZZLE2( Vector2D, Vector2D, x,y );
SWIZZLE2( Vector2D, Vector2D, y,x );
SWIZZLE2( Vector2D, Vector2D, y,y );

SWIZZLE3( Vector2D, Vector3D, x,x,x );
SWIZZLE3( Vector2D, Vector3D, x,x,y );
SWIZZLE3( Vector2D, Vector3D, x,y,x );
SWIZZLE3( Vector2D, Vector3D, x,y,y );
SWIZZLE3( Vector2D, Vector3D, y,x,x );
SWIZZLE3( Vector2D, Vector3D, y,x,y );
SWIZZLE3( Vector2D, Vector3D, y,y,x );
SWIZZLE3( Vector2D, Vector3D, y,y,y );

SWIZZLE4( Vector2D, Vector4D, x,x,x,x );
SWIZZLE4( Vector2D, Vector4D, x,x,x,y );
SWIZZLE4( Vector2D, Vector4D, x,x,y,x );
SWIZZLE4( Vector2D, Vector4D, x,x,y,y );
SWIZZLE4( Vector2D, Vector4D, x,y,x,x );
SWIZZLE4( Vector2D, Vector4D, x,y,x,y );
SWIZZLE4( Vector2D, Vector4D, x,y,y,x );
SWIZZLE4( Vector2D, Vector4D, x,y,y,y );
SWIZZLE4( Vector2D, Vector4D, y,x,x,x );
SWIZZLE4( Vector2D, Vector4D, y,x,x,y );
SWIZZLE4( Vector2D, Vector4D, y,x,y,x );
SWIZZLE4( Vector2D, Vector4D, y,x,y,y );
SWIZZLE4( Vector2D, Vector4D, y,y,x,x );
SWIZZLE4( Vector2D, Vector4D, y,y,x,y );
SWIZZLE4( Vector2D, Vector4D, y,y,y,x );
SWIZZLE4( Vector2D, Vector4D, y,y,y,y );
// - ------------------------------------------------------------------------------------------ - //
SWIZZLE2( Vector3D, Vector2D, x,x );
SWIZZLE2( Vector3D, Vector2D, x,y );
SWIZZLE2( Vector3D, Vector2D, x,z );
SWIZZLE2( Vector3D, Vector2D, y,x );
SWIZZLE2( Vector3D, Vector2D, y,y );
SWIZZLE2( Vector3D, Vector2D, y,z );
SWIZZLE2( Vector3D, Vector2D, z,x );
SWIZZLE2( Vector3D, Vector2D, z,y );
SWIZZLE2( Vector3D, Vector2D, z,z );

SWIZZLE3( Vector3D, Vector3D, x,x,x );
SWIZZLE3( Vector3D, Vector3D, x,x,y );
SWIZZLE3( Vector3D, Vector3D, x,x,z );
SWIZZLE3( Vector3D, Vector3D, x,y,x );
SWIZZLE3( Vector3D, Vector3D, x,y,y );
SWIZZLE3( Vector3D, Vector3D, x,y,z );
SWIZZLE3( Vector3D, Vector3D, x,z,x );
SWIZZLE3( Vector3D, Vector3D, x,z,y );
SWIZZLE3( Vector3D, Vector3D, x,z,z );
SWIZZLE3( Vector3D, Vector3D, y,x,x );
SWIZZLE3( Vector3D, Vector3D, y,x,y );
SWIZZLE3( Vector3D, Vector3D, y,x,z );
SWIZZLE3( Vector3D, Vector3D, y,y,x );
SWIZZLE3( Vector3D, Vector3D, y,y,y );
SWIZZLE3( Vector3D, Vector3D, y,y,z );
SWIZZLE3( Vector3D, Vector3D, y,z,x );
SWIZZLE3( Vector3D, Vector3D, y,z,y );
SWIZZLE3( Vector3D, Vector3D, y,z,z );
SWIZZLE3( Vector3D, Vector3D, z,x,x );
SWIZZLE3( Vector3D, Vector3D, z,x,y );
SWIZZLE3( Vector3D, Vector3D, z,x,z );
SWIZZLE3( Vector3D, Vector3D, z,y,x );
SWIZZLE3( Vector3D, Vector3D, z,y,y );
SWIZZLE3( Vector3D, Vector3D, z,y,z );
SWIZZLE3( Vector3D, Vector3D, z,z,x );
SWIZZLE3( Vector3D, Vector3D, z,z,y );
SWIZZLE3( Vector3D, Vector3D, z,z,z );

SWIZZLE4( Vector3D, Vector4D, x,x,x,x );
SWIZZLE4( Vector3D, Vector4D, x,x,x,y );
SWIZZLE4( Vector3D, Vector4D, x,x,x,z );
SWIZZLE4( Vector3D, Vector4D, x,x,y,x );
SWIZZLE4( Vector3D, Vector4D, x,x,y,y );
SWIZZLE4( Vector3D, Vector4D, x,x,y,z );
SWIZZLE4( Vector3D, Vector4D, x,x,z,x );
SWIZZLE4( Vector3D, Vector4D, x,x,z,y );
SWIZZLE4( Vector3D, Vector4D, x,x,z,z );
SWIZZLE4( Vector3D, Vector4D, x,y,x,x );
SWIZZLE4( Vector3D, Vector4D, x,y,x,y );
SWIZZLE4( Vector3D, Vector4D, x,y,x,z );
SWIZZLE4( Vector3D, Vector4D, x,y,y,x );
SWIZZLE4( Vector3D, Vector4D, x,y,y,y );
SWIZZLE4( Vector3D, Vector4D, x,y,y,z );
SWIZZLE4( Vector3D, Vector4D, x,y,z,x );
SWIZZLE4( Vector3D, Vector4D, x,y,z,y );
SWIZZLE4( Vector3D, Vector4D, x,y,z,z );
SWIZZLE4( Vector3D, Vector4D, x,z,x,x );
SWIZZLE4( Vector3D, Vector4D, x,z,x,y );
SWIZZLE4( Vector3D, Vector4D, x,z,x,z );
SWIZZLE4( Vector3D, Vector4D, x,z,y,x );
SWIZZLE4( Vector3D, Vector4D, x,z,y,y );
SWIZZLE4( Vector3D, Vector4D, x,z,y,z );
SWIZZLE4( Vector3D, Vector4D, x,z,z,x );
SWIZZLE4( Vector3D, Vector4D, x,z,z,y );
SWIZZLE4( Vector3D, Vector4D, x,z,z,z );

SWIZZLE4( Vector3D, Vector4D, y,x,x,x );
SWIZZLE4( Vector3D, Vector4D, y,x,x,y );
SWIZZLE4( Vector3D, Vector4D, y,x,x,z );
SWIZZLE4( Vector3D, Vector4D, y,x,y,x );
SWIZZLE4( Vector3D, Vector4D, y,x,y,y );
SWIZZLE4( Vector3D, Vector4D, y,x,y,z );
SWIZZLE4( Vector3D, Vector4D, y,x,z,x );
SWIZZLE4( Vector3D, Vector4D, y,x,z,y );
SWIZZLE4( Vector3D, Vector4D, y,x,z,z );
SWIZZLE4( Vector3D, Vector4D, y,y,x,x );
SWIZZLE4( Vector3D, Vector4D, y,y,x,y );
SWIZZLE4( Vector3D, Vector4D, y,y,x,z );
SWIZZLE4( Vector3D, Vector4D, y,y,y,x );
SWIZZLE4( Vector3D, Vector4D, y,y,y,y );
SWIZZLE4( Vector3D, Vector4D, y,y,y,z );
SWIZZLE4( Vector3D, Vector4D, y,y,z,x );
SWIZZLE4( Vector3D, Vector4D, y,y,z,y );
SWIZZLE4( Vector3D, Vector4D, y,y,z,z );
SWIZZLE4( Vector3D, Vector4D, y,z,x,x );
SWIZZLE4( Vector3D, Vector4D, y,z,x,y );
SWIZZLE4( Vector3D, Vector4D, y,z,x,z );
SWIZZLE4( Vector3D, Vector4D, y,z,y,x );
SWIZZLE4( Vector3D, Vector4D, y,z,y,y );
SWIZZLE4( Vector3D, Vector4D, y,z,y,z );
SWIZZLE4( Vector3D, Vector4D, y,z,z,x );
SWIZZLE4( Vector3D, Vector4D, y,z,z,y );
SWIZZLE4( Vector3D, Vector4D, y,z,z,z );

SWIZZLE4( Vector3D, Vector4D, z,x,x,x );
SWIZZLE4( Vector3D, Vector4D, z,x,x,y );
SWIZZLE4( Vector3D, Vector4D, z,x,x,z );
SWIZZLE4( Vector3D, Vector4D, z,x,y,x );
SWIZZLE4( Vector3D, Vector4D, z,x,y,y );
SWIZZLE4( Vector3D, Vector4D, z,x,y,z );
SWIZZLE4( Vector3D, Vector4D, z,x,z,x );
SWIZZLE4( Vector3D, Vector4D, z,x,z,y );
SWIZZLE4( Vector3D, Vector4D, z,x,z,z );
SWIZZLE4( Vector3D, Vector4D, z,y,x,x );
SWIZZLE4( Vector3D, Vector4D, z,y,x,y );
SWIZZLE4( Vector3D, Vector4D, z,y,x,z );
SWIZZLE4( Vector3D, Vector4D, z,y,y,x );
SWIZZLE4( Vector3D, Vector4D, z,y,y,y );
SWIZZLE4( Vector3D, Vector4D, z,y,y,z );
SWIZZLE4( Vector3D, Vector4D, z,y,z,x );
SWIZZLE4( Vector3D, Vector4D, z,y,z,y );
SWIZZLE4( Vector3D, Vector4D, z,y,z,z );
SWIZZLE4( Vector3D, Vector4D, z,z,x,x );
SWIZZLE4( Vector3D, Vector4D, z,z,x,y );
SWIZZLE4( Vector3D, Vector4D, z,z,x,z );
SWIZZLE4( Vector3D, Vector4D, z,z,y,x );
SWIZZLE4( Vector3D, Vector4D, z,z,y,y );
SWIZZLE4( Vector3D, Vector4D, z,z,y,z );
SWIZZLE4( Vector3D, Vector4D, z,z,z,x );
SWIZZLE4( Vector3D, Vector4D, z,z,z,y );
SWIZZLE4( Vector3D, Vector4D, z,z,z,z );
// - ------------------------------------------------------------------------------------------ - //
#undef SWIZZLE4
#undef SWIZZLE3
#undef SWIZZLE2
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D ClosestPointOnLine( const Vector2D& A, const Vector2D& B, const Vector2D& P ) {
	Vector2D Line = B - A;
	Vector2D LineNormal = Line;
	Real LineLength = LineNormal.NormalizeRet();
	
	Vector2D Ray = P - A;
	
	Real DotLength = dot(LineNormal, Ray);
	
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
