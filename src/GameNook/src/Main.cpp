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

// - ------------------------------------------------------------------------------------------ - //
// Number of Frames, followed by frame numbers //
// - ------------------------------------------------------------------------------------------ - //
const int Nook_Idle[] = { 12, /**/ 0,0,1,1,3,3,0,0,1,1,2,2 };
const int Nook_Run[] = { 6, /**/ 4,5,6,7,8,9 };
const int Nook_PreJump[] = { 2, /**/ 10,11 };
const int Nook_Jump[] = { 1, /**/ 12 };
const int Nook_Fall[] = { 1, /**/ 13 };
const int Nook_TouchGround[] = { 1, /**/ 14 };
const int Nook_WallGrab[] = { 1, /**/ 42 };
const int Nook_WallJump[] = { 3, /**/ 43, 43, 12 };
const int Nook_Transform[] = { 12, /**/ 21,22,23,24,25,26,27,28,29,30,31,32 };
// - ------------------------------------------------------------------------------------------ - //
const int Nook_Sm_Idle[] = { 1, /**/ 15 };
const int Nook_Sm_Run[] = { 4, /**/ 15,16,17,18 };
//const int Nook_Sm_Anticipation[] = { 3, /**/ 0,10,11 };
const int Nook_Sm_Jump[] = { 1, /**/ 19 };
const int Nook_Sm_Fall[] = { 1, /**/ 20 };
//const int Nook_Sm_TouchGround[] = { 1, /**/ 14 };
const int Nook_Sm_Transform[] = { 9, /**/ 33,34,35,36,37,38,39,40,41 };
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
const int TILE_COLLISION = 1857;
const int TILE_NOGROW = 1858;
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

int TilesetId; // ID //
int PlayerId; // ID //

Vector2D CameraPos;

typedef cGrid2D<short> LayerType;
GelArray< LayerType* >* MapLayer;


// - ------------------------------------------------------------------------------------------ - //
const int NOOK_BIG_WIDTH = 14;
const int NOOK_BIG_HEIGHT = 28;
const int NOOK_SM_WIDTH = 6;
const int NOOK_SM_HEIGHT = 6;
// - ------------------------------------------------------------------------------------------ - //
class cPlayer {
public:
	Vector2D Pos;
	Vector2D Old;
	
	const int* CurrentAnimation;
	const int* IntermediateAnimation;
	int CurrentFrame;
	int FrameDelay;
	
	Vector2D Anchor;
	Vector2D Shape;
	
	bool OnGround, WasOnGround;
	bool OnCeiling, WasOnCeiling;
	bool OnWall, WasOnWall;
	int JumpPower;

	bool FacingLeft;
	
	bool IsBig;
	
public:
	cPlayer( float _x, float _y ) :
		Pos( _x, _y ),
		Old( _x, _y )
	{
		CurrentAnimation = Nook_Idle;
		IntermediateAnimation = 0;
		CurrentFrame = 0;
		FrameDelay = 0;
		
		Anchor.x = 32;
		Anchor.y = 64;
		
		
		OnGround = false;
		WasOnGround = false;
		OnCeiling = false;
		WasOnCeiling = false;
		OnWall = false;
		WasOnWall = false;
		JumpPower = 0;
		
		FacingLeft = false;
		
		SetBig( true, false );
	}
	
