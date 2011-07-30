// - ------------------------------------------------------------------------------------------ - //
#ifndef __SoundPlayer_H__
#define __SoundPlayer_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWSMOBILE
#if defined(PRODUCT_SMILESZEN)
enum {
	SND_MENU_CLICK = 0,
	SND_MENU_NEXT,
	SND_MENU_PREV,
	SND_PAUSE,
	SND_RESUME,
	SND_UNDO,
	SND_SWAP,
	SND_TOGGLE,
	SND_TWIST,
	SND_ZEN_MINUS,
	SND_ZEN_SAME,
	SND_ZEN_PLUS,
	SND_ZEN_PLUSPLUS,
	SND_ZEN_WIN,
	SND_ACHIEVEMENT,
	
	SND_MAX
};
#elif defined(PRODUCT_SMILESDROP)
enum {
	SND_MENU_CLICK = 0,
	SND_MENU_NEXT,
	SND_MENU_PREV,
	SND_PAUSE,
	SND_RESUME,
	SND_SWAP,
	SND_TOGGLE,
	SND_ICEBREAK,
	SND_ROCKBREAK,
	SND_LEVELUP,
	SND_TWIST,
	SND_TONYHAWK,
	SND_DROP_WIN,
	SND_ACHIEVEMENT,
	
	SND_TONE01,
	SND_TONE02,
	SND_TONE03,
	SND_TONE04,
	SND_TONE05,
	SND_TONE06,
	SND_TONE07,
	SND_TONE08,
	SND_TONE09,
	SND_TONE10,
	SND_TONE11,
	SND_TONE12,
	SND_TONE13,
	SND_TONE14,
	SND_TONE15,
	SND_TONE16,
	SND_TONE17,
	SND_TONE18,
	SND_TONE19,
	SND_TONE20,
	SND_TONE21,
	SND_TONE22,
	SND_TONE23,
	SND_TONE24,
	SND_TONE25,
	SND_TONE26,
	SND_TONE27,
	SND_TONE28,
	SND_TONE29,
	SND_TONE30,
	SND_TONE31,
	
	SND_MAX
};
#else // PRODUCT_SMILES //
enum {
	SND_MENU_CLICK = 0,
	SND_MENU_NEXT,
	SND_MENU_PREV,
	SND_PAUSE,
	SND_RESUME,
	SND_UNDO,
	SND_SWAP,
	SND_TOGGLE,
	SND_ICEBREAK,
	SND_ROCKBREAK,
	SND_LEVELUP,
	SND_TWIST,
	SND_TONYHAWK,
	SND_ZEN_MINUS,
	SND_ZEN_SAME,
	SND_ZEN_PLUS,
	SND_ZEN_PLUSPLUS,
	SND_ZEN_WIN,
	SND_DROP_WIN,
	SND_ACHIEVEMENT,
	
	SND_TONE01,
	SND_TONE02,
	SND_TONE03,
	SND_TONE04,
	SND_TONE05,
	SND_TONE06,
	SND_TONE07,
	SND_TONE08,
	SND_TONE09,
	SND_TONE10,
	SND_TONE11,
	SND_TONE12,
	SND_TONE13,
	SND_TONE14,
	SND_TONE15,
	SND_TONE16,
	SND_TONE17,
	SND_TONE18,
	SND_TONE19,
	SND_TONE20,
	SND_TONE21,
	SND_TONE22,
	SND_TONE23,
	SND_TONE24,
	SND_TONE25,
	SND_TONE26,
	SND_TONE27,
	SND_TONE28,
	SND_TONE29,
	SND_TONE30,
	SND_TONE31,
	
	SND_MAX
};
#endif // PRODUCT //
#else // !USES_WINDOWSMOBILE //
enum {
	SND_MENU_CLICK = 0,
	SND_MENU_NEXT,
	SND_MENU_PREV,
	SND_PAUSE,
	SND_RESUME,
	SND_UNDO,
	SND_SWAP,
	SND_TOGGLE,
	SND_ICEBREAK,
	SND_ROCKBREAK,
	SND_LEVELUP,
	SND_TWIST,
	SND_TONYHAWK,
	SND_ZEN_MINUS,
	SND_ZEN_SAME,
	SND_ZEN_PLUS,
	SND_ZEN_PLUSPLUS,
	SND_ZEN_WIN,
	SND_DROP_WIN,
	SND_ACHIEVEMENT,
	SND_WOOHOO,
	SND_AWW,
	
	SND_TONE01,
	SND_TONE02,
	SND_TONE03,
	SND_TONE04,
	SND_TONE05,
	SND_TONE06,
	SND_TONE07,
	SND_TONE08,
	SND_TONE09,
	SND_TONE10,
	SND_TONE11,
	SND_TONE12,
	SND_TONE13,
	SND_TONE14,
	SND_TONE15,
	SND_TONE16,
	SND_TONE17,
	SND_TONE18,
	SND_TONE19,
	SND_TONE20,
	SND_TONE21,
	SND_TONE22,
	SND_TONE23,
	SND_TONE24,
	SND_TONE25,
	SND_TONE26,
	SND_TONE27,
	SND_TONE28,
	SND_TONE29,
	SND_TONE30,
	SND_TONE31,
	
	
	SND_MAX
};
#endif // USES_WINDOWSMOBILE //
// - ------------------------------------------------------------------------------------------ - //
extern int sndSoundEnabled;
void sndPlay( int SoundName );
// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_IOS
void sndInit();
void sndUpdate();
void sndFree();
#endif // USES_IOS // 
// - ------------------------------------------------------------------------------------------ - //
#endif // __SoundPlayer_H__ //
// - ------------------------------------------------------------------------------------------ - //
