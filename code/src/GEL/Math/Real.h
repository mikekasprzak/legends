// - ------------------------------------------------------------------------------------------ - //
// Real //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Real_H__
#define __Geometry_Real_H__
// - ------------------------------------------------------------------------------------------ - //
// Todo: 
// - ------------------------------------------------------------------------------------------ - //
#include <cmath>
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4305) // Truncation
#pragma warning (disable : 4244) // Tructation, data loss potential 
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	// Compute J terms in the series expansion.  K is the loop variable.
	template<int N, int I, int J, int K>
	class _SineSeries {
	public:
		//enum { M_PI = 3.1415926535897932384626433832795 };
	    enum { go = (K+1 != J) };
	
	    static inline float accumulate() {
	        return 1-(I*2*M_PI/N)*(I*2*M_PI/N)/(2*K+2)/(2*K+3) *
	            _SineSeries<N*go,I*go,J*go,(K+1)*go>::accumulate();
	    }
	};
	// - -------------------------------------------------------------------------------------- - //
	// Specialization to terminate loop
	template<>
	class _SineSeries<0,0,0,0> {
	public:
	    static inline float accumulate() {
	    	return 1;
	    }
	};
	// - -------------------------------------------------------------------------------------- - //
	// Template Math - Sine function. 
	// Usage (45 degrees): float f = TemplateSine<360,45>::sin();
	// - -------------------------------------------------------------------------------------- - //
	template<int N, int I>
	class TemplateSine {
	public:
		//enum { M_PI = 3.1415926535897932384626433832795 };
		
	    static inline float sin() {
	        return (I*2*M_PI/N) * _SineSeries<N,I,10,0>::accumulate();
	    }
	};
	// - -------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
