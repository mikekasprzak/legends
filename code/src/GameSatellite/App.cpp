// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include "Util/safe_sprintf.h"

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
void cApp::Draw( ) {
}
// - ------------------------------------------------------------------------------------------ - //

