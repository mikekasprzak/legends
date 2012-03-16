// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsPointCluster3D_H__
#define __AdvancedGeometry_PointVsPointCluster3D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector3D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the position of the nearest point //
inline const Vector3D Nearest_Point_On_PointCluster3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount ) {
	Vector3D Point;
	Real DistanceSquared;
	
	if ( VsCount >= 1 ) {
		Point = VsPoint[ 0 ];
		DistanceSquared = (Point - Pos).MagnitudeSquared();
		
		for ( size_t idx = 1; idx < VsCount; idx++ ) {
			Real NewDistanceSquared = (VsPoint[ idx ] - Pos).MagnitudeSquared();
			if ( DistanceSquared > NewDistanceSquared ) {
				Point = VsPoint[ idx ];
				DistanceSquared = NewDistanceSquared;
			}
		}
	}
	
	return Point;
}
// - ------------------------------------------------------------------------------------------ - //
// Get the position of the nearest point //
inline const Vector3D Nearest_CornerPoint_On_PointCluster3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount ) {
	return Nearest_Point_On_PointCluster3D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //
// Get the position of the nearest point //
inline const Vector3D Nearest_CornerPoint_OnEdgeOf_PointCluster3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount ) {
	return Nearest_Point_On_PointCluster3D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //
// Get the index of the nearest corner point //
inline const size_t Nearest_CornerPointIndex_On_PointCluster3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount ) {
	size_t Index;
	Real DistanceSquared;
	
	if ( VsCount >= 1 ) {
		Index = 0;
		DistanceSquared = (VsPoint[ 0 ] - Pos).MagnitudeSquared();
		
		for ( size_t idx = 1; idx < VsCount; idx++ ) {
			Real NewDistanceSquared = (VsPoint[ idx ] - Pos).MagnitudeSquared();
			if ( DistanceSquared > NewDistanceSquared ) {
				Index = idx;
				DistanceSquared = NewDistanceSquared;
			}
		}
	}
	
	return Index;
}
// - ------------------------------------------------------------------------------------------ - //
// Get the position of the corner point //
inline const size_t Nearest_CornerPointIndex_OnEdgeOf_PointCluster3D( const Vector3D& Pos, const Vector3D* VsPoint, const size_t VsCount ) {
	return Nearest_CornerPointIndex_On_PointCluster3D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsPointCluster3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
