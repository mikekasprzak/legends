// - -------------------------------------------------------------------------------------- - //
#include "Grid2D.h"
#include <Node/DisjointSet.h>
// - -------------------------------------------------------------------------------------- - //
// http://en.wikipedia.org/wiki/Blob_extraction
// http://robotix.in/tutorials/category/imageprocessing/blob_detection
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const NSet2<u16,Grid2D<u16>> BlobExtract( const Grid2D<tType>& Data, const tType Middle ) {
	const u16 BGVal = 0xFFFF;
	u16 NextLabel = 0;
	DisjointSet Linked(0);
	NSet2<u16,Grid2D<u16>> Ret( 0, Grid2D<u16>(Data.Width(),Data.Height(),BGVal) );
			
	// First Pass //
	for ( szt y = 0; y < Data.Height(); y++ ) {
		for ( szt x = 0; x < Data.Width(); x++ ) {
			if ( Data(x,y) >= Middle ) {
//				Log( "%i %i -- %i", x, y, NextLabel );
				enum { N_Size = 2 };
				u16 N[N_Size];
				for ( szt idx = 0; idx < N_Size; idx++ ) {
					N[idx] = BGVal;
				}
				
				if ( (x>0) && (Data(x-1,y) >= Middle) ) {
					N[0] = Ret.b(x-1,y);
				}
				if ( (y>0) && (Data(x,y-1) >= Middle) ) {
					N[1] = Ret.b(x,y-1);
				}

//					if ( Data.Wrap(x-1,y) >= Middle ) {
//						N[0] = Ret.b.Wrap(x-1,y);
//					}
//					if ( Data.Wrap(x,y-1) >= Middle ) {
//						N[1] = Ret.b.Wrap(x,y-1);
//					}
				
				// If Neighbours is Empty //
				if ( AllEq( BGVal, N[0], N[1] ) ) {
					Linked.Add(NextLabel);
					Ret.b(x,y) = NextLabel;
					NextLabel++;
				}
				else {
					Ret.b(x,y) = ::Min( N[0], N[1] );	// Ok, because BGVal is big //
					
					// Perform a union on Neighbours //
					for ( szt idx = 0; idx < N_Size; idx++ ) {
						if ( N[idx] != BGVal ) {
							for ( szt idx2 = idx+1; idx2 < N_Size; idx2++ ) {
								if ( N[idx2] != BGVal ) {
									if ( N[idx] != N[idx2] ) {
										Linked.Union( N[idx], N[idx2] );
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	// Second Pass //
	for ( szt y = 0; y < Data.Height(); y++ ) {
		for ( szt x = 0; x < Data.Width(); x++ ) {
			if ( Data(x,y) >= Middle ) {
//				Log( "> %i %i -- %i", x, y, Ret.b(x,y) );
				Ret.b(x,y) = Linked.Find( Ret.b(x,y) );
			}
		}
	}
	
	return Ret;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<u16> BlobExtractWrapped( const Grid2D<tType>& Data, const tType Middle ) {
	const u16 BGVal = 0xFFFF;
	u16 NextLabel = 0;
	DisjointSet Linked(0);
	Grid2D<u16> Ret( Data.Width(), Data.Height(), BGVal );
			
	// First Pass //
	for ( int y = 0; y < (int)Data.Height()+1; y++ ) {
		for ( int x = 0; x < (int)Data.Width()+1; x++ ) {
			if ( Data.Wrap(x,y) >= Middle ) {
				enum { N_Size = 2 };
				u16 N[N_Size];
				for ( szt idx = 0; idx < N_Size; idx++ ) {
					N[idx] = BGVal;
				}
				
				if ( (Data.Wrap(x-1,y) >= Middle) ) {
					N[0] = Ret.Wrap(x-1,y);
				}
				if ( (Data.Wrap(x,y-1) >= Middle) ) {
					N[1] = Ret.Wrap(x,y-1);
				}
				
				// If Neighbours is Empty //
				if ( AllEq( BGVal, N[0], N[1] ) ) {
					Linked.Add(NextLabel);
					Ret.Wrap(x,y) = NextLabel;
					NextLabel++;
				}
				else {
					Ret.Wrap(x,y) = ::Min( N[0], N[1] );	// Ok, because BGVal is big //
					
					// Perform a union on Neighbours //
					for ( szt idx = 0; idx < N_Size; idx++ ) {
						if ( N[idx] != BGVal ) {
							for ( szt idx2 = idx+1; idx2 < N_Size; idx2++ ) {
								if ( N[idx2] != BGVal ) {
									if ( N[idx] != N[idx2] ) {
										Linked.Union( N[idx], N[idx2] );
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	// Second Pass //
	for ( szt y = 0; y < Data.Height(); y++ ) {
		for ( szt x = 0; x < Data.Width(); x++ ) {
			if ( Data(x,y) >= Middle ) {
				Ret(x,y) = Linked.Find( Ret(x,y) );
			}
		}
	}
	
	return Ret;
}	
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
// Explicit Instances (because we're using a template this is necessary) //
// - -------------------------------------------------------------------------------------- - //
template const NSet2<u16,Grid2D<u16>> BlobExtract<int>( const Grid2D<int>&, const int );
template const NSet2<u16,Grid2D<u16>> BlobExtract<float>( const Grid2D<float>&, const float );
// - -------------------------------------------------------------------------------------- - //
template const Grid2D<u16> BlobExtractWrapped<int>( const Grid2D<int>&, const int );
template const Grid2D<u16> BlobExtractWrapped<float>( const Grid2D<float>&, const float );
// - -------------------------------------------------------------------------------------- - //
