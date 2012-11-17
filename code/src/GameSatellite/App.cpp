// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include "Util/sprintf.h"

#include "App.h"
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
	Client_Start();
	Client_Connect();
	
	// Do Stuff //
	{
		fflush(0);
		getchar(); // Wait until user hits "enter"
	}
	
	// Cleanup //
	Client_Stop();

	// Finished //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

