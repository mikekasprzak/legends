// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_MULTITOUCH) && defined(USES_WINDOWS)
// - ------------------------------------------------------------------------------------------ - //
#include "Input_MultiTouch_Windows.h"
// - ------------------------------------------------------------------------------------------ - //
// Code borrowed from Osmos //
// - ------------------------------------------------------------------------------------------ - //
// TODO: Put this in its own header (in Osmos, it's in a file WinHeaders.h)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// - ------------------------------------------------------------------------------------------ - //
typedef BOOL (WINAPI *pRTW)	(HWND, ULONG);								// RegisterTouchWindow
typedef BOOL (WINAPI *pGTII)(HTOUCHINPUT, UINT, PTOUCHINPUT, int);		// GetTouchInputInfo
typedef BOOL (WINAPI *pCTIH)(HTOUCHINPUT);								// CloseTouchInputHandle
typedef BOOL (WINAPI *pSGC)	(HWND, DWORD, UINT, PGESTURECONFIG, UINT);	// SetGestureConfig
typedef BOOL (WINAPI *pGGI)	(HGESTUREINFO, PGESTUREINFO);				// GetGestureInfo
typedef BOOL (WINAPI *pCGIH)(HGESTUREINFO);								// CloseGestureInfoHandle
// - ------------------------------------------------------------------------------------------ - //

// The Osmos code detects common gestures, so you'll want to gut that stuff

