// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_CircleVsPolygon2D_H__
#define __AdvancedGeometry_CircleVsPolygon2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// NOTE: This function does and will not work because it changes the y distortion behavior of //
//   the corners, thus creating extra overlaps.  I.e. 2 points initially the same on the Y axis //
//   now become different, thusly creating a funnel where 2 hits are caught, instead of one //
// - ------------------------------------------------------------------------------------------ - //
// The hacked Point Vs Polygon Function, to handle circles //
bool TestCircleVsPolygon2D( const Vector2D& Pos, const Real Radius, const Vector2D* VsPoint, const size_t VsCount ) {
	// Odd number of nodes //
	bool OddNodes = false;
	
	// Previous Node //	
	size_t j = VsCount - 1;

	// For every side //
	for ( size_t i = 0; i < VsCount; i++ ) {
		// Test if the pair of points are on different sides of the point via the y axis //
		// NOTE: This is also supposed to rule out the i.y == j.y case //
		
		
		
		
		if ( ((VsPoint[i].y - Radius < Pos.y) && (VsPoint[j].y + Radius >= Pos.y)) ||
		 	 ((VsPoint[j].y - Radius < Pos.y) && (VsPoint[i].y + Radius >= Pos.y))
			) 
//		if ( ((VsPoint[i].y < Pos.y) && (VsPoint[j].y >= Pos.y)) ||
//		 	 ((VsPoint[j].y < Pos.y) && (VsPoint[i].y >= Pos.y))
//			) 
		{
			// Depending on the Sign of the AHeight, add or subtract radius //
			Real AHeight = (VsPoint[j].y-VsPoint[i].y);
			Real VsY = VsPoint[i].y;
			
			if ( AHeight < 0 ) {
				AHeight += Radius + Radius;
				VsY += Radius;
			}
			else {
				AHeight -= Radius + Radius;
				VsY -= Radius;
			}
			
			
			// Depending on the Sign of the AWidth, add or subtract radius //
			Real AWidth = (VsPoint[j].x-VsPoint[i].x);
			Real VsX = VsPoint[i].x;
			
			if ( AWidth < 0 ) {
				AWidth += Radius + Radius;
				VsX += Radius;
			}
			else {
				AWidth -= Radius + Radius;
				VsX -= Radius;
			}
			
				
			if (VsX + (Pos.y - VsY) / AHeight * AWidth < Pos.x)
			{
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
#endif // __AdvancedGeometry_CircleVsPolygon2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
