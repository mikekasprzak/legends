// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL_MIXER
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#ifdef USES_SDL_BASEDIR
#include <SDL.h>
#include <SDL_mixer.h>
#else // USES_SDL_BASEDIR //
#include <SDL/SDL.h>
#ifdef USES_MAEMO
#include "Maemo/SDL_mixer.h"
#else // USES_MAEMO //
#include <SDL/SDL_mixer.h>
#endif // USES_MAEMO //
#endif // USES_SDL_BASEDIR //
#ifdef USES_WEBOS
#include <PDL.h>
#endif // USES_WEBOS //

#include "MusicPlayer.h"
// - ------------------------------------------------------------------------------------------ - //
int MusicEnabled;
int CurrentSong;
int LastSong;
Mix_Music* MusicFile[MUS_MAX];

float CurrentFade;
float TargetFade;
float FadeRate;

bool ChangeTrack;
// - ------------------------------------------------------------------------------------------ - //
void musPlay( int SoundName ) {
	if ( MusicEnabled ) {
		if ( CurrentSong != SoundName ) {
			double Pos = 0;	// Song Position //
			int Fade = 0;	// Do not use. I need my own fader. //

#ifdef USES_WEBOS
			PDL_NotifyMusicPlaying( PDL_TRUE );
#endif // USES_WEBOS //
			
			musUpdate();
			Log( "Is Playing Music: %i\n", Mix_PlayingMusic() );
			Mix_FadeInMusicPos(MusicFile[SoundName], -1, Fade, Pos);
			//Mix_PlayMusic(MusicFile[SoundName],-1);
			Log( "Playing Song %i [%i]\n", SoundName, Mix_GetMusicType(MusicFile[SoundName]) );
			Log( "Is Playing Music: %i\n", Mix_PlayingMusic() );
			
			LastSong = CurrentSong;
			CurrentSong = SoundName;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musStop() {
	Mix_HaltMusic();
	CurrentFade = 0;
	CurrentSong = -1;
	ChangeTrack = false;

#ifdef USES_WEBOS
	PDL_NotifyMusicPlaying( PDL_FALSE );
#endif // USES_WEBOS //
}
// - ------------------------------------------------------------------------------------------ - //
void musPause() {
	if ( CurrentSong != -1 ) {
		Mix_PauseMusic();
		CurrentFade = 0;

#ifdef USES_WEBOS
		PDL_NotifyMusicPlaying( PDL_FALSE );
#endif // USES_WEBOS //
	}

	SDL_PauseAudio(1);
}
// - ------------------------------------------------------------------------------------------ - //
void musResume() {
	SDL_PauseAudio(0);

	if ( CurrentSong != -1 ) {
#ifdef USES_WEBOS
		PDL_NotifyMusicPlaying( PDL_TRUE );
#endif // USES_WEBOS //

		Mix_ResumeMusic();
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
#define musLoad( _id, _s ) \
{ \
	char FilePath[2048]; \
	extern char AppBaseDir[]; \
	sprintf( FilePath, "%sMusic/" _s ".ogg", AppBaseDir ); \
	Log( "Added %s\n", FilePath ); \
	MusicFile[_id] = Mix_LoadMUS( FilePath ); \
	if ( !MusicFile[_id]) Log("Mix_LoadMUS: %s\n", Mix_GetError()); \
}
// - ------------------------------------------------------------------------------------------ - //
void musInit() {
	CurrentSong = -1;
	LastSong = -1;

	CurrentFade = 0.0f;
	TargetFade = 1.0f;
	FadeRate = 0.01f;
	
	ChangeTrack = false;
	
	Log( "Initializing SDL_mixer Music\n" );

/*
	Log( "- %i music deocoders available\n", Mix_GetNumMusicDecoders() );
	for( int idx = 0; idx < Mix_GetNumMusicDecoders(); idx++ ) {
		Log( "+ [%i] is for %s\n", idx, Mix_GetMusicDecoder(idx) );
	}
*/
	
	#include "MusicFiles.inc"
}
// - ------------------------------------------------------------------------------------------ - //
void musUpdate() {
	if ( MusicEnabled ) {
		if ( ChangeTrack ) {
			if ( CurrentFade > 0 ) {
				CurrentFade -= FadeRate;
			}
			else {
#ifdef USES_WEBOS
				PDL_NotifyMusicPlaying( PDL_TRUE );
#endif // USES_WEBOS //

				CurrentFade = 0;
				Log( "Is Playing Music: %i\n", Mix_PlayingMusic() );
				Mix_FadeInMusicPos(MusicFile[CurrentSong], -1, 0, 0);
				//Mix_PlayMusic(MusicFile[CurrentSong],-1);
				Log( "Playing Song %i (Cross Faded) [%i]\n", CurrentSong, Mix_GetMusicType(MusicFile[CurrentSong]) );
				Log( "Is Playing Music: %i\n", Mix_PlayingMusic() );
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
		
		Mix_VolumeMusic( (int)(CurrentFade * (float)MIX_MAX_VOLUME) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void musFree() {
	Mix_HaltMusic();

	for ( int idx = 0; idx < MUS_MAX; idx++ ) {
		Mix_FreeMusic( MusicFile[idx] );
	}

//	Mix_CloseAudio();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //
