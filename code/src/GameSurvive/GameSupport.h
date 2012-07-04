// - ------------------------------------------------------------------------------------------ - //
#ifndef __GameSupport_H__
#define __GameSupport_H__
// - ------------------------------------------------------------------------------------------ - //
#include "UI/UIHost.h"
// - ------------------------------------------------------------------------------------------ - //
class cGameSupport {
	static cGameSupport* CurrentInstance;
public:
	static cGameSupport* Current() {
		return CurrentInstance;
	}

public:
	cGameSupport();
	~cGameSupport();
	
	void Step();
	void Draw();

public:
	// General //
	float CurrentAngle;

public:	
	// Mouse Cursor //
	cUIHost MouseCursor;
	bool MouseVisible;
		
	int CursorTimeout;
	bool HasDetectedMotion;
	
	void MouseInit();
	void MouseExit();
	void MouseStep();
	void MouseDraw();
	
	void MouseEventMove();
	void MouseEventButtonUp();
	void MouseEventButtonDown();
	void MouseEventWindowFocus( const bool Focus );

public:
	// Focus Lost Image //
	cUIHost LostFocusImage;
	bool LostFocus;
	
	void LostFocusInit();
	void LostFocusExit();
	void LostFocusStep();
	void LostFocusDraw();
	
	void LostFocusEvent( const bool Focus );

public:
	// Fade In/Out //
	GelColor FadeColor;
	float CurrentFade;

	void FadeInit();
	void FadeExit();
	void FadeStep();
	void FadeDraw();
	
	void FadeSetColor( const GelColor Color );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GameSupport_H__ //
// - ------------------------------------------------------------------------------------------ - //
