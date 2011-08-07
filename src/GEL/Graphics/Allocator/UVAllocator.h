// - ------------------------------------------------------------------------------------------ - //
#ifndef __UVAllocator_H__
#define __UVAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Types/UVSet.h>
#include <Graphics/GelUV.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class UVAllocator: public Allocator< UVSet<GelUV> > {
public:
//	inline UVAllocator()
//	{
//	}
	
	inline UVAllocator( const int MaxSize, const int Start = 0 ) :
		Allocator< UVSet<GelUV> >( MaxSize, Start )
	{
	}
public:
	inline const int AddMany( const GelUV* Src, const int Count ) {
		int OldSize = Allocator< UVSet<GelUV> >::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator< UVSet<GelUV> >::Data[ Allocator< UVSet<GelUV> >::_Size + idx ].u = Src[(idx<<1)+0];
			Allocator< UVSet<GelUV> >::Data[ Allocator< UVSet<GelUV> >::_Size + idx ].v = Src[(idx<<1)+1];
		}

		Allocator< UVSet<GelUV> >::_Size += Count;

		return OldSize;
	}


	inline void AddRect6( GelUV U1, GelUV V1, GelUV U2, GelUV V2 ) {
		UVSet<GelUV>* VP = &Allocator< UVSet<GelUV> >::Data[ Allocator< UVSet<GelUV> >::_Size ];
		
		VP[0] = UVSet<GelUV>( U1, V1 );
		VP[1] = UVSet<GelUV>( U2, V1 );
		VP[2] = UVSet<GelUV>( U1, V2 );
		VP[3] = UVSet<GelUV>( U2, V1 );
		VP[4] = UVSet<GelUV>( U1, V2 );
		VP[5] = UVSet<GelUV>( U2, V2 );		
		
		Allocator< UVSet<GelUV> >::_Size += 6;
	}


	inline void AddQuad6( const GelUV* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[2], 3 );
	}

	inline void AddQuad6( const UVSet<GelUV>* Src ) {
		AddMany( (GelUV*)&Src[0], 3 );
		AddMany( (GelUV*)&Src[1], 3 );
	}


	inline void AddQuad4( const GelUV* Src ) {
		AddMany( &Src[0], 4 );
	}

	inline void AddQuad4( const UVSet<GelUV>* Src ) {
		AddMany( (GelUV*)&Src[0], 4 );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __UVAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
