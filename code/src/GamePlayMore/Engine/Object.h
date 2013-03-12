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
#include <vector>

#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>

#include "Template.h"
#include "UID.h"
#include "KeyStore.h"
#include "Body.h"
// - ------------------------------------------------------------------------------------------ - //
class cObject {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cObject thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	cTemplate* Template;				// Refernce to our Parent Template (Not Parent Object) //
	cUID UID;							// UniqueId for this Object //
	
	// Family //
	cObject* Parent;					// My Parent Object. Zero if I have no parent //
	std::vector<cObject*> Child;		// Our Children //
	
	// Variables //
	cKeyStore OVar;						// Key (Variable) Storage //
	
	// Collision //
	cBody* Body;						// TODO: Do some stuff like Flex here.

	// Sensors //
	std::vector<cBody*> Sensor; 		// Our Sensors //

	// Position and AABB //
	Rect3D Rect;
	Rect3D SensorRect; 					// Sum of all Sensors //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cObject() :
		Template( 0 ),
		Parent( 0 ),
		Body( 0 ),
		Rect( Vector3D::Zero, Vector3D::Zero )
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline const Vector3D GetPos() {
		return Rect.Center();
	}
	inline const Matrix4x4& GetTransform() {
		if ( Body ) {
			return Body->GetTransform();
		}
		else {
			return Matrix4x4::Identity;
		}
	}
	
	void Notify( cObject* Reciever, const int Message ) {
		cObject* TempObject = Shared.Object;
		cTemplate* TempTemplate = Shared.Template;
		Shared.Object = Reciever;
		Shared.Template = Reciever->Template;
		
		Reciever->Template->Notice( Reciever, this, Message );
		
		Shared.Template = TempTemplate;
		Shared.Object = TempObject;
	}

public:	
	void Step();
	void Draw( const Matrix4x4& Matrix );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_OBJECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
