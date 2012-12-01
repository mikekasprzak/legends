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

//	enet_address_set_host( &Address, "127.0.0.1" );
//	enet_address_set_host( &Address, "192.168.1.111" );
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
		
		int Data[] = { 1 };
		
		Log( "Sending Ping..." );
		ENetPacket* Packet = enet_packet_create( &Data, sizeof(Data), ENET_PACKET_FLAG_UNSEQUENCED );
		enet_uint32 TimeStamp = enet_time_get();
		if ( int Error = enet_peer_send( Client_Peer, CH_OUTSIDERS, Packet ) ) {
			Log("* Send Error: %i", Error);
		}
		//enet_host_flush( Client_NetHost ); // enet_host_service() 
		
		ENetEvent Event;
		while( enet_host_service( Client_NetHost, &Event, 1000 ) > 0 ) {
			switch( Event.type ) {
				case ENET_EVENT_TYPE_RECEIVE: {
					enet_uint32 TimeStamp2 = enet_time_get();
					
					if ( Event.channelID == CH_OUTSIDERS ) {
						int* Data = (int*)Event.packet->data;
						if ( Data[0] == 2 ) {
							Log( "Ping Recieved in %i ms", (int)(TimeStamp2-TimeStamp) );
						}
						else {
							Log( "What?" );
						}
					}
					else {
						Log( "Who?" );
					}
					break;
				}
				default: {
					break;
				}
			};	
			// ENET_EVENT_TYPE_CONNECT, ENET_EVENT_TYPE_DISCONNECT (also NONE but unused)
		}
		enet_peer_disconnect( Client_Peer, 2 );
		Log( "Done." );
		
		return true;
	}
	else {
		enet_peer_reset( Client_Peer );
		
		Log( "Connection Failed!" );
		return false;
	}
}
// - ------------------------------------------------------------------------------------------ - //
