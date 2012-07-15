// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLDANIMAL_H__
#define __WORLDANIMAL_H__
// - ------------------------------------------------------------------------------------------ - //
#include "WorldObject.h"
// - ------------------------------------------------------------------------------------------ - //
class cWorldAnimal: public cWorldObject {
public:
	int ChronoType;
	enum {
		CT_DEAD 		= 0, // Never Awake //
		CT_INSOMNIAC	= 1, // Always Awake //
		CT_DIURNAL 		= 2, // Day Awake //
		CT_NOCTURNAL	= 3, // Night Awake // 

		// CREPUSCULAR -- Twilight (Dawn/Dusk) //
		CT_MATUTINAL	= 4, // Dawn Awake //
		CT_VESPERTINE	= 5, // Dusk Awake //
		CT_BIMODAL		= 6, // Both Dawn and Dusk Awake //
		
		CT_CATHEMERAL	= 7, // Randomly Awake (like a pet cat) //
	};
	
	static int CtDead[];// 		= { 0,0,0,0,0,0,0,0 };
	static int CtInsomniac[];//	= { 1,1,1,1,1,1,1,1 };
	static int CtDiurnal[];//	= { 1,1,1,1,0,0,0,0 };
	static int CtNocturnal[];//	= { 0,0,0,0,1,1,1,1 };
	static int CtMatutinal[];//	= { 1,1,0,0,0,0,1,1 };
	static int CtVespertine[];//= { 0,0,1,1,1,1,0,0 };
	static int CtBimodal[];//	= { 1,0,0,1,1,0,0,1 };
public:
	cWorldAnimal() 
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLDANIMAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
