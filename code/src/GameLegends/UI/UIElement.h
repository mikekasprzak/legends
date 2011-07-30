// - ------------------------------------------------------------------------------------------ - //
#ifndef __UIElement_H__
#define __UIElement_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Bits.h>
// - ------------------------------------------------------------------------------------------ - //
// - Text Strings without Font
// - Text Strings with Font
// - Vertices, UVs, Colors without Texture
// - Vertices, UVs, Colors with Texture
// - Slice with Texture
// - Slice without Texture
// - Scrollable Border/View
// - Another one of these (recursive)
// - ------------------------------------------------------------------------------------------ - //
enum {
	UI_DUMMY = 0,
	UI_SLICE = 1,
	UI_GRAPHIC,
	UI_TEXTURE_SLICE,
	UI_GEOMETRY,
	UI_TEXTURE_GEOMETRY,
	UI_TEXT,
};
// - ------------------------------------------------------------------------------------------ - //
// Original Alignments (Note, treat zero and 2 as centering) //
enum {
	UIA_HCENTER = 2 << 0,
	UIA_VCENTER = 2 << 2,
	
	UIA_HLEFT = 1 << 0,
	UIA_HRIGHT = 3 << 0,
	UIA_VTOP = 1 << 2,
	UIA_VBOTTOM = 3 << 2,

	
	UIA_HMASK = 3 << 0,
	UIA_VMASK = 3 << 2,
	
	UIA_MASK = UIA_HMASK | UIA_VMASK,
};
// - ------------------------------------------------------------------------------------------ - //
enum {
	UIA_DEFAULT = UIA_HCENTER | UIA_VCENTER,
	
	UIA_CENTER_CENTER = UIA_HCENTER | UIA_VCENTER,
	UIA_CENTER = UIA_HCENTER | UIA_VCENTER,

	UIA_LEFT = UIA_HLEFT | UIA_VCENTER,
	UIA_RIGHT = UIA_HRIGHT | UIA_VCENTER,

	UIA_TOP = UIA_HCENTER | UIA_VTOP,
	UIA_BOTTOM = UIA_HCENTER | UIA_VBOTTOM,

	UIA_TOP_LEFT = UIA_HLEFT | UIA_VTOP,
	UIA_TOP_CENTER = UIA_HCENTER | UIA_VTOP,
	UIA_TOP_RIGHT = UIA_HRIGHT | UIA_VTOP,
	UIA_BOTTOM_LEFT = UIA_HLEFT | UIA_VBOTTOM,
	UIA_BOTTOM_CENTER = UIA_HCENTER | UIA_VBOTTOM,
	UIA_BOTTOM_RIGHT = UIA_HRIGHT | UIA_VBOTTOM,
	UIA_CENTER_LEFT = UIA_HLEFT | UIA_VCENTER,
	UIA_CENTER_RIGHT = UIA_HRIGHT | UIA_VCENTER,

	UIA_LEFT_TOP = UIA_HLEFT | UIA_VTOP,
	UIA_CENTER_TOP = UIA_HCENTER | UIA_VTOP,
	UIA_RIGHT_TOP = UIA_HRIGHT | UIA_VTOP,
	UIA_LEFT_BOTTOM = UIA_HLEFT | UIA_VBOTTOM,
	UIA_CENTER_BOTTOM = UIA_HCENTER | UIA_VBOTTOM,
	UIA_RIGHT_BOTTOM = UIA_HRIGHT | UIA_VBOTTOM,
	UIA_LEFT_CENTER = UIA_HLEFT | UIA_VCENTER,
	UIA_RIGHT_CENTER = UIA_HRIGHT | UIA_VCENTER,
};
// - ------------------------------------------------------------------------------------------ - //
enum {
	UIF_INVISIBLE = bit4,
	UIF_VARIABLE = bit5,
	UIF_RANGE = bit6,
	UIF_NOSORT = bit7,
};
// - ------------------------------------------------------------------------------------------ - //
struct cUIElement {
	// 16 Bytes //
	short Type;
	short Flags; // Alignment (Bits 0-3) and more //

	int x;
	int y;

	float Scale;  // 1
	
	// 16 Bytes //
	union {
		int _PAD1;
		int DataIndex;		// Index in to the array of whatever type this is //
	};
	
	// WARNING! THIS DIDN'T WORK ON 64BIT BECAUSE OF POINTERS! //
	union {
		int _PAD2;
//		char* FontName;
		int FontIndex;
		
//		char* TextureName;
		int TextureIndex;
	};
	
	union {
		int _PAD3;
		struct {
			short Value;
			short _PAD;
		};
	};
		
	union {
		int _PAD4;
		struct {
			short Min;
			short Max;
		};
	};
#ifdef __VERSION__ // GCC //
} __attribute__((packed));
#else // NOT GCC //
};
#endif // __VERSION__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // __UIElement_H__ /
// - ------------------------------------------------------------------------------------------ - //
