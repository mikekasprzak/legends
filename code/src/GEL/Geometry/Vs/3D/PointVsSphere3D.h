// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsSphere3D_H__
#define __AdvancedGeometry_PointVsSphere3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector3D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Test_Point_Inside_Sphere3D.  Vs should (?) be reserved for Sphere Vs Sphere?
//   No.  Testing is one thing.  A test means there's a contact.  Inside means it's entirely //
//   contained within the other one. //
inline bool Test_Point_Vs_Sphere3D( const Vector3D& Pos, const Vector3D& VsPos, const Real VsRadius ) {
	Vector3D Diff = VsPos - Pos;
	return Diff.MagnitudeSquared() < (VsRadius * VsRadius);
}
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//// TODO: The solving stuff below isn't done.  I have to figure out exactly what solving actually //
////   needs.  I thought it wanted to know if it was inside the sphere, but I think it actually //
////   wants something to do with the distance between the spheres.  I.e. a vector to say "how" to //
////   solve, by pushing outward. //
//// - ------------------------------------------------------------------------------------------ - //
//struct cPointVsSphere3D {
//	// --- Start Part ------------------ //
//	Vector3D Diff;
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
//inline cPointVsSphere3D StartPointVsSphere3D( const Vector3D& Pos, const Vector3D& VsPos, const Real VsRadius ) {
//	cPointVsSphere3D Info;
//	
//	Info.Diff = VsPos - Pos;
//	Info.MagnitudeSquared = Info.Diff.MagnitudeSquared();
//	Info.Radius = VsRadius;
//	
//	return Info;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline bool TestPointVsSphere3D( const cPointVsSphere3D& Info ) {
//	return Info.MagnitudeSquared < Info.RadiusSquared();
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline cPointVsSphere3D SolvePointVsSphere3D( const cPointVsSphere3D& _Info ) {
//	cPointVsSphere3D Info = _Info;
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
//inline cPointVsSphere3D SolvePointVsSphere3D( const Vector3D& Pos, const Vector3D& VsPos, const Real VsRadius ) {
//	cPointVsSphere3D Info = StartPointVsSphere3D( Pos, VsPos, VsRadius );
//	return SolvePointVsSphere3D( Info );
//}
//// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Finds the nearest point, returning the same point if inside //
inline Vector3D Nearest_Point_On_Sphere3D( const Vector3D& Pos, const Vector3D& VsPos, const Real VsRadius ) {
	Vector3D Point = Pos - VsPos;
	Real Mag = Point.NormalizeRet();
	
	if ( Mag < VsRadius )
		return Pos;
	else
		return VsPos + (Point * VsRadius);	
}
// - ------------------------------------------------------------------------------------------ - //
// Finds the nearest point on an edge, no matter what //
inline Vector3D Nearest_Point_OnEdgeOf_Sphere3D( const Vector3D& Pos, const Vector3D& VsPos, const Real VsRadius ) {
	Vector3D Point = Pos - VsPos;
//	Real Mag = Point.NormalizeRet();
	
	return VsPos + (Point * VsRadius);	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsSphere3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
