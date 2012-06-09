// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <Debug/GelDebug.h>
#include <Core/DataBlock.h>
#include <Core/GelArray.h>

#include <Grid/Grid2D_Class.h>

#include <Math/Vector.h>
#include <Geometry/Rect.h>

#include <cJSON.h>

#include "Gel2D/GelGraphics2D.h"
// - ------------------------------------------------------------------------------------------ - //
// Game Res             -- 240x160 (GBA 3:2)
// 3DS      - 400x240
// PS MINIS - 480x272
// iPhone Original      -- 480x320 (x2)
// PS Vita  - 960x544   -- 720x480 (x3)
// iPhone Retina        -- 960x640 (x4)
// iPad	1+2 - 1024x768
// HD 720p  - 1280x720  
// PC HD    - 1366x768 
// PC 16:10 - 1280x800  -- 1200x800 (x5)
// HD 1080p - 1920x1080 -- 1440x960 (x6)
// PC HD+   - 1920x1200 -- 1680x1120 (x7)
// iPad Ret - 2048x1536 -- 1920x1280 (x8)
//                      -- 2160x1440 (x9)
// PC 2k+   - 2560x1600 -- 2400x1600 (x10)
// - ------------------------------------------------------------------------------------------ - //
// Instead, what should be done is aspect ratios should be tested //
// 3:2   -- 240x160 -- (x2) 480x320, (x3) 720x480, (x4) 960x640,  (x5) 1200x800, (x6) 1440x960, (x7) 1680x1120
// ~4:3  -- 212x160 -- (x2) 424x320, (x3) 636x480, (x4) 848x640,  (x5) 1060x800, (x6) 1272x960, (x7) 1484x1120
// ~16:9 -- 284x160 -- (x2) 568x320, (x3) 852x480, (x4) 1136x640, (x5) 1420x800, (x6) 1704x960, (x7) 1988x1120
// 16:10 -- 256x160 -- (x2) 512x320, (x3) 768x480, (x4) 1024x640, (x5) 1280x800, (x6) 1536x960, (x7) 1792x1120
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GameInit() __attribute__((used));
void GameExit() __attribute__((used));
void GameStep() __attribute__((used));
void GameDraw() __attribute__((used));
void GameDrawPaused() __attribute__((used));

