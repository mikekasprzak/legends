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

uniform mat4 ViewMatrix;

attribute vec4 VertexPos;
attribute vec4 Normal;
attribute vec4 Color1;
attribute vec4 Color2;

varying vec2 var_TexCoord;
varying vec4 var_Color1;
varying vec4 var_Color2;

void main() {
	gl_Position = ViewMatrix * VertexPos;
	var_TexCoord = VertexPos.xy;
	var_Color1 = Color1;
	var_Color2 = Color2;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
//uniform lowp vec4 MinColor;
//uniform lowp vec4 MaxColor;

uniform sampler2D TexImage0;

varying vec2 var_TexCoord;
varying vec4 var_Color1;
varying vec4 var_Color2;

void main() {
//	vec4 Sample = texture2D( TexImage0, var_TexCoord );
//	gl_FragColor = mix( MinColor, MaxColor, Sample );
	gl_FragColor = var_Color1 + var_Color2;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
