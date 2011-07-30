// - ------------------------------------------------------------------------------------------ - //
#ifndef __Graphics_System_H__
#define __Graphics_System_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Bits.h>
#include <Math/Real.h>
#include <Graphics/Color.h>
// - ------------------------------------------------------------------------------------------ - //
// Non resulotion globals //
namespace System {
	extern volatile bool CloseButtonPressed;
	extern volatile bool ToggleFullScreen;
	
	extern volatile bool ShutdownGame;

	union cInitFlags {
		struct {
			bool FullScreen:1;
			bool AutodetectScreenShape:1;
			
			bool ScreenShapeSet:1;
			bool RefShapeSet:1;
			bool OverscanSet:1;
			bool NativeScalarSet:1;
				
			bool NativeShapeDetected:1;
		};
		int Flags;
	};
	
	extern volatile cInitFlags InitFlags;
	
	enum eGPU {
		GEL_GPU_NONE = 0,
		GEL_GPU_INTEL,				// GMA/GMA HD //
		GEL_GPU_NVIDIA,				// GeForce/Quadro/Tegra //
		GEL_GPU_ATI,				// Radeon/FireGL //
		GEL_GPU_AMD = GEL_GPU_ATI,	// Radeon/FireGL //
		GEL_GPU_POWERVR,			// PowerVR/IMG //
		GEL_GPU_QUALCOMM,			// Adreno //
		GEL_GPU_ARM, 				// MALI //
	};
	
	union cInfoFlags {
		struct {
			union {
				// NOTE: Being clever here. HasTetureCompression is true if any bit is set. //
				struct {
					bool HasS3TC:1;  // S3/NVidia: http://www.opengl.org/registry/specs/EXT/texture_compression_s3tc.txt and http://www.opengl.org/registry/specs/S3/s3tc.txt
					bool HasPVRTC:1; // PowerVR/IMG: http://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc.txt
					bool HasETC1:1;  // Ericsson: http://www.khronos.org/registry/gles/extensions/OES/OES_compressed_ETC1_RGB8_texture.txt
					bool HasATC:1;   // ATI/Qualcomm: http://www.khronos.org/registry/gles/extensions/AMD/AMD_compressed_ATC_texture.txt

					bool HasDXT1:1;  // NVidia: http://www.opengl.org/registry/specs/EXT/texture_compression_dxt1.txt and http://www.khronos.org/registry/gles/extensions/EXT/texture_compression_dxt1.txt - Limited S3TC support
					bool Has3TC:1;   // ATI: http://www.khronos.org/registry/gles/extensions/AMD/AMD_compressed_3DC_texture.txt
					bool HasFXT:1;   // 3DFX: http://www.opengl.org/registry/specs/3DFX/texture_compression_FXT1.txt

					bool HasRGTC:1;  // NVidia: http://www.opengl.org/registry/specs/EXT/texture_compression_rgtc.txt and http://www.opengl.org/registry/specs/ARB/texture_compression_rgtc.txt - BC4 and BC5 from DX10
					bool HasBPTC:1;  // NVidia: http://www.opengl.org/registry/specs/ARB/texture_compression_bptc.txt - Float
					bool HasVTC:1;   // NVidia: http://www.opengl.org/registry/specs/NV/texture_compression_vtc.txt - 3D S3TC
					bool HasLATC:1;  // NVidia: http://www.opengl.org/registry/specs/EXT/texture_compression_latc.txt - Luminance Alpha
					
					bool HasNativeTC:1; // Has some native Texture Compression, and not one of the above standards //
				};
				bool HasTextureCompression:16;
			};
			bool IsFullScreen:1;
			bool HasScreenShape:1;
				
			eGPU GPUVendor:4;
		};
		int Flags;
	};
	
	extern volatile cInfoFlags InfoFlags;
	extern int MaxTextureSize;
	
	extern int StencilSize;
	extern int DepthSize;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Graphics_System_H__ //
// - ------------------------------------------------------------------------------------------ - //
