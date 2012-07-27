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
	cGelArrayPtr<cPassive*> Inventory;
public:
	inline cActive() :
		Template(0)
	{
	}
	
	inline ~cActive() {
		Inventory.DeleteAll();
	}

	inline cActive( const cActiveTemplate* _Template ) :
		Template( _Template )
	{
	}
	
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ACTIVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
