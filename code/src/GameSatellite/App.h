// - ------------------------------------------------------------------------------------------ - //
#ifndef __SAT_APP_H__
#define __SAT_APP_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include "Util/sprintf.h"

#include "Net/Net.h"
#include "Net/NetGet.h"

#include "NetAdapter/NetAdapter.h"
// - ------------------------------------------------------------------------------------------ - //
#include <enet/enet.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Util/Functor.h"
#include "SatGeoData.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cApp {
public: // Class Helpers //
	typedef cApp thistype;
	inline void* GetThis() { return this; }

public:
	class cSettings {
	public:
	
	public:
		cSettings()
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

public: // Matchmaking ------------------------------------------------------------------------ - //

public: // Client ----------------------------------------------------------------------------- - //
	ENetHost* Client_NetHost;
	ENetPeer* Client_Peer;
	
	enum {
		CH_MESSAGE = 0,		// Messages Channel. Chat, Broadcasts, etc // 
		CH_DATA,
		
		CH_MAX				// Number of Channels //
	};

	int Client_Start();
	void Client_Stop();
	bool Client_Connect();
	
public: // Main ------------------------------------------------------------------------------- - //
	cApp();
	~cApp();
	int operator()( );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __SAT_APP_H__ //
// - ------------------------------------------------------------------------------------------ - //
