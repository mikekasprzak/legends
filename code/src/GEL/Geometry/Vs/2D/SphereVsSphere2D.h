// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_SphereVsSphere2D_H__
#define __AdvancedGeometry_SphereVsSphere2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include "PointVsSphere2D.h"
// - ------------------------------------------------------------------------------------------ - //
inline bool Test_Sphere_Vs_Sphere2D( const Vector2D& Pos, const Real& Radius, const Vector2D& VsPos, const Real VsRadius ) {
	return Test_Point_Vs_Sphere2D( Pos, VsPos, Radius + VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //
inline Vector2D Nearest_SpherePoint_On_Sphere2D( const Vector2D& Pos, const Real& Radius, const Vector2D& VsPos, const Real VsRadius ) {
	return Nearest_Point_On_Sphere2D( Pos, VsPos, Radius + VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //
inline Vector2D Nearest_SpherePoint_OnEdgeOf_Sphere2D( const Vector2D& Pos, const Real& Radius, const Vector2D& VsPos, const Real VsRadius ) {
	return Nearest_Point_OnEdgeOf_Sphere2D( Pos, VsPos, Radius + VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_SphereVsSphere2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
