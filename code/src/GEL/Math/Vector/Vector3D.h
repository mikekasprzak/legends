// - ------------------------------------------------------------------------------------------ - //
// Vector3D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector3D_H__
#define __Geometry_Vector3D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <External/boost/operators.hpp>

#include "../Real.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Vector3D& operator _OP_ ( const Vector3D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		z _OP_ _Vs.z; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Vector3D& operator _OP_ ( const Real& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		z _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class Vector3D : 
	boost::additive< Vector3D,
	boost::arithmetic2< Vector3D, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real x, y, z;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Vector3D Identity;
	static const Vector3D One;
	static const Vector3D Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Vector3D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector3D( const Real& _x, const Real& _y, const Real& _z ) :
		x( _x ),
		y( _y ),
		z( _z )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& Set( const Real& _x, const Real& _y, const Real& _z ) {
		x = _x;
		y = _y;
		z = _z;
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

	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const Vector3D& _Vs ) const {
		if ( (x - _Vs.x).IsZero() )
			if ( (y - _Vs.y).IsZero() )
				return (z - _Vs.z).IsZero();
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Dot Product //
	inline const Real dot( const Vector3D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y) + (z * _Vs.z);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Real dot( const Vector3D& a, const Vector3D& b ) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Component-wise Multipy (no longer dot product) //
//	inline const Vector3D operator * ( const Vector3D& _Vs ) const {
//		return Vector3D( (x * _Vs.x), (y * _Vs.y), (z * _Vs.z) );
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Cross product //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D cross( const Vector3D& _Vs ) const {
		return Vector3D(
			(y * _Vs.z) - (z * _Vs.y),
			(z * _Vs.x) - (x * _Vs.z),
			(x * _Vs.y) - (y * _Vs.x)
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Vector3D cross( const Vector3D& a, const Vector3D b ) {
		return Vector3D(
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x)
			);
	}
	// - -------------------------------------------------------------------------------------- - //
//	// *note* this is the % sign because it is at the same level as the * and / signs, unlike the //
//	//        ^ sign, which is at the binary logic level (OR, AND, XOR). //
//	inline const Vector3D operator % ( const Vector3D& _Vs ) const {
//		return Vector3D(
//			(y * _Vs.z) - (z * _Vs.y),
//			(z * _Vs.x) - (x * _Vs.z),
//			(x * _Vs.y) - (y * _Vs.x)
//			);
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Like the GLSL parallel, blends between two vectors by alpha (0 = a returned, 1 = b returned) //
	inline const Vector3D mix( const Vector3D& _Vs, const Real Alpha ) const {
		return ((*this) * (Real::One - Alpha)) + (_Vs * Alpha);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Vector3D mix( const Vector3D& a, const Vector3D& b, const Real Alpha ) {
		return (a * (Real::One - Alpha)) + (b * Alpha);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const Vector3D operator - ( ) const {
		return Vector3D( -x, -y, -z );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Scale( const Vector3D& Vs ) const {
		return Vector3D( x * Vs.x, y * Vs.y, z * Vs.z );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real SumOf() const {
		return x+y+z;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real ProductOf() const {
		return x*y*z;
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
	inline Vector3D& Normalize() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return *this = Vector3D::Zero;
	
		return *this = *this / Mag;
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
	inline const Vector3D Normal() const {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector3D::Zero;
		
		Vector3D Result( *this );
		Result /= Mag;
		
		return Result;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Variation, make all axis of length 1, unless the axis is a zero //
	inline Vector3D& AxisNormalize() {
		*this = Vector3D( x.Normal(), y.Normal(), z.Normal() );
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, returns all axis of length 1, unless the axis is a zero //
	inline const Vector3D AxisNormal() const {
		return Vector3D( x.Normal(), y.Normal(), z.Normal() );
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
		return (x * x) + (y * y) + (z * z);
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return x.Abs() + y.Abs() + z.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MinClamp( const Vector3D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		if ( z < _Vs.z )
			z = _Vs.z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MaxClamp( const Vector3D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		if ( z > _Vs.z )
			z = _Vs.z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MinClamp( const Real& _x, const Real& _y, const Real& _z ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		if ( z < _z )
			z = _z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MaxClamp( const Real& _x, const Real& _y, const Real& _z ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		if ( z > _z )
			z = _z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Min( const Vector3D& _Vs ) const {
		Vector3D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Max( const Vector3D& _Vs ) const {
		Vector3D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Min( const Real& _x, const Real& _y, const Real& _z ) const {
		Vector3D Vec = *this;
		Vec.MinClamp( _x, _y, _z );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Max( const Real& _x, const Real& _y, const Real& _z ) const {
		Vector3D Vec = *this;
		Vec.MaxClamp( _x, _y, _z );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const Vector3D& _Vs ) const {
		return dot((*this), _Vs) > Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const Vector3D& _Vs ) const {
		return dot((*this), _Vs) < Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const Vector3D& _Vs ) const {
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
	// Returns true if this vector is axis aligned, but false if a zero vector //
	inline const bool IsAxisAligned() const {
		int Zeroes = 0;
		if ( x.IsZero() )
			Zeroes++;
		if ( y.IsZero() )
			Zeroes++;
		if ( z.IsZero() )
			Zeroes++;
			
		return Zeroes == 2;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Give me a legal Tangent vector to this one. Does not guarentee anything else about it. //
	inline const Vector3D Tangent() const {
		Vector3D Ret( 1,0,0 );
		if ( IsAxisAligned() ) {
			Ret = Vector3D( Real::Sine45, Real::Sine45, 0 );
		}
		
//		return cross(Ret,*this);
		return cross(cross(Ret,*this),*this);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// WARNING: A limit of 64 ToString calls can be made at a time, otherwise returned values may be bad //
	inline const char* ToString() const {
		static char Text[64][128];		// 64 slots, 128 chars long (8,192 bytes). An Int is 10 chars long max. //
		static int CurrentText = 0;
		CurrentText++;
		CurrentText &= 63;
		
		safe_sprintf( Text[CurrentText], sizeof(Text[CurrentText]), "%f,%f,%f", x.ToFloat(), y.ToFloat(), z.ToFloat() );
		return Text[CurrentText];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Explicit Conversion Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const class Vector2D ToVector2D() const;
	inline const class Vector4D ToVector4D() const;
	inline const class Vector3D ToHomoVector3D() const;
	inline const class Vector4D ToHomoVector4D() const;
	
//	inline const class Matrix2x1& ToMatrix2x1() const;
//	inline const class Matrix1x2& ToMatrix1x2() const;
	inline const class Matrix3x1& ToMatrix3x1() const;
	inline const class Matrix1x3& ToMatrix1x3() const;
	inline const class Matrix4x1 ToMatrix4x1() const;
	inline const class Matrix1x4 ToMatrix1x4() const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Projection //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D ApplyMatrix( const class Matrix3x3& ) const;
	inline const Vector3D ApplyMatrix( const class Matrix4x4& ) const;
//	inline const Vector3D ApplyMatrix( const class Matrix4x3& ) const;
//	inline const Vector3D ApplyMatrix( const class Matrix3x4& ) const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D XAxis() const {
		return Vector3D( x, Real::Zero, Real::Zero );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D YAxis() const {
		return Vector3D( Real::Zero, y, Real::Zero );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D ZAxis() const {
		return Vector3D( Real::Zero, Real::Zero, z );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	#define SWIZZLE2_PROTO( _TYPE, _A, _B ) \
		inline const _TYPE _A ## _B () const;
	#define SWIZZLE3_PROTO( _TYPE, _A, _B, _C ) \
		inline const _TYPE _A ## _B ## _C () const;
	#define SWIZZLE4_PROTO( _TYPE, _A, _B, _C, _D ) \
		inline const _TYPE _A ## _B ## _C ## _D() const;
	// - -------------------------------------------------------------------------------------- - //
	#define _SWIZZLE2_PROTO( _TYPE, _A, _B ) \
		inline const _TYPE _ ## _A ## _B () const;
	#define _SWIZZLE3_PROTO( _TYPE, _A, _B, _C ) \
		inline const _TYPE _ ## _A ## _B ## _C () const;
	#define _SWIZZLE4_PROTO( _TYPE, _A, _B, _C, _D ) \
		inline const _TYPE _ ## _A ## _B ## _C ## _D() const;
	// - -------------------------------------------------------------------------------------- - //
	SWIZZLE2_PROTO( Vector2D, x,x );
	SWIZZLE2_PROTO( Vector2D, x,y );
	SWIZZLE2_PROTO( Vector2D, x,z );
	SWIZZLE2_PROTO( Vector2D, y,x );
	SWIZZLE2_PROTO( Vector2D, y,y );
	SWIZZLE2_PROTO( Vector2D, y,z );
	SWIZZLE2_PROTO( Vector2D, z,x );
	SWIZZLE2_PROTO( Vector2D, z,y );
	SWIZZLE2_PROTO( Vector2D, z,z );

	_SWIZZLE2_PROTO( Vector2D, x,x );	// *** //
	_SWIZZLE2_PROTO( Vector2D, x,y );
	_SWIZZLE2_PROTO( Vector2D, x,z );
	_SWIZZLE2_PROTO( Vector2D, x,0 );
	_SWIZZLE2_PROTO( Vector2D, x,1 );
	_SWIZZLE2_PROTO( Vector2D, y,x );	// *** //
	_SWIZZLE2_PROTO( Vector2D, y,y );
	_SWIZZLE2_PROTO( Vector2D, y,z );
	_SWIZZLE2_PROTO( Vector2D, y,0 );
	_SWIZZLE2_PROTO( Vector2D, y,1 );
	_SWIZZLE2_PROTO( Vector2D, z,x );	// *** //
	_SWIZZLE2_PROTO( Vector2D, z,y );
	_SWIZZLE2_PROTO( Vector2D, z,z );
	_SWIZZLE2_PROTO( Vector2D, z,0 );
	_SWIZZLE2_PROTO( Vector2D, z,1 );
	_SWIZZLE2_PROTO( Vector2D, 0,x );	// *** //
	_SWIZZLE2_PROTO( Vector2D, 0,y );
	_SWIZZLE2_PROTO( Vector2D, 0,z );
	_SWIZZLE2_PROTO( Vector2D, 0,0 );
	_SWIZZLE2_PROTO( Vector2D, 0,1 );
	_SWIZZLE2_PROTO( Vector2D, 1,x );	// *** //
	_SWIZZLE2_PROTO( Vector2D, 1,y );
	_SWIZZLE2_PROTO( Vector2D, 1,z );
	_SWIZZLE2_PROTO( Vector2D, 1,0 );
	_SWIZZLE2_PROTO( Vector2D, 1,1 );

	SWIZZLE3_PROTO( Vector3D, x,x,x );
	SWIZZLE3_PROTO( Vector3D, x,x,y );
	SWIZZLE3_PROTO( Vector3D, x,x,z );
	SWIZZLE3_PROTO( Vector3D, x,y,x );
	SWIZZLE3_PROTO( Vector3D, x,y,y );
	SWIZZLE3_PROTO( Vector3D, x,y,z );
	SWIZZLE3_PROTO( Vector3D, x,z,x );
	SWIZZLE3_PROTO( Vector3D, x,z,y );
	SWIZZLE3_PROTO( Vector3D, x,z,z );
	SWIZZLE3_PROTO( Vector3D, y,x,x );
	SWIZZLE3_PROTO( Vector3D, y,x,y );
	SWIZZLE3_PROTO( Vector3D, y,x,z );
	SWIZZLE3_PROTO( Vector3D, y,y,x );
	SWIZZLE3_PROTO( Vector3D, y,y,y );
	SWIZZLE3_PROTO( Vector3D, y,y,z );
	SWIZZLE3_PROTO( Vector3D, y,z,x );
	SWIZZLE3_PROTO( Vector3D, y,z,y );
	SWIZZLE3_PROTO( Vector3D, y,z,z );
	SWIZZLE3_PROTO( Vector3D, z,x,x );
	SWIZZLE3_PROTO( Vector3D, z,x,y );
	SWIZZLE3_PROTO( Vector3D, z,x,z );
	SWIZZLE3_PROTO( Vector3D, z,y,x );
	SWIZZLE3_PROTO( Vector3D, z,y,y );
	SWIZZLE3_PROTO( Vector3D, z,y,z );
	SWIZZLE3_PROTO( Vector3D, z,z,x );
	SWIZZLE3_PROTO( Vector3D, z,z,y );
	SWIZZLE3_PROTO( Vector3D, z,z,z );

	_SWIZZLE3_PROTO( Vector3D, x,x,x );	// *** //
	_SWIZZLE3_PROTO( Vector3D, x,x,y );
	_SWIZZLE3_PROTO( Vector3D, x,x,z );
	_SWIZZLE3_PROTO( Vector3D, x,x,0 );
	_SWIZZLE3_PROTO( Vector3D, x,x,1 );
	_SWIZZLE3_PROTO( Vector3D, x,y,x );
	_SWIZZLE3_PROTO( Vector3D, x,y,y );
	_SWIZZLE3_PROTO( Vector3D, x,y,z );
	_SWIZZLE3_PROTO( Vector3D, x,y,0 );
	_SWIZZLE3_PROTO( Vector3D, x,y,1 );
	_SWIZZLE3_PROTO( Vector3D, x,z,x );
	_SWIZZLE3_PROTO( Vector3D, x,z,y );
	_SWIZZLE3_PROTO( Vector3D, x,z,z );
	_SWIZZLE3_PROTO( Vector3D, x,z,0 );
	_SWIZZLE3_PROTO( Vector3D, x,z,1 );
	_SWIZZLE3_PROTO( Vector3D, x,0,x );
	_SWIZZLE3_PROTO( Vector3D, x,0,y );
	_SWIZZLE3_PROTO( Vector3D, x,0,z );
	_SWIZZLE3_PROTO( Vector3D, x,0,0 );
	_SWIZZLE3_PROTO( Vector3D, x,0,1 );
	_SWIZZLE3_PROTO( Vector3D, x,1,x );
	_SWIZZLE3_PROTO( Vector3D, x,1,y );
	_SWIZZLE3_PROTO( Vector3D, x,1,z );
	_SWIZZLE3_PROTO( Vector3D, x,1,0 );
	_SWIZZLE3_PROTO( Vector3D, x,1,1 );
	_SWIZZLE3_PROTO( Vector3D, y,x,x );	// *** //
	_SWIZZLE3_PROTO( Vector3D, y,x,y );
	_SWIZZLE3_PROTO( Vector3D, y,x,z );
	_SWIZZLE3_PROTO( Vector3D, y,x,0 );
	_SWIZZLE3_PROTO( Vector3D, y,x,1 );
	_SWIZZLE3_PROTO( Vector3D, y,y,x );
	_SWIZZLE3_PROTO( Vector3D, y,y,y );
	_SWIZZLE3_PROTO( Vector3D, y,y,z );
	_SWIZZLE3_PROTO( Vector3D, y,y,0 );
	_SWIZZLE3_PROTO( Vector3D, y,y,1 );
	_SWIZZLE3_PROTO( Vector3D, y,z,x );
	_SWIZZLE3_PROTO( Vector3D, y,z,y );
	_SWIZZLE3_PROTO( Vector3D, y,z,z );
	_SWIZZLE3_PROTO( Vector3D, y,z,0 );
	_SWIZZLE3_PROTO( Vector3D, y,z,1 );
	_SWIZZLE3_PROTO( Vector3D, y,0,x );
	_SWIZZLE3_PROTO( Vector3D, y,0,y );
	_SWIZZLE3_PROTO( Vector3D, y,0,z );
	_SWIZZLE3_PROTO( Vector3D, y,0,0 );
	_SWIZZLE3_PROTO( Vector3D, y,0,1 );
	_SWIZZLE3_PROTO( Vector3D, y,1,x );
	_SWIZZLE3_PROTO( Vector3D, y,1,y );
	_SWIZZLE3_PROTO( Vector3D, y,1,z );
	_SWIZZLE3_PROTO( Vector3D, y,1,0 );
	_SWIZZLE3_PROTO( Vector3D, y,1,1 );
	_SWIZZLE3_PROTO( Vector3D, z,x,x );	// *** //
	_SWIZZLE3_PROTO( Vector3D, z,x,y );
	_SWIZZLE3_PROTO( Vector3D, z,x,z );
	_SWIZZLE3_PROTO( Vector3D, z,x,0 );
	_SWIZZLE3_PROTO( Vector3D, z,x,1 );
	_SWIZZLE3_PROTO( Vector3D, z,y,x );
	_SWIZZLE3_PROTO( Vector3D, z,y,y );
	_SWIZZLE3_PROTO( Vector3D, z,y,z );
	_SWIZZLE3_PROTO( Vector3D, z,y,0 );
	_SWIZZLE3_PROTO( Vector3D, z,y,1 );
	_SWIZZLE3_PROTO( Vector3D, z,z,x );
	_SWIZZLE3_PROTO( Vector3D, z,z,y );
	_SWIZZLE3_PROTO( Vector3D, z,z,z );
	_SWIZZLE3_PROTO( Vector3D, z,z,0 );
	_SWIZZLE3_PROTO( Vector3D, z,z,1 );
	_SWIZZLE3_PROTO( Vector3D, z,0,x );
	_SWIZZLE3_PROTO( Vector3D, z,0,y );
	_SWIZZLE3_PROTO( Vector3D, z,0,z );
	_SWIZZLE3_PROTO( Vector3D, z,0,0 );
	_SWIZZLE3_PROTO( Vector3D, z,0,1 );
	_SWIZZLE3_PROTO( Vector3D, z,1,x );
	_SWIZZLE3_PROTO( Vector3D, z,1,y );
	_SWIZZLE3_PROTO( Vector3D, z,1,z );
	_SWIZZLE3_PROTO( Vector3D, z,1,0 );
	_SWIZZLE3_PROTO( Vector3D, z,1,1 );	
	_SWIZZLE3_PROTO( Vector3D, 0,x,x );	// *** //
	_SWIZZLE3_PROTO( Vector3D, 0,x,y );
	_SWIZZLE3_PROTO( Vector3D, 0,x,z );
	_SWIZZLE3_PROTO( Vector3D, 0,x,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,x,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,y,x );
	_SWIZZLE3_PROTO( Vector3D, 0,y,y );
	_SWIZZLE3_PROTO( Vector3D, 0,y,z );
	_SWIZZLE3_PROTO( Vector3D, 0,y,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,y,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,z,x );
	_SWIZZLE3_PROTO( Vector3D, 0,z,y );
	_SWIZZLE3_PROTO( Vector3D, 0,z,z );
	_SWIZZLE3_PROTO( Vector3D, 0,z,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,z,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,0,x );
	_SWIZZLE3_PROTO( Vector3D, 0,0,y );
	_SWIZZLE3_PROTO( Vector3D, 0,0,z );
	_SWIZZLE3_PROTO( Vector3D, 0,0,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,0,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,1,x );
	_SWIZZLE3_PROTO( Vector3D, 0,1,y );
	_SWIZZLE3_PROTO( Vector3D, 0,1,z );
	_SWIZZLE3_PROTO( Vector3D, 0,1,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,1,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,x,x );	// *** //
	_SWIZZLE3_PROTO( Vector3D, 1,x,y );
	_SWIZZLE3_PROTO( Vector3D, 1,x,z );
	_SWIZZLE3_PROTO( Vector3D, 1,x,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,x,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,y,x );
	_SWIZZLE3_PROTO( Vector3D, 1,y,y );
	_SWIZZLE3_PROTO( Vector3D, 1,y,z );
	_SWIZZLE3_PROTO( Vector3D, 1,y,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,y,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,z,x );
	_SWIZZLE3_PROTO( Vector3D, 1,z,y );
	_SWIZZLE3_PROTO( Vector3D, 1,z,z );
	_SWIZZLE3_PROTO( Vector3D, 1,z,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,z,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,0,x );
	_SWIZZLE3_PROTO( Vector3D, 1,0,y );
	_SWIZZLE3_PROTO( Vector3D, 1,0,z );
	_SWIZZLE3_PROTO( Vector3D, 1,0,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,0,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,1,x );
	_SWIZZLE3_PROTO( Vector3D, 1,1,y );
	_SWIZZLE3_PROTO( Vector3D, 1,1,z );
	_SWIZZLE3_PROTO( Vector3D, 1,1,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,1,1 );
	
	SWIZZLE4_PROTO( Vector4D, x,x,x,x );	// *** //
	SWIZZLE4_PROTO( Vector4D, x,x,x,y );
	SWIZZLE4_PROTO( Vector4D, x,x,x,z );
	SWIZZLE4_PROTO( Vector4D, x,x,y,x );
	SWIZZLE4_PROTO( Vector4D, x,x,y,y );
	SWIZZLE4_PROTO( Vector4D, x,x,y,z );
	SWIZZLE4_PROTO( Vector4D, x,x,z,x );
	SWIZZLE4_PROTO( Vector4D, x,x,z,y );
	SWIZZLE4_PROTO( Vector4D, x,x,z,z );
	SWIZZLE4_PROTO( Vector4D, x,y,x,x );
	SWIZZLE4_PROTO( Vector4D, x,y,x,y );
	SWIZZLE4_PROTO( Vector4D, x,y,x,z );
	SWIZZLE4_PROTO( Vector4D, x,y,y,x );
	SWIZZLE4_PROTO( Vector4D, x,y,y,y );
	SWIZZLE4_PROTO( Vector4D, x,y,y,z );
	SWIZZLE4_PROTO( Vector4D, x,y,z,x );
	SWIZZLE4_PROTO( Vector4D, x,y,z,y );
	SWIZZLE4_PROTO( Vector4D, x,y,z,z );
	SWIZZLE4_PROTO( Vector4D, x,z,x,x );
	SWIZZLE4_PROTO( Vector4D, x,z,x,y );
	SWIZZLE4_PROTO( Vector4D, x,z,x,z );
	SWIZZLE4_PROTO( Vector4D, x,z,y,x );
	SWIZZLE4_PROTO( Vector4D, x,z,y,y );
	SWIZZLE4_PROTO( Vector4D, x,z,y,z );
	SWIZZLE4_PROTO( Vector4D, x,z,z,x );
	SWIZZLE4_PROTO( Vector4D, x,z,z,y );
	SWIZZLE4_PROTO( Vector4D, x,z,z,z );
	SWIZZLE4_PROTO( Vector4D, y,x,x,x );	// *** //
	SWIZZLE4_PROTO( Vector4D, y,x,x,y );
	SWIZZLE4_PROTO( Vector4D, y,x,x,z );
	SWIZZLE4_PROTO( Vector4D, y,x,y,x );
	SWIZZLE4_PROTO( Vector4D, y,x,y,y );
	SWIZZLE4_PROTO( Vector4D, y,x,y,z );
	SWIZZLE4_PROTO( Vector4D, y,x,z,x );
	SWIZZLE4_PROTO( Vector4D, y,x,z,y );
	SWIZZLE4_PROTO( Vector4D, y,x,z,z );
	SWIZZLE4_PROTO( Vector4D, y,y,x,x );
	SWIZZLE4_PROTO( Vector4D, y,y,x,y );
	SWIZZLE4_PROTO( Vector4D, y,y,x,z );
	SWIZZLE4_PROTO( Vector4D, y,y,y,x );
	SWIZZLE4_PROTO( Vector4D, y,y,y,y );
	SWIZZLE4_PROTO( Vector4D, y,y,y,z );
	SWIZZLE4_PROTO( Vector4D, y,y,z,x );
	SWIZZLE4_PROTO( Vector4D, y,y,z,y );
	SWIZZLE4_PROTO( Vector4D, y,y,z,z );
	SWIZZLE4_PROTO( Vector4D, y,z,x,x );
	SWIZZLE4_PROTO( Vector4D, y,z,x,y );
	SWIZZLE4_PROTO( Vector4D, y,z,x,z );
	SWIZZLE4_PROTO( Vector4D, y,z,y,x );
	SWIZZLE4_PROTO( Vector4D, y,z,y,y );
	SWIZZLE4_PROTO( Vector4D, y,z,y,z );
	SWIZZLE4_PROTO( Vector4D, y,z,z,x );
	SWIZZLE4_PROTO( Vector4D, y,z,z,y );
	SWIZZLE4_PROTO( Vector4D, y,z,z,z );
	SWIZZLE4_PROTO( Vector4D, z,x,x,x );	// *** //
	SWIZZLE4_PROTO( Vector4D, z,x,x,y );
	SWIZZLE4_PROTO( Vector4D, z,x,x,z );
	SWIZZLE4_PROTO( Vector4D, z,x,y,x );
	SWIZZLE4_PROTO( Vector4D, z,x,y,y );
	SWIZZLE4_PROTO( Vector4D, z,x,y,z );
	SWIZZLE4_PROTO( Vector4D, z,x,z,x );
	SWIZZLE4_PROTO( Vector4D, z,x,z,y );
	SWIZZLE4_PROTO( Vector4D, z,x,z,z );
	SWIZZLE4_PROTO( Vector4D, z,y,x,x );
	SWIZZLE4_PROTO( Vector4D, z,y,x,y );
	SWIZZLE4_PROTO( Vector4D, z,y,x,z );
	SWIZZLE4_PROTO( Vector4D, z,y,y,x );
	SWIZZLE4_PROTO( Vector4D, z,y,y,y );
	SWIZZLE4_PROTO( Vector4D, z,y,y,z );
	SWIZZLE4_PROTO( Vector4D, z,y,z,x );
	SWIZZLE4_PROTO( Vector4D, z,y,z,y );
	SWIZZLE4_PROTO( Vector4D, z,y,z,z );
	SWIZZLE4_PROTO( Vector4D, z,z,x,x );
	SWIZZLE4_PROTO( Vector4D, z,z,x,y );
	SWIZZLE4_PROTO( Vector4D, z,z,x,z );
	SWIZZLE4_PROTO( Vector4D, z,z,y,x );
	SWIZZLE4_PROTO( Vector4D, z,z,y,y );
	SWIZZLE4_PROTO( Vector4D, z,z,y,z );
	SWIZZLE4_PROTO( Vector4D, z,z,z,x );
	SWIZZLE4_PROTO( Vector4D, z,z,z,y );
	SWIZZLE4_PROTO( Vector4D, z,z,z,z );

	_SWIZZLE4_PROTO( Vector4D, x,x,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, x,x,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,x,z );
	_SWIZZLE4_PROTO( Vector4D, x,x,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,z );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,x,z,x );
	_SWIZZLE4_PROTO( Vector4D, x,x,z,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,z,z );
	_SWIZZLE4_PROTO( Vector4D, x,x,z,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,z,1 );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,z );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,z );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, x,y,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,x,z );
	_SWIZZLE4_PROTO( Vector4D, x,y,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,z );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,z,x );
	_SWIZZLE4_PROTO( Vector4D, x,y,z,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,z,z );
	_SWIZZLE4_PROTO( Vector4D, x,y,z,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,z,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,z );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,z );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,1 );
	_SWIZZLE4_PROTO( Vector4D, x,z,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, x,z,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,z,x,z );
	_SWIZZLE4_PROTO( Vector4D, x,z,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,z,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,z,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,z,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,z,y,z );
	_SWIZZLE4_PROTO( Vector4D, x,z,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,z,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,z,z,x );
	_SWIZZLE4_PROTO( Vector4D, x,z,z,y );
	_SWIZZLE4_PROTO( Vector4D, x,z,z,z );
	_SWIZZLE4_PROTO( Vector4D, x,z,z,0 );
	_SWIZZLE4_PROTO( Vector4D, x,z,z,1 );
	_SWIZZLE4_PROTO( Vector4D, x,z,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,z,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,z,0,z );
	_SWIZZLE4_PROTO( Vector4D, x,z,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,z,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,z,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,z,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,z,1,z );
	_SWIZZLE4_PROTO( Vector4D, x,z,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,z,1,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, x,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,x,z );
	_SWIZZLE4_PROTO( Vector4D, x,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,z );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,z,x );
	_SWIZZLE4_PROTO( Vector4D, x,0,z,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,z,z );
	_SWIZZLE4_PROTO( Vector4D, x,0,z,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,z,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,z );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,z );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, x,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,x,z );
	_SWIZZLE4_PROTO( Vector4D, x,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,z );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,z,x );
	_SWIZZLE4_PROTO( Vector4D, x,1,z,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,z,z );
	_SWIZZLE4_PROTO( Vector4D, x,1,z,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,z,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,z );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,z );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, y,x,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,x,z );
	_SWIZZLE4_PROTO( Vector4D, y,x,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,z );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,z,x );
	_SWIZZLE4_PROTO( Vector4D, y,x,z,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,z,z );
	_SWIZZLE4_PROTO( Vector4D, y,x,z,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,z,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,z );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,z );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, y,y,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,x,z );
	_SWIZZLE4_PROTO( Vector4D, y,y,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,z );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,z,x );
	_SWIZZLE4_PROTO( Vector4D, y,y,z,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,z,z );
	_SWIZZLE4_PROTO( Vector4D, y,y,z,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,z,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,z );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,z );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,z,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, y,z,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,z,x,z );
	_SWIZZLE4_PROTO( Vector4D, y,z,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,z,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,z,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,z,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,z,y,z );
	_SWIZZLE4_PROTO( Vector4D, y,z,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,z,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,z,z,x );
	_SWIZZLE4_PROTO( Vector4D, y,z,z,y );
	_SWIZZLE4_PROTO( Vector4D, y,z,z,z );
	_SWIZZLE4_PROTO( Vector4D, y,z,z,0 );
	_SWIZZLE4_PROTO( Vector4D, y,z,z,1 );
	_SWIZZLE4_PROTO( Vector4D, y,z,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,z,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,z,0,z );
	_SWIZZLE4_PROTO( Vector4D, y,z,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,z,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,z,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,z,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,z,1,z );
	_SWIZZLE4_PROTO( Vector4D, y,z,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,z,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, y,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,x,z );
	_SWIZZLE4_PROTO( Vector4D, y,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,z );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,z,x );
	_SWIZZLE4_PROTO( Vector4D, y,0,z,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,z,z );
	_SWIZZLE4_PROTO( Vector4D, y,0,z,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,z,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,z );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,z );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, y,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,x,z );
	_SWIZZLE4_PROTO( Vector4D, y,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,z );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,z,x );
	_SWIZZLE4_PROTO( Vector4D, y,1,z,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,z,z );
	_SWIZZLE4_PROTO( Vector4D, y,1,z,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,z,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,z );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,z );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,1 );
	_SWIZZLE4_PROTO( Vector4D, z,x,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, z,x,x,y );
	_SWIZZLE4_PROTO( Vector4D, z,x,x,z );
	_SWIZZLE4_PROTO( Vector4D, z,x,x,0 );
	_SWIZZLE4_PROTO( Vector4D, z,x,x,1 );
	_SWIZZLE4_PROTO( Vector4D, z,x,y,x );
	_SWIZZLE4_PROTO( Vector4D, z,x,y,y );
	_SWIZZLE4_PROTO( Vector4D, z,x,y,z );
	_SWIZZLE4_PROTO( Vector4D, z,x,y,0 );
	_SWIZZLE4_PROTO( Vector4D, z,x,y,1 );
	_SWIZZLE4_PROTO( Vector4D, z,x,z,x );
	_SWIZZLE4_PROTO( Vector4D, z,x,z,y );
	_SWIZZLE4_PROTO( Vector4D, z,x,z,z );
	_SWIZZLE4_PROTO( Vector4D, z,x,z,0 );
	_SWIZZLE4_PROTO( Vector4D, z,x,z,1 );
	_SWIZZLE4_PROTO( Vector4D, z,x,0,x );
	_SWIZZLE4_PROTO( Vector4D, z,x,0,y );
	_SWIZZLE4_PROTO( Vector4D, z,x,0,z );
	_SWIZZLE4_PROTO( Vector4D, z,x,0,0 );
	_SWIZZLE4_PROTO( Vector4D, z,x,0,1 );
	_SWIZZLE4_PROTO( Vector4D, z,x,1,x );
	_SWIZZLE4_PROTO( Vector4D, z,x,1,y );
	_SWIZZLE4_PROTO( Vector4D, z,x,1,z );
	_SWIZZLE4_PROTO( Vector4D, z,x,1,0 );
	_SWIZZLE4_PROTO( Vector4D, z,x,1,1 );
	_SWIZZLE4_PROTO( Vector4D, z,y,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, z,y,x,y );
	_SWIZZLE4_PROTO( Vector4D, z,y,x,z );
	_SWIZZLE4_PROTO( Vector4D, z,y,x,0 );
	_SWIZZLE4_PROTO( Vector4D, z,y,x,1 );
	_SWIZZLE4_PROTO( Vector4D, z,y,y,x );
	_SWIZZLE4_PROTO( Vector4D, z,y,y,y );
	_SWIZZLE4_PROTO( Vector4D, z,y,y,z );
	_SWIZZLE4_PROTO( Vector4D, z,y,y,0 );
	_SWIZZLE4_PROTO( Vector4D, z,y,y,1 );
	_SWIZZLE4_PROTO( Vector4D, z,y,z,x );
	_SWIZZLE4_PROTO( Vector4D, z,y,z,y );
	_SWIZZLE4_PROTO( Vector4D, z,y,z,z );
	_SWIZZLE4_PROTO( Vector4D, z,y,z,0 );
	_SWIZZLE4_PROTO( Vector4D, z,y,z,1 );
	_SWIZZLE4_PROTO( Vector4D, z,y,0,x );
	_SWIZZLE4_PROTO( Vector4D, z,y,0,y );
	_SWIZZLE4_PROTO( Vector4D, z,y,0,z );
	_SWIZZLE4_PROTO( Vector4D, z,y,0,0 );
	_SWIZZLE4_PROTO( Vector4D, z,y,0,1 );
	_SWIZZLE4_PROTO( Vector4D, z,y,1,x );
	_SWIZZLE4_PROTO( Vector4D, z,y,1,y );
	_SWIZZLE4_PROTO( Vector4D, z,y,1,z );
	_SWIZZLE4_PROTO( Vector4D, z,y,1,0 );
	_SWIZZLE4_PROTO( Vector4D, z,y,1,1 );
	_SWIZZLE4_PROTO( Vector4D, z,z,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, z,z,x,y );
	_SWIZZLE4_PROTO( Vector4D, z,z,x,z );
	_SWIZZLE4_PROTO( Vector4D, z,z,x,0 );
	_SWIZZLE4_PROTO( Vector4D, z,z,x,1 );
	_SWIZZLE4_PROTO( Vector4D, z,z,y,x );
	_SWIZZLE4_PROTO( Vector4D, z,z,y,y );
	_SWIZZLE4_PROTO( Vector4D, z,z,y,z );
	_SWIZZLE4_PROTO( Vector4D, z,z,y,0 );
	_SWIZZLE4_PROTO( Vector4D, z,z,y,1 );
	_SWIZZLE4_PROTO( Vector4D, z,z,z,x );
	_SWIZZLE4_PROTO( Vector4D, z,z,z,y );
	_SWIZZLE4_PROTO( Vector4D, z,z,z,z );
	_SWIZZLE4_PROTO( Vector4D, z,z,z,0 );
	_SWIZZLE4_PROTO( Vector4D, z,z,z,1 );
	_SWIZZLE4_PROTO( Vector4D, z,z,0,x );
	_SWIZZLE4_PROTO( Vector4D, z,z,0,y );
	_SWIZZLE4_PROTO( Vector4D, z,z,0,z );
	_SWIZZLE4_PROTO( Vector4D, z,z,0,0 );
	_SWIZZLE4_PROTO( Vector4D, z,z,0,1 );
	_SWIZZLE4_PROTO( Vector4D, z,z,1,x );
	_SWIZZLE4_PROTO( Vector4D, z,z,1,y );
	_SWIZZLE4_PROTO( Vector4D, z,z,1,z );
	_SWIZZLE4_PROTO( Vector4D, z,z,1,0 );
	_SWIZZLE4_PROTO( Vector4D, z,z,1,1 );
	_SWIZZLE4_PROTO( Vector4D, z,0,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, z,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, z,0,x,z );
	_SWIZZLE4_PROTO( Vector4D, z,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, z,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, z,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, z,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, z,0,y,z );
	_SWIZZLE4_PROTO( Vector4D, z,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, z,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, z,0,z,x );
	_SWIZZLE4_PROTO( Vector4D, z,0,z,y );
	_SWIZZLE4_PROTO( Vector4D, z,0,z,z );
	_SWIZZLE4_PROTO( Vector4D, z,0,z,0 );
	_SWIZZLE4_PROTO( Vector4D, z,0,z,1 );
	_SWIZZLE4_PROTO( Vector4D, z,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, z,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, z,0,0,z );
	_SWIZZLE4_PROTO( Vector4D, z,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, z,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, z,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, z,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, z,0,1,z );
	_SWIZZLE4_PROTO( Vector4D, z,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, z,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, z,1,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, z,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, z,1,x,z );
	_SWIZZLE4_PROTO( Vector4D, z,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, z,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, z,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, z,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, z,1,y,z );
	_SWIZZLE4_PROTO( Vector4D, z,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, z,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, z,1,z,x );
	_SWIZZLE4_PROTO( Vector4D, z,1,z,y );
	_SWIZZLE4_PROTO( Vector4D, z,1,z,z );
	_SWIZZLE4_PROTO( Vector4D, z,1,z,0 );
	_SWIZZLE4_PROTO( Vector4D, z,1,z,1 );
	_SWIZZLE4_PROTO( Vector4D, z,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, z,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, z,1,0,z );
	_SWIZZLE4_PROTO( Vector4D, z,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, z,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, z,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, z,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, z,1,1,z );
	_SWIZZLE4_PROTO( Vector4D, z,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, z,1,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, 0,x,x,y );
	_SWIZZLE4_PROTO( Vector4D, 0,x,x,z );
	_SWIZZLE4_PROTO( Vector4D, 0,x,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,y,x );
	_SWIZZLE4_PROTO( Vector4D, 0,x,y,y );
	_SWIZZLE4_PROTO( Vector4D, 0,x,y,z );
	_SWIZZLE4_PROTO( Vector4D, 0,x,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,z,x );
	_SWIZZLE4_PROTO( Vector4D, 0,x,z,y );
	_SWIZZLE4_PROTO( Vector4D, 0,x,z,z );
	_SWIZZLE4_PROTO( Vector4D, 0,x,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,0,x );
	_SWIZZLE4_PROTO( Vector4D, 0,x,0,y );
	_SWIZZLE4_PROTO( Vector4D, 0,x,0,z );
	_SWIZZLE4_PROTO( Vector4D, 0,x,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,1,x );
	_SWIZZLE4_PROTO( Vector4D, 0,x,1,y );
	_SWIZZLE4_PROTO( Vector4D, 0,x,1,z );
	_SWIZZLE4_PROTO( Vector4D, 0,x,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,x,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 0,y,x,y );
	_SWIZZLE4_PROTO( Vector4D, 0,y,x,z );
	_SWIZZLE4_PROTO( Vector4D, 0,y,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,y,x );
	_SWIZZLE4_PROTO( Vector4D, 0,y,y,y );
	_SWIZZLE4_PROTO( Vector4D, 0,y,y,z );
	_SWIZZLE4_PROTO( Vector4D, 0,y,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,z,x );
	_SWIZZLE4_PROTO( Vector4D, 0,y,z,y );
	_SWIZZLE4_PROTO( Vector4D, 0,y,z,z );
	_SWIZZLE4_PROTO( Vector4D, 0,y,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,0,x );
	_SWIZZLE4_PROTO( Vector4D, 0,y,0,y );
	_SWIZZLE4_PROTO( Vector4D, 0,y,0,z );
	_SWIZZLE4_PROTO( Vector4D, 0,y,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,1,x );
	_SWIZZLE4_PROTO( Vector4D, 0,y,1,y );
	_SWIZZLE4_PROTO( Vector4D, 0,y,1,z );
	_SWIZZLE4_PROTO( Vector4D, 0,y,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,y,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 0,z,x,y );
	_SWIZZLE4_PROTO( Vector4D, 0,z,x,z );
	_SWIZZLE4_PROTO( Vector4D, 0,z,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,y,x );
	_SWIZZLE4_PROTO( Vector4D, 0,z,y,y );
	_SWIZZLE4_PROTO( Vector4D, 0,z,y,z );
	_SWIZZLE4_PROTO( Vector4D, 0,z,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,z,x );
	_SWIZZLE4_PROTO( Vector4D, 0,z,z,y );
	_SWIZZLE4_PROTO( Vector4D, 0,z,z,z );
	_SWIZZLE4_PROTO( Vector4D, 0,z,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,0,x );
	_SWIZZLE4_PROTO( Vector4D, 0,z,0,y );
	_SWIZZLE4_PROTO( Vector4D, 0,z,0,z );
	_SWIZZLE4_PROTO( Vector4D, 0,z,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,1,x );
	_SWIZZLE4_PROTO( Vector4D, 0,z,1,y );
	_SWIZZLE4_PROTO( Vector4D, 0,z,1,z );
	_SWIZZLE4_PROTO( Vector4D, 0,z,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,z,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,z );
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,z );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,z,x );
	_SWIZZLE4_PROTO( Vector4D, 0,0,z,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,z,z );
	_SWIZZLE4_PROTO( Vector4D, 0,0,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,z );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,z );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,z );
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,z );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,z,x );
	_SWIZZLE4_PROTO( Vector4D, 0,1,z,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,z,z );
	_SWIZZLE4_PROTO( Vector4D, 0,1,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,z );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,z );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, 1,x,x,y );
	_SWIZZLE4_PROTO( Vector4D, 1,x,x,z );
	_SWIZZLE4_PROTO( Vector4D, 1,x,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,y,x );
	_SWIZZLE4_PROTO( Vector4D, 1,x,y,y );
	_SWIZZLE4_PROTO( Vector4D, 1,x,y,z );
	_SWIZZLE4_PROTO( Vector4D, 1,x,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,z,x );
	_SWIZZLE4_PROTO( Vector4D, 1,x,z,y );
	_SWIZZLE4_PROTO( Vector4D, 1,x,z,z );
	_SWIZZLE4_PROTO( Vector4D, 1,x,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,0,x );
	_SWIZZLE4_PROTO( Vector4D, 1,x,0,y );
	_SWIZZLE4_PROTO( Vector4D, 1,x,0,z );
	_SWIZZLE4_PROTO( Vector4D, 1,x,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,1,x );
	_SWIZZLE4_PROTO( Vector4D, 1,x,1,y );
	_SWIZZLE4_PROTO( Vector4D, 1,x,1,z );
	_SWIZZLE4_PROTO( Vector4D, 1,x,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,x,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 1,y,x,y );
	_SWIZZLE4_PROTO( Vector4D, 1,y,x,z );
	_SWIZZLE4_PROTO( Vector4D, 1,y,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,y,x );
	_SWIZZLE4_PROTO( Vector4D, 1,y,y,y );
	_SWIZZLE4_PROTO( Vector4D, 1,y,y,z );
	_SWIZZLE4_PROTO( Vector4D, 1,y,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,z,x );
	_SWIZZLE4_PROTO( Vector4D, 1,y,z,y );
	_SWIZZLE4_PROTO( Vector4D, 1,y,z,z );
	_SWIZZLE4_PROTO( Vector4D, 1,y,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,0,x );
	_SWIZZLE4_PROTO( Vector4D, 1,y,0,y );
	_SWIZZLE4_PROTO( Vector4D, 1,y,0,z );
	_SWIZZLE4_PROTO( Vector4D, 1,y,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,1,x );
	_SWIZZLE4_PROTO( Vector4D, 1,y,1,y );
	_SWIZZLE4_PROTO( Vector4D, 1,y,1,z );
	_SWIZZLE4_PROTO( Vector4D, 1,y,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,y,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 1,z,x,y );
	_SWIZZLE4_PROTO( Vector4D, 1,z,x,z );
	_SWIZZLE4_PROTO( Vector4D, 1,z,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,y,x );
	_SWIZZLE4_PROTO( Vector4D, 1,z,y,y );
	_SWIZZLE4_PROTO( Vector4D, 1,z,y,z );
	_SWIZZLE4_PROTO( Vector4D, 1,z,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,z,x );
	_SWIZZLE4_PROTO( Vector4D, 1,z,z,y );
	_SWIZZLE4_PROTO( Vector4D, 1,z,z,z );
	_SWIZZLE4_PROTO( Vector4D, 1,z,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,0,x );
	_SWIZZLE4_PROTO( Vector4D, 1,z,0,y );
	_SWIZZLE4_PROTO( Vector4D, 1,z,0,z );
	_SWIZZLE4_PROTO( Vector4D, 1,z,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,1,x );
	_SWIZZLE4_PROTO( Vector4D, 1,z,1,y );
	_SWIZZLE4_PROTO( Vector4D, 1,z,1,z );
	_SWIZZLE4_PROTO( Vector4D, 1,z,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,z,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,z );
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,z );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,z,x );
	_SWIZZLE4_PROTO( Vector4D, 1,0,z,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,z,z );
	_SWIZZLE4_PROTO( Vector4D, 1,0,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,z );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,z );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,x );	// * //
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,z );
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,z );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,z,x );
	_SWIZZLE4_PROTO( Vector4D, 1,1,z,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,z,z );
	_SWIZZLE4_PROTO( Vector4D, 1,1,z,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,z,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,z );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,z );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,1 );
	// - -------------------------------------------------------------------------------------- - //
	#undef _SWIZZLE4_PROTO
	#undef _SWIZZLE3_PROTO
	#undef _SWIZZLE2_PROTO
	// - -------------------------------------------------------------------------------------- - //
	#undef SWIZZLE4_PROTO
	#undef SWIZZLE3_PROTO
	#undef SWIZZLE2_PROTO
	// - -------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector3D operator - ( const Real& a, const Vector3D& b ) {
	Vector3D Ret( a - b.x, a - b.y, a - b.z );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector3D operator / ( const Real& a, const Vector3D& b ) {
	Vector3D Ret( a / b.x, a / b.y, a / b.z );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //

// -- ---------------------------------------------------------------------------------------- -- //
// External Vector Operations, for GLSL familiar syntax //
// -- ---------------------------------------------------------------------------------------- -- //
inline const Real dot( const Vector3D& a, const Vector3D& b ) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
// - -------------------------------------------------------------------------------------- - //
inline const Vector3D cross( const Vector3D& a, const Vector3D b ) {
	return Vector3D(
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
		);
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector3D mix( const Vector3D& a, const Vector3D& b, const Real Alpha ) {
	return (a * (Real::One - Alpha)) + (b * Alpha);
}
// -- ---------------------------------------------------------------------------------------- -- //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Vector3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
