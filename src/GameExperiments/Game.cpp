// - ------------------------------------------------------------------------------------------ - //
// NOTES: 
// - Hey cool, I saw inside TinyXML a suggestion that a handle can be used to simplify if (0) checks.
//   My theroy, implement a member function you use for access, and check the "this" variable if it's
//   zero.  If it's zero, then assume a failed lookup occured and do nothing.
// - Make the new_DataBlock call a bit more obvious that it reads a file
// - Also, give an option to load a datablock with a trailing zero (cJSON wanted this)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
#include <AssetPool/AssetPool.h>
#include <Graphics/GraphicsDraw.h>
#include <Graphics/Mesh/PMEFile.h>
#include <Geometry/Projection/Projection.h>
#include <Geometry/Curve/Curve.h>

#include <Types/Set.h>
#include <Grid/Grid2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Engine/Room.h"
// - ------------------------------------------------------------------------------------------ - //




// - ------------------------------------------------------------------------------------------ - //
//struct VertType {
//	Vector3D Pos;
//};
// - ------------------------------------------------------------------------------------------ - //
//class cRoom {
//public:
//	GelArray<VertType>* Vert;
//	GelArray<unsigned short>* Index;
//	GelArray<unsigned short>* OutlineIndex;
//};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cRoom Room[4];
cPMEFile* Mesh;
// - ------------------------------------------------------------------------------------------ - //

GelAssetHandle txPlayer;
GelAssetHandle txSword;

