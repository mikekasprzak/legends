// - ------------------------------------------------------------------------------------------ - //
#ifndef PRODUCT_LEGACY_SMILES
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>

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
void musPlay( int SoundName ) {
	if ( MusicEnabled ) {
		if ( CurrentSong != SoundName ) {
			musUpdate();
//			SoundEngine_CurrentSong = SoundEngine->play2D( MusicFile[SoundName], true, false, true );
			
			LastSong = CurrentSong;
			CurrentSong = SoundName;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musStop() {
//	if ( SoundEngine_CurrentSong )
//		SoundEngine_CurrentSong->stop();
	CurrentFade = 0;
	CurrentSong = -1;
	ChangeTrack = false;
}
// - ------------------------------------------------------------------------------------------ - //
void musPause() {
	if ( CurrentSong != -1 ) {
//		if ( SoundEngine_CurrentSong ) {
//			SoundEngine_CurrentSong->setVolume( 0 );
//			SoundEngine_CurrentSong->setIsPaused(true);
//		}
		CurrentFade = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musResume() {
	if ( CurrentSong != -1 ) {
//		if ( SoundEngine_CurrentSong )
//			SoundEngine_CurrentSong->setIsPaused(false);
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
//		if ( CurrentSong >= MUS_MAX ) {
//			CurrentSong = 0;
//		}
		ChangeTrack = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#define musLoad( _id, _s ) \
{ \
	char FilePath[2048]; \
	extern char AppBaseDir[]; \
	sprintf( FilePath, "%sMusic/" _s ".ogg", AppBaseDir ); \
	MusicFile[_id] = SoundEngine->addSoundSourceFromFile( FilePath ); \
	MusicFile[_id]->setDefaultVolume(0); \
}
// - ------------------------------------------------------------------------------------------ - //
void musInit() {
	CurrentSong = -1;
	LastSong = -1;

	CurrentFade = 0.0f;
	TargetFade = 1.0f;
	FadeRate = 0.01f;
	
	ChangeTrack = false;

//	SoundEngine_CurrentSong = 0;

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
//				SoundEngine_CurrentSong = SoundEngine->play2D( MusicFile[CurrentSong], true, false, true );
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
		
//		if ( SoundEngine_CurrentSong )
//			SoundEngine_CurrentSong->setVolume( CurrentFade );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musFree() {
	musStop();

//	for ( int idx = 0; idx < MUS_MAX; idx++ ) {
//		MusicFile[idx]->drop();
//	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // PRODUCT_LEGACY_SMILES //
// - ------------------------------------------------------------------------------------------ - //
