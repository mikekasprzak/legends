// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_WORLD_H__
#define __LIFEFORMULA_WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
// World -- Life ƒormula
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>

#include <Geometry/Rect.h>
#include <Input/Input_Mouse.h>

#include <Core/GelArray.h>
#include <Grid/Grid2D_Class.h>
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
	cGelArray<cActiveTemplate>		ActiveTemplate;
	cGelArray<cPassiveTemplate>		PassiveTemplate;

	// Camera //
	cMapView View;
	
public:
	cWorld( const int Width, const int Height ) :
		Map( Width, Height, cTile() ),
		View()
	{
		// Dummy Create //
		ActiveTemplate.PushBack( cActiveTemplate() );
		ActiveTemplate.Back().Load( "Content/Misc/TestActive.json" );
		
		Log( "Active Inventory: %i", ActiveTemplate.Back().InventorySize );

		Map(2,1).Active.Get() = new cActive( &(ActiveTemplate.Back()) );
		View.Focus = Map(2,1).Active[Map(2,1).Active.FirstIterator()];
		View.FocusIndex = Map.Index(2,1);
		
		PassiveTemplate.PushBack( cPassiveTemplate() );
		PassiveTemplate.Back().Load( "Content/Misc/TestPassive.json" );
		
		Log( "Passive Stack Max: %i", PassiveTemplate.Back().MaxCount );

		Map(3,1).Passive.Get() = new cPassive( &(PassiveTemplate.Back()) );
	}
	
public:
	void Step( const Vector3D& MouseRay ) {
		View.Step( Map, MouseRay );
	}
	
	void DrawView( /* const Vector3D Pos */ ) {		
		View.Draw( Map );
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
