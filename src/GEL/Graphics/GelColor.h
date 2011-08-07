// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_GelColor_H__
#define __GEL_GRAPHICS_GelColor_H__
// - ------------------------------------------------------------------------------------------ - //
typedef int GelColor;
// - ------------------------------------------------------------------------------------------ - //
#define GEL_RGB(_r,_g,_b)		((_r)|((_g)<<8)|((_b)<<16)|((255)<<24))
#define GEL_RGBA(_r,_g,_b,_a)	((_r)|((_g)<<8)|((_b)<<16)|((_a)<<24))
// - ------------------------------------------------------------------------------------------ - //
#define GEL_GET_R(c)			(((c))&255)
#define GEL_GET_G(c)			(((c)>>8)&255)
#define GEL_GET_B(c)			(((c)>>16)&255)
#define GEL_GET_A(c)			(((c)>>24)&255)
// - ------------------------------------------------------------------------------------------ - //
#define GEL_RGB_BLACK			GEL_RGB(0,0,0)
#define GEL_RGB_GREY			GEL_RGB(127,127,127)
#define GEL_RGB_WHITE			GEL_RGB(255,255,255)

#define GEL_RGB_RED				GEL_RGB(255,0,0)
#define GEL_RGB_GREEN			GEL_RGB(0,255,0)
#define GEL_RGB_BLUE			GEL_RGB(0,0,255)

#define GEL_RGB_MAGENTA			GEL_RGB(255,0,255)
#define GEL_RGB_YELLOW			GEL_RGB(255,255,0)
#define GEL_RGB_CYAN			GEL_RGB(0,255,255)

#define GEL_RGB_ORANGE			GEL_RGB(255,127,0)
#define GEL_RGB_PINK			GEL_RGB(255,0,127)
#define GEL_RGB_PURPLE			GEL_RGB(127,0,255)
#define GEL_RGB_PUKE			GEL_RGB(127,255,0)
#define GEL_RGB_MINT			GEL_RGB(0,255,127)
#define GEL_RGB_SKY				GEL_RGB(0,127,255)

#define GEL_RGB_DEFAULT			GEL_RGB_WHITE
// - ------------------------------------------------------------------------------------------ - //
inline GelColor GEL_MULTIPLY_COLOR( const GelColor a, const GelColor b ) {
	return GEL_RGBA(
		(GEL_GET_R(a) * GEL_GET_R(b)) >> 8,
		(GEL_GET_G(a) * GEL_GET_G(b)) >> 8,
		(GEL_GET_B(a) * GEL_GET_B(b)) >> 8,
		(GEL_GET_A(a) * GEL_GET_A(b)) >> 8
		);
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Not really optimized. //
inline GelColor GEL_HSV( float Hue, float Sat, float Val, int a = 255 ) {
	float r,g,b;

	while (Hue < 0)
		Hue += 360;
	while (Hue > 360)
		Hue -= 360;
		
	if ( Sat > 1.0f ) 
		Sat = 1.0f;
	else if ( Sat < 0.0f )
		Sat = 0.0f;
		
	if ( Val > 1.0f ) 
		Val = 1.0f;
	else if ( Val < 0.0f )
		Val = 0.0f;

	if (Hue < 120) {
		r = (120 - Hue) / 60.0f;
		g = Hue / 60.0f;
		b = 0;
	}
	else if (Hue < 240) {
		r = 0;
		g = (240 - Hue) / 60.0f;
		b = (Hue - 120) / 60.0f;
	}
	else {
		r = (Hue - 240) / 60.0f;
		g = 0;
		b = (360 - Hue) / 60.0f;
	}
	
	r = (r > 1)?1:r;
	g = (g > 1)?1:g;
	b = (b > 1)?1:b;

	r = (1 - Sat + Sat * r) * Val;
	g = (1 - Sat + Sat * g) * Val;
	b = (1 - Sat + Sat * b) * Val;

	return GEL_RGBA( (int)(r * 255.0f), (int)(g * 255.0f), (int)(b * 255.0f), a );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_GelColor_H__ //
// - ------------------------------------------------------------------------------------------ - //
