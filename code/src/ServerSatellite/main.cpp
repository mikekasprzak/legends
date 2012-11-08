// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <Debug/Log.h>

#include <Mongoose/mongoose.h>

#include "NetGet.h"
#include <cJSON/cJSON.h>
#include <Core/Data_MD5.h>

#include "../GameSatellite/SatBody/SatBody.h"

#include "Task/GelTask.h"

#include "NetAdapter/NetAdapter.h"
// - ------------------------------------------------------------------------------------------ - //
#include "GELGeoData.h"
// - ------------------------------------------------------------------------------------------ - //

const NetAdapterInfo* Adapter;
GELGeoData MyGeo;

// - ------------------------------------------------------------------------------------------ - //
static void* WebServerCallback( mg_event event, mg_connection *conn ) {
	const mg_request_info* request_info = mg_get_request_info(conn);
	
	if (event == MG_NEW_REQUEST) {
		const unsigned char* IP = (const unsigned char*)&request_info->remote_ip;
		
		char content[1024];
		int content_length = snprintf(
			content, sizeof(content),
			"Hello from %s (Internet: %s, LAN: %s | %s)!\n\nYou are %i.%i.%i.%i:%i -- %s",
			MyGeo.Country, MyGeo.IP,
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
	else {
		return NULL;
	}
}
// - ------------------------------------------------------------------------------------------ - //


void SatBodyTest() {
	cSatModule Module;
//	Module.Add( SatComponent::PLANAR );
//	Module.Component->Back().Planar.Add();
//	//Module.Component->Back().Planar.Data[0];

	Module.AddPlanar( 6 );
	auto Planar = Module.Component->Back().Planar.Data;
	
	Log( "> %i", Planar->Size );

	{
		size_t idx = 0;
		
		// Front and Back //
		Planar->Data[idx++].Set( Vector3D(0,2,0), Vector3D(0,1,0) );
		Planar->Data[idx++].Set( Vector3D(0,-2,0), Vector3D(0,-1,0) );
		
		// Sides //
//		Planar->Data[idx++].Set( Vector3D(1,0,0), Vector3D(1,0,0) );
//		Planar->Data[idx++].Set( Vector3D(-1,0,0), Vector3D(-1,0,0) );
		Planar->Data[idx++].Set( Vector3D(1,0,0), Vector3D(+0.9659,+0.2588,0) );
		Planar->Data[idx++].Set( Vector3D(-1,0,0), Vector3D(-0.9659,-0.2588,0) );
		
		// Top and Bottom //
		Planar->Data[idx++].Set( Vector3D(0,0,1), Vector3D(0,0,1) );
		Planar->Data[idx++].Set( Vector3D(0,0,-1), Vector3D(0,0,-1) );
	}
	

	int Count = 0;

	// http://www.softsurfer.com/Archive/algorithm_0104/algorithm_0104B.htm#Intersection%20of%203%20Planes
	//
	// I am not 100% sure yet if this is detecting the correct number of intersections. //
	// I am going to need to see the results graphed. //
	// When I flip the sign of the Y axis in Side2 (above), I get 2 weird coords //
	// I'm expecting 2 more coords actually, but not where they were coming up. //
	//
	// Our goal is to get the points, since they help us define the convex hull. //
	// Later, take note of all points found on the specific planes. Do this during detection. //
	// Once we have all points on each plane, we can walk around the outsides to build the polygon. //
	// Once we have the polygon of each plane (face), we can eliminate duplicate vertices. //
	// Then we can build the faces by triangulating. //
	// Presto! We have build a component's mesh! //
	//
	// NOTE: Knowing edges will be helpful later when aligning components to other components. //
	//   A component may want to align to the center (fin), or above and below an edge (wings) in the normal dir. //
	for ( auto a = 0; a < Planar->Size; a++ ) {
		for ( auto b = a+1; b < Planar->Size; b++ ) {
			for ( auto c = b+1; c < Planar->Size; c++ ) {
					
				Real Intersection =
					dot( Planar->Data[a].Normal, cross( Planar->Data[b].Normal, Planar->Data[c].Normal ) );
				
				if ( !Intersection.IsZero() ) {
					// D's are the dot of the normal and point //
					Real D1 = dot( Planar->Data[a].Normal, Planar->Data[a].Point );
					Real D2 = dot( Planar->Data[b].Normal, Planar->Data[b].Point );
					Real D3 = dot( Planar->Data[c].Normal, Planar->Data[c].Point );
					
					// Multiply the D's by the cross product of the OTHER normals //
					Vector3D Result = (
						-D1 * cross( Planar->Data[b].Normal, Planar->Data[c].Normal ) +
						-D2 * cross( Planar->Data[a].Normal, Planar->Data[c].Normal ) +
						-D3 * cross( Planar->Data[a].Normal, Planar->Data[b].Normal ) 
						) /
						Intersection;
					
					Log( "* %f -- %f, %f, %f", Intersection.ToFloat(), Result.x.ToFloat(), Result.y.ToFloat(), Result.z.ToFloat() );
				}
				Count++;
			}
		}
	}
	
	Log( "> %i", Count );

	
}

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	gelNetInit();
	
	// **** //
	
	SatBodyTest();

	// **** //
	
	{
		class cShirt {
		public:
			
		};
		
		cShirt Shirt;
	}
	
	// **** //

	pNetAdapterInfo* Adapters = new_pNetAdapterInfo();
	Adapter = get_primary_pNetAdapterInfo( Adapters );

	printf( "%s: %s (%s) -- %s [%s]\n", Adapter->Name, Adapter->IP, Adapter->MAC, Adapter->NetMask, Adapter->Broadcast );
		
	MyGeo = GetMyGeoData();
	
	//printf( "ME: %s %s %f %f\n", MyGeo.IP, MyGeo.Country, MyGeo.Latitude, MyGeo.Longitude );
	
	{
		int Port = 10080;
	
		// **** //
		
		char PortString[7];
		snprintf( PortString, sizeof(PortString), "%i", Port );
	
		struct mg_context *ctx;
		const char *options[] = {"listening_ports", PortString, NULL};
		
		ctx = mg_start( &WebServerCallback, NULL, options );
		Log( "Webserver started on Port %s.", PortString ); 
		Log( "Visit http://%s:%s in a web browser to edit settings.", Adapter->IP, PortString );
		fflush(0);
		getchar(); // Wait until user hits "enter"
		mg_stop(ctx);	
	
		return 0;
	}

	// **** //

	printf( "Lets Start!\n" );
	fflush( 0 );

	// **** //
	
	if ( MyGeo.Success ) {	
		int MyPort = 10240;
		int MyVersion = 100;
		
		printf( "Sending Update Packet...\n" );
		fflush( 0 );
		
		{
			char KeyData[1024];
			snprintf( KeyData, sizeof(KeyData), "%i&%s&%i&%s",
				MyPort,
				MyGeo.IP,
				MyVersion,
				"ChupacabraSatellites"
				);
			
			MD5Hash MD5 = hash_MD5_Data( KeyData, strlen(KeyData) );	
			
			char PostData[4096];
			snprintf( PostData, sizeof(PostData), "action=update&Address=%s&Port=%i&Version=%i&Latitude=%f&Longitude=%f&Info=%s%s%s%s&Key=%s",
				MyGeo.IP,
				MyPort,
				MyVersion,
				MyGeo.Latitude,
				MyGeo.Longitude,
				"DD",
				MyGeo.Country,
				"__",
				"__",
				MD5.Text // Not actually a key //
				);
			
			printf( "To Send: %s\n", PostData );
			
			GelArray<char>* ServerData = gelNetPostText( "http://sykhronics.com/satellite/json.php", PostData );
			
			// Nothing to do with it //
			printf( "Return: \n%s\n", ServerData->Data );
			
			delete_GelArray<char>( ServerData );
		}
	}	

	// **** //

	{
//		GelArray<char>* ImageData = gelNetGetBinary( "http://www.gravatar.com/avatar/8266e6e52fe185d057db55021ac7bb86" );	
//		write_GelArray<char>( ImageData, "blah.png" );
//		delete_GelArray<char>( ImageData );
	}

	delete_pNetAdapterInfo( Adapters );

	return 0;
}

