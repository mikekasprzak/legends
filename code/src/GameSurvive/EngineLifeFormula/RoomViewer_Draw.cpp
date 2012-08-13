// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GraphicsDraw.h>

#include "RoomViewer.h"
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
extern bool ShowDebug;
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
void cRoomViewer::Draw( const GelCamera& Camera ) {
	const cGrid2D<cTile>& Map = Room->Map;

	Matrix4x4 LocalView;

	gelEnableDepthWriting();
	gelEnableDepthTest();

	cEngine::TileMeshRenderer->Bind();

	for ( size_t y = 0; y < Size; y++ ) {
		for ( size_t x = 0; x < Size; x++ ) {
			int Index = Map.Index( x + Pos.x, y + Pos.y );
			
			LocalView = Matrix4x4::TranslationMatrix( 
				Vector3D(
					+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
					+(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
					-Real(cTile::DEFAULT_TILE_HEIGHT)
					) 
				);
			LocalView *= Camera.ProjectionView;
			
			Vector2D UVPos( Map.IndexToX(Index), Map.IndexToY(Index) );
			UVPos *= Real(4);
			
			cEngine::TileMeshRenderer->DrawMesh( Map[Index].ShaftMesh, UVPos, LocalView );
			cEngine::TileMeshRenderer->DrawMesh( Map[Index].TopMesh, UVPos, LocalView );
		}
	}

	gelDisableDepthWriting();
		
	// Outline //
	gelDrawModeFlat();
	gelLoadMatrix( Camera.CoplanarProjectionView );

	if ( ShowDebug ) {
		for ( size_t y = 0; y < Size; y++ ) {
			for ( size_t x = 0; x < Size; x++ ) {
				int Index = Map.Index( x + Pos.x, y + Pos.y );
	
				// HACK: Funny Z to test depth			
				Vector3D DrawPos( 
						+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
						+(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
						Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)
						);
	
				gelSetColor( GEL_RGBA(0,255,0,192) );
	
				gelDrawSquare( 
					DrawPos,
					TileHalfSize 
					);
	
				// Surface Normal //
				gelSetColor( GEL_RGB_YELLOW );
				gelDrawLine( 
					DrawPos,
					DrawPos + Map[Index].Normal
					);
			}
		}
	}
	
	// Cursor //
	if ( SelectedTile != -1 ) {
		int x = (SelectedTile % Size);
		int y = (SelectedTile / Size);
		int Index = Map.Index( x + Pos.x, y + Pos.y );
		
		// HACK: Funny Z to test depth
		Vector3D DrawPos( 
				+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
				+(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
				Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)
				);
				
		gelSetColor( GEL_RGB_RED );	
		gelDrawSquare( 
			DrawPos,
			TileHalfSize 
			);
	}
			
	for ( size_t y = 0; y < Size; y++ ) {
		for ( size_t x = 0; x < Size; x++ ) {
			int Index = Map.Index( x + Pos.x, y + Pos.y );

			// HACK: Funny Z to test depth			
			Vector3D DrawPos( 
					+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
					+(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
					Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)
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
	
	gelDisableDepthTest();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
