// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_DrawTexturedColors_H__
#define __GEL_GraphicsDraw_DrawTexturedColors_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELSDraw_DrawTexturedColors.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLinesTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED_COLORS
	gels_DrawTexturedColors( GEL_LINES, Poly, UV, Colors, PolyCount );
#endif // GELS_DRAW_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStripTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED_COLORS
	gels_DrawTexturedColors( GEL_LINE_STRIP, Poly, UV, Colors, PolyCount );
#endif // GELS_DRAW_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoopTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED_COLORS
	gels_DrawTexturedColors( GEL_LINE_LOOP, Poly, UV, Colors, PolyCount );
#endif // GELS_DRAW_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLinesTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED_COLORS
	gels_DrawIndexedTexturedColors( GEL_LINES, Poly, UV, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStripTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED_COLORS
	gels_DrawIndexedTexturedColors( GEL_LINE_STRIP, Poly, UV, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoopTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED_COLORS
	gels_DrawIndexedTexturedColors( GEL_LINE_LOOP, Poly, UV, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPointsTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED_COLORS
	gels_DrawTexturedColors( GEL_POINTS, Poly, UV, Colors, PolyCount );
#endif // GELS_DRAW_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTrianglesTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED_COLORS
	gels_DrawTexturedColors( GEL_TRIANGLES, Poly, UV, Colors, PolyCount );
#endif // GELS_DRAW_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStripTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED_COLORS
	gels_DrawTexturedColors( GEL_TRIANGLE_STRIP, Poly, UV, Colors, PolyCount );
#endif // GELS_DRAW_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFanTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
#ifdef GELS_DRAW_TEXTURED_COLORS
	gels_DrawTexturedColors( GEL_TRIANGLE_FAN, Poly, UV, Colors, PolyCount );
#endif // GELS_DRAW_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTrianglesTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED_COLORS
	gels_DrawIndexedTexturedColors( GEL_TRIANGLES, Poly, UV, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStripTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED_COLORS
	gels_DrawIndexedTexturedColors( GEL_TRIANGLE_STRIP, Poly, UV, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFanTexturedColors_( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_TEXTURED_COLORS
	gels_DrawIndexedTexturedColors( GEL_TRIANGLE_FAN, Poly, UV, Colors, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_TEXTURED_COLORS //
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLinesTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelDrawLinesTexturedColors_( Poly, UV, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStripTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelDrawLineStripTexturedColors_( Poly, UV, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoopTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelDrawLineLoopTexturedColors_( Poly, UV, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLinesTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedLinesTexturedColors_( Poly, UV, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStripTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedLineStripTexturedColors_( Poly, UV, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoopTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedLineLoopTexturedColors_( Poly, UV, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPointsTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
 	gelDrawPointsTexturedColors_( Poly, UV, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTrianglesTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
	gelDrawTrianglesTexturedColors_( Poly, UV, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStripTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
	gelDrawTriangleStripTexturedColors_( Poly, UV, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFanTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const size_t PolyCount ) {
	gelDrawTriangleFanTexturedColors_( Poly, UV, Colors, PolyCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTrianglesTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedTrianglesTexturedColors_( Poly, UV, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStripTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedTriangleStripTexturedColors_( Poly, UV, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFanTexturedColors( const VertType* Poly, const GelUV* UV, const unsigned int* Colors, const unsigned short* Index, const size_t IndexCount ) {
	gelDrawIndexedTriangleFanTexturedColors_( Poly, UV, Colors, Index, IndexCount );
	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_DrawTexturedColors_H__ //
// - ------------------------------------------------------------------------------------------ - //
