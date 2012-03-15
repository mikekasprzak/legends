// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsPolygon2D_H__
#define __AdvancedGeometry_PointVsPolygon2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
#include "PointVsChain2D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Function by Darel Rex Finley - http://alienryderflex.com/polygon/
bool Test_Point_Vs_Polygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	// Odd number of nodes //
	bool OddNodes = false;
	
	// Previous Node //	
	size_t j = VsCount - 1;

	// For every side //
	for ( size_t i = 0; i < VsCount; i++ ) {
		// Test if the pair of points are on different sides of the point via the y axis //
		// NOTE: This rules out the i.y == j.y case, because < & >= //
		if ( ((VsPoint[i].y < Pos.y) && (VsPoint[j].y >= Pos.y )) || ((VsPoint[j].y < Pos.y) && (VsPoint[i].y >= Pos.y)) ) {
			// (Vs[i].x + (y - Vs[i].y) / AHeight * AWidth) < x //
			// AWidth and AHeight are dimensions that include a sign //
			if (VsPoint[i].x + (Pos.y-VsPoint[i].y) / (VsPoint[j].y-VsPoint[i].y) * (VsPoint[j].x-VsPoint[i].x) < Pos.x) {
				OddNodes = !OddNodes;
			}
        }
        // Make j the current point, since i is about it become the next one //
    	j = i;
	}

	// The algorithm says
	return OddNodes;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Nearest_Point_OnEdgeOf_Polygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return Nearest_Point_On_Chain2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Nearest_Point_On_Polygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	if ( Test_Point_Vs_Polygon2D( Pos, VsPoint, VsCount ) ) {
		return Pos;
	}
	else {
		return Nearest_Point_OnEdgeOf_Polygon2D( Pos, VsPoint, VsCount );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the position of the nearest corner point //
inline const Vector2D Nearest_CornerPoint_OnEdgeOf_Polygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return Nearest_CornerPoint_On_Chain2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //
// Get the index of the nearest corner point //
inline const size_t Nearest_CornerPointIndex_OnEdgeOf_Polygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return Nearest_CornerPointIndex_On_Chain2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the index of the nearest corner point //
inline const int Nearest_EdgeIndex_Of_Polygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return Nearest_EdgeIndex_Of_Chain2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Nearest_EdgeNormal_Of_Polygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	return Nearest_EdgeNormal_Of_Chain2D( Pos, VsPoint, VsCount );
}
// - ------------------------------------------------------------------------------------------ - //


//// - ------------------------------------------------------------------------------------------ - //
//struct cPointVsPolygon2D {
//};
//// - ------------------------------------------------------------------------------------------ - //
//
//// - ------------------------------------------------------------------------------------------ - //
//cPointVsPolygon2D StartPointVsPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
//	return cPointVsPolygon2D();
//}
//// - ------------------------------------------------------------------------------------------ - //
//bool TestPointVsPolygon2D( const cPointVsPolygon2D& Info ) {
//	return true;
//}
//// - ------------------------------------------------------------------------------------------ - //
//cPointVsPolygon2D SolvePointVsPolygon2D( const cPointVsPolygon2D& Info ) {
//	return cPointVsPolygon2D();
//}
//// - ------------------------------------------------------------------------------------------ - //
//cPointVsPolygon2D SolvePointVsPolygon2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
//	return cPointVsPolygon2D();
//}
//// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// TODO: possibly use http://alienryderflex.com/polygon_fill/
////  public-domain code by Darel Rex Finley, 2007
//
//int  nodes, nodeX[MAX_POLY_CORNERS], pixelX, pixelY, i, j, swap ;
//
////  Loop through the rows of the image.
//for (pixelY=IMAGE_TOP; pixelY<IMAGE_BOT; pixelY++) {
//
//  //  Build a list of nodes.
//  nodes=0; j=polyCorners-1;
//  for (i=0; i<polyCorners; i++) {
//    if (polyY[i]<(double) pixelY && polyY[j]>=(double) pixelY
//    ||  polyY[j]<(double) pixelY && polyY[i]>=(double) pixelY) {
//      nodeX[nodes++]=(int) (polyX[i]+(y-polyY[i])/(polyY[j]-polyY[i])
//      *(polyX[j]-polyX[i])); }
//    j=i; }
//
//  //  Sort the nodes, via a simple “Bubble” sort.
//  i=0;
//  while (i<nodes-1) {
//    if (nodeX[i]>nodeX[i+1]) {
//      swap=nodeX[i]; nodeX[i]=nodeX[i+1]; nodeX[i+1]=swap; if (i) i--; }
//    else {
//      i++; }}
//
//  //  Fill the pixels between node pairs.
//  for (i=0; i<nodes; i+=2) {
//    if   (nodeX[i  ]>=IMAGE_RIGHT) break;
//    if   (nodeX[i+1]> IMAGE_LEFT ) {
//      if (nodeX[i  ]< IMAGE_LEFT ) nodeX[i  ]=IMAGE_LEFT ;
//      if (nodeX[i+1]> IMAGE_RIGHT) nodeX[i+1]=IMAGE_RIGHT;
//      for (j=nodeX[i]; j<nodeX[i+1]; j++) fillPixel(j,pixelY); }}}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsPolygon2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
