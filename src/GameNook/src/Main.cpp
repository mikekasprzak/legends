// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>
#include <math.h>

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
void GameInit() __attribute__((used));
void GameExit() __attribute__((used));
void GameStep() __attribute__((used));
void GameDraw() __attribute__((used));

void GameInput( float x, float y, int bits ) __attribute__((used));
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int ScreenWidth;
int ScreenHeight;
int HalfScreenWidth;
int HalfScreenHeight;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const int Nook_Idle[] = { 0,0,1,1,3,3,0,0,1,1,2,2 };
const int Nook_Run[] = { 4,5,6,7,8,9 };
const int Nook_Anticipation[] = { 0,10,11 };
const int Nook_Jump[] = { 12 };
const int Nook_Fall[] = { 13 };
const int Nook_TouchGround[] = { 14 };
// - ------------------------------------------------------------------------------------------ - //

float gx;
float gy;
int Button;

void GameInput( float x, float y, int bits ) {
	gx = x;
	gy = y;
	Button = bits;
}

int TilesetId; // ID //
int PlayerId; // ID //

Vector2D CameraPos;

typedef cGrid2D<short> LayerType;
GelArray< LayerType* >* MapLayer;

// - ------------------------------------------------------------------------------------------ - //
void GameInit() {
	ScreenWidth = 320;
	ScreenHeight = 240;
	HalfScreenWidth = ScreenWidth >> 1;
	HalfScreenHeight = ScreenHeight >> 1;
	
	gelGraphicsInit( ScreenWidth, ScreenHeight );
	
	CameraPos.x = Real( HalfScreenWidth );
	CameraPos.y = Real( HalfScreenHeight );
	
	TilesetId = gelLoadTileset( "Content/Nook-Tileset.png", 8, 8 );
	PlayerId = gelLoadTileset( "Content/Nook-Player.png", 64, 64 );
	
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
void GameExit() {
	gelGraphicsExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GameStep() {
	if ( Button & 0x10 ) {
		CameraPos.x += gx * 4;
		CameraPos.y += gy * 4;
	}
	else {
		CameraPos.x += gx * 2;//0.5;
		CameraPos.y += gy * 2;//0.5;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void GameDraw() {
	int StartX, StartY;
	int OffsetX, OffsetY;
	float CameraOffsetX, CameraOffsetY;
	float CameraOffsetXCenter, CameraOffsetYCenter;

	int TilesWide = (ScreenWidth/8)+1;
	int TilesTall = (ScreenHeight/8)+1;

	gelBindImage( TilesetId );
	for ( size_t Layer = 0; Layer < (MapLayer->Size - 1); Layer++ ) {
		int MapWidth = MapLayer->Data[Layer]->Width();
		int MapHeight = MapLayer->Data[Layer]->Height();
		
		float CameraScalar = 1.0f;
		if ( Layer == 0 ) {
			CameraScalar = 0.5f;
		}
		
		CameraOffsetX = CameraPos.x.ToFloat();
		CameraOffsetY = CameraPos.y.ToFloat();
		CameraOffsetXCenter = (CameraOffsetX) - (float)(HalfScreenWidth);
		CameraOffsetYCenter = (CameraOffsetY) - (float)(HalfScreenHeight);

		CameraOffsetX *= CameraScalar;
		CameraOffsetY *= CameraScalar;
		CameraOffsetXCenter *= CameraScalar;
		CameraOffsetYCenter *= CameraScalar;
		
		if ( CameraOffsetXCenter < 0 )
			CameraOffsetXCenter = 0;
		if ( CameraOffsetYCenter < 0 )
			CameraOffsetYCenter = 0;
		
		OffsetX = ((int)floor(CameraOffsetXCenter) + HalfScreenWidth) % 8;			
		OffsetY = ((int)floor(CameraOffsetYCenter) + HalfScreenHeight) % 8;
		
		StartX = CameraOffsetXCenter / 8;
		if ( StartX < 0 ) {
			StartX = 0;
			OffsetX = 0;
		}
		if ( StartX >= (int)((float)(MapWidth - TilesWide) * CameraScalar) + 1 ) {
			StartX = (int)((float)(MapWidth - TilesWide) * CameraScalar) + 1;
			OffsetX = 0;
		}
	
		StartY = CameraOffsetYCenter / 8;
		if ( StartY < 0 ) {
			StartY = 0;
			OffsetY = 0;
		}
		if ( StartY >= (int)((float)(MapHeight - TilesTall) * CameraScalar) + 1 ) {
			StartY = (int)((float)(MapHeight - TilesTall) * CameraScalar) + 1;
			OffsetY = 0;
		}
	
		int EndX = StartX + TilesWide;
		if ( EndX > MapWidth )
			EndX = MapWidth;
		int EndY = StartY + TilesTall;
		if ( EndY > MapHeight )
			EndY = MapHeight;

//		char Blah[2048];
//		sprintf( Blah, "Pos: (%f %f) (%i, %i) (%i, %i)", CameraOffsetXCenter, CameraOffsetYCenter, StartX, StartY, OffsetX, OffsetY );
//		gelSetColor( 255,255,255,255 );
//		gelDrawText( 0, 120, Blah );

		for ( int _y = StartY; _y < EndY; _y++ ) {
			for ( int _x = StartX; _x < EndX; _x++ ) {
				int Tile = (*MapLayer->Data[Layer])(_x, _y);
				if ( Tile > 0 ) {
					gelDrawTile( 
						Tile-1, 
						((_x - StartX) * 8) - OffsetX, 
						((_y - StartY) * 8) - OffsetY
						);
				}
			}
		}
	}
	
	Vector2D Anchor;
	Anchor.x = 32;
	Anchor.y = 32;
	
	
//	int* CurrentAnimation = Nook_Idle;
//	int CurrentAnimation_Length = sizeof(Nook_Idle)/sizeof(int);
	const int* CurrentAnimation = Nook_Run;
	int CurrentAnimation_Length = sizeof(Nook_Run)/sizeof(int);
	
	static int FrameDelay = 0;
	static int Goo = 0;
	
	FrameDelay++;
	if ( FrameDelay == 3 ) {
		FrameDelay = 0;
		Goo++;
		if ( Goo == CurrentAnimation_Length )
		Goo = 0; 
	}
	
	gelBindImage( PlayerId );
	gelDrawTile(
		CurrentAnimation[Goo],
		floor(CameraPos.x.ToFloat() - (StartX<<3) - OffsetX) - Anchor.x.ToFloat(), 
		floor(CameraPos.y.ToFloat() - (StartY<<3) - OffsetY) - Anchor.y.ToFloat()
		);
		

//	gelSetColor( 255,0,0,255 );
//	gelDrawCircle( 
//		CameraPos.x.ToFloat() - (StartX<<3) - OffsetX, 
//		CameraPos.y.ToFloat() - (StartY<<3) - OffsetY, 
//		10 
//		);
}
// - ------------------------------------------------------------------------------------------ - //

