// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Rectangles3D_H__
#define __GraphicsDraw_Rectangles3D_H__
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCube( const Vector3D& P1, const Vector3D& P2, const GelColor Color = Current::Color ) {
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

	gelDrawLines( (Vector3D*)Verts, 24, Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawCube( const Real P1x, const Real P1y, const Real P1z, const Real P2x, const Real P2y, const Real P2z, const GelColor Color = Current::Color ) {
	gelDrawCube( Vector3D( P1x, P1y, P1z), Vector3D( P2x, P2y, P2z ), Color );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRect( const Vector3D& P1, const Vector3D& P2, const GelColor Color = Current::Color ) {
	float Diff = P1.z + ((P2.z - P1.z) * Real::Half);

	float Verts[] = {
		(float)P1.x, (float)P1.y, (float)P1.z,
		(float)P1.x, (float)P2.y, Diff,
		(float)P2.x, (float)P2.y, (float)P2.z,
		(float)P2.x, (float)P1.y, Diff,
	};

	gelDrawLineLoop( (Vector3D*)Verts, 4, Color );    
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRect( const Real P1x, const Real P1y, const Real P1z, const Real P2x, const Real P2y, const Real P2z, const GelColor Color = Current::Color ) {
	gelDrawRect( Vector3D( P1x, P1y, P1z), Vector3D( P2x, P2y, P2z ), Color );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Vector3D& P1, const Vector3D& P2, const GelColor Color = Current::Color ) {
	float Diff = P1.z + ((P2.z - P1.z) * Real::Half);

    float Verts[] = {
		(float)P1.x, (float)P1.y, (float)P1.z,
		(float)P1.x, (float)P2.y, Diff,
		(float)P2.x, (float)P1.y, Diff,
		(float)P2.x, (float)P2.y, (float)P2.z,
    };

	gelDrawTriangleStrip( (Vector3D*)Verts, 4, Color );    
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFill( const Real P1x, const Real P1y, const Real P1z, const Real P2x, const Real P2y, const Real P2z, const GelColor Color = Current::Color ) {
	gelDrawRectFill( Vector3D( P1x, P1y, P1z), Vector3D( P2x, P2y, P2z ), Color );
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
inline void gelDrawRectFillTextured_( const Vector3D& P1, const Vector3D& P2, const Vector2D& UV1 = Vector2D(0,0), const Vector2D&UV2 = Vector2D(1,1) ) {
	float Diff = P1.z + ((P2.z - P1.z) * Real::Half);

    float Verts[] = {
		(float)P1.x, (float)P1.y, (float)P1.z,
		(float)P2.x, (float)P1.y, Diff,
		(float)P1.x, (float)P2.y, Diff,
		(float)P2.x, (float)P2.y, (float)P2.z,
    };

	GelUV UVs[] = {
		(GelUV)(UV1.x * Real(GEL_UV_ONE_F)), (GelUV)(UV1.y * Real(GEL_UV_ONE_F)),
		(GelUV)(UV2.x * Real(GEL_UV_ONE_F)), (GelUV)(UV1.y * Real(GEL_UV_ONE_F)),
		(GelUV)(UV1.x * Real(GEL_UV_ONE_F)), (GelUV)(UV2.y * Real(GEL_UV_ONE_F)),
		(GelUV)(UV2.x * Real(GEL_UV_ONE_F)), (GelUV)(UV2.y * Real(GEL_UV_ONE_F)),
	};

	gelDrawTriangleStripTextured_( (Vector3D*)Verts, UVs, 4 );    
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawRectFillTextured( const Vector3D& P1, const Vector3D& P2, const Vector2D& UV1 = Vector2D(0,0), const Vector2D&UV2 = Vector2D(1,1), const GelColor Color = Current::Color ) {
	gelSetColor( Color );
	gelDrawRectFillTextured_( P1, P2, UV1, UV2 );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GraphicsDraw_Rectangles3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
