// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_OBJECT_H__
#define __PLAYMORE_OBJECT_H__
// - ------------------------------------------------------------------------------------------ - //
// Objects are things in the game. An Object can be on 1 of 2 lists: The Active and the Inactive //
// lists. The Active list is for objects and parent objects that are actively in the world. The //
// Inactive list is for objects that are children of parent objects. Possibly, this distinction //
// isn't clear enough. The other option is to call the Inactive list the Children list, or the //
// Parent and Child lists respectfully (instead of Active). Any object that is a child becomes //
// responsibility of the Parent. The parent must explicitly step and notify the children //
// (assuming they're not shielding the children from information). Good design would be on death //
// to release all children, or if the object suits it, kill all children (how morbid!). //
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>

#include "Shared.h"
#include "Tag.h"
#include "Body.h"
#include "Template.h"
// - ------------------------------------------------------------------------------------------ - //
class cObject {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cObject thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cTemplate* Object;
	
	// Family //
	cObject* Parent;
	cObject* Child;	// TODO: Array //
	
	// Position and AABB //
	Rect3D Rect;

	// Tags //
	cTag* Tag; // TODO: Key/Value Pair //
	
	// Collision //
	cBody* Body;
	
	// Sensors //
	cBody* Sensor; // TODO: Array //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cObject() :
		Object( 0 ),
		Parent( 0 ),
		Child( 0 ),
		Rect( Vector3D::Zero, Vector3D::Zero ),
		Body( 0 ),
		Sensor( 0 )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline const Vector3D GetPos() {
		return Rect.Center();
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
#endif // __PLAYMORE_OBJECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
