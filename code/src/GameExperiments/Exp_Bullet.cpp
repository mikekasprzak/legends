// - ------------------------------------------------------------------------------------------ - //
// Include this first, as I know how the rest of the code works... well, most of it. Later didn't work //
#include <btBulletDynamicsCommon.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>

extern void CallExp_Bullet();
void CallExp_Bullet() {
	Log("+ Now Testing Bullet\n");
	{
		// First we need to pick the broadphase algorithm. I.e. the "are we (maybe) close" check. //
		// Generally there's 2 options. Dbvt works with any size world, SAP has fixed size world //
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();
		
		// Configure the main collision detection system (non-broadphase) //
		btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher( collisionConfiguration );
		
		// The above detects, while this the solver solves and resolves collision constraints //
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
		
		
		// Create our simulation based on the configurations above //
		btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, broadphase, solver, collisionConfiguration );

		// Set Gravity //
		dynamicsWorld->setGravity( btVector3(0,-10,0) );
		
		// Do stuff! //
		{
			// ** Create our Collision Shapes (separate from dynamics... apparently these are wise to re-use) ** //
			// Create a Plane (directional vector and ?? (length?)) //
			btCollisionShape* groundShape = new btStaticPlaneShape( btVector3(0,1,0), 1 );
			// Create a ball (radius) //
			btCollisionShape* ballShape = new btSphereShape(1);
			
			// ** Create our Rigid Bodies (dynamics) ** //
			// Ground Plane Orientation (quaternion) and position (vector) //
			btDefaultMotionState* groundMotionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3(0,-1,0) ) );
			// Configure construction: Mass, MotionState, Shape, Inertia //
			btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI( 0, groundMotionState, groundShape, btVector3(0,0,0) );
			// Create //
			btRigidBody* groundRigidBody = new btRigidBody( groundRigidBodyCI );
			// Add to the world //
			dynamicsWorld->addRigidBody( groundRigidBody );
			
			// Ball Orientation //
			btDefaultMotionState* ballMotionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3(0,50,0) ) );

			btScalar ballMass = 1;
			btVector3 ballInertia(0,0,0);
			ballShape->calculateLocalInertia( ballMass, ballInertia );

			btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI( ballMass, ballMotionState, ballShape, ballInertia );
			btRigidBody* ballRigidBody = new btRigidBody( ballRigidBodyCI );
			
			dynamicsWorld->addRigidBody( ballRigidBody );
			
			// Do Simulation //
			for (int i=0 ; i<300 ; i++) {			
				dynamicsWorld->stepSimulation(1/60.f,10);
				
				btTransform trans;
				ballRigidBody->getMotionState()->getWorldTransform(trans);
				
				Log( "sphere height: %f\n", trans.getOrigin().getY() );
			}

			// Cleanup //
			dynamicsWorld->removeRigidBody(ballRigidBody);
			delete ballRigidBody->getMotionState();
			delete ballRigidBody;
			
			dynamicsWorld->removeRigidBody(groundRigidBody);
			delete groundRigidBody->getMotionState();
			delete groundRigidBody;
			
			
			delete ballShape;
			
			delete groundShape;
		}
		
		// Clean up //
		delete dynamicsWorld;
		delete solver;
		delete dispatcher;
		delete collisionConfiguration;
		delete broadphase;
	}
	Log("- Done Testing Bullet\n");
	Log("\n");
}
