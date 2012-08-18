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

#include <Graphics/Allocator/Vector3DAllocator.h>
#include <Types/Set.h>

#include <Grid/Grid2D_Class.h>
#include "Tile.h"

#include "Active.h"
#include "Room.h"

#include "../Camera/Camera.h"
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
		Size( 9/*32*/ ),
		Room( 0 ),
		Focus( 0 )
	{
		HalfSize = Real(Size) * Real::Half;

		TileSize = Real(4); // Should equal RegionSize / Size
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
	void Draw( const GelCamera& Camera );//const Matrix4x4& ViewMatrix );
	// NOTES: Object Drawing happens here, not inside Tile. Object Drawing will require
	//        some Y sorting, given that everything (at least early stuff) will be alpha
	//        sprites.
	//        Terrain is drawn here too, because here we can cache the data.
	// TODO: I should be able to generate the renderable geometry for any set of map tiles.
	//       This set of tiles is a thing I can remember or dispose of. Needed for scroll FX.
	//       Regrettably, a constantly scrolling map will need to rebuild the geometry every
	//       time you move. There might be some smartness to building it 2 tiles away from
	//       the edge, instead of just 1 tile.
	//       To cheat, I can draw all tiles one at a time. That will at least let me make
	//       this work sooner than later. The cheat wont be slow, until I start subdividing.
	//       Searching through subdivided data will be faster and do accurate projection
	//       textures if they stay separate, and I use a matrix to transform+draw it and all
	//       projection textures via the same vertices.
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ROOMVIEWER_H__ //
// - ------------------------------------------------------------------------------------------ - //
