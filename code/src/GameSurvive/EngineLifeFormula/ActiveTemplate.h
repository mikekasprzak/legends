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
	int InventorySize;
public:
	cActiveTemplate() :
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
