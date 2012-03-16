// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsCapsule3D_H__
#define __AdvancedGeometry_PointVsCapsule3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector3D.h>
#include "PointVsLine3D.h"
#include "PointVsSphere3D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const bool Test_Point_Vs_Capsule3D( const Vector3D& Pos, const Vector3D& VsA, const Vector3D& VsB, const Real VsRadius ) {
	Vector3D VsPoint = Nearest_Point_On_Line3D( Pos, VsA, VsB );
	return Test_Point_Vs_Sphere3D( Pos, VsPoint, VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsCapsule3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
