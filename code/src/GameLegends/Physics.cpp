// - ------------------------------------------------------------------------------------------ - //
#include "Physics.h"
#include <Debug/GelDebug.h>
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::Init() {
	Log("+ Creating Bullet Simulation\n");
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
}
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::Exit() {
	// Clean up //
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;

	Log("- Done Bullet Simulation\n");
	Log("\n");
}
// - ------------------------------------------------------------------------------------------ - //
void cPhysics::Step() {
	dynamicsWorld->stepSimulation( 1/60.f, 10 );
}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
