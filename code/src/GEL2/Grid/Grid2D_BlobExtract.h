// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_BLOBEXTRACT_H__
#define __GEL2_GRID_GRID2D_BLOBEXTRACT_H__
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
const Grid2D<u16> BlobExtract( const Grid2D<tType>& Data, const tType Middle = 0.5f );

template< typename tType >
const Grid2D<u16> BlobExtractWrapped( const Grid2D<tType>& Data, const tType Middle = 0.5f );
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_GRID2D_BLOBEXTRACT_H__ //
// - ------------------------------------------------------------------------------------------ - //
