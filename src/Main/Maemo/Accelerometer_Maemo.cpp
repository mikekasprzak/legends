// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_MAEMO
// - ------------------------------------------------------------------------------------------ - //
#include <math.h>
#include <stdio.h>

#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
static int ocnt=0;
static int oax=0;
static int oay=0;
static int oaz=0;
	
static const char *accel_filename = "/sys/class/i2c-adapter/i2c-3/3-001d/coord";

int liqaccel_read(int *ax,int *ay,int *az)
{
	FILE *fd;
	int rs;
	fd = fopen(accel_filename, "r");
	if(fd==NULL){ Log("liqaccel, cannot open for reading"); return -1;}	
	rs=fscanf((FILE*) fd,"%i %i %i",ax,ay,az);	
	fclose(fd);	
	if(rs != 3){ Log("liqaccel, cannot read information"); return -2;}
	int bx=*ax;
	int by=*ay;
	int bz=*az;
	if(ocnt>0)
	{
		*ax=oax+(bx-oax)*0.1;
		*ay=oay+(by-oay)*0.1;
		*az=oaz+(bz-oaz)*0.1;
	}
	oax=*ax;
	oay=*ay;
	oaz=*az;
	ocnt++;
	return 0;
}
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
void Maemo_Orientation() {
	// Since accelerometer only updates 30 times per second, and we don't need realtime, track changes every 4 frames //
	accel_update++;
	if ( accel_update & 3 )
		return;
	
	// Store last accelerometer data //
	oldaccel_x = accel_x;
	oldaccel_y = accel_y;
	oldaccel_z = accel_z;		
	
	// Get Latest Data //
	int ax, ay, az;
	liqaccel_read( &ax, &ay, &az );

//	accel_x = (float)ax / 1000.0f;
//	accel_y = (float)ay / 1000.0f;
//	accel_z = (float)az / 1000.0f;

	accel_x = -(float)ay / 1000.0f;
	accel_y = (float)ax / 1000.0f;
	accel_z = (float)az / 1000.0f;

	
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
/*
#include <libosso.h>

int screen_light_update = 0;

void Maemo_KeepScreenOn() {
	screen_light_update++;
	if ( screen_light_update & 1023 )
		return;

	extern osso_context_t *osso_context;
	osso_display_state_on( osso_context );
}
*/
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MAEMO //
// - ------------------------------------------------------------------------------------------ - //
