// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_SUBGRID2D_RAYCAST_H__
#define __GEL2_GRID_SUBGRID2D_RAYCAST_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/IVector.h>
#include <Math/Vector.h>
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
	Dest.Fill( 0xFF ); // ? //

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
// This is flawed because: 
// - Tiles in shadow don't cast a shadow (and need to). "Untouched" and Swirl's fault.
// - Shadow rasterizing is expensive and slow (when it's per tile).
// - ------------------------------------------------------------------------------------------ - //
inline void TraceShadowGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int x1, const int y1, const int x2, const int y2, const u8* const TileInfo, const u8 BitMask ) {
	// Only if untouched //
	if ( Dest(x2,y2) == 0xFF ) {
		if ( (x1 == x2) && (y1 == y2) ) {
			Dest(x2,y2) = 0;
			return;
		}
		
		// If our tile is solid, then make it cast a shadow //
		if ( (TileInfo[Src(x2,y2)] & BitMask) == BitMask ) {		
			Vector2D Start(x1,y1);
			Start += Vector2D::Half;
				
			Vector2D End(x2,y2);
			End += Vector2D::Half;
			
			Vector2D Ray = End-Start;
			Vector2D RayNormal = Ray.Normal();
			
			Real Radius(1.01f);
//			Real Radius(0.7071f);
			
			Vector2D PointA = End + (RayNormal.Tangent() * Radius);
			Vector2D PointB = End - (RayNormal.Tangent() * Radius);
			
			Vector2D RayA = PointA-Start;
			Vector2D RayB = PointB-Start;
			Vector2D RayATangent = -RayA.Tangent();
			Vector2D RayBTangent = RayB.Tangent();
			
			for ( szt y = 0; y < Dest.Height(); y++ ) {	
				for ( szt x = 0; x < Dest.Width(); x++ ) {
					if ( (Dest(x,y) == 0) || (Dest(x,y) == 0xFF) ) {
						Vector2D PointToStart( x1-((int)x), y1-((int)y) );
						Vector2D PointToEnd( x2-((int)x), y2-((int)y) );
						
						if ((dot(PointToStart,RayATangent) < Real::Zero) && 
							(dot(PointToStart,RayBTangent) < Real::Zero) &&
							(dot(PointToEnd,Ray) < Real::Zero)) 
						{					
							Dest(x,y) = 2;
						}
					}
				}
			}
			
			Dest(x2,y2) = 1;
		}
		else {
			Dest(x2,y2) = 0;
		}		
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateShadowGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask ) {
	Dest.Fill( 0xFF );

//	for ( int y = StartY-5; y < StartY+6; y++ ) {	
//		for ( int x = StartX-5; x < StartX+6; x++ ) {

//	for ( szt y = 0; y < Src.Height(); y++ ) {	
//		for ( szt x = 0; x < Src.Width(); x++ ) {
//			TraceShadowGrid( Src, Dest, StartX, StartY, x, y, TileInfo, BitMask );
//		}
//	}

	IVector2D Pos(StartX,StartY);
	IVector2D Facing(0,-1);

	szt Repeat = 1;

	// Do the start //
	{
		szt Index = Src.DeadIndex(Pos.x,Pos.y,SZT_MAX);
		if ( Index != SZT_MAX ) { 
			TraceShadowGrid( Src, Dest, StartX, StartY, StartX, StartY, TileInfo, BitMask );
		}
	}
	
	szt Fails = 0;
	
	// Do the rest (alternatively, check if Repeat is greater than the dimensions) //
	while( Repeat > Fails ) {//Dest.Width() ) {//Value < Dest.Size() ) {
		Fails = 0;
		// Do it twice //
		for ( szt idx2 = 2+1; --idx2 ; ) {
			// Go straight "Repeat" number of times //
			for ( szt idx = Repeat; idx-- ; ) {
				Pos += Facing;
				szt Index = Src.DeadIndex(Pos.x,Pos.y,SZT_MAX);
				if ( Index != SZT_MAX ) {
					TraceShadowGrid( Src, Dest, StartX, StartY, Pos.x.ToInt(), Pos.y.ToInt(), TileInfo, BitMask );
				}
				else {
					Fails++;
				}
			}
			// Turn //
			Facing = Facing.Tangent();
		}
		// Increase repeats (every 2 times) //
		Repeat++;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_SUBGRID2D_RAYCAST_H__ //
// - ------------------------------------------------------------------------------------------ - //
