// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_TILE_H__
#define __LIFEFORMULA_TILE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
#include <Debug/Log.h>

#include <Graphics/Allocator/Vector3DAllocator.h>
#include <Types/Set.h>

#include "Passive.h"
#include "Active.h"
#include "Soil.h"

#include "CArrayPtr.h"
#include "CArray.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cTile {
public:
	enum { 
		// Constants //
		DEFAULT_TILE_HEIGHT = 16,	// Water Level = 0 //
		MAX_ACTIVE = 4,
		MAX_PASSIVE = 8,
	};

public:												// --Words (32bit)-- //
	cSoil								Soil;		// 4 - Soil Content //
	CArrayPtr<cActive*,MAX_ACTIVE>		Active;		// 4 //
	CArrayPtr<cPassive*,MAX_PASSIVE>	Passive;	// 8 //
	
	// TODO: Replace this with a custom/generative Mesh type //
	Vector3DAllocator 					Vertex;		// 2 - Vertexes (Size, Ptr) //
	Allocator< ABCSet<short> >			Index;		// 2 - Vertex Indexes //
	Allocator< ABSet<short> >			OutlineIndex;
	// NOTES: Above is all relative 0,0,0 (Z=Height).
	//        Map Rendering, I go through all visible tiles and create new Mesh
	//        to represent the entire map. It is the sum of all individual tile
	//        Vertex data. Indexes need to be correctly offset in to the Mesh when 
	//        added. Positions need to be offset as well.
	//        I should allocate enough room for all vertices, and all indexes.
	//        However, I don't have to use them all.
	//        The above data should be usable to create a border/outline effect
	//        when I want to highlight a specific tile.
	//        I should have a preprocess function that eliminates duplicate verts.
	
	int Height;										// 1 - Elevation //

	// Note the time when we last changed the tile, so data can be cached //
	// LastUpdate // When we last refreshed the geometry //
	// LastChange // When we last had something changed (thusly need a geometry refresh) //
public:
	cTile() :
		Height( DEFAULT_TILE_HEIGHT ),
		Vertex( 4 ),		// 4 corners (Center Ignored) //
		Index( 3*2 ),		// 6 indexes, two triangles, make a quad (Side faces don't matter yet) //
		OutlineIndex( 5 )	// 5 indexes, line loop, make an outline for the tile //
	{
	}
	
	~cTile() {
		Active.DeleteAll();
		Passive.DeleteAll();
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_TILE_H__ //
// - ------------------------------------------------------------------------------------------ - //
