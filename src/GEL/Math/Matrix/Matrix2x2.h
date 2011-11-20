// - ------------------------------------------------------------------------------------------ - //
// Matrix2x2 //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Matrix2x2_H__
#define __Geometry_Matrix2x2_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define NOT_GCC
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <External/boost/operators.hpp>

#include <Math/Real.h>
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Matrix2x2& operator _OP_ ( const Real& _Vs ) { \
		Array[0] _OP_ _Vs; \
		Array[1] _OP_ _Vs; \
		Array[2] _OP_ _Vs; \
		Array[3] _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// 4 part 2x2 Matrix class //
// - ------------------------------------------------------------------------------------------ - //
class Matrix2x2 :
	boost::multipliable<Matrix2x2,
	boost::arithmetic2<Matrix2x2, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real Array[4];
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Matrix2x2 Identity;
	static const Matrix2x2 Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix2x2() {
	}
	// - -------------------------------------------------------------------------------------- - //
#ifdef NOT_GCC
	// - -------------------------------------------------------------------------------------- - //	
	inline Matrix2x2( const Vector2D& _v1, const Vector2D& _v2 )
	{
		Array[0] = _v1.x;
		Array[1] = _v1.y;
		Array[2] = _v2.x;
		Array[3] = _v2.y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix2x2( const Real& _e1, const Real& _e2, const Real& _e3, const Real& _e4 )
	{
		Array[0] = _e1;
		Array[1] = _e2;
		Array[2] = _e3;
		Array[3] = _e4;
	}
	// - -------------------------------------------------------------------------------------- - //	
#else // NOT_GCC //
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix2x2( const Vector2D& _v1, const Vector2D& _v2 ) :
		Array( (Real[]) { 
			_v1.x, _v1.y,
			_v2.x, _v2.y
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix2x2( const Real& _e1, const Real& _e2, const Real& _e3, const Real& _e4 ) :
		Array( (Real[]) {
			_e1, _e2,
			_e3, _e4
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //	
#endif // MSC_VER //
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators - The rest will be handled by Boost //
	// - -------------------------------------------------------------------------------------- - //
	// Indexing //
	inline Real& operator [] ( const int& idx ) {
		return Array[ idx ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Indexing //
	inline const Real& operator [] ( const int& idx ) const {
		return Array[ idx ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& operator () ( const int& _x, const int& _y ) {
		return Array[ (_y << 1) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& operator () ( const int& _x, const int& _y ) const {
		return Array[ (_y << 1) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& Matrix( const int& _x, const int& _y ) {
		return Array[ (_y << 1) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Matrix( const int& _x, const int& _y ) const {
		return Array[ (_y << 1) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Negation Operator //
	inline const Matrix2x2 operator - ( ) const {
		return Matrix2x2(
			-Array[0], -Array[1],
			-Array[2], -Array[3]
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Matrix //
	// [ 0 1 ] //
	// [ 2 3 ] //
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix2x2& operator *= ( const Matrix2x2& _Vs ) {
		Matrix2x2 Temp;
		// Top Row //
		Temp.Array[ 0 ] = (Array[ 0 ] * _Vs.Array[ 0 ]) + (Array[ 1 ] * _Vs.Array[ 2 ]);
		Temp.Array[ 1 ] = (Array[ 0 ] * _Vs.Array[ 1 ]) + (Array[ 1 ] * _Vs.Array[ 3 ]);
		// Bottom Row //
		Temp.Array[ 2 ] = (Array[ 3 ] * _Vs.Array[ 0 ]) + (Array[ 4 ] * _Vs.Array[ 2 ]);
		Temp.Array[ 3 ] = (Array[ 3 ] * _Vs.Array[ 1 ]) + (Array[ 4 ] * _Vs.Array[ 3 ]);
		
		return *this = Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Calculate Adjoint of Matrix //
//	inline const Matrix2x2 Adjoint() {
//		// TODO: This might be incorrect... it might actually be 0 2 1 3
//		return Matrix2x2( Array[3], -Array[1], -Array[2], Array[0] );
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Calculate the determinant, for the inverse //
	inline const Real Determinant() const {
		return (Array[0]*Array[3]) - (Array[1]*Array[2]);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Calculate the Inverse //
//	inline const Matrix2x2 Inverse() {
//		// Possible bug.  If the Determinant is 0, then the matrix has no inverse //
//		return Adjoint() / Determinant();
//	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Scalar Operations //
	// - -------------------------------------------------------------------------------------- - //
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
	// Creates a scaling Matrix from a vector //
	inline static const Matrix2x2 Scale( const Vector2D& _Vs ) {
		Matrix2x2 Matrix(
			_Vs.x,
			Real::Zero,
			Real::Zero,
			_Vs.y
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a scaling matrix from a scalar //
	inline static const Matrix2x2 Scale( const Real& Scalar ) {
		Matrix2x2 Matrix(
			Scalar,
			Real::Zero,
			Real::Zero,
			Scalar
			);	
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation matrix from a given angle //
	inline static const Matrix2x2 Rotate( const Real& Angle ) {
		Real AngleCos = Angle.Cos();
		Real AngleSin = Angle.Sin();
		
		Matrix2x2 Matrix(
			AngleCos,
			AngleSin,
			-AngleSin,
			AngleCos
			);		
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation and scaling matrix from a given angle and scalar //
	inline static const Matrix2x2 RotateScale( const Real& Angle, const Real& Scalar ) {
		Real AngleCos = Angle.Cos();
		Real AngleSin = Angle.Sin();
		
		Matrix2x2 Matrix(
			AngleCos * Scalar,
			AngleSin * Scalar,
			-AngleSin * Scalar,
			AngleCos * Scalar
			);		
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates an orientation matrix from a vector //
	inline static const Matrix2x2 Orientation( const Vector2D& Vec ) {
		Matrix2x2 Matrix(
			Vec.x,
			Vec.y,
			-Vec.Tangent().x,
			Vec.Tangent().y
			);		
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation Matrix from an angle scalar //
	inline static const Matrix2x2 RotationMatrix( Real Angle ) {
		Angle /= 360.0f;
		Matrix2x2 Matrix(
			Real::Cos(Angle), Real::Sin(Angle),
			-Real::Sin(Angle), Real::Cos(Angle)
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix2x2 operator - ( const Real& a, const Matrix2x2& b ) {
	Matrix2x2 Ret( a - b.Array[0], a - b.Array[1], a - b.Array[2], a - b.Array[3] );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Matrix2x2 operator / ( const Real& a, const Matrix2x2& b ) {
	Matrix2x2 Ret( a / b.Array[0], a / b.Array[1], a / b.Array[2], a / b.Array[3] );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //


// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Matrix2x2_H__ //
// - ------------------------------------------------------------------------------------------ - //
