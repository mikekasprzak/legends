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
uniform lowp vec4 MinColor;
uniform lowp vec4 MaxColor;

varying vec2 var_TexCoord;

void main() {
	vec4 Sample = texture2D(TexImage0, var_TexCoord.xy);
	gl_FragColor = mix( MinColor, MaxColor, Sample );
//	gl_FragColor = mix( vec4(1,0,0,1), vec4(0,1,0,1), Sample );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
