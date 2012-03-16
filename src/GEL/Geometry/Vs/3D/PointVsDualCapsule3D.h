// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsDualCapsule3D_H__
#define __AdvancedGeometry_PointVsDualCapsule3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector3D.h>
#include "PointVsLine3D.h"
#include "PointVsSphere3D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const bool Test_Point_Vs_DualCapsule3D( const Vector3D& Pos, const Vector3D& VsA, const Real VsRadiusA, const Vector3D& VsB, const Real VsRadiusB ) {
	cNearest_PointInfo_On_Line3D Info = Nearest_PointInfo_On_Line3D( Pos, VsA, VsB );
	Real RadiusDiff = VsRadiusB-VsRadiusA;
	return Test_Point_Vs_Sphere3D( Pos, Info.Point, VsRadiusA + (RadiusDiff * (Info.DistanceOnLine/Info.LineLength)) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsDualCapsule3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
