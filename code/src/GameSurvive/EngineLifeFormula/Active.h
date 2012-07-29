// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_ACTIVE_H__
#define __LIFEFORMULA_ACTIVE_H__
// - ------------------------------------------------------------------------------------------ - //
// Active Object -- An Instance of an Active Object //
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelArray.h>

#include "ActiveTemplate.h"
#include "Passive.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cActive {
public:
	const cActiveTemplate* Template;	// What we're based on //
public:
	int PosIndex;						// Position Index //
	cGelArrayPtr<cPassive*> Inventory;
public:
	// Default Constructor -- Should probably not be called //
	inline cActive() :
		Template(0),
		PosIndex(-1)
	{
	}

	// All Objects should be constructed based on a template //
	inline cActive( const cActiveTemplate* _Template ) :
		Template( _Template ),
		PosIndex( -1 ),
		Inventory( _Template->InventorySize )
	{
	}

	// Destructor //	
	inline ~cActive() {
		Inventory._DeleteAll(); // Underscore version, because I know nulling isn't needed //
	}
	
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ACTIVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
