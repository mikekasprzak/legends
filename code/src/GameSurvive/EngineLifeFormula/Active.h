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
	// Essential Properties //
	const cActiveTemplate* Template;	// What we're based on //
	int PosIndex;						// Position Index //
public:
	// Instance Properties //
	cGelArrayPtr<cPassive*> Inventory;
	
	// *STATS* //
	// Health
	//   HP growth can be represented by immunities increasing with the stat raising to show precion
	// Energy 
	//   Replenish with sleep/caffeine
	// Hunger
	//   Hydration? Dehydrated causes headaches and weakness.
	//   Fruit = High Hydration Foods. Meat = Low Hydration, High Protein
	// Mental State? a +/- stat. Caffeine and Drugs are -, but not sure what's +.
	//   Addiction can be a dynamic property. Moves the Mental State center?
	//   Mental State describes Sensitivity? - Mellow/Numbness vs + Twitchy/Act-Before-Thinking

	// Other Stat Considerations? //
	// Body Stats
	//   All statistics that shape the statistics
	// Body State?
	//   Serious Injury - Losing a limb would permanently affect Health
	//   Injury - Breaking a leg would affect Health, but would heal over time
	//   Wound - Cuts, scrapes, and blood loss. 
	//   A lizard is capable of healing Serious Injuries. Regeneration Property.
	// Illness
	//   Inflicted - Can only be explicitly given
	//   Contageous - Some function that gives to neighbours under conditions
	// A Rock
	//   Unaffected by Energy and Hunger
	// A Tree
	//   Unaffected by Energy (doesn't move), but still hungers. Eats Soil Minerals, Sunlight, Moisture
	// Food
	//   Carbohydrate - Complex Carb (starch, i.e. cereal, bread, pasta), Simple Carb (sugar, i.e. Candy, jam, dessert)
	//   Fat - Animal (Lard, Fish Oil, Butter, Whale Blubber), Plant Oils (Peanut, Soya Bean, Sunflower, Sesame, Coconut, Olive)
	//   Protein - Provider of Amino Acids (Fuel?). Microorganisms can produce all essential acids. Animals get them from food.
	//   Vitamin Classes - A B C D E K -- Water Soluable B C -- Fat Soluable A D E K
	//   (Wikipedia Says: Carbs not required. the body can obtain all its energy from protein and fats)
	
	// Other Stats generate the Baseline Stat values via a scripted function called during a //
	//   Body State Change. Growth, Injuries, etc.
public:
	// Default Constructor -- Should probably not be called //
	inline cActive() :
		Template(0),
		PosIndex(-1)
	{
	}

	// All Objects should be constructed based on a template //
	inline cActive( const cActiveTemplate* _Template ) :
		Template( _Template ),
		PosIndex( -1 ),
		Inventory( _Template->InventorySize )
	{
	}

	// Destructor //	
	inline ~cActive() {
		Inventory._DeleteAll(); // Underscore version, because I know nulling isn't needed //
	}
	
public:
	void Step( class cRoom* Room );
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
}; // namepsace LifeFormula //
// - ------------------------------------------------------------------------------------------ - //
#endif // __LIFEFORMULA_ACTIVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
