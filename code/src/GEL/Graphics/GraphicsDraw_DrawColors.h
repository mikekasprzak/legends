// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_DrawColors_H__
#define __GEL_GraphicsDraw_DrawColors_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELSDraw_DrawColors.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLinesColors_( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_COLORS
	gels_DrawColors( GEL_LINES, Poly, Colors, PolyCount );
#endif // GELS_DRAW_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStripColors_( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_COLORS
	gels_DrawColors( GEL_LINE_STRIP, Poly, Colors, PolyCount );
#endif // GELS_DRAW_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoopColors_( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_COLORS
	gels_DrawColors( GEL_LINE_LOOP, Poly, Colors, PolyCount );
#endif // GELS_DRAW_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLinesColors_( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_COLORS
	gels_DrawIndexedColors( GEL_LINES, Poly, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStripColors_( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_COLORS
	gels_DrawIndexedColors( GEL_LINE_STRIP, Poly, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoopColors_( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_COLORS
	gels_DrawIndexedColors( GEL_LINE_LOOP, Poly, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPointsColors_( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_COLORS
	gels_DrawColors( GEL_POINTS, Poly, Colors, PolyCount );
#endif // GELS_DRAW_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTrianglesColors_( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_COLORS
	gels_DrawColors( GEL_TRIANGLES, Poly, Colors, PolyCount );
#endif // GELS_DRAW_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStripColors_( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_COLORS
	gels_DrawColors( GEL_TRIANGLE_STRIP, Poly, Colors, PolyCount );
#endif // GELS_DRAW_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFanColors_( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_COLORS
	gels_DrawColors( GEL_TRIANGLE_FAN, Poly, Colors, PolyCount );
#endif // GELS_DRAW_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTrianglesColors_( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_COLORS
	gels_DrawIndexedColors( GEL_TRIANGLES, Poly, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStripColors_( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_COLORS
	gels_DrawIndexedColors( GEL_TRIANGLE_STRIP, Poly, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFanColors_( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_COLORS
	gels_DrawIndexedColors( GEL_TRIANGLE_FAN, Poly, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLinesColors( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelDrawLinesColors_( Poly, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStripColors( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelDrawLineStripColors_( Poly, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoopColors( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount, const ColorType Color = Current::Color ) {
	gelDrawLineLoopColors_( Poly, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLinesColors( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedLinesColors_( Poly, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStripColors( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedLineStripColors_( Poly, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoopColors( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedLineLoopColors_( Poly, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPointsColors( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
 	gelDrawPointsColors_( Poly, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTrianglesColors( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
	gelDrawTrianglesColors_( Poly, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStripColors( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
	gelDrawTriangleStripColors_( Poly, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFanColors( const VertType* Poly, const unsigned int* Colors, const size_t PolyCount ) {
	gelDrawTriangleFanColors_( Poly, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTrianglesColors( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedTrianglesColors_( Poly, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStripColors( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedTriangleStripColors_( Poly, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFanColors( const VertType* Poly, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedTriangleFanColors_( Poly, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_DrawColors_H__ //
// - ------------------------------------------------------------------------------------------ - //
