// - ------------------------------------------------------------------------------------------ - //
#ifndef __StaticUVAllocator_H__
#define __StaticUVAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Types/UVSet.h>
#include <Graphics/UV.h>
// - ------------------------------------------------------------------------------------------ - //
#include "StaticAllocator.h"
// - ------------------------------------------------------------------------------------------ - //
template< const int MaxSize >
class StaticUVAllocator: public StaticAllocator<UVSet<UVType>,MaxSize> {
public:
	inline StaticUVAllocator()
	{
	}
	
	inline StaticUVAllocator( const int Start ) :
		StaticAllocator<UVSet<UVType>,MaxSize>( Start )
	{
	}
public:
	inline const int AddMany( const UVType* Src, const int Count ) {
		int OldSize = StaticAllocator<UVSet<UVType>,MaxSize>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			StaticAllocator<UVSet<UVType>,MaxSize>::Data[ StaticAllocator<UVSet<UVType>,MaxSize>::_Size + idx ].u = Src[(idx<<1)+0];
			StaticAllocator<UVSet<UVType>,MaxSize>::Data[ StaticAllocator<UVSet<UVType>,MaxSize>::_Size + idx ].v = Src[(idx<<1)+1];
		}

		StaticAllocator<UVSet<UVType>,MaxSize>::_Size += Count;

		return OldSize;
	}


	inline void AddRect6( UVType U1, UVType V1, UVType U2, UVType V2 ) {
		UVSet<UVType>* VP = &StaticAllocator<UVSet<UVType>,MaxSize>::Data[ StaticAllocator<UVSet<UVType>,MaxSize>::_Size ];
		
		VP[0] = UVSet<UVType>( U1, V1 );
		VP[1] = UVSet<UVType>( U2, V1 );
		VP[2] = UVSet<UVType>( U1, V2 );
		VP[3] = UVSet<UVType>( U2, V1 );
		VP[4] = UVSet<UVType>( U1, V2 );
		VP[5] = UVSet<UVType>( U2, V2 );		
		
		StaticAllocator<UVSet<UVType>,MaxSize>::_Size += 6;
	}


	inline void AddQuad6( const UVType* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[2], 3 );
	}

	inline void AddQuad6( const UVSet<UVType>* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[1], 3 );
	}


	inline void AddQuad4( const UVType* Src ) {
		AddMany( &Src[0], 4 );
	}

	inline void AddQuad4( const UVSet<UVType>* Src ) {
		AddMany( &Src[0], 4 );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __StaticUVAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
