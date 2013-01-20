// - ------------------------------------------------------------------------------------------ - //
#ifndef __Grid_Data2D_Geometry_H__
#define __Grid_Data2D_Geometry_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>
#include "Data2D_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Optimized_TriangleStrips are ordered in cache friendly columns (Y) //
// Even columns cache, odd columns miss, but that's still better than not caching at all. //
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void calculate_OptimizedVertexes_Triangles( Data2D<tType>* Data, size_t* VertexCount ) {
	*VertexCount = Data->Size();
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void calculate_OptimizedVertexes_TriangleStrips( Data2D<tType>* Data, size_t* VertexCount ) {
	*VertexCount = Data->Size();
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void calculate_OptimizedIndexes_Triangles( Data2D<tType>* Data, size_t* IndexCount ) {
	*IndexCount = (Data->Height() - 1) * (Data->Width() - 1) * (3+3);
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void calculate_OptimizedIndexes_TriangleStrips( Data2D<tType>* Data, size_t* IndexCount, const bool PrimitiveRestart = false ) {
	// If using primitive-restart, degenerates are 1 vertex (special code -1), otherwise 2 //
	if ( PrimitiveRestart ) {
		// Primitive Restart Command //
		*IndexCount = (((Data->Height()*2)+1) * (Data->Width()-1)) - 1;
	}
	else {
		// Degenerate Triangles //
		*IndexCount = (((Data->Height()*2)+2) * (Data->Width()-1)) - 2;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void calculate_Optimized_Triangles( Data2D<tType>* Data, size_t* VertexCount, size_t* IndexCount ) {
	calculate_OptimizedVertexes_Triangles( Data, VertexCount );
	calculate_OptimizedIndexes_Triangles( Data, IndexCount );
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void calculate_Optimized_TriangleStrips( Data2D<tType>* Data, size_t* VertexCount, size_t* IndexCount, const bool PrimitiveRestart = false ) {
	calculate_OptimizedVertexes_TriangleStrips( Data, VertexCount );
	calculate_OptimizedIndexes_TriangleStrips( Data, IndexCount, PrimitiveRestart );
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType, class tType >
inline void generate_OptimizedVertexes_Triangles( Data2D<tType>* Data, VertType* Vertex, const Vector3D Scale = Vector3D(1,1,1) ) {
	// Generate Vertices (-1 to +1) //
	const Real WScalar = Real(2) / Real(Data->Width() - 1);
	const Real HScalar = Real(2) / Real(Data->Height() - 1);
	
	for ( int w = 0; w < Data->Width(); w++ ) {
		for ( int h = 0; h < Data->Height(); h++ ) {
			*((Vector3D*)Vertex) = Vector3D( (Real(w) * WScalar) - Real::One, (Real(h) * HScalar) - Real::One, Real(Data->Index(w,h)) / Real(MaxValue<tType>()) );
			*((Vector3D*)Vertex) = ((Vector3D*)Vertex)->Scale(Scale);
			Vertex++;
//			*((Vector3D*)Vertex) = Vector3D( (Real(w+1) * WScalar) - Real::One, (Real(h) * HScalar) - Real::One, Real(Data->Index(w+1,h)) / Real(MaxValue<tType>()) );
//			*((Vector3D*)Vertex) = ((Vector3D*)Vertex)->Scale(Scale);
//			Vertex++;
//			*((Vector3D*)Vertex) = Vector3D( (Real(w) * WScalar) - Real::One, (Real(h+1) * HScalar) - Real::One, Real(Data->Index(w,h+1)) / Real(MaxValue<tType>()) );
//			*((Vector3D*)Vertex) = ((Vector3D*)Vertex)->Scale(Scale);
//			Vertex++;
//			*((Vector3D*)Vertex) = Vector3D( (Real(w+1) * WScalar) - Real::One, (Real(h+1) * HScalar) - Real::One, Real(Data->Index(w+1,h+1)) / Real(MaxValue<tType>()) );
//			*((Vector3D*)Vertex) = ((Vector3D*)Vertex)->Scale(Scale);
//			Vertex++;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType, class tType >
inline void generate_OptimizedVertexes_TriangleStrips( Data2D<tType>* Data, VertType* Vertex, const Vector3D Scale = Vector3D(1,1,1) ) {
	// Generate Vertices (two rows at a time, for cache) //
	size_t Rows = Data->Width() - 1;
	const Real WScalar = Real(2) / Real(Rows);
	const Real HScalar = Real(2) / Real(Data->Height() - 1);
	
	for ( int w = 0; w < Rows; w+=2 ) {
		for ( int h = 0; h < Data->Height(); h++ ) {
			*((Vector3D*)Vertex) = Vector3D( (Real(w) * WScalar) - Real::One, (Real(h) * HScalar) - Real::One, Real(Data->Index(w,h)) / Real(MaxValue<tType>()) );
			// This is a function. It returns a value scaled up. //
			*((Vector3D*)Vertex) = ((Vector3D*)Vertex)->Scale(Scale);
			Vertex++;
			*((Vector3D*)Vertex) = Vector3D( (Real(w+1) * WScalar) - Real::One, (Real(h) * HScalar) - Real::One, Real(Data->Index(w+1,h)) / Real(MaxValue<tType>()) );
			// This is a function. It returns a value scaled up. //
			*((Vector3D*)Vertex) = ((Vector3D*)Vertex)->Scale(Scale);
			Vertex++;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void generate_OptimizedIndexes_Triangles( Data2D<tType>* Data, unsigned short* Index ) {
	const size_t Rows = Data->Width();
	const size_t Column = Data->Height();
	size_t IndexValue = 0;
	for ( int w = 0; w < Rows-1; w++ ) {		
		for ( int h = 0; h < Column-1; h++ ) {
			// Add whatever the inner loop type is to the values, for correct offsetting //
			*(Index++) = IndexValue;
			*(Index++) = IndexValue+Column;
			*(Index++) = IndexValue+1;
			
			*(Index++) = IndexValue+Column;
			*(Index++) = IndexValue+Column+1;
			*(Index++) = IndexValue+1;
			
			IndexValue += 1;
		}
		IndexValue += 1;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline void generate_OptimizedIndexes_TriangleStrips( Data2D<tType>* Data, unsigned short* Index, const bool PrimitiveRestart = false ) {
	const size_t Rows = Data->Width() - 1;
	size_t IndexValue = 0;
	size_t OddValueA;
	size_t OddValueB;
	for ( int w = 0; w < Rows; w++ ) {		
		// Even Field //
		if ( (w & 1) == 0 ) {
			for ( int h = 0; h < Data->Height(); h++ ) {
				*(Index++) = IndexValue++;
				*(Index++) = IndexValue++;
			}

			if ( w+1 != Rows ) {
				// Write Degenerate //
				if ( PrimitiveRestart ) {
					*(Index++) = 0xFFFF;
				}
				else {
					*(Index++) = IndexValue - 1;
					*(Index++) = IndexValue + 1 - (Data->Height()<<1);
				}
			}
		}
		// Odd Field //
		else {
			OddValueA = IndexValue + 1 - (Data->Height()<<1);
			OddValueB = IndexValue;
			
			for ( int h = 0; h < Data->Height(); h++ ) {
				*(Index++) = OddValueA;
				OddValueA += 2;
				*(Index++) = OddValueB;
				OddValueB += 2;
			}

			// Not needed, will always end on an even boundary //
			if ( w+1 != Rows ) {
				// Write Degenerate //
				if ( PrimitiveRestart ) {
					*(Index++) = 0xFFFF;
				}
				else {
					*(Index++) = OddValueB - 2;
					*(Index++) = IndexValue;
				}			
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// WARNING! Width must be even! //
template< class VertType, class tType >
inline void generate_Optimized_Triangles( Data2D<tType>* Data, VertType* Vertex, unsigned short* Index, const Vector3D Scale = Vector3D(1,1,1) ) {
	generate_OptimizedVertexes_Triangles( Data, Vertex, Scale );
	generate_OptimizedIndexes_Triangles( Data, Index  );
}
// - ------------------------------------------------------------------------------------------ - //
// WARNING! Width must be even! //
template< class VertType, class tType >
inline void generate_Optimized_TriangleStrips( Data2D<tType>* Data, VertType* Vertex, unsigned short* Index, const Vector3D Scale = Vector3D(1,1,1), const bool PrimitiveRestart = false ) {
	generate_OptimizedVertexes_TriangleStrips( Data, Vertex, Scale );
	generate_OptimizedIndexes_TriangleStrips( Data, Index, PrimitiveRestart );
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType, class tType >
inline void new_Optimized_TriangleStrips( Data2D<tType>* Data, GelArray<VertType>** Vertex, GelArray<unsigned short>** Index, const Vector3D Scale = Vector3D(1,1,1), const bool PrimitiveRestart = false ) {
	size_t VertexCount;
	size_t IndexCount;
	calculate_Optimized_TriangleStrips( Data, &VertexCount, &IndexCount, PrimitiveRestart );

	*Vertex = new_GelArray<VertType>(VertexCount);
	*Index = new_GelArray<unsigned short>(IndexCount);
	
	generate_Optimized_TriangleStrips( Data, (*Vertex)->Data, (*Index)->Data, Scale, PrimitiveRestart );
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType, class tType >
inline void new_Optimized_Triangles( Data2D<tType>* Data, GelArray<VertType>** Vertex, GelArray<unsigned short>** Index, const Vector3D Scale = Vector3D(1,1,1) ) {
	size_t VertexCount;
	size_t IndexCount;
	calculate_Optimized_Triangles( Data, &VertexCount, &IndexCount );

	*Vertex = new_GelArray<VertType>(VertexCount);
	*Index = new_GelArray<unsigned short>(IndexCount);
	
	generate_Optimized_Triangles( Data, (*Vertex)->Data, (*Index)->Data, Scale );
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void delete_Triangles( GelArray<VertType>* Vertex, GelArray<unsigned short>* Index ) {
	delete_GelArray( Vertex );
	delete_GelArray( Index );	
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void delete_TriangleStrips( GelArray<VertType>* Vertex, GelArray<unsigned short>* Index ) {
	delete_GelArray( Vertex );
	delete_GelArray( Index );	
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t indexVertex_Optimized_TriangleStrips( const size_t Height, const size_t x, const size_t y ) {
	return ((y<<1) + (x&1)) + (((x>>1) * Height)<<1);
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline const size_t indexVertex_Optimized_TriangleStrips( Data2D<tType>* Data, const size_t x, const size_t y ) {
	return indexVertex_Optimized_TriangleStrips(Data->Height(),x,y);
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t indexStripSize_Optimized_TriangleStrips( const size_t Height ) {
	return (Height<<1);
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline const size_t indexStripSize_Optimized_TriangleStrips( Data2D<tType>* Data ) {
	return indexStripSize_Optimized_TriangleStrips(Data->Height());
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t indexStripCount_Optimized_TriangleStrips( const size_t Width ) {
	return Width-1;
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline const size_t indexStripCount_Optimized_TriangleStrips( Data2D<tType>* Data ) {
	return indexStripCount_Optimized_TriangleStrips(Data->Width());
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t indexIndex_Optimized_TriangleStrips( const size_t Height, const size_t Strip, const size_t Index, const bool PrimitiveRestart = false ) {
	if ( PrimitiveRestart )
		return Index + ((indexStripSize_Optimized_TriangleStrips(Height)+1)*Strip);
	else
		return Index + ((indexStripSize_Optimized_TriangleStrips(Height)+2)*Strip);
}
// - ------------------------------------------------------------------------------------------ - //
template< class tType >
inline const size_t indexIndex_Optimized_TriangleStrips( Data2D<tType>* Data, const size_t Strip, const size_t Index, const bool PrimitiveRestart = false ) {
	return indexIndex_Optimized_TriangleStrips(Data->Height(),Strip,Index,PrimitiveRestart);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline unsigned int count_PrimitiveRestarts( GelArray<unsigned short>* Index ) {
	unsigned int Count = 0;
	for( size_t idx = 0; idx < Index->Size; idx++ ) {
		if ( Index->Data[idx] == 0xFFFF )
			Count++;
	}
	return Count;
}
// - ------------------------------------------------------------------------------------------ - //
inline unsigned int count_DegenerateTriangles( GelArray<unsigned short>* Index ) {
	unsigned int Count = 0;
	for( size_t idx = 0; idx < Index->Size-3; idx++ ) {
		if ( Index->Data[idx] == Index->Data[idx+1] ) {
			Count++;
			idx+=3;
		}
		else if ( Index->Data[idx+1] == Index->Data[idx+2] ) {
			Count++;
			idx+=3;
		}
	}
	return Count;
}
// - ------------------------------------------------------------------------------------------ - //
inline unsigned int count_Triangles_Triangles( GelArray<unsigned short>* Index ) {
	return Index->Size / 3;
}
// - ------------------------------------------------------------------------------------------ - //
inline unsigned int count_Triangles_TriangleStrip( GelArray<unsigned short>* Index, const bool PrimitiveRestart = false ) {
	unsigned int Count = 0;
	
	for( size_t idx = 2; idx < Index->Size; idx++ ) {
		if ( PrimitiveRestart ) {
			if ( Index->Data[idx] == 0xFFFF )
				continue;
		}
		else {
			// So we don't go out of bounds //
			if ( idx < Index->Size-2 ) {
				if ( Index->Data[idx] == Index->Data[idx+1] ) {
					idx+=3;
					continue;
				}
				else if ( Index->Data[idx+1] == Index->Data[idx+2] ) {
					idx+=3;
					continue;
				}
			}
		}
		Count++;
	}
	return Count;
}
// - ------------------------------------------------------------------------------------------ - //
// Generate a list of outlines... not a line strip, since I need to jump //
inline void new_Triangles_OutlineList( GelArray<unsigned short>* Index, GelArray<unsigned short>** NewIndex ) {
	unsigned int Triangles = count_Triangles_Triangles( Index );
	Log( "Triangles Found: %i (%i)\n", Triangles, Index->Size );
	
	// This is +2 for a reason... not sure why... something to do with Triangles... rethink the math //
	//*NewIndex = new_GelArray<unsigned short>((Triangles*2)+2);
	*NewIndex = new_GelArray<unsigned short>(((Triangles*2)+2)*3);
	unsigned short* Write = &((*NewIndex)->Data[0]);

//	int Count = 0;

	//for( size_t idx = 0; idx < Index->Size-1; idx++ ) {
	for( size_t idx = 0; idx < Index->Size-2; idx+=6 ) {
//		// So we don't go out of bounds //
//		if ( idx < Index->Size-2 ) {
//			if ( Index->Data[idx] == Index->Data[idx+1] ) {
//				idx+=3;
////				Log("Skip %i (%i)\n",Count,idx);
//				continue;
//			}
//			else if ( Index->Data[idx+1] == Index->Data[idx+2] ) {
//				idx+=3;
////				Log("Skip %i (%i)\n",Count,idx);
//				continue;
//			}
//		}
		
		*(Write++) = Index->Data[idx];
		*(Write++) = Index->Data[idx+1];
		
		*(Write++) = Index->Data[idx];
		*(Write++) = Index->Data[idx+2];
		
		*(Write++) = Index->Data[idx+1];
		*(Write++) = Index->Data[idx+2];

//		Count++;
//		if ( (Count % 100 == 0) || (Count > 7900) )
//			Log("%i (%i)\n",Count,idx);
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Generate a list of outlines... not a line strip, since I need to jump //
inline void new_TriangleStrip_OutlineList( GelArray<unsigned short>* Index, GelArray<unsigned short>** NewIndex, const bool PrimitiveRestart = false ) {
	unsigned int Triangles = count_Triangles_TriangleStrip( Index, PrimitiveRestart );
	Log( "Triangles Found: %i (%i)\n", Triangles, Index->Size );
	
	// This is +2 for a reason... not sure why... something to do with Triangles... rethink the math //
	//*NewIndex = new_GelArray<unsigned short>((Triangles*2)+2);
	*NewIndex = new_GelArray<unsigned short>(((Triangles*2)+2)*2);
	unsigned short* Write = &((*NewIndex)->Data[0]);

//	int Count = 0;

	//for( size_t idx = 0; idx < Index->Size-1; idx++ ) {
	for( size_t idx = 0; idx < Index->Size-2; idx++ ) {
		if ( PrimitiveRestart ) {
			if ( Index->Data[idx] == 0xFFFF ) {
//				Log("Skip %i (%i)\n",Count,idx);
				continue;
			}
		}
		else {
			// So we don't go out of bounds //
			if ( idx < Index->Size-2 ) {
				if ( Index->Data[idx] == Index->Data[idx+1] ) {
					idx+=3;
//					Log("Skip %i (%i)\n",Count,idx);
					continue;
				}
				else if ( Index->Data[idx+1] == Index->Data[idx+2] ) {
					idx+=3;
//					Log("Skip %i (%i)\n",Count,idx);
					continue;
				}
			}
		}
		
		*(Write++) = Index->Data[idx];
		*(Write++) = Index->Data[idx+1];
		*(Write++) = Index->Data[idx];
		*(Write++) = Index->Data[idx+2];
//		Count++;
//		if ( (Count % 100 == 0) || (Count > 7900) )
//			Log("%i (%i)\n",Count,idx);
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_OutlineList( GelArray<unsigned short>* Index ) {
	delete_GelArray( Index );	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Grid_Data2D_Geometry_H__ //
// - ------------------------------------------------------------------------------------------ - //
