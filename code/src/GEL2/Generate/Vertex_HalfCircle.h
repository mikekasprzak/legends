// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GENERATE_VERTEX_HALFCIRCLE_H__
#define __GEL2_GENERATE_VERTEX_HALFCIRCLE_H__
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_HalfCircle( T* Dest, const Vector3D& Pos, const Real& Radius, const Vector3D& Normal, const st32 Steps = 16 ) {
	Vector3D* Out;

//	float FloatSteps = Steps+Steps;
	float FloatSteps = 1.0f / (float)(Steps+Steps);
	
	float BaseAngle = ArcTan2( -Normal.x, Normal.y );
    
    // NOTE: <= is not < //
	for ( st32 idx = 0; idx <= Steps; idx++ ) {
		Out = (Vector3D*)Dest++;
		Out->x = Pos.x + (Real::Cos(idx * FloatSteps + BaseAngle) * Radius);
		Out->y = Pos.y + (Real::Sin(idx * FloatSteps + BaseAngle) * Radius);
		Out->z = Pos.z;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_HalfCircle( T* Dest, const Vector2D& Pos, const Real& Radius, const Vector3D& Normal, const st32 Steps = 16 ) {
	generate_Vertex3D_HalfCircle( Dest, Pos.ToVector3D(), Radius, Normal, Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_HalfCircle( const st32 Steps = 16 ) {
	return Steps+1;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_HalfCircle( const Vector3D&, const Real&, const st32 Steps = 16 ) {
	return size_Vertex3D_HalfCircle( Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_HalfCircle( const Vector2D&, const Real&, const st32 Steps = 16 ) {
	return size_Vertex3D_HalfCircle( Steps );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GENERATE_VERTEX_HALFCIRCLE_H__ //
// - ------------------------------------------------------------------------------------------ - //
