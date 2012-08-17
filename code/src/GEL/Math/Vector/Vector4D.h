// - ------------------------------------------------------------------------------------------ - //
// Vector4D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector4D_H__
#define __Geometry_Vector4D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <External/boost/operators.hpp>

#include "../Real.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Vector4D& operator _OP_ ( const Vector4D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		z _OP_ _Vs.z; \
		w _OP_ _Vs.w; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Vector4D& operator _OP_ ( const Real& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		z _OP_ _Vs; \
		w _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class Vector4D : 
	boost::additive< Vector4D,
	boost::arithmetic2< Vector4D, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real x, y, z, w;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Vector4D Identity;
	static const Vector4D One;
	static const Vector4D Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Vector4D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector4D( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) :
		x( _x ),
		y( _y ),
		z( _z ),
		w( _w )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& Set( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators - The rest will be handled by Boost //
	// - -------------------------------------------------------------------------------------- - //
	// Vector //
	OVERLOAD_SYMBOLEQUALS_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( -= );
	// OVERLOAD_SYMBOLEQUALS_OPERATOR( *= );
	// OVERLOAD_SYMBOLEQUALS_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const Vector4D& _Vs ) const {
		if ( (x - _Vs.x).IsZero() )
			if ( (y - _Vs.y).IsZero() )
				if ( (z - _Vs.z).IsZero() )
					return (w - _Vs.w).IsZero();
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Dot Product //
	inline const Real dot( const Vector4D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y) + (z * _Vs.z) + (w * _Vs.w);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Real dot( const Vector4D& a, const Vector4D& b ) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Component-wise Multipy (no longer dot product) //
//	inline const Vector4D operator * ( const Vector4D& _Vs ) const {
//		return Vector4D( (x * _Vs.x), (y * _Vs.y), (z * _Vs.z), (w * _Vs.w) );
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Like the GLSL parallel, blends between two vectors by alpha (0 = a returned, 1 = b returned) //
	inline const Vector4D mix( const Vector4D& _Vs, const Real Alpha ) const {
		return ((*this) * (Real::One - Alpha)) + (_Vs * Alpha);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Vector4D mix( const Vector4D& a, const Vector4D& b, const Real Alpha ) {
		return (a * (Real::One - Alpha)) + (b * Alpha);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const Vector4D operator - ( ) const {
		return Vector4D( -x, -y, -z, -w );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real SumOf() const {
		return x+y+z+w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real ProductOf() const {
		return x*y*z*w;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Scalar //
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( -= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& Normalize() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector4D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real NormalizeRet() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Real::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Vector4D Normal() const {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector4D::Zero;
		
		Vector4D Result( *this );
		Result /= Mag;
		
		return Result;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const Real Magnitude() const {
		Real Mag( MagnitudeSquared() );
//		Mag = Mag.Sqrt();
	
		if ( Mag.IsZeroOrLess() )
			return Real::Zero;
		else
			return Mag.Sqrt_();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Real MagnitudeSquared() const {
		return (x * x) + (y * y) + (z * z) + (w * w);
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return x.Abs() + y.Abs() + z.Abs() + w.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MinClamp( const Vector4D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		if ( z < _Vs.z )
			z = _Vs.z;
		if ( w < _Vs.w )
			w = _Vs.w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MaxClamp( const Vector4D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		if ( z > _Vs.z )
			z = _Vs.z;
		if ( w > _Vs.w )
			w = _Vs.w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MinClamp( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		if ( z < _z )
			z = _z;
		if ( w < _w )
			w = _w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MaxClamp( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		if ( z > _z )
			z = _z;
		if ( w > _w )
			w = _w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Min( const Vector4D& _Vs ) const {
		Vector4D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Max( const Vector4D& _Vs ) const {
		Vector4D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Min( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) const {
		Vector4D Vec = *this;
		Vec.MinClamp( _x, _y, _z, _w );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Max( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) const {
		Vector4D Vec = *this;
		Vec.MaxClamp( _x, _y, _z, _w );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const Vector4D& _Vs ) const {
		return dot((*this), _Vs) > Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const Vector4D& _Vs ) const {
		return dot((*this), _Vs) < Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const Vector4D& _Vs ) const {
		return dot((*this), _Vs).IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		return x.IsZero() && y.IsZero() && z.IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroOrLess() const {
		return x.IsZeroOrLess() && y.IsZeroOrLess() && z.IsZeroOrLess();
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Explicit Conversion Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const class Vector2D ToVector2D() const;
	inline const class Vector3D ToVector3D() const;
	
//	inline const class Matrix2x1& ToMatrix2x1() const;
//	inline const class Matrix1x2& ToMatrix1x2() const;
//	inline const class Matrix3x1& ToMatrix3x1() const;
//	inline const class Matrix1x3& ToMatrix1x3() const;
	inline const class Matrix4x1& ToMatrix4x1() const;
	inline const class Matrix1x4& ToMatrix1x4() const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Projection //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D ApplyMatrix( const class Matrix4x4& ) const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D XAxis() const {
		return Vector4D( x, Real::Zero, Real::Zero, Real::Zero );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D YAxis() const {
		return Vector4D( Real::Zero, y, Real::Zero, Real::Zero );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D ZAxis() const {
		return Vector4D( Real::Zero, Real::Zero, z, Real::Zero );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D WAxis() const {
		return Vector4D( Real::Zero, Real::Zero, Real::Zero, w );
	}
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector4D operator - ( const Real& a, const Vector4D& b ) {
	Vector4D Ret( a - b.x, a - b.y, a - b.z, a - b.w );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector4D operator / ( const Real& a, const Vector4D& b ) {
	Vector4D Ret( a / b.x, a / b.y, a / b.z, a / b.w );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //

// -- ---------------------------------------------------------------------------------------- -- //
// External Vector Operations, for GLSL familiar syntax //
// -- ---------------------------------------------------------------------------------------- -- //
inline const Real dot( const Vector4D& a, const Vector4D& b ) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector4D mix( const Vector4D& a, const Vector4D& b, const Real Alpha ) {
	return (a * (Real::One - Alpha)) + (b * Alpha);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Vector4D_H__ //
// - ------------------------------------------------------------------------------------------ - //
