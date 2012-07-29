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
	
	cActive* Focus;

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
	
	// Add an IVector (Integer Vector) to a MapIndex encoded position //
	inline const int AddToMapIndex( const cGrid2D<cTile>& Map, const int MapIndex, const IVector2D& Offset ) const {
		if ( MapIndex == -1 )
			return -1;
		return Map.Index( Map.IndexToX( MapIndex ) + Offset.x, Map.IndexToY( MapIndex ) + Offset.y );
	}
	
	// Best way to move an object is to remove it from the old position FIRST, then add it to an empty position. //
	//   Doing this will be sure that by entering and leaving the same tile, it has enough room to hold you. //
	inline void MapMoveActive( cGrid2D<cTile>& Map, cActive* Object, const int FromIndex, const int ToIndex ) {
		Map[FromIndex].Active.Remove( Map[FromIndex].Active.FindNextIndex( Object ) );
		Map[ToIndex].Active.Get() = Object;
		Object->PosIndex = ToIndex;	// Take note of where we are now //
	}
	inline void MapMovePassive( cGrid2D<cTile>& Map, cPassive* Object, const int FromIndex, const int ToIndex ) {
		Map[FromIndex].Passive.Remove( Map[FromIndex].Passive.FindNextIndex( Object ) );
		Map[ToIndex].Passive.Get() = Object;
	}
	
	// Best way to remove an object from the Map. Remember, all objects have a unique object pointer instance. //
	//   It's only the Templates themselves that have the same pointers (cActiveTemplate), not the instances. //
	inline void MapRemoveActive( cGrid2D<cTile>& Map, cActive* Object, const int FromIndex ) {
		Map[FromIndex].Active.Remove( Map[FromIndex].Active.FindNextIndex( Object ) );
		Object->PosIndex = -1;	// Note that we now have no idea where we are //
	}
	inline void MapRemovePassive( cGrid2D<cTile>& Map, cPassive* Object, const int FromIndex ) {
		Map[FromIndex].Passive.Remove( Map[FromIndex].Passive.FindNextIndex( Object ) );
	}

	// Best way to add an object to the Map. //
	inline void MapAddActive( cGrid2D<cTile>& Map, cActive* Object, const int ToIndex ) {
		Map[ToIndex].Active.Get() = Object;
		Object->PosIndex = ToIndex;	// Take note of where we are now //
	}
	inline void MapAddPassive( cGrid2D<cTile>& Map, cPassive* Object, const int ToIndex ) {
		Map[ToIndex].Passive.Get() = Object;
	}


public:
	void Step( cGrid2D<cTile>& Map, const Vector3D& MouseRay );
	void Draw( const cGrid2D<cTile>& Map );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_MAPVIEW_H__ //
// - ------------------------------------------------------------------------------------------ - //
