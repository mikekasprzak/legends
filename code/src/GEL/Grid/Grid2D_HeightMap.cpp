// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include <Math/Real.h>
#include "Grid2D_HeightMap.h"
// - ------------------------------------------------------------------------------------------ - //
const int _displacement_PlasmaFractal_HeightMap( const int Displacement ) {
	return (int)((Real::Random() * Real(Displacement)) - Real(Displacement >> 1)).ToFloat();	
}
// - ------------------------------------------------------------------------------------------ - //
void _diamond_PlasmaFractal_HeightMap( cGrid2D<int>& Map, const int x1, const int y1, const int x2, const int y2 ) {
	int Step = x2-x1;	// Always a Power of Two, so this is safe //
	
	if ( Step <= 1 )
		return;

	int Displacement = Step;
	int HalfD = Displacement >> 1;
	
	int XMid = x1 + HalfD;
	int YMid = y1 + HalfD;
	
	// Diamond Step (4 corners equal a middle) //
	Map( XMid, YMid ) = 
		((
			Map.Wrap( x1, y1 ) +
			Map.Wrap( x2, y1 ) +
			Map.Wrap( x1, y2 ) +
			Map.Wrap( x2, y2 )
		) / 4) +
		_displacement_PlasmaFractal_HeightMap( Displacement );
}
// - ------------------------------------------------------------------------------------------ - //
void _square_PlasmaFractal_HeightMap( cGrid2D<int>& Map, const int x1, const int y1, const int x2, const int y2 ) {
	int Step = x2-x1;	// Always a Power of Two, so this is safe //
	
	if ( Step <= 1 )
		return;

	int Displacement = Step;
	int HalfD = Displacement >> 1;
	
	int F = Map.IndexWrap( x1 + HalfD, y1 );
	int G = Map.IndexWrap( x1, y1 + HalfD );
	int H = Map.IndexWrap( x2, y1 + HalfD );
	int I = Map.IndexWrap( x1 + HalfD, y2 );
	
	// Square Step (4 midpoints, with need for the diamond) //
	Map[F] = 
		((
			Map.Wrap( x1, y1 ) +
			Map.Wrap( x2, y1 ) +
			Map.Wrap( x1 + HalfD, y1 - HalfD ) +
			Map.Wrap( x1 + HalfD, y1 + HalfD )
		) / 4) +
		_displacement_PlasmaFractal_HeightMap( Displacement );

	Map[G] = 
		((
			Map.Wrap( x1, y1 ) +
			Map.Wrap( x1, y2 ) +
			Map.Wrap( x1 - HalfD, y1 + HalfD ) +
			Map.Wrap( x1 + HalfD, y1 + HalfD )
		) / 4) +
		_displacement_PlasmaFractal_HeightMap( Displacement );

	Map[H] = 
		((
			Map.Wrap( x2, y1 ) +
			Map.Wrap( x2, y2 ) +
			Map.Wrap( x2 - HalfD, y1 + HalfD ) +
			Map.Wrap( x2 + HalfD, y1 + HalfD )
		) / 4) +
		_displacement_PlasmaFractal_HeightMap( Displacement );

	Map[I] = 
		((
			Map.Wrap( x1, y2 ) +
			Map.Wrap( x2, y2 ) +
			Map.Wrap( x1 + HalfD, y2 - HalfD ) +
			Map.Wrap( x1 + HalfD, y2 + HalfD )
		) / 4) +
		_displacement_PlasmaFractal_HeightMap( Displacement );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// The Diamond-Square algorithm (Midpoint Displacement, Cloud/Plasma Fractal) -- Powers of Two //
// - http://en.wikipedia.org/wiki/Diamond-square_algorithm //
// - Game Programming Gems #1 - 4.18 Fractal Terrain Generation - Pg 503 //
cGrid2D<int> generate_PlasmaFractal_HeightMap( const size_t Width, const size_t Height ) {
	cGrid2D<int> Map(Width, Height);
	Map.Fill(0);
	
	// -- Setup -- //
	Map( 0, 0 ) = Map.Width() >> 2;	// Start Value //
	int W = Map.Width();
	int H = Map.Height();
	
	int XSteps = 1;
	int YSteps = 1;
	
	while( W >= 2 ) {
		// -- Diamond -- //
		for ( int y = 0; y < YSteps; y++ ) {
			for ( int x = 0; x < XSteps; x++ ) {
				int x1 = W * x;
				int y1 = H * y;
				int x2 = W * (x+1);
				int y2 = H * (y+1);
				_diamond_PlasmaFractal_HeightMap( Map, x1, y1, x2, y2 );
			}
		}
		// -- Square -- //
		for ( int y = 0; y < YSteps; y++ ) {
			for ( int x = 0; x < XSteps; x++ ) {
				int x1 = W * x;
				int y1 = H * y;
				int x2 = W * (x+1);
				int y2 = H * (y+1);
				_square_PlasmaFractal_HeightMap( Map, x1, y1, x2, y2 );
			}
		}
		
		W >>= 1;
		H >>= 1;

		XSteps <<= 1;
		YSteps <<= 1;
	}

	return Map;
}
// - ------------------------------------------------------------------------------------------ - //