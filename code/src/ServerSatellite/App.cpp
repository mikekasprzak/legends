// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include "Util/sprintf.h"

#include "App.h"

#undef MOUSE_MOVED
#include <curses.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cApp::cApp() {
	MyGeo = new TFunctor<SatGeoData>();	// Start Thread //
	
	Adapters = new_pNetAdapterInfo();
	Adapter = get_primary_pNetAdapterInfo( Adapters );
	
	Log( "%s: %s (%s) -- %s [%s]", Adapter->Name, Adapter->IP, Adapter->MAC, Adapter->NetMask, Adapter->Broadcast );
	
}
// - ------------------------------------------------------------------------------------------ - //
cApp::~cApp() {
	delete_pNetAdapterInfo( Adapters );

	delete( MyGeo );
}
// - ------------------------------------------------------------------------------------------ - //
int cApp::operator()( ) {
	// Wait for threads to finish //
	MyGeo->join();
			
	// Init //
	WebServer_Start();
	Server_Start();
	
//	cbreak();
//	halfdelay(1);
//	noecho();
//	refresh();

// This doesn't work without a Window //

//    filter();
    initscr();
//    newterm(NULL,stdout,stdin);
    cbreak();
	halfdelay(1);
    noecho();
//    keypad(stdscr, TRUE);
	
	// Do Stuff //
	int TheChar;
	while ( (TheChar = getch()) != 27 ) {
		Server_Poll();
//		fflush(0);
//		getchar(); // Wait until user hits "enter"
	}
	
	// Cleanup //
	Server_Stop();
	WebServer_Stop();

	// Finished //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

