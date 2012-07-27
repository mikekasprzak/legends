// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_MAPVIEW_H__
#define __LIFEFORMULA_MAPVIEW_H__
// - ------------------------------------------------------------------------------------------ - //
// Map View -- 
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
#include <Math/IVector.h>
#include <Math/Real.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cMapView {
public:
	IVector2D	Pos;
	Integer		Size; 		// Not seperate Width and Height, as all views will be square //
	Real 		HalfSize;	// Real because the sizes tend to be odd //

	Real TileSize;
	Real TileHalfSize;
	
	int SelectedTile;
	
	

public:
	cMapView() :
		Pos( 0, 0 ),
		Size( 9 )
	{
		HalfSize = Real(Size) * Real::Half;

		TileSize = Real(6); // Should equal RegionSize / Size
		TileHalfSize = TileSize * Real::Half;
		
	}
	
	void Step( const Vector3D& MouseRay ) {
		SelectedTile = -1;

		Rect2D Playfield( 
			-(TileSize * HalfSize), 
			-(TileSize * HalfSize),
			+(TileSize * Real(Size)), 
			+(TileSize * Real(Size))
			);

//		if ( Playfield == Mouse.Pos ) {
		if ( Playfield == MouseRay.ToVector2D() ) {
			int x = (Playfield.MapX( MouseRay.x ) * Real(Size));
			int y = (Playfield.MapY( -MouseRay.y ) * Real(Size));
			
			SelectedTile = (y * Size) + x;
		}
		else {
			SelectedTile = -1;
		}
	}
	
	// Draw what the camera sees //
	void Draw( const cGrid2D<cTile>& Map ) {
		for ( size_t y = 0; y < Size; y++ ) {
			for ( size_t x = 0; x < Size; x++ ) {
				int Index = Map.Index( x, y );

				// HACK: Negative Y
				// HACK: Funny Z to test depth			
				Vector3D DrawPos( 
						+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
						-(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
						Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)//(Real(x) / Real(1)) * Real(y)
						);

				gelSetColor( GEL_RGBA(0,255,0,128) );
				if ( x == (SelectedTile % Size) )
					if ( y == (SelectedTile / Size) )
						gelSetColor( GEL_RGBA(255,255,0,128) );					
				
				gelDrawSquareFill( 
					DrawPos,
					TileHalfSize 
					);

				gelSetColor( GEL_RGB_GREEN );
				if ( x == (SelectedTile % Size) )
					if ( y == (SelectedTile / Size) )
						gelSetColor( GEL_RGB_RED );

				gelDrawSquare( 
					DrawPos,
					TileHalfSize 
					);
				
				if ( Map[Index].Active.Size() > 0 ) {
					gelSetColor( GEL_RGB_YELLOW );
					gelDrawCircleFill( 
						DrawPos, 
						TileHalfSize * Real::ThreeQuarter
						);
				}					
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_MAPVIEW_H__ //
// - ------------------------------------------------------------------------------------------ - //