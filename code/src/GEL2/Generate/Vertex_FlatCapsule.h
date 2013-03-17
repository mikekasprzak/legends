// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GENERATE_VERTEX_FLATCAPSULE_H__
#define __GEL2_GENERATE_VERTEX_FLATCAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
// Flat Capsule has no End Cap //
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_FlatCapsule( T* Dest, const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB ) {
	Vector3D* Out;

	Vector3D Line = PosB - PosA;
	Vector3D Tangent = cross(Line,Vector3D(0,0,1)).Normal();
	Vector3D LineNormal = Line.Normal();
	
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosA.x + (RadiusA * Tangent.x), PosA.y + (RadiusA * Tangent.y), PosA.z );
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosB.x + (RadiusB * Tangent.x), PosB.y + (RadiusB * Tangent.y), PosB.z );
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosB.x - (RadiusB * Tangent.x), PosB.y - (RadiusB * Tangent.y), PosB.z );
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosA.x - (RadiusB * Tangent.x), PosA.y - (RadiusA * Tangent.y), PosA.z );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_FlatCapsule( T* Dest, const Vector2D& PosA, const Real& RadiusA, const Vector2D& PosB, const Real& RadiusB ) {
	generate_Vertex3D_FlatCapsule( Dest, PosA.ToVector3D(), RadiusA, PosB.ToVector3D(), RadiusB );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_FlatCapsule() {
	return 4;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_FlatCapsule( const Vector3D&, const Real&, const Vector3D&, const Real& ) {
	return size_Vertex3D_FlatCapsule();
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_FlatCapsule( const Vector2D&, const Real&, const Vector2D&, const Real& ) {
	return size_Vertex3D_FlatCapsule();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GENERATE_VERTEX_FLATCAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
