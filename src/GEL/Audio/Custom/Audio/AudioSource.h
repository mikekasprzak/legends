// - ------------------------------------------------------------------------------------------ - //
#ifndef __Audio_AudioSource_H__
#define __Audio_AudioSource_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Core/DataBlock.h>
#include "AudioInfo.h"
#include "AudioDecoder.h"

// TODO: Remove this //
#include "WAVFile.h"
// - ------------------------------------------------------------------------------------------ - //
struct AudioSource {
	// NOTE: Verbatum the "AudioInfo" structure //
	int SampleRate;
	int Channels;
	int BitsPerSample;
	int SampleSize;
	
	// Source Specific data continues here //
	int LengthInBytes;
	int LengthInSamples;
	void* Data;
	
	AudioDecoder* Decoder;
	DataBlock* FileData;

public:
	AudioSource() :
		SampleRate( 44100 ),
		Channels(1),
		BitsPerSample(16),
		SampleSize(2),
		
		LengthInBytes(0),
		LengthInSamples(0),
		
		Decoder(0),
		FileData(0)
	{
	}

	~AudioSource() {
		if (FileData) {
			delete_DataBlock( FileData );
		}
	}

public:
	// TODO: Factor in Pitch and Volume //
	AudioState Decode( void* OutBlock, const AudioInfo* Info, const int SampleCount, AudioState State, const float Volume = 1.0f, const float Pitch = 1.0f, const bool Loop = false ) const {
		// Bail if not playing //
		if ( !AudioState_IsPlaying(State) )
			return State;
		
		#define PITCH_SHIFTER 16
		#define VOLUME_SHIFTER 8
		#define MAX_FREQ ((1<<15)-1)
		#define MIN_FREQ (-(1<<15))
		
		// Do Decoding ------------------------------- //
		short* Out = (short*)OutBlock;
		short* In = (short*)Data;

		int IntVolume = (int)(Volume * (float)(1<<VOLUME_SHIFTER));
		
		int StepSize = (int)(Pitch * (float)(1<<PITCH_SHIFTER));

		int TotalSamplesDecoded = 0;
		do {
			int SampleStep = 0;
			
			int SamplesToDecode = SampleCount - TotalSamplesDecoded;
			int SamplesToStep = (SamplesToDecode * StepSize)>>PITCH_SHIFTER;
			
			if ( State+(SamplesToStep) >= LengthInSamples ) {
				SamplesToDecode = LengthInSamples-State;
				if ( SamplesToDecode > SampleCount ) {
					SamplesToDecode <<= PITCH_SHIFTER;
					SamplesToDecode /= StepSize;
				}
				SamplesToStep = (SamplesToDecode * StepSize)>>PITCH_SHIFTER;
			}
			
			// TODO: Optimize this loop //
			for ( int idx = 0; idx < SamplesToDecode; idx++ ) {
				int SampleIndex = (State + (SampleStep>>PITCH_SHIFTER)) * Channels;
				
				// NOTE: shifted down by 1, since it's too loud //
				int Sample = ((int)Out[idx]) + (((((int)In[SampleIndex]) * IntVolume)>>VOLUME_SHIFTER)>>0);
				SampleStep += StepSize;
				
				// Frequency Clamping  //
				if ( Sample > MAX_FREQ ) {
					Sample = MAX_FREQ;
				}
				else if ( Sample < MIN_FREQ ) {
					Sample = MIN_FREQ;
				}
				
				// Write the Sample //	
				Out[idx] = Sample;
			}
			
			#undef PITCH_SHIFTER
			#undef VOLUME_SHIFTER
			
			// Update State ------------------------------ //
			State += SamplesToStep;
			TotalSamplesDecoded += SamplesToStep;
			if ( State >= LengthInSamples ) {
				if ( Loop ) {
					State = 0;
				}
				else {
					State = AUDIOSTATE_FINISHED;
				}
			}
		} while ( Loop && (TotalSamplesDecoded < SampleCount) );
		
		return State;
	}
};
// - ------------------------------------------------------------------------------------------ - //
inline void Free_AudioSource( AudioSource* Source ) {
	delete Source;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Audio_AudioSource_H__ //
// - ------------------------------------------------------------------------------------------ - //
