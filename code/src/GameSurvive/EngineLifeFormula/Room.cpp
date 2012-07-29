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
	AddActive( cEngine::View->Focus, Map.Index(2,1) );						// Add to Map //

	cEngine::LoadPassiveTemplate( "Content/Misc/TestPassive.json" );
	
	Log( "Passive Stack Max: %i", cEngine::PassiveTemplate.Back()->MaxCount );

	Map(3,1).Passive.Get() = new cPassive( cEngine::PassiveTemplate.Back() );
}
// - ------------------------------------------------------------------------------------------ - //
cRoom::~cRoom() {
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
