// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_DrawTextured_H__
#define __GEL_GraphicsDraw_DrawTextured_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELSDraw_DrawTextured.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLinesTextured_( const VertType* Poly, const UVType* UV, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( GEL_LINES, Poly, UV, PolyCount );
#endif // GELS_DRAW_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStripTextured_( const VertType* Poly, const UVType* UV, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( GEL_LINE_STRIP, Poly, UV, PolyCount );
#endif // GELS_DRAW_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoopTextured_( const VertType* Poly, const UVType* UV, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( GEL_LINE_LOOP, Poly, UV, PolyCount );
#endif // GELS_DRAW_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLinesTextured_( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED
	gels_DrawIndexedTextured( GEL_LINES, Poly, UV, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStripTextured_( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED
	gels_DrawIndexedTextured( GEL_LINE_STRIP, Poly, UV, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoopTextured_( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED
	gels_DrawIndexedTextured( GEL_LINE_LOOP, Poly, UV, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPointsTextured_( const VertType* Poly, const UVType* UV, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( GEL_POINTS, Poly, UV, PolyCount );
#endif // GELS_DRAW_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTrianglesTextured_( const VertType* Poly, const UVType* UV, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( GEL_TRIANGLES, Poly, UV, PolyCount );
#endif // GELS_DRAW_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStripTextured_( const VertType* Poly, const UVType* UV, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( GEL_TRIANGLE_STRIP, Poly, UV, PolyCount );
#endif // GELS_DRAW_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFanTextured_( const VertType* Poly, const UVType* UV, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED
	gels_DrawTextured( GEL_TRIANGLE_FAN, Poly, UV, PolyCount );
#endif // GELS_DRAW_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTrianglesTextured_( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED
	gels_DrawIndexedTextured( GEL_TRIANGLES, Poly, UV, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStripTextured_( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED
	gels_DrawIndexedTextured( GEL_TRIANGLE_STRIP, Poly, UV, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFanTextured_( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED
	gels_DrawIndexedTextured( GEL_TRIANGLE_FAN, Poly, UV, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED //
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLinesTextured( const VertType* Poly, const UVType* UV, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawLinesTextured_( Poly, UV, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStripTextured( const VertType* Poly, const UVType* UV, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawLineStripTextured_( Poly, UV, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoopTextured( const VertType* Poly, const UVType* UV, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawLineLoopTextured_( Poly, UV, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLinesTextured( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedLinesTextured_( Poly, UV, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStripTextured( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedLineStripTextured_( Poly, UV, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoopTextured( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedLineLoopTextured_( Poly, UV, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPointsTextured( const VertType* Poly, const UVType* UV, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
 	gelDrawPointsTextured_( Poly, UV, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTrianglesTextured( const VertType* Poly, const UVType* UV, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawTrianglesTextured_( Poly, UV, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStripTextured( const VertType* Poly, const UVType* UV, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawTriangleStripTextured_( Poly, UV, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFanTextured( const VertType* Poly, const UVType* UV, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawTriangleFanTextured_( Poly, UV, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTrianglesTextured( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedTrianglesTextured_( Poly, UV, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStripTextured( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedTriangleStripTextured_( Poly, UV, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFanTextured( const VertType* Poly, const UVType* UV, const unsigned short* Index, const size_t IndexCount, const ColorType Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedTriangleFanTextured_( Poly, UV, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_DrawTextured_H__ //
// - ------------------------------------------------------------------------------------------ - //
