// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_WORLD_H__
#define __LIFEFORMULA_WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
// World -- Life ƒormula
// - ------------------------------------------------------------------------------------------ - //
// https://twitter.com/statuses/user_timeline/lifeformulas.rss
// https://twitter.com/statuses/user_timeline/lifeformulas.json
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>

#include <Core/GelArray.h>
#include <Grid/Grid2D_Class.h>

#include "Active.h"
#include "Passive.h"
#include "Tile.h"

#include "MapView.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	// Simulation //
	int Iteration;
	// NOTE: Certain aspects of the simulation do not need to be done every iteration frame, such //
	//       as erosion of dirt. //
	
	// World //
	cGrid2D<cTile> 					Map;
	cGelArrayPtr<cActiveTemplate*>	ActiveTemplate;		// Pointers because every time these 2 Arrays
	cGelArrayPtr<cPassiveTemplate*>	PassiveTemplate;	//   resize, the addresses would break.

	// Camera //
	cMapView View;
	
public:
	cWorld( const int Width, const int Height ) :
		Map( Width, Height, cTile() ),
		View()
	{
		// Dummy Create //
		ActiveTemplate.PushBack( new cActiveTemplate() );
		ActiveTemplate.Back()->Load( "Content/Misc/TestActive.json" );
		
		Log( "Active Inventory: %i", ActiveTemplate.Back()->InventorySize );

		View.Focus = new cActive( ActiveTemplate.Back() );		// Create //
		View.MapAddActive( Map, View.Focus, Map.Index(2,1) );	// Add to Map //

//		Map(2,1).Active.Get() = new cActive( ActiveTemplate.Back() );
//		View.Focus = Map(2,1).Active[Map(2,1).Active.FirstIterator()];
//		View.Focus->PosIndex = Map.Index(2,1);
		
		PassiveTemplate.PushBack( new cPassiveTemplate() );
		PassiveTemplate.Back()->Load( "Content/Misc/TestPassive.json" );
		
		Log( "Passive Stack Max: %i", PassiveTemplate.Back()->MaxCount );

		Map(3,1).Passive.Get() = new cPassive( PassiveTemplate.Back() );
	}
	
	~cWorld() {
		ActiveTemplate._DeleteAll();
		PassiveTemplate._DeleteAll();
	}

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

public:
	void Step( const Vector3D& MouseRay );
	void DrawView( /* const Vector3D Pos */ );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
