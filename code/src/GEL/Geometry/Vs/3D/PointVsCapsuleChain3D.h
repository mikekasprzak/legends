// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsCapsuleChain3D_H__
#define __AdvancedGeometry_PointVsCapsuleChain3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector3D.h>
#include "PointVsChain3D.h"
#include "PointVsSphere3D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const bool Test_Point_Vs_CapsuleChain3D( const Vector3D& Pos, const Vector3D* VsPoints, const size_t VsCount, const Real VsRadius ) {
	Vector3D VsPoint = Nearest_Point_On_Chain3D( Pos, VsPoints, VsCount );
	return Test_Point_Vs_Sphere3D( Pos, VsPoint, VsRadius );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the nearest Edge Point //
inline const Vector3D Nearest_EdgePoint_On_CapsuleChain3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount, const Real VsRadius ) {
	cNearest_PointInfo_On_Chain3D Info = Nearest_PointInfo_On_Chain3D( Pos, VsPoint, VsCount );
	
	Vector3D Line = Info.Point - Pos;
	return Info.Point - (Line.Normal() * VsRadius);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Get the nearest Inner Edge Point //
inline const Vector3D Nearest_InnerEdgePoint_On_CapsuleChain3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount, const Real VsRadius ) {
	cNearest_PointInfo_On_Chain3D Info = Nearest_PointInfo_On_Chain3D( Pos, VsPoint, VsCount );
	if ( Info.Corner == 1 ) {
		// If it's a concave angle //
		if ( dot(Info.PreviousLine, Info.Normal) >= Real::Zero ) {
			//printf( "%i - Concave\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point - (Line.Normal() * VsRadius);
		}
		// If it's a convex angle //
		else {
			//printf( "%i - Convex\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point + (Line.Normal() * VsRadius);
		}
	}
	else if ( Info.Corner == 2 ) {
		// If it's a concave angle //
		if ( dot(Info.NextLine, Info.Normal) <= Real::Zero ) {
			//printf( "%i + Concave\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point - (Line.Normal() * VsRadius);
		}
		// If it's a convex angle //
		else {
			//printf( "%i + Convex\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point + (Line.Normal() * VsRadius);
		}
	}
	else {
		//printf( "%i - ???\n", Info.Corner );
		return Info.Point + (Info.Normal * VsRadius);
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Get the nearest Outer Edge Point //
inline const Vector3D Nearest_OuterEdgePoint_On_CapsuleChain3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount, const Real VsRadius ) {
	cNearest_PointInfo_On_Chain3D Info = Nearest_PointInfo_On_Chain3D( Pos, VsPoint, VsCount );
	if ( Info.Corner == 1 ) {
		// If it's a concave angle //
		if ( dot(Info.PreviousLine, Info.Normal) <= Real::Zero ) {
			//printf( "%i - Concave\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point - (Line.Normal() * VsRadius);
		}
		// If it's a convex angle //
		else {
			//printf( "%i - Convex\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point + (Line.Normal() * VsRadius);
		}
	}
	else if ( Info.Corner == 2 ) {
		// If it's a concave angle //
		if ( dot(Info.NextLine, Info.Normal) >= Real::Zero ) {
			//printf( "%i + Concave\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point - (Line.Normal() * VsRadius);
		}
		// If it's a convex angle //
		else {
			//printf( "%i + Convex\n", Info.Corner );
			Vector3D Line = Info.Point - Pos;
			return Info.Point + (Line.Normal() * VsRadius);
		}
	}
	else {
		//printf( "%i - ???\n", Info.Corner );
		return Info.Point + (-Info.Normal * VsRadius);
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsCapsuleChain3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
