// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>

#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
int cApp::Client_Start() {
	if ( enet_initialize() != 0 ) {
		Log("Error Initializing ENet");
		return 1;	
	}		
	
	Client_NetHost = enet_host_create( 
		NULL,	 	// Address to bind to //
		1, 			// Clients and/or outgoing connections //
		CH_MAX, 	// Channels //
		0, 			// Incoming Bandwitdth (0=no limit) //
		0 			// Outgoing Bandwidth (0=no limit) //
		);

	return (Client_NetHost == 0) ? 1 : 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Client_Stop() {
	enet_host_destroy( Client_NetHost );
	
	enet_deinitialize();
}
// - ------------------------------------------------------------------------------------------ - //
bool cApp::Client_Connect() {
	ENetAddress Address;
	ENetEvent Event;

	enet_address_set_host( &Address, "foagies.mooo.com" );
	Address.port = 10240;

	Client_Peer = enet_host_connect(
		Client_NetHost, 
		&Address, 
		CH_MAX,
		0
		); 	

	if ( Client_Peer == NULL ) {
		Log("ERROR: No Available Peers"); // WTF //
		return false;
	}
	
	if ( enet_host_service( Client_NetHost, &Event, 5000 ) > 0 && Event.type == ENET_EVENT_TYPE_CONNECT ) {
		Log( "Connection Success!" );
		return true;
	}
	else {
		enet_peer_reset( Client_Peer );
		
		Log( "Connection Failed!" );
		return false;
	}
}
// - ------------------------------------------------------------------------------------------ - //
