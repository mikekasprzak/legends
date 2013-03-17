// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GENERATE_VERTEX_RECT_H__
#define __GEL2_GENERATE_VERTEX_RECT_H__
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Rect( T* Dest, const Vector3D& Pos, const Vector3D& Shape ) {
	Vector3D* Out;
	
	Out = (Vector3D*)Dest++;
	*Out = Pos;
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._x00();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape;
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._0y0();
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Rect( T* Dest, const Vector2D& Pos, const Vector2D& Shape ) {
	generate_Vertex3D_Rect( Dest, Pos.ToVector3D(), Shape.ToVector3D() );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Rect() {
	return 4;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Rect( const Vector3D&, const Vector3D& ) {
	return size_Vertex3D_Rect();
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Rect( const Vector2D&, const Vector2D& ) {
	return size_Vertex3D_Rect();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GENERATE_VERTEX_RECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
