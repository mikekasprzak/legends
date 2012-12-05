// - ------------------------------------------------------------------------------------------ - //
#include "System.h"
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
Signal GainFocus;
Signal LoseFocus;

int DepthBits = 0;
int StencilBits = 0;
int MaxTextureSize = 0;
eGPU GPUVendor = GPU_NONE;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef ndebug
void DummyGain(void*) {
	Log( "** Focus Gained" );
}
void DummyLose(void*) {
	Log( "** Focus Lost" );
}
#endif // ndebug //
// - ------------------------------------------------------------------------------------------ - //
void Init() {
#ifndef ndebug
	// Debug Builds Only, an extra signal function call that logs focus gained and lost //
	GainFocus.Connect( DummyGain );
	LoseFocus.Connect( DummyLose );
#endif // ndebug //

	GraphicsAPIInit();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
