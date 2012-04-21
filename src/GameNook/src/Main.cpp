// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>

#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>
#include <Core/GelArray.h>
#include <Core/GelDirectory.h>
#include <Grid/Grid2D_Class.h>

#include <Math/Vector.h>

#include <cJSON.h>

#include "Gel2D/GelGraphics2D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int ScreenWidth;
int ScreenHeight;
// - ------------------------------------------------------------------------------------------ - //

float gx;
float gy;

void GameInput( float x, float y, int bits ) __attribute__((used));
void GameInput( float x, float y, int bits ) {
	gx = x;
	gy = y;
//	Input_Stick
}

int Tileset; // ID //

Vector2D CameraPos;

typedef cGrid2D<short> LayerType;
GelArray< LayerType* >* MapLayer;

// - ------------------------------------------------------------------------------------------ - //
void GameInit() __attribute__((used));
void GameInit() {
	ScreenWidth = 320;
	ScreenHeight = 240;
	gelGraphicsInit( ScreenWidth, ScreenHeight );
	
	CameraPos.x = Real( ScreenWidth >> 1 );
	CameraPos.y = Real( ScreenHeight >> 1 );
	
	Tileset = gelLoadTileset( "Content/Nook-Tileset.png", 8, 8 );
//	Tileset = gelLoadImage( "Content/Nook-Tileset.png" );
	
	LogLevel = 3;
	
	DataBlock* OriginalMap = new_read_nullterminate_DataBlock( "MapData.json" );

	Log( "Parsing JSON Map File..." );
	
	cJSON* root = cJSON_Parse( OriginalMap->Data );
	
	if ( root == 0 ) {
		Log( "Error parsing data!" );
	}
	else {
		Log( "Parsed!" );
		Log( "Extracting Data..." );

		cJSON* Layers = cJSON_GetObjectItem( root, "layers" );
		int ArraySize = cJSON_GetArraySize( Layers );
		
		MapLayer = new_GelArray<LayerType*>( ArraySize );

		for ( int idx = 0; idx < ArraySize; idx++ ) {
			cJSON* obj = cJSON_GetArrayItem( Layers, idx );
			
			MapLayer->Data[idx] = new LayerType( cJSON_GetObjectItem( obj, "width" )->valueint, cJSON_GetObjectItem( obj, "height" )->valueint, 0 );
			
			cJSON* LayerData = cJSON_GetObjectItem( obj, "data" );
			int LayerArraySize = cJSON_GetArraySize( LayerData );
			for ( int idx2 = 0; idx2 < LayerArraySize; idx2++ ) {
				(*MapLayer->Data[ idx ])[ idx2 ] = cJSON_GetArrayItem( LayerData, idx2 )->valueint;
			}
		}
		Log( "Done Extracting Data." );
	}
	
	cJSON_Delete( root );
	
	delete_DataBlock( OriginalMap );
}
// - ------------------------------------------------------------------------------------------ - //
void GameExit() __attribute__((used));
void GameExit() {
	gelGraphicsExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GameStep() __attribute__((used));
void GameStep() {
	CameraPos.x += gx * 2;
	CameraPos.y += gy * 2;
}
// - ------------------------------------------------------------------------------------------ - //
void GameDraw() __attribute__((used));
void GameDraw() {
	
	int MapWidth = MapLayer->Data[0]->Width();
	int MapHeight = MapLayer->Data[0]->Height();
	int TilesWide = (ScreenWidth/8)+1;
	int TilesTall = (ScreenHeight/8)+1;
	
	int CameraOffsetX = CameraPos.x.ToFloat() - (ScreenWidth>>1);
	int CameraOffsetY = CameraPos.y.ToFloat() - (ScreenHeight>>1);
	int OffsetX = (int)CameraPos.x.ToFloat() & 7;
	int OffsetY = (int)CameraPos.y.ToFloat() & 7;
	
	int StartX = CameraOffsetX >> 3;
	if ( StartX < 0 ) {
		StartX = 0;
		OffsetX = 0;
	}
	if ( StartX > MapWidth - TilesWide + 1 ) {
		StartX = MapWidth - TilesWide + 1;
		OffsetX = 0;
	}

	int StartY = CameraOffsetY >> 3;
	if ( StartY < 0 ) {
		StartY = 0;
		OffsetY = 0;
	}
	if ( StartY > MapHeight - TilesTall + 1 ) {
		StartY = MapHeight - TilesTall + 1;
		OffsetY = 0;
	}

	int EndX = StartX + TilesWide;
	if ( EndX > MapWidth )
		EndX = MapWidth;
	int EndY = StartY + TilesTall;
	if ( EndY > MapHeight )
		EndY = MapHeight;
	

	gelBindImage( Tileset );
	for ( size_t Layer = 0; Layer < (MapLayer->Size - 1); Layer++ ) {
		for ( int _y = StartY; _y < EndY; _y++ ) {
			for ( int _x = StartX; _x < EndX; _x++ ) {
				int Tile = (*MapLayer->Data[Layer])(_x, _y);
				if ( Tile > 0 ) {
					gelDrawTile( 
						Tile-1, 
						((_x-StartX) * 8) - OffsetX, 
						((_y-StartY) * 8) - OffsetY
						);
				}
			}
		}
	}
		
	gelSetColor( 255,0,0,255 );
	gelDrawCircle( CameraPos.x.ToFloat() - (StartX<<3) - OffsetX, CameraPos.y.ToFloat() - (StartY<<3) - OffsetY, 10 );
}
// - ------------------------------------------------------------------------------------------ - //

