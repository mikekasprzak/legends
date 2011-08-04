// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_CONSTANTS_H__
#define __GEL_CONSTANTS_H__
// - ------------------------------------------------------------------------------------------ - //
// Executive Decision: Center goes with Left and Right. Middle with Top and Bottom //
// - ------------------------------------------------------------------------------------------ - //
enum GEL_Align {
	GEL_ALIGN_LEFT			= 0x1,
	GEL_ALIGN_CENTER		= 0x2,
	GEL_ALIGN_RIGHT			= 0x3,

	GEL_ALIGN_TOP			= 0x1<<2,
	GEL_ALIGN_MIDDLE		= 0x2<<2,
	GEL_ALIGN_BOTTOM		= 0x3<<2,

	GEL_ALIGN_TOP_LEFT		= GEL_ALIGN_TOP | GEL_ALIGN_LEFT,
	GEL_ALIGN_TOP_CENTER	= GEL_ALIGN_TOP | GEL_ALIGN_CENTER,
	GEL_ALIGN_TOP_RIGHT		= GEL_ALIGN_TOP | GEL_ALIGN_RIGHT,

	GEL_ALIGN_MIDDLE_LEFT	= GEL_ALIGN_MIDDLE | GEL_ALIGN_LEFT,
	GEL_ALIGN_MIDDLE_CENTER	= GEL_ALIGN_MIDDLE | GEL_ALIGN_CENTER,
	GEL_ALIGN_MIDDLE_RIGHT	= GEL_ALIGN_MIDDLE | GEL_ALIGN_RIGHT,

	GEL_ALIGN_BOTTOM_LEFT	= GEL_ALIGN_BOTTOM | GEL_ALIGN_LEFT,
	GEL_ALIGN_BOTTOM_CENTER	= GEL_ALIGN_BOTTOM | GEL_ALIGN_CENTER,
	GEL_ALIGN_BOTTOM_RIGHT	= GEL_ALIGN_BOTTOM | GEL_ALIGN_RIGHT,

	GEL_ALIGN_DEFAULT		= GEL_ALIGN_MIDDLE_CENTER,
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif //__GEL_CONSTANTS_H__ //
// - ------------------------------------------------------------------------------------------ - //
