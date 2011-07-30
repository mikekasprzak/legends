// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsEdgedPolygon2D_H__
#define __AdvancedGeometry_PointVsEdgedPolygon2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
#include "PointVsLine2D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// NOTE: You still need to test within the entire volume to verify that it's inside the polygon. //
//   Other actions can ignore sides, since their job is to find the nearest one. //
// - ------------------------------------------------------------------------------------------ - //
// Function by Darel Rex Finley - http://alienryderflex.com/polygon/
bool Test_Point_Vs_EdgedPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const bool* VsEnabled, const size_t VsCount ) {
	// Odd number of nodes //
	bool OddNodes = false;
	
	// Previous Node //	
	size_t j = VsCount - 1;

	// For every side //
	for ( size_t i = 0; i < VsCount; i++ ) {
//		if ( VsEnabled[i] ) {
			// Test if a side crosses the y axis //
			if ( ((VsPoint[i].y < Pos.y) && (VsPoint[j].y >= Pos.y )) || ((VsPoint[j].y < Pos.y) && (VsPoint[i].y >= Pos.y)) ) {
				// TODO: Uhh... I'm not sure. //
				if (VsPoint[i].x + (Pos.y-VsPoint[i].y) / (VsPoint[j].y-VsPoint[i].y) * (VsPoint[j].x-VsPoint[i].x) < Pos.x) {
					OddNodes = !OddNodes;
				}
	        }
//	    }
        // Make j the current point, since i is about it become the next one //
    	j = i;
	}

	// The algorithm says
	return OddNodes;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Nearest_Point_OnEdgeOf_EdgedPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const bool* VsEnabled, const size_t VsCount ) {
	Vector2D Point;
	Real DistanceSquared = 999999;
	
	if ( VsCount >= 1 ) {
		if ( VsEnabled[ VsCount - 1 ] ) {
			Point = Nearest_Point_On_Line2D( Pos, VsPoint[ VsCount - 1 ], VsPoint[ 0 ] );
			DistanceSquared = (Point - Pos).MagnitudeSquared();
		}
		
		for ( size_t idx = 0; idx < VsCount - 1; idx++ ) {
			if ( VsEnabled[idx] ) {
				Vector2D NewPoint = Nearest_Point_On_Line2D( Pos, VsPoint[ idx ], VsPoint[ idx + 1 ] );
				Real NewDistanceSquared = (NewPoint - Pos).MagnitudeSquared();
				
				if ( DistanceSquared > NewDistanceSquared ) {
					Point = NewPoint;
					DistanceSquared = NewDistanceSquared;
				}
			}
		}
	}
	
	return Point;
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Nearest_Point_On_EdgedPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const bool* VsEnabled, const size_t VsCount ) {
	if ( Test_Point_Vs_EdgedPolygon2D( Pos, VsPoint, VsEnabled, VsCount ) ) {
		return Pos;
	}
	else {
		return Nearest_Point_OnEdgeOf_EdgedPolygon2D( Pos, VsPoint, VsEnabled, VsCount );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the position of the nearest corner point //
inline const Vector2D Nearest_CornerPoint_OnEdgeOf_EdgedPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const bool* VsEnabled, const size_t VsCount ) {
	Vector2D Point;
	Real DistanceSquared = 999999;
	
	// TODO: Remove a point if next and previous are not there //
	
	if ( VsCount >= 1 ) {
//		if ( VsEnabled[ VsCount - 1 ] ) {
			Point = VsPoint[ 0 ];
			DistanceSquared = (Point - Pos).MagnitudeSquared();
//		}
		
		for ( size_t idx = 1; idx < VsCount; idx++ ) {
//			if ( VsEnabled[idx] ) {
				Real NewDistanceSquared = (VsPoint[ idx ] - Pos).MagnitudeSquared();
				if ( DistanceSquared > NewDistanceSquared ) {
					Point = VsPoint[ idx ];
					DistanceSquared = NewDistanceSquared;
				}
//			}
		}
	}
	
	return Point;
}
// - ------------------------------------------------------------------------------------------ - //
// Get the index of the nearest corner point //
inline const size_t Nearest_CornerPointIndex_OnEdgeOf_EdgedPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const bool* VsEnabled, const size_t VsCount ) {
	size_t Index = 0;
	Real DistanceSquared = 999999;
	
	// TODO: Remove a point if next and previous are not there //
	
	if ( VsCount >= 1 ) {
//		if ( VsEnabled[ VsCount - 1 ] ) {
			DistanceSquared = (VsPoint[ 0 ] - Pos).MagnitudeSquared();
//		}
		
		for ( size_t idx = 1; idx < VsCount; idx++ ) {
//			if ( VsEnabled[idx] ) {
				Real NewDistanceSquared = (VsPoint[ idx ] - Pos).MagnitudeSquared();
				if ( DistanceSquared > NewDistanceSquared ) {
					Index = idx;
					DistanceSquared = NewDistanceSquared;
				}
//			}
		}
	}
	
	return Index;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the index of the nearest corner point //
inline const size_t Nearest_EdgeIndex_Of_EdgedPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const bool* VsEnabled, const size_t VsCount ) {
	size_t Index = 0;
	Vector2D Point;
	Real DistanceSquared = 999999;
	
	if ( VsCount >= 1 ) {
		if ( VsEnabled[ VsCount - 1 ] ) {
			Index = VsCount - 1;
			Point = Nearest_Point_On_Line2D( Pos, VsPoint[ VsCount - 1 ], VsPoint[ 0 ] );
			DistanceSquared = (Point - Pos).MagnitudeSquared();
		}
		
		for ( size_t idx = 0; idx < VsCount - 1; idx++ ) {
			if ( VsEnabled[idx] ) {
				Vector2D NewPoint = Nearest_Point_On_Line2D( Pos, VsPoint[ idx ], VsPoint[ idx + 1 ] );
				Real NewDistanceSquared = (NewPoint - Pos).MagnitudeSquared();
				
				if ( DistanceSquared > NewDistanceSquared ) {
					Index = idx;
					Point = NewPoint;
					DistanceSquared = NewDistanceSquared;
				}
			}
		}
	}
	
	return Index;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsEdgedPolygon2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
