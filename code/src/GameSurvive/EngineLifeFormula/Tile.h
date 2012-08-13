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
		Height( DEFAULT_TILE_HEIGHT )
	{
		AddMesh_Plane1();
	}
	
	~cTile() {
		//VVVLog( "* ~cTile: 0x%x", this );
		
		Active.DeleteAll();
		Passive.DeleteAll();
	}

public:
	void AddMesh_Plane0() {
		Mesh = cTileMesh( 5, 4 );
		
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,Height), Vector3D(0,0,1), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
	
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,-2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,-2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );

		Mesh.Index.Add( ABCSet<unsigned short>(0,1,2) );
		Mesh.Index.Add( ABCSet<unsigned short>(0,2,3) );
		Mesh.Index.Add( ABCSet<unsigned short>(0,3,4) );
		Mesh.Index.Add( ABCSet<unsigned short>(0,4,1) );
	}

	void AddMesh_Plane1() {
		Mesh = cTileMesh( 9, 2*4 );
		
		Vector3D DefaultNormal(0,0,1);
		GelColor Color1 = GEL_RGBA(255,255,255,255);
		GelColor Color2 = GEL_RGBA(255,255,255,0);
		
		// 0 - 1 - 2 // a -> b //      b //
		// | A | B | // ^   /  //    / | //
		// 3 - 4 - 5 // | /    //  /   v //
		// | C | D | // c      // c <- d //
		// 6 - 7 - 8 //        //        //
		
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,-2,Height), DefaultNormal, Color1, Color2 ) );	// 0 //
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+0,-2,Height), DefaultNormal, Color1, Color2 ) );	// 1 //
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,-2,Height), DefaultNormal, Color1, Color2 ) );	// 2 //

		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+0,Height), DefaultNormal, Color1, Color2 ) );	// 3 //
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+0,+0,Height), DefaultNormal, Color1, Color2 ) );	// 4 //
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+0,Height), DefaultNormal, Color1, Color2 ) );	// 5 //

		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+2,Height), DefaultNormal, Color1, Color2 ) );	// 6 //
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+0,+2,Height), DefaultNormal, Color1, Color2 ) );	// 7 //
		Mesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+2,Height), DefaultNormal, Color1, Color2 ) );	// 8 //

//		// Quad A //
//		Mesh.Index.Add( ABCSet<unsigned short>(0,1,3) );
//		Mesh.Index.Add( ABCSet<unsigned short>(1,4,3) );
//		// Quad B //
//		Mesh.Index.Add( ABCSet<unsigned short>(1,5,4) );
//		Mesh.Index.Add( ABCSet<unsigned short>(1,2,5) );
//		// Quad C //
//		Mesh.Index.Add( ABCSet<unsigned short>(3,7,6) );
//		Mesh.Index.Add( ABCSet<unsigned short>(3,4,7) );
//		// Quad D //
//		Mesh.Index.Add( ABCSet<unsigned short>(4,5,7) );
//		Mesh.Index.Add( ABCSet<unsigned short>(5,8,7) );

		// Quad A //
		Mesh.Index.Add( ABCSet<unsigned short>(0,4,3) );
		Mesh.Index.Add( ABCSet<unsigned short>(0,1,4) );
		// Quad B //
		Mesh.Index.Add( ABCSet<unsigned short>(1,2,4) );
		Mesh.Index.Add( ABCSet<unsigned short>(2,5,4) );
		// Quad C //
		Mesh.Index.Add( ABCSet<unsigned short>(3,4,6) );
		Mesh.Index.Add( ABCSet<unsigned short>(4,7,6) );
		// Quad D //
		Mesh.Index.Add( ABCSet<unsigned short>(4,8,7) );
		Mesh.Index.Add( ABCSet<unsigned short>(4,5,8) );
	}
	
	void UpdateMesh() {
		for ( int idx = 0; idx < Mesh.Vertex.Size(); idx++ ) {
			Mesh.Vertex[idx].Pos.z = Height;
		}
	}

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_TILE_H__ //
// - ------------------------------------------------------------------------------------------ - //
