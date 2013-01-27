// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_GENERATEDISTANCEGRID_H__
#define __GEL2_GRID_GRID2D_GENERATEDISTANCEGRID_H__
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void GenerateMagnitudeDistanceGrid2D( Grid2D<tType>& Dest, const int x1, const int y1 ) {
	for ( szt y2 = 0; y2 < Dest.Height(); y2++ ) {	
		for ( szt x2 = 0; x2 < Dest.Width(); x2++ ) {
			int xDiff = x2-x1;
			int yDiff = y2-y1;
		
			int xDiffABS = xDiff;
			if ( xDiff < 0 )
				xDiffABS = -xDiff;
		
			int yDiffABS = yDiff;
			if ( yDiff < 0 )
				yDiffABS = -yDiff;

			// Magnitude //
			int MagnitudeSquared = xDiffABS*xDiffABS+yDiffABS*yDiffABS;
			Dest(x2,y2) = sqrt(MagnitudeSquared);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline const Grid2D<tType> GenerateMagnitudeDistanceGrid2D( const szt w, const szt h, const int CenterX, const int CenterY ) {
	Grid2D<tType> Ret(w,h);
	GenerateMagnitudeDistanceGrid2D( Ret, CenterX, CenterY );
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void GenerateManhattanDistanceGrid2D( Grid2D<tType>& Dest, const int x1, const int y1 ) {
	for ( szt y2 = 0; y2 < Dest.Height(); y2++ ) {	
		for ( szt x2 = 0; x2 < Dest.Width(); x2++ ) {
			int xDiff = x2-x1;
			int yDiff = y2-y1;
		
			int xDiffABS = xDiff;
			if ( xDiff < 0 )
				xDiffABS = -xDiff;
		
			int yDiffABS = yDiff;
			if ( yDiff < 0 )
				yDiffABS = -yDiff;

			// Manhattan Distance //
			Dest(x2,y2) = xDiffABS+yDiffABS;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline const Grid2D<tType> GenerateManhattanDistanceGrid2D( const szt w, const szt h, const int CenterX, const int CenterY ) {
	Grid2D<tType> Ret(w,h);
	GenerateManhattanDistanceGrid2D( Ret, CenterX, CenterY );
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void GenerateMaxitudeDistanceGrid2D( Grid2D<tType>& Dest, const int x1, const int y1 ) {
	for ( szt y2 = 0; y2 < Dest.Height(); y2++ ) {	
		for ( szt x2 = 0; x2 < Dest.Width(); x2++ ) {
			int xDiff = x2-x1;
			int yDiff = y2-y1;
		
			int xDiffABS = xDiff;
			if ( xDiff < 0 )
				xDiffABS = -xDiff;
		
			int yDiffABS = yDiff;
			if ( yDiff < 0 )
				yDiffABS = -yDiff;

			// Maxitude Distance (Chebyshev Distance) //
			if ( xDiffABS > yDiffABS )
				Dest(x2,y2) = xDiffABS;
			else
				Dest(x2,y2) = yDiffABS;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline const Grid2D<tType> GenerateMaxitudeDistanceGrid2D( const szt w, const szt h, const int CenterX, const int CenterY ) {
	Grid2D<tType> Ret(w,h);
	GenerateMaxitudeDistanceGrid2D( Ret, CenterX, CenterY );
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline void GenerateMinitudeDistanceGrid2D( Grid2D<tType>& Dest, const int x1, const int y1 ) {
	for ( szt y2 = 0; y2 < Dest.Height(); y2++ ) {	
		for ( szt x2 = 0; x2 < Dest.Width(); x2++ ) {
			int xDiff = x2-x1;
			int yDiff = y2-y1;
		
			int xDiffABS = xDiff;
			if ( xDiff < 0 )
				xDiffABS = -xDiff;
		
			int yDiffABS = yDiff;
			if ( yDiff < 0 )
				yDiffABS = -yDiff;

			// Axitude (Axis'manitude? since it generates axis distances) //
			// Minitude Distance (the opposite of Chebyshev, Min instead of Max) //
			if ( xDiffABS < yDiffABS )
				Dest(x2,y2) = xDiffABS;
			else
				Dest(x2,y2) = yDiffABS;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
inline const Grid2D<tType> GenerateMinitudeDistanceGrid2D( const szt w, const szt h, const int CenterX, const int CenterY ) {
	Grid2D<tType> Ret(w,h);
	GenerateMinitudeDistanceGrid2D( Ret, CenterX, CenterY );
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_GRID2D_GENERATEDISTANCEGRID_H__ //
// - ------------------------------------------------------------------------------------------ - //
