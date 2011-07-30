// - ------------------------------------------------------------------------------------------ - //
#include "Matrix4x4.h"
// - ------------------------------------------------------------------------------------------ - //
const Matrix4x4 Matrix4x4::Identity(
	Real::One, Real::Zero, Real::Zero, Real::Zero,
	Real::Zero, Real::One, Real::Zero, Real::Zero,
	Real::Zero, Real::Zero, Real::One, Real::Zero,
	Real::Zero, Real::Zero, Real::Zero, Real::One
	);
// - ------------------------------------------------------------------------------------------ - //
const Matrix4x4 Matrix4x4::Zero(
	Real::Zero, Real::Zero, Real::Zero, Real::Zero,
	Real::Zero, Real::Zero, Real::Zero, Real::Zero,
	Real::Zero, Real::Zero, Real::Zero, Real::Zero,
	Real::Zero, Real::Zero, Real::Zero, Real::Zero
	);
// - ------------------------------------------------------------------------------------------ - //
