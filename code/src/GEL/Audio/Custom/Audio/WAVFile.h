// - ------------------------------------------------------------------------------------------ - //
#ifndef __WAVFile_H__
#define __WAVFile_H__
// - ------------------------------------------------------------------------------------------ - //
// I used the spec found here: https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Nonstandard Extension: Zero Sized Array in Struct/Union
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Standard Uncompressed WAV File Header.  Compressed files are *slightly* different. //
// - ------------------------------------------------------------------------------------------ - //
struct WAVFile {
	// "RIFF" Chunk //
	unsigned int ChunkID;		// "RIFF", 0x52494646 //
	int ChunkSize;				// 36 + SubChunk2Size, or rather 4+(8+SubChunk1Size)+(8+SubChunk2Size) //
	unsigned int Format;		// "WAVE", 0x57415645 //
	
	// "fmt " sub-chunk //
	unsigned int SubChunk1ID;	// "fmt ", 0x666d7420 //
	int SubChunk1Size;			// 16 for PCM WAV's //
	short AudioFormat;			// PCM=1, other values for other schemes //
	short NumberOfChannels;		// Mono=1, Stere=2 //
	int SampleRate;				// 8000, 44100, ... //
	int ByteRate;				// 176400 (44khz stereo 16bit) -- SampleRate * NumChannels * (BitsPerSample/8) //
	short SampleSize;			// 4 (stereo 16bit) -- NumChannels * (BitsPerSample/8) //
	short BitsPerSample;		// 8 (8bit), 16 (16bit) //
	// NOTE: Non PCM WAV's wolud have extra data after this point //
	
	// "data" sub-chunk //
	unsigned int SubChunk2ID;	// "data", 0x64617461 //
	int SubChunk2Size;			// Data Size -- NumSamples * NumChannels * BitsPerSample/8 //
	unsigned char Data[0];		// Actual Data //
};
// - ------------------------------------------------------------------------------------------ - //
struct WAVFile_RIFFChunk {
	// "RIFF" Chunk //
	unsigned int ChunkID;		// "RIFF", 0x52494646 //
	int ChunkSize;				// 36 + SubChunk2Size, or rather 4+(8+SubChunk1Size)+(8+SubChunk2Size) //

	unsigned int Format;		// "WAVE", 0x57415645 //
};
// - ------------------------------------------------------------------------------------------ - //
struct WAVFile_FMTChunk {	
	// "fmt " sub-chunk //
	unsigned int ChunkID;		// "fmt ", 0x666d7420 //
	int ChunkSize;				// 16 for PCM WAV's //

	short AudioFormat;			// PCM=1, other values for other schemes //
	short NumberOfChannels;		// Mono=1, Stere=2 //
	int SampleRate;				// 8000, 44100, ... //
	int ByteRate;				// 176400 (44khz stereo 16bit) -- SampleRate * NumChannels * (BitsPerSample/8) //
	short SampleSize;			// 4 bytes (stereo 16bit) -- NumChannels * (BitsPerSample/8) //
	short BitsPerSample;		// 8 (8bit), 16 (16bit) //
	// NOTE: Non PCM WAV's wolud have extra data after this point //
};
// - ------------------------------------------------------------------------------------------ - //
struct WAVFile_DataChunk {	
	// "data" sub-chunk //
	unsigned int ChunkID;		// "data", 0x64617461 //
	int ChunkSize;				// Data Size -- NumSamples * NumChannels * BitsPerSample/8 //

