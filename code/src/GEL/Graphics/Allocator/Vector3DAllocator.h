// - ------------------------------------------------------------------------------------------ - //
#ifndef __Vector3DAllocator_H__
#define __Vector3DAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector3D.h>
#include "Allocator.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class Vector3DAllocator: public Allocator<Vector3D> {
public:
	inline Vector3DAllocator( const int MaxSize, const int Start = 0 ) :
		Allocator<Vector3D>( MaxSize, Start )
	{
	}
public:
	inline const int AddMany( const int Count ) {
		int OldSize = Allocator<Vector3D>::_Size;
		Allocator<Vector3D>::_Size += Count;

		return OldSize;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Vector3DAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
