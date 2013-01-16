// - ------------------------------------------------------------------------------------------ - //
#ifndef __Grid_Grid2D_HeightMap_H__
#define __Grid_Grid2D_HeightMap_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Grid2D_Class.h"
// - ------------------------------------------------------------------------------------------ - //
// The Diamond-Square algorithm (Midpoint Displacement, Cloud/Plasma Fractal) -- Powers of Two //
cGrid2D<int> generate_PlasmaFractal_HeightMapInt( const size_t Width, const size_t Height );
cGrid2D<float> generate_PlasmaFractal_HeightMapFloat( const size_t Width, const size_t Height );
// - ------------------------------------------------------------------------------------------ - //
#endif // __Grid_Grid2D_HeightMap_H__ //
// - ------------------------------------------------------------------------------------------ - //