	unsigned char Data[0];		// Actual Data //
};
// - ------------------------------------------------------------------------------------------ - //
// * The default byte ordering assumed for WAVE data files is little-endian. Files written using 
//   the big-endian byte ordering scheme have the identifier RIFX instead of RIFF.
// * The sample data must end on an even byte boundary. Whatever that means.
// * 8-bit samples are stored as unsigned bytes, ranging from 0 to 255. 16-bit samples are stored
//   as 2's-complement signed integers, ranging from -32768 to 32767.
// * There may be additional subchunks in a Wave data stream. If so, each will have a 
//   char[4] SubChunkID, and unsigned long SubChunkSize, and SubChunkSize amount of data.
// * RIFF stands for Resource Interchange File Format. 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define CHUNK_HEADER_SIZE		8
// - ------------------------------------------------------------------------------------------ - //
#define WAV_CHUNK_RIFF_BE		0x52494646 // "RIFF" //
#define WAV_CHUNK_WAVE_BE		0x57415645 // "WAVE" //
#define WAV_CHUNK_FMT_BE		0x666d7420 // "fmt " //
#define WAV_CHUNK_DATA_BE		0x64617461 // "data" //
// - ------------------------------------------------------------------------------------------ - //
#define WAV_CHUNK_RIFF_LE		0x46464952 // "RIFF" //
#define WAV_CHUNK_WAVE_LE		0x45564157 // "WAVE" //
#define WAV_CHUNK_FMT_LE		0x20746d66 // "fmt " //
#define WAV_CHUNK_DATA_LE		0x61746164 // "data" //
// - ------------------------------------------------------------------------------------------ - //
#define WAV_CHUNK_RIFF			WAV_CHUNK_RIFF_LE
#define WAV_CHUNK_WAVE			WAV_CHUNK_WAVE_LE
#define WAV_CHUNK_FMT_			WAV_CHUNK_FMT_LE
#define WAV_CHUNK_DATA			WAV_CHUNK_DATA_LE
// - ------------------------------------------------------------------------------------------ - //
#define WAV_FORMAT_PCM			0x1
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Offsets //
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int WAVFile_GetSubChunk1Offset( const void* Data ) {
	return sizeof(WAVFile_RIFFChunk);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int WAVFile_GetSubChunk2Offset( const void* Data ) {
	const WAVFile* Wav = ((WAVFile*)Data);
	return sizeof(WAVFile_RIFFChunk) + (CHUNK_HEADER_SIZE + Wav->SubChunk1Size); 
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int WAVFile_GetFormatChunkOffset( const void* Data ) {
	return WAVFile_GetSubChunk1Offset(Data);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int WAVFile_GetDataChunkOffset( const void* Data ) {
	return WAVFile_GetSubChunk2Offset(Data);
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int WAVFile_GetDataOffset( const void* Data ) {
	return WAVFile_GetSubChunk2Offset(Data) + CHUNK_HEADER_SIZE; 
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// 
// - ------------------------------------------------------------------------------------------ - //
inline const WAVFile_RIFFChunk* WAVFile_GetRIFFChunk( const void* Data ) {
	return (WAVFile_RIFFChunk*)Data;
}
// - ------------------------------------------------------------------------------------------ - //
inline const WAVFile_FMTChunk* WAVFile_GetFMTChunk( const void* Data ) {
	return (WAVFile_FMTChunk*)(((char*)Data) + WAVFile_GetSubChunk1Offset(Data));
}
// - ------------------------------------------------------------------------------------------ - //
inline const WAVFile_DataChunk* WAVFile_GetDataChunk( const void* Data ) {
	return (WAVFile_DataChunk*)(((char*)Data) + WAVFile_GetSubChunk2Offset(Data));
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline unsigned char* WAVFile_GetData( const void* Data ) {
	return (unsigned char*)(((char*)Data) + WAVFile_GetDataOffset( Data ));
}
// - ------------------------------------------------------------------------------------------ - //
inline const unsigned int WAVFile_GetDataSize( const void* Data ) {
	return WAVFile_GetDataChunk(Data)->ChunkSize;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const short WAVFile_GetFormat( const void* Data ) {
	return WAVFile_GetFMTChunk(Data)->AudioFormat;
}
// - ------------------------------------------------------------------------------------------ - //
inline const int WAVFile_GetSampleRate( const void* Data ) {
	return WAVFile_GetFMTChunk(Data)->SampleRate;
}
// - ------------------------------------------------------------------------------------------ - //
inline const short WAVFile_GetNumberOfChannels( const void* Data ) {
	return WAVFile_GetFMTChunk(Data)->NumberOfChannels;
}
// - ------------------------------------------------------------------------------------------ - //
inline const short WAVFile_GetBitsPerSample( const void* Data ) {
	return WAVFile_GetFMTChunk(Data)->BitsPerSample;
}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
inline const int WAVFile_GetByteRate( const void* Data ) {
	return WAVFile_GetFMTChunk(Data)->ByteRate;
}
// - ------------------------------------------------------------------------------------------ - //
inline const int WAVFile_GetSampleSize( const void* Data ) {
	return WAVFile_GetFMTChunk(Data)->SampleSize;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline bool IsWAV( const void* Data ) {
	return ((WAVFile*)Data)->Format == WAV_CHUNK_WAVE;
}
// - ------------------------------------------------------------------------------------------ - //
inline bool IsPCMWAV( const void* Data ) {
	if ( IsWAV(Data) )
		return WAVFile_GetFormat(Data) == WAV_FORMAT_PCM;
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __WAVFile_H__
// - ------------------------------------------------------------------------------------------ - //
