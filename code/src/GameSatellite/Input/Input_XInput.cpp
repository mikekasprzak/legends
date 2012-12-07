// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_XINPUT
// - ------------------------------------------------------------------------------------------ - //
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <XInput/XInput.h>
#include "Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
namespace XInput {
// - ------------------------------------------------------------------------------------------ - //
// Reference: http://code.google.com/p/xcontroller/
// MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinputenable%28v=vs.85%29.aspx
// - ------------------------------------------------------------------------------------------ - //
bool Connected[XUSER_MAX_COUNT];
bool OldConnected[XUSER_MAX_COUNT];

XINPUT_STATE State[XUSER_MAX_COUNT];
XINPUT_CAPABILITIES Caps[XUSER_MAX_COUNT];
XINPUT_BATTERY_INFORMATION Battery[XUSER_MAX_COUNT];
XINPUT_BATTERY_INFORMATION HeadsetBattery[XUSER_MAX_COUNT];
XINPUT_VIBRATION Vibration[XUSER_MAX_COUNT];
// - ------------------------------------------------------------------------------------------ - //
void Init() {
	ZeroMemory( &Connected, sizeof(Connected) );
	ZeroMemory( &OldConnected, sizeof(OldConnected) );
	
	ZeroMemory( &State, sizeof(State) );
	ZeroMemory( &Vibration, sizeof(Vibration) );
	
	// Connect Signals (Functions to be called) //
	System::GainFocus.Connect( GainFocus );
	System::LoseFocus.Connect( LoseFocus );
		
	Input::Poll.Connect( PollEvent );
}
// - ------------------------------------------------------------------------------------------ - //
void InitEvent( void* ) {
	Init();
	Poll();
	
	Log( "-=- XInput -- %i Device(s) Connected -=-", DevicesConnected() );
	for ( size_t idx = 0; idx < Size(); idx++ ) {
        if ( IsConnected(idx) ) {
        	Log( "%i - Connected", idx );
		}			
	}
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
void Poll() {
	for ( int idx = 0; idx < XUSER_MAX_COUNT; idx++ ) {
		OldConnected[idx] = Connected[idx];
		
		Connected[idx] = (XInputGetState(idx, &State[idx]) == ERROR_SUCCESS);
		// ERROR_SUCCESS, ERROR_DEVICE_NOT_CONNECTED

		if( Connected[idx] ) {
			XInputGetCapabilities( idx, 0, &Caps[idx] );
			XInputGetBatteryInformation( idx, BATTERY_DEVTYPE_GAMEPAD, &Battery[idx] );
			XInputGetBatteryInformation( idx, BATTERY_DEVTYPE_HEADSET, &HeadsetBattery[idx] );
			XInputSetState( idx, &Vibration[idx] );
		}
	}
	
	// TODO: KeyStrokes
}
// - ------------------------------------------------------------------------------------------ - //
void PollEvent( void* ) {
	Poll();
	if ( HasConnectionChanged() ) {
		for ( size_t idx = 0; idx < XInput::Size(); idx++ ) {
			if ( HasConnectionChanged(idx) ) {
				Log( "** XInput Controller %i %s", idx, IsConnected(idx) ? "Connected" : "Disconnected" );
			}
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void LoseFocus( void* ) {
	XInputEnable( FALSE );
}
// - ------------------------------------------------------------------------------------------ - //
void GainFocus( void* ) {
	XInputEnable( TRUE );
}
// - ------------------------------------------------------------------------------------------ - //
size_t Size() {
	return XUSER_MAX_COUNT;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
size_t DevicesConnected() {
	size_t Count = 0;
	for ( size_t idx = 0; idx < XUSER_MAX_COUNT; idx++ ) {
		if( IsConnected(idx) ) {
			Count++;
		}
	}
	return Count;
}
// - ------------------------------------------------------------------------------------------ - //
bool IsConnected( const int Index ) {
	return Connected[Index];
}
bool IsConnected() {
	for ( int idx = 0; idx < XUSER_MAX_COUNT; idx++ ) {
		return_if( IsConnected(idx) );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool HasConnectionChanged( const int Index ) {
	return OldConnected[Index] != Connected[Index];
}
bool HasConnectionChanged() {
	for ( int idx = 0; idx < XUSER_MAX_COUNT; idx++ ) {
		return_if( HasConnectionChanged(idx) );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace XInput //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_XINPUT //
// - ------------------------------------------------------------------------------------------ - //
