// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GraphicsDraw.h>

#include "RoomView.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
void cRoomView::Draw( ) {
	const cGrid2D<cTile>& Map = Room->Map;
	
	for ( size_t y = 0; y < Size; y++ ) {
		for ( size_t x = 0; x < Size; x++ ) {
			int Index = Map.Index( x, y );

			// HACK: Negative Y
			// HACK: Funny Z to test depth			
			Vector3D DrawPos( 
					+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
					-(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
					Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)//(Real(x) / Real(1)) * Real(y)
					);

			gelSetColor( GEL_RGBA(0,255,0,128) );
			if ( x == (SelectedTile % Size) )
				if ( y == (SelectedTile / Size) )
					gelSetColor( GEL_RGBA(255,255,0,128) );					
			
			gelDrawSquareFill( 
				DrawPos,
				TileHalfSize 
				);

			gelSetColor( GEL_RGB_GREEN );
			if ( x == (SelectedTile % Size) )
				if ( y == (SelectedTile / Size) )
					gelSetColor( GEL_RGB_RED );

			gelDrawSquare( 
				DrawPos,
				TileHalfSize 
				);
			
			if ( Map[Index].Active.Size() > 0 ) {
				gelSetColor( GEL_RGB_YELLOW );
				gelDrawCircleFill( 
					DrawPos, 
					TileHalfSize * Real::ThreeQuarter
					);
			}					
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
