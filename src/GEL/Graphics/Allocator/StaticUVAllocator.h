// - ------------------------------------------------------------------------------------------ - //
#ifndef __StaticUVAllocator_H__
#define __StaticUVAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Types/UVSet.h>
#include <Graphics/GelUV.h>
// - ------------------------------------------------------------------------------------------ - //
#include "StaticAllocator.h"
// - ------------------------------------------------------------------------------------------ - //
template< const int MaxSize >
class StaticUVAllocator: public StaticAllocator<UVSet<GelUV>,MaxSize> {
public:
	inline StaticUVAllocator()
	{
	}
	
	inline StaticUVAllocator( const int Start ) :
		StaticAllocator<UVSet<GelUV>,MaxSize>( Start )
	{
	}
public:
	inline const int AddMany( const GelUV* Src, const int Count ) {
		int OldSize = StaticAllocator<UVSet<GelUV>,MaxSize>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			StaticAllocator<UVSet<GelUV>,MaxSize>::Data[ StaticAllocator<UVSet<GelUV>,MaxSize>::_Size + idx ].u = Src[(idx<<1)+0];
			StaticAllocator<UVSet<GelUV>,MaxSize>::Data[ StaticAllocator<UVSet<GelUV>,MaxSize>::_Size + idx ].v = Src[(idx<<1)+1];
		}

		StaticAllocator<UVSet<GelUV>,MaxSize>::_Size += Count;

		return OldSize;
	}


	inline void AddRect6( GelUV U1, GelUV V1, GelUV U2, GelUV V2 ) {
		UVSet<GelUV>* VP = &StaticAllocator<UVSet<GelUV>,MaxSize>::Data[ StaticAllocator<UVSet<GelUV>,MaxSize>::_Size ];
		
		VP[0] = UVSet<GelUV>( U1, V1 );
		VP[1] = UVSet<GelUV>( U2, V1 );
		VP[2] = UVSet<GelUV>( U1, V2 );
		VP[3] = UVSet<GelUV>( U2, V1 );
		VP[4] = UVSet<GelUV>( U1, V2 );
		VP[5] = UVSet<GelUV>( U2, V2 );		
		
		StaticAllocator<UVSet<GelUV>,MaxSize>::_Size += 6;
	}


	inline void AddQuad6( const GelUV* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[2], 3 );
	}

	inline void AddQuad6( const UVSet<GelUV>* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[1], 3 );
	}


	inline void AddQuad4( const GelUV* Src ) {
		AddMany( &Src[0], 4 );
	}

	inline void AddQuad4( const UVSet<GelUV>* Src ) {
		AddMany( &Src[0], 4 );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __StaticUVAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
