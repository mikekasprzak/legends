// - ------------------------------------------------------------------------------------------ - //
#ifdef GL_ES
	precision highp float;
#else // !GL_ES //
	#define lowp
#endif // GL_ES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef VERTEX_SHADER
// - ------------------------------------------------------------------------------------------ - //
// Color Scalar can be optimized away by the "Normalize" feature of attrib //
#ifdef COLOR_SCALAR
const float ColorScalar = 1.0/255.0;
#endif COLOR_SCALAR

uniform lowp vec4 GlobalColor;
uniform mat4 ViewMatrix;
varying lowp vec4 v_Color;
attribute vec4 VertexPos;

#ifdef SHADER_TEXTURE
	const float UVScalar = 1.0/1024.0;

	uniform lowp sampler2D TexImage0;
	varying lowp vec2 v_TexCoord;
	attribute lowp vec2 TexCoord;
#endif // SHADER_TEXTURE //

#ifdef SHADER_COLOR
	attribute lowp vec4 VertexColor;
#endif // SHADER_COLOR //

void main() {
	gl_Position = ViewMatrix * VertexPos;

	#ifdef SHADER_TEXTURE
		v_TexCoord = TexCoord * UVScalar;
	#endif // SHADER_TEXTURE //
	
	#ifdef COLOR_SCALAR
		#ifdef SHADER_FLAT
			v_Color = ColorScalar * GlobalColor;
		#else // !SHADER_FLAT //
			v_Color = VertexColor * ColorScalar * GlobalColor;
		#endif // SHADER_FLAT //
	#else // COLOR_SCALAR //
		#ifdef SHADER_FLAT
			v_Color = GlobalColor;
		#else // !SHADER_FLAT //
			v_Color = VertexColor * GlobalColor;
		#endif // SHADER_FLAT //
	#endif // COLOR_SCALAR //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
//uniform lowp vec4 GlobalColor;
#ifdef SHADER_TEXTURE
	uniform lowp sampler2D TexImage0;
	varying lowp vec2 v_TexCoord;
#endif // SHADER_TEXTURE //

varying lowp vec4 v_Color;

void main() {
	#ifdef SHADER_TEXTURE
		gl_FragColor = v_Color * texture2D(TexImage0, v_TexCoord.xy);
	#else // SHADER_TEXTURE //
		gl_FragColor = v_Color;
	#endif // SHADER_TEXTURE //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
