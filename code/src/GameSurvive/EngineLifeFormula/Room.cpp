// - ------------------------------------------------------------------------------------------ - //
#include "Room.h"

#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
cRoom::cRoom( const int Width, const int Height ) :
	Map( Width, Height, cTile() ),
	View()
{
	// Dummy Create //
	cEngine::LoadActiveTemplate( "Content/Misc/TestActive.json" );
	
	Log( "Active Inventory: %i", cEngine::ActiveTemplate.Back()->InventorySize );

	View.Focus = new cActive( cEngine::ActiveTemplate.Back() );	// Create //
	AddActive( View.Focus, Map.Index(2,1) );					// Add to Map //

	cEngine::LoadPassiveTemplate( "Content/Misc/TestPassive.json" );
	
	Log( "Passive Stack Max: %i", cEngine::PassiveTemplate.Back()->MaxCount );

	Map(3,1).Passive.Get() = new cPassive( cEngine::PassiveTemplate.Back() );
}
// - ------------------------------------------------------------------------------------------ - //
cRoom::~cRoom() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cRoom::Step( const Vector3D& MouseRay ) {
	for ( size_t idx = 0; idx < Map.Size(); idx++ ) {
		int Dude = Map[idx].Active.FirstIterator();
		if ( Dude != -1 ) {
			Map[idx].Active[Dude]->Step( this );
		}
	}
	
	View.Step( this, MouseRay );
}
// - ------------------------------------------------------------------------------------------ - //
void cRoom::DrawView( /* const Vector3D Pos */ ) {
	View.Draw( this );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
