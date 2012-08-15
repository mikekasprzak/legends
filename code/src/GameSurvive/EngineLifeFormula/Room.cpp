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

	// Ambient Occlusion based on height of neighbours //
	{
		Vector3D UpNormal(0,0,1);
		int DefaultHeight = -1024;	// SOME UNUSED TOO-LOW HEIGHT //
		
		for ( size_t idx = 0; idx < Map[Index].Mesh.Vertex.Size(); idx++ ) {
			cTileMeshVertex& Me = Map[Index].Mesh.Vertex[idx];
			int Value = 255;
			int VsHeight = DefaultHeight; 
			
			bool IsUpNormal = dot( UpNormal, Me.Normal ) > Real(0.01); // Including error //

			Vector3D ToCenter = (Vector3D(0,0,Me.Pos.z) - Me.Pos);
			ToCenter.AxisNormalize();
			
			bool IsCornerNormal = ToCenter.Manhattan() > Real(1.01); // Including error //
			IVector2D FromCenter( (int)-ToCenter.x, (int)-ToCenter.y );			
			
			if ( IsUpNormal ) {
				// Up Normals //
				if ( IsCornerNormal ) {
					// 3 Corners //
					int GreaterSides = 0;

					int NewHeight = Map.Wrap( x, y + FromCenter.y ).Height;
					if ( NewHeight > (int)Me.Pos.z )
						GreaterSides++;						
					if ( NewHeight >= VsHeight )
						VsHeight = NewHeight;
					
					NewHeight = Map.Wrap( x + FromCenter.x, y + FromCenter.y ).Height;
					if ( NewHeight > (int)Me.Pos.z )
						GreaterSides++;
					if ( NewHeight >= VsHeight )
						VsHeight = NewHeight;
					
					NewHeight = Map.Wrap( x + FromCenter.x, y ).Height;
					if ( NewHeight > (int)Me.Pos.z )
						GreaterSides++;
					if ( NewHeight >= VsHeight )
						VsHeight = NewHeight;
					
					if ( GreaterSides == 1 )
						VsHeight = DefaultHeight;
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
				int GreaterSides = 0;
				
				// Side Normals //
				if ( IsCornerNormal ) {
					// The Diagonal //
					int NewHeight = Map.Wrap( x + FromCenter.x, y + FromCenter.y ).Height;
					if ( NewHeight > (int)Me.Pos.z )
						GreaterSides++;
					if ( NewHeight > VsHeight )
						VsHeight = NewHeight;

					// The Normal Direction //
					NewHeight = Map.Wrap( x + (int)Me.Normal.x, y + (int)Me.Normal.y ).Height;
					if ( NewHeight > (int)Me.Pos.z )
						GreaterSides++;
					if ( NewHeight > VsHeight )
						VsHeight = NewHeight;
						
					// The Side Direction (Cross Product) //
//					Vector3D Cross = cross( UpNormal, Me.Normal );
//					Vector3D Cross = cross( Me.Normal, UpNormal );
//					Cross.AxisNormalize();	// NOTE: If not axis aligned angles, this will break //

//					Vector2D Cross = -Me.Normal.ToVector2D().Tangent();

					IVector2D Cross( FromCenter.x - (int)Me.Normal.x, FromCenter.y - (int)Me.Normal.y );

					// The cross product direction //
					NewHeight = Map.Wrap( x + (int)Cross.x, y + (int)Cross.y ).Height;
					if ( NewHeight > (int)Me.Pos.z ) {
						GreaterSides++;
					}
//					else if ( NewHeight == (int)Me.Pos.z ) {
//						if ( VsHeight > NewHeight )
//							GreaterSides++;
//					}
					// No Height Setting here, because that would cause side tiles outside //
					// the view to cast a shadow on the block, which is incorrect //
				}
				else { // Mid Normal //
					VsHeight = Map.Wrap( x + FromCenter.x, y + FromCenter.y ).Height;
					GreaterSides = 2;
				}
				
				// Inclusive, since we are directly a crease //
				if ( (VsHeight >= (int)Me.Pos.z) && (GreaterSides > 0) ) {
					Value = 128;
				}
			}

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
