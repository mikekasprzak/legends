// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Rectangles2D_H__
#define __GraphicsDraw_Rectangles2D_H__
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRect( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color ) {
	float Verts[] = {
		(float)P1.x, (float)P1.y,
		(float)P1.x, (float)P2.y,
		(float)P2.x, (float)P2.y,
		(float)P2.x, (float)P1.y,
	};

	gelDrawLineLoop( (Vector2D*)Verts, 4, Color );    
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRect( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const GelColor Color = Current::Color ) {
	gelDrawRect( Vector2D( P1x, P1y ), Vector2D( P2x, P2y ), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color ) {
    float Verts[] = {
		(float)P1.x, (float)P1.y,
		(float)P1.x, (float)P2.y,
		(float)P2.x, (float)P1.y,
		(float)P2.x, (float)P2.y,
    };
    
	gelDrawTriangleStrip( (Vector2D*)Verts, 4, Color );    
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const GelColor Color = Current::Color ) {
	gelDrawRectFill( Vector2D( P1x, P1y), Vector2D( P2x, P2y ), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectNormals( const Vector2D& P1, const Vector2D& P2, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixRectNormals( Buffer, Matrix, Rect2D::Pair( P1, P2 ), NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectWithNormals( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
	gelDrawRect( P1, P2, Color );
	gelDrawRectNormals( P1, P2, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectTextured( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color ) {
    float Verts[] = {
		(float)P1.x, (float)P1.y,
		(float)P1.x, (float)P2.y,
		(float)P2.x, (float)P1.y,
		(float)P2.x, (float)P2.y,
    };

    GelUV UV[] = {
		UV_ZERO, UV_ZERO,
		UV_ZERO, UV_ONE,
		UV_ONE, UV_ZERO,
		UV_ONE, UV_ONE,
    };
    
	gelDrawTriangleStripTextured( (Vector2D*)Verts, UV, 4, Color );    
}


// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_Rectangles2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
