// - ------------------------------------------------------------------------------------------ - //
#include "Graphics_System.h"
// - ------------------------------------------------------------------------------------------ - //
// Non resulotion globals //
namespace System {
	volatile bool CloseButtonPressed = false;	
	volatile bool ToggleFullScreen = false;

	volatile bool ShutdownGame = false;

	volatile cInitFlags InitFlags;
	volatile cInfoFlags InfoFlags;
	
	int MaxTextureSize = 1024;
	
	int StencilSize = 0;
	int DepthSize = 0;
};
// - ------------------------------------------------------------------------------------------ - //
