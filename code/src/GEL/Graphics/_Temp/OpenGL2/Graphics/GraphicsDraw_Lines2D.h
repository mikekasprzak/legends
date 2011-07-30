// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Lines2D_H__
#define __GraphicsDraw_Lines2D_H__
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawLine( const Vector2D& P1, const Vector2D& P2, const ColorType Color = Current::Color) {
	gelFlatShaded();
	gelSetColor( Color );

    float Verts[] = {
		P1.x, P1.y,
		P2.x, P2.y,
    };
    
	gelVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 2 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawLineNormal( const Vector2D& P1, const Vector2D& P2, const Real Length = Current::NormalLength, const ColorType Color = Current::Color) {
	gelFlatShaded();
	gelSetColor( Color );
	
	Vector2D Ray = (P2-P1);
	Vector2D Normal = Ray.Tangent().Normal();
	
	Vector2D Center = P1 + (Ray * Real::Half);
	Vector2D NormalPos = Center + (Normal * Length);

    float Verts[] = {
		Center.x, Center.y,
		NormalPos.x, NormalPos.y,
    };
    
    gelVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 2 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
// Arrowheads on one end (B) //
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawArrow( const Vector2D& P1, const Vector2D& P2, const ColorType Color = Current::Color, const Real HeadLength = Current::NormalLength ) {
	gelFlatShaded();
	gelSetColor( Color );

	Vector2D HeadPoint = P2 - P1;
	HeadPoint.Normalize();
	HeadPoint *= HeadLength;

    float Verts[] = {
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)P2.x-0.1f, (float)P2.y-0.0f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.Rotate45().x+P2.x+0.0f, (float)-HeadPoint.Rotate45().y+P2.y+0.1f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.RotateNegative45().x+P2.x+0.0f, (float)-HeadPoint.RotateNegative45().y+P2.y+0.1f,
    };
    
    gelVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 6 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
// Arrowheads on both ends //
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawArrow2( const Vector2D& P1, const Vector2D& P2, const ColorType Color = Current::Color, const Real HeadLength = Current::NormalLength ) {
	gelFlatShaded();
	gelSetColor( Color );

	Vector2D HeadPoint = P2 - P1;
	HeadPoint.Normalize();
	HeadPoint *= HeadLength;

    float Verts[] = {
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)P2.x-0.1f, (float)P2.y-0.0f,
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)HeadPoint.Rotate45().x+P1.x+0.0f, (float)HeadPoint.Rotate45().y+P1.y+0.1f,
		(float)P1.x+0.0f, (float)P1.y+0.1f,
		(float)HeadPoint.RotateNegative45().x+P1.x+0.0f, (float)HeadPoint.RotateNegative45().y+P1.y+0.1f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.Rotate45().x+P2.x+0.0f, (float)-HeadPoint.Rotate45().y+P2.y+0.1f,
		(float)P2.x+0.0f, (float)P2.y+0.1f,
		(float)-HeadPoint.RotateNegative45().x+P2.x+0.0f, (float)-HeadPoint.RotateNegative45().y+P2.y+0.1f,
    };
    
    gelVertexPointer( 2, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 10 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_Lines2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
