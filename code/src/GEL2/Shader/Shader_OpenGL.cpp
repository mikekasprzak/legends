// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include "Shader.h"
#include "Embedded/GLSL/EmbeddedShaders.h"	// DefaultShader_json, etc //
// - ------------------------------------------------------------------------------------------ - //
namespace Shader {
// - ------------------------------------------------------------------------------------------ - //
cUberShader* Default;
// - ------------------------------------------------------------------------------------------ - //
void Init() {
	atexit( Exit );

	// Use Files //	
//	Default = new cUberShader( "src/GEL2/Shader/Embedded/GLSL/DefaultShader.json" );
	// Use Embedded //
	Default = new cUberShader( DefaultShader_json, DefaultShader_json_Size, DefaultShader_glsl, DefaultShader_glsl_Size );
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	delete Default;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Shader //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
