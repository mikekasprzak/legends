// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
#include "Util/sprintf.h"

#include "Net/Net.h"
#include "Net/NetGet.h"

#include <Mongoose/mongoose.h>

#include <cJSON/cJSON.h>
#include <Core/Data_MD5.h>

#include "NetAdapter/NetAdapter.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Util/Functor.h"
#include "SatGeoData.h"
// - ------------------------------------------------------------------------------------------ - //

class cApp {
public: // Class Helpers //
	typedef cApp thistype;
	inline void* GetThis() { return this; }

public:
	class cSettings {
	public:
		int Port;
	
	public:
		cSettings() :
			Port( 10080 )
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

public: // Matchmaking //
	

public:
	cApp();
	~cApp();
	int operator()( );
};
// - ------------------------------------------------------------------------------------------ - //

