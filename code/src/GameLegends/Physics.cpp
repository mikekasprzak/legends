// - ------------------------------------------------------------------------------------------ - //
#include "Physics.h"
#include <Debug/GelDebug.h>
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::Init() {
	Log("+ Creating Bullet Simulation");
	// First we need to pick the broadphase algorithm. I.e. the "are we (maybe) close" check. //
	// Generally there's 2 options. Dbvt works with any size world, SAP has fixed size world //
	broadphase = new btDbvtBroadphase();
	
	// Configure the main collision detection system (non-broadphase) //
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher( collisionConfiguration );
	
	// The above detects, while this the solver solves and resolves collision constraints //
	solver = new btSequentialImpulseConstraintSolver();
	
	
	// Create our simulation based on the configurations above //
	dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, broadphase, solver, collisionConfiguration );

	// Set Gravity //
	dynamicsWorld->setGravity( btVector3(0,0,-40) );

	Log("- Bullet Simulation Created");
}
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::Exit() {
	Log("+ Shutting Down Bullet Simulation");

	// Clean up //
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;

	Log("- Bullet Simulation Shut Down");
	Log("");
}
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::Step() {
	dynamicsWorld->stepSimulation( 1/60.f, 10 );
}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
