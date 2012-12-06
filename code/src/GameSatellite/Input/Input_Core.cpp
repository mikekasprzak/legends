// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Input.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
void Init() {
	#ifdef USES_XINPUT
	{
		XInput::Init();
		XInput::Poll();
		
		Log( "-=- XInput -- %i Device(s) Connected -=-", XInput::DevicesConnected() );
		for ( size_t idx = 0; idx < XInput::Size(); idx++ ) {
	        if ( XInput::IsConnected(idx) ) {
	        	Log( "%i - Connected", idx );
			}			
		}
		Log( "" );
	}
	#endif // USES_XINPUT //
}
// - ------------------------------------------------------------------------------------------ - //
void Poll() {
	#ifdef USES_XINPUT
	{
		XInput::Poll();
		if ( XInput::HasConnectionChanged() ) {
			for ( size_t idx = 0; idx < XInput::Size(); idx++ ) {
				if ( XInput::HasConnectionChanged(idx) ) {
					Log( "** XInput Controller %i %s", idx, XInput::IsConnected(idx) ? "Connected" : "Disconnected" );
				}
			}
		}
	}
	#endif // USES_XINPUT //
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
// - ------------------------------------------------------------------------------------------ - //
