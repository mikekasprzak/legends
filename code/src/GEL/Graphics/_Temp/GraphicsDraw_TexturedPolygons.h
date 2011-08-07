// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_TexturedPolygons_H__
#define __GraphicsDraw_TexturedPolygons_H__
// - ------------------------------------------------------------------------------------------ - //
#include "UV.h"
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawTexturedPolygon( const float* Vertex, const GelUV* UV, const size_t VertexCount, const Vector2D& Offset ) {
    glEnable(GL_TEXTURE_2D);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	{
#ifdef _MSC_VER
		float* Verts = (float*)_malloca( sizeof(float) * (VertexCount << 1) );
//		float* Verts = new float[ VertexCount << 1 ];
#else // _MSC_VER //
		float Verts[ VertexCount << 1 ];
#endif // _MSC_VER //

		for ( size_t idx = 0; idx < VertexCount; idx++ ) {
			Verts[0+(idx<<1)] = (float)Offset.x + Vertex[0+(idx<<1)];
			Verts[1+(idx<<1)] = (float)Offset.y + Vertex[1+(idx<<1)];
		}
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UV);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);

#ifdef _MSC_VER
		_freea( Verts );
//		delete [] Verts;
#endif // _MSC_VER //
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawTexturedPolygon( const Vector2D* Vertex, const GelUV* UV, const size_t VertexCount, const Vector2D& Offset ) {
	gelDrawTexturedPolygon( (const float*)Vertex, UV, VertexCount, Offset );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawScaledTexturedPolygon( const float* Vertex, const GelUV* UV, const size_t VertexCount, const Vector2D& Offset, const float Scale ) {
    glEnable(GL_TEXTURE_2D);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	{
#ifdef _MSC_VER
		float* Verts = (float*)_malloca( sizeof(float) * (VertexCount << 1) );
//		float* Verts = new float[ VertexCount << 1 ];
#else // _MSC_VER //
		float Verts[ VertexCount << 1 ];
#endif // _MSC_VER //
		
		for ( size_t idx = 0; idx < VertexCount; idx++ ) {
			Verts[0+(idx<<1)] = (float)Offset.x + (Vertex[0+(idx<<1)] * Scale);
			Verts[1+(idx<<1)] = (float)Offset.y + (Vertex[1+(idx<<1)] * Scale);
		}
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UV);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);

#ifdef _MSC_VER
		_freea( Verts );
//		delete [] Verts;
#endif // _MSC_VER //
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawScaledTexturedPolygon( const Vector2D* Vertex, const GelUV* UV, const size_t VertexCount, const Vector2D& Offset, const float Scale ) {
	gelDrawScaledTexturedPolygon( (const float*)Vertex, UV, VertexCount, Offset, Scale );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawScaledTexturedPolygon( const float* Vertex, const GelUV* UV, const size_t VertexCount, const Vector2D& Offset, const Vector2D& Scale ) {
    glEnable(GL_TEXTURE_2D);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	{
#ifdef _MSC_VER
		float* Verts = (float*)_malloca( sizeof(float) * (VertexCount << 1) );
//		float* Verts = new float[ VertexCount << 1 ];
#else // _MSC_VER //
		float Verts[ VertexCount << 1 ];
#endif // _MSC_VER //
		
		for ( size_t idx = 0; idx < VertexCount; idx++ ) {
			Verts[0+(idx<<1)] = (float)Offset.x + (Vertex[0+(idx<<1)] * Scale.x);
			Verts[1+(idx<<1)] = (float)Offset.y + (Vertex[1+(idx<<1)] * Scale.y);
		}
		
		glVertexPointer(2, GL_FLOAT, 0, Verts);
		glTexCoordPointer(2, GL_UVType, 0, UV);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);

#ifdef _MSC_VER
		_freea( Verts );
//		delete [] Verts;
#endif // _MSC_VER //
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawScaledTexturedPolygon( const Vector2D* Vertex, const GelUV* UV, const size_t VertexCount, const Vector2D& Offset, const Vector2D& Scale ) {
	gelDrawScaledTexturedPolygon( (const float*)Vertex, UV, VertexCount, Offset, Scale );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawTexturedPolygons( const float* Vertex, const GelUV* UV, const size_t VertexCount ) {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glTexCoordPointer(2, GL_UVType, 0, UV);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawTexturedIndexedPolygons( const float* Vertex, const GelUV* UV, const size_t VertexCount, const unsigned short* Indexes, const size_t IndexCount ) {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glTexCoordPointer(2, GL_UVType, 0, UV);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_SHORT, Indexes);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDisable(GL_TEXTURE_2D);	
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawTexturedIndexedPolygons( const float* Vertex, const GelUV* UV, const unsigned int* Colors, const size_t VertexCount, const unsigned short* Indexes, const size_t IndexCount ) {
	glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glTexCoordPointer(2, GL_UVType, 0, UV);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, Colors);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_SHORT, Indexes);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glDisable(GL_TEXTURE_2D);
	gelApplyColor( Current::Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawColoredPolygons( const float* Vertex, const unsigned int* Colors, const size_t VertexCount ) {
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, Colors);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
	
	glDisableClientState(GL_COLOR_ARRAY);
	
	gelApplyColor( Current::Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawPolygons( const float* Vertex, const size_t VertexCount ) {
	glVertexPointer(2, GL_FLOAT, 0, Vertex);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_TexturedPolygons_H__ //
// - ------------------------------------------------------------------------------------------ - //
