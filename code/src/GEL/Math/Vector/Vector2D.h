// - ------------------------------------------------------------------------------------------ - //
// Vector2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector2D_H__
#define __Geometry_Vector2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <External/boost/operators.hpp>

#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Vector2D& operator _OP_ ( const Vector2D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Vector2D& operator _OP_ ( const Real& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class Vector2D : 
	boost::additive<Vector2D,
	boost::arithmetic2<Vector2D, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real x, y;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Vector2D Identity;
	static const Vector2D One;
	static const Vector2D Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Vector2D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector2D( const Real& _x, const Real& _y ) :
		x( _x ),
		y( _y )
	{
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& Set( const Real& _x, const Real& _y ) {
		x = _x;
		y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& Set( const Vector2D& _v ) {
		*this = _v;
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
	// Dot Product //
	inline const Real operator * ( const Vector2D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const Vector2D operator - ( ) const {
		return Vector2D( -x, -y );
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
	inline bool operator == ( const Vector2D& _Vs ) const {
		if ( (x - _Vs.x).IsZero() )
			return (y - _Vs.y).IsZero();
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& Normalize() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
	
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
	inline const Vector2D Normal() const {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
		
		Vector2D Result( *this );
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
			return Mag.Sqrt();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Real MagnitudeSquared() const {
		return (x * x) + (y * y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return x.Abs() + y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// No Cross product, as we instead have tangents //
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MinClamp( const Vector2D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MaxClamp( const Vector2D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MinClamp( const Real& _x, const Real& _y ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MaxClamp( const Real& _x, const Real& _y ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Min( const Vector2D& _Vs ) const {
		Vector2D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Max( const Vector2D& _Vs ) const {
		Vector2D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Min( const Real& _x, const Real& _y ) const {
		Vector2D Vec = *this;
		Vec.MinClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Max( const Real& _x, const Real& _y ) const {
		Vector2D Vec = *this;
		Vec.MaxClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const Vector2D& _Vs ) const {
		return ((*this) * _Vs.Tangent()) > Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const Vector2D& _Vs ) const {
		return ((*this) * _Vs.Tangent()) < Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const Vector2D& _Vs ) const {
		return ((*this) * _Vs.Tangent()).IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		return x.IsZero() && y.IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroOrLess() const {
		return x.IsZeroOrLess() && y.IsZeroOrLess();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Return a special vector only with the x or y part that is largest //
	// If you want this normalized, you must normalize it yourself, appropriately //
	inline const Vector2D AxisAligned() const {
		if ( x.Abs() >= y.Abs() )
			return Vector2D( x, 0 );
		else
			return Vector2D( 0, y );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Specific Functions that apply to this type //
	// - -------------------------------------------------------------------------------------- - //
	// Normally I have clockwise and counterclockwise variants, but potential changes in the //
	//   Mapping co-ordinates make counterclockwise clockwise, and vice versa.  So instead, use //
	//   Tangent() and -Tangent() for the respected sides. //
	inline const Vector2D Tangent() const {
		return Vector2D( y, -x );
	}
	// - -------------------------------------------------------------------------------------- - //
	// A 45 degree rotation of a vector.  Negating doesn't flip this, you want the -Tangent() of //
	//   the rotation. i.e. -v.Rotate45().Tangent().  Alternatively, RotateNegative45() does this //
	inline const Vector2D Rotate45() const {
		return Vector2D( x + y, y - x ) * Real::Sin45;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D RotateNegative45() const {
		return Vector2D( x - y, y + x ) * Real::Sin45;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D FlipX() {
		return Vector2D( -x, y );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D FlipY() {
		return Vector2D( x, -y );
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Explicit Conversion Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const class Vector3D ToVector3D() const;
	inline const class Vector4D ToVector4D() const;
	inline const class Vector3D ToHomoVector3D() const;
	inline const class Vector4D ToHomoVector4D() const;

	
	inline const class Matrix2x1& ToMatrix2x1() const;
	inline const class Matrix1x2& ToMatrix1x2() const;
//	inline const class Matrix3x1& ToMatrix3x1() const;
//	inline const class Matrix1x3& ToMatrix1x3() const;
//	inline const class Matrix3x1& ToMatrix4x1() const;
//	inline const class Matrix1x3& ToMatrix1x4() const;
	
	inline const class ScalarVector2D& ToScalarVector() const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Projection //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D ApplyMatrix( const class Matrix2x2& ) const;
	inline const Vector2D ApplyMatrix( const class Matrix3x3& ) const;
//	inline const Vector2D ApplyMatrix( const class Matrix2x3& ) const;
//	inline const Vector2D ApplyMatrix( const class Matrix3x2& ) const;
	inline const Vector2D ApplyMatrix( const class Matrix4x4& ) const;
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D operator - ( const Real& a, const Vector2D& b ) {
	Vector2D Ret( a - b.x, a - b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector2D operator / ( const Real& a, const Vector2D& b ) {
	Vector2D Ret( a / b.x, a / b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Vector2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
