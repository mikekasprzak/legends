// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_BADA
// - ------------------------------------------------------------------------------------------ - //
#include <math.h>

#include <Debug/GelDebug.h>
// - ------------------------------------------------------------------------------------------ - //
extern float orientation_x;
extern float orientation_y;
extern float orientation_z;
// - ------------------------------------------------------------------------------------------ - //

extern float accel_x;
extern float accel_y;
extern float accel_z;
extern int phone_orientation;

float accel_x;
float accel_y;
float accel_z;

// - ------------------------------------------------------------------------------------------ - //

float oldaccel_x;
float oldaccel_y;
float oldaccel_z;

int accel_update = 0;
// - ------------------------------------------------------------------------------------------ - //
void Bada_Orientation() {
	// Since accelerometer only updates 30 times per second, and we don't need realtime, track changes every 4 frames //
	accel_update++;
	if ( accel_update & 3 )
		return;
	
	// Store last accelerometer data //
	oldaccel_x = accel_x;
	oldaccel_y = accel_y;
	oldaccel_z = accel_z;		
	
	// Get Latest Data //
//	accel_x = orientation_x;
//	accel_y = orientation_y;
//	accel_z = orientation_z;

	accel_x = -orientation_y;
	accel_y = orientation_x;
	accel_z = orientation_z;

	
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
	
	// Set System Orientation //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MAEMO //
// - ------------------------------------------------------------------------------------------ - //
