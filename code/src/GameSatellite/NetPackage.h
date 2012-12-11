// - ------------------------------------------------------------------------------------------ - //
// A NetPackage is like a Network Packet (eventually, it becomes one). //
// It's a collection of messages, and supports combining reliable and //
// unreliable messages in to a single package (of messages). //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __NET_NETPACKAGE_H__
#define __NET_NETPACKAGE_H__
// - ------------------------------------------------------------------------------------------ - //
enum {	// Package Types //
	NP_UNRELIABLE = 0x0000,
	NP_RELIABLE = 0x8000,

	NP_EOF = 0,							// Special code for no more chunks (Type=0 and Size=0) //
	NP_RECEIPT = 0 | NP_RELIABLE,		// Special code for receipts (also reliable) //
	NP_MESSAGE = 1 | NP_RELIABLE,		// Chat Messages //
	
	NP_BASE = 2,						// Base ID to use for new message codes //
	NP_RELIABLE_BASE = 2 | NP_RELIABLE,	// Base ID to use for new reliable message codes //
};
// - ------------------------------------------------------------------------------------------ - //
struct cNP_Header {
	unsigned short Type;				// One of the above enums, or custom (NP_BASE+value) //
	unsigned short Size;				// In Bytes //
};
// - ------------------------------------------------------------------------------------------ - //
struct cNP_ReliableHeader {
	unsigned short Type;				// One of the above enums, or custom (NP_RELIABLE_BASE+value) //
	unsigned short Size;				// In Bytes //
	unsigned short UID;					// Unique Packet ID (Just a local incrementing number) //
};
// - ------------------------------------------------------------------------------------------ - //
struct cNP_Chunk {
	cNP_Header Header;
	char Data[0];

	inline const size_t Size() const {
		return Header.Size;
	}
	inline const size_t SizeOf() const {
		return Header.Size;				// Always in Bytes //
	}
};
// - ------------------------------------------------------------------------------------------ - //
struct cNP_ReliableChunk {
	cNP_ReliableHeader Header;
	char Data[0];

	inline const size_t Size() const {
		return Header.Size;
	}
	inline const size_t SizeOf() const {
		return Header.Size;				// Always in Bytes //
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Receipts are confirmations that a reliable packet was recieved //
struct cNP_ReceiptChunk {
	cNP_ReliableHeader Header;
	unsigned short Data[0];				// UID //
	
	inline const size_t Size() const {
		return Header.Size >> 1;		// We know the correct Data Size! //
	}
	inline const size_t SizeOf() const {
		return Header.Size;				// Always in Bytes //
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A chunked data format that is built by Clients and Servers, then sent over some transport //
struct cNetPackage {
	static unsigned short _NextUID;
	inline static const unsigned short NextUID() {
		return _NextUID++;		// TODO: Thread locking? So long as we package in 1 thread we're ok
	}
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __NET_NETPACKAGE_H__ //
// - ------------------------------------------------------------------------------------------ - //
