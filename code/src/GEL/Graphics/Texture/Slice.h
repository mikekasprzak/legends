

/*
"SLIC" - Magic number for slice files

ChunkSize - Number of bytes the slices chunk is
 SliceCount - Number of slices
 Slice[x] - All the slices

ChunkSize - Number of bytes the strings chunk is
 char[x] - Text

ChunkSize
 IMAGE DATA

*/

// NOTE: I've used signed numbers here, so you have the option to create edge overlapping slices //
// - ------------------------------------------------------------------------------------------ - //
struct SLICE_Chunk {
	unsigned int ChunkSize;		// Size of chunk (omitting the Magic Number and size) // 
	unsigned int Magic;			// Magic Number //

	char Data[0];
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct SLICE_Slice {
	short w, h;					// Dimensions of our sub image //
	short x, y;					// Offset in to the original image //
	
	unsigned int ImageNumber;	// Which Image Chunk to associate with //
	unsigned int NameStart;		// The starting index in to the strings table //
};
// - ------------------------------------------------------------------------------------------ - //
struct SLICE_SliceChunk {
	unsigned int ChunkSize;		// The entire size of the slices section //
	unsigned int Magic;			// Magic Number "SLCE" //

	unsigned int Count;			// How many slices //
	SLICE_Slice Slice[0];		// Our slices //
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
struct SLICE_Header {
	unsigned int SLIC;			// Magic Number "SLIC" //
	
	char Data[0];
};
// - ------------------------------------------------------------------------------------------ - //

/*

SLICE_Header				// Magic Number "SLIC" //

SLICE_SliceChunk Slice;		// Slice Info Chunk "SLI " //	
SLICE_Chunk Strings;		// String Table Chunk "STR " //
SLICE_Chunk Image;			// Image File Chunk //
...							// (Optional) More Image File Chunks //

*/

