// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLD_H__
#define __WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Grid/Grid2D_Class.h>
// - ------------------------------------------------------------------------------------------ - //
class cTile {
public:
	int Water;
	int Soil;

public:
	cTile() {}
	cTile( const int _Water, const int _Soil ) :
		Water( _Water ),
		Soil( _Soil )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
cTile WaterTile( /*W*/ 20, /*S*/ 0 );
cTile SoilTile( /*W*/ 0, /*S*/ 10 );

// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	cGrid2D<cTile> Map;
	int Iteration;
	
public:
	cWorld( const int Width, const int Height, const int Seed ) :
		Map( Width, Height, WaterTile ),
		Iteration( Seed )
	{
		Generate( Seed );
	}
	
	void Generate( const int Seed ) {
		srand( Seed );
	
		//Map.DrawRectFill( 4,4, 5,3, SoilTile );
		
		//Map.DrawLine( 2,2, 7,7, SoilTile );
		//RadialGenerateBaseMap();
		NoiseGenerateBaseMap();

		// Fix outsides with water edge //
		Map.DrawRect( 0,0, Map.Width(),Map.Height(), WaterTile );

		// Fill in generated holes //
		ErodeGeneratedHoles(1);
		for ( int idx = 0; idx < 3; idx++ ) {
			FillGeneratedHoles();
			ErodeGeneratedHoles();
		}
	}

	void RadialGenerateBaseMap() {
		int Steps = 24;
		
		int CenterX = 8;
		int CenterY = 4;
		
		for ( int Angle = 0; Angle < Steps; Angle++ ) {
			Vector2D Vec = Vector2D::Angle( Real((float)Angle / (float)Steps) );
			Vec *= Real(6);//Real::Random() * Real( 8 );
				
			Map.DrawLine( 
				CenterX,
				CenterY, 
				CenterX + (int)((Vec.x.ToFloat())), 
				CenterY + (int)((Vec.y.ToFloat())), 
				SoilTile
				);
		}
	}

	void NoiseGenerateBaseMap() {
		for ( size_t y = 0; y < Map.Height(); y++ ) {
			for ( size_t x = 0; x < Map.Width(); x++ ) {
				Map(x,y) = (Real::Random() > Real(0.6)) ? SoilTile : WaterTile;
			}
		}
	}
	
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
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
