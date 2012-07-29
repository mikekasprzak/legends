// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_ROOMVIEWER_H__
#define __LIFEFORMULA_ROOMVIEWER_H__
// - ------------------------------------------------------------------------------------------ - //
// Room View -- 
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
#include <Math/IVector.h>
#include <Math/Real.h>
#include <Math/Vector.h>

#include <Grid/Grid2D_Class.h>
#include "Tile.h"

#include "Active.h"
#include "Room.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cRoomViewer {
public:
	IVector2D	Pos;
	Integer		Size; 		// Not seperate Width and Height, as all views will be square //
	Real 		HalfSize;	// Real because the sizes tend to be odd //

	Real TileSize;
	Real TileHalfSize;
	
	int SelectedTile;
	
	cRoom*		Room;		// The Room we care about //
	cActive*	Focus;		// Who we are watching in the room (as the camera) //

public:
	inline cRoomViewer() :
		Pos( 0, 0 ),
		Size( 9 ),
		Room( 0 ),
		Focus( 0 )
	{
		HalfSize = Real(Size) * Real::Half;

		TileSize = Real(6); // Should equal RegionSize / Size
		TileHalfSize = TileSize * Real::Half;
	}
	
	inline void Set( cRoom* _Room ) {
		Room = _Room;
	}
	
	inline ~cRoomViewer() {
	}

public:
	// Convert a local (SelectedTile) coordinate in to a map coordinate //
	inline const int ToMapIndex( const cGrid2D<cTile>& Map, const int Index ) const {
		if ( Index == -1 )
			return -1;
		return (Map.Width() * (Pos.y + (Index / Size))) + Pos.x + (Index % Size);
	}

public:
	void Step( const Vector3D& MouseRay );
	void Draw( );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ROOMVIEWER_H__ //
// - ------------------------------------------------------------------------------------------ - //
