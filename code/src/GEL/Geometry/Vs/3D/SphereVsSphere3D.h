// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_SphereVsSphere3D_H__
#define __AdvancedGeometry_SphereVsSphere3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include "PointVsSphere3D.h"
// - ------------------------------------------------------------------------------------------ - //
inline bool Test_Sphere_Vs_Sphere3D( const Vector3D& Pos, const Real& Radius, const Vector3D& VsPos, const Real VsRadius ) {
	return Test_Point_Vs_Sphere3D( Pos, VsPos, Radius + VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //
inline Vector3D Nearest_SpherePoint_On_Sphere3D( const Vector3D& Pos, const Real& Radius, const Vector3D& VsPos, const Real VsRadius ) {
	return Nearest_Point_On_Sphere3D( Pos, VsPos, Radius + VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //
inline Vector3D Nearest_SpherePoint_OnEdgeOf_Sphere3D( const Vector3D& Pos, const Real& Radius, const Vector3D& VsPos, const Real VsRadius ) {
	return Nearest_Point_OnEdgeOf_Sphere3D( Pos, VsPos, Radius + VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_SphereVsSphere3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
