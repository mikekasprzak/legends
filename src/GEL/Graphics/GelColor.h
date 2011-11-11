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
typedef long long int GelSColor;
// - ------------------------------------------------------------------------------------------ - //
#define GEL_SRGB(_r,_g,_b)		((_r&0xffffll)|((_g&0xffffll)<<16)|((_b&0xffffll)<<32)|((255ll)<<48))
#define GEL_SRGBA(_r,_g,_b,_a)	((_r&0xffffll)|((_g&0xffffll)<<16)|((_b&0xffffll)<<32)|((_a&0xffffll)<<48))
// - ------------------------------------------------------------------------------------------ - //
inline int SignExtend8To32( const int Value ) {
	if ( Value & 0x80 )
		return 0xffffff00 | Value;
	else
		return Value;
}
// - ------------------------------------------------------------------------------------------ - //
inline int SignExtend16To32( const int Value ) {	
	if ( Value & 0x8000 )
		return 0xffff0000 | Value;
	else
		return Value;
}
// - ------------------------------------------------------------------------------------------ - //
inline int SignExtend24To32( const int Value ) {
	if ( Value & 0x800000 )
		return 0xff000000 | Value;
	else
		return Value;
}
// - ------------------------------------------------------------------------------------------ - //
//#define GEL_SGET_R(c)			SignExtend16To32(((c)>>0)&0xffff)
//#define GEL_SGET_G(c)			SignExtend16To32(((c)>>16)&0xffff)
//#define GEL_SGET_B(c)			SignExtend16To32(((c)>>32)&0xffff)
//#define GEL_SGET_A(c)			SignExtend16To32(((c)>>48)&0xffff)
// - ------------------------------------------------------------------------------------------ - //
#define GEL_SGET_R(c)			(short)(((c)>>0)&0xffff)
#define GEL_SGET_G(c)			(short)(((c)>>16)&0xffff)
#define GEL_SGET_B(c)			(short)(((c)>>32)&0xffff)
#define GEL_SGET_A(c)			(short)(((c)>>48)&0xffff)
// - ------------------------------------------------------------------------------------------ - //
#define GEL_SRGB_BLACK			GEL_SRGB(0,0,0)
#define GEL_SRGB_GREY			GEL_SRGB(127,127,127)
#define GEL_SRGB_WHITE			GEL_SRGB(255,255,255)

#define GEL_SRGB_RED			GEL_SRGB(255,0,0)
#define GEL_SRGB_GREEN			GEL_SRGB(0,255,0)
#define GEL_SRGB_BLUE			GEL_SRGB(0,0,255)

#define GEL_SRGB_MAGENTA		GEL_SRGB(255,0,255)
#define GEL_SRGB_YELLOW			GEL_SRGB(255,255,0)
#define GEL_SRGB_CYAN			GEL_SRGB(0,255,255)

#define GEL_SRGB_ORANGE			GEL_SRGB(255,127,0)
#define GEL_SRGB_PINK			GEL_SRGB(255,0,127)
#define GEL_SRGB_PURPLE			GEL_SRGB(127,0,255)
#define GEL_SRGB_PUKE			GEL_SRGB(127,255,0)
#define GEL_SRGB_MINT			GEL_SRGB(0,255,127)
#define GEL_SRGB_SKY			GEL_SRGB(0,127,255)

#define GEL_SRGB_DEFAULT		GEL_SRGB_WHITE
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline int SaturateToU8( const int In ) {
	if ( In > 255 )
		return 255;
	else if ( In < 0 )
		return 0;
	
	return In;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelColor ToGelColor( const GelSColor In ) {
	return GEL_RGBA( GEL_SGET_R(In), GEL_SGET_G(In), GEL_SGET_B(In), GEL_SGET_A(In) );
}
// - ------------------------------------------------------------------------------------------ - //
inline GelColor ToGelColorSaturate( const GelSColor In ) {
	return GEL_RGBA( SaturateToU8(GEL_SGET_R(In)), SaturateToU8(GEL_SGET_G(In)), SaturateToU8(GEL_SGET_B(In)), SaturateToU8(GEL_SGET_A(In)) );
}
// - ------------------------------------------------------------------------------------------ - //
inline GelSColor ToGelSColor( const GelColor In ) {
	return GEL_SRGBA( GEL_GET_R(In), GEL_GET_G(In), GEL_GET_B(In), GEL_GET_A(In) );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_GelColor_H__ //
// - ------------------------------------------------------------------------------------------ - //
