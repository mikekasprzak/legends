// - ------------------------------------------------------------------------------------------ - //
#ifndef __Audio_AudioStream_H__
#define __Audio_AudioStream_H__
// - ------------------------------------------------------------------------------------------ - //
#include "AudioSource.h"
#include "AudioInfo.h"
// - ------------------------------------------------------------------------------------------ - //
struct AudioStream {
	AudioSource* CurrentSource;
	AudioState State;
	float Pitch;
	float Volume;
	bool Loop;
	bool Paused;

public:
	AudioStream() :
		CurrentSource( 0 ),
		State( AUDIOSTATE_FINISHED ),
		Paused( false )
	{
	}
	
public:
	bool IsActive() {
		return AudioState_IsPlaying( State );
	}

	void Play( AudioSource* Source, float _Volume = 0.25f, float _Pitch = 1.0f, bool _Loop = false ) {
		Volume = _Volume;
		Pitch = _Pitch;
		Loop = _Loop;
		CurrentSource = Source;
		State = AUDIOSTATE_START;
	}
	
	void SetPitch( float _Pitch ) {
		Pitch = _Pitch;
	}
	
	void SetVolume( float _Volume ) {
		Volume = _Volume;
	}
	
	void Stop() {
		CurrentSource = 0;
		State = AUDIOSTATE_FINISHED;
	}
	
	void Pause() {
		Paused = true;
	}

	void Resume() {
		Paused = false;
	}

	bool IsSource( const AudioSource* Source ) {
		return CurrentSource == Source;
	}
	
	void Decode( void* OutBlock, const AudioInfo* Info, const int SampleCount ) {
		if ( AudioState_IsPlaying( State ) && !Paused ) {
			State = CurrentSource->Decode( OutBlock, Info, SampleCount, State, Volume, Pitch, Loop );
		}
	} 
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Audio_AudioStream_H__ //
// - ------------------------------------------------------------------------------------------ - //
