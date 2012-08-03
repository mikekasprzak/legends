// - ------------------------------------------------------------------------------------------ - //
#ifndef __FOUNDATION_FdMultiSprite_H__
#define __FOUNDATION_FdMultiSprite_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Allocator/Vector2DAllocator.h>
#include <Graphics/Allocator/UVAllocator.h>
// - ------------------------------------------------------------------------------------------ - //
class cFdMultiSprite {
public:
	Vector2DAllocator Vert;
	UVAllocator UV;

public:
	inline cFdMultiSprite( const size_t Count ) :
		Vert( Count * (3*2) ),
		UV( Count * (3*2) )
	{
	}

public:
	inline void AddRect( const Vector2D& P1, const Vector2D& P2, const Vector2D& UV1, const Vector2D& UV2 ) {
		// Add Vertices //
		Vert.AddRect6( P1, P2 );			
		// Add UV's //
		UV.AddRect6( UV1, UV2 );		
	} 

public:
	inline void Draw() {
		gelDrawTexturedPolygons(
			(float*)Vert.Get(),
			(GelUV*)UV.Get(),
			Vert.Size()
			);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __FOUNDATION_FdMultiSprite_H__ //
// - ------------------------------------------------------------------------------------------ - //
