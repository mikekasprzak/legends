// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_INSTANCE_H__
#define __PLAYMORE_INSTANCE_H__
// - ------------------------------------------------------------------------------------------ - //
// Instances exist in the game world. Instances are simplified, lightweight, whatever dynamic //
// data is needed by an Object to exist. This can be as simple as a position, or as complex as //
// a rigid body. //
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include "Object.h"
// - ------------------------------------------------------------------------------------------ - //
class cInstance {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cInstance thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cObject* Object;
	
	// Family //
	cInstance* Parent;
	cInstance* Child;	// TODO: Make this in to some sort of linked list. //
	
	// Position and AABB //
	Vector3D Pos;
	Vector3D Shape; // Together they make an AABB //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cInstance() :
		Parent( 0 ),
		Child( 0 ),
		Pos( Vector3D::Zero ),
		Shape( Vector3D::Zero )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline const Vector3D GetPos() {
		return Pos;
	}
	inline const Matrix4x4& GetTransform() {
		return Matrix4x4::Identity;
	}
	
public:
	inline void Step() {
		
	}
	
	inline void Draw() {
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_INSTANCE_H__ //
// - ------------------------------------------------------------------------------------------ - //
