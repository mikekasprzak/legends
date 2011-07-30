// - ------------------------------------------------------------------------------------------ - //
#ifndef __Audio_AudioMixer_H__
#define __Audio_AudioMixer_H__
// - ------------------------------------------------------------------------------------------ - //
#include "AudioStream.h"
#include "AudioInfo.h"
#include "AudioSource.h"
// - ------------------------------------------------------------------------------------------ - //
struct AudioMixer {
	AudioInfo Info;
	int LengthInSamples;
	char* ActiveBuffer;
	char* PassiveBuffer;
	
	int StreamCount;
	AudioStream* Stream;
	
	float GlobalVolume;
	
public:
	AudioMixer();
	~AudioMixer();
public:
	void ClearActiveBuffer();
	void ClearPassiveBuffer();
	void SwapBuffers();
	
public:
	void UpdateBuffer();
	void Play( AudioSource* Sound, const float Volume = 1.0f, const float Pitch = 1.0f, const bool Loop = false );
	void Stop( AudioSource* Sound );

	void Pause( AudioSource* Sound );
	void Resume( AudioSource* Sound );

	int FindChannel( AudioSource* Sound );
	
	inline char* GetData() {
		return ActiveBuffer;
	}
	
	inline int GetSize() {
		return LengthInSamples*Info.SampleSize;
	}
	
	inline int GetSizeInSamples() {
		return LengthInSamples;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Audio_AudioMixer_H__ //
// - ------------------------------------------------------------------------------------------ - //
