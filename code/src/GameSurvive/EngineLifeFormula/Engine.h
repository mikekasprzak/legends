// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_ENGINE_H__
#define __LIFEFORMULA_ENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
// LifeFormula Engine -- A rigid grid based world simulation //
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>

#include "Active.h"
#include "Passive.h"
#include "Tile.h"

#include "Room.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cEngine {
public:
	static cEngine* Instance;

	static cGelArrayPtr<cActiveTemplate*>	ActiveTemplate;		// Pointers because every time these 2 Arrays
	static cGelArrayPtr<cPassiveTemplate*>	PassiveTemplate;	//   resize, the addresses would break.
public:
	cRoom* Room;
public:
	cEngine() {
		Instance = this; // *IMPORTANT* THIS MUST COME FIRST BEFORE ANY ROOMS ARE CREATED! //
		// - ----- - //		
		Room = new cRoom( 32, 32 );
	}

	~cEngine() {
		delete Room;
		
		ActiveTemplate._DeleteAll();
		PassiveTemplate._DeleteAll();
	}		
public:
	// Static Functions (using the Instance) //
	inline static cActiveTemplate* LoadActiveTemplate( const char* FileName ) {
		cEngine::ActiveTemplate.PushBack( new cActiveTemplate() );
		cEngine::ActiveTemplate.Back()->Load( FileName );
		return cEngine::ActiveTemplate.Back();
	}
	
	inline static cPassiveTemplate* LoadPassiveTemplate( const char* FileName ) {
		cEngine::PassiveTemplate.PushBack( new cPassiveTemplate() );
		cEngine::PassiveTemplate.Back()->Load( FileName );
		return cEngine::PassiveTemplate.Back();
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
