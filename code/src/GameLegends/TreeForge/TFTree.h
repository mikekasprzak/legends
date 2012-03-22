// - ------------------------------------------------------------------------------------------ - //
#ifndef __TreeForge_TFTree_H__
#define __TreeForge_TFTree_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
#define TF_MAX_CHILDREN	7
// - ------------------------------------------------------------------------------------------ - //
class cTFNode {
public:
	cTFNode* Parent;					// NULL if the root node //
	cTFNode* Child[TF_MAX_CHILDREN];	// NULL if the end node of a branch //
	
	int Depth;							// Used by Algorithms to weigh the effect //
	Real Radius;						// Size of the Capsule End //
	
	Vector3D Offset;					// Positional offset from the last node //

public:
	cTFNode() {
	}
	
	cTFNode( const int _Depth, const Real _Radius ) :
		Depth( _Depth ),
		Radius( _Radius )
	{	
		// Clear the children //
		for ( int idx = 0; idx < TF_MAX_CHILDREN; idx++ ) {
			Child[idx] = 0;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cTFTree {
public:
	cTFNode* Root;		// Where a tree begins //
public:
	// Defaults //
	cTFTree() :
		Root( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cTFGenerator {
public:
	// Trees grow towards the sun's heat. Generally speaking that's almayst always up, because once //
	// the sun crosses the horizon, the heat is no longer felt by the tree. Noon will almost always //
	// be the hottest point of the sun, creating a general average that encourages them upward. //
	Vector3D SunDirection;		// A normalized up vector describing which way a tree wants to grow. //
	Vector3D HorizonDirection;	// A normalized reference vector along the horizon/ground plane. //
	
	Real RootRadius;			// Starting fatness of the tree //
	
public:
	cTFGenerator() :
		SunDirection( 0, 1, 0 ),		// TIP: Y should NEVER be zero. //
		HorizonDirection( 0, 0, 1 ), 	// If the sun is never 0, this can be constant. Sun CROSS Horizon = Basis. //
		
		RootRadius( Real(32.0f) )
	{
	}
	
public:
	cTFTree* Generate() {
		cTFTree* Tree = new cTFTree();
		Tree.Root = new cTFNode( 0, RootRadius );
		Tree.Root->Offset = Vector3D::Zero;
		Tree.Root->Parent = 0; // NULL //
		
		
		return Tree;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __TreeForge_TFTree_H__ //
// - ------------------------------------------------------------------------------------------ - //