void GameInput( float x, float y, int Current, int Last ) __attribute__((used));
// - ------------------------------------------------------------------------------------------ - //
extern "C" {
int sndPlay( const char* SoundName );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int ScreenWidth;
int ScreenHeight;
int HalfScreenWidth;
int HalfScreenHeight;
// - ------------------------------------------------------------------------------------------ - //

const int STATE_TITLE =	1;
const int STATE_PLAY =	2;
const int STATE_WIN =	3;

int GameState;

int TilesetId;
int PlayerId;
int EnemyId;
//int HudId;
//int TitleId;
//int WinId;

Vector2D CameraPos;

typedef cGrid2D<short> LayerType;
GelArray< LayerType* >* MapLayer;

//int GlobalTotalKeys;

// - ------------------------------------------------------------------------------------------ - //
// Number of Frames, followed by frame numbers //
// - ------------------------------------------------------------------------------------------ - //
const int Player_Idle[] = { 64, /**/ 0,0,0,0,0,0,2,2,2,2,0,0,1,1,1,1,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,1,1,1,1,0,0,2,2,2,2,0,0,0,0,0,0,3,3,0,0, };
const int Player_Maul[] = { 3, /**/ 4,4,4 };
const int Player_Hop[] = { 3, /**/ 8,8,1 };
// - ------------------------------------------------------------------------------------------ - //
const int Enemy_Idle[] = { 1, /**/ 0 };
const int Enemy_Shoot[] = { 4, /**/ 1,1,1,1 };
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const int TILE_COLLISION = 	1;
const int TILE_EXIT =	 	2;

const int TILE_FOOD =	 	(8*7)+1;
const int TILE_FOOD_END =	(8*7)+8;

const int TILE_FISH =	 	(8*7)+1;
const int TILE_APPLE =	 	(8*7)+2;


const int TILE_ENEMY =		(8*7)+7;
const int TILE_START =		(8*7)+8;
// - ------------------------------------------------------------------------------------------ - //

float gx;
float gy;

int _Input_KeyCurrent;
int _Input_KeyLast;

const int KEY_UP = 			0x1;
const int KEY_DOWN = 		0x2;
const int KEY_LEFT = 		0x4;
const int KEY_RIGHT = 		0x8;
const int KEY_ACTION = 		0x10;
const int KEY_ACTION2 = 	0x20;
const int KEY_ACTION3 = 	0x40;
const int KEY_ACTION4 = 	0x80;
const int KEY_MENU =		0x800;

// - -------------------------------------------------------------------------------------------------------------- - //
// Key pressed this frame //
inline const int Input_Key( const int Mask = 0xFFFFFFFF ) {
	return _Input_KeyCurrent & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Key pressed last frame //
inline const int Input_KeyLast( const int Mask = 0xFFFFFFFF ) {
	return _Input_KeyLast & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Key was just pressed this frame //
inline const int Input_KeyPressed( const int Mask  = 0xFFFFFFFF ) {
	return (_Input_KeyCurrent ^ _Input_KeyLast) & _Input_KeyCurrent & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Key was just released this frame //
inline const int Input_KeyReleased( const int Mask  = 0xFFFFFFFF ) {
	return (_Input_KeyCurrent ^ _Input_KeyLast) & _Input_KeyLast & Mask;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
void GameInput( float x, float y, int Current, int Last ) {
	gx = x;
	gy = y;
	_Input_KeyCurrent = Current;
	_Input_KeyLast = Last;
}
// - -------------------------------------------------------------------------------------------------------------- - //

int CountEnemies( const int Layer ) {
	int MapWidth = MapLayer->Data[Layer]->Width();
	int MapHeight = MapLayer->Data[Layer]->Height();
	
	int Count = 0;

	for ( int _y = 0; _y < MapHeight; _y++ ) {
		for ( int _x = 0; _x < MapWidth; _x++ ) {
			int Tile = (*MapLayer->Data[Layer])(_x, _y);
			
			if ( Tile == TILE_ENEMY )
				Count++;
		}
	}
	
	return Count;
}

// - -------------------------------------------------------------------------------------------------------------- - //
int GameMoves = 0;
int GameMoveCountdown = 60*2;
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
class cEnemy { 
public:
	struct cPos {
		int x, y;
		
		cPos() : x(0), y(0) { }
		cPos(int _x, int _y) : x(_x), y(_y) { }
	} Pos;
	
	const int* CurrentAnimation;
	const int* IntermediateAnimation;
	int CurrentFrame;
	int FrameDelay;
	
	Vector2D Anchor;
		
	bool FacingLeft;

public:
	cEnemy( int _x, int _y ) :
		Pos( _x, _y )
	{
		CurrentAnimation = Enemy_Idle;
		IntermediateAnimation = 0;
		CurrentFrame = 0;
		FrameDelay = 0;
		
		Anchor.x = 8;
		Anchor.y = 8;
		
		FacingLeft = false;

		SetAnimation( Enemy_Idle );
	}
	
	inline void SetIntermediateAnimation( const int* AnimationName ) {
		if ( IntermediateAnimation != AnimationName ) {
			IntermediateAnimation = AnimationName;
			CurrentFrame = 0;
			FrameDelay = 0;
		}	
	}
	
	inline void SetAnimation( const int* AnimationName ) {
		if ( CurrentAnimation != AnimationName ) {
			CurrentAnimation = AnimationName;
			if ( IntermediateAnimation == 0 ) {
				CurrentFrame = 0;
				FrameDelay = 0;
			}
		}
	}
	
	inline void ForceIntermediateAnimation( const int* AnimationName ) {
		IntermediateAnimation = AnimationName;
		CurrentFrame = 0;
		FrameDelay = 0;
	}
	
	inline void ForceAnimation( const int* AnimationName ) {
		CurrentAnimation = AnimationName;
		if ( IntermediateAnimation == 0 ) {
			CurrentFrame = 0;
			FrameDelay = 0;
		}
	}
	
	void Step() {
		// Set Facing Direction //
		FacingLeft = ((GameMoves / 4) & 1) == 0;
		
		// Animation System //
		FrameDelay++;
		if ( FrameDelay >= 6 ) {
			FrameDelay = 0;
			CurrentFrame++;
			if ( IntermediateAnimation ) {
				if ( CurrentFrame == IntermediateAnimation[0] ) {
					CurrentFrame = 0;
					IntermediateAnimation = 0;
				}
			}
			else {
				if ( CurrentFrame == CurrentAnimation[0] )
					CurrentFrame = 0;
			}
		}
	}
	
	void Draw( const Vector2D& Camera ) {
		int TileSize = 16;
		
		gelBindImage( EnemyId );
				
		if ( FacingLeft ) {
			gelDrawTileFlipX(
				IntermediateAnimation ? IntermediateAnimation[ CurrentFrame + 1 ] : CurrentAnimation[ CurrentFrame + 1 ],
				floor( (Pos.x * TileSize) - Anchor.x - Camera.x ),
				floor( (Pos.y * TileSize) - Anchor.y - Camera.y )
				);
		}
		else {
			gelDrawTile(
				IntermediateAnimation ? IntermediateAnimation[ CurrentFrame + 1 ] : CurrentAnimation[ CurrentFrame + 1 ],
				floor( (Pos.x * TileSize) - Anchor.x - Camera.x ),
				floor( (Pos.y * TileSize) - Anchor.y - Camera.y )
				);
		}
	}
};
// - -------------------------------------------------------------------------------------------------------------- - //

GelArray< cEnemy* >* MapEnemy;

// - -------------------------------------------------------------------------------------------------------------- - //

const int HopTable[] = { 0,0,0,1,1,2,2,3,3,3,3,3,3,2,2,1,0 };
const int MaulTable[] = { 0,2,3,4,4,5,5,6,6,6,6,6,6,5,4,2,0 };

// - ------------------------------------------------------------------------------------------ - //
class cPlayer {
public:
	struct cPos {
		int x, y;
		
		cPos() : x(0), y(0) { }
		cPos(int _x, int _y) : x(_x), y(_y) { }
	} Pos;
	
	const int* CurrentAnimation;
	const int* IntermediateAnimation;
	int CurrentFrame;
	int FrameDelay;
	
	Vector2D Anchor;
	
	int OffsetX, OffsetY;
	int OffsetAnim;
	
	bool FacingLeft;
	
public:
	cPlayer( int _x, int _y ) :
		Pos( _x, _y )
	{
		CurrentAnimation = Player_Idle;
		IntermediateAnimation = 0;
		CurrentFrame = 0;
		FrameDelay = 0;
		
		Anchor.x = 8;
		Anchor.y = 8;
		
		OffsetX = 0;
		OffsetY = 0;
		OffsetAnim = 0;
		
		
		FacingLeft = false;

		SetAnimation( Player_Idle );
	}
	
	inline void SetIntermediateAnimation( const int* AnimationName ) {
		if ( IntermediateAnimation != AnimationName ) {
			IntermediateAnimation = AnimationName;
			CurrentFrame = 0;
			FrameDelay = 0;
		}	
	}
	
	inline void SetAnimation( const int* AnimationName ) {
		if ( CurrentAnimation != AnimationName ) {
			CurrentAnimation = AnimationName;
			if ( IntermediateAnimation == 0 ) {
				CurrentFrame = 0;
				FrameDelay = 0;
			}
		}
	}
	
	inline void ForceIntermediateAnimation( const int* AnimationName ) {
		IntermediateAnimation = AnimationName;
		CurrentFrame = 0;
		FrameDelay = 0;
	}
	
	inline void ForceAnimation( const int* AnimationName ) {
		CurrentAnimation = AnimationName;
		if ( IntermediateAnimation == 0 ) {
			CurrentFrame = 0;
			FrameDelay = 0;
		}
	}
	
	inline bool IsHopping() {
		return OffsetAnim > 0;
	}

	
//	inline Rect2D GetRect() {
//		return Rect2D( Pos - Vector2D(Shape.x * Real::Half, Shape.y), Shape );
//	}
//
//	inline Rect2D GetRectPlus( const Real _w, const Real _h ) {
//		return Rect2D( Pos - Vector2D((Shape.x + _w) * Real::Half, Shape.y + _h), Shape + Vector2D(_w,_h) );
//	}
//	
//	inline Rect2D GetRect( const Real ForcedWidth, const Real ForcedHeight) {
//		return Rect2D( Pos - Vector2D(ForcedWidth * Real::Half, ForcedHeight), Vector2D( ForcedWidth, ForcedHeight ) );
//	}

	void Step() {
		if ( OffsetX != 0 ) {
			if ( OffsetX > 0 )
				OffsetX--;
			else if ( OffsetX < 0 )
				OffsetX++;
		}

		if ( OffsetY != 0 ) {
			if ( OffsetY > 0 )
				OffsetY--;
			else if ( OffsetY < 0 )
				OffsetY++;
		}

		if ( OffsetAnim != 0 ) {
			if ( OffsetAnim > 0 )
				OffsetAnim--;
			else if ( OffsetAnim < 0 )
				OffsetAnim++;
		}
		
		if ( !IsHopping() ) {
			// Check if shot //
			{
				
			}		
			
			// Do Movement //
			{
				int SX = 0;
				int SY = 0;
				
				int Layer = 0;
				
				if ( Input_Key( KEY_RIGHT ) ) {
					int Tile = (*MapLayer->Data[Layer])(Pos.x+1, Pos.y);
					if ( Tile != TILE_COLLISION )
						SX = 1;
				}
				else if ( Input_Key( KEY_LEFT ) ) {
					int Tile = (*MapLayer->Data[Layer])(Pos.x-1, Pos.y);
					if ( Tile != TILE_COLLISION )
						SX = -1;
				}
				
				if ( SX == 0 ) {
					if ( Input_Key( KEY_DOWN ) ) {
						int Tile = (*MapLayer->Data[Layer])(Pos.x, Pos.y+1);
						if ( Tile != TILE_COLLISION )
							SY = 1;
					}
					else if ( Input_Key( KEY_UP ) ) {
						int Tile = (*MapLayer->Data[Layer])(Pos.x, Pos.y-1);
						if ( Tile != TILE_COLLISION )
							SY = -1;
					}
				}
				
				if ( (SX|SY) != 0 ) {
					GameMoves++;
					GameMoveCountdown = 60*2;
					
//					ForceIntermediateAnimation( Player_Maul );
					ForceIntermediateAnimation( Player_Hop );
					
					ForceAnimation( Player_Idle );
					
					Pos.x += SX;
					Pos.y += SY;
					
					OffsetX = SX * 16;
					OffsetY = SY * 16;
					OffsetAnim = 16;
				}
			}
		}

		
		// Animation System //
		FrameDelay++;
		if ( FrameDelay >= 6 ) {
			FrameDelay = 0;
			CurrentFrame++;
			if ( IntermediateAnimation ) {
				if ( CurrentFrame == IntermediateAnimation[0] ) {
					CurrentFrame = 0;
					IntermediateAnimation = 0;
				}
			}
			else {
				if ( CurrentFrame == CurrentAnimation[0] )
					CurrentFrame = 0;
			}
		}
	}
	
	void Draw( const Vector2D& Camera ) {
//		{
//			Rect2D Rect = GetRect();
//			
//			gelSetColor( 255,255,0,64 );
//			gelDrawRectFill( Rect.P1().x - Camera.x, Rect.P1().y - Camera.y, Rect.Width(), Rect.Height() );
//		}

		int TileSize = 16;
		
		gelBindImage( PlayerId );
		
		const int* TweakTable;
		
		TweakTable = HopTable;
//		if ( Attacking )
//			TweakTable = MaulTable;
		
		if ( FacingLeft ) {
			gelDrawTileFlipX(
				IntermediateAnimation ? IntermediateAnimation[ CurrentFrame + 1 ] : CurrentAnimation[ CurrentFrame + 1 ],
				floor( (Pos.x * TileSize) - OffsetX - Anchor.x - Camera.x ),
				floor( (Pos.y * TileSize) - OffsetY - TweakTable[OffsetAnim] - Anchor.y - Camera.y )
				//floor(Pos.x - Anchor.x - Camera.x), 
				//floor(Pos.y - Anchor.y - Camera.y)
				);
		}
		else {
			gelDrawTile(
				IntermediateAnimation ? IntermediateAnimation[ CurrentFrame + 1 ] : CurrentAnimation[ CurrentFrame + 1 ],
//				floor(Pos.x - Anchor.x - Camera.x), 
//				floor(Pos.y - Anchor.y - Camera.y)
				floor( (Pos.x * TileSize) - OffsetX - Anchor.x - Camera.x ),
				floor( (Pos.y * TileSize) - OffsetY - TweakTable[OffsetAnim] - Anchor.y - Camera.y )
				);
		}
			
//			gelSetColor( 255,0,0,255 );
//			gelDrawCircle( 
//				Pos.x - Camera.x,
//				Pos.y - Camera.y,
//				4 
//				);
	}
};
// - ------------------------------------------------------------------------------------------ - //

cPlayer* Player;

// - ------------------------------------------------------------------------------------------ - //
extern "C" {
	size_t mrGetLayerCount();
	void mrBindLayer( const int _Layer );
	size_t mrGetWidth();
	size_t mrGetHeight();
	int mrGet( int _x, int _y );
	size_t mrGetSize();
	int mrIndex( size_t Index );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void ProcessObjectLayer( const int Layer ) {
	int MapWidth = MapLayer->Data[Layer]->Width();
	int MapHeight = MapLayer->Data[Layer]->Height();
	
	int EnemyCount = CountEnemies( Layer );
	
	if ( MapEnemy ) {
		for ( int idx = 0; idx < EnemyCount; idx++ ) {
			delete MapEnemy->Data[idx];
		}
		delete_GelArray<cEnemy*>( MapEnemy );
	}

	MapEnemy = new_GelArray<cEnemy*>( EnemyCount );
	
	int CurrentEnemy = 0;

	for ( int _y = 0; _y < MapHeight; _y++ ) {
		for ( int _x = 0; _x < MapHeight; _x++ ) {
			int Tile = (*MapLayer->Data[Layer])(_x, _y);

			if ( Tile == 0 ) {
				continue;
			}
			else if ( Tile == TILE_START ) {
				Player->Pos.x = _x;
				Player->Pos.y = _y;

				(*MapLayer->Data[Layer])(_x, _y) = 0;
			}
			else if ( Tile == TILE_ENEMY ) {
				MapEnemy->Data[CurrentEnemy++] = new cEnemy( _x, _y );

				(*MapLayer->Data[Layer])(_x, _y) = 0;
			}			
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void LoadMap() {
	if ( MapLayer ) {
		for ( int idx = 0; idx < mrGetLayerCount(); idx++ ) {
			delete MapLayer->Data[idx];
		}
		delete_GelArray<LayerType*>( MapLayer );
	}

	if ( Player ) {
		delete Player;
	}

	// ---------------------- //
	
	GameMoves = 0;
	GameMoveCountdown = 60*2;

	// Start New Level //
	MapLayer = new_GelArray<LayerType*>( mrGetLayerCount() );

	int LayerCount = mrGetLayerCount();
	Log( "* New Level with %i layers", LayerCount );

	for ( int idx = 0; idx < LayerCount; idx++ ) {
		mrBindLayer( idx );
		MapLayer->Data[idx] = new LayerType( mrGetWidth(), mrGetHeight(), 0 );
		Log( "* New Layer: %ix%i -- %i", mrGetWidth(), mrGetHeight(), mrGetSize() );
		
		int LayerSize = mrGetSize();	
		for ( int idx2 = 0; idx2 < LayerSize; idx2++ ) {
			(*MapLayer->Data[ idx ])[ idx2 ] = mrIndex( idx2 );
		}
	}

	// ---------------------- //

	Player = new cPlayer( 1, 1 );
	
	CameraPos = Vector2D( Player->Pos.x * 16, Player->Pos.y * 16);
	
	ProcessObjectLayer( 0 );//MapLayer->Size - 1 );
	
//	GlobalTotalKeys = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void GameInit() {	
	ScreenWidth = 256;//160;//320;
	ScreenHeight = 160;//120;//240;
	HalfScreenWidth = ScreenWidth >> 1;
	HalfScreenHeight = ScreenHeight >> 1;
	
	gelGraphicsInit( ScreenWidth, ScreenHeight );
	
	CameraPos.x = Real( HalfScreenWidth );
	CameraPos.y = Real( HalfScreenHeight );
	
	TilesetId = gelLoadTileset( "Content/Tiles.png", 16, 16 );
	PlayerId = gelLoadTileset( "Content/BearArt.png", 32, 32 );
	EnemyId = gelLoadTileset( "Content/Hunter.png", 32, 32 );
//	HudId = gelLoadTileset( "Content/Hud-Things.png", 32, 32 );
//	DoorId = gelLoadTileset( "Content/Door.png", 64, 64 );
//	StarsId = gelLoadTileset( "Content/Stars-and-keys.png", 32, 32 );
//	
//	TitleId = gelLoadImage( "Content/Title.png" );
//	WinId = gelLoadImage( "Content/Win.png" );
	
//	LogLevel = 3;

	GameState = STATE_PLAY;//STATE_TITLE;
	
	// ---------------------- //
	
	LoadMap();
/*
	MapLayer = new_GelArray<LayerType*>( mrGetLayerCount() );

	int LayerCount = mrGetLayerCount();

	for ( int idx = 0; idx < LayerCount; idx++ ) {
		mrBindLayer( idx );
		MapLayer->Data[idx] = new LayerType( mrGetWidth(), mrGetHeight(), 0 );
		
		int LayerSize = mrGetSize();	
		for ( int idx2 = 0; idx2 < LayerSize; idx2++ ) {
			(*MapLayer->Data[ idx ])[ idx2 ] = mrIndex( idx2 );
		}
	}
*/
	// ---------------------- //
/*	
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
*/
	// ---------------------- //
}
// - ------------------------------------------------------------------------------------------ - //
void GameExit() {
	// TODO: Delete Map //
	
	delete Player;
	
	gelGraphicsExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void EngineStep() {
	GameMoveCountdown--;
	if ( GameMoveCountdown == 0 ) {
		GameMoves++;
		GameMoveCountdown = 60*2;
	}
	
	Player->Step();

	for ( int idx = 0; idx < MapEnemy->Size; idx++ ) {
		MapEnemy->Data[idx]->Step( );
	}
	
	//CameraPos += (Player->Pos - Vector2D(0,32) - CameraPos) * Real(0.05);
//	CameraPos = Player->Pos;
	
	CameraPos += (Vector2D( Player->Pos.x * 16, Player->Pos.y * 16) - CameraPos) * Real(0.05);

	
//	int OldGlobalTotalKeys = GlobalTotalKeys;
//	GlobalTotalKeys = Player->KeysUsed + Player->TotalKeys;
//	if ( GlobalTotalKeys == TotalKeysInMap ) {
//		if ( GlobalTotalKeys != OldGlobalTotalKeys ) {
//			sndPlay( "Win" );
//		}
//	}
}
// - ------------------------------------------------------------------------------------------ - //
void GameStep() {
	switch ( GameState ) {
		case STATE_TITLE: {
			if ( Input_KeyPressed( KEY_ACTION ) || Input_KeyPressed( KEY_UP ) ) {
				GameState = STATE_PLAY;
			}
			break;
		}
		case STATE_PLAY: {
			EngineStep();
			
			if ( Input_KeyPressed( KEY_MENU ) ) {
				GameState = STATE_TITLE;
				LoadMap();
			}

			break;	
		}
		case STATE_WIN: {
			if ( Input_KeyPressed( KEY_ACTION ) || Input_KeyPressed( KEY_UP ) ) {
				// TODO: Reset Game //
				LoadMap();
				
				GameState = STATE_PLAY;
			}
			break;
		}
	};
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void DrawLayer( const int Layer ) {
	int TileSize = 16;
	
	int TilesWide = (ScreenWidth/TileSize)+1;
	int TilesTall = (ScreenHeight/TileSize)+1;

	int MapWidth = MapLayer->Data[Layer]->Width();
	int MapHeight = MapLayer->Data[Layer]->Height();
	
	float CameraScalar = 1.0f;
//	if ( Layer == 0 ) {
//		CameraScalar = 0.5f;
//	}
	
	float CameraOffsetX = CameraPos.x.ToFloat();
	float CameraOffsetY = CameraPos.y.ToFloat();
	float CameraOffsetXCenter = (CameraOffsetX) - (float)(HalfScreenWidth);
	float CameraOffsetYCenter = (CameraOffsetY) - (float)(HalfScreenHeight);

	CameraOffsetX *= CameraScalar;
	CameraOffsetY *= CameraScalar;
	CameraOffsetXCenter *= CameraScalar;
	CameraOffsetYCenter *= CameraScalar;
	
	if ( CameraOffsetXCenter < 0 )
		CameraOffsetXCenter = 0;
	if ( CameraOffsetYCenter < 0 )
		CameraOffsetYCenter = 0;
	
	int OffsetX = ((int)floor(CameraOffsetXCenter) + HalfScreenWidth) % TileSize;			
	int OffsetY = ((int)floor(CameraOffsetYCenter) + HalfScreenHeight) % TileSize;
	
	int StartX = CameraOffsetXCenter / TileSize;
	if ( StartX < 0 ) {
		StartX = 0;
		OffsetX = 0;
	}
	if ( StartX >= (int)((float)(MapWidth - TilesWide) * CameraScalar) + 1 ) {
		StartX = (int)((float)(MapWidth - TilesWide) * CameraScalar) + 1;
		OffsetX = 0;
	}

	int StartY = CameraOffsetYCenter / TileSize;
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

//	gelDrawTiles( 
//		&((*MapLayer->Data[Layer])[0]), 
//		MapWidth, MapHeight, 
//		StartX, StartY, 
//		EndX, EndY, 
//		-1, 
//		OffsetX, OffsetY 
//		);

	for ( int _y = StartY; _y < EndY; _y++ ) {
		for ( int _x = StartX; _x < EndX; _x++ ) {
			int Tile = (*MapLayer->Data[Layer])(_x, _y);
			if ( Tile > 0 ) {
				gelDrawTile( 
					Tile-1, 
					((_x - StartX) * TileSize) - OffsetX, 
					((_y - StartY) * TileSize) - OffsetY
					);
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void EngineDraw() {
	gelSetColor( 0,0,0,255 );
	gelDrawRectFill( 0, 0, ScreenWidth, ScreenHeight );
	
	// Draw Bottom Layers //
	gelBindImage( TilesetId );
	DrawLayer( 0 );
//	for ( size_t Layer = 0; Layer < (MapLayer->Size-1); Layer++ ) {
//		DrawLayer( Layer );
//	}

	int TileSize = 16;

	// Transform Camera //
	int Layer = 0;
	int MapWidth = MapLayer->Data[Layer]->Width();
	int MapHeight = MapLayer->Data[Layer]->Height();

	Vector2D TransformedCameraPos = CameraPos - Vector2D( HalfScreenWidth, HalfScreenHeight );
	
	if ( TransformedCameraPos.x < 0 )
		TransformedCameraPos.x = 0;
	if ( TransformedCameraPos.y < 0 )
		TransformedCameraPos.y = 0;
		
	if ( TransformedCameraPos.x > (MapWidth * TileSize) - ScreenWidth )
		TransformedCameraPos.x = (MapWidth * TileSize) - ScreenWidth;
	if ( TransformedCameraPos.y > (MapHeight * TileSize) - ScreenHeight )
		TransformedCameraPos.y = (MapHeight * TileSize) - ScreenHeight;
		
	TransformedCameraPos.x = floor(TransformedCameraPos.x);
	TransformedCameraPos.y = floor(TransformedCameraPos.y);

	// Draw Objects //		
//	for ( int idx = 0; idx < MapDoor->Size; idx++ ) {
//		MapDoor->Data[idx]->Draw( TransformedCameraPos );
//	}
	
	for ( int idx = 0; idx < MapEnemy->Size; idx++ ) {
		MapEnemy->Data[idx]->Draw( TransformedCameraPos );
	}
	
	Player->Draw( TransformedCameraPos );

/*
	// Draw Top Layers //
//	DrawObjectLayer( MapLayer->Size - 1 );
	
//	gelBindImage( TilesetId );
//	DrawLayer( MapLayer->Size - 3 );
	
	// Draw UI //
	char Text[128];
	
//	sprintf( Text, "%i/%i", Player->TotalKeys, TotalKeysInMap - Player->KeysUsed );
//	gelSetColor( 0x6F, 0x82, 0xE4, 255 );
//	gelDrawTextLeft( Text, 32+0, 16+1, 23, "FourB" );
//	gelSetColor( 0xD6, 0xEB, 0xFF, 255 );
//	gelDrawTextLeft( Text, 32+0, 16+0, 23, "FourB" );
	
//	sprintf( Text, "%i/%i", Player->TotalStars, TotalStarsInMap );
//	gelSetColor( 0xC7, 0x85, 0x00, 255 );
//	gelDrawTextRight( Text, 320-32-0, 16+1, 23, "FourB" );
//	gelSetColor( 0xFF, 0xE3, 0x00, 255 );
//	gelDrawTextRight( Text, 320-32-0, 16+0, 23, "FourB" );
*/
//	gelBindImage( HudId );
//	gelDrawTile( 0, /**/ 0, 0 );
//	gelDrawTile( 1, /**/ 320-32-0, 0 );
	
//	sprintf( Text, "(%f, %f)", Player->Pos.x.ToFloat(), Player->Pos.y.ToFloat() );
//	gelSetColor( 0xFF, 0xE3, 0x00, 255 );
//	gelDrawTextLeft( Text, 0, 190, 15, "FourB" );
//	sprintf( Text, "(%f, %f)", Player->Pos.x.ToFloat() - Player->Old.x.ToFloat(), Player->Pos.y.ToFloat() - Player->Old.y.ToFloat() );
//	gelSetColor( 0xFF, 0xE3, 0x00, 255 );
//	gelDrawTextLeft( Text, 0, 205, 15, "FourB" );
//	sprintf( Text, "(%f, %f)", gx, gy );
//	gelSetColor( 0xFF, 0xE3, 0x00, 255 );
//	gelDrawTextLeft( Text, 0, 220, 15, "FourB" );

}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GameDrawPaused() {
	
}
// - ------------------------------------------------------------------------------------------ - //
void GameDraw() {
	switch ( GameState ) {
		case STATE_TITLE: {
//			gelBindImage( TitleId );
//			gelDrawImage(0,0);
			break;
		}
		case STATE_PLAY: {
			EngineDraw();
	
			break;	
		}
		case STATE_WIN: {
//			gelBindImage( WinId );
//			gelDrawImage(0,0);
	
//			char Text[64];
//			sprintf( Text, "%i", Player->TotalStars );
//			gelSetColor( 0xC7, 0x85, 0x00, 255 );
//			gelDrawTextLeft( Text, 140-36, 150+2, 46, "FourB" );
//			gelSetColor( 0xFF, 0xE3, 0x00, 255 );
//			gelDrawTextLeft( Text, 140-36, 150, 46, "FourB" );
	
			break;
		}
	};
	
	if ( Input_KeyPressed( KEY_MENU ) ) {
		LoadMap();
	}
}
// - ------------------------------------------------------------------------------------------ - //
