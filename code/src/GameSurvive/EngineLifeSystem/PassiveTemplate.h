// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFESYSTEM_PASSIVETEMPLATE_H__
#define __LIFESYSTEM_PASSIVETEMPLATE_H__
// - ------------------------------------------------------------------------------------------ - //
// Passive Template Object -- Common properties between all instances this Object //
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
// - ------------------------------------------------------------------------------------------ - //
namespace LifeSystem {
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
}; // namepsace LifeSystem //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFESYSTEM_PASSIVETEMPLATE_H__ //
// - ------------------------------------------------------------------------------------------ - //
