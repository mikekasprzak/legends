// - ------------------------------------------------------------------------------------------ - //
#ifndef __GraphicsDraw_Lines3D_H__
#define __GraphicsDraw_Lines3D_H__
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void gelDrawLine( const Vector3D& P1, const Vector3D& P2, const ColorType Color = Current::Color) {
//	gelSetColor( Color );

    float Verts[] = {
		P1.x, P1.y, P1.z,
		P2.x, P2.y, P2.z,
    };
 
 	gelDrawLines( (Vector3D*)Verts, 2, Color );
   
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 2 );
//
//	gelRestoreColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//inline void gelDrawArrow( const Vector3D& P1, const Vector3D& P2, const ColorType Color = Current::Color, const Real HeadLength = Current::NormalLength ) {
//	gelSetColor( Color );
//
//	Vector3D HeadPoint = P2 - P1;
//	HeadPoint.Normalize();
//	HeadPoint *= HeadLength;
//
//    float Verts[] = {
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		
//		
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.Rotate45().y+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//		
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.Rotate45().z+P2.z,
//    };
//    
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 10 );
//
//	gelRestoreColor( Color );
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void gelDrawArrow2( const Vector3D& P1, const Vector3D& P2, const ColorType Color = Current::Color, const Real HeadLength = Current::NormalLength ) {
//	gelSetColor( Color );
//
//	Vector3D HeadPoint = P2 - P1;
//	HeadPoint.Normalize();
//	HeadPoint *= HeadLength;
//
//    float Verts[] = {
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)P2.x, (float)P2.y, (float)P2.z,
//
//		
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.Rotate45().x+P1.x, (float)HeadPoint.Rotate45().y+P1.y, (float)HeadPoint.Rotate45().z+P1.z,
//
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.RotateNegative45().x+P1.x, (float)HeadPoint.RotateNegative45().y+P1.y, (float)HeadPoint.RotateNegative45().z+P1.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.Rotate45().z+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//
//		
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.Rotate45().x+P1.x, (float)HeadPoint.Rotate45().y+P1.y, (float)HeadPoint.RotateNegative45().z+P1.z,
//
//		(float)P1.x, (float)P1.y, (float)P1.z,
//		(float)HeadPoint.RotateNegative45().x+P1.x, (float)HeadPoint.RotateNegative45().y+P1.y, (float)HeadPoint.Rotate45().z+P1.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.Rotate45().x+P2.x, (float)-HeadPoint.Rotate45().y+P2.y, (float)-HeadPoint.RotateNegative45().z+P2.z,
//
//		(float)P2.x, (float)P2.y, (float)P2.z,
//		(float)-HeadPoint.RotateNegative45().x+P2.x, (float)-HeadPoint.RotateNegative45().y+P2.y, (float)-HeadPoint.Rotate45().z+P2.z,
//    };
//    
//    glVertexPointer( 3, GL_FLOAT, 0, Verts );
//    glDrawArrays( GL_LINES, 0, 18 );
//
//	gelRestoreColor( Color );
//}
//// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_Lines3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
