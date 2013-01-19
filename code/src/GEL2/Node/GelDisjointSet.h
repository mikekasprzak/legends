// - ------------------------------------------------------------------------------------------ - //
// Disjoint Set - a Disjointed Set type (used in some algorithms) //
// - ------------------------------------------------------------------------------------------ - //
// http://en.wikipedia.org/wiki/Disjoint-set_data_structure
// http://www2.hawaii.edu/~suthers/courses/ics311f11/Notes/Topic-15/Disjoint-Sets.pdf
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_NODE_DISJOINTSET_H__
#define __GEL2_NODE_DISJOINTSET_H__
// - ------------------------------------------------------------------------------------------ - //
// http://avdongre.wordpress.com/2011/12/06/disjoint-set-data-structure-c/
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
class GelDisjointSet {
public:
	typedef st32 ValType;
	struct Set {
		unsigned int Rank;
		ValType Parent;
		
		Set() :
			Rank(0)
		{
		}

		Set( const ValType i ) : 
			Rank(0),
			Parent(i)
		{
		}
	};
	std::vector<Set> Forest;
	//GelArray<Set>* Forest;

public:
	inline GelDisjointSet( const ValType n ) :
		Forest( 0 )
	{
		Log( "NN %i", n );
		Forest.reserve( n );
		for ( st32 i=0; i<n; i++ ) {
			Forest.push_back( Set(i) );
//			pushback_GelArray( &Forest );//, i );
//			back_GelArray( Forest )->Parent = i;
		}
	}
	
	inline const ValType Find( const ValType i ) {
		if ( Forest[i].Parent == i ) {
			return i;
		}
		else {
			Log( "* %i %x", i, Forest[i].Parent );
			Forest[i].Parent = Find( Forest[i].Parent );
			return Forest[i].Parent;
		}
	}
	
	inline void Union( const ValType i, const ValType j ) {
		Log( "UNE! %i %i", i, j );
		ValType root_i = Find(i);
		ValType root_j = Find(j);
		
		if ( root_i != root_j ) {
			if (Forest[root_i].Rank < Forest[root_j].Rank) {
				Forest[root_i].Parent = root_j;
			}
			else if ( Forest[root_i].Rank > Forest[root_j].Rank ) {
				Forest[root_j].Parent = root_i;
			}
			else {
				Forest[root_i].Parent = root_j;
				Forest[root_j].Rank += 1;
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//#include "GelList.h"
//#include <Core/GelArray.h>
// - ------------------------------------------------------------------------------------------ - //
//template< typename T = int >
//class GelDisjointSet {
//public:
//	// a: Rank, b: Value //
//	typedef NSet2<int,T> DType;
//	typedef GelList<DType>* DisjointType;
//	GelArray<DisjointType>* Set;
//	
//	inline GelDisjointSet() :
//		Set( new_GelArray<DisjointType>(0) )
//	{
//	}
//	
//	inline ~GelDisjointSet() {
//		delete_GelArray<DisjointType>( Set );
//	}
//	
//public:
//	// Add a new Set containing a Rank and Value //
//	inline void MakeSet( const T Val ) {
//		pushback_GelArray<DisjointType>( Set, new_GelList<T>() );
//		back_GelArray<DisjointType>(Set)->PushBack( DType(0,Val) );
//	}
//	
//	
//	inline const T Find( const T Val ) {
//		
//	}
//
//	// 
//	inline void Union( const T Val1, const T Val2 ) {
//	}
//};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_NODE_DISJOINTSET_H__ //
// - ------------------------------------------------------------------------------------------ - //
