// - ------------------------------------------------------------------------------------------ - //
// NET ADAPTER -- A cross platform library for getting presentable Network Adapter information.
// By Mike Kasprzak -- http://www.toonormal.com http://www.sykhronics.com -- twitter @mikekasprzak
// http://code.google.com/p/net-adapter/
//
// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either
// in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and
// by any means.
// 
// In jurisdictions that recognize copyright laws, the author or authors of this software dedicate
// any and all copyright interest in the software to the public domain. We make this dedication for
// the benefit of the public at large and to the detriment of our heirs and successors. We intend 
// this dedication to be an overt act of relinquishment in perpetuity of all present and future 
// rights to this software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// 
// For more information, please refer to <http://unlicense.org/>
// - ------------------------------------------------------------------------------------------ - //
#if !defined(NET_ADAPTER_STUB)
#if defined(_WIN32) 					// Both 32bit and 64bit Windows //
// - ------------------------------------------------------------------------------------------ - //
// We need to do this ourselves: http://msdn.microsoft.com/en-us/library/aa383745.aspx
#define _WIN32_WINNT 0x0501				// Windows XP+ //
#include <winsock2.h>
#include <windows.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Iphlpapi.h>
#include <ws2tcpip.h>
// - ------------------------------------------------------------------------------------------ - //
#pragma comment(lib, "Ws2_32.lib")		// Automatically including in Visual Studio //
#pragma comment(lib, "Iphlpapi.lib")
// - ------------------------------------------------------------------------------------------ - //
#include "NetAdapter.h"
#include "NetAdapter_Internal.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define safe_sprintf sprintf_s
#else // _MSC_VER
#define safe_sprintf snprintf
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
pNetAdapterInfo* new_pNetAdapterInfo() {
	// http://msdn.microsoft.com/en-us/library/windows/desktop/aa366058%28v=vs.85%29.aspx
	ULONG IPASize = 16384;
	IP_ADAPTER_ADDRESSES* IPA = (IP_ADAPTER_ADDRESSES*)new char[IPASize];
	
	// http://msdn.microsoft.com/en-us/library/windows/desktop/aa365915%28v=vs.85%29.aspx
	GetAdaptersAddresses( /*AF_UNSPEC*/AF_INET, 0, NULL, IPA, &IPASize );

	// IP_ADAPTER_UNICAST_ADDRESS -- http://msdn.microsoft.com/en-us/library/windows/desktop/aa366066%28v=vs.85%29.aspx
	// SOCKET_ADDRESS -- http://msdn.microsoft.com/en-us/library/windows/desktop/ms740507%28v=vs.85%29.aspx
	// sockaddr/sockaddr_in -- http://msdn.microsoft.com/en-us/library/windows/desktop/ms740496%28v=vs.85%29.aspx
	// Alternatively -- http://www.beej.us/guide/bgnet/output/html/multipage/sockaddr_inman.html
	
	// Count the number Interfaces with IPv4 addresses //
	size_t IPv4Count = 0;
	for ( IP_ADAPTER_ADDRESSES* Current = IPA; Current != 0; Current = Current->Next ) {
		for ( IP_ADAPTER_UNICAST_ADDRESS* Cur = Current->FirstUnicastAddress; Cur != 0; Cur = Cur->Next ) {
			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
				// Found one! //
				IPv4Count++;
				break;
			}
		}
	}
	
	// Allocate the pNetAdapterInfo's //
	pNetAdapterInfo* Adapters = new pNetAdapterInfo[IPv4Count+1];

	// Allocate NetAdapterInfos per IP //	
	for ( size_t idx = 0; idx < IPv4Count; idx++ ) {
		Adapters[idx] = new_NetAdapterInfo();	// Internal Function //
	}
	
	Adapters[IPv4Count] = 0; // Last one a null pointer //

	
	// Iterate though and populate data //
	size_t Index = 0;
	for ( IP_ADAPTER_ADDRESSES* Current = IPA; Current != 0; Current = Current->Next ) {
		bool HasIPv4 = false;
		for ( IP_ADAPTER_UNICAST_ADDRESS* Cur = Current->FirstUnicastAddress; Cur != 0; Cur = Cur->Next ) {
			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;
				const unsigned char* DataAddr = (const unsigned char*)&(SAI->sin_addr.s_addr);

				int* IPv4 = (int*)Adapters[Index]->Data.IPv4;
				*IPv4 = *(int*)DataAddr;
								
				safe_sprintf( Adapters[Index]->IP, sizeof(Adapters[Index]->IP), "%s", inet_ntoa( SAI->sin_addr ) );
				
				HasIPv4 = true;
				break;
			}
		}
		
		// If an IP address wasn't found, then don't waste this NetAdapterInfo //
		if ( !HasIPv4 )
			continue;

		// Extract MAC //
		if ( Current->PhysicalAddressLength > 0 ) {
			memcpy( Adapters[Index]->Data.MAC, Current->PhysicalAddress, sizeof(Adapters[Index]->Data.MAC) );
			sprintf( Adapters[Index]->MAC, "%02x:%02x:%02x:%02x:%02x:%02x",
				Current->PhysicalAddress[0],
				Current->PhysicalAddress[1],
				Current->PhysicalAddress[2],
				Current->PhysicalAddress[3],
				Current->PhysicalAddress[4],
				Current->PhysicalAddress[5]
				);
		}
		
		// Extract DNS //
		for ( IP_ADAPTER_DNS_SERVER_ADDRESS* Cur = Current->FirstDnsServerAddress; Cur != 0; Cur = Cur->Next ) {
			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;								
				safe_sprintf( Adapters[Index]->DNS, sizeof(Adapters[Index]->DNS), "%s", inet_ntoa( SAI->sin_addr ) );
				break;
			}
		}

		// Anycast and Multicast address code, in case I ever decide to use them //
		
