// - ------------------------------------------------------------------------------------------ - //
#ifndef __LEGENDS_PHYSICS_H__
#define __LEGENDS_PHYSICS_H__
// - ------------------------------------------------------------------------------------------ - //
// Include this first, as I know how the rest of the code works... well, most of it. Later didn't work //
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Grid/Grid2D.h>

#include <vector>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cPhysicsObject {
public:
	cPhysicsObject() :
		Mesh( 0 )
	{
	}
	
	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	
	btTriangleIndexVertexArray* Mesh;	// Optional //
	
	btTransform trans;
	
	inline void UpdateTransform() {
		rigidBody->getMotionState()->getWorldTransform(trans);
	}
	
	void Step() {
		UpdateTransform();
	}
	
	inline Vector3D GetPos() const {
		return Vector3D( trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() );
	}

	inline Matrix3x3 GetBasis() const {
		btVector3 c1( trans.getBasis().getColumn(0) );
		btVector3 c2( trans.getBasis().getColumn(1) );
		btVector3 c3( trans.getBasis().getColumn(2) );
		
		return Matrix3x3( 
			Vector3D( *((Vector3D*)&c1) ),
			Vector3D( *((Vector3D*)&c2) ),
			Vector3D( *((Vector3D*)&c3) )
			);
	}
	
	inline void Exit() {
		delete rigidBody->getMotionState();
		delete rigidBody;
		delete shape;
				
		if ( Mesh != 0 ) {
			delete Mesh;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cPhysics {
public:
	void Init();
	void Exit();
	
	void Step();
	
	cPhysicsObject* AddBall( Vector3D& Pos, Real Radius ) {
		cPhysicsObject* obj = new cPhysicsObject;
		
		// Create a ball (radius) //
		obj->shape = new btSphereShape( Radius );
		
		// Ball Orientation //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3( Pos.x, Pos.y, Pos.z ) ) );

		btScalar ballMass = 2;
		btVector3 ballInertia(0,0,0);
		obj->shape->calculateLocalInertia( ballMass, ballInertia );

		btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI( ballMass, obj->motionState, obj->shape, ballInertia );
		obj->rigidBody = new btRigidBody( ballRigidBodyCI );
		
		dynamicsWorld->addRigidBody( obj->rigidBody );
		
		obj->UpdateTransform();
		
		return obj;
	}	
	
	cPhysicsObject* AddSphere( Vector3D& Pos, Real Radius ) {
		cPhysicsObject* obj = new cPhysicsObject;
		
		// Create a sphere (radius) //
		obj->shape = new btSphereShape( Radius );
		
		// Ball Orientation //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3( Pos.x, Pos.y, Pos.z ) ) );

		btScalar ballMass = 2;
		btVector3 ballInertia(0,0,0);
		obj->shape->calculateLocalInertia( ballMass, ballInertia );

		btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI( ballMass, obj->motionState, obj->shape, ballInertia );
		obj->rigidBody = new btRigidBody( ballRigidBodyCI );
		
		// Amount to constrain by each axis //
		obj->rigidBody->setAngularFactor( btVector3(0,0,0) );	// Rotation //
		//obj->rigidBody->setLinearFactor( btVector3(0,0,1) );	// Translation //
		
		dynamicsWorld->addRigidBody( obj->rigidBody );
		
		obj->UpdateTransform();
		
		return obj;
	}
	
	cPhysicsObject* AddConvexHull( Vector3D& Pos, Real Radius, float* Points, int Count, int Size ) {
		cPhysicsObject* obj = new cPhysicsObject;
		
		// Create a ball (radius) //
		obj->shape = new btConvexHullShape(
			(btScalar*)Points, Count, Size
			);
		
		// Ball Orientation //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3( Pos.x, Pos.y, Pos.z ) ) );
		
		obj->shape->setLocalScaling( btVector3( Radius, Radius, Radius ) );

		btScalar ballMass = 1;
		btVector3 ballInertia(0,0,0);
		obj->shape->calculateLocalInertia( ballMass, ballInertia );

		btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI( ballMass, obj->motionState, obj->shape, ballInertia );
		obj->rigidBody = new btRigidBody( ballRigidBodyCI );
		
		dynamicsWorld->addRigidBody( obj->rigidBody );
		
		obj->UpdateTransform();
		
		return obj;
	}
	
	cPhysicsObject* AddStaticPlane( ) {
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

		obj->UpdateTransform();
		
		return obj;
	}

	cPhysicsObject* AddStaticHeightMap( Vector3D& Pos, Grid2D<unsigned char>& Grid, const Real Scale ) {
		cPhysicsObject* obj = new cPhysicsObject;

		// Create a Heightmap //
		obj->shape = new btHeightfieldTerrainShape( 
			Grid.w,
			Grid.h,
			&Grid.Data[0],
			0.128f,				// Scale //
			0, 32,			// MIN, MAX //
			2, 				// Up Axis (x=0,y=1,z=2),
			PHY_UCHAR, 		// PHY_SHORT, PHY_FLOAT
			false
			);

		obj->shape->setLocalScaling( btVector3( (float)Scale/32.0f, (float)Scale/32.0f, (float)Scale/64.0f ) );

		// Heightmap Orientation (quaternion) and position (vector) //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3( Pos.x, Pos.y, 32.0f+Pos.z ) ) );
		// Configure construction: Mass, MotionState, Shape, Inertia //
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI( 0, obj->motionState, obj->shape, btVector3(0,0,0) );
		// Create //
		obj->rigidBody = new btRigidBody( groundRigidBodyCI );
		
		// Add to the world //
		dynamicsWorld->addRigidBody( obj->rigidBody );

		obj->UpdateTransform();
		
		return obj;
	}


	cPhysicsObject* AddStaticMesh(
		Vector3D& Pos, Real Radius, 
		float* Verts, unsigned int VertCount, unsigned int VertStride, 
		int* Faces, unsigned int FaceCount 
		)
	{
		cPhysicsObject* obj = new cPhysicsObject;
		
		obj->Mesh = new btTriangleIndexVertexArray(
			FaceCount, Faces, 3 * sizeof(int),
			VertCount, (btScalar*)Verts, VertStride
			);

		// Create a Mesh //
		obj->shape = new btBvhTriangleMeshShape( 
			obj->Mesh,
			true
			);

		obj->shape->setLocalScaling( btVector3( Radius, Radius, Radius ) );

		// Heightmap Orientation (quaternion) and position (vector) //
		obj->motionState = new btDefaultMotionState( btTransform( btQuaternion(0,0,0,1), btVector3( Pos.x, Pos.y, Pos.z ) ) );
		// Configure construction: Mass, MotionState, Shape, Inertia //
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI( 0, obj->motionState, obj->shape, btVector3(0,0,0) );
		// Create //
		obj->rigidBody = new btRigidBody( groundRigidBodyCI );
		
		// Add to the world //
		dynamicsWorld->addRigidBody( obj->rigidBody );

		obj->UpdateTransform();
		
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
