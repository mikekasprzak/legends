// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_SUBGRID2D_RAYCAST_H__
#define __GEL2_GRID_SUBGRID2D_RAYCAST_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/IVector.h>
// - ------------------------------------------------------------------------------------------ - //
inline void TraceRayGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int x1, const int y1, const int x2, const int y2, const u8* const TileInfo, const u8 BitMask ) {
	// Only if it's untouched //
	if ( Dest(x2,y2) == 0xFF ) {
		IVector2D Start(x1,y1);
		IVector2D End(x2,y2);
		IVector2D Diff = End-Start;
		IVector2D Sign(1,1);
		IVector2D DiffABS(Diff);
		
		// Figure out the sign of xDiff //
		if ( Diff.x < 0 ) {
			Sign.x = -1;
			DiffABS.x = -Diff.x;
		}
	
		// Figure out the sign of yDiff //
		if ( Diff.y < 0 ) {
			Sign.y = -1;
			DiffABS.y = -Diff.y;
		}
		
		IVector2D LargeAxis(1,0);
		IVector2D SmallAxis(0,1);
		
		if ( DiffABS.x < DiffABS.y ) {
			LargeAxis = IVector2D(0,1);
			SmallAxis = IVector2D(1,0);
		}
		
		int StepsToTake = (LargeAxis*DiffABS).SumOf().ToInt();
		
		int FirstSolid = StepsToTake+1;
		for ( int idx = 0; idx <= StepsToTake; idx++ ) {
			int x = x1 + ((idx*Diff.x.ToInt())/StepsToTake);
			int y = y1 + ((idx*Diff.y.ToInt())/StepsToTake);
			if ( idx < FirstSolid ) {
				if ( (TileInfo[Src(x,y)] & BitMask) == BitMask ) {
					FirstSolid = idx;
				}
				Dest(x,y) = 0;
			}
			else {
				Dest(x,y) = idx-FirstSolid;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask ) {
	Dest.Fill( 0xFF );

	for ( szt y = 0; y < Src.Height(); y++ ) {	
		for ( szt x = 0; x < Src.Width(); x++ ) {
			TraceRayGrid( Src, Dest, StartX, StartY, x, y, TileInfo, BitMask );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( Grid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask ) {
	GenerateRaycastGrid( SubGrid2D<u8>(Src), Dest, StartX, StartY, TileInfo, BitMask );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_SUBGRID2D_RAYCAST_H__ //
// - ------------------------------------------------------------------------------------------ - //
