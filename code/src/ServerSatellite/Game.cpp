
#include "../GameSatellite/SatBody/SatBody.h"

extern void SatBodyTest();
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