//		for ( IP_ADAPTER_ANYCAST_ADDRESS* Cur = Current->FirstAnycastAddress; Cur != 0; Cur = Cur->Next ) {
//			//printf("** %i\n", Cur->Address.lpSockaddr->sa_family);
//			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
//				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;
//				printf( "Anycast: %s\n", inet_ntoa( SAI->sin_addr ) );
//			}
//		}
		
//		for ( IP_ADAPTER_MULTICAST_ADDRESS* Cur = Current->FirstMulticastAddress; Cur != 0; Cur = Cur->Next ) {
//			//printf("*** %i\n", Cur->Address.lpSockaddr->sa_family);
//			if ( Cur->Address.lpSockaddr->sa_family == AF_INET ) {
//				sockaddr_in* SAI = (sockaddr_in*)Cur->Address.lpSockaddr;
//				printf( "Multicast: %s\n", inet_ntoa( SAI->sin_addr ) );
//			}
//		}		
		
		// Copy Name //
		{
			// The strings are stored in wchar_t's, so we copy it to our char[] //
			size_t Length = wcstombs( Adapters[Index]->Name, Current->FriendlyName, sizeof(Adapters[Index]->Name) );
		}
		
		// Copy Description //
		{
			// The strings are stored in wchar_t's, so we copy it to our char[] //
			size_t Length = wcstombs( Adapters[Index]->Description, Current->Description, sizeof(Adapters[Index]->Description) );
		}
				
		Index++;
	}	
	
	delete IPA;

	// Retrieve NetMask and Broadcast // 
	{
		SOCKET sd = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
		if ( sd != SOCKET_ERROR ) {
			DWORD BytesReturned = 0;
			INTERFACE_INFO InterfaceList[32];
			if ( WSAIoctl( sd, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList, sizeof(InterfaceList), &BytesReturned, 0, 0) != SOCKET_ERROR ) {
				size_t NumInterfaces = BytesReturned / sizeof(INTERFACE_INFO);
				for ( size_t idx = 0; idx < NumInterfaces; idx++ ) {
					for ( size_t idx2 = 0; idx2 < IPv4Count; idx2++ ) {
						u_long inFlags = InterfaceList[idx].iiFlags;
						sockaddr_in* inIP = (sockaddr_in*)&(InterfaceList[idx].iiAddress);
						sockaddr_in* inNetMask = (sockaddr_in*)&(InterfaceList[idx].iiNetmask);
						sockaddr_in* inBroadcast = (sockaddr_in*)&(InterfaceList[idx].iiBroadcastAddress);
						
						// Flags: IFF_UP, IFF_POINTTOPOINT, IFF_LOOPBACK, IFF_BROADCAST, IFF_MULTICAST //

						int* a = (int*)Adapters[idx2]->Data.IPv4;
						int* b = (int*)&(inIP->sin_addr.s_addr);
						
						if ( *a == *b ) {
							int* NetMask = (int*)Adapters[idx2]->Data.NetMask;
							*NetMask = *(int*)&(inNetMask->sin_addr.s_addr);

							safe_sprintf( 
								Adapters[idx2]->NetMask, sizeof(Adapters[idx2]->NetMask), 
								"%s", 
								inet_ntoa( inNetMask->sin_addr ) 
								);
							
							// The Broadcast Address that WinSock2 recommends is terrible. All 255's. So I calc. //
							
							int* Broadcast = (int*)Adapters[idx2]->Data.Broadcast;
							*Broadcast = ((*a) & (*NetMask)) | (~(*NetMask));
							
							unsigned char* BC = Adapters[idx2]->Data.Broadcast;

							safe_sprintf( 
								Adapters[idx2]->Broadcast, sizeof(Adapters[idx2]->Broadcast), 
								"%i.%i.%i.%i", 
								BC[0],BC[1],BC[2],BC[3]
								);        							
						}
					}
				}
			}
			closesocket( sd );
		}
	}

	return Adapters;
}
// - ------------------------------------------------------------------------------------------ - //
const NetAdapterInfo* get_primary_pNetAdapterInfo( const pNetAdapterInfo* Adapters ) {
	if ( Adapters ) {
		size_t Index = 0;
		
		while ( Adapters[Index] != 0 ) {
			if ( strcmp( Adapters[Index]->DNS, "" ) != 0 )
				return Adapters[Index];
			
			Index++;
		};
		
		// None Found //
		return 0;
	}
	else {
		// Hey you goof! You gave me a null pointer! //
		return 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // _WIN32 //
#endif // !NET_ADAPTER_STUB //
// - ------------------------------------------------------------------------------------------ - //
