// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Color_H__
#define __GEL_Color_H__
// - ------------------------------------------------------------------------------------------ - //
typedef int ColorType;
// - ------------------------------------------------------------------------------------------ - //
#ifdef RGB
#undef RGB
#endif // RGB //
// - ------------------------------------------------------------------------------------------ - //
#ifdef RGBA
#undef RGBA
#endif // RGBA //
// - ------------------------------------------------------------------------------------------ - //
#define RGB(_r,_g,_b)		((_r)|((_g)<<8)|((_b)<<16)|((255)<<24))
#define RGBA(_r,_g,_b,_a)	((_r)|((_g)<<8)|((_b)<<16)|((_a)<<24))
// - ------------------------------------------------------------------------------------------ - //
#define GET_R(c)	(((c))&255)
#define GET_G(c)	(((c)>>8)&255)
#define GET_B(c)	(((c)>>16)&255)
#define GET_A(c)	(((c)>>24)&255)
// - ------------------------------------------------------------------------------------------ - //
#define RGB_BLACK	RGB(0,0,0)
#define RGB_GREY	RGB(127,127,127)
#define RGB_WHITE	RGB(255,255,255)

#define RGB_RED		RGB(255,0,0)
#define RGB_GREEN	RGB(0,255,0)
#define RGB_BLUE	RGB(0,0,255)

#define RGB_MAGENTA	RGB(255,0,255)
#define RGB_YELLOW	RGB(255,255,0)
#define RGB_CYAN	RGB(0,255,255)

#define RGB_ORANGE	RGB(255,127,0)
#define RGB_PINK	RGB(255,0,127)
#define RGB_PURPLE	RGB(127,0,255)
#define RGB_PUKE	RGB(127,255,0)
#define RGB_MINT	RGB(0,255,127)
#define RGB_SKY		RGB(0,127,255)
// - ------------------------------------------------------------------------------------------ - //
inline ColorType Multiply_Color( const ColorType a, const ColorType b ) {
	return RGBA(
		(GET_R(a) * GET_R(b)) >> 8,
		(GET_G(a) * GET_G(b)) >> 8,
		(GET_B(a) * GET_B(b)) >> 8,
		(GET_A(a) * GET_A(b)) >> 8
		);
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: Not really optimized. //
inline ColorType HSV( float Hue, float Sat, float Val, int a = 255 ) {
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

	return RGBA( (int)(r * 255.0f), (int)(g * 255.0f), (int)(b * 255.0f), a );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Color_H__ //
// - ------------------------------------------------------------------------------------------ - //
