// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_PASSIVETEMPLATE_H__
#define __LIFEFORMULA_PASSIVETEMPLATE_H__
// - ------------------------------------------------------------------------------------------ - //
// Passive Template Object -- Common properties between all instances this Object //
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cPassiveTemplate {
public:
	size_t	MaxCount;		// The Maximum number allowed in one pile //
public:
	cPassiveTemplate() :
		MaxCount(1)
	{
	}
	
public:
	void Load( const char* InFile );
	void Save( const char* OutFile );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_PASSIVETEMPLATE_H__ //
// - ------------------------------------------------------------------------------------------ - //
