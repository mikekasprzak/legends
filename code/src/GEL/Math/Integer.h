// - ------------------------------------------------------------------------------------------ - //
// Integer //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Integer_H__
#define __Geometry_Integer_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Move Constructor (C++11), INT_MAX, MAX_VALUE (+), MIN_VALUE (-)
// - ------------------------------------------------------------------------------------------ - //
#include <math.h>
#ifndef _WIN32_WCE
#include <stdlib.h>
#else // _WIN32_WCE //
#include <stddef.h>
#endif // _WIN32_WCE //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
// This set is used for straight duplicate overloading of types, such as the float/Real wrapper //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Integer& operator _OP_ ( const Integer& _Vs ) { \
		Value _OP_ _Vs.Value; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( _OP_ ) \
	inline const Integer& operator _OP_ () { \
		_OP_ Value; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( _OP_ ) \
	inline const Integer operator _OP_ ( int ) { \
		return Value _OP_; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_OPERATOR( _OP_ ) \
	inline const bool operator _OP_ ( const Integer& _Vs ) const { \
		return Value _OP_ _Vs.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOL_OPERATOR( _OP_ ) \
	inline const Integer operator _OP_ ( const Integer& _Vs ) const { \
		return Value _OP_ _Vs.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( _TYPE_, _OP_ ) \
	inline const _TYPE_ operator _OP_ ( const _TYPE_& A, const Integer& B ) { \
		return A _OP_ B.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( _TYPE_, _OP_ ) \
	inline const _TYPE_ operator _OP_ ( const Integer& A, const _TYPE_& B ) { \
		return A.Value _OP_ B; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( _TYPE_, _OP_ ) \
	inline const bool operator _OP_ ( const _TYPE_& A, const Integer& B ) { \
		return A _OP_ B.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( _TYPE_, _OP_ ) \
	inline const bool operator _OP_ ( const Integer& A, const _TYPE_& B ) { \
		return A.Value _OP_ B; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class Integer {
public:
	typedef int IntType;
	IntType Value;

public:
	inline Integer() :
		Value( 0 )
	{
	}

	inline Integer( const IntType _Value ) :
		Value( _Value )
	{
	}

public:
	enum {
		// Regular constants //
		Identity = 1,
		Zero = 0,
		
		// Other constants special to this type //
		One = 1,
		SmallestUnit = 1	
	};

public:
	// - -------------------------------------------------------------------------------------- - //
	// Convert all Integers to int automatically //
//	inline operator IntType () {
//		return Value;
//	}
	// - -------------------------------------------------------------------------------------- - //
	inline operator const IntType () {
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IntType ToInt() const {
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
public:		
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators, essentially a wrapping for float/double's normal operators //
	// - -------------------------------------------------------------------------------------- - //
	OVERLOAD_SYMBOLEQUALS_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( -= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( /= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( %= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( |= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( &= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( ^= );

	OVERLOAD_SYMBOL_OPERATOR( + );
	OVERLOAD_SYMBOL_OPERATOR( - );
	OVERLOAD_SYMBOL_OPERATOR( * );
	OVERLOAD_SYMBOL_OPERATOR( / );
	OVERLOAD_SYMBOL_OPERATOR( % );
	OVERLOAD_SYMBOL_OPERATOR( | );
	OVERLOAD_SYMBOL_OPERATOR( & );
	OVERLOAD_SYMBOL_OPERATOR( ^ );
	OVERLOAD_SYMBOL_OPERATOR( >> );
	OVERLOAD_SYMBOL_OPERATOR( << );

	OVERLOAD_TEST_OPERATOR( == );
	OVERLOAD_TEST_OPERATOR( != );
	OVERLOAD_TEST_OPERATOR( <= );
	OVERLOAD_TEST_OPERATOR( >= );
	OVERLOAD_TEST_OPERATOR( < );
	OVERLOAD_TEST_OPERATOR( > );
	
//	OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( ++ );
//	OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( -- );
//
//	OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( ++ );
//	OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( -- );

	inline const IntType operator - ( ) const {
		return -Value;
	}

public:		
	// - -------------------------------------------------------------------------------------- - //
	// Increment and decrement operators //
	// - -------------------------------------------------------------------------------------- - //
	inline const IntType operator ++ () {
		return ++Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IntType operator ++ ( int ) {
		return Value++;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IntType operator -- () {
		return --Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const IntType operator -- ( int ) {
		return Value--;
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline void Normalize() {
		if ( Value > 0 )
			Value = 1;
		else if ( Value < 0 )
			Value = -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Integer NormalizeRet() {
		Integer Temp( *this );
		if ( Value > 0 )
			Value = 1;
		else if ( Value < 0 ) {
			Value = -1;
			Temp = -Temp;
		}
		return Temp;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Integer Normal() const {
		if ( Value > 0 )
			return 1;
		else if ( Value < 0 )
			return -1;
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const Integer Magnitude() const {
		return Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Integer MagnitudeSquared() const {
		return Value * Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Integer Manhattan() const {
		return Abs();
	}


	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions: Min = take smallest.  Max = take biggest. //
	// - -------------------------------------------------------------------------------------- - //
	inline Integer Min( const Integer& _Vs ) const {
		Integer Number = *this;
		if ( Number > _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Integer Max( const Integer& _Vs ) const {
		Integer Number = *this;
		if ( Number < _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Integer& MinClamp( const Integer& _Vs ) {
		if ( *this > _Vs )
			*this = _Vs;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Integer& MaxClamp( const Integer& _Vs ) {
		if ( *this < _Vs )
			*this = _Vs;
		return *this;
	}	
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Range Testing: Inclusive Bottom and Top //
	// - -------------------------------------------------------------------------------------- - //
	inline const Integer Range( const Integer& _Min, const Integer& _Max ) const {
		Integer Number = *this;
		// Min //
		if ( Number < _Min )
			return _Min;
		// Max //
		if ( Number > _Max )
			return _Max - 1;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Integer& RangeClamp( const Integer& _Min, const Integer& _Max ) {
		// Min //
		if ( *this < _Min )
			*this = _Min;
		// Max //
		if ( *this > _Max )
			*this = _Max - 1;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool InRange( const Integer& _Min, const Integer& _Max ) const {
		// Min //
		if ( *this < _Min )
			return false;
		// Max //
		if ( *this > _Max )
			return false;
		return true;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Specific Functions that apply to this type //
	// - -------------------------------------------------------------------------------------- - //
	inline const Integer Abs() const {
		if ( Value < 0 )
			return -Value;
		else
			return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const Integer Sqrt() const {
		if ( !IsZero() )
			return (int)sqrt( (float)Value );
		else
			return 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const Integer Sqrt_() const {
		return (int)sqrt( (float)Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		return Value == 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroOrLess() const {
		return Value < Integer::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const bool Is( const Integer& _Vs ) const {
		return Value == _Vs.Value;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	static inline const int Random() {
		return rand();
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const int Random( const int Value ) {
		return rand() % Value;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	static inline const int Clamp( const int Value, const int Min, const int Max ) {
		if ( Value < Min )
			return Min;
		else if ( Value > Max )
			return Max;
		else
			return Value;
	}	
	// - -------------------------------------------------------------------------------------- - //
public:
	
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, + );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, - );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, * );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, / );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, % );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, | );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, & );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, ^ );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, >> );
OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( int, << );
OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( int, > );
OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( int, < );
OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( int, >= );
OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( int, <= );
OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( int, == );
OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( int, != );

OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, + );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, - );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, * );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, / );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, % );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, | );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, & );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, ^ );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, >> );
OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( int, << );
OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( int, > );
OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( int, < );
OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( int, >= );
OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( int, <= );
OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( int, == );
OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( int, != );
// - ------------------------------------------------------------------------------------------ - //
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, + );
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, - );
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, * );
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, / );
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, % );
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, | );
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, & );
//OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( unsigned int, ^ );
//OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( unsigned int, > );
//OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( unsigned int, < );
//OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( unsigned int, >= );
//OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( unsigned int, <= );
//OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( unsigned int, == );
//OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( unsigned int, != );
//
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, + );
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, - );
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, * );
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, / );
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, % );
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, | );
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, & );
//OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( unsigned int, ^ );
//OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( unsigned int, > );
//OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( unsigned int, < );
//OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( unsigned int, >= );
//OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( unsigned int, <= );
//OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( unsigned int, == );
//OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( unsigned int, != );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR
#undef OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR
#undef OVERLOAD_TEST_OPERATOR
#undef OVERLOAD_SYMBOL_OPERATOR
#undef OVERLOAD_TYPEA_SYMBOL_B_OPERATOR
#undef OVERLOAD_A_SYMBOL_TYPEB_OPERATOR
#undef OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR
#undef OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Integer_H__ //
// - ------------------------------------------------------------------------------------------ - //
