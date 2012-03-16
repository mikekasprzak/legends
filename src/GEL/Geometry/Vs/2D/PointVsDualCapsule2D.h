// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsDualCapsule2D_H__
#define __AdvancedGeometry_PointVsDualCapsule2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
#include "PointVsLine2D.h"
#include "PointVsSphere2D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const bool Test_Point_Vs_DualCapsule2D( const Vector2D& Pos, const Vector2D& VsA, const Real VsRadiusA, const Vector2D& VsB, const Real VsRadiusB ) {
	cNearest_PointInfo_On_Line2D Info = Nearest_PointInfo_On_Line2D( Pos, VsA, VsB );
	Real RadiusDiff = VsRadiusB-VsRadiusA;
	return Test_Point_Vs_Sphere2D( Pos, Info.Point, VsRadiusA + (RadiusDiff * (Info.DistanceOnLine/Info.LineLength)) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsDualCapsule2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
