// - ------------------------------------------------------------------------------------------ - //
#include <math.h>

#include <Debug/GelDebug.h>
// - ------------------------------------------------------------------------------------------ - //
extern float orientation_x;
extern float orientation_y;
extern float orientation_z;
// - ------------------------------------------------------------------------------------------ - //
float orientation_x;
float orientation_y;
float orientation_z;
// - ------------------------------------------------------------------------------------------ - //

extern float accel_x;
extern float accel_y;
extern float accel_z;
extern int phone_orientation;

float accel_x;
float accel_y;
float accel_z;

// - ------------------------------------------------------------------------------------------ - //
extern float smoothaccel_x;
extern float smoothaccel_y;
extern float smoothaccel_z;

float smoothaccel_x;
float smoothaccel_y;
float smoothaccel_z;
// - ------------------------------------------------------------------------------------------ - //
#define ACCEL_MAX	4

float oldaccel_x[ACCEL_MAX];
float oldaccel_y[ACCEL_MAX];
float oldaccel_z[ACCEL_MAX];

int accel_update = 0;
// - ------------------------------------------------------------------------------------------ - //
extern void Generic_Orientation();
void Generic_Orientation() {
	// Shift the last stored accelerometer datas //
	for ( int idx = 1; idx < ACCEL_MAX; idx++ ) {
		oldaccel_x[idx] = oldaccel_x[idx-1];
		oldaccel_y[idx] = oldaccel_y[idx-1];
		oldaccel_z[idx] = oldaccel_z[idx-1];
	}
	
	// Store last accelerometer data //
	oldaccel_x[0] = accel_x;
	oldaccel_y[0] = accel_y;
	oldaccel_z[0] = accel_z;
	
	// Get Latest Data -- Note the order differential //
	accel_x = orientation_y;
	accel_y = orientation_x;
	accel_z = orientation_z;
	
	// Calculate Smoothed Acceleration //
	smoothaccel_x = accel_x;
	smoothaccel_y = accel_y;
	smoothaccel_z = accel_z;

	for ( int idx = 0; idx < ACCEL_MAX; idx++ ) {
		smoothaccel_x += oldaccel_x[idx];
		smoothaccel_y += oldaccel_y[idx];
		smoothaccel_z += oldaccel_z[idx];
	}
	
	smoothaccel_x /= (float)(1+ACCEL_MAX);
	smoothaccel_y /= (float)(1+ACCEL_MAX);
	smoothaccel_z /= (float)(1+ACCEL_MAX);
	
	// Since accelerometer only updates 30 times per second, and we don't need realtime, track changes every 4 frames //
	accel_update++;
	if ( accel_update & 3 )
		return;
	
	// Bail if accelerometer has changed too quickly //
	if ( fabs(fabs(oldaccel_x[0]) - fabs(accel_x)) > 0.1f )
		return;
	if ( fabs(fabs(oldaccel_y[0]) - fabs(accel_y)) > 0.1f )
		return;
	if ( fabs(fabs(oldaccel_z[0]) - fabs(accel_z)) > 0.1f )
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
				phone_orientation = 3;
			else
				phone_orientation = 1;
		}
	}
	else {
		if ( (fabs(accel_y) - fabs(accel_x)) < 0.1f ) {
			// Do nothing, inbetween orientations //
		}
		else {
			if ( accel_y < 0.0f )
				phone_orientation = 2;
			else
				phone_orientation = 0;
		}
	}
	
	// Set System Orientation //
}
// - ------------------------------------------------------------------------------------------ - //
