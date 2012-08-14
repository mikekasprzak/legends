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
//#define TILE_DEBUG
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cTile {
public:
	enum { 
		// Constants //
		DEFAULT_TILE_HEIGHT = 8,	// Water Level = 0 //
		MAX_ACTIVE = 4,
		MAX_PASSIVE = 8,
	};

public:												// --Words (32bit)-- //
	cSoil								Soil;		// 4 - Soil Content //
	CArrayPtr<cActive*,MAX_ACTIVE>		Active;		// 4 //
	CArrayPtr<cPassive*,MAX_PASSIVE>	Passive;	// 8 //
	
	int Height;										// 1 - Elevation //
	signed char CornerHeight[4];					// 1 - Relative Corner Height //
	int PAD1[2];									// 2 - PADDING //
	
	Vector3D Normal;								// 3 - Surface Normal //
	int PAD2[1];									// 1 - PADDING //
	
//	Woof Burf;
	
	// TODO: Replace this with a custom/generative Mesh type //
	cTileMesh							TopMesh;	// 4 - Vertex and Index Pointers //
	cTileMesh							ShaftMesh;	// 4 - Vertex and Index Pointers //
	
//	cTileMesh							Mesh;
	
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
		Normal( 0, 0, 1 )
	{
		#ifdef TILE_DEBUG
			Log( "+ cTile(): 0x%x", this );
		#endif // TILE_DEBUG //
		
//		CornerHeight[0] = 0;
//		CornerHeight[1] = 0;
//		CornerHeight[2] = 0;
//		CornerHeight[3] = 0;

		AddMesh_TopPlane1();
		AddMesh_Shaft0();

		#ifdef TILE_DEBUG
			Log( "- cTile(): 0x%x", this );
		#endif // TILE_DEBUG //
	}
	
	~cTile() {
		#ifdef TILE_DEBUG
			Log( "+ ~cTile(): 0x%x", this );
		#endif // TILE_DEBUG //
		
		Active.DeleteAll();
		Passive.DeleteAll();

		#ifdef TILE_DEBUG
			Log( "- ~cTile(): 0x%x", this );
		#endif // TILE_DEBUG //
	}

public:
	void AddMesh_TopPlane0() {
		TopMesh = cTileMesh( 5, 2*2 );
		
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(0,0,Height), Vector3D(0,0,1), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
	
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,-2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,-2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+2,Height), Vector3D(0,0,1).Normal(), GEL_RGBA(255,255,255,255), GEL_RGBA(255,255,255,0) ) );

		TopMesh.Index.Add( ABCSet<unsigned short>(0,1,2) );
		TopMesh.Index.Add( ABCSet<unsigned short>(0,2,3) );
		TopMesh.Index.Add( ABCSet<unsigned short>(0,3,4) );
		TopMesh.Index.Add( ABCSet<unsigned short>(0,4,1) );
	}

	void AddMesh_TopPlane1() {
		TopMesh = cTileMesh( 9, 2*4 );
		
		Vector3D DefaultNormal(0,0,1);
		GelColor Color1 = GEL_RGBA(255,255,255,255);
		GelColor Color2 = GEL_RGBA(255,255,255,0);
		
		// 0 - 1 - 2 // a -> b //      b //
		// | A | B | // ^   /  //    / | //
		// 3 - 4 - 5 // | /    //  /   v //
		// | C | D | // c      // c <- d //
		// 6 - 7 - 8 //        //        //
		
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,-2,Height), DefaultNormal, Color1, Color2 ) );	// 0 //
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+0,-2,Height), DefaultNormal, Color1, Color2 ) );	// 1 //
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,-2,Height), DefaultNormal, Color1, Color2 ) );	// 2 //

		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+0,Height), DefaultNormal, Color1, Color2 ) );	// 3 //
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+0,+0,Height), DefaultNormal, Color1, Color2 ) );	// 4 //
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+0,Height), DefaultNormal, Color1, Color2 ) );	// 5 //

		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+2,Height), DefaultNormal, Color1, Color2 ) );	// 6 //
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+0,+2,Height), DefaultNormal, Color1, Color2 ) );	// 7 //
		TopMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+2,Height), DefaultNormal, Color1, Color2 ) );	// 8 //

