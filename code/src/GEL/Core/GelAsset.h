// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_CORE_GELASSET_H__
#define __GEL_CORE_GELASSET_H__
// - ------------------------------------------------------------------------------------------ - //
enum GelAsset_T {
	// - -------------------------------------------------------------------------------------- - //
	GEL_ASSET_NULL = 0,						// NULL Asset //
	// - -------------------------------------------------------------------------------------- - //
	GEL_ASSET_UNKNOWN = 1,					// Asset is Unknown data //
	GEL_ASSET_RAW = 2,						// Asset is RAW data //
	// - -------------------------------------------------------------------------------------- - //
	GEL_ASSET_KNOWN = 0x200,				// A known asset if equal or greater than this //
	// - -------------------------------------------------------------------------------------- - //
	// General Compressed Formats //
	GEL_ASSET_COMPRESSION_BASE = 0x200,
	
	GEL_ASSET_LZMA = GEL_ASSET_COMPRESSION_BASE,
	GEL_ASSET_GZIP,
	GEL_ASSET_BZIP2,
	
	GEL_ASSET_COMPRESSION_MAX,
	// - -------------------------------------------------------------------------------------- - //
	// Image/Texture Formats //
	GEL_ASSET_TEXTURE_BASE = 0x400,
	
	GEL_ASSET_PVR = GEL_ASSET_TEXTURE_BASE,
	GEL_ASSET_DXT,
	GEL_ASSET_PNG,
	GEL_ASSET_TGA,
	GEL_ASSET_PSD,
	GEL_ASSET_STB_IMAGE,					// Image loadable by STB_Image //
	GEL_ASSET_STB_IMAGE_NATIVE,				// The native STB_Image format (what it gives me) //
	
	GEL_ASSET_TEXTURE_MAX,
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

	GEL_ASSET_SCRIPT_BASE,
	GEL_ASSET_SQUIRREL = GEL_ASSET_SCRIPT_BASE,
	GEL_ASSET_LUA,
	GEL_ASSET_PYTHON,	
	GEL_ASSET_C,
	GEL_ASSET_C_PLUS_PLUS,
	GEL_ASSET_SCRIPT_MAX,

	GEL_ASSET_SHADER_BASE,
	GEL_ASSET_GLSL_VERTEX_PROGRAM = GEL_ASSET_SHADER_BASE,
	GEL_ASSET_GLSL_FRAGMENT_PROGRAM,
	GEL_ASSET_GLSL_GEOMETRY_PROGRAM,
	GEL_ASSET_CG_VERTEX_PROGRAM,
	GEL_ASSET_CG_FRAGMENT_PROGRAM,
	GEL_ASSET_CG_GEOMETRY_PROGRAM,
	GEL_ASSET_HLSL_VERTEX_PROGRAM,
	GEL_ASSET_HLSL_FRAGMENT_PROGRAM,
	GEL_ASSET_HLSL_GEOMETRY_PROGRAM,
	GEL_ASSET_SHADER_MAX,
	
	GEL_ASSET_TEXT_MAX,
	// - -------------------------------------------------------------------------------------- - //
	
	GEL_ASSET_TYPE_MASK		= 0xffff,		// Mask for the type part //
	GEL_ASSET_INFO_MASK		= 0xffff0000,	// Mask for the Info part //
	
