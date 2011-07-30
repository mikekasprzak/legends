// - ------------------------------------------------------------------------------------------ - //
#ifndef __Game_H__
#define __Game_H__
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
	cFdoHeightMap HeightMap;
	Matrix4x4 SpinMatrix;
	Matrix4x4 CameraMatrix;
	
	Matrix4x4 ModelViewMatrix;
	
	Vector3D CameraWorldPos;
public:
	cObject* Obj[2];
	cObject3D* Obj3[1];

public:
	cGame() :
		FirstRun( true ),
		Capture( false ),
		
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
