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
	
	void WebServer_Start() {
		WebServer_Requests = 0;
		
		char PortString[7];
		safe_sprintf( PortString, sizeof(PortString), "%i", Settings.Port );
	
		const char *options[] = {
			"listening_ports", PortString, 
			NULL
		};
		
		WebServer_ctx = mg_start( &stWebServer_Callback, this, options );
		Log( "Webserver started on Port %s.", PortString ); 
		Log( "Visit http://%s:%s in a web browser to edit settings.", Adapter->IP, PortString );
	}
	
	void WebServer_Stop() {
		mg_stop( WebServer_ctx );
	}
	
	void* WebServer_Callback( mg_event event, mg_connection *conn ) {
		const mg_request_info* request_info = mg_get_request_info(conn);
		
		WebServer_Requests++;
//		Log( "* %i %i", Requests, event );
		
		// Standard Web Requests give me 2 messages:
		//   1. MG_NEW_REQUEST (0)
		//   2. MG_REQUEST_COMPLETE (1)
		
		if (event == MG_NEW_REQUEST) {
			const unsigned char* IP = (const unsigned char*)&request_info->remote_ip;
			
			char content[1024];
			int content_length = safe_sprintf(
				content, sizeof(content),
				"Hello from %s (Internet: %s, LAN: %s | %s)!\n\nYou are %i.%i.%i.%i:%i -- %s",
				MyGeo->Country, MyGeo->IP,
				Adapter->IP, Adapter->NetMask,
				(int)IP[3],(int)IP[2],(int)IP[1],(int)IP[0],
				request_info->remote_port,
				request_info->query_string
				);
	
			mg_printf(conn,
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: text/plain\r\n"
				"Content-Length: %d\r\n" // Always set Content-Length
				"\r\n"
				"%s",
				content_length, content);
			
			// Mark as processed
			return (void*)"";
		}
		else if ( event == MG_REQUEST_COMPLETE ) {
			// Do nothing. Be happy. //
			return NULL;
		}
		else {
			return NULL;
		}
	}	
	
	static void* stWebServer_Callback( mg_event event, mg_connection *conn ) {
		cApp* th = (cApp*)mg_get_user_data(conn);
		return th->WebServer_Callback( event, conn );
	}

public: // Matchmaking //
	

public:
	cApp() {
		MyGeo = new TFunctor<SatGeoData>();	// Start Thread //
		
		Adapters = new_pNetAdapterInfo();
		Adapter = get_primary_pNetAdapterInfo( Adapters );
		
		Log( "%s: %s (%s) -- %s [%s]", Adapter->Name, Adapter->IP, Adapter->MAC, Adapter->NetMask, Adapter->Broadcast );
		
	}
	
	~cApp() {
		delete_pNetAdapterInfo( Adapters );

		delete( MyGeo );
	}
	
	int operator()( ) {
		// Wait for threads to finish //
		MyGeo->join();
				
		// Init //
		WebServer_Start();
		
		// Do Stuff //
		{
			fflush(0);
			getchar(); // Wait until user hits "enter"
		}
		
		// Cleanup //		
		WebServer_Stop();

		// Finished //
		return 0;
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	gelNetInit();
	
	// **** //
	
	extern void SatBodyTest();
	SatBodyTest();
	
	// **** //

	{
		cApp App;
		App();
	}

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
