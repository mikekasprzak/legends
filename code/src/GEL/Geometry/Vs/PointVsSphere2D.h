// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsSphere2D_H__
#define __AdvancedGeometry_PointVsSphere2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Test_Point_Inside_Sphere2D.  Vs should (?) be reserved for Sphere Vs Sphere?
//   No.  Testing is one thing.  A test means there's a contact.  Inside means it's entirely //
//   contained within the other one. //
inline bool Test_Point_Vs_Sphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
	Vector2D Diff = VsPos - Pos;
	return Diff.MagnitudeSquared() < (VsRadius * VsRadius);
}
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//// TODO: The solving stuff below isn't done.  I have to figure out exactly what solving actually //
////   needs.  I thought it wanted to know if it was inside the sphere, but I think it actually //
////   wants something to do with the distance between the spheres.  I.e. a vector to say "how" to //
////   solve, by pushing outward. //
//// - ------------------------------------------------------------------------------------------ - //
//struct cPointVsSphere2D {
//	// --- Start Part ------------------ //
//	Vector2D Diff;
//	Real MagnitudeSquared;
//	Real Radius;
//	
//	inline const Real RadiusSquared() const {
//		return Radius * Radius;
//	}
//
//	// --- Solve Part ------------------ //
//	Real Magnitude;
//		
//	//bool InsideSphere;
//};
//// - ------------------------------------------------------------------------------------------ - //
//
//// - ------------------------------------------------------------------------------------------ - //
//inline cPointVsSphere2D StartPointVsSphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
//	cPointVsSphere2D Info;
//	
//	Info.Diff = VsPos - Pos;
//	Info.MagnitudeSquared = Info.Diff.MagnitudeSquared();
//	Info.Radius = VsRadius;
//	
//	return Info;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline bool TestPointVsSphere2D( const cPointVsSphere2D& Info ) {
//	return Info.MagnitudeSquared < Info.RadiusSquared();
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline cPointVsSphere2D SolvePointVsSphere2D( const cPointVsSphere2D& _Info ) {
//	cPointVsSphere2D Info = _Info;
//	
//	Info.Magnitude = Info.MagnitudeSquared.Sqrt();
//	
//	// TODO: More stuff needs to be done here, to correctly be considered a solve //
//	
//	//Info.InsideSphere = Info.MagnitudeSquared < Info.RadiusSquared;
//	
//	
//	return Info;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline cPointVsSphere2D SolvePointVsSphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
//	cPointVsSphere2D Info = StartPointVsSphere2D( Pos, VsPos, VsRadius );
//	return SolvePointVsSphere2D( Info );
//}
//// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Finds the nearest point, returning the same point if inside //
inline Vector2D Nearest_Point_On_Sphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
	Vector2D Point = Pos - VsPos;
	Real Mag = Point.NormalizeRet();
	
	if ( Mag < VsRadius )
		return Pos;
	else
		return VsPos + (Point * VsRadius);	
}
// - ------------------------------------------------------------------------------------------ - //
// Finds the nearest point on an edge, no matter what //
inline Vector2D Nearest_Point_OnEdgeOf_Sphere2D( const Vector2D& Pos, const Vector2D& VsPos, const Real VsRadius ) {
	Vector2D Point = Pos - VsPos;
	Real Mag = Point.NormalizeRet();
	
	return VsPos + (Point * VsRadius);	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsSphere2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
