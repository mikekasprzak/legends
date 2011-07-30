// - ------------------------------------------------------------------------------------------ - //
#include "Matrix3x3.h"
// - ------------------------------------------------------------------------------------------ - //
const Matrix3x3 Matrix3x3::Identity(
	Real::One, Real::Zero, Real::Zero,
	Real::Zero, Real::One, Real::Zero,
	Real::Zero, Real::Zero, Real::One
	);
// - ------------------------------------------------------------------------------------------ - //
const Matrix3x3 Matrix3x3::Zero(
	Real::Zero, Real::Zero, Real::Zero,
	Real::Zero, Real::Zero, Real::Zero,
	Real::Zero, Real::Zero, Real::Zero
	);
// - ------------------------------------------------------------------------------------------ - //
