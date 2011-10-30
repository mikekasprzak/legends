// - ------------------------------------------------------------------------------------------ - //
#ifdef VERTEX_SHADER
// - ------------------------------------------------------------------------------------------ - //
// Color Scalar can be optimized away by the "Normalize" feature of attrib //
const float ColorScalar = 1.0/255.0;
const float UVScalar = 1.0/1024.0;

//uniform vec4 GlobalColor;
uniform mat4 ViewMatrix;

varying vec2 v_TexCoord;
//varying vec4 v_Color;

attribute vec4 VertexPos;
attribute vec2 TexCoord;

void main() {
	gl_Position = ViewMatrix * VertexPos;
	v_TexCoord = TexCoord * UVScalar;
//	v_Color = ColorScalar * GlobalColor;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
uniform sampler2D TexImage0;
//const vec4 Blender0 = vec4(1,1,1,4);
//const vec4 Blender = vec4(1,1,1,3);
//const vec4 Blender2 = vec4(1,1,1,2);

const float Blender0 = 3;
const float Blender1 = 2;
const float Blender2 = 1;

#ifdef LIGHT_BLUR
const float MainAxis1 = 0.005;
const float MainAxis2 = 0.01;
const float OffAxis1 = 0.0025;
const float OffAxis2 = -0.0025;
#else // HEAVY_BLUR //
const float MainAxis1 = 0.01;
const float MainAxis2 = 0.02;
const float OffAxis1 = 0.005;
const float OffAxis2 = -0.005;
#endif // HEAVY_BLUR //

#ifndef H_BLUR_PASS
const vec2 VStep = vec2( OffAxis1, MainAxis1 );
const vec2 VStep2 = vec2( OffAxis2, MainAxis2 );
#endif // !H_BLUR_PASS //

#ifndef V_BLUR_PASS
const vec2 HStep = vec2( MainAxis1, OffAxis1 );
const vec2 HStep2 = vec2( MainAxis2, OffAxis2 );
#endif // !V_BLUR_PASS //

#if defined(H_BLUR_PASS) || defined(V_BLUR_PASS)
	const float Frac = 1 / 9.0;
#else // x_BLUR_PASS //
	const float Frac = 1 / 15.0;
#endif // x_BLUR_PASS //

varying vec2 v_TexCoord;

void main() {
#if defined(V_BLUR_PASS)
	// Individual Blur Passes //
	gl_FragColor = 
		(texture2D(TexImage0, v_TexCoord.xy) * Blender0 + 
		texture2D(TexImage0, v_TexCoord.xy + VStep) * Blender1 +
		texture2D(TexImage0, v_TexCoord.xy - VStep) * Blender1 +
		texture2D(TexImage0, v_TexCoord.xy + VStep2) * Blender2 +
		texture2D(TexImage0, v_TexCoord.xy - VStep2) * Blender2) * Frac;
#elif defined(H_BLUR_PASS)
	// Individual Blur Passes //
	gl_FragColor = 
		(texture2D(TexImage0, v_TexCoord.xy) * Blender0 + 
		texture2D(TexImage0, v_TexCoord.xy + HStep) * Blender1 +
		texture2D(TexImage0, v_TexCoord.xy - HStep) * Blender1 +
		texture2D(TexImage0, v_TexCoord.xy + HStep2) * Blender2 +
		texture2D(TexImage0, v_TexCoord.xy - HStep2) * Blender2) * Frac;
#else // x_BLUR_PASS //
	// Combined Blur Passes //
	gl_FragColor = 
		(
			texture2D(TexImage0, v_TexCoord.xy) * Blender0 + 
			texture2D(TexImage0, v_TexCoord.xy + VStep) * Blender1 +
			texture2D(TexImage0, v_TexCoord.xy - VStep) * Blender1 +
			texture2D(TexImage0, v_TexCoord.xy + VStep2) * Blender2 +
			texture2D(TexImage0, v_TexCoord.xy - VStep2) * Blender2 +
			texture2D(TexImage0, v_TexCoord.xy + HStep) * Blender1 +
			texture2D(TexImage0, v_TexCoord.xy - HStep) * Blender1 +
			texture2D(TexImage0, v_TexCoord.xy + HStep2) * Blender2 +
			texture2D(TexImage0, v_TexCoord.xy - HStep2) * Blender2
		) * Frac;
#endif // x_BLUR_PASS //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
