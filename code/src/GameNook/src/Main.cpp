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
#include <Geometry/Rect.h>

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
// Number of Frames, followed by frame numbers //
// - ------------------------------------------------------------------------------------------ - //
const int Nook_Idle[] = { 12, /**/ 0,0,1,1,3,3,0,0,1,1,2,2 };
const int Nook_Run[] = { 6, /**/ 4,5,6,7,8,9 };
const int Nook_Anticipation[] = { 3, /**/ 0,10,11 };
const int Nook_Jump[] = { 1, /**/ 12 };
const int Nook_Fall[] = { 1, /**/ 13 };
const int Nook_TouchGround[] = { 1, /**/ 14 };
// - ------------------------------------------------------------------------------------------ - //

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
class cPlayer {
public:
	Vector2D Pos;
	Vector2D Old;
	
	const int* CurrentAnimation;
	int CurrentFrame;
	int FrameDelay;
	
	Vector2D Anchor;
	Vector2D Shape;
	
	bool OnGround;
	bool OnCeiling;
	int JumpPower;

	bool FacingLeft;
	
public:
	cPlayer( float _x, float _y ) :
		Pos( _x, _y ),
		Old( _x, _y )
	{
		CurrentAnimation = Nook_Idle;
		CurrentFrame = 0;
		FrameDelay = 0;
		
		Anchor.x = 32;
		Anchor.y = 64;
		
		Shape.x = 18;
		Shape.y = 28;
		
		OnGround = false;
		JumpPower = 0;
		
		FacingLeft = false;
	}
	
	void SetAnimation( const int* AnimationName ) {
		if ( CurrentAnimation != AnimationName ) {
			CurrentAnimation = AnimationName;
			CurrentFrame = 0;
			FrameDelay = 0;
		}
	}
	
	void ForceAnimation( const int* AnimationName ) {
		CurrentAnimation = AnimationName;
		CurrentFrame = 0;
		FrameDelay = 0;
	}
	
	inline Rect2D GetRect() {
		return Rect2D( Pos - Vector2D(Shape.x * Real::Half, Shape.y), Shape );
	}
	
	void Step() {
		// Physics //
		{
			Vector2D Velocity = Pos - Old;
			Velocity += Vector2D( 0, 0.4f ); // Gravity //
			Velocity += Vector2D( gx, 0 ) * Real(0.2);
			
			if ( (JumpPower > 0) && (gy < 0) ) {
				Velocity.y = -(Real(JumpPower) * Real(0.5));
				JumpPower--;
			}
			if ( gy >= 0 ) {
				JumpPower = 0;
			}
			
			Old = Pos;
			Pos += Velocity * Real( 0.98 );
		}

		// Solve Versus Map //
		{
			Rect2D Rect = GetRect();
			
			int Layer = MapLayer->Size-1;
			
			int StartX = (int)floor(Rect.P1().x.ToFloat()) >> 3;
			int StartY = (int)floor(Rect.P1().y.ToFloat()) >> 3;
			int EndX = ((int)ceil(Rect.P2().x.ToFloat()) >> 3) + 1;
			int EndY = ((int)ceil(Rect.P2().y.ToFloat()) >> 3) + 1;

			int MapWidth = MapLayer->Data[Layer]->Width();
			int MapHeight = MapLayer->Data[Layer]->Height();
			
			if ( StartX < 0 )
				StartX = 0;
			if ( StartY < 0 )
				StartY = 0;
			if ( EndX < 0 )
				EndX = 0;
			if ( EndY < 0 )
				EndY = 0;
			
			if ( StartX >= MapWidth )
				StartX = MapWidth-1;
			if ( StartY >= MapHeight )
				StartY = MapHeight-1;
			if ( EndX >= MapWidth )
				EndX = MapWidth-1;
			if ( EndY >= MapHeight )
				EndY = MapHeight-1;
			
			OnGround = false;
			
			for ( int _y = StartY; _y < EndY; _y++ ) {
				for ( int _x = StartX; _x < EndX; _x++ ) {
					if ( (*MapLayer->Data[ Layer ])(_x, _y) > 0 ) {
						Rect2D VsRect( Vector2D( _x << 3, _y << 3), Vector2D( 8, 8 ) );
						
						if ( Rect == VsRect ) {
							// Perform a Rectangle Union //
							Rect2D Result = VsRect - Rect;
							Vector2D Line = VsRect.Center() - Rect.Center(); 
							
//							Pos += Line.Normal() * (((8+20)/2) - Line.Magnitude()) * Real::Half;
//							Rect = GetRect();

//							gelSetColor( 255,0,0,255 );
//							gelDrawRectFill( Result.P1().x, Result.P1().y, Result.Width(), Result.Height() );
							
							// If it's wider, solve tall //
							if ( Result.Width() > Result.Height() ) {
								Pos.y -= Line.y.Normal() * Result.Height();// * Real::Half;
								
								if ( Line.y > Real::Zero ) {
									JumpPower = 16;
									OnGround = true;
								}
								else if ( Line.y < Real::Zero ) {
									JumpPower = 0;
									OnCeiling = true;
								}
							}
							else {
								Pos.x -= Line.x.Normal() * Result.Width();// * Real::Half;
							}

							Rect = GetRect();

//							gelSetColor( 0,255,0,64 );
						}
						else {						
//							gelSetColor( 0,64,0,64 );
						}

//						gelDrawRectFill( VsRect.P1().x, VsRect.P1().y, VsRect.Width(), VsRect.Height() );
					}
				}
			}
		}
			
		// Animation and Controls //
		if ( OnGround ) {
			if ( gx != 0 ) {
				SetAnimation( Nook_Run );
			}
			else {
				SetAnimation( Nook_Idle );
			}
			
			// NOTE: This scope makes changing which way you face only work when on the ground //
			if ( gx > 0 ) {
				FacingLeft = false;
			}
			else if ( gx < 0 ) {
				FacingLeft = true;
			}
		}
		else {
			if ( (Old - Pos).y > 0 ) {
				SetAnimation( Nook_Jump );
			}
			else {
				SetAnimation( Nook_Fall );
			}
		}
		
		FrameDelay++;
		if ( FrameDelay >= 3 ) {
			FrameDelay = 0;
			CurrentFrame++;
			if ( CurrentFrame == CurrentAnimation[0] )
				CurrentFrame = 0;
		}		
	}
	
