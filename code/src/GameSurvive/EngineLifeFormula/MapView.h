// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_MAPVIEW_H__
#define __LIFEFORMULA_MAPVIEW_H__
// - ------------------------------------------------------------------------------------------ - //
// Map View -- 
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
#include <Math/IVector.h>
#include <Math/Real.h>
#include <Math/Vector.h>

#include <Grid/Grid2D_Class.h>
#include "Tile.h"
#include "Active.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cMapView {
public:
	IVector2D	Pos;
	Integer		Size; 		// Not seperate Width and Height, as all views will be square //
	Real 		HalfSize;	// Real because the sizes tend to be odd //

	Real TileSize;
	Real TileHalfSize;
	
	int SelectedTile;
	
	cActive* Focus;			// Who we are watching (as the camera) //

public:
	inline cMapView() :
		Pos( 0, 0 ),
		Size( 9 ),
		Focus( 0 )
	{
		HalfSize = Real(Size) * Real::Half;

		TileSize = Real(6); // Should equal RegionSize / Size
		TileHalfSize = TileSize * Real::Half;
	}
	
	inline ~cMapView() {
	}

public:
	// Convert a local (SelectedTile) coordinate in to a map coordinate //
	inline const int ToMapIndex( const cGrid2D<cTile>& Map, const int Index ) const {
		if ( Index == -1 )
			return -1;
		return (Map.Width() * (Pos.y + (Index / Size))) + Pos.x + (Index % Size);
	}

public:
	void Step( class cRoom* Room, const Vector3D& MouseRay );
	void Draw( class cRoom* Room );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_MAPVIEW_H__ //
// - ------------------------------------------------------------------------------------------ - //
