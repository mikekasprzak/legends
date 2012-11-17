// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>

#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
int cApp::Server_Start() {
	if ( enet_initialize() != 0 ) {
		Log("Error Initializing ENet");
		return 1;	
	}		
	
	ENetAddress Address;
	Address.host = ENET_HOST_ANY;
	Address.port = Settings.Port;

	Server_NetHost = enet_host_create( 
		&Address, 	// Address to bind to //
		32, 		// Clients and/or outgoing connections //
		2, 			// Channels (2 means 0,1) //
		0, 			// Incoming Bandwitdth (0=no limit) //
		0 			// Outgoing Bandwidth (0=no limit) //
		);

	Log( "* %s Started on %i.%i.%i.%i %i\n", 
		Server_NetHost ? "Server":"Client",
		(Address.host>>0)&255, 
		(Address.host>>8)&255, 
		(Address.host>>16)&255, 
		(Address.host>>24)&255, 
		Address.port );
		
	return (Server_NetHost == 0) ? 1 : 0;
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Server_Stop() {
	enet_host_destroy( Server_NetHost );
	
	enet_deinitialize();
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Server_Poll() {
	ENetEvent NetEvent;
	
	while ( enet_host_service( Server_NetHost, &NetEvent, 0 ) > 0 ) {
		switch ( NetEvent.type ) {
			case ENET_EVENT_TYPE_CONNECT: {
				Log("* Connection!");
				break;
			}
	        case ENET_EVENT_TYPE_RECEIVE: {
				Log("* PACKET!");
	        	
	            break;
	        }
			case ENET_EVENT_TYPE_DISCONNECT: {
				Log("* Disconnected");
				break;
			}
			default: {
				Log("* WTF!");
				break;
			}
		}					
	}
}
// - ------------------------------------------------------------------------------------------ - //
