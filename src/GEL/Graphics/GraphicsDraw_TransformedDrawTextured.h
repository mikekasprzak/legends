// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_TransformedDrawTextured_H__
#define __GEL_GraphicsDraw_TransformedDrawTextured_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GraphicsDraw_DrawTextured.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Change allocation scheme //
// - ------------------------------------------------------------------------------------------ - //
inline void gelTransformedDrawTextured( const int Mode, const Vector2D* Vertex, const UVType* UV, const size_t VertexCount, const Vector2D& Offset, const Vector2D& Scale = Vector2D::One ) {
#ifdef _MSC_VER
	float* Verts = (float*)_malloca( sizeof(float) * (VertexCount << 1) );
#else // _MSC_VER //
	float Verts[ VertexCount << 2 ];
#endif // _MSC_VER //
		
	for ( size_t idx = 0; idx < VertexCount; idx++ ) {
		Verts[0+(idx<<1)] = (float)Offset.x + (Vertex[idx].x * Scale.x);
		Verts[1+(idx<<1)] = (float)Offset.y + (Vertex[idx].y * Scale.y);
	}
		
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( Mode, (Vector2D*)Verts, UV, VertexCount );
#endif // GELS_DRAW_TEXTURED //

#ifdef _MSC_VER
	_freea( Verts );
#endif // _MSC_VER //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelTransformedDrawTextured( const int Mode, const Vector2D* Verts, const UVType* UV, const size_t VertexCount, const Vector2D& Offset, const Real& Scale ) {
	gelTransformedDrawTextured( Mode, Verts, UV, VertexCount, Offset, Vector2D(Scale,Scale) );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelTransformedDrawTextured( const int Mode, const Vector3D* Vertex, const UVType* UV, const size_t VertexCount, const Vector3D& Offset, const Vector3D& Scale = Vector3D::One ) {
#ifdef _MSC_VER
	float* Verts = (float*)_malloca( sizeof(float) * (VertexCount * 3) );
#else // _MSC_VER //
	float Verts[ VertexCount * 3 ];
#endif // _MSC_VER //
		
	for ( size_t idx = 0; idx < VertexCount; idx++ ) {
		Verts[0+(idx*3)] = (float)Offset.x + (Vertex[idx].x * Scale.x);
		Verts[1+(idx*3)] = (float)Offset.y + (Vertex[idx].y * Scale.y);
		Verts[2+(idx*3)] = (float)Offset.z + (Vertex[idx].z * Scale.z);
	}
		
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( Mode, (Vector3D*)Verts, UV, VertexCount );
#endif // GELS_DRAW_TEXTURED //

#ifdef _MSC_VER
	_freea( Verts );
#endif // _MSC_VER //
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelTransformedDrawTextured( const int Mode, const Vector3D* Verts, const UVType* UV, const size_t VertexCount, const Vector3D& Offset, const Real& Scale ) {
	gelTransformedDrawTextured( Mode, Verts, UV, VertexCount, Offset, Vector3D(Scale,Scale,Scale) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_TransformedDrawTextured_H__ //
// - ------------------------------------------------------------------------------------------ - //
