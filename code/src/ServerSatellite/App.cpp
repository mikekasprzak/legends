// - ------------------------------------------------------------------------------------------ - //
#include "App.h"

#include <Timer/Timer.h>
#include <Debug/Log.h>
#include <Util/safe_sprintf.h>

#include "Text/Out.h"
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
	
	// Do Stuff //
	int TheChar;
	while ( (TheChar = GetCh()) != 27 ) {
		Server_Poll(50); // Time in MS //
		//Wait(50); // 20 times per second //
	}
		
	// Cleanup //
	Server_Stop();
	WebServer_Stop();

	// Finished //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

