// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include "Util/sprintf.h"

#include "App.h"

#include <Text/Out.h>
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

	OutInit();
	
	Out( "This is shitty 'eh" );
	OutColor( OUT_RED );
	Out( "This is shittier" );
	OutColor( OUT_INV_RED );
	Out( "This is shittier" );
	OutColor( OUT_LIGHT_RED );
	Out( "This is shittier" );
	OutColor( OUT_INV_LIGHT_RED );
	Out( "This is shittier" );
	OutResetColor();
	Out( "Indeed" );
	
	//OutFlush();
	
	// Do Stuff //
	int TheChar;
	while ( (TheChar = GetCh()) != 27 ) {
		Server_Poll();
//		fflush(0);
//		getchar(); // Wait until user hits "enter"
	}
	
	OutExit();
	
	// Cleanup //
	Server_Stop();
	WebServer_Stop();

	// Finished //
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

