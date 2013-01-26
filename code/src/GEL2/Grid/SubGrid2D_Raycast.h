// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_SUBGRID2D_RAYCAST_H__
#define __GEL2_GRID_SUBGRID2D_RAYCAST_H__
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( const SubGrid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask ) {
	
}
// - ------------------------------------------------------------------------------------------ - //
inline void GenerateRaycastGrid( Grid2D<u8>& Src, Grid2D<u8>& Dest, const int StartX, const int StartY, const u8* const TileInfo, const u8 BitMask ) {
	GenerateRaycastGrid( SubGrid2D<u8>(Src), Dest, StartX, StartY, TileInfo, BitMask );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_SUBGRID2D_RAYCAST_H__ //
// - ------------------------------------------------------------------------------------------ - //
