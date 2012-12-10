// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include <Util/safe_sprintf.h>

#include "App.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cApp::cApp() {
	MyGeo = new TFunctor<SatGeoData>();	// Start Thread //
	
	Adapters = new_pNetAdapterInfo();
	Adapter = get_primary_pNetAdapterInfo( Adapters );
	
	Log( "%s: %s (%s) -- %s [%s]", Adapter->Name, Adapter->IP, Adapter->MAC, Adapter->NetMask, Adapter->Broadcast );

	// Wait for threads to finish //
	MyGeo->join();
			
	// Init //
	Client_Start();
	Client_Connect();

}
// - ------------------------------------------------------------------------------------------ - //
cApp::~cApp() {
	// Cleanup //
	Client_Stop();

	delete_pNetAdapterInfo( Adapters );

	delete( MyGeo );
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Step( ) {
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Draw( Screen::cNative& Native ) {
	glMatrixMode( GL_PROJECTION | GL_MODELVIEW );
	glLoadIdentity();
	
	float NewSize = 320.0f * Native.GetAspectRatio();
	glOrtho(
		-320,320,
		NewSize,-NewSize,
		0,1
		);

	float x = 0;
	float y = 0;
	static float r = 0;
	r += 0.5f;
    // Draw //
    glClearColor(0,0,0,1); // Use OpenGL commands, see the OpenGL reference.
    glClear(GL_COLOR_BUFFER_BIT); // clearing screen
    glRotatef(r,0.0f,0.0f,1.0f);  // rotating everything
    glBegin(GL_QUADS); // drawing a multicolored triangle
		glColor3f(1.0f,0.0f,0.0f); glVertex2f(x-90.0f, y+90.0f);
		glColor3f(1.0f,1.0f,1.0f); glVertex2f(x+90.0f, y+90.0f);
		glColor3f(0.0f,1.0f,0.0f); glVertex2f(x+90.0f, y-90.0f);
		glColor3f(0.0f,0.0f,1.0f); glVertex2f(x-90.0f, y-90.0f);
    glEnd();
}
// - ------------------------------------------------------------------------------------------ - //

