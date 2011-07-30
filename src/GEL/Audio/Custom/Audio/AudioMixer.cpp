// - ------------------------------------------------------------------------------------------ - //
#include <Core/Data.h>
#include "AudioMixer.h"
// - ------------------------------------------------------------------------------------------ - //
AudioMixer::AudioMixer() {
	LengthInSamples = 1024+256+128;//2048;//1024;//44100/25;//1024;
	GlobalVolume = 1.0f;

	Info.SampleRate = 44100;
	Info.Channels = 1;
	Info.BitsPerSample = 16;
	Info.SampleSize = 2;

	ActiveBuffer = new char[LengthInSamples*Info.SampleSize];
	PassiveBuffer = new char[LengthInSamples*Info.SampleSize];
	
	StreamCount = 8;
	Stream = new AudioStream[StreamCount];
	
	ClearActiveBuffer();
	ClearPassiveBuffer();
}
// - ------------------------------------------------------------------------------------------ - //
AudioMixer::~AudioMixer() {
	delete [] Stream;
	delete [] PassiveBuffer;
	delete [] ActiveBuffer;
}
// - ------------------------------------------------------------------------------------------ - //
void AudioMixer:: ClearActiveBuffer() {
	set_Data( 0, (void*)ActiveBuffer, LengthInSamples*Info.SampleSize );
}
// - ------------------------------------------------------------------------------------------ - //
void AudioMixer:: ClearPassiveBuffer() {
	set_Data( 0, (void*)PassiveBuffer, LengthInSamples*Info.SampleSize );
}
// - ------------------------------------------------------------------------------------------ - //
void AudioMixer:: SwapBuffers() {
	char* Temp = ActiveBuffer;
	ActiveBuffer = PassiveBuffer;
	PassiveBuffer = Temp;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void AudioMixer:: UpdateBuffer() {
	ClearPassiveBuffer();
	// TODO: Loop optimize this (minor, but may as well) //
	for ( int idx = 0; idx < StreamCount; idx++ ) {
		Stream[idx].Decode( (void*)PassiveBuffer, &Info, LengthInSamples );
	}
	
	SwapBuffers();
}
// - ------------------------------------------------------------------------------------------ - //
void AudioMixer::Play( AudioSource* Sound, const float Volume, const float Pitch, const bool Loop ) {
	if ( Sound == 0 )
		return;
	
	// TODO: Optimize by making this a ring buffer. I.e. remember last given sound, and circle around. //
	for ( int idx = 0; idx < StreamCount; idx++ ) {
		if ( !Stream[idx].IsActive() ) {
			Stream[idx].Play( Sound, Volume * GlobalVolume, Pitch, Loop );
			return;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void AudioMixer::Stop( AudioSource* Sound ) {
	if ( Sound == 0 )
		return;
	
	for ( int idx = 0; idx < StreamCount; idx++ ) {
		if ( Stream[idx].IsSource( Sound ) ) {
			Stream[idx].Stop();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
int AudioMixer::FindChannel( AudioSource* Sound ) {
	for ( int idx = 0; idx < StreamCount; idx++ ) {
		if ( Stream[idx].IsSource( Sound ) ) {
			return idx+1;
		}
	}
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
void AudioMixer::Pause( AudioSource* Sound ) {
	if ( Sound == 0 )
		return;

	for ( int idx = 0; idx < StreamCount; idx++ ) {
		if ( Stream[idx].IsSource( Sound ) ) {
			Stream[idx].Pause();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void AudioMixer::Resume( AudioSource* Sound ) {
	if ( Sound == 0 )
		return;

	for ( int idx = 0; idx < StreamCount; idx++ ) {
		if ( Stream[idx].IsSource( Sound ) ) {
			Stream[idx].Resume();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

