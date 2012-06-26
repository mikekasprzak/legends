// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLD_H__
#define __WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Grid/Grid2D_Class.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cTile {
public:
	Vector2D Motion;
	Vector2D Accumulator;
	
	int Water;
	int Soil;
	int Clay;

public:
	cTile() {}
	cTile( const int _Water, const int _Soil, const int _Clay ) :
		Water( _Water ),
		Soil( _Soil ),
		Clay( _Clay )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
cTile WaterTile( /*W*/ 10, /*S*/  0, /*C*/  0 );
cTile SoilTile(  /*W*/  0, /*S*/ 10, /*C*/  0 );
cTile ClayTile(  /*W*/  0, /*S*/  0, /*C*/ 10 );

// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	cGrid2D<cTile> Map;
	int Iteration;
	
public:
	cWorld( const int Width, const int Height, const int Seed ) :
		Map( Width, Height, WaterTile ),
		Iteration( 0 )
	{
		Generate( Seed );
		
		Vector2D Start(0,0);
		Vector2D Vs1(4,0);
		Vector2D Vs2(4,4);
		Vector2D Vs3(4,3);
		Vector2D Vs4(4,2);
		Vector2D Vs5(4,1);
		
		printf( "Hey1: %f,%f  %f\n", (Vs1-Start).MinitudeNormal().x.ToFloat(), (Vs1-Start).MinitudeNormal().y.ToFloat(), (Vs1-Start).Minitude().ToFloat() );
		printf( "Hey2: %f,%f  %f\n", (Vs2-Start).MinitudeNormal().x.ToFloat(), (Vs2-Start).MinitudeNormal().y.ToFloat(), (Vs2-Start).Minitude().ToFloat() );
		printf( "HeyA: %f,%f  %f\n", (Vs3-Start).MinitudeNormal().x.ToFloat(), (Vs3-Start).MinitudeNormal().y.ToFloat(), (Vs3-Start).Minitude().ToFloat() );
		printf( "HeyB: %f,%f  %f\n", (Vs4-Start).MinitudeNormal().x.ToFloat(), (Vs4-Start).MinitudeNormal().y.ToFloat(), (Vs4-Start).Minitude().ToFloat() );
		printf( "HeyC: %f,%f  %f\n", (Vs5-Start).MinitudeNormal().x.ToFloat(), (Vs5-Start).MinitudeNormal().y.ToFloat(), (Vs5-Start).Minitude().ToFloat() );
	}
	
	void Generate( const int Seed ) {
		srand( Seed );
	
		//Map.DrawRectFill( 4,4, 5,3, SoilTile );
		
		//Map.DrawLine( 2,2, 7,7, SoilTile );
		RadialGenerateBaseMap();
		//NoiseGenerateBaseMap();

		// Fix outsides with water edge //
		Map.DrawRect( 0,0, Map.Width(),Map.Height(), WaterTile );

		// Fill in generated holes //
		ErodeGeneratedHoles(1);
		for ( int idx = 0; idx < 3; idx++ ) {
			FillGeneratedHoles();
			ErodeGeneratedHoles();
		}
	}

	// TODO: Make a member of Grid //
	void RadialGenerateBaseMap() {
		int Steps = 48;
		
		int CenterX = 15;
		int CenterY = 15;
		
		for ( int Angle = 0; Angle < Steps; Angle++ ) {
			Vector2D Vec = Vector2D::Angle( Real((float)Angle / (float)Steps) );
			Vec *= Real(5) + (Real::Random() * Real( 11 ));
				
			Map.DrawLine( 
				CenterX,
				CenterY, 
				CenterX + (int)((Vec.x.ToFloat())), 
				CenterY + (int)((Vec.y.ToFloat())), 
				SoilTile
				);
		}
	}

	// TODO: Make a member of Grid //
	void NoiseGenerateBaseMap() {
		for ( size_t y = 0; y < Map.Height(); y++ ) {
			for ( size_t x = 0; x < Map.Width(); x++ ) {
				Map(x,y) = (Real::Random() > Real(0.6)) ? SoilTile : WaterTile;
			}
		}
	}
	
	// TODO: Make a member of Grid //
	void FillGeneratedHoles( const int ChecksConstant = 5 ) {
		for ( size_t y = 1; y < Map.Height()-1; y++ ) {
			for ( size_t x = 1; x < Map.Width()-1; x++ ) {
				int Check = 0;
				if ( Map(x-1,y+0).Soil > 0 ) Check++;
				if ( Map(x+1,y+0).Soil > 0 ) Check++;
				if ( Map(x+0,y-1).Soil > 0 ) Check++;
				if ( Map(x+0,y+1).Soil > 0 ) Check++;
				if ( Map(x-1,y-1).Soil > 0 ) Check++;
				if ( Map(x+1,y-1).Soil > 0 ) Check++;
				if ( Map(x+1,y+1).Soil > 0 ) Check++;
				if ( Map(x-1,y+1).Soil > 0 ) Check++;
				
				if ( Check >= ChecksConstant )
					Map(x,y) = SoilTile;
			}
		}
	}
	
	// TODO: Make a member of Grid //
	void ErodeGeneratedHoles( const int ChecksConstant = 2 ) {
		for ( size_t y = 1; y < Map.Height()-1; y++ ) {
			for ( size_t x = 1; x < Map.Width()-1; x++ ) {
				int Check = 0;
				if ( Map(x-1,y+0).Soil > 0 ) Check++;
				if ( Map(x+1,y+0).Soil > 0 ) Check++;
				if ( Map(x+0,y-1).Soil > 0 ) Check++;
				if ( Map(x+0,y+1).Soil > 0 ) Check++;
				if ( Map(x-1,y-1).Soil > 0 ) Check++;
				if ( Map(x+1,y-1).Soil > 0 ) Check++;
				if ( Map(x+1,y+1).Soil > 0 ) Check++;
				if ( Map(x-1,y+1).Soil > 0 ) Check++;
				
				if ( Check <= ChecksConstant )
					Map(x,y) = WaterTile;
			}
		}		
	}
	
