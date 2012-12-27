// - ------------------------------------------------------------------------------------------ - //
#ifndef __SATBODY_COMPONENT_PLANAR_H__
#define __SATBODY_COMPONENT_PLANAR_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/GelStyle.h>
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
		inline Plane() :
			Point(0,0,0),
			Normal(0,0,0)
		{
		}

		inline Plane( const Vector3D& _Point, const Vector3D& _Normal ) :
			Point( _Point ),
			Normal( _Normal )
		{
		}

		inline Plane( const Real px, const Real py, const Real pz, const Real nx, const Real ny, const Real nz ) :
			Point(px,py,pz),
			Normal(nx,ny,nz)
		{
		}
	public:
		inline void Set( const Vector3D& _Point, const Vector3D& _Normal ) {
			Point = _Point;
			Normal = _Normal;
		}
	};

public:
	GelArray<Plane>* Data;
	
public:
	inline void New( const size_t Count = 0 ) {
		Data = new_GelArray<Plane>( Count );
	}
	inline void Delete() {
		delete_GelArray<Plane>( Data );
		Data = 0;
	}
	
	void Add( ) {
		pushback_GelArray<Plane>( &Data );
		Plane* Back = back_GelArray<Plane>( Data );
		
		Back->Point = Vector3D(1,1,1);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SATBODY_COMPONENT_PLANAR_H__ //
// - ------------------------------------------------------------------------------------------ - //
