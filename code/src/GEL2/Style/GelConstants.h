// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_STYLE_CONSTANTS_H__
#define __GEL2_STYLE_CONSTANTS_H__
// - ------------------------------------------------------------------------------------------ - //
// Executive Decision: Center goes with Left and Right. Middle with Top and Bottom //
// - ------------------------------------------------------------------------------------------ - //
enum GelAlign {
	// Horizontal //
	GEL_ALIGN_LEFT				= 0x1,
	GEL_ALIGN_CENTER			= 0x2,
	GEL_ALIGN_RIGHT				= 0x3,

	// Vertical //
	GEL_ALIGN_TOP				= 0x1<<4,
	GEL_ALIGN_MIDDLE			= 0x2<<4,
	GEL_ALIGN_BOTTOM			= 0x3<<4,
	GEL_ALIGN_BASELINE			= 0x6<<4,		// Includes MIDDLE bit as a fallback //
	
	// Bitmasks for each bit alignement set //
	GEL_ALIGN_HBITS				= 0x3<<0,
	GEL_ALIGN_VBITS				= 0x3<<4,

	// Bitmasks for each font bit aligment set //
	GEL_ALIGN_FONT_HBITS		= 0x3<<0,
	GEL_ALIGN_FONT_VBITS		= 0x7<<4,

	// Bitmasks for all bit alignement sets //
	GEL_ALIGN_ALL_HBITS			= 0xF<<0,
	GEL_ALIGN_ALL_VBITS			= 0xF<<4,

	GEL_ALIGN_TOP_LEFT			= GEL_ALIGN_TOP | GEL_ALIGN_LEFT,
	GEL_ALIGN_TOP_CENTER		= GEL_ALIGN_TOP | GEL_ALIGN_CENTER,
	GEL_ALIGN_TOP_RIGHT			= GEL_ALIGN_TOP | GEL_ALIGN_RIGHT,

	GEL_ALIGN_MIDDLE_LEFT		= GEL_ALIGN_MIDDLE | GEL_ALIGN_LEFT,
	GEL_ALIGN_MIDDLE_CENTER		= GEL_ALIGN_MIDDLE | GEL_ALIGN_CENTER,
	GEL_ALIGN_MIDDLE_RIGHT		= GEL_ALIGN_MIDDLE | GEL_ALIGN_RIGHT,

	GEL_ALIGN_BOTTOM_LEFT		= GEL_ALIGN_BOTTOM | GEL_ALIGN_LEFT,
	GEL_ALIGN_BOTTOM_CENTER		= GEL_ALIGN_BOTTOM | GEL_ALIGN_CENTER,
	GEL_ALIGN_BOTTOM_RIGHT		= GEL_ALIGN_BOTTOM | GEL_ALIGN_RIGHT,

	GEL_ALIGN_BASELINE_LEFT		= GEL_ALIGN_BASELINE | GEL_ALIGN_LEFT,
	GEL_ALIGN_BASELINE_CENTER	= GEL_ALIGN_BASELINE | GEL_ALIGN_CENTER,
	GEL_ALIGN_BASELINE_RIGHT	= GEL_ALIGN_BASELINE | GEL_ALIGN_RIGHT,

//	GEL_ALIGN_DEFAULT			= GEL_ALIGN_MIDDLE_CENTER,
	GEL_ALIGN_DEFAULT			= GEL_ALIGN_BASELINE_CENTER,
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif //__GEL2_STYLE_CONSTANTS_H__ //
// - ------------------------------------------------------------------------------------------ - //
