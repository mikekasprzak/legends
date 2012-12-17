// - ------------------------------------------------------------------------------------------ - //
#ifndef __SAT_APP_H__
#define __SAT_APP_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Net/Net.h>
#include <Net/NetGet.h>

#include <Mongoose/mongoose.h>

#include <cJSON/cJSON.h>
#include <Core/Data_MD5.h>

#include <NetAdapter/NetAdapter.h>
// - ------------------------------------------------------------------------------------------ - //
#include <enet/enet.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Sat/SatGeoData.h>
#include <Util/Functor.h>
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
		
public: // Main ------------------------------------------------------------------------------- - //
	cApp();
	~cApp();
	int operator()( );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SAT_APP_H__ //
// - ------------------------------------------------------------------------------------------ - //