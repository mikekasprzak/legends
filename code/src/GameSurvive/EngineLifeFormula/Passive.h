// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_PASSIVE_H__
#define __LIFEFORMULA_PASSIVE_H__
// - ------------------------------------------------------------------------------------------ - //
// Passive Object -- An Instance of a Passive Object //
// - ------------------------------------------------------------------------------------------ - //
#include "PassiveTemplate.h"
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cPassive {
public:
	const cPassiveTemplate* 		Template;	// What we the instance are an instance of //
	const class cActiveTemplate*	Parent;		// What we're made of (Bear Meat, Birch Wood) //
	size_t 							Count;		// How many in this pile // 
public:
	inline cPassive() :
		Template(0),
		Parent(0),
		Count(1)
	{
	}
	
	inline cPassive( const cPassiveTemplate* _Template, const size_t _Count = 1 ) :
		Template( _Template ),
		Parent(0),
		Count( _Count )
	{
	}
	
public:
	void Step();
	void Draw();	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_PASSIVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
