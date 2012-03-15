// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsPointCluster2D_H__
#define __AdvancedGeometry_PointVsPointCluster2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the position of the nearest point //
inline const Vector2D Nearest_Point_On_PointCluster2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	Vector2D Point;
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
inline const Vector2D Nearest_CornerPoint_On_PointCluster2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return NearestPointOnPointCluster2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //
// Get the position of the nearest point //
inline const Vector2D Nearest_CornerPoint_OnEdgeOf_PointCluster2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return NearestPointOnPointCluster2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //
// Get the index of the nearest corner point //
inline const size_t Nearest_CornerPointIndex_On_PointCluster2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
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
inline const size_t Nearest_CornerPointIndex_OnEdgeOf_PointCluster2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return NearestCornerPointIndexOnPointCluster2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsPointCluster2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
