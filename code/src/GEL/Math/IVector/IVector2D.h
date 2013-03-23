// - ------------------------------------------------------------------------------------------ - //
// IVector2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_IVector2D_H__
#define __Geometry_IVector2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <External/boost/operators.hpp>

#include <Math/Integer.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const IVector2D& operator _OP_ ( const IVector2D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const IVector2D& operator _OP_ ( const Integer& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class IVector2D : 
	boost::additive<IVector2D,
	boost::multiplicative<IVector2D,
	boost::arithmetic2<IVector2D, Integer
	> > >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Integer x, y;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const IVector2D Identity;
	static const IVector2D One;
	static const IVector2D Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline IVector2D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline IVector2D( const Integer& _x, const Integer& _y ) :
		x( _x ),
		y( _y )
	{
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& Set( const Integer& _x, const Integer& _y ) {
		x = _x;
		y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& Set( const IVector2D& _v ) {
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
	OVERLOAD_SYMBOLEQUALS_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //
	// Dot Product //
	inline const Integer dot( const IVector2D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Integer dot( const IVector2D& a, const IVector2D& b ) {
		return (a.x * b.x) + (a.y * b.y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Component-wise Multipy (no longer dot product) //
//	inline const IVector2D operator * ( const IVector2D& _Vs ) const {
//		return IVector2D( (x * _Vs.x), (y * _Vs.y) );
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Like the GLSL parallel, blends between two vectors by alpha (0 = a returned, 1 = b returned) //
//	inline const IVector2D mix( const IVector2D& _Vs, const Integer Alpha ) const {
//		return ((*this) * (Integer::One - Alpha)) + (_Vs * Alpha);
//	}
	// - -------------------------------------------------------------------------------------- - //
//	inline static const IVector2D mix( const IVector2D& a, const IVector2D& b, const Integer Alpha ) {
//		return (a * (Integer::One - Alpha)) + (b * Alpha);
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const IVector2D operator - ( ) const {
		return IVector2D( -x, -y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Integer SumOf() const {
		return x+y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Integer ProductOf() const {
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
	inline bool operator == ( const IVector2D& _Vs ) const {
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
//	inline const IVector2D& Normalize() {
//		Integer Mag( Magnitude() );
//	
//		if ( Mag.IsZeroOrLess() )
//			return IVector2D::Zero;
//	
//		return *this /= Mag;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
//	inline const Integer NormalizeRet() {
//		Integer Mag( Magnitude() );
//	
//		if ( Mag.IsZeroOrLess() )
//			return Integer::Zero;
//	
//		*this /= Mag;
//		return Mag;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
//	inline const IVector2D Normal() const {
//		Integer Mag( Magnitude() );
//	
//		if ( Mag.IsZeroOrLess() )
//			return IVector2D::Zero;
//		
//		IVector2D Result( *this );
//		Result /= Mag;
//		
//		return Result;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const Integer Magnitude() const {
		Integer Mag( MagnitudeSquared() );
//		Mag = Mag.Sqrt();
	
		if ( Mag.IsZeroOrLess() )
			return Integer::Zero;
		else
			return Mag.Sqrt_();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Integer MagnitudeSquared() const {
		return (x * x) + (y * y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Manhattan Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& ManhattanNormalize() {
		Integer Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return IVector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Integer ManhattanNormalizeRet() {
		Integer Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return Integer::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const IVector2D ManhattanNormal() const {
		Integer Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return IVector2D::Zero;
		
		IVector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Integer Manhattan() const {
		return x.Abs() + y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Maxitude Functions -- Chebyshev Distance, Uniform Normal -- http://en.wikipedia.org/wiki/Chebyshev_distance //
	// http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Maximum_norm_.28special_case_of:_infinity_norm.2C_uniform_norm.2C_or_supremum_norm.29 //
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& MaxitudeNormalize() {
		Integer Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return IVector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Integer MaxitudeNormalizeRet() {
		Integer Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Integer::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const IVector2D MaxitudeNormal() const {
		Integer Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return IVector2D::Zero;
		
		IVector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The greatest absolute value part //
	inline const Integer Maxitude() const {
		return x.Abs() > y.Abs() ? x.Abs() : y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Minitude Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& MinitudeNormalize() {
		Integer Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return IVector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Integer MinitudeNormalizeRet() {
		Integer Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Integer::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const IVector2D MinitudeNormal() const {
		Integer Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return IVector2D::Zero;
		
		IVector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The smallest absolute value part //
	inline const Integer Minitude() const {
		return x.Abs() < y.Abs() ? x.Abs() : y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// No Cross product, as we instead have tangents //
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& MinClamp( const IVector2D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& MaxClamp( const IVector2D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& MinClamp( const Integer& _x, const Integer& _y ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D& MaxClamp( const Integer& _x, const Integer& _y ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D Min( const IVector2D& _Vs ) const {
		IVector2D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D Max( const IVector2D& _Vs ) const {
		IVector2D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D Min( const Integer& _x, const Integer& _y ) const {
		IVector2D Vec = *this;
		Vec.MinClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D Max( const Integer& _x, const Integer& _y ) const {
		IVector2D Vec = *this;
		Vec.MaxClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const IVector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()) > Integer::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const IVector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()) < Integer::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const IVector2D& _Vs ) const {
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
	inline const IVector2D AxisAligned() const {
		if ( x.Abs() >= y.Abs() )
			return IVector2D( x, 0 );
		else
			return IVector2D( 0, y );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Specific Functions that apply to this type //
	// - -------------------------------------------------------------------------------------- - //
	// Normally I have clockwise and counterclockwise variants, but potential changes in the //
	//   Mapping co-ordinates make counterclockwise clockwise, and vice versa.  So instead, use //
	//   Tangent() and -Tangent() for the respected sides. //
	inline const IVector2D Tangent() const {
		return IVector2D( y, -x );
	}
	// - -------------------------------------------------------------------------------------- - //
	// A 45 degree rotation of a vector.  Negating doesn't flip this, you want the -Tangent() of //
	//   the rotation. i.e. -v.Rotate45().Tangent().  Alternatively, RotateNegative45() does this //
//	inline const IVector2D Rotate45() const {
//		return IVector2D( x + y, y - x ) * Integer::Sine45;
//	}
	// - -------------------------------------------------------------------------------------- - //
//	inline const IVector2D RotateNegative45() const {
//		return IVector2D( x - y, y + x ) * Integer::Sine45;
//	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
//	inline static const IVector2D Angle( const Integer _Angle ) {
//		return IVector2D( Integer::Sin(_Angle), -Integer::Cos(_Angle) );
//	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D FlipX() {
		return IVector2D( -x, y );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IVector2D FlipY() {
		return IVector2D( x, -y );
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
inline const IVector2D operator - ( const Integer& a, const IVector2D& b ) {
	IVector2D Ret( a - b.x, a - b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const IVector2D operator / ( const Integer& a, const IVector2D& b ) {
	IVector2D Ret( a / b.x, a / b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //

// -- ---------------------------------------------------------------------------------------- -- //
// External Vector Operations, for GLSL familiar syntax //
// -- ---------------------------------------------------------------------------------------- -- //
inline const Integer dot( const IVector2D& a, const IVector2D& b ) {
	return (a.x * b.x) + (a.y * b.y);
}
// -- ---------------------------------------------------------------------------------------- -- //
//inline const IVector2D mix( const IVector2D& a, const IVector2D& b, const Integer Alpha ) {
//	return (a * (Integer::One - Alpha)) + (b * Alpha);
//}
// -- ---------------------------------------------------------------------------------------- -- //


// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_IVector2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
