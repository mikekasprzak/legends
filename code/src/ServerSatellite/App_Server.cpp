// - ------------------------------------------------------------------------------------------ - //
#include "Text/Out.h"

#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
int cApp::Server_Start() {
	if ( enet_initialize() != 0 ) {
		Out("Error Initializing ENet");
		return 1;	
	}		
	
	ENetAddress Address;
	Address.host = ENET_HOST_ANY;
	Address.port = Settings.Port;

	Server_NetHost = enet_host_create( 
		&Address, 	// Address to bind to //
		32, 		// Clients and/or outgoing connections //
		CH_MAX, 	// Channels //
		0, 			// Incoming Bandwitdth (0=no limit) //
		0 			// Outgoing Bandwidth (0=no limit) //
		);

	Out( "* %s Started on %i.%i.%i.%i %i\n", 
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
void cApp::Server_Poll( const int TimeInMS ) {
	ENetEvent Event;
	
	while ( enet_host_service( Server_NetHost, &Event, TimeInMS ) > 0 ) {
		switch ( Event.type ) {
			case ENET_EVENT_TYPE_CONNECT: {
				Out("* Connection!");
				break;
			}
	        case ENET_EVENT_TYPE_RECEIVE: {
				Out("* PACKET!");
				
				if ( Event.channelID == CH_OUTSIDERS ) {
					int* Data = (int*)Event.packet->data;
					if ( Data[0] == 1 ) {
						Out("* Pinged... sending Pong" );
						
						int Response[] = { 2 };
						ENetPacket* Packet = enet_packet_create( &Response, sizeof(Response), ENET_PACKET_FLAG_UNSEQUENCED );
						
						enet_peer_send( Event.peer, CH_OUTSIDERS, Packet );
						enet_host_flush( Server_NetHost );
					}
					else {
						Out("Hmm");
					}
				}
				else {
					Out("Uh");
				}
	        	
	            break;
	        }
			case ENET_EVENT_TYPE_DISCONNECT: {
				Out("* Disconnected");
				break;
			}
			default: {
				Out("* WTF!");
				break;
			}
		}					
	}
}
// - ------------------------------------------------------------------------------------------ - //