/*
class IWinTouchAPI
{
public:
	pRTW	pRegisterTouchWindow;
	pGTII	pGetTouchInputInfo;
	pCTIH	pCloseTouchInputHandle;
	pSGC	pSetGestureConfig;
	pGGI	pGetGestureInfo;
	pCGIH	pCloseGestureInfoHandle;

	IWinTouchAPI()
		: pRegisterTouchWindow( NULL )
		, pGetTouchInputInfo( NULL )
		, pCloseTouchInputHandle( NULL )
		, pSetGestureConfig( NULL )
		, pGetGestureInfo( NULL )
		, pCloseGestureInfoHandle( NULL )
	{}
};

// Returns pointers to the touch API interface, or NULL if the interface isn't supported.
static IWinTouchAPI* InitWinTouchAPI()
{
	// Look up the touch DLL.
	HMODULE TouchDLL = GetModuleHandle( TEXT("user32.dll") );
	if ( !TouchDLL )
		return NULL;

	// Look up the touch interfaces we need, aborting if one is missing.
	pRTW pRegisterTouchWindow = (pRTW) GetProcAddress( TouchDLL, "RegisterTouchWindow" );
	if ( !pRegisterTouchWindow )
		return NULL;

	pGTII pGetTouchInputInfo = (pGTII) GetProcAddress( TouchDLL, "GetTouchInputInfo" );
	if ( !pGetTouchInputInfo )
		return NULL;

	pCTIH pCloseTouchInputHandle = (pCTIH) GetProcAddress( TouchDLL, "CloseTouchInputHandle" );
	if ( !pCloseTouchInputHandle )
		return NULL;

	pSGC pSetGestureConfig = (pSGC) GetProcAddress( TouchDLL, "SetGestureConfig" );
	if ( !pSetGestureConfig )
		return NULL;

	pGGI pGetGestureInfo = (pGGI) GetProcAddress( TouchDLL, "GetGestureInfo" );
	if ( !pGetGestureInfo )
		return NULL;

	pCGIH pCloseGestureInfoHandle = (pCGIH) GetProcAddress( TouchDLL, "CloseGestureInfoHandle" );
	if ( !pCloseGestureInfoHandle )
		return NULL;

	// All touch interfaces 
	static IWinTouchAPI API;
	API.pRegisterTouchWindow = pRegisterTouchWindow;
	API.pGetTouchInputInfo = pGetTouchInputInfo;
	API.pCloseTouchInputHandle = pCloseTouchInputHandle;
	API.pSetGestureConfig = pSetGestureConfig;
	API.pGetGestureInfo = pGetGestureInfo;
	API.pCloseGestureInfoHandle = pCloseGestureInfoHandle;
	return &API;
}

// Returns a pointer to an API appropriate for this system.
IMultiTouch* GetMultiTouchAPI()
{
	static IMultiTouch* SMultiTouchAPI = NULL;
	if ( !SMultiTouchAPI )
	{
		// Check the OS and see if the touch API is supported.
		static IWinTouchAPI* OSTouchAPI = InitWinTouchAPI();
		if ( OSTouchAPI )
		{
			// It is!  Create a Win7 API.
			static IMultiTouch_Win7 SWin7API( OSTouchAPI );
			SMultiTouchAPI = &SWin7API;
		}
		else
		{
			// No OS support; return a null API.
			static IMultiTouch_Null SNullAPI;
			SMultiTouchAPI = &SNullAPI;
		}
	}
	Assert( SMultiTouchAPI );
	return SMultiTouchAPI;
}

#define LODWORD(ull) ((DWORD)((ULONGLONG)(ull) & 0x00000000ffffffff))

static POINT _ptFirst;        // first significant point of the gesture
static POINT _ptSecond;       // second significant point of the gesture
static DWORD _dwArguments;    // 4 bytes long argument

// Main function of this class decodes gesture information in:
//      hWnd        window handle
//      wParam      message parameter (message-specific)
//      lParam      message parameter (message-specific)
static LRESULT GestureWndProc(HWND hWnd, WPARAM, LPARAM lParam, IWinTouchAPI* InAPI)
{
    // helper variables
    POINT ptZoomCenter;
    double k;

    GESTUREINFO gi;
    gi.cbSize = sizeof(gi);
    BOOL bResult = InAPI->pGetGestureInfo((HGESTUREINFO)lParam, &gi);

    if (!bResult)
    {
        LogErr(TEXT("Error in execution of GetGestureInfo"));
        return FALSE;
    }

    switch (gi.dwID)
    {
    case GID_BEGIN:
        break;

    case GID_END:
        break;
    
    case GID_ZOOM:
        switch (gi.dwFlags)
        {
        case GF_BEGIN:
            _dwArguments = LODWORD(gi.ullArguments);
            _ptFirst.x = gi.ptsLocation.x;
            _ptFirst.y = gi.ptsLocation.y;
            ScreenToClient(hWnd,&_ptFirst);
			//Log(TEXT("ZOOM BEGIN: x = %d, y = %d"), _ptFirst.x, _ptFirst.y);
            break;

        default:
            // We read here the second point of the gesture. This is middle point between fingers in this new position.
            _ptSecond.x = gi.ptsLocation.x;
            _ptSecond.y = gi.ptsLocation.y;
            ScreenToClient(hWnd,&_ptSecond);
			//Log(TEXT("ZOOM default: (%d, %d) to (%d, %d), %d to %d"), _ptFirst.x, _ptFirst.y, _ptSecond.x, _ptSecond.y, _dwArguments, LODWORD(gi.ullArguments));

            // We have to calculate zoom center point 
            ptZoomCenter.x = (_ptFirst.x + _ptSecond.x)/2;
            ptZoomCenter.y = (_ptFirst.y + _ptSecond.y)/2;           
            
            // The zoom factor is the ratio between the new and the old distance.
            // The new distance between two fingers is stored in gi.ullArguments 
            // (lower DWORD) and the old distance is stored in _dwArguments.
            k = (double)(LODWORD(gi.ullArguments))/(double)(_dwArguments);
			//k = 1.f/k; // to invert zoom
			const float maxk = 1.3f;
			const float invmaxk = 1.f/maxk;
			if (k > maxk)
				k = maxk;
			else if (k < invmaxk)
				k = invmaxk;
			//Log(TEXT("k = %f"), k);

			Char zoomCommand[50]; App_sprintf_s(zoomCommand, 50, TEXT("zoomRatio %f\n"), k);
			GCmdController->EnqueueText( zoomCommand, -1 );

            // Now we have to store new information as a starting information for the next step in this gesture.
            _ptFirst = _ptSecond;
            _dwArguments = LODWORD(gi.ullArguments);
            break;
        }
        break;
    
    case GID_PAN:
        switch (gi.dwFlags)
        {
        case GF_BEGIN:
            _ptFirst.x = gi.ptsLocation.x;
            _ptFirst.y = gi.ptsLocation.y;
            ScreenToClient(hWnd, &_ptFirst);
			//MouseMove( _ptFirst.x, _ptFirst.y );
            break;

        default:
            // We read the second point of this gesture. It is a middle point between fingers in this new position
            _ptSecond.x = gi.ptsLocation.x;
            _ptSecond.y = gi.ptsLocation.y;
            ScreenToClient(hWnd, &_ptSecond);
			//MouseMove( _ptSecond.x, _ptSecond.y );

            // We have to copy second point into first one to prepare for the next step of this gesture.
            _ptFirst = _ptSecond;
            break;
        }
        break;

    case GID_ROTATE:
		{
			static float accumulatedRotation = 0;
			const  float rotationToStep = 0.2f;

			switch (gi.dwFlags)
			{
			case GF_BEGIN:
				_dwArguments = 0;
				accumulatedRotation = 0;
				break;

			default:
				_ptFirst.x = gi.ptsLocation.x;
				_ptFirst.y = gi.ptsLocation.y;
				ScreenToClient(hWnd, &_ptFirst);

				// Gesture handler returns cumulative rotation angle. However we want the delta angle
				float angle = -(float)(GID_ROTATE_ANGLE_FROM_ARGUMENT(LODWORD(gi.ullArguments)) - GID_ROTATE_ANGLE_FROM_ARGUMENT(_dwArguments));
				//Log(TEXT("angle = %f"), angle);

				if (fabs(angle) < 2.f) // janky gesture recognition often gives PI or thereabouts, which is garbage
				{
					accumulatedRotation += angle;
					int steps = (int)(accumulatedRotation / rotationToStep);

					if (steps != 0)
					{
						Char timeCommand[50]; App_sprintf_s(timeCommand, 50, TEXT("timeDilation %d\n"), steps);
						GCmdController->EnqueueText( timeCommand, -1 );
						accumulatedRotation -= steps * rotationToStep;
					}
				}

				_dwArguments = LODWORD(gi.ullArguments);
				break;
			}
		}
        break;

    case GID_TWOFINGERTAP:
		KeyDown( K_SPACE, true );
		KeyUp  ( K_SPACE );
        break;

    case GID_PRESSANDTAP:
        switch (gi.dwFlags)
        {
        case GF_BEGIN:
			//if ( !MouseDown() )
			//{
			//	CKeys::KeyEvent( K_MOUSE1, true );
			//}
            break;
        }
        break;
    }

    InAPI->pCloseGestureInfoHandle((HGESTUREINFO)lParam);

    return TRUE;
}

// Extracts contact point in client area coordinates (pixels) from a TOUCHINPUT
// structure. TOUCHINPUT structure uses 100th of a pixel units.
// in:
//      hWnd        window handle
//      ti          TOUCHINPUT structure (info about contact)
// returns:
//      POINT with contact coordinates
POINT GetTouchPoint(HWND hWnd, const TOUCHINPUT& ti)
{
    POINT pt;
    pt.x = ti.x / 100;
    pt.y = ti.y / 100;
    ScreenToClient(hWnd, &pt);
    return pt;
}

// Extracts contact ID from a TOUCHINPUT structure.
// in:
//      ti          TOUCHINPUT structure (info about contact)
// returns:
//      ID assigned to the contact
inline int GetTouchContactID(const TOUCHINPUT& ti)
{
    return ti.dwID;
}

///////////////////////////////////////////////////////////////////////////////
// WM_TOUCH message handlers

// Handler for touch-down message.
// Starts a new stroke and assigns a color to it.
// in:
//      hWnd        window handle
//      ti          TOUCHINPUT structure (info about contact)
static void OnTouchDownHandler(HWND hWnd, const TOUCHINPUT& ti)
{
    // Extract contact info: point of contact and ID
    POINT pt = GetTouchPoint(hWnd, ti);
    int iCursorId = GetTouchContactID(ti);

	//Log(TEXT("Touch Down, id = %d, (%d, %d)"), iCursorId, pt.x, pt.y);

    // We have just started a new stroke, which must have an ID value unique
    // among all the strokes currently being drawn. Check if there is a stroke
    // with the same ID in the  collection of the strokes in drawing.
    ASSERT(g_StrkColDrawing.FindStrokeById(iCursorId) == -1);

	// new touchdown should remove all complete touches, and reset the history of all active ones
	g_StrkColFinished.Clear();
	for (int i=0; i<g_StrkColDrawing.Count(); i++)
		g_StrkColDrawing[i]->ClearHistory();

    // Create new stroke, add point
    CStroke* pStrkNew = new CStroke;
    pStrkNew->AddPoint(pt);
    pStrkNew->SetId(iCursorId);

    // Add new stroke to the collection of strokes in drawing.
    g_StrkColDrawing.Add(pStrkNew);
}

static int pan1accum = 0;
static int pan2accum = 0;

// Handler for touch-move message.
// Adds a point to the stroke in drawing and draws new stroke segment.
// in:
//      hWnd        window handle
//      ti          TOUCHINPUT structure (info about contact)
static void OnTouchMoveHandler(HWND hWnd, const TOUCHINPUT& ti)
{
    // Extract contact info: contact ID
    int iCursorId = GetTouchContactID(ti);

    // Find the stroke in the collection of the strokes in drawing.
    int iStrk = g_StrkColDrawing.FindStrokeById(iCursorId);

	Assert((iStrk >= 0) && (iStrk < g_StrkColDrawing.Count()));
	CStroke& curStroke = *g_StrkColDrawing[iStrk];

    // Extract contact info: contact point
    POINT pt;
    pt = GetTouchPoint(hWnd, ti);

    // Add contact point to the stroke
    g_StrkColDrawing[iStrk]->AddPoint(pt);

	switch (gestureState)
	{
	case GS_INDETERMINATE:
		// is this a pan/zoom/rotate?
		if (g_StrkColDrawing.Count() >= 2 )
		{
			CStroke& stroke1 = *g_StrkColDrawing[0];
			CStroke& stroke2 = *g_StrkColDrawing[1];
			if (stroke1.Count() >= 2 && stroke2.Count() >= 2)
			{
				POINT dp1 = stroke1.GetTotalMovement();
				POINT dp2 = stroke2.GetTotalMovement();
				//Log(TEXT("INDET MOVE: dp1 (%d, %d), dp2 (%d, %d)"), dp1.x, dp1.y, dp2.x, dp2.y);
				long ad1x = abs(dp1.x);
				long ad1y = abs(dp1.y);
				long ad2x = abs(dp2.x);
				long ad2y = abs(dp2.y);

				long d12x1 = (stroke2[0].x - stroke1[0].x);
				long d12y1 = (stroke2[0].y - stroke1[0].y);
				long d12x2 = (stroke2[stroke2.Count()-1].x - stroke1[stroke1.Count()-1].x);
				long d12y2 = (stroke2[stroke2.Count()-1].y - stroke1[stroke1.Count()-1].y);
				long d1sqr = (d12x1 * d12x1) + (d12y1 * d12y1);
				long d2sqr = (d12x2 * d12x2) + (d12y2 * d12y2);
				float d1 = sqrt(float(d1sqr));
				float d2 = sqrt(float(d2sqr));
				float pinch = fabs(d2 - d1);
				//Log(TEXT("d1 = %f, d2 = %f"), d1, d2);

				if (pinch > criticalLength)
				{
					gestureState = GS_ZOOM;
					//bJustSwitchedToZoomState = true;
				}
			}
		} // 2 strokes or more
		if ( g_StrkColDrawing.Count() == 1 ) // one finger pan?
		{
			CStroke& stroke1 = *g_StrkColDrawing[0];

			POINT dp1 = stroke1.GetTotalMovement();
			long ad1x = abs(dp1.x);
			long ad1y = abs(dp1.y);
			if (ad1x > criticalLength &&
				float(ad1y)/float(ad1x) < diagonalRatio)
			{
				gestureState = GS_PAN_SMOOTH;
			}

			//CCounter dt; dt = stroke1.GetLastTime() - stroke1.GetStartTime();			
			//if (dt.GetSecs() >= flickTime)
			//{
			//	POINT dp1 = stroke1.GetTotalMovement();
			//	long ad1x = abs(dp1.x);
			//	long ad1y = abs(dp1.y);
			//	if (ad1x > criticalLength &&
			//		float(ad1y)/float(ad1x) < diagonalRatio)
			//	{
			//		gestureState = GS_PAN_ONE;
			//	}
			//}
		}
		break;
	case GS_PAN: // two-finger pan (currently disabled)
		{
			if (&curStroke == g_StrkColDrawing[0])
				pan1accum += curStroke.GetLastMovement().x;
			else if (&curStroke == g_StrkColDrawing[1])
				pan2accum += curStroke.GetLastMovement().x;

			Char smoothTimeDilationCommand[50];
			if (pan1accum > 0 && pan2accum > 0)
			{
				int accum = min(pan1accum, pan2accum);
				App_sprintf_s(smoothTimeDilationCommand, 50, TEXT("smoothTimeDilation %f\n"), pow(1.0035f, accum));
				GCmdController->EnqueueText( smoothTimeDilationCommand, -1 );
				pan1accum -= accum;
				pan2accum -= accum;
			}
			else if (pan1accum < 0 && pan2accum < 0)
			{
				int accum = max(pan1accum, pan2accum);
				App_sprintf_s(smoothTimeDilationCommand, 50, TEXT("smoothTimeDilation %f\n"), pow(1.f/1.0035f, -accum));
				GCmdController->EnqueueText( smoothTimeDilationCommand, -1 );
				pan1accum -= accum;
				pan2accum -= accum;
			}
		}
		break;
	case GS_ZOOM:
		{
			if ( g_StrkColDrawing.Count() >= 2 )
			{
				CStroke& stroke1 = *g_StrkColDrawing[0];
				CStroke& stroke2 = *g_StrkColDrawing[1];

				if (stroke1.Count() >= 2 && stroke2.Count() >= 2)
				{
					long d12x1 = (stroke2[stroke2.Count()-2].x - stroke1[stroke1.Count()-2].x);
					long d12y1 = (stroke2[stroke2.Count()-2].y - stroke1[stroke1.Count()-2].y);
					long d12x2 = (stroke2[stroke2.Count()-1].x - stroke1[stroke1.Count()-1].x);
					long d12y2 = (stroke2[stroke2.Count()-1].y - stroke1[stroke1.Count()-1].y);

					if (bJustSwitchedToZoomState)
					{
						d12x1 = (stroke2[0].x - stroke1[0].x);
						d12y1 = (stroke2[0].y - stroke1[0].y);
					}

					long d1sqr = (d12x1 * d12x1) + (d12y1 * d12y1);
					long d2sqr = (d12x2 * d12x2) + (d12y2 * d12y2);
					float d1 = sqrt(float(d1sqr));
					float d2 = sqrt(float(d2sqr));
					//Log(TEXT("d1 = %f, d2 = %f"), d1, d2);

					//float pinch = fabs(d2/d1);
					//float k = pinch;
					//const float maxk = 1.3f;
					//const float invmaxk = 1.f/maxk;
					//if (k > maxk)
					//	k = maxk;
					//else if (k < invmaxk)
					//	k = invmaxk;
					//Log(TEXT("k = %f"), k);

					float pinch = d2 - d1;
					float k = pow(1.002f, pinch);

					Char zoomCommand[50]; App_sprintf_s(zoomCommand, 50, TEXT("zoomRatio %f\n"), k);
					GCmdController->EnqueueText( zoomCommand, -1 );
				}
			}
			else
			{
				int i = 3;
				i++;
			}
			bJustSwitchedToZoomState = false;
		}
		break;
	case GS_PAN_ONE: // one-finger pan (currently disabled)
		{
			if (&curStroke == g_StrkColDrawing[0])
				pan1accum += curStroke.GetLastMovement().x;
			Char smoothTimeDilationCommand[50];
			if (pan1accum > 0)
			{
				App_sprintf_s(smoothTimeDilationCommand, 50, TEXT("smoothTimeDilation %f\n"), pow(1.003f, pan1accum));
				GCmdController->EnqueueText( smoothTimeDilationCommand, -1 );
			}
			if (pan1accum < 0)
			{
				App_sprintf_s(smoothTimeDilationCommand, 50, TEXT("smoothTimeDilation %f\n"), pow(1.f/1.003f, -pan1accum));
				GCmdController->EnqueueText( smoothTimeDilationCommand, -1 );
			}
			pan1accum = 0;
		}
		break;
	case GS_PAN_SMOOTH: // one-finger pan with flick potential
		{
			if (&curStroke == g_StrkColDrawing[0])
				pan1accum += curStroke.GetLastMovement().x;

			// first bit-of-time on pan should be lower sensitivity (to mitigate shooting past flick target)
			float sensitivity = 1.0035f;
			float dt = (float)(curStroke.GetLastTime() - curStroke.GetStartTime()).GetSecs();
			if (dt < flickTime)
				sensitivity = 1.0015f;

			Char smoothTimeDilationCommand[50];
			if (pan1accum > 0)
			{
				App_sprintf_s(smoothTimeDilationCommand, 50, TEXT("smoothTimeDilation %f\n"), pow(sensitivity, pan1accum));
				GCmdController->EnqueueText( smoothTimeDilationCommand, -1 );
			}
			if (pan1accum < 0)
			{
				App_sprintf_s(smoothTimeDilationCommand, 50, TEXT("smoothTimeDilation %f\n"), pow(1.f/sensitivity, -pan1accum));
				GCmdController->EnqueueText( smoothTimeDilationCommand, -1 );
			}
			pan1accum = 0;
		}
		break;
	}
}

// Handler for touch-up message.
// Finishes the stroke and moves it to the collection of finished strokes.
// in:
//      hWnd        window handle
//      ti          TOUCHINPUT structure (info about contact)
static void OnTouchUpHandler(HWND hWnd, const TOUCHINPUT& ti)
{
    // Extract contact info: contact ID
    int iCursorId = GetTouchContactID(ti);
	POINT pt = GetTouchPoint(hWnd, ti);

	//Log(TEXT("Touch Up, id = %d, (%d, %d)"), iCursorId, pt.x, pt.y);

    // Find the stroke in the collection of the strokes in drawing.
    int iStrk = g_StrkColDrawing.FindStrokeById(iCursorId);
    ASSERT((iStrk >= 0) && (iStrk < g_StrkColDrawing.Count()));

	const CStroke& curStroke = *g_StrkColDrawing[iStrk];

	static bool bNoTapUntilAllTouchesRemoved = false;

	switch (gestureState)
	{
	case GS_INDETERMINATE: // flick? part of a double-tap, triple-tap...?
		if (g_StrkColDrawing.Count() > 1) // not the last, just move it to history
		{
			g_StrkColFinished.Add(g_StrkColDrawing[iStrk]);
			g_StrkColDrawing.Remove(iStrk);
		}
		else // last one. evaluation time!
		{
			// check for number of time-overlapping touches
			CCounter strokeStartTime = curStroke.GetLastTime();
			//Log(TEXT("stroke id %d, stokeTime = %f"), curStroke.GetId(), strokeStartTime.GetMSecs());

			int iNumTouchesInStroke = 0;
			CCounter earliestStartTime = strokeStartTime;
			for (int i=g_StrkColFinished.Count()-1; i>=0; i--)
			{
				//Log(TEXT("stroke %d, id = %d, start = %f, end = %f"), i, g_StrkColFinished[i]->GetId(), g_StrkColFinished[i]->GetStartTime().GetMSecs(), g_StrkColFinished[i]->GetLastTime().GetMSecs());
				if (g_StrkColFinished[i]->ContainsTime(strokeStartTime, 200.f))
				{
					// find earliest start time...
					if (g_StrkColFinished[i]->GetStartTime() < earliestStartTime)
						earliestStartTime = g_StrkColFinished[i]->GetStartTime();
					iNumTouchesInStroke++;
				}
				else
				{
					//Log(TEXT("touch %d not in time"), i);
					g_StrkColFinished.Remove(i);
				}
			}

			// eveything left in g_StrkColFinished overlaps with this last stroke
			CCounter deltaTime; deltaTime.Sample();
			deltaTime -= earliestStartTime;
			double dt = deltaTime.GetSecs();
			//Log(TEXT("dt = %f, numTouches = %d"), dt, iNumTouchesInStroke);
					
			if (!bNoTapUntilAllTouchesRemoved)
			{
				if (iNumTouchesInStroke == 0)
				{
					POINT dp = curStroke.GetTotalMovement();
					long adx = abs(dp.x);
					long ady = abs(dp.y);
					//Log(TEXT("dt = %f, dx = %d, dy = %d"), dt, dp.x, dp.y);
					if (dt < flickTime && adx > criticalLength && float(ady)/float(adx) < diagonalRatio)
					{ //flick!
						if (dp.x > 0) //flick right!
						{ 
							GCmdController->EnqueueText( TEXT("timewarpdirection 1\n"), -1 ); 
						}
						else //flick left!
						{ 
							GCmdController->EnqueueText( TEXT("timewarpdirection 0\n"), -1 ); 
						}
					}
					else if (dt < 0.4f && adx < criticalLength && ady < criticalLength)
					{ // click
						POINT p = curStroke.GetStartPoint();
						MouseMove( p.x, p.y );
						if ( !MouseDown() )
						{
							CKeys::KeyEvent( K_MOUSE1, true );
							CKeys::KeyEvent( K_MOUSE1, false );
						}
						MouseUp();
					}
				}
				else if (dt < 0.4f && iNumTouchesInStroke == 1)
				{ // two-finger tap
					KeyDown( K_SPACE, true );
					KeyUp  ( K_SPACE );
				}
				else if (dt < 1.f && iNumTouchesInStroke == 2)
				{ // three-finger tap
					KeyDown( K_ESCAPE, true );
					KeyUp  ( K_ESCAPE );
				}
			}

			g_StrkColFinished.Clear();
			g_StrkColDrawing.Clear();
		}
		break;

	case GS_PAN_SMOOTH:
	case GS_PAN_ONE:
	case GS_PAN:
	case GS_ZOOM:

		if (gestureState == GS_PAN_SMOOTH)
		{
			float dt = (float)(curStroke.GetLastTime() - curStroke.GetStartTime()).GetSecs();
			POINT dp = curStroke.GetTotalMovement();
			long adx = abs(dp.x);
			long ady = abs(dp.y);
			//Log(TEXT("dt = %f, dx = %d, dy = %d"), dt, dp.x, dp.y);
			if (dt < flickTime && adx > criticalLength && float(ady)/float(adx) < diagonalRatio)
			{ //flick!
				if (dp.x > 0) //flick right!
				{ 
					GCmdController->EnqueueText( TEXT("timewarpdirection 1\n"), -1 ); 
				}
				else //flick left!
				{ 
					GCmdController->EnqueueText( TEXT("timewarpdirection 0\n"), -1 ); 
				}
			}
			else
			{
				GCmdController->EnqueueText( TEXT("smoothTimeDilation 0\n"), -1 ); // snap to normal
			}
		}

		else if (gestureState == GS_PAN_ONE ||
				 gestureState == GS_PAN)
		{
			GCmdController->EnqueueText( TEXT("smoothTimeDilation 0\n"), -1 ); // snap to normal
		}

		g_StrkColFinished.Clear();
		g_StrkColDrawing.Remove(iStrk);
		for (int i=0; i<g_StrkColDrawing.Count(); i++)
			g_StrkColDrawing[i]->ClearHistory();
		gestureState = GS_INDETERMINATE;
		pan1accum = pan2accum = 0;
		bNoTapUntilAllTouchesRemoved = true;

		break;
	}

	if (bNoTapUntilAllTouchesRemoved && g_StrkColDrawing.Count() == 0)
		bNoTapUntilAllTouchesRemoved = false;
}

bool IMultiTouch_Win7::IsMultiTouchSupported()
{
	bool bResult = false;
	const int value = GetSystemMetrics(SM_DIGITIZER);
	if (value != 0)
	{
		if (value & NID_MULTI_INPUT)
		{
			// digitizer is multitouch
			const int MaxTouches = GetSystemMetrics(SM_MAXIMUMTOUCHES);
			Log( TEXT("Detected multitouch hardware (max touches: %d)"), MaxTouches );
			bResult = true;
		}
	}
	return bResult;
}

void IMultiTouch_Win7::IRegisterTouchWindow(HWND hWnd)
{
	// Do we want to register for WM_TOUCH events as opposed to gestures?
	if ( GRawTouch )
	{
		m_API->pRegisterTouchWindow( hWnd, 0 );
	}
}

LRESULT IMultiTouch_Win7::OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bOutMsgWasProcessedByTouch)
{
	switch( uMsg )
	{
		case WM_GESTURENOTIFY:
		{
			// This is the right place to define the list of gestures that this
			// application will support. By populating GESTURECONFIG structure 
			// and calling SetGestureConfig function. We can choose gestures 
			// that we want to handle in our application. In this app we
			// decide to handle all gestures.
			GESTURECONFIG gc =
			{
				0,              // gesture ID
				GC_ALLGESTURES, // settings related to gesture ID that are to be 
								// turned on
				0               // settings related to gesture ID that are to be 
								// turned off
			};

			const BOOL bResult = m_API->pSetGestureConfig
			(
				hWnd,                 // window for which configuration is specified  
				0,                    // reserved, must be 0
				1,                    // count of GESTURECONFIG structures
				&gc,                  // array of GESTURECONFIG structures, dwIDs will be processed in the
									  // order specified and repeated occurances will overwrite previous ones
				sizeof(GESTURECONFIG) // sizeof(GESTURECONFIG)
			);                        
            
			GESTURENOTIFYSTRUCT* gns = (GESTURENOTIFYSTRUCT*)lParam;
			MouseMove( gns->ptsLocation.x, gns->ptsLocation.y );			

			if (!bResult)
			{
				LogErr(TEXT("Error in execution of SetGestureConfig"));
			}			
		}
		break;

		// WM_TOUCH message handlers
		case WM_TOUCH:
		{
			// WM_TOUCH message can contain several messages from different contacts
			// packed together.
			// Message parameters need to be decoded:
			unsigned int numInputs = (unsigned int) wParam; // Number of actual per-contact messages
			TOUCHINPUT* ti = new TOUCHINPUT[numInputs]; // Allocate the storage for the parameters of the per-contact messages
			if (ti == NULL)
			{
				break;
			}
			// Unpack message parameters into the array of TOUCHINPUT structures, each
			// representing a message for one single contact.
			if (m_API->pGetTouchInputInfo((HTOUCHINPUT)lParam, numInputs, ti, sizeof(TOUCHINPUT)))
			{
				// For each contact, dispatch the message to the appropriate message
				// handler.
				for (unsigned int i = 0; i < numInputs; ++i)
				{
					if (ti[i].dwFlags & TOUCHEVENTF_DOWN)
					{
						OnTouchDownHandler(hWnd, ti[i]);
					}
					else if (ti[i].dwFlags & TOUCHEVENTF_MOVE)
					{
						OnTouchMoveHandler(hWnd, ti[i]);
					}
					else if (ti[i].dwFlags & TOUCHEVENTF_UP)
					{
						OnTouchUpHandler(hWnd, ti[i]);
					}
				}
			}
			m_API->pCloseTouchInputHandle((HTOUCHINPUT)lParam);
			delete [] ti;

			// signal to game to use multitouch interface (instructions, no cursor, etc)
			GCmdController->EnqueueText( TEXT("multiTouch 1\n"), -1 );
		}
		break;


		case WM_GESTURE:
		{
			// gesture processing all happens in GestureWndProc
			bOutMsgWasProcessedByTouch = true;
			return GestureWndProc(hWnd,wParam,lParam,m_API);
		}
		break;

		case WM_TABLET_FLICK:
		{
			const FLICK_DATA& flickData = *(const FLICK_DATA *)&wParam; 
			FLICKDIRECTION flickDirection = FLICKDIRECTION((*((int*)&flickData) & 0x000000E0) >> 5);

			if (flickDirection == FLICKDIRECTION_LEFT)
			{
				GCmdController->EnqueueText( TEXT("timewarpdirection 0\n"), -1 ); 
				bOutMsgWasProcessedByTouch = true;
				return FLICK_WM_HANDLED_MASK;
			}
			else if (flickDirection == FLICKDIRECTION_RIGHT)
			{
				GCmdController->EnqueueText( TEXT("timewarpdirection 1\n"), -1 ); 
				bOutMsgWasProcessedByTouch = true;
				return FLICK_WM_HANDLED_MASK;
			}
			else if (flickDirection == FLICKDIRECTION_DOWN)
			{
				//GCmdController->EnqueueText( TEXT("timewarpdirection 1\n"), -1 ); 
				bOutMsgWasProcessedByTouch = true;
				return FLICK_WM_HANDLED_MASK;
			}
		}
		break;
	}

	bOutMsgWasProcessedByTouch = false;
	return 0;
}

// Returns true if the caller should abort message processing.
bool IMultiTouch_Win7::OnLButtonDown()
{
	// we can distinguish between mouse clicks and touch clicks:
	const LPARAM extraLowParam = GetMessageExtraInfo();
	const LPARAM highBits = extraLowParam & 0xFFFFFF00; // if (highBits == 0xFF515700) // pen or touch
	const LPARAM lowBits  = extraLowParam & 0x80;		  // if (lowBits  >  0) touch (as opposed to pen)
	const bool isTouch = GRawTouch && (highBits == 0xFF515700) && (lowBits > 0);
	if (isTouch)
		// signal to game to use multitouch interface (instructions, no cursor, etc)
		GCmdController->EnqueueText( TEXT("multiTouch 1\n"), -1 );
	else
		// signal to game to use non-multitouch interface (instructions, show mouse cursor, etc)
		GCmdController->EnqueueText( TEXT("multiTouch 0\n"), -1 );
	return isTouch;
}

// Returns true if the caller should abort message processing.
bool IMultiTouch_Win7::OnRButtonDown()
{
	// we can distinguish between mouse clicks and touch clicks:
	const LPARAM extraLowParam = GetMessageExtraInfo();
	const LPARAM highBits = extraLowParam & 0xFFFFFF00; // if (highBits == 0xFF515700) // pen or touch
	const LPARAM lowBits  = extraLowParam & 0x80;		  // if (lowBits  >  0) touch (as opposed to pen)
	const bool isTouch = GRawTouch && (highBits == 0xFF515700) && (lowBits > 0);
	return isTouch;
}
*/

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MULTITOUCH && USES_WINDOWS //
// - ------------------------------------------------------------------------------------------ - //
