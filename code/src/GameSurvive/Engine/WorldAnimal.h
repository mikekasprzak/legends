// - ------------------------------------------------------------------------------------------ - //
#ifndef __WORLDANIMAL_H__
#define __WORLDANIMAL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Binary.h>
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
	
	//int ChronoMask;	// Hours of the day I am awake -- 24 hour //
	enum {
		CM_DAY			= (b11111111 << 16) | (b11110000 << 8) | b00000000,
		CM_NIGHT		= (b00000000 << 16) | (b00001111 << 8) | b11111111,
		
		CM_DAWN			= (b00000000 << 16) | (b00000000 << 8) | b00000001,
		CM_SUNRISE		= (b10000000 << 16) | (b00000000 << 8) | b00000000,
		CM_SUNSET		= (b00000000 << 16) | (b00010000 << 8) | b00000000,
		CM_DUSK			= (b00000000 << 16) | (b00001000 << 8) | b00000000,		
		
		CM_DEAD			= 0,
		CM_DIURNAL		= CM_DAY,
		CM_NOCTURNAL	= CM_NIGHT,
		CM_INSOMNIAC	= CM_DIURNAL | CM_NOCTURNAL,
		
		// Not entirely accurate (twilights only), but I prefer it to be a 2 hour period //
		CM_MATUTINAL	= CM_DAWN | CM_SUNRISE,
		CM_VESPERTINE	= CM_DUSK | CM_SUNSET,
		CM_BIMODAL		= CM_MATUTINAL | CM_VESPERTINE,
		
		CM_MASK			= (b11111111 << 16) | (b11111111 << 8) | b11111111
	};
public:
	cWorldAnimal() 
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __WORLDANIMAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
