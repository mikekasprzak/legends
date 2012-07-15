// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLD_H__
#define __WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
#include "WorldTile.h"
#include "WorldObject.h"
#include "WorldPlayer.h"
#include "WorldAnimal.h"

#include <Grid/Grid2D_Class.h>

#include <Graphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	// -- The World -- //
	
	// Chronotype //
	// - Diurnal      (Awake Day, Sleep Night)
	// - Nocturnal    (Awake Night, Sleep Day)
	// - Crepuscular  (Awake Twilight (dawn/dusk))
	//   - Matutinal  (Awake Dawn)
	//   - Vespertine (Awake Dusk)
	//   - Bimodal    (Awake both Twilights)
	// - Cathemeral   (Awake semi-randomly/adapting to others)

public:
	// -- The Map -- //
	cGrid2D<cWorldTile> Map;
	
	// Camera //
	int RoomX, RoomY;
	int RoomSize; // Not seperate RoomWidth and RoomHeight, as all rooms will be square //

public:
	cWorld( const int Width, const int Height ) :
		Map( Width, Height, cWorldTile() ),
		RoomX( 0 ), RoomY( 0 ),
		RoomSize( 7 )
	{	
	}
	
public:
	// Draw what the camera sees //
	void DrawRoom( /* const Vector3D Pos */ ) {
		Real TileSize(8); // Should equal RegionSize / RoomSize
		Real TileHalfSize = TileSize * Real::Half;
			
		Real RoomHalfSize = Real(RoomSize) * Real::Half;
		
		gelSetColor( GEL_RGB_YELLOW );
		
		for ( size_t y = 0; y < RoomSize; y++ ) {
			for ( size_t x = 0; x < RoomSize; x++ ) {
				gelDrawSquare( 
					Vector3D( 
						((Real(x) - RoomHalfSize) * TileSize) + TileHalfSize, 
						((Real(y) - RoomHalfSize) * TileSize) + TileHalfSize, 
						(Real(x) / Real(1)) * Real(y)
						), 
					TileHalfSize 
					);
			}
		}
	}
	
	// - ------ - //
	
	// Draw the entire map as a top-down 2D view //
	void DrawMap2D( const Vector3D Pos ) {
		
	}

	// Draw the entire map as a top-down angled 3D view //
	void DrawMap3D( const Vector3D Pos ) {
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
