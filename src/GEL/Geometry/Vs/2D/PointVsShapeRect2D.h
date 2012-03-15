// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsShapeRect2D_H__
#define __AdvancedGeometry_PointVsShapeRect2D_H__
// - ------------------------------------------------------------------------------------------ - //
// Point vs. a Rectangle that is defined by a Point and a vector describing its shape (width, height) //
// Shape should be positive only //
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// NOTE: P2's components must be larger than P1's. //
bool Test_Point_Vs_ShapeRect2D( const Vector2D& v, const Vector2D& P1, const Vector2D& Shape ) {
	if ( v.x >= P1.x )
		if ( v.x < (P1.x + Shape.x) )
			if ( v.y >= P1.y )
				return ( v.y < (P1.y + Shape.y) );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: P2's components must be larger than P1's. //
inline const Vector2D Nearest_Point_On_ShapeRect2D( const Vector2D& v, const Vector2D& P1, const Vector2D& Shape ) {
	Vector2D Point;
	Vector2D P2 = P1 + Shape;

	if ( v.x < P1.x )
		Point.x = P1.x;
	else if ( v.x > P2.x )
		Point.x = P2.x;
	else
		Point.x = v.x;

	if ( v.y < P1.y )
		Point.y = P1.y;
	else if ( v.y > P2.y )
		Point.y = P2.y;
	else
		Point.y = v.y;

	return Point;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Does not require that P2 be larger than P2. //
inline const Vector2D Nearest_CornerPoint_OnEdgeOf_ShapeRect2D( const Vector2D& v, const Vector2D& P1, const Vector2D& Shape ) {
	Vector2D Point;
	Vector2D P2 = P1 + Shape;

	if ( (v.x - P1.x).Abs() < (v.x - P2.x).Abs() )
		Point.x = P1.x;
	else
		Point.x = P2.x;

	if ( (v.y - P1.y).Abs() < (v.y - P2.y).Abs() )
		Point.y = P1.y;
	else
		Point.y = P2.y;

	return Point;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Does not require that P2 be larger than P2. //
inline const size_t Nearest_CornerPointIndex_OnEdgeOf_ShapeRect2D( const Vector2D& v, const Vector2D& P1, const Vector2D& Shape ) {
	size_t Index = 0;
	Vector2D P2 = P1 + Shape;

	if ( (v.x - P1.x).Abs() < (v.x - P2.x).Abs() )
		Index |= 0;
	else
		Index |= 1;

	if ( (v.y - P1.y).Abs() < (v.y - P2.y).Abs() )
		Index |= 0;
	else
		Index |= 2;

	return Index;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Does not require that P2 be larger than P1. //
inline const Vector2D Nearest_Point_OnEdgeOf_ShapeRect2D( const Vector2D& v, const Vector2D& P1, const Vector2D& Shape ) {
	Vector2D Point = Nearest_Point_On_ShapeRect2D( v, P1, Shape );
	Vector2D P2 = P1 + Shape;
	
	// If we're inside //
	if ( Point == v ) {
		Vector2D Corner;
		Vector2D Length;
		
		// Note the best edge, and distance to it //
		if ( (v.x - P1.x).Abs() < (v.x - P2.x).Abs() ) {
			Corner.x = P1.x;
			Length.x = (v.x - P1.x).Abs();
		}
		else {
			Corner.x = P2.x;
			Length.x = (v.x - P2.x).Abs();
		}
	
		if ( (v.y - P1.y).Abs() < (v.y - P2.y).Abs() ) {
			Corner.y = P1.y;
			Length.y = (v.y - P1.y).Abs();
		}
		else {
			Corner.y = P2.y;
			Length.y = (v.y - P2.y).Abs();
		}
	
		// Depending which length is longer, align that axis //
		if ( Length.x > Length.y ) {
			Point.y = Corner.y;
		}
		else {
			Point.x = Corner.x;
		}
	}

	return Point;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsShapeRect2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
