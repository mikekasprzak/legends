// - ------------------------------------------------------------------------------------------ - //
// Real //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Real_H__
#define __Geometry_Real_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Decide what to do about Function(Value) functions. There are many Value.Function()
//       versions, and that may not be the ideal approach (shitty syntax for A * B pairs).
// TODO: If all functions become isolated Function(Value) types, make the Value.Function()
//       version of these functions call Function(Value), so not to repeat code.
// TODO: Consider making lower case 'function(value)' versions that deal with floats and doubles.
//       Design these to be Ansi C Math library compatible. Call them here.
// TODO: Remove the sine templates. I have no qualms with realtime calculation of this.
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <cmath>
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4305) // Truncation
#pragma warning (disable : 4244) // Tructation, data loss potential 
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
//	// - -------------------------------------------------------------------------------------- - //
//	// Compute J terms in the series expansion.  K is the loop variable.
//	template<int N, int I, int J, int K>
//	class _SineSeries {
//	public:
//		//enum { M_PI = 3.1415926535897932384626433832795 };
//	    enum { go = (K+1 != J) };
//	
//	    static inline float accumulate() {
//	        return 1-(I*2*M_PI/N)*(I*2*M_PI/N)/(2*K+2)/(2*K+3) *
//	            _SineSeries<N*go,I*go,J*go,(K+1)*go>::accumulate();
//	    }
//	};
//	// - -------------------------------------------------------------------------------------- - //
//	// Specialization to terminate loop
//	template<>
//	class _SineSeries<0,0,0,0> {
//	public:
//	    static inline float accumulate() {
//	    	return 1;
//	    }
//	};
//	// - -------------------------------------------------------------------------------------- - //
//	// Template Math - Sine function. 
//	// Usage (45 degrees): float f = TemplateSine<360,45>::sin();
//	// - -------------------------------------------------------------------------------------- - //
//	template<int N, int I>
//	class TemplateSine {
//	public:
//		//enum { M_PI = 3.1415926535897932384626433832795 };
//		
//	    static inline float sin() {
//	        return (I*2*M_PI/N) * _SineSeries<N,I,10,0>::accumulate();
//	    }
//	};
//	// - -------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
// This set is used for straight duplicate overloading of types, such as the float/Real wrapper //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Real& operator _OP_ ( const Real& _Vs ) { \
		x _OP_ _Vs.x; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLPREFIX_OPERATOR( _OP_ ) \
	inline const Real& operator _OP_ () { \
		_OP_ x; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLSYMBOLSUFFIX_OPERATOR( _OP_ ) \
	inline const Real operator _OP_ ( int ) { \
		return x _OP_; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_TEST_OPERATOR( _OP_ ) \
	inline const bool operator _OP_ ( const Real& _Vs ) const { \
		return x _OP_ _Vs.x; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOL_OPERATOR( _OP_ ) \
	inline const Real operator _OP_ ( const Real& _Vs ) const { \
		return x _OP_ _Vs.x; \
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
	// Our actual data contents -- NEW: Renamed "Data" to "x", to be vector friendly // 
	_RealType x;
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
	static const Real Two;
	static const Real Four;
	static const Real Half;
	static const Real Quarter;
	static const Real SmallestUnit;

	static const Real Three;
	static const Real ThreeQuarter;
	static const Real Third;
	
	static const Real Pi;
	static const Real TwoPi;		// (Pi + Pi)
	static const Real HalfPi;		// (Pi / 2)
	static const Real QuarterPi;	// (Pi / 4)
	static const Real InvPi; 		// (1 / Pi)
	static const Real InvTwoPi;		// (1 / TwoPi)
	static const Real InvHalfPi;	// (1 / HalfPi)
	static const Real InvQuarterPi;	// (1 / QuarterPi)
	
	static const Real e;			// Euler's Number/Napier's Constant. Used in Natural Logarithms (log)
	
	static const Real Sin45;		// Precomputed value of a 45 degree angle //
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Real() :
		x( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real( const _RealType& _x ) :
		x( _x )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Set( const Real& _Vs ) {
		x = _Vs.x;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Covert all reals into our floating point type automatically //
	// - -------------------------------------------------------------------------------------- - //
	// Might need a non const float returning variant //
	inline operator const _RealType () const {
		return x;	
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
	// Negative //
	inline const Real operator - ( ) const {
		return -x;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline void Normalize() {
		if ( x > Zero )
			x = One;
		else if ( x < Zero )
			x = -One;
		else
			x = Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real NormalizeRet() {
		Real Temp( *this );
		if ( x > Zero )
			x = One;
		else if ( x < Zero ) {
			x = -One;
			Temp = -Temp;
		}
		else
			x = Zero;
		return Temp;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Real Normal() const {
		if ( x > Zero )
			return One;
		else if ( x < Zero )
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
		return x * x;
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
		if ( x < Zero )
			return -x;
		else
			return x;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const Real Sqrt() const {
		if ( IsZero() )
			return Real::Zero;
		else
			return std::sqrt( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline const Real Sqrt_() const {
		return std::sqrt( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	// TODO: Pow, Cubert (Cube Root)
	// TODO: ldexp (load exponent, build a floating point number), frexp (read), modf (extract fmod)
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Signal Conversion to/from [0,1] and [-1,+1] //
	// - -------------------------------------------------------------------------------------- - //
	// Expands a value from [0,1] to [-1,+1] //
	inline const Real Expand() const {
		return (*this * Real(2)) - Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Compacts a value from [-1,+1] to [0,1] //
	inline const Real Compact() const {
		return (*this * Real::Half) + Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Simple Math //
	// - -------------------------------------------------------------------------------------- - //
	// Double the value //
	inline const Real CalcDouble() const {
		return *this + *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Triple the value //
	inline const Real CalcTriple() const {
		return *this + *this + *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Quadruple the value //
	inline const Real CalcQuadruple() const {
		return *this * Real::Four;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Half the value //
	inline const Real CalcHalf() const {
		return *this * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Third the value //
	inline const Real CalcThird() const {
		return *this * Real::Third;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Quarter the value //
	inline const Real CalcQuarter() const {
		return *this * Real::Quarter;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Power of Two - Square (sqr) //
	inline const Real Pow2() const {
		return *this * *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Power of Three - Cube (cube) //
	inline const Real Pow3() const {
		return *this * *this * *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	// TODO: Power, Summation (Sigma), Product (uppercase Pi)
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// LOGARITHM NOTES //
	//   10^x (TenPowX) is a significant quantity when dealing with logarithms. //
	//   10^2 = 100, Log(100) = 2. 10^3 = 1000, Log(1000) = 3. //
	//   The "10" represents the base of the number system.
	//   C standard library has a log10() function for doing this (Common Base-10).
	//   C standard also has log() function (Neutral Base-E). "Inverse of the Natural Exponent Func"
	//   It is related to the exp() function (Base-E Exponent)... which is not the same thing as pow()
	//   The "ln" is the natural logarithm function on the calculator!!
	//   To calculate Log2(n) (Binary Logarithm), do either ln(n)/ln(2) or log10(n)/log10(2) //
	//   e is a mathematical constant. It's where, after smartness, the logarithm base intersects 1.
	//   e is Napier's Constant or Euler's Number, not to be confused with Euler's Constant.
	//   http://en.wikipedia.org/wiki/E_%28mathematical_constant%29
	//
	//   [Base 2] Binary Logarithm  -- No Function, but can be calculated with func(n)/func(2)
	//   [Base e] Natural Logarithm -- log(n) in C, ln(n) on Calculator. e is Euler's Number.
	//   [Base 10] Common Logarithm -- log10(n) in C, log(n) on Calculator. Paired with 10^x.
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Power functions to contrast the various logarithm bases //
	// - -------------------------------------------------------------------------------------- - //
	inline const Real TwoPow() const {
		return std::pow( 2, *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real NaturalPow() const { 
		return std::exp( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real OctPow() const {
		return std::pow( 8, *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real TenPow() const {
		return std::pow( 10, *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HexPow() const {
		return std::pow( 16, *this );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// I'm assuming "log10" is the faster logarithm function. If wrong, make it log. 
	// - -------------------------------------------------------------------------------------- - //
	inline const Real TwoLog() const {
		return (float)std::log10( *this ) * (float)std::log10( 2 );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real NaturalLog() const {
		return std::log( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real OctLog() const {
		return (float)std::log10( *this ) * (float)std::log10( 8 );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real TenLog() const {
		return std::log10( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real HexLog() const {
		return (float)std::log10( *this ) * (float)std::log10( 16 );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Repeating Patterns //
	// - -------------------------------------------------------------------------------------- - //
	// Sine - Input *[0,1] -- Output *[-1,+1] //
	inline const Real Sin() const {
		return std::sin( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Cosine - Input *[0,1] -- Output *[-1,+1] //
	inline const Real Cos() const {
		return std::cos( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// ArcSine and ArcCosine are only partial inverses of Sine and Cosine. They are non-repeating.
	// They are used to partially get the curve of Sine and Cosine but about the opposite axis.
	// They are NOT full waves, despite the input of two iterations [-1,+1], you get two halfs. //
	// - -------------------------------------------------------------------------------------- - //
	// ArcSine - Input [-1,+1] -- Output [-.5,+.5]
	inline const Real ArcSin() const {
		return std::asin( *this ) * Real::InvPi;// / Real::Pi; // Optimization //
	}
	// - -------------------------------------------------------------------------------------- - //
	// ArcCosine - Input [-1,+1] -- Output [0,1]
	inline const Real ArcCos() const {
		return std::acos( *this ) * Real::InvPi;// / Real::Pi; // Optimization //
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// TODO: Update these //
	// TODO: Add Cotangent, Secant, Cosecant... all are weird-ass waveforms like Tangent //
	// TODO: Add Hyperbolic functions (sinh, cosh)... though they're also weird-ass like Tangent //
	// - -------------------------------------------------------------------------------------- - //
	// Tangent - Input *[0,1] -- Output *[-?,+?] //
	inline const Real Tan() const {
		return std::tan( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Arc Tangent - Input *[0,1] -- Output *[-?,+?] //
	inline const Real ArcTan() const {
		return std::atan( *this * Real::TwoPi );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// ArcTan2 (atan2) can be found outside, since it takes 2 arguments (y,x) //
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// SawTooth Wave  /| /|
	//               / |/ | -- 2 periods shown - Input *[0,1] -- Output *[0,1]
	inline const Real SawTooth() const {
		return *this - Floor(*this);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse SawTooth Wave |\ |\																  //
	//                       | \| \ -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	inline const Real InvSawTooth() const {
		return Real::One - SawTooth();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Triangle Wave  /\  /\																	  //
	//               /  \/  \ -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	inline const Real Triangle() const {
		Real Period = SawTooth() * Real::Two; // Get a 0-2 range //
		
		if ( Period >= Real::One )
			return Period.InvSawTooth(); // Period 1-2 goes down //
		else
			return Period.SawTooth();    // Period 0-1 goes up //
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Triangle Wave \  /\  /
	//                        \/  \/  -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	inline const Real InvTriangle() const {
		return Real::One - Triangle();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Wave  |-| |-    This is different than clamping. You may want that instead.
	//             _| |_|  -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	inline const Real Square() const {
		return SawTooth().Round();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Square Wave -| |-| 
	//                      |_| |_ -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	inline const Real InvSquare() const {
		return Real::One - Square();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Circle Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real Circle() const {
		return CalcHalf().Sin().Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Circle Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real InvCircle() const {
		return Real::One - Circle();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cosine Circle Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real CoCircle() const {
		return CalcHalf().Cos().Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Cosine Circle Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real InvCoCircle() const {
		return Real::One - CoCircle();
	}
	// - -------------------------------------------------------------------------------------- - //

	// TODO: Figure out which of these are Ease In's and Ease Out's //
	// - -------------------------------------------------------------------------------------- - //
	// Circle Tooth Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real CircleTooth() const {
		return SawTooth().CalcQuarter().Sin().Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Circle Tooth Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real InvCircleTooth() const {
		return Real::One - CircleTooth();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cosine Circle Tooth Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real CoCircleTooth() const {
		return SawTooth().CalcQuarter().Cos().Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Inverse Cosine Circle Tooth Wave -- Input *[0,1] -- Output *[0,1]
	inline const Real InvCoCircleTooth() const {
		return Real::One - CoCircleTooth();
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Sine and Cosine family waveform functions //
	// NOTE: Sine and Cosine family functions lack Inverse functions, but can flip the waveform 
	//       by simply negating the returned value!
	// - -------------------------------------------------------------------------------------- - //
	// Sine Triangle Wave /\  /\      Starts at 0 following a rigid wave similar to Sine.
	//                      \/  \/ -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real SinTriangle() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return Period - Real(3+1); // Period 3-4 starts at -1 and goes up //
		else if ( Period >= Real(1) )
			return Real::One - (Period - Real(1)); // Periods 1-2 and 2-3 go the same way //
		else
			return Period; // Period 0-1 is the same as a SawTooth //
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cosine Triangle Wave \  /\  /    Similar to InvTriangle(), except with negative ranges.
	//                       \/  \/  -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real CosTriangle() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(2) )
			return Period - Real(2+1); // Periods 2-3 and 3-4 start at -1 and go the same way //
		else
			return Real::One - Period; // Periods 0-1 and 1-2 start at +1 and go the same way //
	}
	// - -------------------------------------------------------------------------------------- - //
	// Sine Square Wave _|-|_   _|-|_ 
	//                       |_|     |_| -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real SinSquare() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return -Period.InvSquare();
		else if ( Period >= Real(2) )
			return -Period.Square();
		else if ( Period >= Real(1) )
			return Period.InvSquare();
		else
			return Period.Square();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cosine Square Wave -|_   _|-|_   _|
	//                       |_|     |_|   -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real CosSquare() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return Period.Square();
		else if ( Period >= Real(2) )
			return -Period.InvSquare();
		else if ( Period >= Real(1) )
			return -Period.Square();
		else
			return Period.InvSquare();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Sine Saw Tooth Wave /| /|     Different from SinTriangle(). Ups take 2x as long, then drop.
	//                      |/ |/ -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real SinSawTooth() const {
		Real Period = SawTooth() * Real(2); // Get a 0-2 range //
		
		if ( Period >= Real(1) )
			return Period.SawTooth() - Real::One;
		else
			return Period.SawTooth();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cosine Saw Tooth Wave '| /| ,    *NOTE* WEIRD! A slightly forward offset SinSawTooth()
	//                        |/ |/  -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real CosSawTooth() const {
		return Real( *this + Real::Quarter ).SinSawTooth();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Sine Tooth Wave  /| /|    Since true CosSawTooth is strange, this is what you expect.
	//                 / |/ | -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real SinTooth() const {
		return SawTooth().Expand();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cosine Tooth Wave  /| /|     *NOTE* WEIRD! A slightly forward offset SinTooth()
	//                   ' |/ |, -- 2 periods shown -- Input *[0,1] -- Output *[-1,+1]
	inline const Real CosTooth() const {
		return Real( *this + Real::Quarter ).SinTooth();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Pulse Waves -- Waveforms with a controllable HalfPeriod, which is the midpoint of the waveform //
	// - -------------------------------------------------------------------------------------- - //
	// Triangle Pulse Wave  /\  /\  															  //
	//                     /  \/  \ -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	// A period of 0 and 1 return a Sawtooth like curve //
	inline const Real TrianglePulse( const Real& HalfPeriod = Real::Half ) const {
		const Real Wave = SawTooth();
		
		if (Wave >= HalfPeriod)
			// A HalfPeriod of 1 should be caught by the floor, wrapping it back to zero) //
			return Real::One - ((Wave - HalfPeriod) / (Real::One - HalfPeriod));
		else
			// If HalfPeriod is zero, the above should catch it, avoiding our division by zero //
			return Wave / HalfPeriod;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Pulse Wave  |-| |-| 
	//                   _| |_| | -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	// A period of 0 and 1 return constantly high //
	inline const Real SquarePulse( const Real& HalfPeriod = Real::Half ) const {
		const Real Wave = SawTooth();
		
		if (Wave >= HalfPeriod)
			// A HalfPeriod of 1 should be caught by the floor, wrapping it back to zero) //
			return Real::One;
		else
			// If HalfPeriod is zero, the above should catch it, avoiding our division by zero //
			return Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Linear Interpolation Pulse  /| /|    A SawTooth() where you control the midpoint (0.5) interpolation rate.
	//                            / |/ | -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	inline const Real LerpPulse( const Real& HalfPeriod = Real::Half ) const {
		const Real Wave = SawTooth();
		
		if (Wave >= HalfPeriod)
			// A HalfPeriod of 1 should be caught by the floor, wrapping it back to zero) //
			return Real::Half + (((Wave - HalfPeriod) / (Real::One - HalfPeriod)) * Real::Half);
		else
			// If HalfPeriod is zero, the above should catch it, avoiding our division by zero //
			return (Wave / HalfPeriod) * Real::Half;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Double Saw Tooth Pulse  /| /| /| /|    A single SawTooth Pulse is useless, so here's two.
	//                        / |/ |/ |/ | -- 2 periods shown -- Input *[0,1] -- Output *[0,1]
	inline const Real DoubleSawToothPulse( const Real& HalfPeriod = Real::Half ) const {
		const Real Wave = SawTooth();
		
		if (Wave >= HalfPeriod)
			// A HalfPeriod of 1 should be caught by the floor, wrapping it back to zero) //
			return ((Wave - HalfPeriod) / (Real::One - HalfPeriod));
		else
			// If HalfPeriod is zero, the above should catch it, avoiding our division by zero //
			return Wave / HalfPeriod;
	}
	// - -------------------------------------------------------------------------------------- - //
	

	// - -------------------------------------------------------------------------------------- - //
	// Parabolic Curve Sine and Cosine family waveform functions //
	// NOTE: Sine and Cosine family functions lack Inverse functions, but can flip the waveform 
	//       by simply negating the returned value!
	// - -------------------------------------------------------------------------------------- - //
	// Sin Parabolic Curve "Smooth Step" -- Slowly leaves and reaches extreme, with brief stops.
	inline const Real SinSmoothStep() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return -Period.SawTooth()._InvSmoothStep();
		else if ( Period >= Real(2) )
			return -Period.SawTooth()._SmoothStep();
		else if ( Period >= Real(1) )
			return Period.SawTooth()._InvSmoothStep();
		else
			return Period.SawTooth()._SmoothStep();
	}		
	// - -------------------------------------------------------------------------------------- - //
	// Sin Parabolic Curve "Ease In" -- Slowly reaches extreme, with a brief stop.
	inline const Real SinEaseIn() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return -Period.SawTooth()._InvEaseOut();
		else if ( Period >= Real(2) )
			return -Period.SawTooth()._EaseIn();
		else if ( Period >= Real(1) )
			return Period.SawTooth()._InvEaseOut();
		else
			return Period.SawTooth()._EaseIn();
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Sin Parabolic Curve "Ease In" Tooth -- Hits the tooth and turns around.
	inline const Real SinEaseInTooth() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return -Period.SawTooth()._InvEaseIn();
		else if ( Period >= Real(2) )
			return -Period.SawTooth()._EaseIn();
		else if ( Period >= Real(1) )
			return Period.SawTooth()._InvEaseIn();
		else
			return Period.SawTooth()._EaseIn();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Sin Parabolic Curve "Ease Out" -- Quickly reaches extreme, with a brief stop.
	inline const Real SinEaseOut() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return -Period.SawTooth()._InvEaseIn();
		else if ( Period >= Real(2) )
			return -Period.SawTooth()._EaseOut();
		else if ( Period >= Real(1) )
			return Period.SawTooth()._InvEaseIn();
		else
			return Period.SawTooth()._EaseOut();
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Sin Parabolic Curve "Ease Out" Tooth -- NOTE: A decent approximation for SIN!
	inline const Real SinEaseOutTooth() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(3) )
			return -Period.SawTooth()._InvEaseOut();
		else if ( Period >= Real(2) )
			return -Period.SawTooth()._EaseOut();
		else if ( Period >= Real(1) )
			return Period.SawTooth()._InvEaseOut();
		else
			return Period.SawTooth()._EaseOut();
	}
	// - -------------------------------------------------------------------------------------- - //
	// TODO: Cosine Versions //
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Experiments //
	// - -------------------------------------------------------------------------------------- - //
	// NOTES: The Ease In makes it accelerate fast, but the trasition to Triangle abruptly slows it.
	//        This is probably not useful. An ideal alternative would be to Mix or feed values in
	//        to Triangle itself.
	inline const Real SinEaseInToTriangle() const {
		Real Period = SawTooth() * Real(4); // Get a 0-4 range //
		
		if ( Period >= Real(1) )
			return SinTriangle();
		else
			return Period.SawTooth().CalcQuarter().Sin();//_EaseIn();
	}	
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
//	// Clamps a value from 0-1 //
//	inline const Real Clamp() const {
//		if ( *this <= Real::Zero )
//			return Real::Zero;
//		else if ( *this >= Real::One )
//			return Real::One;
//		return *this;
//	}
//	// - -------------------------------------------------------------------------------------- - //
//	// Inversely Clamps values outside 0-1 to their opposite //
//	inline const Real InvClamp() const {
//		if ( *this <= Real::Zero )
//			return Real::One;
//		else if ( *this >= Real::One )
//			return Real::Zero;
//		return *this;
//	}
//	// - -------------------------------------------------------------------------------------- - //

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
	// These are Macros so that the code is pasted. Typically, the line that follows is a return. // 
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

	// - -------------------------------------------------------------------------------------- - //
	// Simple Clamping of values between 0 and 1  //
	inline const Real Clamp() const {
		ZERO_ONE_CLAMP();
		return *this;
	}
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
		return (*this).Abs() <= Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroOrLess() const {
		//return *this == Real::Zero;
		return *this <= Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const bool Is( const Real& _Vs ) const {
		//return (*this - _Vs) == Real::Zero;
		return (*this - _Vs).Abs() <= Real::SmallestUnit;
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
		if ( IsZero( Value ) )
			return Real::Zero;
		else
			return std::sqrt( Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Square Root //
	inline static const Real Sqrt_( _RealType Value ) {
		return std::sqrt( Value );
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
	inline static const bool IsZeroOrLess( _RealType Value ) {
		return Value < Real::SmallestUnit;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Due to some signature issues, printf needs an explicit function for converting to float. //
	// - -------------------------------------------------------------------------------------- - //
	inline const float ToFloat() const {
		return x;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// WARNING: A limit of 64 ToString calls can be made at a time, otherwise returned values may be bad //
	inline const char* ToString() const {
		static char Text[64][128];		// 64 slots, 128 chars long (8,192 bytes). An Int is 10 chars long max. //
		static int CurrentText = 0;
		CurrentText++;
		CurrentText &= 63;
		
		safe_sprintf( Text[CurrentText], sizeof(Text[CurrentText]), "%f", x );
		return Text[CurrentText];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Swizzle //
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
	SWIZZLE2_PROTO( class Vector2D, x,x );
	SWIZZLE3_PROTO( class Vector3D, x,x,x );
	SWIZZLE4_PROTO( class Vector4D, x,x,x,x );

	_SWIZZLE2_PROTO( class Vector2D, x,x );
	_SWIZZLE2_PROTO( class Vector2D, x,0 );
	_SWIZZLE2_PROTO( class Vector2D, x,1 );
	_SWIZZLE2_PROTO( class Vector2D, 0,x );
	_SWIZZLE2_PROTO( class Vector2D, 0,0 );
	_SWIZZLE2_PROTO( class Vector2D, 0,1 );
	_SWIZZLE2_PROTO( class Vector2D, 1,x );
	_SWIZZLE2_PROTO( class Vector2D, 1,0 );
	_SWIZZLE2_PROTO( class Vector2D, 1,1 );

	_SWIZZLE3_PROTO( class Vector3D, x,x,x );
	_SWIZZLE3_PROTO( class Vector3D, x,x,0 );
	_SWIZZLE3_PROTO( class Vector3D, x,x,1 );
	_SWIZZLE3_PROTO( class Vector3D, x,0,x );
	_SWIZZLE3_PROTO( class Vector3D, x,0,0 );
	_SWIZZLE3_PROTO( class Vector3D, x,0,1 );
	_SWIZZLE3_PROTO( class Vector3D, x,1,x );
	_SWIZZLE3_PROTO( class Vector3D, x,1,0 );
	_SWIZZLE3_PROTO( class Vector3D, x,1,1 );
	_SWIZZLE3_PROTO( class Vector3D, 0,x,x );
	_SWIZZLE3_PROTO( class Vector3D, 0,x,0 );
	_SWIZZLE3_PROTO( class Vector3D, 0,x,1 );
	_SWIZZLE3_PROTO( class Vector3D, 0,0,x );
	_SWIZZLE3_PROTO( class Vector3D, 0,0,0 );
	_SWIZZLE3_PROTO( class Vector3D, 0,0,1 );
	_SWIZZLE3_PROTO( class Vector3D, 0,1,x );
	_SWIZZLE3_PROTO( class Vector3D, 0,1,0 );
	_SWIZZLE3_PROTO( class Vector3D, 0,1,1 );
	_SWIZZLE3_PROTO( class Vector3D, 1,x,x );
	_SWIZZLE3_PROTO( class Vector3D, 1,x,0 );
	_SWIZZLE3_PROTO( class Vector3D, 1,x,1 );
	_SWIZZLE3_PROTO( class Vector3D, 1,0,x );
	_SWIZZLE3_PROTO( class Vector3D, 1,0,0 );
	_SWIZZLE3_PROTO( class Vector3D, 1,0,1 );
	_SWIZZLE3_PROTO( class Vector3D, 1,1,x );
	_SWIZZLE3_PROTO( class Vector3D, 1,1,0 );
	_SWIZZLE3_PROTO( class Vector3D, 1,1,1 );

	_SWIZZLE4_PROTO( class Vector4D, x,x,x,x );	// *** //
	_SWIZZLE4_PROTO( class Vector4D, x,x,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,x,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,x,0,x );
	_SWIZZLE4_PROTO( class Vector4D, x,x,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,x,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,x,1,x );
	_SWIZZLE4_PROTO( class Vector4D, x,x,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,x,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,0,x,x );
	_SWIZZLE4_PROTO( class Vector4D, x,0,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,0,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,0,0,x );
	_SWIZZLE4_PROTO( class Vector4D, x,0,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,0,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,0,1,x );
	_SWIZZLE4_PROTO( class Vector4D, x,0,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,0,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,1,x,x );
	_SWIZZLE4_PROTO( class Vector4D, x,1,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,1,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,1,0,x );
	_SWIZZLE4_PROTO( class Vector4D, x,1,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,1,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, x,1,1,x );
	_SWIZZLE4_PROTO( class Vector4D, x,1,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, x,1,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,x,x );	// *** //
	_SWIZZLE4_PROTO( class Vector4D, 0,x,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,0,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,1,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,x,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,x,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,0,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,1,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,0,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,x,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,0,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,1,x );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, 0,1,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,x,x );	// *** //
	_SWIZZLE4_PROTO( class Vector4D, 1,x,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,0,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,1,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,x,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,x,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,0,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,1,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,0,1,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,x,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,x,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,x,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,0,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,0,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,0,1 );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,1,x );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,1,0 );
	_SWIZZLE4_PROTO( class Vector4D, 1,1,1,1 );	
	// - -------------------------------------------------------------------------------------- - //
	#undef _SWIZZLE4_PROTO
	#undef _SWIZZLE3_PROTO
	#undef _SWIZZLE2_PROTO
	// - -------------------------------------------------------------------------------------- - //
	#undef SWIZZLE4_PROTO
	#undef SWIZZLE3_PROTO
	#undef SWIZZLE2_PROTO
	// - -------------------------------------------------------------------------------------- - //
	// Random Numbers //
	static Real Random();
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Arc Tangent 2 - Input *[0,1] -- Output *[-?,+?] //
inline const Real ArcTan2( const Real y, const Real x ) {
	return std::atan2( y, x ) * Real::InvTwoPi; // Optimization for / TwoPi
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Operations, for GLSL familiar syntax. From the Procedural book. //
// NOTE: These functions, for the most part, operate on ranges. Functions above are typically [0,1]
// - ------------------------------------------------------------------------------------------ - //
inline const Real mix( const Real a, const Real b, const Real Alpha ) {
	return (a * (Real::One - Alpha)) + (b * Alpha);
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real step( const Real a, const Real x ) {
	return Real(x >= a); // NOTE: This is a boolean op [0,1] //
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real pulse( const Real a, const Real b, const Real x ) {
	return step(a,x) - step(b,x); // Clever! x>a Becomes 1, then as x>b it becomes 1-1=0 //
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real min( const Real a, const Real b ) {
	return a < b ? a : b;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real max( const Real a, const Real b ) {
	return a < b ? b : a;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real clamp( const Real x, const Real a, const Real b ) {
	return min( max(x,a), b );
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real abs( const Real x ) {
	return x < Real::Zero ? -x : x;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real smoothstep( const Real a, const Real b, Real x ) {
	if ( x < a )  return Real::Zero;
	if ( x >= b ) return Real::One;
	x = (x-a) / (b-a);
	return (x*x * (Real::Three - Real::Two*x));
}
// - ------------------------------------------------------------------------------------------ - //
// Page 34 - Splines
// - ------------------------------------------------------------------------------------------ - //
inline const Real gammacorrect( const Real Gamma, const Real x ) {
	return pow( x, Real::One/Gamma );
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real bias( const Real b, const Real x ) {
	return pow( x, log(b) / log(0.5f) );
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real gain( const Real g, const Real x ) {
	if ( x < Real::Half )
		return bias( Real::One - g, Real::Two * x) / Real::Two;
	else
		return Real::One - bias( Real::One - g, Real::Two * x) / Real::Two;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Real boxstep( const Real a, const Real b, const Real x ) { 
	return clamp( (x-a)/(b-a), Real::Zero, Real::One );
}
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
