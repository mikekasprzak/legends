// - ------------------------------------------------------------------------------------------ - //
#ifndef __Vector2DAllocator_H__
#define __Vector2DAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
#include "Allocator.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class Vector2DAllocator: public Allocator<Vector2D> {
public:
//	inline Vector2DAllocator()
//	{
//	}
	
	inline Vector2DAllocator( const int MaxSize, const int Start = 0 ) :
		Allocator<Vector2D>( MaxSize, Start )
	{
	}
public:
	inline const int AddMany( const int Count ) {
		int OldSize = Allocator<Vector2D>::_Size;
		Allocator<Vector2D>::_Size += Count;

		return OldSize;
	}

	inline const int AddMany( const float* Src, const int Count ) {
		int OldSize = Allocator<Vector2D>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].x = Src[(idx<<1)+0];
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].y = Src[(idx<<1)+1];
		}

		Allocator<Vector2D>::_Size += Count;

		return OldSize;
	}

	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos ) {
		int OldSize = Allocator<Vector2D>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].x = Src[(idx<<1)+0] + Pos.x;
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].y = Src[(idx<<1)+1] + Pos.y;
		}

		Allocator<Vector2D>::_Size += Count;

		return OldSize;
	}

	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos, const Real Scale ) {
		int OldSize = Allocator<Vector2D>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].x = (Src[(idx<<1)+0]*Scale) + Pos.x;
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].y = (Src[(idx<<1)+1]*Scale) + Pos.y;
		}

		Allocator<Vector2D>::_Size += Count;

		return OldSize;
	}
	
	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos, const Vector2D& Scale ) {
		int OldSize = Allocator<Vector2D>::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].x = (Src[(idx<<1)+0]*Scale.x) + Pos.x;
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ].y = (Src[(idx<<1)+1]*Scale.y) + Pos.y;
		}

		Allocator<Vector2D>::_Size += Count;

		return OldSize;
	}
	
	inline const int AddMany( const float* Src, const int Count, const Vector2D& Pos, const Matrix2x2& Scale ) {
		int OldSize = Allocator<Vector2D>::_Size;
			
		Vector2D PosVector;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			PosVector = Vector2D( Src[(idx<<1)+0], Src[(idx<<1)+1] );
			PosVector = PosVector.ApplyMatrix( Scale );
			PosVector += Pos;
			
			Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size + idx ] = PosVector;
		}

		Allocator<Vector2D>::_Size += Count;

		return OldSize;
	}

	inline void AddRect6( Vector2D& P1, Vector2D P2 ) {
		Vector2D* VP = &Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size ];
		
		VP[0] = Vector2D( P1.x, P1.y );
		VP[1] = Vector2D( P2.x, P1.y );
		VP[2] = Vector2D( P1.x, P2.y );
		VP[3] = Vector2D( P2.x, P1.y );
		VP[4] = Vector2D( P1.x, P2.y );
		VP[5] = Vector2D( P2.x, P2.y );
		
		Allocator<Vector2D>::_Size += 6;
	}

	inline void AddRect6( Vector2D& P1, Vector2D P2, Vector2D Pos, Real Angle ) {
		Vector2D* VP = &Allocator<Vector2D>::Data[ Allocator<Vector2D>::_Size ];
		
		VP[0] = Vector2D( P1.x, P1.y );
		VP[1] = Vector2D( P2.x, P1.y );
		VP[2] = Vector2D( P1.x, P2.y );
		VP[3] = Vector2D( P2.x, P1.y );
		VP[4] = Vector2D( P1.x, P2.y );
		VP[5] = Vector2D( P2.x, P2.y );

		Matrix2x2 Rotation = Matrix2x2::RotationMatrix( Angle );
		
		VP[0] = VP[0].ApplyMatrix(Rotation) + Pos;
		VP[1] = VP[1].ApplyMatrix(Rotation) + Pos;
		VP[2] = VP[2].ApplyMatrix(Rotation) + Pos;
		VP[3] = VP[3].ApplyMatrix(Rotation) + Pos;
		VP[4] = VP[4].ApplyMatrix(Rotation) + Pos;
		VP[5] = VP[5].ApplyMatrix(Rotation) + Pos;
			
		Allocator<Vector2D>::_Size += 6;
	}
	

	inline void AddQuad6( const float* Src, const Vector2D& Pos ) {
		AddMany( &Src[0], 3, Pos );
		AddMany( &Src[2], 3, Pos );
	}

	inline void AddQuad6( const Vector2D* Src, const Vector2D& Pos ) {
		AddMany( (float*)&Src[0], 3, Pos );
		AddMany( (float*)&Src[1], 3, Pos );
	}

	inline void AddQuad6( const float* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[2], 3, Pos, Scale );
	}

	inline void AddQuad6( const Vector2D* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( (float*)&Src[0], 3, Pos, Scale );
		AddMany( (float*)&Src[1], 3, Pos, Scale );
	}

	inline void AddQuad6( const float* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[2], 3, Pos, Scale );
	}

	inline void AddQuad6( const Vector2D* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( (float*)&Src[0], 3, Pos, Scale );
		AddMany( (float*)&Src[1], 3, Pos, Scale );
	}

	inline void AddQuad6( const float* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( &Src[0], 3, Pos, Scale );
		AddMany( &Src[2], 3, Pos, Scale );
	}

	inline void AddQuad6( const Vector2D* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( (float*)&Src[0], 3, Pos, Scale );
		AddMany( (float*)&Src[1], 3, Pos, Scale );
	}


	inline void AddQuad4( const float* Src, const Vector2D& Pos ) {
		AddMany( &Src[0], 4, Pos );
	}

	inline void AddQuad4( const Vector2D* Src, const Vector2D& Pos ) {
		AddMany( (float*)&Src[0], 4, Pos );
	}

	inline void AddQuad4( const float* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline void AddQuad4( const Vector2D* Src, const Vector2D& Pos, const Real Scale ) {
		AddMany( (float*)&Src[0], 4, Pos, Scale );
	}

	inline void AddQuad4( const float* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline void AddQuad4( const Vector2D* Src, const Vector2D& Pos, const Vector2D& Scale ) {
		AddMany( (float*)&Src[0], 4, Pos, Scale );
	}

	inline void AddQuad4( const float* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( &Src[0], 4, Pos, Scale );
	}

	inline void AddQuad4( const Vector2D* Src, const Vector2D& Pos, const Matrix2x2& Scale ) {
		AddMany( (float*)&Src[0], 4, Pos, Scale );
	}

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Vector2DAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