// - ------------------------------------------------------------------------------------------ - //
void cGame::Init() {
	extern void ExpInit();
	extern void CallExp();
	extern void ExpExit();

	// Run experiments //
	ExpInit();
	CallExp();
	ExpExit();

	// Reset Camera //
	CameraWorldPos = Vector3D(0,0,0);
	CameraEyePos = Vector3D( _TV(0), _TV(-2), _TV(0) ); // TODO: Should be positive //
//	CameraFollow = 0;
	CameraTilt = Vector3D(0,0,1024);

	
	Log("End of Init\n");
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::Exit() {
	delete Obj3[0];
	
	delete Mesh;
	
	delete Obj[0];
	delete Obj[1];

//	delete_Triangles( Room[0].Vert, Room[0].Index );
//	delete_OutlineList( Room[0].OutlineIndex );
//	delete_Triangles( Room[1].Vert, Room[1].Index );
//	delete_OutlineList( Room[1].OutlineIndex );
//	delete_Triangles( Room[2].Vert, Room[2].Index );
//	delete_OutlineList( Room[2].OutlineIndex );
//	delete_Triangles( Room[3].Vert, Room[3].Index );
//	delete_OutlineList( Room[3].OutlineIndex );

}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void cGame::GotFocus() {
//	ContentScan();
}
// - ------------------------------------------------------------------------------------------ - //
void cGame::LostFocus() {
	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::Step() {
	static float Angle = 0;
	Angle += 0.3f;
	
//	SpinMatrix = Matrix4x4::RotationMatrixXZ( Angle );
	SpinMatrix = Matrix4x4::RotationMatrixXY( Angle );

//	static int Xer = 0;
//	Xer++;
//	Vert->Data[indexVertex_Optimized_TriangleStrips(64,Xer&63,Xer&63)].Pos.z+=4;

	Vector2D Stick(0,0);

	{
		Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if ( keystate[SDL_SCANCODE_UP] ) {
			Stick.y = 1.0f;
		}
		if ( keystate[SDL_SCANCODE_DOWN] ) {
			Stick.y = -1.0f;
		}
		if ( keystate[SDL_SCANCODE_LEFT] ) {
			Stick.x = -1.0f;
		}
		if ( keystate[SDL_SCANCODE_RIGHT] ) {
			Stick.x = 1.0f;
		}
		if ( keystate[SDL_SCANCODE_PAGEUP] ) {
			CameraWorldPos += Vector3D(0,0,2.5f);
		}
		if ( keystate[SDL_SCANCODE_PAGEDOWN] ) {
			CameraWorldPos += Vector3D(0,0,-2.5f);
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
	
	CameraWorldPos += Stick.ToVector3D() * Real( 2.5f );

}
// - ------------------------------------------------------------------------------------------ - //
//
//void cGame::DrawRoom( cRoom* ThisRoom, const Vector3D& Offset ) {
//			gelLoadMatrix( ModelViewMatrix );
////			gelLoadMatrix( ViewMatrix );
////			gelMultMatrix( CameraMatrix );
////			gelMultMatrix( SpinMatrix );
//			gelMultMatrix( Matrix4x4::TranslationMatrix( Offset ) );
//			
//			gelDrawIndexedTriangles( ThisRoom->Vert->Data, ThisRoom->Index->Data, ThisRoom->Index->Size, GEL_RGBA(255,255,255,64) );
//////			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->Index->Data, ThisRoom->Index->Size, GEL_RGBA(0,255,0,64) );
//			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->OutlineIndex->Data, ThisRoom->OutlineIndex->Size, GEL_RGBA(0,255,0,64) );
//			gelDrawPoints( ThisRoom->Vert->Data, ThisRoom->Vert->Size, GEL_RGB_YELLOW );
//	
////			gelDrawIndexedTriangleStrip( ThisRoom->Vert->Data, ThisRoom->Index->Data, 1024/*ThisRoom->Index->Size*/, GEL_RGBA(255,255,255,64) );
//////			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->Index->Data, ThisRoom->Index->Size, GEL_RGBA(0,255,0,64) );
////			gelDrawIndexedLines( ThisRoom->Vert->Data, ThisRoom->OutlineIndex->Data, 1024/*ThisRoom->OutlineIndex->Size*/, GEL_RGBA(0,255,0,64) );
////			gelDrawPoints( ThisRoom->Vert->Data, ThisRoom->Vert->Size, GEL_RGB_YELLOW );
//	
////			static int StripNum = 0;
////			StripNum++;
////			StripNum %= indexStripCount_Optimized_TriangleStrips(65);
////			gelDrawIndexedTriangleStrip( 
////				ThisRoom->Vert->Data,
////				&ThisRoom->Index->Data[indexIndex_Optimized_TriangleStrips(65,StripNum,0)],
////				indexStripSize_Optimized_TriangleStrips(65),
////				GEL_RGBA(255,0,0,128)
////				);	
//}
// - ------------------------------------------------------------------------------------------ - //
void cGame::UpdateCameraMatrix() {
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

// - ------------------------------------------------------------------------------------------ - //
void cGame::Draw() {
	gelSetClearColor( GEL_RGB_BLACK );
	gelClear();
	
	UpdateCameraMatrix();


//	Matrix4x4 Look = Calc_LookAt( Vector3D(0,256,1024), Vector3D(0,0,0), Vector3D(0,0,1) );
////	Matrix4x4 Look = Calc_LookAt( Vector3D(0,32,1024), Vector3D(0,0,0) );
//
//	
	gelEnableAlphaBlending();

	gelDrawModeColors();
	gelLoadMatrix( ObserverCamera.ProjectionView );	
	gelDrawLine( Vector3D(-12,-12,0), Vector3D(12,12,0), GEL_RGB_GREEN, GEL_RGB_RED );
	
	/*
	
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
		ModelViewMatrix = Matrix4x4::TranslationMatrix( CameraWorldPos ) * ModelViewMatrix;
	
		gelDrawModeFlat();
		
		DrawRoom( &(Room[0]), Vector3D(0,0,0) );

		// Monkey Head //
		{
			gelLoadMatrix( ModelViewMatrix );
			gelSetColor( GEL_RGBA(255,0,0,64) );
			Obj3[0]->Draw();
			gelSetColor( GEL_RGB_DEFAULT );

//			gelMultMatrix( Matrix4x4::TranslationMatrix( Vector3D( 0, 0, 32+16 ) ) );
//			gelMultMatrix( Matrix4x4::ScalarMatrix( Vector3D( 16, 16, 16 ) ) );
//
//			gelSetColor( GEL_RGBA(255,0,0,64) );
//			gelDrawIndexedTriangles( &(Mesh->Mesh[0].Vertex[0]), (unsigned short*)&(Mesh->Mesh[0].FaceGroup[0].Face[0]), Mesh->Mesh[0].FaceGroup[0].Face.size()*3 );
//			gelSetColor( GEL_RGB_DEFAULT );
		}

		DrawRoom( &(Room[1]), Vector3D(128,256,0) );

		gelDrawModeTextured();
		{
			gelLoadMatrix( ModelViewMatrix );
			Obj[0]->Draw();

			gelLoadMatrix( ModelViewMatrix );
			Obj[1]->Draw();
		}
		
		gelDrawModeFlat();

		DrawRoom( &(Room[2]), Vector3D(128,512,0) );
		DrawRoom( &(Room[3]), Vector3D(256+128,512,0) );
	}
	
	*/
	

/*
	// Reset Camera //
	{
		Real Near = 100;
		Real Length = 800;
		
		Real Far = Near + Length;
		Real PlanePos = 0.5;
		
		Real CameraPos = Near + ((Far - Near) * PlanePos);

		//Matrix4x4 Look2 = Calc_LookAt( Vector3D(0,0,0), Vector3D(0,150,800) );
		Matrix4x4 Look2 = Calc_LookAt( Vector3D(0,0,0), Vector3D(0,0,800), Vector3D(0,0,1) );
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
*/
		gelDrawModeTextured();
		gelLoadMatrix( UICamera.ProjectionView );
		gelSetColor( GEL_RGB_DEFAULT );
		gelEnableAlphaBlending();
}
// - ------------------------------------------------------------------------------------------ - //
