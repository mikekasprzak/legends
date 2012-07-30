// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_ACTIVETEMPLATE_H__
#define __LIFEFORMULA_ACTIVETEMPLATE_H__
// - ------------------------------------------------------------------------------------------ - //
// Active Template Object -- Common properties between all instances this Object //
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cActiveTemplate {
public:
	cActiveTemplate* Parent;		// If we are a mutation, what were we? //
	int InventorySize;				// How many things you can hold //
public:
	cActiveTemplate() :
		Parent(0),
		InventorySize( 0 )
	{
	}
	
public:
	void Load( const char* InFile );
	void Save( const char* OutFile );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ACTIVETEMPLATE_H__ //
// - ------------------------------------------------------------------------------------------ - //
