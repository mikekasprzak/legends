// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_CORE_GELASSET_H__
#define __GEL_CORE_GELASSET_H__
// - ------------------------------------------------------------------------------------------ - //
enum GelAsset_T {
	// - -------------------------------------------------------------------------------------- - //
	GEL_ASSET_NULL = 0,						// NULL Asset //
	// - -------------------------------------------------------------------------------------- - //
	GEL_ASSET_RAW = 1,						// Asset is RAW data //
	// - -------------------------------------------------------------------------------------- - //
	// General Compressed Formats //
	GEL_ASSET_COMPRESSION_BASE = 0x200,
	
	GEL_ASSET_LZMA = GEL_ASSET_COMPRESSION_BASE,
	GEL_ASSET_GZIP,
	GEL_ASSET_BZIP2,
	
	GEL_ASSET_COMPRESSION_MAX,
	// - -------------------------------------------------------------------------------------- - //
	// Image/Texture Formats //
	GEL_ASSET_IMAGE_BASE = 0x400,
	
	GEL_ASSET_PVR = GEL_ASSET_IMAGE_BASE,
	GEL_ASSET_DXT,
	GEL_ASSET_PNG,
	GEL_ASSET_TGA,
	GEL_ASSET_PSD,
	GEL_ASSET_STB_IMAGE,					// Image loadable by STB_Image //
	GEL_ASSET_STB_IMAGE_NATIVE,				// The native STB_Image format (what it gives me) //
	
	GEL_ASSET_IMAGE_MAX,
	// - -------------------------------------------------------------------------------------- - //
	// 3D Model Formats //
	GEL_ASSET_MODEL_BASE = 0x600,
	
	GEL_ASSET_MODEL_NATIVE = GEL_ASSET_MODEL_BASE,	
	GEL_ASSET_PME,							// My (original) native format //
	GEL_ASSET_BLENDER,
	GEL_ASSET_WINGS,
	GEL_ASSET_ASSIMP_MODEL,					// Model loadable by the Asset Import Library (ASSIMP) //
	GEL_ASSET_ASSIMP_MODEL_NATIVE,			// The native Assimp_Model format (what it gives me) //
	
	GEL_ASSET_MODEL_MAX,
	// - -------------------------------------------------------------------------------------- - //
	// Audio Formats //
	GEL_ASSET_AUDIO_BASE = 0x800,
	
	GEL_ASSET_WAV = GEL_ASSET_AUDIO_BASE,	
	GEL_ASSET_ADPCM,
	GEL_ASSET_OGG,
	GEL_ASSET_MP3,
	
	GEL_ASSET_AUDIO_MAX,
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Text, Data, and Source Code Formats //
	GEL_ASSET_TEXT_BASE = 0x1000,
	
	GEL_ASSET_TXT = GEL_ASSET_TEXT_BASE,	// Unspecific Text Files //
	GEL_ASSET_XML,
	GEL_ASSET_JSON,
	GEL_ASSET_CSV,							// CSV Spreadsheet //

	GEL_ASSET_SQUIRREL,
	GEL_ASSET_LUA,
	GEL_ASSET_PYTHON,
	GEL_ASSET_C,
	GEL_ASSET_C_PLUS_PLUS,

	GEL_ASSET_GLSL_VERTEX_PROGRAM,
	GEL_ASSET_GLSL_FRAGMENT_PROGRAM,
	GEL_ASSET_GLSL_GEOMETRY_PROGRAM,
	GEL_ASSET_CG_VERTEX_PROGRAM,
	GEL_ASSET_CG_FRAGMENT_PROGRAM,
	GEL_ASSET_CG_GEOMETRY_PROGRAM,
	GEL_ASSET_HLSL_VERTEX_PROGRAM,
	GEL_ASSET_HLSL_FRAGMENT_PROGRAM,
	GEL_ASSET_HLSL_GEOMETRY_PROGRAM,
	
	GEL_ASSET_TEXT_MAX,
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// General Properties //
	GEL_ASSET_HAS_INFO		= 0x10000,		// This format has information about the contained data //
	GEL_ASSET_IS_SHARE		= 0x20000,		// This format shares data with a proxy. //
	GEL_ASSET_IS_PROXY		= 0x40000,		// This format is a proxy. DO NOT DELETE ME! //
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
struct GelAssetType {
	union {
		struct {
			int Type:16;				// The type of the Asset //
			bool HasInfo:1;				// Has information about its contents //
			bool IsShare:1;				// Shares data with the a proxy asset //
			bool IsProxy:1;				// References other data. DO NOT DELETE ME! //
		};
		GelAsset_T BitMask;			// Whole type of the asset //
	};
};
// - ------------------------------------------------------------------------------------------ - //
// TODO: Asset Check operators //
// - ------------------------------------------------------------------------------------------ - //
extern GelAsset_T is_Compression_GelAsset( const char* InData );
extern GelAsset_T is_Texture_GelAsset( const char* InData );
extern GelAsset_T is_Model_GelAsset( const char* InData );
extern GelAsset_T is_Audio_GelAsset( const char* InData );
extern GelAsset_T is_Text_GelAsset( const char* InData );

extern GelAsset_T is_GelAsset( const char* InData );
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_CORE_GELASSET_H__ //
// - ------------------------------------------------------------------------------------------ - //
