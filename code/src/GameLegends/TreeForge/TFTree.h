// - ------------------------------------------------------------------------------------------ - //
#ifndef __TreeForge_TFTree_H__
#define __TreeForge_TFTree_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
class cTFNode {
public:
	// NOTE: Data sorted for improved data alignments //
	
	Vector3D Offset;					// Direction of the segment //
//	Real SegmentLength;					// Length of this branch segment //

	Vector3D Pos;						// Current Position (may change) //
	Real Radius;						// Size of the Capsule End //


	cTFNode* Prev;						// NULL if the start node of a branch //
	cTFNode* Next;						// NULL if the end node of a branch //
	
	cTFNode* Parent;					// Node to socket myself to //
	int Depth;							// Used by Algorithms to weigh the effect //

public:
	inline cTFNode() {
	}
	
	inline cTFNode( const int _Depth, const Real _Radius ) :
		Depth( _Depth ),
		Radius( _Radius ),
		Parent( 0 )
	{	
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cTFBranch {
public:
	cTFNode* Root;					// Where the tree is sprouted from //

public:
	inline cTFBranch() :
		Root( 0 )
	{
	}
	
	inline ~cTFBranch() {
		if ( Root ) {
			cTFNode* CurrentNode = Root;
			while( CurrentNode->Next != 0 ) {
				cTFNode* LastNode = CurrentNode;
				CurrentNode = CurrentNode->Next;
				delete LastNode;
			};
			delete CurrentNode;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cTFTree {
public:
	std::vector<cTFBranch*> Branch;	// All branches of the tree //
		
public:
	// Defaults //
	inline cTFTree()
	{
	}
	
	inline ~cTFTree() {
		for ( int idx = 0; idx < Branch.size(); idx++ ) {
			if ( Branch[idx] != 0 ) {
				delete Branch[idx];
			}
		}
	}

public:
	void GenerateMesh( const int CapsuleSides );
	
	void Draw() {
		for ( int idx = 0; idx < Branch.size(); idx++ ) {
			cTFNode* CurrentNode = Branch[idx]->Root;
			Vector3D Pos = CurrentNode->Offset - Vector3D(0,96,0);
			CurrentNode->Pos = CurrentNode->Offset; // Cache Position //
			
			// If I have a parent set, position myself relative them //
			if ( CurrentNode->Parent ) {
				Pos += CurrentNode->Parent->Pos;
				CurrentNode->Pos += CurrentNode->Parent->Pos;
			}
	
			gelSetColor( GEL_RGB_YELLOW );
			gelDrawDiamond( Pos, CurrentNode->Radius );
			gelSetColor( GEL_RGB_DEFAULT );
			gelDrawCircle( Pos, CurrentNode->Radius );
	
			while( CurrentNode->Next != 0 ) {
				Vector3D NextPos = Pos + CurrentNode->Next->Offset;
				CurrentNode->Next->Pos = CurrentNode->Pos + CurrentNode->Next->Offset; // Cache Position //
				
				gelDrawLine( Pos, NextPos );
				
				Pos = NextPos;
				CurrentNode = CurrentNode->Next;

				gelDrawCircle( Pos, CurrentNode->Radius );
			}
		}
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
	inline cTFGenerator() :
		SunDirection( 0, 1, 0 ),		// TIP: Y should NEVER be zero. //
		HorizonDirection( 0, 0, 1 ), 	// If the sun is never 0, this can be constant. Sun CROSS Horizon = Basis. //
		
		RootRadius( Real(8.0f) )
	{
	}
	
public:
	cTFTree* Generate() {
		cTFTree* Tree = new cTFTree();
		Tree->Branch.push_back( new cTFBranch() );
	
		int Depth = 0;
		int BranchLength = 12 + (rand()&15);
		
		Real Straightness = Real::Random() * Real(0.2f);
		Real RandomAngle = Real::Random();
		Vector3D Tilt( Real::Cos( RandomAngle ), 0, Real::Sin( RandomAngle ) );
		
		Real CurrentRadius( RootRadius );
		Real GrowthLength( 32 );

		Vector3D GrowthDirection = SunDirection;
		GrowthDirection += Tilt * Real( 0.3f );

		RandomAngle = Real::Random();
		Tilt = Vector3D( Real::Cos( RandomAngle ), 0, Real::Sin( RandomAngle ) );
		
		{
			cTFNode* LastNode = new cTFNode( Depth++, CurrentRadius );
			LastNode->Offset = Vector3D::Zero;
			LastNode->Radius = CurrentRadius;
			LastNode->Prev = 0; // NULL //
			
			Tree->Branch.back()->Root = LastNode;	// Store the Root Node //
			
			cTFNode* CurrentNode = 0; // NULL //
						
			for ( int idx = 0; idx < BranchLength; idx++ ) {
				CurrentNode = new cTFNode( Depth++, CurrentRadius );
				LastNode->Next = CurrentNode;
				CurrentNode->Prev = LastNode;
				
				CurrentNode->Offset = (GrowthLength * (Real::Random()+Real(0.5f))) * GrowthDirection;
				CurrentNode->Radius = CurrentRadius;
				
				// Per Segment Tweak //
				GrowthDirection += Tilt * Straightness;
				GrowthDirection.Normalize();
				
				GrowthLength *= 0.85;
				CurrentRadius *= 0.9;
				LastNode = CurrentNode;
			}
			
			CurrentNode->Next = 0; // NULL //
		}
		
		// Add Branches //
		{
			cTFNode* CurrentRootNode = Tree->Branch[0]->Root;
			int MinimumDepth = 1 + (rand() % 3);

			while( CurrentRootNode->Next != 0 ) {
				for ( int NewBranchesCount = 0; NewBranchesCount = rand() % 5; NewBranchesCount++ ) {
					Depth = CurrentRootNode->Depth;
					BranchLength = 3 + (rand()&7);
					
					CurrentRadius = CurrentRootNode->Radius;//Real( RootRadius - Real(0.1f * (float)Depth) );
					GrowthLength = CurrentRootNode->Offset.Magnitude();//Real( 24 );//- Real(8.0f * (float)Depth) );
	
					RandomAngle = Real::Random();
					Tilt = Vector3D( Real::Cos( RandomAngle ), 0, Real::Sin( RandomAngle ) );
	
					GrowthDirection = CurrentRootNode->Offset.Normal();
	//				Matrix3x3 Transform = Matrix3x3::RotateZ( 0.25f );//Matrix3x3::RotateY( RandomAngle ) * Matrix3x3::RotateX( 0.5f );
	//				GrowthDirection.ApplyMatrix( Transform );
	
	//				Vector3D BasisA = cross( GrowthDirection, HorizonDirection );
	//				Vector3D BasisB = cross( BasisA, GrowthDirection );
					GrowthDirection = cross( GrowthDirection, Tilt );
	
	//				//GrowthDirection += Tilt * Real( 0.3f );
	
					Straightness = Real::Random() * Real(0.5f);
	
					RandomAngle = Real::Random();
					Tilt = CurrentRootNode->Offset.Normal();//Vector3D( Real::Cos( RandomAngle ), 0, Real::Sin( RandomAngle ) );
	
					if ( Depth > MinimumDepth ) {
						Tree->Branch.push_back( new cTFBranch() );
						
						cTFNode* LastNode = new cTFNode( Depth++, CurrentRadius );
						LastNode->Offset = Vector3D::Zero;
						LastNode->Radius = CurrentRadius;
						LastNode->Prev = 0; // NULL //
						LastNode->Parent = CurrentRootNode;
						
						Tree->Branch.back()->Root = LastNode;	// Store the Root Node of the new branch //
						
						cTFNode* CurrentNode = 0; // NULL //
								
						for ( int idx = 0; idx < BranchLength; idx++ ) {
							CurrentNode = new cTFNode( Depth++, CurrentRadius );
							LastNode->Next = CurrentNode;
							CurrentNode->Prev = LastNode;
							
							CurrentNode->Offset = (GrowthLength * (Real::Random()+Real(0.5f))) * GrowthDirection;
							CurrentNode->Radius = CurrentRadius;
							
							// Per Segment Tweak //
							GrowthDirection += Tilt * Straightness;
							GrowthDirection.Normalize();
							
							GrowthLength *= 0.8;
							CurrentRadius *= 0.8;
							LastNode = CurrentNode;
						}
						
						CurrentNode->Next = 0; // NULL //				
					}
				}

				CurrentRootNode = CurrentRootNode->Next;
			}				
		}	
		
		return Tree;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __TreeForge_TFTree_H__ //
// - ------------------------------------------------------------------------------------------ - //
