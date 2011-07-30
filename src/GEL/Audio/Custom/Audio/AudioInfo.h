// - ------------------------------------------------------------------------------------------ - //
#ifndef __Audio_AudioInfo_H__
#define __Audio_AudioInfo_H__
// - ------------------------------------------------------------------------------------------ - //
struct AudioInfo {
	int SampleRate;
	int Channels;
	int BitsPerSample;
	int SampleSize;
};
// - ------------------------------------------------------------------------------------------ - //
enum {
	AUDIOSTATE_START = 0,
	AUDIOSTATE_FINISHED = -2,
};
// - ------------------------------------------------------------------------------------------ - //
typedef int AudioState;
// - ------------------------------------------------------------------------------------------ - //
inline bool AudioState_IsFinished( const AudioState& State ) {
	return State == AUDIOSTATE_FINISHED;
}
// - ------------------------------------------------------------------------------------------ - //
inline bool AudioState_IsPlaying( const AudioState& State ) {
	return State >= 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Audio_AudioInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //