// - ------------------------------------------------------------------------------------------ - //
#if defined( USES_IOS )
// - ------------------------------------------------------------------------------------------ - //
#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AVFoundation/AVFoundation.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include "MusicPlayer.h"
// - ------------------------------------------------------------------------------------------ - //
AVAudioPlayer* MusicPlayer = 0;
// - ------------------------------------------------------------------------------------------ - //
int MusicEnabled;
int CurrentSong;
int LastSong;

float CurrentFade;
float TargetFade;
float FadeRate;

bool ChangeTrack;
// - ------------------------------------------------------------------------------------------ - //
#define musLoad( _id, _s ) \
	_s,

char* MusicFile[] = {
	#include "MusicFiles.inc"
};
// - ------------------------------------------------------------------------------------------ - //
#undef musLoad
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool IsAudioPlaying() {
    // check if we've got music playing already ...
    UInt32 isPlaying;
    UInt32 propertySize = sizeof(isPlaying);
    AudioSessionInitialize(NULL, NULL, NULL, NULL);
    AudioSessionGetProperty(kAudioSessionProperty_OtherAudioIsPlaying, &propertySize, &isPlaying);
    return isPlaying;
}
// - ------------------------------------------------------------------------------------------ - //
void PlaySong( int SoundName ) {
	if ( IsAudioPlaying() )
		return;
	Log( "Playing: %s\n", MusicFile[SoundName] );
	NSString *soundFile = [[NSBundle mainBundle] pathForResource:[NSString stringWithCString: MusicFile[SoundName] encoding: [NSString defaultCStringEncoding]] ofType:@"caf"];
	
	if (MusicPlayer) {
	    [MusicPlayer stop];
	    [MusicPlayer release];
	    MusicPlayer = NULL;
	}
	
	MusicPlayer = [AVAudioPlayer alloc];
	[MusicPlayer initWithContentsOfURL: [NSURL fileURLWithPath:soundFile] error:nil];
	MusicPlayer.numberOfLoops = -1;
	MusicPlayer.volume = CurrentFade;

	[MusicPlayer prepareToPlay];
	[MusicPlayer stop];
	[MusicPlayer play];
}
// - ------------------------------------------------------------------------------------------ - //
void SetVolume( float Value ) {
	if ( MusicPlayer ) {
        MusicPlayer.volume = Value;
    }
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void musPlay( int SoundName ) {
	if ( MusicEnabled ) {
		if ( CurrentSong != SoundName ) {
			musUpdate();

			PlaySong( SoundName );
			
			LastSong = CurrentSong;
			CurrentSong = SoundName;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musStop() {
	if ( MusicPlayer ) {
		Log( "Stopping Music\n" );
        [MusicPlayer stop];
    }
	CurrentFade = 0;
	CurrentSong = -1;
	ChangeTrack = false;
}
// - ------------------------------------------------------------------------------------------ - //
void musPause() {
	if ( CurrentSong != -1 ) {
		if ( MusicPlayer ) {
			Log( "Pausing Music...\n" );
			[MusicPlayer pause];
		}
		CurrentFade = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musResume() {
	if ( CurrentSong != -1 ) {
		CurrentFade = 0;
		if ( MusicPlayer ) {
			Log( "Resuming Music...\n" );
			MusicPlayer.volume = CurrentFade;
			[MusicPlayer play];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musSetVolume( float Value ) {
	TargetFade = Value;
}
// - ------------------------------------------------------------------------------------------ - //
void musSetFadeRate( float Value ) {
	FadeRate = Value;
}
// - ------------------------------------------------------------------------------------------ - //
void musNextTrack() {
	if ( MusicEnabled ) {
		Log( "Next Track...\n" );
		CurrentSong++;
		if ( CurrentSong >= MUS_MAX ) {
			CurrentSong = 0;
		}
		ChangeTrack = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
//#define musLoad( _id, _s ) \
//	MusicFile[_id] = Mix_LoadMUS( "Music/" _s ".ogg" );
// - ------------------------------------------------------------------------------------------ - //
void musInit() {
	Log( "Initialize Music...\n" );
	CurrentSong = -1;
	LastSong = -1;
	
	CurrentFade = 0.0f;
	TargetFade = 1.0f;
	FadeRate = 0.01f;
	
	ChangeTrack = false;
	
	MusicPlayer = 0;
	
//	#include "MusicFiles.inc"
}
// - ------------------------------------------------------------------------------------------ - //
void musUpdate() {
	if ( MusicEnabled ) {
		if ( ChangeTrack ) {
			if ( CurrentFade > 0 ) {
				CurrentFade -= FadeRate;
			}
			else {
				CurrentFade = 0;
	
				PlaySong( CurrentSong );
	
				ChangeTrack = false;
			}
		}
		else {
			if ( CurrentFade < TargetFade ) {
				CurrentFade += FadeRate;
			}
			else if ( CurrentFade > TargetFade ) {
				CurrentFade -= FadeRate;
			}
		}
	
		SetVolume( CurrentFade );	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musFree() {
	if ( MusicPlayer ) {
		Log( "Freeing Music...\n" );
		
        [MusicPlayer stop];
        [MusicPlayer release];
        MusicPlayer = NULL;
    }
}// - ------------------------------------------------------------------------------------------ - //
#endif // USES_IOS //
// - ------------------------------------------------------------------------------------------ - //
