// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Polygons_H__
#define __GraphicsDraw_Polygons_H__
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawClosedPolygon( const Vector2D* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );
        
    glVertexPointer( 2, GL_FLOAT, 0, (const float*)Poly );
    glDrawArrays( GL_LINE_LOOP, 0, PolyCount );
    
    gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawOpenPolygon( const Vector2D* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );
        
    glVertexPointer( 2, GL_FLOAT, 0, (const float*)Poly );
    glDrawArrays( GL_LINE_STRIP, 0, PolyCount );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawClosedPolygonNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixClosedPolygonNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawOpenPolygonNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixOpenPolygonNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawClosedPolygonInvNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixClosedPolygonInvNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawOpenPolygonInvNormals( const Vector2D* Poly, const size_t PolyCount, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixOpenPolygonInvNormals( Buffer, Matrix, Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawClosedPolygonWithNormals( const Vector2D* Poly, const size_t PolyCount, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
	gelDrawClosedPolygon(Poly, PolyCount, Color );
	gelDrawClosedPolygonNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawOpenPolygonWithNormals( const Vector2D* Poly, const size_t PolyCount, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
	gelDrawOpenPolygon(Poly, PolyCount, Color );
	gelDrawOpenPolygonNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawClosedPolygonWithInvNormals( const Vector2D* Poly, const size_t PolyCount, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
	gelDrawClosedPolygon(Poly, PolyCount, Color );
	gelDrawClosedPolygonInvNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawOpenPolygonWithInvNormals( const Vector2D* Poly, const size_t PolyCount, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
	gelDrawOpenPolygon(Poly, PolyCount, Color );
	gelDrawOpenPolygonInvNormals(Poly, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawPolygonEdge( const int Index, const Vector2D* Poly, const size_t PolyCount, const GelColor Color = Current::Color ) {
	int NextIndex = Index+1;
	if ( NextIndex >= PolyCount ) 
		NextIndex = 0;
	gelDrawLine( Poly[Index], Poly[NextIndex], Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawEdgedPolygonNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixEdgedPolygonNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawEdgedPolygonInvNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixEdgedPolygonInvNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawEdgedPolygon( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const GelColor Color = Current::Color ) {
//	MatrixEdgedPolygon( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawEdgedPolygonWithNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixEdgedPolygonWithNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, Color, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawEdgedPolygonWithInvNormals( const Vector2D* Poly, const bool* PolygonEnabled, const size_t PolyCount, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixEdgedPolygonWithInvNormals( Buffer, Matrix, Poly, PolygonEnabled, PolyCount, Color, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_Polygons_H__ //
// - ------------------------------------------------------------------------------------------ - //
