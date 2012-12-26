// - ------------------------------------------------------------------------------------------ - //
#ifdef VERTEX_SHADER
// - ------------------------------------------------------------------------------------------ - //
// Color Scalar can be optimized away by the "Normalize" feature of attrib //
const float ColorScalar = 1.0/255.0;
const float UVScalar = 1.0/1024.0;

uniform vec4 GlobalColor;
uniform sampler2D TexImage0;
uniform mat4 ViewMatrix;

varying vec2 v_TexCoord;
varying vec4 v_Color;

attribute vec4 VertexPos;
attribute vec2 TexCoord;
attribute vec4 VertexColor;

void main() {
	gl_Position = ViewMatrix * VertexPos;
	v_TexCoord = TexCoord * UVScalar;
	v_Color = VertexColor * ColorScalar * GlobalColor;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
uniform vec4 GlobalColor;
uniform sampler2D TexImage0;

varying vec2 v_TexCoord;
varying vec4 v_Color;

void main() {
	gl_FragColor = v_Color * texture2D(TexImage0, v_TexCoord.xy);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef GEOMETRY_SHADER //
// - ------------------------------------------------------------------------------------------ - //
#endif // GEOMETRY_SHADER //
// - ------------------------------------------------------------------------------------------ - //
