// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_CLASS_BLIT_H__
#define __GEL2_GRID_GRID2D_CLASS_BLIT_H__
// - -------------------------------------------------------------------------------------- - //
//template< typename tType >
//void Grid2D<tType>::Copy(
//	const Grid2D<tType>& Src,
//	const Grid2D<tType>& Dest,
//	const int SrcX,
//	const int SrcY,
//	const int DestX,
//	const int DestY,
//	int Width,
//	int Height
//	)
//{
//	if ( SrcX+Width > Src.Width() ) {
//		Width = Src.Width() - SrcX;
//	}
//	if ( SrcX+Width > Dest.Width() ) {
//		Width = Dest.Width() - SrcX;
//	}
//
//	if ( SrcY+Height > Src.Height() ) {
//		Height = Src.Height() - SrcY;
//	}
//	if ( SrcY+Height > Dest.Height() ) {
//		Height = Dest.Height() - SrcY;
//	}
//	
//	// Copy Data //
//	for ( szt y = Height; y--; ) {
//		for ( szt x = Width; x--; ) {
//			Dest(DestX + x, DestY + y) = Src(SrcX + x, SrcY + y);
//		}
//	}
//}
/*
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
tType* Grid2D<tType>::CopyData(
	const Grid2D<tType>& Src,
	const szt NewWidth,
	const szt NewHeight,
	const int SrcStartX,
	const int SrcStartY,
	const int DestStartX,
	const int DestStartY,
	const tType& InitValue
	)
{
	Grid2D Dest( NewWidth, NewHeight, InitValue );
	//tType* DataCopy = new tType[ NewWidth * NewHeight ];
	//Fill( DataCopy, NewWidth * NewHeight, InitValue );

	return CopyData( Src, Dest, SrcStartX, SrcStartY, DestStartX, DestStartY );
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<tType> Grid2D<tType>::Copy(
	const Grid2D<tType>& Src,
	const szt NewWidth,
	const szt NewHeight,
	const int SrcStartX,
	const int SrcStartY,
	const int DestStartX,
	const int DestStartY,
	const tType& InitValue
	)
{
	Grid2D<tType> NewGrid;
	
	NewGrid.SetData( CopyData( Src, NewWidth, NewHeight, SrcStartX, SrcStartY, DestStartX, DestStartY, InitValue ) );
	NewGrid.w = NewWidth;
	NewGrid.h = NewHeight;
	
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
*/
// - -------------------------------------------------------------------------------------- - //
#define _GRID2D_MERGE_SETUP() \
	/* Top corner of the grid */ \
	int GridX1 = GridAX; \
	int GridY1 = GridAY; \
	\
	if ( GridX1 > GridBX ) \
		GridX1 = GridBX; \
	if ( GridY1 > GridBY ) \
		GridY1 = GridBY; \
	\
	/* Bottom corner of the grid */ \
	int GridX2 = GridAX + GridA.Width(); \
	int GridY2 = GridAY + GridA.Height(); \
	\
	if ( GridX2 < (int)(GridBX + GridB.Width()) ) \
		GridX2 = GridBX + GridB.Width(); \
	if ( GridY2 < (int)(GridBY + GridB.Height()) ) \
		GridY2 = GridBY + GridB.Height(); \
	\
	/* Calculate the dimensions */ \
	int Width = GridX2 - GridX1; \
	int Height = GridY2 - GridY1; \
	\
	/* Calculate Start Positions */ \
	int AX = GridAX - GridX1; \
	int AY = GridAY - GridY1; \
	int BX = GridBX - GridX1; \
	int BY = GridBY - GridY1;
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<tType> Grid2D<tType>::Merge(
	const Grid2D<tType>& GridA,
	const Grid2D<tType>& GridB,
	const int GridAX,
	const int GridAY,
	const int GridBX,
	const int GridBY,
	const tType& InitValue
	)
{
	_GRID2D_MERGE_SETUP();
		
	// Create a Grid to hold our copy //
	Grid2D<tType> NewGrid( Width, Height, InitValue );

	// Copy GridA //
	for ( szt _y = GridA.Height(); _y--; ) {
		for ( szt _x = GridA.Width(); _x--; ) {
			NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
		}
	}

	// Copy GridB //
	for ( szt _y = GridB.Height(); _y--; ) {
		for ( szt _x = GridB.Width(); _x--; ) {
			NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
		}
	}
	
	// Return the grid //
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >	
const Grid2D<tType> Grid2D<tType>::MergeBlend(
	const Grid2D<tType>& GridA,
	const Grid2D<tType>& GridB,
	const int GridAX,
	const int GridAY,
	const int GridBX,
	const int GridBY,
	const tType& TestValue,
	const tType& InitValue
	)
{
	_GRID2D_MERGE_SETUP();
		
	// Create a Grid to hold our copy //
	Grid2D<tType> NewGrid( Width, Height, InitValue );

	// Copy GridA //
	for ( szt _y = GridA.Height(); _y--; ) {
		for ( szt _x = GridA.Width(); _x--; ) {
			if ( GridA( _x, _y ) != TestValue )
				NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
		}
	}

	// Copy GridB //
	for ( szt _y = GridB.Height(); _y--; ) {
		for ( szt _x = GridB.Width(); _x--; ) {
			if ( GridB( _x, _y ) != TestValue )
				NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
		}
	}
	
	// Return the grid //
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<tType> Grid2D<tType>::MergeBlendOnly(
	const Grid2D<tType>& GridA,
	const Grid2D<tType>& GridB,
	const int GridAX,
	const int GridAY,
	const int GridBX,
	const int GridBY,
	const tType& TestValue,
	const tType& InitValue
	)
{
	_GRID2D_MERGE_SETUP();
		
	// Create a Grid to hold our copy //
	Grid2D<tType> NewGrid( Width, Height, InitValue );

	// Copy GridA //
	for ( szt _y = GridA.Height(); _y--; ) {
		for ( szt _x = GridA.Width(); _x--; ) {
			if ( GridA( _x, _y ) == TestValue )
				NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
		}
	}

	// Copy GridB //
	for ( szt _y = GridB.Height(); _y--; ) {
		for ( szt _x = GridB.Width(); _x--; ) {
			if ( GridB( _x, _y ) == TestValue )
				NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
		}
	}
	
	// Return the grid //
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<tType> Grid2D<tType>::MergeBlendOnlyMask(
	const Grid2D<tType>& GridA,
	const Grid2D<tType>& GridB,
	const int GridAX,
	const int GridAY,
	const int GridBX,
	const int GridBY,
	const tType& TestValue,
	const tType& MaskValue,
	const tType& InitValue
	)
{
	_GRID2D_MERGE_SETUP();
		
	// Create a Grid to hold our copy //
	Grid2D<tType> NewGrid( Width, Height, InitValue );

	// Copy GridA //
	for ( szt _y = GridA.Height(); _y--; ) {
		for ( szt _x = GridA.Width(); _x--; ) {
			if ( GridA( _x, _y ) == TestValue )
				NewGrid( AX + _x, AY + _y ) = MaskValue;
		}
	}

	// Copy GridB //
	for ( szt _y = GridB.Height(); _y--; ) {
		for ( szt _x = GridB.Width(); _x--; ) {
			if ( GridB( _x, _y ) == TestValue )
				NewGrid( BX + _x, BY + _y ) = MaskValue;
		}
	}
	
	// Return the grid //
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
template< typename tType >
const Grid2D<tType> Grid2D<tType>::MergeBlendMask(
	const Grid2D<tType>& GridA,
	const Grid2D<tType>& GridB,
	const int GridAX,
	const int GridAY,
	const int GridBX,
	const int GridBY,
	const tType& TestValue,
	const tType& MaskValue,
	const tType& InitValue
	)
{
	_GRID2D_MERGE_SETUP();
		
	// Create a Grid to hold our copy //
	Grid2D<tType> NewGrid( Width, Height, InitValue );

	// Copy GridA //
	for ( szt _y = GridA.Height(); _y--; ) {
		for ( szt _x = GridA.Width(); _x--; ) {
			if ( GridA( _x, _y ) != TestValue )
				NewGrid( AX + _x, AY + _y ) = MaskValue;
		}
	}

	// Copy GridB //
	for ( szt _y = GridB.Height(); _y--; ) {
		for ( szt _x = GridB.Width(); _x--; ) {
			if ( GridB( _x, _y ) != TestValue )
				NewGrid( BX + _x, BY + _y ) = MaskValue;
		}
	}
	
	// Return the grid //
	return NewGrid;
}
// - -------------------------------------------------------------------------------------- - //
#endif // __GEL2_GRID_GRID2D_CLASS_BLIT_H__ //
// - -------------------------------------------------------------------------------------- - //
