// - ------------------------------------------------------------------------------------------ - //
#include "Room.h"

#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
cRoom::cRoom( const int Width, const int Height ) :
	Map( Width, Height )
{
	Log("+ Start of cRoom()...");

	// Dummy Create //
	cEngine::LoadActiveTemplate( "Content/Misc/TestActive.json" );
	
	Log( "* Active Inventory: %i", cEngine::ActiveTemplate.Back()->InventorySize );

	cEngine::View->Focus = new cActive( cEngine::ActiveTemplate.Back() );	// Create //
	AddActive( cEngine::View->Focus, Map.Index(1,1) );						// Add to Map //

	cEngine::LoadPassiveTemplate( "Content/Misc/TestPassive.json" );
	
	Log( "* Passive Stack Max: %i", cEngine::PassiveTemplate.Back()->MaxCount );

	Map(1,1).Passive.Get() = new cPassive( cEngine::PassiveTemplate.Back() );
	
	Log("* Generating Map");
	Generate();
	
	Log("- cRoom() done.");
}
// - ------------------------------------------------------------------------------------------ - //
cRoom::~cRoom() {
	Log("+ Start of ~cRoom()...");
	
	// ****** //
	
	Log("- ~cRoom() done.");
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRoom::UpdateMesh( const int Index ) {	
	int x = Map.IndexToX( Index );
	int y = Map.IndexToY( Index );
	
	Map[Index].UpdateMesh();

/*
	// Plane1 //	
	{
		Vector3D DefaultNormal = Map[Index].TopMesh.Vertex[4].Normal; // Center //
		int Height = Map[Index].Height;

		cTileMesh& Mesh = Map[Index].TopMesh;
	
		Mesh.Vertex[0].Normal = DefaultNormal;
		Mesh.Vertex[0].Normal += Real(Map.Wrap(x-1,y-0).Height - Height).Max(0).Normal() * Vector3D(-1,-0,0);
		Mesh.Vertex[0].Normal += Real(Map.Wrap(x-1,y-1).Height - Height).Max(0).Normal() * Vector3D(-0.5,-0.5,0);
		Mesh.Vertex[0].Normal += Real(Map.Wrap(x-0,y-1).Height - Height).Max(0).Normal() * Vector3D(-0,-1,0);
		Mesh.Vertex[0].Normal.Normalize();//AxisNormalize().Normalize();
	
		Mesh.Vertex[1].Normal = DefaultNormal;
		Mesh.Vertex[1].Normal += Real(Map.Wrap(x-0,y-1).Height - Height).Max(0).Normal() * Vector3D(-0,-1,0);
		Mesh.Vertex[1].Normal.Normalize();//AxisNormalize().Normalize();
	
		Mesh.Vertex[2].Normal = DefaultNormal;
		Mesh.Vertex[2].Normal += Real(Map.Wrap(x+1,y-0).Height - Height).Max(0).Normal() * Vector3D(+1,-0,0);
		Mesh.Vertex[2].Normal += Real(Map.Wrap(x+1,y-1).Height - Height).Max(0).Normal() * Vector3D(+0.5,-0.5,0);
		Mesh.Vertex[2].Normal += Real(Map.Wrap(x+0,y-1).Height - Height).Max(0).Normal() * Vector3D(+0,-1,0);
		Mesh.Vertex[2].Normal.Normalize();//AxisNormalize().Normalize();
	
		Mesh.Vertex[3].Normal = DefaultNormal;
		Mesh.Vertex[3].Normal += Real(Map.Wrap(x-1,y+0).Height - Height).Max(0).Normal() * Vector3D(-1,+0,0);
		Mesh.Vertex[3].Normal.Normalize();//AxisNormalize().Normalize();
		
		// No Middle //
	
		Mesh.Vertex[5].Normal = DefaultNormal;
		Mesh.Vertex[5].Normal += Real(Map.Wrap(x+1,y+0).Height - Height).Max(0).Normal() * Vector3D(+1,+0,0);
		Mesh.Vertex[5].Normal.Normalize();//AxisNormalize().Normalize();
	
		Mesh.Vertex[6].Normal = DefaultNormal;
		Mesh.Vertex[6].Normal += Real(Map.Wrap(x-1,y+0).Height - Height).Max(0).Normal() * Vector3D(-1,+0,0);
		Mesh.Vertex[6].Normal += Real(Map.Wrap(x-1,y+1).Height - Height).Max(0).Normal() * Vector3D(-0.5,+0.5,0);
		Mesh.Vertex[6].Normal += Real(Map.Wrap(x-0,y+1).Height - Height).Max(0).Normal() * Vector3D(-0,+1,0);
		Mesh.Vertex[6].Normal.Normalize();//AxisNormalize().Normalize();
	
		Mesh.Vertex[7].Normal = DefaultNormal;
		Mesh.Vertex[7].Normal += Real(Map.Wrap(x+0,y+1).Height - Height).Max(0).Normal() * Vector3D(+0,+1,0);
		Mesh.Vertex[7].Normal.Normalize();//AxisNormalize().Normalize();
	
		Mesh.Vertex[8].Normal = DefaultNormal;
		Mesh.Vertex[8].Normal += Real(Map.Wrap(x+1,y+0).Height - Height).Max(0).Normal() * Vector3D(+1,+0,0);
		Mesh.Vertex[8].Normal += Real(Map.Wrap(x+1,y+1).Height - Height).Max(0).Normal() * Vector3D(+0.5,+0.5,0);
		Mesh.Vertex[8].Normal += Real(Map.Wrap(x+0,y+1).Height - Height).Max(0).Normal() * Vector3D(+0,+1,0);
		Mesh.Vertex[8].Normal.Normalize();//AxisNormalize().Normalize();
	}
*/

	// Ambient Occlusion based on height of neighbours //
	{
		Vector3D UpNormal(0,0,1);		
		
		for ( size_t idx = 0; idx < Map[Index].Mesh.Vertex.Size(); idx++ ) {
			cTileMeshVertex& Me = Map[Index].Mesh.Vertex[idx];
			int Value = 255;
			int VsHeight = -1024; // SOME UNUSED TOO-LOW HEIGHT //
			
			bool IsUpNormal = dot( UpNormal, Me.Normal ) > Real(0.1); // Including error //

			Vector3D ToCenter = (Vector3D(0,0,Me.Pos.z) - Me.Pos);
			ToCenter.AxisNormalize();
			
			bool IsCornerNormal = ToCenter.Manhattan() > Real(1.01); // Including error //
			IVector2D FromCenter( (int)-ToCenter.x, (int)-ToCenter.y );			
			
			if ( IsUpNormal ) {
				// Up Normals //
				if ( IsCornerNormal ) {
					// 3 Corners //
					int NewHeight = Map.Wrap( x, y + FromCenter.y ).Height;
					if ( NewHeight > VsHeight )
						VsHeight = NewHeight;
					NewHeight = Map.Wrap( x + FromCenter.x, y + FromCenter.y ).Height;
					if ( NewHeight > VsHeight )
						VsHeight = NewHeight;
					NewHeight = Map.Wrap( x + FromCenter.x, y ).Height;
					if ( NewHeight > VsHeight )
						VsHeight = NewHeight;
				}
				else { // Mid Normal //
					VsHeight = Map.Wrap( x + FromCenter.x, y + FromCenter.y ).Height;
				}
				
				// Exclusive, because we crease only when the other is taller //
				if ( Real(VsHeight) > Me.Pos.z ) {
					Value = 128;
				}
			}
			else {
				// Side Normals //
				if ( IsCornerNormal ) {
					// Two Corners Only! //					
					// The Diagonal //
					int NewHeight = Map.Wrap( x + FromCenter.x, y + FromCenter.y ).Height;
					if ( NewHeight > VsHeight )
						VsHeight = NewHeight;
					// The Normal Direction //
					NewHeight = Map.Wrap( x + (int)Me.Normal.x, y + (int)Me.Normal.y ).Height;
					if ( NewHeight > VsHeight )
						VsHeight = NewHeight;
				}
				else { // Mid Normal //
					VsHeight = Map.Wrap( x + FromCenter.x, y + FromCenter.y ).Height;
				}
				
				// Inclusive, since we are directly a crease //
				if ( Real(VsHeight) >= Me.Pos.z ) {
					Value = 128;
				}
			}
			
//			if ( Map[Index].Mesh.Vertex[idx].Normal == Vector3D(-1,0,0) ) {
//				VsHeight = Left.Height+1;
//			}
//			else if ( Map[Index].Mesh.Vertex[idx].Normal == Vector3D(+1,0,0) ) {
//				VsHeight = Right.Height+1;
//			}
//			else if ( Map[Index].Mesh.Vertex[idx].Normal == Vector3D(0,+1,0) ) {
//				VsHeight = Top.Height+1;
//			}
//			else if ( Map[Index].Mesh.Vertex[idx].Normal == Vector3D(0,-1,0) ) {
//				VsHeight = Bottom.Height+1;
//			}
//			else if ( Map[Index].Mesh.Vertex[idx].Normal == Vector3D(0,0,+1) ) {
//				VsHeight = -1024;	// SOME UNUSED TOO-LOW HIGHT //
//				
//				Vector3D ToCenter = -(Vector3D(0,0,0) - Map[Index].Mesh.Vertex[idx].Pos);
//				ToCenter.AxisNormalize();
//				if ( ToCenter.x > Real::Zero )
//					VsHeight = VsHeight < Right.Height ? Right.Height : VsHeight;
//				if ( ToCenter.x < Real::Zero )
//					VsHeight = VsHeight < Left.Height ? Left.Height : VsHeight;
//				if ( ToCenter.y > Real::Zero )
//					VsHeight = VsHeight < Top.Height ? Top.Height : VsHeight;
//				if ( ToCenter.y < Real::Zero )
//					VsHeight = VsHeight < Bottom.Height ? Bottom.Height : VsHeight;
//			}
//			
//			if ( Map[Index].Mesh.Vertex[idx].Pos.z < Real(VsHeight) ) {
//				Value = 128;
//			}
			
			Me.Color2 = GEL_RGBA(Value,Value,Value,Value);
		}
	}
	
	// Terrain change based on elevation //
	{
		int Value = Map[Index].Height * 64;

		if ( Value > 255 )
			Value = 255;
		if ( Value < 0 )
			Value = 0;

		for ( size_t idx = 0; idx < Map[Index].Mesh.Vertex.Size(); idx++ ) {
			Map[Index].Mesh.Vertex[idx].Color1 = GEL_RGBA(255,255,255,Value);
		}
	}

}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRoom::Step( ) {
	for ( size_t idx = 0; idx < Map.Size(); idx++ ) {
		int Dude = Map[idx].Active.FirstIterator();
		if ( Dude != -1 ) {
			Map[idx].Active[Dude]->Step( this );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cRoom::Draw( /* const Vector3D Pos */ ) {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRoom::Generate() {
	// Generate HeightMap //
	cGrid2D<int> HeightMap = generate_PlasmaFractal_HeightMap( Map.Width(), Map.Height() );
	
	// Fill in holes and hills that are alone //
	for ( size_t y = 0; y < Map.Height(); y++ ) {
		for ( size_t x = 0; x < Map.Width(); x++ ) {
			int Common = 1;
			if ( HeightMap.Wrap(x-1,y) == HeightMap(x,y) )
				Common++;
			if ( HeightMap.Wrap(x+1,y) == HeightMap(x,y) )
				Common++;
			if ( HeightMap.Wrap(x,y-1) == HeightMap(x,y) )
				Common++;
			if ( HeightMap.Wrap(x,y+1) == HeightMap(x,y) )
				Common++;

			if ( HeightMap.Wrap(x-1,y-1) == HeightMap(x,y) )
				Common++;
			if ( HeightMap.Wrap(x+1,y-1) == HeightMap(x,y) )
				Common++;
			if ( HeightMap.Wrap(x-1,y+1) == HeightMap(x,y) )
				Common++;
			if ( HeightMap.Wrap(x+1,y+1) == HeightMap(x,y) )
				Common++;
			
			if ( Common <= 2 ) {
				HeightMap(x,y) = HeightMap.Wrap(x-1,y);
			}
		}		
	}
	
	
	// Copy Heights //
	for ( size_t y = 0; y < Map.Height(); y++ ) {
		for ( size_t x = 0; x < Map.Width(); x++ ) {
			Map(x,y).Height = HeightMap(x,y);
		}		
	}

	// Update Meshes //
	for ( int idx = 0; idx < Map.Size(); idx++ ) {
		UpdateMesh( idx );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
