// - ------------------------------------------------------------------------------------------ - //
#ifdef GL_ES
	precision highp float;
#else // !GL_ES //
	#define lowp
	#define mediump
	#define highp
#endif // GL_ES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef VERTEX_SHADER
// - ------------------------------------------------------------------------------------------ - //

uniform lowp vec4 GlobalColor;
uniform mat4 ViewMatrix;
varying lowp vec4 v_Color;
attribute vec4 VertexPos;

#ifdef SHADER_TEXTURE
	uniform lowp sampler2D TexImage0;
#endif // SHADER_TEXTURE //

// SHADER_NONE means there is no per-pixel data. PPD can be a texture or noise. //
#if !defined(SHADER_NONE)
	const float UVScalar = 1.0/1024.0;
	varying lowp vec2 v_TexCoord;
	attribute lowp vec2 TexCoord;
#endif // SHADER_NONE //

#ifdef SHADER_COLOR
	attribute lowp vec4 VertexColor;
#endif // SHADER_COLOR //

void main() {
	gl_Position = ViewMatrix * VertexPos;

	#if !defined(SHADER_NONE)
		v_TexCoord = TexCoord * UVScalar;
	#endif // SHADER_NONE //
	
	#ifdef SHADER_FLAT
		v_Color = GlobalColor;
	#else // !SHADER_FLAT //
		v_Color = VertexColor * GlobalColor;
	#endif // SHADER_FLAT //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
#ifdef SHADER_TEXTURE
	uniform lowp sampler2D TexImage0;
#endif // SHADER_TEXTURE //

#ifdef SHADER_NOISE
	uniform float Seed;
	
	float rand(vec2 co) {
		// http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
	    return fract(sin(dot(co.xy,vec2(12.9898,78.233))) * 43758.5453);
	}
#endif // SHADER_NOISE //

#if !defined(SHADER_NONE)
	varying lowp vec2 v_TexCoord;
#endif // SHADER_NONE //

varying lowp vec4 v_Color;

void main() {
	#ifdef SHADER_NOISE
		float Random = rand(vec2(v_TexCoord.s+2.34*Seed,v_TexCoord.t+3.14*Seed));
		#ifdef SHADER_NOISE_1BIT
			gl_FragColor = v_Color * vec4( vec3( round(Random) ), 1.0 );
		#else // SHADER_NOISE_1BIT //
			gl_FragColor = v_Color * vec4( vec3( Random ), 1.0 );
		#endif // SHADER_NOISE_1BIT //
	#endif // SHADER_NOISE //
			
	#ifdef SHADER_TEXTURE
		gl_FragColor = v_Color * texture2D(TexImage0, v_TexCoord);
	#endif // SHADER_TEXTURE //
	
	#ifdef SHADER_NONE
		gl_FragColor = v_Color;
	#endif // SHADER_NONE //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
