// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Rectangles2D_H__
#define __GraphicsDraw_Rectangles2D_H__
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRect( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );

	float Verts[] = {
		(float)P1.x, (float)P1.y,
		(float)P1.x, (float)P2.y,
		(float)P2.x, (float)P2.y,
		(float)P2.x, (float)P1.y,
	};
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRect( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );

	float Verts[] = {
		(float)P1x, (float)P1y,
		(float)P1x, (float)P2y,
		(float)P2x, (float)P2y,
		(float)P2x, (float)P1y,
	};
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Vector2D& P1, const Vector2D& P2, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );

    float Verts[] = {
		(float)P1.x, (float)P1.y,
		(float)P1.x, (float)P2.y,
		(float)P2.x, (float)P1.y,
		(float)P2.x, (float)P2.y,
    };
    
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gelRestoreColor( Color );
*/
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Real P1x, const Real P1y, const Real P2x, const Real P2y, const GelColor Color = Current::Color ) {
/*
	gelSetColor( Color );

    float Verts[] = {
		(float)P1x, (float)P1y,
		(float)P1x, (float)P2y,
		(float)P2x, (float)P1y,
		(float)P2x, (float)P2y,
	};
        
    glVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gelRestoreColor( Color );
*/
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
#endif // __GraphicsDraw_Rectangles2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
