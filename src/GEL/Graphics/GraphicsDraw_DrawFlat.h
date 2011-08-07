// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_DrawFlat_H__
#define __GEL_GraphicsDraw_DrawFlat_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL1/GELSDraw_DrawFlat.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLines_( const VertType* Poly, const size_t PolyCount ) {
#ifdef GELS_DRAW_FLAT
	gels_DrawFlat( GEL_LINES, Poly, PolyCount );
#endif // GELS_DRAW_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStrip_( const VertType* Poly, const size_t PolyCount ) {
#ifdef GELS_DRAW_FLAT
	gels_DrawFlat( GEL_LINE_STRIP, Poly, PolyCount );
#endif // GELS_DRAW_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoop_( const VertType* Poly, const size_t PolyCount ) {
#ifdef GELS_DRAW_FLAT
	gels_DrawFlat( GEL_LINE_LOOP, Poly, PolyCount );
#endif // GELS_DRAW_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLines_( const VertType* Poly, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_FLAT
	gels_DrawIndexedFlat( GEL_LINES, Poly, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStrip_( const VertType* Poly, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_FLAT
	gels_DrawIndexedFlat( GEL_LINE_STRIP, Poly, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoop_( const VertType* Poly, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_FLAT
	gels_DrawIndexedFlat( GEL_LINE_LOOP, Poly, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPoints_( const VertType* Poly, const size_t PolyCount ) {
#ifdef GELS_DRAW_FLAT
	gels_DrawFlat( GEL_POINTS, Poly, PolyCount );
#endif // GELS_DRAW_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangles_( const VertType* Poly, const size_t PolyCount ) {
#ifdef GELS_DRAW_FLAT
	gels_DrawFlat( GEL_TRIANGLES, Poly, PolyCount );
#endif // GELS_DRAW_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStrip_( const VertType* Poly, const size_t PolyCount ) {
#ifdef GELS_DRAW_FLAT
	gels_DrawFlat( GEL_TRIANGLE_STRIP, Poly, PolyCount );
#endif // GELS_DRAW_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFan_( const VertType* Poly, const size_t PolyCount ) {
#ifdef GELS_DRAW_FLAT
	gels_DrawFlat( GEL_TRIANGLE_FAN, Poly, PolyCount );
#endif // GELS_DRAW_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangles_( const VertType* Poly, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_FLAT
	gels_DrawIndexedFlat( GEL_TRIANGLES, Poly, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStrip_( const VertType* Poly, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_FLAT
	gels_DrawIndexedFlat( GEL_TRIANGLE_STRIP, Poly, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFan_( const VertType* Poly, const unsigned short* Index, const size_t IndexCount ) {
#ifdef GELS_DRAW_INDEXED_FLAT
	gels_DrawIndexedFlat( GEL_TRIANGLE_FAN, Poly, Index, IndexCount );
#endif // GELS_DRAW_INDEXED_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLines( const VertType* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawLines_( Poly, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineStrip( const VertType* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawLineStrip_( Poly, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawLineLoop( const VertType* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawLineLoop_( Poly, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLines( const VertType* Poly, const unsigned short* Index, const size_t IndexCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedLines_( Poly, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineStrip( const VertType* Poly, const unsigned short* Index, const size_t IndexCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedLineStrip_( Poly, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedLineLoop( const VertType* Poly, const unsigned short* Index, const size_t IndexCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedLineLoop_( Poly, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawPoints( const VertType* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
 	gelDrawPoints_( Poly, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangles( const VertType* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawTriangles_( Poly, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleStrip( const VertType* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawTriangleStrip_( Poly, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawTriangleFan( const VertType* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawTriangleFan_( Poly, PolyCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangles( const VertType* Poly, const unsigned short* Index, const size_t IndexCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedTriangles_( Poly, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleStrip( const VertType* Poly, const unsigned short* Index, const size_t IndexCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedTriangleStrip_( Poly, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //
template< class VertType >
inline void gelDrawIndexedTriangleFan( const VertType* Poly, const unsigned short* Index, const size_t IndexCount, const GelColor Color = Current::Color ) {
	gelApplyColor( Color );
        
	gelDrawIndexedTriangleFan_( Poly, Index, IndexCount );

	gelRestoreColor();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_DrawFlat_H__ //
// - ------------------------------------------------------------------------------------------ - //
