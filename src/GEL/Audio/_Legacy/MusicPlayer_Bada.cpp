// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_BADA
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>

#include <BadaPlayer.h>
#include "MusicPlayer.h"
// - ------------------------------------------------------------------------------------------ - //
int MusicEnabled;
int CurrentSong;
int LastSong;

float CurrentFade;
float TargetFade;
float FadeRate;

bool ChangeTrack;
// - ------------------------------------------------------------------------------------------ - //
BadaPlayer* MyBadaPlayer = 0;

#define musLoad( _id, _s ) \
	"/Res/Music/" _s ".aac",

char* MusicFile[] = {
	#include "MusicFiles.inc"
};
// - ------------------------------------------------------------------------------------------ - //
void musPlay( int SoundName ) {
	if ( MusicEnabled ) {
		if ( CurrentSong != SoundName ) {
			musUpdate();
			if ( MyBadaPlayer )
				MyBadaPlayer->Play( MusicFile[SoundName], CurrentFade );
			
			LastSong = CurrentSong;
			CurrentSong = SoundName;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musStop() {
	if ( MyBadaPlayer )
		MyBadaPlayer->Stop();
	CurrentFade = 0;
	CurrentSong = -1;
	ChangeTrack = false;
}
// - ------------------------------------------------------------------------------------------ - //
void musPause() {
	if ( CurrentSong != -1 ) {
		if ( MyBadaPlayer ) {
			MyBadaPlayer->SetVolume( 0 );
			MyBadaPlayer->Pause();
		}

		CurrentFade = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musResume() {
	if ( CurrentSong != -1 ) {
		if ( MyBadaPlayer ) {
			MyBadaPlayer->Resume();
		}
		CurrentFade = 0;
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
		CurrentSong++;
		if ( CurrentSong >= MUS_MAX ) {
			CurrentSong = 0;
		}
		ChangeTrack = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musInit() {
	CurrentSong = -1;
	LastSong = -1;

	CurrentFade = 0.0f;
	TargetFade = 1.0f;
	FadeRate = 0.01f;
	
	ChangeTrack = false;

	MyBadaPlayer = new BadaPlayer();
	MyBadaPlayer->Init();
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
				if ( MyBadaPlayer )
					MyBadaPlayer->Play( MusicFile[CurrentSong], CurrentFade );

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

		if ( MyBadaPlayer )
			MyBadaPlayer->SetVolume( CurrentFade );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musFree() {
	musStop();
	
	if ( MyBadaPlayer ) {
		MyBadaPlayer->Exit();
		delete MyBadaPlayer;
		MyBadaPlayer = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_BADA //
// - ------------------------------------------------------------------------------------------ - //
