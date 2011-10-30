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
const vec4 Blender = vec4(1,1,1,0.5);
const vec4 Blender2 = vec4(1,1,1,0.25);

#ifdef V_PASS
const vec2 Step = vec2(0,0.005);
const vec2 Step2 = vec2(0,0.005);
#else // H_PASS //
const vec2 Step = vec2(0.005,0);
const vec2 Step2 = vec2(0.005,0);
#endif // x_PASS //

varying vec2 v_TexCoord;
//varying vec4 v_Color;

void main() {
	gl_FragColor = 
		texture2D(TexImage0, v_TexCoord.xy) + 
		texture2D(TexImage0, v_TexCoord.xy + Step) * Blender +
		texture2D(TexImage0, v_TexCoord.xy - Step) * Blender +
		texture2D(TexImage0, v_TexCoord.xy + Step2) * Blender2 +
		texture2D(TexImage0, v_TexCoord.xy - Step2) * Blender2
			;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
