// - ------------------------------------------------------------------------------------------ - //
#include <s3e.h>
#include <s3ePointer.h>
#include <s3eDevice.h>
#include <s3eGL.h>

#include <GLES/gl.h>
#include <EGL/egl.h>
#include <IwGL.h>

#include <Graphics/Graphics.h>
#include <Input/Input.h>
#include <Debug/Log.h>
#include <Timer/Timer.h>
#include <System/Path.h>
// - ------------------------------------------------------------------------------------------ - //
extern void Simple_Init( int Width, int Height );
extern void Simple_Exit();
extern void Simple_Step();
extern void Simple_Draw();
extern void Simple_FocusLost();
extern void Simple_FocusGained();
// - ------------------------------------------------------------------------------------------ - //

bool HasAccelerometer;

// - ------------------------------------------------------------------------------------------ - //
extern int mouse_x;
extern int mouse_y;
extern int mouse_b;
extern int mouse_b_new;

extern int EventValue;
// - ------------------------------------------------------------------------------------------ - //
int32 PointerEvent_Button( s3ePointerEvent* e, void* User ) {
//	if ( e->m_Button == S3E_POINTER_BUTTON_SELECT ) 
	if ( e->m_Pressed ) 	
	{
		mouse_x = e->m_x;
		mouse_y = e->m_y;
		mouse_b |= 1;
		mouse_b_new |= 1;
	}
	else {
//		mouse_x = e->m_x;
//		mouse_y = e->m_y;
		mouse_b = 0;
	}
	
	return S3E_RESULT_SUCCESS;
}
// - ------------------------------------------------------------------------------------------ - //
int32 PointerEvent_Motion( s3ePointerMotionEvent* e, void* User ) {
	if ( mouse_b != 0 ) {
		mouse_x = e->m_x;
		mouse_y = e->m_y;
	}	
	return S3E_RESULT_SUCCESS;
}
// - ------------------------------------------------------------------------------------------ - //
int32 KeyboardEvent_Key( s3eKeyboardEvent* e, void* User ) {
	if ( e->m_Pressed ) {
		switch( e->m_Key ) {
			case s3eKeyEsc:
			case s3eKeyLSK:
			case s3eKeyBack:
			case s3eKeyMenu:
			{
				EventValue = 1;
				
#ifdef USES_MARMALADE_ANDROID
				extern bool IsMainMenu();
				if ( e->m_Key == s3eKeyBack ) {
					if ( IsMainMenu() ) {
						System::CloseButtonPressed = true;
					}
				}
#endif // USES_MARMALADE_ANDROID //				
				break;
			}
		
//			case s3eKeyF10:
//			{
//				System::CloseButtonPressed = true;
//				break;
//			}
		};
	}
	return S3E_RESULT_SUCCESS;
}

