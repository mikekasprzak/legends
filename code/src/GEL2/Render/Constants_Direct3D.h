// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_RENDER_CONSTANTS_DIRECT3D_H__
#define __GEL2_RENDER_CONSTANTS_DIRECT3D_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_DIRECT3D11)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_D3D11.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Update unfinished constants below //

// - ------------------------------------------------------------------------------------------ - //
// Stencil Test and Depth Test Function Modes //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_NEVER								0//GL_NEVER
#define GEL_LESS								1//GL_LESS
#define GEL_LESSEQUAL							2//GL_LEQUAL
#define GEL_GREATER								3//GL_GREATER
#define GEL_GREATEREQUAL						4//GL_GEQUAL
#define GEL_EQUAL								5//GL_EQUAL
#define GEL_NOTEQUAL							6//GL_NOTEQUAL
#define GEL_ALWAYS								8//GL_ALWAYS
// - ------------------------------------------------------------------------------------------ - //
// Stencil Operations //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_KEEP								1//GL_KEEP
#define GEL_ZERO								2//GL_ZERO
#define GEL_REPLACE								3//GL_REPLACE
#define GEL_INVERT								4//GL_INVERT
#define GEL_INCR								5//GL_INCR			// Saturate //
#define GEL_DECR								6//GL_DECR			// Saturate //
#define GEL_INCRWRAP							7//GL_INCR_WRAP		// GL 1.4+, ES 2.0 and D3D //
#define GEL_DECRWRAP							8//GL_DECR_WRAP		// GL 1.4+, ES 2.0 and D3D //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Render Operations //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_POINTS								D3D11_PRIMITIVE_TOPOLOGY_POINTLIST
#define GEL_LINES								D3D11_PRIMITIVE_TOPOLOGY_LINELIST
#define GEL_LINE_STRIP							D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
#define GEL_TRIANGLES							D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
#define GEL_TRIANGLE_STRIP						D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP

#define GEL_LINE_LOOP							GEL_LINE_STRIP		// GL Only (Stub) //
#define GEL_TRIANGLE_FAN						GEL_TRIANGLE_STRIP	// GL Only (Stub) //

#define GEL_LINES_ADJ							D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ 		// D3D Only //
#define GEL_LINE_STRIP_ADJ						D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ		// D3D Only //
#define GEL_TRIANGLES_ADJ						D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ	// D3D Only //
#define GEL_TRIANGLE_STRIP_ADJ					D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ	// D3D Only //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DrawMode States //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_DRAWMODE_FLAT						0
#define GEL_DRAWMODE_COLORS						1
#define GEL_DRAWMODE_TEXTURED					2
#define GEL_DRAWMODE_TEXTURED_COLORS			3
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_DIRECT3D11) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_RENDER_CONSTANTS_DIRECT3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
