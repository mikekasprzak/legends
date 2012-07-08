// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLDMAP_H__
#define __WORLDMAP_H__
// - ------------------------------------------------------------------------------------------ - //
#include "WorldTile.h"
#include "WorldObject.h"
#include "WorldPlayer.h"

#include <Grid/Grid2D_Class.h>

#include <Graphics/GraphicsDraw.h>
// - ------------------------------------------------------------------------------------------ - //
class cWorldMap {
public:
	cGrid2D<cWorldTile> Map;
	
	// Camera //
	int RoomX, RoomY;
	int RoomWidth, RoomHeight;

public:
	cWorldMap( const int Width, const int Height ) :
		Map( Width, Height, cWorldTile() ),
		RoomX( 0 ), RoomY( 0 ),
		RoomWidth( 7 ), RoomHeight( 7 )
	{	
	}
	
public:
	// Draw what the camera sees //
	void DrawRoom( /* const Vector3D Pos */ ) {
		gelDrawRect( Vector3D(-100,-100,0), Vector3D(+100,+100,0) );
		gelSetColor( GEL_RGB_YELLOW );
		gelDrawSquare( Vector3D(0,0,0), Real(40) );
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
#endif // __WORLDMAP_H__ //
// - ------------------------------------------------------------------------------------------ - //
