// - ------------------------------------------------------------------------------------------ - //
#ifndef _WIN32_WCE
#include <stdlib.h>
#else // _WIN32_WCE //
#include <stddef.h>
#endif // _WIN32_WCE //
// - ------------------------------------------------------------------------------------------ - //
#include "Real.h"
// - ------------------------------------------------------------------------------------------ - //
// Regular constants //
// - ------------------------------------------------------------------------------------------ - //
const Real Real::Identity( 1.0 );
const Real Real::Zero( 0.0 );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Other constants special to this type //
// - ------------------------------------------------------------------------------------------ - //
const Real Real::One( 1.0 );
const Real Real::Two( 2.0 );
const Real Real::Four( 4.0 );
const Real Real::Half( 0.5 );
const Real Real::Quarter( 0.25 );
const Real Real::SmallestUnit( 0.005 );
		
const Real Real::Three( 3.0 );
const Real Real::ThreeQuarter( 0.75 );
const Real Real::Third( 1.0 / 3.0 );
	
const Real Real::Pi( 3.1415926535897932384626433832795 );
const Real Real::TwoPi( Pi+Pi );	// Tau //
const Real Real::HalfPi( Pi * Real::Half );
const Real Real::QuarterPi( Pi * Real::Quarter );
const Real Real::InvPi( One / Pi );
const Real Real::InvTwoPi( One / TwoPi );
const Real Real::InvHalfPi( One / HalfPi );
const Real Real::InvQuarterPi( One / QuarterPi );
	
const Real Real::e( 2.71828182845904523536028747135266249775724709369995 );
	
const Real Real::Sine45( 0.70710678118654752440084436210485 );
// - ------------------------------------------------------------------------------------------ - //
Real Real::Random() {
	return Real( rand() / (float)RAND_MAX );
}
// - ------------------------------------------------------------------------------------------ - //
