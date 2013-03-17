// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GENERATE_VERTEX_CUBE_H__
#define __GEL2_GENERATE_VERTEX_CUBE_H__
// - ------------------------------------------------------------------------------------------ - //
// Draw using GEL_LINES //
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Cube( T* Dest, const Vector3D& Pos, const Vector3D& Shape ) {
	Vector3D* Out;
	
	// Top //
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._000();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._x00();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._x00();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._xy0();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._xy0();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._0y0();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._0y0();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._000();

	// Bottom //
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._00z();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._x0z();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._x0z();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._xyz();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._xyz();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._0yz();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._0yz();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._00z();
	
	// Side //
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._000();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._00z();

	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._x00();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._x0z();

	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._xy0();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._xyz();

	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._0y0();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Shape._0yz();
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Cube() {
	return 8+8+4+4;
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Cube( const Vector3D&, const Vector3D& ) {
	return size_Vertex3D_Cube();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GENERATE_VERTEX_CUBE_H__ //
// - ------------------------------------------------------------------------------------------ - //
