// - ------------------------------------------------------------------------------------------ - //
#ifdef VERTEX_SHADER
// - ------------------------------------------------------------------------------------------ - //
const float UVScalar = 1.0/1024.0;

uniform mat4 ViewMatrix;

attribute vec4 VertexPos;
attribute vec2 TexCoord;

varying vec2 var_TexCoord;


void main() {
	gl_Position = ViewMatrix * VertexPos;
	var_TexCoord = TexCoord * UVScalar;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
uniform sampler2D TexImage0;
varying vec2 var_TexCoord;

const vec2 Center = vec2(0.5,0.5);
const float RadialOffset = -0.25;

void main() {	
	float Alpha = length( Center - var_TexCoord );
	gl_FragColor = vec4(texture2D(TexImage0, var_TexCoord.xy).rgb - Alpha, RadialOffset + Alpha * 3);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