public:
	void SetOutsideMotion() {
		Real Scalar = 1;
		int w = Map.Width();
		int h = Map.Height();
		
		for ( size_t y = 1; y < h-1; y++ ) {
			Map(0,y).Motion = (Vector2D(Map.HalfWidth(),Map.HalfHeight()) - Vector2D(0,y)).Normal() * Scalar;
			Map(w-1,y).Motion = (Vector2D(Map.HalfWidth(),Map.HalfHeight()) - Vector2D(w-1,y)).Normal() * Scalar;
		}

		for ( size_t x = 0; x < w; x++ ) {
			Map(x,0).Motion = (Vector2D(Map.HalfWidth(),Map.HalfHeight()) - Vector2D(x,0)).Normal() * Scalar;
			Map(x,h-1).Motion = (Vector2D(Map.HalfWidth(),Map.HalfHeight()) - Vector2D(x,h-1)).Normal() * Scalar;
		}		
	}
	
	void StepMotion() {
		// Copy my motion to the Accumulator //
		for ( size_t y = 0; y < Map.Height(); y++ ) {
			for ( size_t x = 0; x < Map.Width(); x++ ) {
				Map(x,y).Accumulator = Map(x,y).Motion;
			}
		}
		for ( size_t y = 0; y < Map.Height(); y++ ) {
			for ( size_t x = 0; x < Map.Width(); x++ ) {
				int _x = x;
				int _y = y;
				//Map(x,y).Accumulator = Map(x,y).Motion;
			}
		}
		// Write the accumulator to Motion //
		for ( size_t y = 0; y < Map.Height(); y++ ) {
			for ( size_t x = 0; x < Map.Width(); x++ ) {
				Map(x,y).Motion = Map(x,y).Accumulator;
			}
		}
	}

public:
	void Step() {
		SetOutsideMotion();
		
		Iteration++;
	}
	
	void Draw() {
		const int BaseColor = 32;
		
		for ( size_t y = 0; y < Map.Height(); y++ ) {
			for ( size_t x = 0; x < Map.Width(); x++ ) {
				// Draw Tile //
				int Red = BaseColor + (Map(x,y).Soil<<2);
				int Green = BaseColor + (Map(x,y).Clay<<2);
				int Blue = BaseColor + (Map(x,y).Water<<2);
				
				gelSetColor( Red,Green,Blue,255 );
				gelDrawRectFill( x*16,y*16, 16,16 );
				
				// Draw Wind //
				if ( Map(x,y).Motion.MagnitudeSquared() == Real::Zero ) {
					gelSetColor( 255,255,255,128 );
					gelDrawCircleFill( (x*16)+8,(y*16)+8, 3 );
				}
				else {
					
				}
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
