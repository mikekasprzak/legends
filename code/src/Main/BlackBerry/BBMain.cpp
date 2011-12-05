
#include <stdio.h>
#include <System/Path.h>

extern int FPS_Counter;
int FPS_Counter = 0;

extern void SkipTime();
void SkipTime() {
	
}
/*
 * Copyright (c) 2011 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <screen/screen.h>
#include <bps/navigator.h>
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "bbutil.h"


void handleScreenEvent(bps_event_t *event)
{
    screen_event_t screen_event = screen_event_get_event(event);

    int screen_val;
    screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TYPE, &screen_val);

    switch (screen_val) {
    case SCREEN_EVENT_MTOUCH_TOUCH:
    case SCREEN_EVENT_MTOUCH_MOVE:
    case SCREEN_EVENT_MTOUCH_RELEASE:
        break;
    }
}

int initialize()
{
	EGLint surface_width, surface_height;

	eglQuerySurface(egl_disp, egl_surf, EGL_WIDTH, &surface_width);
	EGLint err = eglGetError();
	if (err != 0x3000) {
		return EXIT_FAILURE;
	}

	eglQuerySurface(egl_disp, egl_surf, EGL_HEIGHT, &surface_height);
	err = eglGetError();
	if (err != 0x3000) {
		return EXIT_FAILURE;
	}
	
	extern void Simple_Init( int Width, int Height );
	Simple_Init( surface_width, surface_height );

	return EXIT_SUCCESS;
}

void render()
{
	extern void Simple_Step();
	Simple_Step();

	extern void Simple_Draw();
	Simple_Draw();

    //Use utility code to update the screen
    bbutil_swap();
}

int main(int argc, char *argv[]) {
	extern char AppBaseDir[];
	gelGetContentPath( AppBaseDir, 2048 );
	extern char AppSaveDir[];
	gelGetStoragePath( AppSaveDir, 2048 );
	
	printf("OH SHIT: %s\n", AppBaseDir);
	
	extern int LogLevel;
	LogLevel = 3;

	int rc;
	int exit_application = 0;
	static screen_context_t screen_cxt;

	//Create a screen context that will be used to create an EGL surface to to receive libscreen events
	screen_create_context(&screen_cxt, 0);

	//Initialize BPS library
	bps_initialize();

	//Use utility code to initialize EGL in landscape orientation
	if (EXIT_SUCCESS != bbutil_init_egl(screen_cxt, GL_ES_2, LANDSCAPE)) {
		fprintf(stderr, "bbutil_init_egl failed\n");
		bbutil_terminate();
		screen_destroy_context(screen_cxt);
		return 0;
	}

	//Initialize application logic
	if (EXIT_SUCCESS != initialize()) {
		fprintf(stderr, "initialize failed\n");
		bbutil_terminate();
		screen_destroy_context(screen_cxt);
		return 0;
	}

	//Signal BPS library that navigator and screen events will be requested
	if (BPS_SUCCESS != screen_request_events(screen_cxt)) {
		fprintf(stderr, "screen_request_events failed\n");
		bbutil_terminate();
		screen_destroy_context(screen_cxt);
		return 0;
	}

	if (BPS_SUCCESS != navigator_request_events(0)) {
		fprintf(stderr, "navigator_request_events failed\n");
		bbutil_terminate();
		screen_destroy_context(screen_cxt);
		return 0;
	}

	//Signal BPS library that navigator orientation is not to be locked
	if (BPS_SUCCESS != navigator_rotation_lock(false)) {
		fprintf(stderr, "navigator_rotation_lock failed\n");
		bbutil_terminate();
		screen_destroy_context(screen_cxt);
		return 0;
	}

	while (!exit_application) {
		//Request and process BPS next available event
		bps_event_t *event = NULL;
		rc = bps_get_event(&event, 0);
		assert(rc == BPS_SUCCESS);

		if (event) {
			int domain = bps_event_get_domain(event);

			if (domain == screen_get_domain()) {
				handleScreenEvent(event);
			} else if ((domain == navigator_get_domain())
					&& (NAVIGATOR_EXIT == bps_event_get_code(event))) {
				exit_application = 1;
			}
		}

		render();
	}

	//Stop requesting events from libscreen
	screen_stop_events(screen_cxt);
	
	extern void Simple_Exit();
	Simple_Exit();

	//Shut down BPS library for this process
	bps_shutdown();

	//Use utility code to terminate EGL setup
	bbutil_terminate();

	//Destroy libscreen context
	screen_destroy_context(screen_cxt);
	return 0;
}
