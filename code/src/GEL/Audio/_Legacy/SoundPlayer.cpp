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
#include "SoundPlayer.h"
// - ------------------------------------------------------------------------------------------ - //
int sndSoundEnabled;
Mix_Chunk* SoundFile[SND_MAX];
// - ------------------------------------------------------------------------------------------ - //
void sndPlay( int SoundName ) {
	if ( sndSoundEnabled ) {
		Mix_PlayChannel( -1, SoundFile[SoundName], 0 );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#define sndLoad( _id, _s ) \
{ \
	char FilePath[2048]; \
	extern char AppBaseDir[]; \
	sprintf( FilePath, "%sSound/" _s ".wav", AppBaseDir ); \
	SoundFile[_id] = Mix_LoadWAV( FilePath ); \
}
// - ------------------------------------------------------------------------------------------ - //
void sndInit() {
	SDL_InitSubSystem( SDL_INIT_AUDIO );
	
#ifdef USES_SDL_MIXER
//	Mix_Init( MIX_INIT_OGG );
#else
	Mix_Init();
#endif // USES_SDL_MIXER //
	
#ifdef USES_WEBOS
#define SAMPLE_RATE 44100
#define BUFFER_SIZE (512*4)
#define CHANNELS 8
#else // USES_WEBOS //
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 2048
#define CHANNELS 8
#endif // USES_WEBOS //
	
	if ( Mix_OpenAudio( SAMPLE_RATE, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, BUFFER_SIZE ) < 0 ) {
		// Uhh... Audio failed //
		Log( "Error!  Sound Init Failed!\n" );
	}
	Mix_AllocateChannels( CHANNELS );
	

	#include "SoundFiles.inc"
}
// - ------------------------------------------------------------------------------------------ - //
void sndFree() {
	for ( int idx = 0; idx < SND_MAX; idx++ ) {
		// Do something //
		Mix_FreeChunk( SoundFile[idx] );
	}

	Mix_CloseAudio();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_IRRKLANG)
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <irrKlang.h>

#include "SoundPlayer.h"
// - ------------------------------------------------------------------------------------------ - //
int sndSoundEnabled;
extern irrklang::ISoundEngine* SoundEngine;
irrklang::ISoundEngine* SoundEngine;
irrklang::ISoundSource* SoundFile[SND_MAX];
// - ------------------------------------------------------------------------------------------ - //
void sndPlay( int SoundName ) {
	if ( sndSoundEnabled ) {
		SoundEngine->play2D( SoundFile[SoundName] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#define sndLoad( _id, _s ) \
{ \
	char FilePath[2048]; \
	extern char AppBaseDir[]; \
	sprintf( FilePath, "%sSound/" _s ".wav", AppBaseDir ); \
	SoundFile[_id] = SoundEngine->addSoundSourceFromFile( FilePath, irrklang::ESM_NO_STREAMING, true ); \
}
// - ------------------------------------------------------------------------------------------ - //
void sndInit() {
	SoundEngine = irrklang::createIrrKlangDevice();

	#include "SoundFiles.inc"
}
// - ------------------------------------------------------------------------------------------ - //
void sndFree() {
	SoundEngine->removeAllSoundSources();
	
//	for ( int idx = 0; idx < SND_MAX; idx++ ) {
//		SoundFile[idx]->drop();
//	}
	
	SoundEngine->drop();
}
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_BADA) 

#include "SoundPlayer.h"
#include <Audio/AudioMixer.h>
#include <Audio/WAVFile_Load.h>
#include <Debug/Log.h>

int sndSoundEnabled;
AudioMixer* MyMixer;
AudioSource* SoundFile[SND_MAX];

void sndPlay( int SoundName ) {
	if ( sndSoundEnabled ) {
		MyMixer->Play( SoundFile[SoundName] );
	}
}

#define sndLoad( _id, _s ) \
{ \
	char FilePath[2048]; \
	extern char AppBaseDir[]; \
	sprintf( FilePath, "%sSound/" _s ".wav", AppBaseDir ); \
	Log( "Loading %s\n", FilePath ); \
	SoundFile[_id] = Load_WAVFile( FilePath ); \
}

void sndInit() {
	MyMixer = new AudioMixer();
	
	#include "SoundFiles.inc"	
}

void sndUpdate() {
	MyMixer->UpdateBuffer();
	
	//writeAudio(WaveOut, MyMixer->ActiveBuffer, MyMixer->LengthInSamples * MyMixer->Info.SampleSize );
}

void sndFree() {
	for ( int idx = 0; idx < SND_MAX; idx++ ) {
		Free_WAVFile( SoundFile[idx] );
	}	
	
	delete MyMixer;
}

// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WINDOWSMOBILE)
// - ------------------------------------------------------------------------------------------ - //
// From scratch sound player/mixer via waveOut (like Windows) //
// - ------------------------------------------------------------------------------------------ - //
#include <windows.h>
#include <mmsystem.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Audio/AudioMixer.h>
//#include <Audio/AudioSource.h>
// - ------------------------------------------------------------------------------------------ - //
#include "SoundPlayer.h"
// - ------------------------------------------------------------------------------------------ - //

int sndSoundEnabled;
//HMIXER Mixer;
HWAVEOUT WaveOut;

#define BLOCK_SIZE (1024*2)//8192
#define BLOCK_COUNT 20

/* function prototypes */ 
static void CALLBACK waveOutProc(HWAVEOUT, UINT, DWORD, DWORD, DWORD);
static WAVEHDR* allocateBlocks(int size, int count);
static void freeBlocks(WAVEHDR* blockArray);
static void writeAudio(HWAVEOUT hWaveOut, LPSTR data, int size);

/* module level variables */
static CRITICAL_SECTION waveCriticalSection;
static WAVEHDR* waveBlocks;
static volatile int waveFreeBlockCount;
static int waveCurrentBlock;

static void CALLBACK waveOutProc( HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
    /* ignore calls that occur due to openining and closing the device. */
    if(uMsg != WOM_DONE)
    	return;
    	
	{
		/* pointer to free block counter */
		int* freeBlockCounter = (int*)dwInstance;
		
		
		EnterCriticalSection(&waveCriticalSection);
		(*freeBlockCounter)++;
		LeaveCriticalSection(&waveCriticalSection);
	}
}

WAVEHDR* allocateBlocks(int size, int count)
{
    unsigned char* buffer;
    int i;
    WAVEHDR* blocks;
    DWORD totalBufferSize = (size + sizeof(WAVEHDR)) * count;
    /* allocate memory for the entire set in one go */
    if ( (buffer = (unsigned char*)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, totalBufferSize)) == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        ExitProcess(1);
    }

    /* and set up the pointers to each bit */
    blocks = (WAVEHDR*)buffer;
    buffer += sizeof(WAVEHDR) * count;


	for(i = 0; i < count; i++) {
        blocks[i].dwBufferLength = size;
        blocks[i].lpData = (LPSTR)buffer;
        buffer += size;
    }

    return blocks;
}

void freeBlocks(WAVEHDR* blockArray)
{
    /* and this is why allocateBlocks works the way it does */ 
    HeapFree(GetProcessHeap(), 0, blockArray);
}

void writeAudio(HWAVEOUT hWaveOut, LPSTR data, int size)
{
    WAVEHDR* current;
    int remain;
    current = &waveBlocks[waveCurrentBlock];


	while(size > 0) {
        /* first make sure the header we're going to use is unprepared */
        if(current->dwFlags & WHDR_PREPARED) 
        	waveOutUnprepareHeader(hWaveOut, current, sizeof(WAVEHDR));

		if(size < (int)(BLOCK_SIZE - current->dwUser)) {
            memcpy(current->lpData + current->dwUser, data, size);
            current->dwUser += size;
            break;
        }

        remain = BLOCK_SIZE - current->dwUser;

        memcpy(current->lpData + current->dwUser, data, remain);
        size -= remain;
        data += remain;
        current->dwBufferLength = BLOCK_SIZE;
        waveOutPrepareHeader(hWaveOut, current, sizeof(WAVEHDR));
        waveOutWrite(hWaveOut, current, sizeof(WAVEHDR));
        
        EnterCriticalSection(&waveCriticalSection);
        waveFreeBlockCount--;
        LeaveCriticalSection(&waveCriticalSection);
        
        /* wait for a block to become free */
        while(!waveFreeBlockCount)
        	Sleep(10);
        
        /* point to the next block */
        waveCurrentBlock++;
        waveCurrentBlock %= BLOCK_COUNT;
        current = &waveBlocks[waveCurrentBlock];
        current->dwUser = 0;
    }
}

#include <Audio/WAVFile_Load.h>

AudioMixer* MyMixer;
AudioSource* SoundFile[SND_MAX];

HANDLE SoundThreadHandle;

DWORD WINAPI sndThread( LPVOID lpParameter ) {
	while(1) {
		if ( waveFreeBlockCount > 17 ) {
			for ( int idx = 0; idx < 1; idx++ ) {
				MyMixer->UpdateBuffer();
				writeAudio(WaveOut, MyMixer->ActiveBuffer, MyMixer->LengthInSamples * MyMixer->Info.SampleSize );
			}
		}
		Sleep( 20 );
	}
	return 0;
}


void sndPlay( int SoundName ) {
	if ( sndSoundEnabled )
	{
		MyMixer->Play( SoundFile[SoundName] );
	}
}

extern char ApplicationPath[_MAX_PATH+1];
		
#define sndLoad( _id, _s ) \
{ \
	char Path[_MAX_PATH+1]; \
	sprintf( Path, "%s\\Sound\\" _s ".wav", ApplicationPath ); \
	\
	SoundFile[_id] = Load_WAVFile( Path ); \
}

//	SoundFile[_id] = Load_WAVFile( "Program Files\\Smiles\\Sound\\" _s ".wav" );


void sndInit() {
	wLog( L"+ %i \"waveOut\" sound device(s) available.\n", waveOutGetNumDevs() );
	wLog( L"+ %i \"mixer\" sound device(s) available.\n", mixerGetNumDevs() );
	//mixerOpen( &Mixer, 


    /* initialise the module variables */ 
    waveBlocks = allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
    waveFreeBlockCount = BLOCK_COUNT;
    waveCurrentBlock= 0;
    InitializeCriticalSection(&waveCriticalSection);


	MyMixer = new AudioMixer();

/*
	WAVEFORMATEX WaveFormat = {
		WAVE_FORMAT_PCM, // Stream Format //
		2, // Stereo //
		44100, // Sample Rate //
		44100*2*2, // Bytes per Second //
		2*2, // Block Size (Bytes Per * Channels) //
		16, // Bits Per Sample //
		0 // Extra Info Size //
	};
*/

	// NOTE: Data written to the buffer MUST be exactly the same, otherwise it wont work //
	WAVEFORMATEX WaveFormat = {
		WAVE_FORMAT_PCM, // Stream Format //
		1, // Mono //
		44100, // Sample Rate //
		44100*2, // Bytes per Second //
		2, // Block Size (Bytes Per * Channels) //
		16, // Bits Per Sample //
		0 // Extra Info Size //
	};

//	Log( "- Initializing waveOut Interface...\n" );
//	if ( waveOutOpen( &WaveOut, WAVE_MAPPER, &WaveFormat, 0, 0, CALLBACK_NULL ) != MMSYSERR_NOERROR ) {
//		Log( "* Audio Error\n" );
//	}
//	else {
//		Log( "+ Success: waveOut available\n" );
//	}
	
	Log( "- Initializing waveOut Interface...\n" );
	if ( waveOutOpen( &WaveOut, WAVE_MAPPER, &WaveFormat, (DWORD_PTR)waveOutProc, (DWORD_PTR)&waveFreeBlockCount, CALLBACK_FUNCTION ) != MMSYSERR_NOERROR ) {
		Log( "* Audio Error\n" );
	}
	else {
		Log( "+ Success: waveOut available\n" );
	}
	
	#include "SoundFiles.inc"	

	
	SoundThreadHandle = CreateThread( NULL, NULL, &sndThread, 0, 0, NULL/*&SoundThreadID*/ );
	SetThreadPriority( SoundThreadHandle, THREAD_PRIORITY_TIME_CRITICAL );
}

void sndUpdate() {
	MyMixer->UpdateBuffer();
	
	writeAudio(WaveOut, MyMixer->ActiveBuffer, MyMixer->LengthInSamples * MyMixer->Info.SampleSize );
}

void sndFree() {
	TerminateThread( SoundThreadHandle, 0 );
	CloseHandle( SoundThreadHandle );
	
	for ( int idx = 0; idx < SND_MAX; idx++ ) {
		Free_WAVFile( SoundFile[idx] );
	}	
	
	Log( "- Shutting Down waveOut...\n" );
	if ( waveOutClose( WaveOut ) != MMSYSERR_NOERROR ) {
		Log( "* Audio Error\n" );
	}
	else {
		Log( "+ Success: waveOut shut down\n" );
	}

	delete MyMixer;

	
    for(int i = 0; i < waveFreeBlockCount; i++) 
		if (waveBlocks[i].dwFlags & WHDR_PREPARED)
    		waveOutUnprepareHeader(WaveOut, &waveBlocks[i], sizeof(WAVEHDR));
    DeleteCriticalSection(&waveCriticalSection);
    freeBlocks(waveBlocks);
}

/*/
// - ------------------------------------------------------------------------------------------ - //
// PlaySound Version (1 sound at a time)
// - ------------------------------------------------------------------------------------------ - //
#include <windows.h>
#include <soundfile.h>
#include "SoundPlayer.h"

int sndSoundEnabled;

#define sndLoad( _id, _s ) \
	L"Program Files\\Smiles\\" L ## _s L".wav",

const wchar_t* SoundFile[SND_MAX] = {
	#include "SoundFiles.inc"
};

void sndPlay( int SoundName ) {
	PlaySound( SoundFile[SoundName], 0, SND_FILENAME | SND_ASYNC );
}
void sndInit() {
}
void sndFree() {
}

// - ------------------------------------------------------------------------------------------ - //
// SndPlayer Version //
// - ------------------------------------------------------------------------------------------ - //
#include <windows.h>
#include <soundfile.h>
#include "SoundPlayer.h"
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
int sndSoundEnabled;
HSOUND SoundFile[SND_MAX];
// - ------------------------------------------------------------------------------------------ - //
void sndPlay( int SoundName ) {
	//if ( sndSoundEnabled )
	{
		wLog( L"+ Playing Sound %i...\n", SoundName );
		if ( SndPlayAsync( SoundFile[SoundName], 0) ) {
			wLog( L"* ERROR PLAY SOUND!\n" );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#define sndLoad( _id, _s ) \
	{ \
		const char* File = "Program Files\\Smiles\\" _s ".wav"; \
		wchar_t wFile[2000]; \
		MultiByteToWideChar( CP_UTF8, 0, File, -1, wFile, 2000 ); \
		wLog( L"+ Loading Sound \"%s\"...\n", wFile );\
		if ( SndOpen( wFile, &SoundFile[_id] ) ) \
			wLog( L"* ERROR OPENING FILE!\n" ); \
		else \
			wLog( L"+ Success!\n" ); \
	}
//	SndOpen( "Sound/" _s ".wav", SoundFile[_id] )
// - ------------------------------------------------------------------------------------------ - //
void sndInit() {
	#include "SoundFiles.inc"
}
// - ------------------------------------------------------------------------------------------ - //
void sndFree() {
	for ( int idx = 0; idx < SND_MAX; idx++ ) {
		SndClose( SoundFile[idx] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
/*/
// - ------------------------------------------------------------------------------------------ - //
#else // No engine available //
// - ------------------------------------------------------------------------------------------ - //
#include "SoundPlayer.h"

int sndSoundEnabled;

void sndPlay( int SoundName ) {
}

void sndInit() {
}

void sndFree() {
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Sound engines //
// - ------------------------------------------------------------------------------------------ - //
