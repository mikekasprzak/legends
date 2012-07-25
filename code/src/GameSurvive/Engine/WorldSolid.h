// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLDSOLID_H__
#define __WORLDSOLID_H__
// - ------------------------------------------------------------------------------------------ - //
// Solid's are large things like trees and rocks. //
// - They cannot be carried.
// - They don't have a position. Position is handled by the tiles themselves.
// - They can be interacted with. Harvested from, or destroyed.
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //
class cWorldSolid {
public:
	Real Volume;
public:
	cWorldSolid()
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLDSOLID_H__ //
// - ------------------------------------------------------------------------------------------ - //
