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
#include <Graphics/Mesh/PMEFile_SimpleSelfShadow.h>
#include <Geometry/Projection/Projection.h>
#include <Geometry/Curve/Curve.h>

#include <Types/Set.h>
#include <Grid/Grid2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //

GelAssetHandle txPlayer;
GelAssetHandle txCursorMove;
GelAssetHandle txCursorStop;
GelAssetHandle txCursorAttack;

GLuint FBOTextureId;
GLuint FBOId;

int FBOSize = 1024;

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
void cGame::AddObject( const Vector3D& _Pos, const char* _File, const Real _Scalar ) {
	Obj.push_back( new cObject( _Pos, _File, _Scalar ) );
	Obj.back()->PhysicsObject = Physics.AddBall( Obj.back()->Pos, Obj.back()->Scalar );
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
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::AddOldRoom( const Vector3D& _Pos, const char* _File ) {
	Vector3D RoomScale(128,128,64);

	Room.push_back( new cRoom( _Pos ) );
	Room.back()->Grid = load_Grid2D<cRoom::GType>( _File );
	new_Optimized_Triangles( Room.back()->Grid, &Room.back()->Vert, &Room.back()->Index, RoomScale );
	new_Triangles_OutlineList( Room.back()->Index, &Room.back()->OutlineIndex );
	Room.back()->PhysicsObject = Physics.AddStaticHeightMap( Room.back()->Pos, *(Room.back()->Grid) );
	Room.back()->Color = new_GelArray<GelColor>(Room.back()->Vert->Size);
	for( int idx = 0; idx < Room.back()->Color->Size; idx++ ) {
		Grid2D<cRoom::GType>* Grid = Room.back()->Grid;
//		int Color = 255-Grid->Data[idx];//Room.back()->Vert->Data[idx].Pos.z;
		int Color = 225-(3*Room.back()->Vert->Data[idx].Pos.z);
		if ( Color > 255 )
			Color = 255;
		if ( Color < 0 )
			Color = 0;
		Room.back()->Color->Data[idx] = GEL_RGBA(Color,Color,Color,255);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::AddOldRoomMesh( const Vector3D& _Pos, const char* _File ) {
	cPMEFile* RMesh = new cPMEFile();
	RMesh->Import( _File );


	RoomMesh.push_back( 
		new cRoomMesh( 
			_Pos, 
			RMesh, 
			Real(16) 
			) 
		);

	unsigned short* Faces = (unsigned short*)&(RoomMesh.back()->Mesh->Mesh[0].FaceGroup[0].Face[0].a);
	unsigned int FaceCount = RoomMesh.back()->Mesh->Mesh[0].FaceGroup[0].Face.size();
	
	std::vector< int > FaceHack;
	for ( int idx = 0; idx < FaceCount*3; idx++ ) {
		FaceHack.push_back( Faces[idx] );
	}

	RoomMesh.back()->PhysicsObject = Physics.AddStaticMesh( 
		RoomMesh.back()->Pos, RoomMesh.back()->Scalar, 
		
		(float*)&(RoomMesh.back()->Mesh->Mesh[0].Vertex[0].Pos), 
		RoomMesh.back()->Mesh->Mesh[0].Vertex.size(), 
		sizeof(cPMEVertex),
		
		&(FaceHack[0]), 
		FaceCount
		);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::Init() {
	Log( "+ Start of Init..." );
	
	// Initialize the Virtual Machine... //
	vm_Init();
	
	extern int LogLevel;
	LogLevel = 2;

	InitScripts();
	LoadScripts();
	
	Physics.Init();
	
	// *** //
	
	// Create the FBO Target Texture //
	glGenTextures(1, &FBOTextureId);
	glBindTexture(GL_TEXTURE_2D, FBOTextureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FBOSize, FBOSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Create the FBO Target RBO (for non color data storage - depth, stencil, etc) //
//	glGenRenderbuffersEXT(1, &RBODepthId);
//	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rboId);
//	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, TEXTURE_WIDTH, TEXTURE_HEIGHT);
//	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	// Create FBO //
	glGenFramebuffersEXT(1, &FBOId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOId);

	// Attach the Texture to the FBO //
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, FBOTextureId, 0);

//	// attach the renderbuffer to depth attachment point
//	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, RBOId);

	// check FBO status
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if ( status != GL_FRAMEBUFFER_COMPLETE_EXT )
		Log( "ERROR: FBO Unavailable!" );

	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	// *** //
	
	// Store the current clock, so the content scanner can know to disregard extra scans //
	LastContentScan = GetTimeNow();

	// Some Art Assets //
	txCursorMove = AssetPool::Load( "/Cursor_Move" );
	txCursorStop = AssetPool::Load( "/Cursor_Stop" );
	txCursorAttack = AssetPool::Load( "/Cursor_Attack" );

	// Reset Camera //
	CameraWorldPos = Vector3D(0,0,0);
	CameraFollow = 0;	

	// Add Rooms //	
	AddOldRoom( Vector3D(0,0+512,0), "Content/Tests/Room01.tga" );
	AddOldRoom( Vector3D(128,256+512,0), "Content/Tests/Room02.tga" );
	AddOldRoom( Vector3D(128,512+512,0), "Content/Tests/Room03.tga" );
	AddOldRoom( Vector3D(256+128,512+512,0), "Content/Tests/Room04.tga" );
	
	// Add some Objects //
	AddObject( Vector3D(0,0,32+16), "Content/Objects/Discs/Player_disc.json", Real(12) );
	Obj.back()->IsGlowing = true;
	AddObject( Vector3D(0,32,32+16), "Content/Objects/Discs/Bat_disc.json", Real(12) );

	// Follow the 1st object //
	CameraFollow = Obj[0];

	AddObject3D( Vector3D( 32, 32, 32+16 ), "/Skull", Real(12) );
	Obj3.back()->Color = GEL_RGB_RED;
	Obj3.back()->IsGlowing = true;

	AddObject3D( Vector3D( 32+32, 32, 32+16 ), "/Skull", Real(8) );
	AddObject3D( Vector3D( 32+64, 32, 32+16 ), "/Bottle", Real(8) );

	AddObject3D( Vector3D( 32, 32+32, 32+16 ), "/Book_Open", Real(8) );
	AddObject3D( Vector3D( 32+32, 32+32, 32+16 ), "/Shield", Real(6) );
	AddObject3D( Vector3D( 32+64, 32+32, 32+16 ), "/Shield", Real(8) );
	AddObject3D( Vector3D( 32, 32+64, 32+16 ), "/CandleStick", Real(8) );
	AddObject3D( Vector3D( 32+32, 64+32, 32+16 ), "/Key_Boxy", Real(4) );
	AddObject3D( Vector3D( 32+64, 64+32, 32+16 ), "/Key_Boxy", Real(8) );
	AddObject3D( Vector3D( 32, 32+64, 32 ), "/Table_SquareCenter", Real(8) );
	AddObject3D( Vector3D( -108, 32, 64+32 ), "/Sword.dae", Real(20) );
	AddObject3D( Vector3D( 0, -48, 64+16 ), "/Sword.dae", Real(10) );
	Obj3.back()->IsGlowing = true;

	AddOldRoomMesh( Vector3D( 0, 0, 0 ), "Content/Models/Native/RockTest.dae" );

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

	for ( int idx = 0; idx < RoomMesh.size(); idx++ ) {
		Physics.Remove( RoomMesh[idx]->PhysicsObject );
		delete RoomMesh[idx]->Mesh;
		delete RoomMesh[idx];
	}

	for ( int idx = 0; idx < Room.size(); idx++ ) {
		Physics.Remove( Room[idx]->PhysicsObject );
		
		delete_Triangles( Room[idx]->Vert, Room[idx]->Index );
		delete_OutlineList( Room[idx]->OutlineIndex );
		delete_Grid2D( Room[idx]->Grid );
	}
	
	glDeleteFramebuffers( 1, &FBOId );
//	glDeleteRenderbuffers( 1, &RBOId );
	glDeleteTextures( 1, &FBOTextureId );
	
	
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
	gelEnableDepthWriting();
	
	gelSetClearColor( GEL_RGB_BLACK );
	gelClear();
	gelClearDepth();

	Matrix4x4 Look = Calc_LookAt( Vector3D(0,256,1024), Vector3D(0,0,0) );
//	Matrix4x4 Look = Calc_LookAt( Vector3D(0,32,1024), Vector3D(0,0,0) );
	
	gelEnableAlphaBlending();

	// Main Render //
	{
		// Camera //
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.50;

		gelSetDepthRange( 0, 1 );
		gelSetDepthFunc( GEL_LESSEQUAL );
		
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
		ModelViewMatrix = Matrix4x4::TranslationMatrix( -CameraWorldPos - Vector3D(0,-50,-160) ) * ModelViewMatrix;

		gelEnableDepthWriting();
		gelEnableDepthTest();

		gelDrawModeColors();	
		for ( int idx = 0; idx < Room.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			Room[idx]->Draw();
		}

		gelDrawModeTextured();	
		for ( int idx = 0; idx < RoomMesh.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			RoomMesh[idx]->Draw();
		}

		//gelDrawModeFlat();
		//gelDrawModeColors();
		gelDrawModeTextured();	
		// Monkey Head //
		for ( int idx = 0; idx < Obj3.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			// Changing Alpha no longer works because depth test is removing backfaces //
//			gelSetColor( GEL_RGBA(255-(int)(Obj3[idx]->Scalar*Real(32)),0,0,255) );
			Obj3[idx]->Draw();
//			gelSetColor( GEL_RGB_DEFAULT );
		}

		gelDisableDepthWriting();
		
		// Alpha Testing will not work here. I need to disable writing, and sort them relative camera //
		gelDrawModeTextured();		
		for ( int idx = 0; idx < Obj.size(); idx++ ) {
			gelLoadMatrix( ModelViewMatrix );
			Obj[idx]->Draw();
		}
		gelSetColor( GEL_RGB_DEFAULT );
				
		gelDisableDepthTest();

		if ( CameraFollow ) {
			gelLoadMatrix( ModelViewMatrix );
			
			gelDrawModeTextured();
			AssetPool::Set( txCursorAttack );

			gelDrawSquareFillTextured( CameraFollow->Pos + -Input_MoveStick.ToVector3D() * Real(24), Real(6), GEL_RGB(255,242,0) );
		}		
	}


	// Draw to the FBO //
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBOId);
	gelDisableBlending();

	// Update Proxy settings to reflect the FBO //
	int BufferSize = FBOSize;
	ProxyScreen::Width = BufferSize;
	ProxyScreen::Height = BufferSize / ActualScreen::AspectRatio;
	gelCalculateProxyScreenShape();

	// Fill with dummy color //
	glViewport( 
		0,
		0,
		ProxyScreen::Width, 
		ProxyScreen::Width
		);
	gelResetNativeClip();		
	gelSetClearColor( GEL_RGB(64,0,0) );
	gelClear();

	// Correct Shape //
	glViewport( 
		0,
		0,
		ProxyScreen::Width, 
		ProxyScreen::Height
		);
		
	// Load the proxy clipping coords //
	gelResetProxyClip();
	
	gelSetClearColor( GEL_RGBA(255,255,255,0) );
//	gelSetClearColor( GEL_RGB_BLACK );
	gelClear();


	gelEnableAlphaBlending();

	// Glow Render //
	{
		// Camera //
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.50;
		
		Real CameraPos = Near + ((Far - Near) * PlanePos);
		
		int ScWidth = ActualScreen::Width;
		int ScHeight = ActualScreen::Height;

		Real EffectWidth = ScWidth / RefScreen::Scalar;
		Real EffectHeight = ScHeight / RefScreen::Scalar;

		CameraMatrix = Look * Matrix4x4::TranslationMatrix( Vector3D( 0, 0, CameraPos ) );
		ViewMatrix = Calc_Frustum_PerspectiveProjection( 
			EffectWidth,
			EffectHeight,
			Real( Near ),
			Real( Far ),
			Real( PlanePos )
			);
	
		ModelViewMatrix = ViewMatrix;
		ModelViewMatrix = CameraMatrix * ModelViewMatrix;
		ModelViewMatrix = Matrix4x4::TranslationMatrix( -CameraWorldPos - Vector3D(0,-50,-160) ) * ModelViewMatrix;

		// NOTE: Glows will always overlay, since we are not referencing the original Z buffer, and testing vs. //
		gelDisableDepthWriting();
		gelDisableDepthTest();
	
	
		// Alpha Testing will not work here. I need to disable writing, and sort them relative camera //

		gelDrawModeFlat();	
		for ( int idx = 0; idx < Obj3.size(); idx++ ) {
			if ( Obj3[idx]->IsGlowing ) {
				gelLoadMatrix( ModelViewMatrix );
				Obj3[idx]->DrawGlow();
			}
		}

		gelDrawModeTextured();		
		for ( int idx = 0; idx < Obj.size(); idx++ ) {
			if ( Obj[idx]->IsGlowing ) {
				gelLoadMatrix( ModelViewMatrix );
				Obj[idx]->DrawGlow();
			}
		}
		gelSetColor( GEL_RGB_DEFAULT );	
	}

	glViewport( 
		0,
		0, 
//		NativeScreen::Width, 
//		NativeScreen::Height
		ActualScreen::Width, 
		ActualScreen::Height
		);
		
	// Restore regular clipping coords //
	gelResetClip();
	// Unbind the FBO //
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	// Reset Camera for UI //
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

		// Draw Color Buffer to screen //
		glBindTexture(GL_TEXTURE_2D, FBOTextureId);	
		gelDrawModeTextured();
		
		int Scalar = FullRefScreen::Width>>1;
		int UnusedPixels = (ProxyScreen::Width - ProxyScreen::Height)>>1;
		Real UnusedSpace = Real(UnusedPixels) / Real(ProxyScreen::Width);
		Real Offset = UnusedSpace * Real(Scalar+Scalar);

		gelSetColor( GEL_RGBA(255,255,255,16) );
		gelDrawRectFillTextured( 
			Vector3D( -Scalar, Scalar - Offset + 4, 0 ),
			Vector3D( Scalar, -Scalar - Offset + 4, 0 )
			);
		gelDrawRectFillTextured( 
			Vector3D( -Scalar, Scalar - Offset - 4, 0 ),
			Vector3D( Scalar, -Scalar - Offset - 4, 0 )
			);
		gelDrawRectFillTextured( 
			Vector3D( -Scalar + 4, Scalar - Offset, 0 ),
			Vector3D( Scalar  + 4, -Scalar - Offset, 0 )
			);
		gelDrawRectFillTextured( 
			Vector3D( -Scalar - 4, Scalar - Offset, 0 ),
			Vector3D( Scalar  - 4, -Scalar - Offset, 0 )
			);
			
		gelSetColor( GEL_RGBA(255,255,255,32) );
		gelDrawRectFillTextured( 
			Vector3D( -Scalar + 2, Scalar - Offset  + 2, 0 ),
			Vector3D( Scalar  + 2, -Scalar - Offset + 2, 0 )
			);
		gelDrawRectFillTextured( 
			Vector3D( -Scalar + 2, Scalar - Offset  - 2, 0 ),
			Vector3D( Scalar  + 2, -Scalar - Offset - 2, 0 )
			);
		gelDrawRectFillTextured( 
			Vector3D( -Scalar - 2, Scalar - Offset  + 2, 0 ),
			Vector3D( Scalar  - 2, -Scalar - Offset + 2, 0 )
			);
		gelDrawRectFillTextured( 
			Vector3D( -Scalar - 2, Scalar - Offset  - 2, 0 ),
			Vector3D( Scalar  - 2, -Scalar - Offset - 2, 0 )
			);
			
//		gelSetColor( GEL_RGBA(255,255,255,128) );
//		gelDrawRectFillTextured( 
//			Vector3D( -Scalar, Scalar - Offset, 0 ),
//			Vector3D( Scalar, -Scalar - Offset, 0 )
//			);

		gelSetColor( GEL_RGB_DEFAULT );
		
		gelEnableAlphaBlending();
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
