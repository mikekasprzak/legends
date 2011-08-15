// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
#include "IMAFile.h"
#include "IMAFile_Load.h"
// - ------------------------------------------------------------------------------------------ - //
// NOTE: For now, we'll use the WAV decoder.  IMA we'll only use during load. //
#include "WAVFile_Decoder.h"
#include "IMAFile_Decoder.h"
// - ------------------------------------------------------------------------------------------ - //
AudioSource* Load_IMAFile( const char* File ) {
	AudioSource* Source = new AudioSource;
	
	// NOTE: This is only temporary. Read 
	DataBlock* InputFile = new_read_DataBlock( File );

	if ( InputFile == 0 ) {
		Log("* IMA READ FAILED\n");
		delete Source;
		return 0;
	}

/*	
	Source->FileData = new_read_DataBlock( File );

	if ( Source->FileData == 0 ) {
		Log("* WAV READ FAILED\n");
		delete Source;
		return 0;
	}
*/	
	
	// Allocate a chunk of memory 4x our size (to decode the IMA to) //
	Source->FileData = new_DataBlock( InputFile->Size * 4 );
	
	// Decode IMA data to the buffer //
	DecodeADPCM( InputFile->Data, Source->FileData->Data, InputFile->Size );
	
	// Fade in/out the start and end of the buffer //
	{
		short* FadeIn = (short*)Source->FileData->Data;
		short* FadeOut = (short*)&Source->FileData->Data[Source->FileData->Size];
		FadeIn[0] = 0;
		int Max = 128;
		if ( Source->FileData->Size < 128 )
			Max = Source->FileData->Size;
			
		for ( int idx = 1; idx < Max; idx++ ) {
			float Scalar = ((float)idx) / 128.0f;
			FadeIn[idx] = (short)(((float)FadeIn[idx]) * Scalar);
			FadeOut[-idx] = (short)(((float)FadeOut[-idx]) * Scalar);
		}
	}
	
	// Throw away the loaded file //
	delete_DataBlock( InputFile );
	

	// Temporary, but correct. // 
	// Though we're loading the file as an IMA, we'll be using the WAV decoder (once decoders work) //
	Source->Decoder = (AudioDecoder*)&WAVFileDecoderInstance;
	
	Source->SampleRate = 44100;//WAVFile_GetFMTChunk(Source->FileData->Data)->SampleRate;
	Source->Channels = 1;//WAVFile_GetFMTChunk(Source->FileData->Data)->NumberOfChannels;
	Source->BitsPerSample = 16;//WAVFile_GetFMTChunk(Source->FileData->Data)->BitsPerSample;
	Source->SampleSize = 2;//WAVFile_GetFMTChunk(Source->FileData->Data)->SampleSize;
	
	Source->LengthInBytes = Source->FileData->Size;//WAVFile_GetDataSize(Source->FileData->Data);
	Source->LengthInSamples = Source->FileData->Size >> 1;//Source->LengthInBytes / Source->SampleSize;
	Source->Data = Source->FileData->Data;//WAVFile_GetData(Source->FileData->Data);
	
	Log("- *IMA* SampleRate: %i  Channels: %i\n",Source->SampleRate,Source->Channels);
	
	return Source;
}
// - ------------------------------------------------------------------------------------------ - //
void Free_IMAFile( AudioSource* Source ) {
	Free_AudioSource( Source );
}
// - ------------------------------------------------------------------------------------------ - //
