// - ------------------------------------------------------------------------------------------ - //
// Short Integer //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_SInteger_H__
#define __Geometry_SInteger_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Make this behave as just a storage type. All operations are on Integers.
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
	inline const SInteger& operator _OP_ ( const SInteger& _Vs ) { \
		Value _OP_ _Vs.Value; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( _OP_ ) \
	inline const SInteger& operator _OP_ () { \
		_OP_ Value; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( _OP_ ) \
	inline const SInteger operator _OP_ ( int ) { \
		return Value _OP_; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_OPERATOR( _OP_ ) \
	inline const bool operator _OP_ ( const SInteger& _Vs ) const { \
		return Value _OP_ _Vs.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOL_OPERATOR( _OP_ ) \
	inline const SInteger operator _OP_ ( const SInteger& _Vs ) const { \
		return Value _OP_ _Vs.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TYPEA_SYMBOL_B_OPERATOR( _TYPE_, _OP_ ) \
	inline const _TYPE_ operator _OP_ ( const _TYPE_& A, const SInteger& B ) { \
		return A _OP_ B.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_A_SYMBOL_TYPEB_OPERATOR( _TYPE_, _OP_ ) \
	inline const _TYPE_ operator _OP_ ( const SInteger& A, const _TYPE_& B ) { \
		return A.Value _OP_ B; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_TYPEA_SYMBOL_B_OPERATOR( _TYPE_, _OP_ ) \
	inline const bool operator _OP_ ( const _TYPE_& A, const SInteger& B ) { \
		return A _OP_ B.Value; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_A_SYMBOL_TYPEB_OPERATOR( _TYPE_, _OP_ ) \
	inline const bool operator _OP_ ( const SInteger& A, const _TYPE_& B ) { \
		return A.Value _OP_ B; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class SInteger {
public:
	typedef short IntType;
	IntType Value;

public:
	inline SInteger() :
		Value( 0 )
	{
	}

	inline SInteger( const IntType _Value ) :
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
	inline operator IntType () {
		return Value;
	}

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
	OVERLOAD_SYMBOL_OPERATOR( << );
	OVERLOAD_SYMBOL_OPERATOR( >> );

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
	inline const SInteger NormalizeRet() {
		SInteger Temp( *this );
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
	inline const SInteger Normal() const {
		if ( Value > 0 )
			return 1;
		else if ( Value < 0 )
			return -1;
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const SInteger Magnitude() const {
		return Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const SInteger MagnitudeSquared() const {
		return Value * Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const SInteger Manhattan() const {
		return Abs();
	}


	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions: Min = take smallest.  Max = take biggest. //
	// - -------------------------------------------------------------------------------------- - //
	inline SInteger Min( const SInteger& _Vs ) const {
		SInteger Number = *this;
		if ( Number > _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline SInteger Max( const SInteger& _Vs ) const {
		SInteger Number = *this;
		if ( Number < _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline SInteger& MinClamp( const SInteger& _Vs ) {
		if ( *this > _Vs )
			*this = _Vs;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline SInteger& MaxClamp( const SInteger& _Vs ) {
		if ( *this < _Vs )
			*this = _Vs;
		return *this;
	}	
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Range Testing: Inclusive Bottom and Top //
	// - -------------------------------------------------------------------------------------- - //
	inline const SInteger Range( const SInteger& _Min, const SInteger& _Max ) const {
		SInteger Number = *this;
		// Min //
		if ( Number < _Min )
			return _Min;
		// Max //
		if ( Number > _Max )
			return _Max - 1;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline SInteger& RangeClamp( const SInteger& _Min, const SInteger& _Max ) {
		// Min //
		if ( *this < _Min )
			*this = _Min;
		// Max //
		if ( *this > _Max )
			*this = _Max - 1;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool InRange( const SInteger& _Min, const SInteger& _Max ) const {
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
	inline const SInteger Abs() const {
		if ( Value < 0 )
			return -Value;
		else
			return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const SInteger Sqrt() const {
		if ( !IsZero() )
			return (int)sqrt( (float)Value );
		else
			return 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const SInteger Sqrt_() const {
		return (int)sqrt( (float)Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		return Value == 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroOrLess() const {
		return Value < SInteger::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const bool Is( const SInteger& _Vs ) const {
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
#endif // __Geometry_SInteger_H__ //
// - ------------------------------------------------------------------------------------------ - //
