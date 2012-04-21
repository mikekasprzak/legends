// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>

#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>
#include <Core/GelArray.h>
#include <Core/GelDirectory.h>
#include <Grid/Grid2D_Class.h>

#include <cJSON.h>

#include "Gel2D/GelGraphics2D.h"
// - ------------------------------------------------------------------------------------------ - //

float gx;
float gy;

void GameInput( float x, float y, int bits ) __attribute__((used));
void GameInput( float x, float y, int bits ) {
	gx = x;
	gy = y;
//	Input_Stick
}

float px, py;
int Tileset;

typedef cGrid2D<short> LayerType;
GelArray< LayerType* >* MapLayer;

// - ------------------------------------------------------------------------------------------ - //
void GameInit() __attribute__((used));
void GameInit() {
	gelGraphicsInit( 320, 240 );
	
	px = 100;
	py = 100;
	
	Tileset = gelLoadTileset( "Content/Nook-Tileset.png", 8, 8 );
//	Tileset = gelLoadImage( "Content/Nook-Tileset.png" );
	
	LogLevel = 3;
	
//	init_GelDirectory();
//	GelDirectory* DirTree = new_GelDirectory( "Content" );
//	populate_GelDirectory( DirTree );

//	if ( exists_GelFile( "MapData.json" ) ) Log( "Exists 1" );
//	if ( exists_GelFile( "MapData.jsonoo" ) ) Log( "Exists 2" );
//	if ( exists_GelFile( "Content" ) ) Log( "Exists 3" );
//	if ( exists_GelFile( "David" ) ) Log( "Exists 4" );
	
	DataBlock* OriginalMap = new_read_nullterminate_DataBlock( "MapData.json" );

	Log( "Parsing file..." );
	
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
			
//			MapLayer.push_back( LayerData( cJSON_GetObjectItem( obj, "width" )->valueint, cJSON_GetObjectItem( obj, "height" )->valueint ) );
//			MapLayer.back().Resize( cJSON_GetObjectItem( obj, "width" )->valueint, cJSON_GetObjectItem( obj, "height" )->valueint, 0 );

			MapLayer->Data[idx] = new LayerType( cJSON_GetObjectItem( obj, "width" )->valueint, cJSON_GetObjectItem( obj, "height" )->valueint, 0 );
			
			cJSON* LayerData = cJSON_GetObjectItem( obj, "data" );
			int LayerArraySize = cJSON_GetArraySize( LayerData );
			for ( int idx2 = 0; idx2 < LayerArraySize; idx2++ ) {
				(*MapLayer->Data[ idx ])[ idx2 ] = cJSON_GetArrayItem( LayerData, idx2 )->valueint;
			}
			
//			Log( "%s -- %i, %i, %i", 
//				cJSON_GetObjectItem( obj, "file" )->valuestring, 
//				cJSON_GetObjectItem( obj, "x" )->valueint, 
//				cJSON_GetObjectItem( obj, "y" )->valueint,
//				cJSON_GetObjectItem( obj, "z" )->valueint 
//				);
		}
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
	px += gx * 4;
	py += gy * 4;
}
// - ------------------------------------------------------------------------------------------ - //
void GameDraw() __attribute__((used));
void GameDraw() {
	

//	gelBindImage( Tileset );
//	gelDrawImage( 0, 0 );
//	
//	gelDrawImageCrop( 0,0, 8,8, 160,120 );

	gelBindImage( Tileset );
	for ( size_t Layer = 0; Layer < MapLayer->Size-1; Layer++ ) {
//		for ( int _y = 0; _y < MapLayer->Data[Layer]->Height(); _y++ ) {
//			for ( int _x = 0; _x < MapLayer->Data[Layer]->Width(); _x++ ) {
		for ( int _y = 0; _y < (320/8)+1; _y++ ) {
			for ( int _x = 0; _x < (240/8)+1; _x++ ) {
				int Tile = (*MapLayer->Data[Layer])(_x, _y);
				if ( Tile > 0 ) {
					gelDrawTile( Tile-1, _x * 8, _y * 8 );
				}
			}
		}
	}
		
	gelSetColor( 255,0,0,255 );
	gelDrawCircle( px, py, 10 );
	
}
// - ------------------------------------------------------------------------------------------ - //

