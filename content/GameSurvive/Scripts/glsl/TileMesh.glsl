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
uniform vec3 FaceCenter;
//uniform float Scalar;

//uniform vec3 FaceNormal;
//const vec3 FaceCenter = vec3(0,0,0);

attribute vec3 VertexPos;	// Was vec4, despite it being a vec3. GL knows to pad with 1's. //
attribute vec3 Normal;
attribute vec4 Color1;
attribute vec4 Color2;

varying vec2 var_TexCoord;
varying vec4 var_Color1;
varying vec4 var_Color2;

void main() {
	vec3 Pos = VertexPos;// * Scalar;
	gl_Position = ViewMatrix * vec4( Pos, 1 );	// Manually making it a homogeneous vector //

	var_TexCoord = VertexPos.xy * 0.5;
	var_Color1 = Color1 * (1.0/255.0);
//	var_Color2 = Color2 * (1.0/255.0);
//	var_Color2 = vec4(0.75);

//	var_Color2 = vec4( dot( Normal, FaceNormal ) ); // Darker as angle changes, no proximity //
	
	vec3 ToCenter = FaceCenter - VertexPos;
	var_Color2 = vec4( min(1.0 + dot( Normal, normalize(ToCenter) ), 1.0) );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // VERTEX_SHADER //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifdef FRAGMENT_SHADER
// - ------------------------------------------------------------------------------------------ - //
//uniform lowp vec4 MinColor;
//uniform lowp vec4 MaxColor;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

varying vec2 var_TexCoord;
varying vec4 var_Color1;
varying vec4 var_Color2;

void main() {
//	gl_FragColor = mix( texture2D( TexImage0, var_TexCoord ), texture2D( TexImage1, var_TexCoord ), 1 );

//	gl_FragColor = 
//		mix((vec4( var_Color1.rgb,1 ) * texture2D( Texture0, var_TexCoord )),
//			(vec4( var_Color2.rgb,1 ) * texture2D( Texture1, var_TexCoord )),
//			var_Color1.a
//			);

	gl_FragColor = vec4(var_Color2.rgb,1) *
		mix((vec4( var_Color1.rgb,1 ) * texture2D( Texture0, var_TexCoord )),
			(vec4( var_Color1.rgb,1 ) * texture2D( Texture1, var_TexCoord )),
			var_Color1.a
			);

}
// - ------------------------------------------------------------------------------------------ - //
#endif // FRAGMENT_SHADER //
// - ------------------------------------------------------------------------------------------ - //
