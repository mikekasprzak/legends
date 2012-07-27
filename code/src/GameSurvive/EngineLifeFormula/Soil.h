// - ------------------------------------------------------------------------------------------ - //
#ifndef __LIFEFORMULA_SOIL_H__
#define __LIFEFORMULA_SOIL_H__
// - ------------------------------------------------------------------------------------------ - //
// Soil -- 
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Integer.h>
// - ------------------------------------------------------------------------------------------ - //
namespace LifeFormula {
// - ------------------------------------------------------------------------------------------ - //
class cSoil {
public:
	Integer Mineral;
	Integer Organic;
	Integer Water;
	
	Integer Dummy;		// To be replaced by something real //
	
	// Temperature? //
	// Radiation -- Some article I was reading said some plants are unaffected by Chernoble //
	// Acidity/Ph Level vs Alkalinity //
	// Roots -- Raises the solidity while maintaining moisture
	// Moisture (Water) -- Does the absense of moisture raises the solidity?
public:
	cSoil() :
		Mineral( 25 ),
		Organic( 25 ),
		Water( 25 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_SOIL_H__ //
// - ------------------------------------------------------------------------------------------ - //
