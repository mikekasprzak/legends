// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFESYSTEM_WORLD_H__
#define __LIFESYSTEM_WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
// World -- 
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Graphics/GraphicsDraw.h>

#include <Grid/Grid2D_Class.h>
#include "Tile.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeSystem {
// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	// Simulation //
	int Iteration;
	
	// World //
	cGrid2D<cTile> Map;

	// Camera //
	int ViewX, ViewY;
	int ViewSize; // Not seperate ViewWidth and ViewHeight, as all views will be square //
	
public:
	cWorld( const int Width, const int Height ) :
		Map( Width, Height, cTile() ),
		ViewX( 0 ), ViewY( 0 ),
		ViewSize( 7 )
	{
		Map(2,1).Active.Get() = new cActive();
		
		cPassiveTemplate* Dummy = new cPassiveTemplate();
		Dummy->Load( "Content/Misc/TestPassive.json" );
		
		Log( "HEEEEB! %i", Dummy->MaxCount );

		Map(3,1).Passive.Get() = new cPassive( Dummy );
	}
	
public:
	// Draw what the camera sees //
	void DrawView( /* const Vector3D Pos */ ) {
		Real TileSize(8); // Should equal RegionSize / ViewSize
		Real TileHalfSize = TileSize * Real::Half;
			
		Real ViewHalfSize = Real(ViewSize) * Real::Half;
		
		gelSetColor( GEL_RGB_GREEN );
		
		for ( size_t y = 0; y < ViewSize; y++ ) {
			for ( size_t x = 0; x < ViewSize; x++ ) {
				int Index = Map.Index( x, y );

				// HACK: Negative Y
				// HACK: Funny Z				
				Vector3D DrawPos( 
						+(((Real(x) - ViewHalfSize) * TileSize) + TileHalfSize), 
						-(((Real(y) - ViewHalfSize) * TileSize) + TileHalfSize), 
						(Real(x) / Real(1)) * Real(y)
						);
				
				gelDrawSquare( 
					DrawPos,
					TileHalfSize 
					);
				
				if ( Map[Index].Active.Size() > 0 ) {
					gelDrawCircle( 
						DrawPos, 
						TileHalfSize
						);
				}					
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeSystem //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFESYSTEM_WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
