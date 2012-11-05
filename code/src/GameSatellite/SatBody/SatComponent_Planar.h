// - ------------------------------------------------------------------------------------------ - //
#ifndef __SATBODY_COMPONENT_PLANAR_H__
#define __SATBODY_COMPONENT_PLANAR_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelTypes.h>
#include <Core/GelArray.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cSatComponent_Planar {
public:
	int	Type;

public:
	class Plane {
	public:
		Vector3D Point;
		Vector3D Normal;
	public:
		Plane() :
			Point(0,0,0),
			Normal(0,0,0)
		{
		}

		Plane( const Real px, const Real py, const Real pz, const Real nx, const Real ny, const Real nz ) :
			Point(px,py,pz),
			Normal(nx,ny,nz)
		{
		}
	};

public:
	GelArray<Plane>* Data;
	
public:
	void Add( ) {
		// Create or Resize Component //
		pushback_GelArray<Plane>( &Data );
		Plane* Back = back_GelArray<Plane>( Data );
		
		Back->Point = Vector3D(1,1,1);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SATBODY_COMPONENT_PLANAR_H__ //
// - ------------------------------------------------------------------------------------------ - //
