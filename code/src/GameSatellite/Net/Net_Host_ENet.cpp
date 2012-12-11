// - ------------------------------------------------------------------------------------------ - //
// ENET Supports:
//   Reliable Sequenced     -- ENET_PACKET_FLAG_RELIABLE
//   Unreliable Sequenced   -- null (even though there's a ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE, that's internal)
//   Unreliable Unsequenced -- ENET_PACKET_FLAG_UNSEQUENCED

// Unreliable Sequenced means throw away packets that are older than the last accepted one //
// Unreliable Unsequenced means fuck you ENet

// TCP *ONLY* supports Reliable Sequenced
// - ------------------------------------------------------------------------------------------ - //
#include "Net_Host.h"
#include <enet/enet.h>
#include "../NetPackage.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Net {
// - ------------------------------------------------------------------------------------------ - //
ENetHost* Host;
ENetPeer* Peer;
bool Server = false;
// - ------------------------------------------------------------------------------------------ - //
void Host_Exit() {
	enet_deinitialize();
}
// - ------------------------------------------------------------------------------------------ - //
void Host_Init() {
	Log( "-=- Networking -=-" );
	Log( "Using ENet v%i.%i.%i", ENET_VERSION_MAJOR, ENET_VERSION_MINOR, ENET_VERSION_PATCH );
	Log( "" );
	
	if ( enet_initialize() != 0 ) {
		Log("Error Initializing ENet");
		return;// 1;	
	}
	
	atexit( Host_Exit );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Host_StartServer() {
	//Host_Init();

	ENetAddress Address;
	Address.host = ENET_HOST_ANY;
	Address.port = 10240;//Settings.Port;

	Host = enet_host_create( 
		&Address, 	// Address to bind to (NULL if a client) //
		32, 		// Clients and/or outgoing connections //
		1, 			// Channels //
		0, 			// Incoming Bandwitdth (0=no limit) //
		0 			// Outgoing Bandwidth (0=no limit) //
		);

//	Log( "* %s Started on %i.%i.%i.%i %i\n", 
//		Host ? "Server":"Client",
//		(Address.host>>0)&255, 
//		(Address.host>>8)&255, 
//		(Address.host>>16)&255, 
//		(Address.host>>24)&255, 
//		Address.port );

	Server = true;
		
	//return (Server_NetHost == 0) ? 1 : 0;
}
// - ------------------------------------------------------------------------------------------ - //
void Host_StopServer() {
	enet_host_destroy( Host );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Host_StartClient() {
	Log( "* Host_StartClient" );
	//Host_Init();

	Host = enet_host_create( 
		NULL,	 	// Address to bind to (NULL if a Client) //
		1, 			// Clients and/or outgoing connections //
		1,		 	// Channels //
		0, 			// Incoming Bandwitdth (0=no limit) //
		0 			// Outgoing Bandwidth (0=no limit) //
		);
		
	Server = false;
	
	//return (Host == 0) ? 1 : 0;
}
// - ------------------------------------------------------------------------------------------ - //
void Host_StopClient() {
	enet_host_destroy( Host );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Host_Send( cNetPackage* Package, ENetPeer* _Peer ) {
	//Log( "* Host_Send" );
//	cNP_Chunk<>* Base = (cNP_Chunk<>*)Package->Get();
//	Log( "* [%i]", Base->Header.Type );
	
	ENetPacket* Packet = enet_packet_create( Package->Get(), Package->Size(), 0 );
	enet_peer_send( _Peer, 0, Packet );	// Channel 0 //
}
// - ------------------------------------------------------------------------------------------ - //
void Host_SendPing( ENetPeer* _Peer ) {
	//Log( "* Host_SendPing" );
	cNetPackage* Package = new cNetPackage;
	Package->AddPing();
	Host_Send( Package, _Peer );
	delete Package;
}
// - ------------------------------------------------------------------------------------------ - //
void Host_SendPing() {
	Host_SendPing( Peer );
}
// - ------------------------------------------------------------------------------------------ - //
void Host_SendPong( ENetPeer* _Peer ) {
	cNetPackage* Package = new cNetPackage;
	Package->AddPong();
	Host_Send( Package, _Peer );
	delete Package;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Host_Connect() {	// Clients Only //
	Log( "* Host_Connect" );
	
	ENetAddress Address;
	enet_address_set_host( &Address, "127.0.0.1" );
//	enet_address_set_host( &Address, "192.168.1.111" );
//	enet_address_set_host( &Address, "foagies.mooo.com" );
	Address.port = 10240;

	Peer = enet_host_connect(
		Host, 		// Host Structure //
		&Address, 	// IP+Port //
		1,			// Channels //
		0
		); 	

	if ( Peer == NULL ) {
		Log( "ERROR: No Available Peers" ); // WTF //
		return;// false;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void Host_Poll( const int TimeInMS ) {		// Both //
	ENetEvent Event;
	
	while ( enet_host_service( Host, &Event, TimeInMS ) > 0 ) {
		switch ( Event.type ) {
			case ENET_EVENT_TYPE_CONNECT: {
				Log("* ENET_EVENT_TYPE_CONNECT");
				if ( !Server )
					Host_SendPing();
				break;
			}
	        case ENET_EVENT_TYPE_RECEIVE: {
				Log("* ENET_EVENT_TYPE_RECEIVE");
				
				// TODO: Confirm that we're not outside the packet size //
				cNP_Chunk<>* Base = (cNP_Chunk<>*)Event.packet->data;
				cNP_Chunk<>* Chunk = Base;
				while ( Chunk ) {
					Log( "* [%i]", Chunk->Header.Type );
					if ( Chunk->Header.Type == NP_PING ) {
						Log( "** Ping" );
						Host_SendPong( Event.peer );
					}
					else if ( Chunk->Header.Type == NP_PONG ) {
						Log( "** Pong" );
					}

					Chunk = cNetPackage::Next( Chunk );
				}
	            break;
	        }
			case ENET_EVENT_TYPE_DISCONNECT: {
				Log("* ENET_EVENT_TYPE_DISCONNECT");
				break;
			}
			case ENET_EVENT_TYPE_NONE: { 
				// No Event //
				break;	
			}
			default: {
				Log("* ENET_EVENT_TYPE_WTF!?!");
				break;
			}
		}				
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
}; // namespace Net //
// - ------------------------------------------------------------------------------------------ - //
