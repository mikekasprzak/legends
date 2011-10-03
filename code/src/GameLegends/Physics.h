// - ------------------------------------------------------------------------------------------ - //
#ifndef __LEGENDS_PHYSICS_H__
#define __LEGENDS_PHYSICS_H__
// - ------------------------------------------------------------------------------------------ - //
// Include this first, as I know how the rest of the code works... well, most of it. Later didn't work //
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Grid/Grid2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cPhysicsObject {
public:
	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	
	btTransform trans;
	
	void Step() {
		rigidBody->getMotionState()->getWorldTransform(trans);
	}
	
	inline Vector3D GetPos() const {
		return Vector3D( trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() );
	}
	
	inline void Exit() {
		delete rigidBody->getMotionState();
		delete rigidBody;
		delete shape;		
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cPhysics {
public:
	void Init();
	void Exit();
	
	void Step();
	
	cPhysicsObject* AddBall( Vector3D& Pos ) {
		cPhysicsObject* obj = new cPhysicsObject;
		
		// Create a ball (radius) //
		obj->shape = new btSphereShape(1);
		
		// Ball Orientation //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3( Pos.x, Pos.y, Pos.z ) ) );

		btScalar ballMass = 1;
		btVector3 ballInertia(0,0,0);
		obj->shape->calculateLocalInertia( ballMass, ballInertia );

		btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI( ballMass, obj->motionState, obj->shape, ballInertia );
		obj->rigidBody = new btRigidBody( ballRigidBodyCI );
		
		dynamicsWorld->addRigidBody( obj->rigidBody );
		
		return obj;
	}
	
	cPhysicsObject* AddPlane( ) {
		cPhysicsObject* obj = new cPhysicsObject;

		// Create a Plane (directional vector and ?? (length?)) //
		obj->shape = new btStaticPlaneShape( btVector3(0,0,1), 1 );

		// Ground Plane Orientation (quaternion) and position (vector) //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3(0,0,-1) ) );
		// Configure construction: Mass, MotionState, Shape, Inertia //
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI( 0, obj->motionState, obj->shape, btVector3(0,0,0) );
		// Create //
		obj->rigidBody = new btRigidBody( groundRigidBodyCI );
		
		// Add to the world //
		dynamicsWorld->addRigidBody( obj->rigidBody );
		
		return obj;
	}

	cPhysicsObject* AddHeightMap( Vector3D& Pos, Grid2D<unsigned char>& Grid ) {
		cPhysicsObject* obj = new cPhysicsObject;

		// Create a Plane (directional vector and ?? (length?)) //
		obj->shape = new btHeightfieldTerrainShape( 
			Grid.w,
			Grid.h,
			&Grid.Data[0],
			1024,			// Scale //
			0, 255,			// MIN, MAX //
			2, 				// Up Axis (x=0,y=1,z=2),
			PHY_UCHAR, 		// PHY_SHORT, PHY_FLOAT
			false
			);

		// Ground Plane Orientation (quaternion) and position (vector) //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3( Pos.x, Pos.y, Pos.z ) ) );
		// Configure construction: Mass, MotionState, Shape, Inertia //
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI( 0, obj->motionState, obj->shape, btVector3(0,0,0) );
		// Create //
		obj->rigidBody = new btRigidBody( groundRigidBodyCI );
		
		// Add to the world //
		dynamicsWorld->addRigidBody( obj->rigidBody );
		
		return obj;
	}
	
	void Remove( cPhysicsObject* obj ) {
		dynamicsWorld->removeRigidBody( obj->rigidBody );
		obj->Exit();
		delete obj;
	}

public:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __LEGENDS_PHYSICS_H__ //
// - ------------------------------------------------------------------------------------------ - //
