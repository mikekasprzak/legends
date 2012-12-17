// - ------------------------------------------------------------------------------------------ - //
#include <vnet/vnet.h>
// - ------------------------------------------------------------------------------------------ - //
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/event.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
typedef evutil_socket_t VNetSocket;		// ENET: SOCKET on Windows, int on Unix //
// - ------------------------------------------------------------------------------------------ - //
struct VNetPeer {
	struct VNetHost* host;
};
// - ------------------------------------------------------------------------------------------ - //
struct VNetHost {
	VNetSocket socket;
	
	event_base* base;
	bufferevent* bev;
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Utility Functions //
// - ------------------------------------------------------------------------------------------ - //
inline void vn_Zero( void* Dest, size_t Size ) {
	memset( Dest, 0, Size );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// API Init //
// - ------------------------------------------------------------------------------------------ - //
VNET_API int vnet_initialize( void ) {
	// TODO: WinSock2 //
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
VNET_API void vnet_deinitialize( void ) {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// bev == bufferevent, cb == callback //
// - ------------------------------------------------------------------------------------------ - //
void bevcb( bufferevent* bev, short events, void *ptr ) {
	if (events & BEV_EVENT_CONNECTED) {
		/*	We're connected to 127.0.0.1:8080.   Ordinarily we'd do
			something here, like start reading or writing. */
	} 
	else if (events & BEV_EVENT_ERROR) {
		/* An error occured while connecting. */
		if (events & BEV_EVENT_READING) {
		}
		else if (events & BEV_EVENT_WRITING) {
		}
	}
	else if (events & BEV_EVENT_TIMEOUT) {
		/* A user timeout occured */
	}
	else if (events & BEV_EVENT_EOF) {
		/* EOF reached (?) */
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
VNET_API VNetHost*	vnet_host_create( const VNetAddress* address, size_t peerCount, size_t channelLimit, vnet_uint32 incomingBandwidth, vnet_uint32 outgoingBandwidth ) {
	VNetHost* host;
//	ENetPeer* currentPeer;
	
	host = new VNetHost;
	vn_Zero( host, sizeof(VNetHost) );
	
	host->base = event_base_new();
//	host->socket
//	evutil_make_socket_nonblocking( 
	host->bev = bufferevent_socket_new( host->base, -1, BEV_OPT_CLOSE_ON_FREE );
	bufferevent_setcb( host->bev, NULL, NULL, bevcb, NULL );
	
	// Bleh, this is a lot of work. //
	// TBH, I don't really fully understand enet and sockets anyway. libevent is designed
	// to wrap typical socket programming, so you still need to know how typical sockets
	// work to use it. I do know this, but I wont claim to know it well.
	
	// The solution of vnet was to wrap how enet works, and I still think this is a good idea, but
	// it may be a better idea to wrap a generic networking interface. Not how it works per se, but
	// more how it's used. Treat enet as a transport layer, and simplify my direct interface to it.
	// Once that's in place, I build, send, and recieve packets by whatever transport layer I have
	// available to me. Depending on the port, a transporter is used to send and recieve these msgs.
	// ENet is still a relatively low level "how" layer. I love its concept of channels. But I will
	// not be sending ENet packets, but game packets. 
	
	return host;
}
// - ------------------------------------------------------------------------------------------ - //
VNET_API void		vnet_host_destroy( VNetHost* host ) {
	bufferevent_free( host->bev );
	
	evutil_closesocket( host->socket );
	event_base_free( host->base );
	
	delete host;
}
// - ------------------------------------------------------------------------------------------ - //
