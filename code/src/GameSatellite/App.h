// - ------------------------------------------------------------------------------------------ - //
#ifndef __SAT_APP_H__
#define __SAT_APP_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>

#include <Net/Net.h>
#include <Net/NetGet.h>

#include <NetAdapter/NetAdapter.h>
// - ------------------------------------------------------------------------------------------ - //
#include <enet/enet.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Sat/SatGeoData.h>

#include <Screen/Screen.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_SERVER
#include <Mongoose/mongoose.h>
#endif // PRODUCT_SERVER //
// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cApp {
public: // Class Helpers //
	typedef cApp thistype;
	inline void* GetThis() { return this; }

public:
	class cSettings {
	public:
		int Port;
		int WebServerPort;
	
	public:
		cSettings() :
			Port( 10240 ),
			WebServerPort( 10080 )
		{
			Load();
		}
		
		void Load() {
		}

		void Save() {
		}
	} Settings;
	
	// Not settings //

	pNetAdapterInfo* Adapters;
	const NetAdapterInfo* Adapter;
	
	TFunctor<SatGeoData>* MyGeo;

#ifdef PRODUCT_SERVER
public: // WebServer -------------------------------------------------------------------------- - //
	struct mg_context* WebServer_ctx;
	int WebServer_Requests;
	
	void WebServer_Start();
	void WebServer_Stop();
	
	void* WebServer_Callback( mg_event event, mg_connection *conn );
	static void* stWebServer_Callback( mg_event event, mg_connection *conn );

public: // Matchmaking ------------------------------------------------------------------------ - //

public: // Server ----------------------------------------------------------------------------- - //
	ENetHost* Server_NetHost;
	
	enum {
		CH_MESSAGE = 0,		// Messages Channel. Chat, Broadcasts, etc // 
		CH_DATA,
		CH_OUTSIDERS,		// Outside Players pinging server for latency //
		
		CH_MAX				// Number of Channels //
	};
	
	enum {
		MSG_PING = 1,		// Ping Message, for checking how responsive a server is //
		MSG_PONG,			// Ping Response Message //
		
	};

	int Server_Start();
	void Server_Stop();
	void Server_Poll( const int TimeInMS = 0 );
#endif // PRODUCT_SERVER //
#ifdef PRODUCT_CLIENT
public: // Client ----------------------------------------------------------------------------- - //
	ENetHost* Client_NetHost;
	ENetPeer* Client_Peer;
	
	enum {
		CH_MESSAGE = 0,		// Messages Channel. Chat, Broadcasts, etc // 
		CH_DATA,
		CH_OUTSIDERS,		// Outside Players pinging server for latency //
		
		CH_MAX				// Number of Channels //
	};

	int Client_Start();
	void Client_Stop();
	bool Client_Connect();
#endif // PRODUCT_CLIENT //
	
public: // Main ------------------------------------------------------------------------------- - //
	cApp();
	~cApp();

#ifdef PRODUCT_SERVER
	int operator()( );
#endif // PRODUCT_SERVER //

#ifdef PRODUCT_CLIENT
	void Step();
	void Draw( Screen::cNative& Native );
#endif // PRODUCT_CLIENT //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SAT_APP_H__ //
// - ------------------------------------------------------------------------------------------ - //
