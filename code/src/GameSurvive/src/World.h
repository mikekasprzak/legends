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
	cWorld( const int Width, const int Height ) :
		Map( Width, Height, WaterTile ),
		Iteration( 0 )
	{
		Generate();
	}
	
	void Generate() {
		//Map.DrawRect( 0,0, Map.Width(),Map.Height(), SoilTile );
		
		//Map.DrawRectFill( 4,4, 5,3, SoilTile );
		
		Map.DrawLine( 2+6,2, 4+6,9, SoilTile );
	}

	void RadialGenerateBaseMap() {
		for ( size_t x = 0; x < Map.Width(); x++ ) {
			
		}
		for ( size_t y = 0; y < Map.Height(); y++ ) {
		}
	}

	void NoiseGenerateBaseMap() {
		for ( size_t y = 0; y < Map.Height(); y++ ) {
			for ( size_t x = 0; x < Map.Width(); x++ ) {
			}
		}		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //
