// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFESYSTEM_WORLD_H__
#define __LIFESYSTEM_WORLD_H__
// - ------------------------------------------------------------------------------------------ - //
// World -- 
// - ------------------------------------------------------------------------------------------ - //
//#include <Math/Real.h>
#include <Grid/Grid2D_Class.h>
#include "Tile.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeSystem {
// - ------------------------------------------------------------------------------------------ - //
class cWorld {
public:
	cGrid2D<cTile> Map;
	int Iteration;
	
public:
	cWorld() :
		Map(2,2)
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeSystem //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFESYSTEM_WORLD_H__ //
// - ------------------------------------------------------------------------------------------ - //