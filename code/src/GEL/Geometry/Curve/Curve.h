// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Curve_H__
#define __Geometry_Curve_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Several of these functions can be optimized by giving a target chunk of memory and //
//   a number of units desired.  //
// - ------------------------------------------------------------------------------------------ - //
// From the "Real Time Cameras" book //
// - ------------------------------------------------------------------------------------------ - //
// Linear Interpolation Curves //
inline Vector3D Calc_LinearCurve( const Vector3D& a, const Vector3D& b, const Real& Time ) {
	return a + ((1.0f - Time) * (b-a));
}
// - ------------------------------------------------------------------------------------------ - //
// These are curves like you see in Vector art software.  Tangents are the inner handles. //
inline Vector3D Calc_HermiteCurve( const Vector3D& a, const Vector3D& b, const Vector3D& StartTangent, const Vector3D& EndTangent, const Real& Time ) {
	if ( Time <= Real::Zero )
		return a;
	else if ( Time >= Real::One )
		return b;
	
	const Real t2(Time*Time); // Squared //
	const Real t3(t2*Time);   // Cubed //
	
	// Calculate Basis Functions //
	const Real _a0 = (Real(2) * t3) - (Real(3) * t2) + Real(1);
	const Real _a1 = (-Real(2) * t3) + (Real(3) * t2);
	const Real _b0 = t3 - (Real(2) * t2) + Time;
	const Real _b1 = t3 - t2;
	
	// Use cubic basis functions with points and tangents //
	return (_a0 * a) + (_a1 * b) + (_b0 * StartTangent) + (_b1 * EndTangent);
}
// - ------------------------------------------------------------------------------------------ - //
// Catmull-Rom Curve - Passes through all 4 points, though the curve is between b and c //
inline Vector3D Calc_CatmullRomCurve( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Real& Time ) {
	if ( Time <= Real::Zero )
		return b;
	else if ( Time >= Real::One )
		return c;
	
	const Real t2(Time*Time); // Squared //
	const Real t3(t2*Time);   // Cubed //

	// From Real-Time Cameras book, didn't work. 2nd set of points were all screwy //
//	return 
//		a * (-Real::Half * t3 + t2 - Real::Half * Time) + 
//		b * (Real(1.5f) * t3 + Real(-2.5f) * t2 * Real(1)) +
//		c * (-Real(1.5f) * t3 + Real(2.0f) * t2 + Real::Half * Time) +
//		d * (Real::Half * t3 - Real::Half * t2);

	// http://steve.hollasch.net/cgindex/curves/catmull-rom.html //
	return Real::Half * (
		(-a + Real(3)*b - Real(3)*c + d) * t3 +
        (Real(2)*a - Real(5)*b + Real(4)*c - d) * t2 +
        (-a+c) * Time +
        Real(2)*b
        );
}
// - ------------------------------------------------------------------------------------------ - //
// Rounded Catmull-Rom Curve - Rounder version of Catmull Rom ;) //
// NOTE: This doesn't actually work... :( //
inline Vector3D Calc_RoundedCatmullRomCurve( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Real& Time ) {
	if ( Time <= Real::Zero )
		return b;
	else if ( Time >= Real::One )
		return c;
	
	const Vector3D cb = c - b;
	if ( !cb.IsZeroOrLess() )
		return b;

	Vector3D ab = a - b;
	if ( !ab.IsZeroOrLess() )
		ab = Vector3D(0,1,0);

	Vector3D bVelocity = cb.Normal() - ab.Normal();
	if ( !bVelocity.IsZeroOrLess() )
		bVelocity.Normalize();
	else
		bVelocity = Vector3D(0,1,0);

	Vector3D dc = d - c;
	if ( !dc.IsZeroOrLess() )
		dc = Vector3D(0,1,0);
	
	Vector3D bc = -cb;
	
	Vector3D cVelocity = dc.Normal() - bc.Normal();
	if ( cVelocity.IsZeroOrLess() )
		cVelocity.Normalize();
	else
		cVelocity = Vector3D(0,1,0);
	
	const Real cbDistance = cb.Magnitude();
	
	return Calc_CatmullRomCurve( b, c, bVelocity * cbDistance, cVelocity * cbDistance, Time );
}
// - ------------------------------------------------------------------------------------------ - //
// KB Spline Curve - Like a Catmull Rom, but with some controllers for weighting towards ends //
inline Vector3D Calc_KBSplineCurve( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Real& Time, const Real& Tension = Real::Zero, const Real& Continuity = Real::Zero, const Real& Bias = Real::Zero ) {
	const Vector3D ab( (b-a).Normal() );
	const Vector3D cd( (d-c).Normal() );
	const Vector3D inTangent(
		( (Real::One - Tension) * (Real::One - Continuity) * (Real::One + Bias) ) * Real::Half * ab +
		( (Real::One - Tension) * (Real::One + Continuity) * (Real::One - Bias) ) * Real::Half * cd);
	const Vector3D outTangent(
		( (Real::One - Tension) * (Real::One + Continuity) * (Real::One + Bias) ) * Real::Half * ab +
		( (Real::One - Tension) * (Real::One - Continuity) * (Real::One - Bias) ) * Real::Half * cd);
	return Calc_HermiteCurve( b, c, inTangent, outTangent, Time );
}
// - ------------------------------------------------------------------------------------------ - //
// Quadradic Bezier Curve - 3 point curve //
inline Vector3D Calc_BezierCurve( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Real& Time ) {
	const Real OneMinusTime( Real::One - Time );
	
	return
		(a * OneMinusTime * OneMinusTime) +
		(b * Real(2) * Time * OneMinusTime) +
		(c * Time * Time);
}
// - ------------------------------------------------------------------------------------------ - //
// Cubic Bezier Curve - 4 point curve //
inline Vector3D Calc_BezierCurve( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Real& Time ) {
	const Real OneMinusTime( Real::One - Time );
	
	return
		(a * OneMinusTime * OneMinusTime * OneMinusTime) +
		(b * Real(3) * Time * OneMinusTime * OneMinusTime) +
		(c * Real(3) * Time * Time * OneMinusTime) +
		(d * Time * Time * Time);
}
// - ------------------------------------------------------------------------------------------ - //
// Uniform Cubic Bezier Spline Curve - 4 point curve, evenly spaced steps, doesn't meet end points //
inline Vector3D Calc_BSplineCurve( const Vector3D& a, const Vector3D& b, const Vector3D& c, const Vector3D& d, const Real& Time ) {
	const Real t2(Time*Time); // Squared //
	const Real t3(t2*Time);   // Cubed //
	
	return (
		( a * ((-t3) + (Real(3)*t2) + (Real(-3)*Time) + Real::One) ) +
		( b * ((Real(3)*t3) + (Real(-6)*t2) + Real(4)) ) +
		( c * ((Real(-3)*t3) + (Real(3)*t2) + (Real(3)*Time) + Real::One) ) +
		( d * t3 )
		) / Real(6);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Curve_H__ //
// - ------------------------------------------------------------------------------------------ - //
