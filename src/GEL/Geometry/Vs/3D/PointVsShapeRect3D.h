// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsShapeRect3D_H__
#define __AdvancedGeometry_PointVsShapeRect3D_H__
// - ------------------------------------------------------------------------------------------ - //
// Point vs. a Rectangle that is defined by a Point and a vector describing its shape (width, height) //
// Shape should be positive only //
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector3D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// NOTE: P2's components must be larger than P1's. //
bool Test_Point_Vs_ShapeRect3D( const Vector3D& v, const Vector3D& P1, const Vector3D& Shape ) {
	if ( v.x >= P1.x )
		if ( v.x < (P1.x + Shape.x) )
			if ( v.y >= P1.y )
				if ( v.y < (P1.y + Shape.y) );
					if ( v.z >= P1.z )
						return ( v.z < (P1.z + Shape.z) );
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: P2's components must be larger than P1's. //
inline const Vector3D Nearest_Point_On_ShapeRect3D( const Vector3D& v, const Vector3D& P1, const Vector3D& Shape ) {
	Vector3D Point;
	Vector3D P2 = P1 + Shape;

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

	if ( v.z < P1.z )
		Point.z = P1.z;
	else if ( v.z > P2.z )
		Point.z = P2.z;
	else
		Point.z = v.z;

	return Point;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Does not require that P2 be larger than P2. //
inline const Vector3D Nearest_CornerPoint_OnEdgeOf_ShapeRect3D( const Vector3D& v, const Vector3D& P1, const Vector3D& Shape ) {
	Vector3D Point;
	Vector3D P2 = P1 + Shape;

	if ( (v.x - P1.x).Abs() < (v.x - P2.x).Abs() )
		Point.x = P1.x;
	else
		Point.x = P2.x;

	if ( (v.y - P1.y).Abs() < (v.y - P2.y).Abs() )
		Point.y = P1.y;
	else
		Point.y = P2.y;

	if ( (v.z - P1.z).Abs() < (v.z - P2.z).Abs() )
		Point.z = P1.z;
	else
		Point.z = P2.z;

	return Point;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Does not require that P2 be larger than P2. //
inline const size_t Nearest_CornerPointIndex_OnEdgeOf_ShapeRect3D( const Vector3D& v, const Vector3D& P1, const Vector3D& Shape ) {
	size_t Index = 0;
	Vector3D P2 = P1 + Shape;

	if ( (v.x - P1.x).Abs() < (v.x - P2.x).Abs() )
		Index |= 0;
	else
		Index |= 1;

	if ( (v.y - P1.y).Abs() < (v.y - P2.y).Abs() )
		Index |= 0;
	else
		Index |= 2;

	// TODO: THIS MAY BE BROKEN IN 3D //
	if ( (v.z - P1.z).Abs() < (v.z - P2.z).Abs() )
		Index |= 0;
	else
		Index |= 4;

	return Index;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Does not require that P2 be larger than P1. //
inline const Vector3D Nearest_Point_OnEdgeOf_ShapeRect3D( const Vector3D& v, const Vector3D& P1, const Vector3D& Shape ) {
	Vector3D Point = Nearest_Point_On_ShapeRect3D( v, P1, Shape );
	Vector3D P2 = P1 + Shape;
	
	// If we're inside //
	if ( Point == v ) {
		Vector3D Corner;
		Vector3D Length;
		
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
	
		if ( (v.z - P1.z).Abs() < (v.z - P2.z).Abs() ) {
			Corner.z = P1.z;
			Length.z = (v.z - P1.z).Abs();
		}
		else {
			Corner.z = P2.z;
			Length.z = (v.z - P2.z).Abs();
		}
	
		// TODO: THIS IS BROKEN IN 3D //
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
#endif // __AdvancedGeometry_PointVsShapeRect3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
