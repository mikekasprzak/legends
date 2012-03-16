// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsLine2D_H__
#define __AdvancedGeometry_PointVsLine2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct cNearest_PointInfo_On_Line2D {
	Vector2D Point;
	
	Vector2D Line;
	Vector2D LineNormal;
	Real LineLength;

	int Corner;
	
	Vector2D CornerToPoint;
	Real DistanceOnLine;
};
// - ------------------------------------------------------------------------------------------ - //
inline const cNearest_PointInfo_On_Line2D Nearest_PointInfo_On_Line2D( const Vector2D& p, const Vector2D& a, const Vector2D& b ) {
	cNearest_PointInfo_On_Line2D Info;
	Info.Corner = 0;
	
	// Calculate our notable rays //
	Info.Line = b - a; // ab //
	Info.CornerToPoint = p - a; // ap //

	// Normalize and Store the Line Normal and Length //
	Info.LineNormal = Info.Line;
	Info.LineLength = Info.LineNormal.NormalizeRet();

	// Calculate how far 
	Info.DistanceOnLine = dot( Info.CornerToPoint, Info.LineNormal );
	
	// Set Point to a position on the line //
	if ( Info.DistanceOnLine <= Real::Zero ) {
		Info.Point = a;
		Info.Corner = 1;
	}
	else if ( Info.DistanceOnLine >= Info.LineLength ) {
		Info.Point = b;
		Info.Corner = 2;
	}
	else {
		Info.Point = a + (Info.LineNormal * Info.DistanceOnLine);
	}
	
	// Return the Info Structure //
	return Info;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Nearest_Point_On_Line2D( const Vector2D& p, const Vector2D& a, const Vector2D& b ) {
	cNearest_PointInfo_On_Line2D Info = Nearest_PointInfo_On_Line2D( p, a, b );
	return Info.Point;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsLine2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
