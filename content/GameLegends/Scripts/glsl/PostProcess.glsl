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

const float Blender0 = 4;
const float Blender = 2;
const float Blender2 = 1;

const float Frac = 1 / 10.0;//14.0;


#ifdef V_BLUR_PASS
const vec2 Step = vec2( 0.0025, 0.005 );
const vec2 Step2 = vec2( -0.0025, 0.01 );
#else // H_BLUR_PASS //
const vec2 Step = vec2( 0.005, 0.0025 );
const vec2 Step2 = vec2( 0.01, -0.0025 );
#endif // x_BLUR_PASS //

//#ifdef V_BLUR_PASS
//const vec2 Step = vec2( 0.005, 0.01 );
//const vec2 Step2 = vec2( -0.005, 0.02 );
//#else // H_BLUR_PASS //
//const vec2 Step = vec2( 0.01, 0.005 );
//const vec2 Step2 = vec2( 0.02, -0.005 );
//#endif // x_BLUR_PASS //

varying vec2 v_TexCoord;

void main() {
	gl_FragColor = 
		(texture2D(TexImage0, v_TexCoord.xy) * Blender0 + 
		texture2D(TexImage0, v_TexCoord.xy + Step) * Blender +
		texture2D(TexImage0, v_TexCoord.xy - Step) * Blender +
		texture2D(TexImage0, v_TexCoord.xy + Step2) * Blender2 +
		texture2D(TexImage0, v_TexCoord.xy - Step2) * Blender2) * Frac;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
