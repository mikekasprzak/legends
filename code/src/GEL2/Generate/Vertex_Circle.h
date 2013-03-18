// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GENERATE_VERTEX_CIRCLE_H__
#define __GEL2_GENERATE_VERTEX_CIRCLE_H__
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Circle( T* Dest, const Vector3D& Pos, const Real& Radius, const st32 Steps = 32 ) {
	Vector3D* Out;

//	float FloatSteps = Steps;
	float FloatSteps = 1.0f / (float)Steps;
    
	for ( st32 idx = 0; idx < Steps; idx++ ) {
		Out = (Vector3D*)Dest++;
		Out->x = Pos.x + (Real::Cos(idx * FloatSteps) * Radius);
		Out->y = Pos.y + (Real::Sin(idx * FloatSteps) * Radius);
		Out->z = Pos.z;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Circle( T* Dest, const Vector2D& Pos, const Real& Radius, const st32 Steps = 32 ) {
	generate_Vertex3D_Circle( Dest, Pos.ToVector3D(), Radius, Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Circle( const st32 Steps = 32 ) {
	return Steps;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Circle( const Vector3D&, const Real&, const st32 Steps = 32 ) {
	return size_Vertex3D_Circle( Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Circle( const Vector2D&, const Real&, const st32 Steps = 32 ) {
	return size_Vertex3D_Circle( Steps );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_CircleNormals( T* Dest, const Vector3D& Pos, const Real& = Real::One, const Real NormalLength = Real(4) ) {
	Vector3D* Out;

	Out = (Vector3D*)Dest++;
	*Out = Pos - Vector3D(0,0,NormalLength);
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(0,0,NormalLength);
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_CircleNormals( T* Dest, const Vector2D& Pos, const Real& Radius = Real::One, const Real NormalLength = Real(4) ) {
	generate_Vertex3D_CircleNormals( Dest, Pos.ToVector3D(), Radius, NormalLength );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_CircleNormals() {
	return 2;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_CircleNormals( const Vector3D&, const Real& ) {
	return size_Vertex3D_Circle();
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_CircleNormals( const Vector2D&, const Real& ) {
	return size_Vertex3D_Circle();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GENERATE_VERTEX_CIRCLE_H__ //
// - ------------------------------------------------------------------------------------------ - //