	inline void SetBig( const bool _IsBig, const bool _SetAnimation = true ) {
		IsBig = _IsBig;
		
		if ( IsBig ) {
			Shape.x = NOOK_BIG_WIDTH;
			Shape.y = NOOK_BIG_HEIGHT;
			if ( _SetAnimation ) {
				SetAnimation( Nook_Idle );
				SetIntermediateAnimation( Nook_Sm_Transform );
			}
		}
		else {
			Shape.x = NOOK_SM_WIDTH;
			Shape.y = NOOK_SM_WIDTH;
			if ( _SetAnimation ) {
				SetAnimation( Nook_Sm_Idle );
				SetIntermediateAnimation( Nook_Transform );
			}
		}
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

	
	inline Rect2D GetRect() {
		return Rect2D( Pos - Vector2D(Shape.x * Real::Half, Shape.y), Shape );
	}
	
	inline Rect2D GetRect( const Real ForcedWidth, const Real ForcedHeight) {
		return Rect2D( Pos - Vector2D(ForcedWidth * Real::Half, ForcedHeight), Vector2D( ForcedWidth, ForcedHeight ) );
	}

	inline bool NotTransforming() {
		return (IntermediateAnimation != Nook_Sm_Transform) && (IntermediateAnimation != Nook_Transform);
	}
	
	inline bool NotWallJumping() {
		return IntermediateAnimation != Nook_WallJump;
	}
	
	bool CanTransformHere() {
		Rect2D Rect = GetRect( NOOK_BIG_WIDTH, NOOK_BIG_HEIGHT );
		
		int Layer = MapLayer->Size-2;
		
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
		
		WasOnGround = OnGround;
		OnGround = false;
		
		for ( int _y = StartY; _y < EndY; _y++ ) {
			for ( int _x = StartX; _x < EndX; _x++ ) {
				int TileToTest = (*MapLayer->Data[ Layer ])(_x, _y);
				
				if ( (TileToTest >= TILE_COLLISION) && (TileToTest <= TILE_NOGROW) ) {
					Rect2D VsRect( Vector2D( _x << 3, _y << 3), Vector2D( 8, 8 ) );
					
					if ( Rect == VsRect ) {
						return false;
					}
				}
			}
		}
		
		return true;
	}
	
	void Step() {
		// Physics //
		{
			Pos += Vector2D( 0, 0.4f ); // Gravity //
			if ( NotTransforming() && NotWallJumping() ) {
				Pos += Vector2D( gx, 0 ) * (IsBig ? Real(0.2) : Real(0.15));
			}
			
			Vector2D Velocity = Pos - Old;
			if ( (JumpPower > 0) ) {
				if ( Input_Key( KEY_UP ) && NotTransforming() ) {
					if ( Input_KeyPressed( KEY_UP ) ) {
						if ( IsBig ) {
							sndPlay( "Jump01" );
							if ( OnGround )
								SetIntermediateAnimation( Nook_PreJump );
							else if ( OnWall ) {
								if ( FacingLeft ) {
									Velocity.x = +Real(5);
								}
								else {
									Velocity.x = -Real(5);
								}
								FacingLeft = !FacingLeft;
								SetIntermediateAnimation( Nook_WallJump );
							}
						}
						else {
							sndPlay( "Jump02" );
						}
					}

					Velocity.y = -(Real(JumpPower) * Real(0.5));
					JumpPower--;
				}
			}
			if ( !Input_Key( KEY_UP ) ) {
				JumpPower = 0;
			}
			Pos -= (Pos-Old) - Velocity;
			
			// Clamp to Speed //
			if ( IsBig ) {
				if ( (Pos - Old).MagnitudeSquared() > 8*8 ) {
					Pos = Old + ((Pos - Old).Normal() * Real(8));
				}
			}
			else {
				if ( (Pos - Old).MagnitudeSquared() > 6*6 ) {
					Pos = Old + ((Pos - Old).Normal() * Real(6));
				}
			}
			
			Velocity = Pos - Old;
			Old = Pos;
			
			Real Scalar( 0.96 );
			if ( OnGround && gx == 0 ) {
				Scalar = Real( 0.8 );
			}
			if ( OnWall && (gx != 0) && (Velocity.y > 0) ) {
				Scalar = Real( 0.3 );
			}
			
			Pos += Velocity * Scalar;
		}

		// Solve Versus Map //
		{
			Rect2D Rect = GetRect();
			
			int Layer = MapLayer->Size-2;
			
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
			
			WasOnGround = OnGround;
			WasOnCeiling = OnCeiling;
			WasOnWall = OnWall;
			OnGround = false;
			OnCeiling = false;
			OnWall = false;

			int CollisionBits = 0;
			
			static const int COLLISION_TOP_LEFT =		0x10;
			static const int COLLISION_TOP_RIGHT =		0x20;
			static const int COLLISION_BOTTOM_LEFT =	0x40;
			static const int COLLISION_BOTTOM_RIGHT =	0x80;

			static const int COLLISION_TOP =			0x1;
			static const int COLLISION_BOTTOM =			0x2;
			static const int COLLISION_LEFT =			0x4;
			static const int COLLISION_RIGHT =			0x8;

			Rect2D VsBottomRect;
			Rect2D VsTopRect;
			Rect2D VsLeftRect;
			Rect2D VsRightRect;
			
			Rect2D VsTopLeftRect;
			Rect2D VsTopRightRect;
			Rect2D VsBottomLeftRect;
			Rect2D VsBottomRightRect;
			
//			// Corners //
//			{
//				if ( (*MapLayer->Data[ Layer ])(StartX, StartY) == TILE_COLLISION ) {
//					VsTopLeftRect = Rect2D( Vector2D( StartX << 3, StartY << 3), Vector2D( 8, 8 ) );
//					CollisionBits |= COLLISION_TOP_LEFT;
//				}
//				if ( (*MapLayer->Data[ Layer ])(EndX-1, StartY) == TILE_COLLISION ) {
//					VsTopRightRect = Rect2D( Vector2D( (EndX-1) << 3, StartY << 3), Vector2D( 8, 8 ) );
//					CollisionBits |= COLLISION_TOP_RIGHT;
//				}
//				if ( (*MapLayer->Data[ Layer ])(StartX, EndY-1) == TILE_COLLISION ) {
//					VsBottomLeftRect = Rect2D( Vector2D( StartX << 3, (EndY-1) << 3), Vector2D( 8, 8 ) );
//					CollisionBits |= COLLISION_BOTTOM_LEFT;
//				}
//				if ( (*MapLayer->Data[ Layer ])(EndX-1, EndY-1) == TILE_COLLISION ) {
//					VsBottomRightRect = Rect2D( Vector2D( (EndX-1) << 3, (EndY-1) << 3), Vector2D( 8, 8 ) );
//					CollisionBits |= COLLISION_BOTTOM_RIGHT;
//				}
//			}
			
			// Bottom Row //
			{
				bool Started = false;
				
				int _y = EndY - 1;
				for ( int _x = StartX; _x < EndX; _x++ ) {
					if ( (*MapLayer->Data[ Layer ])(_x, _y) == TILE_COLLISION ) {
						if ( Started ) {
							VsBottomRect += Rect2D( Vector2D( _x << 3, _y << 3), Vector2D( 8, 32 ) );
						}
						else {
							VsBottomRect = Rect2D( Vector2D( _x << 3, _y << 3), Vector2D( 8, 32 ) );
							Started = true;
							CollisionBits |= COLLISION_BOTTOM;
						}
					}
				}
			}
			
			// Left Row //
			{
				bool Started = false;
				
				int _x = StartX;
				for ( int _y = StartY; _y < EndY; _y++ ) {
					if ( (*MapLayer->Data[ Layer ])(_x, _y) == TILE_COLLISION ) {
						if ( Started ) {
							VsLeftRect += Rect2D( Vector2D( (_x-3) << 3, _y << 3), Vector2D( 32, 8 ) );
						}
						else {
							VsLeftRect = Rect2D( Vector2D( (_x-3) << 3, _y << 3), Vector2D( 32, 8 ) );
							CollisionBits |= COLLISION_LEFT;
							Started = true;
						}
					}
				}
			}


			// Right Row //
			{
				bool Started = false;
				
				int _x = EndX - 1;
				for ( int _y = StartY; _y < EndY; _y++ ) {
					if ( (*MapLayer->Data[ Layer ])(_x, _y) == TILE_COLLISION ) {
						if ( Started ) {
							VsRightRect += Rect2D( Vector2D( _x << 3, _y << 3), Vector2D( 32, 8 ) );
						}
						else {
							VsRightRect = Rect2D( Vector2D( _x << 3, _y << 3), Vector2D( 32, 8 ) );
							CollisionBits |= COLLISION_RIGHT;
							Started = true;
						}
					}
				}
			}

			// Top Row //
			{
				bool Started = false;
				
				int _y = StartY;
				for ( int _x = StartX; _x < EndX; _x++ ) {
					if ( (*MapLayer->Data[ Layer ])(_x, _y) == TILE_COLLISION ) {
						if ( Started ) {
							VsTopRect += Rect2D( Vector2D( _x << 3, (_y-3) << 3), Vector2D( 8, 32 ) );
						}
						else {
							VsTopRect = Rect2D( Vector2D( _x << 3, (_y-3) << 3), Vector2D( 8, 32 ) );
							CollisionBits |= COLLISION_TOP;
							Started = true;
						}
					}
				}
			}
			
			// SOLVE! //
			{
				int ActualCollisionBits = 0;

				if ( CollisionBits & COLLISION_BOTTOM )
					if ( VsBottomRect.Width() > 8 )
						if ( Rect == VsBottomRect )
							ActualCollisionBits |= COLLISION_BOTTOM;
				if ( CollisionBits & COLLISION_TOP )
					if ( VsTopRect.Width() > 8 )
						if ( Rect == VsTopRect )
							ActualCollisionBits |= COLLISION_TOP;
				if ( CollisionBits & COLLISION_LEFT )
					if ( VsLeftRect.Height() > 8 )
						if ( Rect == VsLeftRect )
							ActualCollisionBits |= COLLISION_LEFT;
				if ( CollisionBits & COLLISION_RIGHT )
					if ( VsRightRect.Height() > 8 )
						if ( Rect == VsRightRect )
							ActualCollisionBits |= COLLISION_RIGHT;

				if ( ActualCollisionBits == 0 ) {
					if ( CollisionBits & COLLISION_BOTTOM )
						if ( Rect == VsBottomRect )
							ActualCollisionBits |= COLLISION_BOTTOM;
					if ( CollisionBits & COLLISION_TOP )
						if ( Rect == VsTopRect )
							ActualCollisionBits |= COLLISION_TOP;
					if ( CollisionBits & COLLISION_LEFT )
						if ( Rect == VsLeftRect )
							ActualCollisionBits |= COLLISION_LEFT;
					if ( CollisionBits & COLLISION_RIGHT )
						if ( Rect == VsRightRect )
							ActualCollisionBits |= COLLISION_RIGHT;
				}
				
//				if ( CollisionBits & COLLISION_TOP_LEFT )
//					if ( Rect == VsTopLeftRect )
//						ActualCollisionBits |= COLLISION_TOP_LEFT;
//				if ( CollisionBits & COLLISION_TOP_RIGHT )
//					if ( Rect == VsTopRightRect )
//						ActualCollisionBits |= COLLISION_TOP_RIGHT;
//				if ( CollisionBits & COLLISION_BOTTOM_LEFT )
//					if ( Rect == VsBottomLeftRect )
//						ActualCollisionBits |= COLLISION_BOTTOM_LEFT;
//				if ( CollisionBits & COLLISION_BOTTOM_RIGHT )
//					if ( Rect == VsBottomRightRect )
//						ActualCollisionBits |= COLLISION_BOTTOM_RIGHT;				
				
				if ( ActualCollisionBits & COLLISION_BOTTOM ) {
					Rect2D Result = VsBottomRect - Rect;
					Vector2D Line = VsBottomRect.Center() - Rect.Center(); 
					
					if ( Result.Width() > Result.Height() ) {
						Pos.y -= Line.y.Normal() * Result.Height();// * Real::Half;
							
						if ( Line.y > Real::Zero ) {
							if ( !Input_Key( KEY_UP ) ) {
								if ( IsBig )
									JumpPower = 16;
								else
									JumpPower = 10;
							}
							if ( WasOnGround == false ) {
								sndPlay( "Ground" );
								if ( IsBig && NotTransforming() )
									SetIntermediateAnimation( Nook_TouchGround );
							}
							OnGround = true;
						}
					}
					else {
//						Pos.x -= Line.x.Normal() * Result.Width();// * Real::Half;
					}
				}

				if ( ActualCollisionBits & COLLISION_TOP ) {
					Rect2D Result = VsTopRect - Rect;
					Vector2D Line = VsTopRect.Center() - Rect.Center(); 
					
					if ( Result.Width() > Result.Height() ) {
						Pos.y -= Line.y.Normal() * Result.Height();// * Real::Half;
							
						if ( Line.y < Real::Zero ) {
							JumpPower = 0;
							if ( WasOnCeiling == false ) {
								sndPlay( "Ceiling" );
							}
							OnCeiling = true;
						}
					}
					else {
//						Pos.x -= Line.x.Normal() * Result.Width();// * Real::Half;
					}
				}


				if ( ActualCollisionBits & COLLISION_LEFT ) {
					Rect2D Result = VsLeftRect - Rect;
					Vector2D Line = VsLeftRect.Center() - Rect.Center(); 
					
					if ( Result.Width() > Result.Height() ) {
//						Pos.y -= Line.y.Normal() * Result.Height();// * Real::Half;
					}
					else {
						Pos.x -= Line.x.Normal() * Result.Width();// * Real::Half;

						if ( VsLeftRect.Height() > 24 ) {
							if ( !Input_Key( KEY_UP ) ) {
								if ( IsBig )
									JumpPower = 12;
							}
														
							OnWall = true;
							if ( gx < 0 )
								FacingLeft = true;
						}
					}
				}
				
				if ( ActualCollisionBits & COLLISION_RIGHT ) {
					Rect2D Result = VsRightRect - Rect;
					Vector2D Line = VsRightRect.Center() - Rect.Center(); 
					
					if ( Result.Width() > Result.Height() ) {
//						Pos.y -= Line.y.Normal() * Result.Height();// * Real::Half;
					}
					else {
						Pos.x -= Line.x.Normal() * Result.Width();// * Real::Half;

						if ( VsRightRect.Height() > 24 ) {
							if ( !Input_Key( KEY_UP ) ) {
								if ( IsBig )
									JumpPower = 12;
							}
						
							OnWall = true;
							if ( gx > 0 )
								FacingLeft = false;
						}
					}
				}
				
			}
									
			/*
			for ( int _y = StartY; _y < EndY; _y++ ) {
				for ( int _x = StartX; _x < EndX; _x++ ) {
					if ( (*MapLayer->Data[ Layer ])(_x, _y) == TILE_COLLISION ) {
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
									if ( !Input_Key( KEY_UP ) ) {
										if ( IsBig )
											JumpPower = 16;
										else
											JumpPower = 10;
									}
									if ( WasOnGround == false ) {
										if ( IsBig && NotTransforming() )
											SetIntermediateAnimation( Nook_TouchGround );
									}
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
			*/
		}
			
		// Animation and Controls //
		if ( OnGround ) {
			if ( NotTransforming() ) {
				if ( gx != 0 ) {
					SetAnimation( IsBig ? Nook_Run : Nook_Sm_Run );
				}
				else {
					SetAnimation( IsBig ? Nook_Idle : Nook_Sm_Idle );
				}
				
				// NOTE: This scope makes changing which way you face only work when on the ground //
				if ( gx > 0 ) {
					FacingLeft = false;
				}
				else if ( gx < 0 ) {
					FacingLeft = true;
				}
			}
		}
		else {
			if ( (Old - Pos).y > 0 ) {
				SetAnimation( IsBig ? Nook_Jump : Nook_Sm_Jump );
			}
			else {
				if ( IsBig ) {
					if ( OnWall ) {
						if ( CurrentAnimation != Nook_WallGrab ) {
							sndPlay( "Slide" );
						}
						SetAnimation( Nook_WallGrab );
					}
					else
						SetAnimation( Nook_Fall );
				}
				else {
					SetAnimation( Nook_Sm_Fall );
				}
			}
		}

		if ( Input_KeyPressed( KEY_ACTION ) ) {
			if ( NotTransforming() ) {
				if ( IsBig == false ) {
					if ( CanTransformHere() ) {
						SetBig( !IsBig );
						sndPlay( "Change" );
					}
					else {
						// TODO: Honk Can't Transform //
						sndPlay( "CantChange" );
					}
				}
				else {
					SetBig( !IsBig );
					sndPlay( "Change" );
				}
			}
		}
		
		FrameDelay++;
		if ( FrameDelay >= 3 ) {
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
		
		gelBindImage( PlayerId );
		
		if ( FacingLeft ) {
			gelDrawTileFlipX(
				IntermediateAnimation ? IntermediateAnimation[ CurrentFrame + 1 ] : CurrentAnimation[ CurrentFrame + 1 ],
				floor(Pos.x - Anchor.x - Camera.x), 
				floor(Pos.y - Anchor.y - Camera.y)
				);
		}
		else {
			gelDrawTile(
				IntermediateAnimation ? IntermediateAnimation[ CurrentFrame + 1 ] : CurrentAnimation[ CurrentFrame + 1 ],
				floor(Pos.x - Anchor.x - Camera.x), 
				floor(Pos.y - Anchor.y - Camera.y)
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

	Player = new cPlayer( 112+16+32, 104+32 );
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
	Player->Step();
	
	CameraPos += (Player->Pos - CameraPos) * Real(0.25);
//	CameraPos = Player->Pos;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void DrawLayer( const int Layer ) {
	int TilesWide = (ScreenWidth/8)+1;
	int TilesTall = (ScreenHeight/8)+1;

	int MapWidth = MapLayer->Data[Layer]->Width();
	int MapHeight = MapLayer->Data[Layer]->Height();
	
	float CameraScalar = 1.0f;
	if ( Layer == 0 ) {
		CameraScalar = 0.5f;
	}
	
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
	
	int OffsetX = ((int)floor(CameraOffsetXCenter) + HalfScreenWidth) % 8;			
	int OffsetY = ((int)floor(CameraOffsetYCenter) + HalfScreenHeight) % 8;
	
	int StartX = CameraOffsetXCenter / 8;
	if ( StartX < 0 ) {
		StartX = 0;
		OffsetX = 0;
	}
	if ( StartX >= (int)((float)(MapWidth - TilesWide) * CameraScalar) + 1 ) {
		StartX = (int)((float)(MapWidth - TilesWide) * CameraScalar) + 1;
		OffsetX = 0;
	}

	int StartY = CameraOffsetYCenter / 8;
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
// - ------------------------------------------------------------------------------------------ - //
void GameDraw() {
	// Draw Bottom Layers //
	gelBindImage( TilesetId );
	for ( size_t Layer = 0; Layer < (MapLayer->Size - 3); Layer++ ) {
		DrawLayer( Layer );
	}

	// Transform Camera //
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

	// Draw Objects //		
	Player->Draw( TransformedCameraPos );

	// Draw Top Layers //
	gelBindImage( TilesetId );
	DrawLayer( MapLayer->Size - 3 );
}
// - ------------------------------------------------------------------------------------------ - //

