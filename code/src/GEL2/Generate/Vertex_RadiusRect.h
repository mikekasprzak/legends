// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GENERATE_VERTEX_RADIUSRECT_H__
#define __GEL2_GENERATE_VERTEX_RADIUSRECT_H__
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_RadiusRect( T* Dest, const Vector3D& Pos, const Vector3D& HalfShape ) {
	Vector3D* Out;
	
	Out = (Vector3D*)Dest++;
	*Out = Pos - HalfShape;
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(+HalfShape.x,-HalfShape.y,+HalfShape.z);
	Out = (Vector3D*)Dest++;
	*Out = Pos + HalfShape;
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(-HalfShape.x,+HalfShape.y,+HalfShape.z);
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_RadiusRect( T* Dest, const Vector2D& Pos, const Vector2D& HalfShape ) {
	generate_Vertex3D_RadiusRect( Dest, Pos.ToVector3D(), HalfShape.ToVector3D() );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_RadiusRect( T* Dest, const Vector3D& Pos, const Real& Radius ) {
	generate_Vertex3D_RadiusRect( Dest, Pos, Vector3D(Radius,Radius,Radius) );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_RadiusRect( T* Dest, const Vector2D& Pos, const Real& Radius ) {
	generate_Vertex3D_RadiusRect( Dest, Pos.ToVector3D(), Vector3D(Radius,Radius,Radius) );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_RadiusRect() {
	return 4;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_RadiusRect( const Vector3D&, const Vector3D& ) {
	return size_Vertex3D_RadiusRect();
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_RadiusRect( const Vector2D&, const Vector2D& ) {
	return size_Vertex3D_RadiusRect();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GENERATE_VERTEX_RADIUSRECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