	// - -------------------------------------------------------------------------------------- - //
	// General Properties //
	GEL_ASSET_HAS_INFO		= 0x10000,		// This format has information about the contained data //
	GEL_ASSET_IS_SHARE		= 0x20000,		// This format shares data with a proxy. //
	GEL_ASSET_IS_PROXY		= 0x40000,		// This format is a proxy. DO NOT DELETE ME! //
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
extern GelAsset_T is_Compression_Data_GelAsset( const char* InData );
extern GelAsset_T is_Texture_Data_GelAsset( const char* InData );
extern GelAsset_T is_Model_Data_GelAsset( const char* InData );
extern GelAsset_T is_Audio_Data_GelAsset( const char* InData );
extern GelAsset_T is_Text_Data_GelAsset( const char* InData );
// Subsections of Text //
extern GelAsset_T is_Script_Data_GelAsset( const char* InData );
extern GelAsset_T is_Shader_Data_GelAsset( const char* InData );

extern GelAsset_T is_Compression_Name_GelAsset( const char* FileName );
extern GelAsset_T is_Texture_Name_GelAsset( const char* FileName );
extern GelAsset_T is_Model_Name_GelAsset( const char* FileName );
extern GelAsset_T is_Audio_Name_GelAsset( const char* FileName );
extern GelAsset_T is_Text_Name_GelAsset( const char* FileName );
// Subsections of Text //
extern GelAsset_T is_Script_Name_GelAsset( const char* FileName );
extern GelAsset_T is_Shader_Name_GelAsset( const char* FileName );

extern GelAsset_T is_Data_GelAsset( const char* InData );
extern GelAsset_T is_Name_GelAsset( const char* FileName );

inline bool is_GelAsset( const GelAsset_T Asset ) {
	return (Asset >= GEL_ASSET_KNOWN);
}
// - ------------------------------------------------------------------------------------------ - //
struct GelAssetType {
	union {
		struct {
			int Type:16;				// The type of the Asset //
			bool HasInfo:1;				// Has information about its contents //
			bool IsShare:1;				// Shares data with the a proxy asset //
			bool IsProxy:1;				// References other data. DO NOT DELETE ME! //
		};
		GelAsset_T BitMask;				// Whole type of the asset //
	};
	
	// Constructor //
	GelAssetType() {
		BitMask = GEL_ASSET_NULL;
	}		
	
	// Data Tests //
	inline void TestCompressionData( const char* InData ) {
		BitMask = is_Compression_Data_GelAsset( InData );
	}
	inline void TestTextureData( const char* InData ) {
		BitMask = is_Texture_Data_GelAsset( InData );
	}
	inline void TestAudioData( const char* InData ) {
		BitMask = is_Audio_Data_GelAsset( InData );
	}
	inline void TestModelData( const char* InData ) {
		BitMask = is_Model_Data_GelAsset( InData );
	}
	inline void TestTextData( const char* InData ) {
		BitMask = is_Text_Data_GelAsset( InData );
	}
	inline void TestScriptData( const char* InData ) {
		BitMask = is_Script_Data_GelAsset( InData );
	}
	inline void TestShaderData( const char* InData ) {
		BitMask = is_Shader_Data_GelAsset( InData );
	}
	inline void TestData( const char* InData ) {
		BitMask = is_Data_GelAsset( InData );
	}
	
	// Name Tests //

	// Am I an Asset? //
	inline bool IsCompression() {
		return (Type >= GEL_ASSET_COMPRESSION_BASE) && (Type <= GEL_ASSET_COMPRESSION_MAX);
	}
	inline bool IsTexture() {
		return (Type >= GEL_ASSET_TEXTURE_BASE) && (Type <= GEL_ASSET_TEXTURE_MAX);
	}
	inline bool IsModel() {
		return (Type >= GEL_ASSET_MODEL_BASE) && (Type <= GEL_ASSET_MODEL_MAX);
	}
	inline bool IsAudio() {
		return (Type >= GEL_ASSET_AUDIO_BASE) && (Type <= GEL_ASSET_AUDIO_MAX);
	}
	inline bool IsText() {
		return (Type >= GEL_ASSET_TEXT_BASE) && (Type <= GEL_ASSET_TEXT_MAX);
	}
	inline bool IsScript() {
		return (Type >= GEL_ASSET_SCRIPT_BASE) && (Type <= GEL_ASSET_SCRIPT_MAX);
	}
	inline bool IsShader() {
		return (Type >= GEL_ASSET_SHADER_BASE) && (Type <= GEL_ASSET_SHADER_MAX);
	}
	
	inline bool IsAsset() {
		return is_GelAsset( BitMask );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_CORE_GELASSET_H__ //
// - ------------------------------------------------------------------------------------------ - //
