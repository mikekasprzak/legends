// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Rectangles3D_H__
#define __GraphicsDraw_Rectangles3D_H__
// - ------------------------------------------------------------------------------------------ - //
//// - ------------------------------------------------------------------------------------------ - //
//inline void gelDrawRect( const Vector3D& P1, const Vector3D& P2, const GelColor Color = Current::Color ) {
//	gelSetColor( Color );
//
//	float Diff = P1.z + ((P2.z - P1.z) * Real::Half);
//
//	float Verts[] = {
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)P1.x, (float)P2.y, Diff,
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)P2.x, (float)P1.y, Diff,
//	};
//    
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINE_LOOP, 0, 4 );
//
//	gelRestoreColor( Color );
//}
// - ------------------------------------------------------------------------------------------ - //
// TODO: This should be "Cube" //
inline void gelDrawRect( const Vector3D& P1, const Vector3D& P2, const GelColor Color = Current::Color ) {
	gelFlatShaded();
	gelSetColor( Color );

	Vector3D Diff = P2-P1;
	Vector3D XDiff(Diff.x,0,0);
	Vector3D YDiff(0,Diff.y,0);
	Vector3D ZDiff(0,0,Diff.z);

	Vector3D Verts[] = {
		P1, P1+XDiff,
		P1, P1+YDiff,
		P1, P1+ZDiff,

		P1+ZDiff, P1+ZDiff+XDiff,
		P1+ZDiff, P1+ZDiff+YDiff,

		P2, P2-XDiff,
		P2, P2-YDiff,
		P2, P2-ZDiff,

		P2-ZDiff, P2-ZDiff-XDiff,
		P2-ZDiff, P2-ZDiff-YDiff,

		P1+XDiff, P1+ZDiff+XDiff,
		P1+YDiff, P1+ZDiff+YDiff,
	};
    
    gelVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINES, 0, 24 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRect( const Real P1x, const Real P1y, const Real P1z, const Real P2x, const Real P2y, const Real P2z, const GelColor Color = Current::Color ) {
	gelFlatShaded();
	gelSetColor( Color );
	
	float Diff = P1z + ((P2z - P1z) * Real::Half);

	float Verts[] = {
		(float)P1x, (float)P1y, (float)P1z,
		(float)P1x, (float)P2y, Diff,
		(float)P2x, (float)P2y, (float)P2z,
		(float)P2x, (float)P1y, Diff,
	};
    
    gelVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_LINE_LOOP, 0, 4 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Vector3D& P1, const Vector3D& P2, const GelColor Color = Current::Color ) {
	gelFlatShaded();
	gelSetColor( Color );

	float Diff = P1.z + ((P2.z - P1.z) * Real::Half);

    float Verts[] = {
		(float)P1.x, (float)P1.y, (float)P1.z,
		(float)P1.x, (float)P2.y, Diff,
		(float)P2.x, (float)P1.y, Diff,
		(float)P2.x, (float)P2.y, (float)P2.z,
    };
    
    gelVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Real P1x, const Real P1y, const Real P1z, const Real P2x, const Real P2y, const Real P2z, const GelColor Color = Current::Color ) {
	gelFlatShaded();
	gelSetColor( Color );

	float Diff = P1z + ((P2z - P1z) * Real::Half);

    float Verts[] = {
		(float)P1x, (float)P1y, (float)P1z,
		(float)P1x, (float)P2y, Diff,
		(float)P2x, (float)P1y, Diff,
		(float)P2x, (float)P2y, (float)P2z,
	};
        
    gelVertexPointer( 3, GL_FLOAT, 0, Verts );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectNormals( const Vector3D& P1, const Vector3D& P2, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
//	MatrixRectNormals( Buffer, Matrix, Rect2D::Pair( P1, P2 ), NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectWithNormals( const Vector3D& P1, const Vector3D& P2, const GelColor Color = Current::Color, const Real NormalLength = Current::NormalLength, const GelColor NormalColor = Current::NormalColor ) {
	gelDrawRect( P1, P2, Color );
	gelDrawRectNormals( P1, P2, NormalLength, NormalColor );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_Rectangles3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
