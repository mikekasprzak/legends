// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>
#include <vector>

#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>
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

typedef cGrid2D<short> LayerData;
std::vector< cGrid2D<short> > MapLayer;

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

		for ( int idx = 0; idx < ArraySize; idx++ ) {
			cJSON* obj = cJSON_GetArrayItem( Layers, idx );
			
			MapLayer.push_back( LayerData( cJSON_GetObjectItem( obj, "width" )->valueint, cJSON_GetObjectItem( obj, "height" )->valueint ) );
//			MapLayer.back().Resize( cJSON_GetObjectItem( obj, "width" )->valueint, cJSON_GetObjectItem( obj, "height" )->valueint, 0 );
			
			cJSON* LayerData = cJSON_GetObjectItem( obj, "data" );
			int LayerArraySize = cJSON_GetArraySize( LayerData );
			for ( int idx = 0; idx < LayerArraySize; idx ++ ) {
				MapLayer.back()[ idx ] = cJSON_GetArrayItem( LayerData, idx )->valueint;
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
	px += gx;
	py += gy;
}
// - ------------------------------------------------------------------------------------------ - //
void GameDraw() __attribute__((used));
void GameDraw() {
	

//	gelBindImage( Tileset );
//	gelDrawImage( 0, 0 );
//	
//	gelDrawImageCrop( 0,0, 8,8, 160,120 );

	gelBindImage( Tileset );
	for ( int Layer = 0; Layer < MapLayer.size(); Layer++ ) {
		for ( int _y = 0; _y < MapLayer[Layer].Height(); _y++ ) {
			for ( int _x = 0; _x < MapLayer[Layer].Width(); _x++ ) {
				gelDrawTile( MapLayer[Layer](_x, _y), _x * 8, _y * 8 );
			}
		}
	}
		
	gelSetColor( 255,0,0,255 );
	gelDrawCircle( px, py, 10 );
	
}
// - ------------------------------------------------------------------------------------------ - //

