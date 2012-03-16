// - ------------------------------------------------------------------------------------------ - //
// NOTES: 
// - Hey cool, I saw inside TinyXML a suggestion that a handle can be used to simplify if (0) checks.
//   My theroy, implement a member function you use for access, and check the "this" variable if it's
//   zero.  If it's zero, then assume a failed lookup occured and do nothing.
// - ------------------------------------------------------------------------------------------ - //
// VPN Test! //

// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include <Debug/GelDebug.h>

#include <AssetPool/AssetPool.h>
#include <Graphics/GraphicsDraw.h>
#include <Input/Input.h>
#include <Graphics/Mesh/PMEFile.h>
#include <Graphics/Mesh/PMEFile_SimpleSelfShadow.h>
#include <Geometry/Projection/Projection.h>
#include <Geometry/Curve/Curve.h>

#include <Types/Set.h>
#include <Grid/Grid2D.h>

#include <Geometry/Vs/2D.h>
#include <Geometry/Vs/3D.h>

#include <cJSON.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_HIDAPI
#include "3DMouse/3DMouse_SpaceNavigator.h"
#endif // USES_HIDAPI //
// - ------------------------------------------------------------------------------------------ - //

GelAssetHandle txCursorMove;
GelAssetHandle txCursorStop;
GelAssetHandle txCursorAttack;

// - ------------------------------------------------------------------------------------------ - //

typedef int v4si __attribute__ ((vector_size (16)));
     
v4si a, b, c;

