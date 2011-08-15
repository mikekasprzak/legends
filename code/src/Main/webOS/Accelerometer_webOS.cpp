// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WEBOS
// - ------------------------------------------------------------------------------------------ - //
#include <math.h>
#include <Debug/GelDebug.h>

#include <SDL/SDL.h>
#include <PDL.h>
#include <PDLPatch.h>

#include <Graphics/Graphics_Screen.h>
// - ------------------------------------------------------------------------------------------ - //
extern float accel_x;
extern float accel_y;
extern float accel_z;
extern int phone_orientation;

float accel_x;
float accel_y;
float accel_z;
// - ------------------------------------------------------------------------------------------ - //
SDL_Joystick* WebOSJoystick;

float oldaccel_x;
float oldaccel_y;
float oldaccel_z;

int accel_update = 0;

#ifndef NDEBUG
extern bool AccelMessage;
bool AccelMessage = false;
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
// Wide Orientations, as in Tablets and PC's //
PDL_Orientation PDL_Orientations_Wide[] = {
	PDL_ORIENTATION_0,
	PDL_ORIENTATION_90,
	PDL_ORIENTATION_180,
	PDL_ORIENTATION_270,
};
// - ------------------------------------------------------------------------------------------ - //
// Tall Orientations, as in Phones //
PDL_Orientation PDL_Orientations_Tall[] = {
	PDL_ORIENTATION_90,
	PDL_ORIENTATION_180,
	PDL_ORIENTATION_270,
	PDL_ORIENTATION_0,
};
// - ------------------------------------------------------------------------------------------ - //
void WebOS_AccelerometerInit() {
	SDL_InitSubSystem( SDL_INIT_JOYSTICK );
	WebOSJoystick = SDL_JoystickOpen(0);
#ifndef NDEBUG	
	AccelMessage = false;
#endif // NDEBUG //
}
// - ------------------------------------------------------------------------------------------ - //
void WebOS_Orientation() {
	// Since accelerometer only updates 30 times per second, and we don't need realtime, track changes every 4 frames //
	accel_update++;
	if ( accel_update & 3 )
		return;
	
	// Store last accelerometer data //
	oldaccel_x = accel_x;
	oldaccel_y = accel_y;
	oldaccel_z = accel_z;	
	
	// Get latest data //
	accel_x = (float) SDL_JoystickGetAxis( WebOSJoystick, 0 ) / 32768.0;
	accel_y = (float) SDL_JoystickGetAxis( WebOSJoystick, 1 ) / 32768.0;
	accel_z = (float) SDL_JoystickGetAxis( WebOSJoystick, 2 ) / 32768.0;

#ifndef NDEBUG	
	if ( AccelMessage ) {
		Log( "***** Logging Accelerometer Status ***** \n" );
		Log( "X: %f,  Y: %f,  Z: %f\n", accel_x, accel_y, accel_z );
	
		AccelMessage = false;
		
		if ( ActualScreen::TallScreen ) {
			// Tall //
		}
		else {
			// Wide //
			Log( "* NOTE: Wide Orientation, so x and y will be flipped.\n" );
		}
	}
#endif // NDEBUG //

	if ( ActualScreen::TallScreen ) {
		// Tall //
	}
	else {
		// Wide //
		accel_x = -accel_x;
		accel_y = -accel_y;
	}

	// Bail if accelerometer has changed too quickly //
	if ( fabs(fabs(oldaccel_x) - fabs(accel_x)) > 0.1f )
		return;
	if ( fabs(fabs(oldaccel_y) - fabs(accel_y)) > 0.1f )
		return;
	if ( fabs(fabs(oldaccel_z) - fabs(accel_z)) > 0.1f )
		return;

	
	if ( fabs(accel_z) > 0.9f ) {
		// Do nothing, Z is bigger //	
	}
	else if ( fabs(accel_x) > fabs(accel_y) ) {
		if ( (fabs(accel_x) - fabs(accel_y)) < 0.1f ) {
			// Do nothing, inbetween orientations //
		}
		else {
			if ( accel_x < 0.0f )
				phone_orientation = 2;
			else
				phone_orientation = 0;
		}
	}
	else {
		if ( (fabs(accel_y) - fabs(accel_x)) < 0.1f ) {
			// Do nothing, inbetween orientations //
		}
		else {
			if ( accel_y < 0.0f )
				phone_orientation = 1;
			else
				phone_orientation = 3;
		}
	}
	
	if ( ActualScreen::TallScreen ) {
		PDL_SetOrientation( PDL_Orientations_Tall[phone_orientation] );
	}
	else {
//		PDL_SetOrientation( PDL_Orientations_Wide[phone_orientation] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WEBOS //
// - ------------------------------------------------------------------------------------------ - //
