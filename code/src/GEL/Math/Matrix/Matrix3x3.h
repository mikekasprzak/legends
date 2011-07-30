// - ------------------------------------------------------------------------------------------ - //
// Matrix3x3 //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Matrix3x3_H__
#define __Geometry_Matrix3x3_H__
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
#include <Math/Vector/Vector3D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Matrix3x3& operator _OP_ ( const Real& _Vs ) { \
		Array[0] _OP_ _Vs; \
		Array[1] _OP_ _Vs; \
		Array[2] _OP_ _Vs; \
		Array[3] _OP_ _Vs; \
		Array[4] _OP_ _Vs; \
		Array[5] _OP_ _Vs; \
		Array[6] _OP_ _Vs; \
		Array[7] _OP_ _Vs; \
		Array[8] _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// 4 part 3x3 Matrix class //
// - ------------------------------------------------------------------------------------------ - //
class Matrix3x3 :
	boost::multipliable<Matrix3x3,
	boost::arithmetic2<Matrix3x3, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real Array[9];
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Matrix3x3 Identity;
	static const Matrix3x3 Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
#ifdef NOT_GCC
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3()
	{
		Array[0] = Real::One;
		Array[1] = Real::Zero;
		Array[2] = Real::Zero;

		Array[3] = Real::Zero;
		Array[4] = Real::One;
		Array[5] = Real::Zero;

		Array[6] = Real::Zero;
		Array[7] = Real::Zero;
		Array[8] = Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3( const Vector2D& _v1, const Vector2D& _v2, const Vector2D& _v3 )
	{
		Array[0] = _v1.x;
		Array[1] = _v1.y;
		Array[2] = Real::Zero;

		Array[3] = _v2.x;
		Array[4] = _v2.y;
		Array[5] = Real::Zero;

		Array[6] = _v3.x;
		Array[7] = _v3.y;
		Array[8] = Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3( const Vector3D& _v1, const Vector3D& _v2, const Vector3D& _v3 )
	{
		Array[0] = _v1.x;
		Array[1] = _v1.y;
		Array[2] = _v1.z;

		Array[3] = _v2.x;
		Array[4] = _v2.y;
		Array[5] = _v2.z;

		Array[6] = _v3.x;
		Array[7] = _v3.y;
		Array[8] = _v3.z;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3( const Real& _e1, const Real& _e2, const Real& _e3, const Real& _e4, const Real& _e5, const Real& _e6, const Real& _e7, const Real& _e8, const Real& _e9 )
	{
		Array[0] = _e1;
		Array[1] = _e2;
		Array[2] = _e3;

		Array[3] = _e4;
		Array[4] = _e5;
		Array[5] = _e6;

		Array[6] = _e7;
		Array[7] = _e8;
		Array[8] = _e9;
	}
	// - -------------------------------------------------------------------------------------- - //	
#else // NOT_GCC //
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3():
		Array( (Real[]) { 
			Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero,
			Real::Zero, Real::Zero, Real::One
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3( const Vector2D& _v1, const Vector2D& _v2, const Vector2D& _v3 ) :
		Array( (Real[]) { 
			_v1.x, _v1.y, Real::Zero,
			_v2.x, _v2.y, Real::Zero,
			_v3.x, _v3.y, Real::One
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3( const Vector3D& _v1, const Vector3D& _v2, const Vector3D& _v3 ) :
		Array( (Real[]) { 
			_v1.x, _v1.y, _v1.z,
			_v2.x, _v2.y, _v2.z,
			_v3.x, _v3.y, _v3.z
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix3x3( const Real& _e1, const Real& _e2, const Real& _e3, const Real& _e4, const Real& _e5, const Real& _e6, const Real& _e7, const Real& _e8, const Real& _e9 ) :
		Array( (Real[]) {
			_e1, _e2, _e3,
			_e4, _e5, _e6,
			_e7, _e8, _e9
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //	
#endif // NOT_GCC //
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
	inline Real& operator () ( const int& _x, const int& _y ) {
		//return Array[ (_y * 3) + _x ];
		return Array[ ((_y << 1) + _y) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& operator () ( const int& _x, const int& _y ) const {
		//return Array[ (_y * 3) + _x ];
		return Array[ ((_y << 1) + _y) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& Matrix( const int& _x, const int& _y ) {
		//return Array[ (_y * 3) + _x ];
		return Array[ ((_y << 1) + _y) + _x ];
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Matrix( const int& _x, const int& _y ) const {
		//return Array[ (_y * 3) + _x ];
		return Array[ ((_y << 1) + _y) + _x ];
	}	
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Matrix //
	// [ 0 1 2 ] //
	// [ 3 4 5 ] //
	// [ 6 7 8 ] //
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3& operator *= ( const Matrix3x3& _Vs ) {
		Matrix3x3 Temp;
		// Top Row //
		Temp.Array[ 0 ] = (Matrix( 0, 0 ) * _Vs( 0, 0 )) + (Matrix( 1, 0 ) * _Vs( 0, 1 )) + (Matrix( 2, 0 ) * _Vs( 0, 2 ));
		Temp.Array[ 1 ] = (Matrix( 0, 0 ) * _Vs( 1, 0 )) + (Matrix( 1, 0 ) * _Vs( 1, 1 )) + (Matrix( 2, 0 ) * _Vs( 1, 2 ));
		Temp.Array[ 2 ] = (Matrix( 0, 0 ) * _Vs( 2, 0 )) + (Matrix( 1, 0 ) * _Vs( 2, 1 )) + (Matrix( 2, 0 ) * _Vs( 2, 2 ));
		// Middle Row //
		Temp.Array[ 3 ] = (Matrix( 0, 1 ) * _Vs( 0, 0 )) + (Matrix( 1, 1 ) * _Vs( 0, 1 )) + (Matrix( 2, 1 ) * _Vs( 0, 2 ));
		Temp.Array[ 4 ] = (Matrix( 0, 1 ) * _Vs( 1, 0 )) + (Matrix( 1, 1 ) * _Vs( 1, 1 )) + (Matrix( 2, 1 ) * _Vs( 1, 2 ));
		Temp.Array[ 5 ] = (Matrix( 0, 1 ) * _Vs( 2, 0 )) + (Matrix( 1, 1 ) * _Vs( 2, 1 )) + (Matrix( 2, 1 ) * _Vs( 2, 2 ));
		// Bottom Row //
		Temp.Array[ 6 ] = (Matrix( 0, 2 ) * _Vs( 0, 0 )) + (Matrix( 1, 2 ) * _Vs( 0, 1 )) + (Matrix( 2, 2 ) * _Vs( 0, 2 ));
		Temp.Array[ 7 ] = (Matrix( 0, 2 ) * _Vs( 1, 0 )) + (Matrix( 1, 2 ) * _Vs( 1, 1 )) + (Matrix( 2, 2 ) * _Vs( 1, 2 ));
		Temp.Array[ 8 ] = (Matrix( 0, 2 ) * _Vs( 2, 0 )) + (Matrix( 1, 2 ) * _Vs( 2, 1 )) + (Matrix( 2, 2 ) * _Vs( 2, 2 ));
		
		return *this = Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Calculate Adjoint of Matrix //
	inline const Matrix3x3 Transpose() {
		return Matrix3x3(
			Array[0], Array[3], Array[6],
			Array[1], Array[4], Array[7],
			Array[2], Array[5], Array[8]
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Calculate the determinant, for the inverse //
	inline const Real Determinant() const {
		return
			(Matrix(0,0) * ((Matrix(1,1) * Matrix(2,2)) - (Matrix(1,2) * Matrix(2,1)))) +
			(Matrix(0,1) * ((Matrix(1,2) * Matrix(2,0)) - (Matrix(1,0) * Matrix(2,2)))) +
			(Matrix(0,2) * ((Matrix(1,0) * Matrix(2,1)) - (Matrix(1,1) * Matrix(2,0))));
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Calculate the Inverse //
//	inline const Matrix3x3 Inverse() {
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
	inline static const Matrix3x3 Scaling( const Vector2D& _Vs ) {
		Matrix3x3 Matrix(
			_Vs.x, Real::Zero, Real::Zero,
			Real::Zero, _Vs.y, Real::Zero,
			Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a scaling Matrix from a vector //
	inline static const Matrix3x3 Scaling( const Vector3D& _Vs ) {
		Matrix3x3 Matrix(
			_Vs.x, Real::Zero, Real::Zero,
			Real::Zero, _Vs.y, Real::Zero,
			Real::Zero, Real::Zero, _Vs.z
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a scaling matrix from a scalar //
	inline static const Matrix3x3 Scaling( const Real& Scalar ) {
		Matrix3x3 Matrix(
			Scalar, Real::Zero, Real::Zero,
			Real::Zero, Scalar, Real::Zero,
			Real::Zero, Real::Zero, Scalar
			);	
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a translating Matrix from a vector //
	inline static const Matrix3x3 Translating( const Vector2D& _Vs ) {
		Matrix3x3 Matrix(
			Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero,
			_Vs.x, _Vs.y, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a translating Matrix from a vector //
	inline static const Matrix3x3 Translating( const Vector3D& _Vs ) {
		Matrix3x3 Matrix(
			Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero,
			_Vs.x, _Vs.y, _Vs.z
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation Matrix from a vector ((0,1) being an untransformed matrix) //
	inline static const Matrix3x3 Rotating( const Vector2D& _Vs ) {
		Matrix3x3 Matrix(
			_Vs.y, -_Vs.x, Real::Zero,
			_Vs.x, _Vs.y, Real::Zero,
			Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation Matrix from an Angle //
	inline static const Matrix3x3 Rotating( const Real& Angle ) {
		Matrix3x3 Matrix(
			Angle.Cos(), -Angle.Sin(), Real::Zero,
			Angle.Sin(), Angle.Cos(), Real::Zero,
			Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix3x3 operator - ( const Real& a, const Matrix3x3& b ) {
	return Matrix3x3(
		a - b.Array[0], a - b.Array[1], a - b.Array[2],
		a - b.Array[3], a - b.Array[4], a - b.Array[5],
		a - b.Array[6], a - b.Array[7], a - b.Array[8]
		);
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Matrix3x3 operator / ( const Real& a, const Matrix3x3& b ) {
	return Matrix3x3(
		a / b.Array[0], a / b.Array[1], a / b.Array[2],
		a / b.Array[3], a / b.Array[4], a / b.Array[5],
		a / b.Array[6], a / b.Array[7], a / b.Array[8]
		);
}
// -- ---------------------------------------------------------------------------------------- -- //


// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Matrix3x3_H__ //
// - ------------------------------------------------------------------------------------------ - //
