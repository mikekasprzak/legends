// - ------------------------------------------------------------------------------------------ - //
#ifndef __VNET_VNET_H__
#define __VNET_VNET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include "types.h"
// - ------------------------------------------------------------------------------------------ - //
enum {
   VNET_HOST_ANY       = 0,            /* specifies the default server host */
   VNET_PORT_ANY       = 0             /* specifies that a port should be automatically chosen */
};
// - ------------------------------------------------------------------------------------------ - //
struct VNetAddress {
	vnet_uint32 host;
	vnet_uint16 port;
};
// - ------------------------------------------------------------------------------------------ - //
// Defined inside vnet.cpp, so you should only ever use pointers to them //
struct VNetSocketType;
struct VNetSocketWait;
struct VNetSocketOption;
//struct VNetAddress; 		// Defined Above //
struct VNetPacketFlag;
struct VNetPacket;
struct VNetAcknowledgement;
struct VNetOutgoingCommand;
struct VNetIncomingCommand;
struct VNetPeerState;
struct VNetChannel;
struct VNetPeer;
struct VNetCompressor;		// Wont do? //
struct VNetHost;
struct VNetEventType;
struct VNetEvent;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
VNET_API int vnet_initialize( void );
VNET_API void vnet_deinitialize( void );
// - ------------------------------------------------------------------------------------------ - //
VNET_API VNetHost*	vnet_host_create( const VNetAddress*, size_t, size_t, vnet_uint32, vnet_uint32 );
VNET_API void		vnet_host_destroy( VNetHost* );

// - ------------------------------------------------------------------------------------------ - //
#endif // __VNET_VNET_H__ //
// - ------------------------------------------------------------------------------------------ - //
