#ifdef GL_ES
precision highp float;
#else // GL_ES //
#define lowp
#define mediump
#define highp
#endif // GL_ES //

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
uniform vec2 AspectScalar;
varying vec2 var_TexCoord;

const vec2 Center = vec2(0.5,0.5);
const float RadialOffset = -0.25;

void main() {	
	float Alpha = length( (Center - var_TexCoord) * AspectScalar );
	float Dark = min(1.0, (1.45-Alpha));
//	gl_FragColor = vec4(texture2D(TexImage0, var_TexCoord.xy).rgb - Alpha, RadialOffset + Alpha * 0.5);
	gl_FragColor = vec4(texture2D(TexImage0, var_TexCoord.xy).rgb * Dark, RadialOffset + Alpha * 1.5);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
