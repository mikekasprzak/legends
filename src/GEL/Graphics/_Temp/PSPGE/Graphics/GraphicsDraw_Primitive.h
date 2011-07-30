// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_Primitive_H__
#define __GEL_GraphicsDraw_Primitive_H__
// - ------------------------------------------------------------------------------------------ - //
// Polygon Batch is a function and class for drawing vertex arrays.  //
// Texturing and specific textures must be enabled/set before calling the batch Drawing functions //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Binary.h>
// - ------------------------------------------------------------------------------------------ - //
#define PRIMITIVE_2D				b00000001
#define PRIMITIVE_3D				b00000010

#define PRIMITIVE_INDEX_MASK		b00001100
#define PRIMITIVE_INDEX_8BIT		b00000100
#define PRIMITIVE_INDEX_16BIT		b00001000
#define PRIMITIVE_INDEX_32BIT		b00001100

#define PRIMITIVE_UV_MASK			b11110000
#define PRIMITIVE_UV_8BIT			b00010000
#define PRIMITIVE_UV_16BIT			b00100000
#define PRIMITIVE_UV_32BIT			b00110000
#define PRIMITIVE_UV_FLOAT			b01000000
#define PRIMITIVE_UV_HALFFLOAT		b01010000
#define PRIMITIVE_UV_FIXED			b01100000			// Not needed? //
#define PRIMITIVE_UV_SYSTEM			b11110000

#define PRIMITIVE_VERTEX_MASK		((b00001111)<<8)
#define PRIMITIVE_VERTEX_8BIT		((b00000001)<<8)
#define PRIMITIVE_VERTEX_16BIT		((b00000010)<<8)
#define PRIMITIVE_VERTEX_32BIT		((b00000011)<<8)
#define PRIMITIVE_VERTEX_FLOAT		((b00000100)<<8)
#define PRIMITIVE_VERTEX_HALFFLOAT	((b00000101)<<8)
#define PRIMITIVE_VERTEX_FIXED		((b00000110)<<8)	// Not needed? //
#define PRIMITIVE_VERTEX_SYSTEM		((b00001111)<<8)

#define PRIMITIVE_NORMAL_MASK		((b11110000)<<8)
#define PRIMITIVE_NORMAL_8BIT		((b00010000)<<8)
#define PRIMITIVE_NORMAL_16BIT		((b00100000)<<8)
#define PRIMITIVE_NORMAL_32BIT		((b00110000)<<8)
#define PRIMITIVE_NORMAL_FLOAT		((b01000000)<<8)
#define PRIMITIVE_NORMAL_HALFFLOAT	((b01010000)<<8)
#define PRIMITIVE_NORMAL_FIXED		((b01100000)<<8) 	// Not needed? //
#define PRIMITIVE_NORMAL_SYSTEM		((b11110000)<<8)
// - ------------------------------------------------------------------------------------------ - //
#define PRIMITIVE_RENDERMODE_MASK	((b11110000)<<24)		
#define PRIMITIVE_POINTS			((b00010000)<<24)	// Not Supported by DS //
#define PRIMITIVE_LINES				((b00100000)<<24)	// Not Supported by DS //
#define PRIMITIVE_LINE_STRIP		((b00110000)<<24)	// Not Supported by PS1, DS //
#define PRIMITIVE_LINE_LOOP			((b01000000)<<24)	// Not Supported by PS1, PS2, DS, Cube, Xbox, DirectX //
#define PRIMITIVE_TRIANGLES			((b01010000)<<24)
#define PRIMITIVE_TRIANGLE_STRIP	((b01100000)<<24)
#define PRIMITIVE_TRIANGLE_FAN		((b01110000)<<24)	// Not Supported by PS1, DS //

