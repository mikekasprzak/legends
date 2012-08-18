// - ------------------------------------------------------------------------------------------ - //
#ifndef __PVR3Texture_H__
#define __PVR3Texture_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Nonstandard Extension: Zero Sized Array in Struct/Union
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int 			pvr_u32;
typedef unsigned long long int	pvr_u64;
// - ------------------------------------------------------------------------------------------ - //
struct PVR3Texture {		// Header is always 52 bytes //
	pvr_u32 Version;		// Magic Number 'P' 'V' 'R' 3 //
	pvr_u32 Flags;
	pvr_u64 PixelFormat;	// 64 bit descriptor of the data //
	pvr_u32 ColorSpace;		// 0 - Linear RGB, 1 - sRGB
	pvr_u32 ChannelType;	// 
	pvr_u32 Height;
	pvr_u32 Width;
	pvr_u32 Depth;			// Typically 1. Number of layers in a 3D texture (Z) //
	pvr_u32 NumSurfaces;	// Typically 1. Number of surfaces in a texture array //
	pvr_u32 NumFaces;		// Typically 1. Number of faces in a Cube Map //  
	pvr_u32 MipMapCount;	// 1 or more. Number of Mip Maps in this texture //
	pvr_u32 MetaDataSize;	// Size of the "Meta Data" section in bytes (comes before data) //

	unsigned char Data[0];	// The "Meta Data" and "Texture Data" sections follow //
};
// - ------------------------------------------------------------------------------------------ - //
struct PVR3MetaData {		// Header is is always 12 bytes //
	pvr_u32 FourCC;			// Four Byte Identifier //
	pvr_u32	Key;			// Paired with FourCC, determines what the Meta Data does //
	pvr_u32 Size;			// Size in bytes of this Meta Data Section //
	
	unsigned char Data[0];	// Actual Meta Data follows //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define PVR3_MAGIC_LE		0x03525650
#define PVR3_MAGIC_BE		0x50565203
#define PVR3_MAGIC			PVR3_MAGIC_LE
// - ------------------------------------------------------------------------------------------ - //
#define PVR3_RGBA_8888		0x0808080861626772LL		// OGL8888 //
#define PVR3_RGBA_4444		0x0404040461626772LL		// OGL4444 //

#define PVR3_ARGB_8888		0x0808080862677261LL		// 8888 //
#define PVR3_ARGB_4444		0x0404040462677261LL		// 4444 //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline bool IsPVR3( const void* Data ) {
	return ((PVR3Texture*)Data)->Version == PVR3_MAGIC;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __PVR3Texture_H__ //
// - ------------------------------------------------------------------------------------------ - //