//		// Quad A //
//		TopMesh.Index.Add( ABCSet<unsigned short>(0,1,3) );
//		TopMesh.Index.Add( ABCSet<unsigned short>(1,4,3) );
//		// Quad B //
//		TopMesh.Index.Add( ABCSet<unsigned short>(1,5,4) );
//		TopMesh.Index.Add( ABCSet<unsigned short>(1,2,5) );
//		// Quad C //
//		TopMesh.Index.Add( ABCSet<unsigned short>(3,7,6) );
//		TopMesh.Index.Add( ABCSet<unsigned short>(3,4,7) );
//		// Quad D //
//		TopMesh.Index.Add( ABCSet<unsigned short>(4,5,7) );
//		TopMesh.Index.Add( ABCSet<unsigned short>(5,8,7) );

		// Quad A //
		TopMesh.Index.Add( ABCSet<unsigned short>(0,4,3) );
		TopMesh.Index.Add( ABCSet<unsigned short>(0,1,4) );
		// Quad B //
		TopMesh.Index.Add( ABCSet<unsigned short>(1,2,4) );
		TopMesh.Index.Add( ABCSet<unsigned short>(2,5,4) );
		// Quad C //
		TopMesh.Index.Add( ABCSet<unsigned short>(3,4,6) );
		TopMesh.Index.Add( ABCSet<unsigned short>(4,7,6) );
		// Quad D //
		TopMesh.Index.Add( ABCSet<unsigned short>(4,8,7) );
		TopMesh.Index.Add( ABCSet<unsigned short>(4,5,8) );
	}

	void AddMesh_Shaft0() {
		ShaftMesh = cTileMesh( 8, 2*4 );

		Vector3D DefaultNormal(0,0,-1);
		GelColor Color1 = GEL_RGBA(255,255,255,0);
		GelColor Color2 = GEL_RGBA(255,255,255,0);
		
		// 0 - 1 // a -> b //      b //
		// |   | // ^   /  //    / | //
		// 2 - 3 // | /    //  /   v //
		//       // c      // c <- d //
		// 4 - 5 //
		// |   | //
		// 6 - 7 //
		
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,-2,Height), DefaultNormal /*Vector3D(-1,-1,+1).Normal()*/, Color1, Color2 ) );
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,-2,Height), DefaultNormal /*Vector3D(+1,-1,+1).Normal()*/, Color1, Color2 ) );
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+2,Height), DefaultNormal /*Vector3D(-1,+1,+1).Normal()*/, Color1, Color2 ) );
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+2,Height), DefaultNormal /*Vector3D(+1,+1,+1).Normal()*/, Color1, Color2 ) );
		
		int Floor = -16;
		if ( Height < -16 )
			Floor = Height-4;
		
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,-2,Floor), DefaultNormal /*Vector3D(-1,-1,+1).Normal()*/, Color1, Color2 ) );
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,-2,Floor), DefaultNormal /*Vector3D(+1,-1,+1).Normal()*/, Color1, Color2 ) );
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(-2,+2,Floor), DefaultNormal /*Vector3D(-1,+1,+1).Normal()*/, Color1, Color2 ) );
		ShaftMesh.Vertex.Add( cTileMeshVertex( Vector3D(+2,+2,Floor), DefaultNormal /*Vector3D(+1,+1,+1).Normal()*/, Color1, Color2 ) );

		// ^  Up //
		ShaftMesh.Index.Add( ABCSet<unsigned short>(1,0,5) );
		ShaftMesh.Index.Add( ABCSet<unsigned short>(0,4,5) );
		// <- Left //
		ShaftMesh.Index.Add( ABCSet<unsigned short>(0,2,4) );
		ShaftMesh.Index.Add( ABCSet<unsigned short>(2,6,4) );
		// v  Down //
		ShaftMesh.Index.Add( ABCSet<unsigned short>(2,3,6) );
		ShaftMesh.Index.Add( ABCSet<unsigned short>(3,7,6) );
		// -> Right //
		ShaftMesh.Index.Add( ABCSet<unsigned short>(3,1,7) );
		ShaftMesh.Index.Add( ABCSet<unsigned short>(1,5,7) );		
	}

public:
	void UpdateMesh() {
		// Top Mesh //
		for ( int idx = 0; idx < TopMesh.Vertex.Size(); idx++ ) {
			TopMesh.Vertex[idx].Pos.z = Height;
		}

		int Floor = -8;
		if ( Height < -8 )
			Floor = Height-4;
		
		// Shaft Mesh //
		for ( int idx = 0; idx < ShaftMesh.Vertex.Size(); idx++ ) {
			// Works on Shaft0 Only //
			if ( idx < 4 )
				ShaftMesh.Vertex[idx].Pos.z = Height;
			else 
				ShaftMesh.Vertex[idx].Pos.z = Floor;
		}
	}

};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_TILE_H__ //
// - ------------------------------------------------------------------------------------------ - //
