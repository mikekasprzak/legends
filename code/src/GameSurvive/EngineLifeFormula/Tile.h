// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_TILE_H__
#define __LIFEFORMULA_TILE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
#include <Debug/Log.h>
#include <Debug/Woof.h>

#include "TileMesh.h"

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
	
	int Height;										// 1 - Elevation //
	int Padding[3];									// 3 - Padding (until I have something to put here) //
	
//	Woof Burf;
	
	// TODO: Replace this with a custom/generative Mesh type //
	cTileMesh							Mesh;		// 4 - Vertex and Index Pointers //
//	Allocator< ABSet<short> >			OutlineIndex;
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

	// Note the time when we last changed the tile, so data can be cached //
	// LastUpdate // When we last refreshed the geometry //
	// LastChange // When we last had something changed (thusly need a geometry refresh) //
public:
	cTile() :
		Height( DEFAULT_TILE_HEIGHT ),
		Mesh( 5, 4 )
//		OutlineIndex( 5 )	// 5 indexes, line loop, make an outline for the tile //
	{

		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,0), Vector3D(0,0,1), GEL_RGBA(255,255,255,128), GEL_RGBA(255,255,255,0) ) );
	
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,-1,0), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,-1,0), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,0), GEL_RGBA(255,255,255,0) ) );
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+1,+1,0), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-1,+1,0), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );

//		for ( int idx = 0; idx < Mesh.Vertex.Size(); idx++ ) {
//			Log( "! TTT %i (%f %f %f)", idx, Mesh.Vertex[idx].Pos.x.ToFloat(), Mesh.Vertex[idx].Pos.y.ToFloat(), Mesh.Vertex[idx].Pos.z.ToFloat() );
//		}

		Mesh.Index.Add( ABCSet<unsigned short>(0,1,2) );
		Mesh.Index.Add( ABCSet<unsigned short>(0,2,3) );
		Mesh.Index.Add( ABCSet<unsigned short>(0,3,4) );
		Mesh.Index.Add( ABCSet<unsigned short>(0,4,1) );
		
//		VVLog( "* Me: 0x%x (Mesh: 0x%x Vert: 0x%x Index: 0x%x)", this, &Mesh, Mesh.Vertex.Data, Mesh.Index.Data );
	}
	
	~cTile() {
//		VVLog( "* Dead: 0x%x", this );
		
		Active.DeleteAll();
		Passive.DeleteAll();
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_TILE_H__ //
// - ------------------------------------------------------------------------------------------ - //