extern v4si Cornball();
v4si Cornball() {
	return c = a + b;
}

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
void cGame::SortObject() {
	// TODO: Only 1 per frame //

	// One Forward Step of Bubble Sort //
	for ( int idx = 1; idx < (int)Obj_Sort.size(); idx++ ) {
		Vector3D V1 = CameraEyePos - Obj[Obj_Sort[idx-1]]->Pos;
		Vector3D V2 = CameraEyePos - Obj[Obj_Sort[idx-0]]->Pos;
		if ( V1.MagnitudeSquared() > V2.MagnitudeSquared() ) {
			int Temp = Obj_Sort[idx-1];
			Obj_Sort[idx-1] = Obj_Sort[idx-0];
			Obj_Sort[idx-0] = Temp;
		}
	}
	// One Backward Step of Bubble Sort //
	for ( int idx = (int)Obj_Sort.size()-1; idx > 0; idx-- ) {
		Vector3D V1 = CameraEyePos - Obj[Obj_Sort[idx-1]]->Pos;
		Vector3D V2 = CameraEyePos - Obj[Obj_Sort[idx-0]]->Pos;
		if ( V1.MagnitudeSquared() > V2.MagnitudeSquared() ) {
			int Temp = Obj_Sort[idx-1];
			Obj_Sort[idx-1] = Obj_Sort[idx-0];
			Obj_Sort[idx-0] = Temp;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::SortObject3D() {
	// TODO: Only 1 per frame //
	
	// One Forward Step of Bubble Sort //
	for ( int idx = 1; idx < (int)Obj3_Sort.size(); idx++ ) {
		Vector3D V1 = CameraEyePos - Obj3[Obj3_Sort[idx-1]]->Pos;
		Vector3D V2 = CameraEyePos - Obj3[Obj3_Sort[idx-0]]->Pos;
		if ( V1.MagnitudeSquared() > V2.MagnitudeSquared() ) {
			int Temp = Obj3_Sort[idx-1];
			Obj3_Sort[idx-1] = Obj3_Sort[idx-0];
			Obj3_Sort[idx-0] = Temp;
		}
	}
	// One Backward Step of Bubble Sort //
	for ( int idx = (int)Obj3_Sort.size()-1; idx > 0; idx-- ) {
		Vector3D V1 = CameraEyePos - Obj3[Obj3_Sort[idx-1]]->Pos;
		Vector3D V2 = CameraEyePos - Obj3[Obj3_Sort[idx-0]]->Pos;
		if ( V1.MagnitudeSquared() > V2.MagnitudeSquared() ) {
			int Temp = Obj3_Sort[idx-1];
			Obj3_Sort[idx-1] = Obj3_Sort[idx-0];
			Obj3_Sort[idx-0] = Temp;
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::AddObject( const Vector3D& _Pos, const char* _File, const Real _Scalar ) {
	Obj.push_back( new cObject( _Pos, _File, _Scalar ) );
	Obj.back()->PhysicsObject = Physics.AddSphere( Obj.back()->Pos, Obj.back()->Scalar );
	
	Obj_Sort.push_back( Obj_Sort.size() );
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::AddObject3D( const Vector3D& _Pos, const char* _File, const Real _Scalar ) {
	Obj3.push_back( new cObject3D( _Pos, _File, _Scalar ) );
	
	cPMEFile* Mesh = AssetPool::GetMesh( Obj3.back()->MeshHandle );
	Obj3.back()->PhysicsObject = Physics.AddConvexHull( 
		Obj3.back()->Pos, 
		Obj3.back()->Scalar, 
		(float*)&(Mesh->Mesh[0].Vertex[0].Pos), 
		Mesh->Mesh[0].Vertex.size(), 
		sizeof(cPMEVertex) 
		);	

	Obj3_Sort.push_back( Obj3_Sort.size() );
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::AddOldRoom( const Vector3D& _Pos, const char* _File, const Real _Scalar ) {
	Vector3D RoomScale( _Scalar, _Scalar, _Scalar * Real::Half );

	Room.push_back( new cRoom( _Pos ) );
	Room.back()->Grid = load_Grid2D<cRoom::GType>( _File );
	new_Optimized_Triangles( Room.back()->Grid, &Room.back()->Vert, &Room.back()->Index, RoomScale );
	new_Triangles_OutlineList( Room.back()->Index, &Room.back()->OutlineIndex );
	Room.back()->PhysicsObject = Physics.AddStaticHeightMap( Room.back()->Pos, *(Room.back()->Grid), _Scalar );
	Room.back()->Color = new_GelArray<GelColor>(Room.back()->Vert->Size);
	for( int idx = 0; idx < Room.back()->Color->Size; idx++ ) {
		Grid2D<cRoom::GType>* Grid = Room.back()->Grid;
//		int Color = 255-Grid->Data[idx];//Room.back()->Vert->Data[idx].Pos.z;
		int Color = 225-(32*Room.back()->Vert->Data[idx].Pos.z);
		if ( Color > 255 )
			Color = 255;
		if ( Color < 0 )
			Color = 0;
		Room.back()->Color->Data[idx] = GEL_RGBA(Color,Color,Color,255);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::AddOldRoomMesh( const Vector3D& _Pos, const char* _File, const Real _Scalar ) {
	RoomMesh.push_back( new cRoomMesh( _Pos, _File, _Scalar ) );

	cPMEFile* RMesh = AssetPool::GetMesh( RoomMesh.back()->MeshHandle );

	unsigned short* Faces = (unsigned short*)&(RMesh->Mesh[0].FaceGroup[0].Face[0].a);
	unsigned int FaceCount = RMesh->Mesh[0].FaceGroup[0].Face.size();
	
	RoomMesh.back()->FaceHack.clear();
	for ( int idx = 0; idx < FaceCount*3; idx++ ) {
		RoomMesh.back()->FaceHack.push_back( Faces[idx] );
	}

	RoomMesh.back()->PhysicsObject = Physics.AddStaticMesh( 
		RoomMesh.back()->Pos, RoomMesh.back()->Scalar, 
		
		(float*)&(RMesh->Mesh[0].Vertex[0].Pos), 
		RMesh->Mesh[0].Vertex.size(), 
		sizeof(cPMEVertex),
		
		&(RoomMesh.back()->FaceHack[0]), 
		FaceCount
		);
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::LoadMap() {
	const char* InFile = "Content/Maps/GameMap.json";
	
	DataBlock* File = new_read_nullterminate_DataBlock( InFile );
	if ( File == 0 ) {
		Log( "! Map: Error reading file %s!", InFile );
	}
	cJSON* root = cJSON_Parse( File->Data );

	if ( root == 0 ) {
		Log( "! Map: Error parsing JSON data! Check for bad formatting, extra commas, etc" );
	}
	else {
		int Count = cJSON_GetArraySize( root );
		Log( "> %i Objects found in map", Count );
	
		for ( int idx = 0; idx < Count; idx++ ) {
			cJSON* Element = cJSON_GetArrayItem( root, idx );
	
			cJSON* obj = cJSON_GetObjectItem( Element, "Type" );
			if ( obj ) {
				if ( obj->valuestring == std::string("Object") ) {
					Vector3D Pos(0,0,0);

					cJSON* _Pos = cJSON_GetObjectItem( Element, "Pos" );
					if ( _Pos ) {
						Pos = Vector3D(
							cJSON_GetArrayItem( _Pos, 0 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 1 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 2 )->valuedouble
							);
					}
			
					AddObject( Pos, cJSON_GetObjectItem( Element, "Disc" )->valuestring );
					
					cJSON* _Scalar = cJSON_GetObjectItem( Element, "Scalar" );
					if ( _Scalar ) {
						Obj.back()->Scalar = cJSON_GetObjectItem( Element, "Scalar" )->valuedouble;
					}
					
					cJSON* _Glowing = cJSON_GetObjectItem( Element, "Glowing" );
					if ( _Glowing ) {
						Obj.back()->IsGlowing = cJSON_GetObjectItem( Element, "Glowing" )->type;
					}

					cJSON* _Focus = cJSON_GetObjectItem( Element, "Focus" );
					if ( _Focus ) {
						if ( cJSON_GetObjectItem( Element, "Focus" )->type ) {
							CameraFollow = Obj.back();
							CameraWorldPos = CameraFollow->Pos;
						}
					}
				}
				else if ( obj->valuestring == std::string("Item") ) {
					Vector3D Pos(0,0,0);

					cJSON* _Pos = cJSON_GetObjectItem( Element, "Pos" );
					if ( _Pos ) {
						Pos = Vector3D(
							cJSON_GetArrayItem( _Pos, 0 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 1 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 2 )->valuedouble
							);
					}
			
					AddObject3D( Pos, cJSON_GetObjectItem( Element, "Mesh" )->valuestring );
					
					cJSON* _Scalar = cJSON_GetObjectItem( Element, "Scalar" );
					if ( _Scalar ) {
						Obj3.back()->Scalar = cJSON_GetObjectItem( Element, "Scalar" )->valuedouble;
					}
					
					cJSON* _Glowing = cJSON_GetObjectItem( Element, "Glowing" );
					if ( _Glowing ) {
						Obj3.back()->IsGlowing = cJSON_GetObjectItem( Element, "Glowing" )->type;
					}

//					cJSON* _Focus = cJSON_GetObjectItem( Element, "Focus" );
//					if ( _Focus ) {
//						if ( cJSON_GetObjectItem( Element, "Focus" )->type ) {
//							CameraFollow = Obj.back();
//						}
//					}
				}
				else if ( obj->valuestring == std::string("RoomMesh") ) {
					Vector3D Pos(0,0,0);

					cJSON* _Pos = cJSON_GetObjectItem( Element, "Pos" );
					if ( _Pos ) {
						Pos = Vector3D(
							cJSON_GetArrayItem( _Pos, 0 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 1 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 2 )->valuedouble
							);
					}
			
					AddOldRoomMesh( Pos, cJSON_GetObjectItem( Element, "Mesh" )->valuestring );
					
					cJSON* _Scalar = cJSON_GetObjectItem( Element, "Scalar" );
					if ( _Scalar ) {
						RoomMesh.back()->Scalar = cJSON_GetObjectItem( Element, "Scalar" )->valuedouble;
					}
				}
				else if ( obj->valuestring == std::string("Room") ) {
					Vector3D Pos(0,0,0);

					cJSON* _Pos = cJSON_GetObjectItem( Element, "Pos" );
					if ( _Pos ) {
						Pos = Vector3D(
							cJSON_GetArrayItem( _Pos, 0 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 1 )->valuedouble,
							cJSON_GetArrayItem( _Pos, 2 )->valuedouble
							);
					}
			
					AddOldRoom( Pos, cJSON_GetObjectItem( Element, "Mesh" )->valuestring );
				}
			}
			
		}
	}
		
	cJSON_Delete( root );
	delete_DataBlock( File );	
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Init() {
	Log( "+ Start of Init..." );

	// Depth Buffer Ranges //
	gelSetDepthRange( 0, 1 );
	gelSetDepthFunc( GEL_LESSEQUAL );
	
	// Initialize the Virtual Machine... //
	vm_Init();
	
	extern int LogLevel;
	LogLevel = 2;

	InitScripts();
	LoadScripts();
	
	Physics.Init();
	
	ShowDebug = false;

	extern char AppBaseDir[]; 
	std::string Prefix = AppBaseDir;
	Font = new GelFont( std::string( Prefix + "Content/Misc/Fonts/Arial.fnt").c_str() );
//	Font = new GelFont( "Content/Misc/Fonts/CourierNew.fnt" );
//	Font = new GelFont( "Content/Misc/Fonts/Fontin.fnt" );

	GelSColor Col64 = GEL_SRGB( 280, -2, -32000 );
	Log( "!!!!!!!!!!!!!!!!!!!!! %i %i %i %i", GEL_SGET_R(Col64), GEL_SGET_G(Col64), GEL_SGET_B(Col64), GEL_SGET_A(Col64) );
	

	// *** //

	RenderTarget.resize(5);
	RenderTarget[RT_PRIMARY] = 
		new cRenderTarget( ActualScreen::Width>>0, ActualScreen::Height>>0, 1, 1, 0 );

	RenderTarget[RT_BLURY] = 
		new cRenderTarget( ActualScreen::Width>>0, ActualScreen::Height>>0, 1, 0, 0 );

	RenderTarget[RT_BLURY2] = 
		new cRenderTarget( ActualScreen::Width>>0, ActualScreen::Height>>0, 1, 0, 0 );
			
	RenderTarget[RT_MINI1] = 
		new cRenderTarget( ActualScreen::Width>>0, ActualScreen::Height>>0, 1, 0, 0 );
	
	RenderTarget[RT_MINI2] = 
		new cRenderTarget( ActualScreen::Width>>0, ActualScreen::Height>>0, 1, 0, 0 );
	
	UberShader.resize(3);
	UberShader[US_POSTPROCESS] =
		new cUberShader( std::string( Prefix + "Content/Scripts/glsl/PostProcess.json").c_str() );

	UberShader[US_EDGEBLEND] =
		new cUberShader( std::string( Prefix + "Content/Scripts/glsl/PPEdgeBlend.json").c_str() );

	UberShader[US_TEXTWOBLEND] =
		new cUberShader( std::string( Prefix + "Content/Scripts/glsl/TexTwoBlend.json").c_str() );
	
	// *** //
	
#ifdef USES_HIDAPI
	HIDAPI_Check();

	SpaceNavigator_Init();
#endif // USES_HIDAPI //

	// *** //
	
	// Store the current clock, so the content scanner can know to disregard extra scans //
	LastContentScan = GetTimeNow();

	// Some Art Assets //
	txCursorMove = AssetPool::Load( "/Cursor_Move" );
	txCursorStop = AssetPool::Load( "/Cursor_Stop" );
	txCursorAttack = AssetPool::Load( "/Cursor_Attack" );

	// Reset Camera //
	CameraWorldPos = Vector3D(0,0,0);
	CameraEyePos = Vector3D( _TV(0), _TV(-2), _TV(0) ); // TODO: Should be positive //
	CameraFollow = 0;
	CameraTilt = Vector3D(0,0,1024);

	//LoadMap();

	// Add Rooms //	
	AddOldRoom( Vector3D(0,0+64,0), std::string( Prefix + "Content/Tests/Room01.tga").c_str() );
	AddOldRoom( Vector3D(16,32+64,0), std::string( Prefix + "Content/Tests/Room02.tga").c_str() );
	AddOldRoom( Vector3D(16,64+64,0), std::string( Prefix + "Content/Tests/Room03.tga").c_str() );
	AddOldRoom( Vector3D(32+16,64+64,0), std::string( Prefix + "Content/Tests/Room04.tga").c_str() );
	
	// Add some Objects //
	AddObject( Vector3D(16,0,10+4+2), std::string( Prefix + "Content/Objects/Discs/Player_disc.json").c_str(), Real(1.2) );
	Obj.back()->IsGlowing = true;
	AddObject( Vector3D(0,64+4,10+4+2), std::string( Prefix + "Content/Objects/Discs/Bat_disc.json").c_str(), Real(1.2) );

	// Follow the 1st object //
	CameraFollow = Obj[0];
	CameraWorldPos = CameraFollow->Pos;

	AddObject3D( Vector3D( 4, 4, 4+2 ), "/Skull.pme", Real(1.2) );
	Obj3.back()->Color = GEL_RGB_RED;
	Obj3.back()->GlowColor = GEL_RGBA(64,64,0,64);
	Obj3.back()->IsGlowing = true;

//	AddObject3D( Vector3D( 4+4, 4, 4+2 ), "/Skull.pme", Real(0.8) );
	AddObject3D( Vector3D( 4+8, 4, 4+2 ), "/Bottle.pme", Real(1.8) );

	AddObject3D( Vector3D( 4, 4+4, 4+2 ), "/Book_Open.pme", Real(0.8) );
	AddObject3D( Vector3D( 4+4, 4+4, 4+2 ), "/Shield.pme", Real(0.6) );
//	AddObject3D( Vector3D( 4+8, 4+4, 4+2 ), "/Shield.pme", Real(0.8) );
	AddObject3D( Vector3D( 4, 4+8, 4+2 ), "/CandleStick.pme", Real(0.8) );
	AddObject3D( Vector3D( 4+4, 8+4, 4+2 ), "/Key_Boxy.pme", Real(0.4) );
	
//	AddObject3D( Vector3D( 4+4, 8+4, 4+2 ), "/Key_Boxy.pme", Real(0.8) );
//	AddObject3D( Vector3D( 4, 4+8, 4 ), "/Table_SquareCenter.pme", Real(0.8) );
	AddObject3D( Vector3D( -14, 4, 8+4 ), "/Sword.pme", Real(2) );
//	AddObject3D( Vector3D( 0, -6, 8+2 ), "/Sword.pme", Real(1) );
//	Obj3.back()->IsGlowing = true;

	AddOldRoomMesh( Vector3D( 0, 0, 0 ), "/RockTest.pme" );

//	cPMEFile MeshTest;
//	MeshTest.Import( "Content/Models/Export/uvtest.dae" );
//	MeshTest.FileName = "Content/Models/Native/uvtest.pme";
//	MeshTest.TextSave();
	
	Log( "- End of Init" );
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Exit() {
	
	for ( size_t idx = 0; idx < Obj.size(); idx++ ) {
		Physics.Remove( Obj[idx]->PhysicsObject );
		delete Obj[idx];
	}
	for ( size_t idx = 0; idx < Obj3.size(); idx++ ) {
		Physics.Remove( Obj3[idx]->PhysicsObject );
		delete Obj3[idx];
	}

	for ( size_t idx = 0; idx < RoomMesh.size(); idx++ ) {
		Physics.Remove( RoomMesh[idx]->PhysicsObject );
		delete RoomMesh[idx];
	}

	for ( size_t idx = 0; idx < Room.size(); idx++ ) {
		Physics.Remove( Room[idx]->PhysicsObject );
		
		delete_Triangles( Room[idx]->Vert, Room[idx]->Index );
		delete_OutlineList( Room[idx]->OutlineIndex );
		delete_Grid2D( Room[idx]->Grid );
	}

	for ( size_t idx = 0; idx < RenderTarget.size(); idx++ ) {	
		delete RenderTarget[idx];
	}

	for ( size_t idx = 0; idx < UberShader.size(); idx++ ) {	
		delete UberShader[idx];
	}

	delete Font;
	
	// Shut Down Physics //
	Physics.Exit();

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
#ifdef USES_SDL		
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
		
		static bool KeyDown = false;

		if ( keystate[SDL_SCANCODE_F1] ) {
			if ( KeyDown == false ) {
				ShowDebug = !ShowDebug;
				KeyDown = true;
			}
		}
		else {
			KeyDown = false;
		}

#endif // USES_SDL //		

#ifdef PRODUCT_MOBILE
		extern float accel_x;
		extern float accel_y;
		extern float accel_z;

		Stick.x = accel_y;
		Stick.y = accel_x;
#endif // PRODUCT_MOBILE //

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

#ifdef USES_HIDAPI
	SpaceNavigator_Update();
#endif // USES_HIDAPI //
	
	Input_MoveStick = Stick;
	
	if ( CameraFollow != 0 ) {
		CameraWorldPos += (CameraFollow->Pos - CameraWorldPos) * Real(0.1f);//Stick.ToVector3D() * Real( 2.5f );
		
		//CameraFollow->Pos -= Input_MoveStick.ToVector3D();
		if ( (Stick.x != Real::Zero) || (Stick.y != Real::Zero) ) {
			CameraFollow->PhysicsObject->rigidBody->activate(true);

			CameraFollow->PhysicsObject->rigidBody->applyCentralForce( 
				btVector3( 16.0 * Input_MoveStick.x, 16.0 * Input_MoveStick.y, 0 )
				);

//			CameraFollow->PhysicsObject->rigidBody->applyCentralImpulse( 
//				btVector3( 500.0 * Input_MoveStick.x, 500.0 * Input_MoveStick.y, 0 )
//				);

//			CameraFollow->PhysicsObject->rigidBody->applyForce( 
//				btVector3( 500.0 * Input_MoveStick.x, 500.0 * Input_MoveStick.y, 0 ), 
//				btVector3( 32.0 * Input_MoveStick.x, 32.0 * Input_MoveStick.y, 0 ) );
		}
	}
	
	SortObject();
	SortObject3D();
	
	// Step Physics //
	Physics.Step();
	
	// Step Objects //
	for ( size_t idx = 0; idx < Obj.size(); idx++ ) {
		Obj[idx]->Step();
	}
	for ( size_t idx = 0; idx < Obj3.size(); idx++ ) {
		Obj3[idx]->Step();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::DrawRoom( cRoom* ThisRoom, const Vector3D& Offset ) {
	gelLoadMatrix( ObserverCamera.ProjectionView );
	gelMultMatrix( Matrix4x4::TranslationMatrix( Offset ) );
	
	gelDrawIndexedTriangles( ThisRoom->Vert->Data, ThisRoom->Index->Data, ThisRoom->Index->Size, GEL_RGBA(255,255,255,64) );
	gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->OutlineIndex->Data, ThisRoom->OutlineIndex->Size, GEL_RGBA(0,255,0,64) );
	gelDrawPoints( ThisRoom->Vert->Data, ThisRoom->Vert->Size, GEL_RGB_YELLOW );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::UpdateCameraMatrix() {
/*
	Vector3D ViewerPos( 0, 256, 1024 );
	
#ifdef USES_HIDAPI
	ViewerPos.x = 0 + (SpaceNavigator[4] * 512);
	ViewerPos.y = 256 + (SpaceNavigator[3] * 512);
#endif // USES_HIDAPI //

#ifdef PRODUCT_MOBILE
extern float smoothaccel_x;
extern float smoothaccel_y;
extern float smoothaccel_z;

	float TiltScalar = 256+128;

	ViewerPos.x = 0.0f - (smoothaccel_y * TiltScalar);
	ViewerPos.y = 0.0f - (smoothaccel_x * TiltScalar);	
#endif // PRODUCT_MOBILE //

	ViewerPos.Normalize();
	ViewerPos *= 1024.0f;

	Vector3D CameraDiff = CameraTilt - ViewerPos;
	CameraTilt -= CameraDiff * Real(0.25);
	
	// NOTE: Camera Up should not be hardcoded! //
	Matrix4x4 Look = Calc_LookAtOnly( CameraTilt, CameraFollow->Pos, Vector3D(0,1,0) );

#ifdef USES_HIDAPI
	Look = Look * Matrix4x4::RotationMatrixXY( SpaceNavigator[5] * 32.0f );
#endif // USES_HIDAPI //

	// Camera //
	Real Near = _TV(10);
	Real Length = _TV(100);
	
	Real Far = Near + Length;
	Real CenterPlanePos = _TV(0.50f);

	Real CameraPos = Near + ((Far - Near) * CenterPlanePos);

	CameraMatrix = Look * Matrix4x4::TranslationMatrix( Vector3D( 0, 0, CameraPos ) );
		
	ViewMatrix = Calc_Frustum_PerspectiveProjection( 
		ActualScreen::Width * Real(0.1f) / RefScreen::Scalar,
		ActualScreen::Height * Real(0.1f) / RefScreen::Scalar,
		Real( Near ),
		Real( Far ),
		Real( CenterPlanePos )
		);

	ModelViewMatrix = ViewMatrix;
	ModelViewMatrix.Multiply( CameraMatrix );
	ModelViewMatrix.Multiply( Matrix4x4::TranslationMatrix( -CameraWorldPos - CameraEyePos ) );
*/
	ObserverCamera.SetFrustum( 
//		ActualScreen::Width * Real(0.1f) / RefScreen::Scalar,
//		ActualScreen::Height * Real(0.1f) / RefScreen::Scalar,
		FullRefScreen::Width * Real(0.1f),
		FullRefScreen::Height * Real(0.1f),
		_TV(10),
		_TV(110)
		);
	ObserverCamera.Pos = CameraWorldPos + Vector3D(0,0,64);
	ObserverCamera.Look = CameraWorldPos;
	ObserverCamera.Up = Vector3D(0,1,0);
	ObserverCamera.UpdateMatrix();
	

	// UI Aligned Camera //
	Real Near = _TV(100);
	Real Length = _TV(800);
	
	Real Far = Near + Length;
	Real PlanePos = _TV(0.5f);
	
	Real CameraPos = Near + ((Far - Near) * PlanePos);

	UICamera.SetFrustum(
//		ActualScreen::Width / RefScreen::Scalar,
//		ActualScreen::Height / RefScreen::Scalar,
		FullRefScreen::Width,
		FullRefScreen::Height,
		Near,
		Far,
		PlanePos
		);
	UICamera.Pos = Vector3D(0,0,CameraPos);
	UICamera.Look = Vector3D(0,0,0);
	UICamera.Up = Vector3D(0,1,0);
	UICamera.UpdateMatrix();
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::DrawScene() {
	gelEnableDepthWriting();
	gelEnableDepthTest();
	gelDisableBlending();

	gelDrawModeColors();	
	for ( size_t idx = 0; idx < Room.size(); idx++ ) {
		gelLoadMatrix( ObserverCamera.ProjectionView );
		Room[idx]->Draw();
	}
	gelDrawModeNull();

//	gelEnableTexturing();
	UberShader[US_TEXTWOBLEND]->Bind( 0 );
	for ( size_t idx = 0; idx < RoomMesh.size(); idx++ ) {
		RoomMesh[idx]->Draw( UberShader[US_TEXTWOBLEND], ObserverCamera.ProjectionView );
	}

	// Monkey Head //
	UberShader[US_TEXTWOBLEND]->Bind( 0 );
	for ( size_t idx = 0; idx < Obj3.size(); idx++ ) {
		// Changing Alpha no longer works because depth test is removing backfaces //
		Obj3[ Obj3_Sort[idx] ]->Draw( UberShader[US_TEXTWOBLEND], ObserverCamera.ProjectionView );
	}

	gelDisableDepthWriting();	// Just writing. Depth Testing is still enabled. //
	gelEnablePremultipliedAlphaBlending();
	
	// Alpha Testing will not work here. I need to disable writing, and sort them relative camera //
	gelDrawModeTextured();		
	for ( size_t idx = 0; idx < Obj.size(); idx++ ) {
		gelLoadMatrix( ObserverCamera.ProjectionView );
		Obj[ Obj_Sort[idx] ]->Draw();
	}
	gelSetColor( GEL_RGB_DEFAULT );
			
	gelDisableDepthTest();		// Testing too. Depth buffer is off //
	
	if ( ShowDebug ) {
		gelDisableBlending();
		gelDrawModeFlat();

		for ( size_t idx = 0; idx < Obj3.size(); idx++ ) {
			gelLoadMatrix( ObserverCamera.ProjectionView );
			Obj3[ idx ]->DrawDebug();
		}
		for ( size_t idx = 0; idx < Obj.size(); idx++ ) {
			gelLoadMatrix( ObserverCamera.ProjectionView );
			Obj[ idx ]->DrawDebug();
		}
		for ( size_t idx = 0; idx < Room.size(); idx++ ) {
			gelLoadMatrix( ObserverCamera.ProjectionView );
			Room[ idx ]->DrawDebug();
		}
		for ( size_t idx = 0; idx < RoomMesh.size(); idx++ ) {
			gelLoadMatrix( ObserverCamera.ProjectionView );
			RoomMesh[ idx ]->DrawDebug();
		}
		
		gelEnablePremultipliedAlphaBlending();
	}

	if ( CameraFollow ) {
		gelLoadMatrix( ObserverCamera.ProjectionView );
		
		gelDrawModeTextured();
		AssetPool::Set( txCursorAttack );

		gelDrawSquareFillTextured( CameraFollow->Pos + Input_MoveStick.ToVector3D() * Real(2.4), Real(0.6), GEL_RGB(255,242,0) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::DrawSceneGlow() {
	gelDisableBlending();
	gelDisableDepthWriting();
	gelDisableDepthTest();
	
	
	gelSetClearColor( GEL_RGBA(0,0,0,0) );
	gelClear();

//	gelEnableAlphaBlending();

	// Glow Render //
	{
		// NOTE: Glows will always overlay, since we are not referencing the original Z buffer, and testing vs. //
		
		// Alpha Testing will not work here. I need to disable writing, and sort them relative camera //
		gelDrawModeFlat();	
		for ( size_t idx = 0; idx < Obj3.size(); idx++ ) {
			if ( Obj3[ Obj3_Sort[idx] ]->IsGlowing ) {
				gelLoadMatrix( ObserverCamera.ProjectionView );
				Obj3[ Obj3_Sort[idx] ]->DrawGlow();
			}
		}
		
		gelEnablePremultipliedAlphaBlending();
		gelDrawModeTextured();		
		for ( size_t idx = 0; idx < Obj.size(); idx++ ) {
			if ( Obj[ Obj_Sort[idx] ]->IsGlowing ) {
				gelLoadMatrix( ObserverCamera.ProjectionView );
				Obj[ Obj_Sort[idx] ]->DrawGlow();
			}
		}
		gelSetColor( GEL_RGB_DEFAULT );	
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::Draw() {
	glDisable( GL_CULL_FACE );
	gelDisableStencilWriting();
	gelDisableStencilTest();
	glDisable( GL_SCISSOR_TEST );

	UpdateCameraMatrix();

	int CurrentRT = 0;
	int ScalarX = FullRefScreen::Width>>1;
	int ScalarY = FullRefScreen::Height>>1;

	CurrentRT = RT_PRIMARY;
	RenderTarget[CurrentRT]->Bind();
	{
		gelEnableDepthWriting();

#ifdef NDEBUG	// Only in Debug build, Clear to red, so we can see undrawn pixels //
		gelSetClearColor( GEL_RGB_RED );
#else // NDEBUG //
		gelSetClearColor( GEL_RGB_WHITE );
//		gelSetClearColor( GEL_RGB_BLACK );
#endif // NDEBUG //

		gelClear( true, true );

		DrawScene();
		gelDrawModeColors();
		gelLoadMatrix( ObserverCamera.ProjectionView );	
		gelDrawLine( Vector3D(-12,-12,0), Vector3D(12,12,0), GEL_RGB_GREEN, GEL_RGB_RED );
	}

	CurrentRT = RT_MINI1;
	RenderTarget[CurrentRT]->Bind();
	{
		DrawSceneGlow();
	}
/*
	// Reset Camera for UI //
	Matrix4x4 CameraViewMatrix;
	{
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.5;
		
		Real CameraPos = Near + ((Far - Near) * PlanePos);

		//Matrix4x4 Look2 = Calc_LookAtOnly( Vector3D(0,0,0), Vector3D(0,150,800), Vector3D(0,1,0) );
		Matrix4x4 Look2 = Calc_LookAtOnly( Vector3D(0,0,0), Vector3D(0,0,800), Vector3D(0,1,0) );
		CameraMatrix = Look2 * Matrix4x4::TranslationMatrix( -Vector3D( 0, 0, -CameraPos ) );
		ViewMatrix = Calc_Frustum_PerspectiveProjection( 
			ActualScreen::Width / RefScreen::Scalar,
			ActualScreen::Height / RefScreen::Scalar,
			Real( Near ),
			Real( Far ),
			Real( PlanePos )
			);
		
		CameraViewMatrix = ViewMatrix;
		CameraViewMatrix = CameraMatrix * CameraViewMatrix;
	}
*/
		static float Bork = 0;
		Bork+=0.01f;

	gelDisableBlending();

	CurrentRT = RT_MINI2;
	RenderTarget[CurrentRT]->Bind();
	{
		gelSetClearColor( GEL_RGBA(0,0,0,0) );
		gelClear();

		UberShader[US_POSTPROCESS]->Bind(US_PP_VBLUR);
		UberShader[US_POSTPROCESS]->BindUniformMatrix4x4( "ViewMatrix", UICamera.ProjectionView );
		RenderTarget[RT_MINI1]->BindAsTexture();
	
		gelDrawRectFillTextured_( 
			Vector3D( -ScalarX, -ScalarY, 0 ),
			Vector3D( ScalarX, ScalarY, 0 )
//			Vector3D( -ScalarX, -ScalarY * Real::Sin(Bork), 0 ),
//			Vector3D( ScalarX, ScalarY * Real::Sin(Bork), 0 )
			);
	}

	CurrentRT = RT_BLURY;
	RenderTarget[CurrentRT]->Bind();
	{
		gelSetClearColor( GEL_RGBA(0,0,0,0) );
		gelClear();

		UberShader[US_POSTPROCESS]->Bind(US_PP_BLUR);
		UberShader[US_POSTPROCESS]->BindUniformMatrix4x4( "ViewMatrix", UICamera.ProjectionView );
		RenderTarget[RT_PRIMARY]->BindAsTexture();
	
		gelDrawRectFillTextured_( 
			Vector3D( -ScalarX, -ScalarY, 0 ),
			Vector3D( ScalarX, ScalarY, 0 )
			);
	}

	CurrentRT = RT_BLURY2;
	RenderTarget[CurrentRT]->Bind();
	{
		gelSetClearColor( GEL_RGBA(0,0,0,0) );
		gelClear();

		UberShader[US_POSTPROCESS]->Bind(US_PP_BLUR);
		UberShader[US_POSTPROCESS]->BindUniformMatrix4x4( "ViewMatrix", UICamera.ProjectionView );
		RenderTarget[RT_BLURY]->BindAsTexture();
	
		gelDrawRectFillTextured_( 
			Vector3D( -ScalarX, -ScalarY, 0 ),
			Vector3D( ScalarX, ScalarY, 0 )
			);
	}

	CurrentRT = RT_BLURY;
	RenderTarget[CurrentRT]->Bind();
	{
		gelSetClearColor( GEL_RGBA(0,0,0,0) );
		gelClear();

		UberShader[US_POSTPROCESS]->Bind(US_PP_BLUR);
		UberShader[US_POSTPROCESS]->BindUniformMatrix4x4( "ViewMatrix", UICamera.ProjectionView );
		RenderTarget[RT_BLURY2]->BindAsTexture();
	
		gelDrawRectFillTextured_( 
			Vector3D( -ScalarX, -ScalarY, 0 ),
			Vector3D( ScalarX, ScalarY, 0 )
			);
	}

	cRenderTarget::UnBind();	// Back to Screen //
	CurrentRT = 0;

	// - -------------------------------------------------------------------------------------- - //
	// NOTE: After this point, we need to use different coordinate systems to map UVs correctly. //
	// Hey remember the Cartesian vs UV corner disparity thing? This is that exact same thing. //

	// HACK: Fix the flipped matrix by manually un-flipping the matrix //
//	UICamera.Projection.Matrix(1,1) = -UICamera.Projection.Matrix(1,1);
//	UICamera.CalculateProjectionView();
//	ObserverCamera.Projection.Matrix(1,1) = -ObserverCamera.Projection.Matrix(1,1);
//	ObserverCamera.CalculateProjectionView();

	gelEnableDepthWriting();
	gelClearDepth();

	{
		{
			gelDrawModeTextured();
			gelLoadMatrix( UICamera.ProjectionView );
			RenderTarget[RT_PRIMARY]->BindAsTexture();
	
			gelSetColor( GEL_RGBA(255,255,255,255) );
			gelDrawRectFillTextured_( 
				Vector3D( -ScalarX, -ScalarY, 0 ),
				Vector3D( ScalarX, ScalarY, 0 )
				);
		}

		{
			gelEnableAlphaBlending();
	//		UberShader[US_POSTPROCESS]->Bind(US_PP_HBLUR_HEAVY);
			UberShader[US_EDGEBLEND]->Bind(0);
	
	//		glActiveTexture( GL_TEXTURE0 );
			RenderTarget[RT_BLURY]->BindAsTexture();
	//		UberShader[US_EDGEBLEND]->BindUniform1i( "TexImage0", 0 );
			UberShader[US_EDGEBLEND]->BindUniformMatrix4x4( "ViewMatrix", UICamera.ProjectionView );
			UberShader[US_EDGEBLEND]->BindUniform2f( "AspectScalar", 1.0f, 1.0f / ActualScreen::AspectRatio );
	
			gelDrawRectFillTextured_( 
				Vector3D( -ScalarX, -ScalarY, 0 ),
				Vector3D( ScalarX, ScalarY, 0 )
				);		
		}

		{
			gelEnablePremultipliedAlphaBlending();
	
			UberShader[US_POSTPROCESS]->Bind(US_PP_HBLUR);
			UberShader[US_POSTPROCESS]->BindUniformMatrix4x4( "ViewMatrix", UICamera.ProjectionView );
			RenderTarget[RT_MINI2]->BindAsTexture();
//			RenderTarget[RT_MINI1]->BindAsTexture();
	
			gelDrawRectFillTextured_( 
				Vector3D( -ScalarX, -ScalarY, 0 ),
				Vector3D( ScalarX, ScalarY, 0 )
				);
		}

#ifdef USES_HIDAPI
		SpaceNavigator_DrawValues();
#endif // USES_HIDAPI //
				
		gelEnablePremultipliedAlphaBlending();

		Vector3D MouseRayStart = Mouse.Pos.ToVector3D();
//		MouseRayStart.z = Real(-1);
		MouseRayStart.z = ObserverCamera.NearPlane;//+Real(1);

		Vector3D MouseRayEnd = Mouse.Pos.ToVector3D();
//		MouseRayEnd.z = Real(1);
		MouseRayEnd.z = ObserverCamera.FarPlane;//-Real(1);

		Calc_UnProject( 
			Mouse.Pos.x.ToFloat(), Mouse.Pos.y.ToFloat(), Real(0),
			ObserverCamera.View,
			ObserverCamera.Projection,
			(const int[]){-FullRefScreen::Width>>1,-FullRefScreen::Height>>1,FullRefScreen::Width,FullRefScreen::Height},
			(float*)&MouseRayStart.x,(float*)&MouseRayStart.y,(float*)&MouseRayStart.z
			);

		Calc_UnProject( 
			Mouse.Pos.x.ToFloat(), Mouse.Pos.y.ToFloat(), Real(1),
			ObserverCamera.View,
			ObserverCamera.Projection,
			(const int[]){-FullRefScreen::Width>>1,-FullRefScreen::Height>>1,FullRefScreen::Width,FullRefScreen::Height},
			(float*)&MouseRayEnd.x,(float*)&MouseRayEnd.y,(float*)&MouseRayEnd.z
			);
		

		btVector3 BTRayStart = btVector3( MouseRayStart.x, MouseRayStart.y, MouseRayStart.z );		
		btVector3 BTRayEnd = btVector3( MouseRayEnd.x, MouseRayEnd.y, MouseRayEnd.z );		
		
		btCollisionWorld::ClosestRayResultCallback RayInfo( BTRayStart, BTRayEnd );
		Physics.dynamicsWorld->rayTest( BTRayStart, BTRayEnd, RayInfo );

		// Draw //
		Matrix4x4 VisibleMatrix = ObserverCamera.ProjectionView;
		
		gelDrawModeFlat();
		gelLoadMatrix( VisibleMatrix );
		gelDrawCircleFill( MouseRayStart - Vector3D(0,0,0.01), Real(0.3), GEL_RGBA(128,0,0,128) );
		gelDrawCircleFill( MouseRayEnd + Vector3D(0,0,0.01), Real(0.3), GEL_RGBA(0,128,0,128) );

		// Coords are in full space. If near plane is 10, then visible coords start at 10. If far is 110, they end at 110 //
		gelDrawCircleFill( ObserverCamera.Pos - Vector3D(0 * 0.1f,0 * 0.1f,60), Real(0.5f), GEL_RGBA(128,128,128,128) );

		Vector3D HitPoint = *((Vector3D*)&RayInfo.m_hitPointWorld);
		gelDrawCircleFill( HitPoint, Real(1), GEL_RGBA(128,0,128,128) );

		gelDrawModeColors();
		gelLoadMatrix( VisibleMatrix );
		gelDrawLine( MouseRayStart, MouseRayEnd, GEL_RGBA(255,0,0,255), GEL_RGBA(0,255,0,255) );
	
//		gelDrawLine( Vector3D(-12,-12,0), Vector3D(12,12,0), GEL_RGB_GREEN, GEL_RGB_RED );


		gelDrawModeColors();
		gelLoadMatrix( UICamera.ProjectionView );	
		gelDrawLine( Vector3D(-128,-128,0), Vector3D(128,128,0), GEL_RGB_GREEN, GEL_RGB_RED );
				
		// Text //		
		gelDrawModeTextured();
		gelLoadMatrix( UICamera.ProjectionView );

		gelEnablePremultipliedAlphaBlending();
		gelSetColor( GEL_RGB_YELLOW );
	
		extern int FPS_Counter;		
		Font->printf( 
			Vector3D( FullRefScreen::Width>>1, FullRefScreen::Height>>1, 0 ), 
			2, 
			GelFont::ALIGN_RIGHT | GelFont::ALIGN_TOP, 
			"FPS: %i - %i, %i (%f, %f)", FPS_Counter, FullRefScreen::Width, FullRefScreen::Height, Mouse.Pos.x.ToFloat(), Mouse.Pos.y.ToFloat() );

		Font->printf( 
			Vector3D( FullRefScreen::Width>>1, 0, 0 ), 
			1, 
			GelFont::ALIGN_RIGHT | GelFont::ALIGN_VCENTER, 
			"Hello Gentlemen" );
		Font->printf( 
			Vector3D( FullRefScreen::Width>>1, -16, 0 ), 
			1, 
			GelFont::ALIGN_RIGHT | GelFont::ALIGN_VCENTER, 
			"(%f, %f, %f)", MouseRayStart.x.ToFloat(), MouseRayStart.y.ToFloat(), MouseRayStart.z.ToFloat() );
//		Font->printf( 
//			Vector3D( FullRefScreen::Width>>1, -32, 0 ), 
//			1, 
//			GelFont::ALIGN_LEFT | GelFont::ALIGN_TOP, 
//			"(%f, %f, %f)", MouseRayMiddle.x.ToFloat(), MouseRayMiddle.y.ToFloat(), MouseRayMiddle.z.ToFloat() );
		Font->printf( 
			Vector3D( FullRefScreen::Width>>1, -48, 0 ), 
			1, 
			GelFont::ALIGN_RIGHT | GelFont::ALIGN_VCENTER, 
			"(%f, %f, %f)", MouseRayEnd.x.ToFloat(), MouseRayEnd.y.ToFloat(), MouseRayEnd.z.ToFloat() );

		gelSetColor( GEL_RGB_ORANGE );
		Font->printf( 
			Vector3D( FullRefScreen::Width>>1, -64, 0 ), 
			1, 
			GelFont::ALIGN_RIGHT | GelFont::ALIGN_VCENTER, 
			"(%f, %f, %f)", HitPoint.x.ToFloat(), HitPoint.y.ToFloat(), HitPoint.z.ToFloat() );

		gelSetColor( GEL_RGB_YELLOW );

		Matrix4x4 Check = ObserverCamera.View;
//		Matrix4x4 Check = ObserverCamera.View.Minor44().ToMatrix4x4();
//		Check = Check * Check.Transpose();
		Font->printf( 
			Vector3D( FullRefScreen::Width>>1, -80, 0 ), 
			1, 
			GelFont::ALIGN_RIGHT | GelFont::ALIGN_VCENTER, 
			"(%f | %f | %f | %f)", Check.Row0().SumOf().ToFloat(), Check.Row1().SumOf().ToFloat(), Check.Row2().SumOf().ToFloat(), Check.Row3().SumOf().ToFloat() );

		// *** //

		gelDrawModeTextured();
		gelLoadMatrix( UICamera.ProjectionView );
		gelSetColor( GEL_RGB_DEFAULT );
		gelEnableAlphaBlending();		
	}	
}
// - ------------------------------------------------------------------------------------------ - //
