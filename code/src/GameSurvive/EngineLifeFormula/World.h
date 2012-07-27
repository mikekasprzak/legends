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
	
	// World //
	cGrid2D<cTile> 					Map;
	cGelArray<cActiveTemplate>		ActiveTemplate;
	cGelArray<cPassiveTemplate>		PassiveTemplate;

	// Camera //
	cMapView View;
//	int ViewX, ViewY;
//	int ViewSize; // Not seperate ViewWidth and ViewHeight, as all views will be square //
//	
//	Real TileSize;
//	Real TileHalfSize;
//	Real ViewHalfSize;
//	
//	int SelectedTile;
	
public:
	cWorld( const int Width, const int Height ) :
		Map( Width, Height, cTile() ),
		View()
//		ViewX( 0 ), ViewY( 0 ),
//		ViewSize( 7 ),
//		TileSize( 8 ) // Should equal RegionSize / ViewSize
	{
//		TileHalfSize = TileSize * Real::Half;
//		ViewHalfSize = Real(ViewSize) * Real::Half;		

		// Dummy Create //
		Map(2,1).Active.Get() = new cActive();
		
		PassiveTemplate.PushBack( cPassiveTemplate() );
		PassiveTemplate.Back().Load( "Content/Misc/TestPassive.json" );
		
		Log( "HEEEEB! %i", PassiveTemplate.Back().MaxCount );

		Map(3,1).Passive.Get() = new cPassive( &(PassiveTemplate.Back()) );
	}
	
public:
	void Step( const Vector3D& MouseRay ) {
		View.Step( MouseRay );
		
//		SelectedTile = -1;
//
//		Rect2D Playfield( 
//			-(TileSize * ViewHalfSize), 
//			-(TileSize * ViewHalfSize),
//			+(TileSize * Real(ViewSize)), 
//			+(TileSize * Real(ViewSize))
//			);
//
////		if ( Playfield == Mouse.Pos ) {
//		if ( Playfield == MouseRay.ToVector2D() ) {
//			int x = (Playfield.MapX( MouseRay.x ) * Real(ViewSize));
//			int y = (Playfield.MapY( -MouseRay.y ) * Real(ViewSize));
//			
//			SelectedTile = (y * ViewSize) + x;
//		}
//		else {
//			SelectedTile = -1;
//		}
//		
////		Mouse.Pos.x.ToFloat(), Mouse.Pos.y.ToFloat()
	}
	
	// Draw what the camera sees //
	void DrawView( /* const Vector3D Pos */ ) {		
		View.Draw( Map );		
//		for ( size_t y = 0; y < ViewSize; y++ ) {
//			for ( size_t x = 0; x < ViewSize; x++ ) {
//				int Index = Map.Index( x, y );
//
//				// HACK: Negative Y
//				// HACK: Funny Z to test depth			
//				Vector3D DrawPos( 
//						+(((Real(x) - ViewHalfSize) * TileSize) + TileHalfSize), 
//						-(((Real(y) - ViewHalfSize) * TileSize) + TileHalfSize), 
//						Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)//(Real(x) / Real(1)) * Real(y)
//						);
//
//				gelSetColor( GEL_RGBA(0,255,0,128) );
//				if ( x == (SelectedTile % ViewSize) )
//					if ( y == (SelectedTile / ViewSize) )
//						gelSetColor( GEL_RGBA(255,255,0,128) );					
//				
//				gelDrawSquareFill( 
//					DrawPos,
//					TileHalfSize 
//					);
//
//				gelSetColor( GEL_RGB_GREEN );
//				if ( x == (SelectedTile % ViewSize) )
//					if ( y == (SelectedTile / ViewSize) )
//						gelSetColor( GEL_RGB_RED );
//
//				gelDrawSquare( 
//					DrawPos,
//					TileHalfSize 
//					);
//				
//				if ( Map[Index].Active.Size() > 0 ) {
//					gelSetColor( GEL_RGB_YELLOW );
//					gelDrawCircleFill( 
//						DrawPos, 
//						TileHalfSize * Real::ThreeQuarter
//						);
//				}					
//			}
//		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
