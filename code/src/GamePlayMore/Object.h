// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYMORE_OBJECT_H__
#define __PLAYMORE_OBJECT_H__
// - ------------------------------------------------------------------------------------------ - //
// Objects describe things that *CAN* exist in the game world. They're like templates for things //
// that can be created. To exist in the game world, you need an Instance. //
// - ------------------------------------------------------------------------------------------ - //
class cObject {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef cObject thistype;
	inline void* GetThis() { return this; }
public: // - Member Variables ----------------------------------------------------------------- - //
	// Collision //
	// Artwork //
	// Code //

public: // - Constructors and Destructors ----------------------------------------------------- - //
	cObject()
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYMORE_OBJECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
