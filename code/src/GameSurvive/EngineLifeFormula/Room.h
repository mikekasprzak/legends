// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_ROOM_H__
#define __LIFEFORMULA_ROOM_H__
// - ------------------------------------------------------------------------------------------ - //
// Room -- Life ƒormula
// - ------------------------------------------------------------------------------------------ - //
// https://twitter.com/statuses/user_timeline/lifeformulas.rss
// https://twitter.com/statuses/user_timeline/lifeformulas.json
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Math/IVector.h>

//#include <Core/GelArray.h>
#include <Grid/Grid2D_Class.h>

#include "Active.h"
#include "Passive.h"
#include "Tile.h"

//#include "MapView.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cRoom {
public:
	// Simulation //
	int Iteration;
	// NOTE: Certain aspects of the simulation do not need to be done every iteration frame, such //
	//       as erosion of dirt. //
	
	cGrid2D<cTile>	Map; // Map Data //

	
public:
	cRoom( const int Width, const int Height );
	~cRoom();

public:
	// Add an IVector (Integer Vector) to a MapIndex encoded position //
	inline const int AddToIndex( const int MapIndex, const IVector2D& Offset ) const {
		if ( MapIndex == -1 )
			return -1;
		return Map.Index( Map.IndexToX( MapIndex ) + Offset.x, Map.IndexToY( MapIndex ) + Offset.y );
	}
	
	// NOTE: This is how we move around the map //
	// Best way to move an object is to remove it from the old position FIRST, then add it to an empty position. //
	//   Doing this will be sure that by entering and leaving the same tile, it has enough room to hold you. //
	inline void MoveActive( cActive* Object, const int FromIndex, const int ToIndex ) {
		Map[FromIndex].Active.Remove( Map[FromIndex].Active.FindNextIndex( Object ) );
		Map[ToIndex].Active.Get() = Object;
		Object->PosIndex = ToIndex;	// Take note of where we are now //
	}
	inline void MovePassive( cPassive* Object, const int FromIndex, const int ToIndex ) {
		Map[FromIndex].Passive.Remove( Map[FromIndex].Passive.FindNextIndex( Object ) );
		Map[ToIndex].Passive.Get() = Object;
	}
	
	// NOTE: This is how we remove from this map (To potentially add to a different map) //
	// Best way to remove an object from the Map. Remember, all objects have a unique object pointer instance. //
	//   It's only the Templates themselves that have the same pointers (cActiveTemplate), not the instances. //
	inline void RemoveActive( cActive* Object, const int FromIndex ) {
		Map[FromIndex].Active.Remove( Map[FromIndex].Active.FindNextIndex( Object ) );
		Object->PosIndex = -1;	// Note that we now have no idea where we are //
	}
	inline void RemovePassive( cPassive* Object, const int FromIndex ) {
		Map[FromIndex].Passive.Remove( Map[FromIndex].Passive.FindNextIndex( Object ) );
	}

	// NOTE: This is how we add to a map (Possibly a different map that it was Removed from) //
	// Best way to add an object to the Map. //
	inline void AddActive( cActive* Object, const int ToIndex ) {
		Map[ToIndex].Active.Get() = Object;
		Object->PosIndex = ToIndex;	// Take note of where we are now //
	}
	inline void AddPassive( cPassive* Object, const int ToIndex ) {
		Map[ToIndex].Passive.Get() = Object;
	}

	void UpdateMesh( const int x, const int y );
	
public:
	void Step( /*const Vector3D& MouseRay*/ );
	void Draw( /* const Vector3D Pos */ );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ROOM_H__ //
// - ------------------------------------------------------------------------------------------ - //
