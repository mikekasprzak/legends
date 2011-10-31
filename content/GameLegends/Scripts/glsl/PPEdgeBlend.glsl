// - ------------------------------------------------------------------------------------------ - //
#ifdef VERTEX_SHADER
// - ------------------------------------------------------------------------------------------ - //
// Color Scalar can be optimized away by the "Normalize" feature of attrib //
const float ColorScalar = 1.0/255.0;
const float UVScalar = 1.0/1024.0;

uniform mat4 ViewMatrix;

varying vec2 v_TexCoord;

attribute vec4 VertexPos;
attribute vec2 TexCoord;

uniform vec4 GlobalColor;
varying vec4 v_Color;

void main() {
	gl_Position = ViewMatrix * VertexPos;
	v_TexCoord = TexCoord * UVScalar;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
uniform sampler2D TexImage0;
varying vec2 v_TexCoord;

varying vec4 v_Color;


const vec2 Center = vec2(0.5,0.5);

void main() {
	float Alpha = length( Center - v_TexCoord );
	gl_FragColor = vec4(texture2D(TexImage0, v_TexCoord.xy).rgb - Alpha, (-0.25) + Alpha * 3);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