// - ------------------------------------------------------------------------------------------ - //
volatile bool GLContextAvailable;
volatile bool IsActive;
// - ------------------------------------------------------------------------------------------ - //
int32 GLEvent_Suspend( void* e, void* User ) {
	Log("*** OpenGL Suspend\n");
	GLContextAvailable = false;
	//IwGLSuspend(); // NOTE: Called Automatically //
	return S3E_RESULT_SUCCESS;
}
// - ------------------------------------------------------------------------------------------ - //
int32 GLEvent_Resume( void* e, void* User ) {
	Log("*** OpenGL Resume\n");
	GLContextAvailable = true;
	//IwGLResume(); // NOTE: Called Automatically //
//	TexturePool::ReloadTextures();
	return S3E_RESULT_SUCCESS;
}
// - ------------------------------------------------------------------------------------------ - //
int32 DeviceEvent_Pause( void* e, void* User ) {
	Log("*** Pause\n");
	IsActive = false;
	Simple_FocusLost();
	return S3E_RESULT_SUCCESS;
}
// - ------------------------------------------------------------------------------------------ - //
int32 DeviceEvent_Resume( void* e, void* User ) {
	Log("*** Resume\n");
	IsActive = true;
	Simple_FocusGained();
	return S3E_RESULT_SUCCESS;
}
// - ------------------------------------------------------------------------------------------ - //
int32 DeviceEvent_Exit( void* e, void* User ) {
	Log("*** Exit\n");
	System::CloseButtonPressed = true;
	return S3E_RESULT_SUCCESS;
}
// - ------------------------------------------------------------------------------------------ - //
//int32 DeviceEvent_Foreground( void* e, void* User ) {
//	Log("*** Foreground\n");
//	return S3E_RESULT_SUCCESS;
//}
// - ------------------------------------------------------------------------------------------ - //
//int32 DeviceEvent_Background( void* e, void* User ) {
//	Log("*** Background\n");
//	return S3E_RESULT_SUCCESS;
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Init() {
	extern char AppBaseDir[];
	extern char AppSaveDir[];
	gelGetContentPath( AppBaseDir, 2048 );
	gelGetStoragePath( AppSaveDir, 2048 );
	Log( "+ Base Directory: %s\n\n", AppBaseDir );
	Log( "+ Save Directory: %s\n\n", AppSaveDir );

	Log( "*** MARMALADE DEVICE INFO ***\n" );
	Log( "- DEVICE_OS: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_OS ), s3eDeviceGetInt( S3E_DEVICE_OS ) );
	Log( "- DEVICE_CLASS: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_CLASS ), s3eDeviceGetInt( S3E_DEVICE_CLASS ) );
	Log( "- DEVICE_OS_VERSION: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_OS_VERSION ), s3eDeviceGetInt( S3E_DEVICE_OS_VERSION ) );
	Log( "- DEVICE_SDK_VERSION: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_SDK_VERSION ), s3eDeviceGetInt( S3E_DEVICE_SDK_VERSION ) );
	Log( "- DEVICE_S3E_VERSION: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_S3E_VERSION ), s3eDeviceGetInt( S3E_DEVICE_S3E_VERSION ) );
	Log( "- DEVICE_ID: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_ID ), s3eDeviceGetInt( S3E_DEVICE_ID ) );
	Log( "- DEVICE_ARCHITECTURE: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_ARCHITECTURE ), s3eDeviceGetInt( S3E_DEVICE_ARCHITECTURE ) );
	Log( "- DEVICE_CHIPSET: %s\n", s3eDeviceGetString( S3E_DEVICE_CHIPSET ) );
	Log( "- DEVICE_NUM_CPU_CORES: %i\n", s3eDeviceGetInt( S3E_DEVICE_NUM_CPU_CORES ) );
	Log( "- DEVICE_FPU: %i\n", s3eDeviceGetInt( S3E_DEVICE_FPU ) );
	Log( "- DEVICE_FREE_RAM: %i\n", s3eDeviceGetInt( S3E_DEVICE_FREE_RAM ) );
	Log( "- DEVICE_TOTAL_RAM: %i\n", s3eDeviceGetInt( S3E_DEVICE_TOTAL_RAM ) );
	Log( "- DEVICE_MEM_TOTAL: %i\n", s3eDeviceGetInt( S3E_DEVICE_MEM_TOTAL ) );
	Log( "- DEVICE_MEM_FREE: %i\n", s3eDeviceGetInt( S3E_DEVICE_MEM_FREE ) );
	Log( "- DEVICE_BATTERY_LEVEL: %i\n", s3eDeviceGetInt( S3E_DEVICE_BATTERY_LEVEL ) );
	Log( "- DEVICE_MAINS_POWER: %i\n", s3eDeviceGetInt( S3E_DEVICE_MAINS_POWER ) );
	Log( "- DEVICE_PROXIMITY: %i\n", s3eDeviceGetInt( S3E_DEVICE_PROXIMITY ) );
	Log( "- DEVICE_NAME: %s\n", s3eDeviceGetString( S3E_DEVICE_NAME ) );
	Log( "- PHONE_NUMBER: %s\n", s3eDeviceGetString( S3E_DEVICE_PHONE_NUMBER ) );
	Log( "- DEVICE_IMSI: %s\n", s3eDeviceGetString( S3E_DEVICE_IMSI ) );
	Log( "- DEVICE_UNIQUE_ID: %s (%i)\n", s3eDeviceGetString( S3E_DEVICE_UNIQUE_ID ), s3eDeviceGetInt( S3E_DEVICE_UNIQUE_ID ) );
	Log( "- DEVICE_LANGUAGE: %i\n", s3eDeviceGetInt( S3E_DEVICE_LANGUAGE ) );
	Log( "- DEVICE_STATE: %i\n", s3eDeviceGetInt( S3E_DEVICE_STATE ) );
	Log( "- DEVICE_LOCALE: %s\n", s3eDeviceGetString( S3E_DEVICE_LOCALE ) );
	
	// Devices with MBX - Also see: http://www.trejan.com/projects/ipod/phobos.html //
	//"iPod1,1"		// iPod 1
	//"iPod2,1"		// iPod 2
	//"iPhone1,1"	// iPhone
	//"iPhone1,2"	// iPhone 3G
	
	// Should probably pattern match "iPod1", "iPod2", and "iPhone1" (note the CDMA code below) //

	// Devices with SGX //
	//"iPhone2,1"	// iPhone 3GS
	//"iPhone3,1"	// iPhone 4
	//"iPhone3,3"	// iPhone 4 CDMA
	//"iPod3,1"		// iPod 3
	//"iPod4,1"		// iPod 4
	//"iPad1,1"		// iPad 1
	//"iPad2,1"		// iPad 2 ??? (guess)
	//"AppleTV2,1"	// Apple TV
		
	EventValue = 0;

	HasAccelerometer = false;
	if ( s3eAccelerometerGetInt( S3E_ACCELEROMETER_AVAILABLE ) ) {
		Log( "* Accelerometer Available! Starting...\n" );
		HasAccelerometer = true;
		s3eAccelerometerStart();
	}
	else {
		Log( "- No Accelerometer\n" );
	}
	
	s3ePointerRegister( S3E_POINTER_BUTTON_EVENT, (s3eCallback)PointerEvent_Button, 0 );
	s3ePointerRegister( S3E_POINTER_MOTION_EVENT, (s3eCallback)PointerEvent_Motion, 0 );
	s3eKeyboardRegister( S3E_KEYBOARD_KEY_EVENT, (s3eCallback)KeyboardEvent_Key, 0 );
	IwGLRegister( IW_GL_SUSPEND, (s3eCallback)GLEvent_Suspend, 0 );
	IwGLRegister( IW_GL_RESUME, (s3eCallback)GLEvent_Resume, 0 );
	
	s3eDeviceRegister( S3E_DEVICE_PAUSE, DeviceEvent_Pause, 0 );
	s3eDeviceRegister( S3E_DEVICE_UNPAUSE, DeviceEvent_Resume, 0 );
	s3eDeviceRegister( S3E_DEVICE_EXIT, DeviceEvent_Exit, 0 );
	
//	s3eDeviceRegister( S3E_DEVICE_BACKGROUND, DeviceEvent_Background, 0 );
//	s3eDeviceRegister( S3E_DEVICE_FOREGROUND, DeviceEvent_Foreground, 0 );
   
	glDisable( GL_DEPTH_TEST );  
	glDisable( GL_CULL_FACE );
	glDisable( GL_DITHER );
	glDisable( GL_FOG );
	glDisable( GL_COLOR_MATERIAL );
	glDisable( GL_LIGHTING );
	glDisable( GL_ALPHA_TEST );
	
	glDisable( GL_DEPTH_TEST );
	glDepthMask( GL_FALSE );

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glClearColor(1,1,1,1);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	IwGLSwapBuffers();

	glClearColor(1,1,1,1);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	IwGLSwapBuffers();

	glClearColor(1,1,1,1);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	IwGLSwapBuffers();
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	if ( HasAccelerometer ) {
		s3eAccelerometerStop();
	}

//	s3eDeviceUnRegister( S3E_DEVICE_FOREGROUND, DeviceEvent_Foreground );
//	s3eDeviceUnRegister( S3E_DEVICE_BACKGROUND, DeviceEvent_Background );

	s3eDeviceUnRegister( S3E_DEVICE_PAUSE, (s3eCallback)DeviceEvent_Pause );
	s3eDeviceUnRegister( S3E_DEVICE_UNPAUSE, (s3eCallback)DeviceEvent_Resume );
	s3eDeviceUnRegister( S3E_DEVICE_EXIT, (s3eCallback)DeviceEvent_Exit );

	s3eGLUnRegister( S3E_GL_RESUME, (s3eCallback)GLEvent_Resume );
	s3eGLUnRegister( S3E_GL_SUSPEND, (s3eCallback)GLEvent_Suspend );

	s3eKeyboardUnRegister( S3E_KEYBOARD_KEY_EVENT, (s3eCallback)KeyboardEvent_Key );

	s3ePointerUnRegister( S3E_POINTER_MOTION_EVENT, (s3eCallback)PointerEvent_Motion );
	s3ePointerUnRegister( S3E_POINTER_BUTTON_EVENT, (s3eCallback)PointerEvent_Button );
}
// - ------------------------------------------------------------------------------------------ - //
void Update() {
	if ( HasAccelerometer ) {
		extern float orientation_x;
		extern float orientation_y;
		extern float orientation_z;
		extern void Generic_Orientation();
		
		float Scalar = 1.0f / (float)(S3E_ACCELEROMETER_1G); 
		
		orientation_x = ((float)s3eAccelerometerGetX()) * Scalar;
		orientation_y = ((float)s3eAccelerometerGetY()) * Scalar;
		orientation_z = ((float)s3eAccelerometerGetZ()) * Scalar;
		Generic_Orientation();
	}
		
	Simple_Step();
}
// - ------------------------------------------------------------------------------------------ - //
void Draw() {
//	glClearColor(1,1,1,1);
//	//IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
//	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
//	glDisable( GL_DEPTH_TEST );
//	glDepthMask( GL_FALSE );

//	glClearColor(1,1,1,1);
//	glClear( GL_DEPTH_BUFFER_BIT );
	glDisable( GL_DEPTH_TEST );
//	glDisable ( GL_LIGHTING );
//	glDisable( GL_ALPHA_TEST );
//	glDepthMask( GL_FALSE );
//	glDisable( GL_CULL_FACE );
//	glDisable( GL_DITHER );
//	glDisable( GL_FOG );
//	glDisable( GL_COLOR_MATERIAL );
//	glDisable( GL_COLOR_LOGIC_OP );
//	glDisable( GL_STENCIL_TEST );
//	glDisable( GL_SCISSOR_TEST );


//	glMatrixMode( GL_PROJECTION );
//	glLoadIdentity();
//	
//	glMatrixMode( GL_TEXTURE );
//	glLoadIdentity();
//	glScalef( 1 / UV_ONE_F, 1 / UV_ONE_F, 1 / UV_ONE_F );
//
//    glMatrixMode( GL_MODELVIEW );
//    glLoadIdentity();
    
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//	glDisableClientState(GL_COLOR_ARRAY);
//	glDisable( GL_TEXTURE_2D );
	

	Simple_Draw();
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
TIMEVALUE WorkTime;
extern void SkipTime();
void SkipTime() {
	WorkTime = GetTimeNow();
}
// - ------------------------------------------------------------------------------------------ - //

//--------------------------------------------------------------------------
// Main global function
//--------------------------------------------------------------------------
S3E_MAIN_DECL void IwMain() {
	IwGLInit();
	GLContextAvailable = true;
	IsActive = true;
	
	Init();

	Simple_Init( IwGLGetInt( IW_GL_WIDTH ), IwGLGetInt( IW_GL_HEIGHT ) );
	SkipTime();
	SetFramesPerSecond( 60 );
	
	int nextFrame = 0;

	while ( true ) {
		s3eDeviceYield(0);

		if ( IsActive ) {
			TIMEVALUE TimeDiff = SubtractTime( GetTimeNow(), WorkTime );
			int FramesOfWork = GetFrames( &TimeDiff );
	
			for ( int Frame = 0; Frame < (FramesOfWork); Frame++ ) {
				Update();
				AddFrame( &WorkTime );
	
				if ( s3eDeviceCheckQuitRequest() || gelHasShutdown() )
					break;
			}
			
			if ( s3eDeviceCheckQuitRequest() || gelHasShutdown() )
				break;
			
			if (FramesOfWork > 0) {
				if ( GLContextAvailable )
					Draw();
				glFlush();
				IwGLSwapBuffers();
			}
		}
	}
	Simple_Exit();
	Exit();
		
	IwGLTerminate();
}
