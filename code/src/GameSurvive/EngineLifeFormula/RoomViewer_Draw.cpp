// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GraphicsDraw.h>

#include "RoomViewer.h"
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
void cRoomViewer::Draw( const Matrix4x4& ViewMatrix ) {
//	Matrix4x4 ViewMatrix = Matrix4x4::ScalarMatrix(2);
//	ViewMatrix *= _ViewMatrix;
	
	const cGrid2D<cTile>& Map = Room->Map;

	Matrix4x4 LocalView;

	gelEnableDepthWriting();
	gelEnableDepthTest();
	cEngine::TileMeshRenderer->Bind();

	for ( size_t y = 0; y < Size; y++ ) {
		for ( size_t x = 0; x < Size; x++ ) {
			int Index = Map.Index( x, y );
			
			LocalView = Matrix4x4::TranslationMatrix( 
				Vector3D(
					+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
					+(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
					-Real(cTile::DEFAULT_TILE_HEIGHT)// * TileHalfSize//Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)
					) 
				);
//			LocalView *= Matrix4x4::ScalarMatrix( TileHalfSize );
			LocalView *= ViewMatrix;
			
			cEngine::TileMeshRenderer->DrawMesh( Map[Index].Mesh, LocalView );
		}
	}
	
	// Outline //
	gelDrawModeFlat();
	gelLoadMatrix( ViewMatrix );

	for ( size_t y = 0; y < Size; y++ ) {
		for ( size_t x = 0; x < Size; x++ ) {
			int Index = Map.Index( x, y );

			// HACK: Funny Z to test depth			
			Vector3D DrawPos( 
					+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
					+(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
					Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)// * TileHalfSize//Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT) * TileHalfSize//(Real(x) / Real(1)) * Real(y)
					);

//			gelSetColor( GEL_RGBA(0,255,0,128) );
//			if ( x == (SelectedTile % Size) )
//				if ( y == (SelectedTile / Size) )
//					gelSetColor( GEL_RGBA(255,255,0,128) );					
//			
//			gelDrawSquareFill( 
//				DrawPos,
//				TileHalfSize 
//				);

//			gelSetColor( GEL_RGB_GREEN );
//			if ( x == (SelectedTile % Size) )
//				if ( y == (SelectedTile / Size) )
//					gelSetColor( GEL_RGB_RED );
//
//			gelDrawSquare( 
//				DrawPos,
//				TileHalfSize 
//				);
		}
	}

	gelDisableDepthTest();
	gelDisableDepthWriting();
			
	for ( size_t y = 0; y < Size; y++ ) {
		for ( size_t x = 0; x < Size; x++ ) {
			int Index = Map.Index( x, y );

			// HACK: Funny Z to test depth			
			Vector3D DrawPos( 
					+(((Real(x) - HalfSize) * TileSize) + TileHalfSize), 
					+(((Real(y) - HalfSize) * TileSize) + TileHalfSize), 
					Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT)// * TileHalfSize//Real(Map[Index].Height - cTile::DEFAULT_TILE_HEIGHT) * TileHalfSize//(Real(x) / Real(1)) * Real(y)
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
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
