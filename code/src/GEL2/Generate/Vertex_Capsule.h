// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GENERATE_VERTEX_CAPSULE_H__
#define __GEL2_GENERATE_VERTEX_CAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Capsule( T* Dest, const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const st32 Steps = 32 ) {
	Vector3D* Out;

	Vector3D Line = PosB - PosA;
	Vector3D Normal = Line.Normal();

//	float FloatSteps = Steps;
	float FloatSteps = 1.0f / (float)Steps;
	st32 HalfSteps = Steps >> 1;
	
	float BaseAngle = ArcTan2( Normal.x, -Normal.y );
    
    // NOTE: <= is not < //
	for ( st32 idx = 0; idx <= HalfSteps; idx++ ) {
		Out = (Vector3D*)Dest++;
		Out->x = PosA.x + (Real::Cos(idx * FloatSteps + BaseAngle) * RadiusA);
		Out->y = PosA.y + (Real::Sin(idx * FloatSteps + BaseAngle) * RadiusA);
		Out->z = PosA.z;
	}

	for ( st32 idx = HalfSteps; idx <= Steps; idx++ ) {
		Out = (Vector3D*)Dest++;
		Out->x = PosB.x + (Real::Cos(idx * FloatSteps + BaseAngle) * RadiusB);
		Out->y = PosB.y + (Real::Sin(idx * FloatSteps + BaseAngle) * RadiusB);
		Out->z = PosB.z;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Capsule( T* Dest, const Vector2D& PosA, const Real& RadiusA, const Vector2D& PosB, const Real& RadiusB, const st32 Steps = 32 ) {
	generate_Vertex3D_Capsule( Dest, PosA.ToVector3D(), RadiusA, PosB.ToVector3D(), RadiusB, Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Capsule( const st32 Steps = 32 ) {
	return Steps+2;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Capsule( const Vector3D&, const Real&, const st32 Steps = 32 ) {
	return size_Vertex3D_Capsule( Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Capsule( const Vector2D&, const Real&, const st32 Steps = 32 ) {
	return size_Vertex3D_Capsule( Steps );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GENERATE_VERTEX_CAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
