// - ------------------------------------------------------------------------------------------ - //
// NOTES: 
// - Hey cool, I saw inside TinyXML a suggestion that a handle can be used to simplify if (0) checks.
//   My theroy, implement a member function you use for access, and check the "this" variable if it's
//   zero.  If it's zero, then assume a failed lookup occured and do nothing.
// - ------------------------------------------------------------------------------------------ - //
// - Make the F12 key dump the Game Instance (or the GameHost), causing a re-search for asset files
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include <Debug/GelDebug.h>

#include <AssetPool/AssetPool.h>
#include <Graphics/GraphicsDraw.h>
#include <Graphics/Mesh/PMEFile.h>
#include <Geometry/Projection/Projection.h>
#include <Geometry/Curve/Curve.h>

#include <Types/Set.h>
#include <Grid/Grid2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cPMEFile* Mesh;
cPMEFile* Mesh2;
// - ------------------------------------------------------------------------------------------ - //

GelAssetHandle txPlayer;
GelAssetHandle txSword;

// - ------------------------------------------------------------------------------------------ - //
void cGame::InitScripts() {
	vm_ScriptsLoaded = false;

	// TODO: Compiled Version is ".nut.cnut", or ".nut.cnut.lzma"
	// Can probably make a call to the GelDirectory and get all the .nut files //
	
	Script.push_back( vmScript( "/Main.nut" ) );
	
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::LoadScripts() {
	Log( "+ Loading Scripts..." );

	for ( int idx = 0; idx < Script.size(); idx++ ) {
		vm_CompileAndRun( AssetPool::Get( Script[idx].Handle ), Script[idx].FileName );	
	}
	vm_ScriptsLoaded = true;

	Log( "- Done Loading Scripts." );
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::ReloadScripts() {
	if ( vm_ScriptsLoaded ) {				
		Log( "+ Scanning %i Scripts for changes...", Script.size() );

		for ( int idx = 0; idx < Script.size(); idx++ ) {
			if ( AssetPool::HasChanged( Script[idx].Handle ) ) {
				Log( "* Change detected in \"%s\". Reloading...", Script[idx].FileName );
				AssetPool::Reload( Script[idx].Handle );
				vm_CompileAndRun( AssetPool::Get( Script[idx].Handle ), Script[idx].FileName );
			}
		}

		Log( "- Done Scanning Scripts." );
	}
	else {
		ELog( "Scipts haven't been loaded yet!" );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::ContentScan() {
	TIMEVALUE CurrentScan = GetTimeNow();
	TIMEVALUE Diff = SubtractTime(CurrentScan, LastContentScan);
	
	// Refresh content only if the time that has passed is greater than a small minimum of frames //
	if ( GetFrames( &Diff ) >= 4 ) {
		// Reload one of my game scripts //
		ReloadScripts();
		
		// Scan source code for changes //
		ReloadChangedTweakableValues();
		
		// Get a fresh clock, so that in case the refresh took a while, it wont again //
		LastContentScan = GetTimeNow();
	}
	else {
		VVLog("* Scanned again too soon!");
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::Init() {
	Log( "+ Start of Init..." );
	
	// Run the Experiments ... //
//	extern void ExpInit();
//	ExpInit();
//	extern void CallExp();
//	CallExp();

	// Initialize the Virtual Machine... //
	vm_Init();
	
	extern int LogLevel;
	LogLevel = 2;

	InitScripts();
	LoadScripts();
	
	Physics.Init();
	
	// Store the current clock, so the content scanner can know to disregard extra scans //
	LastContentScan = GetTimeNow();

	CameraWorldPos = Vector3D(0,0,0);
	CameraFollow = 0;
	
	// ??? //
	Vector3D RoomScale(128,128,64);

	{
		Room.push_back( new cRoom( Vector3D(0,0,0) ) );
		Room.back()->Grid = load_Grid2D<cRoom::GType>( "Content/Tests/Room01.tga" );
		new_Optimized_Triangles( Room.back()->Grid, &Room.back()->Vert, &Room.back()->Index, RoomScale );
		new_Triangles_OutlineList( Room.back()->Index, &Room.back()->OutlineIndex );
		Room.back()->PhysicsObject = Physics.AddHeightMap( Room.back()->Pos, *(Room.back()->Grid) );
		Room.back()->Color = new_GelArray<GelColor>(Room.back()->Vert->Size);
		for( int idx = 0; idx < Room.back()->Color->Size; idx++ ) {
			Grid2D<cRoom::GType>* Grid = Room.back()->Grid;
//			int Color = 255-Grid->Data[idx];//Room.back()->Vert->Data[idx].Pos.z;
			int Color = 225-(3*Room.back()->Vert->Data[idx].Pos.z);
			if ( Color > 255 )
				Color = 255;
			if ( Color < 0 )
				Color = 0;
			Room.back()->Color->Data[idx] = GEL_RGBA(Color,Color,Color,Color);
		}
	}
	{
		Room.push_back( new cRoom( Vector3D(128,256,0) ) );
		Room.back()->Grid = load_Grid2D<cRoom::GType>( "Content/Tests/Room02.tga" );
		new_Optimized_Triangles( Room.back()->Grid, &Room.back()->Vert, &Room.back()->Index, RoomScale );
		new_Triangles_OutlineList( Room.back()->Index, &Room.back()->OutlineIndex );
		Room.back()->PhysicsObject = Physics.AddHeightMap( Room.back()->Pos, *(Room.back()->Grid) );
		Room.back()->Color = new_GelArray<GelColor>(Room.back()->Vert->Size);
		for( int idx = 0; idx < Room.back()->Color->Size; idx++ ) {
			Grid2D<cRoom::GType>* Grid = Room.back()->Grid;
//			int Color = 255-Grid->Data[idx];//Room.back()->Vert->Data[idx].Pos.z;
			int Color = 225-(3*Room.back()->Vert->Data[idx].Pos.z);
			if ( Color > 255 )
				Color = 255;
			if ( Color < 0 )
				Color = 0;
			Room.back()->Color->Data[idx] = GEL_RGBA(Color,Color,Color,Color);
		}
	}
	{
		Room.push_back( new cRoom( Vector3D(128,512,0) ) );
		Room.back()->Grid = load_Grid2D<cRoom::GType>( "Content/Tests/Room03.tga" );
		new_Optimized_Triangles( Room.back()->Grid, &Room.back()->Vert, &Room.back()->Index, RoomScale );
		new_Triangles_OutlineList( Room.back()->Index, &Room.back()->OutlineIndex );
		Room.back()->PhysicsObject = Physics.AddHeightMap( Room.back()->Pos, *(Room.back()->Grid) );
		Room.back()->Color = new_GelArray<GelColor>(Room.back()->Vert->Size);
		for( int idx = 0; idx < Room.back()->Color->Size; idx++ ) {
			Grid2D<cRoom::GType>* Grid = Room.back()->Grid;
//			int Color = 255-Grid->Data[idx];//Room.back()->Vert->Data[idx].Pos.z;
			int Color = 225-(3*Room.back()->Vert->Data[idx].Pos.z);
			if ( Color > 255 )
				Color = 255;
			if ( Color < 0 )
				Color = 0;
			Room.back()->Color->Data[idx] = GEL_RGBA(Color,Color,Color,Color);
		}
	}
	{
		Room.push_back( new cRoom( Vector3D(256+128,512,0) ) );
		Room.back()->Grid = load_Grid2D<cRoom::GType>( "Content/Tests/Room04.tga" );
		new_Optimized_Triangles( Room.back()->Grid, &Room.back()->Vert, &Room.back()->Index, RoomScale );
		new_Triangles_OutlineList( Room.back()->Index, &Room.back()->OutlineIndex );
		Room.back()->PhysicsObject = Physics.AddHeightMap( Room.back()->Pos, *(Room.back()->Grid) );
		Room.back()->Color = new_GelArray<GelColor>(Room.back()->Vert->Size);
		for( int idx = 0; idx < Room.back()->Color->Size; idx++ ) {
			Grid2D<cRoom::GType>* Grid = Room.back()->Grid;
//			int Color = 255-Grid->Data[idx];//Room.back()->Vert->Data[idx].Pos.z;
			int Color = 225-(3*Room.back()->Vert->Data[idx].Pos.z);
			if ( Color > 255 )
				Color = 255;
			if ( Color < 0 )
				Color = 0;
			Room.back()->Color->Data[idx] = GEL_RGBA(Color,Color,Color,Color);
		}
	}

	Mesh = new cPMEFile( "Content/Models/Native/Monkey.pme" );
	Mesh2 = new cPMEFile();
	
	Mesh2->Import( "Content/Models/Native/Chest.3ds" );
	
	txPlayer = AssetPool::Load( "/Player01" );
	txSword = AssetPool::Load( "/Sword01" );

//	txSword = AssetPool::Load( "/Fontin_0" );

	Obj.push_back( new cObject( Vector3D(0,0,32+16), txPlayer ) );
	Obj.back()->PhysicsObject = Physics.AddBall( Obj.back()->Pos, Obj.back()->Scalar );
	Obj.push_back( new cObject( Vector3D(64+26,32,32+16+64), txSword ) );
	Obj.back()->PhysicsObject = Physics.AddBall( Obj.back()->Pos, Obj.back()->Scalar );

	Obj3.push_back( new cObject3D( Vector3D( 32, 32, 32+16 ), Mesh, Real(16) ) );
	Obj3.back()->PhysicsObject = Physics.AddConvexHull( Obj3.back()->Pos, Obj3.back()->Scalar, (float*)&(Obj3.back()->Mesh->Mesh[0].Vertex[0].Pos), Obj3.back()->Mesh->Mesh[0].Vertex.size(), sizeof(cPMEVertex) );
	Obj3.push_back( new cObject3D( Vector3D( -108, 32, 64+16 ), Mesh2, Real(20) ) );
	Obj3.back()->PhysicsObject = Physics.AddConvexHull( Obj3.back()->Pos, Obj3.back()->Scalar, (float*)&(Obj3.back()->Mesh->Mesh[0].Vertex[0].Pos), Obj3.back()->Mesh->Mesh[0].Vertex.size(), sizeof(cPMEVertex) );
	Obj3.push_back( new cObject3D( Vector3D( 0, -48, 64+16 ), Mesh2, Real(10) ) );
	Obj3.back()->PhysicsObject = Physics.AddConvexHull( Obj3.back()->Pos, Obj3.back()->Scalar, (float*)&(Obj3.back()->Mesh->Mesh[0].Vertex[0].Pos), Obj3.back()->Mesh->Mesh[0].Vertex.size(), sizeof(cPMEVertex) );
//	Obj3.push_back( new cObject3D( Vector3D( 128, 256+128, 256 ), Mesh, Real(20) ) );
//	Obj3.back()->PhysicsObject = Physics.AddConvexHull( Obj3.back()->Pos, Obj3.back()->Scalar, (float*)&(Obj3.back()->Mesh->Mesh[0].Vertex[0].Pos), Obj3.back()->Mesh->Mesh[0].Vertex.size(), sizeof(cPMEVertex) );
	
	CameraFollow = Obj[0];
	
	
	Log( "- End of Init" );
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Exit() {
	
	for ( int idx = 0; idx < Obj.size(); idx++ ) {
		Physics.Remove( Obj[idx]->PhysicsObject );
		delete Obj[idx];
	}
	for ( int idx = 0; idx < Obj3.size(); idx++ ) {
		Physics.Remove( Obj3[idx]->PhysicsObject );
		delete Obj3[idx];
	}
	
	delete Mesh;
	delete Mesh2;

	for ( int idx = 0; idx < Room.size(); idx++ ) {
		Physics.Remove( Room[idx]->PhysicsObject );
		
		delete_Triangles( Room[idx]->Vert, Room[idx]->Index );
		delete_OutlineList( Room[idx]->OutlineIndex );
		delete_Grid2D( Room[idx]->Grid );
	}
	
	// Shut Down Physics //
	Physics.Exit();

	// Kill Experiments //
//	extern void ExpExit();
//	ExpExit();

	// Kill VM //
	vm_Exit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::GotFocus() {
	ContentScan();
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::LostFocus() {
	
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
void cGame::Step() {
	float CameraSpeed = _TV(1.0f);	

	// Input //
	Vector2D Stick(0,0);
	{
		Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if ( keystate[SDL_SCANCODE_UP] ) {
			Stick.y = CameraSpeed;
		}
		if ( keystate[SDL_SCANCODE_DOWN] ) {
			Stick.y = -CameraSpeed;
		}
		if ( keystate[SDL_SCANCODE_LEFT] ) {
			Stick.x = -CameraSpeed;
		}
		if ( keystate[SDL_SCANCODE_RIGHT] ) {
			Stick.x = CameraSpeed;
		}
		if ( keystate[SDL_SCANCODE_PAGEUP] ) {
			CameraWorldPos += Vector3D(0,0,2.5f);
		}
		if ( keystate[SDL_SCANCODE_PAGEDOWN] ) {
			CameraWorldPos += Vector3D(0,0,-2.5f);
		}
		
		if ( keystate[SDL_SCANCODE_SPACE] ) {
			vm_CallFunc( "DoAwesome" );
		}
		

#ifdef USES_ICADE
		// iCade (Joystick Emulation via Keyboard) //
		extern int iCadeStatus;
		
		// Convert iCade to Stick //
		if ( iCadeStatus & (1 << 0) ) {
			Stick.y = 1.0f;
		}
		if ( iCadeStatus & (1 << 1) ) {
			Stick.y = -1.0f;
		}
		if ( iCadeStatus & (1 << 2) ) {
			Stick.x = 1.0f;
		}
		if ( iCadeStatus & (1 << 3) ) {
			Stick.x = -1.0f;
		}
#endif // USES_ICADE //
	}
	
	Input_MoveStick = Stick;
	
	if ( CameraFollow != 0 ) {
		CameraWorldPos += (CameraFollow->Pos - CameraWorldPos) * Real(0.1f);//Stick.ToVector3D() * Real( 2.5f );
		
		//CameraFollow->Pos -= Input_MoveStick.ToVector3D();
		CameraFollow->PhysicsObject->rigidBody->applyForce( 
			btVector3( 500.0 * -Input_MoveStick.x, 500.0 * -Input_MoveStick.y, 0 ), 
			btVector3( 32.0 * Input_MoveStick.x, 32.0 * Input_MoveStick.y, 0 ) );
	}
	
	// Step Physics //
	Physics.Step();
	
	// Step Objects //
	for ( int idx = 0; idx < Obj.size(); idx++ ) {
		Obj[idx]->Step();
	}
	for ( int idx = 0; idx < Obj3.size(); idx++ ) {
		Obj3[idx]->Step();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::DrawRoom( cRoom* ThisRoom, const Vector3D& Offset ) {
			gelLoadMatrix( ModelViewMatrix );
//			gelLoadMatrix( ViewMatrix );
//			gelMultMatrix( CameraMatrix );
//			gelMultMatrix( SpinMatrix );
			gelMultMatrix( Matrix4x4::TranslationMatrix( Offset ) );
			
			gelDrawIndexedTriangles( ThisRoom->Vert->Data, ThisRoom->Index->Data, ThisRoom->Index->Size, GEL_RGBA(255,255,255,64) );
////			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->Index->Data, ThisRoom->Index->Size, GEL_RGBA(0,255,0,64) );
			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->OutlineIndex->Data, ThisRoom->OutlineIndex->Size, GEL_RGBA(0,255,0,64) );
			gelDrawPoints( ThisRoom->Vert->Data, ThisRoom->Vert->Size, GEL_RGB_YELLOW );
	
//			gelDrawIndexedTriangleStrip( ThisRoom->Vert->Data, ThisRoom->Index->Data, 1024/*ThisRoom->Index->Size*/, GEL_RGBA(255,255,255,64) );
////			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->Index->Data, ThisRoom->Index->Size, GEL_RGBA(0,255,0,64) );
//			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->OutlineIndex->Data, 1024/*ThisRoom->OutlineIndex->Size*/, GEL_RGBA(0,255,0,64) );
//			gelDrawPoints( ThisRoom->Vert->Data, ThisRoom->Vert->Size, GEL_RGB_YELLOW );
	
//			static int StripNum = 0;
//			StripNum++;
//			StripNum %= indexStripCount_Optimized_TriangleStrips(65);
//			gelDrawIndexedTriangleStrip( 
//				ThisRoom->Vert->Data,
//				&ThisRoom->Index->Data[indexIndex_Optimized_TriangleStrips(65,StripNum,0)],
//				indexStripSize_Optimized_TriangleStrips(65),
//				GEL_RGBA(255,0,0,128)
//				);	
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Draw() {
	gelSetClearColor( GEL_RGB_BLACK );
	gelClear();

	Matrix4x4 Look = Calc_LookAt( Vector3D(0,256,1024), Vector3D(0,0,0) );
//	Matrix4x4 Look = Calc_LookAt( Vector3D(0,32,1024), Vector3D(0,0,0) );

	
	gelEnableAlphaBlending();
	
	// Terrain //
	{
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.25;
		
		Real CameraPos = Near + ((Far - Near) * PlanePos);

		CameraMatrix = Look * Matrix4x4::TranslationMatrix( Vector3D( 0, 0, CameraPos ) );
		ViewMatrix = Calc_Frustum_PerspectiveProjection( 
			ActualScreen::Width / RefScreen::Scalar,
			ActualScreen::Height / RefScreen::Scalar,
			Real( Near ),
			Real( Far ),
			Real( PlanePos )
			);
	
		ModelViewMatrix = ViewMatrix;
		ModelViewMatrix = CameraMatrix * ModelViewMatrix;
//		ModelViewMatrix = SpinMatrix * ModelViewMatrix;
		ModelViewMatrix = Matrix4x4::TranslationMatrix( -CameraWorldPos - Vector3D(0,-30,-100) ) * ModelViewMatrix;
	
		gelDrawModeColors();	
		for ( int idx = 0; idx < Room.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			Room[idx]->Draw();
		}

		gelDrawModeFlat();
		// Monkey Head //
		for ( int idx = 0; idx < Obj3.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			gelSetColor( GEL_RGBA(255,0,0,64) );
			Obj3[idx]->Draw();
			gelSetColor( GEL_RGB_DEFAULT );
		}

		gelDrawModeTextured();		
		for ( int idx = 0; idx < Obj.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			Obj[idx]->Draw();
		}
/*
		gelDrawModeFlat();		
		for ( int idx = 0; idx < Obj.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			Obj[idx]->DrawDebug();
		}
		for ( int idx = 0; idx < Obj3.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			Obj3[idx]->DrawDebug();
		}
		for ( int idx = 0; idx < Room.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			Room[idx]->DrawDebug();
		}
*/		
		if ( CameraFollow ) {
			gelDrawModeFlat();
			gelLoadMatrix( ModelViewMatrix );
			gelDrawCircle( CameraFollow->Pos + -Input_MoveStick.ToVector3D() * Real(20), Real(4), GEL_RGB_WHITE );
		}		
	}


	// Reset Camera //
	{
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.5;
		
		Real CameraPos = Near + ((Far - Near) * PlanePos);

		//Matrix4x4 Look2 = Calc_LookAt( Vector3D(0,0,0), Vector3D(0,150,800) );
		Matrix4x4 Look2 = Calc_LookAt( Vector3D(0,0,0), Vector3D(0,0,800) );
		CameraMatrix = Look2 * Matrix4x4::TranslationMatrix( -Vector3D( 0, 0, -CameraPos ) );
		ViewMatrix = Calc_Frustum_PerspectiveProjection( 
			ActualScreen::Width / RefScreen::Scalar,
			ActualScreen::Height / RefScreen::Scalar,
			Real( Near ),
			Real( Far ),
			Real( PlanePos )
			);
		
		Matrix4x4 CameraViewMatrix = ViewMatrix;
		CameraViewMatrix = CameraMatrix * CameraViewMatrix;
//		CameraViewMatrix = SpinMatrix * CameraViewMatrix;
	
		gelLoadMatrix( CameraViewMatrix );
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