// This set is used for straight duplicate overloading of types, such as the float/Real wrapper //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Real& operator _OP_ ( const Real& _Vs ) { \
		Data _OP_ _Vs.Data; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( _OP_ ) \
	inline const Real& operator _OP_ () { \
		_OP_ Data; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( _OP_ ) \
	inline const Real operator _OP_ ( int ) { \
		return Data _OP_; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_OPERATOR( _OP_ ) \
	inline const bool operator _OP_ ( const Real& _Vs ) const { \
		return Data _OP_ _Vs.Data; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOL_OPERATOR( _OP_ ) \
	inline const Real operator _OP_ ( const Real& _Vs ) const { \
		return Data _OP_ _Vs.Data; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A type to wrap a floating point type (float/double) //
// - ------------------------------------------------------------------------------------------ - //
class Real {
	// - -------------------------------------------------------------------------------------- - //
	typedef float _RealType;
	// - -------------------------------------------------------------------------------------- - //	
	// Our actual data contents // 
	_RealType Data;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Real Identity;
	static const Real Zero;
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Other constants special to this type //
	// - -------------------------------------------------------------------------------------- - //
	static const Real One;
	static const Real Half;
	static const Real Quarter;
	static const Real SmallestUnit;
	
	static const Real Pi;
	static const Real TwoPi;
	
	static const Real Sin45;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Real() :
		Data( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real( const _RealType& _Data ) :
		Data( _Data )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Set( const Real& _Vs ) {
		Data = _Vs.Data;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Covert all reals into our floating point type automatically //
	// - -------------------------------------------------------------------------------------- - //
	// Might need a non const float returning variant //
	inline operator const _RealType () const {
		return Data;	
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators, essentially a wrapping for float/double's normal operators //
	// - -------------------------------------------------------------------------------------- - //
	OVERLOAD_SYMBOLEQUALS_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( -= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( /= );

	OVERLOAD_SYMBOL_OPERATOR( + );
	OVERLOAD_SYMBOL_OPERATOR( - );
	OVERLOAD_SYMBOL_OPERATOR( * );
	OVERLOAD_SYMBOL_OPERATOR( / );

	OVERLOAD_TEST_OPERATOR( == );
	OVERLOAD_TEST_OPERATOR( != );
	OVERLOAD_TEST_OPERATOR( <= );
	OVERLOAD_TEST_OPERATOR( >= );
	
	OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( ++ );
	OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( -- );

	OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( ++ );
	OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( -- );
	// - -------------------------------------------------------------------------------------- - //
	// Dot Product //
	inline const Real operator - ( ) const {
		return -Data;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline void Normalize() {
		if ( Data > Zero )
			Data = One;
		else if ( Data < Zero )
			Data = -One;
		else
			Data = Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real NormalizeRet() {
		Real Temp( *this );
		if ( Data > Zero )
			Data = One;
		else if ( Data < Zero ) {
			Data = -One;
			Temp = -Temp;
		}
		else
			Data = Zero;
		return Temp;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Real Normal() const {
		if ( Data > Zero )
			return One;
		else if ( Data < Zero )
			return -One;
		else
			return Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const Real Magnitude() const {
		return Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Real MagnitudeSquared() const {
		return Data * Data;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// No Dot or Cross, as their's not enough axis for tangents //
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Min( const Real& _Vs ) const {
		Real Number = *this;
		if ( Number > _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real Max( const Real& _Vs ) const {
		Real Number = *this;
		if ( Number < _Vs )
			return _Vs;
		return Number;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& Minimize( const Real& _Vs ) {
		if ( *this > _Vs )
			*this = _Vs;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& Maximize( const Real& _Vs ) {
		if ( *this < _Vs )
			*this = _Vs;
		return *this;
	}	
	// - -------------------------------------------------------------------------------------- - //
	static inline const Real Min( const Real& a, const Real& b ) {
		if ( a > b )
			return b;
		return a;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Real Max( const Real& a, const Real& b ) {
		if ( a < b )
			return b;
		return a;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
//	inline const Real Range( const Real& _Min, const Real& _Max ) const {
	inline const Real Clamp( const Real& _Min, const Real& _Max ) const {
		Real Number = *this;
		// Min //
		if ( Number < _Min )
			return _Min;
		// Max //
		if ( Number > _Max )
			return _Max;
		return Number;
	}
//	// - -------------------------------------------------------------------------------------- - //
//	inline Real& RangeClamp( const Real& _Min, const Real& _Max ) {
//		// Min //
//		if ( *this < _Min )
//			*this = _Min;
//		// Max //
//		if ( *this > _Max )
//			*this = _Max;
//		return *this;
//	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool InRange( const Real& _Min, const Real& _Max ) const {
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
	inline const Real Abs() const {
		if ( Data < Zero )
			return -Data;
		else
			return Data;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const Real Sqrt() const {
		if ( !IsZero() )
			return std::sqrt( *this );
		else
			return Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Sine //
	inline const Real Sin() const {
		return std::sin( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Cosine //
	inline const Real Cos() const {
		return std::cos( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Tangent //
	inline const Real Tan() const {
		return std::tan( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Arc Tangent //
	inline const Real ArcTan() const {
		return std::atan( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// SawTooth Wave   /| /|
	//                / |/ | (2 periods shown, 0-1)
	inline const Real SawTooth() const {
		return *this - Floor(*this);
	}
	// - -------------------------------------------------------------------------------------- - //
	// InvSawTooth Wave  |\ |\  .
	//                   | \| \ (2 periods shown, 0-1)
	inline const Real InvSawTooth() const {
		return (Real::One - *this).SawTooth();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Saw Wave  /\  /\  .
	//          /  \/  \ (2 periods shown, 0-1)
	// A period of 0 and 1 return a Sawtooth like curve //
	inline const Real Saw( const Real& Period = Real::Half ) const {
		const Real Wave = SawTooth();
		
		if (Wave >= Period)
			// A period of 1 should be caught by the floor, wrapping it back to zero) //
			return Real::One - ((Wave - Period) / (Real::One - Period));
		else
			// If period is zero, the above should catch it, avoiding our division by zero //
			return Wave / Period;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Wave  |-| |-| 
	//             _| |_| | (2 periods shown, 0-1)
	// A period of 0 and 1 return constantly high //
	inline const Real Square( const Real& Period = Real::Half ) const {
		const Real Wave = SawTooth();
		
		if (Wave >= Period)
			return Real::One;
		else
			return Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Expands a value from 0-1 to -1 to +1 //
	inline const Real Expand() const {
		return (*this * Real(2)) - Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Compacts a value from -1 to +1 to 0-1 //
	inline const Real Compact() const {
		return (*this * Real::Half) + Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Clamps a value from 0-1 //
	inline const Real Clamp() const {
		if ( *this <= Real::Zero )
			return Real::Zero;
		else if ( *this >= Real::One )
			return Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inversely Clamps values outside 0-1 to their opposite //
	inline const Real InvClamp() const {
		if ( *this <= Real::Zero )
			return Real::One;
		else if ( *this >= Real::One )
			return Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// *** TIP *** - Interpolation functions can be called more than once for greater impact! //
	// - -------------------------------------------------------------------------------------- - //
	// Linear Interpolation  /
	//                      /  (DOES NOT CLAMP! Use Lerp() instead) 
	inline const Real _Lerp() const {
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Linear Interpolation \   .
	//                               \  (DOES NOT CLAMP! Use InvLerp() instead) 
	inline const Real _InvLerp() const {			
		return (Real::One - *this)._Lerp();
	}
	// - -------------------------------------------------------------------------------------- - //
	// SmoothStep Interpolation   /'
	//                          ,/   (DOES NOT CLAMP! Use SmoothStep() instead) 
	inline const Real _SmoothStep() const {
		return (*this) * (*this) * (Real(3) - (Real(2) * (*this)));
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse SmoothStep Interpolation '\   .
	//                                    \. (DOES NOT CLAMP! Use InvSmoothStep() instead) 
	inline const Real _InvSmoothStep() const {
		return (Real::One - *this)._SmoothStep();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-In Interpolation  .-'`
	//                       /   (DOES NOT CLAMP! Use EaseIn() instead) 
	inline const Real _EaseIn() const {
		return (*this) * (*this);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-More-In Interpolation  .-'`
	//                            /   (DOES NOT CLAMP! Use EaseMoreOut() instead) 
	inline const Real _EaseMoreIn() const {
		return (*this) * (*this) * (*this);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-Out Interpolation    /
	//                        .,/   (DOES NOT CLAMP! Use EaseIn() instead) 
	inline const Real _EaseOut() const {
		return Real::One - (Real::One - *this) * (Real::One - *this);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-More-Out Interpolation    /
	//                             .,/   (DOES NOT CLAMP! Use EaseMoreOut() instead) 
	inline const Real _EaseMoreOut() const {
		return Real::One - (Real::One - *this) * (Real::One - *this) * (Real::One - *this);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real _InvEaseIn() const {
		return (Real::One - *this)._EaseIn();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real _InvEaseOut() const {
		return (Real::One - *this)._EaseOut();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real _InvEaseMoreIn() const {
		return (Real::One - *this)._EaseMoreIn();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real _InvEaseMoreOut() const {
		return (Real::One - *this)._EaseMoreOut();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	#define ZERO_ONE_CLAMP() \
		if ( *this <= Real::Zero ) \
			return Real::Zero; \
		else if ( *this >= Real::One ) \
			return Real::One;
	// - -------------------------------------------------------------------------------------- - //
	#define ONE_ZERO_CLAMP() \
		if ( *this <= Real::Zero ) \
			return Real::One; \
		else if ( *this >= Real::One ) \
			return Real::Zero;
	// - -------------------------------------------------------------------------------------- - //
	// Linear Interpolation    /--
	//                      __/    (clamps at 0 and 1) 
	inline const Real Lerp() const {
		ZERO_ONE_CLAMP();
		return _Lerp();
	}
	// - -------------------------------------------------------------------------------------- - //
	// SmoothStep Interpolation     /'--
	//                          __,/    (clamps at 0 and 1) 
	inline const Real SmoothStep() const {
		ZERO_ONE_CLAMP();
		return _SmoothStep();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Linear Interpolation --\    .
	//                                 \__ (clamps at 0 and 1) 
	inline const Real InvLerp() const {
		ONE_ZERO_CLAMP();
		return _InvLerp();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse SmoothStep Interpolation --'\     .
	//                                      \.__ (clamps at 0 and 1) 
	inline const Real InvSmoothStep() const {
		ONE_ZERO_CLAMP();
		return _InvSmoothStep();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-In Interpolation  .-'`
	//                       /      (clamps at 0 and 1) 
	inline const Real EaseIn() const {
		ZERO_ONE_CLAMP();
		return _EaseIn();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-Out Interpolation    / 
	//                        .,/   (clamps at 0 and 1) 
	inline const Real EaseOut() const {
		ZERO_ONE_CLAMP();
		return _EaseOut();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-In Interpolation  .-'`
	//                       /      (clamps at 0 and 1) 
	inline const Real EaseMoreIn() const {
		ZERO_ONE_CLAMP();
		return _EaseMoreIn();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ease-Out Interpolation    /
	//                        .,/   (clamps at 0 and 1) 
	inline const Real EaseMoreOut() const {
		ZERO_ONE_CLAMP();
		return _EaseMoreOut();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real InvEaseIn() const {
		ONE_ZERO_CLAMP();
		return _InvEaseIn();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real InvEaseOut() const {
		ONE_ZERO_CLAMP();
		return _InvEaseOut();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real InvEaseMoreIn() const {
		ONE_ZERO_CLAMP();
		return _InvEaseMoreIn();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real InvEaseMoreOut() const {
		ONE_ZERO_CLAMP();
		return _InvEaseMoreOut();
	}
	// - -------------------------------------------------------------------------------------- - //
	#undef ONE_ZERO_CLAMP
	#undef ZERO_ONE_CLAMP
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Floor //
	inline const Real Floor() const {
		return std::floor( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ceil //
	inline const Real Ceil() const {
		return std::ceil( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Round //
	inline const Real Round() const {
		if ( (*this - this->Floor()) > Real::Half )
			return this->Ceil();
		else
			return this->Floor();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Square Root ( 1 / sqrt(Value) ) //
//	inline const Real InvSqrt() const {
//		if ( !this->IsZero() )
//			return std::sqrt( *this );
//		else
//			return Real::Zero;
//	}
	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		//return *this == Real::Zero;
		return (*this).Abs() < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroPositive() const {
		//return *this == Real::Zero;
		return *this < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const bool Is( const Real& _Vs ) const {
		//return (*this - _Vs) == Real::Zero;
		return (*this - _Vs).Abs() < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Specific Functions that apply to this type //
	// - -------------------------------------------------------------------------------------- - //
	inline static const Real Abs( _RealType Value ) {
		if ( Real(Value) < Zero )
			return -Real(Value);
		else
			return Real(Value);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline static const Real Sqrt( _RealType Value ) {
		if ( !IsZero( Value ) )
			return std::sqrt( Value );
		else
			return Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Sine //
	inline static const Real Sin( _RealType Value ) {
		return std::sin( Value * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Cosine //
	inline static const Real Cos( _RealType Value ) {
		return std::cos( Value * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Tangent //
	inline static const Real Tan( _RealType Value ) {
		return std::tan( Value * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Floor //
	inline static const Real Floor( _RealType Value ) {
		return std::floor( Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Ceil //
	inline static const Real Ceil( _RealType Value ) {
		return std::ceil( Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Round //
	inline static const Real Round( _RealType Value ) {
		if ( (Value - Floor(Value)) > Real::Half )
			return Ceil(Value);
		else
			return Floor(Value);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Square Root ( 1 / sqrt(Value) ) //
//	inline static const Real InvSqrt( float Value ) {
//		if ( IsZero( Value ) )
//			return std::sqrt( Value );
//		else
//			return Real::Zero;
//	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const bool IsZero( _RealType Value ) {
		//return *this == Real::Zero;
		return Abs(Value) < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline static const bool IsZeroPositive( _RealType Value ) {
		return Value < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	

	// Random Numbers //
	static Real Random();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR
#undef OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR
#undef OVERLOAD_TEST_OPERATOR
#undef OVERLOAD_SYMBOL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Real_H__ //
// - ------------------------------------------------------------------------------------------ - //
