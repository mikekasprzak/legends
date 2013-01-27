// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_SUBGRID2D_RAYCAST_H__
#define __GEL2_GRID_SUBGRID2D_RAYCAST_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/IVector.h>
// - ------------------------------------------------------------------------------------------ - //
inline void TraceRayGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int x1, const int y1, const int x2, const int y2, const u8* const TileInfo, const u8 BitMask, const int ViewRadius ) {
	// Only if it's untouched //
	//if ( Dest(x2,y2) == 0xFF ) 

	if ( (x1 == x2) && (y1 == y2) )
		return;
		
	{
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
		int StepsToTakeSquared = StepsToTake*StepsToTake;
		
		int FirstSolid = StepsToTake+1;
		for ( int idx = 0; idx <= StepsToTake; idx++ ) {
			int x = (idx * Diff.x.ToInt());
			int y = (idx * Diff.y.ToInt());
			int MagnitudeSquared = (x*x/StepsToTakeSquared) + (y*y/StepsToTakeSquared);
			
			x /= StepsToTake;
			y /= StepsToTake;
			x += x1;
			y += y1;
			
			int ToWrite = 0;
			if ( idx < FirstSolid ) {
				if ( (sqrt(MagnitudeSquared) > ViewRadius) || ((TileInfo[Src(x,y)] & BitMask) == BitMask) ) {
					FirstSolid = idx;
				}
				//ToWrite = 0;
			}
			else {
				ToWrite = idx-FirstSolid;
			}
			
			if ( Dest(x,y) > ToWrite )
				Dest(x,y) = ToWrite;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask, const int ViewRadius = 0xFF ) {
	Dest.Fill( 0xFF );

	for ( szt y = 0; y < Src.Height(); y++ ) {	
		for ( szt x = 0; x < Src.Width(); x++ ) {
			TraceRayGrid( Src, Dest, StartX, StartY, x, y, TileInfo, BitMask, ViewRadius );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( Grid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask, const int ViewRadius = 0xFF ) {
	GenerateRaycastGrid( SubGrid2D<u8>(Src), Dest, StartX, StartY, TileInfo, BitMask, ViewRadius );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_SUBGRID2D_RAYCAST_H__ //
// - ------------------------------------------------------------------------------------------ - //