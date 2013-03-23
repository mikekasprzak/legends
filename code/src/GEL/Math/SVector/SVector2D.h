// - ------------------------------------------------------------------------------------------ - //
// SVector2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_SVector2D_H__
#define __Geometry_SVector2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <External/boost/operators.hpp>

#include <Math/SInteger.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const SVector2D& operator _OP_ ( const SVector2D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const SVector2D& operator _OP_ ( const SInteger& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class SVector2D : 
	boost::additive<SVector2D,
	boost::arithmetic2<SVector2D, SInteger
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	SInteger x, y;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const SVector2D Identity;
	static const SVector2D One;
	static const SVector2D Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline SVector2D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline SVector2D( const SInteger& _x, const SInteger& _y ) :
		x( _x ),
		y( _y )
	{
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& Set( const SInteger& _x, const SInteger& _y ) {
		x = _x;
		y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& Set( const SVector2D& _v ) {
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
	inline const SInteger dot( const SVector2D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const SInteger dot( const SVector2D& a, const SVector2D& b ) {
		return (a.x * b.x) + (a.y * b.y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Component-wise Multipy (no longer dot product) //
//	inline const SVector2D operator * ( const SVector2D& _Vs ) const {
//		return SVector2D( (x * _Vs.x), (y * _Vs.y) );
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Like the GLSL parallel, blends between two vectors by alpha (0 = a returned, 1 = b returned) //
//	inline const SVector2D mix( const SVector2D& _Vs, const SInteger Alpha ) const {
//		return ((*this) * (SInteger::One - Alpha)) + (_Vs * Alpha);
//	}
	// - -------------------------------------------------------------------------------------- - //
//	inline static const SVector2D mix( const SVector2D& a, const SVector2D& b, const SInteger Alpha ) {
//		return (a * (SInteger::One - Alpha)) + (b * Alpha);
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const SVector2D operator - ( ) const {
		return SVector2D( -x, -y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const SInteger SumOf() const {
		return x+y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SInteger ProductOf() const {
		return x*y;
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
	inline bool operator == ( const SVector2D& _Vs ) const {
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
//	inline const SVector2D& Normalize() {
//		SInteger Mag( Magnitude() );
//	
//		if ( Mag.IsZeroOrLess() )
//			return SVector2D::Zero;
//	
//		return *this /= Mag;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
//	inline const SInteger NormalizeRet() {
//		SInteger Mag( Magnitude() );
//	
//		if ( Mag.IsZeroOrLess() )
//			return SInteger::Zero;
//	
//		*this /= Mag;
//		return Mag;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
//	inline const SVector2D Normal() const {
//		SInteger Mag( Magnitude() );
//	
//		if ( Mag.IsZeroOrLess() )
//			return SVector2D::Zero;
//		
//		SVector2D Result( *this );
//		Result /= Mag;
//		
//		return Result;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const SInteger Magnitude() const {
		SInteger Mag( MagnitudeSquared() );
//		Mag = Mag.Sqrt();
	
		if ( Mag.IsZeroOrLess() )
			return SInteger::Zero;
		else
			return Mag.Sqrt_();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const SInteger MagnitudeSquared() const {
		return (x * x) + (y * y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Manhattan Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& ManhattanNormalize() {
		SInteger Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return SVector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const SInteger ManhattanNormalizeRet() {
		SInteger Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return SInteger::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const SVector2D ManhattanNormal() const {
		SInteger Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return SVector2D::Zero;
		
		SVector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const SInteger Manhattan() const {
		return x.Abs() + y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Maxitude Functions -- Chebyshev Distance, Uniform Normal -- http://en.wikipedia.org/wiki/Chebyshev_distance //
	// http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Maximum_norm_.28special_case_of:_infinity_norm.2C_uniform_norm.2C_or_supremum_norm.29 //
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& MaxitudeNormalize() {
		SInteger Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return SVector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const SInteger MaxitudeNormalizeRet() {
		SInteger Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return SInteger::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const SVector2D MaxitudeNormal() const {
		SInteger Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return SVector2D::Zero;
		
		SVector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The greatest absolute value part //
	inline const SInteger Maxitude() const {
		return x.Abs() > y.Abs() ? x.Abs() : y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Minitude Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& MinitudeNormalize() {
		SInteger Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return SVector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const SInteger MinitudeNormalizeRet() {
		SInteger Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return SInteger::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const SVector2D MinitudeNormal() const {
		SInteger Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return SVector2D::Zero;
		
		SVector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The smallest absolute value part //
	inline const SInteger Minitude() const {
		return x.Abs() < y.Abs() ? x.Abs() : y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// No Cross product, as we instead have tangents //
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& MinClamp( const SVector2D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& MaxClamp( const SVector2D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& MinClamp( const SInteger& _x, const SInteger& _y ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D& MaxClamp( const SInteger& _x, const SInteger& _y ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D Min( const SVector2D& _Vs ) const {
		SVector2D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D Max( const SVector2D& _Vs ) const {
		SVector2D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D Min( const SInteger& _x, const SInteger& _y ) const {
		SVector2D Vec = *this;
		Vec.MinClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D Max( const SInteger& _x, const SInteger& _y ) const {
		SVector2D Vec = *this;
		Vec.MaxClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const SVector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()) > SInteger::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const SVector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()) < SInteger::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const SVector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()).IsZero();
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
	inline const SVector2D AxisAligned() const {
		if ( x.Abs() >= y.Abs() )
			return SVector2D( x, 0 );
		else
			return SVector2D( 0, y );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Specific Functions that apply to this type //
	// - -------------------------------------------------------------------------------------- - //
	// Normally I have clockwise and counterclockwise variants, but potential changes in the //
	//   Mapping co-ordinates make counterclockwise clockwise, and vice versa.  So instead, use //
	//   Tangent() and -Tangent() for the respected sides. //
	inline const SVector2D Tangent() const {
		return SVector2D( y, -x );
	}
	// - -------------------------------------------------------------------------------------- - //
	// A 45 degree rotation of a vector.  Negating doesn't flip this, you want the -Tangent() of //
	//   the rotation. i.e. -v.Rotate45().Tangent().  Alternatively, RotateNegative45() does this //
//	inline const SVector2D Rotate45() const {
//		return SVector2D( x + y, y - x ) * SInteger::Sine45;
//	}
	// - -------------------------------------------------------------------------------------- - //
//	inline const SVector2D RotateNegative45() const {
//		return SVector2D( x - y, y + x ) * SInteger::Sine45;
//	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
//	inline static const SVector2D Angle( const SInteger _Angle ) {
//		return SVector2D( SInteger::Sin(_Angle), -SInteger::Cos(_Angle) );
//	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D FlipX() {
		return SVector2D( -x, y );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const SVector2D FlipY() {
		return SVector2D( x, -y );
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Explicit Conversion Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const class Vector3D ToVector3D() const;
	inline const class Vector4D ToVector4D() const;
	inline const class Vector3D ToHomoVector3D() const;
	inline const class Vector4D ToHomoVector4D() const;
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const SVector2D operator - ( const SInteger& a, const SVector2D& b ) {
	SVector2D Ret( a - b.x, a - b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const SVector2D operator / ( const SInteger& a, const SVector2D& b ) {
	SVector2D Ret( a / b.x, a / b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //

// -- ---------------------------------------------------------------------------------------- -- //
// External Vector Operations, for GLSL familiar syntax //
// -- ---------------------------------------------------------------------------------------- -- //
inline const SInteger dot( const SVector2D& a, const SVector2D& b ) {
	return (a.x * b.x) + (a.y * b.y);
}
// -- ---------------------------------------------------------------------------------------- -- //
//inline const SVector2D mix( const SVector2D& a, const SVector2D& b, const SInteger Alpha ) {
//	return (a * (SInteger::One - Alpha)) + (b * Alpha);
//}
// -- ---------------------------------------------------------------------------------------- -- //


// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_SVector2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
