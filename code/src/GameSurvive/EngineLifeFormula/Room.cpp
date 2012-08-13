// - ------------------------------------------------------------------------------------------ - //
#include "Room.h"

#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
cRoom::cRoom( const int Width, const int Height ) :
	Map( Width, Height, cTile() )
{
	// Dummy Create //
	cEngine::LoadActiveTemplate( "Content/Misc/TestActive.json" );
	
	Log( "Active Inventory: %i", cEngine::ActiveTemplate.Back()->InventorySize );

	cEngine::View->Focus = new cActive( cEngine::ActiveTemplate.Back() );	// Create //
	AddActive( cEngine::View->Focus, Map.Index(1,1) );						// Add to Map //

	cEngine::LoadPassiveTemplate( "Content/Misc/TestPassive.json" );
	
	Log( "Passive Stack Max: %i", cEngine::PassiveTemplate.Back()->MaxCount );

	Map(1,1).Passive.Get() = new cPassive( cEngine::PassiveTemplate.Back() );
		
	
	Map(3,4).Height += 16;
	Map(4,4).Height += 16;
	Map(5,4).Height += 12;
	Map(5,3).Height += 8;
	Map(5,2).Height += 4;

	Map(7,7).Height += 16;

	Map(1,7).Height -= 4;
	Map(2,7).Height -= 4;
	Map(2,6).Height -= 4;
	Map(3,7).Height -= 4;
	Map(3,6).Height -= 4;
	Map(3,8).Height -= 4;
	Map(4,7).Height -= 16;

	for ( int idx = 0; idx < Map.Size(); idx++ ) {
		UpdateMesh( idx % Map.Width(), idx / Map.Width() );
	}
}
// - ------------------------------------------------------------------------------------------ - //
cRoom::~cRoom() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRoom::UpdateMesh( const int x, const int y ) {
	Map(x,y).UpdateMesh();// Map.Index(x-1,y), Map.Index(x+1,y), Map.Index(x,y-1), Map.Index(x,y+1) );
/*	
	int Height = Map(x,y).Height;
	Map(x,y).Mesh.Vertex[1].Normal = Map(x,y).Mesh.Vertex[0].Normal;
	Map(x,y).Mesh.Vertex[1].Normal += -Real(Map(x,y).Height - Map(x-1,y-0).Height).Min(0).Normal() * Vector3D(-1,-0,0);
	Map(x,y).Mesh.Vertex[1].Normal += -Real(Map(x,y).Height - Map(x-1,y-1).Height).Min(0).Normal() * Vector3D(-1,-1,0);
	Map(x,y).Mesh.Vertex[1].Normal += -Real(Map(x,y).Height - Map(x-0,y-1).Height).Min(0).Normal() * Vector3D(-0,-1,0);
	Map(x,y).Mesh.Vertex[1].Normal.Normalize();

	Map(x,y).Mesh.Vertex[2].Normal = Map(x,y).Mesh.Vertex[0].Normal;
	Map(x,y).Mesh.Vertex[2].Normal += -Real(Map(x,y).Height - Map(x+1,y-0).Height).Min(0).Normal() * Vector3D(+1,-0,0);
	Map(x,y).Mesh.Vertex[2].Normal += -Real(Map(x,y).Height - Map(x+1,y-1).Height).Min(0).Normal() * Vector3D(+1,-1,0);
	Map(x,y).Mesh.Vertex[2].Normal += -Real(Map(x,y).Height - Map(x+0,y-1).Height).Min(0).Normal() * Vector3D(+0,-1,0);
	Map(x,y).Mesh.Vertex[2].Normal.Normalize();
                            
	Map(x,y).Mesh.Vertex[3].Normal = Map(x,y).Mesh.Vertex[0].Normal;
	Map(x,y).Mesh.Vertex[3].Normal += -Real(Map(x,y).Height - Map(x+1,y+0).Height).Min(0).Normal() * Vector3D(+1,+0,0);
	Map(x,y).Mesh.Vertex[3].Normal += -Real(Map(x,y).Height - Map(x+1,y+1).Height).Min(0).Normal() * Vector3D(+1,+1,0);
	Map(x,y).Mesh.Vertex[3].Normal += -Real(Map(x,y).Height - Map(x+0,y+1).Height).Min(0).Normal() * Vector3D(+0,+1,0);
	Map(x,y).Mesh.Vertex[3].Normal.Normalize();

	Map(x,y).Mesh.Vertex[4].Normal = Map(x,y).Mesh.Vertex[0].Normal;
	Map(x,y).Mesh.Vertex[4].Normal += -Real(Map(x,y).Height - Map(x-1,y+0).Height).Min(0).Normal() * Vector3D(-1,+0,0);
	Map(x,y).Mesh.Vertex[4].Normal += -Real(Map(x,y).Height - Map(x-1,y+1).Height).Min(0).Normal() * Vector3D(-1,+1,0);
	Map(x,y).Mesh.Vertex[4].Normal += -Real(Map(x,y).Height - Map(x-0,y+1).Height).Min(0).Normal() * Vector3D(-0,+1,0);
	Map(x,y).Mesh.Vertex[4].Normal.Normalize();
*/

	Vector3D Default = Map(x,y).Mesh.Vertex[4].Normal;
//	Vector3D Default = Vector3D(0,0,0);
	int Height = Map(x,y).Height;

	Map(x,y).Mesh.Vertex[0].Normal = Default;
	Map(x,y).Mesh.Vertex[0].Normal += Real(Map(x-1,y-0).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-1,-0,0);
	Map(x,y).Mesh.Vertex[0].Normal += Real(Map(x-1,y-1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-0.5,-0.5,0);
	Map(x,y).Mesh.Vertex[0].Normal += Real(Map(x-0,y-1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-0,-1,0);
	Map(x,y).Mesh.Vertex[0].Normal.Normalize();//AxisNormalize().Normalize();

	Map(x,y).Mesh.Vertex[1].Normal = Default;
	Map(x,y).Mesh.Vertex[1].Normal += Real(Map(x-0,y-1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-0,-1,0);
	Map(x,y).Mesh.Vertex[1].Normal.Normalize();//AxisNormalize().Normalize();

	Map(x,y).Mesh.Vertex[2].Normal = Default;
	Map(x,y).Mesh.Vertex[2].Normal += Real(Map(x+1,y-0).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+1,-0,0);
	Map(x,y).Mesh.Vertex[2].Normal += Real(Map(x+1,y-1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+0.5,-0.5,0);
	Map(x,y).Mesh.Vertex[2].Normal += Real(Map(x+0,y-1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+0,-1,0);
	Map(x,y).Mesh.Vertex[2].Normal.Normalize();//AxisNormalize().Normalize();

	Map(x,y).Mesh.Vertex[3].Normal = Default;
	Map(x,y).Mesh.Vertex[3].Normal += Real(Map(x-1,y+0).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-1,+0,0);
	Map(x,y).Mesh.Vertex[3].Normal.Normalize();//AxisNormalize().Normalize();
	
	// No Middle //

	Map(x,y).Mesh.Vertex[5].Normal = Default;
	Map(x,y).Mesh.Vertex[5].Normal += Real(Map(x+1,y+0).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+1,+0,0);
	Map(x,y).Mesh.Vertex[5].Normal.Normalize();//AxisNormalize().Normalize();

	Map(x,y).Mesh.Vertex[6].Normal = Default;
	Map(x,y).Mesh.Vertex[6].Normal += Real(Map(x-1,y+0).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-1,+0,0);
	Map(x,y).Mesh.Vertex[6].Normal += Real(Map(x-1,y+1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-0.5,+0.5,0);
	Map(x,y).Mesh.Vertex[6].Normal += Real(Map(x-0,y+1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(-0,+1,0);
	Map(x,y).Mesh.Vertex[6].Normal.Normalize();//AxisNormalize().Normalize();

	Map(x,y).Mesh.Vertex[7].Normal = Default;
	Map(x,y).Mesh.Vertex[7].Normal += Real(Map(x+0,y+1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+0,+1,0);
	Map(x,y).Mesh.Vertex[7].Normal.Normalize();//AxisNormalize().Normalize();

	Map(x,y).Mesh.Vertex[8].Normal = Default;
	Map(x,y).Mesh.Vertex[8].Normal += Real(Map(x+1,y+0).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+1,+0,0);
	Map(x,y).Mesh.Vertex[8].Normal += Real(Map(x+1,y+1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+0.5,+0.5,0);
	Map(x,y).Mesh.Vertex[8].Normal += Real(Map(x+0,y+1).Height - Map(x,y).Height).Max(0).Normal() * Vector3D(+0,+1,0);
	Map(x,y).Mesh.Vertex[8].Normal.Normalize();//AxisNormalize().Normalize();
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
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
