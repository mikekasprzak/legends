// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_H__
#define __Game_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Timer/Timer.h>
// - ------------------------------------------------------------------------------------------ - //
#include <squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>
#include <Object/FdoHeightMap.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Physics.h"
#include "Engine/Room.h"
#include "Engine/RoomMesh.h"
#include "Engine/Object.h"
#include "Engine/Object3D.h"
// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	bool FirstRun;
	bool Capture;

public:
	// Virtual Machine Section (Here, and not separate due to ties with rest of engine) //
	HSQUIRRELVM vm;
	static void vm_PrintFunc( HSQUIRRELVM v, const SQChar *s, ... );
	static void vm_ErrorFunc( HSQUIRRELVM v, const SQChar *s, ... );
	
	bool vm_ScriptsLoaded;

	void vm_Init();
	void vm_Exit();
	SQRESULT vm_CompileAndRun( DataBlock* InData, const char* FileName = "" );
	SQRESULT vm_CallFunc( const char* FuncName );
	
	struct vmScript {
		const char* FileName;
		GelAssetHandle Handle;
		
		vmScript() :
			FileName( 0 ),
			Handle( 0 )
		{
		}

		vmScript( const char* _FileName ) :
			FileName( _FileName ),
			Handle( AssetPool::Load( _FileName ) )
		{
		}
	};

	// Script Loading (make this better) //	
	void InitScripts();
	void LoadScripts();
	void ReloadScripts();

	std::vector< vmScript > Script;

	TIMEVALUE LastContentScan;
	void ContentScan();

public:
	cFdoHeightMap HeightMap;
	Matrix4x4 SpinMatrix;
	Matrix4x4 CameraMatrix;
	
	Matrix4x4 ModelViewMatrix;
	
	Vector3D CameraWorldPos;
	Vector3D CameraEyePos;
	cObject* CameraFollow;
	
	Vector2D Input_MoveStick;
	Vector3D Input_MoveTarget; // ?? //
public:
	cPhysics Physics;
	
	std::vector< cObject* > Obj;
	std::vector< cObject3D* > Obj3;
		
	std::vector< int > Obj_Sort;
	std::vector< int > Obj3_Sort;
		
		
	std::vector< cRoom* > Room;
	std::vector< cRoomMesh* > RoomMesh;


	void AddObject( const Vector3D& _Pos, const char* _File, const Real _Scalar = Real(1) );
	void AddObject3D( const Vector3D& _Pos, const char* _File, const Real _Scalar = Real(1) );

	void SortObject();
	void SortObject3D();

	void AddOldRoom( const Vector3D& _Pos, const char* _File, const Real _Scalar = Real(8) );
	void AddOldRoomMesh( const Vector3D& _Pos, const char* _File, const Real _Scalar = Real(2) );

	void LoadMap();
public:
	cGame() :
		FirstRun( true ),
		Capture( false ),
		vm_ScriptsLoaded( false ),
		
		HeightMap(4,4)
	{
		Init();
	}
	
	~cGame() {
		Exit();
	}
	
	void Init();
	void Exit();
	void Step();
	void Draw();
	
	void GotFocus();
	void LostFocus();
	
	
	void DrawRoom( cRoom* ThisRoom, const Vector3D& Offset );
public:
	void ForcePaused() {
	}
	void SaveState() {
	}
	void UpdateUI() {
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Game_H__ //
// - ------------------------------------------------------------------------------------------ - //
