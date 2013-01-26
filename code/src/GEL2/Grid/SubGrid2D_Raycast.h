// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_SUBGRID2D_RAYCAST_H__
#define __GEL2_GRID_SUBGRID2D_RAYCAST_H__
// - ------------------------------------------------------------------------------------------ - //
inline void TraceRaycastGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int x1, const int y1, const int x2, const int y2, const u8* const TileInfo, const u8 BitMask ) {
	// Only if it's untouched //
	if ( Dest(x2,y2) == 0xFF ) {
		int xDiff = x2-x1;
		int yDiff = y2-y1;

		int SignX = 1;
		int SignY = 1;
		int xDiffABS = xDiff;
		int yDiffABS = yDiff;
		
		// Figure out the sign of xDiff //
		if ( xDiff < 0 ) {
			SignX = -1;
			xDiffABS = -xDiff;
		}
	
		// Figure out the sign of yDiff //
		if ( yDiff < 0 ) {
			SignY = -1;
			yDiffABS = -yDiff;
		}
		
		// HACK //
		if ( xDiffABS > yDiffABS ) {
			Dest(x2,y2) = xDiffABS;
		}
		else {
			Dest(x2,y2) = yDiffABS;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask ) {
	Dest.Fill( 0xFF );

	for ( szt y = 0; y < Src.Height(); y++ ) {	
		for ( szt x = 0; x < Src.Width(); x++ ) {
			TraceRaycastGrid( Src, Dest, StartX, StartY, x, y, TileInfo, BitMask );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( Grid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask ) {
	GenerateRaycastGrid( SubGrid2D<u8>(Src), Dest, StartX, StartY, TileInfo, BitMask );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_SUBGRID2D_RAYCAST_H__ //
// - ------------------------------------------------------------------------------------------ - //
