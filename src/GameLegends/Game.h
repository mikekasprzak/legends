// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_H__
#define __Game_H__
// - ------------------------------------------------------------------------------------------ - //
#include <squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>
#include <Object/FdoHeightMap.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Engine/Room.h"
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

	// Script Loading (make this better) //	
	void InitScripts();
	void LoadScripts();
	void ReloadScripts();
	
	GelAssetHandle CoreScript;

public:
	cFdoHeightMap HeightMap;
	Matrix4x4 SpinMatrix;
	Matrix4x4 CameraMatrix;
	
	Matrix4x4 ModelViewMatrix;
	
	Vector3D CameraWorldPos;
public:
	cObject* Obj[2];
	cObject3D* Obj3[2];

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
