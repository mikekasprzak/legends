// - ------------------------------------------------------------------------------------------ - //
// DirectX 10 Spec DDS Texture Format (Backwards compatible with DX9 DDS) //
// - ------------------------------------------------------------------------------------------ - //
// For more info, see: http://msdn.microsoft.com/en-us/library/bb943990(VS.85).aspx //
// TODO: Remove DX10 references (Generalize) //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_TEXTURE_TEXTURE_DDS_H__
#define __GEL2_TEXTURE_TEXTURE_DDS_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Nonstandard Extension: Zero Sized Array in Struct/Union
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
// NOTE: According to the original spec, all data is DWORD's. DWORD's are 32bit unsigned numbers. //
// DXT Chunk Size: max(1, width * 4) * max(1, height * 4) * 8(DXT1) or 16(DXT2-5)
// - ------------------------------------------------------------------------------------------ - //
// TODO: Look up flag values //
// - ------------------------------------------------------------------------------------------ - //
namespace Texture {
// - ------------------------------------------------------------------------------------------ - //
// Pixel Encoding Format Information (DDS_PIXELFORMAT) //
typedef struct /*DDSPixelFormat*/ { 
	unsigned HeaderSize;		// Always 32 (bytes) //
	unsigned Flags;				// Flags that describe the data //
	unsigned FourCC;			// Magic Number describing pixel format ("DXT1", etc) //

	// When an uncompressed RGB or RGBA format, these are valid //
	unsigned BitCount;			// The number of bits per pixel //

	// Bit Masks for describing uncompressed formats //
	unsigned RedMask;			// ARGB -> 0x00FF0000 //
	unsigned GreenMask;			// ARGB -> 0x0000FF00 //
	unsigned BlueMask;			// ARGB -> 0x000000FF //
	unsigned AlphaMask;			// ARGB -> 0xFF000000 //
} DDSPixelFormat;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// The DDS Texture Format - A full DDS texture header is 128 bytes including magic number //
// - ------------------------------------------------------------------------------------------ - //
typedef struct /*DDSTexture*/ {
	// Top of file (Header) //
	unsigned DDS;				// Magic Number "DDS " //
	
	// DDS_HEADER Chunk //
	unsigned HeaderSize;		// Always 124 (bytes) //
	unsigned Flags;				// Flags that list included information in this file //
	unsigned Height;
	unsigned Width;
	unsigned LinearSize;		// Byte size of first compressed mipmap //
	unsigned Depth;				// How many layers of volumetric textures (otherwise 0) //
	unsigned MipMapCount;		// Number of mipmap levels (otherwise 0) //

	unsigned Reserved1[7];		// Unused (usually 11, but I found something) //
	unsigned ExporterInfo[4];	// Information about the exporter application (ignore this) //
	
	DDSPixelFormat PixelFormat;	// The pixel format (32 bytes, 8 DWORD's) //

	unsigned Caps;				// Legacy Capabilities Flags (Ignore this unless writing) //
	unsigned CubeVolumeCaps;	// Legacy Capabilities Flags (Ignore this unless writing) //
	unsigned Reserved2[3];		// Unused... Formely "DDSCaps" and "Reserved2" //

	// Including the Magic Number, the above should total 128 bytes (32 DWORD's) //

	// The rest of the file (Texture Data Chunks, or a Texture Array Header then Data Chunks) //
	unsigned char Data[0];		// Everything following is Data //
} DDSTexture;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DDS Texture Flags //
// - ------------------------------------------------------------------------------------------ - //
#define DDSD_CAPS			??		// Has Capabilities Section (required, even though obsolete) //
#define DDSD_HEIGHT			??		// Has Height (required) //
#define DDSD_WIDTH			??		// Has Width (required) //
#define DDSD_PITCH			??		// Has a Pitch provided for an uncompressed texture //
#define DDSD_LINEARSIZE		??		// Has a Linear Size provided for the 1st compressed texture //
#define DDSD_DEPTH			??		// Has a Depth //
#define DDSD_PIXELFORMAT	??		// Has Pixel Format Section (required) //
#define DDSD_MIPMAPCOUNT	??		// Has a Mipmap Count //
// - ------------------------------------------------------------------------------------------ - //
#define DDSD_DEFAULT				(DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT)
#define DDSD_DEFAULT_MIPMAPPED		(DDSD_DEFAULT|DDSD_LINEARSIZE|DDSD_MIPMAPCOUNT)
#define DDSD_DEFAULT_VOLUMETRIC		(DDSD_DEFAULT|DDSD_PITCH|DDSD_DEPTH)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DDS Pixel Format Flags //
// - ------------------------------------------------------------------------------------------ - //
#define DDSPF_RGB			??		// Uncompressed RGB Data //
#define DDSPF_FOURCC		??		// Texture contains Compressed Data, FourCC says what kind //
#define DDSPF_ALPHAPIXELS	??		// Texture contains Alpha Data //
// - ------------------------------------------------------------------------------------------ - //
#define DDSPF_DEFAULT						0
#define DDSPF_DEFAULT_UNCOMPRESSED			(DDSPF_RGB)
#define DDSPF_DEFAULT_COMPRESSED			(DDSPF_FOURCC)
#define DDSPF_DEFAULT_UNCOMPRESSED_ALPHA	(DDSPF_DEFAULT_UNCOMPRESSED|DDSPF_ALPHAPIXELS)
#define DDSPF_DEFAULT_COMPRESSED_ALPHA		(DDSPF_DEFAULT_COMPRESSED|DDSPF_ALPHAPIXELS)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DDS Capability Flags (LEGACY - Writing only) //
// - ------------------------------------------------------------------------------------------ - //
#define DDSCAPS_COMPLEX		??		// File contains multiple surfaces (mipmaps, cubemaps, etc) //
#define DDSCAPS_MIPMAP		??		// File contains mipmaps //
#define DDSCAPS_TEXTURE		??		// Says the file contains texture information (required) //
// - ------------------------------------------------------------------------------------------ - //
#define DDSCAPS_DEFAULT					(DDSCAPS_TEXTURE)
#define DDSCAPS_DEFAULT_MIPMAPPED		(DDSCAPS_DEFAULT|DDSCAPS_COMPLEX|DDSCAPS_MIPMAP)
// - ------------------------------------------------------------------------------------------ - //
#define DDSCVCAPS_DEFAULT				0
#define DDSCVCAPS_DEFAULT_CUBEMAP		?? // NOTE: If used, all faces should be set //
#define DDSCVCAPS_DEFAULT_VOLUMETRIC	??
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// *NOTE* The above is everything you need for DDS Files. //
// - ------------------------------------------------------------------------------------------ - //
//   DirectX 10 support a featured called Texture Arrays, and the DDS file format can be extended //
//   to contain a collection of prearranged sets of textures.  They can be used as an alternative //
//   to a texture atlas.  There's likely a command and other stream that says what texture in the //
//   array to use, like how GL lets you use an Index Array to specify vert/uv/colors that make up //
//   faces. //
// - ------------------------------------------------------------------------------------------ - //
//   It almost seems as if this DDS_HEADER_DXT10 format is native, like a brief texture //
//   compression header found in DXT or PVR information. //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DDS Texture Arrays //
// - ------------------------------------------------------------------------------------------ - //
typedef enum /*DXGI_FORMAT*/ {
    DXGI_FORMAT_UNKNOWN = 0,
    DXGI_FORMAT_R32G32B32A32_TYPELESS = 1,
    DXGI_FORMAT_R32G32B32A32_FLOAT = 2,
    DXGI_FORMAT_R32G32B32A32_UINT = 3,
    DXGI_FORMAT_R32G32B32A32_SINT = 4,
    DXGI_FORMAT_R32G32B32_TYPELESS = 5,
    DXGI_FORMAT_R32G32B32_FLOAT = 6,
    DXGI_FORMAT_R32G32B32_UINT = 7,
    DXGI_FORMAT_R32G32B32_SINT = 8,
    DXGI_FORMAT_R16G16B16A16_TYPELESS = 9,
    DXGI_FORMAT_R16G16B16A16_FLOAT = 10,
    DXGI_FORMAT_R16G16B16A16_UNORM = 11,
    DXGI_FORMAT_R16G16B16A16_UINT = 12,
    DXGI_FORMAT_R16G16B16A16_SNORM = 13,
    DXGI_FORMAT_R16G16B16A16_SINT = 14,
    DXGI_FORMAT_R32G32_TYPELESS = 15,
    DXGI_FORMAT_R32G32_FLOAT = 16,
    DXGI_FORMAT_R32G32_UINT = 17,
    DXGI_FORMAT_R32G32_SINT = 18,
    DXGI_FORMAT_R32G8X24_TYPELESS = 19,
    DXGI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
    DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
    DXGI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
    DXGI_FORMAT_R10G10B10A2_TYPELESS = 23,
    DXGI_FORMAT_R10G10B10A2_UNORM = 24,
    DXGI_FORMAT_R10G10B10A2_UINT = 25,
    DXGI_FORMAT_R11G11B10_FLOAT = 26,
    DXGI_FORMAT_R8G8B8A8_TYPELESS = 27,
    DXGI_FORMAT_R8G8B8A8_UNORM = 28,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
    DXGI_FORMAT_R8G8B8A8_UINT = 30,
    DXGI_FORMAT_R8G8B8A8_SNORM = 31,
    DXGI_FORMAT_R8G8B8A8_SINT = 32,
    DXGI_FORMAT_R16G16_TYPELESS = 33,
    DXGI_FORMAT_R16G16_FLOAT = 34,
    DXGI_FORMAT_R16G16_UNORM = 35,
    DXGI_FORMAT_R16G16_UINT = 36,
    DXGI_FORMAT_R16G16_SNORM = 37,
    DXGI_FORMAT_R16G16_SINT = 38,
    DXGI_FORMAT_R32_TYPELESS = 39,
    DXGI_FORMAT_D32_FLOAT = 40,
    DXGI_FORMAT_R32_FLOAT = 41,
    DXGI_FORMAT_R32_UINT = 42,
    DXGI_FORMAT_R32_SINT = 43,
    DXGI_FORMAT_R24G8_TYPELESS = 44,
    DXGI_FORMAT_D24_UNORM_S8_UINT = 45,
    DXGI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
    DXGI_FORMAT_X24_TYPELESS_G8_UINT = 47,
    DXGI_FORMAT_R8G8_TYPELESS = 48,
    DXGI_FORMAT_R8G8_UNORM = 49,
    DXGI_FORMAT_R8G8_UINT = 50,
    DXGI_FORMAT_R8G8_SNORM = 51,
    DXGI_FORMAT_R8G8_SINT = 52,
    DXGI_FORMAT_R16_TYPELESS = 53,
    DXGI_FORMAT_R16_FLOAT = 54,
    DXGI_FORMAT_D16_UNORM = 55,
    DXGI_FORMAT_R16_UNORM = 56,
    DXGI_FORMAT_R16_UINT = 57,
    DXGI_FORMAT_R16_SNORM = 58,
    DXGI_FORMAT_R16_SINT = 59,
    DXGI_FORMAT_R8_TYPELESS = 60,
    DXGI_FORMAT_R8_UNORM = 61,
    DXGI_FORMAT_R8_UINT = 62,
    DXGI_FORMAT_R8_SNORM = 63,
    DXGI_FORMAT_R8_SINT = 64,
    DXGI_FORMAT_A8_UNORM = 65,
    DXGI_FORMAT_R1_UNORM = 66,
    DXGI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
    DXGI_FORMAT_R8G8_B8G8_UNORM = 68,
    DXGI_FORMAT_G8R8_G8B8_UNORM = 69,
    DXGI_FORMAT_BC1_TYPELESS = 70,
    DXGI_FORMAT_BC1_UNORM = 71,
    DXGI_FORMAT_BC1_UNORM_SRGB = 72,
    DXGI_FORMAT_BC2_TYPELESS = 73,
    DXGI_FORMAT_BC2_UNORM = 74,
    DXGI_FORMAT_BC2_UNORM_SRGB = 75,
    DXGI_FORMAT_BC3_TYPELESS = 76,
    DXGI_FORMAT_BC3_UNORM = 77,
    DXGI_FORMAT_BC3_UNORM_SRGB = 78,
    DXGI_FORMAT_BC4_TYPELESS = 79,
    DXGI_FORMAT_BC4_UNORM = 80,
    DXGI_FORMAT_BC4_SNORM = 81,
    DXGI_FORMAT_BC5_TYPELESS = 82,
    DXGI_FORMAT_BC5_UNORM = 83,
    DXGI_FORMAT_BC5_SNORM = 84,
    DXGI_FORMAT_B5G6R5_UNORM = 85,
    DXGI_FORMAT_B5G5R5A1_UNORM = 86,
    DXGI_FORMAT_B8G8R8A8_UNORM = 87,
    DXGI_FORMAT_B8G8R8X8_UNORM = 88,
    DXGI_FORMAT_FORCE_UINT = 0xffffffffUL,
} DXGI_FORMAT;
// - ------------------------------------------------------------------------------------------ - //
typedef enum /*D3D10_RESOURCE_DIMENSION*/ {
    D3D10_RESOURCE_DIMENSION_UNKNOWN = 0,
    D3D10_RESOURCE_DIMENSION_BUFFER = 1,
    D3D10_RESOURCE_DIMENSION_TEXTURE1D = 2,
    D3D10_RESOURCE_DIMENSION_TEXTURE2D = 3,
    D3D10_RESOURCE_DIMENSION_TEXTURE3D = 4,
} D3D10_RESOURCE_DIMENSION;
// - ------------------------------------------------------------------------------------------ - //
typedef enum /*D3D10_RESOURCE_MISC_FLAG*/ {
    D3D10_RESOURCE_MISC_GENERATE_MIPS = 0x1L,
    D3D10_RESOURCE_MISC_SHARED = 0x2L,
    D3D10_RESOURCE_MISC_TEXTURECUBE = 0x4L,
} D3D10_RESOURCE_MISC_FLAG;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DDS Texture Array Header //
typedef struct /*DDS_HEADER_DXT10*/ {
	DXGI_FORMAT dxgiFormat;							// The Surface Pixel Format //
	D3D10_RESOURCE_DIMENSION resourceDimension;		// The type of resource being used //
	unsigned miscFlag;								// Less common resource options //
	unsigned arraySize;								// Number of Elements in the Array //
	unsigned reserved;
} DDS_HEADER_DXT10;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Texture //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_TEXTURE_TEXTURE_DDS_H__ //
// - ------------------------------------------------------------------------------------------ - //