#define PRIMITIVE_QUADS				((b10000000)<<24)	// Not Supported by GL ES, GL 3.0, PS2, DirectX //
#define PRIMITIVE_QUAD_STRIP		((b10010000)<<24)	// Not Supported by GL ES, GL 3.0, PS1, PS2, Cube, DirectX //
#define PRIMITIVE_SPRITE			((b11000000)<<24)	// Only Supported by PS1, PS2 //
#define PRIMITIVE_POLYGON			((b11010000)<<24)	// Only Supported by GL, Xbox. Depreciated in GL 3.0 //
// - ------------------------------------------------------------------------------------------ - //
#define PRIMITIVE_DEFAULT		(PRIMITIVE_3D|PRIMITIVE_UV_SYSTEM|PRIMITIVE_INDEX_32BIT)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawPrimitive( 
	const size_t Count,
	const void* Vertex, const void* Normal = 0, const void* UV = 0, const void* Color = 0,
	const void* Index = 0, const int Stride = 0, const int ColorStride = 0, const unsigned Flags = PRIMITIVE_DEFAULT | PRIMITIVE_TRIANGLES
	)
{
/*
	int VertexDimensions;
	if ( Flags & PRIMITIVE_2D )
		VertexDimensions = 2;
	else if ( Flags & PRIMITIVE_3D )
		VertexDimensions = 3;
	else
		return;
	
	if ( Vertex ) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(VertexDimensions, GL_FLOAT, Stride, Vertex);
	}
	else
		return;
		
	if ( Normal ) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, Stride, Normal);
	}
	else {
		glDisableClientState(GL_NORMAL_ARRAY);		
	}
	
	if ( UV ) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		int UVFormat;
		if ( (Flags & PRIMITIVE_UV_MASK) == PRIMITIVE_UV_SYSTEM )
			UVFormat = GL_UVType;
		else if ( (Flags & PRIMITIVE_UV_MASK) == PRIMITIVE_UV_8BIT )
			UVFormat = GL_BYTE;
		else if ( (Flags & PRIMITIVE_UV_MASK) == PRIMITIVE_UV_16BIT )
			UVFormat = GL_SHORT;
		// NOTE: DID NOT WORK ON iPHONE SDK!! //
//		else if ( (Flags & PRIMITIVE_UV_MASK) == PRIMITIVE_UV_32BIT )
//			UVFormat = GL_INT;

		else if ( (Flags & PRIMITIVE_UV_MASK) == PRIMITIVE_UV_FLOAT )
			UVFormat = GL_FLOAT;
		else
			return;
			
		glTexCoordPointer(2, UVFormat, Stride, UV);

		//glEnable(GL_TEXTURE_2D);
	}
	else {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	
	if ( Color ) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, ColorStride, Color);
	}
	else {
		glDisableClientState(GL_COLOR_ARRAY);
	}

	int RenderMode;
	if ( (Flags & PRIMITIVE_RENDERMODE_MASK) == PRIMITIVE_POINTS )
		RenderMode = GL_POINTS;
	else if ( (Flags & PRIMITIVE_RENDERMODE_MASK) == PRIMITIVE_LINES )
		RenderMode = GL_LINES;
	else if ( (Flags & PRIMITIVE_RENDERMODE_MASK) == PRIMITIVE_LINE_STRIP )
		RenderMode = GL_LINE_STRIP;
	else if ( (Flags & PRIMITIVE_RENDERMODE_MASK) == PRIMITIVE_LINE_LOOP )
		RenderMode = GL_LINE_LOOP;
	else if ( (Flags & PRIMITIVE_RENDERMODE_MASK) == PRIMITIVE_TRIANGLES )
		RenderMode = GL_TRIANGLES;
	else if ( (Flags & PRIMITIVE_RENDERMODE_MASK) == PRIMITIVE_TRIANGLE_STRIP )
		RenderMode = GL_TRIANGLE_STRIP;
	else if ( (Flags & PRIMITIVE_RENDERMODE_MASK) == PRIMITIVE_TRIANGLE_FAN )
		RenderMode = GL_TRIANGLE_FAN;
	else
		return;
		
	if ( Index ) {
		int IndexFormat;
		if ( (Flags & PRIMITIVE_INDEX_MASK) == PRIMITIVE_INDEX_8BIT )
			IndexFormat = GL_UNSIGNED_BYTE;
		else if ( (Flags & PRIMITIVE_INDEX_MASK) == PRIMITIVE_INDEX_16BIT )
			IndexFormat = GL_UNSIGNED_SHORT;
		// NOTE: DID NOT WORK ON iPHONE SDK!! //
//		else if ( (Flags & PRIMITIVE_INDEX_MASK) == PRIMITIVE_INDEX_32BIT )
//			IndexFormat = GL_UNSIGNED_INT;

		else
			return;

		glDrawElements(RenderMode, Count, IndexFormat, Index);
	}
	else {
		glDrawArrays(RenderMode, 0, Count);
	}
	
//	if ( UV ) {
//		glDisable(GL_TEXTURE_2D);
//	}

	gelsApplyColor( Current::Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
class cPrimitive {
public:
	// If there's Indexes, then this is an index count.  Otherwise it's a vert count. //
	size_t Count;
	
	const void* Vertex;
	const void* Normal;
	const void* UV;
	const void* Color;

	const void* Index;
	
	int Stride;
	int ColorStride;
	
	unsigned Flags; // 2D versus 3D?, 16bit versus 32bit Indexes?, "shorts" for UVs? //
public:
	cPrimitive( 
		const size_t _Count = 0,
		const void* _Vertex = 0, const void* _Normal = 0, const void* _UV = 0, const void* _Color = 0,
		const void* _Index = 0, const int _Stride = 0, const int _ColorStride = 0, const unsigned _Flags = PRIMITIVE_DEFAULT
		) :
		Count( _Count ),
		Vertex( _Vertex ),
		Normal( _Normal ),
		UV( _UV ),
		Color( _Color ),
		Index( _Index ),
		Stride( _Stride ),
		ColorStride( _ColorStride ),
		Flags( _Flags )
	{
	}
	
	inline void Draw() {
		gelDrawPrimitive( Count, Vertex, Normal, UV, Color, Index, Stride, ColorStride, Flags );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_Primitive_H__ //
// - ------------------------------------------------------------------------------------------ - //
