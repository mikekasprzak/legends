// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_CORE_H__
#define __GEL_SYSTEM_CORE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Signal.h>
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
// Core Features //
extern Signal GainFocus;
extern Signal LoseFocus;

void Init();
// - ------------------------------------------------------------------------------------------ - //
// Platform Specific Features //
void GraphicsAPIInit();	// Called from Init() //

// Set inside GraphicsAPIInit //
extern int DepthBits;
extern int StencilBits;
extern int MaxTextureSize;	

enum eGPU {
	GPU_NONE = 0,
	GPU_INTEL,				// GMA/GMA HD //
	GPU_NVIDIA,				// GeForce/Quadro/Tegra //
	GPU_ATI,				// Radeon/FireGL //
	GPU_AMD = GPU_ATI,		// Radeon/FireGL //
	GPU_POWERVR,			// PowerVR/IMG //
	GPU_QUALCOMM,			// Adreno //
	GPU_ARM, 				// MALI //
	GPU_VIVANTE,			// GC //
};

extern eGPU GPUVendor;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_CORE_H__ //
// - ------------------------------------------------------------------------------------------ - //
