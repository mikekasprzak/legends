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
		
		CT_CATHEMERAL	= 7, // Randomly Awake //
	};
public:
	cWorldAnimal() 
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLDANIMAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
