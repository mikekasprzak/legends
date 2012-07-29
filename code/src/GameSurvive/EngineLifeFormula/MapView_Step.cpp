// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>
#include <Input/Input_Mouse.h>

#include "MapView.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
void cMapView::Step( cGrid2D<cTile>& Map, const Vector3D& MouseRay ) {
	SelectedTile = -1;

	Rect2D Playfield( 
		-(TileSize * HalfSize), 
		-(TileSize * HalfSize),
		+(TileSize * Real(Size)), 
		+(TileSize * Real(Size))
		);

	// Convert Mouse Cursor Position in to an Index //
	if ( Playfield == MouseRay.ToVector2D() ) {
		int x = (Playfield.MapX( MouseRay.x ) * Real(Size));
		int y = (Playfield.MapY( -MouseRay.y ) * Real(Size));
		
		SelectedTile = (y * Size) + x;
	}
	else {
		SelectedTile = -1;
	}
	
	// Do Input //
	if ( SelectedTile != -1 ) {
		if ( Focus ) {
			if ( Mouse.Pressed() ) {
				int MapIndex = ToMapIndex(Map,SelectedTile);
				
				MapMoveActive( Map, Focus, Focus->PosIndex, MapIndex );
				
//				Focus->PosIndex = MapIndex;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
