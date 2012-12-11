
// ENET Supports:
//   Reliable Sequenced     -- ENET_PACKET_FLAG_RELIABLE
//   Unreliable Sequenced   -- null (even though there's a ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE, that's internal)
//   Unreliable Unsequenced -- ENET_PACKET_FLAG_UNSEQUENCED

// Unreliable Sequenced means throw away packets that are older than the last accepted one //
// Unreliable Unsequenced means fuck you ENet

// TCP *ONLY* supports Reliable Sequenced
