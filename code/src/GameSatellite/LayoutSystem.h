

enum {
	// Four Split //
	// +-----+-----+ //
	// |  0  |  1  | //
	// +-----+-----+ //
	// |  2  |  3  | //
	// +-----+-----+ //
	RR_FOUR_0 = 			0x1,
	RR_FOUR_1 = 			0x2,
	RR_FOUR_2 = 			0x4,
	RR_FOUR_3 = 			0x8,
	
	RR_FOUR =				(RR_FOUR_0|RR_FOUR_1|RR_FOUR_2|RR_FOUR_3),
	RR_FOUR_TOPLEFT =		RR_FOUR_0,
	RR_FOUR_TOPRIGHT =		RR_FOUR_1,
	RR_FOUR_BOTTOMLEFT =	RR_FOUR_2,
	RR_FOUR_BOTTOMRIGHT =	RR_FOUR_3,

	// Six Split (Wide) //
	// +---+---+---+ //
	// | 0 | 1 | 2 | //
	// +---+---+---+ //
	// | 3 | 4 | 5 | //
	// +---+---+---+ //
	RR_SIXW_0 = 			0x10,
	RR_SIXW_1 = 			0x20,
	RR_SIXW_2 = 			0x40,
	RR_SIXW_3 = 			0x80,
	RR_SIXW_4 = 			0x100,
	RR_SIXW_5 = 			0x200,

	RR_SIXW =				(RR_SIXW_0|RR_SIXW_1|RR_SIXW_2|RR_SIXW_3|RR_SIXW_4|RR_SIXW_5),
	RR_SIXW_TOPLEFT =		RR_SIXW_0,
	RR_SIXW_TOPMIDDLE =		RR_SIXW_1,
	RR_SIXW_TOPRIGHT =		RR_SIXW_2,
	RR_SIXW_BOTTOMLEFT =	RR_SIXW_3,
	RR_SIXW_BOTTOMMIDDLE =	RR_SIXW_4,
	RR_SIXW_BOTTOMRIGHT =	RR_SIXW_5,

	// Six Split (Tall) //
	// +---+---+ //
	// | 0 | 1 | //
	// +---+---+ //
	// | 2 | 3 | //
	// +---+---+ //
	// | 4 | 5 | //
	// +---+---+ //
	RR_SIXT_0 = 			0x400,
	RR_SIXT_1 = 			0x800,
	RR_SIXT_2 = 			0x1000,
	RR_SIXT_3 = 			0x2000,
	RR_SIXT_4 = 			0x4000,
	RR_SIXT_5 = 			0x8000,

	RR_SIXT =				(RR_SIXT_0|RR_SIXT_1|RR_SIXT_2|RR_SIXT_3|RR_SIXT_4|RR_SIXT_5),
	RR_SIXT_TOPLEFT =		RR_SIXT_0,
	RR_SIXT_TOPRIGHT =		RR_SIXT_1,
	RR_SIXT_MIDDLELEFT =	RR_SIXT_2,
	RR_SIXT_MIDDLERIGHT =	RR_SIXT_3,
	RR_SIXT_BOTTOMLEFT =	RR_SIXT_4,
	RR_SIXT_BOTTOMRIGHT =	RR_SIXT_5,

	// Question: Should the ID's map to the same layout as the SIXW? That way the code can be the same? //
};

// TODO: Make a table of which layouts it's part of? Four RR_FOUR's, Six RR_SIXW's, etc. //

// Halfs //
#define H0 (0.0f)
#define H1 (0.5f)
#define H2 (1.0f)

// Thirds //
#define T0 (0.0f/3.0f)
#define T1 (1.0f/3.0f)
#define T2 (2.0f/3.0f)
#define T3 (3.0f/3.0f)

// Render Regions in "0 to 1" format (same as glViewport, but it takes w,h) //
const float RenderRegion[] = {
	// Four Split -- 2x2 (H,H) //
	H0,H0,H1,H1,
	H1,H0,H2,H1,
	H0,H1,H1,H2,
	H1,H1,H2,H2,
	
	// Six Split (Wide) -- 3x2 (T,H) //
	T0,H0,T1,H1,
	T1,H0,T2,H1,
	T2,H0,T3,H1,
	T0,H1,T1,H2,
	T1,H1,T2,H2,
	T2,H1,T3,H2,
	
	// Six Split (Tall) -- 2x3 (H,T) //
	H0,T0,H1,T1,
	H1,T0,H2,T1,
	H0,T1,H1,T2,
	H1,T1,H2,T2,
	H0,T2,H1,T3,
	H1,T2,H2,T3,	
};

#undef H0
#undef H1
#undef H2
#undef T0
#undef T1
#undef T2
#undef T3

// Layout systems should always work in "0 to 1" or "-1 to +1" figures. //
// Minimap placement should be in a corner of an overscan-like rectangle. //