	void Draw( const Vector2D& Camera ) {
		{
			Rect2D Rect = GetRect();
			
			gelSetColor( 255,255,0,64 );
			gelDrawRectFill( Rect.P1().x - Camera.x, Rect.P1().y - Camera.y, Rect.Width(), Rect.Height() );
		}
		
		gelBindImage( PlayerId );
		
		if ( FacingLeft ) {
			gelDrawTileFlipX(
				CurrentAnimation[ CurrentFrame + 1 ],
				floor(Pos.x) - Anchor.x - Camera.x, 
				floor(Pos.y) - Anchor.y - Camera.y
				);
		}
		else {
			gelDrawTile(
				CurrentAnimation[ CurrentFrame + 1 ],
				floor(Pos.x) - Anchor.x - Camera.x, 
				floor(Pos.y) - Anchor.y - Camera.y
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
	
	// ---------------------- //
	
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

	// ---------------------- //

	Player = new cPlayer( 112+16, 104 );
}
// - ------------------------------------------------------------------------------------------ - //
void GameExit() {
	// TODO: Delete Map //
	
	delete Player;
	
	gelGraphicsExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GameStep() {
//	if ( Button & 0x10 ) {
//		CameraPos.x += gx * 4;
//		CameraPos.y += gy * 4;
//	}
//	else {
//		CameraPos.x += gx * 2;//0.5;
//		CameraPos.y += gy * 2;//0.5;
//	}
	
	Player->Step();
	
	CameraPos = Player->Pos;//+= (Player->Pos - CameraPos) * Real(0.25);
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

	int Layer = 0;
	int MapWidth = MapLayer->Data[Layer]->Width();
	int MapHeight = MapLayer->Data[Layer]->Height();

	Vector2D TransformedCameraPos = CameraPos - Vector2D( HalfScreenWidth, HalfScreenHeight );
	
	if ( TransformedCameraPos.x < 0 )
		TransformedCameraPos.x = 0;
	if ( TransformedCameraPos.y < 0 )
		TransformedCameraPos.y = 0;
		
	if ( TransformedCameraPos.x > (MapWidth<<3) - ScreenWidth )
		TransformedCameraPos.x = (MapWidth<<3) - ScreenWidth;
	if ( TransformedCameraPos.y > (MapHeight<<3) - ScreenHeight )
		TransformedCameraPos.y = (MapHeight<<3) - ScreenHeight;
		
	Player->Draw( TransformedCameraPos );

//	gelSetColor( 255,0,0,255 );
//	gelDrawCircle( 
//		CameraPos.x.ToFloat() - (StartX<<3) - OffsetX, 
//		CameraPos.y.ToFloat() - (StartY<<3) - OffsetY, 
//		10 
//		);
}
// - ------------------------------------------------------------------------------------------ - //

