// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GraphicsDraw_H__
#define __GEL_GraphicsDraw_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Graphics.h"
// - ------------------------------------------------------------------------------------------ - //
#include "GraphicsDraw_Lines2D.h"
#include "GraphicsDraw_Lines3D.h"
// - ------------------------------------------------------------------------------------------ - //
#include "GraphicsDraw_Rectangles2D.h"
#include "GraphicsDraw_Rectangles3D.h"
#include "GraphicsDraw_TexturedRectangles2D.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef _MSC_VER
#include "GraphicsDraw_Markers2D.h"
#include "GraphicsDraw_Markers3D.h"
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#include "GraphicsDraw_Polygons.h"
#include "GraphicsDraw_Polygons3D.h"
#include "GraphicsDraw_TexturedPolygons.h"
#include "GraphicsDraw_TexturedPolygons3D.h"
// - ------------------------------------------------------------------------------------------ - //
#include "GraphicsDraw_Text.h"
// - ------------------------------------------------------------------------------------------ - //
//#include "GraphicsDraw_Primitive.h"
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//inline void gelSetTexture( unsigned int GelTextureId ) {
//	glBindTexture( GL_TEXTURE_2D, GelTextureId );
//}
//// - ------------------------------------------------------------------------------------------ - //
//extern unsigned int gelLoadTexture( const char* MyFile );
//// - ------------------------------------------------------------------------------------------ - //
//inline void gelFreeTexture( unsigned int& MyTexture ) {
//	glDeleteTextures( 1, &MyTexture );
//}
//// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GraphicsDraw_H__ //
// - ------------------------------------------------------------------------------------------ - //