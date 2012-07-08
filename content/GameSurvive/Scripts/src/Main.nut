
// -- Smallest Wood Parts -- //

local OB_WoodChips = {
	Name = "Wood Chips"
};

local OB_Stick = {
	Name = "Stick"
};

local OB_LongStick = {
	Name = "Long Stick"
};

// -- Larger Wood Parts -- //

local OB_Wood = { // Wood, Lumber, Timber, Log, Stump //
	Name = "Wood"
};

local OB_LongWood = {
	Name = "Long Wood"
};

// -- Rocks -- //

local OB_Rock = {
	Name = "Rock"
};

local OB_BowedRock = {
	Name = "Bowed Rock"
};

local OB_LongRock = {
	Name = "Long Rock"
};

local OB_SharpRock = {
	Name = "Sharp Rock"
};

// -- -------------------------- -- //

local OB_Spear = {
	Name = "Spear"
};

local OB_Hammer = {
	Name = "Hammer"
};

// -- -------------------------- -- //

local CraftingRecipes = [
	// Tools and Weapons //
	{	In = [ OB_Stick, OB_Rock ],
		Out = [ OB_Hammer ] },
	{	In = [ OB_LongStick, OB_Rock ],
		Out = [ OB_Spear ] },
];

// TODO: Sort objects in the craft boxes alphabetically by name, and scan the recipe list like so. //

// -- -------------------------- -- //

function DoAwesome() {
	print( format("This function does SILLY things! -> %s\n", OB_Stick.Name ) );
}


