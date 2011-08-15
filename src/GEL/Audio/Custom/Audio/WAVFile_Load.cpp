// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include "WAVFile.h"
#include "WAVFile_Load.h"
// - ------------------------------------------------------------------------------------------ - //
#include "WAVFile_Decoder.h"
// - ------------------------------------------------------------------------------------------ - //
AudioSource* Load_WAVFile( const char* File ) {
	AudioSource* Source = new AudioSource;
	
	Source->FileData = new_read_DataBlock( File );

	if ( Source->FileData == 0 ) {
		Log("* WAV READ FAILED\n");
		delete Source;
		return 0;
	}

	Source->Decoder = (AudioDecoder*)&WAVFileDecoderInstance;
	
	Source->SampleRate = WAVFile_GetFMTChunk(Source->FileData->Data)->SampleRate;
	Source->Channels = WAVFile_GetFMTChunk(Source->FileData->Data)->NumberOfChannels;
	Source->BitsPerSample = WAVFile_GetFMTChunk(Source->FileData->Data)->BitsPerSample;
	Source->SampleSize = WAVFile_GetFMTChunk(Source->FileData->Data)->SampleSize;
	
	Source->LengthInBytes = WAVFile_GetDataSize(Source->FileData->Data);
	Source->LengthInSamples = Source->LengthInBytes / Source->SampleSize;
	Source->Data = WAVFile_GetData(Source->FileData->Data);
	
	Log("- SampleRate: %i  Channels: %i\n",Source->SampleRate,Source->Channels);
	
	return Source;
}
// - ------------------------------------------------------------------------------------------ - //
void Free_WAVFile( AudioSource* Source ) {
	Free_AudioSource( Source );
}
// - ------------------------------------------------------------------------------------------ - //
